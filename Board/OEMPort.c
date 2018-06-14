//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Board/OEMPort.c 26    8/08/11 11:10a Artems $
//
// $Revision: 26 $
//
// $Date: 8/08/11 11:10a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Board/OEMPort.c $
// 
// 26    8/08/11 11:10a Artems
// EIP 64107: Changes to support UEFI 2.3.1 and PI 1.2 specifications
// 
// 25    2/08/11 3:31p Artems
// Reduced function header comment to fit in CHM file
// 
// 24    2/07/11 4:43p Artems
// EIP 53374: Replaced TABs with spaces
// 
// 23    12/17/10 12:55p Davidd
// [TAG]        EIP47366
// [Category]   Improvement
// [Description]    Preserve Bios Password when CMOS is bad.
// [Files]          OemDxe.c
// OemPort.c
// 
// 22    9/28/10 10:19a Oleksiyy
// Issue Number:  42804 
// 
// Category:  Improvement
// 
// Description:  Build warning fix. Definition of gPeiStallPpiGuid made
// static to
// fix build process warning about it's second definition.
// 
// Files:  OEMPort.c
// 
// 21    6/25/09 6:09p Robert
// Updated Comments and function headers
// 
// 20    5/22/09 7:02p Felixp
// Clean up of the IsCtrlHomePressed function
// 
// 18    5/22/09 6:08p Felixp
// Core 4.6.3.6 support
// 1. EIP 19921
//    New hooks IsNvramDataCompatible and DxeIsNvramDataCompatible used by
// NVRAM driver are added.
//    NVRAM driver uses the hooks to checks compatibility of the current
// NVRAM data 
//    (mainly Setup-related variables) with the firmware code.
// 2. IsRecovery function updated to return TRUE is the system is already
// in Recovery mode.
//    (this may happen if ROM corruption is detected in ReportFv.c)
// 
// 17    3/05/09 1:52p Felixp
// Bug fix in IsMfgMode
// Coments updated
// 
// 16    3/05/09 1:30p Felixp
// Improvement EIP 18496:
//   eLinks are exposed for the following porting functions defined in
// OemPort:
//     IsRecovery, NoConfigChanges, IsMfgMode, IsResetConfigMode,
// IsDefaultConfigMode
// 
// 15    1/30/09 1:33p Felixp
// Updated to comply with Core 4.6.3.5.
// Improvement. EIP 18483. 
// Interface of the hooks that detect NVRAM operational mode is extended.
// NVRAM driver uses platform hooks(IsMfgMode, IsResetConfigMode,
// IsDefaultConfigMode) 
// defined in this file to detect, which set of configuration values are
// to be used. 
// In some cases the mode is detected based on value of the NVRAM
// variable.
// Interface of the hook functions is extended. New parameter is added. 
// Pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI PPI is passed to the hook
// functions. 
// The pointer can be used to read and enumerate existing NVRAM variables.
// 
// 14    9/06/07 1:24a Felixp
//  - New porting hooks used by Core 4.6.2 NVRAM code added
//  - Clean up
// 
// 13    1/11/07 1:07p Anandakrishnanl
//  Keyboard decode enabling for Recovery support in 64 bit 
// 
// 12    10/16/06 11:52a Fredericko
// Fix logic error with checking for keypress status
// 
// 11    6/13/06 5:00p Sivagarn
// - Updated file header
// - Updated format
// 
// 10    5/09/06 4:57a Sangeethav
// - Cntrl+Home support included.
// 
// 7     11/07/05 6:56p Felixp
// Jumber Recovery support added
// 
// 6     11/07/05 6:14p Markw
// Added recovery checking.
// 
// 5     7/18/05 6:24p Davidd
// Removed the CPU, System Slot, and On-Board Device porting hooks for
// SMBIOS. (They were moved to new porting file SmbiosBoard.c).
// 
// 3     7/13/05 5:33p Davidd
// Added sample code to create dynamic CPU data for SMBIOS.
// 
// 2     7/05/05 11:52a Davidd
// Added porting functions for SMBIOS.
// 
//*****************************************************************************

//<AMI_FHDR_START>
//============================================================================
// Name:        OEMPort.C
//
// Description: This file contains code for OEM related code
//============================================================================
//<AMI_FHDR_END>



//============================================================================
// Includes

#include <Token.h>
#include <EFI.h>
#include <PEI.h>
#include <AmiPeiLib.h>
#include <AmiDxeLib.h>
#include <Protocol/PciIO.h>
#include <Protocol/PciRootBridgeIo.h>
#include <PPI/PciCfg2.h>
#include <PPI/CpuIo.h>
#include <PPI/Stall.h>
#include <PPI/ReadOnlyVariable2.h>
#include <Setup.h>

#if CLEAR_NVRAM_IF_CMOS_BAD
#define AMITSESETUP_GUID \
 { 0xc811fa38, 0x42c8, 0x4579, 0xa9, 0xbb, 0x60, 0xe9, 0x4e, 0xdd, 0xfb, 0x34 }

#define PASSWORD_HOB_GUID \
 { 0x79ce097a, 0x91aa, 0x41ff, 0xb3, 0xa8, 0x53, 0x45, 0x59, 0xb3, 0x0d, 0xb1 }

typedef struct
{
    EFI_HOB_GUID_TYPE   EfiHobGuidType;
    AMITSESETUP         AmiTseData;
} 
PASSWORD_HOB;
#endif      // CLEAR_NVRAM_IF_CMOS_BAD

//============================================================================
// GUID Definitions
static EFI_GUID gPeiStallPpiGuid = EFI_PEI_STALL_PPI_GUID;

//============================================================================
// MACROs
#define PCI_CFG_ADDRESS(bus,dev,func,reg) \
 ((UINT64) ( (((UINTN)bus) << 24) + (((UINTN)dev) << 16) + (((UINTN)func) << 8) + ((UINTN)reg) ))& 0x00000000ffffffff

//============================================================================
// Type definitions
typedef BOOLEAN (ONE_PARAM_FUNCTION)(
    IN EFI_PEI_SERVICES **PeiServices
);
typedef BOOLEAN (TWO_PARAM_FUNCTION)(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
);

//============================================================================
// externs
extern ONE_PARAM_FUNCTION* IsRecoveryList[];
extern ONE_PARAM_FUNCTION* NoConfigChangesList[];
extern TWO_PARAM_FUNCTION* IsMfgModeList[];
extern TWO_PARAM_FUNCTION* IsResetConfigModeList[];
extern TWO_PARAM_FUNCTION* IsDefaultConfigModeList[];

//============================================================================
// Function Definitions

//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure: CallOneParamHooks
//
// Description: 
//  This function calls a list of function defined at build time and 
//  return whether the functions completed successfully or not
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to the PeiServices Table
//
// Output:
//  BOOLEAN 
//  - - TRUE - all functions returned correctly
//  - - FALSE - one of the functions failed during execution
//
// Notes: 
//  Similar to CallTwoParamHooks except that these function only require
//  the PeiServices pointer as a parameter
//          
//**********************************************************************
//<AMI_PHDR_END>
BOOLEAN CallOneParamHooks(
    IN ONE_PARAM_FUNCTION* FunctionList[], IN EFI_PEI_SERVICES **PeiServices
){
    UINTN i;
    BOOLEAN Result = FALSE;
    for(i=0; FunctionList[i] && !Result; i++) 
        Result = FunctionList[i](PeiServices);
    return Result;
}

//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure: CallTwoParamHooks
//
// Description: 
//  This function calls a list of function defined at build time and 
//  return whether the functions completed successfully or not
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to the PeiServices Table
//  IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi - pointer to 
//      the Read Only Variable 2 PPI
//
// Output:
//  BOOLEAN 
//  - - TRUE - all functions returned correctly
//  - - FALSE - one of the functions failed during execution
//
// Notes:
//  Similar to CallOneParamHooks except that these function also require
//  a pointer to the Read Only Variable 2 PPI
//          
//**********************************************************************
//<AMI_PHDR_END>
BOOLEAN CallTwoParamHooks(
    IN TWO_PARAM_FUNCTION* FunctionList[],
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){
    UINTN i;
    BOOLEAN Result = FALSE;
    for(i=0; FunctionList[i] && !Result; i++) 
        Result = FunctionList[i](PeiServices,ReadVariablePpi);
    return Result;
}

#if KBC_SUPPORT
//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure: IsCtrlHomePressed
//
// Description: 
//  This function detects if the Ctrl + Home key press has been made.
//  Is function is only included if KBC_SUPPORT is enabled.  It enables
//  the keyboard checks for the Ctrl + Home key press and then disables
//  the keyboard
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to the PeiServices Table
//
// Output:
//  BOOLEAN 
//  - - TRUE - Ctrl + Home was pressed
//  - - FALSE - Ctrl + Home not detected
//
// Notes:
//  
//**********************************************************************
//<AMI_PHDR_END>
BOOLEAN IsCtrlHomePressed( EFI_PEI_SERVICES **PeiServices){
    UINT8               Index;
    UINT8               KeyValue = 0;
    UINT8               KeyScan = 0;
    UINT8               LoopCount = Recovery_Time_Delay;  // 20 Loop counts * 2ms;
    EFI_STATUS          Status;
    EFI_PEI_STALL_PPI   *StallPpi;
    UINT8               KbcSts = 0;
    UINT8               KbcSts1 = 0;
    UINT8               KbcSts2 = 0;
    BOOLEAN             KbcOBF = TRUE;
    BOOLEAN             KbcIBF = TRUE;
    BOOLEAN             KbcIBF1 = TRUE;
    UINT8               KbcRes = 0;
    EFI_PEI_PCI_CFG2_PPI   *PciCfg = (*PeiServices)->PciCfg;
    EFI_PEI_CPU_IO_PPI    *CpuIo = (*PeiServices)->CpuIo;

    Status = (**PeiServices).LocatePpi (PeiServices, &gPeiStallPpiGuid, 0,
                        NULL, (VOID **)&StallPpi);
    if (EFI_ERROR(Status)) return FALSE;

    //Enable KBD
    KbcSts = CpuIo->IoRead8 ( PeiServices, CpuIo, 0x64 );
    // Check KeyBoard Presence 
    if(KbcSts != 0xFF) {
        //Save the Sys Bit for later use  
        KbcRes = KbcSts & 0x04;
        CpuIo->IoWrite8 ( PeiServices, CpuIo, 0x64, 0x60 );  
                    
        // Wait for Input Buffer Empty  
        while(KbcIBF){
            KbcIBF = FALSE;
            KbcSts1 = CpuIo->IoRead8 ( PeiServices, CpuIo, 0x64 );
            if((KbcSts1 & 0x02) == 02) {
                KbcIBF = TRUE;
            }
        }
        // Keyboard enable, Mouse disable
        CpuIo->IoWrite8 ( PeiServices, CpuIo, 0x60, KbcRes | 0x61 );          
      
        // Wait for Input Buffer Empty 
        while(KbcIBF1){
            KbcIBF1 = FALSE;
            KbcSts2 = CpuIo->IoRead8 ( PeiServices, CpuIo, 0x64 );
            if((KbcSts2 & 0x02) == 02) {
                KbcIBF1 = TRUE;
            }
        } 
    }  

    // Loop for Key scan
    for (Index = 0 ; Index < LoopCount ; Index++) {
        // Wait atleast for 2ms
        StallPpi->Stall( PeiServices, StallPpi, 6000); 
        // Read Key stroke
        if ((CpuIo->IoRead8 ( PeiServices, CpuIo, 0x64 )) & 0x01) {
            KeyValue = (CpuIo->IoRead8 ( PeiServices, CpuIo, 0x60 ));
        }
        // Check for valid key
        if (KeyValue == 0x1d){
            KeyScan |= (1 << 0); // Set BIT0 if it is CTRL key
        } else 
            if (KeyValue == 0x47){
                KeyScan |= (1 << 1); // Set BIT1 if it is HOME key 
            }
        // Check for CTRL_HOME Combination
        if ((KeyScan & 0x03) == 0x03) {
            // Disable KeyBoard Controller
            CpuIo->IoWrite8 ( PeiServices, CpuIo, 0x64, 0x60 );
            CpuIo->IoWrite8 ( PeiServices, CpuIo, 0x60, 0x30 );
            return TRUE;
        }
    }
    // Disable KeyBoard Controller
    CpuIo->IoWrite8 ( PeiServices, CpuIo, 0x64, 0x60 );
    CpuIo->IoWrite8 ( PeiServices, CpuIo, 0x60, 0x30 );

    return FALSE; // No valid key is pressed
}
#endif        // KBC_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IsRecovery
//
// Description: 
//  This function determines if the system is supposed to boot in recovery mode
//
// Input:   
//  **PeiServices - pointer to the Pei Services function and data structure
//
// Output:    
//  TRUE - The system is booting in recovery mode
//  FALSE - Normal Boot
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN 
IsRecovery (
    EFI_PEI_SERVICES    **PeiServices,
    EFI_PEI_PCI_CFG2_PPI   *PciCfg,
    EFI_PEI_CPU_IO_PPI    *CpuIo
)
{
    BOOLEAN IsRecovery;
    EFI_BOOT_MODE BootMode;

    // If we already in recovery mode, just return TRUE
    if (  !EFI_ERROR((*PeiServices)->GetBootMode(PeiServices, &BootMode))
        && BootMode == BOOT_IN_RECOVERY_MODE
    ) return TRUE;

    IsRecovery=CallOneParamHooks(IsRecoveryList, PeiServices);
 
    //You can use IsRecovery eLink to install customer handlers
    //or just add the code here
    //Check recovery jumper
    //IsRecovery = (IoRead16(GPIO_BASE_ADDRESS + ...) & 0x...);

    if (IsRecovery) PEI_PROGRESS_CODE(PeiServices,PEI_RECOVERY_USER);
    return IsRecovery;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OEM_Get4080PinCableStatus
//
// Description: 
//  Detect whether 40/80 pin cable is connected.
//
// Input:       
//  *PciIO    PCI I/O protocol pointer
//  Channel   Channel information
//
// Output:      
//  TRUE  80 Pin cable connected
//  FALSE 40 Pin Cable connected
//
// Notes:       
//  Make use of PciIO protocol to distinguish between multiple IDE controllers.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
OEM_Get4080PinCableStatus (
    IN EFI_PCI_IO_PROTOCOL      *PciIO,
    IN UINT8                    Channel
)
{

/***
  UINT8     *Address;
  UINT8     FwhGpi;
  UINT8     GpiDma66Detect = 0x01;   // Bit 0

//  For SATA always return 80 Pin Cable
    if (CheckSATADevice(PciIO, Channel) == EFI_SUCCESS) return TRUE;

//  ICH firmware hub provides 4 additional GPIs, located at 0xffbc0100
    GpiDma66Detect = Channel == PRIMARY_CHANNEL ? 0x01 : 0x02;
    Address = (UINT8*)0xffbc0100;
    FwhGpi  = *Address;

    if ((FwhGpi & GpiDma66Detect) == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
***/
    return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: NoConfigChanges
//
// Description: 
//  This function determines if the system has not been opened since the 
//  last boot.  Chassis Intrusion sensor used
//
// Input:   
//  **PeiServices - pointer to the Pei Services function and data structure
//
// Output:    
//  TRUE - The Chassis has not been opened
//  FALSE - The Chassis has been opened
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN 
NoConfigChanges(
  EFI_PEI_SERVICES    **PeiServices,
  EFI_PEI_PCI_CFG2_PPI   *PciCfg,
  EFI_PEI_CPU_IO_PPI    *CpuIo
  )
{
    //You can use NoConfigChanges eLink to install customer handlers
    //or just add the code here

//    UINT  Buffer32;
//    UINT16  Buffer16;

// Insert code here that detects an intruder
/*
    // Get Base address of Power Management I/O Registers
    PciCfg->Read( PeiServices, PciCfg, EfiPciCfgWidthUint32,
        LPC_BUS_DEV_FUNC | REG_LPC_PMBASE, (VOID *)&Buffer32 );


    Buffer16 = CpuIo->IoRead16 (PeiServices, CpuIo,
                Buffer32 + TCO_OFFSET + TCO2_STS);

    // check Intrusion Bit in TCO_STS Register
    if ()
        return TRUE;
*/
    return CallOneParamHooks(NoConfigChangesList, PeiServices);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IsMfgMode
//
// Description: 
//  This function determines if the system in in manufacturing mode.
//  This function is called by NVRAM code. 
//  If system is in manufacturing mode, manufacturing values for NVRAM variables 
//  are used.
//
// Input:   
//  **PeiServices - pointer to a pointer to the PEI Services Table. 
//  *ReadVariablePpi - pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI PPI. The pointer 
//                     can be used to read and enumerate existing NVRAM variables.
//
// Output:    
//  TRUE - Manufacturing mode is detected
//  FALSE - Manufacturing mode is not detected
//
// Notes: 
//  This routine is called very early, prior to SBPEI and NBPEI
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsMfgMode(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){
#if MANUFACTURING_MODE_SUPPORT
    //You can use IsMfgMode eLink to install customer handlers
    //or just add the code here
    return CallTwoParamHooks(IsMfgModeList, PeiServices, ReadVariablePpi);
#else
    //Do not change this.
    //This is needed to be able to disable manufacturing mode support using SDL token.
    return FALSE;
#endif
}

#if CLEAR_NVRAM_IF_CMOS_BAD
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PreserveSetupPassword
//
// Description: Save the Setup Password
//
// Input:       EFI_PEI_SERVICES                        **PeiServices,
//              CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI   *ReadVariablePpi
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
PreserveSetupPassword (
    EFI_PEI_SERVICES                        **PeiServices,
    CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI   *ReadVariablePpi
)
{
    EFI_STATUS      Status;
    EFI_GUID        gAmiTseSetupGuid = AMITSESETUP_GUID;
    EFI_GUID        HobListGuid = HOB_LIST_GUID;
    EFI_GUID        PwdHobGuid = PASSWORD_HOB_GUID;
    PASSWORD_HOB    *PwdHobPtr;
    AMITSESETUP     AmiTseData;
    UINTN           VariableSize = sizeof(AMITSESETUP);

    // Read Password from NVRAM
    Status = ReadVariablePpi->GetVariable(
                                    ReadVariablePpi,
                                    L"AMITSESetup",
                                    &gAmiTseSetupGuid,
                                    NULL,
                                    &VariableSize,
                                    &AmiTseData
                                    );
    if (Status == EFI_SUCCESS) {
        // Save Password to Hob
        Status = (*PeiServices)->CreateHob(PeiServices,
                                        EFI_HOB_TYPE_GUID_EXTENSION,
                                        sizeof(PASSWORD_HOB),
                                        &PwdHobPtr);

        if (Status == EFI_SUCCESS) {
            (*PeiServices)->CopyMem(&PwdHobPtr->EfiHobGuidType.Name, &PwdHobGuid, sizeof(EFI_GUID));

            (*PeiServices)->CopyMem(&PwdHobPtr->AmiTseData, &AmiTseData, sizeof(AmiTseData));
        }
    }
}
#endif      // CLEAR_NVRAM_IF_CMOS_BAD

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IsResetConfigMode
//
// Description: 
//  This function determines if the system configuration needs to be reset.
//  This function is called by NVRAM code. 
//
// Input:   
//  **PeiServices - pointer to a pointer to the PEI Services Table. 
//  *ReadVariablePpi - pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI PPI. The 
//                     pointer can be used to read and enumerate existing NVRAM 
//                     variables.
//
// Output:    
//  TRUE - Reset Configuration condition is detected
//  FALSE - Reset Configuration condition is not detected
//
// Notes: This routine is called very early, prior to SBPEI and NBPEI
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsResetConfigMode(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){
#if CLEAR_NVRAM_IF_CMOS_BAD
    PreserveSetupPassword(PeiServices, ReadVariablePpi);
#endif

    //You can use IsResetConfigMode eLink to install customer handlers
    //or just add the code here
    return CallTwoParamHooks(
        IsResetConfigModeList, PeiServices, ReadVariablePpi
    );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IsDefaultConfigMode
//
// Description: 
//  This function determines if the system should boot with the default configuration.
//  This function is called by NVRAM code. 
//  If boot with default configuration is detected, default values for NVRAM 
//  variables are used.
//
// Input:   
//  **PeiServices - pointer to a pointer to the PEI Services Table. 
//  *ReadVariablePpi - pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI PPI. The pointer 
//                     can be used to read and enumerate existing NVRAM variables.
//
// Output:    
//  TRUE - Boot with default configuration is detected
//  FALSE - Boot with default configuration is not detected
//
// Notes: 
//  This routine is callsed very early, prior to SBPEI and NBPEI
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsDefaultConfigMode(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){
    //You can use IsDefaultConfigMode eLink to install customer handlers
    //or just add the code here
    return CallTwoParamHooks(
        IsDefaultConfigModeList, PeiServices, ReadVariablePpi
    );
}

static EFI_GUID SetupVariableGuid = SETUP_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IsNvramDataCompatible
//
// Description: 
//  This function determines if the current NVRAM data 
//  (mainly Setup-related variables) is compatible with the current firmware.
//
// Input:   
//  **PeiServices - pointer to a pointer to the PEI Services Table. 
//  *ReadVariablePpi - pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI PPI. 
//                     The pointer can be used to read and enumerate existing 
//                     NVRAM variables.
//
// Output:    
//  TRUE - the NVRAM data is compatible
//  FALSE - the NVRAM data is not compatible
//
// Notes: 
//  This function is called by NVRAM PEIM. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsNvramDataCompatible(
    IN EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){
    UINTN Size = 0;
    EFI_STATUS Status;

    Status=ReadVariablePpi->GetVariable(
        ReadVariablePpi, L"Setup",
        &SetupVariableGuid, NULL,
        &Size, NULL
    );
    if (Status!=EFI_BUFFER_TOO_SMALL) return TRUE;
    return Size==sizeof(SETUP_DATA);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: DxeIsNvramDataCompatible
//
// Description: 
//  This function determines if the current NVRAM data 
//  (mainly Setup-related variables) is compatible with the current firmware.
//  This function is called by NVRAM Driver. 
//
// Input:       
//  GetVariable - pointer to EFI_GET_VARIABLE function. The pointer can be used 
//                to read existing NVRAM variables.
//
// Output:    
//  TRUE - the NVRAM data is compatible
//  FALSE - the NVRAM data is not compatible
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN DxeIsNvramDataCompatible(
    IN EFI_GET_VARIABLE GetVariable
){
    UINTN Size = 0;
    EFI_STATUS Status;

    Status=GetVariable(
        L"Setup",
        &SetupVariableGuid, NULL,
        &Size, NULL
    );
    if (Status!=EFI_BUFFER_TOO_SMALL) return TRUE;
    return Size==sizeof(SETUP_DATA);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************