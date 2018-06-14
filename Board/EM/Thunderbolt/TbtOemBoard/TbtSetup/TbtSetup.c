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
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtSetup/TbtSetup.c 5     2/18/14 7:31a Barretlin $
//
// $Revision: 5 $
//
// $Date: 2/18/14 7:31a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtSetup/TbtSetup.c $
// 
// 5     2/18/14 7:31a Barretlin
// [TAG]  		EIP152401
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	add new thunderbolt chip series
// [Files]  		TbtSetup.c
// 
// 4     6/19/13 8:33a Barretlin
// [TAG]  		EIP126581
// [Category]  	Improvement
// [Description]  	use thunderbolt FR spec token to update setup string
// [Files]  		TbtSeup.c
// 
// 3     6/16/13 10:23p Barretlin
// [TAG]  		EIP None
// [Category]  	Improvement
// [Description]  	change CR BIOS Spec version display way
// [Files]  		TbtSetup.c
// 
// 2     5/27/13 8:15a Barretlin
// [TAG]  		EIP124914
// [Category]  	New Feature
// [Description]  	Support Falcon Ridge chip
// [Files]  		TbtSetup.c
// 
// 1     1/10/13 4:57a Barretlin
// Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
// Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
// 
// 4     8/16/12 4:19p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Add Thunderbolt Intel Sample Code version information
// [Files]  		Thunderbolt.sdl TbtSetup.sd TbtSetup.uni TbtSetup.c
// 
// 3     7/31/12 5:28a Barretlin
// 
// 2     5/24/12 10:20p Barretlin
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add Thunderbolt version on setup menu
// [Files]  		TbtSetup.sd TbtSetup.uni TbtSetup.c
// Thunderbolt.sdl
// 
// 1     12/08/11 4:09a Wesleychen
// Thunderbolt eModule initially releases.
// 
//**********************************************************************
#include <token.h>
#include <Setup.h>
#include <AmiCSPLib.h>
#include <AmiDxeLib.h>
#include <TbtOemBoard.h>
#include <SetupStrTokens.h>
#if EFI_SPECIFICATION_VERSION>0x20000
#include <Protocol\HiiDatabase.h>
#include <Protocol\HiiString.h>
#else
#include <Protocol/Hii.h>
#endif

//----------------------------------------------------------------------------
// GUID Definition(s)
//----------------------------------------------------------------------------
static EFI_GUID  TbtHRStatusGuid           = AMI_TBT_HR_STATUS_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitiTbtInfo
//
// Description: Initializes Thunderbolt Setup String
//
// Input:       HiiHandle - Handle to HII database
//              Class - Indicates the setup class
//
// Output:      None
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitiTbtInfo(
  IN EFI_HII_HANDLE   HiiHandle,
  IN UINT16           Class )
{
  EFI_STATUS              Status;
  UINTN                   HRStatusSize     = sizeof(AMI_TBT_HR_STATUS_DATA);
  CHAR16                  TbtHRStatusVar[] = TBT_HR_STATUS_VARIABLE;
  AMI_TBT_HR_STATUS_DATA  HRStatusData;
  CHAR16                  *TbtCR           = L"Cactus Ridge";
  CHAR16                  *TbtRR           = L"Redwood Ridge";
  CHAR16                  *TbtFR           = L"Falcon Ridge";
  CHAR16                  *TbtWR           = L"BDW-TBT-LP(WR)";

  Status = pRS->GetVariable( L"TbtHRStatusVar", \
                             &TbtHRStatusGuid, \
                             NULL, \
                             &HRStatusSize, \
                             &HRStatusData );

  TRACE((-1, "TbtSetup: HR is %x series\n", HRStatusData.TbtHRSeries));

  InitString(HiiHandle, STRING_TOKEN(STR_TBT_RC_VERSION_VALUE),
                L"%d.%d", TBT_RC_VERSION/10, TBT_RC_VERSION%10);

  if (HRStatusData.TbtHRSeries == Cactus_Ridge){
     InitString(HiiHandle, STRING_TOKEN(STR_TBT_SPEC_VERSION_VALUE),
                   L"%d.%d", Thunderbolt_CR_VERSION/10, Thunderbolt_CR_VERSION%10);

     InitString(HiiHandle, STRING_TOKEN(STR_TBT_HOST_VALUE),
                   L"%s", TbtCR);
  } else if (HRStatusData.TbtHRSeries == Redwood_Ridge) {
     InitString(HiiHandle, STRING_TOKEN(STR_TBT_SPEC_VERSION_VALUE),
                   L"%d.%d", Thunderbolt_RR_VERSION/10, Thunderbolt_RR_VERSION%10);

     InitString(HiiHandle, STRING_TOKEN(STR_TBT_HOST_VALUE),
                   L"%s", TbtRR);
  } else if (HRStatusData.TbtHRSeries == Falcon_Ridge){
     InitString(HiiHandle, STRING_TOKEN(STR_TBT_SPEC_VERSION_VALUE),
                   L"%d.%d", Thunderbolt_FR_VERSION/10, Thunderbolt_FR_VERSION%10);

     InitString(HiiHandle, STRING_TOKEN(STR_TBT_HOST_VALUE),
                   L"%s", TbtFR);
  } else {
     InitString(HiiHandle, STRING_TOKEN(STR_TBT_SPEC_VERSION_VALUE),
                   L"%d.%d", Thunderbolt_WR_VERSION/10, Thunderbolt_WR_VERSION%10);

     InitString(HiiHandle, STRING_TOKEN(STR_TBT_HOST_VALUE),
                   L"%s", TbtWR);
  }
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