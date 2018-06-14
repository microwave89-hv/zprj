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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NBSetup/NBSetup.c 26    1/15/15 6:28a Dennisliu $
//
// $Revision: 26 $
//
// $Date: 1/15/15 6:28a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NBSetup/NBSetup.c $
// 
// 26    1/15/15 6:28a Dennisliu
// [TAG]           EIP200606
// [Category]      Improvement
// [Description]   The options of "DIMM profile" can't load default. The
// TSE revision 4.6.2_TSE_2_16_1243 behavior change, it is working after
// checking the case EFI_BROWSER_ACTION_DEFAULT_STANDARD and returning
// EFI_UNSUPPORTED.
// [Files]         NBSetup.c
// 
// 24    7/11/14 3:49a Dennisliu
// [TAG]           None
// [Category]      Improvement
// [Description]   Problem: #if directive for TSE_BUILD=0x1208 (EIP176870)
// [Files]
// Board\NB\NBSetup\NBSetup.c
// Chipset\NB\GOP\IntelSaGopSetup\IntelSaGopSetup.c
// 
// 23    7/31/13 2:26a Ireneyang
// [TAG]         None
// [Category]    BrugFix
// [Symptom]     When adding XTU module, it would have building error.
// [Description] Fix building error when adding XTU module.
// [RootCause]   The original NB_SETUP_CALLBACK function only will be
// build
//               only when PERF_TUNE_SUPPORT is 0. However, CRID is one of
// NB_SETUP_CALLBACK and it should be build wheather 
//               PERF_TUNE_SUPPORT is 0 or 1. Others of NB_SETUP_CALLBACK 
//               should still keep be build only when PERF_TUNE_SUPPORT 
//               is 0. 
// [Solution]    Divide others from original NB_SETUP_CALLBACK group to 
//               an new NB_MEMORY_TUNING_CALLBACK and let them only be 
//               build when PERF_TUNE_SUPPORT is 0. Keep CRID in 
//               NB_SETUP_CALLBACK without any building condition. 
// [Files]       NBSetup.sdl; NBSetup.c;
// 
// 22    7/09/13 4:00a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Add new feature CRID into SMBIOS Type88.
// [Files]       NB.sd; NBSetup.c; NBSetup.sdl;
// 
// 21    6/20/13 11:32p Ireneyang
// [TAG]         EIP126611
// [Category]    Improvement
// [Description] Correct GT information.
// [Files]       NBSetup.c;
// 
// 20    6/13/13 7:56a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Update LCAP Max Link Spped Value for Gen2/Gen1.
// 
// 19    5/13/13 6:27a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Add PanelPowerEnable for enabling/disabling VDD force
// bit.
//               (Required only for early enabling of eDP panel)
// [Files]       NBSetup.c; GetSetupData.c; NbSetupData.h; NBPEI.c;
// 
// 18    5/13/13 4:31a Ireneyang
// [TAG]         EIP118807
// [Category]    BrugFix
// [Description] Actual memory size and memory size information in Setup 
//               Menu are dismatch.   
// [Files]       NBSetup.c;
// 
// 17    5/09/13 8:35a Ireneyang
//
// 14    12/24/12 2:56a Jeffch
// [TAG]         None
// [Category]    Bug Fix
// [Description] Remove tRPab and fixed XTU build fail issue.
// [Files]        NBPei.c; NBDxe.c; NB.sd;
// 
// 13    12/22/12 2:32a Jeffch
// 
// 12    12/14/12 5:18a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Show memory voltage.
// [Files]        NB.sd; NB.uni; NBDxe.c.
// 
// 11    11/19/12 4:37a Jeffch
// [TAG]          EIP106919
// [Severity]     Important
// [Description]  Fixed GT info incorrectly when CSM disabled.
// [Files]        NBSetup.c
// 
// 10    10/30/12 7:06a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update SA RC 0.72.
// [Files]        NBSetup.c
// 
// 9     10/14/12 5:36a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Follow SA RC 0.71.
// [Files]        NBPei.c, NBDxe.c; NBGeneric.c; NBCspLib.h; NBSetup.c;
//                  Nb.sd; GetSetupData.c; NBSetup.c;
// 
// 8     10/14/12 12:38a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update by XTU4.0.
// [Files]        NBPei.c, NBDxe.c, NBCspLib.h, NBGeneric.c
// [TAG]          None
// [Severity]     Important
// [Description]  Follow Update by Mahobay.
// [Files]        NBPei.c, NBDxe.c;
// 
// 7     9/26/12 9:33a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Remove SPD XMP Profile support of the setup info.
// [Files]         NB.sd, NBSetup.c
// 
// 6     6/14/12 5:17a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Description]   Fix for setup item 'DIMM profile' associated with
// options.
// [Description]   NBSetup.c, NB.sd
// 
// 5     6/14/12 5:14a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Description]   Fixed Tse 1224 will hang setup call back and value
// error.
// [Description]   NBSetup.c, NB.sd
// 
// 4     4/26/12 2:57a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Adjust Intel System Agent module the Setup item and
// Policy.
// [Description]   GetSetupData.c, NB.sdl, NB.sd, NB.uni, NBDxe.c,
// NBPEI.c,
//                 NBSetup.c, NBSetupReset.c, NbSetupData.h
// 
// 3     4/26/12 2:56a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Correct Graphics Technology (GT) Displays (GT Info) in
// BIOS Setup.
// [Description]   NBSetup.c
// 
// 2     4/05/12 2:27a Yurenlai
// [TAG]  		EIP87103
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change for SystemAgent RefCode Revision: 0.5.5 .
// [Files]  		NBDxe.c, NBPEI.c, NBSMI.C, NBGeneric.cm NB.sd, NBSetup.c,
// GetSetupData.c, NbSetupData.h
// 
// 1     2/08/12 4:33a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NBSetup.c
//
// Description: North Bridge Setup Rountines
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Setup.h>
#include <SetupStrTokens.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\NBMemInfo.h>
#include <MemInfo\MemInfo.h>
#include <SaInfo\SaInfo.h>
#include <Protocol\NBPlatformData.h>
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
#include <Protocol\LegacyBios.h>
#endif

#define _SA_COMMON_DEFINITIONS_H_
#include <SaAccess.h>

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)
#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 0
//
// tCL Macro definitions
//
#ifndef tCL_MINIMUM
#define tCL_MINIMUM   4
#endif
#ifndef tCL_MAXIMUM
#define tCL_MAXIMUM   15
#endif
//
// tRP Macro definitions
//
#ifndef tRP_MINIMUM
#define tRP_MINIMUM   3
#endif
#ifndef tRP_MAXIMUM
#define tRP_MAXIMUM   15
#endif
//
// tRCD Macro definitions
//
#ifndef tRCD_MINIMUM
#define tRCD_MINIMUM   3
#endif
#ifndef tRCD_MAXIMUM
#define tRCD_MAXIMUM   15
#endif
//
// tRAS Macro definitions
//
#ifndef tRAS_MINIMUM
#define tRAS_MINIMUM   9
#endif
#ifndef tRAS_MAXIMUM
#define tRAS_MAXIMUM   63
#endif
//
// tWR Macro definitions
//
#ifndef tWR_MINIMUM
#define tWR_MINIMUM   3
#endif
#ifndef tWR_MAXIMUM
#define tWR_MAXIMUM   31
#endif
//
// tRFC Macro definitions
//
#ifndef tRFC_MINIMUM
#define tRFC_MINIMUM   15
#endif
#ifndef tRFC_MAXIMUM
#define tRFC_MAXIMUM   255
#endif
//
// tRRD Macro definitions
//
#ifndef tRRD_MINIMUM
#define tRRD_MINIMUM   4
#endif
#ifndef tRRD_MAXIMUM
#define tRRD_MAXIMUM   15
#endif
//
// tWTR Macro definitions
//
#ifndef tWTR_MINIMUM
#define tWTR_MINIMUM   3
#endif
#ifndef tWTR_MAXIMUM
#define tWTR_MAXIMUM   31
#endif
//
// tRTP Macro definitions
//
#ifndef tRTP_MINIMUM
#define tRTP_MINIMUM   4
#endif
#ifndef tRTP_MAXIMUM
#define tRTP_MAXIMUM   15
#endif
//
// tFAW Macro definitions
//
#ifndef tFAW_MINIMUM
#define tFAW_MINIMUM   10
#endif
#ifndef tFAW_MAXIMUM
#define tFAW_MAXIMUM   43
#endif
//
// tRC Macro definitions
//
#ifndef tRC_MINIMUM
#define tRC_MINIMUM   1
#endif
#ifndef tRC_MAXIMUM
#define tRC_MAXIMUM   4095
#endif

//
//
// tCWL Macro definitions
//
#ifndef tCWL_MINIMUM
#define tCWL_MINIMUM   5
#endif
#ifndef tCWL_MAXIMUM
#define tCWL_MAXIMUM   12
#endif
//
// tREFI Macro definitions
//
#ifndef tREFI_MINIMUM
#define tREFI_MINIMUM   1
#endif
#ifndef tREFI_MAXIMUM
#define tREFI_MAXIMUM   10000
#endif
//
// tRPab Macro definitions
//
#ifndef tRPab_MINIMUM
#define tRPab_MINIMUM   4
#endif
#ifndef tRPab_MAXIMUM
#define tRPab_MAXIMUM   18
#endif
#endif //#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 0
// Type Definition(s)

// Function Prototype(s)

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)
#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 0
static UINT8 gMaxXmpProfiles = 0;
#endif
STRING_REF  PegInfo[3] = {
  STRING_TOKEN(STR_PEG0_INFO_VALUE),
  STRING_TOKEN(STR_PEG1_INFO_VALUE),
  STRING_TOKEN(STR_PEG2_INFO_VALUE),
};

// GUID Definition(s)
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
static EFI_GUID                    gEfiLegacyBiosProtocol    = EFI_LEGACY_BIOS_PROTOCOL_GUID;
#endif
static EFI_GUID                    gEfiSaInfoProtocolGuid    = EFI_SA_INFO_PROTOCOL_GUID;
static EFI_GUID                    gMemInfoHobProtocolGuid   = MEM_INFO_PROTOCOL_GUID;

// Protocol Definition(s)
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
static EFI_LEGACY_BIOS_PROTOCOL    *LegacyBiosProtocol       = NULL;
#endif

// External Declaration(s)

// Function Definition(s)

VOID
UpdatePegInfo (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
);

VOID
UpdateDmiInfo (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
);

VOID UpdateDDRXmpInfo (
    IN EFI_HII_HANDLE   HiiHandle,
    IN UINT16           Class 
);
//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitNBStrings
//
// Description: Initializes North Bridge Setup String
//
// Input:       HiiHandle - Handle to HII database
//              Class - Indicates the setup class
//
// Output:      None
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitNBStrings (
    IN EFI_HII_HANDLE   HiiHandle,
    IN UINT16           Class )
{

    EFI_STATUS              Status;
    MEM_INFO_PROTOCOL       *MemInfoHobProtocol;
    EFI_SA_INFO_PROTOCOL    *SaInfo;
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
    EFI_IA32_REGISTER_SET   RegSet;
    UINT8                   RevisionHigh;
    UINT8                   RevisionLow;
#endif

    UINT16              Channel_A;
    UINT16              Channel_B;
    UINT16              Slot_0;
    UINT16              Slot_1;
    UINT16              Slot_2;
    UINT16              Slot_3;
    UINT16              DdrFrequency;
    UINT8               MemoryType;
    UINT64              MemorySize;
    UINT64              MchBAR;
    UINTN               Granularity;
    UINT32              IGfxFreq;
    UINT8               GtSkuType;
    UINT32              Value32;
    UINT8               Offset24;
    UINT8               Offset16;
    UINT8               Offset08;
    UINT8               Offset00;
    BOOLEAN             DimmExist[4]  = { 0, 0, 0, 0 };
    UINT8               RankInDimm[4] = { 0, 0, 0, 0 };
    UINT8               MemDevIdx;
    UINT16              VddVoltage[5] = {0};
    UINT16              wDimmValue[DIMM_SLOT_NUM] = {STR_MEMORY_DIMM0_VALUE,
                                                    STR_MEMORY_DIMM1_VALUE,
                                                    STR_MEMORY_DIMM2_VALUE,
                                                    STR_MEMORY_DIMM3_VALUE};
    UINT16              Slot_Array[DIMM_SLOT_NUM];
    NB_SETUP_DATA       NbSetupData;
    UINT8               NbDeviceData; 
    UINT8               GtTypeAndValue;

   if (Class == CHIPSET_FORM_SET_CLASS)
   {
      // Get the Memory Info HOB Protocol if it exists.
      Status = pBS->LocateProtocol (&gMemInfoHobProtocolGuid, NULL, &MemInfoHobProtocol);
      if (!EFI_ERROR (Status)) {

      // each channel has 2 dimms...


        GetNbSetupData( pRS, &NbSetupData, FALSE );     

        if((NbSetupData.DisableDimmChannel0 == 1) || (NbSetupData.DisableDimmChannel0 == 3)){
            Slot_0    = 0;
        }else{
            Slot_0    = (UINT16) ((MemInfoHobProtocol->MemInfoData.dimmSize[0]));
        }

        if((NbSetupData.DisableDimmChannel0 == 2) || (NbSetupData.DisableDimmChannel0 == 3)){
            Slot_1    = 0;
        }else{
            Slot_1    = (UINT16) ((MemInfoHobProtocol->MemInfoData.dimmSize[1]));
        }

        if((NbSetupData.DisableDimmChannel1 == 1) || (NbSetupData.DisableDimmChannel1 == 3)){
            Slot_2    = 0;
        }else{
            Slot_2    = (UINT16) ((MemInfoHobProtocol->MemInfoData.dimmSize[2]));
        }

        if((NbSetupData.DisableDimmChannel1 == 2) || (NbSetupData.DisableDimmChannel1 == 3)){
            Slot_3    = 0;
        }else{
            Slot_3    = (UINT16) ((MemInfoHobProtocol->MemInfoData.dimmSize[3]));
        }

        Channel_A     = Slot_0 + Slot_1;
        Channel_B     = Slot_2 + Slot_3;
        Granularity   = 1;
        MemoryType    = 3;
        MemorySize = (UINT64) ((Channel_A + Channel_B) * Granularity);
        DdrFrequency  = MemInfoHobProtocol->MemInfoData.ddrFreq;

        VddVoltage[0] = MemInfoHobProtocol->MemInfoData.VddVoltage[0];

        for (MemDevIdx = 0; MemDevIdx < 4; MemDevIdx++) {
          DimmExist[MemDevIdx]  = MemInfoHobProtocol->MemInfoData.DimmExist[MemDevIdx];
          RankInDimm[MemDevIdx] = MemInfoHobProtocol->MemInfoData.RankInDimm[MemDevIdx];
          VddVoltage[MemDevIdx+1] = MemInfoHobProtocol->MemInfoData.VddVoltage[MemDevIdx];
        }

        InitString( HiiHandle, \
                    STRING_TOKEN(STR_MEMORY_SIZE_VALUE), \
                    L"%4d MB (DDR3)", \
                    MemorySize);

        InitString( HiiHandle, \
                    STRING_TOKEN(STR_MEMORY_SPEED_VALUE), \
                    L"%4d Mhz", \
                    DdrFrequency );

        InitString( HiiHandle, \
                    STRING_TOKEN(STR_MEMORY_VOLTAGE_VALUE), \
                    L"%1d.%2dv", \
                    VddVoltage[0] / 1000,  (VddVoltage[0] % 1000) / 10 );

        Slot_Array[0] = Slot_0;
        Slot_Array[1] = Slot_1;
        Slot_Array[2] = Slot_2;
        Slot_Array[3] = Slot_3;

        for (MemDevIdx = 0; MemDevIdx < DIMM_SLOT_NUM; MemDevIdx++) {
            if(Slot_Array[MemDevIdx] == 0)
                continue;
            MemorySize = (MemInfoHobProtocol->MemInfoData.dimmSize[MemDevIdx] * Granularity);
            if (MemorySize)
                InitString( HiiHandle, \
                            wDimmValue[MemDevIdx], \
                            L"%4d MB (DDR3)", \
                            MemorySize);
        }

        //
        // Update the tCL, tRCD, tRP and tRAS string with data obtained from MemInfo protocol
        //
        InitString (
          HiiHandle,
          STRING_TOKEN (STR_MEMORY_CL_VALUE),
          L"%d",
          MemInfoHobProtocol->MemInfoData.Timing[0].tCL
        );

        InitString (
          HiiHandle,
          STRING_TOKEN (STR_MEMORY_TRCD_VALUE),
          L"%d",
          MemInfoHobProtocol->MemInfoData.Timing[0].tRCD
        );

        InitString (
          HiiHandle,
          STRING_TOKEN (STR_MEMORY_TRP_VALUE),
          L"%d",
          MemInfoHobProtocol->MemInfoData.Timing[0].tRP
        );

        InitString (
          HiiHandle,
          STRING_TOKEN (STR_MEMORY_TRAS_VALUE),
          L"%d",
          MemInfoHobProtocol->MemInfoData.Timing[0].tRAS
        );

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 0
        InitString (
          HiiHandle,
          STRING_TOKEN (STR_MEMORY_TWR_VALUE),
          L"%d",
          MemInfoHobProtocol->MemInfoData.Timing[0].tWR
        );

        InitString (
          HiiHandle,
          STRING_TOKEN (STR_MEMORY_TRFC_VALUE),
          L"%d",
          MemInfoHobProtocol->MemInfoData.Timing[0].tRFC
        );

        InitString (
          HiiHandle,
          STRING_TOKEN (STR_MEMORY_TRRD_VALUE),
          L"%d",
          MemInfoHobProtocol->MemInfoData.Timing[0].tRRD
        );

        InitString (
          HiiHandle,
          STRING_TOKEN (STR_MEMORY_TWTR_VALUE),
          L"%d",
          MemInfoHobProtocol->MemInfoData.Timing[0].tWTR
        );

        InitString (
          HiiHandle,
          STRING_TOKEN (STR_MEMORY_TRTP_VALUE),
          L"%d",
          MemInfoHobProtocol->MemInfoData.Timing[0].tRTP
        );

        InitString (
          HiiHandle,
          STRING_TOKEN (STR_MEMORY_TFAW_VALUE),
          L"%d",
          MemInfoHobProtocol->MemInfoData.Timing[0].tFAW
        );
#endif

      }   // MemInfoHobProtocol     

      // - Sa version
      Status = pBS->LocateProtocol( &gEfiSaInfoProtocolGuid, \
                                    NULL, \
                                    &SaInfo );
      if (!EFI_ERROR (Status)) {

         Offset24  = (UINT8) ((SaInfo->RCVersion & 0xFF000000) >> 24);
         Offset16  = (UINT8) ((SaInfo->RCVersion & 0xFF0000) >> 16);
         Offset08  = (UINT8) ((SaInfo->RCVersion & 0xFF00) >> 8);
         Offset00  = (UINT8) ((SaInfo->RCVersion & 0xFF));

         InitString ( HiiHandle,
                      STRING_TOKEN (STR_SA_RC_REV_VALUE),
                      L"%d.%d.%d.%d",
                      Offset24, Offset16, Offset08, Offset00);
      }

      // MCDECS_SPARE - MRC version
      Value32 = READ_MEM32_MCH(0x5034);
      Offset24 = (UINT8) ((Value32 & 0xFF000000) >> 24);
      Offset16 = (UINT8) ((Value32 & 0xFF0000) >> 16);
      Offset08 = (UINT8) ((Value32 & 0xFF00) >> 8);
      Offset00 = (UINT8) (Value32 & 0xFF);

      InitString ( HiiHandle,
                   STRING_TOKEN (STR_MRC_REV_VALUE),
                   L"%d.%d.%d.%d",
                   Offset24, Offset16, Offset08, Offset00);

      // Vtd Supported
      if (!(READ_PCI32_NB(R_SA_MC_CAPID0_A_OFFSET) & BIT23)) {
        InitString (
          HiiHandle,
          STRING_TOKEN (STR_SA_VTD_VALUE),
          L"Supported"
          );
      }

      UpdatePegInfo(HiiHandle, Class);
      UpdateDmiInfo(HiiHandle, Class);
#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 0
      UpdateDDRXmpInfo(HiiHandle, Class);
#endif



      //
      // Check IGFX device
      //

      if ((READ_PCI8_NB(R_SA_DEVEN) & B_SA_DEVEN_D2EN_MASK)) {
        // 
        // IGFX enable
        // 
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
        if (!LegacyBiosProtocol) {
          Status      = pBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, (void **) &LegacyBiosProtocol);
          if (!EFI_ERROR(Status)) {
          
             RegSet.X.AX = 0x5f01;
             Status      = LegacyBiosProtocol->Int86 (LegacyBiosProtocol, 0x15, &RegSet);
             ASSERT_EFI_ERROR (Status);

             //
             // HEX2Ascii
             //
             RevisionHigh  = (UINT8) (((RegSet.X.DX & 0x0F00) >> 4) | (RegSet.X.DX & 0x000F));
             RevisionLow   = (UINT8) (((RegSet.X.BX & 0x0F00) >> 4) | (RegSet.X.BX & 0x000F));

             InitString (
                     HiiHandle,
                     STRING_TOKEN (STR_CHIP_IGFX_VBIOS_REV_VALUE),
                     L"%02X%02X",
                     RevisionHigh,
                     RevisionLow
             );
           }
        }
#endif

        //
        // Get MCHBAR to read the IGFX temperature
        //
        MchBAR = *(volatile UINT64 *) NB_PCIE_CFG_ADDRESS (0, 0, 0, 0x48) &~(BIT0);

        //
        // Read RP0 (Max) Frequency supported, RP0 ratio is in 100MHz units 
        //
        IGfxFreq = (((READ_MEM32_MCH(0x5998) >> 8) & 0xFF) * 100);

        InitString (
          HiiHandle,
          STRING_TOKEN (STR_IGFX_FREQ_VALUE),
          L"%d MHz",
          IGfxFreq
        );

        NbDeviceData = READ_PCI8_IGD(R_SA_PEG_DID_OFFSET);
 
        GtTypeAndValue = NbDeviceData & 0xf0; 
      
        if (GtTypeAndValue == 0x20) {
          GtSkuType = 3;
        } else if (GtTypeAndValue == 0x10) {
          GtSkuType = 2;
        } else if (GtTypeAndValue == 0x00){
          GtSkuType = 1;
        }      

        // Display GT Type with RP0 Frequency Information
        InitString (
          HiiHandle,
          STRING_TOKEN (STR_PROCESSOR_GT_VALUE),
          L"%a%x (%d MHz)",
          "GT",
          GtSkuType,
          IGfxFreq
          );

      }

   } //(Class == CHIPSET_FORM_SET_CLASS)
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UpdatePegInfo
//
// Description: Update PCIE Info
//
// Input:       HiiHandle - Handle to HII database
//              Class - Indicates the setup class
//
// Output:      None
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UpdatePegInfo (
  IN    EFI_HII_HANDLE     HiiHandle,
  IN    UINT16             Class
  )
{
  UINT16                Data16;
  UINT8                 Index;
  UINT8                 PegDeviceNumber;
  UINT8                 PegFunctionNumber;

  Data16 = 0;

  for (Index = 0; Index < 3; Index++) {

    PegDeviceNumber   = SA_PEG10_DEV_NUM;
    PegFunctionNumber = Index;

    //
    // Check for DID VID to check Root Port is present
    //
    Data16 = *(volatile UINT16 *) NB_PCIE_CFG_ADDRESS (SA_PEG_BUS_NUM, PegDeviceNumber, PegFunctionNumber, 0x0);

    if (Data16 != 0xFFFF) {
      //
      // Read Slot Status register
      //
      Data16 = *(volatile UINT16 *) NB_PCIE_CFG_ADDRESS (SA_PEG_BUS_NUM, PegDeviceNumber, PegFunctionNumber, R_SA_PEG_SLOTSTS_OFFSET);

      //
      // Check for Presence Detect State SlotStatus 0xba[6]
      //
      if (Data16 & 0x40) {
        //
        // Read LinkStatus 0xb2[3-0]-Current Link Speed, [9-4]-Negotiated Link Width.
        //
        Data16 = *(volatile UINT16 *) NB_PCIE_CFG_ADDRESS (SA_PEG_BUS_NUM, PegDeviceNumber, PegFunctionNumber,  R_SA_PEG_LSTS_OFFSET);

        InitString (
          HiiHandle,
          PegInfo[Index],
          L"x%d  Gen%1d",
          (Shr64((Data16 & 0x3f0), 4)),
          (Data16 & 0xf)
          );

      }
    }
  }
  //
  // for loop
  //

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UpdateDmiInfo
//
// Description: Update NB DMI Info
//
// Input:       HiiHandle - Handle to HII database
//              Class - Indicates the setup class
//
// Output:      None
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateDmiInfo (
  IN    EFI_HII_HANDLE    HiiHandle,
  IN    UINT16            Class
  )
{
  UINT16        Data16;
  UINT32        Data32;
  UINT64        DmiBar;

  // Get DMIBAR
  DmiBar = (UINT64)READ_PCI32_NB(0x68) & ~BIT0; //DMI BAR
 
  // LCAP 3:0 - Max Link Speed, Gen2/Gen1 Infomation
  Data32 = READ_MEM32(DmiBar + 0x8a);
  
  // LSTS 9:4 - DMI Link Negotiated Width
  Data16 = READ_MEM16(DmiBar + 0x8a);

  InitString (
    HiiHandle,
    STRING_TOKEN(STR_DMI_INFO_VALUE),
    L"X%d  Gen%1d",
    ((Data16 >> 4) & 0xf),
    (Data32 & 0xf)
   );
}

EFI_STATUS
EFIAPI
NB_SETUP_CALLBACK (
    IN EFI_HII_HANDLE HiiHandle, 
    IN UINT16         Class, 
    IN UINT16         SubClass, 
    IN UINT16         Key
)
{
        SETUP_DATA      *SetupData = NULL;
        CALLBACK_PARAMETERS *pCallbackData = NULL;
        EFI_STATUS               Status = EFI_SUCCESS;
#if EFI_SPECIFICATION_VERSION > 0x20000
        UINTN           BufferSize= sizeof(SETUP_DATA);
        EFI_GUID        SetupGuid = SETUP_GUID;
#else
        UINT8 *pNvRamMap;
#endif

        pCallbackData = GetCallbackParameters();
        if(pCallbackData == NULL) return Status;      

#if ((TSE_BUILD >= 0x1224) && (EFI_SPECIFICATION_VERSION >= 0x2000A))
        if (pCallbackData->Action != EFI_BROWSER_ACTION_CHANGED)
           return Status;
#elif ((TSE_BUILD > 0x1208) && (EFI_SPECIFICATION_VERSION >= 0x2000A))
        // Check callback action
        if (pCallbackData->Action != EFI_BROWSER_ACTION_CHANGING)
           return Status;
#endif

#if EFI_SPECIFICATION_VERSION > 0x20000
        Status = pBS->AllocatePool(EfiBootServicesData, BufferSize, &SetupData);
        if(EFI_ERROR(Status)) return Status;

        Status = HiiLibGetBrowserData(
                &BufferSize, SetupData,
                &SetupGuid,  L"Setup"
        );
        ASSERT_EFI_ERROR(Status);
#else   
        pNvRamMap = pCallbackData->Data->NvRamMap;
        SetupData = (SETUP_DATA*)pNvRamMap;
#endif

        switch (Key) 
        {
            case NB_CRID_KEY:
               SetupData->PchEnableCrid = SetupData->EnableNbCrid;
               break; 
        }

#if EFI_SPECIFICATION_VERSION > 0x20000
        Status = HiiLibSetBrowserData(
                BufferSize, SetupData,
                &SetupGuid,  L"Setup"
        );
        ASSERT_EFI_ERROR(Status);    

        pBS->FreePool(SetupData);
#endif;

        return EFI_SUCCESS;
}


#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 0
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UpdateDDRXmpInfo
//
// Description: Update DDR XMP Info
//
// Input:       HiiHandle - Handle to HII database
//              Class - Indicates the setup class
//
// Output:      None
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID UpdateDDRXmpInfo (
    IN EFI_HII_HANDLE   HiiHandle,
    IN UINT16           Class )
{
   UINTN               VariableSize;
   NB_PLATFORM_DATA    NBPlatformData = {0};
   EFI_GUID            SetupGuid = SETUP_GUID;
   EFI_STATUS          Status;

   // Read the NB Platform Data
   VariableSize = sizeof (NB_PLATFORM_DATA);
   Status = pRS->GetVariable (
             L"NBPlatformData",
             &SetupGuid,
             NULL,
             &VariableSize,
             &NBPlatformData
             );

   if (!EFI_ERROR (Status)) {
      if (NBPlatformData.XmpProfile1) {
           gMaxXmpProfiles = 2;
           InitString(
             HiiHandle,
             STRING_TOKEN(STR_XMP_PROFILE_1_VALUE),
             L"%a",
             "Supported"
             );

       }

       if (NBPlatformData.XmpProfile2) {
           gMaxXmpProfiles = 3;
           InitString(
             HiiHandle,
             STRING_TOKEN(STR_XMP_PROFILE_2_VALUE),
             L"%a",
             "Supported"
             );
       }
   }
}

EFI_STATUS
EFIAPI
NB_MEMORY_TUNING_CALLBACK (
    IN EFI_HII_HANDLE HiiHandle, 
    IN UINT16         Class, 
    IN UINT16         SubClass, 
    IN UINT16         Key
)
{
        SETUP_DATA      *SetupData = NULL;
        CALLBACK_PARAMETERS *pCallbackData = NULL;
        EFI_STATUS               Status = EFI_SUCCESS;
#if EFI_SPECIFICATION_VERSION > 0x20000
        UINTN           BufferSize= sizeof(SETUP_DATA);
        EFI_GUID        SetupGuid = SETUP_GUID;
#else
        UINT8 *pNvRamMap;
#endif

        pCallbackData = GetCallbackParameters();
        if(pCallbackData == NULL) return Status;      

#if ((TSE_BUILD >= 0x1243) && (EFI_SPECIFICATION_VERSION >= 0x2000A))   // [ EIP200606 ]
        if (pCallbackData->Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD)
           return EFI_UNSUPPORTED;
#endif

#if ((TSE_BUILD >= 0x1224) && (EFI_SPECIFICATION_VERSION >= 0x2000A))
        if (pCallbackData->Action != EFI_BROWSER_ACTION_CHANGED)
           return Status;
#elif ((TSE_BUILD > 0x1208) && (EFI_SPECIFICATION_VERSION >= 0x2000A))
        // Check callback action
        if (pCallbackData->Action != EFI_BROWSER_ACTION_CHANGING)
           return Status;
#endif

#if EFI_SPECIFICATION_VERSION > 0x20000
        Status = pBS->AllocatePool(EfiBootServicesData, BufferSize, &SetupData);
        if(EFI_ERROR(Status)) return Status;

        Status = HiiLibGetBrowserData(
                &BufferSize, SetupData,
                &SetupGuid,  L"Setup"
        );
        ASSERT_EFI_ERROR(Status);
#else   
        pNvRamMap = pCallbackData->Data->NvRamMap;
        SetupData = (SETUP_DATA*)pNvRamMap;
#endif

        switch (Key) 
        {
            case Default_SPD:
            case Custom_SPD:
            case XMP_SPD1:
            case XMP_SPD2:
                if (SetupData->SpdProfileSelected >= gMaxXmpProfiles &&\
                    SetupData->SpdProfileSelected != 1) 
                    SetupData->SpdProfileSelected = gMaxXmpProfiles;
            break;

            case NB_tCL_KEY:
                if (SetupData->tCL > tCL_MAXIMUM) SetupData->tCL = tCL_MAXIMUM;
                if (SetupData->tCL < tCL_MINIMUM) SetupData->tCL = tCL_MINIMUM;
            break;

            case NB_tRP_KEY:
                if (SetupData->tRP > tRP_MAXIMUM) SetupData->tRP = tRP_MAXIMUM;
                if (SetupData->tRP < tRP_MINIMUM) SetupData->tRP = tRP_MINIMUM;
            break;

            case NB_tRCD_KEY:
                if (SetupData->tRCD > tRCD_MAXIMUM) SetupData->tRCD = tRCD_MAXIMUM;
                if (SetupData->tRCD < tRCD_MINIMUM) SetupData->tRCD = tRCD_MINIMUM;
            break;

            case NB_tRAS_KEY:
                if (SetupData->tRAS > tRAS_MAXIMUM) SetupData->tRAS = tRAS_MAXIMUM;
                if (SetupData->tRAS < tRAS_MINIMUM) SetupData->tRAS = tRAS_MINIMUM;
            break;

            case NB_tWR_KEY:
                if (SetupData->tWR > tWR_MAXIMUM) SetupData->tWR = tWR_MAXIMUM;
                if (SetupData->tWR < tWR_MINIMUM) SetupData->tWR = tWR_MINIMUM;
            break;

            case NB_tRFC_KEY:
                if (SetupData->tRFC > tRFC_MAXIMUM) SetupData->tRFC = tRFC_MAXIMUM;
                if (SetupData->tRFC < tRFC_MINIMUM) SetupData->tRFC = tRFC_MINIMUM;
            break;

            case NB_tWTR_KEY:
                if (SetupData->tWTR > tWTR_MAXIMUM) SetupData->tWTR = tWTR_MAXIMUM;
                if (SetupData->tWTR < tWTR_MINIMUM) SetupData->tWTR = tWTR_MINIMUM;
            break;

            case NB_tRRD_KEY:
                if (SetupData->tRRD > tRRD_MAXIMUM) SetupData->tRRD = tRRD_MAXIMUM;
                if (SetupData->tRRD < tRRD_MINIMUM) SetupData->tRRD = tRRD_MINIMUM;
            break;

            case NB_tRTP_KEY:
                if (SetupData->tRTP > tRTP_MAXIMUM) SetupData->tRTP = tRTP_MAXIMUM;
                if (SetupData->tRTP < tRTP_MINIMUM) SetupData->tRTP = tRTP_MINIMUM;
            break;

            case NB_tFAW_KEY:
                if (SetupData->tFAW > tFAW_MAXIMUM) SetupData->tFAW = tFAW_MAXIMUM;
                if (SetupData->tFAW < tFAW_MINIMUM) SetupData->tFAW = tFAW_MINIMUM;
            break;

            case NB_tRC_KEY:
               if (SetupData->tRC > tRC_MAXIMUM) SetupData->tRC = tRC_MAXIMUM;
               if (SetupData->tRC < tRC_MINIMUM) SetupData->tRC = tRC_MINIMUM;
               break;

            case NB_tCWL_KEY:
               if (SetupData->tCWL > tCWL_MAXIMUM) SetupData->tCWL = tCWL_MAXIMUM;
               if (SetupData->tCWL < tCWL_MINIMUM) SetupData->tCWL = tCWL_MINIMUM;
               break;

            case NB_tREFI_KEY:
               if (SetupData->tREFI > tREFI_MAXIMUM) SetupData->tREFI = tREFI_MAXIMUM;
               if (SetupData->tREFI < tREFI_MINIMUM) SetupData->tREFI = tREFI_MINIMUM;
               break;

//            case NB_tRPab_KEY:
//               if (SetupData->tRPab > tRPab_MAXIMUM) SetupData->tRPab = tRPab_MAXIMUM;
//               if (SetupData->tRPab < tRPab_MINIMUM) SetupData->tRPab = tRPab_MINIMUM;
//               break;
        }

#if EFI_SPECIFICATION_VERSION > 0x20000
        Status = HiiLibSetBrowserData(
                BufferSize, SetupData,
                &SetupGuid,  L"Setup"
        );
        ASSERT_EFI_ERROR(Status);    

        pBS->FreePool(SetupData);
#endif;

        return EFI_SUCCESS;
}
#endif
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
