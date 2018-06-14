//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/TdtWrapper/TdtCallback.h 1     2/08/12 1:07a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:07a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/TdtWrapper/TdtCallback.h $
// 
// 1     2/08/12 1:07a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:40a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:09a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            TdtCallBack.h
//
// Description:     Setup Var definetion.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#define TDT_VOLATILE_SETUP_DATA_GUID \
{0x7b77fb8b, 0x1e0d, 0x4d7e, 0x95, 0x3f, 0x39, 0x80, 0xa2, 0x61, 0xe0, 0x76}

#define TDT_VOLATILE_SETUP_DATA_C_NAME         L"TdtAdvancedSetupDataVar"

typedef struct _TDT_VOLATILE_SETUP_DATA {
  UINT8  TdtEnroll;
} TDT_VOLATILE_SETUP_DATA;

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************