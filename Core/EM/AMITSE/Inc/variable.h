//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/variable.h $
//
// $Author: Arunsb $
//
// $Revision: 13 $
//
// $Date: 5/03/14 6:37p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/variable.h $
// 
// 13    5/03/14 6:37p Arunsb
// [TAG]  			EIP130198
// [Category]  	Improvement
// [Description]  	Increase the variable ID range from 25 to 54
// [Files]  		Variable.h, Setup.ini, UefiSetup.ini
// 
// 12    2/11/14 7:37p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 11    8/19/13 2:49a Premkumara
// [TAG]  		EIP130198
// [Category]  	Improvement
// [Description]  	Increase the variable ID range from 25 to 54
// [Files]  		Variable.h, Setup.ini, UefiSetup.ini
// 
// 10    10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 6     10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 9     1/30/12 1:33a Arunsb
// [TAG]  		EIP74676
// [Category]  	Improvement
// [Description]  	Setup.ini and Upfisetup.ini to reserve 3~5 variable and
// 		GUID for porting purpose
// [Files]  		Amivfr.h, special.h, variable.h, Uefisetup.ini and setup.ini
// 
// 8     12/05/11 5:46a Rajashakerg
// [TAG]  		EIP76381 
// [Category]  	Improvement
// [Description]  	Performance: Improving variable data load and usage
// [Files]  		callback.c, minisetupext.c, variable.c, variable.h,
// minisetup.h, Hii.c, FormBrowser2.c
// 
// 7     11/23/11 5:08a Rajashakerg
// [TAG]  		EIP75473 
// [Category]  	Improvement
// [Description]  	System Time is not updated every second
// [Files]  		variable.h, variable.c, FormBrowser2.c, TseUefiHii.h,
// Uefi21Wapper.c, hii.h, uefi20Wapper.c
// 
// 6     11/13/11 12:23p Arunsb
// [TAG]  		EIP70421
// [Category]  	New Feature
// [Description]  	Support for driver order in TSE
// [Files]  		AMITSE.SDL, CommonHelper.c, setup.ini, uefisetup.ini,
// boot.c,
// minisetup.h, bbs.c, special.c, special.h, tseadvanced.c,
// addbootoption.c,
// callback.c, minisetupext.c, minisetupext.h, popupsel.c, popupsel.h,
// TseLitehelper.c, variable.c, Uefi21Wapper.c, AMIVfr.h, boot.h,
// TseElink.h, variable.h, 
// setup.h, Boot.vfr and Setup.uni
// 
// 5     7/19/11 3:06p Arunsb
// [TAG]        EIP57661
// [Category]   New Feature
// [Description]    Drv health related variable declarations added to
// update the cache.
// [Files]          notify.c, Uefi21Wapper.c and variable.h
// 
// 4     7/19/11 10:47a Blaines
// [TAG] - EIP 63262
// [Category]- Defect
// [Symptom]- Setup page display problem on rose city.
// When SETUP_GROUP_DYNAMIC_PAGES is enabled and Network Stack is enabled,
// the "iSCSI" menu is listed as a dynamic page in advanced menu but only
// 3 of 4 "Port Configuration" pages shows up. The TSE dynamic page count
// is incorrect.
// 
// [Solution]- In the functions (RTIfrProcessRunTimeForms,
// HandleNewIFRPack, HandleRemoveIFRPack, HandleAddIFRPack), make sure the
// nvram cache is updated by calling
// VarUpdateVariable(VARIABLE_ID_DYNAMIC_PAGE_COUNT) when updating
// "DynamicPageCount" variable name. 
// .
// [Files] -  Hii.c, Minisetup.h, Variable.h
// 
// 3     2/19/10 12:59p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 3     1/09/10 2:31a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 2     10/28/09 5:34p Madhans
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 10:50p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:24p Madhans
// Tse 2.0 Code complete Checkin.
// 
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		variable.h
//
// Description:	Variable handling header
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef	_VARIABLE_H_
#define	_VARIABLE_H_

typedef struct _NVRAM_VARIABLE
{
	UINT8	*Buffer;
	UINTN	Size;
}
NVRAM_VARIABLE;

#define VAR_ZERO_OFFSET         0

#define	VAR_COMMAND_GET_VALUE	0
#define	VAR_COMMAND_SET_VALUE	1

#define	VAR_COMMAND_GET_NVRAM	0
#define	VAR_COMMAND_SET_NVRAM	1

// Variable IDs
#define VARIABLE_ID_SETUP			    		0
#define VARIABLE_ID_LANGUAGE		    		1		
#define VARIABLE_ID_BOOT_TIMEOUT	   		2
#define VARIABLE_ID_USER_DEFAULTS	   	3
#define VARIABLE_ID_ERROR_MANAGER	   	4
#define VARIABLE_ID_AMITSESETUP       		5
#define VARIABLE_ID_IDE_SECURITY      		6
#define VARIABLE_ID_BOOT_ORDER         	7
#define VARIABLE_ID_BBS_ORDER           	8
#define VARIABLE_ID_DEL_BOOT_OPTION     	9
#define VARIABLE_ID_ADD_BOOT_OPTION     	10
#define VARIABLE_ID_BOOT_MANAGER        	11
#define VARIABLE_ID_BOOT_NOW            	12
#define VARIABLE_ID_LEGACY_DEV_INFO     	13
#define VARIABLE_ID_AMI_CALLBACK        	14
#define VARIABLE_ID_LEGACY_GROUP_INFO   	15
#define VARIABLE_ID_OEM_TSE_VAR		    	17
#define VARIABLE_ID_DYNAMIC_PAGE_COUNT		18
#define VARIABLE_ID_DRV_HLTH_ENB				19
#define VARIABLE_ID_DRV_HLTH_COUNT			20
#define VARIABLE_ID_DRIVER_MANAGER			22		//EIP70421 & 70422 Support for driver order
#define VARIABLE_ID_DRIVER_ORDER				23	
#define VARIABLE_ID_ADD_DRIVER_OPTION   	24
#define VARIABLE_ID_DEL_DRIVER_OPTION   	25
#define VARIABLE_ID_PORT_OEM1					26		//EIP74676 variables for porting purpose
#define VARIABLE_ID_PORT_OEM2					27
#define VARIABLE_ID_PORT_OEM3					28
#define VARIABLE_ID_PORT_OEM4					29
#define VARIABLE_ID_PORT_OEM5					30
#define VARIABLE_ID_PORT_OEM6					31
#define VARIABLE_ID_PORT_OEM7					32
#define VARIABLE_ID_PORT_OEM8					33
#define VARIABLE_ID_PORT_OEM9					34
#define VARIABLE_ID_PORT_OEM10				35
#define VARIABLE_ID_PORT_OEM11				36
#define VARIABLE_ID_PORT_OEM12				37
#define VARIABLE_ID_PORT_OEM13				38
#define VARIABLE_ID_PORT_OEM14				39
#define VARIABLE_ID_PORT_OEM15				40
#define VARIABLE_ID_PORT_OEM16				41
#define VARIABLE_ID_PORT_OEM17				42
#define VARIABLE_ID_PORT_OEM18				43
#define VARIABLE_ID_PORT_OEM19				44
#define VARIABLE_ID_PORT_OEM20				45
#define VARIABLE_ID_PORT_OEM21				46
#define VARIABLE_ID_PORT_OEM22				47
#define VARIABLE_ID_PORT_OEM23				48
#define VARIABLE_ID_PORT_OEM24				49
#define VARIABLE_ID_PORT_OEM25				50
#define VARIABLE_ID_PORT_OEM26				51
#define VARIABLE_ID_PORT_OEM27				52
#define VARIABLE_ID_PORT_OEM28				53
#define VARIABLE_ID_PORT_OEM29				54                            

//EIP 76381 :  Performance Improving of variable data load and usage
EFI_STATUS GetNvramVariableList(NVRAM_VARIABLE **RetNvramVarList);
VOID CleanTempNvramVariableList();
EFI_STATUS CopyNvramVariableList(NVRAM_VARIABLE *SrcVarList, NVRAM_VARIABLE **DestVarList);

EFI_STATUS VarLoadVariables( VOID **list, NVRAM_VARIABLE *defaultList );
EFI_STATUS VarBuildDefaults( VOID );
VOID *VarGetNvramName( CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size );
EFI_STATUS VarSetNvramName( CHAR16 *name, EFI_GUID *guid, UINT32 attributes, VOID *buffer, UINTN size );
VOID *VarGetNvram( UINT32 variable, UINTN *size );
VOID *VarGetNvramQuestionValue(UINT32 variable, UINTN Offset, UINTN Size);
EFI_STATUS VarSetNvram( UINT32 variable, VOID *buffer, UINTN size );
EFI_STATUS VarGetDefaults( UINT32 variable, UINT32 offset, UINTN size, VOID *buffer );
EFI_STATUS VarGetValue( UINT32 variable, UINT32 offset, UINTN size, VOID *buffer );
EFI_STATUS VarSetValue( UINT32 variable, UINT32 offset, UINTN size, VOID *buffer );
VOID VarUpdateVariable(UINT32 variable);
VOID VarUpdateDefaults(UINT32 variable);
VOID *VarGetVariable( UINT32 variable, UINTN *size );

EFI_STATUS _VarGetData( UINT32 variable, UINT32 offset, UINTN size, VOID *buffer, BOOLEAN useDefaults );
EFI_STATUS _VarGetSetValue( UINTN command, NVRAM_VARIABLE *list, UINT32 variable, UINT32 offset, UINTN size, VOID *buffer );

#endif /* _VARIABLE_H_ */

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**         (C)Copyright 2011, American Megatrends, Inc.             **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093       **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
