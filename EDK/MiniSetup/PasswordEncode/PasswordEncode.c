//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/PasswordEncode/PasswordEncode.c $
//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:				PasswordEncode.c
//
// Description:	This file contains code to handle password encoding feature
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
//


#include "PasswordEncode.h"

INTN MemCmp(VOID* pDestination, VOID* pSource, UINTN Length);

BOOLEAN TseEfiCompareGuid (IN EFI_GUID *Guid1,IN EFI_GUID *Guid2)
{
	return !MemCmp(Guid1,Guid2,sizeof(EFI_GUID));
}

VOID
TseMemCopy (
  IN VOID   *Destination,
  IN VOID   *Source,
  IN UINTN  Length
  )
/*++

Routine Description:

  Copy Length bytes from Source to Destination.

Arguments:

  Destination - Target of copy

  Source      - Place to copy from

  Length      - Number of bytes to copy

Returns:

  None

--*/
{
  CHAR8 *Destination8;
  CHAR8 *Source8;

  if (Source < Destination) {
    Destination8  = (CHAR8 *) Destination + Length - 1;
    Source8       = (CHAR8 *) Source + Length - 1;
    while (Length--) {
      *(Destination8--) = *(Source8--);
    }
  } else {
    Destination8  = (CHAR8 *) Destination;
    Source8       = (CHAR8 *) Source;
    while (Length--) {
      *(Destination8++) = *(Source8++);
    }
  }
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  Hash
//
// Description:    Allows creating a hash of an arbitrary message digest using one or more hash algorithms
//
// Input:
//      This          Pointer to the AMI_DIGITAL_SIGNATURE_PROTOCOL instance.
//      HashAlgorithm Points to the EFI_GUID which identifies the algorithm to use.
//      num_elem      Number of blocks to be passed via next argument:addr[]
//      addr[]        Pointer to array of UINT8* addresses of data blocks to be hashed
//      len           Pointer to array of integers containing length of each block listed by addr[]
//      Hash          Holds the resulting hash computed from the message.
//
// Output:    
//      EFI_SUCCESS           Hash returned successfully.
//      EFI_INVALID_PARAMETER Message or Hash is NULL
//      EFI_UNSUPPORTED       The algorithm specified by HashAlgorithm is not supported by this
//                            driver. Or extend is TRUE and the algorithm doesn't support extending the hash.
//
//<AMI_PHDR_END>
//**********************************************************************
#if TSE_HASH_PASSWORD
EFI_STATUS Hash(
	IN CONST EFI_GUID               *HashAlgorithm,
	IN UINTN                        num_elem,
	IN CONST UINT8                  *stringToHash[],
	IN CONST UINTN                  *HashSize,
	OUT UINT8                       *HashOutput
	)
{
	BOOLEAN     bSha1 = FALSE, bSha256 = FALSE;
	UINT32      HashLen=SHA256_DIGEST_SIZE;

	// Support only SHA1 & SHA256 hashes
	if(TseEfiCompareGuid((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha1Guid))
	{
		bSha1 = TRUE;
		HashLen = SHA1_DIGEST_SIZE;
	}
	else 
		if(TseEfiCompareGuid((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha256Guid))
		{
			bSha256 = TRUE;
			HashLen = SHA256_DIGEST_SIZE;
		}
		else
			return EFI_UNSUPPORTED;

	MemSet(HashOutput, HashLen, 0);

	if(bSha1)
		sha1_vector(num_elem, stringToHash, HashSize, HashOutput);
	else
		sha256_vector(num_elem, stringToHash, HashSize, HashOutput);

	return  EFI_SUCCESS;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PasswordEncodeLocal
//
// Description:	Encodes the input string
//
// Input:		Password : Password array to be encrypted. Encryped
//              password is returned in the same array.
//              MaxSize : Max size of Password
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 HashOutput[20];
VOID TsePasswordEncodeLocal( CHAR16 *Password, UINTN MaxSize);
VOID PasswordEncode( CHAR16 *Password, UINTN MaxSize)
{
#if TSE_HASH_PASSWORD
	UINTN	ii;
	EFI_STATUS Status;
	UINTN HashSize = SHA1_DIGEST_SIZE;

	if (IsPasswordSupportNonCaseSensitive ())
	{
		for ( ii = 0; ii < MaxSize/2; ii++ )
			Password[ii] = ((Password[ii]>=L'a')&&(Password[ii]<=L'z'))?(Password[ii]+L'A'-L'a'):Password[ii];
	}

	Status = Hash(&gEfiHashAlgorithmSha1Guid, TRUE, (CONST UINT8**)&Password, (CONST UINTN*)&MaxSize, (UINT8*)&HashOutput);
   if (!EFI_ERROR (Status))
   {
     	MemSet (Password, MaxSize, 0);
   	TseMemCopy ((UINT8*)Password, (UINT8*)HashOutput, HashSize);
   }
#else
   TsePasswordEncodeLocal (Password, MaxSize);
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsPasswordSupportNonCaseSensitive
//
// Description:	Returns SETUP_PASSWORD_NON_CASE_SENSITIVE token value
//
// Input:		void
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsPasswordSupportNonCaseSensitive()
{
#if SETUP_PASSWORD_NON_CASE_SENSITIVE
	return TRUE;
#endif
	return FALSE;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
