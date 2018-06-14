//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************//
// $Header: /Alaska/BIN/Modules/ACPI/Template/Board/OEM_ACPI.H 3     3/26/09 4:47p Oleksiyy $
//
// $Revision: 3 $
//
// $Date: 3/26/09 4:47p $
//**********************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Board/OEM_ACPI.H $
// 
// 3     3/26/09 4:47p Oleksiyy
// New ACPI Core realization - improves logic, execution time and memory
// usage of ACPI module.
// 
// 1     2/18/09 3:50p Oleksiyy
// 
// 2     1/12/09 11:43a Yakovlevs
// OemAcpiSetPlatformId function Definition added.
// 
// 1     3/24/05 5:00p Sivagarn
// Initial Checkin
// 
// 1     2/03/05 6:41p Sivagarn
// 0ABHI001 Check in
// 
// 3     1/19/05 7:25p Yakovlevs
// 
// 2     7/27/04 6:45p Yakovlevs
// 
// 1     4/08/04 3:29p Yakovlevs
// 
// 2     9/21/01 3:32p Yakovlevs
// Code cleanup
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	OEM_ACPI.H
//
// Description:	OEM specific Definitions in ACPI Module
//
//<AMI_FHDR_END>
//**********************************************************************
//**********************************************************************//
//		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	//
//		!!!!! When porting, should specify proper values here !!!!!!	//
//		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	//
//**********************************************************************//

#ifndef  _ACPIOEM_H   //To Avoid this header get compiled twice
#define  _ACPIOEM_H

#include <Efi.h>
#include <ACPI.h>




//**********************************************************************//
//Function Prototypes
EFI_STATUS OemAcpiSetPlatformId(IN OUT ACPI_HDR *AcpiHdr);



#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
