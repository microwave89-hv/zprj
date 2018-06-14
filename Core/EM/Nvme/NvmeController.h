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
// $Header: /Alaska/SOURCE/Modules/NVMe/NvmeController.h 3     5/19/15 7:59a Deepthins $
//
// $Revision: 3 $
//
// $Date: 5/19/15 7:59a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/NVMe/NvmeController.h $
// 
// 3     5/19/15 7:59a Deepthins
// [TAG]  		EIP218059
// [Category]  	Improvement
// [Description]  	Update Aptio4 NVME module to spec v1.2
// [Files]  		AmiNvmeController.h, NvmeController.h
// 
// 2     9/04/14 7:48a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
// [Files]  		Nvme.cif	
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
// Name:        NvmeController.h
//
// Description: Nvme Controller related defination
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _NVME_CONTROLLER_H_
#define _NVME_CONTROLLER_H_

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

// Refer to NVM Spec second 3.1 NVMe 1.1 which describes the register map for the controller
#define Offset_Cap      0x0
#define Offset_Version  0x8
#define Offset_Intms    0xC
#define Offset_Intmc    0x10
#define Offset_CC       0x14
#define Offset_CSTS     0x1C
#define CSTS_RDY        0x1
#define CSTS_CFS        0x2
#define Offset_Nssrs    0x20
#define Offset_Aqa      0x24
#define Offset_Asq      0x28
#define Offset_Acq      0x30
#define Offset_CMBLOC   0x38
#define Offset_CMBSZ    0x3C
#define Offset_Admin_Submission_Queue_Tail_DoorBell 0x1000

// Admin Cmd Set Figure 38 NVM Express 1.1
#define DELETE_IO_SUBMISSION_QUEUE  0x00
#define CREATE_IO_SUBMISSION_QUEUE  0x01
#define GET_LOG_PAGE                0x02
#define DELETE_IO_COMPLETION_QUEUE  0x04
#define CREATE_IO_COMPLETION_QUEUE  0x05
#define IDENTIFY                    0x06
#define ABORT                       0x08
#define SET_FEATURES                0x09
#define GET_FEATURES                0x0A
#define ASYNC_EVENT_REQUEST         0x0C
#define NAMESPACE_MANAGEMENT        0x0D
#define FIRMWARE_ACTIVATE           0x10
#define FIRMWARE_IMAGE_DOWNLOAD     0x11
#define NAMESPACE_ATTACHMENT        0x15
#define FORMAT_NVM                  0x80
#define SECURITY_SEND               0x81
#define SECURITY_RECEIVE            0x82

//Figure 149: Opcodes for NVM Commands NVM Express 1.2
#define NVME_FLUSH                  0x00
#define NVME_WRITE                  0x01
#define NVME_READ                   0x02
#define NVME_WRITE_UNCORRECTABLE    0x04
#define NVME_COMPARE                0x05
#define NVME_WRITE_ZEROES           0x08
#define NVME_DATASET_MANAGEMENT     0x09
#define NVME_RESERVATION_REGISTER   0x0D
#define NVME_RESERVATION_REPORT     0x0E
#define NVME_RESERVATION_ACQUIRE    0x11
#define NVME_RESERVATION_RELEASE    0x15


#define QUEUE_DOORBELL_OFFSET(QUEUE_NUM, TAIL_HEAD, DoorBellStride) \
        (0x1000 + (((QUEUE_NUM * 2)  + TAIL_HEAD) *  (4 << DoorBellStride)))

//MMIO Access

#define MmAddress( BaseAddr, Register ) \
        ((UINT64)(BaseAddr) + \
        (UINTN)(Register) \
         )
#define Mm32Ptr( BaseAddr, Register ) \
        ((volatile UINT32 *)MmAddress (BaseAddr, Register ))

#define Mm16Ptr( BaseAddr, Register ) \
        ((volatile UINT16 *)MmAddress (BaseAddr, Register ))

#define Mm8Ptr( BaseAddr, Register ) \
        ((volatile UINT8 *)MmAddress (BaseAddr, Register ))

//Controller Generic Registers

#define CONTROLLER_REG32( BaseAddr, Register ) \
        (*Mm32Ptr ((BaseAddr), (Register)))

#define CONTROLLER_REG16( BaseAddr, Register ) \
        (*Mm16Ptr ((BaseAddr), (Register)))

#define CONTROLLER_REG8( BaseAddr, Register ) \
        (*Mm8Ptr ((BaseAddr), (Register)))

#define CONTROLLER_WRITE_REG32( BaseAddr, Register, Data ) \
        (CONTROLLER_REG32 ((BaseAddr), (Register))) = ((UINT32) (Data))

#define CONTROLLER_WRITE_REG16( BaseAddr, Register, Data ) \
        (CONTROLLER_REG16 ((BaseAddr), (Register))) = ((UINT16) (Data))

#define CONTROLLER_WRITE_REG8( BaseAddr, Register, Data ) \
        (CONTROLLER_REG8 ((BaseAddr), (Register))) = ((UINT8) (Data))

#define CONTROLLER_REG8_OR( BaseAddr, Register, OrData) \
        (CONTROLLER_REG8 ((BaseAddr), (Register))) |= ((UINT8) (OrData))

#define CONTROLLER_REG16_OR( BaseAddr, Register, OrData) \
        (CONTROLLER_REG16 ((BaseAddr), (Register))) |= ((UINT16) (OrData))

#define CONTROLLER_REG32_OR( BaseAddr, Register, OrData) \
        (CONTROLLER_REG32 ((BaseAddr), (Register))) = (CONTROLLER_REG32 ((BaseAddr), (Register))) | ((UINT32) (OrData))

#define CONTROLLER_REG8_AND( BaseAddr, Register, AndData) \
        (CONTROLLER_REG8 ((BaseAddr), (Register))) = (CONTROLLER_REG8 ((BaseAddr), (Register))) & ((UINT8) (AndData))

#define CONTROLLER_REG16_AND( BaseAddr, Register, AndData) \
        (CONTROLLER_REG16 ((BaseAddr), (Register))) &= ((UINT16) (AndData))

#define CONTROLLER_REG32_AND( BaseAddr, Register, AndData) \
        (CONTROLLER_REG32 ((BaseAddr), (Register))) = (CONTROLLER_REG32 ((BaseAddr), (Register))) & ((UINT32) (AndData))

#define CONTROLLER_REG8_AND_OR( BaseAddr, Register, AndData, OrData) \
        (CONTROLLER_REG8 ((BaseAddr), (Register)) = \
        (((CONTROLLER_REG8 ((BaseAddr), (Register))) & ((UINT8) (AndData))) | ((UINT8) (OrData))))

#define CONTROLLER_REG16_AND_OR( BaseAddr, Register, AndData, OrData) \
        (CONTROLLER_REG16 ((BaseAddr), (Register)) = \
        (((CONTROLLER_REG16 ((BaseAddr), (Register))) & ((UINT16) AndData)) | ((UINT16) (OrData))))

#define CONTROLLER_REG32_AND_OR( BaseAddr, Register,AndData,  OrData) \
        (CONTROLLER_REG32 ((BaseAddr), (Register)) = \
        (((CONTROLLER_REG32 ((BaseAddr), (Register))) & ((UINT32) (AndData))) | ((UINT32) (OrData))))

#define AMI_NVME_CONTROLLER_PROTOCOL_GUID   { 0xAFA4CF3F, 0xAF71, 0x4C30,  0xA4, 0xFB, 0x29, 0x10, 0xE7, 0x71, 0xF9, 0xB0 }
#define AMI_NVME_PASS_THRU_PROTOCOL_GUID    { 0x4B215191, 0x9A25, 0x43FD,  0x86, 0xB5, 0x74, 0xE7, 0xAF, 0x72, 0x33, 0x15 }
#define AMI_NVME_LEGACY_PROTOCOL_GUID       { 0xD4E79DAE, 0xAAFC, 0x4382,  0x95, 0x40, 0x3E, 0x3F, 0xA4, 0x2D, 0x42, 0x55 }
#define AMI_SMM_NVME_COMMUNICATION_GUID     { 0xEC2BD1FD, 0xE3B0, 0x429B,  0xAD, 0xDF, 0x96, 0x57, 0x93, 0x5A, 0x36, 0x84 }

CHAR8* 
UnicodeStrToAsciiStr (
  IN      CONST CHAR16              *Source,
  OUT     CHAR8                     *Destination
);
#pragma pack()

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
