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

//*************************************************************************
// $Header: /Alaska/SOURCE/Core/Library/Decompress.c 4     7/10/09 3:49p Felixp $
//
// $Revision: 4 $
//
// $Date: 7/10/09 3:49p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Library/Decompress.c $
// 
// 4     7/10/09 3:49p Felixp
// Function headers added
// 
// 3     5/09/07 9:03a Felixp
// 
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name: Decompress.c
//
// Description:	
//  Standard EFI decompressor library functions.
//  The functions are used by Core to implement standard Decompression API.
//  Consumers outside Core should not use functions from this file.
//  The public API should be used instead.
//
//<AMI_FHDR_END>
//*************************************************************************
#include <EFI.h>

#define STATIC static

//
// Decompression algorithm begins here
//

#define     BITBUFSIZ         32
#define     MAXMATCH          256
#define     THRESHOLD         3
#define     CODE_BIT          16
#define     UINT8_MAX         0xff
#define     BAD_TABLE         -1

//
// C: Char&Len Set; P: Position Set; T: exTra Set
//

#define     NC                (0xff + MAXMATCH + 2 - THRESHOLD)
#define     CBIT              9
#define     MAXPBIT           5
#define     TBIT              5
#define     MAXNP             ((1U << MAXPBIT) - 1)
#define     NT                (CODE_BIT + 3)
#if NT > MAXNP
  #define     NPT               NT
#else
  #define     NPT               MAXNP
#endif


//*************************************************************************
//<INT:AMI_SHDR_START>
//
// Name: SCRATCH_DATA
//
// Description: 
//  Scratch buffer structure for the (de)compression routines.
// 
// Fields:
//  Name              Type        Description
//.........................................................................
// mSrcBase          UINT8*      Starting address of compressed data.
// mDstBase          UINT8*      Starting address of decompressed data.
// mOutBuf           UINT32
// mInBuf            UINT32
// mBitCount         UINT16
// mBitBuf           UINT32
// mSubBitBuf        UINT32
// mBlockSize        UINT16
// mCompSize         UINT32
// mOrigSize         UINT32
// mBadTableFlag     UINT16
// mLeft             UINT16
// mmRight           UINT16
// mCLen             UINT8
// mPTLen            UINT8
// mCTable           UINT16
// mPTTable          UINT16
// mPBit             UINT8       The length of the field 'Position Set Code Length Array Size' in Block Header. For EFI 1.1 (de)compression algorithm, mPBit = 4.  For Tiano (de)compression algorithm, mPBit = 5. 
//                               
// Referrals:
// 
// Notes:	
//          
//<INT:AMI_SHDR_END>
//*************************************************************************
typedef struct {
  UINT8       *mSrcBase;      //Starting address of compressed data
  UINT8       *mDstBase;      //Starting address of decompressed data
  UINT32      mOutBuf;
  UINT32      mInBuf;

  UINT16      mBitCount;
  UINT32      mBitBuf;
  UINT32      mSubBitBuf;
  UINT16      mBlockSize;
  UINT32      mCompSize;
  UINT32      mOrigSize;

  UINT16      mBadTableFlag;

  UINT16      mLeft[2 * NC - 1];
  UINT16      mRight[2 * NC - 1];
  UINT8       mCLen[NC];
  UINT8       mPTLen[NPT];
  UINT16      mCTable[4096];
  UINT16      mPTTable[256];

//
// The length of the field 'Position Set Code Length Array Size' in Block Header.
// For EFI 1.1 de/compression algorithm, mPBit = 4
// For Tiano de/compression algorithm, mPBit = 5
//

  UINT8       mPBit;
} SCRATCH_DATA;

//*************************************************************************
//<INT:AMI_PHDR_START>
//
// Name: FillBuf
//
// Description:
//  VOID FillBuf(IN OUT SCRATCH_DATA *Sd, IN UINT16 NumOfBits) shifts
// Sd->mBitBuf NumOfBits left.  Then it reads in NumOfBits bits from source.
//
// Input:
//  IN OUT SCRATCH_DATA *Sd
// The global scratch data.
//
//  IN UINT16 NumOfBits
// The number of bits to shift and read.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
// 
// Notes:	
//          
//<INT:AMI_PHDR_END>
//*************************************************************************
STATIC
VOID
FillBuf (
  IN  SCRATCH_DATA  *Sd,
  IN  UINT16        NumOfBits
  )
{
  Sd->mBitBuf = (UINT32)(Sd->mBitBuf << NumOfBits);

  while (NumOfBits > Sd->mBitCount) {

    Sd->mBitBuf |= (UINT32)(Sd->mSubBitBuf << 
      (NumOfBits = (UINT16)(NumOfBits - Sd->mBitCount)));

    if (Sd->mCompSize > 0) {

      //
      // Get 1 byte into SubBitBuf
      //
      Sd->mCompSize --;
      Sd->mSubBitBuf = 0;
      Sd->mSubBitBuf = Sd->mSrcBase[Sd->mInBuf ++];
      Sd->mBitCount = 8;

    } else {

      //
      // No more bits from the source, just pad zero bit.
      //
      Sd->mSubBitBuf = 0;
      Sd->mBitCount = 8;

    }
  }

  Sd->mBitCount = (UINT16)(Sd->mBitCount - NumOfBits);  
  Sd->mBitBuf |= Sd->mSubBitBuf >> Sd->mBitCount;
}

//*************************************************************************
//<INT:AMI_PHDR_START>
//
// Name: GetBits
//
// Description:
//  UINT32 GetBits(IN OUT SCRATCH_DATA *Sd, IN UINT16 NumOfBits) fetches
// NumOfBits bits out from mBitBuf, then fills mBitBuf with subsequent
// NumOfBits bits from source.  Returns NumOfBits bits that are popped out.
//
// Input:
//  IN OUT SCRATCH_DATA *Sd
// The global scratch data.
//
//  IN UINT16 NumOfBits
// The number of bits to pop and read.
//
// Output:
//  UINT32 number of bits that are popped out.
//
// Modified:
//
// Referrals:
//  FillBuf
// 
// Notes:	
//          
//<INT:AMI_PHDR_END>
//*************************************************************************
STATIC
UINT32
GetBits(
  IN  SCRATCH_DATA  *Sd,
  IN  UINT16    NumOfBits
  )
{
  UINT32  OutBits;

  OutBits = (UINT32)(Sd->mBitBuf >> (BITBUFSIZ - NumOfBits));

  FillBuf (Sd, NumOfBits);

  return  OutBits;
}

//*************************************************************************
//<INT:AMI_PHDR_START>
//
// Nane: MakeTable
//
// Description:
//  UINT16 MakeTable(IN OUT SCRATCH_DATA *Sd, IN UINT16 NumOfChar,
// IN UINT8 *BitLen, IN UINT16 TableBits, OUT UINT16 *Table) creates a
// Huffman Code mapping table according to code length array.
//
// Input:
//  IN OUT SCRATCH_DATA *Sd
// The global scratch data.
//
//  IN UINT16 NumOfChar
// Number of symbols in the symbol set.
//
//  IN UINT8 *BitLen
// Code length array.
//
//  IN UINT16 TableBits
// The width of the mapping table.
//
//  OUT UINT16 *Table
// The table.
//
// Output:
//  UINT16 BAD_TABLE if table is corrupted, otherwise returns 0 if okay.
//
// Modified:
//
// Referrals:
// 
// Notes:	
//          
//<INT:AMI_PHDR_END>
//*************************************************************************
STATIC
UINT16
MakeTable (
  IN  SCRATCH_DATA  *Sd,
  IN  UINT16      NumOfChar,
  IN  UINT8       *BitLen,
  IN  UINT16      TableBits,
  OUT UINT16       *Table
  )
{
  UINT16  Count[17];
  UINT16  Weight[17];
  UINT16  Start[18];
  UINT16  *p;
  UINT16  k;
  UINT16  i;
  UINT16  Len;
  UINT16  Char;
  UINT16  JuBits;
  UINT16  Avail;
  UINT16  NextCode;
  UINT16  Mask;


  for (i = 1; i <= 16; i ++) {
    Count[i] = 0;
  }

  for (i = 0; i < NumOfChar; i++) {
    Count[BitLen[i]]++;
  }

  Start[1] = 0;

  for (i = 1; i <= 16; i ++) {
    Start[i + 1] = (UINT16)(Start[i] + (Count[i] << (16 - i)));
  }

  if (Start[17] != 0) {/*(1U << 16)*/
    return (UINT16)BAD_TABLE;
  }

  JuBits = (UINT16)(16 - TableBits);

  for (i = 1; i <= TableBits; i ++) {
    Start[i] >>= JuBits;
    Weight[i] = (UINT16)(1U << (TableBits - i));
  }

  while (i <= 16) {
    Weight[i++] = (UINT16)(1U << (16 - i));
  }

  i = (UINT16)(Start[TableBits + 1] >> JuBits);

  if (i != 0) {
    k = (UINT16)(1U << TableBits);
    while (i != k) {
      Table[i++] = 0;
    }
  }

  Avail = NumOfChar;
  Mask = (UINT16)(1U << (15 - TableBits));

  for (Char = 0; Char < NumOfChar; Char++) {

    Len = BitLen[Char];
    if (Len == 0) {
      continue;
    }

    NextCode = (UINT16)(Start[Len] + Weight[Len]);

    if (Len <= TableBits) {

      for (i = Start[Len]; i < NextCode; i ++) {
        Table[i] = Char;
      }

    } else {

      k = Start[Len];
      p = &Table[k >> JuBits];
      i = (UINT16)(Len - TableBits);

      while (i != 0) {
        if (*p == 0) {
          Sd->mRight[Avail] = Sd->mLeft[Avail] = 0;
          *p = Avail ++;
        }

        if (k & Mask) {
          p = &Sd->mRight[*p];
        } else {
          p = &Sd->mLeft[*p];
        }

        k <<= 1;
        i --;
      }

      *p = Char;

    }

    Start[Len] = NextCode;
  }
  
  //
  // Succeeds
  //
  return 0;
}

//*************************************************************************
//<INT:AMI_PHDR_START>
//
// Name: DecodeP
//
// Description:
//  UINT32 DecodeP(IN SCRATCH_DATA *Sd) decodes a position value.
//
// Input:
//  IN SCRATCH_DATA *Sd
// The global scratch data.
//
// Output:
//  UINT32 position value decoded.
//
// Modified:
//
// Referrals:
//  FillBuf
//  GetBits
// 
// Notes:	
//          
//<INT:AMI_PHDR_END>
//*************************************************************************
STATIC
UINT32
DecodeP (
  IN  SCRATCH_DATA  *Sd
  )
{
  UINT16  Val;
  UINT32  Mask;
  UINT32  Pos;

  Val = Sd->mPTTable[Sd->mBitBuf >> (BITBUFSIZ - 8)];

  if (Val >= MAXNP) {
    Mask = 1U << (BITBUFSIZ - 1 - 8);

    do {

      if (Sd->mBitBuf & Mask) {
        Val = Sd->mRight[Val];
      } else {
        Val = Sd->mLeft[Val];
      }

      Mask >>= 1;
    } while (Val >= MAXNP);
  }
  
  //
  // Advance what we have read
  //
  FillBuf (Sd, Sd->mPTLen[Val]);
  
  Pos = Val;
  if (Val > 1) {
    Pos = (UINT32)((1U << (Val - 1)) + GetBits (Sd, (UINT16)(Val - 1)));
  }
  return Pos;
}

//*************************************************************************
//<INT:AMI_PHDR_START>
//
// Name: ReadPTLen
//
// Description:
//  UINT16 ReadPTLen(IN OUT SCRATCH_DATA *Sd, IN UINT16 nn, IN UINT16 nbit,
// IN UINT16 Special) reads code lengths for the extra set or the position
// set.
//
// Input:
//  IN OUT SCRATCH_DATA *Sd
// The global scratch data.
//
//  IN UINT16  nn
// Number of symbols.
//
//  IN UINT16  nbit
// Number of bits needed to represent nn.
//
//  IN UINT16  Special
// The special symbol that needs to be taken care of.
//
// Output:
//  UINT16 BAD_TABLE if the table is corrupted, otherwise returns 0 if
// everything okay.
//
// Modified:
//
// Referrals:
//  GetBits
//  FillBuf
//  MakeTable
//
// Notes:	
//          
//<INT:AMI_PHDR_END>
//*************************************************************************
STATIC
UINT16
ReadPTLen (
  IN  SCRATCH_DATA  *Sd,
  IN  UINT16  nn,
  IN  UINT16  nbit,
  IN  UINT16  Special
  )
{
  UINT16    n;
  UINT16    c;
  UINT16    i;
  UINT32    Mask;

  n = (UINT16)GetBits (Sd, nbit);

  if (n == 0) {
    c = (UINT16)GetBits (Sd, nbit);

    for ( i = 0; i < 256; i ++) {
      Sd->mPTTable[i] = c;
    }

    for ( i = 0; i < nn; i++) {
      Sd->mPTLen[i] = 0;
    }

    return 0;
  }

  i = 0;

  while (i < n) {

    c = (UINT16)(Sd->mBitBuf >> (BITBUFSIZ - 3));

    if (c == 7) {
      Mask = 1U << (BITBUFSIZ - 1 - 3);
      while (Mask & Sd->mBitBuf) {
        Mask >>= 1;
        c += 1;
      }
    }

    FillBuf (Sd, (UINT16)((c < 7) ? 3 : c - 3));

    Sd->mPTLen [i++] = (UINT8)c;

    if (i == Special) {
      c = (UINT16)GetBits (Sd, 2);
      while ((INT16)(--c) >= 0) {
        Sd->mPTLen[i++] = 0;
      }
    }
  }

  while (i < nn) {
    Sd->mPTLen [i++] = 0;
  }

  return ( MakeTable (Sd, nn, Sd->mPTLen, 8, Sd->mPTTable) );
}

//*************************************************************************
//<INT:AMI_PHDR_START>
//
// Name: ReadCLen
//
// Description:
//  VOID ReadCLen(IN OUT SCRATCH_DATA *Sd) reads code lengths for Char&Len
// Set.
//
// Input:
//  IN OUT SCRATCH_DATA *Sd
// The global scratch data.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//  GetBits
//  MakeTable
//
// Notes:	
//          
//<INT:AMI_PHDR_END>
//*************************************************************************
STATIC
VOID
ReadCLen (
  SCRATCH_DATA  *Sd
  )
{
  UINT16    n;
  UINT16    c;
  UINT16    i;
  UINT32    Mask;

  n = (UINT16)GetBits(Sd, CBIT);

  if (n == 0) {
    c = (UINT16)GetBits(Sd, CBIT);

    for (i = 0; i < NC; i ++) {
      Sd->mCLen[i] = 0;
    }

    for (i = 0; i < 4096; i ++) {
      Sd->mCTable[i] = c;
    }

    return;
  }

  i = 0;
  while (i < n) {

    c = Sd->mPTTable[Sd->mBitBuf >> (BITBUFSIZ - 8)];
    if (c >= NT) {
      Mask = 1U << (BITBUFSIZ - 1 - 8);

      do {

        if (Mask & Sd->mBitBuf) {
          c = Sd->mRight [c];
        } else {
          c = Sd->mLeft [c];
        }

        Mask >>= 1;

      }while (c >= NT);
    }

    //
    // Advance what we have read
    //
    FillBuf (Sd, Sd->mPTLen[c]);

    if (c <= 2) {

      if (c == 0) {
        c = 1;
      } else if (c == 1) {
        c = (UINT16)(GetBits (Sd, 4) + 3);
      } else if (c == 2) {
        c = (UINT16)(GetBits (Sd, CBIT) + 20);
      }

      while ((INT16)(--c) >= 0) {
        Sd->mCLen[i++] = 0;
      }

    } else {

      Sd->mCLen[i++] = (UINT8)(c - 2);

    }
  }

  while (i < NC) {
    Sd->mCLen[i++] = 0;
  }

  MakeTable (Sd, NC, Sd->mCLen, 12, Sd->mCTable);

  return;
}

//*************************************************************************
//<INT:AMI_PHDR_START>
//
// Name: DecodeC
//
// Description:
//  UINT16 DecodeC(IN OUT SCRATCH_DATA *Sd) decodes a character/length value.
//
// Input:
//  IN OUT SCRATCH_DATA *Sd
// The global scratch data.
//
// Output:
//  UINT16 decoded value.
//
// Modified:
//
// Referrals:
//  ReadPTLen
//  ReadCLen
//  GetBits
//  FillBuf
//
// Notes:	
//          
//<INT:AMI_PHDR_END>
//*************************************************************************
STATIC
UINT16
DecodeC (
  SCRATCH_DATA  *Sd
  )
{
  UINT16      j;
  UINT32      Mask;

  if (Sd->mBlockSize == 0) {

    //
    // Starting a new block
    //

    Sd->mBlockSize = (UINT16)GetBits(Sd, 16);
    Sd->mBadTableFlag = ReadPTLen (Sd, NT, TBIT, 3);
    if (Sd->mBadTableFlag != 0) {
      return 0;
    }

    ReadCLen (Sd);

    Sd->mBadTableFlag = ReadPTLen (Sd, MAXNP, Sd->mPBit, (UINT16)(-1));
    if (Sd->mBadTableFlag != 0) {
      return 0;
    }
  }

  Sd->mBlockSize --;
  j = Sd->mCTable[Sd->mBitBuf >> (BITBUFSIZ - 12)];

  if (j >= NC) {
    Mask = 1U << (BITBUFSIZ - 1 - 12);

    do {
      if (Sd->mBitBuf & Mask) {
        j = Sd->mRight[j];
      } else {
        j = Sd->mLeft[j];
      }

      Mask >>= 1;
    } while (j >= NC);
  }

  //
  // Advance what we have read
  //
  FillBuf(Sd, Sd->mCLen[j]);

  return j;
}

//*************************************************************************
//<INT:AMI_PHDR_START>
//
// Name: Decode
//
// Description:
//  VOID Decode(IN OUT SCRATCH_DATA *Sd) decodes the source data and puts the
// resulting data into the destination buffer.
//
// Input:
//  IN OUT SCRATCH_DATA *Sd
// The global scratch data.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//  DecodeC
//
// Notes:	
//          
//<INT:AMI_PHDR_END>
//*************************************************************************
STATIC
VOID
Decode (
  SCRATCH_DATA  *Sd
  )
{
  UINT16      BytesRemain;
  UINT32      DataIdx;
  UINT16      c;
  
  BytesRemain = (UINT16)(-1);

  DataIdx = 0;

  for (;;) {
    c = DecodeC (Sd);
    if (Sd->mBadTableFlag != 0) {
      return;
    }

    if (c < 256) {

      //
      // Process an Original character
      //

        if (Sd->mOutBuf >= Sd->mOrigSize ) {
            return;
        } else {
            Sd->mDstBase[Sd->mOutBuf ++] = (UINT8)c;
        }

    } else {

      //
      // Process a Pointer
      //

      c = (UINT16)(c - (UINT8_MAX + 1 - THRESHOLD));

      BytesRemain = c;
      
      DataIdx  = Sd->mOutBuf - DecodeP(Sd) - 1;

      BytesRemain --;
      while ((INT16)(BytesRemain) >= 0) {
        Sd->mDstBase[Sd->mOutBuf ++] = Sd->mDstBase[DataIdx ++];
        if (Sd->mOutBuf >= Sd->mOrigSize) {
          return;
        }
        BytesRemain --;
      }
    }
  }

  return;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: GetInfo
//
// Description:
//  EFI_STATUS GetInfo(IN VOID *Source, IN UINT32 SrcSize,
// OUT UINT32 *DstSize, OUT UINT32 *ScratchSize) is the internal
// implementation of DECOMPRESS_PROTOCOL.GetInfo().
// External consumers should use Decompress Protocol (not this function).
//
// Input:
//  IN VOID *Source
// The source buffer containing the compressed data.
//
//  IN UINT32 SrcSize
// The size of source buffer.
//
//  OUT UINT32 *DstSize
// The size of destination buffer.
//
//  OUT UINT32 *ScratchSize
// The size of scratch buffer.
//
// Output:
//  EFI_SUCCESS,           if the size of destination buffer and the size of
//                        scratch buffer are successull retrieved.
//  EFI_INVALID_PARAMETER, if the source data is corrupted.
//
// Modified:
//
// Referrals:
//
// Notes:	
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS
GetInfo (
  IN      VOID    *Source,
  IN      UINT32  SrcSize,
  OUT     UINT32  *DstSize,
  OUT     UINT32  *ScratchSize
  )
{
  UINT8 *Src;

  *ScratchSize = sizeof (SCRATCH_DATA);

  Src = Source;
  if (SrcSize < 8) {
    return EFI_INVALID_PARAMETER;
  }
  
  *DstSize = Src[4] + (Src[5] << 8) + (Src[6] << 16) + (Src[7] << 24);
  return EFI_SUCCESS;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: Decompress
//
// Description:
//  EFI_STATUS Decompress(IN VOID *Source, IN UINT32 SrcSize,
// IN OUT VOID *Destination, IN UINT32 DstSize, IN OUT VOID *Scratch,
// IN UINT32 ScratchSize) is the internal implementation of
// DECOMPRESS_PROTOCOL.Decompress().
// External consumers should use Decompress Protocol (not this function).
//
// Input:
//  IN VOID *Source
// The source buffer containing the compressed data.
//
//  IN UINT32 SrcSize
// The size of source buffer.
//
//  IN OUT VOID *Destination
// The destination buffer to store the decompressed data.
//
//  IN UINT32 DstSize
// The size of destination buffer.
//
//  IN OUT VOID *Scratch
// The buffer used internally by the decompress routine. This  buffer is
// needed to store intermediate data.
//
//  IN UINT32 ScratchSize
// The size of scratch buffer.
//
// Output:
//  EFI_SUCCESS,           if the decompression is successfull.
//  EFI_INVALID_PARAMETER, if the source data is corrupted.
//
// Modified:
//
// Referrals:
//  FillBuf
//  Decode
//
// Notes:	
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS
Decompress (
  IN      VOID    *Source,
  IN      UINT32  SrcSize,
  IN OUT  VOID    *Destination,
  IN      UINT32  DstSize,
  IN OUT  VOID   *Scratch,
  IN      UINT32  ScratchSize
  )
{
  UINT32        Index;
  UINT32        CompSize;
  UINT32        OrigSize;
  EFI_STATUS    Status;
  SCRATCH_DATA  *Sd;
  UINT8         *Src;
  UINT8         *Dst;
  UINT8			PBit;
  Status = EFI_SUCCESS;
  Src  = Source;
  Dst  = Destination;
  
  if (ScratchSize < sizeof (SCRATCH_DATA)) {
      return  EFI_INVALID_PARAMETER;
  }
  
  Sd = (SCRATCH_DATA *)Scratch;
  
  if (SrcSize < 8) {
    return EFI_INVALID_PARAMETER;
  }
  
  CompSize = Src[0] + (Src[1] << 8) + (Src[2] << 16) + (Src[3] << 24);
  OrigSize = Src[4] + (Src[5] << 8) + (Src[6] << 16) + (Src[7] << 24);
  
  //
  // If compressed file size is 0, return
  //

  if (OrigSize == 0) {
      return Status;
  }

  if (SrcSize < CompSize + 8) {
    return EFI_INVALID_PARAMETER;
  }
  
  if (DstSize != OrigSize) {
    return EFI_INVALID_PARAMETER;
  }
  
  Src = Src + 8;

//
// The length of the field 'Position Set Code Length Array Size' in Block Header.
// For EFI 1.1 de/compression algorithm(Version 1), mPBit = 4
// For Tiano de/compression algorithm(Version 2), mPBit = 5
//
  //assume Tiano decompression first.
  //if decompression fails try with EFI decompression
  for(PBit = 5; PBit>=4; PBit--){
      for (Index = 0; Index < sizeof(SCRATCH_DATA); Index++) {
        ((UINT8*)Sd)[Index] = 0;
      }
      Sd->mSrcBase = Src;
      Sd->mDstBase = Dst;
      Sd->mCompSize = CompSize;
      Sd->mOrigSize = OrigSize;
	  Sd->mPBit = PBit;
      //
      // Fill the first BITBUFSIZ bits
      //
      FillBuf(Sd, BITBUFSIZ);

      //
      // Decompress it
      //

      Decode (Sd);
	  
	  if (!Sd->mBadTableFlag) break;
  }
    
  return  (Sd->mBadTableFlag) ? EFI_INVALID_PARAMETER : EFI_SUCCESS;
}

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
