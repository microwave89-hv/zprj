/*++

   Copyright (c)  1999 - 2002 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.


   Module Name:

   sha1.h

   Abstract:

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/sha.h 1     4/21/14 2:14p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:14p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/sha.h $
// 
// 1     4/21/14 2:14p Fredericko
// 
// 1     10/08/13 11:58a Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     10/03/13 12:35p Fredericko
// Sha256 support policy update
// 
// 1     7/10/13 5:50p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// [Files]  		TisLib.cif
// TisLib.mak
// TcgTpm12.h
// TpmLib.h
// TcgCommon.h
// ZTEICTcmOrdinals.h
// TpmLib.c
// TcgCommon.c
// TisLib.sdl
// sha1.h
// INTTcgAcpi.h
// TcgPc.h
// TcmPc.h
// TcgEfiTpm.h
// TcgEFI12.h
// 
// 8     3/29/11 12:24p Fredericko
// 
// 7     3/28/11 12:14p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 6     5/19/10 5:09p Fredericko
// Included File Header
// Included File Revision History 
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  Sha1.h
//
// Description: 
//  Header file for sha1.c
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _CAL_SHA1_H_
#define _CAL_SHA1_H_

#include "TcgTpm12.h"
#include "token.h"


typedef TPM_ALGORITHM_ID TCG_ALGORITHM_ID;
#define TCG_ALG_SHA          0x00000004      // The SHA1 algorithm
typedef unsigned long        u32;

struct SHA1Context {
	u32 state[5];
	u32 count[2];
	unsigned char buffer[64];
};

typedef struct SHA1Context SHA1_CTX;



void SHA1Init(struct SHA1Context *context);
void SHA1Update(struct SHA1Context *context, const void *data, u32 len);
void SHA1Final(unsigned char digest[20], struct SHA1Context *context);

struct sha256_state {
	UINT64 length;
	UINT32 state[8], curlen;
	UINT8 buf[64];
};

typedef struct sha256_state SHA2_CTX;

void sha256_init(struct sha256_state *md);
int  sha256_process(struct sha256_state *md, const unsigned char *in, unsigned long inlen);
int  sha256_done(struct sha256_state *md, unsigned char *out);

#endif  // _CAL_SHA1_H_
