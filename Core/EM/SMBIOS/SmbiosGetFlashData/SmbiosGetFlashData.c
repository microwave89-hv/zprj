//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//

//**********************************************************************//
// $Header: /Alaska/SOURCE/Modules/SMBIOS/SmbiosGetFlashData/SmbiosGetFlashData.c 11    2/17/15 1:17p Davidd $
//
// $Revision: 11 $
//
// $Date: 2/17/15 1:17p $
//**********************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMBIOS/SmbiosGetFlashData/SmbiosGetFlashData.c $
// 
// 11    2/17/15 1:17p Davidd
// [TAG]  		EIP205509
// [Category]  	Improvement
// [Description]  	Merge Aptio V Smbios EIP193807, 193858, 196901 changes
// into Aptio 4 Smbios
// [Files]  		SmbiosDmiEdit.sdl
// SmbiosDmiEdit.c
// SmbiosNvramFunc.c
// SmbiosGetFlashData.c
//
// 10    5/23/13 6:10p Davidd
// [TAG]           EIP124635
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       When DMIEdit data area in BootBlock is erased with 0x00
// value, the system hangs at CP 0x62
// [RootCause]     In function FindRawSection, a pointer is used to
// traverse sections in the FFS to locate the DMIEdit raw data section. In
// case the "size" of the header become corrupted (cleared to zero), this
// zero value is added to the pointer causes it not to move making the
// system hang.
// [Solution]      Check if the size is zero then break out of the while
// loop
// [Files]         SmbiosGetFlashData.c
//
// 9     8/30/11 4:15p Davidd
// [TAG]           EIP65648
// [Category]      Improvement
// [Description]   Update SMBIOS eModules for uEFI 2.3.1 / PI 1.2
// compliance
// [Files]         Smbios.c
//                 Smbios.dxs
//                 SmbiosDMIEdit.c
//                 SmbiosDMIEditFunc.c
//                 SmbiosGetFlashData.c
//                 SmbiosGetFlashData.dxs
//
// 8     5/11/11 12:35p Davidd
// [TAG]           EIP58171
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]       TABLE_INFO structure of SmbiosDMIEdit is not backward
// compatible for AFU preserve DMI structure feature.
// [RootCause]     TABLE_INFO structure of SmbiosDMIEdit is not backward
// compatible.
// [Solution]      New TABLE_INFO structure defined for backward
// compatibility and support added.
// [Files]         Smbios.c
//                 SmbiosDMIEdit.h
//                 SmbiosDMIEditFunc.c
//                 SmbiosGetFlashData.c
//
// 7     11/02/10 4:14p Davidd
// [TAG]           EIP42938
// [Category]      BUG FIX
// [Severity]      Critical
// [Symptom]       The SMBIOS string field cannot be successfully updated
// if it was programmed to Null by the 3-party SMBIOS tool
// [RootCause]     BIOS did not have support for NULL strings
// [Solution]      Problem has been fixed with code changes
// [Files]
//    Smbios.c
//    SmbiosDMIEditFunc.c
//    SmbiosGetFlashData.c
//    SmbiosDMIEdit.h
//    SmbiosFlashData.sdl
//
// 6     6/02/09 11:25a Davidd
// Updated AMI and function headers. (EIP 22180)
//
// 5     12/16/08 2:28a Iminglin
// (EIP17767) The function value of FindFile for compliance.
//
// 4     3/29/07 6:11p Davidd
// Changed the year in the AMI banner and adjust indentation to coding
// standard.
//
// 3     12/15/06 5:47p Davidd
// Code cleanup and reformatted to coding standard.
//
// 2     3/21/06 8:44p Fasihm
// Changed the protocol name FvBlock.h to FirmwareVolumeBlock.h to be
// compatable with the new Aptio 4.5 Core and later.
//
// 1     4/29/05 2:07p Davidd
// Initial checkin.
//
// 2     6/12/04 11:54p Markw
//
// 1     5/20/04 3:41p Markw
//
//**********************************************************************

#include <AmiDxeLib.h>
#include <Token.h>
#include <Protocol\SmbiosGetFlashDataProtocol.h>
#include <Protocol\FirmwareVolumeBlock.h>

#define Align4(Value) (((Value)+3) & ~3)
#define Align8(Value) (((Value)+7) & ~7)
#define SECTION_SIZE(SectionHeaderPtr) \
  ( (UINT32) ( *((UINT32 *) ((EFI_COMMON_SECTION_HEADER *)SectionHeaderPtr)->Size) & 0x00ffffff) )

#pragma pack(1)

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:  TABLE_INFO
//
// Description: DMI data record
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

#define DMIEDIT_WRITE_ONCE      0x01
#define DMIEDIT_DELETE_STRUC    0x02
#define DMIEDIT_ADD_STRUC       0x04
#define DMIEDIT_EXTENDED_HDR    0x80

typedef struct {
    UINT8   Type;
    UINT8   Offset;     // Structure field offset, or string number for Type 11 and 12
    UINT8   Reserved;   // Size of string including \0 or UUID (16)
    UINT8   Flags;      // Bit0 = Write Once
                        // Bit1 = Delete Structure
                        // Bit2 = Add structure
                        // Bit7 = Extended Header
    UINT8   HdrLength;
    UINT16  Size;
    UINT16  Handle;
} TABLE_INFO;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:  ROM_INFO
//
// Description: DMI Data Table Header
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct {
	UINT32	Signature;
	UINT32 	Size;
} ROM_INFO;

#pragma pack()


EFI_GUID FlashDataFile = {0xFD44820B,0xF1AB,0x41c0,0xAE,0x4E,0x0C,0x55,0x55,0x6E,0xB9,0xBD};
EFI_GUID ZeroGuid = {0,0,0,0,0,0,0,0,0,0,0};
EFI_GUID FFGuid = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

ROM_INFO    gRomInfo;
void        *gRomData;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CompareGuid
//
// Description: Compares two input GUIDs
//
// Input:       IN EFI_GUID *G1
//              IN EFI_GUID *G2
//
// Output:      INT8 - 0/-1 for Equal/Not Equal
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INT8
CompareGuid (
    IN EFI_GUID *G1,
    IN EFI_GUID *G2
)
{
	UINT32 *p1 = (UINT32*)G1, *p2 = (UINT32*)G2;
	UINTN	i;
	for(i=0; i<4; ++i) {
		if(p1[i] != p2[i]) return -1;
	}
	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetFlashTableInfo
//
// Description: Get Flash Data location and size.
//
// Input:       IN      EFI_SMBIOS_FLASH_DATA_PROTOCOL  *This
//              IN OUT  VOID                            **Location
//              IN OUT  UINT32                          *Size
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetFlashTableInfo (
	IN      EFI_SMBIOS_FLASH_DATA_PROTOCOL  *This,
	IN OUT  VOID 	                        **Location,
	IN OUT  UINT32 	                        *Size
)
{
	*Location = gRomData;
	*Size = gRomInfo.Size;
	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetField
//
// Description: Get Flash Data Field
//
// Input:       IN EFI_SMBIOS_FLASH_DATA_PROTOCOL   *This
//              IN UINT8                            Table
//              IN UINT8                            Offset
//              IN VOID                             **Field
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetField (
	IN EFI_SMBIOS_FLASH_DATA_PROTOCOL  *This,
	IN UINT8                           Table,
	IN UINT8                           Offset,
	IN VOID                            **Field
)
{
    TABLE_INFO *p = gRomData;

    while ( p->Offset != 0xff && (p->Type != Table || p->Offset != Offset))	{
		p = (TABLE_INFO*)  ((UINT8*)(p+1) + p->Size);
	}

	if (p->Offset != 0xff) {
		*Field = p + 1;
		return EFI_SUCCESS;
	}

	*Field = 0;
	return EFI_NOT_FOUND;
}


EFI_SMBIOS_FLASH_DATA_PROTOCOL gSmbiosFlashDataProtocol = {
	GetFlashTableInfo,
	GetField
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindRawSection
//
// Description: Find the RAW section
//
// Input:       IN VOID  *Section
//              IN VOID  *End
//
// Output:      VOID* - Pointer to Raw Section if found
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID*
FindRawSection (
    IN VOID *Section,
    IN VOID *End
)
{
	EFI_COMMON_SECTION_HEADER	*p = Section;
	while((INT32)p < (INT32)End)	//Use signed because 0 = 0x100000000
	{
		if (p->Type == EFI_SECTION_RAW) return (p+1);

		if (Align4(SECTION_SIZE(p)) == 0x00) {
			return 0;               // Section size = 0 indicates data is corrupted
		}

		p = (EFI_COMMON_SECTION_HEADER*)((UINT8*)p+Align4(SECTION_SIZE(p)));
	}
	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindFile
//
// Description: Find file in the FV with the input GUID
//
// Input:       IN EFI_GUID  *Guid
//              IN VOID      *File
//              IN VOID      *EndOfFiles
//
// Output:      VOID* - Pointer to File if found
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID*
FindFile (
    IN EFI_GUID *Guid,
    IN VOID     *File,
    IN VOID     *EndOfFiles
)
{
	EFI_FFS_FILE_HEADER *p = File;

    while(((INT32)p < (INT32)EndOfFiles) &&
          ((INT32)(p+sizeof(EFI_FFS_FILE_HEADER)) < (INT32)EndOfFiles)) // Use signed because 0 = 0x100000000
	{
		if (0==CompareGuid(Guid,&p->Name)) {
			//Found File.
			return FindRawSection(
				        p+1,
				        (UINT8*)p + (*(UINT32*)p->Size & 0xffffff) - sizeof(*p)
				        );
		}
		//Check for last of File in firmware volume.
		if (0==CompareGuid(&p->Name,&FFGuid) || 0==CompareGuid(&p->Name,&ZeroGuid))
			return NULL;

		p = (EFI_FFS_FILE_HEADER*)((UINT8*)p + Align8((*(UINT32*)p->Size & 0xffffff)));
	}

	return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetDataLocation
//
// Description: Find the Flash Data file in the FV.
//
// Input:       None
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetDataLocation (VOID)
{
	EFI_GUID							gEfiFirmwareVolumeBlockProtocolGuid = EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL_GUID;
    EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL  *FvBlock;
    EFI_PHYSICAL_ADDRESS                Address;
	EFI_HANDLE							*HandleBuffer;
	EFI_STATUS							Status;
    UINTN                               i;
	UINTN								NumHandles;
    void                                *FirstFile;
    void                                *EndOfFiles;
    void                                *File;

    Status = pBS->LocateHandleBuffer(ByProtocol,
                                    &gEfiFirmwareVolumeBlockProtocolGuid,
                                    NULL,
                                    &NumHandles,
                                    &HandleBuffer);
	if (EFI_ERROR(Status)) return Status;

    for (i = 0; i < NumHandles; ++i) {
        Status = pBS->HandleProtocol(HandleBuffer[i],
                                    &gEfiFirmwareVolumeBlockProtocolGuid,
                                    &FvBlock);
        if (EFI_ERROR(Status)) continue;

        Status = FvBlock->GetPhysicalAddress(FvBlock, &Address);

        if (Status == EFI_SUCCESS) {
            FirstFile = (UINT8*)Address
                        + ((EFI_FIRMWARE_VOLUME_HEADER*)Address)->HeaderLength;

            EndOfFiles = (UINT8*)Address
                        + ((EFI_FIRMWARE_VOLUME_HEADER*)Address)->FvLength;

            File = FindFile(&FlashDataFile, FirstFile, EndOfFiles);
            if (!File) {
                Status = EFI_NOT_FOUND;
                continue;
            }

            gRomInfo = *(ROM_INFO*)File;
            gRomData = (ROM_INFO*)File + 1;
            break;
        }
    }

	pBS->FreePool(HandleBuffer);
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosGetFlashDataInstall
//
// Description: Driver entry point for SmbiosGetFlashData
//
// Input:       IN EFI_HANDLE           ImageHandle
//              IN EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SmbiosGetFlashDataInstall (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
)
{
	EFI_STATUS  Status;
	EFI_GUID	gSmbiosFlashDataProtocolGuid = EFI_SMBIOS_FLASH_DATA_PROTOCOL_GUID;

    InitAmiLib(ImageHandle, SystemTable);

    Status = GetDataLocation();
    if (EFI_ERROR(Status)) return Status;

	return pBS->InstallMultipleProtocolInterfaces(
		            &ImageHandle,
		            &gSmbiosFlashDataProtocolGuid,&gSmbiosFlashDataProtocol,
		            NULL);
}

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
