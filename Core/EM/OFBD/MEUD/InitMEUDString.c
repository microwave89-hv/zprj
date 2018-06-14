//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/InitMEUDString.c 6     11/01/11 2:54a Klzhan $
//
// $Revision: 6 $
//
// $Date: 11/01/11 2:54a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/InitMEUDString.c $
// 
// 6     11/01/11 2:54a Klzhan
// [TAG]  		EIP73028
// [Category]  	Improvement
// [Description]  	Pointer might be used without initial.
// 
// 5     2/10/11 4:04a Klzhan
// Improvement : Update output string for SPS FW when disabled ME.
// 
// 4     12/27/10 3:15a Klzhan
// Improvement : Output message for Disabled ME setup item.
// 
// 3     6/10/10 5:54a Klzhan
// Improvement : Implement Setup call back by Elink.
// 
// 2     10/30/09 6:43a Klzhan
// 1. Remove un-used function.
// 
// 1     10/20/09 3:31a Klzhan
// Initail check-in.
//
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	InitMEUDString.c
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "..\OFBD.h"
#include "MEUD.h"
#if EFI_SPECIFICATION_VERSION>0x20000
#include <Protocol/HiiString.h>
#include <Protocol/HiiDatabase.h>
#else
#include <Protocol\Hii.h>
#endif
#include <Setup.h>
#include <Protocol/AMIPostMgr.h>

extern EFI_GUID guidHII;
#if EFI_SPECIFICATION_VERSION>0x20000
EFI_STATUS MEUDSetupCallbackFunction(
    EFI_HII_HANDLE HiiHandle, 
    UINT16 Class, 
    UINT16 SubClass, 
    UINT16 Key);
#else
EFI_STATUS MEUDSetupCallbackFunction(
  IN  EFI_FORM_CALLBACK_PROTOCOL    *This,
  IN  UINT16                        KeyValue,
  IN  EFI_IFR_DATA_ARRAY            *Data,
  OUT EFI_HII_CALLBACK_PACKET       **Packet );
EFI_FORM_CALLBACK_PROTOCOL MEUDSetupCallBack = { NULL,NULL,MEUDSetupCallbackFunction };
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MEUDSetupCallbackFunction
//
// Description:	TSE Callbeck Function.
//              To make ME enter Disable Mode.
//
// Input:
//      VOID
//
// Output: 
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if EFI_SPECIFICATION_VERSION>0x20000
EFI_STATUS MEUDSetupCallbackFunction(
    EFI_HII_HANDLE HiiHandle, 
    UINT16 Class, 
    UINT16 SubClass, 
    UINT16 Key)
#else
EFI_STATUS MEUDSetupCallbackFunction(
    IN  EFI_FORM_CALLBACK_PROTOCOL    *This,
    IN  UINT16                        KeyValue,
    IN  EFI_IFR_DATA_ARRAY            *Data,
    OUT EFI_HII_CALLBACK_PACKET       **Packet )
#endif
{
    UINTN      VariableSize = 1;
    UINT8      Flag,MsgBoxSel;
    EFI_GUID   gMEUDErrorguid = MEUD_ERROR_GUID;
    EFI_GUID   AmiPostMgrProtocolGuid = AMI_POST_MANAGER_PROTOCOL_GUID;
    EFI_STATUS Status;
    CHAR16     *OutputString = L"Disable ME fail !!";

    IoWrite8(0xB2,Disable_ME_SW_SMI);

    Status = pRS->GetVariable( L"ShowMEUDFailMSG", &gMEUDErrorguid,
                               NULL, &VariableSize, &Flag);

    // In SPS, BIOS doesn't send reset message.
    // Add message for User to know what happened.
    if(!EFI_ERROR(Status))
    {
        AMI_POST_MANAGER_PROTOCOL *AmiPostMgr = NULL;

        switch(Flag)
        {
            case 0:
#ifdef CSP_SPSUD_SUPPORT 
#if CSP_SPSUD_SUPPORT
            OutputString = L"ME been Disabled !! Please boot your system to OS for updating ME!!";
#endif
#endif
#ifdef CSP_MEUD_SUPPORT 
#if CSP_MEUD_SUPPORT
            OutputString = L"ME been Disabled !! Please reboot your system !!";
#endif
#endif
            break;

            default:
            OutputString = L"Disable ME fail !!";
            break;
        }
        if (!EFI_ERROR(pBS->LocateProtocol
             (&AmiPostMgrProtocolGuid, NULL, &AmiPostMgr)))
        {
            AmiPostMgr->DisplayMsgBox(
                        L"ME Update Info",
                        OutputString,
                        MSGBOX_TYPE_NULL,
                        &MsgBoxSel
                        );

        }
    }

    return EFI_SUCCESS ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitMEUDInfo
//
// Description:	Register a Setup Item CallBack Info.
//
// Input:
//      IN EFI_HII_HANDLE   HiiHandle
//      IN UINT16           Class
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitMEUDInfo(EFI_HII_HANDLE HiiHandle, UINT16 Class)
{
/*
    EFI_GUID    guidFormCallback = EFI_FORM_CALLBACK_PROTOCOL_GUID;
    EFI_HANDLE    Handle=0;
    EFI_GUID    guidHii = EFI_HII_PROTOCOL_GUID;
    EFI_HII_PROTOCOL    *MEUDHii = NULL;
    EFI_HII_UPDATE_DATA	UpdateData;
    UINT16        RegData = 0;
    EFI_STATUS    Status;

    if (Class != EXIT_FORM_SET_CLASS)
        return EFI_NOT_FOUND ;    

	Status = pBS->LocateProtocol(&guidHii,NULL,&MEUDHii);
	if( EFI_ERROR(Status) )
	{
		TRACE((0x800,"ERROR=%X Locate HII",Status)); 
	}

	// Install a form callback
	TRACE((0x800,"Installing form callback\n"));
	if (EFI_ERROR(
		Status = pBS->InstallProtocolInterface (
	              &Handle,
	              &guidFormCallback,
	              EFI_NATIVE_INTERFACE,
	              &MEUDSetupCallBack
	              )
	))
	{
		TRACE((0x800,"ERROR=%X - InstallProtocolInterface",Status));
	}


	UpdateData.FormSetUpdate = TRUE;	// Flag update pending in FormSet
	UpdateData.FormCallbackHandle = (EFI_PHYSICAL_ADDRESS) Handle;	// Register CallbackHandle data for FormSet
	UpdateData.FormUpdate  = FALSE;
	UpdateData.FormTitle   = 0;
	UpdateData.DataCount   = 0;
	Status = MEUDHii->UpdateForm(MEUDHii, HiiHandle, (EFI_FORM_LABEL)0x0000, FALSE, &UpdateData);
	if( EFI_ERROR(Status) )
	{
		TRACE((0x800,"ERROR=%X UpdateForm",Status)); 
	}
*/
	return EFI_SUCCESS;

}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
