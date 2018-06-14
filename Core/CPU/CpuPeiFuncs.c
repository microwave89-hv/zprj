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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPeiFuncs.c 10    8/06/14 11:57p Crystallee $
//
// $Revision: 10 $
//
// $Date: 8/06/14 11:57p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPeiFuncs.c $
// 
// 10    8/06/14 11:57p Crystallee
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Add special case for saving MTRRs.
// 
// 9     8/05/14 2:21a Crystallee
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	For backward compatible, add old MTRR setting method
// back. Change new MTRR setting method to Policy2.
// 
// 8     7/08/14 3:35a Crystallee
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Add all the possible methods to describing memory in
// MTRRS.
// [Files]  		CpuPei.c, CpuPei.h, CpuPeiFuncs.c
// 
// 7     6/03/13 2:37a Hsingyingchung
// [TAG]  		EIP123835
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	SBY Performance Tuning Guid rev. 1.1 update.
// 
// 6     2/07/13 3:59a Hsingyingchung
// [TAG]  		EIP112631
// [Category]  	Improvement
// [Description]  	add PEI/DMI ratio control item.
// 
// 5     12/20/12 10:09a Hsingyingchung
// [TAG]  		EIP 
// [Category]  	Improvement
// [Description]  	Remove mailbox item limit. Because mailbox item is not
// be effected by turbo mode support or not. 
// 
// 4     11/23/12 2:10a Hsingyingchung
// [TAG]  		EIP99095
// [Category]  	Improvement
// [Description]  	Update by XTU 4.X
// 
// 3     10/25/12 4:01a Davidhsieh
// Add ReadOnlyVariable.h file include
// 
// 2     3/09/12 2:14a Davidhsieh
// Use all variable MTRRs
// 
// 1     2/07/12 3:58a Davidhsieh
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:        CpuPeiFuncs.c
//
// Description:
//  This file is the main CPU PEI component file. This file provides
//  misc functions for CPU PEI drvier usage.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "cpu.h"
#include "AmiCspLibInc.h"
#include <AmiPeiLib.h>
#include <core\PeiHob.h>
#include <token.h>
#include <Ppi\ReadOnlyVariable.h>
#include "CpuPei.h"
#include "Setup.h"

#if PERF_TUNE_SUPPORT == 1
    #include <Ppi\PerfTunePpi.h>
    #include <PerfTune.h>

    //TODO: Update library and remove private structure.
    typedef struct {
        SETUP_DATA *SetupData;
    } PRIVATE_CPU_SETUP_LIB;

    EFI_GUID gAmiDddtPreFlagHobGuid = AMI_DDDT_PRESENT_FLAG_HOB_GUID;
	EFI_GUID gAmiOcConfigHobGuid = AMI_OVERCLOCK_CONFIG_HOB_GUID;   
#endif

#if MTRR_POLICY == 1
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure: InitMtrrPolicy1
//
// Description: Config system cache.
//
// Input:
//      IN EFI_PEI_SERVICES     **PeiServices
//      IN PEI_CACHE_PPI        *CachePpi
//      IN UINT64               Above4GMemoryLength
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitMtrrPolicy1 (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN MEMORY_MAP                   *WbMap,
    IN MEMORY_MAP                   *UcMap,
    IN UINT64                       Above4GMemoryLength
)
{

    UINT64  TotalAbove4GMemoryLength = Above4GMemoryLength + SIZE_4G;
    UINT64  RemainMemoryLength = TotalAbove4GMemoryLength - GetPowerOfTwo64(TotalAbove4GMemoryLength);
    UINT64  Below4GMemoryLength;    
    UINT64  MemoryLengthUc;    
    UINT64  CurrentBaseAddress;    
    UINT64  PowerTwo;    
    UINTN   i, WbCount = 0, UcCount = 0;
    UINT8   MtrrCount = 0;
    UINT8	NumOfOne = 0;    
                
    CurrentBaseAddress = 0;     
    
    for(i = 0; i < 10; i++){
        WbMap[i].Len = 0;
        UcMap[i].Len = 0;
    }
    
    WbMap[WbCount].Base = CurrentBaseAddress;
    WbMap[WbCount].Len = GetPowerOfTwo64(TotalAbove4GMemoryLength);                
    WbCount++;                
    MtrrCount++;

    Below4GMemoryLength = (UINT64)NBGetTsegBase() + TSEG_SIZE;
    
    //
    // UC memory length below 4GB = 4GB - total memory length below 4GB
    //
    MemoryLengthUc = SIZE_4G - Below4GMemoryLength;            
    CurrentBaseAddress = SIZE_4G - GetPowerOfTwo64 (MemoryLengthUc);
    
    for (PowerTwo = GetPowerOfTwo64 (MemoryLengthUc); 
                CurrentBaseAddress >= Below4GMemoryLength; PowerTwo = GetPowerOfTwo64 (MemoryLengthUc)) {
                
        //PEI_TRACE((-1, PeiServices, "UC Memory Length = %08lx at %08lx.\n", PowerTwo, CurrentBaseAddress));        
        UcMap[UcCount].Base = CurrentBaseAddress;
        UcMap[UcCount].Len = PowerTwo;     
        MemoryLengthUc -= PowerTwo;
        CurrentBaseAddress -= GetPowerOfTwo64 (MemoryLengthUc);
        UcCount++;
        MtrrCount++;
        if (MtrrCount > VariableMtrrCount) return EFI_OUT_OF_RESOURCES;
    }    
    
    //
    // Calculate how many MTRRs needs if only use WB type
    //
    for (i = 0; i < 32; i++) {
        if (Shr64(RemainMemoryLength, i) & 0x1 )
            NumOfOne++;
    }
    
    //PEI_TRACE((-1, PeiServices, "Remain above 4G Memory Length = %08lx number of one = %x.\n", RemainMemoryLength, NumOfOne));
    
    if (NumOfOne + MtrrCount < VariableMtrrCount){  //Use WB range is enough
    
        CurrentBaseAddress = GetPowerOfTwo64(TotalAbove4GMemoryLength);
        while(RemainMemoryLength)
        {   
            PowerTwo = GetPowerOfTwo64 (RemainMemoryLength);            
            WbMap[WbCount].Base = CurrentBaseAddress;
            WbMap[WbCount].Len = PowerTwo;
            WbCount++;  
            CurrentBaseAddress += (UINT64)PowerTwo;
            RemainMemoryLength -= (UINT64)PowerTwo;
            MtrrCount++;
            if (MtrrCount > VariableMtrrCount) return EFI_OUT_OF_RESOURCES;
        }
    } else{
        //
        // Use UC to overwrite WB memory
        //
        if ((RemainMemoryLength - GetPowerOfTwo64(RemainMemoryLength)) < SIZE_2G)
        {
            WbMap[WbCount].Base = GetPowerOfTwo64(TotalAbove4GMemoryLength);    
            WbMap[WbCount].Len = GetPowerOfTwo64(RemainMemoryLength);            
            RemainMemoryLength -= WbMap[WbCount].Len;
            WbCount++;
			MtrrCount++;
            WbMap[WbCount].Base = WbMap[WbCount - 1].Base + WbMap[WbCount - 1].Len;
            WbMap[WbCount].Len = GetPowerOfTwo64(Shl64(RemainMemoryLength,1));
            
            MemoryLengthUc = WbMap[WbCount].Len - RemainMemoryLength;        
            CurrentBaseAddress = (WbMap[WbCount].Base + WbMap[WbCount].Len) - GetPowerOfTwo64(MemoryLengthUc);
            if ((WbMap[WbCount].Len + WbMap[WbCount - 1].Len) == GetPowerOfTwo64(WbMap[WbCount].Len + WbMap[WbCount - 1].Len))
            {
                WbMap[WbCount - 1].Len += WbMap[WbCount].Len;
                WbMap[WbCount].Base = 0;
                WbMap[WbCount].Len = 0;
            } else {               
                WbCount++;
				MtrrCount++;
			}
            
        } else{    
            WbMap[WbCount].Base = GetPowerOfTwo64(TotalAbove4GMemoryLength);
            WbMap[WbCount].Len = GetPowerOfTwo64(Shl64(RemainMemoryLength,1));
            if (WbMap[WbCount - 1].Len == WbMap[WbCount].Base){
                // special case to save mtrr
                WbMap[WbCount - 1].Len += WbMap[WbCount].Len;
                WbMap[WbCount].Base = 0;
                WbMap[WbCount].Len = 0;
                WbCount--;
				MtrrCount--;
            }         
            
            MemoryLengthUc = (WbMap[WbCount].Base + WbMap[WbCount].Len) - TotalAbove4GMemoryLength;        
            CurrentBaseAddress = (WbMap[WbCount].Base + WbMap[WbCount].Len) - GetPowerOfTwo64(MemoryLengthUc);
            WbCount++;
			MtrrCount++;
        }
        //PEI_TRACE((-1, PeiServices, "Above 4G UC Memory Length = %08lx base start at %08lx.\n", MemoryLengthUc, CurrentBaseAddress));
        for (PowerTwo = GetPowerOfTwo64 (MemoryLengthUc); 
                CurrentBaseAddress >= TotalAbove4GMemoryLength; PowerTwo = GetPowerOfTwo64 (MemoryLengthUc)) {                
            
            UcMap[UcCount].Base = CurrentBaseAddress;
            UcMap[UcCount].Len = PowerTwo;     
            MemoryLengthUc -= PowerTwo;
            CurrentBaseAddress -= GetPowerOfTwo64 (MemoryLengthUc);
            UcCount++;
            MtrrCount++;
            if (MtrrCount > VariableMtrrCount) return EFI_OUT_OF_RESOURCES;
        }
    }
	
    PEI_TRACE((-1, PeiServices, "Set MTRR policy1 success. MtrrCount = %d\n", MtrrCount));
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure: NumOfOne
//
// Description: Count how many of ones in the binary value.
//
// Input:
//      IN UINT64 InputValue - Needed count value.
//
// Output:
//      UINT8 - Number of one.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 NumOfOne(
	IN UINT64  InputValue)
{
	UINT8   i, j;

	for (i = 0, j = 0; i < 40; i++) {
        if (Shr64(InputValue, i) & 0x1 )
            j++;
		if (Shr64(InputValue, i) == 0)
			break;
    }
	return j;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure: InitMtrrPolicy2
//
// Description: Config system cache.
//
// Input:
//      IN EFI_PEI_SERVICES     **PeiServices
//      IN PEI_CACHE_PPI        *CachePpi
//      IN UINT64               Above4GMemoryLength
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitMtrrPolicy2 (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN MEMORY_MAP                   *WbMap,
    IN MEMORY_MAP                   *UcMap,
    IN UINT64                       Above4GMemoryLength
)
{
    UINT64  TotalMemoryLength = Above4GMemoryLength + SIZE_4G;
    UINT64  RemainMemoryLength;
    UINT64  Below4GMemoryLength;      
    UINTN   i;
	UINT8	WbMtrrCountBelow4G1 = 0;
	UINT8	WbMtrrCountBelow4G2 = 0;
	UINT8	UcMtrrCountBelow4G1 = 0;
	UINT8	UcMtrrCountBelow4G2 = 0;
	UINT8	WbMtrrCountAbove4G1 = 0;
	UINT8	WbMtrrCountAbove4G2 = 0;
	UINT8	UcMtrrCountAbove4G1 = 0;
	UINT8	UcMtrrCountAbove4G2 = 0;
	UINT8	UcMtrrCountAbove4G3 = 0;
	UINT8	UcMtrrCountAbove4G4 = 0;
	UINT8	MtrrCountRemainMemory1 = 0;
	UINT8	MtrrCountRemainMemory2 = 0;
	UINT8	MtrrCountRemainMemory3 = 0;
	UINT64	MemoryLength;
	UINT8   PolicyOneMtrrCount = 0;
	UINT8   PolicyTwoMtrrCount = 0;
	UINT8   PolicyThreeMtrrCount = 0;
	UINT8   PolicyFourMtrrCount = 0;
	UINT8   PolicyFiveMtrrCount = 0;
	UINT8   PolicySixMtrrCount = 0;
	BOOLEAN WbSpecialCase1 = 0;
	BOOLEAN WbSpecialCase2 = 0;

    for(i = 0; i < 10; i++){
        WbMap[i].Len = 0;
        UcMap[i].Len = 0;
    }

	//First, we calculate how many MTRR we need in different situation.
	//1. Calculating MTRR when only use wb type in below 4G memory
	//There are two size of Below4GMemoryLength. One is NBGetTsegBase() + TSEG_SIZE, the other is NBGetTsegBase().
	//Therefore we have two calculating method to calculate wb MTRR below 4G memory.
	//A.When Below4GMemoryLength is NBGetTsegBase()
	Below4GMemoryLength = (UINT64)NBGetTsegBase();
	WbMtrrCountBelow4G1 = NumOfOne(Below4GMemoryLength);

	//B.When Below4GMemoryLength is NBGetTsegBase() + TSEG_SIZE
	Below4GMemoryLength = (UINT64)NBGetTsegBase() + TSEG_SIZE;
	WbMtrrCountBelow4G2 = NumOfOne(Below4GMemoryLength);
	
	//2. Calculating MTRR when use wb type from 0 to 4G, then use uc type to overwrite 4G to Below4GMemoryLength.
	//There are two size of Below4GMemoryLength. One is NBGetTsegBase() + TSEG_SIZE, the other is NBGetTsegBase().
	//Therefore we have two calculating method to calculate uc MTRR below 4G memory.
	//A.When Below4GMemoryLength is NBGetTsegBase()
	Below4GMemoryLength = (UINT64)NBGetTsegBase();
	UcMtrrCountBelow4G1 = NumOfOne(((UINT64)SIZE_4G - Below4GMemoryLength));

	//B.When Below4GMemoryLength is NBGetTsegBase() + TSEG_SIZE
	Below4GMemoryLength = (UINT64)NBGetTsegBase() + TSEG_SIZE;
	UcMtrrCountBelow4G2 = NumOfOne(((UINT64)SIZE_4G - Below4GMemoryLength));

	//3. Calculating MTRR when Memory above 4G is larger then 4G. 
	//A.If it's larger then 4G, memory above 4G should minus SIZE_4G and MTRR count should add 1. 
	//Next, if remain memory above 4G still larger than SIZE_8G, remain memory minus SIZE_8G and MTRR count should add 1.
	//Next, if remain memory above 4G still larger than SIZE_16G, remain memory minus SIZE_16G and MTRR count should add 1. And so on.
	RemainMemoryLength = Above4GMemoryLength;
	MemoryLength = SIZE_4G;
	for (MtrrCountRemainMemory1 = 0; RemainMemoryLength >= MemoryLength; MemoryLength = Shl64(MemoryLength, 1)) {
		MtrrCountRemainMemory1++;
		RemainMemoryLength -= MemoryLength;
	}

	//B.Calculating MTRR when use wb type till remain memory is smaller then 2G
	MemoryLength = GetPowerOfTwo64(RemainMemoryLength);
	for (MtrrCountRemainMemory2 = 0; RemainMemoryLength >= SIZE_2G;) {
		MemoryLength = GetPowerOfTwo64(RemainMemoryLength);
		MtrrCountRemainMemory2++;
		RemainMemoryLength -= MemoryLength;
	}
	
	//C.Calculating MTRR when only use wb type in remain memory
	WbMtrrCountAbove4G1 = NumOfOne(RemainMemoryLength) + MtrrCountRemainMemory2;
	
	//Special case for saving MTRR. If wb setting can combine with previous wb setting. This case only occur in Policy two.
	if ((MtrrCountRemainMemory2 != 0) && (Shl64(GetPowerOfTwo64 (RemainMemoryLength), 1) == MemoryLength))
		WbSpecialCase1 = 0;
	else
		WbSpecialCase1 = 1;
	
	//D.Calculating MTRR when use uc type to overwrite wb type.
	RemainMemoryLength = (Shl64(GetPowerOfTwo64 (RemainMemoryLength), 1)) - RemainMemoryLength;
	UcMtrrCountAbove4G2 = NumOfOne(RemainMemoryLength);

	//4. Calculating MTRR when use uc type to overwrite wb type above 4G memory, there are two calculating methods.
	//A.Set wb type from 4G to shl(PowerOfTwo64(TotalMemoryLength),1), 
	//then use uc to overwrite overflow wb memory.
	RemainMemoryLength = TotalMemoryLength - Shl64(SIZE_4G , MtrrCountRemainMemory1);
	RemainMemoryLength = (Shl64(GetPowerOfTwo64 (RemainMemoryLength), 1)) - RemainMemoryLength;
	UcMtrrCountAbove4G1 = NumOfOne(RemainMemoryLength);

	//B.Set wb type from 0 to shl(PowerOfTwo64(TotalMemoryLength), 1), 
	//then use uc to overwrite overflow wb memory.
	RemainMemoryLength = (Shl64(GetPowerOfTwo64 (TotalMemoryLength), 1)) - TotalMemoryLength;
	UcMtrrCountAbove4G3 = NumOfOne(RemainMemoryLength);
	
	//5. Calculating MTRR when (TotalMemoryLength) minus PowerOfTwo64(TotalMemoryLength) is larger then 2G.
	//A. Calculating MTRR when use wb type till remain memory is smaller then 2G
	RemainMemoryLength = TotalMemoryLength - GetPowerOfTwo64(TotalMemoryLength);
	MemoryLength = GetPowerOfTwo64(RemainMemoryLength);
	for (MtrrCountRemainMemory3 = 0; RemainMemoryLength >= SIZE_2G;) {
		MemoryLength = GetPowerOfTwo64(RemainMemoryLength);
		MtrrCountRemainMemory3++;
		RemainMemoryLength -= MemoryLength;
	}
	//B.Calculating MTRR when use wb type in Remain memory
	WbMtrrCountAbove4G2 = NumOfOne(RemainMemoryLength) + MtrrCountRemainMemory3;
	
	//Special case for saving MTRR. If wb setting can combine with previous wb setting. This case only occur in Policy five.
	if ((MtrrCountRemainMemory3 != 0) && (Shl64(GetPowerOfTwo64 (RemainMemoryLength), 1) == MemoryLength))
		WbSpecialCase2 = 0;
	else
		WbSpecialCase2 = 1;
	
	//C.Calculating MTRR when use uc type to overwrite wb type.
	RemainMemoryLength = (Shl64(GetPowerOfTwo64 (RemainMemoryLength), 1)) - RemainMemoryLength;
	UcMtrrCountAbove4G4 = NumOfOne(RemainMemoryLength);

	//Second, Calculating MTRR for each setting MTRR policy.
	//Policy 1:Only use wb type from 0 to Below4GMemoryLength, and 4G to TotalMemoryLength.
	//
	//		_______  TotalMemoryLength
	//	   |Wb Set |
	//	   |-------| 4G
	//	   |Uc Ori |
	//	   |-------| Below4GMemoryLength
	//	   |Wb Set |
	//	   |_______| 0
	//Chose which Below4GMemoryLength((NBGetTsegBase() + TSEG_SIZE) or NBGetTsegBase()) is better for below 4G memory MTRR setting.
	if (WbMtrrCountBelow4G1 < WbMtrrCountBelow4G2)
		PolicyOneMtrrCount = WbMtrrCountBelow4G1 + WbMtrrCountAbove4G1 + MtrrCountRemainMemory1;
	else
		PolicyOneMtrrCount = WbMtrrCountBelow4G2 + WbMtrrCountAbove4G1 + MtrrCountRemainMemory1;
	
	//Policy 2:First, Use wb type from 0 to Below4GMemoryLength. Use wb type from 4G to 8G, 8G to 16G, and so on.
	//		   Second, if remain memory larger then 2G , use wb type till remain memory samller then 2G. last, set wb type to shl(RemainMemory, 1).
	//		   Third, use uc type from shl(RemainMemory, 1) to TotalMemoryLength.
	//		first Second												 third
	//	   |-------|   													|-------| shl(RemainMemory, 1)
	//	   |       |    					   						   	|Uc Set |
	//	   |Wb Set |												   	|_______| TotalMemoryLength
	//	   |-------| 4G												   	|-------| 4G 
	//	   |Uc Ori |												   	|Same   |
	//	   |-------| Below4GMemoryLength							   	|as     |
	//	   |Wb Set |												   	|first  |
	//	   |_______| 0												   	|_______| 0
	//Chose which Below4GMemoryLength((NBGetTsegBase() + TSEG_SIZE) or NBGetTsegBase()) is better for below 4G memory MTRR setting.
	if (WbMtrrCountBelow4G1 < WbMtrrCountBelow4G2)
		PolicyTwoMtrrCount = WbMtrrCountBelow4G1 + MtrrCountRemainMemory1 + MtrrCountRemainMemory2 + WbSpecialCase1 + UcMtrrCountAbove4G2;
	else
		PolicyTwoMtrrCount = WbMtrrCountBelow4G2 + MtrrCountRemainMemory1 + MtrrCountRemainMemory2 + WbSpecialCase1 + UcMtrrCountAbove4G2;
	
	//Policy 3:	First, Use wb type from 0 to Below4GMemoryLength. Use wb type from 4G to 8G, 8G to 16G, and so on.
	//			Second, set wb type to shl(RemainMemory, 1).
	//		  	Third, use uc type form shl(RemainMemory, 1) to TotalMemoryLength;
	//		first Second												 third
	//	   |-------| shl(PowerOfTwo64(TotalMemoryLength), 1)   			|-------| shl(PowerOfTwo64(TotalMemoryLength), 1)
	//	   |       |    					   						   	|Uc Set |
	//	   |Wb Set |												   	|_______| TotalMemoryLength
	//	   |-------| 4G												   	|-------| 4G 
	//	   |Uc Ori |												   	|Same   |
	//	   |-------| Below4GMemoryLength							   	|as     |
	//	   |Wb Set |												   	|first  |
	//	   |_______| 0												   	|_______| 0
	//Chose which Below4GMemoryLength((NBGetTsegBase() + TSEG_SIZE) or NBGetTsegBase()) is better for below 4G memory MTRR setting.
	if (WbMtrrCountBelow4G1 < WbMtrrCountBelow4G2)
		PolicyThreeMtrrCount = WbMtrrCountBelow4G1 + MtrrCountRemainMemory1 + 1 + UcMtrrCountAbove4G1;
	else
		PolicyThreeMtrrCount = WbMtrrCountBelow4G2 + MtrrCountRemainMemory1 + 1 + UcMtrrCountAbove4G1;
	
	//Policy 4:	First, use wb type from 0 to PowerOfTwo64(TotalMemoryLength). 
	//		  	Second, use uc type from 4G to Below4GMemoryLength.
	//			Third, use wb type from PowerOfTwo64(TotalMemoryLength) to TotalMemoryLength.
	//		first														second and third
	//	   |--------| PowerOfTwo64(TotalMemoryLength)					 _______  TotalMemoryLength
	//	   |       	|    					   						   	|Wb Set |
	//	   |Wb Set 	|												   	|-------| PowerOfTwo64(TotalMemoryLength)
	//	   |ALL   	|	    											|       |  
	//	   |	   	|												   	|-------| 4G
	//	   |	   	|												   	|Uc Set |
	//	   |		|												   	|-------| Below4GMemoryLength
	//	   |________| 0												   	|_______| 0
	//Chose which Below4GMemoryLength is better for below 4G memory MTRR setting.
	if (UcMtrrCountBelow4G1 < UcMtrrCountBelow4G2)
		PolicyFourMtrrCount = 1 + UcMtrrCountBelow4G1 + WbMtrrCountAbove4G2;
	else
		PolicyFourMtrrCount = 1 + UcMtrrCountBelow4G2 + WbMtrrCountAbove4G2;
	
	//Policy 5:	First, use wb type from 0 to PowerOfTwo64(TotalMemoryLength). 
	//		  	Second, use uc type from 4G to Below4GMemoryLength.
	//			Third, remain memory will be (TotalMemoryLength - PowerOfTwo64(TotalMemoryLength)) use wb type\  
	//				   from PowerOfTwo64(TotalMemoryLength) to shl(RemainMemory, 1).
	//			Four, use uc type from shl(RemainMemory, 1) to TotalMemoryLength.
	//		first										 second and third							 Four
	//	   |--------| PowerOfTwo64(TotalMemoryLength)	 -------  shl(RemainMemory, 1)				 -------  shl(RemainMemory, 1)
	//	   |       	|    					   			|_______| TotalMemoryLength					|Uc Set | 
	//	   |Wb Set 	|									|Wb Set | 									|_______| TotalMemoryLength
	//	   |ALL   	|	    							|-------| PowerOfTwo64(TotalMemoryLength)	|	   	|
	//	   |	   	|									|-------| 4G								|Same 	|
	//	   |	   	|									|Uc Set |									|as	   	|
	//	   |		|									|-------| Below4GMemoryLength				|before	|
	//	   |________| 0									|_______| 0									|_______| 0
	//Chose which Below4GMemoryLength is better for below 4G memory MTRR setting.
	if (UcMtrrCountBelow4G1 < UcMtrrCountBelow4G2)
		PolicyFiveMtrrCount = 1 + UcMtrrCountBelow4G1 + MtrrCountRemainMemory3 + WbSpecialCase2 + UcMtrrCountAbove4G4;
	else
		PolicyFiveMtrrCount = 1 + UcMtrrCountBelow4G2 + MtrrCountRemainMemory3 + WbSpecialCase2 + UcMtrrCountAbove4G4;
	
	//Policy 6:First, use wb type to shl(PowerOfTwo64(TotalMemoryLength), 1). 
	//		  Second, use uc type from 4G to Below4GMemoryLength and 
	//		  Uc type from shl(PowerOfTwo64(TotalMemoryLength), 1) to TotalMemoryLength.
	//		first														second
	//	   |--------| shl(PowerOfTwo64(TotalMemoryLength), 1)			|-------| shl(PowerOfTwo64(TotalMemoryLength), 1)
	//	   |       	|    					   						   	|Uc Set |
	//	   |Wb Set 	|												   	|_______| TotalMemoryLength
	//	   |ALL   	|	    											|       |  
	//	   |	   	|												   	|-------| 4G
	//	   |	   	|												   	|Uc Set |
	//	   |		|												   	|-------| Below4GMemoryLength
	//	   |________| 0												   	|_______| 0
	//Chose which Below4GMemoryLength is better for below 4G memory MTRR setting.
	if (UcMtrrCountBelow4G1 < UcMtrrCountBelow4G2)
		PolicySixMtrrCount = 1 + UcMtrrCountBelow4G1 + UcMtrrCountAbove4G3;
	else
		PolicySixMtrrCount = 1 + UcMtrrCountBelow4G2 + UcMtrrCountAbove4G3;
	
//	PEI_TRACE((-1, PeiServices, "WbMtrrCountBelow4G1 = %d, WbMtrrCountBelow4G2 = %d.\n", WbMtrrCountBelow4G1, WbMtrrCountBelow4G2));
//	PEI_TRACE((-1, PeiServices, "UcMtrrCountBelow4G1 = %d, UcMtrrCountBelow4G2 = %d.\n", UcMtrrCountBelow4G1, UcMtrrCountBelow4G2));
//	PEI_TRACE((-1, PeiServices, "WbMtrrCountAbove4G1 = %d, WbMtrrCountAbove4G2= %d, UcMtrrCountAbove4G1 = %d.\n", WbMtrrCountAbove4G1, WbMtrrCountAbove4G2, UcMtrrCountAbove4G1));
//	PEI_TRACE((-1, PeiServices, "UcMtrrCountAbove4G2 = %d, UcMtrrCountAbove4G3 = %d, UcMtrrCountAbove4G4= %d.\n", UcMtrrCountAbove4G2, UcMtrrCountAbove4G3, UcMtrrCountAbove4G4));
//	PEI_TRACE((-1, PeiServices, "WbSpecialCase1 = %d, WbSpecialCase2 = %d.\n", WbSpecialCase1, WbSpecialCase2));
//	PEI_TRACE((-1, PeiServices, "MtrrCountRemainMemory1 = %d, MtrrCountRemainMemory2 = %d, MtrrCountRemainMemory3 = %d.\n", MtrrCountRemainMemory1, MtrrCountRemainMemory2, MtrrCountRemainMemory3));
//	PEI_TRACE((-1, PeiServices, "PolicyOneMtrrCount = %d, PolicyTwoMtrrCount = %d, PolicyThreeMtrrCount = %d.\n", PolicyOneMtrrCount, PolicyTwoMtrrCount, PolicyThreeMtrrCount));
//	PEI_TRACE((-1, PeiServices, "PolicyFourMtrrCount = %d, PolicyFiveMtrrCount = %d, PolicySixMtrrCount = %d.\n", PolicyFourMtrrCount, PolicyFiveMtrrCount, PolicySixMtrrCount));
//	PEI_TRACE((-1, PeiServices, "TsegBase = 0x%8lX, Above4GMemoryLength = 0x%8lX.\n", (UINT64)NBGetTsegBase(), Above4GMemoryLength));
	
	//Policy one
	if (PolicyOneMtrrCount <= VariableMtrrCount) {
		EFI_STATUS	Status = EFI_SUCCESS;
		UINT64  CurrentBaseAddress = 0;
		UINT8   MtrrCount = 0;
		UINT8	WbCount = 0;
		
		//1.Chose which Below4GMemoryLength is better
		if (WbMtrrCountBelow4G1 < WbMtrrCountBelow4G2)
			Below4GMemoryLength = (UINT64)NBGetTsegBase();
		else
			Below4GMemoryLength = (UINT64)NBGetTsegBase() + TSEG_SIZE;
		//2.Use wb type from 0 to Below4GMemoryLength
		RemainMemoryLength = Below4GMemoryLength;
		for (MemoryLength = SIZE_2G; RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
			if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				WbMap[WbCount].Base = CurrentBaseAddress;
				WbMap[WbCount].Len = MemoryLength;
				MtrrCount++;
				WbCount++;
				CurrentBaseAddress += MemoryLength;
				RemainMemoryLength -= MemoryLength;				
			}
		}
		
		//3.When memory above 4G is larger then 4G, set a wb type MTRR from 4G to 8G.
		//Next, if remain memory above 4G still larger than 8G, set a wb type MTRR from 8G to 16G. And so on.
		if (Status == EFI_SUCCESS) {
			RemainMemoryLength = Above4GMemoryLength;
			CurrentBaseAddress = SIZE_4G;
			for (MemoryLength = SIZE_4G; RemainMemoryLength >= MemoryLength; MemoryLength = Shl64(MemoryLength, 1)) {
//				PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				WbMap[WbCount].Base = CurrentBaseAddress;
				WbMap[WbCount].Len = MemoryLength;
				MtrrCount++;
				WbCount++;
				CurrentBaseAddress += MemoryLength;
				RemainMemoryLength -= MemoryLength;
			}
		}
		
		//4.Next, set RemainMemoryLength to wb type.
		if (Status == EFI_SUCCESS) {
			for (MemoryLength = GetPowerOfTwo64(RemainMemoryLength); RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
				if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
					if (MtrrCount >= VariableMtrrCount) {
						Status = EFI_OUT_OF_RESOURCES;
						break;
					}
					WbMap[WbCount].Base = CurrentBaseAddress;
					WbMap[WbCount].Len = MemoryLength;
					MtrrCount++;
					WbCount++;
					CurrentBaseAddress += MemoryLength;
					RemainMemoryLength -= MemoryLength;				
				}
			}
		}
		
		if (Status == EFI_SUCCESS) {
			PEI_TRACE((-1, PeiServices, "Set MTRR policy one success. MtrrCount = %d\n", MtrrCount));
			return EFI_SUCCESS;
		}
	}
	
	//Initialize, just in case
	if ((WbMap[0].Len != 0) || (UcMap[0].Len != 0)) {
		for(i = 0; i < 10; i++){
			WbMap[i].Len = 0;
			UcMap[i].Len = 0;
		}
	}
	
	//Policy Two
	if (PolicyTwoMtrrCount <= VariableMtrrCount) {
		EFI_STATUS	Status = EFI_SUCCESS;
		UINT64  CurrentBaseAddress = 0;
		UINT8   MtrrCount = 0;
		UINT8	WbCount = 0;
		UINT8	UcCount = 0;
		
		//1.Chose which Below4GMemoryLength is better
		if (WbMtrrCountBelow4G1 < WbMtrrCountBelow4G2)
			Below4GMemoryLength = (UINT64)NBGetTsegBase();
		else
			Below4GMemoryLength = (UINT64)NBGetTsegBase() + TSEG_SIZE;
		//2.Use wb type from 0 to Below4GMemoryLength
		RemainMemoryLength = Below4GMemoryLength;
		for (MemoryLength = SIZE_2G; RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
			if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				WbMap[WbCount].Base = CurrentBaseAddress;
				WbMap[WbCount].Len = MemoryLength;
				MtrrCount++;
				WbCount++;
				CurrentBaseAddress += MemoryLength;
				RemainMemoryLength -= MemoryLength;				
			}
		}
		
		//3.When memory above 4G is larger then 4G, set a wb type MTRR from 4G to 8G.
		//Next, if remain memory above 4G still larger than 8G, set a wb type MTRR from 8G to 16G. And so on.
		if (Status == EFI_SUCCESS) {
			RemainMemoryLength = Above4GMemoryLength;
			CurrentBaseAddress = SIZE_4G;
			for (MemoryLength = SIZE_4G; RemainMemoryLength >= MemoryLength; MemoryLength = Shl64(MemoryLength, 1)) {
//				PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				WbMap[WbCount].Base = CurrentBaseAddress;
				WbMap[WbCount].Len = MemoryLength;
				MtrrCount++;
				WbCount++;
				CurrentBaseAddress += MemoryLength;
				RemainMemoryLength -= MemoryLength;
			}
		}
		
		//4.Next, if remain memory larger than 2G, set wb type till remain memory smaller than 2G.
		if (Status == EFI_SUCCESS) {
			for (MemoryLength = GetPowerOfTwo64(RemainMemoryLength); RemainMemoryLength >= SIZE_2G; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
				if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
					if (MtrrCount >= VariableMtrrCount) {
						Status = EFI_OUT_OF_RESOURCES;
						break;
					}
					WbMap[WbCount].Base = CurrentBaseAddress;
					WbMap[WbCount].Len = MemoryLength;
					MtrrCount++;
					WbCount++;
					CurrentBaseAddress += MemoryLength;
					RemainMemoryLength -= MemoryLength;				
				}
			}
		}
		
		//5. Set a wb type from CurrentBaseAddress to shl(PowerOfTwo64(RemainMemoryLength), 1)
		WbMap[WbCount].Base = CurrentBaseAddress;
		WbMap[WbCount].Len = Shl64(GetPowerOfTwo64(RemainMemoryLength), 1);
		//Special case for saving MTRR. If wb setting can combine with previous wb setting.
		if (((WbMap[WbCount - 1].Base + WbMap[WbCount - 1].Len) == WbMap[WbCount].Base) &&
			(GetPowerOfTwo64(WbMap[WbCount - 1].Base) > WbMap[WbCount - 1].Len) &&
			(WbMap[WbCount - 1].Len == WbMap[WbCount].Len)) {
			WbMap[WbCount - 1].Len += WbMap[WbCount].Len;
			WbMap[WbCount].Base = 0;
			WbMap[WbCount].Len = 0;
//			PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", WbMap[WbCount - 1].Len, WbMap[WbCount - 1].Base, MtrrCount - 1));
		}
		else {
//			PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", WbMap[WbCount].Len, CurrentBaseAddress, MtrrCount));
			MtrrCount++;
			WbCount++;
		}
		
		CurrentBaseAddress += Shl64(GetPowerOfTwo64(RemainMemoryLength), 1);
		
		//6.Next, set uc type from Shl64(GetPowerOfTwo64(TotalMemoryLength), 1) to TotalMemoryLength, overwrite wb type.
		RemainMemoryLength = Shl64(GetPowerOfTwo64(RemainMemoryLength), 1) - RemainMemoryLength;
		CurrentBaseAddress -= GetPowerOfTwo64(RemainMemoryLength);
		for (MemoryLength = SIZE_2G; RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
			if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "UC Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				UcMap[UcCount].Base = CurrentBaseAddress;
				UcMap[UcCount].Len = MemoryLength;
				MtrrCount++;
				UcCount++;
				RemainMemoryLength -= MemoryLength;	
				CurrentBaseAddress -= GetPowerOfTwo64 (RemainMemoryLength);			
			}
		}
		
		if (Status == EFI_SUCCESS) {
			PEI_TRACE((-1, PeiServices, "Set MTRR policy two success. MtrrCount = %d\n", MtrrCount));
			return EFI_SUCCESS;
		}
	}
	
	//Initialize, just in case
	if ((WbMap[0].Len != 0) || (UcMap[0].Len != 0)) {
		for(i = 0; i < 10; i++){
			WbMap[i].Len = 0;
			UcMap[i].Len = 0;
		}
	}
	
	//Policy Three
	if (PolicyThreeMtrrCount <= VariableMtrrCount) {
		EFI_STATUS	Status = EFI_SUCCESS;
		UINT64  CurrentBaseAddress = 0;
		UINT8   MtrrCount = 0;
		UINT8	WbCount = 0;
		UINT8	UcCount = 0;
		
		//1.Chose which Below4GMemoryLength is better
		if (WbMtrrCountBelow4G1 < WbMtrrCountBelow4G2)
			Below4GMemoryLength = (UINT64)NBGetTsegBase();
		else
			Below4GMemoryLength = (UINT64)NBGetTsegBase() + TSEG_SIZE;
		//2.Use wb type from 0 to Below4GMemoryLength
		RemainMemoryLength = Below4GMemoryLength;
		for (MemoryLength = SIZE_2G; RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
			if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				WbMap[WbCount].Base = CurrentBaseAddress;
				WbMap[WbCount].Len = MemoryLength;
				MtrrCount++;
				WbCount++;
				CurrentBaseAddress += MemoryLength;
				RemainMemoryLength -= MemoryLength;				
			}
		}
		
		//3.When memory above 4G is larger then 4G, set a wb type MTRR from 4G to 8G.
		//Next, if remain memory above 4G still larger than 8G, set a wb type MTRR from 8G to 16G.
		if (Status == EFI_SUCCESS) {
			RemainMemoryLength = Above4GMemoryLength;
			CurrentBaseAddress = SIZE_4G;
			for (MemoryLength = SIZE_4G; RemainMemoryLength >= MemoryLength; MemoryLength = Shl64(MemoryLength, 1)) {
//				PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				WbMap[WbCount].Base = CurrentBaseAddress;
				WbMap[WbCount].Len = MemoryLength;
				MtrrCount++;
				WbCount++;
				CurrentBaseAddress += MemoryLength;
				RemainMemoryLength -= MemoryLength;
			}
		}
		
		//4.Next, set wb type from 4G to Shl64(GetPowerOfTwo64(RemainMemoryLength), 1).
		RemainMemoryLength = TotalMemoryLength - CurrentBaseAddress;
		if (Status == EFI_SUCCESS) {
			if (RemainMemoryLength > 0) {
				WbMap[WbCount].Base = CurrentBaseAddress;
				WbMap[WbCount].Len = Shl64(GetPowerOfTwo64(RemainMemoryLength), 1);
//				PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", Shl64(GetPowerOfTwo64(RemainMemoryLength), 1), CurrentBaseAddress, MtrrCount));
				MtrrCount++;
				WbCount++;
				CurrentBaseAddress += Shl64(GetPowerOfTwo64(RemainMemoryLength), 1);
				RemainMemoryLength = Shl64(GetPowerOfTwo64(RemainMemoryLength), 1) - RemainMemoryLength;				
			}
		}
		
		//5.Next, set uc type from Shl64(GetPowerOfTwo64(RemainMemoryLength), 1) to RemainMemoryLength
		CurrentBaseAddress -= GetPowerOfTwo64 (RemainMemoryLength);
		for (MemoryLength = GetPowerOfTwo64(RemainMemoryLength); RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
			if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "UC Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				UcMap[UcCount].Base = CurrentBaseAddress;
				UcMap[UcCount].Len = MemoryLength;
				MtrrCount++;
				UcCount++;
				RemainMemoryLength -= MemoryLength;
				CurrentBaseAddress -= GetPowerOfTwo64 (RemainMemoryLength);				
			}
		}
		
		if (Status == EFI_SUCCESS) {
			PEI_TRACE((-1, PeiServices, "Set MTRR policy three success. MtrrCount = %d\n", MtrrCount));
			return EFI_SUCCESS;
		}
	}
	
	//Initialize, just in case
	if ((WbMap[0].Len != 0) || (UcMap[0].Len != 0)) {
		for(i = 0; i < 10; i++){
			WbMap[i].Len = 0;
			UcMap[i].Len = 0;
		}
	}
	
	//Policy Four
	if (PolicyFourMtrrCount <= VariableMtrrCount) {
		EFI_STATUS	Status = EFI_SUCCESS;
		UINT64  CurrentBaseAddress = 0;
		UINT8   MtrrCount = 0;
		UINT8	WbCount = 0;
		UINT8	UcCount = 0;
		
		//1.Chose which Below4GMemoryLength is better
		if (UcMtrrCountBelow4G1 < UcMtrrCountBelow4G2)
			Below4GMemoryLength = (UINT64)NBGetTsegBase();
		else
			Below4GMemoryLength = (UINT64)NBGetTsegBase() + TSEG_SIZE;

		RemainMemoryLength = TotalMemoryLength;
		
		//2.Set GetPowerOfTwo64(RemainMemoryLength) to wb type.
		WbMap[WbCount].Base = CurrentBaseAddress;
		WbMap[WbCount].Len = GetPowerOfTwo64(RemainMemoryLength);
//		PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", GetPowerOfTwo64(RemainMemoryLength), CurrentBaseAddress, MtrrCount));				
		MtrrCount++;
		WbCount++;
		CurrentBaseAddress += GetPowerOfTwo64(RemainMemoryLength);
		RemainMemoryLength -= GetPowerOfTwo64(RemainMemoryLength);
		
		//3.Next, use wb type from CurrentBaseAddress to TotalMemoryLength.
		for (MemoryLength = GetPowerOfTwo64(RemainMemoryLength); RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
			if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				WbMap[WbCount].Base = CurrentBaseAddress;
				WbMap[WbCount].Len = MemoryLength;
				MtrrCount++;
				WbCount++;
				RemainMemoryLength -= MemoryLength;		
				CurrentBaseAddress += MemoryLength;		
			}
		}
		
		//4.Next, use uc type from Below4GMemoryLength to 4G
		if (Status == EFI_SUCCESS) {
			RemainMemoryLength = SIZE_4G - Below4GMemoryLength;
			CurrentBaseAddress = SIZE_4G - GetPowerOfTwo64 (RemainMemoryLength);
			for (MemoryLength = SIZE_2G; RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
				if (RemainMemoryLength >= MemoryLength) {
//					PEI_TRACE((-1, PeiServices, "UC Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
					if (MtrrCount >= VariableMtrrCount) {
						Status = EFI_OUT_OF_RESOURCES;
						break;
					}
					UcMap[UcCount].Base = CurrentBaseAddress;
					UcMap[UcCount].Len = MemoryLength;
					MtrrCount++;
					UcCount++;
					RemainMemoryLength -= MemoryLength;	
					CurrentBaseAddress -= GetPowerOfTwo64 (RemainMemoryLength);			
				}
			}
		}
		
		if (Status == EFI_SUCCESS) {
			PEI_TRACE((-1, PeiServices, "Set MTRR policy four success. MtrrCount = %d\n", MtrrCount));
			return EFI_SUCCESS;
		}
	}
	
		//Initialize, just in case
	if ((WbMap[0].Len != 0) || (UcMap[0].Len != 0)) {
		for(i = 0; i < 10; i++){
			WbMap[i].Len = 0;
			UcMap[i].Len = 0;
		}
	}
	
	//Policy Five
	if (PolicyFiveMtrrCount <= VariableMtrrCount) {
		EFI_STATUS	Status = EFI_SUCCESS;
		UINT64  CurrentBaseAddress = 0;
		UINT8   MtrrCount = 0;
		UINT8	WbCount = 0;
		UINT8	UcCount = 0;
		
		//1.Chose which Below4GMemoryLength is better
		if (UcMtrrCountBelow4G1 < UcMtrrCountBelow4G2)
			Below4GMemoryLength = (UINT64)NBGetTsegBase();
		else
			Below4GMemoryLength = (UINT64)NBGetTsegBase() + TSEG_SIZE;

		RemainMemoryLength = TotalMemoryLength;
		
		//2.Set GetPowerOfTwo64(RemainMemoryLength) to wb type.
		WbMap[WbCount].Base = CurrentBaseAddress;
		WbMap[WbCount].Len = GetPowerOfTwo64(RemainMemoryLength);
//		PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", GetPowerOfTwo64(RemainMemoryLength), CurrentBaseAddress, MtrrCount));				
		MtrrCount++;
		WbCount++;
		CurrentBaseAddress += GetPowerOfTwo64(RemainMemoryLength);
		RemainMemoryLength -= GetPowerOfTwo64(RemainMemoryLength);
		
		//3.Next, use wb type from CurrentBaseAddress till remain memory is smaller 2G.
		for (MemoryLength = GetPowerOfTwo64(RemainMemoryLength); RemainMemoryLength >= SIZE_2G; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
			if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				WbMap[WbCount].Base = CurrentBaseAddress;
				WbMap[WbCount].Len = MemoryLength;
				MtrrCount++;
				WbCount++;
				RemainMemoryLength -= MemoryLength;		
				CurrentBaseAddress += MemoryLength;		
			}
		}
		
		//4. Set a wb type from CurrentBaseAddress to shl(PowerOfTwo64(RemainMemoryLength), 1)
		WbMap[WbCount].Base = CurrentBaseAddress;
		WbMap[WbCount].Len = Shl64(GetPowerOfTwo64(RemainMemoryLength), 1);
		//Special case for saving MTRR. If wb setting can combine with previous wb setting.
		if (((WbMap[WbCount - 1].Base + WbMap[WbCount - 1].Len) == WbMap[WbCount].Base) &&
			(GetPowerOfTwo64(WbMap[WbCount - 1].Base) > WbMap[WbCount - 1].Len) &&
			(WbMap[WbCount - 1].Len == WbMap[WbCount].Len)) {
			WbMap[WbCount - 1].Len += WbMap[WbCount].Len;
			WbMap[WbCount].Base = 0;
			WbMap[WbCount].Len = 0;
//			PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", WbMap[WbCount - 1].Len, WbMap[WbCount - 1].Base, MtrrCount - 1));
		}
		else {
//			PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", WbMap[WbCount].Len, CurrentBaseAddress, MtrrCount));
			MtrrCount++;
			WbCount++;
		}
		CurrentBaseAddress += Shl64(GetPowerOfTwo64(RemainMemoryLength), 1);
		
		//5.Next, set uc type from Shl64(GetPowerOfTwo64(TotalMemoryLength), 1) to TotalMemoryLength, overwrite wb type.
		RemainMemoryLength = Shl64(GetPowerOfTwo64(RemainMemoryLength), 1) - RemainMemoryLength;
		CurrentBaseAddress -= GetPowerOfTwo64(RemainMemoryLength);
		for (MemoryLength = SIZE_2G; RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
			if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "UC Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				UcMap[UcCount].Base = CurrentBaseAddress;
				UcMap[UcCount].Len = MemoryLength;
				MtrrCount++;
				UcCount++;
				RemainMemoryLength -= MemoryLength;	
				CurrentBaseAddress -= GetPowerOfTwo64 (RemainMemoryLength);			
			}
		}
		
		//6.Next, use uc type from Below4GMemoryLength to 4G
		if (Status == EFI_SUCCESS) {
			RemainMemoryLength = SIZE_4G - Below4GMemoryLength;
			CurrentBaseAddress = SIZE_4G - GetPowerOfTwo64 (RemainMemoryLength);
			for (MemoryLength = SIZE_2G; RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
				if (RemainMemoryLength >= MemoryLength) {
//					PEI_TRACE((-1, PeiServices, "UC Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
					if (MtrrCount >= VariableMtrrCount) {
						Status = EFI_OUT_OF_RESOURCES;
						break;
					}
					UcMap[UcCount].Base = CurrentBaseAddress;
					UcMap[UcCount].Len = MemoryLength;
					MtrrCount++;
					UcCount++;
					RemainMemoryLength -= MemoryLength;	
					CurrentBaseAddress -= GetPowerOfTwo64 (RemainMemoryLength);			
				}
			}
		}
		
		if (Status == EFI_SUCCESS) {
			PEI_TRACE((-1, PeiServices, "Set MTRR policy five success. MtrrCount = %d\n", MtrrCount));
			return EFI_SUCCESS;
		}
	}
	
	//Initialize, just in case
	if ((WbMap[0].Len != 0) || (UcMap[0].Len != 0)) {
		for(i = 0; i < 10; i++){
			WbMap[i].Len = 0;
			UcMap[i].Len = 0;
		}
	}
	
	//Policy Six
	if (PolicySixMtrrCount <= VariableMtrrCount) {
		EFI_STATUS	Status = EFI_SUCCESS;
		UINT64  CurrentBaseAddress = 0;
		UINT8   MtrrCount = 0;
		UINT8	WbCount = 0;
		UINT8	UcCount = 0;

		//1.Chose which Below4GMemoryLength is better for below 4G memory MTRR setting.
		if (UcMtrrCountBelow4G1 < UcMtrrCountBelow4G2)
			Below4GMemoryLength = (UINT64)NBGetTsegBase();
		else
			Below4GMemoryLength = (UINT64)NBGetTsegBase() + TSEG_SIZE;

		//2.Set wb type from 0 to Shl64(GetPowerOfTwo64(TotalMemoryLength), 1).
		WbMap[WbCount].Base = CurrentBaseAddress;
		WbMap[WbCount].Len = Shl64(GetPowerOfTwo64(TotalMemoryLength), 1);
//		PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx. MtrrCount = %x\n", Shl64(GetPowerOfTwo64(TotalMemoryLength), 1), CurrentBaseAddress, MtrrCount));		
		MtrrCount++;
		WbCount++;
		CurrentBaseAddress += Shl64(GetPowerOfTwo64(TotalMemoryLength), 1);
	
		//3.Next, set uc type from Shl64(GetPowerOfTwo64(TotalMemoryLength), 1) to TotalMemoryLength.
		RemainMemoryLength = Shl64(GetPowerOfTwo64(TotalMemoryLength), 1) - TotalMemoryLength;
		CurrentBaseAddress -= GetPowerOfTwo64(RemainMemoryLength);
		for (MemoryLength = GetPowerOfTwo64(RemainMemoryLength); RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
			if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "UC Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
				if (MtrrCount >= VariableMtrrCount) {
					Status = EFI_OUT_OF_RESOURCES;
					break;
				}
				UcMap[UcCount].Base = CurrentBaseAddress;
				UcMap[UcCount].Len = MemoryLength;
				MtrrCount++;
				UcCount++;
				RemainMemoryLength -= MemoryLength;	
				CurrentBaseAddress -= GetPowerOfTwo64 (RemainMemoryLength);			
			}
		}
		
		//4.Next, use uc type from Below4GMemoryLength to 4G
		if (Status == EFI_SUCCESS) {
			RemainMemoryLength = SIZE_4G - Below4GMemoryLength;
			CurrentBaseAddress = SIZE_4G - GetPowerOfTwo64 (RemainMemoryLength);
			for (MemoryLength = SIZE_2G; RemainMemoryLength > 0; MemoryLength = GetPowerOfTwo64(RemainMemoryLength)) {
				if (RemainMemoryLength >= MemoryLength) {
//				PEI_TRACE((-1, PeiServices, "UC Memory Length = %08lx at %09lx. MtrrCount = %x\n", MemoryLength, CurrentBaseAddress, MtrrCount));
					if (MtrrCount >= VariableMtrrCount) {
						Status = EFI_OUT_OF_RESOURCES;
						break;
					}
					UcMap[UcCount].Base = CurrentBaseAddress;
					UcMap[UcCount].Len = MemoryLength;
					MtrrCount++;
					UcCount++;
					RemainMemoryLength -= MemoryLength;
					CurrentBaseAddress -= GetPowerOfTwo64 (RemainMemoryLength);				
				}
			}
		}
		
		if (Status == EFI_SUCCESS) {
			PEI_TRACE((-1, PeiServices, "Set MTRR policy six success. MtrrCount = %d\n", MtrrCount));
			return EFI_SUCCESS;
		}
	}
	PEI_TRACE((-1, PeiServices, "Set MTRR status = EFI_OUT_OF_RESOURCES\n"));
	return EFI_OUT_OF_RESOURCES;
}
#endif

#if PERF_TUNE_SUPPORT == 1
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure: CpuPeiIntelXtuDataInit
//
// Description: 
//      Interl XTU utility data initialize in PEI phase
//      
// Input:
//      IN EFI_PEI_SERVICES                 **PeiServices
//      IN EFI_PEI_READ_ONLY_VARIABLE_PPI   *ReadOnlyVariablePpi
//      IN EFI_BOOT_MODE                    BootMode
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CpuPeiIntelXtuDataInit (
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN EFI_PEI_READ_ONLY_VARIABLE_PPI   *ReadOnlyVariablePpi,
    IN EFI_BOOT_MODE                    BootMode
)
{
    EFI_STATUS			Status;
	BIOS_SETTING_DATA	SettingData;
	EFI_GUID			PerfTunePpiGuid = PERF_TUNE_PPI_GUID;
	EFI_GUID			WdtPpiGuid = PERF_TUNE_WDT_PPI_GUID;
	PERF_TUNE_PPI		*PerfTunePpi;
	PERF_TUNE_WDT_PPI	*WdtPpi;
	DDDT_PRESENT_FLAG_HOB  *DddtPreFlagHob;
    VOID        *FirstHob;
    UINT32      CpuSignature = GetCpuSignature();
	UINT32      CpuSigNoVer = CpuSignature & 0xfffffff0;
    UINT8       i;
    UINT8       CpuCores = NumCpuCores();
	UINT8       NumOcBins = 0;
	UINT8       CpuImptype[] = {BIOS_1_CORE_RATIO_IMPLEMENTATION,\
                                BIOS_2_CORE_RATIO_IMPLEMENTATION,\
                                BIOS_3_CORE_RATIO_IMPLEMENTATION,\
                                BIOS_4_CORE_RATIO_IMPLEMENTATION,\
                                BIOS_5_CORE_RATIO_IMPLEMENTATION,\
                                BIOS_6_CORE_RATIO_IMPLEMENTATION  };
    
    OVERCLOCKING_CONFIG_HOB     *OverclockConfigHob;    
	OVERCLOCKING_CONFIG_DATA	*OverclockData;         
    
    if (CpuSigNoVer != IVY_BRIDGE)        
        NumOcBins = (UINT8)((UINT32)(ReadMsr(MSR_FLEX_RATIO)) >> 17) & 0x7;                
    
    Status = (*PeiServices)->GetHobList(PeiServices, &FirstHob);
    ASSERT_PEI_ERROR(PeiServices, Status);
    
    DddtPreFlagHob = (DDDT_PRESENT_FLAG_HOB*) FirstHob;
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &DddtPreFlagHob))) {
        if (guidcmp(&((EFI_HOB_GUID_TYPE*)DddtPreFlagHob)->Name, &gAmiDddtPreFlagHobGuid) == 0) {
            break;
        }
    }
	
    if(!EFI_ERROR(Status)){
        //iGfx Core Current Max Dddt Flag set to 1 or 0
        //if((DddtPreFlagHob->PresentFlag[BIOS_GRAPHICS_TURBO_RATIO_LIMIT_IMPLEMENTATION] == 0)||\
        // (DddtPreFlagHob->PresentFlag[BIOS_GRAPHICS_CORE_VOLTAGE_IMPLEMENTATION] == 0))
        //    DddtPreFlagHob->PresentFlag[BIOS_IGFX_CORE_CURRENT_MAX_IMPLEMENTATION] = 0;
        //else
        //    DddtPreFlagHob->PresentFlag[BIOS_IGFX_CORE_CURRENT_MAX_IMPLEMENTATION] = 1;
        DddtPreFlagHob->PresentFlag[BIOS_IGFX_CORE_CURRENT_MAX_IMPLEMENTATION] = 0;		//disable IGFX current MAX
		
        //if Cpu is partial unlock or full unlock then turbo Core ratio dddt should not build.  
        PEI_TRACE((-1, PeiServices, "CPU PEI XTU data init CpuCores = %x\n", CpuCores));
        for (i = 0; i < sizeof(CpuImptype); i++){
            if(CpuCores < (i + 1)){
                DddtPreFlagHob->PresentFlag[CpuImptype[i]] = 0;
            }
        }

        //Force Runtime Turbo disable
        if (NumOcBins)
            DddtPreFlagHob->PresentFlag[BIOS_RUNTIME_TURBO_ENABLE_IMPLEMENTATION] = 1;
        else	
            DddtPreFlagHob->PresentFlag[BIOS_RUNTIME_TURBO_ENABLE_IMPLEMENTATION] = 0;

        //Overclocking Core Ratio Limit disable
		if (!isXECoreRatioLimitSupported()){
            DddtPreFlagHob->PresentFlag[BIOS_1_CORE_RATIO_IMPLEMENTATION] = 0;//One-core Flag
            DddtPreFlagHob->PresentFlag[BIOS_2_CORE_RATIO_IMPLEMENTATION] = 0;//Two-core Flag
            DddtPreFlagHob->PresentFlag[BIOS_3_CORE_RATIO_IMPLEMENTATION] = 0;//Three-core Flag
            DddtPreFlagHob->PresentFlag[BIOS_4_CORE_RATIO_IMPLEMENTATION] = 0;//Four-core Flag
            DddtPreFlagHob->PresentFlag[BIOS_5_CORE_RATIO_IMPLEMENTATION] = 0;//Five-core Flag
            DddtPreFlagHob->PresentFlag[BIOS_6_CORE_RATIO_IMPLEMENTATION] = 0;//Six-core Flag
        }

        //Package Power Limit disable
        // Skus that support Config TDP are not able to change power limit(MSR 0x610) in real time.
		if (!isXETdcTdpLimitSupported() || (Shr64(ReadMsr(MSR_PLATFORM_INFO), 32) & (BIT1 | BIT2)) ){
            DddtPreFlagHob->PresentFlag[BIOS_SHORT_TDP_IMPLEMENTATION] = 0;             //Short TDP Flag
            DddtPreFlagHob->PresentFlag[BIOS_EXTENDED_TDP_IMPLEMENTATION] = 0;          //Extended TDP Flag
            DddtPreFlagHob->PresentFlag[BIOS_SHORT_TDP_ENABLE_IMPLEMENTATION] = 0;      //Short TDP Enable Flag
            DddtPreFlagHob->PresentFlag[BIOS_EXTENDED_TDP_ENABLE_IMPLEMENTATION] = 0;   //Package TDP Enable Flag
            DddtPreFlagHob->PresentFlag[BIOS_EXTENDED_TIME_WINDOW_IMPLEMENTATION] = 0;  //Package TDP Time Window Flag
        }
        DddtPreFlagHob->PresentFlag[BIOS_RUNTIME_TURBO_OVERRIDE_IMPLEMENTATION] = 0;
        DddtPreFlagHob->PresentFlag[BIOS_MAX_TURBO_MODE_CPU_VOLTAGE_IMPLEMENTATION] = 0;

        //if cpu not support turbo mode, disable TDP, TDC, extend tdp, short tdp and all core ratio DDD table creation.
        if(!isTurboModeSupported()){
            DddtPreFlagHob->PresentFlag[BIOS_TURBO_ENABLE_IMPLEMENTATION] = 0;                  //Turbo Eanble Flag
            DddtPreFlagHob->PresentFlag[BIOS_TDC_VALUE_IMPLEMENTATION] = 0;	                    //TDC Flag
            DddtPreFlagHob->PresentFlag[BIOS_TDP_VALUE_IMPLEMENTATION] = 0;                     //TDP Flag
            DddtPreFlagHob->PresentFlag[BIOS_1_CORE_RATIO_IMPLEMENTATION] = 0;                  //One-core Flag
            DddtPreFlagHob->PresentFlag[BIOS_2_CORE_RATIO_IMPLEMENTATION] = 0;                  //Two-core Flag
            DddtPreFlagHob->PresentFlag[BIOS_3_CORE_RATIO_IMPLEMENTATION] = 0;                  //Three-core Flag
            DddtPreFlagHob->PresentFlag[BIOS_4_CORE_RATIO_IMPLEMENTATION] = 0;                  //Four-core Flag
            DddtPreFlagHob->PresentFlag[BIOS_5_CORE_RATIO_IMPLEMENTATION] = 0;                  //Five-core Flag
            DddtPreFlagHob->PresentFlag[BIOS_6_CORE_RATIO_IMPLEMENTATION] = 0;                  //Six-core Flag
            DddtPreFlagHob->PresentFlag[BIOS_SHORT_TDP_IMPLEMENTATION] = 0;                     //Short TDP Flag
            DddtPreFlagHob->PresentFlag[BIOS_EXTENDED_TDP_IMPLEMENTATION] = 0;                  //Extended TDP Flag
            DddtPreFlagHob->PresentFlag[BIOS_SHORT_TDP_ENABLE_IMPLEMENTATION] = 0;              //Short TDP Enable Flag
            DddtPreFlagHob->PresentFlag[BIOS_RUNTIME_TURBO_OVERRIDE_IMPLEMENTATION] = 0;        //Runtime Turbo Overwride Flag
            DddtPreFlagHob->PresentFlag[BIOS_CPU_PLL_VOLTAGE_UNLOCK_ENABLE_IMPLEMENTATION] = 0; //Internal PLL overvoltage Enable Flag
            DddtPreFlagHob->PresentFlag[BIOS_EXTENDED_TDP_ENABLE_IMPLEMENTATION] = 0;           //Package TDP Enable Flag
            DddtPreFlagHob->PresentFlag[BIOS_EXTENDED_TIME_WINDOW_IMPLEMENTATION] = 0;          //Package TDP Time Window Flag
			/*
            DddtPreFlagHob->PresentFlag[BIOS_OVERCLOCKING_ENABLE_IMPLEMENTATION] = 0;           //Overclocking Lock Flag
            DddtPreFlagHob->PresentFlag[BIOS_CPU_VOLTAGE_IMPLEMENTATION] = 0;                       //Malibox: CPU Voltage Target Flag
            DddtPreFlagHob->PresentFlag[BIOS_IA_CORE_VOLTAGE_MODE_IMPLEMENTATION] = 0;              //Malibox: CPU Voltage Mode Flag
            DddtPreFlagHob->PresentFlag[BIOS_CPU_VOLTAGE_OFFSET_IMPLEMENTATION] = 0;                //Malibox: CPU Voltage Offset Flag
            DddtPreFlagHob->PresentFlag[BIOS_RING_RATIO_IMPLEMENTATION] = 0;                        //Malibox: RING Ratio Flag
            DddtPreFlagHob->PresentFlag[BIOS_RING_VOLTAGE_OVERRIDE_IMPLEMENTATION] = 0;             //Malibox: RING Voltage Target Flag
            DddtPreFlagHob->PresentFlag[BIOS_RING_VOLTAGE_MODE_IMPLEMENTATION] = 0;                 //Malibox: RING Voltage Mode Flag
            DddtPreFlagHob->PresentFlag[BIOS_RING_VOLTAGE_OFFSET_IMPLEMENTATION] = 0;               //Malibox: RING Voltage Offset Flag
            DddtPreFlagHob->PresentFlag[BIOS_DYNAMIC_SVID_CONTROL_IMPLEMENTATION] = 0;              //Malibox: SVID Control Flag
            DddtPreFlagHob->PresentFlag[BIOS_SVID_VOLTAGE_OVERRIDE_IMPLEMENTATION] = 0;             //Malibox: SVID Voltage Target Flag
            DddtPreFlagHob->PresentFlag[BIOS_FIVR_FAULTS_IMPLEMENTATION] = 0;                       //Malibox: FIVR Faults Flag
            DddtPreFlagHob->PresentFlag[BIOS_FIVR_EFFICIENCY_MANAGEMENT_IMPLEMENTATION] = 0;        //Malibox: FIVR Efficiency Management Flag
			*/
        }

        if(!(isFullUnlockCpuSuuported())){
            DddtPreFlagHob->PresentFlag[BIOS_CPU_PLL_VOLTAGE_UNLOCK_ENABLE_IMPLEMENTATION] = 0; //Internal PLL overvoltage Enable Flag
        }
        
        if(!(isBCLKRatioSuuported())){
            DddtPreFlagHob->PresentFlag[BIOS_PEG_DMI_RATIO_IMPLEMENTATION] = 0; 				// PEG/DMI ratio Enable Flag
        }

        DddtPreFlagHob->PresentFlag[BIOS_TDC_VALUE_IMPLEMENTATION] = 0;	    //TDC Flag
	    DddtPreFlagHob->PresentFlag[BIOS_TDP_VALUE_IMPLEMENTATION] = 0;     //TDP Flag		
		
        OverclockConfigHob = (OVERCLOCKING_CONFIG_HOB*) FirstHob;
        while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &OverclockConfigHob))) {
            if (guidcmp(&((EFI_HOB_GUID_TYPE*)OverclockConfigHob)->Name, &gAmiOcConfigHobGuid) == 0) {
                break;
            }
        }
        if(!EFI_ERROR(Status)){
            OverclockData = &OverclockConfigHob->OverclockData;
            //Mailbox item
            //IA core
            if(!OverclockData->OCCap[IA].VoltageOverridesSupported){
                DddtPreFlagHob->PresentFlag[BIOS_IA_CORE_VOLTAGE_MODE_IMPLEMENTATION] = 0;
                DddtPreFlagHob->PresentFlag[BIOS_CPU_VOLTAGE_IMPLEMENTATION] = 0;
            }
            if(!OverclockData->OCCap[IA].VoltageOffsetSupported)
                DddtPreFlagHob->PresentFlag[BIOS_CPU_VOLTAGE_OFFSET_IMPLEMENTATION] = 0;
            //RING
            if(!OverclockData->OCCap[RING].RatioOcSupported)
                DddtPreFlagHob->PresentFlag[BIOS_RING_RATIO_IMPLEMENTATION] = 0;
            if(!OverclockData->OCCap[RING].VoltageOverridesSupported){
                DddtPreFlagHob->PresentFlag[BIOS_RING_VOLTAGE_MODE_IMPLEMENTATION] = 0;
                DddtPreFlagHob->PresentFlag[BIOS_RING_VOLTAGE_OVERRIDE_IMPLEMENTATION] = 0;
            }
            if(!OverclockData->OCCap[RING].VoltageOffsetSupported)
                DddtPreFlagHob->PresentFlag[BIOS_RING_VOLTAGE_OFFSET_IMPLEMENTATION] = 0;
        }
	}

		
	Status = (*PeiServices)->LocatePpi(
					PeiServices,
					&PerfTunePpiGuid,
					0,
					NULL,
					&PerfTunePpi
					);
	if(EFI_ERROR(Status)) return Status;
	
	Status = (*PeiServices)->LocatePpi(
				PeiServices,
				&WdtPpiGuid,
				0,
				NULL,
				&WdtPpi
				);
	if(EFI_ERROR(Status)) return Status;
	
	Status = PerfTunePpi->GetSettingData(PeiServices, &SettingData);
	if(EFI_ERROR(Status)) return Status; 

    if(SettingData.RuntimeTurboEanble == 1 && NumOcBins != 0)
        DddtPreFlagHob->PresentFlag[BIOS_RUNTIME_TURBO_OVERRIDE_IMPLEMENTATION] = 1;
    else
        DddtPreFlagHob->PresentFlag[BIOS_RUNTIME_TURBO_OVERRIDE_IMPLEMENTATION] = 0;

    return Status;

}
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure: CpuPeiMiscFuncs
//
// Description: 
//
// Input:
//      IN EFI_PEI_SERVICES                 **PeiServices
//      IN EFI_PEI_READ_ONLY_VARIABLE_PPI   *ReadOnlyVariablePpi
//      IN EFI_BOOT_MODE                    BootMode
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CpuPeiMiscFuncs (
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN EFI_PEI_READ_ONLY_VARIABLE_PPI   *ReadOnlyVariablePpi,
    IN EFI_BOOT_MODE                    BootMode
)
{

#if PERF_TUNE_SUPPORT == 1
    EFI_STATUS  Status;
    
    Status = CpuPeiIntelXtuDataInit(PeiServices, ReadOnlyVariablePpi, BootMode);
#endif    
    
    return;
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

