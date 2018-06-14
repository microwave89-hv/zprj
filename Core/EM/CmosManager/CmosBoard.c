//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/CmosManager/CmosBoard.c 1     10/25/12 9:02a Wesleychen $Revision: 0 $
//
// $Date: 10/25/12 9:02a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/CmosManager/CmosBoard.c $
// 
// 1     10/25/12 9:02a Wesleychen
// Update it to the rev19.
// 
// 19    6/08/12 4:48p Michaela
// [TAG]          EIP92072
// [Category]     Spec Update
// [Severity]     Normal
// [Description]  CMOS Manager Needs Code Changes for Coding Standards
// Compliance
// [Files]        Multiple
// 
// 18    5/23/12 12:02p Michaela
// [TAG]          EIP90679
// [Category]     Improvement
// [Description]  MonotonicCounter variable guid changed.
// [Files]        CmosBoard.c
// 
// 17    5/23/12 11:48a Michaela
// [TAG]          EIP90679
// [Category]     Improvement
// [Description]  MonotonicCounter variable guid changed.
// [Files]        CmosBoard.c
// 
// 16    6/15/10 2:22p Michaela
// 
// 15    3/08/10 1:08p Michaela
// 
// 14    3/08/10 12:56p Michaela
// Comment example gUnmanagedTable
// 
// 13    3/05/10 4:53p Michaela
// 
// 12    12/04/09 7:30p Michaela
// 
// 11    12/03/09 6:11p Michaela
// Added default implementation of CmosMgrIsColdBoot
// 
// 10    7/29/09 9:54a Michaela
// updates Aptio Enhancement EIP 22205
// (no code changes)
// 
// 9     6/15/09 5:10p Michaela
// 
// 8     6/02/09 3:25p Michaela
// For label: 4.6.3_CMOSMGR_11
// 
// 7     2/23/09 5:59p Michaela
// --ReadWriteSecondBankTranslated() is only included as a porting
//   example, and should be added to SBGeneric.c and prototyped in
//   SBCsplib.h (See notes)
// 
// 6     2/16/09 10:28p Michaela
// ReadWriteStandardRange()
//     - Modified to use CMOS_BANK0_INDEX
//       and CMOS_BANK0_DATA
//     - Validation of CmosRegister parameter
//     - OR CmosRegister with CMOS_NMI_BIT_VALUE
//       to specify NMI bit.
// ReadWriteSecondBankTranslated()
//     - Added to translate CmosRegister to
//       index port value for bank 2 access
//     - Use CMOS_BANK1_INDEX and CMOS_BANK1_DATA
//       to access bank 2
// 
// 5     1/21/09 2:47p Michaela
// change CMOS_CLOCK_RANGE_INDEX to CMOS_STD_INDEX
// and CMOS_CLOCK_RANGE_DATA to CMOS_STD_DATA
// 
// 4     1/21/09 2:38p Michaela
// update for release 4.6.3_CMOSMGR_11:
// 
// **Removed CMOS_CLOCK_RANGE_INDEX and 
//   CMOS_CLOCK_RANGE_DATA SDL Tokens. 
// **Changed the default value of CMOS_STD_INDEX and 
//   CMOS_STD_DATA to 0x70 and 0x71, respectively. 
//   Updated CMOS_PORT_MAPPING elinks to use 
//   ReadWriteStandardRange() for the 0x0 to 0x7f region. 
// **Added CMOS_MGR_SET_NMI_BIT to specify whether or 
//   not to set the NMI bit for access to 0x0 to 0x7f 
//   region. 
// **Removed ReadWriteClockRange() in CmosBoard.c 
// **Modified ReadWriteStandardRange() in CmosBoard.c 
//   to access the NMI range CMOS, where the NMI bit is 
//   set, as specified by the CMOS_MGR_SET_NMI_BIT 
//   Boolean token. 
// Modified ReadWriteStandardRange() in CmosBoard.c to access the NMI
// range CMOS, where the NMI bit is set, as specified by the
// CMOS_MGR_SET_NMI_BIT Boolean token. 
// 
// 3     1/08/09 10:51a Michaela
//   >Added function headers
//   >Updated function parameter modifiers
//   >renamed and updated to CmosBoard module part
//   >Core/Board SDL Tokens and CMOS Tokens are separated
// 
// 2     11/17/08 4:01p Michaela
// --Added default handlers for RTC range and Standard range CMOS
//   registers
// 
// 1     11/14/08 9:24a Michaela
// **Add support for board-specific access functions
// 
// 0     11/12/08 6:00p MichaelA
// Created
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:    CmosBoard.c
//
// Description: Contains routines that are board-specific.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "CmosBoard.h"

//---------------------------------------------------------------------------
// CmosBank is initialized using the CMOS_PORT_MAPPING SDL Elink.
// This array is used to determine which index/data port pair to use for a 
// specific CMOS register address.
//---------------------------------------------------------------------------
extern CMOS_PORT_MAP *gCmosBank;
extern UINT16 gCmosBankCount;


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
// 
// Name: ReadWriteStandardRange
//
// Description:
//  This function is used to access addresses in the Standard CMOS 
//  register range (0x0-0x7f), for PEI and DXE boot phases.
//
// Input:   
//  IN EFI_PEI_SERVICES **PeiServices 
//                  --  PEI Services table pointer (NULL in DXE phase)
//  IN CMOS_ACCESS_TYPE AccessType 
//                  --  ReadType or WriteType to specify the type of access
//  IN UINT16 CmosRegister 
//                  --  The CMOS register to access
//  IN OUT UINT8 *CmosParameterValue 
//                  -- Pointer to the data variable to be accessed
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = or other valid EFI error code
//
// Modified:    None
//
// Referrals:   IoRead8, IoWrite8
//
// Notes:       N/A
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS ReadWriteStandardRange (
    IN      EFI_PEI_SERVICES      **PeiServices,  // NULL in DXE phase
    IN      CMOS_ACCESS_TYPE      AccessType,
    IN      UINT16                CmosRegister,
    IN OUT  UINT8                 *CmosParameterValue )
{
    UINT8   TempValue;
    
    if (CmosRegister > 0x7f)
        return EFI_INVALID_PARAMETER;

    // If reading an RTC register, then check the Update in Progress bit in
    // Status register A to ensure a read is allowed.
    if(CmosRegister <= 9 && AccessType == ReadType) {
        do {
            IoWrite8(CMOS_BANK0_INDEX, 0xa | CMOS_NMI_BIT_VALUE);
            TempValue = IoRead8(CMOS_BANK0_DATA);
        } while (TempValue & 0x80);
    }

    IoWrite8( CMOS_BANK0_INDEX, (UINT8)CmosRegister | CMOS_NMI_BIT_VALUE );

    if (AccessType == ReadType){
        *CmosParameterValue = IoRead8( CMOS_BANK0_DATA );
    }
    else {
        IoWrite8( CMOS_BANK0_DATA, *CmosParameterValue );
    }

    return EFI_SUCCESS;
}

//----------------------------------------------------------------------------
// 
// Name: ReadWriteBank1Translated
//
// Description:
//  This function is used to access addresses in the CMOS register range 
//  (0x80-0xff), for PEI and DXE boot phases.
//
// Input:   
//  IN EFI_PEI_SERVICES **PeiServices
//                  --  Pointer to the PEI services table.  (This pointer
//                      is NULL in the DXE phase.)
//  IN CMOS_ACCESS_TYPE AccessType 
//                  --  ReadType or WriteType to specify the type of access
//  IN UINT16 CmosRegister 
//                  --  The CMOS register to access
//  IN OUT  UINT8 *CmosParameterValue 
//                  -- Pointer to the data variable to be accessed
//
// Output:
//  EFI_STATUS (return value) 
//                  EFI_SUCCESS - the access operation was successfull.
//                  Otherwise - a valid EFI error code is returned.
//
// Modified:    None
//
// Referrals:   IoRead8, IoWrite8
//
// Notes:       
//      This function is used when a translation from logical 
//      address to index port value is required.  For example, the 
//      ICH10 only allows values 0-7f for port 72/73 (upper bank) 
//      access, so logical CMOS address 0x80 must be translated to 
//      index port value 0, 0x81 becomes index port value 1, and 
//      so on.
//
//-------------------------------------------------------------------------- 


//============================================================================
// Southbridge porting notes
//============================================================================
// The following code is an example of how to implement code that
// translates from CMOS register number to access the physical
// CMOS location when the register number is not identical to the
// physical location.
//
// If access to the address range above 0x7f is required, and translation
// between CMOS register number and CMOS index port value must be made,
// then a function similar to this should be place in SBGeneric.c, SBCsplib.h,
// and the appropriate CMOS_PORT_MAPPING eLink should also be defined.
//============================================================================

/*
EFI_STATUS ReadWriteSecondBankTranslated (
    IN      EFI_PEI_SERVICES      **PeiServices,  // NULL in DXE phase
    IN      CMOS_ACCESS_TYPE      AccessType,
    IN      UINT16                CmosRegister,
    IN OUT  UINT8                 *CmosParameterValue )
{
    if (CmosRegister < 0x80 || CmosRegister > 0xff)
        return EFI_INVALID_PARAMETER;

    IoWrite8( CMOS_BANK1_INDEX, (UINT8)(CmosRegister-0x80));

    if (AccessType == ReadType){
        *CmosParameterValue = IoRead8( CMOS_BANK1_DATA );
    }
    else {
        IoWrite8( CMOS_BANK1_DATA, *CmosParameterValue );
    }

    return EFI_SUCCESS;
}
*/


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
// 
// Name: CmosMgrBatteryIsGood
//
// Description:
//  This function is used to determing whether or not the CMOS battery is
//  good.
//
// Input:   
//  IN EFI_PEI_SERVICES **PeiServices
//                  --  Pointer to the PEI services table.  (This pointer
//                      is NULL in the DXE phase.)
//
// Output:
//      BOOLEAN (Return Value)
//                  = TRUE if the battery is good
//                  = TRUE if the battery is bad
//
// Modified:    None
//
// Referrals:   IoRead8, IoWrite8
//
// Notes:       Some chipsets need to check a PCI configuration space
//              register to determine the RTC power status.
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

BOOLEAN CmosMgrBatteryIsGood (
    IN  EFI_PEI_SERVICES      **PeiServices  /* NULL in DXE */  )
{
    // PORTING PORTING PORTING

    IoWrite8( CMOS_BANK0_INDEX, 
        CMOS_RTC_STATUS_REGISTER + CMOS_NMI_BIT_VALUE );

    return ((IoRead8( CMOS_BANK0_DATA ) & 0x80) != 0) ? TRUE : FALSE;

    // PORTING PORTING PORTING
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosIsUsable
//
// Description:
//      This function determines whether or not the CMOS is usable. It may
//      be possible to use the CMOS even if the battery is bad.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Pointer to the Manager's interface
//
// Output:
//      BOOLEAN (Return value)
//                  = TRUE - CMOS is usable
//                  = FALSE - CMOS is not usable
//
// Notes:
//      Typically, register 0xd can be used to determine whether or not
//      CMOS is usable.  It may be possible to use the CMOS for reads/writes
//      if the battery is bad.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN CmosIsUsable (
    IN  EFI_PEI_SERVICES      **PeiServices  /* NULL in DXE */  )
{
    IoWrite8( CMOS_BANK0_INDEX, 
        CMOS_RTC_STATUS_REGISTER + CMOS_NMI_BIT_VALUE );

    return ((IoRead8( CMOS_BANK0_DATA ) & 0x80) != 0) ? TRUE : FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosMgrIsFirstBoot
//
// Description:
//      This function determines whether or not this is the first boot after
//      programming the boot device (flash part, ROM emulator, ...).
//
// Input:
//      IN  EFI_PEI_SERVICES **PeiServices
//                  --  Pointer to the PEI services table.  (This pointer
//                      is NULL in the DXE phase.)
//
// Output:
//      BOOLEAN (Return Value)
//                  = TRUE, if this is the first boot
//                  = FALSE, otherwise
//
// Notes:
//      For some chipsets, there may be additional issues to consider,
//      such as warm reboot during the PEI phase, multiple processor threads
//      and so on.  Therefore, this function can be implemented by an external
//      module (typically the Southbridge module).
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN CmosMgrIsFirstBoot (
    IN  EFI_PEI_SERVICES        **PeiServices )
{
    EFI_STATUS          Status = EFI_SUCCESS;

#ifdef PEI_COMPILE
    UINTN               Size = sizeof(UINT32);
#if ((CORE_COMBINED_VERSION > 262797) && defined(AMI_GLOBAL_VARIABLE_GUID))
    EFI_GUID            GlobalVariableGuid = AMI_GLOBAL_VARIABLE_GUID;
#else 
    EFI_GUID            GlobalVariableGuid = EFI_GLOBAL_VARIABLE;
#endif
    UINT32              Dummy;
    EFI_GUID            Guid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable = NULL;

    // If the MonotonicCounter variable is found then return false
    // to indicate that this is not the first boot.

    Status = (*PeiServices)->LocatePpi( PeiServices, &Guid,
                                        0, NULL, &ReadOnlyVariable);
    if (EFI_ERROR(Status))
        return TRUE;  // assume first boot if PPI not found

    Status = ReadOnlyVariable->GetVariable( PeiServices, 
                                            L"MonotonicCounter", 
                                            &GlobalVariableGuid, 
                                            NULL, 
                                            &Size, &Dummy );
#endif

    // If the CmosManagerStatus variable is not found and this is not the
    // DXE phase then this is the first boot.

    if ( EFI_ERROR(Status) )
        return TRUE;
    else       
        return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosMgrIsBsp
//
// Description:
//      This function returns TRUE if the currently executing CPU core
//      is the boot strap processor (BSP).
//
// Input:
//      IN  EFI_PEI_SERVICES  **PeiServices
//                  --  Pointer to the PEI services table.  (This pointer
//                      is NULL in the DXE phase.)
//
// Output:
//      BOOLEAN (Return Value)
//                  = TRUE, the BSP is executing
//                  = FALSE, otherwise
//
// Notes:
//      For some chipsets, this functions may need to be replaced.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN CmosMgrIsBsp(
    IN  EFI_PEI_SERVICES  **PeiServices )
{
    // if bit 8 of the APIC base register is set, then the current
    // core is the BSP (for most chipsets)

    if ( ReadMsr(MSR_XAPIC_BASE) & XAPIC_BASE_BSP_BIT_MASK )
        return TRUE;
    else
        return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosMgrIsColdBoot
//
// Description:
//      This function returns TRUE to specify the platform is always perfoming
//      a cold boot.
//
// Input:
//      IN  EFI_PEI_SERVICES  **PeiServices
//                  --  Pointer to the PEI services table.  (This pointer
//                      is NULL in the DXE phase.)
//
// Output:
//      BOOLEAN (Return Value)
//                  = TRUE
//
// Notes:
//      For some chipsets, this functions may need to be replaced.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN CmosMgrIsColdBoot(
    IN  EFI_PEI_SERVICES  **PeiServices )
{
    return TRUE;
}


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
