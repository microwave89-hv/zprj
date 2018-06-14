//
// This file contains an 'Intel Peripheral Driver' and is      
// licensed for Intel CPUs and chipsets under the terms of your
// license agreement with Intel or your vendor.  This file may 
// be modified by the user, subject to additional terms of the 
// license agreement                                           
//
/*++

Copyright (c)  1999 - 2003 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:
  
    AcpiVariable.h
    
Abstract:

    GUIDs used for ACPI variables.

--*/

#ifndef _ACPI_VARIABLE_H_
#define _ACPI_VARIABLE_H_

#define EFI_EXTD_ACPI_VARIABLE_GUID \
  { \
    0xbf0c61cd, 0x9ba, 0x49d8, 0x91, 0x87, 0xc2, 0x3a, 0x19, 0x38, 0x41, 0xa4 \
  }

#define EXTD_ACPI_GLOBAL_VARIABLE  L"ExtdAcpiGlobalVariable"

typedef struct _EXTD_ACPI_VARIABLE_SET {
	//
	//Miscellanious ACPI Related variables 
	//
	EFI_PHYSICAL_ADDRESS	ExtdAcpiFacsTable;
	EFI_PHYSICAL_ADDRESS	ExtdAcpiFacpTable;
} EXTD_ACPI_VARIABLE_SET;


extern EFI_GUID gEfiExtdAcpiVariableGuid;

#endif
