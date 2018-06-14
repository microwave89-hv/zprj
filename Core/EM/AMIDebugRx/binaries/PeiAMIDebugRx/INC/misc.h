//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2009, American Megatrends, Inc.        **//
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
// $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/INC/misc.h 2     7/17/09 7:15p Madhans $
//
// $Revision: 2 $
//
// $Date: 7/17/09 7:15p $
//*****************************************************************
//*****************************************************************
//
//	misc.h
//		
//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/INC/misc.h $
// 
// 2     7/17/09 7:15p Madhans
// DebugRx 1.30.0022
// 
// 2     7/13/09 2:49p Sudhirv
// Update with Coding Standards
// 
// 1     7/07/09 4:46p Sudhirv
// Restructure Binaries Created
// 
// 1     5/01/09 7:48p Madhans
// AMIDebug Rx Module. Intial Checkin.
// 
// 1     4/29/09 7:52a Sudhirv
// AMI Debug Rx module created
// 
// 6     8/29/07 12:49p Madhans
// Common code for 4.x and 3.x
// 
// 5     6/13/07 3:17p Madhans
// Copyright Year updated.
// 
// 4     3/13/07 4:08p Ashrafj
// !!!Coding standard!!!
// 
// 3     1/22/07 11:41a Madhans
// Modification made for Binary Release 1.04.0003.
// 
// 5     1/05/07 6:15p Madhan
// 
// 4     1/05/07 1:05p Ashrafj
// Latest version 1.04.0001 Beta
// Known issues from previous 1.04.000 Beta release has been fixed.
// 
// 3     12/05/05 7:29p Ashrafj
// Serial Port Debug Support added for PEI - DXE Debugger.
// 
// Change in Serial Port Communication: Now the data transmission through
// Serial Port is supported with the hardware Flow control feature of the
// Serial Port controller.
// 
// 2     11/29/05 6:08p Markw
// For Alaska, include efi.h instead of defining new typecasts.
// 
// 1     10/19/05 10:54a Felixp
// 
// 1     10/19/05 10:44a Felixp
// 
//
//
//*****************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:		misc.h
//
// Description:	Generic Misc header file.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifdef ALASKA_SUPPORT

#include <efi.h>

#else	/* Support for APTIO projects */

#define UINT64  	unsigned __int64
#define UINT32  	unsigned long
#define UINT16  	unsigned short
#define UINT8  		unsigned char

#define INT32  		signed long
#define INT8  		signed char
#define INT16  		signed short

#define CHAR8		char
#define CHAR16		unsigned short
#define BOOLEAN		unsigned char

#define	UINTN	UINT32
#define	INTN	INT32

#define	VOID	void

#ifndef _EFI_TYPES_H_

#define TRUE	1

#define FALSE	0

#define NULL    0

#define IN
#define OUT

//EFI error types 

//typedef UINTN           EFI_STATUS;
#define		EFI_STATUS		UINTN

#define EFI_ERROR(a)					(((INTN) a) < 0)

#define EFIERR(a)						(0x80000000 | a)

#define EFI_SUCCESS                             0
#define EFI_LOAD_ERROR                  EFIERR(1)
#define EFI_INVALID_PARAMETER           EFIERR(2)
#define EFI_UNSUPPORTED                 EFIERR(3)
#define EFI_BAD_BUFFER_SIZE             EFIERR(4)
#define EFI_BUFFER_TOO_SMALL            EFIERR(5)
#define EFI_NOT_READY                   EFIERR(6)
#define EFI_DEVICE_ERROR                EFIERR(7)
#define EFI_WRITE_PROTECTED             EFIERR(8)
#define EFI_OUT_OF_RESOURCES            EFIERR(9)
#define EFI_VOLUME_CORRUPTED            EFIERR(10)
#define EFI_VOLUME_FULL                 EFIERR(11)
#define EFI_NO_MEDIA                    EFIERR(12)
#define EFI_MEDIA_CHANGED               EFIERR(13)
#define EFI_NOT_FOUND                   EFIERR(14)
#define EFI_ACCESS_DENIED               EFIERR(15)
#define EFI_NO_RESPONSE                 EFIERR(16)
#define EFI_NO_MAPPING                  EFIERR(17)
#define EFI_TIMEOUT                     EFIERR(18)
#define EFI_NOT_STARTED                 EFIERR(19)
#define EFI_ALREADY_STARTED             EFIERR(20)
#define EFI_ABORTED                     EFIERR(21)
#define EFI_ICMP_ERROR                  EFIERR(22)
#define EFI_TFTP_ERROR                  EFIERR(23)
#define EFI_PROTOCOL_ERROR              EFIERR(24)

#endif

#endif
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2009, American Megatrends, Inc.        **//
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
