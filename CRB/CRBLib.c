//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBLib.c 3     5/30/13 11:19p Thomaschen $
//
// $Revision: 3 $
//
// $Date: 5/30/13 11:19p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBLib.c $
// 
// 3     5/30/13 11:19p Thomaschen
// [TAG]         EIP124808
// [Category]    Bug Fix
// [Severity]    Normal
// [Symptom]     WHCK test fail(Class Driver Audio Logo Test (System)).
// [RootCause]   NB Verb table error.
// [Solution]    Modify NB Verb table port B.
// [Files]       CRBLib.c; CRB.sdl;
// 
// 2     5/14/12 8:17a Wesleychen
// Support CRB recovery jumper.
// CRB.SDL; CRBLib.c
// 
// 1     2/12/12 10:38p Victortu
// Intel SharkBay CRB initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        CRBLib.c
//
// Description: This file contains Chipset Reference Board related code that
//              is needed for both PEI & DXE stage. 
//              To avoid code duplication this file is made as a library and
//              linked both in PEI & DXE CRB FFS.
//
// Notes:       MAKE SURE NO PEI OR DXE SPECIFIC CODE IS NEEDED
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Efi.h>
#include <Token.h>
#include <Setup.h>
#include <AmiPeiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

// Function Prototype(s)
VOID CrbSetupCallbacks (
    IN VOID              *Services,
    IN OUT NB_SETUP_DATA *NbSetupData,
    IN SETUP_DATA        *SetupData,
    IN BOOLEAN           Pei 
);

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

UINT32 CrbHdaVerbTbl8[] = {
//
// Rear Audio Verb Table 0x10EC0888
//
// (NID 01h)
//===== HDA Codec Subsystem ID Verb-table =====
//HDA Codec Subsystem ID  : 0x105B0CE3
  0x001720E3,
  0x0017210C, 
  0x0017225B, 
  0x00172310,
//===== Pin Widget Verb-table =====
  //Pin Complex 1     (NID 0x14 )
  0x01471C10,
  0x01471D44,
  0x01471E01,
  0x01471F01,

  //Pin Complex 2     (NID 0x15 )
  0x01571C12,
  0x01571D14,
  0x01571E01,
  0x01571F01,

  //Pin Complex 3     (NID 0x16 )
  0x01671C11,
  0x01671D64,
  0x01671E01,
  0x01671F01,

  //Pin Complex 4     (NID 0x17 )
  0x01771C14,
  0x01771D24,
  0x01771E01,
  0x01771F01,

  //Pin Complex 5     (NID 0x18 )
  0x01871C40,
  0x01871D9C,
  0x01871EA1,
  0x01871F01,

  //Pin Complex 6     (NID 0x19 )
  0x01971C50,
  0x01971D9C,
  0x01971EA1,
  0x01971F02,

  //Pin Complex 7     (NID 0x1A )
  0x01A71C4F,
  0x01A71D34,
  0x01A71E81,
  0x01A71F01,

  //Pin Complex 8     (NID 0x1B )
  0x01B71C20,
  0x01B71D4C,
  0x01B71E21,
  0x01B71F02,

  //Pin Complex 9     (NID 0x1C )
  0x01C71CF0,
  0x01C71D01,
  0x01C71E33,
  0x01C71F59,

  //Pin Complex 10    (NID 0x1D )
  0x01D71C01,
  0x01D71DE6,
  0x01D71E05,
  0x01D71F40,

  //Pin Complex 11    (NID 0x1E )
  0x01E71C30,
  0x01E71D61,
  0x01E71E4B,
  0x01E71F01,

  //Pin Complex 12    (NID 0x1F )
  0x01F71C60,
  0x01F71D71,
  0x01F71ECB,
  0x01F71F01
};

UINT32 CrbHdaVerbTbl9[] = {
//
// Rear Audio Verb Table 0x10EC0885
//
// (NID 01h)
//;===== HDA Codec Subsystem ID Verb-table =====
//;HDA Codec Subsystem ID  : 0x80860021
  0x00172021,
  0x00172100,
  0x00172286,
  0x00172380,
  //===== Pin Widget Verb-table =====
  // Pin Complex 1       (NID 14h)
  0x01471C10,
  0x01471D44,
  0x01471E01,
  0x01471F01,
  // Pin Complex 2       (NID 15h)
  0x01571C20,
  0x01571D44,
  0x01571E21,
  0x01571F02,
  // Pin Complex 3       (NID 16h)
  0x01671C11,
  0x01671D60,
  0x01671E01,
  0x01671F01,
  // Pin Complex 4       (NID 17h)
  0x01771CF0,
  0x01771D11,
  0x01771E11,
  0x01771F41,
  // Pin Complex 5       (NID 18h)
  0x01871C50,
  0x01871D98,
  0x01871EA1,
  0x01871F02,
  // Pin Complex 6       (NID 19h)
  0x01971C12,
  0x01971D10,
  0x01971E01,
  0x01971F01,
  // Pin Complex 7       (NID 1Ah)
  0x01A71C40,
  0x01A71D34,
  0x01A71E81,
  0x01A71F01,
  // Pin Complex 8       (NID 1Bh)
  0x01B71C4F,
  0x01B71D98,
  0x01B71EA1,
  0x01B71F01,
  // Pin Complex 9       (NID 1Ch)
  0x01C71CF0,
  0x01C71D11,
  0x01C71E11,
  0x01C71E41,
  // Pin Complex 10       (NID 1Dh)
  0x01D71CF0,
  0x01D71D01,
  0x01D71E83,
  0x01D71F59,
  // Pin Complex 11       (NID 1Eh)
  0x01E71C30,
  0x01E71D11,
  0x01E71E45,
  0x01E71F01,
  // Pin Complex 12       (NID 1Fh)
  0x01F71CF0,
  0x01F71D11,
  0x01F71E11,
  0x01F71F41
};

UINT32 CrbHdaVerbTbl10[] = {
//
// Rear Audio Verb Table 0x10EC0889
//
// (NID 01h)
//===== HDA Codec Subsystem ID Verb-table =====
//HDA Codec Subsystem ID  : 0x80860022
  0x00172022,
  0x00172100, 
  0x00172286, 
  0x00172380,
//===== Pin Widget Verb-table =====
  //Pin Complex 1     (NID 0x14 )
  0x01471C10,
  0x01471D44,
  0x01471E01,
  0x01471F01,

  //Pin Complex 2     (NID 0x15 )
  0x01571C20,
  0x01571D40,
  0x01571E21,
  0x01571F02,

  //Pin Complex 3     (NID 0x16 )
  0x01671C11,
  0x01671D64,
  0x01671E01,
  0x01671F01,

  //Pin Complex 4     (NID 0x17 )
  0x01771CF0,
  0x01771D11,
  0x01771E11,
  0x01771F41,

  //Pin Complex 5     (NID 0x18 )
  0x01871C50,
  0x01871D98,
  0x01871EA1,
  0x01871F02,

  //Pin Complex 6     (NID 0x19 )
  0x01971C12,
  0x01971D14,
  0x01971E01,
  0x01971F01,

  //Pin Complex 7     (NID 0x1A )
  0x01A71C40,
  0x01A71D34,
  0x01A71E81,
  0x01A71F01,

  //Pin Complex 8     (NID 0x1B )
  0x01B71C4F,
  0x01B71D9C,
  0x01B71EA1,
  0x01B71F01,

  //Pin Complex 9     (NID 0x1C )
  0x01C71CF0,
  0x01C71D11,
  0x01C71E11,
  0x01C71F41,

  //Pin Complex 10    (NID 0x1D )
  0x01D71CF0,
  0x01D71D01,
  0x01D71E83,
  0x01D71F59,

  //Pin Complex 11    (NID 0x1E )
  0x01E71C30,
  0x01E71D11,
  0x01E71E45,
  0x01E71F01,

  //Pin Complex 12    (NID 0x1F )
  0x01F71CF0,
  0x01F71D11,
  0x01F71E11,
  0x01F71F41
};


// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

// All routines in this file will be added into CSP library.

UINT32            CrbNbSaHdaVerbTableData[] = {
  ///
  /// Audio Verb Table - 0x80862807
  ///
  /// Pin Widget 5 - PORT B
  ///
  0x00571C10,
  0x00571D00,
  0x00571E56,
  0x00571F58,
  ///
  /// Pin Widget 6 - PORT C
  ///
  0x00671C20,
  0x00671D00,
  0x00671E56,
  0x00671F18,
  ///
  /// Pin Widget 7 - PORT D
  ///
  0x00771C30,
  0x00771D00,
  0x00771E56,
  0x00771F18
};

NB_SA_HDA_VERB_TABLE CrbNbSaHdaVerbTable[] = {
  { 
      {
      0x80862807, ///< Vendor ID/Device ID
      0x0000,     ///< SubSystem ID
      0xFF,       ///< Revision ID
      0x02,       ///< Front panel support (1=yes, 2=no)
      0x0003,     ///< Number of Rear Jacks
      0x0000      ///< Number of Front Jacks
      },
    0             ///< Pointer to verb table data, need to be inited in the code.
  }
};
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Procedure:   CrbSetupCallbacks
//
// Description: This function returns NB Chipset setup data from system SetupData
//              variable 
//
// Input:       *Services    - Pointer to PeiServices or RuntimeServices
//                             structure  
//              *NbSetupData - Pointer to custom setup data to return
//              *SetupData   - Pointer to system setup data.
//              Pei          - Pei flag. If TRUE we are in PEI phase
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CrbSetupCallbacks (
    IN VOID              *Services,
    IN OUT NB_SETUP_DATA *NbSetupData,
    IN SETUP_DATA        *SetupData,
    IN BOOLEAN           Pei )
{
    if (SetupData != NULL && !Pei) {
        // Porting Start
        NbSetupData->NbSaHdaVerbTable      = CrbNbSaHdaVerbTable;
        NbSetupData->NbSaHdaVerbTable->VerbTableData = CrbNbSaHdaVerbTableData;
        NbSetupData->NbSaHdaVerbTableNum   = sizeof (CrbNbSaHdaVerbTable) / sizeof (NB_SA_HDA_VERB_TABLE);
        // Porting End
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsRecoveryJumper
//
// Description: This function determines the system to boot in recovery mode
//              if recovery jumper is in position.
//
// Input:       IN EFI_PEI_SERVICES             **PeiServices,
//
// Output:      TRUE - The system is booting in recovery mode
//              FALSE - Normal Boot
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsRecoveryJumper
(
  IN EFI_PEI_SERVICES **PeiServices
)
{
  BOOLEAN           JumperFlag;
  UINT32            GpioVal;

  // Read the status of the GPIO22 recovery jumper from the GPIO registers
  GpioVal = IoRead32 (GPIO_BASE_ADDRESS + GP_IOREG_GP_LVL);

  JumperFlag = ((BOOLEAN) (!(GpioVal & BIT22)));

  return JumperFlag;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
