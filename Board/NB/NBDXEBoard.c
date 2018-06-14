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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NBDXEBoard.c 7     5/13/14 10:37p Dennisliu $
//
// $Revision: 7 $
//
// $Date: 5/13/14 10:37p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NBDXEBoard.c $
// 
// 7     5/13/14 10:37p Dennisliu
// [TAG]           EIP167027
// [Category]      Improvement
// [Description]   [SharkBay Aptio4]Variable's attribute needs to be
// reviewed by SA component driver
// [Files]         NBDXEBoard.c; IntelSaGopSetup.c; IntelSaGopPolicy.c;
// NBDxe.c; NbPciCSP.c; PciHostBridge.c;
//
// 6     6/28/13 7:55a Jeffch
//  [TAG]          None
//  [Severity]     Bug Fix
//  [Description]  Fix Boot to OS will BSOD when disable
// SwitchableGraphics_SUPPORT.
//  [Symptom]      update asl name XBAS in NBDXEBoard.c.
//  [RootCause]    RC will not update asl name XBAS when disable
// SwitchableGraphics_SUPPORT.
//  [Files]        NBDxeBoard.c
//
// 5     1/28/13 3:46a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 1.0.
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c;
//                  NB.sd; NB.uni; NBDxeBoard.c
//
// 4     12/14/12 4:51a Jeffch
// [TAG]          EIP106709
// [Severity]     Important
// [Description]  Support PCIE Primary display.
// [Files]        NB.sd; NBDXEboard.c; NB.uni;
// GetSetupData.c;NbSetupData.h;
//
// 3     10/30/12 7:17a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update SA RC 0.72.
// [Files]        NB.sdl; NBDXEboard.c
//
// 2     10/14/12 12:42a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update by XTU4.0.
// [Files]        NB.h, GetSetupData.c, NbSetupData.h
// [TAG]          None
// [Severity]     Important
// [Description]  Follow Update by Mahobay.
// [Files]        NB.sdl, NB.mak.c; NBDXEBoard.c
//
// 1     2/08/12 4:33a Yurenlai
// Intel Haswell/NB eChipset initially releases.
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NBDXEBoard.C
//
// Description: This file contains DXE stage board component code for
//              Template NB
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Efi.h>
#include <Pei.h>
#include <token.h>
#include <Setup.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\NBMemInfo.h>
#include <Protocol\MpService.h>

#if SMBIOS_SUPPORT
#include <Protocol\SmbiosDynamicData.h>
#endif

#if CSM_SUPPORT
#include <Protocol\CsmPlatform.h>
#include <Protocol\LegacyBiosPlatform.h>
#endif
#define _SA_COMMON_DEFINITIONS_H_
#include <Protocol\SaPlatformPolicy\SaPlatformPolicy.h>
#include <SaGlobalNvsArea\SaGlobalNvsArea.h>
//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)


// Type Definition(s)

// Function Prototype(s)

// Protocols that are installed

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)
EFI_GUID gSaGlobalNvsAreaProtocolGuid    = SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL_GUID;
EFI_GUID mDxePlatformSaPolicyGuid = DXE_PLATFORM_SA_POLICY_GUID;
// Protocol Definition(s)
SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL    *gSaGlobalNvsArea;
DXE_PLATFORM_SA_POLICY_PROTOCOL          mDxePlatformSaPolicy;
// External Declaration(s)
NB_SETUP_DATA *gNbSetupData;
// Function Definition(s)
VOID NbSaGlobalNvsAreaNotify (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);
//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBDXE_BoardInit
//
// Description: This function initializes the board specific component in
//              in the chipset north bridge
//
// Input:       ImageHandle Image handle
//              SystemTable Pointer to the system table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBDXE_BoardInit (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable,
    IN NB_SETUP_DATA        *SetupData )
{
    EFI_STATUS         Status = EFI_SUCCESS;
    EFI_EVENT           NbSaGlobalNvsAreaEvent;
    VOID                *NbSaGlobalNvsAreaReg;

    InitAmiLib(ImageHandle, SystemTable);

    gNbSetupData = SetupData;

    //NbSetupdata Pass to SaGlobalNvsArea.
    Status = pBS->CreateEvent (
                    EFI_EVENT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    NbSaGlobalNvsAreaNotify,
                    NULL,
                    &NbSaGlobalNvsAreaEvent
                    );

    if (!EFI_ERROR (Status)) {
      Status = pBS->RegisterProtocolNotify (
                      &gSaGlobalNvsAreaProtocolGuid,
                      NbSaGlobalNvsAreaEvent,
                      &NbSaGlobalNvsAreaReg
                      );
    }


    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbSaGlobalNvsAreaNotify
//
// Description: This callback function is called when a SaGlobalNvsArea Protocol is
//              installed.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbSaGlobalNvsAreaNotify (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
  EFI_STATUS         Status = EFI_SUCCESS;

  ///
  ///  Locate the SA Global NVS Protocol.
  ///
  Status = pBS->LocateProtocol (
                  &gSaGlobalNvsAreaProtocolGuid,
                  NULL,
                  (VOID **) &gSaGlobalNvsArea
                  );
  if (!(EFI_ERROR (Status)))
  {

    ///
    /// Get the platform setup policy.
    ///
    Status = pBS->LocateProtocol (&mDxePlatformSaPolicyGuid, NULL, (VOID **) &mDxePlatformSaPolicy);
    ASSERT_EFI_ERROR (Status);

    gSaGlobalNvsArea->Area->IgdBootType                 = gNbSetupData->IgdBootType;
    gSaGlobalNvsArea->Area->IgdPanelType                = gNbSetupData->LcdPanelType;
    gSaGlobalNvsArea->Area->IgdPanelScaling             = gNbSetupData->LcdPanelScaling;
    gSaGlobalNvsArea->Area->IgdSciSmiMode               = 0;   // 0=Enable, 1= Disabled
//-    gSaGlobalNvsArea->Area->IgdTvFormat                 = NbSetupData->IgdTV1Standard;
//-    gSaGlobalNvsArea->Area->IgdTvMinor                  = NbSetupData->IgdTV2Standard;
    gSaGlobalNvsArea->Area->IgdSscConfig                = gNbSetupData->IgdLcdSSCC;
    gSaGlobalNvsArea->Area->IgdBiaConfig                = gNbSetupData->IgdLcdIBia;

    gSaGlobalNvsArea->Area->BacklightControlSupport     = gNbSetupData->IgdLcdBlc;
    gSaGlobalNvsArea->Area->AlsEnable                   = gNbSetupData->AlsEnable;
    gSaGlobalNvsArea->Area->IgdDvmtMemSize              = gNbSetupData->IgdDvmt50TotalAlloc;
    gSaGlobalNvsArea->Area->GfxTurboIMON                = gNbSetupData->GfxTurboIMON;

    // Get SFF power mode platform data for the IGD driver.  Flip the bit (bitwise xor)
    // since Setup value is opposite of NVS and IGD OpRegion value.
    gSaGlobalNvsArea->Area->IgdPowerConservation        = gNbSetupData->LowPowerMode ^ BIT0;
    gSaGlobalNvsArea->Area->XPcieCfgBaseAddress         = (UINT32)NB_PCIE_CFG_ADDRESS (0, 0, 0, 0);

    //
    // Give the full brightness as the initial value
    //
    gSaGlobalNvsArea->Area->BrightnessPercentage        = 100;

    if(gNbSetupData->AlsEnable) {
      if (gSaGlobalNvsArea->Area->IgdBiaConfig == 0) {
        //
        // Re-change the ALS to disable according to setup.
        //
        gSaGlobalNvsArea->Area->AlsEnable = 0;
      } else if (gSaGlobalNvsArea->Area->IgdBiaConfig < 6) {
        gSaGlobalNvsArea->Area->AlsEnable = 2;
        gSaGlobalNvsArea->Area->AlsAdjustmentFactor = gSaGlobalNvsArea->Area->IgdBiaConfig * 20;
      } else if (gSaGlobalNvsArea->Area->IgdBiaConfig == 6) {
        //
        // The default value from VBT
        //
        gSaGlobalNvsArea->Area->AlsAdjustmentFactor = 100;
        gSaGlobalNvsArea->Area->AlsEnable = 2;
      }
    }

    // Update DeviceIds
    gSaGlobalNvsArea->Area->DeviceId1                   = DeviceID1;
    gSaGlobalNvsArea->Area->DeviceId2                   = DeviceID2;
    gSaGlobalNvsArea->Area->DeviceId3                   = DeviceID3;
    gSaGlobalNvsArea->Area->DeviceId4                   = DeviceID4;
    gSaGlobalNvsArea->Area->DeviceId5                   = DeviceID5;
    gSaGlobalNvsArea->Area->DeviceId6                   = DeviceID6;
    gSaGlobalNvsArea->Area->DeviceId7                   = DeviceID7;
    gSaGlobalNvsArea->Area->DeviceId8                   = DeviceID8;
    gSaGlobalNvsArea->Area->NumberOfValidDeviceId       = ValidDeviceIDs;
    gSaGlobalNvsArea->Area->CurrentDeviceList           = 0x0f;
    gSaGlobalNvsArea->Area->PreviousDeviceList          = 0x0f;

    gSaGlobalNvsArea->Area->Peg0LtrEnable               = mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[0].LtrEnable;
    gSaGlobalNvsArea->Area->Peg0ObffEnable              = mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[0].ObffEnable;
    gSaGlobalNvsArea->Area->Peg0ObffEnable              = mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[0].ObffEnable;
    gSaGlobalNvsArea->Area->Peg1LtrEnable               = mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[1].LtrEnable;
    gSaGlobalNvsArea->Area->Peg1ObffEnable              = mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[1].ObffEnable;
    gSaGlobalNvsArea->Area->Peg2LtrEnable               = mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[2].LtrEnable;
    gSaGlobalNvsArea->Area->Peg2ObffEnable              = mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[2].ObffEnable;
    gSaGlobalNvsArea->Area->PegLtrMaxSnoopLatency       = mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[0].LtrMaxSnoopLatency;
    gSaGlobalNvsArea->Area->PegLtrMaxNoSnoopLatency     = mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[0].LtrMaxNoSnoopLatency;
    gSaGlobalNvsArea->Area->Peg0PowerDownUnusedBundles  = gNbSetupData->PowerDownUnusedBundles[0];
    gSaGlobalNvsArea->Area->Peg1PowerDownUnusedBundles  = gNbSetupData->PowerDownUnusedBundles[1];
    gSaGlobalNvsArea->Area->Peg2PowerDownUnusedBundles  = gNbSetupData->PowerDownUnusedBundles[2];
    gSaGlobalNvsArea->Area->IgdState = 1;

    // If SCI mode is disabled in setup or IGD is disabled return
    if ((READ_PCI32_IGD (0) == 0xFFFFFFFF)) {
        gSaGlobalNvsArea->Area->IgdState = 0;
    }

    gSaGlobalNvsArea->Area->LidState       = 1;

  }

  // Kill event
  pBS->CloseEvent(Event);

}

#if CSM_SUPPORT

typedef struct  {
    UINT8        PegBus;
    UINT8        PegDev;
    UINT8        PegFun;
    EFI_HANDLE   Handle;
} NB_PEG_DEVICES_STRUCT;

NB_PEG_DEVICES_STRUCT NBPegVgaList[] =
{
  {NB_BUS, PCIEBRN_DEV6, PCIEBRN_FUN,  NULL},
  {NB_BUS, PCIEBRN_DEV,  PCIEBRN_FUN,  NULL},
  {NB_BUS, PCIEBRN_DEV,  PCIEBRN_FUN1, NULL},
  {NB_BUS, PCIEBRN_DEV,  PCIEBRN_FUN2, NULL},
};
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    NBGetPlatformHandle
//
// Description: Returns a buffer of handles for the requested subfunction.
//
// Input:
//  This            Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  Mode            Specifies what handle to return.
//                      GetVgaHandle
//                      GetIdeHandle
//                      GetIsaBusHandle
//                      GetUsbHandle
//  Type            Handle Modifier - Mode specific
//  HandleBuffer    Pointer to buffer containing all Handles matching the
//                  specified criteria. Handles are sorted in priority order.
//                  Type EFI_HANDLE is defined in InstallProtocolInterface()
//                  in the EFI 1.10 Specification.
//  HandleCount     Number of handles in HandleBuffer.
//  AdditionalData  Pointer to additional data returned - mode specific..
//
// Output:
//  EFI_SUCCESS The handle is valid.
//  EFI_UNSUPPORTED Mode is not supported on this platform.
//  EFI_NOT_FOUND   The handle is not known.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
NBGetPlatformHandle (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL     *This,
  IN  EFI_GET_PLATFORM_HANDLE_MODE          Mode,
  IN  UINT16                                Type,
  OUT EFI_HANDLE                            **HandleBuffer,
  OUT UINTN                                 *HandleCount,
  OUT VOID                                  OPTIONAL **AdditionalData
)
{
    EFI_STATUS    Status = EFI_SUCCESS;
//------------------------
    switch (Mode) {
        case EfiGetPlatformVgaHandle:{
                UINTN                  sz = 0, i;
                UINT8                  PriVideo=0; //3=AUTO 0=IGD 1=PEG 2=PCI
                UINT8                  PrimaryPeg=0; //0=AUTO 1=PEG11 2=PEG12
                UINT8                  PrimaryPcie=0; //0=AUTO 1=PCIE1 2=PCIE2....
                EFI_HANDLE             *hb, *vh, peg=NULL, peg00=NULL, pcie0=NULL, igd=NULL, pcie=NULL;
                T_ITEM_LIST            VgaList={0,0,NULL};
                PCI_DEV_INFO           *dev;
                EFI_PCI_IO_PROTOCOL    *pciio;
                BOOLEAN                ChangeIgfxToAuto = FALSE;
                BOOLEAN                ChangePegToAuto = FALSE;
                BOOLEAN                ChangepcieToAuto = FALSE;
                BOOLEAN                ChangePrimaryPeg = FALSE;
                BOOLEAN                ChangePrimaryPcie = FALSE;
                NB_SETUP_DATA           *NBSetupData = NULL;
                UINTN                   VariableSize = sizeof(NB_SETUP_DATA);
                //-----------------

                Status = pBS->AllocatePool( EfiBootServicesData, \
                                VariableSize, \
                                &NBSetupData );
                ASSERT_EFI_ERROR(Status);

                GetNbSetupData( pRS, NBSetupData, FALSE );


                PriVideo = NBSetupData->PrimaryDisplay;
                PrimaryPeg  = NBSetupData->PrimaryPeg;
                PrimaryPcie  = NBSetupData->PrimaryPcie;

                // Free memory used for setup data
                pBS->FreePool( NBSetupData );

                //Get all handles with PCI IO Protocol..
                Status=pBS->LocateHandleBuffer(ByProtocol,&gEfiPciIoProtocolGuid,NULL, &sz, &hb);
                if(EFI_ERROR(Status)) return Status;

                for(i=0; i< sz; i++) {

                    Status=pBS->HandleProtocol(hb[i],&gEfiPciIoProtocolGuid,&pciio);
                    if(EFI_ERROR(Status)) {
                        pBS->FreePool(hb);
                        return Status;
                    }

                    dev = (PCI_DEV_INFO*)pciio;
                    //
                    // When a graphics card with internal PCI-PCI bridges (GTX 295) is attached to
                    // PCH PCIe ports video is not displayed.
                    // PCI to PCI bridge has another device with Baseclasscode as 0x03 and  Sub Classcode
                    // as 0x02. And in CSMBsp.c file, it was seeing this as Video controller.
                    //
                    if((dev->Class.BaseClassCode == PCI_CL_DISPLAY) && (dev->Class.SubClassCode == 0x00)) {
                        Status=AppendItemLst(&VgaList, (VOID*)dev);
                        if(EFI_ERROR(Status)) return Status;
                    }
                }

                pBS->FreePool(hb);

                vh=Malloc(sizeof(EFI_HANDLE));
                *vh=NULL;

                for(i=0; i<VgaList.ItemCount; i++) {
                PCI_DEV_INFO               *brg;
                //--------------------------------
                //This is an Easy task we know exactly where it is
                dev = VgaList.Items[i];
                if(igd == NULL) {
                    if((dev->ParentBrg->Type == tPciRootBrg)
                    && (dev->Address.Addr.Device == 2)
                    && (dev->Address.Addr.Function == 0))
                        igd=dev->Handle;
                    }

                //Some Video cards Implement a MULTY FUNCTIONAL Devices;
                //Some - use PCI 2 PCI bridg(es) to multiply itself
                //to Avoid further complications regarding such situation
                //we'll try to handle this situation!
                //We will assume for Primary Video Device Selection that it always
                //will be the function 0 of mulifunctional Device.
                brg = dev->ParentBrg;

                if(peg == NULL) {
                    while(brg->Type == tPci2PciBrg) {
                        if( (brg->DevVenId.VenId == 0x8086 )   //Intel's Vendor ID
                        && (brg->ParentBrg->Type != tPci2PciBrg ) //Must be connected to the HOST
                        && (brg->Address.Addr.Device == 1)     //Device #1
                        && (brg->Address.Addr.Function >= 0)    //Function #0 ~ 2
                        && ( (dev->PciIo.RomImage != NULL )     //Device behind this Bridge must have ROM
                        || (dev->Bar[PCI_MAX_BAR_NO].Type != tBarUnused) )
                        && (dev->Address.Addr.Function == 0 )
                        && (dev->Capab & EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY)
                        && (dev->Capab & EFI_PCI_IO_ATTRIBUTE_VGA_IO) )
                        {
                            if (PrimaryPeg != 0) {
                               if (brg->Address.Addr.Device == 1)
                               {
                                  if (brg->Address.Addr.Function == 1 && PrimaryPeg == 1)
                                     peg = dev->Handle;
                                  else if (brg->Address.Addr.Function == 2 && PrimaryPeg == 2)
                                     peg = dev->Handle;
                                  else if (brg->Address.Addr.Function == 0)
                                     peg00 = dev->Handle;

                               }
                            } else peg=dev->Handle;
                        }

                        if(peg != NULL)break;
                        brg = brg->ParentBrg;
                    } //#### while
                } //#### if(peg == NULL)

                //Do the same for Video that might be behind PCI 2 PCI bridge device 1Eh
                brg=dev->ParentBrg;
                if(pcie == NULL) {
                    while(brg->Type == tPci2PciBrg) {
                        if( (brg->DevVenId.VenId == 0x8086 )    //Intel's Vendor ID
                        && (brg->ParentBrg->Type != tPci2PciBrg )  //Must be connected to the HOST
                        && ((brg->Address.Addr.Device == 0x1C)  // 0:1C:x - PCIe root ports on PCH
                        || (brg->Address.Addr.Device == 0x1E))   // 0:1E:0 - PCI-to-PCI bridge on PCH
                        && ( (dev->PciIo.RomImage != NULL )      //Device must have an Option ROM
                        || (dev->Bar[PCI_MAX_BAR_NO].Type != tBarUnused) )
                        && (dev->Address.Addr.Function == 0 ))
                        {
                            if (PrimaryPcie != 0) {
                               if (brg->Address.Addr.Device == 0x1C)
                               {
                                  if (brg->Address.Addr.Function == 1 && PrimaryPcie == 1)
                                     pcie = dev->Handle;
                                  else if (brg->Address.Addr.Function == 2 && PrimaryPcie == 2)
                                     pcie = dev->Handle;
                                 if (brg->Address.Addr.Function == 3 && PrimaryPcie == 3)
                                     pcie = dev->Handle;
                                 if (brg->Address.Addr.Function == 4 && PrimaryPcie == 4)
                                     pcie = dev->Handle;
                                  else if (brg->Address.Addr.Function == 5 && PrimaryPcie == 5)
                                     pcie = dev->Handle;
                                  else if (brg->Address.Addr.Function == 6 && PrimaryPcie == 6)
                                     pcie = dev->Handle;
                                  else if (brg->Address.Addr.Function == 7 && PrimaryPcie == 7)
                                     pcie = dev->Handle;
                                  else if (brg->Address.Addr.Function == 0)
                                     pcie0 = dev->Handle;

                               }
                            } else pcie=dev->Handle;
                        }

                        if(pcie != NULL) break;
                        brg = brg->ParentBrg;
                    } //#### while
                } //#### if(pcie == NULL)
            } //#### for;

            if (PrimaryPeg != 0 && peg == NULL) {
                peg = peg00;
                ChangePrimaryPeg = TRUE;
            }

            if (PrimaryPcie != 0 && pcie == NULL) {
                pcie = pcie0;
                ChangePrimaryPcie = TRUE;
            }

            //Clear Temp Buffer we had for VGA Handles;
            ClearItemLst(&VgaList, FALSE);
            //3=AUTO 0=IGD 1=PEG 2=pcie
            switch(PriVideo) {
                case 3 : //0 = auto PEG -> pcie -> IGD
                    if(peg) {
                        *vh = peg;
                        break;
                    }

                    if(pcie) {
                        *vh = pcie;
                         break;
                    }

                    if(igd) *vh = igd;
                    break;

                case 4 : //SG: 1=IGD
                case 0 : //1=IGD  b0|d2|f0
                    if(igd) {
                        *vh = igd;
                    } else {
                        ChangeIgfxToAuto = TRUE;
                    }
                    break;

                case 1 : //1=PEG Bridge b0|d1|f0
                    if(peg) {
                        *vh = peg;
                    } else {
                        ChangePegToAuto = TRUE;
                    }
                    break;

                case 2 : //1=PCI2 PCI bridge  b0|d1E|f0
                    if(pcie) {
                        *vh = pcie;
                    } else {
                        ChangepcieToAuto = TRUE;
                    }
                    break;
            } // switch

            if(*vh == NULL) {
                Status = EFI_UNSUPPORTED;
                pBS->FreePool(vh);
            } else {
                Status = EFI_SUCCESS;
                *HandleCount=1;
                *HandleBuffer=vh;
            }

            if(ChangeIgfxToAuto || ChangePegToAuto || ChangepcieToAuto || ChangePrimaryPeg || ChangePrimaryPcie) {
#if defined APAC_NB_SETUP_SUPPORT || defined NB_SETUP_SUPPORT
#if APAC_NB_SETUP_SUPPORT == 1 || NB_SETUP_SUPPORT == 1
                EFI_STATUS             SetupStatus;
                SETUP_DATA             *SetupData = NULL;
                EFI_GUID               SetupGuid  = SETUP_GUID;
                UINT32                 Attributes;  // [ EIP167027 ]


                //SetupStatus = GetEfiVariable(L"Setup",&SetupGuid,NULL,&sz,&SetupData);    // [ EIP167027 ]
                SetupStatus = GetEfiVariable(L"Setup",&SetupGuid,&Attributes,&sz,&SetupData);
                if (!EFI_ERROR(SetupStatus))
                {
                   if (ChangePrimaryPeg) SetupData->PrimaryPeg = 0; // change to AUTO
                   if (ChangePrimaryPcie) SetupData->PrimaryPcie = 0; // change to AUTO

                   if(ChangeIgfxToAuto || ChangePegToAuto || ChangepcieToAuto)
                      SetupData->PrimaryDisplay = 3; // change to AUTO

                   //SetupStatus = pRS->SetVariable (
                   //                    L"Setup",
                   //                    &SetupGuid,
                   //                    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                   //                    sizeof(SETUP_DATA),
                   //                    SetupData);
                   SetupStatus = pRS->SetVariable (
                                       L"Setup",
                                       &SetupGuid,
                                       Attributes,
                                       sizeof(SETUP_DATA),
                                       SetupData);
                   ASSERT_EFI_ERROR (SetupStatus);
                }
#endif
#endif
            }
        }break;
        default: Status = EFI_UNSUPPORTED;
    } // switch

    return Status;
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
