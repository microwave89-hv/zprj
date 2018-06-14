//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtSetup/TbtSetupReset.c 8     5/19/14 7:40a Barretlin $
//
// $Revision: 8 $
//
// $Date: 5/19/14 7:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtSetup/TbtSetupReset.c $
// 
// 8     5/19/14 7:40a Barretlin
// [TAG]  		EIP165410
// [Category]  	Improvement
// [Description]  	Support Thunderbolt AIC at NB PCIE slot
// [Files]  		TbtPei.c TbtDxe.c TbtGpe.asl TbtSmm.c TbtOemBoard.c
// TbtOemLib.c TbtOemLib.h TbtSetup.sdl TbtSetup.sd TbtSetup.uni
// TbtSetupReset.c
// 
// 7     1/05/14 2:14p Barretlin
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Support Thunderbolt feature Enable/Disable in run time
// Support dynamic Thunderbolt AIC location in run time
// [Files]  		TbtSetup.sdl TbtSetup.sd TbtSetup.uni TbtSetupReset.c
// 
// 6     6/21/13 7:53a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix build error with non Intel RC project
// [Files]  		TbtSetupReset.c
// 
// 5     6/21/13 5:16a Barretlin
// [TAG]  		EIPNone
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	can not change Falcon Ridge security level
// [RootCause]  	can not regconize Falcon Ridge chip
// [Solution]  	add Falcon Ridge chip
// [Files]  		TbtSetupReset.c
// 
// 4     4/12/13 1:03p Barretlin
// 
// 3     4/03/13 2:54a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Double check Security Level between Thunderbolt host FW
// and BIOS are same or not for Redwood Ridge chip when entering setup
// page.
// [Files]  		TbtOemLib.c TbtOemLib.h TbtSetupReset.c
// 
// 2     2/06/13 2:25a Barretlin
// 
// 1     1/10/13 4:57a Barretlin
// Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
// Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
// 
// 1     12/12/12 4:40a Barretlin
// [TAG]  		None
// [Category]  	New Feature
// [Description]  	Add Thunderbolt TSE Setup Reset Hook
// [Files]  		TbtSetupReset.c
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  TbtSetupReset.c
//
// Description:	Setup Reset Rountines
//
//<AMI_FHDR_END>
//**********************************************************************

#include <EFI.h>
#include <Token.h>
#include <Setup.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <TbtOemLib.h>
#include <TbtOemBoard.h>
#if defined(RESET_RUNTIME_SERVICES_SUPPORT) && (RESET_RUNTIME_SERVICES_SUPPORT == 0)
#include <Protocol\PchReset\PchReset.h>
#else
#include <AmiCSPLib.h>
#if defined TBT_INTEL_RC_CONFIG && TBT_INTEL_RC_CONFIG == 1
#include <PchRegsLpc.h>
#endif
#endif

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
static SETUP_DATA        gNewSetupData;
static SETUP_DATA        gOldSetupData;

//----------------------------------------------------------------------------
// GUID Definition(s)
//----------------------------------------------------------------------------
static EFI_GUID          gEfiSetupGuid    = SETUP_GUID;
static EFI_GUID          TbtHRStatusGuid  = AMI_TBT_HR_STATUS_GUID;

UINTN                    HRStatusSize     = sizeof(AMI_TBT_HR_STATUS_DATA);
AMI_TBT_HR_STATUS_DATA   HRStatusData;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TbtProcessEnterSetup
//
// Description:	This function is a hook called when TSE determines
//              that it has to load the boot options in the boot
//              order. This function is available as ELINK.
//
// Input:       VOID
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TbtProcessEnterSetup(VOID)
{
    EFI_STATUS              Status;
    UINTN                   VariableSize = sizeof (SETUP_DATA);
    UINT8                   SecurityLevelState;
    
    TRACE((-1, "TbtSetupReset.c: TbtProcessEnterSetup().....\n"));
    Status = pRS->GetVariable(
                            L"Setup",
                            &gEfiSetupGuid,
                            NULL,
                            &VariableSize,
                            &gOldSetupData);
    ASSERT_EFI_ERROR(Status);
    
    Status = pRS->GetVariable( L"TbtHRStatusVar", \
                               &TbtHRStatusGuid, \
                               NULL, \
                               &HRStatusSize, \
                               &HRStatusData );
    ASSERT_EFI_ERROR(Status);

    //
    // synchronize Thunderbolt security level config between BIOS and Thunderbolt
    // host FW
    if ((gOldSetupData.TbtEnable != 0) && (HRStatusData.TbtHRSeries != Cactus_Ridge)){
        SecurityLevelState = SynchSecurityLevel(gOldSetupData.TbtSecurityLevel, gOldSetupData.TbtHostLocation);
        TRACE((-1, "TbtSetupReset: Synchronizing Security Level between host Fw and BIOS state is %x\n", SecurityLevelState));
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TbtSetupResetHook
//
// Description:	This function is a hook called after some control 
//              modified in the setup utility by user. This
//              function is available as ELINK.
//
// Input:       VOID
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TbtSetupResetHook(VOID)
{
    EFI_STATUS              Status;
    UINT8                   SetSecurityFlag = 0;
    UINT8                   ResetFlag = 0;    
    UINTN                   VariableSize;
    
    VariableSize = sizeof (SETUP_DATA);
    Status = pRS->GetVariable (
                        L"Setup",
                        &gEfiSetupGuid,
                        NULL,
                        &VariableSize,
                        &gNewSetupData);
    ASSERT_EFI_ERROR(Status);
    
    if ((!EFI_ERROR (Status)) && (gNewSetupData.TbtEnable != 0) && \
      (HRStatusData.TbtHRSeries != Cactus_Ridge))
    {
        // Check Security Setup Setting first
        if (gNewSetupData.TbtSecurityLevel != gOldSetupData.TbtSecurityLevel){
            SetSecurityFlag |= 1;
        } // Thunderbolt security level changed by user

        // Check Thunderbolt host location 
        if (gNewSetupData.TbtHostLocation != gOldSetupData.TbtHostLocation){
            ResetFlag |= 1;
        }

        // programming Redwood Ridge's/Falcon Ridge's/Win Ridge's Security Level
        if (SetSecurityFlag != 0){
            ProgramTbtSecurityLevel(&(gNewSetupData.TbtSecurityLevel), HRStatusData.TbtHRSeries, gNewSetupData.TbtHostLocation, FALSE);
            ResetFlag |= 1;
        }

        // Reset system if need
        if(ResetFlag != 0){
#if defined(RESET_RUNTIME_SERVICES_SUPPORT) && (RESET_RUNTIME_SERVICES_SUPPORT == 0)
            pRS->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
#else
#if defined TBT_INTEL_RC_CONFIG && TBT_INTEL_RC_CONFIG == 1
            SBLib_ExtResetSystem (SbResetFull);
#else
            SBLib_ResetSystem(FullReset);
#endif
#endif
            EFI_DEADLOOP();
        }
    } // Get New Setup Data success && Thunderbolt Function is enable
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************