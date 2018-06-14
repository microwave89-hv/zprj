//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/OFBD/OFBD.h 20    7/31/13 4:55a Terrylin $
//
// $Revision: 20 $
//
// $Date: 7/31/13 4:55a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD/OFBD.h $
// 
// 20    7/31/13 4:55a Terrylin
// [TAG]  		EIP125898
// [Category]  	Improvement
// [Description]  	1. Update modules to compliant with PI 1.2 and UEFI
// 2.3.1 specifications. 
// 2. Add OFBD_TC_51_DC_EXT_STRUCT new structure definition.
// [Files]  		OFBD.c
// OFBD.h
// 
// 19    10/11/12 2:34a Terrylin
// [Category]  	New Feature
// [Description]  	Add BatteryCheck component for OEM can use this to
// replace Legacy ECB table check support in Non-CSM environment.
// [Files]  		OFBD.sdl
// OFBD.h
// OFBD.cif
// 
// 18    7/24/12 3:59a Terrylin
// [Category]  	Improvement
// [Description]  	Add new Return Statuses of Type Code 51 for AFU general
// commands.
// 
// 17    2/22/12 4:39a Terrylin
// Add new command status for GAN support
// 
// 16    10/27/11 5:01a Terrylin
// Add new command status of Secure Update.
// 
// 15    10/24/11 2:47a Terrylin
// Adjust the OEM OA module part definitions.
// 
// 14    10/13/11 11:23p Terrylin
// [TAG]  		EIP72332
// [Category]  	Improvement
// [Description]  	Add new Return Statuses of Type Code 51 for AFU general
// commands.
// 
// 13    9/19/11 5:03a Terrylin
// Added OEM OA module part definitions.
// 
// 12    9/15/11 11:43p Calvinchen
// Added Secure Update OFBD definitions.
// 
// 11    7/21/11 5:54a Terrylin
// [TAG]  		EIP46069
// [Category]  	Improvement
// [Description]  	Support Runtime secure flash update mode
// 
// 10    7/07/11 1:52a Terrylin
// [TAG]  		EIP46069
// [Category]  	New Feature
// [Description]  	Support Secure Flash Update interface via OFBD
// protocols
// [Files]  		OFBD.h
// OFBD.cif
// 
// 9     4/20/11 6:46a Terrylin
// [TAG]  		EIP52968
// [Category]  	Improvement
// [Description]  	Adjust OFBD_TC_55_MEUD_STRUCT structure, for new ME
// firmware update rule.
// 
// 8     3/16/11 10:39p Terrylin
// Correct Copyright information.
// 
// 7     3/16/11 10:13p Terrylin
// [TAG]  		EIP51285
// [Category]  	Improvement
// [Description]  	Fill the description of each file for user more
// clearly.
// [Files]  		OFBD.mak
// OFBD.dxs
// OFBD.c
// OFBD.h
// 
// 6     1/17/11 4:01a Terrylin
// [TAG]  		EIP51076
// [Category]  	New Feature
// [Description]  	Add some new statuses for "/CLNEVNLOG" command of AFU.
// 
// 5     8/11/10 11:13p Terrylin
// Add some new statuses for /CMD: command.
// 
// 4     5/06/10 2:10a Lawrencechang
// 1. Modify the Type Code 51 Structure and Return Status.
// 2. Add some new statuses for /ECX command.
// 3. Add new DMI flags for /R command.
// 
// 3     1/11/10 3:45a Lawrencechang
// Modify Type#50 ROM hole structure.
// 
// 2     12/01/09 4:35a Lawrencechang
// Add a new status for /ECX command.
// 
// 1     4/13/09 5:46a Lawrencechang
// Initial check-in.
// 
// 1     3/13/06 1:16a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	OFBD.h
//
// Description: Header file for the OFBD
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _EFI_OFBD_H_
#define _EFI_OFBD_H_
#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
//	On Flash Block Structure Definition
//----------------------------------------------------------------------------
//=======================
// OFBD Header structure 
//=======================
#pragma pack(1)
typedef struct 
{
	UINT32 OFBD_SIG;            //'OFBD'
    UINT16 OFBD_VER;            //0200
    UINT16 OFBD_Size;     
    UINT32 OFBD_FS;    
    UINT16 OFBD_RS;      
	UINT16 OFBD_HDR_SIZE;
	UINT16 OFBD_OS;	
}OFBD_HDR;
#pragma pack()

//=================
// On Flash Status 
//=================
#define     OFBD_FS_VC		BIT00
#define     OFBD_FS_BBLK 	BIT01
#define     OFBD_FS_NVRAM   BIT02
#define     OFBD_FS_MAIN 	BIT03
#define     OFBD_FS_NCB		BIT04
#define     OFBD_FS_ROMH 	BIT05
#define     OFBD_FS_SFU	    BIT06
#define     OFBD_FS_OA	    BIT07
#define     OFBD_FS_AC_BAT	BIT16
#define     OFBD_FS_SECURUD	BIT22
#define     OFBD_FS_ERR_LOG	BIT23
#define     OFBD_FS_OEM_CMD	BIT24
#define     OFBD_FS_SETUP	BIT25
#define		OFBD_FS_MEUD    BIT26
#define     OFBD_FS_EC		BIT27
#define     OFBD_FS_ORI		BIT28
#define     OFBD_FS_PWD		BIT29
#define     OFBD_FS_CFG		BIT30

//================
// Return  Status 
//================
#define OFBD_RS_SUPPORT         BIT00
#define OFBD_RS_PROTECT	        BIT01
#define OFBD_RS_PROTECT_PART    BIT02
#define OFBD_RS_ERR_OUT         BIT03
#define OFBD_RS_DIS_OEMSTR      BIT04

//================
// OS environment 
//================
#define OFBD_OS_DOS 	BIT00
#define OFBD_OS_WIN 	BIT01
#define OFBD_OS_LINUX 	BIT02
#define OFBD_OS_FREEBSD	BIT03
#define OFBD_OS_EFI	    BIT04

//===============================
// Extended Table Header  Status 
//===============================
#pragma pack(1)
typedef struct
{
	UINT8 TypeCodeID;
	UINT8 NumTCStruct;
	UINT16 TCStructSize;
}OFBD_EXT_HDR;

typedef struct
{
    UINT32 	OFBD_END;
}OFBD_END;
#pragma pack()

#define OFBD_EXT_TBL_END	0x0FFFF55AA

//================
// Type Code ID   
//================
#define OFBD_EXT_TC_ROMHOLE		0x50
#define OFBD_EXT_TC_AFUDEFCFG	0x51
#define OFBD_EXT_TC_PWD			0x52
#define OFBD_EXT_TC_ORI			0x53
#define OFBD_EXT_TC_EC			0x54
#define OFBD_EXT_TC_MEUD		0x55
#define OFBD_EXT_TC_SETUP		0x56
#define OFBD_EXT_TC_OEM_CMD		0x57
#define OFBD_EXT_TC_CLN_ERR_LOG	0x58
#define OFBD_EXT_TC_SECURE_UD	0x59
#define OFBD_EXT_TC_OA_HANDLE   0x5A
#define OFBD_EXT_TC_AC_BAT		0x5B
#define OFBD_EXT_TC_SFU         0x70

//----------------------------------------------------------------------------
//	On Flash Block Type Code Structure Section
//----------------------------------------------------------------------------
#pragma pack(1)
//===============================
// Type Code 50 Struct ROM HOLE  
//===============================
typedef struct
{
    UINT32      ddExtCmd;
    EFI_GUID    HoleGuid;
}OFBD_TC_50_RH_STRUCT;

//===============================
// Type Code 51 Struct Def Cfg   
//===============================
typedef struct
{
	UINT32 ddExtCfg;
	UINT32 ddRetSts;
}OFBD_TC_51_DC_STRUCT;

typedef struct
{
    UINT32 ddIndexCfg;
	UINT16 ddExtCfg;
	UINT16 ddIgnCfg;
}OFBD_TC_51_DC_EXT_STRUCT;

//=======================
// Type Code 52 Struct   
//=======================
typedef struct
{
    UINT16 dwPwdLen;        //Password Length
    UINT8 dbGetCkSts;       //Get Check Status
    UINT8 dbRetSts;         //Return Status
}OFBD_TC_52_PC_STRUCT;
 
//=================================
// Type Code 53 Struct OEM ROM ID  
//=================================
typedef struct
{
	UINT8 dwGetCkSts;
	UINT8 dwRetSts;
	UINT32 ddStartAddrLow;
	UINT32 ddStartAddrHigh;
	UINT32 ddSize;
}OFBD_TC_53_ORI_STRUCT;

//=======================================
// Type Code 54 Struct Standard EC Flash	
//=======================================
typedef struct
{
	UINT8 dbFlaSts;			//EC Set & Check Status
	UINT16 dwRetSts;		//EC Return Status
	UINT32 ddChkSum;		//EC Data CheckSum
	UINT32 ddSize;			//EC Data Size
}OFBD_TC_54_STD_EC_STRUCT;

//=======================================
// Type Code 55 - ME Ignition Firmware Update Structure

//=======================================
typedef struct 
{
    UINT8	bReturnStatus;
    UINT8	bSubFunction;
    UINT32	dMERuntimeBase;
    UINT32	dMERuntimeLength;
    UINT32	dMEBiosRegionBase;
    UINT32	dMEBiosRegionLength;
#if (OFBD_VERSION >= 0x0210)
    UINT32	ddFlashBufOffset;
    UINT32	ddBlockAddr;
    UINT32	ddBlockSize;
#endif
}OFBD_TC_55_MEUD_STRUCT;

//=======================================
// Type Code 56 Struct 
//=======================================
typedef struct
{
    UINT8 dbGetSts;         //Get Status
    UINT8 dbRetSts;         //Return Status
}OFBD_TC_56_SETUP_STRUCT;

//=======================================
// Type Code 57 Struct 
//=======================================
typedef struct 
{
    UINT16 	dwFlaSts;		// 0: Before Flash, 1: After Flash, 2: Before End
    UINT16 	dwRetSts;		// 0: Failure, 1: Successfully
    UINT32 	ddCMD;			// Bit 0~15: OEM CMD
    UINT32	ddReserve;		// Reserve
} OFBD_TC_57_OEM_CMD_STRUCT;


//=======================================
// Type Code 58 Struct 
//=======================================
typedef struct 
{
    UINT16 	dwFunSts;		// 0: Do nothing 1: Clean Event Log
    UINT16 	dwRetSts;		// 0: Failure, 1: Successfully
} OFBD_TC_58_CEL_STRUCT;

//=======================================
// Type Code 59 Struct 
//=======================================
typedef struct 
{
    UINT64      BufAddr;
    UINT32      BlockAddr;      //0 starts at 0xfff0_0000
    UINT32      BlockSize;
    UINT8       ErrorCode;
    UINT8       bSubFunction;
} OFBD_TC_59_SECURE_UD;

//=======================================
// Type Code 5A Struct 
//=======================================
typedef struct 
{
    UINT8 	dbOASts;		// Bit 0: Notification BIOS, utility is now ready to update the OA data.                                - OFBD_TC_OA_UPDATE_NOTIFY
                            // Bit 1~7: Reserved
                            
    UINT8 	dbErrorID;		// 0~255 : Filled by O.E.M.
    
    UINT16 	dwRetSts;		// Bit 0: OA data is invalid, tell the utility stop the flash procedure                                 - OFBD_RS_OA_DATA_IS_INVALID
                            // Bit 1: OA data has be modified, tell the utility use the new data to update                          - OFBD_RS_OA_DATA_IS_MODIFIED
                            // Bit 2: BIOS has updated the OA, so tell the utility doesn't to update                                - OFBD_RS_OA_UPDATE_SKIPPED
                            // Bit 3: BIOS doesn't allow the OA update, tell the utility stop the flash procedure                   - OFBD_RS_OA_UPDATE_DECLINED
                            // Bit 4~14: Reserved
                            // Bit 15: Use dbErrorID field for utility return OEM specific error code, when this Bit is set to 1.   - OFBD_RS_OA_USE_OEM_ERROR_ID
	UINT32  ddOABlockAddr;  // OA Block Address of BIOS ROM (For NCB mode to use)
    UINT64  ddOADataBuffer; // OA Data Buffer
    UINT32  dwOADataSize;   // OA Data Buffer Size
} OFBD_TC_5A_OA_HANDLE_STRUCT;

//=======================================
// Type Code 5B Struct 
//=======================================
typedef struct
{
    UINT8   dbGetSts;         // Get Status
    UINT8   dbRetSts;         // Return Status

} OFBD_TC_5B_AC_BATTERY_STRUCT;

//=======================================
// Type Code 70 Struct 
//=======================================
typedef struct
{
	UINT8	Command;
	UINT8	Status;
} OFBD_TC_70_SFU_STRUCT;
#pragma pack()

//=============================
// Type Code Specific Status   
//=============================
//=============================
// Type Code 50 Return Status 
//=============================
#define  OFBD_TC_GRS_PROTECT		BIT00

//===============================
// Type Code 50 Hole Description 
//===============================
#define OFBD_TC_RH_HD_ROMHOLE		BIT00
#define OFBD_TC_RH_HD_NCB			BIT01

//=============================
// Type Code 51 Return Status  
//=============================
#define OFBD_TC_CFG_P			BIT00
#define OFBD_TC_CFG_B			BIT01
#define OFBD_TC_CFG_N			BIT02
#define OFBD_TC_CFG_K			BIT03
#define OFBD_TC_CFG_E			BIT04
#define OFBD_TC_CFG_Q			BIT05
#define OFBD_TC_CFG_REBOOT		BIT06
#define OFBD_TC_CFG_X			BIT07
#define OFBD_TC_CFG_S			BIT08
#define OFBD_TC_CFG_ECUF		BIT09
#define OFBD_TC_CFG_SHUTDOWN		BIT10
#define OFBD_TC_CFG_SETUPRESERVE	BIT11
#define OFBD_TC_CFG_ROMHOLE     	BIT12
#define OFBD_TC_CFG_NCB 			BIT13
#define OFBD_TC_CFG_CLNEVNLOG		BIT14
#define OFBD_TC_CFG_R		    BIT15
#define OFBD_TC_CFG_O		    BIT16
#define OFBD_TC_CFG_GAN		    BIT17   //Patch for EIP 75281
#define OFBD_TC_CFG_KN          BIT18
#define OFBD_TC_CFG_L           BIT19
#define OFBD_TC_CFG_LN          BIT20
#define OFBD_TC_CFG_A           BIT21
#define OFBD_TC_CFG_OAD         BIT22
#define OFBD_TC_CFG_CAPSULE     BIT23
#define OFBD_TC_CFG_RECOVERY    BIT24
#define OFBD_TC_CFG_CAF         BIT25
     
//===============================
// Type Code 52 Get Check Status 
// See OFBD Spec 5.2, 6.3 for detail
//===============================
#define OFBD_TC_OPC_GET			BIT00
#define OFBD_TC_OPC_CHECK		BIT01
 
//============================
// Type Code 52 Return Status 
// See OFBD Spec 5.2, 6.3 for detail
//============================
#define OEM_RS_PC_REQ			    BIT00
#define OEM_RS_PC_CK_OK			    BIT01
#define OEM_RS_PC_TIMES_EXCEEDED    BIT02

//========================================
// Type Code 53 Get & Check Status
// See OFBD Spec 5.4, 6.4 for detail 
//========================================
#define OFBD_TC_ORI_GET			BIT00
#define OFBD_TC_ORI_CHECK		BIT01

//========================================
// Type Code 53 Return Status
// See OFBD Spec 5.4, 6.4 for detail 
//========================================
#define OFBD_TC_ORI_REQ			BIT00
#define OFBD_TC_ORI_ROM			BIT01
#define OFBD_TC_ORI_MOD			BIT02
#define OFBD_TC_ORI_GUID		BIT03
#define OFBD_TC_ORI_CK_OK		BIT04

//=======================================
// Type Code 54 Set Status		
// See OFBD Spec 5.5, 6.5 for detail	
//=======================================
#define OFBD_TC_STD_EC_START	BIT00
#define OFBD_TC_STD_EC_FLASH	BIT01
#define OFBD_TC_STD_EC_END	    BIT02
#define OFBD_TC_ECX_SIZE		BIT03		//(EIP31739+) Andy+
#define OFBD_TC_ECX_ERASE		BIT04
#define OFBD_TC_ECX_VERIFY		BIT05
#define OFBD_TC_ECX_RETRY		BIT06

//=======================================
// Type Code 54 Return Status		
// See OFBD Spec 5.5, 6.5 for detail	
//=======================================
#define OFBD_RS_EC_OK 		BIT00
#define OFBD_RS_EC_CHKSUM	BIT01
#define OFBD_RS_EC_ENTRY 	BIT02
#define OFBD_RS_EC_ERASE 	BIT03
#define OFBD_RS_EC_INIT 	BIT04
#define OFBD_RS_EC_START	BIT05
#define OFBD_RS_EC_WRITE 	BIT06
#define OFBD_RS_EC_EXIT 	BIT07
#define OFBD_RS_EC_CHIPID 	BIT08

//===============================
// Type Code 55 SubFunction  
//===============================
#define OFBD_TC_MEUD_GETINFO	    0
#define OFBD_TC_MEUD_START		    BIT00
 
//============================
// Type Code 55 Return Status 
//============================
#define OFBD_TC_MEUD_OK			BIT00
#define OFBD_TC_MEUD_ERROR		BIT01

//===============================
// Type Code 56 Get Check Status 
//===============================
#define OFBD_TC_SETUP_SUPPORT	    BIT00
#define OFBD_TC_SETUP_STORE		    BIT01
#define OFBD_TC_SETUP_RESTORE		BIT02
#define OFBD_TC_DMI_STORE		    BIT03
#define OFBD_TC_DMI_RESTORE		    BIT04
 
//============================
// Type Code 56 Return Status 
//============================
#define OFBD_TC_SETUP_OK			BIT00
#define OFBD_TC_SETUP_NOT_SUPPORT	BIT01
#define OFBD_TC_SETUP_STORE_ERROR	BIT02
#define OFBD_TC_SETUP_RESTORE_ERROR	BIT03
#define OFBD_TC_DMI_STORE_ERROR	    BIT04
#define OFBD_TC_DMI_RESTORE_ERROR   BIT05

//===================================//
// Type Code 57 Flash & Return Status//
//===================================//
// OEM CMD - Flash Status.
#define OFBD_TC_OEM_CMD_BF     1
#define OFBD_TC_OEM_CMD_AF     2
#define OFBD_TC_OEM_CMD_BE     3
#define OFBD_TC_OEM_CMD_SF     4
#define OFBD_TC_OEM_CMD_BUF    5    // For /CMD:"" to use (EIP40787+)
#define OFBD_TC_OEM_CMD_BUF_SF 6
#define OFBD_TC_OEM_CMD_BUF_AF 7
#define OFBD_TC_OEM_CMD_BUF_BE 8

// OEM CMD - Return Status.
#define OFBD_TC_OEM_CMD_OK          BIT00
#define OFBD_TC_OEM_CMD_NOT_SUPPORT BIT01
#define OFBD_TC_OEM_CMD_ERROR       BIT02

//===============================
// Type Code 58 Func Status 
//===============================
#define OFBD_TC_CEL_FUNC_REQ            BIT00

//============================
// Type Code 58 Return Status 
//============================
#define OFBD_TC_CEL_OK		            BIT00
#define OFBD_TC_CEL_ERROR	            BIT01
#define OFBD_TC_CEL_BIOS_NOT_SUPPORT	BIT02

//===============================
// Type Code 59 SubFunction  
//===============================
#define OFBD_TC_SECUREUD_LOAD2SMM       BIT00
#define OFBD_TC_SECUREUD_VERIFY_SMM     BIT01
#define OFBD_TC_SECUREUD_DONE           BIT02

//===============================
// Type Code 5A Func Status 
//===============================
#define OFBD_TC_OA_UPDATE_NOTIFY        BIT00

//============================
// Type Code 5A Return Status 
//============================
#define OFBD_RS_OA_DATA_IS_INVALID		BIT00
#define OFBD_RS_OA_DATA_IS_MODIFIED     BIT01
#define OFBD_RS_OA_UPDATE_SKIPPED       BIT02
#define OFBD_RS_OA_UPDATE_DECLINED      BIT03
#define OFBD_RS_OA_USE_OEM_ERROR_ID     BIT15

//===============================
// Type Code 5B Func Status 
//===============================
#define OFBD_TC_AC_BAT_INFO_REQ        BIT00

//============================
// Type Code 5B Return Status 
//============================
#define OFBD_RS_AC_BAT_OK              BIT00
#define OFBD_RS_AC_BAT_ERR             BIT01

//===================================//
// Type Code 70 Get & Set Status     //
//===================================//
#define OFBD_TC_SFU_GET_FLASH_INFO				BIT00
#define OFBD_TC_SFU_LOAD_FIRMWARE_IMAGE			BIT01
#define OFBD_TC_SFU_GET_FLASH_UPDATE_POLICY		BIT02
#define OFBD_TC_SFU_SET_FLASH_UPDATE_METHOD		BIT03
#define OFBD_TC_SFU_RUNTIME_FLASH				BIT04

//==============================//
// Type Code 70 Return Status   //
//==============================//
#define OFBD_TC_SFU_OK									BIT00
#define OFBD_TC_SFU_NOT_SUPPORTED						BIT01
#define OFBD_TC_SFU_FW_AUTH_FAILED						BIT02
#define OFBD_TC_SFU_INVALID_FW_CAPSULE_HDR				BIT03
#define OFBD_TC_SFU_SIGNING_KEYS_DONT_MATCH				BIT04
#define OFBD_TC_SFU_UNSUPPORTED_CERTIFICATE_HDR_FORMAT	BIT05

//----------------------------------------------------------------------------
// OFBD ROM HOLE CORE SERVICE ROUTINE - INVOKE FUNCTION - Function Driven Token
//----------------------------------------------------------------------------
#define OFBD_RH_HOLE_EXIST_CK      0 // This token is to check OEM's ROM Hole's existance. 
#define OFBD_RH_GET_HOLE_PHY_ADDR  1 // Pass Addr, Size, then Get Phy Addr. Notice: If NULL means AFU Does not support
#define OFBD_RH_HOLE_PROTECT       2 // Protect Sts, Addr, Size

//----------------------------------------------------------------------------
//	ROM HOLE - INVOKE FUNCTION RTN STS
//----------------------------------------------------------------------------
#define OFBD_RH_RTN_SUCCESSFUL                0
#define OFBD_RH_RTN_SERVICE_NOT_FOUND         BIT00
#define OFBD_RH_RTN_SERVICE_PARAMETER_ERROR   BIT01
#define OFBD_RH_RTN_HOLE_NOT_EXIST            BIT02
#define OFBD_RH_RTN_PHY_ADDR_NOT_VALID        BIT03

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
