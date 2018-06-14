#ifndef __FORM_CALLBACK_PROTOCOL_H__
#define __FORM_CALLBACK_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#if EFI_SPECIFICATION_VERSION>0x20000 && !defined(GUID_VARIABLE_DEFINITION)
#pragma message("The EFI_FORM_CALLBACK_PROTOCOL protocol is only supported for the UEFI 2.0 projects")
#pragma message("UEFI 2.1 projects must use HiiConfigAccess.h header instead")
#pragma message("The supported version of the UEFI specification is defined by the EFI_SPECIFICATION_VERSION SDL token")
#error the protocol is depricated
#else
#include <EFI.h>

#define EFI_FORM_CALLBACK_PROTOCOL_GUID  \
   { 0xf3e4543d, 0xcf35, 0x6cef, 0x35, 0xc4, 0x4f, 0xe6, 0x34, 0x4d, 0xfc, 0x54 }

GUID_VARIABLE_DECLARATION(gEfiFormCallbackProtocolGuid,EFI_FORM_CALLBACK_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <Protocol/Hii.h>

typedef struct _EFI_FORM_CALLBACK_PROTOCOL EFI_FORM_CALLBACK_PROTOCOL;

//This flags are different from IFR Flags
#define RESET_REQUIRED  1	//callback operation resulted in an eventual reset to be done upon exit of the browser
#define EXIT_REQUIRED   2   //after the processing of the callback results - exit the browser
#define SAVE_REQUIRED   4   //after the processing of the callback results - save the NV data
#define NV_CHANGED      8   //processing of the callback results - turn the NV flag on
#define NV_NOT_CHANGED 16   //after the processing of the callback results - turn the NV flag off

#pragma pack(push, 1)

typedef struct _EFI_IFR_PACKET {
	EFI_HII_IFR_PACK	*IfrData;
	EFI_HII_STRING_PACK	*StringData;
} EFI_IFR_PACKET;

typedef struct _IFR_DATA_HDR{
	UINT8           OpCode;   //string, numeric, one-of, check box or text
	UINT8           Length;   //length of the EFI_IFR_DATA_ENTRY packet
	UINT16			Flags;    //Flags settings see above
} IFR_DATA_HDR;

typedef struct {
	IFR_DATA_HDR	Header;	
	UINT8			Data[1];  //The data in the form based on the op-code type
// If the OpCode is a OneOf or Numeric type - Data is a UINT16 value
// If the OpCode is a String type - Data is a CHAR16[x] type
// If the OpCode is a Checkbox type - Data is a UINT8 value
// If the OpCode is a NV Access type - Data is a EFI_IFR_NV_DATA structure
} EFI_IFR_DATA;


typedef struct {
	UINT8			*NvRamMap;    // If the flag of the op-code specified retrieval of a copy of the NVRAM map, 
                                  // this is a pointer to a buffer copy
	UINT32			EntryCount;   // Number of EFI_IFR_DATA_ENTRY entries
	EFI_IFR_DATA    Data[1];      // Data entries.
} EFI_IFR_DATA_ARRAY;


typedef union {
	EFI_IFR_DATA_ARRAY		DataArray;    // Primarily used by those who call back to their drivers and use HII as a repository
	EFI_IFR_PACKET			DataPacket;   // Primarily used by those which do not use HII as a repository
	CHAR16					String[1];    // If returning an error - fill the string with null-terminated contents
} EFI_HII_CALLBACK_PACKET;

#pragma pack(pop)

// The following are a Callback Protocol functions
typedef EFI_STATUS (EFIAPI *EFI_FORM_CALLBACK) (
		IN     EFI_FORM_CALLBACK_PROTOCOL	*This,
		IN     UINT16                       KeyValue,
		IN     EFI_IFR_DATA_ARRAY           *Data,
		OUT    EFI_HII_CALLBACK_PACKET      **Packet );


typedef EFI_STATUS (EFIAPI *EFI_NV_READ) (
		IN     EFI_FORM_CALLBACK_PROTOCOL	*This,
		IN     CHAR16                       *VariableName,
		IN     EFI_GUID                     *VendorGuid,
		OUT    UINT32                       *Attributes OPTIONAL,
		IN OUT UINTN                        *DataSize,
		OUT    VOID                         *Buffer );

typedef EFI_STATUS (EFIAPI *EFI_NV_WRITE) (
		IN     EFI_FORM_CALLBACK_PROTOCOL	*This,
		IN     CHAR16						*VariableName,
		IN     EFI_GUID                     *VendorGuid,
		IN     UINT32						Attributes,
		IN     UINTN                        DataSize,
		IN     VOID                         *Buffer,
		OUT    BOOLEAN						*ResetRequired);


//the FormCallback Protocol structure
typedef struct _EFI_FORM_CALLBACK_PROTOCOL {
	EFI_NV_READ                 NvRead;
	EFI_NV_WRITE                NvWrite;
	EFI_FORM_CALLBACK			Callback;
} EFI_FORM_CALLBACK_PROTOCOL;
#endif // #if EFI_SPECIFICATION_VERSION>0x20000
/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
#ifdef __cplusplus
}
#endif
#endif