//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtDxe/TbtDxe.c 10    5/19/14 7:32a Barretlin $
//
// $Revision: 10 $
//
// $Date: 5/19/14 7:32a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtDxe/TbtDxe.c $
// 
// 10    5/19/14 7:32a Barretlin
// [TAG]  		EIP165410
// [Category]  	New Feature
// [Description]  	Support Thunderbolt AIC at NB PCIE slot
// [Files]  		TbtPei.c TbtDxe.c TbtGpe.asl TbtSmm.c TbtOemBoard.c
// TbtOemLib.c TbtOemLib.h TbtSetup.sdl TbtSetup.sd TbtSetup.uni
// TbtSetupReset.c
// 
// 9     5/19/14 7:11a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Using setup item choose return value of _RMV method in
// ASL code
// [Files]  		TbtDxe.c TbtGpe.asl TbtOemBoard.c TbtOemBoard.h TbtSetup.sd
// TbtSetup.sdl TbtSetup.uni
// 
// 8     2/27/14 8:38a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	when thunderbolt is disable in run time, PCIE device whcih
// using the same PCIE slot might  work abnormal
// [RootCause]  	protect thunderbolt device function still work
// [Solution]  	According thunderbolt policy to skip protect function
// [Files]  		TbtDxe.c TbtDxeLib.c
// 
// 7     1/05/14 1:43p Barretlin
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Support Thunderbolt feature Enable/Disable in run time
// Support dynamic Thunderbolt AIC location in run time
// [Files]  		TbtDxe.c TbtGpe.asl
// 
// 6     6/21/13 7:40a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix build error with non Intel RC project
// [Files]  		TbtDxe.sdl TbtDxe.c TbtGpe.asl TbtDxeLib.h
// 
// 5     6/18/13 1:41p Barretlin
// [TAG]  		EIP126581
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Follow Thunderbolt BIOS Spec rev1.0 to disable ASL code
// to call Thunderbolt SwSMI when Native PCIE is enable
// [Files]  		TbtDxe.c
// 
// 4     4/10/13 2:31p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Change reported MMIO address way in ASL code
// [Files]  		TbtDxe.c TbtGpe.asl
// 
// 3     4/10/13 1:26p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix Thunderbolt ready to boot event does not be excuted
// on ULT platform
// [Files]  		TbtDxe.c
// 
// 2     1/18/13 2:26a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Improve _RMV ASL code  for SharkBay RC
// [Files]  		TbtDxe.sdl TbtDxe.c TbtGpe.asl
// 
// 1     1/10/13 4:56a Barretlin
// Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
// Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
// 
// 11    12/12/12 3:02a Barretlin
// [TAG]  		EIP108272
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update to Spec 1.4 to support Redwood Ridge chip
// [Files]  		TbtPei.c TbtSmm.c TbtDxe.c TbtDxe.sdl TbtGpe.asl
// TbtOemBoard.c TbtOemBoard.h TbtOemLib.c TbtOemLib.h
// 
// 10    10/28/12 10:50p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Change GPIO routing for SharkBay ULT platform
// [Files]  		TbtDxe.c TbtGpe.asl TbtDxeLib.c TbtDxeLib.h TbtSmm.c
// 
// 9     10/03/12 9:15p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Change Programming security level timing for saving
// boot time
// [Files]  		TbtPei.c TbtDxe.c TbtOemBoard.c TbtOemBoard.h
// TbtOemBoard.sdl TbtOemLib.c TbtOemLib.h
// 
// 8     7/31/12 2:52a Barretlin
// [TAG]  		EIP96350
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change ACPI method from level trigger to edge
// trigger(_L1x to _E1x)
// [Files]  		TbtDxe.c
// 
// 7     7/31/12 2:46a Barretlin
// [TAG]  		EIP91119
// [Category]  	Improvement
// [Description]  	Resolution for enable/disable Thunderbolt device option
// rom at POST time
// [Files]  		TbtDxe.c
// 
// 6     7/25/12 11:58p Barretlin
// [TAG]  		EIP90644
// [Category]  	Improvement
// [Description]  	Change pre-boot event timing from ready to boot to pci
// bus finish assigning resources
// [Files]  		TbtDxe.sdl TbtDxe.c TbtDxeLib.c TbtDxeLib.h
// 
// 5     5/21/12 2:21a Barretlin
// [TAG]  		EIP90003
// [Category]  	Improvement
// [Description]  	If TBT devices with option rom enabled, system maybe
// cannot boot to OS.
// [Files]  		TbtDxe.c TbtSmm.c TbtOemBoard.sdl
// 
// 4     5/07/12 6:34a Barretlin
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add three setup items for debug
// [Files]  		TbtDxe.c
// TbtGpe.asl
// TbtSmm.c
// TbtSetup.sd
// TbtSetup.uni
// TbtOemBoard.c
// TbtOemBoard.h
// 
// 3     4/14/12 4:50a Barretlin
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Improve ASL code, which redefines device name and RMV
// mothod at same address when project supports RMV method, that might
// cause conflict.
// [Files]  		TbtDxe.c  TbtGpe.asl
// 
// 2     2/20/12 12:15a Wesleychen
//  - Add ProgramTbtSecurityLevel().
//  - Add a ready to boot event to invoke SW SMI for resource adjust.
//  - Revise the ACPI table update routine become a protocol callback
// routine.
// 
// 1     12/08/11 4:09a Wesleychen
// Thunderbolt eModule initially releases.
// 
//*************************************************************************
#include <Efi.h>
#include <token.h>
#include <Setup.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <PciBus.h>
#include <Acpi20.h>
#include <Protocol\AcpiSupport.h>
#include <TbtOemBoard.h>

#if ACPI_SUPPORT
 #if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x00010014)
 #include <Protocol\AcpiSystemDescriptionTable.h>
 #else
 #include <Protocol\AcpiSupport.h>
 #endif
#endif
#if CSM_SUPPORT
#include <Protocol\CsmPlatform.h>
#endif
#ifndef EFI_SIGNATURE_16
#define EFI_SIGNATURE_16(A, B)  ((A) | (B << 8))
#endif

#ifndef EFI_SIGNATURE_32
#define EFI_SIGNATURE_32(A, B, C, D)  (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))
#endif

EFI_GUID   gOemTbtProtocolGuid = AMI_TBT_PLATFROM_POLICY_PROTOCOL_GUID;
EFI_GUID   TbtHRStatusGuid     = AMI_TBT_HR_STATUS_GUID;
EFI_GUID   gTbtHobGuid         = AMI_TBT_HOB_GUID;
EFI_GUID   HobListGuid         = HOB_LIST_GUID;
EFI_GUID   SetupGuid           = SETUP_GUID;
#ifdef CSM_OPRROM_POLICY_GUID
EFI_GUID   gCsmOpromPolicyGuid = CSM_OPRROM_POLICY_GUID;
#endif

AMI_TBT_PLATFORM_POLICY_PROTOCOL  *gAmiTbtPlatformPolicy = NULL;

typedef struct {
  UINT32  Signature;
  UINT32  Length;
} EFI_ACPI_COMMON_HEADER;

EFI_EVENT             mAcpiEvent;
//VOID                  *mAcpiReg;
VOID                  *CsmOpromPolicyRegs;
static EFI_BOOT_MODE  BootMode;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   DsdtTableUpdate
//
// Description: Update the DSDT table
//
// Input:       DsdtTable   - The table points to DSDT table.
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
DsdtTableUpdate (
  IN ACPI_HDR   *DsdtTable
  )
{
    UINT8   *CurrPtr;
    UINT8   *DsdtPointer;
    UINT32  *Signature = NULL;
    UINT8   DoneFlag = 0;
    UINT8   TbtAslStartPoint = 0;
    UINT8   HexStr[36] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H',\
                          'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    CurrPtr = (UINT8 *) DsdtTable;
    if (gAmiTbtPlatformPolicy != NULL && (!(gAmiTbtPlatformPolicy->TbtAICSupport))) {
        TRACE((-1, "TbtDxe: Updating DSDT table for Thunderbolt\n"));
        
        for (DsdtPointer = CurrPtr;
             DsdtPointer <= (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length);
             DsdtPointer++ )
        {
            Signature = (UINT32 *) DsdtPointer;
            
            if (*Signature == EFI_SIGNATURE_32 ('O', 'E', '1', 'X')) {
                *DsdtPointer = '_';
                // BIOS support of Thunderbolt devices Specification Update
                // Revision 1.00
                // Change ACPI method from level trigger to edge trigger(_L1x to _E1x)
      #if defined ULT_SUPPORT && ULT_SUPPORT == 1
                if(IsULTPchSeries()){
                    *(DsdtPointer + 2) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt/16];
                    *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt%16];
                } else {
                    *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt];
                }
      #else  
                *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt];
      #endif
            
                DoneFlag = DoneFlag | 0x0f;
                TRACE((-1, "TbtDxe: Update Thunderbolt GPE event method\n"));
            } // GPE event

            if(DoneFlag == 0x0F)  return;
        } //for loop
    }// !(gAmiTbtPlatformPolicy->TbtAICSupport)
    
    if (gAmiTbtPlatformPolicy != NULL && gAmiTbtPlatformPolicy->TbtAICSupport) {
        TRACE((-1, "TbtDxe: Updating DSDT table for Thunderbolt AIC\n"));

        for (DsdtPointer = CurrPtr;
             DsdtPointer <= (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length);
             DsdtPointer++ )
        {
            Signature = (UINT32 *) DsdtPointer;
            switch(*Signature){
                case (EFI_SIGNATURE_32 ('O', 'E', '1', 'X')):
                    *DsdtPointer = '_';
                    // BIOS support of Thunderbolt devices Specification Update
                    // Revision 1.00
                    // Change ACPI method from level trigger to edge trigger(_L1x to _E1x)
      #if defined ULT_SUPPORT && ULT_SUPPORT == 1
                    if(IsULTPchSeries()){
                        *(DsdtPointer + 2) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt/16];
                        *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt%16];
                    } else {
                        *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt];
                    }
      #else 
                    *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt];
      #endif
                    
                    DoneFlag = DoneFlag | BIT00;
                    TRACE((-1, "TbtDxe: Update Thunderbolt GPE event method\n"));
                    break;
#if defined TBT_INTEL_RC_CONFIG && TBT_INTEL_RC_CONFIG == 1
#if defined TBT_UP_PORT_FUNC && TBT_UP_PORT_FUNC == 0
                case (EFI_SIGNATURE_32 ('R', 'P', '0', '1')):
#elif defined TBT_UP_PORT_FUNC && TBT_UP_PORT_FUNC == 1
                case (EFI_SIGNATURE_32 ('R', 'P', '0', '2')):
#elif defined TBT_UP_PORT_FUNC && TBT_UP_PORT_FUNC == 2
                case (EFI_SIGNATURE_32 ('R', 'P', '0', '3')):
#elif defined TBT_UP_PORT_FUNC && TBT_UP_PORT_FUNC == 3
                case (EFI_SIGNATURE_32 ('R', 'P', '0', '4')):
#elif defined TBT_UP_PORT_FUNC && TBT_UP_PORT_FUNC == 4
                case (EFI_SIGNATURE_32 ('R', 'P', '0', '5')):
#elif defined TBT_UP_PORT_FUNC && TBT_UP_PORT_FUNC == 5
                case (EFI_SIGNATURE_32 ('R', 'P', '0', '6')):
#elif defined TBT_UP_PORT_FUNC && TBT_UP_PORT_FUNC == 6
                case (EFI_SIGNATURE_32 ('R', 'P', '0', '7')):
#else
                case (EFI_SIGNATURE_32 ('R', 'P', '0', '8')):
#endif
#endif // TBT_INTEL_RC_CONFIG
                    if (DoneFlag){
                        if (gAmiTbtPlatformPolicy->Dev == 0x1C && \
                            gAmiTbtPlatformPolicy->Fun != TBT_UP_PORT_FUNC){
                            *(DsdtPointer + 3) = HexStr[(gAmiTbtPlatformPolicy->Fun + 1)];
                            DoneFlag++;
                            TRACE((-1, "TbtDxe: Update Thunderbolt Host ASL location to SB root port %x\n", gAmiTbtPlatformPolicy->Fun));
                        }
                        if (gAmiTbtPlatformPolicy->Bus == 0 && \
                            gAmiTbtPlatformPolicy->Dev == 1){
                            *DsdtPointer       = HexStr[25]; // 'P'
                            *(DsdtPointer + 1) = HexStr[14]; // 'E'
                            *(DsdtPointer + 2) = HexStr[16]; // 'G'
                            *(DsdtPointer + 3) = HexStr[(gAmiTbtPlatformPolicy->Fun)];
                            DoneFlag++;
                            TRACE((-1, "TbtDxe: Update Thunderbolt Host ASL location to PEG%x\n", gAmiTbtPlatformPolicy->Fun));
                        }
                    }
                    break;
                default:
                    break;
            } // switch

#if defined TBT_S3_WAK_SMI && TBT_S3_WAK_SMI == 1 && TBT_PCI0_INI_SUPPORT == 1
            if(DoneFlag == 0x06)  return;
#elif defined TBT_PCI0_INI_SUPPORT && TBT_PCI0_INI_SUPPORT == 1
            if(DoneFlag == 0x05)  return;
#else
            if(DoneFlag == 0x04)  return;
#endif
        } // for loop
    }// gAmiTbtPlatformPolicy->TbtAICSupport
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CreateTbtAcpiCallback
//
// Description: This function will create all ACPI components for SB when
//              ACPI support protocol is available.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CreateTbtAcpiCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
  UINTN                      Index;
  EFI_ACPI_SUPPORT_PROTOCOL  *As;
  FACP_20                    *Table = NULL;
  EFI_ACPI_TABLE_VERSION     Version;
  UINTN                      Handle;
  ACPI_HDR                   *DsdtPtr = NULL;
  EFI_STATUS                 Status;
  //UINT8                      SubBus;
  UINTN                      HRStatusSize = sizeof(AMI_TBT_HR_STATUS_DATA);
  AMI_TBT_HR_STATUS_DATA     HRStatusData;
  UINT8                      TbtSmiNotifyEnable;
  UINT8                      TbtBus;
  SETUP_DATA                 *SetupData;
  UINTN                      VariableSize = sizeof(SETUP_DATA);

  Status = pBS->LocateProtocol(&gEfiAcpiSupportGuid, NULL, &As);

  // Find DSDT ACPI Table
  for (Index = 0; Index < ACPI_RSDT_TABLE_NUM; Index++) {
    Status = As->GetAcpiTable(As, Index, &Table, &Version, &Handle);
    if (EFI_ERROR(Status)) break;//no more tables left    

    if ((Table->Header.Signature == FACP_SIG) && (DsdtPtr == NULL)) {
        DsdtPtr = (ACPI_HDR*)Table->DSDT;

        TRACE((-1, "TbtDxe: Found DSDT Table at 0x%08X\n", DsdtPtr));

        DsdtTableUpdate (DsdtPtr);

        // Thunderbolt BIOS Implementation guide for Redwood Ridge/Falcon Ridge 
        // based devices rev 1.0
        // 2.1.3.2 BIOS setup options for Thunderbolt
        // Switch between Native PCIe Enable and Disabled with the following settings:
        // --------------------------------------------------------------------
        // Native PCIe support disabled (default) | Native PCIe support enabled
        // --------------------------------------------------------------------
        //           SCI Call Enabled             |      SCI Call Enabled
        // --------------------------------------------------------------------
        //           SMI Call Enabled             |      SMI Call Disabled
        // --------------------------------------------------------------------
        //          Notify Call Enabled           |      Notify Call Enabled
        // --------------------------------------------------------------------
        Status = pBS->AllocatePool( EfiBootServicesData,
                              VariableSize,
                              &SetupData );
        ASSERT_EFI_ERROR(Status);
        
        Status = pRS->GetVariable( L"Setup", \
                                   &SetupGuid, \
                                   NULL, \
                                   &VariableSize, \
                                   SetupData );
        ASSERT_EFI_ERROR (Status);

#if defined TBT_INTEL_RC_CONFIG && TBT_INTEL_RC_CONFIG == 1
        if (SetupData->PciExpNative){
            TbtSmiNotifyEnable = gAmiTbtPlatformPolicy->NotifyEnabled << 1;
        } else {
            TbtSmiNotifyEnable = gAmiTbtPlatformPolicy->SwSmiEnabled | (gAmiTbtPlatformPolicy->NotifyEnabled << 1);
        }
#else
        // For non Intel RC project
        TbtSmiNotifyEnable = gAmiTbtPlatformPolicy->SwSmiEnabled | (gAmiTbtPlatformPolicy->NotifyEnabled << 1);
#endif
        Status = UpdateAslNameObject(DsdtPtr, "TSNE", TbtSmiNotifyEnable);
        TRACE((-1, "TbtDxe: Updating TSNE Name Object %r\n", Status));
        ASSERT_EFI_ERROR(Status);
        pBS->FreePool(SetupData);

        //Update System MMIO PCIE Base address
        //TRACE((-1, "TbtDxe: Update TBT Host DownStream port MMIO Base address in ASL code\n"));
        //SubBus = READ_PCI8(gAmiTbtPlatformPolicy->Bus, gAmiTbtPlatformPolicy->Dev, gAmiTbtPlatformPolicy->Fun, PCI_PBUS+1);
        //Status = UpdateAslNameObject(DsdtPtr, "PEMA", (PCIEX_BASE_ADDRESS | (SubBus << 20)));
        //TRACE((-1, "TbtDxe: Updating PEMA Name Object %r\n", Status));
        //ASSERT_EFI_ERROR(Status);

        //Update TBT Host location bus in ASL code
        if (gAmiTbtPlatformPolicy->TbtAICSupport){
            if (gAmiTbtPlatformPolicy->Bus == 0 && gAmiTbtPlatformPolicy->Dev == 0x1c){
                Status = UpdateAslNameObject(DsdtPtr, "TBRP", (gAmiTbtPlatformPolicy->Fun + 1));
                TRACE((-1, "TbtDxe: Updating TBRP Name Object %r\n", Status));
                ASSERT_EFI_ERROR(Status);
            } else if (gAmiTbtPlatformPolicy->Bus == 0 && gAmiTbtPlatformPolicy->Dev == 1){
                Status = UpdateAslNameObject(DsdtPtr, "TBRP", (gAmiTbtPlatformPolicy->Fun + 0x20));
                TRACE((-1, "TbtDxe: Updating TBRP Name Object %r\n", Status));
                ASSERT_EFI_ERROR(Status);
            }
        }
        TbtBus = MMIO_READ8(TBT_CFG_ADDRESS(gAmiTbtPlatformPolicy->Bus, gAmiTbtPlatformPolicy->Dev, gAmiTbtPlatformPolicy->Fun, PCI_SBUS));
        Status = UpdateAslNameObject(DsdtPtr, "TBUS", TbtBus);
        TRACE((-1, "TbtDxe: Updating TBUS Name Object %r\n", Status));
        ASSERT_EFI_ERROR(Status);
        
        //Update TBT Host Information in ASL code
        TRACE((-1, "TbtDxe: Update TBT Host Information in ASL code\n"));
        Status = pRS->GetVariable( L"TbtHRStatusVar", \
                                   &TbtHRStatusGuid, \
                                   NULL, \
                                   &HRStatusSize, \
                                   &HRStatusData );
        if (!EFI_ERROR(Status)){
            Status = UpdateAslNameObject(DsdtPtr, "TBHR", HRStatusData.TbtHRSeries);
            TRACE((-1, "TbtDxe: Updating TBHR Name Object %r\n", Status));
            ASSERT_EFI_ERROR(Status);
        }
        
        // Update _RMV method return value for Thunderbolt
        Status = UpdateAslNameObject( DsdtPtr, "TBMV", gAmiTbtPlatformPolicy->TbtRmvReturnValue);
        TRACE((-1, "TbtDxe: Update TRMV ASL object value = %x, %r\n", gAmiTbtPlatformPolicy->TbtRmvReturnValue, Status));
        ASSERT_EFI_ERROR(Status);

        break;
    }
  }
  // Kill the Event
  pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   DisableTbtDeviceRomCallback
//
// Description: Disable all Tbt devices option ROM to aviod S4 resume problem.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DisableTbtDeviceRomCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context )
{
  EFI_STATUS                  Status;
  EFI_HANDLE                  Handle;
  UINTN                       Size = sizeof(EFI_HANDLE);
  CSM_PLATFORM_POLICY_DATA    *CsmOpromPolicyData;
  EFI_PCI_IO_PROTOCOL         *PciIo;
  PCI_DEV_INFO                *Device;

  TRACE((-1, "TbtDxe: DisableTbtDeviceRomCallback() Entry\n"));

  Status = pBS->LocateHandle(ByRegisterNotify, NULL, CsmOpromPolicyRegs, &Size, &Handle);
  if (EFI_ERROR(Status)) return;

  Status = pBS->HandleProtocol(Handle, &gCsmOpromPolicyGuid, &CsmOpromPolicyData);
  if (EFI_ERROR(Status)) return;

  if(CsmOpromPolicyData == NULL) return; //post-process OpROM callback
  if(CsmOpromPolicyData->PciIo == NULL) return; // OEM Service ROM

  PciIo = CsmOpromPolicyData->PciIo;
  Device = (PCI_DEV_INFO*)PciIo;
  while ((Device->Type != tPciRootBrg) && (Device->ParentBrg != NULL)) {
    Device = Device->ParentBrg;
    if (Device->Address.Addr.Bus != gAmiTbtPlatformPolicy->Bus) continue;
    if (Device->Address.Addr.Device != gAmiTbtPlatformPolicy->Dev) continue;
    if (Device->Address.Addr.Function != gAmiTbtPlatformPolicy->Fun) continue;
    if (gAmiTbtPlatformPolicy->TbtOptionRom || (BootMode & BOOT_ON_S4_RESUME)){
       CsmOpromPolicyData->ExecuteThisRom = FALSE;  //this attritube default is TRUE
       TRACE((-1, "TbtDxe: ExecuteThisRom is setted FALSE.\n"));
    }

    break;
  }

  TRACE((-1, "TbtDxe: DisableTbtDeviceRomCallback() Exit\n"));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InvokeSmiHandlerBeforeBoot
//
// Description: To invoke SW SMI befor boot for reaource adjust.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InvokeSmiHandlerBeforeBoot (
  IN EFI_EVENT    Event,
  IN VOID         *Context )
{
  TbtDxeInvokeSmiHandler();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TbtDxe_Init
//
// Description: This function is the entry point for this DXE.
//
// Input:       ImageHandle - Image handle
//              SystemTable - Pointer to the system table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TbtDxe_Init (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS                 Status;
    EFI_EVENT                  CsmOpromPolicyEvent = NULL;
    TBT_HOB                    *gTbtHob;

    InitAmiLib(ImageHandle, SystemTable);
    TRACE((-1, "TbtDxe: TbtDxe_Init() Entry!!\n"));

    Status = pBS->LocateProtocol( \
                    &gOemTbtProtocolGuid, \
                    NULL, \
                    &gAmiTbtPlatformPolicy);
    if (!EFI_ERROR(Status)) {
        BootMode = GetBootMode();
        if (gAmiTbtPlatformPolicy->TbtEnable){
#ifdef CSM_OPRROM_POLICY_GUID
            Status = RegisterProtocolCallback (&gCsmOpromPolicyGuid,
                                               DisableTbtDeviceRomCallback,
                                               NULL, &CsmOpromPolicyEvent,
                                               &CsmOpromPolicyRegs);
#endif
            if (gAmiTbtPlatformPolicy->SmiNotifyEnabled) {
#if (ACPI_SUPPORT)
                Status = CreateReadyToBootEvent( TPL_NOTIFY,
                                                 CreateTbtAcpiCallback,
                                                 NULL,
                                                 &mAcpiEvent);
#endif       
            } // SmiNotifyEnabled
            
            gTbtHob = (TBT_HOB *)GetEfiConfigurationTable(SystemTable, &HobListGuid);
            if (gTbtHob){
                Status = FindNextHobByGuid((EFI_GUID*)&gTbtHobGuid, &gTbtHob);
                if (!(EFI_ERROR(Status)) && gTbtHob->TbtSecurityLevelFlag){
                    TRACE((-1, "TbtDxe: Need Finish final programming !!!\n"));
                    FinialProgramTbtSecurityLevel(gAmiTbtPlatformPolicy);
                }
            } // gTbtHob
            else TRACE((-1, "TbtDxe: Can not find Thunderbolt Hob !!!\n"));
        }// TbtEnable
    }// gAmiTbtPlatformPolicy success
    TRACE((-1, "TbtDxe: TbtDxe_Init() Exit!!\n"));

    return EFI_SUCCESS;
}


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
