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
// $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtOemLib.h 4     5/19/14 7:38a Barretlin $
//
// $ReviGpion: 1 $
//
// $Date: 5/19/14 7:38a $
//*************************************************************************
// ReviGpion History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtOemLib.h $
// 
// 4     5/19/14 7:38a Barretlin
// [TAG]  		EIP165410
// [Category]  	New Feature
// [Description]  	Support Thunderbolt AIC at NB PCIE slot
// [Files]  		TbtPei.c TbtDxe.c TbtGpe.asl TbtSmm.c TbtOemBoard.c
// TbtOemLib.c TbtOemLib.h TbtSetup.sdl TbtSetup.sd TbtSetup.uni
// TbtSetupReset.c
// 
// 3     1/05/14 2:06p Barretlin
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Support Thunderbolt feature Enable/Disable in run time
// Support dynamic Thunderbolt AIC location in run time
// [Files]  		TbtOemBoard.h TbtOemBoard.c TbtOemLib.c TbtOemLib.h
// 
// 2     4/03/13 2:47a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Double check Security Level between Thunderbolt host FW
// and BIOS are same or not for Redwood Ridge chip when entering setup
// page.
// [Files]  		TbtOemLib.c TbtOemLib.h TbtSetupReset.c
// 
// 1     1/10/13 4:57a Barretlin
// Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
// Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
// 
// 7     12/12/12 4:14a Barretlin
// [TAG]  		EIP108272
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update to Spec 1.4 to support Redwood Ridge chip
// [Files]  		TbtPei.c TbtSmm.c TbtDxe.c TbtDxe.sdl TbtGpe.asl
// TbtOemBoard.c TbtOemBoard.h TbtOemLib.c TbtOemLib.h
// 
// 6     10/28/12 11:50p Barretlin
// [TAG]  		EIP104870
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change wake up flow for Spec 1.2 and Spec 1.3
// [Files]  		TbtPei.c TbtSmm.c TbtOemBoard.c TbtOemBoard.h
// TbtOemBoard.sdl TbtOemLib.c TbtOemLib.h
// 
// 5     10/04/12 10:42p Barretlin
// [TAG]  		EIP102947
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	Update Thunderbolt Spec to Rev 1.2
// [Files]  		TbtPei.c TbtOemLib.c TbtOemLib.h
// 
// 4     10/03/12 9:27p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Change Programming security level timing for saving
// boot time
// [Files]  		TbtPei.c TbtDxe.c TbtOemBoard.h TbtOemLib.c TbtOemLib.h
// 
// 3     3/05/12 1:16a Barretlin
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
// 1     2/19/12 11:56p Wesleychen
// [TAG]         None
// [Category]    Improvement
// [Description] Add TbtOemLib.
// [Files]       TbtOemLib.c; TbtOemLib.h; TbtOemBoard,mak;
//               TbtOemBoard.cif.
// 
// 1     12/08/11 4:09a Wesleychen
// Thunderbolt eModule initially releases.
//
//*************************************************************************
#ifndef _THUNDERBOLT_OEM_LIB_
#define _THUNDERBOLT_OEM_LIB_

#include "TbtOemBoard.h"

UINT8 ReadSio(
  IN UINT8           Index
);

VOID WriteSio(
  IN UINT8           Index,
  IN UINT8           Value
);

VOID SetSio(
  IN UINT8           Index,
  IN UINT8           Set
);

VOID ResetSio(
  IN UINT8           Index,
  IN UINT8           Rst
);

VOID OpenSioConfig(
  VOID
);

VOID SetSioLdn(
  IN UINT8           Ldn
);

UINT8 GetHRInfo(
  VOID
);

BOOLEAN TbtSetPCIe2TBTCommand(
  IN UINT8             UpPortBus,
  IN UINT8             Data,
  IN UINT8             Command,
  IN UINTN             Timeout
);

VOID TbtBeforeSxExitFlow(
  IN VOID              *Services,
  IN UINT8             TbtHostSeries
);

UINT8 SynchSecurityLevel(
  IN UINT8             BiosSecurityLevel,
  IN UINT8             TbtHostLocation
);

VOID ProgramTbtSecurityLevel(
  IN UINT8             *TbtSecurityLevel,
  IN UINT8             TbtHostSeries,
  IN UINT8             TbtHostLocation,
  IN BOOLEAN           IsPei
);

VOID PeiFinialProgramTbtSecurityLevel(
  IN UINT8             TbtSecurityLevel
);

VOID FinialProgramTbtSecurityLevel(
  IN AMI_TBT_PLATFORM_POLICY_PROTOCOL *PlatformPolocy
);

EFI_STATUS ActiveTbtGpio2(
  VOID
);

EFI_STATUS InactiveTbtGpio2(
  VOID
);

EFI_STATUS PollTbtGpio9(
  VOID
);

EFI_STATUS PullDownTbtGpio9(
  VOID
);

EFI_STATUS ReleaseTbtGpio9(
  VOID
);

EFI_STATUS PowerOnPOC(
  VOID
);

EFI_STATUS PowerOffPOC(
  VOID
);

#endif // _THUNDERBOLT_OEM_LIB_
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
