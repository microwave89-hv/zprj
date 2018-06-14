//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/DataHub.h 2     3/13/06 1:40a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:40a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DataHub.h $
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     3/12/04 5:30p Markw
// 
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	DataHub_h
//
// Description:	
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef _DATA_HUB_PROTOCOL_H_
#define _DATA_HUB_PROTOCOL_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_DATA_HUB_PROTOCOL_GUID \
	{0xae80d021,0x618e,0x11d4,0xbc,0xd7,0x0,0x80,0xc7,0x3c,0x88,0x81}

GUID_VARIABLE_DECLARATION(gEfiDataHubProtocolGuid,EFI_DATA_HUB_PROTOCOL_GUID);

typedef struct _EFI_DATA_HUB_PROTOCOL EFI_DATA_HUB_PROTOCOL;

typedef struct {
	UINT16		Version;
	UINT16		HeaderSize;
	UINT32		RecordSize;
	EFI_GUID	DataRecordGuid;
	EFI_GUID	ProducerName;
	UINT64		DataRecordClass;
	EFI_TIME	LogTime;
	UINT64		LogMonotonicCount;
} EFI_DATA_RECORD_HEADER;


//************************************************************
// Version value
//************************************************************
#define EFI_DATA_RECORD_HEADER_VERSION	0x0100

//************************************************************
// DataRecordClass values
//************************************************************
//
// Definition of DataRecordClass. These are used to filter
// out data types at a very high level. The
// DataRecord. DataRecordGuid still defines the format
// of the data.
//
#define EFI_DATA_CLASS_DEBUG			0x0000000000000001
#define EFI_DATA_CLASS_ERROR			0x0000000000000002
#define EFI_DATA_CLASS_DATA				0x0000000000000004
#define EFI_DATA_CLASS_PROGRESS_CODE	0x0000000000000008

typedef EFI_STATUS (EFIAPI *EFI_DATA_HUB_LOG_DATA) (
	IN EFI_DATA_HUB_PROTOCOL	*This,
	IN EFI_GUID					*DataRecordGuid,
	IN EFI_GUID					*ProducerName,
	IN UINT64					DataRecordClass,
	IN VOID						*RawData,
	IN UINT32					RawDataSize
);

typedef EFI_STATUS (EFIAPI *EFI_DATA_HUB_GET_NEXT_DATA_RECORD) (
	IN EFI_DATA_HUB_PROTOCOL	*This,
	IN OUT UINT64				*MonotonicCount,
	IN EFI_EVENT				*FilterDriver OPTIONAL,
	OUT	EFI_DATA_RECORD_HEADER	**Record
);

typedef EFI_STATUS (EFIAPI *EFI_DATA_HUB_REGISTER_DATA_FILTER_DRIVER) (
	IN EFI_DATA_HUB_PROTOCOL	*This,
	IN EFI_EVENT				FilterEvent,
	IN EFI_TPL					FilterTpl,
	IN UINT64					FilterClass,
	IN EFI_GUID					*FilterDataRecordGuid OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_DATA_HUB_UNREGISTER_DATA_FILTER_DRIVER) (
	IN EFI_DATA_HUB_PROTOCOL	*This,
	IN EFI_EVENT				FilterEvent
);

struct _EFI_DATA_HUB_PROTOCOL {
	EFI_DATA_HUB_LOG_DATA						LogData;
	EFI_DATA_HUB_GET_NEXT_DATA_RECORD			GetNextDataRecord;
	EFI_DATA_HUB_REGISTER_DATA_FILTER_DRIVER	RegisterFilterDriver;
	EFI_DATA_HUB_UNREGISTER_DATA_FILTER_DRIVER	UnregisterFilterDriver;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
