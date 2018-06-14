//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Modules/SMBIOS/SmbiosDMIEdit/SmbiosDMIEditBoard.c 8     4/06/10 3:26p Davidd $
//
// $Revision: 8 $
//
// $Date: 4/06/10 3:26p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/SMBIOS/SmbiosDMIEdit/SmbiosDMIEditBoard.c $
// 
// 8     4/06/10 3:26p Davidd
// Added code to enable shadow ram write by calling the newly added
// generic OemRuntimeShadowRamWrite function from CSP Lib.
// 
// 7     6/02/09 4:51p Davidd
// Updated AMI headers (EIP 22180)
// 
// 6     10/27/08 1:04p Davidd
// 
// 5     9/26/08 11:02a Davidd
// Provided sample code to enable / disable E000 and F000 shadow for Intel
// chipset.
// 
// 4     11/19/07 11:47a Robert
// 
// 3     12/15/06 5:37p Davidd
// Code cleanup and reformatted to coding standard.
//
// 2     11/02/06 10:09a Fasihm
// Updated the code from Assembly to C, so as to compile and build in the
// x64 BIOS build environment.
//
// 1     5/24/06 11:59a Fasihm
// Initial check-in for the Santa Rosa Project. (Matanzas CRB) with
// Crestline + ICH8M + Merom Processor.
//
// 1     8/16/05 11:04a Mirk
//
// 1     8/10/05 11:31a Davidd
// Initial checkin. To be used with SMBIOS Core ALPHA_01.04.
//
// 1     8/10/05 11:18a Davidd
// New SmbiosDMIEditBoard component.
//
//*****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:    SmbiosDMIEditBoard.C
//
// Description: This file contains code for OEM related code for DMIEdit
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------------
// Includes

#include <Token.h>
#include <EFI.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>

extern
VOID OemRuntimeShadowRamWrite(
    IN BOOLEAN Enable
);

//    //
//    //  Sample code for Weybridge CRB. Needs to be changed for other platforms.
//    //
//UINT8   Reg90Byte;      // 0F000 PAM Reg
//#if ((defined(ITK_SUPPORT) && (ITK_SUPPORT != 0)) || SMBIOS_TABLE_LOCATION)
//UINT8   Reg95Byte;      // 0E000-0E400 PAM Reg
//UINT8   Reg96Byte;      // 0E8000-0EC00 PAM Reg
//#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                     ***** PORTING REQUIRED *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure: EnableShadowWrite
//
// Description: This function enables write to F000 shadow,
//              and E000 shadow if ITK_SUPPORT token
//              or SMBIOS_TABLE_LOCATION token is set.
//
// Input: None
//
// Output: None
//
// Note:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
EnableShadowWrite (VOID)
{
    OemRuntimeShadowRamWrite(TRUE);     // Call this generic function
                                        // if CSP Library in project is 
                                        // 4.6.4.0_CSPLibrary_013 or later

//    //
//    //
//    //  Sample code for Weybridge CRB. Needs to be changed for other platforms.
//    //

//    UINT8 bValue;

//    // 0F000 shadow
//    IoWrite32(0x0CF8, 0x80000090);
//    Reg90Byte = bValue = IoRead8(0x0CFC);
//    bValue |= 0x30;
//    IoWrite8(0x0CFC, bValue);

//#if ((defined(ITK_SUPPORT) && (ITK_SUPPORT != 0)) || SMBIOS_TABLE_LOCATION)
//    // 0E000-0E400 shadow
//    IoWrite32(0x0CF8, 0x80000095);
//    Reg95Byte = bValue = IoRead8(0x0CFD);
//    bValue |= 0x33;
//    IoWrite8(0x0CFD, bValue);

//    // 0E800-0EC00 shadow
//    IoWrite32(0x0CF8, 0x80000096);
//    Reg96Byte = bValue = IoRead8(0x0CFE);
//    bValue |= 0x33;
//    IoWrite8(0x0CFE, bValue);
//#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                     ***** PORTING REQUIRED *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure: DisableShadowWrite
//
// Description: This function makes F000 shadow read only,
//              and E000 shadow read only if ITK_SUPPORT token
//              or SMBIOS_TABLE_LOCATION token is set.
//
// Input: None
//
// Output: None
//
// Note:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
DisableShadowWrite (VOID)
{
    OemRuntimeShadowRamWrite(FALSE);    // Call this generic function
                                        // if CSP Library in project is
                                        // 4.6.4.0_CSPLibrary_013 or later

//    //
//    //  Sample code for Weybridge CRB. Needs to be changed for other platforms.
//    //

//    // 0F000 shadow
//    IoWrite32(0x0CF8, 0x80000090);
//    IoWrite8(0x0CFC, Reg90Byte);

//#if ((defined(ITK_SUPPORT) && (ITK_SUPPORT != 0)) || SMBIOS_TABLE_LOCATION)
//    // 0E000-0E400 shadow
//    IoWrite32(0x0CF8, 0x80000095);
//    IoWrite8(0x0CFD, Reg95Byte);

//    // 0E800-0EC00 shadow
//    IoWrite32(0x0CF8, 0x80000096);
//    IoWrite8(0x0CFE, Reg96Byte);
//#endif
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
