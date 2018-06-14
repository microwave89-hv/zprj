//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformSetupInfo/PlatformSetupInfo.c 13    8/02/13 6:46a Alanlin $
//
// $Revision: 13 $
//
// $Date: 8/02/13 6:46a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformSetupInfo/PlatformSetupInfo.c $
// 
// 13    8/02/13 6:46a Alanlin
// [TAG] None
// [Category] Normal
// [Severity] Normal
// [Description] Update to support Haswell ULT D0 setup info
// [Files] PlatformSetupInfo.c
// 
// 12    6/04/13 10:10a Alanlin
// [TAG] None 
// [Category] Bug Fix
// [Severity] Normal
// [Symptom] UEFI_231C_SCT_Final_Draft_201303 test failed.
// [RootCause] The variable use illegal variable guid.
// [Solution] Change GUID form EFI_GLOBAL_VARIABLE to
// AMI_GLOBAL_VARIABLE_GUID.
// [Files] PlatformSetupInfo.c
// 
// 11    3/15/13 6:56a Alanlin
// [TAG] None
// [Category] Normal
// [Severity] Normal
// [Description] Add PCH Lan version information.
// [Files] PlatformSetupInfo.c, PlatformSetupInfo.h.
// 
// 10    1/28/13 11:12p Alanlin
// [TAG] EIP113555
// [Category] Important
// [Severity] Important
// [Description] Update Shark Bay Client ACPI Reference Code Beta Version
// 1.0.0
// 
// 9     1/18/13 3:59a Alanlin
// [TAG] None
// [Category] Normal
// [Severity] Normal
// [Description] Fixed that Setup menu shows incorrect CPU informaion for
// C0 stepping
// [Files] PlatformSetupInfo.c.
// 
// 8     1/15/13 5:48a Alanlin
// [TAG] None
// [Category] Normal
// [Severity] Normal
// [Description] Update to support Haswell C0 and ULT C1 setup info
// [Files] PlatformSetupInfo.c, PlatformSetupInfo.h
// 
// 7     11/26/12 6:01a Alanlin
// [TAG] None
// [Category] Improvement
// [Severity] Normal
// [Description] Fixed that Setup menu shows incorrect CPU informaion for
// Sharkbay ULT.
// [Files] PlatformSetupInfo.c, PlatformSetupInfo.h
// 
// 6     8/14/12 8:56a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Severity]    Important
// [Description] Update to support Haswell B0 and ULT A0 setup info.
// [Files]       PlatformSetupInfo.c, PlatformSetupInfo.h
// 
// 5     7/11/12 3:55a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Correct Lan PHY Revision in BIOS Setup info.
// [Files]       PlatformSetupInfo.c, PlatformSetupInfo.h
// 
// 4     4/25/12 1:23p Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Correct Graphics Technology (GT) Displays (GT Info) in
// BIOS Setup.
// [Files]       PlatformSetupInfo.c, PlatformSetupInfo.h
// 
// 3     4/05/12 7:14a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Severity]    Important
// [Description] Fixed building error for Intel System Agent
// Label:"4.6.5.3_Intel_SA-RC_055_004".
// [Files]       PlatformSetupInfo.c, PlatformSetupInfo.mak
// 
// 2     3/26/12 4:06a Yurenlai
// [TAG]  		EIP86219
// [Category]  	New Feature
// [Description]  	Add PCH information in SharkBay BIOS setup.
// [Files]  		PlatformSetupInfo.c, PlatformSetupInfo.sd,
// PlatformSetupInfo.uni
// 
// 1     2/24/12 1:02a Yurenlai
// Add PlatformSetupInfo module part.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  PlatformSetupInfo.c
//
// Description: Display platform information
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------
#include <Setup.h>
#include <SetupStrTokens.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#if defined (IntelTXT_SUPPORT) && IntelTXT_SUPPORT
#include <Txt.h>
#endif
#if defined CRB_EC_SUPPORT && CRB_EC_SUPPORT
#include <Protocol\EcAccess.h>
#endif
#if EFI_SPECIFICATION_VERSION>0x20000
#include <Protocol\HiiDatabase.h>
#include <Protocol\HiiString.h>
#define LANGUAGE_CODE_ENGLISH    "en-US"
#else
#include <Protocol/Hii.h>
#endif
#include "PchRegs.h"
#include "PlatformSetupInfo.h"
#include "CpuRegs.h"

EFI_HII_HANDLE          gMainHiiHandle = NULL;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Name:        UpdateCpuInformation
//
// Description: Update CPU Information to Main page.
//
// Input:       None
//
// Output:      None
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateCpuInformation (VOID)
{
    UINT32                  RegEax, RegEbx, RegEcx, RegEdx;
    UINT32                  CpuSignature;
    UINT32                  CpuID;
    UINT8                   CpuStepping;
    UINTN                   i, Count;
    UINT8                   CpuCores = NumCpuCores();
    CPU_REV                 ProcessorRevisionTable[] = {    
                                {CPUID_FULL_FAMILY_MODEL_HASWELL_A0, 0x01, "A0"},
                                {CPUID_FULL_FAMILY_MODEL_HASWELL_B0, 0x02, "B0"},
                                {CPUID_FULL_FAMILY_MODEL_HASWELL_B0, 0x05, "C0"},
                                {CPUID_FULL_FAMILY_MODEL_HASWELL_C0, 0x05, "C0"},
                                {CPUID_FULL_FAMILY_MODEL_HASWELL_C0, 0x06, "C0"},
                                {CPUID_FULL_FAMILY_MODEL_HASWELL_ULT, 0x01, "A0"},
                                {CPUID_FULL_FAMILY_MODEL_HASWELL_ULT, 0x02, "B0"},
                                {CPUID_FULL_FAMILY_MODEL_HASWELL_ULT, 0x03, "B1"},
                                {CPUID_FULL_FAMILY_MODEL_HASWELL_ULT_C0, 0x09, "C0"},
                                {CPUID_FULL_FAMILY_MODEL_HASWELL_ULT_C0, 0x0B, "D0"},
                                {CPUID_FULL_FAMILY_MODEL_CRYSTALWELL, 0x02, "B0"},
                                };

    CPULib_CpuID (1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    CpuSignature = RegEax & CPUID_FULL_FAMILY_MODEL;
    CpuID = RegEax & 0xFFFFF;
    CpuStepping = MmioRead8 (PciNBD0F0RegBase + PCIE_Revision_Identification);


    switch (CpuSignature) {
      case CPUID_FULL_FAMILY_MODEL_HASWELL:
        InitString (
          gMainHiiHandle,
          STRING_TOKEN (STR_BOARD_PROCESSOR_VALUE),
          L"%a",
          "Haswell"
          );
          break;
      case CPUID_FULL_FAMILY_MODEL_HASWELL_ULT:
        InitString (
          gMainHiiHandle,
          STRING_TOKEN (STR_BOARD_PROCESSOR_VALUE),
          L"%a",
          "Haswell ULT"
          );
          break;
      case CPUID_FULL_FAMILY_MODEL_CRYSTALWELL:
        InitString (
          gMainHiiHandle,
          STRING_TOKEN (STR_BOARD_PROCESSOR_VALUE),
          L"%a",
          "Crystalwell"
          );
          break;
      default:
        InitString (
          gMainHiiHandle,
          STRING_TOKEN (STR_BOARD_PROCESSOR_VALUE),
          L"%a",
          "Unknown"
          );
    }

    Count = sizeof (ProcessorRevisionTable) / sizeof (ProcessorRevisionTable[0]);
    for (i = 0; i < Count; i++) {
      if ((CpuID == ProcessorRevisionTable[i].CPUID) && (CpuStepping == ProcessorRevisionTable[i].Stepping)){
        InitString (
          gMainHiiHandle,
          STRING_TOKEN (STR_BOARD_PROCESSOR_STEPPING_VALUE),
          L"%a",
          ProcessorRevisionTable[i].String
          );
        break;
      }
    }

    InitString (
      gMainHiiHandle,
      STRING_TOKEN (STR_BOARD_PROCESSOR_COUNT_VALUE),
      L"%xCore(s) / %xThread(s)",
      CpuCores,
      CpuCores * (IsHtEnabled() ? 2 : 1)
      );
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Name:        UpdatePchInformation
//
// Description: Update PCH Information to Main page.
//
// Input:       None
//
// Output:      None
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdatePchInformation (VOID)
{
    UINT16      Data16;

    Data16 = MmioRead16 (PciD31F0RegBase + R_PCH_LPC_DEVICE_ID);

    if (IS_PCH_LPTH_LPC_DEVICE_ID (Data16)) {
      InitString (
        gMainHiiHandle,
        STRING_TOKEN (STR_BOARD_CHIP_SB_VALUE),
        L"%a",
        "LynxPoint"
        );
    }
    else if (IS_PCH_LPTLP_LPC_DEVICE_ID (Data16)) {
      InitString (
        gMainHiiHandle,
        STRING_TOKEN (STR_BOARD_CHIP_SB_VALUE),
        L"%a",
        "LynxPoint-LP"
        );
    }
    else {
      InitString (
        gMainHiiHandle,
        STRING_TOKEN (STR_BOARD_CHIP_SB_VALUE),
        L"%a",
        "Unknown"
        );
    }

#if defined (IntelTXT_SUPPORT) && IntelTXT_SUPPORT
    //
    // Platform PCH TXT capability
    //
    if (MmioRead32 (TXT_PUBLIC_BASE + 0x10) & BIT0) {
      InitString (
        gMainHiiHandle,
        STRING_TOKEN (STR_BOARD_PLATFORM_TXT_VALUE),
        L"%a",
        "Supported"
        );
    } else {
      InitString (
        gMainHiiHandle,
        STRING_TOKEN (STR_BOARD_PLATFORM_TXT_VALUE),
        L"%a",
        "Unsupported"
        );
    }
#endif
}

#if defined CRB_EC_SUPPORT && CRB_EC_SUPPORT
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Name:        UpdateEcVersion
//
// Description: Update the version of CRB EC.
//
// Input:       None
//
// Output:      None
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateEcVersion (VOID)
{
    EFI_STATUS              Status = EFI_SUCCESS;
    EFI_GUID                EfiEcAccessProtocolGuid = EC_PROTOCOL_GUID;
    EFI_EC_ACCESS_PROTOCOL  *ECAccess = NULL;
    EFI_GUID                gAmiGlobalVariableGuid = AMI_GLOBAL_VARIABLE_GUID;
    UINT8                   DataHigh = 0;
    UINT8                   DataLow = 0;
    UINTN                   VariableSize;

    Status = pBS->LocateProtocol (&EfiEcAccessProtocolGuid, NULL, &ECAccess);
    if (EFI_ERROR(Status)) {
      return;
    } 

    //
    // Initializing the size for retrieving variable(s) "ECRev1" & "ECRev2"
    //
    VariableSize = sizeof (UINT8);
    pRS->GetVariable (
           L"ECRev1",
           &gAmiGlobalVariableGuid,
           NULL,
           &VariableSize,
           &DataHigh
           );
    pRS->GetVariable (
           L"ECRev2",
           &gAmiGlobalVariableGuid,
           NULL,
           &VariableSize,
           &DataLow
           );

    InitString (
      gMainHiiHandle,
      STRING_TOKEN (STR_BOARD_CHIP_EC_REV_VALUE),
      L"%02X%a%02X",
      DataHigh,
      ".",
      DataLow
      );
}
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Name:        UpdateLanPhyRevision
//
// Description: Retrieves LAN PHY Revision.
//
// Input:       None
//
// Output:      None
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateLanPhyRevision (VOID)
{
  UINTN         PciD25F0RegBase;
  UINT32        GbEBar;
  UINT32        RegisterValue;
  UINTN         LoopTime;
  UINT8         LanPhyRev;
  UINTN         Index;
  UINT8         Data;
  BOOLEAN       Found;
  LAN_PHY_INFO  LanPhyInfoTable[] = {
                    { LAN_PHY_REV_A0, "A0" },
                    { LAN_PHY_REV_A1, "A1" },
                    { LAN_PHY_REV_A2, "A2" },
                    { LAN_PHY_REV_A3, "A3" },
                    { LAN_PHY_REV_B0, "B0" },
                    { LAN_PHY_REV_C0, "C0" }};
  GbEBar    = 0;
  LanPhyRev = 0;
  Found     = FALSE;

  PciD25F0RegBase =
    (
      PCIEX_BASE_ADDRESS +
      ((PCI_BUS_NUMBER_PCH_LAN) << 20) +
      ((PCI_DEVICE_NUMBER_PCH_LAN) << 15) +
      ((PCI_FUNCTION_NUMBER_PCH_LAN) << 12)
    );
  GbEBar  = MmioRead32 (PciD25F0RegBase + R_PCH_LAN_MEM_BASE_A) & B_PCH_LAN_MBARB_BA;

  Data    = MmioRead8 (PciD25F0RegBase + R_PCH_LAN_CMD);
  //
  // Command Register's Value is 0 in Fast Boot and Modifying here
  //
  if ((Data & B_PCH_LAN_CMD_MSE) == 0) {
    MmioWrite8 ((PciD25F0RegBase + R_PCH_LAN_CMD), 0x07);
    Found = TRUE;
  }
  //
  // Request semaphore
  //
  Mmio32 (GbEBar, PHY_SEMAPHORE_REG) |= BIT5;

  for (LoopTime = 0; LoopTime < GBE_MAX_LOOP_TIME; LoopTime++) {
    RegisterValue = MmioRead32 (GbEBar + PHY_SEMAPHORE_REG);

    if (RegisterValue & BIT5) {
      break;
    }

    pBS->Stall (10);
  }

  if (LoopTime >= GBE_MAX_LOOP_TIME) {
    return ;
  }
  //
  // Write PHY_CONFIG_REG with set page 769
  //
  MmioWrite32 ((GbEBar + PHY_CONFIG_REG), PHY_PAGE769_SET_REG);
  for (LoopTime = 0; LoopTime < GBE_MAX_LOOP_TIME; LoopTime++) {
    RegisterValue = MmioRead32 (GbEBar + PHY_CONFIG_REG);

    if (RegisterValue & BIT28) {
      break;
    }

    pBS->Stall (10);
  }

  if (LoopTime >= GBE_MAX_LOOP_TIME) {
    return ;
  }
  //
  // Delay 4ms after page change
  //
  pBS->Stall (4000);

  //
  // Write PHY_CONFIG_REG with slow MDIO mode
  //
  MmioWrite32 ((GbEBar + PHY_CONFIG_REG), PHY_SLOW_MDIO_MODE_REG);
  for (LoopTime = 0; LoopTime < GBE_MAX_LOOP_TIME; LoopTime++) {
    RegisterValue = MmioRead32 (GbEBar + PHY_CONFIG_REG);

    if (RegisterValue & BIT28) {
      break;
    }

    pBS->Stall (10);
  }

  if (LoopTime >= GBE_MAX_LOOP_TIME) {
    return ;
  }
  //
  // Read register PHY Version (offset 0x3)
  //
  MmioWrite32 ((GbEBar + PHY_CONFIG_REG), PHY_READ_PHY_OFFSET3_REG);
  for (LoopTime = 0; LoopTime < GBE_MAX_LOOP_TIME; LoopTime++) {
    RegisterValue = MmioRead32 (GbEBar + PHY_CONFIG_REG);
    if (RegisterValue & BIT28) {
      break;
    }

    pBS->Stall (10);
  }

  if (LoopTime >= GBE_MAX_LOOP_TIME) {
    return ;
  }
  //
  // Read LAN PHY revision from PHY register 3
  //
  LanPhyRev = (UINT8) MmioRead16 (GbEBar + PHY_CONFIG_REG);

  //
  // Write PHY_CONFIG_REG to write fast mdio mode
  //
  MmioWrite32 ((GbEBar + PHY_CONFIG_REG), PHY_FAST_MDIO_MODE_REG);
  for (LoopTime = 0; LoopTime < GBE_MAX_LOOP_TIME; LoopTime++) {
    RegisterValue = MmioRead32 (GbEBar + PHY_CONFIG_REG);

    if (RegisterValue & BIT28) {
      break;
    }

    pBS->Stall (10);
  }

  if (LoopTime >= GBE_MAX_LOOP_TIME) {
    return ;
  }
  //
  // Free semaphore
  //
  Mmio32 (GbEBar, PHY_SEMAPHORE_REG) &= ~BIT5;

  //
  // LAN PHY Revision
  //
  if (LanPhyRev) {
    for (Index = 0; Index < (sizeof (LanPhyInfoTable)/sizeof (LAN_PHY_INFO)); Index++) {
      if (LanPhyRev == LanPhyInfoTable[Index].LanPhyRev) {
        InitString (
          gMainHiiHandle,
          STRING_TOKEN (STR_BOARD_LAN_PHY_REV_VALUE),
          L"%a",
          LanPhyInfoTable[Index].LanPhyString
          );
        break;
      }
    }
  }

  if (Found == TRUE) {
    MmioWrite8 ((PciD25F0RegBase + R_PCH_LAN_CMD), Data);
  }

  return ;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Name:        UpdateSpiClockFreqInfo
//
// Description: Update SPI Clock Frequency information to Main page.
//
// Input:       None
//
// Output:      None
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateSpiClockFreqInfo (VOID)
{
    UINT32      Flcomp;
    UINT32      SpiFrequ;

    MmioRW32 ((SB_RCBA + R_PCH_SPI_FDOC), (UINT32)(V_PCH_SPI_FDOC_FDSS_COMP), (UINT32)(B_PCH_SPI_FDOC_FDSS_MASK | B_PCH_SPI_FDOC_FDSI_MASK));
    Flcomp = MmioRead32 (SB_RCBA + R_PCH_SPI_FDOD);
  
    // Check Dual Output Fast Read Support
    if (Flcomp & BIT30) {
      InitString (
        gMainHiiHandle,
        STRING_TOKEN (STR_SPI_DOFR_SUPPORT_VALUE),
        L"%a",
        "Supported"
        );
    }
    else {
      InitString (
        gMainHiiHandle,
        STRING_TOKEN (STR_SPI_DOFR_SUPPORT_VALUE),
        L"%a",
        "Unsupported"
        );
    }  

    //
    // Fast Read Clock Frequency
    //  
    switch ((Flcomp & (BIT23 | BIT22 | BIT21)) >> 21) {  
      case V_PCH_SPI_SSFC_SCF_20MHZ:
                SpiFrequ = 20;
                InitString (
                  gMainHiiHandle,
                  STRING_TOKEN (STR_SPI_FAST_READ_FREQUENCY_VALUE),
                  L"%d MHz",
                  SpiFrequ
                  ); 
                break;
      case V_PCH_SPI_SSFC_SCF_33MHZ:
                SpiFrequ = 33;
                InitString (
                  gMainHiiHandle,
                  STRING_TOKEN (STR_SPI_FAST_READ_FREQUENCY_VALUE),
                  L"%d MHz",
                  SpiFrequ
                  );
                break;
      case V_PCH_SPI_SSFC_SCF_50MHZ:
                SpiFrequ = 50;
                InitString (
                  gMainHiiHandle,
                  STRING_TOKEN (STR_SPI_FAST_READ_FREQUENCY_VALUE),
                  L"%d MHz",
                  SpiFrequ
                  );
                break;
      default: break;
    }
  
    //
    // Write and Erase Clock Frequency
    // 
    switch ((Flcomp & (BIT26 | BIT25 | BIT24)) >> 24) {
      case V_PCH_SPI_SSFC_SCF_20MHZ: 
                SpiFrequ = 20;
                InitString (
                  gMainHiiHandle,
                  STRING_TOKEN (STR_SPI_WRITE_CLOCK_FREQUENCY_VALUE),
                  L"%d MHz",
                  SpiFrequ
                  );
                break;
      case V_PCH_SPI_SSFC_SCF_33MHZ:
                SpiFrequ = 33;
                InitString (
                  gMainHiiHandle,
                  STRING_TOKEN (STR_SPI_WRITE_CLOCK_FREQUENCY_VALUE),
                  L"%d MHz",
                  SpiFrequ
                  ); 
                break;
      case V_PCH_SPI_SSFC_SCF_50MHZ:
                SpiFrequ = 50;
                InitString (
                  gMainHiiHandle,
                  STRING_TOKEN (STR_SPI_WRITE_CLOCK_FREQUENCY_VALUE),
                  L"%d MHz",
                  SpiFrequ
                  );
                break;
      default: break; 
    }
  
    //
    // Read ID and Read Status Clock Frequency
    // 
    switch ((Flcomp & (BIT29 | BIT28 | BIT27)) >> 27) {  
      case V_PCH_SPI_SSFC_SCF_20MHZ: 
                SpiFrequ = 20;
                InitString (
                  gMainHiiHandle,
                  STRING_TOKEN (STR_SPI_READ_CLOCK_FREQUENCY_VALUE),
                  L"%d MHz",
                  SpiFrequ
                  ); 
                break;
      case V_PCH_SPI_SSFC_SCF_33MHZ:
                SpiFrequ = 33;
                InitString (
                  gMainHiiHandle,
                  STRING_TOKEN (STR_SPI_READ_CLOCK_FREQUENCY_VALUE),
                  L"%d MHz",
                  SpiFrequ
                  ); 
                break;
      case V_PCH_SPI_SSFC_SCF_50MHZ:
                SpiFrequ = 50;
                InitString (
                  gMainHiiHandle,
                  STRING_TOKEN (STR_SPI_READ_CLOCK_FREQUENCY_VALUE),
                  L"%d MHz",
                  SpiFrequ
                  ); 
                break;
      default: break;  
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetAndUpdateHiiString
//
// Description: This function Reads a String from HII Handle and updates the 
//              string to Main HII Handle.
//
// Input:       HiiHandleGet    - Efi Hii Handle
//              TokenGet        - String Token
//              TokenUpdate     - String Token
//
// Output:      Returns  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetAndUpdateHiiString (
    IN EFI_HII_HANDLE HiiHandleGet,
    IN STRING_REF     TokenGet,
    IN STRING_REF     TokenUpdate)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
#if EFI_SPECIFICATION_VERSION>0x20000
    static EFI_HII_STRING_PROTOCOL  *HiiString = NULL;
    CHAR8                           Language[] = LANGUAGE_CODE_ENGLISH;
#else
    static EFI_HII_PROTOCOL         *Hii = NULL;
#endif
    CHAR16                          String[0x100];
    UINTN                           StringLength = sizeof(String)/sizeof(CHAR16);

    if (HiiHandleGet == NULL) {
      return EFI_INVALID_PARAMETER;
    }
    
#if EFI_SPECIFICATION_VERSION > 0x20000
    if (HiiString == NULL) {
      Status = pBS->LocateProtocol (&gEfiHiiStringProtocolGuid, NULL, &HiiString);
    }
#else
    if (Hii == NULL) {
      Status = pBS->LocateProtocol (&gEfiHiiProtocolGuid, NULL, &Hii);
    }
#endif
    ASSERT_EFI_ERROR(Status); 

    pBS->SetMem(String, (sizeof(CHAR16) * StringLength), 0);     

#if EFI_SPECIFICATION_VERSION>0x20000
    Status = HiiString->GetString (HiiString,
                                   (CHAR8*) &Language,
                                   HiiHandleGet,
                                   TokenGet,
                                   String,
                                   &StringLength,
                                   NULL);
#else
    Status = Hii->GetString (Hii,
                             HiiHandleGet,
                             TokenGet,
                             FALSE,
                             NULL,
                             &StringLength,
                             String);
#endif

    if (EFI_ERROR(Status)) {
      return Status;
    }

    ASSERT (gMainHiiHandle != NULL);

    InitString (
      gMainHiiHandle,
      TokenUpdate,
      L"%s",
      String      
      );

    return EFI_SUCCESS;
}

                                        // (EIP86219)>
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Name:        InitPlatformSetupInfo
//
// Description: This function will display platform information and put into 
//              variables of PlatformSetupInfo.uni file.
//
// Input:       EFI_HII_HANDLE HiiHandle
//
// Output:      VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
InitPlatformSetupInfo(
    EFI_HII_HANDLE      HiiHandle,
    UINT16              Class
)
{
  if (Class == MAIN_FORM_SET_CLASS) {
    gMainHiiHandle = HiiHandle;

    UpdateCpuInformation ();

    UpdatePchInformation ();

    UpdateLanPhyRevision ();

#if defined CRB_EC_SUPPORT && CRB_EC_SUPPORT
    UpdateEcVersion ();
#endif
    
    UpdateSpiClockFreqInfo ();
  }

  if (Class == ADVANCED_FORM_SET_CLASS) {
    //
    // Update Processor Information
    //
    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_CPU_SKT0_VERSION_VALUE), STRING_TOKEN(STR_BOARD_PROCESSOR_VERSION_VALUE)); 

    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_PROCESSOR_SPEED_VALUE), STRING_TOKEN(STR_BOARD_PROCESSOR_SPEED_VALUE)); 

    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_CPU_SKT0_CPUID_VALUE), STRING_TOKEN(STR_BOARD_PROCESSOR_ID_VALUE));

    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_CPU_SKT0_MICROCODE_VALUE), STRING_TOKEN(STR_BOARD_PROCESSOR_MICROCODE_VALUE));

#if defined (iME_SUPPORT) && iME_SUPPORT
    //
    // Update ME Information
    //
    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_ME_FW_VERSION_VALUE), STRING_TOKEN(STR_BOARD_ME_FW_REV_VALUE));

    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_ME_FW_SKU_VALUE), STRING_TOKEN(STR_BOARD_ME_FW_SKU_VALUE));
#endif
  }

  if (Class == CHIPSET_FORM_SET_CLASS) {
    //
    // Update SA Information
    //
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_CHIP_IGFX_VBIOS_REV_VALUE), STRING_TOKEN(STR_BOARD_IGFX_VBIOS_REV_VALUE));
#endif

    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_MRC_REV_VALUE), STRING_TOKEN(STR_BOARD_MRC_REV_VALUE));
 
    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_MEMORY_SIZE_VALUE), STRING_TOKEN(STR_BOARD_MEMORY_SIZE_VALUE));

    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_MEMORY_SPEED_VALUE), STRING_TOKEN(STR_BOARD_MEMORY_FREQ_VALUE));

    // Display GT Type with RP0 Frequency Information
    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_PROCESSOR_GT_VALUE), STRING_TOKEN(STR_BOARD_PROCESSOR_GT_VALUE));

    //
    // Update PCH Information
    //
    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_PCH_SKU_VALUE), STRING_TOKEN(STR_BOARD_CHIP_SB_SKU_VALUE));
    GetAndUpdateHiiString (HiiHandle, STRING_TOKEN(STR_PCH_REVID_VALUE), STRING_TOKEN(STR_BOARD_CHIP_SB_REV_VALUE));
  }

  return;
}
                                        // <(EIP86219)

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
