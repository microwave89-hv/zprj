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
// $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtOemBoard.h 11    5/19/14 7:15a Barretlin $
//
// $Revision: 11 $
//
// $Date: 5/19/14 7:15a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtOemBoard.h $
// 
// 11    5/19/14 7:15a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Using setup item choose return value of _RMV method in
// ASL code
// [Files]  		TbtDxe.c TbtGpe.asl TbtOemBoard.c TbtOemBoard.h TbtSetup.sd
// TbtSetup.sdl TbtSetup.uni
// 
// 10    2/18/14 7:29a Barretlin
// [TAG]  		EIP152401
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	add new Thunderbolt chip series
// [Files]  		TbtOemBoard.h
// 
// 9     2/10/14 1:26p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	remove useless policy item and setup item
// [Files]  		TbtOemBoard.h TbtOemBoard.c TbSetup.sdl TbtSetup.sd
// TbtSetup.uni TbtSmm.c
// 
// 8     1/05/14 2:06p Barretlin
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Support Thunderbolt feature Enable/Disable in run time
// Support dynamic Thunderbolt AIC location in run time
// [Files]  		TbtOemBoard.h TbtOemBoard.c TbtOemLib.c TbtOemLib.h
// 
// 7     7/26/13 1:53a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix build error at MahoBay/ChiefRiver platform
// [Files]  		TbtPei.c TbtOemBoard.h
// 
// 6     6/21/13 7:50a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix build error with non Intel RC project
// [Files]  		TbtOemBoard.h TbtOemBoard.sdl
// 
// 5     6/17/13 2:18a Barretlin
// [TAG]  		EIP126581
// [Category]  	Improvement
// [Description]  	add new AIC support setup item and change
// TBWakeupSupport name
// [Files]  		TbtOemBoard.h TbtOemBoard.c
// 
// 4     4/24/13 2:40a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Add new series
// [Files]  		TbtOemBoard.h
// 
// 3     4/03/13 3:04a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Adding mask definition for reading Redwood Ridge
// command
// [Files]  		TbtOemBoard.h
// 
// 2     2/06/13 6:33a Barretlin
// [TAG]  		EIP114556
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	Add more definition for Thunderbolt RR Spec 0.9
// [Files]  		TbtOemBoard.h
// 
// 1     1/10/13 4:57a Barretlin
// Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
// Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
// 
// 15    12/12/12 4:14a Barretlin
// [TAG]  		EIP108272
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update to Spec 1.4 to support Redwood Ridge chip
// [Files]  		TbtPei.c TbtSmm.c TbtDxe.c TbtDxe.sdl TbtGpe.asl
// TbtOemBoard.c TbtOemBoard.h TbtOemLib.c TbtOemLib.h
// 
// 14    10/28/12 11:50p Barretlin
// [TAG]  		EIP104870
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change wake up flow for Spec 1.2 and Spec 1.3
// [Files]  		TbtPei.c TbtSmm.c TbtOemBoard.c TbtOemBoard.h
// TbtOemBoard.sdl TbtOemLib.c TbtOemLib.h
// 
// 13    10/28/12 11:21p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Create new setup item for thunderbolt POC handling
// [Files]  		TbtOemBoard.c TbtOemBoard.h TbtSetup.sdl TbtSetup.sd
// TbtSetup.uni
// 
// 12    10/03/12 9:27p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Change Programming security level timing for saving
// boot time
// [Files]  		TbtPei.c TbtDxe.c TbtOemBoard.h TbtOemLib.c TbtOemLib.h
// 
// 11    8/20/12 5:12a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix IO resource workaround broken in 4C 2port case
// [Files]  		TbtSmm.c TbtOemBoard.c TbtOemBoard.h TbtSetup.sdl
// TbtSetup.sd TbtSetup.uni
// 
// 10    8/17/12 8:44a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Add IO resource workaround for Thunderbolt Spec1.1
// Because new spec has removed IO resource for Thunderbolt device
// [Files]  		TbtSmm.c TbtOemBoard.h TbtOemBoard.c TbtSetup.sdl
// TbtSetup.sd TbtSetup.uni 
// 
// 9     7/31/12 4:07a Barretlin
// [TAG]  		EIP96350
// [Category]  	Spec Update
// [Severity]  	Critical
// [Description]  	Updated Thunderbolt specification to version 1.00
// [Files]  		TbtDxe.c TbtSmm.c TbtOemBoard.c TbtOemBoard.h
// TbtOemBoard.sdl TbtSetup.sd TbtSetup.uni
// 
// 8     7/31/12 3:15a Barretlin
// [TAG]  		EIP91119
// [Category]  	Improvement
// [Description]  	Resolution for enable/disable Thunderbolt device option
// rom at POST time
// [Files]  		TbtDxe.c TbtOemBoard.c TbtOemBoard.h TbtOemBoard.sdl
// TbtSetup.sdl TbtSetup.sd TbtSetup.uni
// 
// 7     5/22/12 10:00a Barretlin
// [TAG]  		EIP90650
// [Category]  	Spec Update
// [Description]  	Specificatoin Update 0.94 - The default value of
// OPTIONAL workaround for devices that don't support surprise-removal
// should be disable.
// [Files]  		TbtSmm.c TbtOemBoard.c TbtOemBoard.h
// TbtSetup.sdl TbtSetup.sd TbtSetup.uni
// 
// 6     5/07/12 7:00a Barretlin
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
// 5     3/05/12 1:16a Barretlin
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
// 3     2/20/12 12:57a Wesleychen
// Add new policy "SmiNotifyEnabled".
// 
// 1     12/08/11 4:09a Wesleychen
// Thunderbolt eModule initially releases.
//
//*************************************************************************
#ifndef _THUNDERBOLT_OEM_PROTOCOL_
#define _THUNDERBOLT_OEM_PROTOCOL_

#include <Hob.h>

#define AMI_TBT_PLATFROM_POLICY_PROTOCOL_GUID { 0x380D7A5E, 0x1BCA, 0x11E1, 0xA1, 0x10, 0xE8, 0xEB, 0x47, 0x24, 0x01, 0x9B }

#define AMI_TBT_HR_STATUS_GUID { 0x380D7A5E, 0x1BCA, 0x11E1, 0xA1, 0x10, 0xE8, 0x59, 0x87, 0x32, 0xF1, 0x56 }

#define AMI_TBT_HOB_GUID { 0x380D7A5E, 0x1BCA, 0x11E1, 0xA1, 0x10, 0xE8, 0x5A, 0x87, 0x15, 0x15, 0x47 }

#define TBT_HR_STATUS_VARIABLE L"TbtHRStatusVar"

#define RR_PCIE2TBT 0x54C

#define RR_TBT2PCIE 0x548

#define PCIE2TBT_VLD_B 1

#define TBT2PCIE_DON_R 1

#define MASK_DATA (BIT08 | BIT09 | BIT10 | BIT11)

#define MASK_ERROR (BIT12 | BIT13 | BIT14 | BIT15)

#ifdef PCIEX_BASE_ADDRESS 
#define TBT_CFG_ADDRESS(bus, dev, func, reg) NB_PCIE_CFG_ADDRESS(bus, dev, func, reg)
#endif

#ifndef R_PCH_RCRB_PM_CFG
#define R_PCH_RCRB_PM_CFG   0x3318  // Power Management Configuration Register
#endif

typedef enum {
    Cactus_Ridge = 1,
    Redwood_Ridge,
    Falcon_Ridge,
    BDW_TBT_LP
} TBT_HOST_SERIES;

typedef enum {
    TBT_NORMAL_MODE = 1,
    TBT_NORMAL_MODE_WO_NHI,
    TBT_DIRECT_CONNECTED_WO_NHI,
    TBT_REDRIVER_ONLY,
    TBT_OFF_MODE,
    TBT_DEBUG_MODE,
    TBT_RR_LEGACY_CONNECTION = 0,
    TBT_RR_UNIQUIE_ID,
    TBT_RR_ONE_TIME_SAVED_KEY,
    TBT_RR_DPPLUS
} TBT_SECURITY_TYPE;

typedef enum {
    TBT_GO2SX_WITH_WAKE = 2,
    TBT_GO2SX_NO_WAKE,
    TBT_SX_EXIT_TBT_CONNECTED,
    TBT_SX_EXIT_NO_TBT_CONNECTED,
    TBT_OS_UP,
    TBT_SET_SECURITY_LEVEL = 8,
    TBT_GET_SECURITY_LEVEL
} TBT_RR_COMMOND;

typedef VOID (EFIAPI *TBT_PROGRAM_SEURITY_LVL) (
  IN TBT_SECURITY_TYPE   SecurityLevel
 );

typedef struct _AMI_TBT_HR_STATUS_DATA {
  UINT8                    TbtHRSeries;
  UINT8                    TbtHRStatus;
} AMI_TBT_HR_STATUS_DATA;

typedef struct {
  EFI_HOB_GUID_TYPE        Header;
  UINT8                    TbtSecurityLevelFlag;
} TBT_HOB;

typedef struct _AMI_TBT_PLATFORM_POLICY_PROTOCOL {
  UINT8                    TbtEnable;
  UINT8                    TbtGO2SX;
  UINT8                    TbtForcePWR;
  UINT8                    TbtHotPlugEvt;
  UINT8                    TbtOK2GO2SX_N;
  UINT8                    CacheLineSize;
  UINT8                    TbtWakeupSupport;
  UINT8                    TbtAICSupport;
  UINT8                    TbtHandlePOC;
  UINT8                    TbtSecurityLevel;
  UINT8                    Bus;
  UINT8                    Dev;
  UINT8                    Fun;
  UINT16                   ReserveMemoryPerSlot;
  UINT16                   ReservePMemoryPerSlot;
  UINT8                    ReserveIOPerSlot;
  UINT8                    SmiNotifyEnabled;
  UINT8                    SwSmiEnabled;
  UINT8                    NotifyEnabled;
  UINT8                    TbtRmvReturnValue;
  UINT8                    TbtOptionRom;
  UINT8                    TbtIOresourceEnable;
  UINT8                    TbtNVMversion;
} AMI_TBT_PLATFORM_POLICY_PROTOCOL;

#if !defined TBT_INTEL_RC_CONFIG || TBT_INTEL_RC_CONFIG == 0
#define PCI_DEVICE_NUMBER_PCH_LPC       LPC_DEVICE
#define PCI_FUNCTION_NUMBER_PCH_LPC     LPC_FUNC
#define R_PCH_LPC_GPI_ROUT              0xB8
#define R_PCH_PCIE_CLS                  0x0C
#define R_PCH_PCIE_SLCTL                0x58
#define R_PCH_PCIE_SLSTS                0x5A
#define B_PCH_PCIE_SLSTS_PDS            BIT06
#define R_PCH_PCIE_PMCS                 0xA4
#define B_PCH_PCIE_PMCS_PS              (BIT00 | BIT01)
#endif // TBT_INTEL_RC_CONFIG == 0

#endif // _THUNDERBOLT_OEM_PROTOCOL_
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
