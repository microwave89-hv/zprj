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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/amiver.h $
//
// $Author: Arunsb $
//
// $Revision: 4 $
//
// $Date: 10/18/12 5:58a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/amiver.h $
// 
// 4     10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 3     2/19/10 1:01p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:11p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
// 
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		amiver.h
//
// Description:	This file contains version macros.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _AMIVER_H_
#define	_AMIVER_H_

#define AMI_VERSION_SIGNATURE	{'$','A','P','V'}

#pragma pack(1)
typedef struct
{
	CHAR8	signature[4];
	UINT8	major;
	UINT8	minor;
	UINT16	build;
	CHAR8	name[4];
	UINT8	reserved[4];
}
AMI_VERSION;
#pragma pack()

#ifdef __cplusplus
extern "C"
{
#define	AMI_SET_VERSION(major,minor,build,sign)	\
AMI_VERSION gVersion_##sign = { \
	AMI_VERSION_SIGNATURE, \
	major, \
	minor, \
	build, \
    ##sign, \
	{ 0, 0, 0, 0 } \
}

}
#else

#define	AMI_SET_VERSION(major,minor,build,sign)	\
AMI_VERSION gVersion_##sign = { \
	AMI_VERSION_SIGNATURE, \
	major, \
	minor, \
	build, \
    #sign, \
	{ 0, 0, 0, 0 } \
}


#endif //__cplusplus

#define	AMI_GET_VERSION_MAJOR(ver)	((ver).major)
#define	AMI_GET_VERSION_MINOR(ver)	((ver).minor)
#define	AMI_GET_VERSION_BUILD(ver)	((ver).build)
#define	AMI_GET_VERSION_NAME(ver)	((ver).name)

#define	AMI_VERSION_STRUCT(sign)	(gVersion_##sign)

#define	AMI_CHECK_VERSION(ver) \
	( ((ver).major != 0) || ((ver).minor != 0) )

#endif /* _AMIVER_H_ */

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
