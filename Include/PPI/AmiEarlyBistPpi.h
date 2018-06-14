//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPPIs/AmiEarlyBistPpi.h 1     2/07/12 3:58a Davidhsieh $
//
// $Revision: 1 $
//
// $Date: 2/07/12 3:58a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPPIs/AmiEarlyBistPpi.h $
// 
// 1     2/07/12 3:58a Davidhsieh
// 
// 1     5/06/11 6:07a Davidhsieh
// First release
// 
// 2     3/04/09 10:42a Markw
// Update copyright header.
// 
// 1     10/03/08 1:18p Markw
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	AmiEarlyBistPpi.h
//
// Description: AmiEarlyBistPpi.h
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __AMI_EARLY_BIST_PPI_H__
#define __AMI_EARLY_BIST_PPI_H__
#ifdef __cplusplus
extern "C" {
#endif

//a7e2ce72-dc32-4bc0-9e35-feb30ae5cc47
#define AMI_EARLY_BIST_PPI_GUID \
    {0xa7e2ce72, 0xdc32, 0x4bc0, 0x9e, 0x35, 0xfe, 0xb3, 0xa, 0xe5, 0xcc, 0x47}

typedef struct {
    UINT32 ApicId;
    UINT32 Bist;
} CPU_BIST;


typedef struct {
	UINT32      NumBists;       //Number of Bists in array.
    CPU_BIST    CpuBist[1];     //Variable length array
} AMI_EARLY_BIST_PPI;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
