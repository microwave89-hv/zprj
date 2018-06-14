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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccSetup/IccLoadDefault.c 3     2/22/13 2:27a Klzhan $
//
// $Revision: 3 $
//
// $Date: 2/22/13 2:27a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccSetup/IccLoadDefault.c $
// 
// 3     2/22/13 2:27a Klzhan
// [TAG]  		EIP115268
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Icc Setup Item be hidden after load default(F3)
// [RootCause]  	New TSE check gGrowserCallbackEnabled
// [Solution]  	Enable gGrowserCallbackEnabled when call HiiSetBrowserData
// 
// 2     4/24/12 12:31a Klzhan
// Update modulepart to latest
// 
// 1     2/08/12 1:07a Klzhan
// Initial Check in 
// 
// 1     5/04/11 3:08a Klzhan
// EIP58767 : ICC Setup item will not be hidden when load default.
// 
// 1     11/01/10 9:42a Tonywu
// Fix that the "ICC OverClocking" form will be hidden when setup loads
// defaults.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        IccLoadDefault.c
//
// Description: Enter when loaded default in SETUP.
//
//<AMI_FHDR_END>
//**********************************************************************

#include <Setup.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "IccSetup.h"

EFI_STATUS FindVariableIndex(CHAR16 *Name, EFI_GUID *Guid, UINT32 *Index);

extern BOOLEAN gBrowserCallbackEnabled;

VOID IccSetupLoadDefault(VOID)
{
    UINT8  i;
    EFI_STATUS Status;

    UINTN SelectionBufferSize = sizeof(ICC_VOLATILE_SETUP_DATA);
    EFI_GUID IccSetupDataGuid = ICC_VOLATILE_SETUP_DATA_GUID;
    ICC_VOLATILE_SETUP_DATA* IccSetupData = NULL;
    ICC_VOLATILE_SETUP_DATA* TseIccSetupData = NULL;
    BOOLEAN OrgBrowserCallbackEnabled = gBrowserCallbackEnabled;

    Status = pBS->AllocatePool(EfiBootServicesData, SelectionBufferSize, &IccSetupData);
    if (!EFI_ERROR(Status))
    {
        Status = pRS->GetVariable (
                        ICC_VOLATILE_SETUP_DATA_C_NAME,
                        &IccSetupDataGuid,
                        NULL,
                        &SelectionBufferSize,
                        IccSetupData);
        ASSERT_EFI_ERROR(Status);
        if (!EFI_ERROR(Status))
        {
            if (IccSetupData->AllowAdvancedOptions == 1)
            {
                Status = pBS->AllocatePool(EfiBootServicesData, SelectionBufferSize, &TseIccSetupData);
                if(EFI_ERROR(Status)) {
                    return;
                }
                gBrowserCallbackEnabled = TRUE;
                Status = HiiLibGetBrowserData(&SelectionBufferSize, 
                                              TseIccSetupData,
                                              &IccSetupDataGuid, 
                                              L"IccAdvancedSetupDataVar"
                                              );
                if(EFI_ERROR(Status)) 
                {
                    pBS->FreePool(TseIccSetupData);
                    gBrowserCallbackEnabled = OrgBrowserCallbackEnabled;
                    return;
                }

                TseIccSetupData->AllowAdvancedOptions = IccSetupData->AllowAdvancedOptions;
                for (i=0; i<6 ;i++)
                {
                    TseIccSetupData->ShowClock[i] = IccSetupData->ShowClock[i];
                    TseIccSetupData->ShowSsc[i] = IccSetupData->ShowSsc[i];
                    TseIccSetupData->Frequency[i] = IccSetupData->Frequency[i];
                    TseIccSetupData->SscPercent[i] = IccSetupData->SscPercent[i];
                }
                Status = HiiLibSetBrowserData(
                             SelectionBufferSize, TseIccSetupData,
                             &IccSetupDataGuid, L"IccAdvancedSetupDataVar");

                pBS->FreePool(TseIccSetupData);
                gBrowserCallbackEnabled = OrgBrowserCallbackEnabled;

            }
        }

    }
}

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
