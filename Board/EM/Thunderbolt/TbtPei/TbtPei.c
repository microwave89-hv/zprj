//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtPei/TbtPei.c 11    5/19/14 7:31a Barretlin $
//
// $Revision: 11 $
//
// $Date: 5/19/14 7:31a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtPei/TbtPei.c $
// 
// 11    5/19/14 7:31a Barretlin
// [TAG]  		EIP165410
// [Category]  	New Feature
// [Description]  	Support Thunderbolt AIC at NB PCIE slot
// [Files]  		TbtPei.c TbtDxe.c TbtGpe.asl TbtSmm.c TbtOemBoard.c
// TbtOemLib.c TbtOemLib.h TbtSetup.sdl TbtSetup.sd TbtSetup.uni
// TbtSetupReset.c
// 
// 10    1/06/14 5:21a Barretlin
// 
// 9     1/05/14 1:30p Barretlin
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Support Thunderbolt feature Enable/Disable in run time
// Support dynamic Thunderbolt AIC location in run time
// [Files]  		TbtPei.c
// 
// 8     7/26/13 1:50a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix build error at MahoBay/ChiefRiver platform
// [Files]  		TbtPei.c TbtOemBoard.h
// 
// 7     6/20/13 2:15a Barretlin
// [TAG]  		EIP126581
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Follow Thunderbolt RR/FR BIOS Spec rev 1.0 to set PCH
// PM_CFG register for Add-in Card
// [Files]  		TbtPei.c
// 
// 6     6/17/13 4:36a Barretlin
// [TAG]  		EIP None
// [Category]  	Improvement
// [Description]  	change TBWakeupSupport name
// [Files]  		TbtPei.c
// 
// 5     5/27/13 7:27a Barretlin
// [TAG]  		EIP124914
// [Category]  	New Feature
// [Description]  	Support Falcon Ridge chip
// [Files]  		TbtPei.c
// 
// 4     4/24/13 2:30a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Using token to decide execute Sx_Exit command of RR
// chip in S5 boot path
// [Files]  		TbtPei.c TbtOemBoard.sdl
// 
// 3     4/12/13 12:51p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix security level of CR chip not be programming in
// some case
// [Files]  		TbtPei.c
// 
// 2     2/06/13 1:46a Barretlin
// [TAG]  		EIP114556
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change fast link bring-up flow for Thunderbolt RR
// Spec0.9
// [Files]  		TbtPei.c
// 
// 1     1/10/13 4:55a Barretlin
// Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
// Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
// 
// 7     12/12/12 2:40a Barretlin
// [TAG]  		EIP108272
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update to Spec. 1.4 to support Redwood Ridge chip
// [Files]  		TbtPei.c TbtSmm.c TbtDxe.c TbtDxe.sdl TbtGpe.asl
// TbtOemBoard.c TbtOemBoard.h TbtOemLib.c TbtOemLib.h
// 
// 6     10/28/12 11:41p Barretlin
// [TAG]  		EIP104870
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change wake up flow for Spec 1.2 and Spec 1.3
// [Files]  		TbtPei.c TbtSmm.c TbtOemBoard.c TbtOemBoard.h
// 
// 5     10/04/12 10:35p Barretlin
// [TAG]  		EIP102947
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	Update Thunderbolt Spec to Rev 1.2
// [Files]  		TbtPei.c TbtOemLib.c TbtOemLib.h
// 
// 4     10/03/12 9:06p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Change Programming security level timing for saving
// boot time
// [Files]  		TbtPei.c TbtDxe.c TbtOemBoard.c TbtOemBoard.h
// TbtOemBoard.sdl TbtOemLib.c TbtOemLib.h
// 
// 3     4/14/12 4:26a Barretlin
// [TAG]                      None
// [Category]               Improvement
// [Description]            Fix Programming error at specification 0.90
// update
// [Files]                      TbtPei.c
// 
// 2     3/05/12 1:21a Barretlin
// [TAG]  		EIP83266
// [Category]  	Spec Update
// [Description]  	Specificatoin Update 0.90
// [Files]  		TbtSetup.sdl
// TbtSetup.sd
// TbtSetup.uni
// TbtSetup.cif
// TbtOemBoard.h
// TbtOemLib.c
// TbtOemLib.h
// TbtSmm.c
// TbtPei..
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  <TbtPei.c>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Token.h>
#include <Setup.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <TbtOemBoard.h>
#include <PPI\stall.h>
#include <ppi\ReadOnlyVariable.h>
#include <PPI\NBPPI.h>

//----------------------------------------------------------------------------
// GUID Definition(s)
//----------------------------------------------------------------------------
EFI_GUID gEfiPeiReadOnlyVariablePpiGuid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
EFI_GUID gTbtHRStatusGuid               = AMI_TBT_HR_STATUS_GUID;
EFI_GUID gPeiStallPpiGuid               = EFI_PEI_STALL_PPI_GUID;
EFI_GUID gTbtHobGuid                    = AMI_TBT_HOB_GUID;
EFI_GUID SetupGuid                      = SETUP_GUID;

//----------------------------------------------------------------------------
// Function Prototype Definition(s)
//----------------------------------------------------------------------------
EFI_STATUS TbtCRSxExitFlow (
    IN EFI_PEI_SERVICES             **PeiServices);

EFI_STATUS TbtSxExitFlow (
    IN EFI_PEI_SERVICES             **PeiServices);

EFI_STATUS TbtPeiAfterNbPcieReady(
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi );

//----------------------------------------------------------------------------
// Notified PPI Definition(s)
//----------------------------------------------------------------------------
static EFI_PEI_NOTIFY_DESCRIPTOR TbtNotifyList[] = {
        { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
          EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
//          &gEfiPeiEndOfPeiPhasePpiGuid, TbtPeiAfterNbPcieReady },
          &gAmiPeiBeforeMrcGuid, TbtPeiAfterNbPcieReady },
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: TbtPeiEntry
//
// Description:
//      This function is the main PEI phase entry point for the Thunderbolt
//      module.
//
// Input:
//      IN EFI_FFS_FILE_HEADER *FfsHeader
//                  -- FFS file header pointer
//      IN EFI_PEI_SERVICES **PeiServices
//                  -- PEI Services table pointer
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = or other valid EFI error code
//
// Notes:
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TbtPeiEntry(
    IN EFI_FFS_FILE_HEADER        *FfsHeader,
    IN EFI_PEI_SERVICES           **PeiServices )
{
    EFI_STATUS                      Status;
    UINTN                           VariableSize = sizeof(SETUP_DATA);
    UINTN                           HRStatusSize = sizeof(AMI_TBT_HR_STATUS_DATA);
    SETUP_DATA                      SetupData;
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
    EFI_BOOT_MODE                   BootMode;
    AMI_TBT_HR_STATUS_DATA          HRStatusData;
    UINT8                           TBus = TBT_UP_PORT_BUS;
    UINT8                           TDev = TBT_UP_PORT_DEV;
    UINT8                           TFun = TBT_UP_PORT_FUNC;

    PEI_TRACE((TRACE_ALWAYS, PeiServices, "Intel Thunderbolt PEI Entry !!!\n"));
    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "BootMode = %X\n", BootMode));
    if (BootMode > BOOT_ON_S3_RESUME){
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "Thunderbolt dones't support working with this Boot mode !!!\n"));
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "Intel Thunderbolt PEI Exit !!!\n"));
        return EFI_SUCCESS;
    }
    
    // Locate PeiReadOnlyVariable ppi.
    Status = (*PeiServices)->LocatePpi ( PeiServices, \
                                         &gEfiPeiReadOnlyVariablePpiGuid, \
                                         0, \
                                         NULL, \
                                         &ReadOnlyVariable);
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Locate PeiReadOnlyVariable Ppi Status = %r\n", Status));
     
    Status = ReadOnlyVariable->GetVariable ( PeiServices,
                                             L"Setup",
                                             &SetupGuid,
                                             NULL,
                                             &VariableSize,
                                             &SetupData );
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Locate Get Setup ReadOnlyVariable Status = %r\n", Status));
    
    if ((!EFI_ERROR(Status)) && (SetupData.TbtEnable == 0)){
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Thunderbolt function is disable in Setup...\n"));
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Skip all action for TBT in PEI phase\n"));
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "Intel Thunderbolt PEI Exit !!!\n"));
        return EFI_SUCCESS;
    }

    // Thunderbolt BIOS Implementation guide for Redwood Ridge/Falcon Ridge/Win Ridge
    // based devices Specification Update Revision 1.0
    // 2.1.3.7 PCH configuration for hosts with Add-In Card support
    // During boot, reboot and wake T218 field (bits [1:0]) of PCH PM_CFG register should
    // be set to 11b - 10 ms (default value is 0b - 10 us)
    if ((!EFI_ERROR(Status)) && SetupData.TbtAICSupport){
        SET_MEM8_RCRB(R_PCH_RCRB_PM_CFG, (BIT00 | BIT01));
    } // end of setting T218 field
    
    // Get Thunderbolt host status variable
    Status = ReadOnlyVariable->GetVariable ( PeiServices,
                                             L"TbtHRStatusVar",
                                             &gTbtHRStatusGuid,
                                             NULL,
                                             &HRStatusSize,
                                             &HRStatusData );
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Locate Get TbtHRStatusVar ReadOnlyVariable Status = %r\n", Status));

    if(!EFI_ERROR(Status)){
        // For OEM doing anything before Thunderbolt Sx Exit flow
        TbtBeforeSxExitFlow(PeiServices, HRStatusData.TbtHRSeries);

        // Check Thunderbolt host is at NB PCIE slot or SB PCIE slot
        if (SetupData.TbtHostLocation >= 0x20){
            // Thunderbolt host is at NB PCIE root port
            Status = (*PeiServices)->NotifyPpi( PeiServices, TbtNotifyList );
            PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Thunderbolt host is at NB PCIE slot, create notify event %r\n", Status));
            ASSERT_PEI_ERROR(PeiServices, Status);
            PEI_TRACE((TRACE_ALWAYS, PeiServices, "Intel Thunderbolt PEI Exit !!!\n"));
            return EFI_SUCCESS;
        }

        switch(HRStatusData.TbtHRSeries){
            case Cactus_Ridge:
                PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Cactus Ridge wake flow ...\n"));
                Status = TbtCRSxExitFlow(PeiServices);
                break;

            case Redwood_Ridge:
            case Falcon_Ridge:
            case BDW_TBT_LP:
                PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Redwood Ridge/Falcon Ridge/Win Ridge wake flow ...\n"));
                Status = TbtSxExitFlow(PeiServices);
                break;
        } // end of switch
        ASSERT_PEI_ERROR(PeiServices, Status);
    } // end of if

    PEI_TRACE((TRACE_ALWAYS, PeiServices, "Intel Thunderbolt PEI Exit !!!\n"));
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TbtCRSxExitFlow
//
// Description: Thunderbolt host Sx Exit Flow for Cactus Ridge chip
//
// Input:       EFI_PEI_SERVICES             **PeiServices
//
// Output:      EFI_STATUS                   
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TbtCRSxExitFlow (
    IN EFI_PEI_SERVICES             **PeiServices)
{
    EFI_STATUS                      Status    = EFI_SUCCESS;
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
    AMI_TBT_HR_STATUS_DATA          TbtHostInfo;
    SETUP_DATA                      SetupData;
    EFI_BOOT_MODE                   BootMode;
    EFI_PEI_STALL_PPI               *StallPpi = NULL;
    TBT_HOB                         *tHob;
    UINTN                           VariableSize = sizeof(SETUP_DATA);
    UINTN                           HRStatusSize = sizeof(AMI_TBT_HR_STATUS_DATA);
    UINTN                           Delay;
    
    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    ASSERT_PEI_ERROR(PeiServices, Status);

    Status = (*PeiServices)->LocatePpi ( PeiServices, &gEfiPeiReadOnlyVariablePpiGuid,
                                         0, NULL, &ReadOnlyVariable);
    ASSERT_PEI_ERROR(PeiServices, Status);

    Status = ReadOnlyVariable->GetVariable ( PeiServices, L"Setup",
                                             &SetupGuid, NULL,
                                             &VariableSize, &SetupData);
    ASSERT_PEI_ERROR(PeiServices, Status);
    
    Status = ReadOnlyVariable->GetVariable ( PeiServices, L"TbtHRStatusVar",
                                             &gTbtHRStatusGuid, NULL,
                                             &HRStatusSize, &TbtHostInfo);
    ASSERT_PEI_ERROR(PeiServices, Status);
    
    if (TbtHostInfo.TbtHRSeries != Cactus_Ridge) return EFI_INVALID_PARAMETER;

    // Locate Stall Ppi
    Status = (*PeiServices)->LocatePpi (PeiServices, &gPeiStallPpiGuid, 0, NULL, &StallPpi);
    ASSERT_PEI_ERROR(PeiServices, Status);

    // For Debug, out put 80 port CP 0x14
    IoWrite8(0x80, 0x14);

    if (SetupData.TbtWakeupSupport){
        // BIOS support of Thunderbolt devices Specification Update Revision 0.90
        // When BIOS decides to wake system the first step that should be
        // performed is deasserting of GO2Sx pin to wake HR.
        Status = InactiveTbtGpio2();

        // If remembered HR state was active(system went to sleep status with
        // attached devices), BIOS should stall wake process for approximately
        // 2.5 seconds to ensure completeness of TBT link to all endpoint devices.
        if (TbtHostInfo.TbtHRStatus){
            PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: HR status is active, delay 2.5 seconds...\n"));
            Delay = (UINTN)((SetupData.TbtWakeupDelay)*1000);
            if (Delay != 0) StallPpi->Stall(PeiServices, StallPpi, Delay);
        }

        if (BootMode <= BOOT_ON_S5_RESUME){
            Status = (*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, sizeof(TBT_HOB), &tHob);
            if (!EFI_ERROR(Status)){
                PEI_TRACE((TRACE_ALWAYS,PeiServices,"TbtPei: Create Thunderbolt Hob for Programming Cactus Ridge host Security Level = %x !!!\n", SetupData.TbtSecurityLevel));
                tHob->Header.Name = gTbtHobGuid;
                tHob->TbtSecurityLevelFlag = 1;
            }
        }
    } else {
        // BIOS support of Thunderbolt devices Specification Update Revision 1.2
        // If system does not support "Wake From Thunderbolt Devices" function and
        // remembered HR state was active(system went to sleep status with attached devices),
        // BIOS should:
        // 1. Pull down GPIO_9__OK2GO2SX_N_OD
        // 2. Stall wake process for approximately 2.5 seconds to ensure
        //    completeness of TBT link to all endpoint devices.
        // 3. Release pull down GPIO_9__OK2GO2SX_N_OD (Make control pin as input)
        
        // Power on POC of Thunderbolt host chip
        if (SetupData.TbtHandlePOC)
            Status = PowerOnPOC();

        if (TbtHostInfo.TbtHRStatus){
            // program GPIO_9 as output
            Status = PullDownTbtGpio9();
            
            // delay 2.5 seconds
            Delay = (UINTN)((SetupData.TbtWakeupDelay)*1000);
            if (Delay != 0) StallPpi->Stall(PeiServices, StallPpi, Delay);
            
            // release GPIO_9
            Status = ReleaseTbtGpio9();
        }

        if (BootMode != BOOT_ON_S3_RESUME){
            Status = (*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, sizeof(TBT_HOB), &tHob);
            if (!EFI_ERROR(Status)){
                PEI_TRACE((TRACE_ALWAYS,PeiServices,"TbtPei: Create Thunderbolt Hob for Programming Cactus Ridge host Security Level = %x !!!\n", SetupData.TbtSecurityLevel));
                tHob->Header.Name = gTbtHobGuid;
                tHob->TbtSecurityLevelFlag = 1;
            }
        }
    }

    // Program Thunderbolt host security level
    PEI_TRACE((TRACE_ALWAYS,PeiServices,"TbtPei: Start Programming Security Level = %x !!!\n", SetupData.TbtSecurityLevel));
    ProgramTbtSecurityLevel(&(SetupData.TbtSecurityLevel), TbtHostInfo.TbtHRSeries, TBT_UP_PORT_FUNC, TRUE);

    if ((BootMode == BOOT_ON_S3_RESUME) && (!SetupData.TbtWakeupSupport)){
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: No support wake from thunderbolt and in S3 boot path !!!\n"));
        // delay 400ms
        StallPpi->Stall(PeiServices, StallPpi, (450*1000));

        // Finish programming security level
        PeiFinialProgramTbtSecurityLevel(SetupData.TbtSecurityLevel);
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TbtSxExitFlow
//
// Description: Thunderbolt host Sx Exit Flow for Redwood Ridge, Falcon Ridge
//              and Win Ridge(BDW-TBT-LP) chips
//
// Input:       EFI_PEI_SERVICES             **PeiServices
//
// Output:      EFI_STATUS                   
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TbtSxExitFlow (
    IN EFI_PEI_SERVICES             **PeiServices)
{
    EFI_STATUS                      Status    = EFI_SUCCESS;
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
    AMI_TBT_HR_STATUS_DATA          TbtHostInfo;
    SETUP_DATA                      SetupData;
    EFI_BOOT_MODE                   BootMode;
    EFI_PEI_STALL_PPI               *StallPpi = NULL;
    UINTN                           VariableSize = sizeof(SETUP_DATA);
    UINTN                           HRStatusSize = sizeof(AMI_TBT_HR_STATUS_DATA);
    UINTN                           Delay;
    UINTN                           Counter;
    UINT32                          REG_VAL = 0;
    UINT8                           TBus = TBT_UP_PORT_BUS;
    UINT8                           TDev = TBT_UP_PORT_DEV;
    UINT8                           TFun = TBT_UP_PORT_FUNC;
    
    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    ASSERT_PEI_ERROR(PeiServices, Status);

    Status = (*PeiServices)->LocatePpi ( PeiServices, &gEfiPeiReadOnlyVariablePpiGuid,
                                         0, NULL, &ReadOnlyVariable);
    ASSERT_PEI_ERROR(PeiServices, Status);

    Status = ReadOnlyVariable->GetVariable ( PeiServices, L"Setup",
                                             &SetupGuid, NULL,
                                             &VariableSize, &SetupData);
    ASSERT_PEI_ERROR(PeiServices, Status);
    
    Status = ReadOnlyVariable->GetVariable ( PeiServices, L"TbtHRStatusVar",
                                             &gTbtHRStatusGuid, NULL,
                                             &HRStatusSize, &TbtHostInfo);
    ASSERT_PEI_ERROR(PeiServices, Status);
    
    if (TbtHostInfo.TbtHRSeries == Cactus_Ridge) return EFI_INVALID_PARAMETER;

    // Get Thunderbolt host location
    if (SetupData.TbtHostLocation < 0x20){
        // Thunderbolt host is at SB PCIE root port
        TFun = SetupData.TbtHostLocation;
    } else {
        // Thunderbolt host is at NB PCIE root port
        TDev = 0x01;
        TFun = SetupData.TbtHostLocation - 0x20;
    }

    //Assign temp bus
    WRITE_PCI16(TBus, TDev, TFun, PCI_PBUS+1, 0x0505);
    // Do a dummy Write
    WRITE_PCI32(5, 0, 0, PCI_VID, 0x12345678);

#if defined TBT_RR_S5_SXEXIT && TBT_RR_S5_SXEXIT == 1
    if (TbtHostInfo.TbtHRStatus){
#else
    if ((TbtHostInfo.TbtHRStatus) && ((BootMode == BOOT_ON_S3_RESUME) || (BootMode == BOOT_ON_S4_RESUME))){
#endif
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: HR status is active...\n"));

        // Locate Stall Ppi
        Status = (*PeiServices)->LocatePpi (PeiServices, &gPeiStallPpiGuid, 0, NULL, &StallPpi);
        ASSERT_PEI_ERROR(PeiServices, Status);

        // For Debug, out put 80 port CP 0x14
        IoWrite8(0x80, (TBT_SX_EXIT_TBT_CONNECTED | 0x10));

        if (!(SetupData.TbtWakeupSupport)){
            // BIOS support of Thunderbolt devices Specification for 
            // RR Revision 1.0 / FR Revision 1.1 / WR Revision 1.0
            // 2.2.2.4 Sx exit flow for Hosts without Thunderbolt wake support
            // If BIOS saved pre-Sx Host Router state as active
            // (system went to sleep with attached devices),
            // BIOS should add 500ms delay before proceeding to next step
            Delay = (UINTN)(550 * 1000);
            StallPpi->Stall(PeiServices, StallPpi, Delay);
        }
        // BIOS support of Thunderbolt devices Specification for 
        // RR Revision 1.0 / FR Revision 1.1 / WR Revision 1.0
        // 2.2.2.5 Sx exit flow for Hosts with and without Thunderbolt wake support
        // Upon wake, if BIOS saved pre-Sx Host Router state as active, BIOS sholud:
        // 1. Apply "PCIE2TBT <-> TBT2PCIE" handshake procedure with 
        //    "Sx_Exit_TBT_Connected" command.
        // 2. If procedure above returns true, BIOS sholud perform 
        //    "wait for fast link bring-up" loop.

        // Excute command...
        if (MMIO_READ32(TBT_CFG_ADDRESS(0x05, 0, 0, PCI_RID))!= 0xFFFFFFFF){
            if (TbtSetPCIe2TBTCommand(0x05, 0, TBT_SX_EXIT_TBT_CONNECTED, 0x8FFFFF)){
                for(Counter=0;Counter<0x2000;Counter++){
                    if (MMIO_READ32(TBT_CFG_ADDRESS(5, 0, 0, PCI_VID)) != 0xFFFFFFFF){
                        break;
                    }
                    StallPpi->Stall(PeiServices, StallPpi, 1000);
                } // for loop
            } //  end of if
        } //  end of if
    } // Host is active

    // Remove temp bus
    WRITE_PCI32(TBus, TDev, TFun, PCI_PBUS, 0xFF000000);

    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TbtPeiAfterNbPcieReady
//
// Description: When Thunderbolt host is at NB PCIE slot, we do Sx_Exit flow 
//              here avoiding chipset limitation
//
// Input:       EFI_PEI_SERVICES             **PeiServices
//              EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor
//              VOID                         *InvokePpi
//
// Output:      EFI_STATUS                   
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TbtPeiAfterNbPcieReady(
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi )
{
    EFI_STATUS                      Status    = EFI_SUCCESS;
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
    SETUP_DATA                      SetupData;
    AMI_TBT_HR_STATUS_DATA          TbtHostInfo;
    UINTN                           VariableSize = sizeof(SETUP_DATA);
    UINTN                           HRStatusSize = sizeof(AMI_TBT_HR_STATUS_DATA);

    PEI_TRACE((TRACE_ALWAYS,PeiServices, "TbtPeiAfterNbPcieReady Start.\n"));

    Status = (*PeiServices)->LocatePpi ( PeiServices, &gEfiPeiReadOnlyVariablePpiGuid,
                                         0, NULL, &ReadOnlyVariable);
    ASSERT_PEI_ERROR(PeiServices, Status);

    Status = ReadOnlyVariable->GetVariable ( PeiServices, L"Setup",
                                             &SetupGuid, NULL,
                                             &VariableSize, &SetupData);
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Locate Get Setup ReadOnlyVariable Status = %r\n", Status));
    
    Status = ReadOnlyVariable->GetVariable ( PeiServices, L"TbtHRStatusVar",
                                             &gTbtHRStatusGuid, NULL,
                                             &HRStatusSize, &TbtHostInfo);
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Locate Get TbtHRStatusVar ReadOnlyVariable Status = %r\n", Status));
    
    if(!EFI_ERROR(Status) && (SetupData.TbtHostLocation >= 0x20)){
        switch(TbtHostInfo.TbtHRSeries){
            case Cactus_Ridge:
                PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Cactus Ridge wake flow ...\n"));
                Status = TbtCRSxExitFlow(PeiServices);
                break;

            case Redwood_Ridge:
            case Falcon_Ridge:
            case BDW_TBT_LP:
                PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Redwood Ridge/Falcon Ridge/Win Ridge wake flow ...\n"));
                Status = TbtSxExitFlow(PeiServices);
                break;
        } // end of switch
        ASSERT_PEI_ERROR(PeiServices, Status);
    }

    PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPeiAfterNbPcieReady End.\n"));
    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
