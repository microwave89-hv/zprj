//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/S3/BootScriptExecuter.c 2     9/17/13 10:02p Thomaschen $
//
// $Revision: 2 $
//
// $Date: 9/17/13 10:02p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/S3/BootScriptExecuter.c $
// 
// 2     9/17/13 10:02p Thomaschen
// update for ACPI module labeled 47
// 
// 8     12/13/12 12:03p Oleksiyy
// [TAG]  		EIP109290
// [Category]  	Improvement
// [Description]  	Issues found by CppCheck in ACPI eModule
// [Files]  		AcpiCore.c, mptable.c, AmlString.c, BootScriptSave.c and
// BootScriptExecuter.c
// 
// 7     9/29/11 5:05p Oleksiyy
// [TAG]  		EIP71372 
// [Category]  	Improvement
// [Description]  	EFI_BOOT_SCRIPT_DISPATCH_2_OPCODE added.
// [Files]  		BootScriptExecuter.c and BootScriptSave.c
// 
// 6     7/19/11 11:34a Oleksiyy
// [TAG]  		EIP64108 
// [Category]  	Improvement
// [Description]  	ACPI, convert or update all eModules to be compliant
// with PI 1.2, and UEFI 2.3.1 specifications. 
// [Files]  		AcpiCore.c, mptable.c, AcpiS3Save.c, S3Resume.dxs,
// S3Resume.c, AcpiPeiS3Func.c, BootScriptExecuter.c and DxeIpl.c
// 
// 5     6/01/11 10:27a Oleksiyy
// [TAG]  		EIP56650 
// [Category]  	New Feature
// [Description]  	S3 Save State Protocol and S3 Smm Save State Protocol
// backward compatibility improved.
// [Files]  		BootScriptExecuter.c
// 
// 4     5/19/11 10:40a Oleksiyy
// [TAG]  		EIP60727 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Dispatch opcode invalid
// [RootCause]  	Dispatch opcode realization was commented out mistakenly.
// [Solution]  	Commented out code restored.
// [Files]  		BootScriptExecuter.c
// 
// 3     5/13/11 3:23p Oleksiyy
// [TAG]  		EIP56650 
// [Category]  	New Feature
// [Description]  	S3 Save State Protocol and S3 Smm Save State Protocol
// functions added. Support for opcodes introduced in PI 1.2 added.
// [Files]  		BootScriptCommon.h, BootScriptExecuter.c,
// BootScriptPrivate.h, BootScriptSave.c and BootScriptSave.h
// 
// 2     3/18/11 3:51p Oleksiyy
// [TAG]  		EIP53402 
// [Category]  	Improvement
// [Description]  	Improving backward computability and architecture.
// [Files]  		ACPI.mak, AcpiCore.cif, S3Save.cif, S3Save.mak,
// S3Restore.mak, BootScriptExecutor.c, S3Common.cif, S3SaveState.h,
// S3smmSaveState.h
// 
// 2     3/09/11 6:09p Artems
// 
// 1     3/09/11 6:09p Artems
// 
// 1     2/03/11 4:09p Oleksiyy
// [TAG]  		EIP53402 
// [Category]  	Improvement
// [Description]  	Create new label of ACPI with separate S3 Functionality
// [Files]  		S3Restore.cif
// S3Restore.sdl
// S3Restore.mak
// S3Resume.dxs
// AcpiS3Wake.asm
// S3Resume.c
// AcpiPeiS3Func.c
// AcpiPeiS3Func.h
// BootScriptExecuter.c
// 
// 11    3/04/10 2:06p Oleksiyy
// EIP 35847: Bug Fix
// 
// 10    11/05/09 4:00p Oleksiyy
// EIP 27821 Support for 64 bit operations in Bootscript added. To use
// this functions AmiLib.h, CpuIo.c, IA32CLib.c, PciCfg.c, x64AsmLib.asm
// files should be updated also.
// 
// 9     3/26/09 4:51p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 8     10/10/08 8:16p Felixp
// Performance measurement support added
// 
// 6     6/06/08 11:54a Felixp
// Performance measurement support added
// 
// 5     4/16/08 12:10p Yakovlevs
// fixed compilation issue 
// 
// 4     4/15/08 9:20p Yakovlevs
// Functions Headers added; Removed definition of EFI_BOOT_SCRIPT WDTH
// 
// 3     6/07/07 3:09p Felixp
// 
// 2     6/05/07 12:17a Felixp
// Added SmmBus support
// 
// 1     4/23/07 1:31p Felixp
// 
// 15    12/26/06 2:56p Markw
// Add BootScript Polling.
// 
// 14    11/22/06 4:35p Markw
// Move certain Mem/Io write trace statments before instead of after the
// write. This is so if the write causes a hang, it can be seen on serial
// redirection.
// 
// 13    9/22/06 6:08p Markw
// 64-bit fix.
// 
// 12    3/15/06 2:41p Markw
// 
// 11    3/15/06 2:37p Markw
// Fixed bug, used value instead of Mask.
// 
// 10    3/13/06 9:51a Felixp
// 
// 9     10/09/05 11:25a Felixp
// Performance measurements added.
// 
// 8     6/23/05 5:37p Markw
// Added defintions from Boot Script Save Protocol.
// 
// 7     6/15/05 4:20p Markw
// Modified dispatch function to pass in PeiServices.
// 
// 6     6/06/05 7:49p Felixp
// 
// 5     6/06/05 1:26p Felixp
// Usage of CPU I/O and PCI Cfg changed to match PEI CIS 0.91
// 
// 4     5/27/05 1:36a Felixp
// 
// 3     5/16/05 3:03p Markw
// Added more trace messages.
// 
// 2     4/04/05 2:38p Markw
// Fix write to pci register bug.
// Add temporary trace statements.
//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:    BootScriptExecuter.c
//
//  Description:	Boot script execution support functions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Ppi\BootScriptExecuter.h>
#include <Ppi\CpuIo.h>
#include <Ppi\PciCfg2.h>
#if PI_SPECIFICATION_VERSION>=0x10000
#include <Ppi\Smbus2.h>
#else
#include <Ppi\Smbus.h>
#endif
#include <Ppi\Stall.h>
#include "BootScriptPrivate.h"
#include <AmiPeiLib.h>

#if (CORE_REVISION >= 0x5)
#include <BootScriptCommon.h>
#else

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
//*******************************************
// EFI Save State Script Opcode definitions (PI)
//*******************************************

#define EFI_BOOT_SCRIPT_IO_WRITE_OPCODE                 0x00
#define EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE            0x01
#define EFI_BOOT_SCRIPT_MEM_WRITE_OPCODE                0x02
#define EFI_BOOT_SCRIPT_MEM_READ_WRITE_OPCODE           0x03
#define EFI_BOOT_SCRIPT_PCI_CONFIG_WRITE_OPCODE         0x04
#define EFI_BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_OPCODE    0x05
#define EFI_BOOT_SCRIPT_SMBUS_EXECUTE_OPCODE            0x06
#define EFI_BOOT_SCRIPT_STALL_OPCODE                    0x07
#define EFI_BOOT_SCRIPT_DISPATCH_OPCODE                 0x08

#define EFI_BOOT_SCRIPT_DISPATCH_2_OPCODE               0x09
#define EFI_BOOT_SCRIPT_INFORMATION_OPCODE              0x0A
#define EFI_BOOT_SCRIPT_PCI_CONFIG2_WRITE_OPCODE        0x0B
#define EFI_BOOT_SCRIPT_PCI_CONFIG2_READ_WRITE_OPCODE   0x0C
#define EFI_BOOT_SCRIPT_IO_POLL_OPCODE                  0x0D
#define EFI_BOOT_SCRIPT_MEM_POLL_OPCODE                 0x0E
#define EFI_BOOT_SCRIPT_PCI_CONFIG_POLL_OPCODE          0x0F
#define EFI_BOOT_SCRIPT_PCI_CONFIG2_POLL_OPCODE         0x10
#define EFI_BOOT_SCRIPT_LABEL_OPCODE_OEM                0x83

#else 
//*******************************************
// EFI Boot Script Opcode definitions (Framework)
//*******************************************

#define EFI_BOOT_SCRIPT_IO_WRITE_OPCODE					0x00
#define EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE			0x01
#define EFI_BOOT_SCRIPT_MEM_WRITE_OPCODE				0x02
#define EFI_BOOT_SCRIPT_MEM_READ_WRITE_OPCODE			0x03
#define EFI_BOOT_SCRIPT_PCI_CONFIG_WRITE_OPCODE			0x04
#define EFI_BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_OPCODE	0x05
#define EFI_BOOT_SCRIPT_SMBUS_EXECUTE_OPCODE			0x06
#define EFI_BOOT_SCRIPT_STALL_OPCODE					0x07
#define EFI_BOOT_SCRIPT_DISPATCH_OPCODE					0x08

#endif
//
// Extensions to boot script definitions
//
//OEM
#ifndef EFI_BOOT_SCRIPT_IO_POLL_OPCODE_OEM
#define EFI_BOOT_SCRIPT_IO_POLL_OPCODE_OEM                  0x80
#endif

#ifndef EFI_BOOT_SCRIPT_MEM_POLL_OPCODE_OEM
#define EFI_BOOT_SCRIPT_MEM_POLL_OPCODE_OEM                 0x81
#endif

#ifndef EFI_BOOT_SCRIPT_PCI_POLL_OPCODE_OEM
#define EFI_BOOT_SCRIPT_PCI_POLL_OPCODE_OEM                 0x82
#endif



#define EFI_BOOT_SCRIPT_TABLE_OPCODE                  0xAA
#define EFI_BOOT_SCRIPT_TERMINATE_OPCODE              0xFF



//*******************************************
// EFI_BOOT_SCRIPT_WIDTH
//*******************************************
typedef enum {
	EfiBootScriptWidthUint8,
	EfiBootScriptWidthUint16,
	EfiBootScriptWidthUint32,
	EfiBootScriptWidthUint64,
	EfiBootScriptWidthFifoUint8,
	EfiBootScriptWidthFifoUint16,
	EfiBootScriptWidthFifoUint32,
	EfiBootScriptWidthFifoUint64,
	EfiBootScriptWidthFillUint8,
	EfiBootScriptWidthFillUint16,
	EfiBootScriptWidthFillUint32,
	EfiBootScriptWidthFillUint64,
	EfiBootScriptWidthMaximum
} EFI_BOOT_SCRIPT_WIDTH;

#endif //#if (CORE_REVISION >= 0x5)

typedef EFI_STATUS (EFIAPI *DISPATCH_ENTRYPOINT_FUNC) (
  IN EFI_HANDLE ImageHandle, 
  IN VOID*      Context
);


EFI_GUID gBootScriptExecuterGuid = EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI_GUID;
#if PI_SPECIFICATION_VERSION>=0x10000
EFI_GUID gSmBusGuid		= EFI_PEI_SMBUS2_PPI_GUID;
#else
EFI_GUID gSmBusGuid		= EFI_PEI_SMBUS_PPI_GUID;
#endif
EFI_GUID gStallGuid		= EFI_PEI_STALL_PPI_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: PciRegAdd
//
// Description: Increase the Pci register number by a value.
//
// Input: 
//	IN UINT64 Address	- Pci Address
//	IN UINT8 ValueSize  - Add value to register.
//
// Output: 
//	UINT64	New Pci Address.
//
// Notes:
//  Here is the control flow of this function:
//  1. Get extended register.
//  2. If extended register, increment it by ValueSize
//     else increment the non-extended register.
//  3. Return the Address.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT64 PciRegAdd(UINT64 Address,UINT8 ValueSize)
{
	UINT32	ExtReg;

	ExtReg = (UINT32) (*((UINT32*)&Address +1));
	if (ExtReg)
		(*((UINT32*)&Address + 1)) += ValueSize;
	
	else (*(UINT8*)&Address) = (*(UINT8*)&Address) + ValueSize;
	
	return Address;
}
#if defined (PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x0001000A)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: SwitchPciCfgPpi
//
// Description: Serchs for PCI_CFG2_PPI with corresponding Segment
//
// Input: 
//	IN EFI_PEI_SERVICES					**PeiServices
//	IN UINT16                           SegmentSwitchTo

//
// Output: 
//	EFI_PEI_PCI_CFG2_PPI* Pointer to Pci Cfg PPI with Segment wanted
//  NULL if not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_PEI_PCI_CFG2_PPI* SwitchPciCfgPpi(
    IN EFI_PEI_SERVICES		    **PeiServices, 
    IN UINT16                   SegmentSwitchTo
    )
{
    UINT32 i = 0;
    EFI_GUID PciCfg2PpiGuid = EFI_PEI_PCI_CFG2_PPI_GUID;
    EFI_PEI_PCI_CFG2_PPI    *PciCfg2Ppi;
    EFI_STATUS Status;
    while (TRUE) {
       
        Status = (**PeiServices).LocatePpi( PeiServices,
            &PciCfg2PpiGuid, i, NULL, &PciCfg2Ppi );

        if ( EFI_ERROR( Status ) ) {
            break;
        }

        if (PciCfg2Ppi->Segment == SegmentSwitchTo) //We found PPI we need
            return PciCfg2Ppi;  //return pointer
        i++;
    }
    return NULL;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: ExecuteScript
//
// Description:
//
// Input: 
//	IN EFI_PEI_SERVICES					**PeiServices
//	IN EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI	*This
//	IN EFI_PHYSICAL_ADDRESS				Address
//	IN EFI_GUID							*FvFile OPTIONAL
//
// Output: 
//	EFI_STATUS
//
// Notes:
//  Here is the control flow of this function:
//  1. Locate Ppis: CpuIo PciCfg SmBus.
//  2. If any of the Ppis doesn't exist return EFI_UNSUPPORTED.
//	---Execute table Script---
//  3. Read Opcode type:
//		a. EFI_BOOT_SCRIPT_IO_WRITE_OPCODE
//		b. EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE
//      etc. 
//  If TABLE_END_OP_CODE, return EFI_SUCCESS.
//	If unknown opcode return EFI_UNSUPPORTED.
//
//  4. Copy the Opcode type to its structure. Structure will be aligned.
//  5. If it has a buffer, get Buffer address in table.
//  6. Get address of in table for next Opcode.
//  7. Call appropriate Ppi for OpCode with parameters from the structure.
//
//	Check BootScript spec for better understanding of code. 
//  Note for writes there are EfiBootScriptWidthUintxx,
//		EfiBootScriptWidthFifoUintxx, and EfiBootScriptWidthFillUintxx.
//  xx Denotes 8,16,32,or 64(unsupported).
//
//	8. Go to step 3.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ExecuteScript(
	IN EFI_PEI_SERVICES					**PeiServices,
	IN EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI	*This,
	IN EFI_PHYSICAL_ADDRESS				Address,
	IN EFI_GUID							*FvFile OPTIONAL
	)
{
	VOID *TableAddr = (VOID *)(UINTN) Address;
	BOOT_SCRIPT_DATA BootScript;
	UINT16	Type;
	UINT32	AddressCount;
	UINT8	ValueSize;
	UINT8	Width;
	UINT64	Count;
	VOID	*Buffer;
//	UINT32	Value32;
	UINT64	Value64;
	UINTN	i;

	EFI_STATUS Status;

	EFI_PEI_CPU_IO_PPI	*CpuIoPpi;

	EFI_PEI_PCI_CFG2_PPI    *PciCfgPpi;
#if PI_SPECIFICATION_VERSION>=0x1000A
    BOOLEAN     Pi12Spec = FALSE;
    UINT64      PollDelay;
#endif
#if PI_SPECIFICATION_VERSION>=0x10000
    EFI_PEI_SMBUS2_PPI	*SmBusPpi;
#else
	EFI_PEI_SMBUS_PPI	*SmBusPpi;
#endif
	EFI_PEI_STALL_PPI	*StallPpi;

	if (FvFile) return EFI_UNSUPPORTED;
	if (!Address) return EFI_INVALID_PARAMETER;

	CpuIoPpi = (*PeiServices)->CpuIo;
	PciCfgPpi = (*PeiServices)->PciCfg;

	Status = (**PeiServices).LocatePpi (
        PeiServices,
        &gSmBusGuid,
        0,
        NULL,
        &SmBusPpi
        );
	if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;

	Status = (**PeiServices).LocatePpi (
        PeiServices,
        &gStallGuid,
        0,
        NULL,
        &StallPpi
        );
	if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;

	for(;;) {
#if PI_SPECIFICATION_VERSION>=0x0001000A
        PEI_TRACE((TRACE_ALWAYS,PeiServices,"UniqueIndex %x\n", ((BOOT_SCRIPT_INFO_STRUCTURE*) TableAddr)->UniqueIndex));
        TableAddr = (UINT8*) TableAddr + sizeof(BOOT_SCRIPT_INFO_STRUCTURE);
#endif   
		Type = *(UINT8*) TableAddr + (*((UINT8*) TableAddr + 1) << 8);	//In case not aligned if alignment required.
		switch(Type&0xff) {
		case EFI_BOOT_SCRIPT_IO_WRITE_OPCODE:
			MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_WRITE_IO));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_WRITE_IO);
			
			Width = (UINT8)(BootScript.WrIo.Type >> 8);
			ValueSize = 1 << (Width & 3);
			Count = BootScript.WrIo.Count;
			Buffer = TableAddr;

			AddressCount = ValueSize * (  ((Width & ~3) != EfiBootScriptWidthFifoUint8 ) ? (UINT32)Count : 1);
			TableAddr = (UINT8*)TableAddr + AddressCount;

			PEI_TRACE((TRACE_ALWAYS,PeiServices,"Io Write %x=", BootScript.WrIo.Port));
#ifdef EFI_DEBUG
			switch(ValueSize) {
			case 1:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%x\n", *(UINT8*)Buffer));
				break;
			case 2:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%x\n", *(UINT16*)Buffer));
				break;
			case 4:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%x\n", *(UINT32*)Buffer));
				break;
            case 8:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%lx\n", *(UINT64*)Buffer));
				break;
			default:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"Unknown\n"));
			}
#endif
			CpuIoPpi->Io.Write(PeiServices,
				CpuIoPpi,
				Width,
				BootScript.WrIo.Port,
				(UINTN)Count,
				Buffer);
			break;
		case EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE:
			MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_READ_WRITE_IO));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_READ_WRITE_IO);

			Width = (UINT8)((BootScript.WrIo.Type >> 8) & 3);	//Only EfiBootScriptWidthUintxx Supported

			CpuIoPpi->Io.Read(PeiServices,
				CpuIoPpi,
				Width,
				BootScript.RwIo.Port,
				1,
				&Value64);

			Value64 &= BootScript.RwIo.Mask;
			Value64 |= BootScript.RwIo.Value;

			PEI_TRACE((TRACE_ALWAYS,PeiServices,"Io R/Write %x=%x\n", BootScript.WrIo.Port,Value64));
			CpuIoPpi->Io.Write(PeiServices,
				CpuIoPpi,
				Width,
				BootScript.RwIo.Port,
				1,
				&Value64);
			break;
#if PI_SPECIFICATION_VERSION>=0x0001000A
        case EFI_BOOT_SCRIPT_IO_POLL_OPCODE:
			MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_IO_POLL));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_IO_POLL);
            PollDelay = Div64(BootScript.IoPoll.Delay, 10, NULL) + 1; // converting x100 ns units to ms, used in stall
            PEI_TRACE((TRACE_ALWAYS,PeiServices,"IO Poll Delay %lx *100ns\n", BootScript.IoPoll.Delay));
            Pi12Spec = TRUE;
#endif
		case EFI_BOOT_SCRIPT_IO_POLL_OPCODE_OEM:
#if PI_SPECIFICATION_VERSION>=0x0001000A
            if (!Pi12Spec)
#endif
            {
			    MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_POLL_IO));
			    TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_POLL_IO);
            }
			Width = (UINT8)((BootScript.PollIo.Type >> 8) & 3);	//Only EfiBootScriptWidthUintxx Supported

            PEI_TRACE((TRACE_ALWAYS,PeiServices,
                "Io Poll: Port = %x, Mask = %lx, Result = %lx\n",
                BootScript.PollIo.Port,
                BootScript.PollIo.Mask,
                BootScript.PollIo.Result
            ));

            do {
    			CpuIoPpi->Io.Read(PeiServices,
				    CpuIoPpi,
				    Width,
				    BootScript.PollIo.Port,
				    1,
				    &Value64);
			    Value64 &= BootScript.PollIo.Mask;
#if PI_SPECIFICATION_VERSION>=0x0001000A
                if (Pi12Spec)
                {
                    StallPpi->Stall(PeiServices, StallPpi, 1);
                    if (--PollDelay == 0) // delay criteria meet
                        Value64 = BootScript.PollIo.Result; //terminate cycle 
                }
#endif
            } while (Value64 != BootScript.PollIo.Result);
#if PI_SPECIFICATION_VERSION>=0x0001000A
            Pi12Spec = FALSE;    
#endif
			break;

		case EFI_BOOT_SCRIPT_MEM_WRITE_OPCODE:
			MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_WRITE_MEM));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_WRITE_MEM);
			Buffer = TableAddr;

			Width = (UINT8)(BootScript.WrMem.Type >> 8);
			ValueSize = 1 << (Width & 3);
			Count = BootScript.WrMem.Count;

			AddressCount = ValueSize * (  ((Width & ~3) != EfiBootScriptWidthFifoUint8 ) ? (UINT32)Count : 1);
			TableAddr = (UINT8*)TableAddr + AddressCount;

			PEI_TRACE((TRACE_ALWAYS,PeiServices,"Mem Write %lx=", BootScript.WrMem.Address));
#ifdef EFI_DEBUG
			switch(ValueSize) {
			case 1:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%x\n", *(UINT8*)Buffer));
				break;
			case 2:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%x\n", *(UINT16*)Buffer));
				break;
			case 4:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%x\n", *(UINT32*)Buffer));
				break;
            case 8:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%lx\n", *(UINT64*)Buffer));
				break;
			default:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"Unknown\n"));
			}
#endif
			CpuIoPpi->Mem.Write(PeiServices,
				CpuIoPpi,
				Width,
				BootScript.WrMem.Address,
				(UINTN)Count,
				Buffer);
			break;
		case EFI_BOOT_SCRIPT_MEM_READ_WRITE_OPCODE:
			MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_READ_WRITE_MEM));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_READ_WRITE_MEM);

			Width = (UINT8)((BootScript.WrMem.Type >> 8) & 3);	//Only EfiBootScriptWidthUintxx Supported

			CpuIoPpi->Mem.Read(PeiServices,
				CpuIoPpi,
				Width,
				BootScript.RwMem.Address,
				1,
				&Value64);

			Value64 &= BootScript.RwMem.Mask;
			Value64 |= BootScript.RwMem.Value;

			PEI_TRACE((TRACE_ALWAYS,PeiServices,"Mem R/Write %lx=%x\n", BootScript.WrMem.Address,(UINT32)Value64));
    		CpuIoPpi->Mem.Write(PeiServices,
				CpuIoPpi,
				Width,
				 BootScript.RwMem.Address,
				1,
				&Value64);
			break;
#if PI_SPECIFICATION_VERSION>=0x0001000A
        case EFI_BOOT_SCRIPT_MEM_POLL_OPCODE:
			MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_MEM_POLL));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_MEM_POLL);
            PollDelay = BootScript.MemPoll.LoopTimes + 1;
            PEI_TRACE((TRACE_ALWAYS,PeiServices,"Mem Poll Delay %lx \n", BootScript.MemPoll.Delay));
            PEI_TRACE((TRACE_ALWAYS,PeiServices,"Mem Poll Loop Times %lx \n", BootScript.MemPoll.LoopTimes));
            Pi12Spec = TRUE;
#endif       
        case EFI_BOOT_SCRIPT_MEM_POLL_OPCODE_OEM:
#if PI_SPECIFICATION_VERSION>=0x0001000A
            if (!Pi12Spec)
#endif
            {
			    MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_POLL_MEM));
			    TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_POLL_MEM);
            }
			Width = (UINT8)((BootScript.PollMem.Type >> 8) & 3);	//Only EfiBootScriptWidthUintxx Supported

            PEI_TRACE((TRACE_ALWAYS,PeiServices,
                "Mem Poll: Address = %lx, Mask = %lx, Result = %lx\n",
                BootScript.PollMem.Address,
                BootScript.PollMem.Mask,
                BootScript.PollMem.Result
            ));

            do { 
    			CpuIoPpi->Mem.Read(PeiServices,
    				CpuIoPpi,
    				Width,
    				BootScript.PollMem.Address,
    				1,
    				&Value64);

			    Value64 &= BootScript.PollMem.Mask;
#if PI_SPECIFICATION_VERSION>=0x0001000A
                if (Pi12Spec)
                {
                    UINTN Delay = (UINTN)BootScript.MemPoll.Delay;

                    StallPpi->Stall(PeiServices, StallPpi, Delay);
                    if (--PollDelay == 0) // delay criteria meet
                    {
                        PEI_TRACE((TRACE_ALWAYS, PeiServices, 
                            "Mem Poll: Address = %lx, Mask = %lx, Result = %lx\n", 
                            BootScript.PollMem.Address, BootScript.PollMem.Mask, Value64));
                        break;
                    }
                }
#endif

            } while (Value64 != BootScript.PollMem.Result);
#if PI_SPECIFICATION_VERSION>=0x0001000A
            Pi12Spec = FALSE;    
#endif
			break;
#if PI_SPECIFICATION_VERSION>=0x0001000A
        case EFI_BOOT_SCRIPT_PCI_CONFIG2_WRITE_OPCODE:
			MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_PCI_CFG2_WRITE));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_PCI_CFG2_WRITE);
            if (BootScript.WrPci2.Segment != 0)
                PciCfgPpi = SwitchPciCfgPpi(PeiServices, BootScript.WrPci2.Segment);
            if (PciCfgPpi == NULL) 
            {
                PEI_TRACE((-1,PeiServices,"Can't found PciCfgPpi.Segment %x\n", BootScript.WrPci2.Segment));
			    return EFI_UNSUPPORTED;
            }   
			PEI_TRACE((TRACE_ALWAYS,PeiServices,"PciCfg2 Write to Segment %x\n = ", BootScript.WrPci2.Segment));
            Pi12Spec = TRUE;

#endif
		case EFI_BOOT_SCRIPT_PCI_CONFIG_WRITE_OPCODE:
#if PI_SPECIFICATION_VERSION>=0x0001000A
            if (!Pi12Spec)            
#endif
            {
			    MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_WRITE_PCI));
			    TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_WRITE_PCI);
            }
			Width = (UINT8)(BootScript.WrPci.Type >> 8);
			ValueSize = 1 << (Width & 3);
			Count = BootScript.WrPci.Count;

			Buffer = TableAddr;

			AddressCount = ValueSize * (  ((Width & ~3) != EfiBootScriptWidthFifoUint8 ) ? (UINT32)Count : 1);
			TableAddr = (UINT8*)TableAddr + AddressCount;

			PEI_TRACE((TRACE_ALWAYS,PeiServices,"Pci Write %lx=", BootScript.WrPci.Address));
#ifdef EFI_DEBUG
			switch(ValueSize) {
			case 1:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%x\n", *(UINT8*)Buffer));
				break;
			case 2:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%x\n", *(UINT16*)Buffer));
				break;
			case 4:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%x\n", *(UINT32*)Buffer));
				break;
            case 8:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"%lx\n", *(UINT64*)Buffer));
				break;
			default:
				PEI_TRACE((TRACE_ALWAYS,PeiServices,"Unknown\n"));
			}
#endif
			for (i = 0; i < Count; ++i)
			{
				Status = PciCfgPpi->Write(PeiServices,
					PciCfgPpi,
					Width & 3,
					BootScript.WrPci.Address,
					Buffer);
				ASSERT_PEI_ERROR(PeiServices, Status);

				switch(Width & ~3)
				{
				case EfiBootScriptWidthUint8:
					Buffer = (UINT8*)Buffer + AddressCount;
					BootScript.WrPci.Address = PciRegAdd(BootScript.WrPci.Address,ValueSize);
					break;
				case EfiBootScriptWidthFifoUint8:
					Buffer = (UINT8*)Buffer + AddressCount;
					break;
				case EfiBootScriptWidthFillUint8:
					BootScript.WrPci.Address = PciRegAdd(BootScript.WrPci.Address,ValueSize);
				}
    		}
#if PI_SPECIFICATION_VERSION>=0x0001000A
            if (Pi12Spec)
            {
                Pi12Spec = FALSE;    
                PciCfgPpi = (*PeiServices)->PciCfg;// restore pointer
            }
#endif
			break;
#if PI_SPECIFICATION_VERSION>=0x0001000A
        case EFI_BOOT_SCRIPT_PCI_CONFIG2_READ_WRITE_OPCODE:
			MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_PCI_CFG2_READ_WRITE));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_PCI_CFG2_READ_WRITE);
            if (BootScript.RwPci2.Segment != 0)
                PciCfgPpi = SwitchPciCfgPpi(PeiServices, BootScript.RwPci2.Segment);
            if (PciCfgPpi == NULL) 
            {
                PEI_TRACE((-1,PeiServices,"Can't found PciCfgPpi.Segment %x\n", BootScript.RwPci2.Segment));
			    return EFI_UNSUPPORTED;
            }   
			PEI_TRACE((TRACE_ALWAYS,PeiServices,"PciCfg2 Read/Write to Segment %x\n = ", BootScript.RwPci2.Segment));
            Pi12Spec = TRUE;
#endif
		case EFI_BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_OPCODE:
#if PI_SPECIFICATION_VERSION>=0x0001000A
            if (!Pi12Spec)            
#endif
            {
			    MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_READ_WRITE_PCI));
			    TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_READ_WRITE_PCI);
            }
			Width = (UINT8)((BootScript.RwPci.Type >> 8) & 3);

			PEI_TRACE((TRACE_ALWAYS,PeiServices,"Pci R/Write %x\n", BootScript.RwPci.Address));

            Status = PciCfgPpi->Read(PeiServices,
				    PciCfgPpi,
                    Width,
                    BootScript.RwPci.Address,
                    &Value64
                    );
			ASSERT_PEI_ERROR(PeiServices, Status);
    
            Value64 = BootScript.RwPci.Value | (Value64 & BootScript.RwPci.Mask);
    
            Status = PciCfgPpi->Write(PeiServices,
				    PciCfgPpi,
                    Width,
                    BootScript.RwPci.Address,
                    &Value64
                    );
			ASSERT_PEI_ERROR(PeiServices, Status);
#if PI_SPECIFICATION_VERSION>=0x0001000A
            if (Pi12Spec)
            {
                Pi12Spec = FALSE;    
                PciCfgPpi = (*PeiServices)->PciCfg;// restore pointer
            }
#endif
			break;
#if PI_SPECIFICATION_VERSION>=0x0001000A
        case EFI_BOOT_SCRIPT_PCI_CONFIG2_POLL_OPCODE:
            MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_PCI_CFG2_POLL));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_PCI_CFG2_POLL);
            if (BootScript.PciPoll2.Segment != 0)
                PciCfgPpi = SwitchPciCfgPpi(PeiServices, BootScript.PciPoll2.Segment);
            if (PciCfgPpi == NULL) 
            {
                PEI_TRACE((-1,PeiServices,"Can't found PciCfgPpi.Segment %x\n", BootScript.PciPoll2.Segment));
			    return EFI_UNSUPPORTED;
            }   
			PEI_TRACE((TRACE_ALWAYS,PeiServices,"PciCfg2 Poll to Segment %x\n = ", BootScript.PciPoll2.Segment));
            Pi12Spec = TRUE;
            
        case EFI_BOOT_SCRIPT_PCI_CONFIG_POLL_OPCODE:
            if (!Pi12Spec)
            {
        	    MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_PCI_CFG_POLL));
			    TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_PCI_CFG_POLL);
                Pi12Spec = TRUE;
            }
            PollDelay = Div64(BootScript.PciPoll.Delay, 10, NULL) + 1; // converting x100 ns units to ms, used in stall
            PEI_TRACE((TRACE_ALWAYS,PeiServices,"PciCfg Poll Delay %lx *100ns\n", BootScript.PciPoll.Delay));
#endif
        case EFI_BOOT_SCRIPT_PCI_POLL_OPCODE_OEM:
#if PI_SPECIFICATION_VERSION>=0x0001000A
            if (!Pi12Spec)
#endif
            {
			    MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_POLL_PCI));
			    TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_POLL_PCI);
            }
			Width = (UINT8)((BootScript.PollPci.Type >> 8) & 3);

            PEI_TRACE((TRACE_ALWAYS,PeiServices,
                "PCI Poll: Address = %x, Mask = %lx, Result = %lx\n",
                BootScript.PollPci.Address,
                BootScript.PollPci.Mask,
                BootScript.PollPci.Result
            ));

            do {
                PciCfgPpi->Read(PeiServices,
                    PciCfgPpi,
                    Width,
                    BootScript.PollPci.Address,
                    &Value64
                );
                Value64 &= BootScript.PollPci.Mask;
#if PI_SPECIFICATION_VERSION>=0x0001000A
                if (Pi12Spec)
                {
                    StallPpi->Stall(PeiServices, StallPpi, 1);
                    if (--PollDelay == 0) // delay criteria meet
                        Value64 = BootScript.PollPci.Result; //terminate cycle 
                }
#endif
            } while (Value64 != BootScript.PollPci.Result);
#if PI_SPECIFICATION_VERSION>=0x0001000A
        if (Pi12Spec)
            {
                Pi12Spec = FALSE;    
                PciCfgPpi = (*PeiServices)->PciCfg;// restore pointer
            }
#endif
        break;

		case EFI_BOOT_SCRIPT_SMBUS_EXECUTE_OPCODE:
			MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_SMBUS_EXECUTE));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_SMBUS_EXECUTE);
			Buffer = TableAddr;
			TableAddr = (UINT8*)TableAddr + BootScript.ExecSmbus.Length;

            PEI_TRACE((-1,PeiServices,
                "Smbus: Address = %x, Command = %x Operation = %x\n",
                BootScript.ExecSmbus.SlaveAddress,
                BootScript.ExecSmbus.Command,
                BootScript.ExecSmbus.Operation
            ));

            //Note: In specification, the length pointer is a IN/OUT.
            //However, I do find that its contents updated.
            SmBusPpi->Execute(
#if PI_SPECIFICATION_VERSION<0x10000
                PeiServices,
#endif
                SmBusPpi,
                BootScript.ExecSmbus.SlaveAddress,
                BootScript.ExecSmbus.Command,
                BootScript.ExecSmbus.Operation,
                BootScript.ExecSmbus.PecCheck,
                (UINTN*)&BootScript.ExecSmbus.Length,
	            Buffer
	        );
    		break;

		case EFI_BOOT_SCRIPT_STALL_OPCODE:
			MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_STALL));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_STALL);

			StallPpi->Stall(PeiServices,
				StallPpi,
				(UINTN)BootScript.Stall.Duration);
			break;

		case EFI_BOOT_SCRIPT_DISPATCH_OPCODE:
            PEI_TRACE((-1,PeiServices,"Dispatch Opcode.\n"));
			MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_DISPATCH));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_DISPATCH);
			((DISPATCH_ENTRYPOINT_FUNC)(UINTN)BootScript.Dispatch.EntryPoint)(NULL, PeiServices);
			break;

#if PI_SPECIFICATION_VERSION>=0x0001000A

        case EFI_BOOT_SCRIPT_DISPATCH_2_OPCODE:
            MemCpy(&BootScript,TableAddr,sizeof(BOOT_SCRIPT_DISPATCH2));
			TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_DISPATCH2);
			((DISPATCH_ENTRYPOINT_FUNC)(UINTN)BootScript.Dispatch.EntryPoint)(NULL, PeiServices);
			break;

        case EFI_BOOT_SCRIPT_INFORMATION_OPCODE:
            TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_INFORMATION);
            PEI_TRACE((-1,PeiServices,"Skipping Information opcode in Boot Script.\n"));
        break;
        case EFI_BOOT_SCRIPT_LABEL_OPCODE_OEM:
            TableAddr = (UINT8*)TableAddr + sizeof(BOOT_SCRIPT_LABEL)
                                          + ((BOOT_SCRIPT_LABEL*)TableAddr)->Size;
            PEI_TRACE((-1,PeiServices,"Skipping Label opcode in Boot Script.\n"));
        break;
            
#endif
		case TABLE_END_OP_CODE:
            PEI_TRACE((-1,PeiServices,"Table End Found.\n"));
			return EFI_SUCCESS;


		default:
			PEI_TRACE((-1,PeiServices,"Boot Script Table Invalid. Type = %x\n", Type));
			return EFI_UNSUPPORTED;
		}
	}
}


EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI gBootScriptExecuterPpi =
{
	ExecuteScript
};


EFI_PEI_PPI_DESCRIPTOR gPpiList =
{
	(EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
	&gBootScriptExecuterGuid,
	&gBootScriptExecuterPpi
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: InitBootScriptExecuter
//
// Description: Increase the Pci register number by a value.
//
// Input: 
//	IN EFI_FFS_FILE_HEADER	*FfsHeader
//	IN EFI_PEI_SERVICES		**PeiServices
//
// Output: 
//	EFI_STATUS
//
// Modified:
//
// Referrals: InstallPpi
//
// Notes:
//  Here is the control flow of this function:
//  1. Install Boot Script Executer Ppi.
//	2. Return status of InstallPpi.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitBootScriptExecuter(
	IN EFI_FFS_FILE_HEADER	*FfsHeader,
	IN EFI_PEI_SERVICES		**PeiServices
	)
{
	return (**PeiServices).InstallPpi(
		PeiServices,
		&gPpiList
		);

}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
