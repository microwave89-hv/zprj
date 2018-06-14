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
// $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtOemBoard.c 7     5/19/14 7:38a Barretlin $
//
// $Revision: 7 $
//
// $Date: 5/19/14 7:38a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtOemBoard.c $
// 
// 7     5/19/14 7:38a Barretlin
// [TAG]  		EIP165410
// [Category]  	New Feature
// [Description]  	Support Thunderbolt AIC at NB PCIE slot
// [Files]  		TbtPei.c TbtDxe.c TbtGpe.asl TbtSmm.c TbtOemBoard.c
// TbtOemLib.c TbtOemLib.h TbtSetup.sdl TbtSetup.sd TbtSetup.uni
// TbtSetupReset.c
// 
// 6     5/19/14 7:15a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Using setup item choose return value of _RMV method in
// ASL code
// [Files]  		TbtDxe.c TbtGpe.asl TbtOemBoard.c TbtOemBoard.h TbtSetup.sd
// TbtSetup.sdl TbtSetup.uni
// 
// 5     2/18/14 2:12a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Release PCIE root port control when Thunderbolt
// function disable in run time
// [Files]  		TbtOemBoard.c
// 
// 4     2/10/14 1:26p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	remove useless policy item and setup item
// [Files]  		TbtOemBoard.h TbtOemBoard.c TbSetup.sdl TbtSetup.sd
// TbtSetup.uni TbtSmm.c
// 
// 3     1/05/14 2:06p Barretlin
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Support Thunderbolt feature Enable/Disable in run time
// Support dynamic Thunderbolt AIC location in run time
// [Files]  		TbtOemBoard.h TbtOemBoard.c TbtOemLib.c TbtOemLib.h
// 
// 2     6/17/13 2:18a Barretlin
// [TAG]  		EIP126581
// [Category]  	Improvement
// [Description]  	add new AIC support setup item and change
// TBWakeupSupport name
// [Files]  		TbtOemBoard.h TbtOemBoard.c
// 
// 1     1/10/13 4:57a Barretlin
// Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
// Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
// 
// 12    12/12/12 4:14a Barretlin
// [TAG]  		EIP108272
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update to Spec 1.4 to support Redwood Ridge chip
// [Files]  		TbtPei.c TbtSmm.c TbtDxe.c TbtDxe.sdl TbtGpe.asl
// TbtOemBoard.c TbtOemBoard.h TbtOemLib.c TbtOemLib.h
// 
// 11    10/28/12 11:50p Barretlin
// [TAG]  		EIP104870
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change wake up flow for Spec 1.2 and Spec 1.3
// [Files]  		TbtPei.c TbtSmm.c TbtOemBoard.c TbtOemBoard.h
// TbtOemBoard.sdl TbtOemLib.c TbtOemLib.h
// 
// 10    10/28/12 11:21p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Create new setup item for thunderbolt POC handling
// [Files]  		TbtOemBoard.c TbtOemBoard.h TbtSetup.sdl TbtSetup.sd
// TbtSetup.uni
// 
// 9     9/22/12 9:59a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Use token to defien thunderbolt chip pins and update
// sample code
// [Files]  		TbtOemBoard.c TbtOemBoard.sdl
// 
// 8     8/20/12 5:12a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix IO resource workaround broken in 4C 2port case
// [Files]  		TbtSmm.c TbtOemBoard.c TbtOemBoard.h TbtSetup.sdl
// TbtSetup.sd TbtSetup.uni
// 
// 7     8/17/12 8:44a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Add IO resource workaround for Thunderbolt Spec1.1
// Because new spec has removed IO resource for Thunderbolt device
// [Files]  		TbtSmm.c TbtOemBoard.h TbtOemBoard.c TbtSetup.sdl
// TbtSetup.sd TbtSetup.uni 
// 
// 6     7/31/12 4:07a Barretlin
// [TAG]  		EIP96350
// [Category]  	Spec Update
// [Severity]  	Critical
// [Description]  	Updated Thunderbolt specification to version 1.00
// [Files]  		TbtDxe.c TbtSmm.c TbtOemBoard.c TbtOemBoard.h
// TbtOemBoard.sdl TbtSetup.sd TbtSetup.uni
// 
// 5     7/31/12 3:15a Barretlin
// [TAG]  		EIP91119
// [Category]  	Improvement
// [Description]  	Resolution for enable/disable Thunderbolt device option
// rom at POST time
// [Files]  		TbtDxe.c TbtOemBoard.c TbtOemBoard.h TbtOemBoard.sdl
// TbtSetup.sdl TbtSetup.sd TbtSetup.uni
// 
// 4     5/22/12 10:00a Barretlin
// [TAG]  		EIP90650
// [Category]  	Spec Update
// [Description]  	Specificatoin Update 0.94 - The default value of
// OPTIONAL workaround for devices that don't support surprise-removal
// should be disable.
// [Files]  		TbtSmm.c TbtOemBoard.c TbtOemBoard.h
// TbtSetup.sdl TbtSetup.sd TbtSetup.uni
// 
// 3     5/07/12 7:00a Barretlin
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
// 2     2/20/12 12:01a Wesleychen
//  - Add new policy "SmiNotifyEnabled".
//  - Move OemProgramTbtSecurityLevel() to TbtDxe.c.
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
#include <TbtOemLib.h>
#include <TbtOemBoard.h>

// GUID Definition(s)
EFI_GUID  AmiTbtPlatformPpolicyGuid = AMI_TBT_PLATFROM_POLICY_PROTOCOL_GUID;
EFI_GUID  TbtHRStatusGuid           = AMI_TBT_HR_STATUS_GUID;
EFI_GUID  SetupGuid                 = SETUP_GUID;

// Variable Declaration(s)
AMI_TBT_PLATFORM_POLICY_PROTOCOL  gTbtPlatformPolicy;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TbtOemBoard_Init
//
// Description: This function is the entry point for TbtOemBoard.
//
// Input:       ImageHandle - Image handle
//              SystemTable - Pointer to the system table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TbtOemBoard_Init (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable )
{
    //
    // OEM Porting is required.
    //
    EFI_STATUS              Status             = EFI_SUCCESS;
    EFI_HANDLE              Handle             = NULL;
    UINTN                   VariableSize       = sizeof(SETUP_DATA);
    UINTN                   HRStatusSize       = sizeof(AMI_TBT_HR_STATUS_DATA);
    UINT32                  Attributes;
    UINT16                  counter;
    UINT8                   TbtSetVariableFlag = 0;
    CHAR16                  TbtHRStatusVar[]   = TBT_HR_STATUS_VARIABLE;
    AMI_TBT_HR_STATUS_DATA  HRStatusData;
    SETUP_DATA              SetupData;
    
    InitAmiLib(ImageHandle, SystemTable);
    
    //Initial Host Router information
    Status = pRS->GetVariable( L"TbtHRStatusVar", \
                               &TbtHRStatusGuid, \
                               NULL, \
                               &HRStatusSize, \
                               &HRStatusData );
    if (EFI_ERROR(Status)){
        TRACE((-1, "TbtOemBoard: Can not get Thunderbolt Host Router Information !!! \n"));
        HRStatusData.TbtHRStatus   = 0;
        //Get Thunderbolt host Series
        HRStatusData.TbtHRSeries = GetHRInfo();
        TRACE((-1, "TbtOemBoard: Thunderbolt Host Router Chip: %x \n", HRStatusData.TbtHRSeries));
        
        Status = pRS->SetVariable( TbtHRStatusVar, \
                                   &TbtHRStatusGuid, \
                                   EFI_VARIABLE_NON_VOLATILE | \
                                   EFI_VARIABLE_BOOTSERVICE_ACCESS | \
                                   EFI_VARIABLE_RUNTIME_ACCESS, \
                                   HRStatusSize, \
                                   &HRStatusData );
        if (!EFI_ERROR(Status))
            TRACE((-1, "TbtOemBoard: Create Thunderbolt Host Router Information !!! \n"));
    }
    
    Status = pRS->GetVariable( L"Setup", \
                               &SetupGuid, \
                               &Attributes, \
                               &VariableSize, \
                               &SetupData );
    ASSERT_EFI_ERROR (Status);
    
    Status = pBS->AllocatePool( \
                  EfiBootServicesData, \
                  sizeof(AMI_TBT_PLATFORM_POLICY_PROTOCOL), \
                  (VOID**)&gTbtPlatformPolicy );
    ASSERT_EFI_ERROR (Status);
    
    TRACE((-1, "TbtOemBoard: Start install Thunderbolt Platform Policy !!! \n"));
    pBS->SetMem( &gTbtPlatformPolicy, sizeof(AMI_TBT_PLATFORM_POLICY_PROTOCOL), 0 );
    
    //
    // OEM Porting required.
    //
/* Sample Code
    gTbtPlatformPolicy.TbtEnable             = SetupData.TbtEnable;
    gTbtPlatformPolicy.TbtGO2SX              = TBT_GO2SX;
    gTbtPlatformPolicy.TbtForcePWR           = TBT_ForcePWR;
    gTbtPlatformPolicy.TbtHotPlugEvt         = TBT_HotPlugEvt;
    gTbtPlatformPolicy.TbtOK2GO2SX_N         = TBT_OK2GO2SX_N;
    gTbtPlatformPolicy.CacheLineSize         = SetupData.TbtCacheLineSize;
    gTbtPlatformPolicy.TbtWakeupSupport      = SetupData.TbtWakeupSupport;
    gTbtPlatformPolicy.TbtAICSupport         = SetupData.TbtAICSupport;
    gTbtPlatformPolicy.TbtHandlePOC          = SetupData.TbtHandlePOC;
    gTbtPlatformPolicy.TbtSecurityLevel      = SetupData.TbtSecurityLevel;
    gTbtPlatformPolicy.Bus                   = TBT_UP_PORT_BUS;
    gTbtPlatformPolicy.Dev                   = TBT_UP_PORT_DEV;
    if (gTbtPlatformPolicy.TbtAICSupport == 1){
        if (SetupData.TbtHostLocation < 0x20){
            gTbtPlatformPolicy.Fun           = SetupData.TbtHostLocation;
        } else {
            gTbtPlatformPolicy.Dev           = 0x01;
            gTbtPlatformPolicy.Fun           = (SetupData.TbtHostLocation) - 0x20;
        }
    } else {
        gTbtPlatformPolicy.Fun               = TBT_UP_PORT_FUNC;
    }
    gTbtPlatformPolicy.ReserveMemoryPerSlot  = SetupData.ReserveMemoryPerSlot;
    gTbtPlatformPolicy.ReservePMemoryPerSlot = SetupData.ReservePMemoryPerSlot;
    gTbtPlatformPolicy.ReserveIOPerSlot      = SetupData.ReserveIOPerSlot;
    gTbtPlatformPolicy.SmiNotifyEnabled      = SetupData.SmiNotifyEnabled;
    gTbtPlatformPolicy.SwSmiEnabled          = SetupData.SwSmiEnabled;
    gTbtPlatformPolicy.NotifyEnabled         = SetupData.NotifyEnabled;
    gTbtPlatformPolicy.TbtOptionRom          = SetupData.TbtOptionRom;
    gTbtPlatformPolicy.TbtRmvReturnValue     = SetupData.TbtRmvReturnValue;
    gTbtPlatformPolicy.TbtIOresourceEnable   = SetupData.TbtIOresourceEnable;
    gTbtPlatformPolicy.TbtNVMversion         = SetupData.TbtNVMversion;

    Status = pBS->InstallProtocolInterface (
                            &Handle,
                            &AmiTbtPlatformPpolicyGuid,
                            EFI_NATIVE_INTERFACE,
                            &gTbtPlatformPolicy
                            );
    ASSERT_EFI_ERROR (Status);
//*/
    //synchronize Thunderbolt Host Router Information with Setup Data
    if (HRStatusData.TbtHRSeries != SetupData.TbtHRSeries){
        TRACE((-1, "TbtOemBoard: Setting Thunderbolt Host Router Information into Setup Data!!! \n"));
        SetupData.TbtHRSeries = HRStatusData.TbtHRSeries;
        TbtSetVariableFlag |= 1;
    }
    
#if defined TBT_INTEL_RC_CONFIG && TBT_INTEL_RC_CONFIG == 1
    if (gTbtPlatformPolicy.TbtEnable){
        if (gTbtPlatformPolicy.TbtAICSupport){
            if ((gTbtPlatformPolicy.Bus == 0) && (gTbtPlatformPolicy.Dev == 0x1C))
            {   // Thunderbolt AIC is at SB PCIE root port
                if ((SetupData.PcieMemRsvd[gTbtPlatformPolicy.Fun] != 353) || \
                    (SetupData.PcieMemRsvd[gTbtPlatformPolicy.Fun] != 737)){
                    // Change PCIE root port resource to correct location
                    SetupData.PcieRootPortEn[gTbtPlatformPolicy.Fun]    = 1;
                    SetupData.PcieRootPortHPE[gTbtPlatformPolicy.Fun]   = 1;
                    SetupData.ExtraBusRsvd[gTbtPlatformPolicy.Fun]      = TBT_DEFAULT_EXTRA_BUS_RESERVED;
                    SetupData.PcieMemRsvd[gTbtPlatformPolicy.Fun]       = TBT_DEFAULT_PCIE_MEM_RESERVED;
                    SetupData.PcieMemRsvdalig[gTbtPlatformPolicy.Fun]   = 26;
                    SetupData.PciePFMemRsvd[gTbtPlatformPolicy.Fun]     = TBT_DEFAULT_PCIE_PF_MEM_RESERVED;
                    SetupData.PciePFMemRsvdalig[gTbtPlatformPolicy.Fun] = 28;
                    SetupData.PcieIoRsvd[gTbtPlatformPolicy.Fun]        = TBT_DEFAULT_PCIE_IO_RESERVED;
                    
                    // Double check resource on other PCIE root port is disable
                    for(counter=0;counter<=7;counter++){
                        if(counter != gTbtPlatformPolicy.Fun){
                            if((SetupData.PcieMemRsvd[counter] == 353) || \
                               (SetupData.PcieMemRsvd[counter] == 737))
                            {
                                SetupData.PcieRootPortHPE[counter]      = 0;
                                SetupData.ExtraBusRsvd[counter]         = 0;
                                SetupData.PcieMemRsvd[counter]          = 10;
                                SetupData.PcieMemRsvdalig[counter]      = 1;
                                SetupData.PciePFMemRsvd[counter]        = 10;
                                SetupData.PciePFMemRsvdalig[counter]    = 1;
                                SetupData.PcieIoRsvd[counter]           = 4;
                            }
                        } // counter != gTbtPlatformPolicy.Fun
                    } // for loop
                    
                    TbtSetVariableFlag |= 1;
                } // PCIE root port resource is at incorrect location
            } else {
                // Thunderbolt AIC is at NB PCIE root port
                // Double check resource on other PCIE root port is disable
                for(counter=0;counter<=7;counter++){
                    if((SetupData.PcieMemRsvd[counter] == 353) || \
                       (SetupData.PcieMemRsvd[counter] == 737))
                    {
                        SetupData.PcieRootPortHPE[counter]      = 0;
                        SetupData.ExtraBusRsvd[counter]         = 0;
                        SetupData.PcieMemRsvd[counter]          = 10;
                        SetupData.PcieMemRsvdalig[counter]      = 1;
                        SetupData.PciePFMemRsvd[counter]        = 10;
                        SetupData.PciePFMemRsvdalig[counter]    = 1;
                        SetupData.PcieIoRsvd[counter]           = 4;

                        TbtSetVariableFlag |= 1;
                    }
                } // for loop
            }
        } else {
            if ((SetupData.PcieMemRsvd[TBT_UP_PORT_FUNC] != 353) || \
                (SetupData.PcieMemRsvd[TBT_UP_PORT_FUNC] != 737))
            {
                SetupData.TbtHostLocation                     = TBT_UP_PORT_FUNC;
                SetupData.PcieRootPortEn[TBT_UP_PORT_FUNC]    = 1;
                SetupData.PcieRootPortHPE[TBT_UP_PORT_FUNC]   = 1;
                SetupData.ExtraBusRsvd[TBT_UP_PORT_FUNC]      = TBT_DEFAULT_EXTRA_BUS_RESERVED;
                SetupData.PcieMemRsvd[TBT_UP_PORT_FUNC]       = TBT_DEFAULT_PCIE_MEM_RESERVED;
                SetupData.PcieMemRsvdalig[TBT_UP_PORT_FUNC]   = 26;
                SetupData.PciePFMemRsvd[TBT_UP_PORT_FUNC]     = TBT_DEFAULT_PCIE_PF_MEM_RESERVED;
                SetupData.PciePFMemRsvdalig[TBT_UP_PORT_FUNC] = 28;
                SetupData.PcieIoRsvd[TBT_UP_PORT_FUNC]        = TBT_DEFAULT_PCIE_IO_RESERVED;
                
                // Double check resource on other PCIE root port is disable
                for(counter=0;counter<=7;counter++){
                    if(counter != TBT_UP_PORT_FUNC){
                        if((SetupData.PcieMemRsvd[counter] == 353) || (SetupData.PcieMemRsvd[counter] == 737)){
                            SetupData.PcieRootPortHPE[counter]   = 0;
                            SetupData.ExtraBusRsvd[counter]      = 0;
                            SetupData.PcieMemRsvd[counter]       = 10;
                            SetupData.PcieMemRsvdalig[counter]   = 1;
                            SetupData.PciePFMemRsvd[counter]     = 10;
                            SetupData.PciePFMemRsvdalig[counter] = 1;
                            SetupData.PcieIoRsvd[counter]        = 4;
                        }
                    } // counter != TBT_UP_PORT_FUNC
                } // for loop
                
                TbtSetVariableFlag |= 1;
            } // PCIE root port resource is not at default location
        } // gTbtPlatformPolicy.TbtAICSupport
    } // gTbtPlatformPolicy.TbtEnable
#endif

  if (TbtSetVariableFlag != 0){
     Status = pRS->SetVariable( L"Setup", &SetupGuid, Attributes, 
                                VariableSize, &SetupData );
  }

  return EFI_SUCCESS;
}
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
