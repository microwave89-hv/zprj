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
// $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Source/CmosAccess.c 25    6/15/10 2:24p Michaela $
// 
// $Revision: 25 $
//
// $Date: 6/15/10 2:24p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Source/CmosAccess.c $
// 
// 25    6/15/10 2:24p Michaela
// 
// 24    3/10/10 4:39p Michaela
// 
// 23    3/08/10 5:39p Michaela
// 
// 22    3/08/10 1:31p Michaela
// 
// 21    3/08/10 1:09p Michaela
// 
// 20    3/05/10 4:55p Michaela
// 
// 19    12/04/09 7:32p Michaela
// 
// 18    12/03/09 6:42p Michaela
// 1. Updated CmosReadWrite() to use physical access to 
//    non-checksummed locations within the Managed Region
//    only if CMOS_RECOVER_ONLY_CHECKSUMMED is TRUE.
//    (controlled via CMOS_MGR_RECOVER_ONLY_CHECKUMMED
//    SDL token)
//    
// 2. Added CanClearLegacyStatusBits() to determine
//    whether or not the legacy status bits can be
//    clear to a non-failure status.
//    
// 3. SynchronizeLegacyStatusRegisters() is updated to
//    only clear the bad checksum failure status in
//    the legacy status registers in the DXE phase
//    or on the first boot after flashing the firmware.
// 
// 17    11/10/09 9:14p Michaela
// 
// 16    7/29/09 9:59a Michaela
// updates Aptio Enhancement EIP 22205
// (no code changes)
// 
// 15    7/23/09 1:30p Michaela
// Rename ReadRtcIndex and WriteRtcIndex
// 
// 14    6/15/09 5:11p Michaela
// 
// 13    6/02/09 3:27p Michaela
// For label: 4.6.3_CMOSMGR_11
// 
// 12    2/23/09 6:03p Michaela
// --code clean-up in CmosBankReadWrite()
// --added test code to support test module it it is present
// 
// 11    11/25/08 3:20p Michaela
// Updates for Label 4.6.3_CMOSMGR_08
// - Assembly macro fixes
// - Added assembly macros
// - Moved loading defaults into DXE phase
// - Updated help file example
// 
// 10    11/17/08 4:40p Michaela
// --Removed Token Name strings in debug development code
// 
// 9     11/17/08 3:39p Michaela
// --Removed debug development code
// --CMOS Buffer feature is depreciated
// --ReadCmosStatusBytes and UpdateBatteryStatus now directly 
//   calls CmosPhysicalReadWrite to avoid error when the 
//   Optimal Defaults table is being used for reads & writes
// 
// 8     11/14/08 9:12a Michaela
// **CMOS register variables changed from UINT8 to UINT16
// **added global CMOS_PORT_MAP array (gCmosBank) for
//   supporting board-specific access functions.  The array is defined
//   using the CMOS_PORT_MAPPING Elink.  The array starts at
//   index 1.
// **Added CmosBankReadWrite() for calling the board-specific
//   access functions.
// **Modified CmosPhysicalReadWrite() to call CmosBankReadWrite()
//   for physical CMOS access
// 
// 7     11/07/08 5:13p Michaela
// Updated to make CMOS manager available in all phases 
// of the boot process:
// 
// A CMOS API Pointer is maintained in CMOS and accessible
// via provided macros in C and assembly source.
// 
// 6     3/25/08 3:04p Michaela
// --deleted UpdateLegacyChecksumStatus
// --Modified SynchronizeLegacyStatusRegisters to 
//   update both battery and checksum status bits
// 
// 5     3/07/08 4:07p Michaela
// Label 4.6.3_CMOSMGR_05 fixes:
// -- write errors to Optimal Defaults buffer before memory detection
// -- CMOS Token table corruption when name strings are disabled
// 
// 4     2/29/08 9:35p Michaela
// - Added recovery path policy
// - fixed other minor bugs
// 
// 3     2/26/08 12:49p Michaela
// Added/modified Helpbuilder headers
// 
// 2     2/22/08 3:20p Olegi
// Renamed some of the equates to avoid the naming collisions.
// 
// 1     2/22/08 2:29p Michaela
// 
// 1     2/04/08 6:00p MichaelA
// Created
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:    CmosAccess.c
//
// Description: Contains the routines that constitute the CMOS access
//              implementation.  This file contains source code that is used
//              for both PEI and DXE phases.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Efi.h>
#ifdef PEI_COMPILE
    #include <Pei.h>
    #include <AmiPeiLib.h>
#else
    #include <AmiDxeLib.h>
#endif
#include <CmosAccess.h>
#include <SspTokens.h>
#include "CmosManager.h"
#include "CmosManagerHob.h"
#include "CmosBoard.h"

//---------------------------------------------------------------------------
// CmosBank is initialized using the CMOS_PORT_MAPPING SDL Elink.
// This array is used to determine which index/data port pair to use or
// which board-specific access function to call for a specific CMOS register 
// address. The first element is not used and contains all zeros.
//---------------------------------------------------------------------------

CMOS_PORT_MAP gCmosBank[] = { {0,0,0,0,0}, CMOS_PORT_MAPPING  };
UINT16 gCmosBankCount = \
    sizeof(gCmosBank) / sizeof(CMOS_PORT_MAP);

EFI_CMOS_BATTERY_TEST gCmosBatteryIsGood = CMOS_BATTERY_TEST_MAPPING;

//---------------------------------------------------------------------------
// Function(s) originally defined in CmosManager.c
//---------------------------------------------------------------------------
extern EFI_CMOS_MANAGER_INTERFACE *GetCmosMangerInterface(
    IN EFI_CMOS_ACCESS_INTERFACE   *Cmos );


//---------------------------------------------------------------------------
// Function(s) originally defined in CmosBuffer.c or CmosPhysical.c
// depending on the sdl token BUFFERED_CMOS_SUPPORT
//---------------------------------------------------------------------------
    

//---------------------------------------------------------------------------
// Function declarations for this file
//---------------------------------------------------------------------------
EFI_STATUS CalculateUpdatedCheckSum(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    IN  UINT16                      CmosAddress,
    IN  UINT8                       OldCmosValue,
    IN  UINT8                       NewCmosValue,
    OUT UINT16                      *NewChecksum );

EFI_STATUS CalculateChecksum(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    OUT UINT16                      *ChecksumValue );

EFI_STATUS WriteChecksum(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    OUT UINT16                      ChecksumValue );


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: EncodeParameter 
//
// Description:
//      Value is shifted left by the bit field size specified in Token.
//
// Input:
//      OUT UINT8 *Value
//                  -- Address of value to be encoded 
//      IN CMOS_TOKEN *Token
//                  -- Token describing the bit field size
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID EncodeParameter(
    OUT UINT8       *Value,
    IN  CMOS_TOKEN  *Token )
{
    *Value <<= Token->Value.Field.BitOffset;
    
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: DecodeParameter
//
// Description:
//      Value is shifted right and masked by the bit field's size and offset
//      as specified in Token.
//
// Input:
//      OUT UINT8 *Value
//                  -- Address of value to be decoded
//      IN CMOS_TOKEN *Token
//                  -- Token describing the bit field's size and offset
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID DecodeParameter(
    OUT UINT8        *Value,
    IN CMOS_TOKEN   *Token )
{
    *Value >>= Token->Value.Field.BitOffset;
    *Value &=  (0xff >> (8 - Token->Value.Field.Size));
    
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: BitFieldOverflow
//
// Description:
//      For testing whether or not a Value overflows the field size
//      as specified in Token. 
//
// Input:
//      IN UINT8 *Value
//                  -- Value to be tested 
//      IN CMOS_TOKEN *Token
//                  -- Token describing the bit field's size
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN BitFieldOverflow(
    IN UINT8        *Value, 
    IN CMOS_TOKEN   *Token )
{
    if ( *Value & ~(0xff >> (8 - Token->Value.Field.Size)) )
        return TRUE;
    else
        return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SetClobberBits
//
// Description:
//      Creates a mask with bits set corresponding to the size and offset
//      of the bit field as specified by Token.
//
// Input:
//      OUT UINT8 *Mask
//                  -- Mask to be created
//      IN CMOS_TOKEN *Token
//                  -- Token describing the bit field's size and offset
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SetClobberBits(
    OUT UINT8        *Mask, 
    IN CMOS_TOKEN   *Token )
{
    *Mask = 0xff >> (8 - Token->Value.Field.Size);
    *Mask <<= Token->Value.Field.BitOffset;
}



//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosFindToken
//
// Description:
//      Returns index of CMOS token in token table or 0 if not found.
//
// Input:
//      IN  EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- This is the CMOS Manager interface pointer.
//      IN  UINT16 CmosToken 
//                  -- Encoded CMOS token for which to locate an index into
//                     the CMOS token table
//
// Output:
//      UINT16 (Return Value)
//                  = Index of the CmosToken in the token table, or
//                  = 0, if the CmosToken was not found
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16 CmosFindToken(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    IN  UINT16                      CmosToken )
{
    UINT16   i = 0;   // First valid token table index is 1
    
    while (++i < Manager->TokenCount) {
        if (Manager->TokenTable[i].Value.AllBits == CmosToken) {
            break;
        }
    }
    
    if (i < Manager->TokenCount)
        return i;

    return 0;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosGetTokenFromRegister
//
// Description:
//      Returns encoded token for the specified register.
//
// Input:
//      IN  EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- This is the CMOS Manager interface pointer.
//      IN  UINT8 CmosRegister 
//                  -- CMOS register to for which to search
//
// Output:
//      UINT16 (Return Value)
//                  = Token found in the token table, or
//                  = 0, if the Register was not found
//
// Notes:
//
//      Caller must ensure the register has been reserved properly
//      in SSP.
//
//      This should be considered a risky function call and extra care
//      should be taken to ensure the proper CmosRegister is specified.
//
//      This function has the potential for problems, as it is possible that 
//      a specified CmosRegister has not been defined in SSP and/or may
//      be used by another CmosToken.
//
//      All verification of parameters must be done by the caller.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16 CmosGetTokenFromRegister(
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  UINT16                      CmosRegister )
{
    UINT16                      i = 0;
    EFI_CMOS_MANAGER_INTERFACE  *Manager = GetCmosMangerInterface(Cmos);
    
    // Manager->TokenCount is the total number of entries in 
    // Manager->TokenTable where the first entry is zero.
    
    while (++i < Manager->TokenCount) {
        if (Manager->TokenTable[i].Value.Field.CmosAddress == CmosRegister){
            break;
        }
    }
    
    // Minimal error checking is to ensure it is an 8-bit CMOS Token
    if (i < Manager->TokenCount ){
        if (Manager->TokenTable[i].Value.Field.Size == 8)
            return Manager->TokenTable[i].Value.AllBits;
    }

    // a valid token is greater than 0x1000
    return 0;  
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosBankReadWrite
//
// Description:
//      This function determines which structure in the global CMOS_PORT_MAP
//      array corresponds to the provided CmosAddress and either calls the
//      associated function or uses the associated IO ports to read/write the 
//      CMOS register value to/from the CmosParameterValue.
//      
// Input:
//      IN      EFI_CMOS_MANAGER_INTERFACE *Manager
//                  --  Pointer to the CMOS Manager internal interface
//      IN      CMOS_ACCESS_TYPE AccessType
//                  --  WriteType or ReadType
//      IN      UINT16 CmosAddress
//                  --  CMOS register to for which the access is to be made
//      IN/OUT  UINT8 *CmosParameterValue
//                  --  This is the value to write for write access or the 
//                      value that was read for read access.
//              
//
// Output:
//      EFI_STATUS (Return Value)
//                  EFI_SUCCESS or valid EFI error code
//
// Notes:
//      N/A
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosBankReadWrite(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    IN  CMOS_ACCESS_TYPE            AccessType,
    IN  UINT16                      CmosAddress,
    IN OUT UINT8                    *CmosParameterValue )
{
    UINT8       i = 1;
    EFI_STATUS  Status = EFI_NOT_FOUND;
    DEFINE_PEI_SERVICES(Manager->Access.PeiServices); // defines NULL if DXE

    // scan the CMOS_PORT_MAP array to determine how to access this address
    for (; i < gCmosBankCount; i++)
    {
      if (     (CmosAddress >= gCmosBank[i].Low) 
            && (CmosAddress <= gCmosBank[i].High) )
      {
      
        // First, attempt to call the board-specific function if available
        if (gCmosBank[i].BoardReadWrite != NULL){
            Status = gCmosBank[i].BoardReadWrite( PeiServices,
                                              AccessType,
                                              CmosAddress,
                                              CmosParameterValue );
            break;
        }
        
        // Otherwise, attempt to use the provided index/data ports 
        // if available (assuming 8 bit port access)
        else if ( (gCmosBank[i].Index > 0) && (gCmosBank[i].Data > 0) ){
            IoWrite8( gCmosBank[i].Index, (UINT8)CmosAddress );
            if (AccessType == ReadType){
                *CmosParameterValue = IoRead8( gCmosBank[i].Data );
            }
            else {
                IoWrite8( gCmosBank[i].Data, *CmosParameterValue );
            }
            Status = EFI_SUCCESS;
            break;
        }
        
      }
    }
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosPhysicalReadWrite
//
// Description:
//      This function provides support for performing the actual
//      read or write from/to a physical CMOS location.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Manager interface pointer
//      IN CMOS_ACCESS_TYPE AccessType
//                  -- Specifies whether to perform a read or a write
//      IN UINT8 CmosAddress
//                  -- Actual CMOS address/offset
//      IN UINT8 BitsToWrite
//                  -- Mask specifying the bits to be written (these
//                      bits will be cleared first)
//      IN OUT  UINT8 *CmosParameterValue
//                  -- CMOS value to be written or, on successful exit, will
//                      contain the value that was read
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = or other valid EFI error code
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosPhysicalReadWrite(
    IN      EFI_CMOS_MANAGER_INTERFACE  *Manager,
    IN      CMOS_ACCESS_TYPE            AccessType,
    IN      UINT16                      CmosAddress,
    IN      UINT8                       BitsToWrite,  
    IN OUT  UINT8                       *CmosParameterValue )
{
    UINT8       CmosRegisterValue;
    UINT8       NewValue;
    UINT16      NewChecksum = 0;
    EFI_STATUS  Status = EFI_SUCCESS;
    DEFINE_PEI_SERVICES(Manager->Access.PeiServices);

    // Always read the value
    CmosBankReadWrite( Manager,
                       ReadType,
                       CmosAddress,
                       &CmosRegisterValue );
    
    // If read access, simply return the unmodified data
    if ( AccessType == ReadType ) {
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
            "    Physical Read: Register 0x%02X = 0x%02X\n",
            CmosAddress, CmosRegisterValue));
        *CmosParameterValue = CmosRegisterValue;
    }
    
    // If writing, then don't clobber unused bits
    else {
        NewValue = (CmosRegisterValue & ~BitsToWrite) | *CmosParameterValue;

        // get the new checksum before writing
        if (!Manager->CheckStatus(Manager, CMOS_FORCE_NO_CHECKSUM))
            Status = CalculateUpdatedCheckSum( Manager, CmosAddress,
                CmosRegisterValue, NewValue, &NewChecksum);

        // write the value
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
            "    Physical Write: Register 0x%02X = 0x%02X\n",
            CmosAddress, NewValue));
        CmosBankReadWrite( Manager,
                           WriteType,
                           CmosAddress,
                           &NewValue );
        
        // write the checksum, if necessary 
        // (this write will cause an infinite loop without a flag)
        if (!Manager->CheckStatus(Manager, CMOS_FORCE_NO_CHECKSUM)){
            if (Manager->CheckStatus(Manager, CMOS_ADDRESS_IS_CHECKSUMMED)){
                Manager->SetStatus(Manager, CMOS_FORCE_NO_CHECKSUM);
                WriteChecksum( Manager, NewChecksum );
                Manager->ClearStatus(Manager, CMOS_FORCE_NO_CHECKSUM);
            }
        }
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: NotChecksummed
//
// Description:
//      This function returns TRUE if the CmosAddress is NOT included in the
//      checksum and returns FALSE otherwise.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE  *Manager
//                  -- Manager interface pointer
//      IN UINT8 CmosAddress
//                  -- Actual CMOS address/offset
//
// Output:
//      BOOLEAN (Return Value)
//                  = TRUE if CmosAddress is NOT included in the checksum
//                  = FALSE if CmosAddress IS included in the checksum
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN NotChecksummed(
    IN      EFI_CMOS_MANAGER_INTERFACE  *Mgr,
    IN      UINT16                      CmosAddress )
{
    UINT16  NoChecksumIndex = 1;    // NoChecksumTable starts at 1

    while ( (NoChecksumIndex < Mgr->NoChecksumCount)
         && (CmosAddress > Mgr->NoChecksumTable[NoChecksumIndex].Index) )
    {
        ++NoChecksumIndex;
    }

    if ( CmosAddress == Mgr->NoChecksumTable[NoChecksumIndex].Index )
        return TRUE;
    else
        return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosBufferReadWrite
//
// Description:
//      This function provides support for performing the actual
//      read or write from/to a CMOS buffer location (using the 
//      Optimal Defaults Table Buffer).
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE  *Manager
//                  -- Manager interface pointer
//      IN CMOS_ACCESS_TYPE AccessType
//                  -- Specifies whether to perform a read or a write
//      IN UINT8 CmosAddress
//                  -- Actual CMOS address/offset
//      IN UINT8 BitsToWrite
//                  -- Mask specifying the bits to be written (these
//                     bits will be cleared first)
//      IN OUT UINT8 *CmosParameterValue
//                  -- CMOS value to be written or, on successful exit, will
//                     contain the value that was read
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = or other valid EFI error code
//
// Notes:
//
//      Control comes here because of one of two reasons:
//
//      1) The checksum is bad
//
//                  All writes/read are to/from the 
//                  Manager->OptimalDefaultTable only for locations not found 
//                  in the Manager->NoChecksumTable until DXE phase.
//
//      2) The battery is bad
//
//                  All writes/read are to/from the 
//                  Manager->OptimalDefaultTable for all locations.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosBufferReadWrite(
    IN      EFI_CMOS_MANAGER_INTERFACE  *Manager,
    IN      CMOS_ACCESS_TYPE            AccessType,
    IN      UINT16                      CmosAddress,
    IN      UINT8                       BitsToWrite,  
    IN OUT  UINT8                       *CmosParameterValue )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       NewValue;
    UINT16      NewChecksum = 0;
    UINT8       CmosRegisterValue;
    // First CMOS register @ buffer index 1
    UINT16      BufferIndex = CmosAddress - FIRST_CMOS_REGISTER + 1; 
    DEFINE_PEI_SERVICES(Manager->Access.PeiServices);

    if (CmosAddress < FIRST_CMOS_REGISTER || CmosAddress > LAST_CMOS_REGISTER){
        CMOS_TRACE((CMOS_TRACE_ALWAYS, 
            "    CmosBufferReadWrite: Invalid CmosAddress (0x%X)\n", 
            CmosAddress ));
        return EFI_INVALID_PARAMETER;
    }

    // get the default value from the table
    CmosRegisterValue = Manager->OptimalDefaultTable[BufferIndex].Value;
                            
    // If read access, simply return the unmodified data
    if ( AccessType == ReadType ) {
        *CmosParameterValue = CmosRegisterValue;
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
            "    Buffer Read: 0x%X = OptimalDefaultTable[%d].Value \n",
            CmosRegisterValue, BufferIndex  ));
    }
    
    // If writing, mark the location as dirty and don't clobber unused bits 
    else {
        NewValue = (CmosRegisterValue & ~BitsToWrite) | *CmosParameterValue;

        // get the new checksum before writing (this sets or clears
        // the CMOS_ADDRESS_IS_CHECKSUMMED Manager->ManagerStatus flag)
        if (!Manager->CheckStatus(Manager, CMOS_FORCE_NO_CHECKSUM)) {
            Status = CalculateUpdatedCheckSum( Manager, CmosAddress,
                CmosRegisterValue, NewValue, &NewChecksum);
        }

        // Optimal default table writes take precedence
        Manager->OptimalDefaultTable[BufferIndex].Value = NewValue;
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
            "    Buffer Write: OptimalDefaultTable[%d].Value = 0x%X\n",
            BufferIndex, NewValue ));

        // write the checksum, if necessary
        // (this write will cause an infinite loop without a flag)
        if (!Manager->CheckStatus(Manager, CMOS_FORCE_NO_CHECKSUM)){
            if (Manager->CheckStatus(Manager, CMOS_ADDRESS_IS_CHECKSUMMED)){
                Manager->SetStatus(Manager, CMOS_FORCE_NO_CHECKSUM);
                WriteChecksum( Manager, NewChecksum );
                Manager->ClearStatus(Manager, CMOS_FORCE_NO_CHECKSUM);
                CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                    "    NewChecksum = 0x%X\n",
                    NewChecksum ));
            }
        }
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosReadWrite
//
// Description:
//      Decides which version of xxxReadWrite to call based upon the
//      current Access Routing Logic.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Manager interface pointer
//      IN CMOS_ACCESS_TYPE AccessType
//                  -- Specifies whether to perform a read or a write
//      IN UINT8 CmosAddress
//                  -- Actual CMOS address/offset
//      IN UINT8 BitsToWrite
//                  -- Mask specifying the bits to be written (these
//                      bits will be cleared first)
//      IN OUT  UINT8 *CmosParameter
//                  -- CMOS value to be written or, on successful exit, will
//                      contain the value that was read
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosReadWrite(
    IN      EFI_CMOS_MANAGER_INTERFACE  *Mgr,
    IN      CMOS_ACCESS_TYPE            AccessType,
    IN      UINT16                      CmosAddress,
    IN      UINT8                       BitsToWrite,  
    IN OUT  UINT8                       *CmosParameter )
{
    BOOLEAN UseBufferAccess = FALSE;
    
    // If the checksum is bad or the battery is bad, accesses will be
    // routed to the optimal default table by default.

    if ( Mgr->CheckStatus( Mgr, CMOS_OPTIMAL_DEFAULTS_ENABLED )){
        UseBufferAccess = TRUE;
        
        // Force physical access if these conditions are applicable:
        //
        //      1. the CMOS is usable,
        //      2. recovery is limited to only checksummed locations
        //      3. the current location is not checksummed

        if (    Mgr->CheckStatus( Mgr, CMOS_IS_USABLE ) 
            &&  Mgr->CheckStatus( Mgr, CMOS_RECOVER_ONLY_CHECKSUMMED )
            &&  NotChecksummed( Mgr, CmosAddress ) )
        {
           UseBufferAccess = FALSE;
        }
    }

    if (UseBufferAccess)        
        return CmosBufferReadWrite( Mgr,
                                    AccessType, 
                                    CmosAddress,  
                                    BitsToWrite,
                                    CmosParameter);
    else
        return CmosPhysicalReadWrite(   Mgr,
                                        AccessType, 
                                        CmosAddress,  
                                        BitsToWrite,
                                        CmosParameter);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosReadWriteEncodedToken
//
// Description:
//      This is the main worker function which verifies and either  
//      reads/writes a value from/to the CMOS location as specified by the  
//      encoded token.
//
// Input:
//      IN      EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- This is the CMOS Manager interface pointer.
//      IN      CMOS_ACCESS_TYPE AccessType
//                  -- Specifies whether to perform a read or a write
//      IN      UINT16 TokenTableIndex
//                  -- Index into the token table
//      IN OUT  UINT8 *CmosParameter
//                  -- CMOS value to be written or, on successful exit, will
//                      contain the value that was read
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = EFI_INVALID_PARAMETER, if the CmosParameter does
//                      not comply with the expected size
//                  = or other valid EFI error code
//
// Notes:
//                  1) Gets the CMOS token from the global table
//                  2) If writing, the value is error-checked for size and 
//                      up-shifted to the correct bit position. Also, the
//                      BitsToWrite mask is used to specify
//                      which bits to clear in the destination before
//                      writing.
//                  3) This token is decoded to get the CMOS index, 
//                  4) The read/write is performed
//                  5) If reading, the value is down-shifted and masked to 
//                      return the expected value.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosReadWriteEncodedToken(
    IN      EFI_CMOS_MANAGER_INTERFACE  *Manager,
    IN      CMOS_ACCESS_TYPE            AccessType,
    IN      UINT16                      TokenTableIndex,
    IN OUT  UINT8                       *CmosParameter )
{
    CMOS_TOKEN  *CmosToken = &Manager->TokenTable[TokenTableIndex];
    UINT8       BitsToWrite = 0;
    DEFINE_PEI_SERVICES(Manager->Access.PeiServices);
    
    // If writing, encode the CmosParameter

    if (AccessType == WriteType) {
    
        // Check to make sure the data is the correct size for the bit field

        if ( BitFieldOverflow(CmosParameter, CmosToken) ){
            return EFI_INVALID_PARAMETER;
        }

        // Shift up to the correct offset within the byte

        EncodeParameter(CmosParameter, CmosToken);
        
        // Set the bits in BitsToWrite mask that are 
        // consumed by this token

        SetClobberBits(&BitsToWrite, CmosToken);
    }
    
    // Read (or write) the CmosParameter to actual (or CMOS buffer) location

    CmosReadWrite(Manager,
                AccessType, 
                (UINT16)CmosToken->Value.Field.CmosAddress,  // byte address
                BitsToWrite,
                CmosParameter);
    
    // If reading, shift down to bit-position zero and mask off upper bits

    if (AccessType == ReadType) 
        DecodeParameter(CmosParameter, CmosToken);
    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosRead
//
// Description:
//      Reads to CmosValue from the CMOS location specified by CmosToken.
//
// Input:
//      IN  EFI_CMOS_ACCESS_INTERFACE *Cmos
//                  -- This is the access interface pointer.
//      IN  UINT16 CmosToken 
//                  -- This is the encoded CMOS location.
//      OUT UINT8 *CmosValue
//                  -- On success, this will contain the value at
//                      the specified CMOS location.
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = EFI_NOT_FOUND, if the token is not in the token table
//                  = or other valid EFI error code
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosRead(
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  UINT16                      CmosToken,
    OUT UINT8                       *CmosValue )
{
    EFI_STATUS                      Status = EFI_NOT_FOUND;
    UINT16                          TokenTableIndex = 0;
    EFI_CMOS_MANAGER_INTERFACE      *Mgr = GetCmosMangerInterface(Cmos);
    DEFINE_PEI_SERVICES(Cmos->PeiServices);

    // if CmosToken <= 0xe, then always read the register.  These registers
    // will be readable regardless of the state of the battery.

    if (CmosToken <= 0xe){
        Status = CmosBankReadWrite( Mgr, ReadType, CmosToken, CmosValue );
    }

    // Otherwise, if CmosToken < MIN_TOKEN_VALUE and the battery is good, 
    // then directly  read the register. (For a bad battery, return 
    // EFI_DEVICE_ERROR.)

    else if (CmosToken < MIN_TOKEN_VALUE) {
        if ( !Mgr->CheckStatus( Mgr, CMOS_IS_USABLE ) ) {
            Status = EFI_DEVICE_ERROR;
        }
        else {
            Status = CmosBankReadWrite( Mgr, ReadType, CmosToken, CmosValue );
        }
    }

    // Otherwise, after validating the CmosToken, decode it to read the  
    // associated register bit(s).

    else {
        TokenTableIndex = CmosFindToken(Mgr, CmosToken);
        if (TokenTableIndex > 0) {
            Status = CmosReadWriteEncodedToken( Mgr, ReadType, 
                                                TokenTableIndex, CmosValue);
        }
        else
            Status = EFI_INVALID_PARAMETER;
    }
    
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: ReadCmosBytes
//
// Description:
//      Reads Bytes from the specified CMOS register(s).
//
// Input:
//      IN  EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Manger interface pointer.
//      IN UINT8 Count
//                  -- Count of CMOS_BYTEs to read
//      OUT CMOS_BYTE *Bytes
//                  -- An array of CMOS_BYTE structures
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ReadCmosBytes(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    IN  UINT16                      Count,
    OUT CMOS_BYTE                   *CmosBytes )
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    UINT16                          i = 0;
    DEFINE_PEI_SERVICES(Manager->Access.PeiServices);


    for (; i < Count; i++){
        Status = CmosReadWrite(Manager, ReadType, CmosBytes[i].Register, 0, 
                                         &CmosBytes[i].Value);
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: ReadCmosStatusBytes
//
// Description:
//      Initializes a CMOS_STATUS_BYTES structure and reads the associated
//      CMOS registers.
//
// Input:
//      IN  EFI_CMOS_ACCESS_INTERFACE *Cmos
//                  --  Manger interface pointer.
//      OUT CMOS_STATUS_BYTES *StatusBytes
//                  --  Address of a valid, uninitialized, CMOS_STATUS_BYTES 
//                      structure.
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ReadCmosStatusBytes(
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    OUT CMOS_STATUS_BYTES           *StatusBytes )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_CMOS_MANAGER_INTERFACE  *Mgr = GetCmosMangerInterface(Cmos);
    UINT8                       CmosValue;
    DEFINE_PEI_SERVICES(Mgr->Access.PeiServices);

    if (StatusBytes == NULL)
        return Status = EFI_INVALID_PARAMETER;
    
    StatusBytes->DiagnosticStatusRegister = CMOS_DIAGNOSTIC_STATUS_REGISTER;
    StatusBytes->BatteryStatusRegister = CMOS_RTC_STATUS_REGISTER;
    
    CmosPhysicalReadWrite(  Mgr, 
                            ReadType, 
                            StatusBytes->BatteryStatusRegister,
                            0, 
                            &StatusBytes->Battery.AllBits );
                                    
    CmosPhysicalReadWrite(  Mgr, 
                            ReadType, 
                            StatusBytes->DiagnosticStatusRegister,
                            0, 
                            &StatusBytes->Diagnostic.AllBits );
                            
    if ( Mgr->CheckStatus(Mgr, CMOS_OPTIMAL_DEFAULTS_ENABLED) )
        StatusBytes->ConfigurationStatus.IsVirtualized = TRUE;
    else
        StatusBytes->ConfigurationStatus.IsVirtualized = FALSE;

    // If the CMOS hardware is usable, update from cmos-based
    // status bits, which are more reliable.  Otherwise, use the 
    // the memory-based status.
    //
    // Note, some information could be lost on reset in DXE 
    // when using the memory-based status.
    //
    // Also, register 0xe is cleared in DXE, if the CMOS
    // is usable and the checksum has been recalculated.

    StatusBytes->ConfigurationStatus.BadBattery = FALSE;
    StatusBytes->ConfigurationStatus.DefaultsLoaded = FALSE;
    StatusBytes->ConfigurationStatus.IsFirstBoot = FALSE;
    StatusBytes->ConfigurationStatus.BadChecksum = FALSE;

    if ( Mgr->CheckStatus(Mgr, CMOS_IS_USABLE) ) {
        StatusBytes->ConfigurationStatus.NotUsable = FALSE;

        Cmos->Read( Cmos, CMOS_MGR_BATTERY_BAD, &CmosValue ); 
        StatusBytes->ConfigurationStatus.BadBattery |= CmosValue;

        Cmos->Read( Cmos, CMOS_MGR_DEFAULTS_LOADED, &CmosValue ); 
        StatusBytes->ConfigurationStatus.DefaultsLoaded |= CmosValue;

        Cmos->Read( Cmos, CMOS_MGR_FIRST_BOOT_DETECTED, &CmosValue ); 
        StatusBytes->ConfigurationStatus.IsFirstBoot |= CmosValue;

        Cmos->Read( Cmos, CMOS_MGR_CHECKSUM_BAD,&CmosValue ); 
        StatusBytes->ConfigurationStatus.BadChecksum |= CmosValue;
    }
    else {
        StatusBytes->ConfigurationStatus.NotUsable = TRUE;
        if ( Mgr->CheckStatus(Mgr, CMOS_BAD_BATTERY) )
            StatusBytes->ConfigurationStatus.BadBattery = TRUE;
        if ( Mgr->CheckStatus(Mgr, CMOS_DEFAULTS_LOADED) )
            StatusBytes->ConfigurationStatus.DefaultsLoaded = TRUE;
        if ( Mgr->CheckStatus(Mgr, CMOS_FIRST_BOOT_DETECTED) )
            StatusBytes->ConfigurationStatus.IsFirstBoot = TRUE;
        if ( Mgr->CheckStatus(Mgr, CMOS_BAD_CHECKSUM) )
            StatusBytes->ConfigurationStatus.BadChecksum = TRUE;
    }


    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: ReadChecksum
//
// Description:
//      Reads the checksum from the CMOS register(s).
//
// Input:
//      IN  EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Manger interface pointer.
//      OUT UINT16 *ChecksumValue
//                  -- The returned checksum value
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ReadChecksum(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    OUT UINT16                      *ChecksumValue )
{
    DEFINE_PEI_SERVICES(Manager->Access.PeiServices);

    Manager->Access.Read( &Manager->Access, CMOS_CHECKSUM_HIGH, 
        (UINT8*)ChecksumValue );
    *ChecksumValue <<= 8;
    Manager->Access.Read( &Manager->Access, CMOS_CHECKSUM_LOW, 
        (UINT8*)ChecksumValue );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: WriteChecksum
//
// Description:
//      Write the checksum to the CMOS register(s).
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Manger interface pointer.
//      IN UINT16 ChecksumValue
//                  -- Value to write to the checksum location.
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS WriteChecksum(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    IN  UINT16                      ChecksumValue )
{
    DEFINE_PEI_SERVICES(Manager->Access.PeiServices);

    // update the HOB if available

    if (Manager->ManagerHob != NULL)
        Manager->ManagerHob->Checksum = ChecksumValue;

        
    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "WriteChecksum: Value = 0x%X\n",
        ChecksumValue ));

    // update the CMOS checksum

    Manager->SetStatus(Manager, CMOS_FORCE_NO_CHECKSUM);
    Manager->Access.Write( &Manager->Access, CMOS_CHECKSUM_LOW, 
        (UINT8)ChecksumValue );
    ChecksumValue >>= 8;
    Manager->Access.Write( &Manager->Access, CMOS_CHECKSUM_HIGH, 
        (UINT8)ChecksumValue );
    Manager->ClearStatus(Manager, CMOS_FORCE_NO_CHECKSUM);

    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: UpdateBatteryStatus
//
// Description:
//      This function is used to update the CMOS battery status.  It is up
//      to the user of the Manager interface to determine whether or ot
//      the platform supports this feature.  (If the platform does not 
//      support this feature, the battery status is indeterminate.)
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Pointer to the Manager's interface
//
// Output:
//      EFI_STATUS (Return value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>


EFI_STATUS UpdateBatteryStatus (
    IN EFI_CMOS_MANAGER_INTERFACE   *Mgr )
{
    EFI_STATUS          Status = EFI_SUCCESS;
    BOOLEAN             IsGood;
    DEFINE_PEI_SERVICES(Mgr->Access.PeiServices);

    CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, "\n\nUpdateBatteryStatus Entry\n"));
    
    // Update the battery status bit in the Manager's CMOS_MANAGER_STATUS
    // field and update the legacy CMOS status register if legacy register
    // updates are enabled.

#ifdef PEI_COMPILE
    IsGood = gCmosBatteryIsGood( PeiServices );
#else
    IsGood = gCmosBatteryIsGood( NULL );
#endif

    if ( IsGood ) {
        Mgr->ClearStatus(Mgr, CMOS_BAD_BATTERY); 
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, "    ...Battery is good.\n" ));
    }
    else {
        Mgr->SetStatus(Mgr, CMOS_BAD_BATTERY); 
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, "    ...Battery is BAD!!\n" ));
    }

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CanClearLegacyStatusBits
//
// Description:
//      Determines whether or not the legacy status bits in 
//      CMOS_DIAGNOSTIC_STATUS_REGISTER can be cleared to a non-failure
//      status.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Mgr
//                  -- Manger interface pointer
//
// Output:
//      BOOLEAN (Return Value)
//                  = TRUE - bits can be cleared
//                  = FALSE - bits can be cleared
//
// Notes:
//
//  EFI_CMOS_ACCESS_INTERFACE.PeiServices == NULL in DXE phase.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN CanClearLegacyStatusBits (
    IN      EFI_CMOS_MANAGER_INTERFACE  *Mgr )
{
    BOOLEAN  IsDxePhase = (Mgr->Access.PeiServices == NULL) ? TRUE : FALSE;
    BOOLEAN  IsFirstBoot = Mgr->CheckStatus(Mgr, CMOS_FIRST_BOOT_DETECTED);

    if ( IsDxePhase  ){
        return TRUE;
    } 
    else {
        return FALSE;
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SynchronizeLegacyStatusRegisters
//
// Description:
//      Synchronizes legacy CMOS status registers with status changes.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Manger interface pointer
//      IN CMOS_MANAGER_STATUS BitMap
//                  -- The status bits to be modified
//      IN CMOS_BIT_ACCESS_TYPE AccessType
//                  -- Specifies whether to set or clear the bits
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//      The BitMap contains all the bits to be modified in the legacy
//      status registers.
//
//      If CMOS_LEGACY_STATUS_ENABLED is off, or is being turned off, this 
//      function will not modify CMOS registers.
//
//      Failure status bits in CMOS_DIAGNOSTIC_STATUS_REGISTER can only be 
//      cleared if this is the first boot or if executing in the DXE phase.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SynchronizeLegacyStatusRegisters(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Mgr,
    IN CMOS_MANAGER_STATUS          BitMap,
    IN CMOS_BIT_ACCESS_TYPE         AccessType )
{
    DIAGNOSTIC_STATUS_BYTE  StatusByte;
    DEFINE_PEI_SERVICES(Mgr->Access.PeiServices);

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
        "\n\nSynchronizeLegacyStatusRegisters: Entry\n" ));

    // If the checksum status is being modified, 
    // then update the ChecksumIsBad bit
    
    if ( (BitMap & CMOS_BAD_CHECKSUM) != 0 )
    {
        // Read the legacy diagnostic status register

        CmosBankReadWrite(  Mgr, ReadType, CMOS_DIAGNOSTIC_STATUS_REGISTER, 
                            &StatusByte.AllBits );

        if (AccessType == SetType){
            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "  StatusByte.Field.ChecksumIsBad = 1\n" ));
            StatusByte.Field.ChecksumIsBad = 1;
        } 
        else if ( CanClearLegacyStatusBits(Mgr) ) {
            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "  StatusByte.Field.ChecksumIsBad = 0\n" ));
            StatusByte.Field.ChecksumIsBad = 0;
        }
        else {
            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "  StatusByte.Field.ChecksumIsBad = No Change\n" ));
        }

        // write back the changes

        CmosBankReadWrite(  Mgr, WriteType, CMOS_DIAGNOSTIC_STATUS_REGISTER, 
                            &StatusByte.AllBits );
    }   
    else {
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
            "  StatusByte.Field.ChecksumIsBad = No Change\n" ));
    }         
    
    

    // If the battery status is being modified, 
    // then update the RtcPowerIsBad bit
    
    if (  (BitMap & CMOS_BAD_BATTERY) != 0 )
    {
        // Read the legacy diagnostic status register

        CmosBankReadWrite(  Mgr, ReadType, CMOS_DIAGNOSTIC_STATUS_REGISTER, 
                            &StatusByte.AllBits );

        if (AccessType == SetType){
            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "  StatusByte.Field.RtcPowerIsBad = 1\n" ));
            StatusByte.Field.RtcPowerIsBad = 1;
        } 
        else if ( CanClearLegacyStatusBits(Mgr) ) {
            StatusByte.Field.RtcPowerIsBad = 0;
            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "  StatusByte.Field.RtcPowerIsBad = 0\n" ));
        }

        // Write the legacy diagnostic status register

        CmosBankReadWrite(  Mgr, WriteType, CMOS_DIAGNOSTIC_STATUS_REGISTER, 
                            &StatusByte.AllBits );
    }
    else {
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
            "  StatusByte.Field.RtcPowerIsBad = No Change\n" ));
    }

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
        "SynchronizeLegacyStatusRegisters: Exit\n\n" ));
                  
    return EFI_SUCCESS;
                  
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CalculateUpdatedCheckSum
//
// Description:
//      Computes a new "updated" CMOS checksum based on the change of value
//      at a single address.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE  *Manager
//                  -- The Manger interface pointer.
//      IN UINT16 CmosAddress
//                  -- CMOS location to be changed
//      IN UINT8 OldCmosValue
//                  -- Current value at the CMOS location
//      IN UINT8 NewCmosValue
//                  -- New value to be written to the CMOS location
//      OUT UINT16 *NewChecksum 
//                  -- Updated checksum
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or a valid EFI error code
//
// Notes:
//      After this call, Manager->CheckStatus(Manager, 
//      CMOS_ADDRESS_IS_CHECKSUMMED) returns TRUE if the address "is" 
//      included in the checksum.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CalculateUpdatedCheckSum(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Mgr,
    IN  UINT16                      CmosAddress,
    IN  UINT8                       OldCmosValue,
    IN  UINT8                       NewCmosValue,
    OUT UINT16                      *NewChecksum )
{
    UINT16  UnmanagedIndex = 1;  // UnmanagedTable starts at 1
    UINT16  NoChecksumIndex = 1; // NoChecksumTable starts at 1
    DEFINE_PEI_SERVICES(Mgr->Access.PeiServices);

    // Check if the address is included in the NoChecksumTable 
    // or the UnmanagedTable

    while ( NoChecksumIndex < Mgr->NoChecksumCount )
    {
        if ( CmosAddress <= Mgr->NoChecksumTable[NoChecksumIndex].Index )
            break;
        ++NoChecksumIndex;
    }

    while ( UnmanagedIndex < Mgr->UnmanagedTableCount )
    {
        if ( CmosAddress <= Mgr->UnmanagedTable[UnmanagedIndex].Index )
            break;
        ++UnmanagedIndex;
    }

    
    // Set ManagerStatus and compute NewChecksum if necessary 

    if (    CmosAddress == Mgr->NoChecksumTable[NoChecksumIndex].Index 
         || CmosAddress == Mgr->UnmanagedTable[UnmanagedIndex].Index     )
    {
#if (FULL_CMOS_MANAGER_DEBUG)
        if ( CmosAddress == Mgr->NoChecksumTable[NoChecksumIndex].Index ) {
            CMOS_TRACE((CMOS_TRACE_ALWAYS, "    ->Not Checksummed (0x%X)\n", CmosAddress ));
        }
        else {
            CMOS_TRACE((CMOS_TRACE_ALWAYS, "    ->Not Managed (0x%X)\n", CmosAddress ));
        }
#endif
        Mgr->ClearStatus(Mgr, CMOS_ADDRESS_IS_CHECKSUMMED);
    }
    else {
        ReadChecksum( Mgr, NewChecksum );
        *NewChecksum = *NewChecksum - OldCmosValue + NewCmosValue;
        Mgr->SetStatus(Mgr, CMOS_ADDRESS_IS_CHECKSUMMED);
    }
    
    return EFI_SUCCESS;
}



//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CalculateChecksum
//
// Description:
//      Calculate the checksum over the entire range of managed CMOS
//      (standard and/or extended CMOS).
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- The Manger interface pointer.
//      OUT UINT16 *ChecksumValue 
//                  -- The calculated checksum.
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Modified:
//      Manager->ManagerStatus
//                  CMOS_BAD_CHECKSUM - set/clear after comparing with
//                                      the current checksum in CMOS.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CalculateChecksum(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Mgr,
    OUT UINT16                      *ChecksumValue )
{
    //-----------------------------------------------------------------------
    // Algorithm Notes:
    //
    //  The NoChecksumTable is in numeric order and contains all CMOS
    //  registers starting at FIRST_CMOS_REGISTER and ending with
    //  LAST_CMOS_REGISTER unless the register has been explicitly specified
    //  with Checksum = YES in the NvramField declaration.
    //
    //  ...the NoChecksumTable need traversed only once.
    //-----------------------------------------------------------------------

    UINT16  CurRegister;
    UINT8   CurValue;
    UINT16  UnmanagedIndex = 1;  // UnmanagedTable starts at 1
    UINT16  NoChecksumIndex = 1; // NoChecksumTable starts at 1
    UINT16  CurrentChecksum;
    DEFINE_PEI_SERVICES(Mgr->Access.PeiServices);

    *ChecksumValue = 0; // ...just in case
    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "\n\nCalculateChecksum: Entry\n" ));
    
    // Calculate it
    for ( CurRegister = Mgr->FirstManagedRegister; 
          CurRegister <= Mgr->LastManagedRegister;   // inclusive
          ++CurRegister ) 
    {
        //---------------------------------------------
        // Skip the location if the location is not managed
        //
        // Note: the UnmanagedTable is in numeric order, 
        //       so it only needs traversed one time.
        //---------------------------------------------
        
        while ( (UnmanagedIndex < Mgr->UnmanagedTableCount)
                && (CurRegister 
                    > Mgr->UnmanagedTable[UnmanagedIndex].Index) )
        {
            ++UnmanagedIndex;
        }
        if ( CurRegister == Mgr->UnmanagedTable[UnmanagedIndex].Index ){
            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "    -->0x%X (un-managed)\n", CurRegister));
            continue;
        }


        while ( (NoChecksumIndex < Mgr->NoChecksumCount)
                && (CurRegister 
                        > Mgr->NoChecksumTable[NoChecksumIndex].Index) )
        {
            ++NoChecksumIndex;
        }
            

        if ( (CurRegister != 
                Mgr->NoChecksumTable[NoChecksumIndex].Index ) )
        {
            CmosReadWrite(Mgr, ReadType, CurRegister, 0, 
                &CurValue);
            *ChecksumValue += CurValue; // update the output parameter
        }
    }
    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
        "\n         --------------------------------\n"));
    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS,   
        "         Computed *ChecksumValue = 0x%04X\n\n",
        *ChecksumValue ));
    
    // Compare with physical CMOS checksum value and set/clear status bit 

    ReadChecksum( Mgr, &CurrentChecksum);

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
        "\n         -----------------------\n"));
    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS,   
        "         Saved Checksum = 0x%04X\n\n",
        CurrentChecksum ));
        
    if (*ChecksumValue != CurrentChecksum) {
        Mgr->SetStatus(Mgr, CMOS_BAD_CHECKSUM);
        CMOS_TRACE((CMOS_TRACE_ALWAYS, "    ...CMOS_BAD_CHECKSUM\n"));
    }
    else {
        Mgr->ClearStatus(Mgr, CMOS_BAD_CHECKSUM);
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "    ...Checksum is OK\n" ));
    }

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "CalculateChecksum: Done\n" ));
    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosWrite
//
// Description: 
//      Writes from CmosValue to CMOS location encoded into CmosToken.
//
// Input:
//      IN  EFI_CMOS_ACCESS_INTERFACE *Cmos
//                  -- This is the access interface pointer.
//      IN  UINT16 CmosToken 
//                  -- This is the encoded CMOS location.
//      IN  UINT8 CmosValue
//                  -- On success, this value will be written to
//                      the specified CMOS location.
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = EFI_NOT_FOUND, if the token is not in the token table
//                  = or other valid EFI error code
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosWrite(
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  UINT16                      CmosToken,
    IN  UINT8                       CmosValue )
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    UINT16                          TokenTableIndex = 0;
    EFI_CMOS_MANAGER_INTERFACE      *Mgr = GetCmosMangerInterface(Cmos);
    DEFINE_PEI_SERVICES(Cmos->PeiServices);


    // if CmosToken <= 0xe, then always write the register.  These registers
    // will be writable regardless of the state of the battery.

    if (CmosToken <= 0xe){
        Status = CmosBankReadWrite( Mgr, WriteType, CmosToken, &CmosValue );
    }

    // Otherwise, if CmosToken is less than MIN_TOKEN_VALUE and the battery 
    // is good, then an additional test is made to disallow writing of actual 
    // registers if they are within the managed region.  Otherwise, the 
    // actual physical register is written. (For a bad battery, return 
    // EFI_DEVICE_ERROR when trying to write the physical register.)
    
    else if ( CmosToken < MIN_TOKEN_VALUE ){
        if ( !Mgr->CheckStatus( Mgr, CMOS_IS_USABLE ) ) {
            Status = EFI_DEVICE_ERROR;
        }
        else if ( (CmosToken >= FIRST_MANAGED_CMOS_ADDRESS)
             && (CmosToken < MAX_MANAGED_CMOS_ADDRESS) )
            Status = EFI_INVALID_PARAMETER;
        else
            Status = CmosBankReadWrite( Mgr, WriteType,
                                        CmosToken, &CmosValue );
    }

    // Otherwise, after validating the CmosToken, decode it to write the  
    // associated register bit(s).

    else if ((TokenTableIndex = CmosFindToken( Mgr, CmosToken )) > 0) {
        Status = CmosReadWriteEncodedToken( Mgr, WriteType, TokenTableIndex,
                                            &CmosValue );
    }
    else
        Status = EFI_INVALID_PARAMETER;

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: LoadOptimalDefaults
//
// Description:
//      Initialize all physical CMOS registers with the default values 
//      specified in NvramField's Default value.
//
// Input:
//      IN  EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- The Manger interface pointer.
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Modified:
//      Manager->ManagerStatus bits:
//                         CMOS_BAD_CHECKSUM - cleared on success
//               CMOS_ERROR_LOADING_DEFAULTS - set on error
//
// Notes:
//      LoadOptimalDefaults will be called for one of two reasons:
//
//      1) On the first boot after flashing the ROM, the default
//         values will be written to all CMOS registers, regardless
//         of whether or not they are listed in the NoChecksumTable.
//
//      2) If a bad checksum is reported in PEI, the 
//         OptimalDefaultTable will be used as a read/write buffer
//         until DXE, where (by default) the CMOS_BAD_CHECKSUM status bit will
//         signal to write the buffer to physical CMOS.
//
//      * The optimal defaults buffer may be modified from the original
//        version if CMOS_OPTIMAL_DEFAULTS_ENABLED status bit is set. 
//
//      * If the CMOS_BAD_CHECKSUM status is set, then only those values
//        included in the checksum are written to physical CMOS.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS LoadOptimalDefaults(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Mgr )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT16      CurRegister;
    UINT8       CurValue;
    UINT16      NewChecksum = 0;
    UINT16      UnmanagedIndex = 1;     // UnmanagedTable starts at 1
    UINT16      DefaultIndex = 1;       // OptimalDefaultTable starts at 1
    UINT16      NoChecksumIndex = 1;    // NoChecksumTable starts at 1
    CMOS_MANAGER_STATUS  SavedStatus = Mgr->ManagerStatus & 
                                    (CMOS_OPTIMAL_DEFAULTS_ENABLED );
    EFI_CMOS_ACCESS_INTERFACE   *Cmos = Mgr->GetAccessInterface(Mgr);
    DEFINE_PEI_SERVICES(Mgr->Access.PeiServices);

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "LoadOptimalDefaults Entry\n"));

    // Calculate it
    //-----------------------------------------------------------------------
    // Configure to ensure reads/writes are to physical registers.
    //-----------------------------------------------------------------------

    Mgr->ClearStatus(Mgr, CMOS_OPTIMAL_DEFAULTS_ENABLED );
        
    // temporarily disallow checksum updating

    Mgr->SetStatus(Mgr, CMOS_FORCE_NO_CHECKSUM);


    //---------------------------------------------
    // For the first boot, ignore the bad checksum
    // so that defaults are loaded for all 
    // registers.
    //---------------------------------------------

    if ( Mgr->CheckStatus( Mgr, CMOS_FIRST_BOOT_DETECTED ) ){
        Mgr->ClearStatus(Mgr, CMOS_BAD_CHECKSUM);
    }

    //-----------------------------------------------------------------------
    // Write the physical registers:
    //
    // There "should" be exactly one default entry for each register in the  
    // managed region. (This is not assumed to be true.)
    //-----------------------------------------------------------------------

    for ( CurRegister = Mgr->FirstManagedRegister; 
          CurRegister <= Mgr->LastManagedRegister;   // inclusive
          ++CurRegister, ++DefaultIndex ) 
    {
        if ( DefaultIndex >= Mgr->OptimalDefaultCount){ // bad news!
            Mgr->SetStatus(Mgr, CMOS_ERROR_LOADING_DEFAULTS);
            break;  
        }

        //---------------------------------------------
        // Skip the location if the location is not managed
        //
        // Note: the UnmanagedTable is in numeric order, 
        //       so it only needs traversed one time.
        //---------------------------------------------
        
        while ( (UnmanagedIndex < Mgr->UnmanagedTableCount)
                && (CurRegister 
                    > Mgr->UnmanagedTable[UnmanagedIndex].Index) )
        {
            ++UnmanagedIndex;
        }
        if ( CurRegister == Mgr->UnmanagedTable[UnmanagedIndex].Index ){

            // Ensure DefaultIndex is not incremented at the top of the 
            // loop, as un-managed locations do not have a default value.

            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "    -->Skip 0x%X (un-managed)\n", 
                CurRegister));
            --DefaultIndex;
            continue;
        }


        //---------------------------------------------
        // Skip location if:
        //
        //    1. there is a bad checksum,
        //    2. recovery is enabled only for checksummed locations
        //
        // (Note, the NoChecksumTable is in numeric order)
        //---------------------------------------------
        
        if ( Mgr->CheckStatus( Mgr, 
                CMOS_BAD_CHECKSUM + CMOS_RECOVER_ONLY_CHECKSUMMED ) )
        {
            while ( (NoChecksumIndex < Mgr->NoChecksumCount)
                && (CurRegister 
                    > Mgr->NoChecksumTable[NoChecksumIndex].Index) )
            {
                ++NoChecksumIndex;
            } 
            if ( (CurRegister 
                    == Mgr->NoChecksumTable[NoChecksumIndex].Index ) ){
                CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                    "    -->Skip 0x%X (not checksummed)\n",
                    CurRegister));
                continue;
            }
        }
        
        // Update the physical register

        CurValue = Mgr->OptimalDefaultTable[DefaultIndex].Value;
        Status = CmosReadWrite(Mgr, WriteType, CurRegister, ALL_BITS, 
                                &CurValue);

        if (EFI_ERROR(Status)){
            CMOS_TRACE((CMOS_TRACE_ALWAYS, 
                "    Unable to load default for register: 0x%X\n",
                CurRegister ));
             break;
        } 
      

    }

    // if no error, calculate checksum and reset the 
    // CMOS_BAD_CHECKSUM status bit.

    if (   EFI_ERROR(Status) 
        || Mgr->CheckStatus(Mgr, CMOS_ERROR_LOADING_DEFAULTS))
    {
        CMOS_TRACE((CMOS_TRACE_ALWAYS, 
            "    Error: Could not load Optimal Defaults\n"));
        Status = EFI_UNSUPPORTED;
    }
    else
    {
        CalculateChecksum(Mgr, &NewChecksum);
        WriteChecksum(Mgr, NewChecksum); 
        Mgr->ClearStatus(Mgr, CMOS_BAD_CHECKSUM);
    }

    //-----------------------------------------------------------------------
    // Restore previous access routing settings. 
    //-----------------------------------------------------------------------

    Mgr->ManagerStatus = Mgr->ManagerStatus | SavedStatus;
    
    // Allow checksums to be computed now

    Mgr->ClearStatus(Mgr, CMOS_FORCE_NO_CHECKSUM);
    
    // Set status bit to indicate that defaults have been loaded

    Mgr->SetStatus(Mgr, CMOS_DEFAULTS_LOADED);

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "LoadOptimalDefaults Exit\n"));

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StopTime
//
// Description: Stops the time on RTC clock.
//
// Input:       
//      IN EFI_CMOS_MANAGER_INTERFACE *Mgr
//                  -- The Manger interface pointer.
//
// Output:      None
//
// Notes:       Here is the control flow of this function:
//              1. Stop the time by setting bit 7 on RTC register 0xb.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID StopTime(
    IN EFI_CMOS_MANAGER_INTERFACE  *Mgr ) 
{
    UINT8  Value;

    CmosBankReadWrite( Mgr, ReadType, 0xb, &Value );
    Value |= 0x80;
    CmosBankReadWrite( Mgr, WriteType, 0xb, &Value );
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StartTime
//
// Description: Start the time on RTC clock. This is used when changing the
//              Date and Time
//
// Input:       
//      IN EFI_CMOS_MANAGER_INTERFACE *Mgr
//                  -- The Manger interface pointer.
//
// Output:      None
//
// Notes:       Here is the control flow of this function:
//              1. Start the time by clearing bit 7 on RTC register 0xb.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID StartTime(
    IN EFI_CMOS_MANAGER_INTERFACE  *Mgr ) 
{
    UINT8  Value;

    CmosBankReadWrite( Mgr, ReadType, 0xb, &Value );
    Value &= 0x7f;
    CmosBankReadWrite( Mgr, WriteType, 0xb, &Value );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BCDToDec
//
// Description: Converts a Decimal value to a BCD value.
//
// Input:       
//      IN UINT8 Dec - Decimal value
//
// Output:      
//      UINT8 (return value) - BCD value
//
// Notes:       
//      Only for 2 digit decimal.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 DecToBCD(IN UINT8 Dec)
{
    UINT8 FirstDigit = Dec % 10;
    UINT8 SecondDigit = Dec / 10;

    return (SecondDigit << 4) + FirstDigit;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BCDToDec
//
// Description: Converts a BCD value to a Decimal value.
//
// Input:       
//      IN UINT8 BCD -- BCD value
//
// Output:      
//      UINT8 - decimal value
//
// Notes:       
//      Only for 2 digit BCD.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 BCDToDec(IN UINT8 BCD)
{
    UINT8 FirstDigit = BCD & 0xf;
    UINT8 SecondDigit = BCD >> 4;;

    return SecondDigit * 10  + FirstDigit;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CmosMgrReadRtcIndex
//
// Description: Read the RTC value at the given Index.
//
// Input:       
//      IN EFI_CMOS_MANAGER_INTERFACE *Mgr
//                  -- The Manger interface pointer.
//      IN UINT8 Index
//
// Output:      
//      UINT8 (return value) --
//                  = RTC Value read from the provided Index
//
// Notes:       
//      Here is the control flow of this function:
//               1. Read port 0x70 (RTC Index Register) to get bit 7.
//                  Bit 7 is the NMI bit-it should not be changed.
//               2. Output 0x70 with the Index and NMI bit setting.
//               3. Read 0x71 for Data. Getting Dec when appropriate.
//               4. Return the Data.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static UINT8 CmosMgrReadRtcIndex(
    IN EFI_CMOS_MANAGER_INTERFACE   *Mgr,
    IN UINT8                        Index )
{
    UINT8   Value;

    CmosBankReadWrite( Mgr, ReadType, Index, &Value );
    Value = BCDToDec(Value);
    
    return Value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CmosMgrWriteRtcIndex
//
// Description: Write the RTC value at the given Index.
//
// Input:       
//      IN EFI_CMOS_MANAGER_INTERFACE *Mgr
//                  -- The Manger interface pointer.
//      IN UINT8 Index
//                  -- Index to write
//      IN UINT8 Value
//                  -- Value to write
//
// Output:      None
//
// Notes:       Here is the control flow of this function:
//              1. Read port 0x70 (RTC Index Register) to get bit 7.
//                 Bit 7 is the NMI bit-it should not be changed.
//              2. Output 0x70 with the Index. Switch to BCD when needed.
//              3. Write the data to 0x71.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static void CmosMgrWriteRtcIndex(
    IN EFI_CMOS_MANAGER_INTERFACE   *Mgr,
    IN UINT8                        Index, 
    IN UINT8                        Value )
{
    Value = DecToBCD(Value);
    CmosBankReadWrite( Mgr, WriteType, Index, &Value );
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CmosSetDateTime
//
// Description: 
//      This routine simply writes the CMOS RTC registers from information
//      provided by the EFI_TIME structure, assuming the information is 
//      correct.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- The Manger interface pointer.
//      IN EFI_TIME *Time
//                  -- EFI Time structure
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Modified:
//      N/A
//
// Notes:       
//      Data is assumed to be valid.  Only a simple check for NULL pointer
//      is done.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosSetDateTime (
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  EFI_TIME                    *Time )
{
    EFI_CMOS_MANAGER_INTERFACE      *Mgr = GetCmosMangerInterface(Cmos);
    DEFINE_PEI_SERVICES(Cmos->PeiServices);

    if (Time == NULL || Mgr == NULL) 
        return EFI_INVALID_PARAMETER;

    StopTime(Mgr);
    
    CmosMgrWriteRtcIndex( Mgr, ACPI_CENTURY_CMOS, Time->Year / 100 );
    CmosMgrWriteRtcIndex( Mgr, 9, Time->Year % 100 );
    CmosMgrWriteRtcIndex( Mgr, 8, Time->Month );
    CmosMgrWriteRtcIndex( Mgr, 7, Time->Day );
    CmosMgrWriteRtcIndex( Mgr, 4, Time->Hour );
    CmosMgrWriteRtcIndex( Mgr, 2, Time->Minute );
    CmosMgrWriteRtcIndex( Mgr, 0, Time->Second );
    
    StartTime(Mgr);

    return  EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CmosGetDateTime
//
// Description: Return the current date and time
//
// Input:       
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- The Manger interface pointer.
//      OUT EFI_TIME *Time
//                  -- EFI Time structure
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosGetDateTime (
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    OUT EFI_TIME                    *Time )
{
    EFI_CMOS_MANAGER_INTERFACE      *Mgr = GetCmosMangerInterface(Cmos);
    DEFINE_PEI_SERVICES(Cmos->PeiServices);

    if (Time == NULL || Cmos == NULL) 
        return EFI_INVALID_PARAMETER;

    //If RTC Year only 1 digit, EFI spec says years range is 1998 - 2097
    Time->Year      = CmosMgrReadRtcIndex(Mgr, ACPI_CENTURY_CMOS) * 100 
                        + CmosMgrReadRtcIndex(Mgr, 9);
    Time->Month     = CmosMgrReadRtcIndex(Mgr, 8);
    Time->Day       = CmosMgrReadRtcIndex(Mgr, 7);
    Time->Hour      = CmosMgrReadRtcIndex(Mgr, 4);
    Time->Minute    = CmosMgrReadRtcIndex(Mgr, 2);
    Time->Second    = CmosMgrReadRtcIndex(Mgr, 0);
    Time->Nanosecond= 0;

    return  EFI_SUCCESS;
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
