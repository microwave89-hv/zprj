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
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/AmiTpmClearOnRollbackProtocol/AmiTpmClearOnRollbackProtocol.h 1     4/21/14 2:16p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:16p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/AmiTpmClearOnRollbackProtocol/AmiTpmClearOnRollbackProtocol.h $
// 
// 1     4/21/14 2:16p Fredericko
// 
// 1     10/08/13 12:01p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:57p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: 
//
// Description:	
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _AMI_TPM_CLEAR_ON_ROLLBACK_H
#define _AMI_TPM_CLEAR_ON_ROLLBACK_H

#define AMI_TPM_ROLLBACK_SMM_PROTOCOL_GUID \
  {0x79fbad19, 0xf9e1, 0x4d08, 0xb7, 0xbc, 0x35, 0x84, 0x53, 0x19, 0x5e, 0x41}

#define TPM_CLEAR_SUCCESSFUL 0x0
#define TPM_CLEAR_RESET_REQUIRED 0x01
#define TPM_FATAL_CONTINUE_FLASH 0x02
#define TPM_FATAL_DISCONTINUE_FLASH 0x03

typedef
UINT8
(EFIAPI * CLEAR_TPM_ON_ROLLBACK)(VOID);

typedef struct _CLEAR_TPM_ROLLBACK_PROTOCOL
{
    CLEAR_TPM_ON_ROLLBACK            ClearTpmOnRollBack;
} CLEAR_TPM_ROLLBACK_PROTOCOL;

#endif
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