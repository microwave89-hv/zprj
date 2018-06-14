//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPlatformPolicy/AmtPlatformPolicy.h 4     8/22/13 8:52a Tristinchou $
//
// $Revision: 4 $
//
// $Date: 8/22/13 8:52a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPlatformPolicy/AmtPlatformPolicy.h $
// 
// 4     8/22/13 8:52a Tristinchou
// [TAG]  		EIP131034
// [Category]  	Improvement
// [Description]  	The system will hang after create/ reset/delete raid
// mode
// [Files]  		AmtPlatformPolicy.h
// 
// 3     5/14/12 4:50a Klzhan
// [TAG]  		EIP89952
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC 0.56
// [Files]  		AmtPlatformPolicy.c
// AmtPlatformPolicy.h
// AmtPlatformPolicy.sdl
// AmtPlatformPolicy.mak
// AmtPlatformPolicy.dxs
// AmtPlatformPolicy.cif
// 
// 2     4/24/12 12:41a Klzhan
// 
// 1     2/08/12 1:08a Klzhan
// Initial Check in 
// 
// 2     9/26/11 6:19a Klzhan
// [TAG]  		EIP70516
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME 8.0 RC 0.8
// [Files]  		AmtPlatformPolicy.c
// AmtPlatformPolicy.h
// AmtPlatformPolicy.sdl
// AmtPlatformPolicy.mak
// AmtPlatformPolicy.dxs
// AmtPlatformPolicy.cif
// 
// 1     2/25/11 1:45a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:11a Klzhan
// Initial Check-in.
//
//**********************************************************************
#ifndef _DXE_AMT_PLATFORM_POLICY_H_
#define _DXE_AMT_PLATFORM_POLICY_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#endif

#include EFI_PROTOCOL_DEFINITION (MeBiosPayloadData)
#include EFI_PROTOCOL_PRODUCER (AmtPlatformPolicy)
#include EFI_GUID_DEFINITION (MeBiosExtensionSetup)
#include "MeLib.h"
#include "Include\Protocol\PDiskInfo.h"
#include "Include\Protocol\PIDEController.h"
// Debug #include "AmtPlatformPolicyUpdateDxeLib.h"

typedef
struct _INSTALL_DISK_INFO_PROTOCOL INSTALL_DISK_INFO_PROTOCOL;

// Based on ATA/ATAPI-6
#pragma pack (1)
typedef struct _IDENTIFY_DATA{ 

	UINT16	General_Config_0;
	UINT16	Reserved_1;
	UINT16	Special_Config_2;
	UINT16	Reserved_3;
	UINT16	Reserved_4;
	UINT16	Reserved_5;
	UINT16	Reserved_6;
	UINT16	Reserved_7;
	UINT16	Reserved_8;
	UINT16	Reserved_9;
	UINT8	Serial_Number_10[20];
	UINT16	Reserved_20;
	UINT16	Reserved_21;
	UINT16	Reserved_22;
	UINT8	Firmware_Revision_23[8];
	UINT8	Model_Number_27[40];
	UINT16	Maximum_Sector_Multiple_Command_47;
	UINT16	Reserved_48;
	UINT16	Capabilities_49;
	UINT16	Capabilities_50;
	UINT16	PIO_Mode_51;
	UINT16	Reserved_52;
	UINT16	Valid_Bits_53;
	UINT16	Reserved_54_58[5];
	UINT16	Valid_Bits_59;
	UINT32	Addressable_Sector_60;
	UINT16	SingleWord_DMA_62;
	UINT16	MultiWord_DMA_63;
	UINT16	PIO_Mode_64;
	UINT16	Min_Multiword_DMA_timing_65;
	UINT16	Manuf_Multiword_DMA_timing_66;
	UINT16	Min_PIO_Mode_timing_67;
	UINT16	Min_PIO_Mode_timing_68;
	UINT16	Reserved_69_74[6];
	UINT16	Queue_Depth_75;
	UINT16	Reserved_76_79[4];
	UINT16	Major_Revision_80;
	UINT16	Minor_Revision_81;
	UINT16	Command_Set_Supported_82;
	UINT16	Command_Set_Supported_83;
	UINT16	Command_Set_Supported_84;
	UINT16	Command_Set_Enabled_85;
	UINT16	Command_Set_Enabled_86;
	UINT16	Command_Set_Enabled_87;
	UINT16	UDMA_Mode_88;
	UINT16	Time_security_Earse_89;
	UINT16	Time_Esecurity_Earse_90;
	UINT16	Current_Power_Level_91;
	UINT16	Master_Password_Rev_92;
	UINT16	Hard_Reset_Value_93;
	UINT16	Acoustic_Level_94;
	UINT16	Reserved_95_99[5];
	UINT64	LBA_48;
	UINT16	Reserved_104_126[23];
	UINT16	Status_Notification_127;
	UINT16	Security_Status_128;
	UINT16	Reserved_129_159[31];
	UINT16	CFA_Power_Mode_160;
	UINT16	Reserved_161_175[15];
	UINT16	Media_Serial_Number_176_205[30];
	UINT16	Reserved_206_254[49];
	UINT16	Checksum_255;
} IDENTIFY_DATA;
#pragma pack ()

EFI_STATUS
AmtDxePolicyInitEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN OUT EFI_SYSTEM_TABLE *SystemTable
  )
/*++

Routine Description:

  Initilize Intel AMT DXE Platform Policy

Arguments:

  ImageHandle - Image handle of this driver.
  SystemTable - Global system service table.

Returns:

  EFI_SUCCESS           Initialization complete.
  EFI_UNSUPPORTED       The chipset is unsupported by this driver.
  EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  EFI_DEVICE_ERROR      Device error, driver exits abnormally.

--*/
;
EFI_STATUS
EFIAPI
InstallDiskInfo (
  VOID
  );

typedef
EFI_STATUS
(EFIAPI *INSTALL_DISK_INFO) (
  VOID
  );

typedef struct _INSTALL_DISK_INFO_PROTOCOL {
  INSTALL_DISK_INFO Install; 
}INSTALL_DISK_INFO_PROTOCOL;

#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************