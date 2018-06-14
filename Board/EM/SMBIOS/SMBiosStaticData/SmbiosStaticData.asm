;****************************************************************************
;****************************************************************************
;**                                                                        **
;**           (C)Copyright 1985-2016, American Megatrends, Inc.            **
;**                                                                        **
;**                          All Rights Reserved.                          **
;**                                                                        **
;**            5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093           **
;**                                                                        **
;**                          Phone: (770)-246-8600                         **
;**                                                                        **
;****************************************************************************
;****************************************************************************

;****************************************************************************
; $Header: /Alaska/BIN/Modules/SMBIOS/SmbiosStaticData/SmbiosStaticData.asm 12    4/07/16 5:53p Davidd $
;
; $Revision: 12 $
;
; $Date: 4/07/16 5:53p $
;****************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/BIN/Modules/SMBIOS/SmbiosStaticData/SmbiosStaticData.asm $
; 
; 12    4/07/16 5:53p Davidd
; [TAG]  		EIP231162
; [Category]  	New Feature
; [Description]  	Merge Aptio V Smbios -09 changes for Aptio 4
; 4.6.5.5_SMBIOS_40 release
; [Files]  		Smbios.sdl
; SmbiosDynamicData.h
; Smbios.h
; SmbiosStaticData.sdl
; SmbiosStaticData.asm
; SmbData.mac
; SmbMacro.aid
; SmbDesc.def
; 
; 11    2/17/15 1:06p Davidd
; [TAG]  		EIP205509
; [Category]  	Improvement
; [Description]  	Merge Aptio V Smbios EIP193807, 193858, 196901 changes
; into Aptio 4 Smbios
; [Files]  		SmbiosStaticData.asm
; Smbdata.mac
; Smbdesc.def
; 
; 10    3/26/12 12:02p Davidd
; [TAG]  		EIP84370
; [Category]  	New Feature
; [Description]  	Flash memory(type 16 and 17) on aptio
; [Files]  		Smbdata.mac
; SmbiosStaticData.asm
; SmbiosStaticData.sdl
; Smbios.c
; Smbios.mak
; Smbios.h
; 
; 9     2/09/11 10:24a Davidd
; [TAG]           EIP53081
; [Category]      Bug Fix
; [Severity]      Minor
; [Symptom]       Smbios Management Device (type 34) must be enabled in
; order to
;                 see System Power Supply (type 39)
; [RootCause]     Macro to create System Power Supply structure (type 39)
;                 was grouped inside macro to create Smbios Management
; Device
;                 (type 34)
; [Solution]      Seperated Type 39 macro from 34.
; [Files]         SmbiosStaticData.asm
;                 Smbdata.mac
;                 Smbmacro.aid
;                 Smbdesc.def
; 
; 8     4/06/10 10:18a Davidd
; Removed CreateBiosLanguageInfo. It is now dynamically created if
; enabled - EIP 34939
; 
; 7     6/02/09 4:41p Davidd
; Reformatted for Coding Standard compliance.
; 
; 6     6/02/09 3:55p Davidd
; Updated AMI headers (EIP 22180)
; 
; 5     5/19/09 11:02a Davidd
; 
; 4     10/13/08 11:15a Davidd
; Added type 40 and 41 support per SMBIOS specification v2.6
; 
; 3     3/29/07 4:53p Davidd
; Changed the year in the AMI banner and adjust indentation to coding
; standard.
; 
; 2     12/15/06 5:21p Davidd
; Code cleanup and reformatted to coding  standard.
;
; 1     4/29/05 2:15p Davidd
; Initial checkin.
;
;****************************************************************************

;----------------------------------------------------------------------------

        INCLUDE token.equ
        INCLUDE smbhdr.equ
        INCLUDE smbmacro.aid
        INCLUDE smbstruc.def
        INCLUDE smb.equ
        INCLUDE smbdata.mac
        INCLUDE smbdesc.def

;----------------------------------------------------------------------------

SMBIOS_DSEG SEGMENT BYTE    PUBLIC  'DATA'
        ASSUME  cs: SMBIOS_DSEG
.586p

;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
        PUBLIC  _SMBDATA_STARTS
_smbdata_starts         LABEL   BYTE    ; Marks start of module
;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
;   SMBIOS DATA STRUCTURES
;----------------------------------------------------------------------------

;SMBDataModuleHeaderSTRUC   {'_AMIDMI_',0203h,0101h,00h,offset smbios_structures_end,00h}

;----------------------------------------------------------------------------
        PUBLIC  smbios_structures_start
smbios_structures_start LABEL   BYTE

        handle = 0
IF MKF_TYPE0_STRUCTURE
        handle = CreateBiosInfo(handle)
ENDIF
IF MKF_TYPE1_STRUCTURE
        handle = CreateSysInfo(handle)
ENDIF
IF MKF_TYPE2_STRUCTURE
        handle = CreateBaseBoardInfo(handle)
ENDIF
IF MKF_TYPE3_STRUCTURE
        handle = CreateSysChassisInfo(handle)
ENDIF
IF MKF_TYPE4_STRUCTURE
        handle = CreateProcessorInfo(handle)
ENDIF
IF MKF_TYPE5_STRUCTURE
        handle = CreateMemCtrlInfo(handle, handle+1)
ENDIF
IF MKF_TYPE6_STRUCTURE
        handle = CreateMemModuleInfo(handle)
ENDIF
IF MKF_TYPE7_STRUCTURE
        handle = CreateExternalCacheInfo(handle)
ENDIF
IF MKF_TYPE8_STRUCTURE
        handle = CreatePortConnectorInfo(handle)
ENDIF
IF MKF_TYPE9_STRUCTURE
        handle = CreateSystemSlotInfo(handle)
ENDIF
IF MKF_TYPE10_STRUCTURE
        handle = CreateOnboardDeviceInfo(handle)
ENDIF
IF MKF_TYPE11_STRUCTURE
        handle = CreateOemStringInfo(handle)
ENDIF
IF MKF_TYPE12_STRUCTURE
        handle = CreateSystemConfigOptionInfo(handle)
ENDIF
IF MKF_TYPE15_STRUCTURE
        handle = CreateEventLogInfo(handle)
ENDIF
IF MKF_TYPE16_STRUCTURE
        handle = CreateMemoryInfo(handle)
ENDIF
IF MKF_FLASH_MEMORY_ARRAY_INFO
        handle = CreateFlashMemoryInfo(handle)
ENDIF
IF MKF_TYPE21_STRUCTURE
        handle = CreateBuiltinPointingDeviceInfo(handle)
ENDIF
IF MKF_TYPE22_STRUCTURE
        handle = CreatePortableBatteryInfo(handle)
ENDIF
IF MKF_TYPE23_STRUCTURE
        handle = CreateSystemResetInfo(handle)
ENDIF
IF MKF_TYPE24_STRUCTURE
        handle = CreateHardwareSecurityInfo(handle)
ENDIF
IF MKF_TYPE25_STRUCTURE
        handle = CreateSystemPowerControlsInfo(handle)
ENDIF
IF MKF_TYPE30_STRUCTURE
        handle = CreateOutofBandRemoteAccessInfo(handle)
ENDIF
IF MKF_TYPE31_STRUCTURE
        handle = CreateBootIntegrityServicesInfo(handle)
ENDIF
IF MKF_TYPE32_STRUCTURE
        handle = CreateSystemBootInfo(handle)
ENDIF
IF MKF_TYPE33_STRUCTURE
        handle = CreateSixtyFourBitMemoryErrorInfo(handle)
ENDIF
IF MKF_TYPE34_STRUCTURE
        handle = CreateManagementDeviceInfo(handle)
ENDIF
IF MKF_TYPE37_STRUCTURE
        handle = CreateMemoryChannelInfo(handle)
ENDIF
IF MKF_TYPE39_STRUCTURE
        handle = CreateSystemPowerSupplyInfo(handle)
ENDIF
IF MKF_TYPE40_STRUCTURE
        handle = CreateAdditionalInformation(handle)
ENDIF
IF MKF_TYPE41_STRUCTURE
        handle = CreateOnboardDevicesExtendedInfo(handle)
ENDIF
IF MKF_TYPE241_STRUCTURE
        handle = CreateOEMMemoryMappedGpnvInfo(handle)
ENDIF
IF MKF_TYPE240_STRUCTURE
        handle = CreateOEMIOMappedGpnvInfo(handle)
ENDIF
IF MKF_TYPE38_STRUCTURE
        handle = CreateIPMIDeviceInfo(handle)
ENDIF
IF MKF_TYPE129_STRUCTURE
        handle = CreateIntelASFTable(handle)
ENDIF
        handle = CreateEndOfTable(handle)

        db      MKF_EXTRA_RESERVED_BYTES dup (0FFh)          ; Extra Space
SMBIOS_DSEG    ENDS                 ; End of Segment
END                                 ; End of File

;----------------------------------------------------------------------------
;****************************************************************************
;****************************************************************************
;**                                                                        **
;**           (C)Copyright 1985-2016, American Megatrends, Inc.            **
;**                                                                        **
;**                          All Rights Reserved.                          **
;**                                                                        **
;**            5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093           **
;**                                                                        **
;**                          Phone: (770)-246-8600                         **
;**                                                                        **
;****************************************************************************
;****************************************************************************
