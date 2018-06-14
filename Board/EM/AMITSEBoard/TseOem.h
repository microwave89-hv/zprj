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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/AMITSEBoard/TseOem.h $
//
// $Author: Arunsb $
//
// $Revision: 3 $
//
// $Date: 10/18/12 6:34a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/AMITSEBoard/TseOem.h $
// 
// 3     10/18/12 6:34a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 4     10/10/12 12:25p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 2     2/19/10 12:58p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 3     2/19/10 8:04a Mallikarjunanv
// updated year in copyright message
// 
// 2     6/24/09 6:33p Madhans
// Coding Standards
// 
// 1     6/09/09 9:53a Madhans
// TSE 2.00.1201
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 11:03p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:25p Madhans
// Tse 2.0 Code complete Checkin.
// 
//
// 
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		TseOem.h
//
// Description:	
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _TSEOEM_H_
#define	_TSEOEM_H_

///dummy structure to avoid compilation errors (moved from AMIVfr.h)
typedef struct _TSE_SETUP_DATA
{
  UINT16    BootCount;

/*  UINT16    TimeoutValue;
  UINT8     Access;
  UINT16    BootCount;
  UINT16    BootValue;
  UINT16    HardDiskCount;
  UINT16    CDROMCount;
  UINT16    FloppyCount;
  UINT16    NetworkCount;
  UINT16    BBSValue;
  UINT16    AMICallback;
  AMITSESETUP   AmiTseSetup;
  UINT8     Reserved2[100];
*/
}TSE_SETUP_DATA;



#endif	///_TSEOEM_H_

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
