//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/OFBD Secure Flash/SecureFlash.c 7     1/17/12 10:24p Lawrencechang $
//
// $Revision: 7 $
//
// $Date: 1/17/12 10:24p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD Secure Flash/SecureFlash.c $
// 
// 7     1/17/12 10:24p Lawrencechang
// Remove unnecessary header file.
// 
// 6     1/04/12 7:14a Lawrencechang
// Remove runtime flash codes, which will be done by SMIFlash protocol.
// 
// 5     12/21/11 8:17a Lawrencechang
// 1. Check if SMIFlash module exists or enables before install SMIFlash
// protocol.
// 2. Add WriteBlockEx() for SMIFlash protocol compatibility.
// WriteBlockEx() will be only used in SMIFlash protocol but no exposed to
// flash ROM interface.
// 
// 4     10/29/11 5:26a Lawrencechang
// Modified for adding SMIFlash protocol compatibility.
// 
// 3     10/28/11 4:28a Lawrencechang
// Add GetFlashInfo() for compatibility with SMIFlash protocol. Only works
// with 4.6.3.2_OFBD.1.0.2.
//
// 2     10/18/11 3:11a Lawrencechang
// Force LoadFirmwareImage(), GetFlashUpdatePolicy() and
// SetFlashUpdateMethod() to return correct error code.
//
// 1     9/16/11 4:25a Lawrencechang
// Initial check-in.
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	SecureFlash.c
//
// Description: This file provides OFBD Secure Flash function.
//
//<AMI_FHDR_END>
//**********************************************************************
#include <EFI.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <Protocol/SecSmiFlash.h>
#include <Protocol/FlashProtocol.h>

#include <OFBD.h>
#include <SecureFlash.h>

// GUIDs of consumed protocols
static EFI_GUID		gEfiSmiFlashProtocolGuid		= EFI_SMI_FLASH_GUID;
static EFI_GUID		gEfiSecSmiFlashProtocolGuid		= EFI_SEC_SMI_FLASH_GUID;

// Consumed protocols
EFI_SEC_SMI_FLASH_PROTOCOL		*SecSmiFlash	= NULL;
FLASH_PROTOCOL					*Flash			= NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: LoadFirmwareImage
//
// Description:	Transfer ROM image from AFU's buffer to Secure Flash Module
//				through EFI_SEC_SMI_FLASH_PROTOCOL.
//
// Input:
//		IN VOID		*Data	The data is a memory buffer. Its content is FUNC_BLOCK
//							defined in SmiFlash.h. The member function
//							LOAD_FLASH_IMAGE in EFI_SEC_SMI_FLASH_PROTOCOL only
//							accepts this type of parameter.
//
// Output:
//		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LoadFirmwareImage (
	VOID		*Data
)
{
	EFI_STATUS		Status;

	if (NULL == SecSmiFlash) return EFI_UNSUPPORTED;

	Status = SecSmiFlash->LoadFwImage((FUNC_BLOCK *)Data);

	((FUNC_BLOCK *)Data)->ErrorCode = (EFI_ERROR(Status) ? 1 : 0);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: GetFlashUpdatePolicy
//
// Description:	Get Flash Update Policy from Secure Flash module.
//
// Input:
//		IN VOID		*Data	The data is a memory buffer. Its content is
//							FLASH_POLICY_INFO_BLOCK defined in SecSmiFlash.h.
//
// Output:
//		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetFlashUpdatePolicy (
	VOID	*Data
)
{
	EFI_STATUS					Status;
	FLASH_POLICY_INFO_BLOCK		*pFlashPolicy = (FLASH_POLICY_INFO_BLOCK *)Data;

	if (NULL == SecSmiFlash) return EFI_UNSUPPORTED;

	Status = SecSmiFlash->GetFlUpdPolicy(pFlashPolicy);

	pFlashPolicy->ErrorCode = (EFI_ERROR(Status) ? 1 : 0);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SetFlashUpdateMethod
//
// Description:	Set Flash Update Policy to Secure Flash module.
//
// Input:
//		IN VOID		*Data	The data is a memory buffer. Its content is
//							FUNC_FLASH_SESSION_BLOCK defined in SecSmiFlash.h.
//
// Output:
//		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetFlashUpdateMethod (
	VOID		*Data
)
{
	EFI_STATUS					Status;
	FUNC_FLASH_SESSION_BLOCK	*pFlashSessionBlock = (FUNC_FLASH_SESSION_BLOCK *)Data;

	if (NULL == SecSmiFlash) return EFI_UNSUPPORTED;

	Status = SecSmiFlash->SetFlUpdMethod(pFlashSessionBlock);

	pFlashSessionBlock->ErrorCode = (EFI_ERROR(Status) ? 1 : 0);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SecureFlashProtocolCallback
//
// Description:	Locate SecSmiFlash protocol callback
//
// Input:
//		IN EFI_EVENT		Event
//		IN VOID				*Context
//
// Output:
//		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SecureFlashProtocolCallback (
	IN	EFI_EVENT		Event,
	IN	VOID			*Context
)
{
	pBS->LocateProtocol(&gEfiSecSmiFlashProtocolGuid, NULL, &SecSmiFlash);
	pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SmmFlashProtocolCallback
//
// Description:	Locate Flash protocol callback
//
// Input:
//		IN EFI_EVENT		Event
//		IN VOID				*Context
//
// Output:
//		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmmFlashProtocolCallback (
	IN	EFI_EVENT		Event,
	IN	VOID			*Context
)
{
	pBS->LocateProtocol(&gFlashSmmProtocolGuid, NULL, &Flash);
	pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   ASFUInSmm
//
// Description: This function installs the ASFU Protocol.
//
// Input:
//		VOID
//
// Output:
//		VOID
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ASFUInSmm (
	VOID
)
{
	EFI_STATUS	Status;
	EFI_HANDLE	DummyHandle = NULL;

	Status = pBS->LocateProtocol(&gEfiSecSmiFlashProtocolGuid, NULL, &SecSmiFlash);
	if (EFI_ERROR(Status)) {
		EFI_EVENT	SecFlashCallbackEvt;
		VOID		*Reg;
		RegisterProtocolCallback(
			&gEfiSecSmiFlashProtocolGuid,
			SecureFlashProtocolCallback,
			NULL,
			&SecFlashCallbackEvt,
			&Reg);
	}

	Status = pBS->LocateProtocol(&gFlashSmmProtocolGuid, NULL, &Flash);
	if (EFI_ERROR(Status)) {
		EFI_EVENT	SmmFlashCallbackEvt;
		VOID		*Reg;
		RegisterProtocolCallback(
			&gFlashSmmProtocolGuid,
			SmmFlashProtocolCallback,
			NULL,
			&SmmFlashCallbackEvt,
			&Reg);
	}

	return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ASFUEntry
//
// Description:	OFBD Secure Flash Update Entry point
//
// Input:
//		IN VOID				*Buffer
//		IN OUT UINT8		*pOFBDDataHandled
//
// Output:
//		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ASFUEntry (
	IN		VOID				*Buffer,
	IN OUT	UINT8		*pOFBDDataHandled
)
{
	OFBD_HDR					*pOFBDHdr;
	OFBD_EXT_HDR				*pOFBDExtHdr;
	VOID						*pOFBDTblEnd;
	OFBD_TC_70_SFU_STRUCT		*ASFUStructPtr;
	EFI_STATUS					Status = EFI_SUCCESS;

	if (*pOFBDDataHandled == 0) {
		pOFBDHdr = (OFBD_HDR *)Buffer;
		pOFBDExtHdr = (OFBD_EXT_HDR *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_HDR_SIZE));
		ASFUStructPtr = (OFBD_TC_70_SFU_STRUCT *)((UINT8 *)pOFBDExtHdr + sizeof(OFBD_EXT_HDR));
		pOFBDTblEnd = (VOID *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_Size));

		if (pOFBDHdr->OFBD_FS & OFBD_FS_SFU) {
			//Check Type Code ID
			if (pOFBDExtHdr->TypeCodeID == OFBD_EXT_TC_SFU) {
				switch (ASFUStructPtr->Command) {
					case OFBD_TC_SFU_LOAD_FIRMWARE_IMAGE :
						Status = LoadFirmwareImage(pOFBDTblEnd);
						break;
					case OFBD_TC_SFU_GET_FLASH_UPDATE_POLICY :
						Status = GetFlashUpdatePolicy(pOFBDTblEnd);
						break;
					case OFBD_TC_SFU_SET_FLASH_UPDATE_METHOD :
						Status = SetFlashUpdateMethod(pOFBDTblEnd);
						break;
					default :
						Status = EFI_UNSUPPORTED;
						break;
				}
				if (EFI_ERROR(Status)) {
					*pOFBDDataHandled = 0xFE;
					ASFUStructPtr->Status = OFBD_TC_SFU_NOT_SUPPORTED;
				} else {
					*pOFBDDataHandled = 0xFF;
					ASFUStructPtr->Status = OFBD_TC_SFU_OK;
				}
			}
		}
	}
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
