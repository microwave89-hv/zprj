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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmControl.h 2     7/08/09 8:01p Markw $
//
// $Revision: 2 $
//
// $Date: 7/08/09 8:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmControl.h $
// 
// 2     7/08/09 8:01p Markw
// Update headers.
// 
// 1     3/18/07 1:54p Markw
// 
// 4     12/19/06 12:42p Felixp
// AMI_SMM_SW_SMI_16_BITS switch removed. Header is reverted to the
// previous version.
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     2/09/04 2:43p Markw
// Fixed header info.
// 
// 1     1/30/04 10:26a Markw
// 
// 1     1/26/04 3:25p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: SmmControl.h
//
// Description:	Provides south bridge functions for triggering and clearing SMIs.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SMM_CONTROL_PROTOCOL_H__
#define __SMM_CONTROL_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_CONTROL_PROTOCOL_GUID \
    {0x8d12e231,0xc667,0x4fd1,0x98,0xf2,0x24,0x49,0xa7,0xe7,0xb2,0xe5}

GUID_VARIABLE_DECLARATION(gEfiSmmControlProtocolGuid,EFI_SMM_CONTROL_PROTOCOL_GUID);

//************************************************
// EFI_SMM_PERIOD
//************************************************
typedef UINTN EFI_SMM_PERIOD;

//*********************************************
// EFI_SMM_CONTROL_REGISTER
//*********************************************
typedef struct {
    UINT8 SmiTriggerRegister;
    UINT8 SmiDataRegister;
} EFI_SMM_CONTROL_REGISTER;


typedef struct _EFI_SMM_CONTROL_PROTOCOL EFI_SMM_CONTROL_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SMM_ACTIVATE) (
    IN EFI_SMM_CONTROL_PROTOCOL *This,
    IN OUT INT8                 *ArgumentBuffer OPTIONAL,
    IN OUT UINTN                *ArgumentBufferSize OPTIONAL,
    IN BOOLEAN                  Periodic OPTIONAL,
    IN UINTN                    ActivationInterval OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_DEACTIVATE) (
    IN EFI_SMM_CONTROL_PROTOCOL *This,
    IN BOOLEAN                  Periodic OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_GET_REGISTER_INFO) (
    IN EFI_SMM_CONTROL_PROTOCOL     *This,
    IN OUT EFI_SMM_CONTROL_REGISTER *SmiRegister
);

//**********************************************************************
//<AMI_THDR_START>
//
// Name:        EFI_SMM_CONTROL_PROTOCOL
//
// Description: Provides south bridge functions for triggering and clearing SMIs.
//
// Fields:     Name			   Type					 Description
//        ------------------------------------------------------------
//        Trigger			   EFI_SMM_ACTIVATE          	Trigger SMI and provide it with a byte code. 
//        Clear			       EFI_SMM_DEACTIVATE         	Clear all SMI sources.
//        GetRegisterInfo	   EFI_SMM_GET_REGISTER_INFO	Get SMI Trigger information.
//        MinimumTriggerPeriod UINTN  						0 in IA32. SMI period is not supported.
//
//<AMI_THDR_END>
//**********************************************************************
struct _EFI_SMM_CONTROL_PROTOCOL {
    EFI_SMM_ACTIVATE            Trigger;
    EFI_SMM_DEACTIVATE          Clear;
    EFI_SMM_GET_REGISTER_INFO   GetRegisterInfo;
    UINTN                       MinimumTriggerPeriod;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

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
