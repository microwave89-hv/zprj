//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuCspLib.c 6     5/22/15 6:07a Crystallee $
//
// $Revision: 6 $
//
// $Date: 5/22/15 6:07a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuCspLib.c $ 
// 
// 6     5/22/15 6:07a Crystallee
// [TAG]  		EIP219394
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Static code analysis issues found in Aptio4 Intel Haswell
// module
// [RootCause]  	Didn't update register content.
// [Solution]  	Update register content.
// 
// 5     8/14/13 4:55a Davidhsieh
// [TAG]  		EIP131295
// [Category]  	Improvement
// [Description]  	Add token to force turbo mode is not supported for i3
// Cpu
// 
// 4     2/07/13 3:56a Hsingyingchung
// [TAG]  		EIP112631
// [Category]  	Improvement
// [Description]  	add IsPowerCycle function.
// 
// 3     11/23/12 2:08a Hsingyingchung
// [TAG]  		EIP99095
// [Category]  	Improvement
// [Description]  	Update by XTU 4.X
// 
// 2     8/21/12 11:28p Davidhsieh
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	EFI_SMM_CPU_PROTOCOL-> ReadSaveState can't get CR4 value
// [RootCause]  	The index for CR4 is incorrect.
// 
// [Solution]  	Correct the index value
// 
// 1     2/07/12 3:58a Davidhsieh
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:        CpuCspLib.c
//
// Description:
//  Contains the CPU library related functions. These functions can be linked
//   with various components in the project.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <efi.h>
#include <token.h>
#include <AmiDxeLib.h>
#include <smm.h>
#include <Pcie.h>

#include "Cpu.h"
#include "CpuCspLib.h"
#include "AmiCspLibInc.h"

#ifndef FV_MICROCODE_BASE
#define FV_MICROCODE_BASE FV_MAIN_BASE
#endif

#define MAX_NR_BUS ((PCIEX_LENGTH/0x100000)-1)

static EFI_GUID gMicrocodeFfsGuid = 
    {0x17088572, 0x377F, 0x44ef, 0x8F, 0x4E, 0xB0, 0x9F, 0xFF, 0x46, 0xA0, 0x70};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsPowerCycle
//
// Description: If Power Cycle is or not.
//
// Input:
//		NULL
//
// Output:
//      UINT8   ,   0 - Not Power Cycle
//                  1 - Power Cycle
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 IsPowerCycle(){
	//
	// This is the sample code for Sharkbay with Lynx Point(ver0.7.0 spec.)
	// Please program properly for your platform
	//                             
	UINT16	Buff16;
	Buff16 = READ_PCI16_SB(0xA2);

	if (((Buff16 & BIT5) != 0) /*&& ((Buff16 & BIT7) != 0)*/) 
	{
		return 0;
	} else {
	    return 1;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PchPmTimerStall
//
// Description:	Delay N*Usec
//
// Input:	UINTN Usec
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PchPmTimerStall (IN UINTN Usec)
{
    UINTN   Counter = Usec * 3;
    UINTN   i;
    UINT32  Data32;
    UINT32  PrevData;

    PrevData = IoRead32(PM_BASE_ADDRESS + 8);
    for (i=0; i < Counter; ) {
       Data32 = IoRead32(PM_BASE_ADDRESS + 8);    
        if (Data32 < PrevData) {        // Reset if there is a overlap
            PrevData=Data32;
            continue;
        }
        i += (Data32 - PrevData); 
        PrevData=Data32;
    }

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PollMailboxReady
//
// Description:	Return OC Mailbox is ready or busy.
//
// Input:	UINT64  *MsrBuf
//
// Output:	UINT8 (1: busy, 0: ready)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 PollMailboxReady()
{
    UINT64 MsrData;
    UINT32 WaitTime = 1000;

    do{
        MsrData = ReadMsr(0x150); //Overclock Mailbox: 0x150
        if(!(Shr64(MsrData,63) & 0x1)) break;
        //gStallPpi->Stall(gPeiServices, gStallPpi, 1000);   //delay 1ms
        PchPmTimerStall(1000);  //delay 1ms
        WaitTime--;
    }while((Shr64(MsrData,63) & 0x1) && WaitTime>0); //check run/busy bit, 1 is busy

    if((Shr64(MsrData,63) & 1) && WaitTime == 0)
        return 1;   //busy
    else
        return 0;   //ready
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ReadMSR150
//
// Description:	Return Msr0x150 data
//
// Input:	UINT64  *MsrBuf
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadMSR150(OUT UINT64 *MsrBuf)
{
    UINT64 MsrData;
    UINT64 MsrDataVerify;

    MsrData = ReadMsr(0x150);

    //gStallPpi->Stall(gPeiServices, gStallPpi, 10000); //wait 10ms
    PchPmTimerStall(10000);  //delay 1ms

    MsrDataVerify = ReadMsr(0x150);

    if((UINT32)MsrData != (UINT32)MsrDataVerify) return EFI_DEVICE_ERROR;
    
    *MsrBuf = MsrData;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetOcCapability
//
// Description:	Get the overclocking capabilities for a given CPU Domain
//              by reading/writing MSR 0x150
//
// Input:	UINT8   DomainID (0:IA, 1:GT, 2:Ring, 3:SA, 4:IOD, 5:IOA)
//          UINT64  *MsrBuf
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetOcCapability(IN UINT8 DomainID, OUT UINT64 *MsrBuf)
{
    UINT64  MsrData;
    if(PollMailboxReady()) return EFI_DEVICE_ERROR;

    MsrData = 0;
    MsrData |= Shl64(DomainID,40);  //Param1
    MsrData |= Shl64(0x01,32);  //Command, Overclocking Capability
    MsrData |= Shl64(0x01,63);  //run/busy bit

    WriteMsr(0x150,MsrData); //Overclock Mailbox: 0x150

    if(PollMailboxReady()) return EFI_DEVICE_ERROR;

    if(ReadMSR150(&MsrData)) return EFI_DEVICE_ERROR;

    *MsrBuf = MsrData;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetSVIDConfig
//
// Description:	Get the SVID Configuration information
//              by reading/writing MSR 0x150
//
// Input:	UINT64  *MsrBuf
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetSVIDConfig(OUT UINT64 *MsrBuf)
{
    UINT64  MsrData;
    if(PollMailboxReady()) return EFI_DEVICE_ERROR;

    MsrData = 0;
    MsrData |= Shl64(0,40);  //Param1, 0 = IVR input
    MsrData |= Shl64(0x12,32);  //Command, Read SVID Config
    MsrData |= Shl64(0x01,63);  //run/busy bit

    WriteMsr(0x150,MsrData); //Overclock Mailbox: 0x150

    if(PollMailboxReady()) return EFI_DEVICE_ERROR;

    if(ReadMSR150(&MsrData)) return EFI_DEVICE_ERROR;

    *MsrBuf = MsrData;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetVoltFreq
//
// Description:	Gets the Voltage and Frequency information for a given CPU domain
//              by reading/writing MSR 0x150
//
// Input:	UINT8   DomainID (0:IA, 1:GT, 2:Ring)
//          UINT64  *MsrBuf
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetVoltFreq(IN UINT8 DomainID, OUT UINT64 *MsrBuf)
{
    UINT64  MsrData;
    if(PollMailboxReady()) return EFI_DEVICE_ERROR;

    MsrData = 0;
    MsrData |= Shl64(DomainID,40);  //Param1, 0 = IVR input
    MsrData |= Shl64(0x10,32);  //Command, Read Voltage/Frequency
    MsrData |= Shl64(0x01,63);  //run/busy bit

    WriteMsr(0x150,MsrData); //Overclock Mailbox: 0x150

    if(PollMailboxReady()) return EFI_DEVICE_ERROR;

    if(ReadMSR150(&MsrData)) return EFI_DEVICE_ERROR;

    *MsrBuf = MsrData;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetFIVRConfig
//
// Description:	Get the FIVR Configuration information
//              by reading/writing MSR 0x150
//
// Input:	UINT64  *MsrBuf
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetFIVRConfig(OUT UINT64 *MsrBuf)
{
    UINT64  MsrData;

    if(PollMailboxReady()) return EFI_DEVICE_ERROR;

    MsrData = 0;
    MsrData |= Shl64(0x0,40);  //Param1
    MsrData |= Shl64(0x14,32);  //Command, Read Misc Global Config
    MsrData |= Shl64(0x01,63);  //run/busy bit

    WriteMsr(0x150,MsrData); //Overclock Mailbox: 0x150

    if(PollMailboxReady()) return EFI_DEVICE_ERROR;

    if(ReadMSR150(&MsrData)) return EFI_DEVICE_ERROR;

    *MsrBuf = MsrData;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	isBCLKRatioSuuported
//
// Description:	Determine if CPU supports BCLK coarse ratio support.
//
// Input:	None
//
// Output:	True if supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN isBCLKRatioSuuported()
{
    UINT32  PciAddress;
    
//    PciAddress = (0x1) << 31 | ((0x0) << 16) | ((0x0) << 11) | ((0x0) << 8) | 0xE4;
	PciAddress = (0x1) << 31 | 0xE4;
    IoWrite32(0x0cf8,PciAddress);
    if ( IoRead32(0x0cfc) & BIT18 ){
       	return FALSE;
    }
	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetCpuSignature
//
// Description: Get the cpu signature.
//
// Input:       VOID
//
// Output:      Cpu Signature
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetCpuSignature()
{
    UINT32 CpuSignature, CpuIdEBX, CpuIdECX, CpuIdEDX;
    CPULib_CpuID(1, &CpuSignature, &CpuIdEBX, &CpuIdECX, &CpuIdEDX);
    return CpuSignature;
}

typedef struct {
    UINT32 Stepping:4;
    UINT32 Model:4;
    UINT32 Family:4;
    UINT32 Type:2;
    UINT32 RV:2;
    UINT32 ExtModel:4;
    UINT32 ExtFamily:8;
} CPU_SIGNATURE;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetCpuFamily
//
// Description: Get the cpu family from signature.
//
// Input:       UINT32 CpuSignature
//
// Output:      UINT32 - Cpu Family
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetCpuFamily(UINT32 CpuSignature)
{
    CPU_SIGNATURE *Signature = (CPU_SIGNATURE*)&CpuSignature;
    return Signature->ExtFamily + Signature->Family;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetCpuModel
//
// Description: Get the cpu model from signature.
//
// Input:       UINT32 CpuSignature
//
// Output:      UINT32 - Cpu Model
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetCpuModel(UINT32 CpuSignature)
{
    CPU_SIGNATURE *Signature = (CPU_SIGNATURE*)&CpuSignature;
    return (Signature->ExtModel << 4) + Signature->Model;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetCpuPlatformId
//
// Description: Get the cpu platform Id.
//
// Input:       VOID
//
// Output:      Cpu Platform Id
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32  GetCpuPlatformId(VOID)
{
    return (UINT32)Shr64(ReadMsr(0x17), 50) & 7;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetSmrrBaseMsr
//
// Description:	Return the Smrr Base Msr
//
// Input:		VOID
//
// Output:		SMRR Base
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32  GetSmrrBaseMsr()
{
    return 0x1f2;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadWriteMsr
//
// Description: This function writes the CPU MSR with the value provided.
//
// Input:
//  Msr     32bit MSR index
//  Value   64bit OR Value
//  Mask    64Bit AND Mask Value
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ReadWriteMsr(UINT32 Msr, UINT64 Value, UINT64 Mask)
{
    UINT64 OrigData = ReadMsr(Msr);
    UINT64 WriteData = (OrigData & Mask) | Value;
    WriteMsr(Msr, WriteData);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumSupportedThreadsPerCore
//
// Description:	Get number of supported threads per core.
//
// Input:   VOID
//
// Output:  UINT8 Number of Threads per core.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 NumSupportedThreadsPerCore()
{
	UINT32	RegEax, RegEbx, RegEcx, RegEdx;

    RegEcx = 0;		
    CPULib_CpuID(0xb, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    return (UINT8)RegEbx;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumSupportedCpuCores
//
// Description:	Get number of supported Cpu Cores per package.
//
// Input:   VOID
//
// Output:  UINT8 Number of supported Cpu Cores per package.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 NumSupportedCpuCores()
{
	UINT32	RegEax, RegEbx, RegEcx, RegEdx;
    UINT8  TotLogicalCpus;
    UINT8  LogicalCpusPerCore;

    RegEcx = 1;		
    CPULib_CpuID(0xb, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    TotLogicalCpus  = (UINT8)RegEbx;

    RegEcx = 0;		
    CPULib_CpuID(0xb, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    LogicalCpusPerCore  = (UINT8)RegEbx;

    return TotLogicalCpus / LogicalCpusPerCore;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumLogicalCpus
//
// Description:	Get number of logical CPUs.
//
// Input:   VOID
//
// Output:  UINT8 Number of logical CPUs.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 NumLogicalCpus()
{
    UINT64  MsrData = ReadMsr(MSR_CORE_THREAD_COUNT);
    return (UINT8)MsrData;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsHtEnabled
//
// Description: Determine if CPU is HT.
//
// Input:   VOID
//
// Output:  True if HT CPU.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsHtEnabled()
{
    UINT8   NumLogCPUs, NumCpuCores;
    UINT64  MsrData = ReadMsr(MSR_CORE_THREAD_COUNT);
    UINT32  CpuSignature = GetCpuSignature() & 0xfffffff0;

    NumCpuCores = (UINT8)((UINT32)MsrData >> 16);

    // Westmere work around
    if (CpuSignature == WESTMERE) NumCpuCores &= 0xf;

    NumLogCPUs = (UINT8)MsrData;

    if ((NumLogCPUs / NumCpuCores) <= 1) return FALSE;
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NumCpuCores
//
// Description: Returns number of CPU Cores
//
// Input: VOID
//
// Output:  Number of CPU Cores.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 NumCpuCores()
{
    UINT32  CpuSignature = GetCpuSignature() & 0xfffffff0;
    UINT64 MsrData = ReadMsr(MSR_CORE_THREAD_COUNT);
    UINT8 NumCpuCores = (UINT8)((UINT32)MsrData >> 16);

    // Westmere work around
    if (CpuSignature == WESTMERE) NumCpuCores &= 0xf;

    return NumCpuCores;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsHt0
//
// Description: Determine if CPU thread is logical CPU 0 executing.
//
// Input: VOID   
//
// Output:  True if logical CPU 0.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsHt0()
{
    UINT32 ApicMask;
    UINT32 ApicId;
    UINT8 ThreadsPerCore = NumSupportedThreadsPerCore();
    UINT32 RegEax, RegEbx, RegEcx, RegEdx;

    if (ThreadsPerCore < 2) return TRUE;    //Check if Ht Capable.
    ApicMask = ThreadsPerCore - 1;

    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    ApicId = RegEbx >> 24; 

    //Use APIC ID to determine if logical CPU.
    if ((ApicId & ApicMask) == 0) return TRUE;  //All logical CPU0 will have bit 0 clear.
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsCore0
//
// Description: Determine if CPU thread is CPU Core 0 executing.
//
// Input:   VOID
//
// Output:  True if logical CPU 0.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsCore0()
{
    UINT32 RegEax, RegEbx, RegEcx, RegEdx;
    UINT8  MaxThreadsPackage;
    UINT32 ApicMask;
    UINT32 ApicId;

    ApicMask = ~(NumSupportedThreadsPerCore() - 1);

    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);

    MaxThreadsPackage = (UINT8)(RegEbx >> 16);
    
    ApicMask &= MaxThreadsPackage - 1;
    ApicId = RegEbx >> 24; 

    //Use APIC ID to determine if logical CPU.
    if ((ApicId & ApicMask) == 0) return TRUE;
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsX64Supported
//
// Description: Determine if CPU supports X64.
//
// Input:   CPU_FEATURES *Features
//
// Output:  True if supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsX64Supported(CPU_FEATURES *Features)
{
    return ((Features->ExtFeatureEdx) >> 29) & 1;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   isXDSupported
//
// Description: Determine if CPU supports Execute Disable.
//
// Input:   CPU_FEATURES *Features
//
// Output:  True if supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN isXDSupported(CPU_FEATURES *Features)
{
    return !!(Features->ExtFeatureEdx & (1 << 20));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	isTurboModeSupported
//
// Description:	Determine if CPU supports Turbo mode.
//
// Input:	None
//
// Output:	True if supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN isTurboModeSupported()
{
	BOOLEAN ret;
	UINT32  RegEax, RegEbx, RegEcx, RegEdx;
	
    UINT64 MsrData = ReadMsr(MSR_IA32_MISC_ENABLE);

#if defined(I3_CPU_NON_TURBO) && (I3_CPU_NON_TURBO == 1)   
{    
    CHAR8   BrandStrBuff[49];
	CHAR8  *BrandString = BrandStrBuff;	
	
    CPULib_CpuID(0x80000002, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    *(UINT32*)BrandString = RegEax; BrandString +=4;
    *(UINT32*)BrandString = RegEbx; BrandString +=4;
    *(UINT32*)BrandString = RegEcx; BrandString +=4;
    *(UINT32*)BrandString = RegEdx; BrandString +=4;
    
    
    CPULib_CpuID(0x80000003, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    *(UINT32*)BrandString = RegEax; BrandString +=4;
    *(UINT32*)BrandString = RegEbx; BrandString +=4;
    *(UINT32*)BrandString = RegEcx; BrandString +=4;
    *(UINT32*)BrandString = RegEdx; BrandString +=4;
    
    CPULib_CpuID(0x80000004, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    *(UINT32*)BrandString = RegEax; BrandString +=4;
    *(UINT32*)BrandString = RegEbx; BrandString +=4;
    *(UINT32*)BrandString = RegEcx; BrandString +=4;
    *(UINT32*)BrandString = RegEdx; BrandString +=4;
    *BrandString = '\0';
    
    BrandString = BrandStrBuff;
    
    while(*BrandString) {        
        if (MemCmp(BrandString, "i3", 2) == 0) return FALSE;
         ++BrandString;
    }    
}
#endif    
	CPULib_CpuID(6, &RegEax, &RegEbx, &RegEcx, &RegEdx);
	ret = ((RegEax >> 1) & 1) | (UINT32) (Shr64(MsrData,TURBO_MODE_DISABLE_BIT) & 1); 
	return ret;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	isFullUnlockCpuSuuported
//
// Description:	Determine if CPU supports Full unlock.
//
// Input:	None
//
// Output:	True if supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN isFullUnlockCpuSuuported()
{
	UINT64	MsrData = ReadMsr(MSR_FLEX_RATIO);
				
	if((UINT32)(Shr64(MsrData, 17)) == 0x7) return TRUE;
	return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	isXETdcTdpLimitSupported
//
// Description:	Determine if CPU supports Programmable TDC/TDP Limit for the Turbo mode.
//
// Input:	None
//
// Output:	True if supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN isXETdcTdpLimitSupported()
{

	BOOLEAN ret;
    	UINT64 MsrData = ReadMsr(MSR_PLATFORM_INFO);
	ret = (UINT32) (MsrData & (1 << XE_TDP_TDC_PROGRAMMABLE_BIT)) ? 1:0; 
	return ret;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	isXECoreRatioLimitSupported
//
// Description:	Determine if CPU supports Programmable Core Ratio Limit for the Turbo mode.
//
// Input:	None
//
// Output:	True if supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

	BOOLEAN isXECoreRatioLimitSupported()
	{
	
		BOOLEAN ret;
	    UINT64 MsrData = ReadMsr(MSR_PLATFORM_INFO);
		ret = (UINT32) (MsrData & (1 << XE_CORE_RATIO_PROGRAMMABLE_BIT)) ? 1:0; 
		return ret;
	}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   isLimitCpuidSupported
//
// Description: Determine if CPU supports limiting CpuId to 3.
//
// Input:   VOID
//
// Output:  True if supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN isLimitCpuidSupported()
{
    UINT32 RegEbx, RegEcx, RegEdx;
    UINT32 LargestCPUIDFunc;
    CPULib_CpuID(0, &LargestCPUIDFunc, &RegEbx, &RegEcx, &RegEdx);
    return LargestCPUIDFunc > 3;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   isMachineCheckSupported
//
// Description: Determine if CPU supports machine check.
//
// Input:   CPU_FEATURES *Features
//
// Output:  True if supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsMachineCheckSupported(CPU_FEATURES *Features)
{
    //Check if MCE and MCA supported.
    return ((Features->FeatureEdx & ((1 << 7) + (1 << 14))) == ((1 << 7) + (1 << 14)));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsVmxSupported
//
// Description: Determine if CPU supports VT extensions Vmx.
//
// Input:   CPU_FEATURES *Features
//
// Output:  True if Vmx supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsVmxSupported(CPU_FEATURES *Features)
{
    return Features->FeatureEcx & (1 << 5);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsSmxSupported
//
// Description: Determine if CPU supports VT extensions Smx.
//
// Input:   CPU_FEATURES *Features
//
// Output:  True if Smx supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsSmxSupported(CPU_FEATURES *Features)
{
    return Features->FeatureEcx & (1 << 6);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPU_IsSmrrSupported
//
// Description: Determine if CPU supports Smrr.
//
// Input:   CPU_FEATURES *Features
//
// Output:  True if Smx supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsSmrrSupported(CPU_FEATURES *Features)
{
    return (BOOLEAN)Features->Flags.SmrrSupport;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsEnergyPerfBiasSupported
//
// Description: Determine if Energy Performance Bias supported.
//
// Input:   VOID
//
// Output:  BOOLEAN - True if Energy Performance Bias supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//	BOOLEAN IsEnergyPerfBiasSupported()
//	{
//	    UINT32 RegEax;
//	    UINT32 RegEbx;
//	    UINT32 RegEcx;
//	    UINT32 RegEdx;
//	
//	    UINT32 CpuSignature = GetCpuSignature();
//	    UINT32 CpuSigNoVer = CpuSignature & 0xfffffff0;
//	    UINT32 CpuVer = CpuSignature & 0xf;
//	
//	    BOOLEAN Support = FALSE;
//	
//	    //This is also used to control setup question. No recommendation in BWG.
//	    //Thus, for now Sandy Bridge Energy Bias Support is coded separately from previous CPUs.
//	    //if (CpuSigNoVer == SANDY_BRIDGE && CpuVer >= 3)
//	    //    return TRUE;
//	 
//	    if (CpuSigNoVer == NEHALEM_EX && CpuVer >= 5) Support = TRUE;
//	    else if (CpuSigNoVer == WESTMERE) Support = TRUE;
//	    else if (CpuSigNoVer == WESTMERE_EX) Support = TRUE;
//	
//	    if (!Support) return FALSE;
//	    ReadWriteMsr(MSR_MISC_PWR_MGMT, (1 << ENG_PERF_BIAS_EN_BIT), (UINT64)-1); //Energy Performance Bias Enable
//	
//	    CPULib_CpuID(6, &RegEax, &RegEbx, &RegEcx, &RegEdx);
//	    return !!(RegEcx & BIT3);
//	}
//	
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsCxInterruptFilteringSupported
//
// Description: Determine if C-state interrupting state supported.
//
// Input:   VOID
//
// Output:  BOOLEAN - True if C-state interrupting supported.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//	BOOLEAN IsCxInterruptFilteringSupported()
//	{
//	    return FALSE;
//	
//	    //Not supported until this is used on a project that can test this functionality.
//	    //DEBUG UINT32 CpuSignature = GetCpuSignature();
//	    //DEBUG if (CpuSignature != 0x00020652) return FALSE;
//	    //DEBUG if ((INT32)Shr64(ReadMsr(MSR_IA32_BIOS_SIGN_ID), 32) < 3) return FALSE;
//	    //DEBUG return TRUE;
//	}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPULib_IsVmxEnabled
//
// Description: Determine if Vmx is enabled.
//
// Input:   VOID
//
// Output:  True if Vmx enabled.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CPULib_IsVmxEnabled()
{
    UINT32 RegEax, RegEbx, RegEcx, RegEdx;
    UINT8  Msr;
    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    if (!(RegEcx & (1 << 5))) return FALSE;

    Msr = (UINT8)ReadMsr(MSR_IA32_FEATURE_CONTROL);
    return !!(Msr & (1 << 2));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPULib_IsSmxEnabled
//
// Description: Determine if Smx is enabled.
//
// Input:   VOID
//
// Output:  True if Smx enabled.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CPULib_IsSmxEnabled()
{
    UINT32 RegEax, RegEbx, RegEcx, RegEdx;
    UINT8  Msr;
    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    if (!(RegEcx & BIT6)) return FALSE;

    Msr = (UINT8)ReadMsr(MSR_IA32_FEATURE_CONTROL);
    return !!(Msr & BIT1);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPULib_IsSmrrEnabled
//
// Description: Determine if Smrr is enabled.
//
// Input:   BOOLEAN
//
// Output:  True if Smrr is enabled.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CPULib_IsSmrrEnabled()
{
    //Once SMRR is enabled, the opened SMM Area can't be read outside of SMM.
#if SMM_CACHE_SUPPORT == 0
    return FALSE;
#else
    //Some CPUs, SMRR has an enable bit. Nehalem only has a capability bit.
    UINT32 MtrrCap = (UINT32)ReadMsr(MSR_IA32_MTRR_CAP);
    return !!(MtrrCap & SMRR_SUPPORT_MASK);
#endif
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPULIB_IsLocalX2ApicEnabled
//
// Description: Get C-state latency.
//
// Input:   VOID
//
// Output:  BOOLEAN - True if enabled
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN CPULib_IsLocalX2ApicEnabled()
{
    UINT32 Msr = (UINT32)ReadMsr(MSR_XAPIC_BASE);
    return !!(Msr & (1 << XAPIC_X2APIC_ENABLE_BIT));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPULib_IsFeatureControlLocked
//
// Description: Check to see if the MSR_IA32_FEATURE_CONTROL is locked.
//
// Input:   VOID
//
// Output:  BOOLEAN - True if MSR_IA32_FEATURE_CONTROL is locked.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CPULib_IsFeatureControlLocked() {
    UINT8 Ia32FeatureCntrl = (UINT8)ReadMsr(MSR_IA32_FEATURE_CONTROL);
    return Ia32FeatureCntrl & 1;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NumberOfCpuSocketsPopulated
//
// Description: Returns number of CPU sockets are populated.
//
// Input:   VOID
//
// Output:  UINT32 - Number of CPU sockets populated.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32  NumberOfCpuSocketsPopulated()
{
#if NUMBER_CPU_SOCKETS > 1
    UINT32  CpuSignature = GetCpuSignature();
    UINT32  CpuSigNoVer  = CpuSignature & 0xfffffff0;
    UINT32 NumCpuSockets = 0;
    UINT32 i;
    UINT32 BusNum;

    //Sandy Bridge Server.
    if (CpuSigNoVer == JAKETOWN) {
        UINT32 *PciAddress = (UINT32*)PCIE_CFG_ADDR(0, 0, 0, 0);
    	if (*PciAddress != 0xffffffff) ++NumCpuSockets;
#if NUMBER_CPU_SOCKETS >= 4
    	PciAddress = (UINT32*)PCIE_CFG_ADDR(0x40, 0, 0, 0);
    	if (*PciAddress != 0xffffffff) ++NumCpuSockets;
#endif
    	PciAddress = (UINT32*)PCIE_CFG_ADDR(0x80, 0, 0, 0);
    	if (*PciAddress != 0xffffffff) ++NumCpuSockets;
#if NUMBER_CPU_SOCKETS >= 4
    	PciAddress = (UINT32*)PCIE_CFG_ADDR(0xc0, 0, 0, 0);
    	if (*PciAddress != 0xffffffff) ++NumCpuSockets;
#endif
        return NumCpuSockets;
    }
    for (i = 0, BusNum = MAX_NR_BUS; i < NUMBER_CPU_SOCKETS; ++i, --BusNum) {
        UINT32 *PciAddress = (UINT32*)PCIE_CFG_ADDR(BusNum, 0, 0, 0);
        if (*PciAddress != 0xffffffff) ++NumCpuSockets;
    }
    return NumCpuSockets;
#else
    return 1;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPULIB_GetCstateLatency
//
// Description: Get C-state latency.
//
// Input:   IN UINT8 Cstate
//
// Output:  UINT32 - C-state latentcy in uS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 CPULIB_GetCstateLatency(IN UINT8 Cstate)
{
    UINT32 CpuSigNoVer = GetCpuSignature() & 0xfffffff0;
    BOOLEAN IsSandyBridge = CpuSigNoVer == SANDY_BRIDGE || CpuSigNoVer == JAKETOWN || CpuSigNoVer == IVY_BRIDGE;

    if (IsSandyBridge) {
        switch(Cstate) {
        case 1: return 1;
        case 3: return 80;
        case 6: return 104;
        case 7: return 109;
        }
    }

    switch(Cstate) {
    case 1: return 3;
    case 3: return 205;
    case 6: return 245;
    case 7: return 245;
    }
    return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPULIB_GetCstatePower
//
// Description: Get C-state power.
//
// Input:   IN UINT8 Cstate
//
// Output:  UINT32 - C-state power in mW.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 CPULIB_GetCstatePower(IN UINT8 Cstate)
{
    switch(Cstate) {
    case 1: return 1000;
    case 3: return 500;
    case 6: return 350;
    case 7: return 200;
    }
    return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: CPULib_FindMicrocodeInFv
//
// Description: Find the microcode address for the CPU calling this in specific firmware volume.
//
// Input: VOID *Fv -- Firmware Volume
//
// Output: VOID * -- 0 if not found or the Microcode Address.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID * CPULib_FindMicrocodeInFv(VOID *Fv)
{
    UINT8  *pEndOfFv = (UINT8*)Fv + ((EFI_FIRMWARE_VOLUME_HEADER*)Fv)->FvLength - 1;
    UINT8  *pFfs = (UINT8*)Fv + ((EFI_FIRMWARE_VOLUME_HEADER*)Fv)->HeaderLength;
    UINT8  *pEndOfFfs;
    UINT32 FfsSize;

    MICROCODE_HEADER  *pUc;
    UINT32 UcSize;
    UINT32 CpuSignature = GetCpuSignature();
    UINT8  CpuFlags = (UINT8)(Shr64(ReadMsr(0x17), 50)) & 7;
    UINT8  UcFlag = 1 << CpuFlags;
   
    //Check for corrupt firmware volume.
    if (((EFI_FIRMWARE_VOLUME_HEADER*)Fv)->Signature != 'HVF_') return 0;
    if (pEndOfFv <= pFfs) return 0;

    while(TRUE) {
        if (*(UINT32*)pFfs == 0xffffffff) return 0;
        if (pFfs >= pEndOfFv) return 0;

        FfsSize = *(UINT32*)&((EFI_FFS_FILE_HEADER*)pFfs)->Size & 0xffffff;

        //Find Microcode file
        if (guidcmp(&((EFI_FFS_FILE_HEADER*)pFfs)->Name, &gMicrocodeFfsGuid) == 0)
            break;
        if ((pFfs + FfsSize) <= pFfs) return 0; //Corruption? 
        pFfs +=  FfsSize;  //Next file.
        pFfs = (UINT8*)(((UINT32)pFfs + 7) & ~7);  //Align on 8 byte boundary.
    }

    pEndOfFfs = pFfs + FfsSize;
#if MPDTable_CREATED
    pEndOfFfs -= *(UINT16*)(pEndOfFfs - 2);  //Last 2 bytes is MPDT Length. Don't look in the MPDT for uC.
#endif

    //Find Microcode
    pUc = (MICROCODE_HEADER*)(pFfs + sizeof(EFI_FFS_FILE_HEADER));    

    while(TRUE) {
        if (pUc->HeaderVersion != 1) return 0;  //End of microcode or corrupt.
        UcSize = pUc->DataSize ? pUc->TotalSize : 2048;

        if (pUc->CpuSignature == CpuSignature && (pUc->Flags & UcFlag))
            break;

        if (pUc->TotalSize > (pUc->DataSize + 48)) {        //Extended signature count.
            MICROCODE_EXT_PROC_SIG_TABLE *SigTable = (MICROCODE_EXT_PROC_SIG_TABLE*)((UINT8*)pUc + pUc->DataSize + 48);
            UINT32 ExtSigCount = SigTable->Count;
            UINT8 i;

            if (ExtSigCount >= 20) return 0;    //Corrupt microcode.

            for (i = 0; i < ExtSigCount; ++i) {
                if (SigTable->ProcSig[i].CpuSignature == CpuSignature && (SigTable->ProcSig[i].Flags & UcFlag)) break;
            }
        }

#if PACK_MICROCODE
        UcSize = (UcSize + (16 - 1)) & ~(16 - 1);
#else
        UcSize = (UcSize + (MICROCODE_BLOCK_SIZE - 1)) & ~(MICROCODE_BLOCK_SIZE - 1);
#endif
        if (((UINT64)(UINTN)pUc + UcSize) >= (UINT64)(UINTN)pEndOfFfs) return 0;   //End of uc or corrupt

        pUc = (MICROCODE_HEADER*)((UINT8*)pUc + UcSize);           
    }
    return pUc; 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: CPULib_FindMicrocode
//
// Description: Find the microcode address for the CPU calling this.
//
// Input: VOID
//
// Output: VOID * -- 0 if not found or the Microcode Address.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID * CPULib_FindMicrocode()
{
    VOID *Microcode;
#if MICROCODE_SPLIT_BB_UPDATE
    Microcode =  CPULib_FindMicrocodeInFv((VOID*)FV_MICROCODE_UPDATE_BASE);
    if (Microcode == NULL) Microcode = CPULib_FindMicrocodeInFv((VOID*)FV_MICROCODE_BASE);
#else
    Microcode =  CPULib_FindMicrocodeInFv((VOID*)FV_MICROCODE_BASE);
#endif
    return Microcode;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: CPULib_GetMicrocodeVer
//
// Description: Get Microcode Version
//
// Input:   VOID
//
// Output:  UINT32 - Microcode Version
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32  CPULib_GetMicrocodeVer()
{
    UINT32 RegEax, RegEbx, RegEcx, RegEdx;

    //Clear IA32_BIOS_SIGN_ID of microcode loaded.
    WriteMsr(MSR_IA32_BIOS_SIGN_ID, 0);

    //Reading CPU ID 1, updates the MSR to the microcode revision.
    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);

    return (UINT32)Shr64(ReadMsr(MSR_IA32_BIOS_SIGN_ID), 32);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SmmBaseChangeCopy
//
// Description: This is SMM code copied to 3000:8000 to set the SmmBase and IED.
//
// Input:   None
//
// Output:  None
//
// Notes:
//      This is in real mode. To generate 16-bit code opcodes, use a small asm
//      file to generate a listing.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//TODO: Move this array into assembly file. It is getting too big.
UINT8 SmmBaseChangeCopy[] =
{                                       //cs = 0x3000
    0x66, 0xb8, 0x00, 0x00, 0x00, 0x00, //0x8000    mov eax, SMM_BASE
    0xbb, 0x00, 0x00,                   //0x8006    mov bx, 0     ;Location SM BASE OFFSET
    0x66, 0x2e, 0x89, 0x07,             //0x8009    mov cs:[bx], eax

    0x66, 0xbb, 0x01, 0x00, 0x00, 0x00, //0x800d    mov ebx, 1
    0x67, 0x66, 0x89, 0x98, 4,0x80,0,0, //0x8013    mov [eax + 8004h], ebx  ;Set SMM initialization
    0x66, 0xb8, 0xff, 0xff, 0xff, 0xff, //0x801b    mov eax, IED_BASE
    0xbb, 0x00, 0x00,                   //0x8021    mov bx, 0     ;Location of IED_SAVESTATE_OFFSET
    0x66, 0x2e, 0x89, 0x07,             //0x8024    mov cs:[bx], eax

    0xbb, 0x00, 0x00,                   //0x8028    mov bx, 0
    0x0b, 0xdb,                         //0x802b    or  bx, bx
    0x75, 0x32,                         //0x802d    jnz FirstIedInit

    0x66, 0x89, 0xc3,                   //0x802f    mov ebx, eax
    0x66, 0x8b, 0xf8,                   //0x8032    mov edi, eax
    0x66, 0x81, 0xc7, 0x0, 0, 0x10, 0,  //0x8035    add edi, 0x10 0000
    0x66, 0xb9, 0x00, 0x20, 0x00, 0x00, //0x803c    mov ecx, 32 * 1024 /4
    0x66, 0x33, 0xc0,                   //0x8042    xor eax, eax
//@@:
    0x66, 0x67, 0xab,                   //0x8045    stosd       //clear IED 32k
    0x67, 0xe2, 0xfa,                   //0x8048    loop @b     

    0x66, 0x89, 0xdf,                   //0x804b    mov edi, ebx
    0x66, 0x81, 0xc7, 0x0, 0, 0x20, 0,  //0x804e    add edi, 0x20 0000
    0x66, 0xb9, 0x00, 0x00, 0x08, 0x00, //0x8055    mov ecx, 0x200000 / 4
//@@:
    0x66, 0x67, 0xab,                   //0x805b    stosd       //clear IED 2MB
    0x67, 0xe2, 0xfa,                   //0x805e    loop @b     

//FirstIedInit:

    0xeb, 0x24,                         //0x8061    jmp NO_SMRR   ;If SMRR, this will be changed to NOPs.
//SMRR:
    0x66, 0xb9, 0x00, 0x00, 0x00, 0x00, //0x8063    mov ecx, 0    ;MSR_SMRR_PHYS_BASE will be updated after copy.
    0x66, 0xb8, 0x00, 0x00, 0x00, 0x00, //0x8069    mov eax, 0    ;This will be updated after copy.
    0x66, 0xba, 0x00, 0x00, 0x00, 0x00, //0x806f    mov edx, 0    ;This will be updated after copy.   
    0x0f, 0x30,                         //0x8075    wrmsr 
    0x66, 0x41,                         //0x8077    inc ecx       ;MSR_SMRR_PHYS_MASK
    0x66, 0xb8, 0x00, 0x00, 0x00, 0x00, //0x8079    mov eax, 0    ;This will be updated after copy.
    0x66, 0xba, 0x00, 0x00, 0x00, 0x00, //0x807f    mov edx, 0    ;This will be updated after copy.
    0x0f, 0x30,                         //0x8085    wrmsr 
//NO_SMRR:
    0xb0, 0x01,                         //0x8087    mov al, 1
    0x2e, 0xa2, 0x8f, 0x80,             //0x8089    mov cs:[0x8076], al     ;set flag
    0x0f, 0xaa,                         //0x808d    rsm
    0x00                                //0x808f    SmmBaseChangeFlag label byte
};

#define SMM_ASM_FIXUP_SMM_BASE                  0x38002
#define SMM_ASM_FIXUP_SMM_BASE_SAVESTATE_OFFSET 0x38007
#define SMM_ASM_FIXUP_IED_BASE                  0x3801d
#define SMM_ASM_FIXUP_IED_SAVESTATE_OFFSET      0x38022
#define SMM_ASM_FIXUP_IED_ZERO_MEM              0x38029
#define SMM_ASM_FIXUP_USE_SMRR                  0x38061
#define SMM_ASM_FIXUP_MSR_SMRR_BASE             0x38065
#define SMM_ASM_FIXUP_SMRR_BASE_EAX             0x3806b
#define SMM_ASM_FIXUP_SMRR_BASE_EDX             0x38071
#define SMM_ASM_FIXUP_SMRR_MASK_EAX             0x3807b
#define SMM_ASM_FIXUP_SMRR_MASK_EDX             0x38081
#define SMM_ASM_BASE_CHANGE_FLAG                0x3808f


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SmmGetBaseSaveBufferSize
//
// Description: Return about of memory required for the SMM handler change.
//
// Input: VOID
//
// Output:
//      UINT32 Amount of memory required for SMM handler change.
//
// Notes:
//      The memory will need to be allocated to use in SmmSetupDefaultHandler.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 SmmGetBaseSaveBufferSize()
{
    return sizeof(SmmBaseChangeCopy) + MAX_SMM_SAVE_STATE_SIZE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SmmSetupDefaultHandler
//
// Description: Save original memory, and copy SMM default handler.
//
// Input:
//      IN VOID     *SmmBaseSaveBuffer
//      IN SMM_HOB  *SmmHob
//
// Output:
//      VOID
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmSetupDefaultHandler(IN VOID *SmmBaseSaveBuffer, IN SMM_HOB *SmmHob)
{
    //Perserve 3000:8000 used by SMM. It will be overwritten.
    MemCpy(SmmBaseSaveBuffer, (VOID*)0x38000, sizeof(SmmBaseChangeCopy));

    MemCpy((UINT8*)SmmBaseSaveBuffer + sizeof(SmmBaseChangeCopy), (UINT8*)0x40000 - MAX_SMM_SAVE_STATE_SIZE, MAX_SMM_SAVE_STATE_SIZE);
    MemCpy((VOID*)0x38000, SmmBaseChangeCopy, sizeof(SmmBaseChangeCopy));

    *(UINT16*)SMM_ASM_FIXUP_SMM_BASE_SAVESTATE_OFFSET = SMM_BASE_SAVE_STATE_OFFSET;
    *(UINT16*)SMM_ASM_FIXUP_IED_SAVESTATE_OFFSET = IED_SAVESTATE_OFFSET;
	*(UINT32*)SMM_ASM_FIXUP_IED_BASE = SmmHob->IedStart;		//IED Start

  //Initialize SMRR
    if(CPULib_IsSmrrEnabled()) {   //Could be disabled. Reset may not clear lock.
        UINT64 TsegMask  = (0xfffffffff & (~(SmmHob->TsegLength - 1))) | (1 << 11);
        *(UINT16*)SMM_ASM_FIXUP_USE_SMRR = 0x9090;               //Jmp changed to NOPs.
        //Update SMRR MSR.
        *(UINT32*)SMM_ASM_FIXUP_MSR_SMRR_BASE = GetSmrrBaseMsr();
        //Update SMRR Base
        *(UINT32*)SMM_ASM_FIXUP_SMRR_BASE_EAX = (UINT32)SmmHob->Tseg | 6;   //Lower 32-bits. 6 = WB.
        *(UINT32*)SMM_ASM_FIXUP_SMRR_BASE_EDX = 0;                          //Upper 32-bits.
        //Update SMRR Mask
        *(UINT32*)SMM_ASM_FIXUP_SMRR_MASK_EAX = (UINT32)TsegMask;           //Lower 32-bits.
        *(UINT32*)SMM_ASM_FIXUP_SMRR_MASK_EDX = 0;                          //Upper 32-bits. SMRR Mask Reserved bits.
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SmmBaseChangeOnCpu
//
// Description: Execute on each CPU to change its own base.
//
// Input:
//      VOID *SmmBase
//
// Output:
//      VOID
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmBaseChangeOnCpu(IN VOID *SmmBase)
{
    *(UINT32*)SMM_ASM_FIXUP_SMM_BASE = (UINT32)SmmBase;
    *(UINT8*)SMM_ASM_BASE_CHANGE_FLAG  = 0;  //Initialize Flag

    //Send SMM IPI
    if (CPULib_IsLocalX2ApicEnabled()) {
        UINT32 ApicId = (UINT32) ReadMsr(MSR_EXT_XAPIC_LOGICAL_APIC_ID);
        ReadWriteMsr(MSR_EXT_XAPIC_ICR,
            Shl64(ApicId, 32) + APIC_NO_SHORT_HAND + APIC_LEVEL_ASSERT + APIC_SMI,
            0xfff32000
        );
    } else {
        UINT8 ApicId = (UINT8)(*(UINT32*)(LOCAL_APIC_BASE + APIC_ID_REGISTER) >> 24);
        MemReadWrite32((UINT32*)(LOCAL_APIC_BASE + APIC_ICR_HIGH_REGISTER), ApicId << 24, 0x00ffffff);
        MemReadWrite32((UINT32*)(LOCAL_APIC_BASE + APIC_ICR_LOW_REGISTER),  APIC_NO_SHORT_HAND + APIC_LEVEL_ASSERT + APIC_SMI, 0);
    }

    while (!(*(volatile UINT8*)SMM_ASM_BASE_CHANGE_FLAG)) CPULib_Pause();    //Wait on Flag
    ++*(UINT16*)SMM_ASM_FIXUP_IED_ZERO_MEM; //Only 0, for first thread to clear IED memory.
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SmmRemoveDefaultHandler
//
// Description: Remove default SMM Handler from memory and restore original data.
//
// Input:
//      IN VOID *SmmBaseSaveBuffer
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmRemoveDefaultHandler(IN VOID *SmmBaseSaveBuffer)
{
    //Restore 3000:8000 overwritten for SMM
    MemCpy((VOID*)0x38000, SmmBaseSaveBuffer, sizeof(SmmBaseChangeCopy));
    MemCpy((UINT8*)0x40000 - MAX_SMM_SAVE_STATE_SIZE, (UINT8*)SmmBaseSaveBuffer + sizeof(SmmBaseChangeCopy), MAX_SMM_SAVE_STATE_SIZE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPUProgramPAMRegisters
//
// Description: Program 0xc0000 - 0xfffff regions to Lock/Unlock.
//
// Input:
//  UINT32 StartAddress
//  UINT32 Length
//  UINT8  Setting
//  UINT32 *Granularity
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CPUProgramPAMRegisters(
    EFI_BOOT_SERVICES       *gBS,
    EFI_RUNTIME_SERVICES    *gRS,
    UINT32  StartAddress,
    UINT32  Length,
    UINT8   Setting,
    UINT32  *Granularity
)
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuLib_SaveCpuState
//
// Description: Save CPU state in SMM.
//
// Input:
//  IN OUT CPU_LIB_SMM_SAVE_RESTORE_DATA *State - Track CPU state.
//
// Output: VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CpuLib_SmmSaveCpuState(IN OUT CPU_LIB_SMM_SAVE_RESTORE_DATA* State)
{
    UINT64 ClkMod = ReadMsr(MSR_IA32_CLOCK_MODULATION);

    State->ClkModEn = (UINT8)ClkMod & CLK_MOD_ENABLE;
    ClkMod &= ~(UINT64)CLK_MOD_ENABLE;
    WriteMsr(MSR_IA32_CLOCK_MODULATION, ClkMod);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuLib_SmmRestoreCpuState
//
// Description: Restore CPU state in SMM.
//
// Input:
//  IN CPU_LIB_SMM_SAVE_RESTORE_DATA *State - Track CPU state.
//
// Output: VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CpuLib_SmmRestoreCpuState(IN CPU_LIB_SMM_SAVE_RESTORE_DATA* State)
{
    if (State->ClkModEn) ReadWriteMsr(MSR_IA32_CLOCK_MODULATION, CLK_MOD_ENABLE, (UINT64)-1);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPU_GetSaveStateId30006
//
// Description:
//  This routines saves the necessary values from Revison 3006
//  SMM save state area.
//
// Input:
//  SmmBase         Pointer to CPU SMM save state.
//  SstSaveState    Pointer to copied SMM save state.
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CPU_GetSaveStateId30006(
    UINT8                   *SmmBase,
    EFI_SMI_CPU_SAVE_STATE  *SstSaveState,
    UINT32                  SmmRevision
)
{
    SstSaveState->SMBASE    = *(UINT32*)(SmmBase + 0xfef8);
    SstSaveState->SMMRevId  = *(UINT32*)(SmmBase + 0xfefc);
#if (((CORE_MAJOR_VERSION << 16) + (CORE_MINOR_VERSION << 8) + CORE_REVISION) > 0x040603)
    SstSaveState->GDTBase   = *(UINT32*)(SmmBase + 0xfe8c);
    SstSaveState->IDTBase   = *(UINT32*)(SmmBase + 0xfe94);
    SstSaveState->CR4       = *(UINT32*)(SmmBase + 0xfe40);
#endif
    SstSaveState->ES        = *(UINT16*)(SmmBase + 0xffa8);
    SstSaveState->CS        = *(UINT16*)(SmmBase + 0xffac);
    SstSaveState->SS        = *(UINT16*)(SmmBase + 0xffb0);
    SstSaveState->DS        = *(UINT16*)(SmmBase + 0xffb4);
    SstSaveState->FS        = *(UINT16*)(SmmBase + 0xffb8);
    SstSaveState->GS        = *(UINT16*)(SmmBase + 0xffbc);
    SstSaveState->LDTBase   = *(UINT32*)(SmmBase + 0xfe9c);
    SstSaveState->TR        = *(UINT32*)(SmmBase + 0xffc4);
    SstSaveState->DR7       = *(UINT32*)(SmmBase + 0xffc8);
    SstSaveState->DR6       = *(UINT32*)(SmmBase + 0xffd0);
    SstSaveState->EAX       = *(UINT32*)(SmmBase + 0xff5c);
    SstSaveState->ECX       = *(UINT32*)(SmmBase + 0xff64);
    SstSaveState->EDX       = *(UINT32*)(SmmBase + 0xff6c);
    SstSaveState->EBX       = *(UINT32*)(SmmBase + 0xff74);
    SstSaveState->ESP       = *(UINT32*)(SmmBase + 0xff7c);
    SstSaveState->EBP       = *(UINT32*)(SmmBase + 0xff84);
    SstSaveState->ESI       = *(UINT32*)(SmmBase + 0xff8c);
    SstSaveState->EDI       = *(UINT32*)(SmmBase + 0xff94);
    SstSaveState->EIP       = *(UINT32*)(SmmBase + 0xffd8);
    SstSaveState->EFLAGS    = *(UINT32*)(SmmBase + 0xffe8);
    SstSaveState->CR3       = *(UINT32*)(SmmBase + 0xfff0);
    SstSaveState->CR0       = *(UINT32*)(SmmBase + 0xfff8);

    if (SmmRevision < 0x30100) {
        SstSaveState->IORestart = *(UINT16*)(SmmBase + 0xff02);
        SstSaveState->AutoHALTRestart = *(UINT16*)(SmmBase + 0xff00);
    } else {
        SstSaveState->AutoHALTRestart   = *(UINT16*)(SmmBase + 0xff02);
        SstSaveState->IORestart = *(UINT16*)(SmmBase + 0xff00);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPU_RestoreSaveStateId30006
//
// Description:
//  This routines restores the necessary values from Revision 3006
//   SMM save state area.
//
// Input:
//  SmmBase         Pointer to SMM save state
//  SstSaveState    Standard SMM save state
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CPU_RestoreSaveStateId30006(
    UINT8                   *SmmBase,
    EFI_SMI_CPU_SAVE_STATE  *SstSaveState,
    UINT32                  SmmRevision
)
{
    *(UINT16*)(SmmBase + 0xffa8)    = SstSaveState->ES;
    *(UINT16*)(SmmBase + 0xffac)    = SstSaveState->CS;
    *(UINT16*)(SmmBase + 0xffb0)    = SstSaveState->SS;
    *(UINT16*)(SmmBase + 0xffb4)    = SstSaveState->DS;
    *(UINT16*)(SmmBase + 0xffb8)    = SstSaveState->FS;
    *(UINT16*)(SmmBase + 0xffbc)    = SstSaveState->GS;
    *(UINT32*)(SmmBase + 0xff5c)    = SstSaveState->EAX;
    *(UINT32*)(SmmBase + 0xff64)    = SstSaveState->ECX;
    *(UINT32*)(SmmBase + 0xff6c)    = SstSaveState->EDX;
    *(UINT32*)(SmmBase + 0xff74)    = SstSaveState->EBX;
    *(UINT32*)(SmmBase + 0xff7c)    = SstSaveState->ESP;
    *(UINT32*)(SmmBase + 0xff84)    = SstSaveState->EBP;
    *(UINT32*)(SmmBase + 0xff8c)    = SstSaveState->ESI;
    *(UINT32*)(SmmBase + 0xff94)    = SstSaveState->EDI;
    *(UINT32*)(SmmBase + 0xffd8)    = SstSaveState->EIP;
    *(UINT32*)(SmmBase + 0xffe8)    = SstSaveState->EFLAGS;

    if (SmmRevision < 0x30100) {
        *(UINT16*)(SmmBase + 0xff02)    = SstSaveState->IORestart;
        *(UINT16*)(SmmBase + 0xff00)    = SstSaveState->AutoHALTRestart;
    } else {
        *(UINT16*)(SmmBase + 0xff02)    = SstSaveState->AutoHALTRestart;
        *(UINT16*)(SmmBase + 0xff00)    = SstSaveState->IORestart;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPU_RestoreDefaultSaveState
//
// Description:
//  This routines copies the necessary values from standard
//   SMM save state area to version 0x30003 SMM save state area.
//
// Input:
//  SmmBase         Pointer to CPU SMM save state.
//  SstSaveState    Pointer to copied SMM save state.
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CPU_RestoreDefaultSaveState
(
    UINT8                       *SmmBase, 
    EFI_SMI_CPU_SAVE_STATE      *SstSaveState
)
{
    EFI_SMI_CPU_SAVE_STATE *SmmSave = (EFI_SMI_CPU_SAVE_STATE*) SmmBase;

    SmmSave->EFLAGS = SstSaveState->EFLAGS;
    SmmSave->EIP = SstSaveState->EIP;
    SmmSave->EDI = SstSaveState->EDI;
    SmmSave->ESI = SstSaveState->ESI;
    SmmSave->EBP = SstSaveState->EBP;
    SmmSave->ESP = SstSaveState->ESP;
    SmmSave->EBX = SstSaveState->EBX;
    SmmSave->EDX = SstSaveState->EDX;
    SmmSave->ECX = SstSaveState->ECX;
    SmmSave->EAX = SstSaveState->EAX;
    SmmSave->AutoHALTRestart = SstSaveState->AutoHALTRestart;
    SmmSave->IORestart = SstSaveState->IORestart;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPU_GetSaveState
//
// Description:
//  This routine is the generic routine used to copy the CPU specific SMM
//   save state to standard save state. 
//
// Input:
//  SmmBase         Pointer to CPU SMM save state.
//  SstSaveState    Pointer to copied SMM save state
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CPU_GetSaveState
(
    UINT8                       *SmmBase, 
    EFI_SMI_CPU_SAVE_STATE      *SstSaveState
)
{
    UINT32 SmmRevision = *(UINT32*)(SmmBase + 0xfefc);

    //Porting Required. PERFORM CPU SPECIFIC save state handling
    if (SmmRevision >= 0x30006) {
        CPU_GetSaveStateId30006(SmmBase, SstSaveState, SmmRevision);
    } else {
        UINTN Index;
        //Copy save state area.
        for (Index = 0; 
                Index < (sizeof(EFI_SMI_CPU_SAVE_STATE) / sizeof(UINT32));
                Index ++) {
            *( ((UINT32 *)SstSaveState) + Index)
                = *( (UINT32 *)(SmmBase + 0xfe00) + Index);
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPU_RestoreSaveState
//
// Description:
//  This routine is the generic routine used to copy the standard 
//  SMM save state from CPU specific save state. This routine 
//  should make sure it does not change read only areas
//
// Input:
//  SmmBase         Pointer to CPU SMM save state.
//  SstSaveState    Pointer to copied SMM save state
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CPU_RestoreSaveState
(
    UINT8                       *SmmBase, 
    EFI_SMI_CPU_SAVE_STATE      *SstSaveState
)
{
    UINT32 SmmRevision = *(UINT32*)(SmmBase + 0xfefc);
    
    //Porting Required. PERFORM CPU SPECIFIC save state handling
    if (SmmRevision >= 0x30006) {
        CPU_RestoreSaveStateId30006(SmmBase, SstSaveState, SmmRevision);
    } else {
        CPU_RestoreDefaultSaveState(SmmBase + 0xfe00, SstSaveState);
    }
}

typedef struct {
    UINT16 SaveStateOffset;
    UINT16 SaveStateWidth;
    UINT16 FrameworkOffset;
    UINT16 FrameworkWidth;
} INTEL_X64_FORMAT;

INTEL_X64_FORMAT gIntelX64Format[] = {
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_GDTBASE = 4
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_IDTBASE = 5
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_LDTBASE = 6
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_GDTLIMIT = 7  No Save State
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_IDTLIMIT = 8  No Save State
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_LDTLIMIT = 9  No Save State
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_LDTINFO = 10  No Save State
    0xffa8, 2, 0x01a8, 2, //EFI_SMM_SAVE_STATE_REGISTER_ES = 20
    0xffac, 2, 0x01ac, 2, //EFI_SMM_SAVE_STATE_REGISTER_CS = 21
    0xffb0, 2, 0x01b0, 2, //EFI_SMM_SAVE_STATE_REGISTER_SS = 22
    0xffb4, 2, 0x01b4, 2, //EFI_SMM_SAVE_STATE_REGISTER_DS = 23
    0xffb8, 2, 0x01b8, 2, //EFI_SMM_SAVE_STATE_REGISTER_FS = 24
    0xffbc, 2, 0x01bc, 2, //EFI_SMM_SAVE_STATE_REGISTER_GS = 25
    0xffc0, 2, 0xffff, 0xff, //EFI_SMM_SAVE_STATE_REGISTER_LDTR_SEL = 26
    0xffc4, 2, 0x01c4, 2,    //EFI_SMM_SAVE_STATE_REGISTER_TR_SEL = 27
    0xffc8, 8, 0x01c8, 4,    //EFI_SMM_SAVE_STATE_REGISTER_DR7 = 28
    0xffd0, 8, 0x01fc, 4,    //EFI_SMM_SAVE_STATE_REGISTER_DR6 = 29
    0xff54, 8, 0xffff, 0xff, //EFI_SMM_SAVE_STATE_REGISTER_R8 = 30
    0xff4c, 8, 0xffff, 0xff, //EFI_SMM_SAVE_STATE_REGISTER_R9 = 31
    0xff44, 8, 0xffff, 0xff, //EFI_SMM_SAVE_STATE_REGISTER_R10 = 32
    0xff3c, 8, 0xffff, 0xff, //EFI_SMM_SAVE_STATE_REGISTER_R11 = 33
    0xff34, 8, 0xffff, 0xff, //EFI_SMM_SAVE_STATE_REGISTER_R12 = 34
    0xff2c, 8, 0xffff, 0xff, //EFI_SMM_SAVE_STATE_REGISTER_R13 = 35
    0xff24, 8, 0xffff, 0xff, //EFI_SMM_SAVE_STATE_REGISTER_R14 = 36
    0xff1c, 8, 0xffff, 0xff, //EFI_SMM_SAVE_STATE_REGISTER_R15 = 37
    0xff5c, 8, 0x01d0, 4, //EFI_SMM_SAVE_STATE_REGISTER_RAX = 38
    0xff74, 8, 0x01dc, 4, //EFI_SMM_SAVE_STATE_REGISTER_RBX = 39
    0xff64, 8, 0x01d4, 4, //EFI_SMM_SAVE_STATE_REGISTER_RCX = 40
    0xff6c, 8, 0x01d8, 4, //EFI_SMM_SAVE_STATE_REGISTER_RDX = 41
    0xff64, 8, 0x01e0, 4, //EFI_SMM_SAVE_STATE_REGISTER_RSP = 42
    0xff84, 8, 0x01e4, 4, //EFI_SMM_SAVE_STATE_REGISTER_RBP = 43
    0xff8c, 8, 0x01e8, 4, //EFI_SMM_SAVE_STATE_REGISTER_RSI = 44
    0xff94, 8, 0x01ec, 4, //EFI_SMM_SAVE_STATE_REGISTER_RDI = 45
    0xffd8, 8, 0x01f0, 4, //EFI_SMM_SAVE_STATE_REGISTER_RIP = 46
    0xffe8, 8, 0x01f4, 4, //EFI_SMM_SAVE_STATE_REGISTER_RFLAGS = 51
    0xfff8, 8, 0x01fc, 4, //EFI_SMM_SAVE_STATE_REGISTER_CR0 = 52
    0xfff0, 8, 0x01f8, 4, //EFI_SMM_SAVE_STATE_REGISTER_CR3 = 53
    0xfe40, 8, 0x00f0, 4, //EFI_SMM_SAVE_STATE_REGISTER_CR4 = 54

    //Supported in XMM Save/restore function
    //EFI_SMM_SAVE_STATE_REGISTER_FCW = 256
    //EFI_SMM_SAVE_STATE_REGISTER_FSW = 257
    //EFI_SMM_SAVE_STATE_REGISTER_FTW = 258
    //EFI_SMM_SAVE_STATE_REGISTER_OPCODE = 259
    //EFI_SMM_SAVE_STATE_REGISTER_FP_EIP = 260
    //EFI_SMM_SAVE_STATE_REGISTER_FP_CS = 261
    //EFI_SMM_SAVE_STATE_REGISTER_DATAOFFSET = 262
    //EFI_SMM_SAVE_STATE_REGISTER_FP_DS = 263
    //EFI_SMM_SAVE_STATE_REGISTER_MM0 = 264
    //EFI_SMM_SAVE_STATE_REGISTER_MM1 = 265
    //EFI_SMM_SAVE_STATE_REGISTER_MM2 = 266
    //EFI_SMM_SAVE_STATE_REGISTER_MM3 = 267
    //EFI_SMM_SAVE_STATE_REGISTER_MM4 = 268
    //EFI_SMM_SAVE_STATE_REGISTER_MM5 = 269
    //EFI_SMM_SAVE_STATE_REGISTER_MM6 = 270
    //EFI_SMM_SAVE_STATE_REGISTER_MM7 = 271
    //EFI_SMM_SAVE_STATE_REGISTER_XMM0 = 272
    //EFI_SMM_SAVE_STATE_REGISTER_XMM1 = 273
    //EFI_SMM_SAVE_STATE_REGISTER_XMM2 = 274
    //EFI_SMM_SAVE_STATE_REGISTER_XMM3 = 275
    //EFI_SMM_SAVE_STATE_REGISTER_XMM4 = 276
    //EFI_SMM_SAVE_STATE_REGISTER_XMM5 = 277
    //EFI_SMM_SAVE_STATE_REGISTER_XMM6 = 278
    //EFI_SMM_SAVE_STATE_REGISTER_XMM7 = 279
    //EFI_SMM_SAVE_STATE_REGISTER_XMM8 = 280
    //EFI_SMM_SAVE_STATE_REGISTER_XMM9 = 281
    //EFI_SMM_SAVE_STATE_REGISTER_XMM10 = 282
    //EFI_SMM_SAVE_STATE_REGISTER_XMM11 = 283
    //EFI_SMM_SAVE_STATE_REGISTER_XMM12 = 284
    //EFI_SMM_SAVE_STATE_REGISTER_XMM13 = 285
    //EFI_SMM_SAVE_STATE_REGISTER_XMM14 = 286
    //EFI_SMM_SAVE_STATE_REGISTER_XMM15 = 287
    //
    // Pseudo-Registers
    //
    //EFI_SMM_SAVE_STATE_REGISTER_IO = 512
    //EFI_SMM_SAVE_STATE_REGISTER_LMA = 513
};

typedef enum {
    CPULIB_SMM_SAVE_STATE_IO_WIDTH_UINT8 = 0,
    CPULIB_SMM_SAVE_STATE_IO_WIDTH_UINT16 = 1,
    CPULIB_SMM_SAVE_STATE_IO_WIDTH_UINT32 = 2,
    CPULIB_SMM_SAVE_STATE_IO_WIDTH_UINT64 = 3
} CPULIB_SMM_SAVE_STATE_IO_WIDTH;

typedef enum {
    CPULIB_SMM_SAVE_STATE_IO_TYPE_INPUT = 1,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_OUTPUT = 2,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_STRING = 4,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_REP_PREFIX = 8
} CPULIB_SMM_SAVE_STATE_IO_TYPE;

typedef struct  {
    UINT64 IoData;
    UINT16 IoPort;
    CPULIB_SMM_SAVE_STATE_IO_WIDTH IoWidth;
    CPULIB_SMM_SAVE_STATE_IO_TYPE IoType;
} CPULIB_SMM_SAVE_STATE_IO_INFO;

UINT8 IOTypeToEMSSIT[] = {
    CPULIB_SMM_SAVE_STATE_IO_TYPE_OUTPUT,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_INPUT,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_STRING,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_STRING,
    0,
    0,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_REP_PREFIX,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_REP_PREFIX,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_OUTPUT,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_INPUT
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPULib_SmmReadSaveState
//
// Description: Read SMM Save state from combination of SMM save state and copy.
//  If frame copy exists, use its data instead from actual save state.
//  A different function gets information for floating point and XMM.
//
// Input:
//  IN UINT8    *SmmBase         - SmmBase of CPU to read Save State.
//  IN UINT8    *SstSaveState    - SMM Save state copy for Framework.
//  IN BOOLEAN  UseSstSaveState  - True if Save state copy exists.
//  IN UINT8    Width            - Width in Bytes of register.
//  IN UINT32   Register         - Register Token in PI SMM.
//  OUT VOID    *Buffer          - Read register into this buffer.
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CPULib_SmmReadSaveState(
    IN UINT8    *SmmBase,
    IN UINT8    *SstSaveState,
    IN BOOLEAN  UseSstSaveState,
    IN UINT8    Width,
    IN UINT32   Register,
    OUT VOID    *Buffer
)
{
    UINT32 Index = 0xffffffff;
    UINTN   Offset;
    
    if (Register >= 20 && Register <= 46) Index = Register - 20;
    if (Register >= 51 && Register <= 54) Index = Register - 20 - (51-47);
    
    if (Index != 0xffffffff) {
        if (Width > gIntelX64Format[Index].SaveStateWidth) return EFI_INVALID_PARAMETER;
        switch(Width) {
        case 1:
            //Use SMM framework buffer if available, because copy may be updated by Framework driver, and copy will overwrite actual save state at end.
            if (UseSstSaveState && gIntelX64Format[Index].FrameworkWidth != 0xff) *(UINT8*)Buffer = *(SstSaveState + gIntelX64Format[Index].FrameworkOffset);
            else *(UINT8*)Buffer = *(SmmBase + gIntelX64Format[Index].SaveStateOffset);
            return EFI_SUCCESS;
        case 2:
            if (UseSstSaveState && gIntelX64Format[Index].FrameworkWidth != 0xff) *(UINT16*)Buffer = *(UINT16*)(SstSaveState + gIntelX64Format[Index].FrameworkOffset);
            else *(UINT16*)Buffer = *(UINT16*)(SmmBase + gIntelX64Format[Index].SaveStateOffset);
            return EFI_SUCCESS;
        case 4:
            if (UseSstSaveState && gIntelX64Format[Index].FrameworkWidth != 0xff) *(UINT32*)Buffer = *(UINT32*)(SstSaveState + gIntelX64Format[Index].FrameworkOffset);
            else *(UINT32*)Buffer = *(UINT32*)(SmmBase + gIntelX64Format[Index].SaveStateOffset);
            return EFI_SUCCESS;
        case 8:
            *(UINT64*)Buffer = *(UINT64*)(SmmBase + gIntelX64Format[Index].SaveStateOffset);
            //Use copy if available, because copy may be updated by Framework driver, and copy will overwrite actual save state at end. Copy doesn't support upper bits.
            if (UseSstSaveState && gIntelX64Format[Index].FrameworkWidth != 0xff) *(UINT32*)Buffer = *(UINT32*)(SstSaveState + gIntelX64Format[Index].FrameworkOffset);
            return EFI_SUCCESS;
        }
    }
    if (Register == 4) {	//GDT
        if (Width != 4 && Width != 8) return EFI_INVALID_PARAMETER;
        if (Width == 8) *((UINT32*)Buffer + 1) =  *(UINT32*)(SmmBase + 0xffd0);
        //Use copy for lower 32-bits
        if (UseSstSaveState) *(UINT32*)Buffer = *(UINT32*)(SstSaveState + 0x188);
        return EFI_SUCCESS;
    }
    if (Register == 5) {	//IDT
        if (Width != 4 && Width != 8) return EFI_INVALID_PARAMETER;
        if (Width == 8) *((UINT32*)Buffer + 1) =  *(UINT32*)(SmmBase + 0xfdd8);
        //Use copy for lower 32-bits
        if (UseSstSaveState) *(UINT32*)Buffer = *(UINT32*)(SstSaveState + 0x194);
        return EFI_SUCCESS;
    }
    if (Register == 6) {    //LDT
        if (Width != 4 && Width != 8) return EFI_INVALID_PARAMETER;
        if (Width == 8) *((UINT32*)Buffer + 1) =  *(UINT32*)(SmmBase + 0xfdd4);
        //Use copy for lower 32-bits
        if (UseSstSaveState) *(UINT32*)Buffer = *(UINT32*)(SstSaveState + 0x1c0);
        return EFI_SUCCESS;
    }

    if (Register == 513) {
        UINT16 Efer;
        if (Width != 1) return EFI_INVALID_PARAMETER;
        Efer = *(UINT16*)(SmmBase + 0xffe0);
        *(UINT8*)Buffer = (Efer & BIT10) == BIT10 ? 64 : 32;
        return EFI_SUCCESS;
    }

    if (Register == 512) {
        UINT32 IoMisc = *(UINT32*)(SmmBase + 0xffa4);
        UINT8  Width = 0;

        if (!(IoMisc & 1)) return EFI_NOT_FOUND;

        switch((IoMisc >> 1) & 7) {
            case 1: Width = 0; break;
            case 2: Width = 1; break;
            case 3: Width = 2; break;
            default: return EFI_NOT_FOUND;
        };

        //Get the I/O address.
        switch ((IoMisc >> 4) & 0xF) {
            case 0:
            case 1:
            case 8:
            case 9:
                Offset = 0xff5c;    //Reg RAX has the value
                break;
            case 2:
            case 3:
            case 6:
            case 7:
                Offset = 0xff9c;    //IO_MEM_ADDRESS has the value
                break;
            default:
                return EFI_NOT_FOUND;   
        }

        ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoPort = (UINT16)(IoMisc >> 16);
        ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoWidth = Width;
        ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoType = IOTypeToEMSSIT[(IoMisc >> 4)  & 0xf];
        
        switch (Width) {
            case 0:
                ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoData = *(UINT8 *)(SmmBase + Offset);                
                break;
            case 1:
                ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoData = *(UINT16 *)(SmmBase + Offset);                
                break;
            case 2:
                 ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoData = *(UINT32 *)(SmmBase + Offset);                
                 break;
            default:
                return EFI_NOT_FOUND;
        }
        return EFI_SUCCESS;   
    }
    return EFI_UNSUPPORTED; //Register not supported.
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuLib_SmmReadSaveStateFxSave
//
// Description: Read SMM Save state for floating point and XMM.
//
// Input:
//  IN UINT8    *FxSave          - FxSave buffer.
//  IN UINT8    Width            - Width in Bytes of register.
//  IN UINT32   Register         - Register Token in PI SMM.
//  OUT VOID    *Buffer          - Read register into this buffer.
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CpuLib_SmmReadSaveStateFxSave(
        IN UINT8    *FxSave,
        IN UINT8    Width,
        IN UINT32   Register,
        OUT VOID    *Buffer
)
{
    if (Register == 256) { //FCW
        if (Width != 2) return EFI_INVALID_PARAMETER;
        *(UINT16*)Buffer = *(UINT16*)FxSave;
        return EFI_SUCCESS;
    }
    if (Register == 257) { //FSW
        if (Width != 2) return EFI_INVALID_PARAMETER;
        *(UINT16*)Buffer = *(UINT16*)(FxSave + 2);
        return EFI_SUCCESS;
    }
    if (Register == 258) { //FTW
        if (Width != 1) return EFI_INVALID_PARAMETER;
        *(UINT8*)Buffer = *(UINT8*)(FxSave + 4);
        return EFI_SUCCESS;
    }
    if (Register == 259) { //FOP
        if (Width != 2) return EFI_INVALID_PARAMETER;
        *(UINT16*)Buffer = *(UINT16*)(FxSave + 6);
        return EFI_SUCCESS;
    }

    if (Register == 260) { //FPU IP
        if (Width == 4) {
            MemCpy(Buffer, FxSave + 8, 4);
            return EFI_SUCCESS;
        }
#if x64_BUILD
        if (Width == 8) {
            MemCpy(Buffer, FxSave + 8, 8);
            return EFI_SUCCESS;
        }
#endif
        return EFI_INVALID_PARAMETER;
    }

#if x64_BUILD == 0
    if (Register == 261) { //CS
        if (Width != 2) return EFI_INVALID_PARAMETER;
        *(UINT16*)Buffer = *(UINT16*)(FxSave + 12);
    }
#endif

    if (Register == 262) { //FPU DP (DataOffset)
        if (Width == 4) {
            MemCpy(Buffer, FxSave + 16, 4);
            return EFI_SUCCESS;
        }
#if x64_BUILD
        if (Width == 8) {
            MemCpy(Buffer, FxSave + 16, 8);
            return EFI_SUCCESS;
        }
#endif
        return EFI_INVALID_PARAMETER;
    }

#if x64_BUILD == 0
    if (Register == 263) { //DS
        if (Width != 2) return EFI_INVALID_PARAMETER;
        *(UINT16*)Buffer = *(UINT16*)(FxSave + 20);
    }
#endif

    if (Register >= 264 && Register <= 271) {   //MM0 - MM7
        if (Width != 10) return EFI_INVALID_PARAMETER;
        MemCpy(Buffer, FxSave + 32 + 16 * (Register - 264), 10);
        return EFI_SUCCESS;
    }
    if (Register >= 272 && Register <= 287) {   //XMM0 - XMM15
        if (Width != 16) return EFI_INVALID_PARAMETER;
        MemCpy(Buffer, FxSave + 160 + 16 * (Register - 272), 16);
        return EFI_SUCCESS;
    }
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CPULib_SmmWriteSaveState
//
// Description: Write SMM Save state from combination of SMM save state and copy.
//  If frame copy exists, use its data instead from actual save state.
//  A different function gets information for floating point and XMM.
//
// Input:
//  IN UINT8    *SmmBase         - SmmBase of CPU to read Save State.
//  IN UINT8    *SstSaveState    - SMM Save state copy for Framework.
//  IN BOOLEAN  UseSstSaveState  - True if Save state copy exists.
//  IN UINT8    Width            - Width in Bytes of register.
//  IN UINT32   Register         - Register Token in PI SMM.
//  IN VOID    *Buffer           - Write register into this buffer.
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CPULib_SmmWriteSaveState(
    IN OUT UINT8 *SmmBase,
    IN OUT UINT8 *SstSaveState,
    IN BOOLEAN   UseSstSaveState,
    IN UINT8     Width,
    IN UINT32	 Register,
    IN VOID      *Buffer
)
{
    UINT32 Index = 0xffffffff;
    
    if (Register >= 20 && Register <= 46) Index = Register - 20;
    if (Register >= 51 && Register <= 54) Index = Register - 20 - (51-47);  //No tokens assigned 47-50.

    if (Index != 0xffffffff) {
        if (Width > gIntelX64Format[Index].SaveStateWidth) return EFI_INVALID_PARAMETER;
        switch(Width) {
        case 1:
            *(SmmBase + gIntelX64Format[Index].SaveStateOffset) = *(UINT8*)Buffer;
            //Copy to save state buffer for SMM framework.
            if (UseSstSaveState && gIntelX64Format[Index].FrameworkWidth != 0xff) *(SstSaveState + gIntelX64Format[Index].FrameworkOffset) = *(UINT8*)Buffer;
            return EFI_SUCCESS;
        case 2:
            *(UINT16*)(SmmBase + gIntelX64Format[Index].SaveStateOffset) = *(UINT16*)Buffer;
            if (UseSstSaveState && gIntelX64Format[Index].FrameworkWidth != 0xff) *(UINT16*)(SstSaveState + gIntelX64Format[Index].FrameworkOffset) = *(UINT16*)Buffer;
            return EFI_SUCCESS;
        case 4:
            *(UINT32*)(SmmBase + gIntelX64Format[Index].SaveStateOffset) = *(UINT32*)Buffer;
            if (UseSstSaveState && gIntelX64Format[Index].FrameworkWidth != 0xff) *(UINT32*)(SstSaveState + gIntelX64Format[Index].FrameworkOffset) = *(UINT32*)Buffer;
            return EFI_SUCCESS;
        case 8:
            *(UINT64*)(SmmBase + gIntelX64Format[Index].SaveStateOffset) = *(UINT64*)Buffer;
            if (UseSstSaveState && gIntelX64Format[Index].FrameworkWidth != 0xff) *(UINT32*)(SstSaveState + gIntelX64Format[Index].FrameworkOffset) = *(UINT32*)Buffer;
            return EFI_SUCCESS;
        }
	}
    if (Register == 4) {	//GDT
        if (Width != 4 && Width != 8) return EFI_INVALID_PARAMETER;
        if (Width == 8) *(UINT32*)(SmmBase + 0xffd0) = *((UINT32*)Buffer + 1);
        *(UINT32*)(SmmBase + 0xfe8c) = *(UINT32*)Buffer;
        //Copy to framework buffer for lower 32-bits
        if (UseSstSaveState) *(UINT32*)(SstSaveState + 0x188) = *(UINT32*)Buffer;
        return EFI_SUCCESS;
    }
    if (Register == 5) {	//IDT
        if (Width != 4 && Width != 8) return EFI_INVALID_PARAMETER;
        if (Width == 8) *(UINT32*)(SmmBase + 0xfdd8) = *((UINT32*)Buffer + 1);
        *(UINT32*)(SmmBase + 0xfe94) = *(UINT32*)Buffer;
        if (UseSstSaveState) *(UINT32*)(SstSaveState + 0x194) = *(UINT32*)Buffer;
        return EFI_SUCCESS;
    }
    if (Register == 6) {	//LDT
        if (Width != 4 && Width != 8) return EFI_INVALID_PARAMETER;
        if (Width == 8) *(UINT32*)(SmmBase + 0xfdd4) = *((UINT32*)Buffer + 1);
        *(UINT32*)(SmmBase + 0xfe9c) = *(UINT32*)Buffer;
        if (UseSstSaveState) *(UINT32*)(SstSaveState + 0x1c0) = *(UINT32*)Buffer;
        return EFI_SUCCESS;
    }
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuLib_SmmWriteSaveStateFxSave
//
// Description: Write SMM Save state for floating point and XMM.
//
// Input:
//  IN UINT8    *FxSave          - FxSave buffer.
//  IN UINT8    Width            - Width in Bytes of register.
//  IN UINT32   Register         - Register Token in PI SMM.
//  IN  VOID    *Buffer          - Write register into this buffer.
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CpuLib_SmmWriteSaveStateFxSave(
        IN UINT8    *FxSave,
        IN UINT8    Width,
        IN UINT32   Register,
        IN VOID     *Buffer
)
{
    if (Register == 256) { //FCW
        if (Width != 2) return EFI_INVALID_PARAMETER;
        *(UINT16*)FxSave = *(UINT16*)Buffer;
        return EFI_SUCCESS;
    }
    if (Register == 257) { //FSW
        if (Width != 2) return EFI_INVALID_PARAMETER;
        *(UINT16*)(FxSave + 2) = *(UINT16*)Buffer;
        return EFI_SUCCESS;
    }
    if (Register == 258) { //FTW
        if (Width != 1) return EFI_INVALID_PARAMETER;
        *(UINT8*)(FxSave + 4) = *(UINT8*)Buffer;
        return EFI_SUCCESS;
    }
    if (Register == 259) { //FOP
        if (Width != 2) return EFI_INVALID_PARAMETER;
        *(UINT16*)(FxSave + 6) = *(UINT16*)Buffer;
        return EFI_SUCCESS;
    }

    if (Register == 260) { //FPU IP
        if (Width == 4) {
            MemCpy(FxSave + 8, Buffer, 4);
            return EFI_SUCCESS;
        }
#if x64_BUILD
        if (Width == 8) {
            MemCpy(FxSave + 8, Buffer, 8);
            return EFI_SUCCESS;
        }
#endif
        return EFI_INVALID_PARAMETER;
    }

#if x64_BUILD == 0
    if (Register == 261) { //CS
        if (Width != 2) return EFI_INVALID_PARAMETER;
        *(UINT16*)(FxSave + 12) = *(UINT16*)Buffer;
    }
#endif

    if (Register == 262) { //FPU DP (DataOffset)
        if (Width == 4) {
            MemCpy(FxSave + 16, Buffer, 4);
            return EFI_SUCCESS;
        }
#if x64_BUILD
        if (Width == 8) {
            MemCpy(FxSave + 16, Buffer, 8);
            return EFI_SUCCESS;
        }
#endif
        return EFI_INVALID_PARAMETER;
    }

#if x64_BUILD == 0
    if (Register == 263) { //DS
        if (Width != 2) return EFI_INVALID_PARAMETER;
        *(UINT16*)(FxSave + 20) = *(UINT16*)Buffer ;
    }
#endif

    if (Register >= 264 && Register <= 271) {   //MM0 - MM7
        if (Width != 10) return EFI_INVALID_PARAMETER;
        MemCpy(FxSave + 32 + 16 * (Register - 264), Buffer, 10);
        return EFI_SUCCESS;
    }
    if (Register >= 272 && Register <= 287) {   //XMM0 - XMM15
        if (Width != 16) return EFI_INVALID_PARAMETER;
        MemCpy(FxSave + 160 + 16 * (Register - 272), Buffer, 16);
        return EFI_SUCCESS;
    }
    return EFI_UNSUPPORTED;
}

static UINT8 CpuIedSig[] = {'I','N','T','E','L',' ','R','S','V','D'};

VOID CPU_SmmMemoryInit(IN SMM_HOB *SmmHob)
{
    UINT8   *IedStart;
    UINT32  IedSize;

    if (!SmmHob->IedStart) return;

    IedStart = (UINT8*)SmmHob->IedStart;
    IedSize = SmmHob->IedSize;

    MemCpy(IedStart, CpuIedSig, sizeof(CpuIedSig));
    *(UINT32*)(IedStart + 10) = IedSize;

    *(UINT16*)(IedStart + 14) = 0;  //Reserved
    *(UINT64*)(IedStart + 16) = 0;  //Trace memory for Nehalem-EX.

    MemSet(IedStart + 24, 24, 0);   //Reserved
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsSwSmiTrigger
//
// Description: This routine checks to see if the cpu caused an software smi.
//
// Input:
//  UINT8 *SmmBase
//  UINT16 SwSmiPort
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsSwSmiTrigger(UINT8 *SmmBase, UINT16 SwSmiPort)
{
    UINT32 IO_MISC_INFO = *(UINT32*)(SmmBase + 0xffa4);
    if (!(IO_MISC_INFO & 1)) return FALSE;  //For valid data, this should be 1.
    return (*((UINT16*)&IO_MISC_INFO + 1) == SwSmiPort);  //[31:16]
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************


