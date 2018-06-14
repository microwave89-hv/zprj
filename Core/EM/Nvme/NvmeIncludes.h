//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/NVMe/NvmeIncludes.h 2     9/04/14 7:37a Anandakrishnanl $
//
// $Revision: 2 $
//
// $Date: 9/04/14 7:37a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/NVMe/NvmeIncludes.h $
// 
// 2     9/04/14 7:37a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
// 
// [Files]  		
// Nvme.cif	
// Nvme.mak	
// Nvme.uni
// Nvme.chm	
// NvmeSetup.c
// NvmeBus.c
// NvmeComponentName.c
// NvmeIncludes.h
// NvmeBus.h
// [NvmeControllerLib]
// [NvmeSmm]
// [NVMEINT13]
// [NvmeProtocol]
// 
// 1     6/20/14 6:27a Anandakrishnanl
// [TAG]  		EIP172958
// [Category]  	New Feature
// [Description]  	Nvme Driver Intial Checkin
// [Files]  		Nvme.cif
// Nvme.sdl
// Nvme.mak
// Nvme.sd
// Nvme.uni
// Nvme.chm
// NvmeSetup.c
// NvmeBus.c
// NvmeController.c
// NvmeComponentName.c
// NvmeIncludes.h
// NvmeBus.h
// NvmeController.h
// 
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    NvmeIncludes.h
//
// Description: Common header file for the Nvme Driver
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _NVME_INCLUDES_H_
#define _NVME_INCLUDES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <Token.h>

#include <Efi.h>
#include <AmiLib.h>
#include <Pci.h>
#include <Protocol/PciIo.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/BlockIo.h>
#include <Protocol/PDiskInfo.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/SmmBase.h>
#include <Protocol/SmmControl2.h>
#include <Protocol/SmmCommunication.h>
#include "NvmeInt13/NvmeInt13.h"


#define LANGUAGE_CODE_ENGLISH    "en-US"
#define MSG_NVME_DP               23


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
