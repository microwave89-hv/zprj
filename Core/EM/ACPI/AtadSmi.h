//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/AtadSmi.h 1     1/23/14 5:47p Oleksiyy $
//
// $Revision: 1 $
//
// $Date: 1/23/14 5:47p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/AtadSmi.h $
// 
// 1     1/23/14 5:47p Oleksiyy
// [TAG]  		EIP113941
// [Category]  	New Feature
// [Description]  	Time and Alarm ACPI device implemented.
// [Files]  		AtadSmi.cif
// AtadSmi.sdl
// AtadSmi.mak
// AtadSmi.dxs
// AtadSmi.h
// AtadSmi.c
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  <Atad.h>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************

//---------------------------------------------------------------------------

#define ATAD_SW_SMI_UPDATE      2
#define ATAD_SW_SMI_GET         1
#define ATAD_SW_SMI_OK          3
#define ATAD_SW_SMI_NOT_GOOD    0xA5


#define ATAD_SMI_GUID \
{0x6F431B9F, 0x57E2, 0x1049, 0x5A, 0x3B, 0x69, 0x50, 0x4A, 0xED, 0x4F, 0x57}
#define EFI_TIME_VARIABLE_GUID \
{0x9d0da369, 0x540b, 0x46f8, 0x85, 0xa0, 0x2b, 0x5f, 0x2c, 0x30, 0x1e, 0x15}

#pragma pack(push, 1)
typedef struct {
    INT16 TimeZone;
    UINT8 Daylight;
    } TIME_VARIABLE;

    
typedef struct
{
    UINT8      Signature;
    UINT8      DayLight;
    UINT16    TimeZone;

} ATAD_VARIABLE;

#pragma pack(pop)

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************