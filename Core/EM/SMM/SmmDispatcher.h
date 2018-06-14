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
// $Header: /Alaska/SOURCE/Modules/SMM/SMMDispatcher/SmmDispatcher.h 2     2/07/11 3:29p Markw $
//
// $Revision: 2 $
//
// $Date: 2/07/11 3:29p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SMMDispatcher/SmmDispatcher.h $
// 
// 2     2/07/11 3:29p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:		SmmDispatcher.h
//
// Description:	SmmDispatcher header file
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_DISPATCHER__H__
#define __SMM_DISPATCHER__H__

#include <SmmPi.h>
#include <AmiLib.h>

//
//  CONTAINING_RECORD - returns a pointer to the structure
//      from one of it's elements.
//
#ifndef _CR
#define _CR(Record, TYPE, Field)  ((TYPE *) ((CHAR8 *) (Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))
#endif

#ifndef CR
#define CR(record, TYPE, field, signature) _CR(record, TYPE, field)
#endif

//
// Define macros to build data structure signatures from characters.
//
#define SIGNATURE_16(A, B)        ((A) | (B << 8))
#define SIGNATURE_32(A, B, C, D)  (SIGNATURE_16 (A, B) | (SIGNATURE_16 (C, D) << 16))
#define SIGNATURE_64(A, B, C, D, E, F, G, H) \
   (SIGNATURE_32 (A, B, C, D) | ((UINT64) (SIGNATURE_32 (E, F, G, H)) << 32))
//---- Added from Core\Tiano.h


//
// SMM_HANDLER - used for each SMM handler
//

#define SMI_ENTRY_SIGNATURE  SIGNATURE_32('s','m','i','e')

 typedef struct {
  UINTN             Signature;
  EFI_LIST_ENTRY    AllEntries;  // All entries

  EFI_GUID          HandlerType; // Type of interrupt
  EFI_LIST_ENTRY    SmiHandlers; // All handlers
} SMM_SMI_ENTRY;

#define SMI_HANDLER_SIGNATURE  SIGNATURE_32('s','m','i','h')

typedef struct {
  UINTN                         Signature;
  EFI_LIST_ENTRY                Link;        // Link on SMI_ENTRY.SmiHandlers
  EFI_SMM_HANDLER_ENTRY_POINT2  Handler;     // The smm handler's entry point
  SMM_SMI_ENTRY                 *SmiEntry;
} SMM_SMI_HANDLER;




#define SMM_EFI_HANDLE_SIGNATURE            SIGNATURE_32('S','h','n','d')
//#define ASSERT_IS_HANDLE(a)  ASSERT((a)->Signature == EFI_HANDLE_SIGNATURE)

#define SMM_PROTOCOL_ENTRY_SIGNATURE        SIGNATURE_32('S','p','r','E')

#define SMM_SMST_SIGNATURE2                 SIGNATURE_32('S','M','T','2')


#ifndef EFI_LIST_ENTRY_DEFINED
#define EFI_LIST_ENTRY_DEFINED
typedef struct _EFI_LIST_ENTRY {
    struct _EFI_LIST_ENTRY *ForwardLink;
    struct _EFI_LIST_ENTRY *BackLink;
} EFI_LIST_ENTRY;
#endif


typedef struct {
  UINTN               Signature;
  /// All handles list of IHANDLE
  EFI_LIST_ENTRY          AllHandles;
  /// List of PROTOCOL_INTERFACE's for this handle
  EFI_LIST_ENTRY          Protocols;
  UINTN               LocateRequest;
} SMM_IHANDLE;



typedef struct {
  UINTN               Signature;
  /// Link Entry inserted to mProtocolDatabase
  EFI_LIST_ENTRY          AllEntries;
  /// ID of the protocol
  EFI_GUID            ProtocolID;
  /// All protocol interfaces
  EFI_LIST_ENTRY          Protocols;
  /// Registerd notification handlers
  EFI_LIST_ENTRY          Notify;
} SMM_PROTOCOL_ENTRY;


#define SMM_PROTOCOL_INTERFACE_SIGNATURE  SIGNATURE_32('S','p','i','f')

typedef struct {
  UINTN                       Signature;
  /// Link on IHANDLE.Protocols
  EFI_LIST_ENTRY                  Link;
  /// Back pointer
  SMM_IHANDLE                     *Handle;
  /// Link on PROTOCOL_ENTRY.Protocols
  EFI_LIST_ENTRY                  ByProtocol;
  /// The protocol ID
  SMM_PROTOCOL_ENTRY              *Protocol;
  /// The interface value
  VOID                        *Interface;
} SMM_PROTOCOL_INTERFACE;

#define SMM_PROTOCOL_NOTIFY_SIGNATURE       ('S','p','r','n')

typedef struct {
  UINTN               Signature;
  SMM_PROTOCOL_ENTRY      *Protocol;
  /// All notifications for this protocol
  EFI_LIST_ENTRY          Link;
  /// Notification function
  EFI_SMM_NOTIFY_FN   Function;
  /// Last position notified
  EFI_LIST_ENTRY          *Position;
} SMM_PROTOCOL_NOTIFY;

typedef struct {
  EFI_GUID        *Protocol;
  VOID            *SearchKey;
  EFI_LIST_ENTRY  *Position;
  SMM_PROTOCOL_ENTRY  *ProtEntry;
} SMM_LOCATE_POSITION;

typedef
SMM_IHANDLE *
(* SMM_CORE_GET_NEXT) (
  IN OUT SMM_LOCATE_POSITION    *Position,
  OUT VOID                      **Interface
  );

VOID
SmmNotifyProtocol (
  IN SMM_PROTOCOL_INTERFACE   *Prot
  );

EFI_STATUS
SmmSmstInstallProtocolInterfaceNotify (       
  IN OUT EFI_HANDLE     *UserHandle,
  IN EFI_GUID           *Protocol,
  IN EFI_INTERFACE_TYPE InterfaceType,
  IN VOID               *Interface,
  IN BOOLEAN            Notify
  );

EFI_STATUS
EFIAPI
SmmSmstHandleProtocol (
  IN EFI_HANDLE       UserHandle,
  IN EFI_GUID         *Protocol,
  OUT VOID            **Interface
  );


EFI_STATUS
EFIAPI
SmmSmstLocateProtocol (
  IN  EFI_GUID  *Protocol,
  IN  VOID      *Registration OPTIONAL,
  OUT VOID      **Interface
  );

EFI_STATUS
EFIAPI
SmmUninstallProtocolInterface (
  IN EFI_HANDLE       UserHandle,
  IN EFI_GUID         *Protocol,
  IN VOID             *Interface
  );

SMM_PROTOCOL_INTERFACE *
SmmRemoveInterfaceFromProtocol (
  IN SMM_IHANDLE   *Handle,
  IN EFI_GUID  *Protocol,
  IN VOID      *Interface
  );




/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

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
