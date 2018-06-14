//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                      All Rights Reserved.                           **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/SuperIo.h 2     5/06/11 12:09p Yakovlevs $
//
// $Revision: 2 $
//
// $Date: 5/06/11 12:09p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/SuperIo.h $
// 
// 2     5/06/11 12:09p Yakovlevs
// AMI Function Headers added.
// 
// 1     5/04/11 5:55p Yakovlevs
// Initial Checkin.
// 

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	SuperIo.h
//
// Description:	EFI SuperIO Protocol Definitions.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __EFI_SUPER_IO_PROTOCOL_H__
#define __EFI_SUPER_IO_PROTOCOL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>

#define EFI_SIO_PROTOCOL_GUID \
  { 0x215fdd18, 0xbd50, 0x4feb, 0x89, 0xb, 0x58, 0xca, 0xb, 0x47, 0x39, 0xe9 }

GUID_VARIABLE_DECLARATION(gEfiSioProtocolGuid, EFI_SIO_PROTOCOL_GUID);

//Small resource common header
typedef union _ACPI_SMALL_RESOURCE_HEADER {
	UINT8		HDR;
	struct{
		UINT8	Length	: 3;
		UINT8	Name	: 4;
		UINT8	Type	: 1;
	};
}ACPI_SMALL_RESOURCE_HEADER;

//Large resource common header
typedef struct _ACPI_LARGE_RESOURCE_HEADER {
	union {
		UINT8	HDR;
		struct {
			UINT8		Name	: 7;
			UINT8		Type	: 1;
		};
	};
	UINT16			Length;
} ACPI_LARGE_RESOURCE_HEADER;

typedef union {
  ACPI_SMALL_RESOURCE_HEADER *SmallHeader;
  ACPI_LARGE_RESOURCE_HEADER *LargeHeader;
} ACPI_RESOURCE_HEADER_PTR;

typedef struct {
  UINT8 Register;       ///< Register number.
  UINT8 AndMask;        ///< Bitwise AND mask.
  UINT8 OrMask;         ///< Bitwise OR mask.
} EFI_SIO_REGISTER_MODIFY;
  
typedef struct _EFI_SIO_PROTOCOL  EFI_SIO_PROTOCOL;
  

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_SIO_REGISTER_ACCESS
//
// Description: Provides a low level access to the registers for the Super I/O.
//
// Input:
//  This        Indicates a pointer to the calling context.
//  Write       Specifies the type of the register operation. If this parameter is TRUE, Value is
//              interpreted as an input parameter and the operation is a register write. If this parameter
//              is FALSE, Value is interpreted as an output parameter and the operation is a register
//              read.
//  ExitCfgMode Exit Configuration Mode Indicator. If this parameter is set to TRUE, the Super I/O
//              driver will turn off configuration mode of the Super I/O prior to returning from this
//              function. If this parameter is set to FALSE, the Super I/O driver will leave Super I/O
//              in the configuration mode.
//              The Super I/O driver must track the current state of the Super I/O and enable the
//              configuration mode of Super I/O if necessary prior to register access.
//  Register    Register number.
//  Value       If Write is TRUE, Value is a pointer to the buffer containing the byte of data to be
//              written to the Super I/O register. If Write is FALSE, Value is a pointer to the
//              destination buffer for the byte of data to be read from the Super I/O register. 
//
// Output:
//   EFI_SUCCESS           The operation completed successfully
//   EFI_INVALID_PARAMETER The Value is NULL
//   EFI_INVALID_PARAMETER Invalid Register number
//
// Notes:
//
//<AMI_SHDR_END>
//**********************************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_SIO_REGISTER_ACCESS)(
  IN   CONST  EFI_SIO_PROTOCOL  *This,
  IN          BOOLEAN           Write,
  IN          BOOLEAN           ExitCfgMode,
  IN          UINT8             Register,
  IN OUT      UINT8             *Value
);
  
//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_SIO_GET_RESOURCES
//
// Description: 
//   Provides an interface to get a list of the current resources consumed by the device in the ACPI
//   Resource Descriptor format.
//
// Input:
//   This            Indicates a pointer to the calling context.
//   ResourceList    A pointer to an ACPI resource descriptor list that defines the current resources used by
//                   the device. Type ACPI_RESOURCE_HEADER_PTR is defined in the below.
//
// Output:
//   EFI_SUCCESS           The operation completed successfully
//   EFI_INVALID_PARAMETER The Value is NULL
//
// Notes:
//
//<AMI_SHDR_END>
//**********************************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_SIO_GET_RESOURCES)(
  IN  CONST EFI_SIO_PROTOCOL            *This,
  OUT       ACPI_RESOURCE_HEADER_PTR    *ResourceList
);
  
//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_SIO_SET_RESOURCES
//
// Description: Sets the resources for the device.
//
// Input:
//   This            Indicates a pointer to the calling context.
//   ResourceList    A pointer to an ACPI resource descriptor list that defines the current resources used by
//                   the device. Type ACPI_RESOURCE_HEADER_PTR is defined in the below.
//
// Output:
//   EFI_SUCCESS           The operation completed successfully
//   EFI_INVALID_PARAMETER The Value is NULL
//
// Notes:
//
//<AMI_SHDR_END>
//**********************************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_SIO_SET_RESOURCES)(
  IN CONST  EFI_SIO_PROTOCOL        *This,
  IN        ACPI_RESOURCE_HEADER_PTR ResourceList
);
  
//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_SIO_POSSIBLE_RESOURCES
//
// Description: 
//  Provides a collection of resource descriptor lists. Each resource descriptor list in the collection
//  defines a combination of resources that can potentially be used by the device.
//
// Input:
//  This                  Indicates a pointer to the calling context.
//  ResourceCollection    Collection of the resource descriptor lists.
//
// Output:
//   EFI_SUCCESS           The operation completed successfully
//   EFI_INVALID_PARAMETER The Value is NULL
//
// Notes:
//
//<AMI_SHDR_END>
//**********************************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_SIO_POSSIBLE_RESOURCES)(
  IN  CONST EFI_SIO_PROTOCOL         *This,
  OUT       ACPI_RESOURCE_HEADER_PTR *ResourceCollection
);
  
//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_SIO_MODIFY
//
// Description: 
//  Provides an interface for a table based programming of the Super I/O registers.
//  
//  The Modify() function provides an interface for table based programming of the Super I/O
//  registers. This function can be used to perform programming of multiple Super I/O registers with a
//  single function call. For each table entry, the Register is read, its content is bitwise ANDed with
//  AndMask, and then ORed with OrMask before being written back to the Register. The Super
//  I/O driver must track the current state of the Super I/O and enable the configuration mode of Super I/
//  O if necessary prior to table processing. Once the table is processed, the Super I/O device has to be
//  returned to the original state.
//
// Input:
//  This                Indicates a pointer to the calling context.
//  Command             A pointer to an array of NumberOfCommands EFI_SIO_REGISTER_MODIFY
//                      structures. Each structure specifies a single Super I/O register modify operation. Type
//                      EFI_SIO_REGISTER_MODIFY is defined in the "Related Definitions" below.
//  NumberOfCommands    Number of elements in the Command array.  
//
// Output:
//   EFI_SUCCESS           The operation completed successfully
//   EFI_INVALID_PARAMETER The Value is NULL
//
// Notes:
//
//<AMI_SHDR_END>
//**********************************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_SIO_MODIFY)(
  IN CONST EFI_SIO_PROTOCOL         *This,
  IN CONST EFI_SIO_REGISTER_MODIFY  *Command,
  IN       UINTN                    NumberOfCommands
);
  
typedef struct _EFI_SIO_PROTOCOL {
  EFI_SIO_REGISTER_ACCESS       RegisterAccess;
  EFI_SIO_GET_RESOURCES         GetResources;
  EFI_SIO_SET_RESOURCES         SetResources;
  EFI_SIO_POSSIBLE_RESOURCES    PossibleResources;
  EFI_SIO_MODIFY                Modify;
}EFI_SIO_PROTOCOL;  

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif // __EFI_SUPER_IO_PROTOCOL_H__

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                      All Rights Reserved.                           **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
