//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/debug.c 7     5/16/08 12:01p Olegi $
//
// $Revision: 7 $
//
// $Date: 5/16/08 12:01p $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/debug.c $
// 
// 7     5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 6     3/20/07 12:18p Olegi
//
// 4     4/14/06 6:39p Olegi
// Conversion to be able to use x64 compiler.
//
// 3     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 2     8/26/05 12:25p Andriyn
// Simulate Mouse Sampling rate by disabling Mouse Polling (reduce USB
// SMI# generation)
//
// 1     3/28/05 6:20p Olegi
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           Debug.c
//
//  Description:    AMI USB Debug output implementation routnes
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        PrintDebugMessage (variable param)
//
// Description: This routine prints the debug message
//
// Parameters: Variable
//
// Output:      Status: SUCCESS = Success
//                      FAILURE = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

RETCODE
PrintDebugMsg(
    int MsgLevel,
    char * Message, ...)
{
    VA_LIST ArgList;

    VA_START(ArgList, Message);

    if ((MsgLevel == 0) ||
        ((MsgLevel <= TopDebugLevel) &&
            (MsgLevel >= BottomDebugLevel)))
    {
#if DEBUG_SWITCH == 1
        EfiDebugVPrint(EFI_D_ERROR, Message, ArgList);
#endif
    }

    VA_END(ArgList);

    return SUCCESS;
}
//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
