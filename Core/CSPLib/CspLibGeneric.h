//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Template/CSPLibrary/CspLibGeneric.h 6     11/12/11 6:39p Artems $
//
// $Revision: 6 $
//
// $Date: 11/12/11 6:39p $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Template/CSPLibrary/CspLibGeneric.h $
// 
// 6     11/12/11 6:39p Artems
// Added functions for TopSwap functionality
// 
// 5     7/14/11 3:19p Artems
// EIP 64106: Updated source to be UEFI 2.3.1 and PI 1.2 compliant
// 
// 4     2/22/11 3:31p Artems
// EIP 51548 - Added AMI copyright headers, replaced TABs with spaces
// 
// 3     3/25/10 3:08p Artems
// EIP 33953: Added eLink infrastructure to support runtime shadow ram
// writing
// 
// 2     6/11/09 5:43p Robert
// Comment updates for CHM and coding standard
// 
// 1     10/13/07 11:29p Michaela
// Initial Checkin
// 
//
//*****************************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        CspLibGeneric.h
//
// Description: This file contains generic code to add functionality that can 
//              be used by any module.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __CSP_LIB_GENERIC__H__
#define __CSP_LIB_GENERIC__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <efi.h>
#include <pei.h>
#include <Protocol\PciRootBridgeIo.h>

#ifndef GUID_ZERO
#define GUID_ZERO \
{   0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }
GUID_VARIABLE_DECLARATION(GuidZero, GUID_ZERO);
#endif


//<AMI_MHDR_START>
//----------------------------------------------------------------------------
// Name: AMI_TRACE
//
// Description:
//      This general-purpose, phase-independent macro allows debugging 
//      messages in code that is shared between PEI and DXE phases.
//
// Input:
//      Identical to TRACE (Type must be AMI_TRACE_ALWAYS)
//
// Notes:
//      For PEI phase, this macro assumes the identifier PeiServices is
//      defined.
//
//      The usage of this macro is identical to TRACE with the exception that
//      the type must always be AMI_TRACE_ALWAYS:
//
//        AMI_TRACE((AMI_TRACE_ALWAYS, "Hello World\n"));
//
//----------------------------------------------------------------------------
//<AMI_MHDR_END>

#if ( defined(TRACE) )
  #define AMI_TRACE(args) TRACE(args)
  #define AMI_TRACE_ALWAYS TRACE_ALWAYS
#elif ( defined(PEI_TRACE) )
  //------------------------------------------------------------------------
  // Generate a compiler message to help identify the build error if 
  // PeiServices is not defined in the calling function.
  //------------------------------------------------------------------------
  #pragma message("AMI_TRACE requires identifier definition: EFI_PEI_SERVICES **PeiServices")
  #define AMI_TRACE(args) PEI_TRACE(args)
  #define AMI_TRACE_ALWAYS TRACE_ALWAYS,PeiServices
#else
  #define AMI_TRACE(args)
  #define AMI_TRACE_ALWAYS
#endif


//<AMI_MHDR_START>
//----------------------------------------------------------------------------
// Name:    ABORT_ERROR
//
// Description: 
//      This phase-independent macro can be used to force premature
//      return from a function on error, displaying a message if possible and 
//      returning the EFI_STATUS value of the error.  (For compatibility, 
//      ABORT_CALL is also defined as a synonym for this macro.)
//
// Input:
//      arg - type must be EFI_STATUS
//
// Notes:
//      Use the macro with a function call to save screen/source file 
//      real estate:
//
//        ABORT_ERROR(FunctionCall(...));
//
//        The macro is replaced with the following:
//
//        {
//          EFI_STATUS Status = FunctionCall(...);
//          if (EFI_ERROR(Status)){
//              ...message with file name, line number and function name...
//              return Status;
//          }
//        }
//
//----------------------------------------------------------------------------
//<AMI_MHDR_END>

#define ABORT_ERROR(arg) { \
  EFI_STATUS Status = arg; \
  if ( EFI_ERROR( Status ) ) \
  { \
    AMI_TRACE((AMI_TRACE_ALWAYS, \
      "\n\nABORT Error in %s \nLine %i: %s\n\n\n",__FILE__, __LINE__, #arg)); \
    return Status; \
  } }
#ifndef ABORT_CALL
#define ABORT_CALL(arg) ABORT_ERROR(arg)
#endif


//<AMI_MHDR_START>
//----------------------------------------------------------------------------
// Name:    ABORT_ERROR_STATUS
//
// Description:
//      This phase-independent macro can be used to force premature
//      return from a function on error, displaying a message if possible and
//      returning the caller-specified value in the event of an error.    
//      (For compatibility, ABORT_CALL_STATUS is also defined as a 
//      synonym for this macro.)
//
// Input: 
//      status - value to return (no type constraint)
//      arg    - type must be EFI_STATUS
//
// Notes:
//      Use the macro with a function call to save screen/source file 
//      real estate (note: the return value is discarded):
//
//        ABORT_ERROR_STATUS(MyErrorValue, FunctionCall(...));
//
//        The macro is replaced with the following:
//
//        {
//          if (EFI_ERROR( FunctionCall(...) ) ){
//            ...message with file name, line number and function name...
//            return MyErrorValue;
//          }
//        }
//
//----------------------------------------------------------------------------
//<AMI_MHDR_END>

#define ABORT_ERROR_STATUS(retval, arg) { \
  if ( EFI_ERROR(arg) ) \
  { \
    AMI_TRACE((AMI_TRACE_ALWAYS, \
      "\n\nABORT Error in %s \nLine %i: %s\n\n\n",__FILE__, __LINE__, #arg)); \
    return (retval); \
  } }
#ifndef ABORT_CALL_STATUS
#define ABORT_CALL_STATUS(retval, arg) ABORT_ERROR_STATUS(retval, arg)
#endif


//<AMI_MHDR_START>
//----------------------------------------------------------------------------
// Name:    STOP_ERROR
//
// Description: 
//      This phase-independent macro can be used to force an infinite loop 
//      on error, ensuring execution does not continue past the error and
//      easing the burden of locating the source of the error.  A message is
//      displayed if possible.  (For compatibility, ASSERT_CALL is 
//      also defined as a synonym for this macro.)
//
// Input: 
//      arg - type must be EFI_STATUS
//
// Notes:
//      Use the macro with a function call to save screen/source file 
//      real estate (note: the return value is discarded):
//
//        STOP_ERROR(FunctionCall(...));
//
//        The macro is replaced with the following:
//
//        {
//          if (EFI_ERROR(FunctionCall(...))){
//            ...message with file name, line number and function name...
//            EFI_DEADLOOP();
//          }
//        }
//
//----------------------------------------------------------------------------
//<AMI_MHDR_END>

#define STOP_ERROR(arg) { \
  if ( EFI_ERROR( arg ) ) { \
    AMI_TRACE((AMI_TRACE_ALWAYS, \
      "\n\nSTOP Error in %s \nLine %i: %s\n",__FILE__, __LINE__,#arg)); \
    EFI_DEADLOOP(); \
  } }
#ifndef ASSERT_CALL
#define ASSERT_CALL(arg) STOP_ERROR(arg)
#endif


//----------------------------------------------------------------------------
// LocateMultiplePpi types/declarations

//<AMI_THDR_START>
//------------------------------------------------------------------
//
// Name:        PPI_LOCATE_STRUCT
//
// Fields:      Type    ParameterName    Description
//------------------------------------------------------------------
//  EFI_GUID  Guid - GUID_ZERO or value of Guid
//  EFI_GUID *GuidPtr - NULL or pointer to Guid
//  UINTN Instance - Instance Number to discover
//  EFI_PEI_PPI_DESCRIPTOR **Descriptor - Pointer to a Pointer to reference the found descriptor. If not NULL, returns a pointer to the descriptor (includes flags, etc)
//  VOID **Ptr - Pointer to be updated with an instance of a pointer to a pointer of the PPI being located
//
// Description: 
//  This data structure contains the information that is used to 
//  make a call to LocatePpi and return the needed pointers
//
// Notes:   
//      
//------------------------------------------------------------------
//<AMI_THDR_END>
typedef struct {                            
    EFI_GUID                    Guid;       // GUID_ZERO or value of Guid
    EFI_GUID                    *GuidPtr;   // NULL or pointer to Guid
    UINTN                       Instance;
    EFI_PEI_PPI_DESCRIPTOR      **Descriptor;
    VOID                        **Ptr;
} PPI_LOCATE_STRUCT;

EFI_STATUS  LocateMultiplePpi (
    EFI_PEI_SERVICES    **PeiServices,
    UINT32              PpiTableSize,
    PPI_LOCATE_STRUCT   *Ppi
);


//----------------------------------------------------------------------------
// LocateMultipleProtocol types/declarations

//<AMI_THDR_START>
//------------------------------------------------------------------
//
// Name:        PROTOCOL_LOCATE_STRUCT
//
// Fields:      Type    ParameterName    Description
//------------------------------------------------------------------
//  EFI_GUID  Guid - GUID_ZERO or value of Guid
//  EFI_GUID *GuidPtr - NULL or pointer to Guid
//  VOID *Registration - Optional Registration Key returned from RegisterProtocolNotify() 
//  VOID **Interface - Pointer to be updated with an instance of a pointer to a pointer of the Protocol being located
//
// Description: 
//  This data structure contains the information that is used to 
//  make a call to LocateProtocol and return the needed pointers
//
// Notes:   
//      
//------------------------------------------------------------------
//<AMI_THDR_END>
typedef struct {                            
    EFI_GUID                    Guid;       // GUID_ZERO or value of Guid
    EFI_GUID                    *GuidPtr;   // NULL or pointer to Guid
    VOID                        *Registration;
    VOID                        **Interface;
} PROTOCOL_LOCATE_STRUCT;

EFI_STATUS  LocateMultipleProtocol (
    EFI_BOOT_SERVICES           *pBS,
    UINT32                      ProtocolTableSize,
    PROTOCOL_LOCATE_STRUCT      *Protocol
);


//----------------------------------------------------------------------------
// PEI PCI Access related types/declarations

//<AMI_THDR_START>
//------------------------------------------------------------------
//
// Name:        PEI_PCI_ARGS
//
// Fields:      Type    ParameterName    Description
//------------------------------------------------------------------
//  EFI_PEI_SERVICES **PeiServices - instance of the PEI Services Table
//  EFI_PEI_PCI_CFG_PPI *Cfg - OPTIONAL Pointer to an Instance of the PciCfg PPI
//  EFI_PEI_PCI_CFG_PPI_WIDTH Width - Width of the data to be accessed in the PCI space
//  UINT32 Address - (B/D/F/R) PCI address of the device to read from
//  VOID *Value - Buffer to store Data to Write or Data that is read
//
// Description: 
//  This data structure contains the information that is used to 
//  read or write to PCI Devices using the PEI PciCfg PPI
//
// Notes:   
//      
//------------------------------------------------------------------
//<AMI_THDR_END>
typedef struct {
    EFI_PEI_SERVICES            **PeiServices;
    EFI_PEI_PCI_CFG2_PPI         *Cfg;
    EFI_PEI_PCI_CFG_PPI_WIDTH   Width;
    UINT32                      Address;        // PEI phase uses 32-bit addresses
    VOID                        *Value;
} PEI_PCI_ARGS;

EFI_STATUS 
PeiWritePci (  
    PEI_PCI_ARGS     *Pci
);

EFI_STATUS  
PeiReadPci(  
    PEI_PCI_ARGS     *Pci
);


//----------------------------------------------------------------------------
// DXE PCI Access related related types/declarations

//<AMI_THDR_START>
//------------------------------------------------------------------
//
// Name:        RTBRG_PCI_ARGS
//
// Fields:      Type    ParameterName    Description
//------------------------------------------------------------------
//  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RtBrdg - Pointer to an instance of the DXE PCI Root Bridge Protocol
//  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH Width - Width of the data to read from or write to the PCI Device
//  UINT64 Address - PCI Address of the Device to read from or write to
//  UINTN Count - Number of times to repeat the Read or write command
//  VOID *Buffer - Buffer to store Data to Write or Data that is read
//
// Description: 
//  This data structure contains the information that is used to 
//  read or write to PCI Devices using the DXE PCI Root Bridge Protocol
//
// Notes:   
//      
//------------------------------------------------------------------
//<AMI_THDR_END>
typedef struct {
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL          *RtBrdg;
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width;
    IN UINT64                                   Address;
    IN UINTN                                    Count;
    IN OUT VOID                                 *Buffer;
} RTBRG_PCI_ARGS;

EFI_STATUS RbReadPci (
    RTBRG_PCI_ARGS  *Arg
);

EFI_STATUS RbWritePci (
    RTBRG_PCI_ARGS  *Arg
);

VOID OemRuntimeShadowRamWrite(
    IN BOOLEAN Enable
);


#define SB_BACKED_UP_CONTROL_REGISTER 0x3414

BOOLEAN IsTopSwapOn(
    VOID
);

VOID SetTopSwap(
    IN BOOLEAN On
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************