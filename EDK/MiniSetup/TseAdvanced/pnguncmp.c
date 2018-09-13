//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/pnguncmp.c $
//
// $Author: Arunsb $
//
// $Revision: 3 $
//
// $Date: 10/18/12 5:53a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/pnguncmp.c $
// 
// 3     10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 2     10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 2     6/20/11 1:19p Rajashakerg
// [TAG]  		EIP60910 
// [Description]  	Updated with respect to the review comments.
// 
// 1     6/13/11 12:21p Rajashakerg
// EIP:60910 -PNG image support in TSE.
// 
//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		pnguncmp.c
//
// Description:		This file contains code for pcx image handling
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "png.h"
#define codeLengthLen  19

typedef struct _PngHuffmanTree
{
	unsigned dat;	
	struct _PngHuffmanTree *zero, *one;
}PngHuffmanTree;

void MakeFixedHuffmanCode(unsigned *hLength, unsigned *hCode);
void MakeDynamicHuffmanCode(unsigned hLength[288], unsigned hCode[288], unsigned nLng, unsigned lng[]);
EFI_STATUS DecodeDynamicHuffmanCode
			(unsigned int *hLit, unsigned int *hDist, unsigned int*hCLen,
			unsigned int **hLengthLiteral, unsigned int **hCodeLiteral,
			unsigned int **hLengthDist, unsigned int **hCodeDist,
			unsigned int *hLengthBuf, unsigned int *hCodeBuf,
			const unsigned char dat[], unsigned int *bytePtr, unsigned int *bitPtr);

PngHuffmanTree *MakeHuffmanTree(unsigned n, unsigned *hLength, unsigned *hCode);
void DeleteHuffmanTree(PngHuffmanTree *node);

unsigned GetCopyLength(unsigned value, unsigned char dat[], unsigned *bytePtr, unsigned *bitPtr);
unsigned GetBackwardDistance(unsigned distCode, unsigned char dat[], unsigned *bytePtr, unsigned *bitPtr);


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:		GetNextBit()
//
// Description: To get the Next Bit
//
// Input:		const unsigned char dat[], unsigned *bytePtr, unsigned *bitPtr
//
// Output:		unsigned int
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
unsigned int GetNextBit(const unsigned char dat[], unsigned *bytePtr, unsigned *bitPtr)
{
	unsigned a;
	unsigned b;
	a = dat[*bytePtr] & *bitPtr;
	*bitPtr <<= 1;
	if(*bitPtr >= 256)
	{
		*bitPtr = 1;
		(*bytePtr)++;
	}
	b = (a != 0 ? 1 : 0);
	return b;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:		GetNextMultiBit()
//
// Description: To get the Next multiple Bits.
//
// Input:		const unsigned char dat[], unsigned *bytePtr, unsigned *bitPtr, unsigned n
//
// Output:		unsigned int
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
unsigned int GetNextMultiBit(const unsigned char dat[], unsigned *bytePtr, unsigned *bitPtr, unsigned n)
{
	unsigned value,mask,i;
	value = 0;
	mask = 1;
	for(i = 0; i < n; i++)
	{
		if(GetNextBit(dat,bytePtr,bitPtr))
		{
			value |= mask;
		}
		mask <<= 1;
	}
	return value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:		MakeFixedHuffmanCode()
//
// Description: To make the fixed huffman code
//
// Input:		unsigned hLength[288],unsigned hCode[288]
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void MakeFixedHuffmanCode(unsigned *hLength, unsigned *hCode)
{
	unsigned i;
	for(i = 0; i <= 143; i++)
	{
		hLength[i] = 8;
		hCode[i] = 0x30+i;
	}
	for(i = 144; i <= 255; i++)
	{
		hLength[i] = 9;
		hCode[i] = 0x190 + (i-144);
	}
	for(i = 256; i <= 279; i++)
	{
		hLength[i] = 7;
		hCode[i] = i - 256;
	}
	for(i=280; i<=287; i++)
	{
		hLength[i] = 8;
		hCode[i] = 0xc0 + (i-280);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:		MakeDynamicHuffmanCode()
//
// Description: To make the Dynamic Huffman Code
//
// Input:		unsigned hLength[],unsigned hCode[],unsigned nLng,unsigned lng[]
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void MakeDynamicHuffmanCode(unsigned hLength[], unsigned hCode[], unsigned nLng, unsigned lng[])
{
	unsigned i, maxLng, code, *bl_count, *next_code, bits, n;

	for(i = 0; i < nLng; i++)
	{
		hLength[i] = lng[i];
		hCode[i] = 0;
	}

	maxLng = 0;
	for(i = 0; i < nLng; i++)
	{
		if(maxLng < lng[i])
		{
			maxLng = lng[i];
		}
	}

	bl_count =  (unsigned int *) EfiLibAllocateZeroPool((maxLng+1)*sizeof(unsigned));
	if (!bl_count) {
		return;
	}
	next_code = (unsigned int *) EfiLibAllocateZeroPool((maxLng+1)*sizeof(unsigned));
	if (!next_code) {
		MemFreePointer(&bl_count);	
		return;
	}
	for(i = 0; i < maxLng+1; i++)
	{
		bl_count[i] = 0;
		next_code[i] = 0;
	}
	for(i = 0; i < nLng; i++)
	{
		bl_count[lng[i]]++;
	}

	code = 0;
	bl_count[0] = 0;
	for (bits = 1; bits <= maxLng; bits++)
	{
		code = (code + bl_count[bits-1]) << 1;
		next_code[bits] = code;
	}

	for (n = 0; n < nLng; n++)
	{
		unsigned len;
		len = lng[n];
		if (len > 0)
		{
			hCode[n] = next_code[len]++;
		}
	}

	if (bl_count != NULL)
	{
		MemFreePointer(&bl_count);
	}
	if (next_code != NULL)
	{
		MemFreePointer(&next_code);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:		DecodeDynamicHuffmanCode()
//
// Description: Decodeing the Dynamic Huffman Code
//
// Input:		unsigned int &hLit,unsigned int &hDist,unsigned int &hCLen,
//			    unsigned int *&hLengthLiteral,unsigned int *&hCodeLiteral,
//				unsigned int *&hLengthDist,unsigned int *&hCodeDist,
//				unsigned int hLengthBuf[322],unsigned int hCodeBuf[322],
//				const unsigned char dat[],unsigned int &bytePtr,unsigned int &bitPtr
//
// Output:		int
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DecodeDynamicHuffmanCode
	   (unsigned int *hLit, unsigned int *hDist, unsigned int *hCLen,
	    unsigned int **hLengthLiteral, unsigned int **hCodeLiteral,
	    unsigned int **hLengthDist, unsigned int **hCodeDist,
	    unsigned int *hLengthBuf, unsigned int *hCodeBuf,
	    const unsigned char dat[], unsigned int *bytePtr, unsigned int *bitPtr)
{
	unsigned int i;
	unsigned int nExtr=0;	
	PngHuffmanTree *lengthTree, *lengthTreePtr;
	unsigned value, copyLength;
	unsigned codeLengthOrder[codeLengthLen] =
	{
		16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15
	};
	unsigned codeLengthCode[codeLengthLen];
	unsigned hLengthCode[codeLengthLen],hCodeCode[codeLengthLen];

	*hLit = 0;
	*hDist = 0;
	*hCLen = 0;

	*hLit = GetNextMultiBit(dat, bytePtr, bitPtr, 5);
	*hDist = GetNextMultiBit(dat, bytePtr, bitPtr, 5);
	*hCLen = GetNextMultiBit(dat, bytePtr, bitPtr, 4);

	for (i = 0; i < codeLengthLen; i++)
	{
		codeLengthCode[i] = 0;
	}
	for (i = 0; i < *hCLen+4; i++)
	{
		codeLengthCode[codeLengthOrder[i]] = GetNextMultiBit(dat, bytePtr, bitPtr, 3);
	}
	
	MakeDynamicHuffmanCode(hLengthCode, hCodeCode, codeLengthLen, codeLengthCode);

	*hLengthLiteral = hLengthBuf;
	*hCodeLiteral = hCodeBuf;
	*hLengthDist = hLengthBuf + *hLit + 257;
	*hCodeDist = hCodeBuf+ *hLit + 257;

	
	lengthTree = MakeHuffmanTree(codeLengthLen, hLengthCode, hCodeCode);
	if (lengthTree == NULL) {
		return EFI_ABORTED;
	}

	lengthTreePtr = lengthTree;
	while (nExtr < *hLit + 257 + *hDist +1)
	{
		if (GetNextBit(dat, bytePtr, bitPtr))
		{
			if(lengthTreePtr->one){
				lengthTreePtr = lengthTreePtr->one;
			}
		}
		else
		{
			if(lengthTreePtr->zero){
				lengthTreePtr = lengthTreePtr->zero;
			}
		}
		if (lengthTreePtr->zero == NULL && lengthTreePtr->one == NULL)
		{
			
			value = lengthTreePtr->dat;

			if (value <= 15)
			{
				hLengthBuf[nExtr++] = value;
			}
			else if (value == 16)
			{
				copyLength = 3 + GetNextMultiBit(dat, bytePtr, bitPtr, 2);
				while (copyLength > 0)
				{
					hLengthBuf[nExtr] = hLengthBuf[nExtr-1];
					nExtr++;
					copyLength--;
				}
			}
			else if (value == 17)
			{
				copyLength = 3 + GetNextMultiBit(dat, bytePtr, bitPtr, 3);
				while (copyLength > 0)
				{
					hLengthBuf[nExtr++] = 0;
					copyLength--;
				}
			}
			else if (value == 18)
			{
				copyLength = 11 + GetNextMultiBit(dat, bytePtr, bitPtr, 7);
				while (copyLength > 0)
				{
					hLengthBuf[nExtr++] = 0;
					copyLength--;
				}
			}

			lengthTreePtr = lengthTree;
		}
	}

	MakeDynamicHuffmanCode(*hLengthLiteral, *hCodeLiteral, *hLit+257, *hLengthLiteral);
	MakeDynamicHuffmanCode(*hLengthDist, *hCodeDist, *hDist+1, *hLengthDist);

	DeleteHuffmanTree(lengthTree);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:		MakeHuffmanTree()
//
// Description: To create the huffman tree
//
// Input:		unsigned n,unsigned hLength[],unsigned hCode[]
//
// Output:		PngHuffmanTree	
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
PngHuffmanTree *MakeHuffmanTree(unsigned n, unsigned *hLength, unsigned *hCode)
{
	unsigned i, j, mask;
	PngHuffmanTree *root, *ptr;

	root = EfiLibAllocateZeroPool(sizeof(PngHuffmanTree));
	if (root == NULL) {
		return (PngHuffmanTree *)NULL;
	}

	for (i = 0; i < n; i++)
	{
		if (hLength[i] > 0)
		{
			ptr = root;
			mask = (1<<(hLength[i]-1));
			for (j = 0; j < hLength[i]; j++)
			{
				if (hCode[i] & mask)
				{
					if (ptr->one == NULL)
					{
						ptr->one = EfiLibAllocateZeroPool(sizeof(PngHuffmanTree));
					}
					ptr = ptr->one;
				}
				else
				{
					if (ptr->zero == NULL)
					{
						ptr->zero = EfiLibAllocateZeroPool(sizeof(PngHuffmanTree));
					}
					ptr = ptr->zero;
				}
				mask >>= 1;
			}
			ptr->dat = i;
		}
	}

	return root;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:		DeleteHuffmanTree()
//
// Description: Deleting the created Trees
//
// Input:		PngHuffmanTree *node
//
// Output:		String size
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void DeleteHuffmanTree(PngHuffmanTree *node)
{
	if (node != NULL)
	{
		DeleteHuffmanTree(node->zero);			//Delete the Huffman tree
		DeleteHuffmanTree(node->one);
		   MemFreePointer( &node);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:		GetCopyLength()
//
// Description: To Get the correct Copy Length
//
// Input:		unsigned value,unsigned char dat[],unsigned &bytePtr,unsigned &bitPtr
//
// Output:		unsigned int
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
unsigned GetCopyLength(unsigned value, unsigned char dat[], unsigned *bytePtr, unsigned *bitPtr)
{
	unsigned copyLength;
	unsigned base,offset,extBits;

	if (value <= 264)
	{
		copyLength = 3 + (value - 257);
	}
	else if (value >= 285)
	{
		copyLength = 258;
	}
	else
	{
		extBits = 1 + (value-265) / 4;
		base = (8 << ((value-265) / 4)) + 3;
		offset = ((value-265) & 3) * (2 << ((value - 265) / 4));

		copyLength = GetNextMultiBit(dat, bytePtr, bitPtr, extBits);
		copyLength += base+offset;
	}

	return copyLength;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:		GetBackwardDistance()
//
// Description: To get the Backward Distance
//
// Input:		unsigned distCode,unsigned char dat[],unsigned &bytePtr,unsigned &bitPtr
//
// Output:		unsigned int 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
unsigned GetBackwardDistance
   (unsigned distCode, unsigned char dat[], unsigned *bytePtr, unsigned *bitPtr)
{
	unsigned backDist;
	unsigned base, offset, extBits;

	if (distCode <= 3)
	{
		backDist = distCode + 1;
	}
	else
	{
		

		base = (4 << ((distCode - 4) / 2)) + 1;
		offset = (distCode&1) * (2 << ((distCode - 4) / 2));
		extBits = (distCode - 2) / 2;

		backDist = GetNextMultiBit(dat,bytePtr,bitPtr,extBits);
		backDist += base + offset;
	}

	return backDist;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Uncompress()
//
// Description: Used to Uncompress the Image data and to convert the RGB format.
//
// Input:		unsigned length,unsigned char dat[]
//
// Output:		int
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Uncompress(unsigned length, unsigned char dat[])
{
	unsigned windowUsed;
	unsigned char *windowBuf;
	unsigned nByteExtracted;
	PngHuffmanTree *codeTree, *codeTreePtr;
	PngHuffmanTree *distTree, *distTreePtr;
	unsigned bytePtr, bitPtr;
	unsigned char cmf, flg;
	unsigned cm, cInfo, windowSize;
	unsigned fDict;
	unsigned *hLengthBuf = (unsigned *)NULL;
	unsigned *hCodeBuf = (unsigned *)NULL;
	unsigned *hLength = (unsigned *)NULL;
	unsigned *hCode = (unsigned *)NULL;
	unsigned value;
	unsigned copyLength,distCode,backDist;
	int i=0;
	windowBuf = (unsigned char *)NULL;
	
	codeTree = (PngHuffmanTree *)NULL;
	distTree = (PngHuffmanTree *)NULL;
	bytePtr = 0;
	bitPtr = 1;
	nByteExtracted = 0;

	cmf = dat[bytePtr++];
	flg = dat[bytePtr++];

	cm = cmf&0x0f;
	if (cm != 8)
	{
		goto ERREND;
	}

	cInfo = (cmf&0xf0)>>4;
	windowSize = 1 << (cInfo + 8);

	windowBuf = (unsigned char *)EfiLibAllocateZeroPool(windowSize);
	windowUsed = 0;

	fDict = (flg&32) >> 5;

	if (fDict != 0)
	{
		goto ERREND;
	}

	while (1)
	{
		unsigned bFinal,bType;

		bFinal = GetNextBit(dat, &bytePtr, &bitPtr);
		bType = GetNextMultiBit(dat, &bytePtr, &bitPtr, 2);

		if (bytePtr >= length)
		{
			goto ERREND;
		}

		if (bType == 0) // No Compression
		{
			unsigned len;
			if (bitPtr != 1) //Skip the current byte.
			{
				bitPtr = 1;
				bytePtr++;
			}
			if (bytePtr >= length)
			{
				goto ERREND;
			}

			len = dat[bytePtr] + dat[bytePtr + 1] * 256;
			bytePtr += 4; //Skip bytes for length(2 bytes) and 1's complement of length(2 bytes).
			
			for( i=0; i<(int)len; i++) //Feed the image data that is not compressed to output buffer.  
			{
				Output(dat[bytePtr+i]);
			}
			bytePtr += len;
		}
		else if (bType == 1 || bType == 2)
		{
			codeTree = (PngHuffmanTree *)NULL;

			if (bType == 1)
			{
				hLength = (unsigned *)EfiLibAllocateZeroPool(288 * sizeof(unsigned));						//Prefast issue fix - Exceeds stack size issue
				hCode = (unsigned *)EfiLibAllocateZeroPool(288 * sizeof(unsigned));
				if (!hLength || !hCode) {
					goto ERREND;
				}
				MakeFixedHuffmanCode(hLength, hCode);
				codeTree = MakeHuffmanTree(288, hLength, hCode);
				distTree = (PngHuffmanTree *)NULL;
				if (hLength) {											//Prefast issue fix - Exceeds stack size issue
					   MemFreePointer( &hLength);
				}
				if (hCode) {
					 MemFreePointer( &hCode);
				}
			}
			else
			{
				unsigned hLit, hDist, hCLen;
				unsigned *hLengthLiteral, *hCodeLiteral;
				unsigned *hLengthDist, *hCodeDist;
				
				hLengthBuf =  (unsigned *)EfiLibAllocateZeroPool(322 * sizeof(unsigned));						//Prefast issue fix - Exceeds stack size issue
				hCodeBuf = (unsigned *)EfiLibAllocateZeroPool(322 * sizeof(unsigned));

				/*Changes
				hLengthLiteral =  (unsigned *)EfiLibAllocateZeroPool(322 * sizeof(unsigned));
				hCodeLiteral =  (unsigned *)EfiLibAllocateZeroPool(322 * sizeof(unsigned));
				hLengthDist =  (unsigned *)EfiLibAllocateZeroPool(322 * sizeof(unsigned));
				hCodeDist =  (unsigned *)EfiLibAllocateZeroPool(322 * sizeof(unsigned));	

				*/
				if (!hLengthBuf || !hCodeBuf) {
					goto ERREND;
				}

				if (DecodeDynamicHuffmanCode
				   (&hLit, &hDist, &hCLen,
				    &hLengthLiteral, &hCodeLiteral, &hLengthDist, &hCodeDist, hLengthBuf, hCodeBuf,
					dat, &bytePtr, &bitPtr)) {
						goto ERREND;
				}

				codeTree = MakeHuffmanTree(hLit+257, hLengthLiteral, hCodeLiteral);
				if (codeTree == NULL) {
					goto ERREND;
				}
				distTree = MakeHuffmanTree(hDist+1, hLengthDist, hCodeDist);
				if (distTree == NULL) {
					goto ERREND;
				}
				/*
				if (hLengthLiteral) {									//Prefast issue fix - Exceeds stack size issue
					   MemFreePointer( &hLengthLiteral);
				}
				if (hCodeLiteral) {									//Prefast issue fix - Exceeds stack size issue
					   MemFreePointer( &hCodeLiteral);
				}
				if (hLengthDist) {									//Prefast issue fix - Exceeds stack size issue
					   MemFreePointer( &hLengthDist);
				}
				if (hCodeDist) {									//Prefast issue fix - Exceeds stack size issue
					   MemFreePointer( &hCodeDist);
				}
				*/
				if (hLengthBuf) {									//Prefast issue fix - Exceeds stack size issue
					   MemFreePointer( &hLengthBuf);
				}
				if (hCodeBuf) {
					   MemFreePointer( &hCodeBuf);
				}
			}

			codeTreePtr = codeTree;
			if (codeTree != NULL)
			{
				while (1)
				{
					if (GetNextBit(dat, &bytePtr, &bitPtr))
					{
						codeTreePtr = codeTreePtr->one;
					}
					else
					{
						codeTreePtr = codeTreePtr->zero;
					}

					if (codeTreePtr == NULL)
					{
						goto ERREND;
					}

					if (codeTreePtr->zero == NULL && codeTreePtr->one == NULL)
					{
					
						value = codeTreePtr->dat;
						if (value < 256)
						{
							windowBuf[windowUsed++] = (unsigned char)value;
							windowUsed &= (windowSize - 1);
							if (Output((unsigned char)value))
							{
								goto ERREND;
							}
							nByteExtracted++;
						}
						else if (value == 256)
						{
							break;
						}
						else if (value <= 285)
						{
							
							copyLength = GetCopyLength(value, dat, &bytePtr, &bitPtr);

							if (bType == 1)
							{
								distCode = 16 * GetNextBit(dat, &bytePtr, &bitPtr);  // 5 bits fixed
								distCode += 8 * GetNextBit(dat, &bytePtr, &bitPtr);  // Reversed order
								distCode += 4 * GetNextBit(dat, &bytePtr, &bitPtr);
								distCode += 2 * GetNextBit(dat, &bytePtr, &bitPtr);
								distCode += GetNextBit(dat, &bytePtr, &bitPtr);
							}
							else
							{
								distTreePtr = distTree;
								while (distTreePtr->zero != NULL || distTreePtr->one != NULL)
								{
									if (GetNextBit(dat,&bytePtr,&bitPtr))
									{
										if (distTreePtr->one)					//Fix for Fortify issue - Null Dereference
											distTreePtr = distTreePtr->one;
									}
									else
									{
										if (distTreePtr->zero)					//Fix for Fortify issue - Null Dereference
											distTreePtr = distTreePtr->zero;
									}
								}
								distCode = distTreePtr->dat;
							}
							backDist = GetBackwardDistance(distCode,dat,&bytePtr,&bitPtr);

						
							for(i=0; i < (int)copyLength; i++)
							{
								unsigned char dat;
								dat = windowBuf[(windowUsed-backDist)&(windowSize-1)];
								if (Output(dat))
								{
									goto ERREND;
								}
								nByteExtracted++;
								windowBuf[windowUsed++] = dat;
								windowUsed &= (windowSize-1);
							}
						}

						codeTreePtr = codeTree;
					}

					if (length <= bytePtr)
					{
						goto ERREND;
					}
				}
			}


			DeleteHuffmanTree(codeTree);
			DeleteHuffmanTree(distTree);
			codeTree = (PngHuffmanTree *)NULL;
			distTree = (PngHuffmanTree *)NULL;
		}
		else
		{
			goto ERREND;
		}


		if (bFinal != 0)
		{
			break;
		}
	}

	   MemFreePointer( &windowBuf);
	windowBuf = (unsigned char *)NULL;

	return EFI_SUCCESS;

ERREND:
	if (windowBuf != NULL)
	{
		   MemFreePointer( &windowBuf);
	}
	if (codeTree != NULL)
	{
		DeleteHuffmanTree(codeTree);
		codeTree = (PngHuffmanTree *)NULL;
	}
	if (distTree != NULL)
	{
		DeleteHuffmanTree(distTree);
		distTree = (PngHuffmanTree *)NULL;
	}
	if (hLength) {												//Prefast issue fix - Exceeds stack size issue
		   MemFreePointer( &hLength);
	}
	if (hCode) {
		   MemFreePointer( &hCode);
	}
	if (hLengthBuf) {
		   MemFreePointer( &hLengthBuf);
	}
	if (hCodeBuf) {
		   MemFreePointer( &hCodeBuf);
	}
	return EFI_ABORTED;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************



	