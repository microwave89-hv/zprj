//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/AmiSmm.h 3     8/10/05 4:56p Markw $
//
// $Revision: 3 $
//
// $Date: 8/10/05 4:56p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/AmiSmm.h $
// 
// 3     8/10/05 4:56p Markw
// Change SmmBasesVariable to point to a function to change SMM Bases.
// 
// 2     4/08/05 4:36p Markw
// Added SmmBasesVariable.
// 
// 1     4/06/05 10:55a Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: AmiSmm.h
//
// Description:	Ami specific Smm definitions
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __AMI_SMM__H__
#define __AMI_SMM__H__

#include <efi.h>

#ifdef __cplusplus
extern "C" {
#endif


//The following is for restoring SMM bases on S3 resume.
#define	SMM_BASES_VARIABLE L"SmmBasesVariable"

#pragma pack(1)

typedef struct _SMM_BASE_CHANGE_INFO SMM_BASE_CHANGE_INFO;

struct _SMM_BASE_CHANGE_INFO {
	VOID			(*ChgSmmBases)(SMM_BASE_CHANGE_INFO *This);
};
#pragma pack()

//This structure is added to SMM Configuration Table to determine
// which CPU generated a software smi.

#define SW_SMI_CPU_TRIGGER_GUID \
    {0xe4d535bb,0x5dea,0x42f8,0xb5,0xf8,0xd6,0xb8,0x13,0xff,0x6b,0x46}

typedef struct {
	UINTN 	Cpu;
} SW_SMI_CPU_TRIGGER;




/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
