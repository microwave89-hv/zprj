//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Core/Modules/Recovery/FsRecovery.c 22    8/09/12 11:13a Pats $
//
// $Revision: 22 $
//
// $Date: 8/09/12 11:13a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/Recovery/FsRecovery.c $
// 
// 22    8/09/12 11:13a Pats
// [TAG] - EIP 80780
// [Category] - Function Request
// [Description] - Support for recovery from media formatted with the
// EXT(x) file system.
// [Files] Recovery.c, Recovery.mak, Recovery.sdl, RecoveryCsp.h (bin),
// and FsRecovery.c (source)
// 
// 21    4/24/12 11:43a Pats
// [TAG]  		EIP87223
// [Category]  	Bug Fix
// [Symptom]  	After update EIP#81131 solution, the MBR recovery function
// would fail
// [RootCause]  	Pointer *Root not being updated correctly in function
// AmiGetFileListFromNtfsVolume().
// [Solution]  	Correct updating of pointer *Root. 
// 
// [Files]  	FsRecovery.c
// 
// 20    1/25/12 2:49p Pats
// [TAG] - EIP 26909
// [Category] - Function Request
// [Description] - Support for recovery from media formatted with the NTFS
// file system. This of necessity includes detection of GPT partitions,
// which may contain any file system.
// [Files] Recovery.c, Recovery.mak, Recovery.sdl, RecoveryCsp.h (bin),
// and FsRecovery.c (source)
// 
// 19    5/13/11 5:07p Artems
// Added secure flash update support
// 
// 18    2/05/11 3:22p Artems
// EIP 39463: Added support to override GetFileName function for custom
// recovery capsule name
// 
// 17    6/11/10 11:36a Artems
// Added porting hooks for GetRecoveryCapsuleFileName and
// IsRecoveryCapsuleValid
// 
// 16    1/05/10 11:59a Robert
// Fixed bug in calculation of byte offset of the beginning of a file on a
// FAT file system.  The old code could not handle a file starting address
// above 4GB.  It now uses a UINT64 calculation so it can handle it
// 
// 15    11/25/09 4:53p Felixp
// sAmiRomFile renamed to RecoveryFileName
// FlashSize renamed ro RecoveryImageSize
// 
// 14    8/11/09 2:27p Robert
// - EIP 24689: There was a bug in the wildcard search with FAT that
// caused it not to identify the file properly.  
// - The code was expecting string termination. Switched to filename
// length instead.  Updated both the FAT file search and the ISO9660
// search with this.
// - Also added a check for the FAT file system that checks for the 0xE5
// character that defines an invalid or deleted file.
// 
// 13    7/09/09 12:54p Artems
// Removed PeiTrace debugging calls
// 
// 12    7/07/09 2:05p Robert
// - Added functionality to search for recovery files that fit one of many
// comma separated pattern strings.
// - Function header updates
// 
// 11    7/01/09 4:18p Rameshr
// Coding Standard and File header updated.
//
// 10    6/16/09 5:21p Artems
// EIP 21169 Added Eltorito support
//
// 7     4/13/07 5:37p Ambikas
// Coding standards changes: Added AMI_PHDRs for every function; split
// multiple declarations on a line into single line statements.
//
// 6     10/13/06 11:07a Felixp
// 1. el Torito support added
// 2. Correct partition handling
//
// 5     9/26/06 9:22a Ambikas
//
// 4     6/04/06 9:29p Ambikas
//
// 3     4/13/06 2:02p Ambikas
//
// 1     12/01/05 9:45a Felixp
//
// 4     11/18/05 3:55p Felixp
// bug fix in ReadFileData
//
// 3     6/06/05 1:27p Felixp
// Type parameter removed from AllocatePages to match PEI CIS 0.91
//
// 2     3/25/05 5:41p Felixp
// small bug fix
//
// 1     3/24/05 3:37p Felixp
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:	    FsRecovery.c
//
// Description:	Recovery Filesytem support
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiPeiLib.h>
#include <Token.h>
#include "Recovery.h"
#include "RecoveryCsp.h"

#define FAT_FILE_NAME_SIZE 11

extern BOOLEAN CdRecoverySupport;
extern BOOLEAN FatRecoverySupport;
extern BOOLEAN NtfsRecoverySupport;
extern BOOLEAN ExtRecoverySupport;

UINT8           *ReadBuffer = NULL;
UINTN           BufferSize  = 0;

UINT8           *FatBuffer    = NULL;
UINTN           FatBufferSize = 0;

UINT8           *RootBuffer    = NULL;
UINTN           RootBufferSize = 0;
UINT32          RootEntries    = 0;
UINT32          RootSize       = 0;

DIR_ENTRY       *FatRecoveryFiles[10];
DIR_RECORD      *CdRecoveryFiles[10];
#if NTFS_RECOVERY_SUPPORT
INDEX_ENTRY     *NtfsRecoveryFiles[10];

//UINT8           MFTRunList[256];
//UINT8           RootRunList[128];
//UINT8           ResidentIndex[256];
BOOLEAN         ResidentPresent;
UINT32          ResidentSize;
#endif
#if EXT_RECOVERY_SUPPORT
DIR_ENTRY_EXT   *ExtRecoveryFiles[10];
UINT32          InodeBlock;     // First block of inode table
UINT8           Indirect;
UINT32          *BlockList;
UINT32          *BlockList2;
#endif

UINTN           PartCount;
BOOLEAN         IsMbr;
UINT32          GpeCount;
UINT32          PartSector;
//MASTER_BOOT_RECORD Mbr;
MEMORY_BLOCK    *MemBlk;

EFI_PEI_SERVICES    **ThisPeiServices;
#if SEARCH_FAT_PATH
RC_VOL_INFO         *ThisVolume; // Saved volume info for path search
#endif

//***************************************************************************

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   toupper
//
// Description: 
//  Converts lower case characters to upper case
//
// Input:       
//  IN CHAR8 c - character to convert
//
// Output:      
//  CHAR8 - converted character value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8 toupper(
    IN CHAR8 c )
{
    return (c >= 'a' && c <= 'z') ? c - 'a' + 'A' : c;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FileCompare
//
// Description: 
//  This function takes a filename and a filename pattern and tries to make 
//  a match.  It can account for Wild characters * and ? in the pattern. Also,
//  the pattern can be multiple comma separated patterns.
//
// Input:       
//  IN CHAR8 *RecoveryFileName - recover file pattern string comma separated
//  IN CHAR8 *FsFilename - file name to check against the pattern string
//  IN BOOLEAN IgnoreSpacesInFilename - If true, ignore spaces in FsFilename when pattern string is a period
//
// Output:      
//  TRUE - Pattern matches filename
//  FALSE - Pattern doesn't match filename
//
// Notes:
//  RecoveryFileNamePattern is taken from the RECOVERY_ROM token and should look
//  like this:   *.rom,ab??rt??.bio,123.bin  etc.
//  The Parameter IgnoreSpacesInFilename is for use with file systems that pad
//  spaces into filenames and don't use periods.  If TRUE, it matches a period 
//  in the pattern to any number of spaces in the filename.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN FileCompare(
    IN CHAR8 *RecoveryFileNamePattern, 
    IN CHAR8 *FsFilename, 
    IN BOOLEAN IgnoreSpacesInFilename,
    IN UINT32 FileNameLength)
{
    CHAR8  ch1, ch;
    UINTN len1, len2;

    for (; ;) {
        // check length of string
        len1 = Strlen(FsFilename);
        len2 = Strlen(RecoveryFileNamePattern);

        // if len1 is 0 then at end of filename
    	if(!len1 || !FileNameLength)
	    {
            // if len2 is 0 then also at end of pattern so file name is 
            //  equal to a pattern
        	if(!len2 )
        		return TRUE;
	        else
            {
                // if len2 is a comma, then it is the same as len2 == 0 so 
                //  file name is equal to a pattern
                ch1 = *RecoveryFileNamePattern;
                if (ch1 == ',')
                {
            		return TRUE;
                }
                // if not a comma or 0, then file does not fit the pattern
	            return FALSE;
            }
        }

        // get next character of the pattern
        ch1 = *RecoveryFileNamePattern;
        RecoveryFileNamePattern ++;

        switch (ch1) 
        {
            case ',':
                return TRUE;
                break;

            case 0: // reached string terminator
                return TRUE;
                break;

            // wild character, it must deal with any number of matching characters 
            //  in the file name string
            case '*':                               
                while (*FsFilename) 
                {
                    if (FileCompare (RecoveryFileNamePattern, FsFilename, IgnoreSpacesInFilename, FileNameLength)) 
                    {
                        return TRUE;
                    }        
                    FsFilename ++;
                    FileNameLength--;
                }
                return FileCompare (RecoveryFileNamePattern, FsFilename, IgnoreSpacesInFilename, FileNameLength);
                break;

            // wild character, it must deal with a matching character in the file name string
            case '?':                               
                if (!*FsFilename) 
                {
                    return FALSE;
                }

                FsFilename ++;
                FileNameLength--;
                break;

            // in this case statement the case '.' must be directly above the default case.
            // if IgnoreSpacesInFilename is FALSE, it is supposed to fall through into default.
            // If IgnoreSpacesInFilenameis TRUE, process the period as a check for spaces character.
            //  then once we skip over all spaces, if there are any, then it moves to the 
            //  next character in the pattern
            case '.':
                // FAT, spaces added to file name to make 8 3  -- no period in the filename either
                if (IgnoreSpacesInFilename == TRUE)  
                {
                    ch = *FsFilename;

                    while ((ch == ' ') && (ch != 0))
                    {
                        FsFilename ++;
                        FileNameLength--;
                        ch = *FsFilename;
                    }
                    break;
                }
                // CDFS, no spaces and there is a period.  Let it fall through to the default case
            default:
                ch = *FsFilename;
                if (toupper(ch) != toupper(ch1)) 
                {
                    return FALSE;
                }
                FsFilename ++;
                FileNameLength--;
                break;
        }
    }        
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FileSearch
//
// Description: 
//  Wrapper function for parsing through a pattern string with multiple entries
//  Each entry is comma separated and can include wild characters like * and ?
//  The Function can handle CDFS and FAT file systems.  
//
// Input:       
//  IN CHAR8 *RecoveryFileName - recover file pattern string comma separated
//  IN CHAR8 *FsFilename - file name to check against the pattern string
//  IN BOOLEAN IgnoreSpacesInFilename - If true, ignore spaces in FsFilename when pattern string is a period
//
// Output:      
//  EFI_SUCCESS - File name fits one of the Pattern strings in RecoveryFileName
//  EFI_INVALID_PARAMETER - one of the strings is NULL or file name doesn't fit pattern string
//
// Notes:
//  
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FileSearch(
    IN CHAR8 *RecoveryFileName, 
    IN CHAR8 *FsFilename, 
    IN BOOLEAN IgnoreSpacesInFilename,
    IN UINT32   FileNameLength)
{
    CHAR8 *RecStrPtr = RecoveryFileName;
    CHAR8 *FilenamePtr = FsFilename;

    if (*RecStrPtr == 0) 
    {
        return EFI_INVALID_PARAMETER;
    }

    if (*FsFilename == 0)
    {
        return EFI_INVALID_PARAMETER;
    }   

    if (FileNameLength == 0 ) 
    {
        return EFI_INVALID_PARAMETER;
    }   
   

    // loop until all possibilities listed in the RecoveryFileName are exhausted
    do {
        // Now compare the current possiblity to the current filename
        FilenamePtr = FsFilename;

        if (*RecStrPtr == ',') 
            RecStrPtr++;

        if (FileCompare(RecStrPtr, FsFilename, IgnoreSpacesInFilename, FileNameLength) == TRUE)
            return EFI_SUCCESS;
        
        while (*RecStrPtr != ',' && *RecStrPtr != 0)
            RecStrPtr ++;

    } while (*RecStrPtr != 0);

    return EFI_INVALID_PARAMETER;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConvertToFatFileName
//
// Description: 
//  Converts file name from "XXXXX.XXX" form to FAT form
//
// Input:       
//  IN  CHAR8 *inFileName - pointer to input file name
//  OUT CHAR8 *outFileName - pointer to output file name
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ConvertToFatFileName(
    IN CHAR8  *inFileName,
    OUT CHAR8 *outFileName )
{
    UINT32 i = 0;
    UINT32 j = 0;

    for ( i = 0; inFileName[i] && inFileName[i] != '.'; i++ ) {
        outFileName[i] =     toupper( inFileName[i] );
    }
    j = i;

    for (; i < 8; i++ ) {
        outFileName[i] = ' ';
    }

    if ( inFileName[j] == '.' ) {
        for ( j++; inFileName[j]; i++, j++ ) {
            outFileName[i] = toupper( inFileName[j] );
        }
    }

    for (; i < 11; i++ ) {
        outFileName[i] = ' ';
    }
    outFileName[i] = 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadDevice
//
// Description: Reads data from Block device
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  UINT64 Start - starting offset in bytes
//  IN  UINTN Size - size of the data to read
//  VOID *Buffer - pointer to buffer to store data
//
// Output:      
//  EFI_SUCCESS
//  Errors
//      - returns either the error status from Allocate Pages or Read Blocks
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadDevice(
    IN EFI_PEI_SERVICES **PeiServices,
    IN RC_VOL_INFO      *Volume,
    IN UINT64           Start,
    IN UINTN            Size,
    OUT VOID            *Buffer )
{
    UINT64               StartLba;
    UINTN                ActualSize;
    UINTN                ActualPages;
    UINT32               StartOffset;
    EFI_STATUS           Status;
    EFI_PHYSICAL_ADDRESS Allocate;

    Start += Volume->PartitionOffset;

    if ( Volume->BlockSize == 4096 )  {
        StartLba    = Shr64( Start, 12 );
        StartOffset = (UINT32)( Start & 0xfff );
    } else if ( Volume->BlockSize == 2048 )  {
        StartLba    = Shr64( Start, 11 );
        StartOffset = (UINT32)( Start & 0x7ff );
    } else {
        StartLba    = Shr64( Start, 9 );
        StartOffset = (UINT32)( Start & 0x1ff );
    }

    ActualSize  = ((StartOffset + Size + Volume->BlockSize - 1) / Volume->BlockSize) * Volume->BlockSize;
    ActualPages = EFI_SIZE_TO_PAGES( ActualSize );

    if ( BufferSize < EFI_PAGES_TO_SIZE( ActualPages )) {
        Status = (*PeiServices)->AllocatePages( PeiServices, EfiBootServicesData, ActualPages, &Allocate );

        if ( EFI_ERROR( Status )) {
            return Status;
        }

        ReadBuffer = (UINT8*)((UINTN)Allocate);
        BufferSize = EFI_PAGES_TO_SIZE( ActualPages );
    }

    Status = Volume->BlkIo->ReadBlocks( PeiServices,
                                        Volume->BlkIo,
                                        Volume->Device,
                                        StartLba,
                                        ActualSize,
                                        ReadBuffer );

    if ( !EFI_ERROR( Status )) {
        MemCpy( Buffer, ReadBuffer + StartOffset, Size );
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsFat
//
// Description: 
//  Checks if given data block describes FAT structure
//
// Input:       
//  BOOT_SECTOR *pBpb - pointer to data block to check
//
// Output:      
//  TRUE - data block is a FAT structure
//  FALSE - data block is not a FAT structure
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsFat(
    IN BOOT_SECTOR *pBpb )
{
    return pBpb->BytsPerSec <= 4096
           && pBpb->SecPerClus && pBpb->SecPerClus <= 128
           && pBpb->RsvdSecCnt
           && pBpb->NumFATs
           && pBpb->Signature == 0xAA55
           && (pBpb->jmp[0] == 0xEB || pBpb->jmp[0] == 0xE9);
}

#if NTFS_RECOVERY_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsNtfs
//
// Description: 
//  Checks if given data block describes NTFS structure
//
// Input:       
//  BOOT_SECTOR *pBpb - pointer to data block to check
//
// Output:      
//  TRUE - data block is a NTFS structure
//  FALSE - data block is not a NTFS structure
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsNtfs(
    IN BOOT_SECTOR *pBpb )
{
    return pBpb->NumFATs == 0
           && pBpb->TotSec16 == 0
           && pBpb->TotSec32 == 0
           && pBpb->Fat.Ntfs.TotSec64 != 0
           && pBpb->OEMName[0] == 0x4E // Name must be "NTFS"
           && pBpb->OEMName[1] == 0x54
           && pBpb->OEMName[2] == 0x46
           && pBpb->OEMName[3] == 0x53
           && pBpb->Signature == 0xAA55
           && (pBpb->jmp[0] == 0xEB || pBpb->jmp[0] == 0xE9);
}
#endif

#if EXT_RECOVERY_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsExt
//
// Description: 
//  Checks if given data block describes EXT Superblock structure
//
// Input:       
//  VOLUME_SB *pSb - pointer to data block to check
//
// Output:      
//  TRUE - data block is a EXT Superblock structure
//  FALSE - data block is not a EXT Superblock structure
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsExt(
    IN VOLUME_SB *pSb )
{
    return pSb->SB_Magic == 0xEF53
           && pSb->SB_BlockSize < 4
           && pSb->SB_FirstBlock < 2
           && pSb->SB_FreeBlocks < pSb->SB_TotalBlocks
           && pSb->SB_FreeInodes < pSb->SB_TotalInodes;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetClustersCount
//
// Description: 
//  Returns number of clusters for given cluster chain
//
// Input:       
//  IN  UINT8 FatType - FAT type (FAT12, FAT16 or FAT32)
//  IN  UINT32 CurrentCluster - first cluster of cluster chain
//  UINT32 *NextCluster - first cluster of next cluster chain if there is break
//  IN  BOOLEAN Continuous - if TRUE, returns only number of subsequent clusters in chain
//                           if FALSE, returns total number of clusters in cluster chain
//
// Output:      
//  UINT32 - number of clusters
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetClustersCount(
    IN UINT8   FatType,
    IN UINT32  CurrentCluster,
    OUT UINT32 *NextCluster,
    IN BOOLEAN Continuous )
{
    UINT32 Count = 0;
    UINT32 WorkCluster;
    UINT32 Cluster = CurrentCluster;

    if ( FatType == FAT16 ) {
        UINT16 *Fat16 = (UINT16*)FatBuffer;
        while ( TRUE )
        {
            Count++;
            WorkCluster = Fat16[Cluster];

            if ( WorkCluster > 0xfff8 ) {
                *NextCluster = 0;
                break;
            }

            if ( WorkCluster != Cluster + 1 && Continuous ) {
                *NextCluster = WorkCluster;
                break;
            }
            Cluster = WorkCluster;
        }
    } else if ( FatType == FAT32 ) {
        UINT32 *Fat32 = (UINT32*)FatBuffer;
        while ( TRUE )
        {
            Count++;
            WorkCluster = Fat32[Cluster] & 0xfffffff;

            if ( WorkCluster > 0xffffff8 ) {
                *NextCluster = 0;
                break;
            }

            if ( WorkCluster != Cluster + 1 && Continuous ) {
                *NextCluster = WorkCluster;
                break;
            }
            Cluster = WorkCluster;
        }
    } else {
        while ( TRUE ) {
            Count++;
            WorkCluster = *(UINT16*)(FatBuffer + Cluster + Cluster / 2);
            WorkCluster = (Cluster & 1) ? WorkCluster >> 4 : WorkCluster & 0xfff;

            if ( WorkCluster > 0xff8 ) {
                *NextCluster = 0;
                break;
            }

            if ( WorkCluster != Cluster + 1 && Continuous ) {
                *NextCluster = WorkCluster;
                break;
            }
            Cluster = WorkCluster;
        }
    }
    return Count;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetFatData
//
// Description: 
//  Reads data from FAT device
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  UINT32 FirstCluster - starting cluster
//  IN  UINTN Size - size of the data to read
//  OUT VOID *Buffer - pointer to buffer to store data
//
// Output:      
//  EFI_SUCCESS - correctly read all FAT data
//  EFI_ABORTED - should never get this.
//  Other - any errors reported from ReadDevice function
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetFatData(
    IN EFI_PEI_SERVICES **PeiServices,
    IN RC_VOL_INFO      *Volume,
    IN UINT32           FirstCluster,
    IN UINTN            Size,
    OUT VOID            *Buffer )
{
    EFI_STATUS Status;
    UINT32     Count;
    UINT32     NextCluster;
    UINT32     Cluster = FirstCluster;
    UINTN      SizeToRead;

    while ( TRUE )
    {
        SizeToRead = Size;
        Count      = GetClustersCount( Volume->FatType, Cluster, &NextCluster, TRUE );
        SizeToRead = (SizeToRead > Count * Volume->BytesPerCluster) ? Count * Volume->BytesPerCluster : SizeToRead;
        Status     = ReadDevice( PeiServices,
                                 Volume,
                                 Volume->DataOffset + Mul64((UINT64)(Cluster - 2), Volume->BytesPerCluster),
                                 SizeToRead,
                                 Buffer );

        if ( EFI_ERROR( Status ) || NextCluster == 0 ) {
            return Status;
        }

        Cluster         = NextCluster;
        (UINT8*)Buffer += SizeToRead;
        Size           -= SizeToRead;
    }
    return EFI_ABORTED;     //should never get here
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetFatType
//
// Description: 
//  Prepares given volume for read operations. Reads FAT table, root directory,
//  determines FAT type
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  BOOT_SECTOR *Bs - pointer to MBR or diskette FAT data
//
// Output:      
//  EFI_STATUS - possible return values from ReadDevice, AllocatePages, GetFatData
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetFatType(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume,
    IN BOOT_SECTOR      *Bs )
{
    EFI_STATUS           Status;
    UINT32               TotalSectors;
    UINT32               FatSectors;
    UINT32               RootSectors;
    UINT32               DataSectors;
    UINT32               RootSize;
    UINT32               FatSize;
    UINT32               DataClusters;
    UINT32               RootClusters;
    UINT32               DummyCluster;
    UINTN                FatPages;
    UINTN                RootPages;
    EFI_PHYSICAL_ADDRESS Allocate;

    FatSectors   = (Bs->FATSz16 != 0) ? Bs->FATSz16 : Bs->Fat.Fat32.FATSz32;
    FatSize      = FatSectors * Bs->BytsPerSec;
    TotalSectors = (Bs->TotSec16 != 0) ?  Bs->TotSec16 : Bs->TotSec32;
    RootSectors  = ((Bs->RootEntCnt * 32) + (Bs->BytsPerSec - 1)) / Bs->BytsPerSec;
    RootSize     = RootSectors * Bs->BytsPerSec;
    DataSectors  = TotalSectors - RootSectors - FatSectors * Bs->NumFATs - Bs->RsvdSecCnt;
    DataClusters = DataSectors / Bs->SecPerClus;

    Volume->FatOffset       = Bs->RsvdSecCnt * Bs->BytsPerSec;
    Volume->RootOffset      = Volume->FatOffset + FatSectors * Bs->NumFATs * Bs->BytsPerSec;
    Volume->DataOffset      = Volume->RootOffset + RootSize;
    Volume->BytesPerCluster = Bs->BytsPerSec * Bs->SecPerClus;
    Volume->FatType         = (DataClusters >= 65525) ? FAT32 : ((DataClusters < 4085) ? FAT12 : FAT16);

    RootEntries = Bs->RootEntCnt;

    //
    //Read FAT table
    //
    FatPages = EFI_SIZE_TO_PAGES( FatSize );
    
    if ( FatBufferSize < EFI_PAGES_TO_SIZE( FatPages )) {
        Status = (*PeiServices)->AllocatePages( PeiServices, EfiBootServicesData, FatPages, &Allocate );

        if ( EFI_ERROR( Status )) {
            return Status;
        }

        FatBuffer     = (UINT8*)((UINTN)Allocate);
        FatBufferSize = EFI_PAGES_TO_SIZE( FatPages );
    }
    MemSet( FatBuffer, FatBufferSize, 0 );
    Status = ReadDevice( PeiServices, Volume, Volume->FatOffset, FatSize, FatBuffer );
    
    if ( EFI_ERROR( Status )) {
        return Status;
    }

    //
    //Read Root directory
    //
    if ( RootSize == 0 ) {      
        //    
        //in case of FAT32 it will be so at this time
        //
        RootClusters = GetClustersCount( FAT32, Bs->Fat.Fat32.RootClus, &DummyCluster, FALSE );
        RootSize    = RootClusters * Volume->BytesPerCluster;
        RootEntries = RootSize / 32;
    }

    RootPages = EFI_SIZE_TO_PAGES( RootSize );

    if ( RootBufferSize < EFI_PAGES_TO_SIZE( RootPages )) {
        Status = (*PeiServices)->AllocatePages( PeiServices, EfiBootServicesData, RootPages, &Allocate );
        if ( EFI_ERROR( Status )) {
            return Status;
        }

        RootBuffer     = (UINT8*)((UINTN)Allocate);
        RootBufferSize = EFI_PAGES_TO_SIZE( RootPages );
    }
    MemSet( RootBuffer, RootBufferSize, 0 );

    if ( Volume->FatType == FAT32 ) {
        Status = GetFatData( PeiServices, Volume, Bs->Fat.Fat32.RootClus, RootSize, RootBuffer );
    }
    else {
        Status = ReadDevice( PeiServices, Volume, Volume->RootOffset, RootSize, RootBuffer );
    }

    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessFatVolume
//
// Description: 
//  Reads recovery capsule from FAT volume
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  CHAR8 *FileName - recovery capsule file name
//  IN  UINTN *FileSize - pointer to size of provided buffer
//  OUT VOID *Buffer - pointer to buffer to store data
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessFatVolume(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume,
    IN OUT UINTN        *FileSize,
    OUT VOID            *Buffer )
{
    EFI_STATUS           Status;
//    BOOT_SECTOR          Bs;
    UINT32               i;
    UINT32               FirstFileCluster;
    UINTN                NumberOfFiles;

    Status = ReadDevice( PeiServices, Volume, 0, 512, &MemBlk->Bs );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    if (!IsFat( &MemBlk->Bs )) {
        return EFI_NOT_FOUND;
    }

    Status = GetFatType( PeiServices, Volume, &MemBlk->Bs );
#if SEARCH_FAT_PATH
    ThisVolume = Volume; // Save volume info for path search
#endif

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    GetFileListFromFatVolume((DIR_ENTRY*)RootBuffer, RootEntries, &NumberOfFiles, FatRecoveryFiles);
    //
    if ( NumberOfFiles == 0 )
        return EFI_NOT_FOUND;

    for(i = 0; i < NumberOfFiles; i++) {
        if ( *FileSize < FatRecoveryFiles[i]->FileSize )
            continue;

        FirstFileCluster = (FatRecoveryFiles[i]->FirstClusterHi << 16) + FatRecoveryFiles[i]->FirstClusterLo;

        Status = GetFatData( PeiServices, Volume, FirstFileCluster, FatRecoveryFiles[i]->FileSize, Buffer );
        if(EFI_ERROR(Status))
            continue;

        if(IsValidFile(Buffer, FatRecoveryFiles[i]->FileSize)) {
            *FileSize = FatRecoveryFiles[i]->FileSize;
            return EFI_SUCCESS;
        }
    }
    return EFI_NOT_FOUND;
}

#if NTFS_RECOVERY_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetRunListElementData
//
// Description: (NTFS) Retrieves the count and cluster of a run from a run list element
//
// Parameters:  UINT8   **pRunList - Pointer to the run list, updated if
//                                   UpdateList is TRUE.
//              UINT64  *ClusterCount - Length of this run in clusters.
//              UINT64  *Cluster - Starting cluster of this run.
//              BOOLEAN UpdateList - Update list pointer to next element if TRUE.
//
// Return value: EFI_STATUS Status (EFI_SUCCESS or EFI_END_OF_FILE)
//
// Modified:
//
// Referral(s):
//
// NOTE(S):     A run list element has 3 parts -- a size byte, a Cluster
//              count, and a Cluster Number.
//              The low nibble of the size byte is the size of the Count
//              in bytes. The high nibble is the size of the Offset in
//              bytes. The element is therefore 1 + (low nibble) + (high
//              nibble) bytes long.
//              The cluster number is a signed number. The new cluster is
//              added to the old one to get the result. So if the new
//              cluster lies before the old one on the disk, it will be
//              a negative number.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetRunListElementData (
    UINT8   **pRunList,
    UINT64  *ClusterCount,
    UINT64  *Cluster,
    BOOLEAN UpdateList
    )
{
    UINT64 TempCount = 0;
    UINT64 TempCluster = 0;
    UINT64 LeftFill = 0;
    UINT8  LowNibble;
    UINT8  HighNibble;
    UINT8  i, HighByte;
    UINT8  *RunListPtr;

//
// If the size byte is 0, we have reached the end of the file.
//    
    RunListPtr = *pRunList;
    if (RunListPtr[0] == 0)
    {
        return EFI_END_OF_FILE;
    }

    LowNibble = RunListPtr[0] & 0xF;
    HighNibble = RunListPtr[0] >> 4;
    RunListPtr++;
//
// Get run length.
//    
    for (i=LowNibble; i>0; i--)
    {
        TempCount = Shl64(TempCount, 8);
        TempCount += RunListPtr[i-1];
    }
    RunListPtr += LowNibble;
//
// Get the run offset.
//    
    HighByte = RunListPtr[HighNibble-1];
    for (i=HighNibble; i>0; i--)
    {
        TempCluster = Shl64(TempCluster, 8);
        TempCluster += RunListPtr[i-1];
    }
    RunListPtr += HighNibble;
//
// If the offset is negative, left-fill the empty bytes with 0xFF.
//    
    if ((HighByte & 0x80) && (HighNibble < 8)) 
    {
        for (i=8; i>HighNibble; i--)
        {
            LeftFill = Shr64(LeftFill, 8);
            LeftFill |= 0xFF00000000000000;
        }
        TempCluster |= LeftFill;
    }

    *Cluster += TempCluster;
    *ClusterCount = TempCount;
    if (UpdateList) *pRunList = RunListPtr;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetFrAttribute
//
// Description: (NTFS) Retrieves a File Record Attribute by it's number from a
//              File Record.
//
// Parameters:  UINT8   *BufferIn - Pointer to a buffer containing a file record
//              UINT8   AttributeNumber - Number of the attribute to retrieve
//              UINTN   **BufferOut - Points to the attribute in the buffer
//
// Return value: EFI_STATUS Status (EFI_SUCCESS or EFI_NOT_FOUND)
//
// Modified:
//
// Referral(s):
//
// Note(s):     Attributes are in sequential order, so, for example,
//              if we're looking for 30, and we find 10 and then 40,
//              we know there is no 30 in the record.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetFrAttribute (
    UINT8 *BufferIn,
    UINT8 AttributeNumber,
    UINT8 **BufferOut
    )
{
    UINT8   *TempBuffer;

    TempBuffer = BufferIn;

//    
// Point to 1st attribute.
//    
    TempBuffer += ((MFT_FILE_RECORD*)TempBuffer)->FR_AttributeOffset; 
//
// Search for the attribute.
//    
    while (TempBuffer[0] != AttributeNumber)
    {
        if (TempBuffer[0] > AttributeNumber) return EFI_NOT_FOUND;
        if (TempBuffer[0] == 0xFF) return EFI_NOT_FOUND;
        if ( ((FR_ATTR_HEADER_RES*)TempBuffer)->AHR_Length == 0 )
            return EFI_NOT_FOUND;
        TempBuffer += ((FR_ATTR_HEADER_RES*)TempBuffer)->AHR_Length;
    }

    *BufferOut = TempBuffer;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetFileRecord
//
// Description: (NTFS) Returns the file record specified by MFTRecordNo in a buffer.
//
// Parameters:  VOLUME_INFO *Vi - Volume Info Structure
//              BOOT_SECTOR *Bs - Boot sector structure
//              UINT64 MFTRecordNo - MFT Record number to get
//              UINT8 *Buffer - Buffer to read record into
//              UINT64 *MFTSector - Sector where record found
//
// Return value: EFI_STATUS Status (EFI_SUCCESS or EFI_NOT_FOUND)
//
// Modified:
//
// Referral(s):
//
// NOTE(S):     The File Records in the Master File Table are numbered
//              sequentially. We just have to count our way through the
//              MFT's run list until we find it.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetFileRecord (
    EFI_PEI_SERVICES **PeiServices,
    RC_VOL_INFO      *Volume,
    BOOT_SECTOR      *Bs,
    UINT64           MFTRecordNo,
    UINT8            *FrBuffer,
    UINT64           *MFTSector OPTIONAL
    )
{
    EFI_STATUS Status;
    UINT8      *pRunList;
    UINT64     Cluster;
    UINT64     Sector;
    UINT64     Count;
    UINT64     ByteCount;
    UINT32     SecPerRecord = 1;
    UINT64     RecordCount;
    UINT32     BytesPerCluster;
    UINT64     Offset;
    UINT32     RecordSize;

    Cluster = 0;
    pRunList = &MemBlk->MFTRunList[0];

    MFTRecordNo &= MAXIMUM_RECORD_NUMBER; // Isolate number part

    Status = GetRunListElementData(&pRunList, &Count, &Cluster, TRUE);
    BytesPerCluster = Bs->BytsPerSec * Bs->SecPerClus;
    ByteCount = Mul64(Count, BytesPerCluster);
    if ( Bs->BytsPerSec <= FILE_RECORD_SIZE ) {
        SecPerRecord = FILE_RECORD_SIZE / Bs->BytsPerSec;
        RecordSize = FILE_RECORD_SIZE;
    } else { // Special case for 4k sectors
        SecPerRecord = 1;
        RecordSize = (UINT32)Bs->BytsPerSec;
    }
//###DEBUG CHANGE NEEDED LATER ////
// In NTFS, the cluster size can be 512 bytes to 4096 bytes.
// File records are 1024 bytes
// For now, we're going to assume a cluster size of 1024 bytes or more.
////////////////////////////

    Sector = Mul64(Cluster, Bs->SecPerClus);
    RecordCount = 0;
    do {
        if (ByteCount > 0)
        {
            Sector += SecPerRecord; 
            ByteCount -= RecordSize;
        } else { // We've used up a run, read from the next one.
            Status = GetRunListElementData(&pRunList, &Count, &Cluster, TRUE);
            if (EFI_ERROR(Status)) return EFI_NOT_FOUND;
            ByteCount = Mul64(Count, BytesPerCluster);
            Sector = Mul64(Cluster, Bs->SecPerClus);
            continue;
        }
        RecordCount++;
    } while (RecordCount < MFTRecordNo); // Record numbers are 0-based.
//
// We found the sector of the file record wanted. Now read it.
//
    Offset = Mul64( Sector, Bs->BytsPerSec );
    Status = ReadDevice( PeiServices, Volume, Offset, RecordSize, FrBuffer );
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;
//
// A File recored begins with "FILE". Check it.
//
    if ( (FrBuffer[0] != 0x46) || \
         (FrBuffer[1] != 0x49) || \
         (FrBuffer[2] != 0x4C) || \
         (FrBuffer[3] != 0x45) ) return EFI_NOT_FOUND;

    *MFTSector = Sector; // Return sector where the record was found
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadNTFSFile
//
// Description: 
//  Reads a file from a device formatted in NTFS.
//
// Input:       
// Parameters:  VOLUME_INFO *Vi - Volume Info Structure
//              BOOT_SECTOR *Bs - Boot sector structure
//              UINT8       *RunList - Run List of file to read
//              VIOD        *Buffer - Buffer to read into
//              UINT64      *Size - Size of file to read
//
// Output:      
//  EFI_STATUS - possible return values 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadNTFSFile( 
    IN EFI_PEI_SERVICES **PeiServices,
    RC_VOL_INFO         *Volume, 
    BOOT_SECTOR         *Bs, 
    UINT8               *RunList, 
    VOID                *Buffer, 
    UINT64              *Size )
{
    UINT64      TotalContiguousBytes;
    UINT64      TotalBytesRead = 0;
    UINT64      AbsByte;
    UINT64      AccessBytes;
    UINT64      ClusterCount;
    UINT64      Cluster = 0;
    EFI_STATUS  Status;

    Status = GetRunListElementData(&RunList, &ClusterCount,
                                       &Cluster, TRUE);
    do {
        TotalContiguousBytes = Mul64(ClusterCount,
                                     Bs->SecPerClus);
        TotalContiguousBytes = Mul64(TotalContiguousBytes,
                                     Bs->BytsPerSec);
        if ( TotalContiguousBytes > *Size) AccessBytes = *Size;

        else AccessBytes = TotalContiguousBytes;

        AbsByte = Mul64( Cluster, Bs->SecPerClus );
        AbsByte = Mul64( AbsByte, Bs->BytsPerSec );

        if (AccessBytes == 0) {
            return EFI_VOLUME_CORRUPTED; // Will happen if early EOF.
        }

        Status = ReadDevice( PeiServices, 
                             Volume, 
                             AbsByte, 
                             (UINTN)AccessBytes, 
                             Buffer );

        if (EFI_ERROR(Status)) {
            break;
        }

        (UINT8 *)Buffer += AccessBytes;
        TotalBytesRead +=AccessBytes;

        *Size   -= AccessBytes; 

        if (AccessBytes == TotalContiguousBytes)
        {
            Status = GetRunListElementData (&RunList, &ClusterCount,
                                            &Cluster, TRUE);
            if (EFI_ERROR(Status)) break; // Error here means EOF.
        }

    } while (*Size);

    *Size = (UINT32)TotalBytesRead;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadNTFSRoot
//
// Description: 
//  Prepares given volume for read operations. Reads NTFS root directory.
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  BOOT_SECTOR *Bs - pointer to MBR
//
// Output:      
//  EFI_STATUS - possible return values 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadNTFSRoot(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume,
    IN BOOT_SECTOR      *Bs )
{
    UINT8       FrBuffer[FILE_RECORD_SIZE]; // This needs to be 4096 for 4k secs.
    UINT8       *Buffer2;
    UINT8       *Buffer3;
    UINT8       *pRunList;
    EFI_STATUS  Status;
    UINT64      TotalSectors;
    UINT64      DataSectors;
    UINT64      Temp64;
    UINT32      Temp32;
    UINT16      Temp16;
    UINT32      IndexSize;
    UINT64      Cluster = 0;
    UINT64      ClusterCount;
    UINT64      TmpRootSize;
    UINTN       RootPages;
    EFI_PHYSICAL_ADDRESS Allocate;

    TotalSectors = Bs->Fat.Ntfs.TotSec64;
    DataSectors  = TotalSectors - Bs->RsvdSecCnt;

    Temp64 = Mul64( Bs->Fat.Ntfs.MFTClus, Bs->SecPerClus );
    Volume->FatOffset = Mul64( Temp64, Bs->BytsPerSec ); // For NTFS, FatOffset is MFT Offset

    //
    // Read the first file record of the MFT, to get the MFT run list.
    //
    Status = ReadDevice( PeiServices, Volume, Volume->FatOffset, FILE_RECORD_SIZE, FrBuffer );
    if ( EFI_ERROR( Status )) {
        return Status;
    }
    Buffer2 = &FrBuffer[0];
    Status = GetFrAttribute( Buffer2, FR_ATTRIBUTE_DATA, &Buffer2 ); // Get data attribute
    if ( EFI_ERROR( Status )) {
        return Status;
    }
    Buffer2 += ((FR_ATTR_HEADER_NONRES*)Buffer2)->AHNR_RunOffset; // Point to run list
    MemCpy( MemBlk->MFTRunList, Buffer2, 256 ); // Copy MFT run list
    //
    // Get the root directory file record, to get its run list.
    //
    Buffer2 = &FrBuffer[0];
    Status = GetFileRecord( PeiServices, Volume, Bs, 5, Buffer2, NULL ); // Root is always record no. 5
    if ( EFI_ERROR( Status )) {
        return Status;
    }
    //
    // Check for a resident index. It will be in the Index Root Attribute.
    // If one if found, it will be saved for searching later.
    //
    ResidentPresent = FALSE;
    Buffer3 = Buffer2;
    Status = GetFrAttribute( Buffer2, FR_ATTRIBUTE_INDEX_ROOT, &Buffer3 );
    if ( Status == EFI_SUCCESS) { // Root Attribute found
        Temp16 = ((FR_ATTR_HEADER_RES*)Buffer3)->AHR_InfoOffset;
        Buffer3 += Temp16;
        IndexSize = ((FR_INDEX_ROOT_ATTRIBUTE*)Buffer3)->IRA_TotalSize;
        Temp32 = ((FR_INDEX_ROOT_ATTRIBUTE*)Buffer3)->IRA_Offset;
        Buffer3 += Temp32 + EFI_FIELD_OFFSET(FR_INDEX_ROOT_ATTRIBUTE, IRA_Offset);
        if (IndexSize >= MINIMUM_ENTRY_SIZE) { // Resident index is not empty
            MemCpy ( MemBlk->ResidentIndex, Buffer3, IndexSize );
            ResidentPresent = TRUE;
            ResidentSize = IndexSize;
        }
    }
    //
    // Now, check for a non-resident index.
    //
    Status = GetFrAttribute( Buffer2, FR_ATTRIBUTE_INDEX_ALLOC, &Buffer2 );
    if ( EFI_ERROR( Status )) {
        return Status;
    }
    Buffer2 += ((FR_ATTR_HEADER_NONRES*)Buffer2)->AHNR_RunOffset; // Point to run list
    MemCpy( MemBlk->RootRunList, Buffer2, 128 ); // Copy Root run list
    //
    // Calculate root directory size by running its run list.
    //
    pRunList = &MemBlk->RootRunList[0];
    TmpRootSize = 0;
    Cluster = 0;
    do {
        Status = GetRunListElementData( &pRunList, &ClusterCount, &Cluster, TRUE );
        if ( Status == EFI_SUCCESS ) TmpRootSize += ClusterCount;
    } while ( Status == EFI_SUCCESS );
    TmpRootSize = Mul64 ( TmpRootSize, Bs->SecPerClus );
    TmpRootSize = Mul64 ( TmpRootSize, Bs->BytsPerSec );

    Buffer2 = &FrBuffer[0];
    RootPages = EFI_SIZE_TO_PAGES( TmpRootSize );
    Status = (*PeiServices)->AllocatePages( PeiServices, EfiBootServicesData, RootPages, &Allocate );
    if ( EFI_ERROR( Status )) {
        return Status;
    }
    RootBuffer     = (UINT8*)((UINTN)Allocate);
    RootBufferSize = EFI_PAGES_TO_SIZE( RootPages );
    MemSet( RootBuffer, RootBufferSize, 0 );
    
    pRunList = &MemBlk->RootRunList[0];
    Status = ReadNTFSFile( PeiServices, Volume, Bs, pRunList, RootBuffer, &TmpRootSize );
    RootSize = (UINT32)TmpRootSize;

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessNTFSVolume
//
// Description: 
//  Reads recovery capsule from NTFS volume
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  CHAR8 *FileName - recovery capsule file name
//  IN  UINTN *FileSize - pointer to size of provided buffer
//  OUT VOID *Buffer - pointer to buffer to store data
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessNTFSVolume(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume,
    IN OUT UINTN        *FileSize,
    OUT VOID            *Buffer )
{
    EFI_STATUS           Status;
//    BOOT_SECTOR          Bs;
    UINT32               i;
    UINTN               NumberOfFiles;
    UINT64              MFTRecord;
    UINT8               *TmpBuffer;
    UINT8               *pRunList;
    UINT64              TmpFileSize;

    Status = ReadDevice( PeiServices, Volume, 0, 512, &MemBlk->Bs );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    if (!IsNtfs( &MemBlk->Bs )) {
        return EFI_NOT_FOUND;
    }

    Status = ReadNTFSRoot( PeiServices, Volume, &MemBlk->Bs );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    GetFileListFromNtfsVolume((UINT8*)RootBuffer, RootSize, &NumberOfFiles, NtfsRecoveryFiles);

    if ( NumberOfFiles == 0 )
        return EFI_NOT_FOUND;

    for(i = 0; i < NumberOfFiles; i++) {
        if ( *FileSize < NtfsRecoveryFiles[i]->INDE_RealSize )
            continue;

        TmpBuffer = (UINT8*)Buffer;
        TmpFileSize = NtfsRecoveryFiles[i]->INDE_RealSize;
        //
        // Get the file's MFT record number, and from that it's run list
        //
        MFTRecord = NtfsRecoveryFiles[i]->INDE_MFTRecord & MAXIMUM_RECORD_NUMBER;
        Status = GetFileRecord( PeiServices, Volume, &MemBlk->Bs, MFTRecord, TmpBuffer, NULL );
        Status = GetFrAttribute( TmpBuffer, FR_ATTRIBUTE_DATA, &TmpBuffer );
        if ( EFI_ERROR( Status )) {
            return Status;
        }
        TmpBuffer += ((FR_ATTR_HEADER_NONRES*)TmpBuffer)->AHNR_RunOffset; // Point to run list
        MemCpy( MemBlk->RootRunList, TmpBuffer, 128 ); // Copy the file's run list
        //
        // Read the file into the provided buffer
        //
        pRunList = &MemBlk->RootRunList[0];
        Status = ReadNTFSFile( PeiServices, Volume, &MemBlk->Bs, pRunList, Buffer, &TmpFileSize );
        if ( EFI_ERROR( Status )) {
            return Status;
        }

        if(IsValidFile(Buffer, (UINTN)TmpFileSize)) {
            *FileSize = (UINTN)TmpFileSize;
            return EFI_SUCCESS;
        }
    }
    return EFI_NOT_FOUND;
}
#endif

#if EXT_RECOVERY_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetNextBlock
//
// Description: (EXT) Retrieves the next block number from an Inode
//              block list.
//
// Parameters:  VOLUME_INFO *Vi - Volume Info Structure
//              VOLUME_SB   *Sb - Superblock structure
//              VOLUME_IT   *Inode - Inode table structure
//              UINT32  *BlockNo - Sequential number of the block
//              UINT32  *Block - Next block of the file
//              BOOLEAN UpdateList - Update block no. to next block if TRUE.
//
// Return value: EFI_STATUS Status (EFI_SUCCESS or EFI_END_OF_FILE)
//
// Modified:
//
// Referral(s):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetNextBlock(
    EFI_PEI_SERVICES **PeiServices,
    RC_VOL_INFO      *Volume,
    VOLUME_SB        *Sb,
    VOLUME_IT        *Inode,
    UINT32           *BlockNo,
    UINT32           *Block,
    BOOLEAN          UpdateList )
{
    UINT32      *BlockListPtr;
    UINT32      TmpBlock;
    UINT32      TmpBlock2;
    UINT32      TmpBlkNo;
    UINT32      IBlkCnt;
    UINT64      Offset;
    UINT32      BlockSize;
    UINT32      NosPerBlock;
    UINTN       BlockPages;
    EFI_STATUS  Status;
    EFI_PHYSICAL_ADDRESS Allocate;

    BlockSize = 1024 << Sb->SB_BlockSize;
    NosPerBlock = BlockSize / 4;
    TmpBlkNo = *BlockNo;

    // Process direct blocks (0-11)
    if ((TmpBlkNo < 12) && (Indirect == 0))
    {
        BlockListPtr = &Inode->Alloc.Ext2.Blocks[0];
        *Block = BlockListPtr[TmpBlkNo];
    }

    // Process single indirect blocks (12-(256+11))
    if ((TmpBlkNo >= 12) && (TmpBlkNo < NosPerBlock+12) && (Indirect != 1))
    {
        Indirect = 1;
        TmpBlock = Inode->Alloc.Ext2.Blocks[12];
        Offset = Mul64(TmpBlock, BlockSize);
        ReadDevice (PeiServices, Volume, Offset, BlockSize, &BlockList[0]);
    }

    if ((TmpBlkNo >= 12) && (TmpBlkNo < NosPerBlock+12) && (Indirect == 1))
    {
        BlockPages = EFI_SIZE_TO_PAGES( BlockSize );
        Status = (*PeiServices)->AllocatePages( PeiServices, EfiBootServicesData, BlockPages, &Allocate );
        if ( EFI_ERROR( Status )) {
            return EFI_END_OF_FILE;
        }
        BlockList = (UINT32*)((UINTN)Allocate);
    
        BlockListPtr = &BlockList[0];
        TmpBlock = TmpBlkNo - 12;
        *Block = BlockListPtr[TmpBlock];
    }

    // Process double indirect blocks ((256+12)-(65536+256+11))
    if ((TmpBlkNo >= (NosPerBlock+12)) && (Indirect != 2))
    {
        Indirect = 2;
        BlockPages = EFI_SIZE_TO_PAGES( BlockSize );
        Status = (*PeiServices)->AllocatePages( PeiServices, EfiBootServicesData, BlockPages, &Allocate );
        if ( EFI_ERROR( Status )) {
            return EFI_END_OF_FILE;
        }
        BlockList2 = (UINT32*)((UINTN)Allocate);
    
        TmpBlock = Inode->Alloc.Ext2.Blocks[13];
        Offset = Mul64(TmpBlock, BlockSize);
        ReadDevice (PeiServices, Volume, Offset, BlockSize, &BlockList[0]);
    }

    if ((TmpBlkNo >= (NosPerBlock+12)) && (Indirect == 2))
    {
        TmpBlock = TmpBlkNo - 12;
        IBlkCnt = TmpBlock / NosPerBlock;
        if (TmpBlock % NosPerBlock == 0)
        {
            // Read another set of nos. into BlockList2
            TmpBlock2 = BlockList[IBlkCnt];
            Offset = Mul64(TmpBlock2, BlockSize);
            ReadDevice (PeiServices, Volume, Offset, BlockSize, &BlockList2[0]);
            BlockListPtr = &BlockList2[0];
        }
        TmpBlock -= (NosPerBlock * IBlkCnt);
        *Block = BlockListPtr[TmpBlock];
    }

    if (UpdateList)
    {
        TmpBlkNo++;
        *BlockNo = TmpBlkNo;
    }
    if (*Block == 0)
    {
        return EFI_END_OF_FILE;
    } else {
        return EFI_SUCCESS;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadExtFile
//
// Description: 
//  Reads a file from a device formatted in Ext(n).
//
// Input:       
// Parameters:  VOLUME_INFO *Vi - Volume Info Structure
//              VOLUME_SB   *Sb - Superblock structure
//              VOLUME_IT   *Inode - Inode table structure
//              VIOD        *Buffer - Buffer to read into
//              UINT64      *Size - Size of file to read
//
// Output:      
//  EFI_STATUS - possible return values 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadExtFile( 
    IN EFI_PEI_SERVICES **PeiServices,
    RC_VOL_INFO         *Volume, 
    VOLUME_SB           *Sb, 
    VOLUME_IT           *Inode, 
    VOID                *Buffer, 
    UINT64              *Size )
{
    EFI_STATUS  Status;
    UINT32      BlockSize;
    UINT32      Block;
    UINT32      BlockNo;
    UINT64      Offset;
    UINT64      TotalBytesRead = 0;
    UINT16      ExtentCount;
    UINT64      BigBlock;
    UINT32      ReadSize;
    UINT16      i;

    BlockSize = 1024 << Sb->SB_BlockSize;
    BlockNo = 0;

    //
    // Check for which allocation method to use for reading the file
    //
    if ((Inode->Alloc.Ext4.Header.EH_Magic == 0xF30A) && \
        (Inode->Alloc.Ext4.Header.EH_Max == 4))
    {
    //
    // Use the EXT4 allocation method
    //
        ExtentCount = Inode->Alloc.Ext4.Header.EH_Extents;

        for (i=0; i<ExtentCount; i++)
        {
            BigBlock = Inode->Alloc.Ext4.Extent[i].EE_BlockLo + \
                       Shl64(Inode->Alloc.Ext4.Extent[i].EE_BlockHi, 0x20);
            Offset = Mul64(BigBlock, BlockSize);
            ReadSize = BlockSize * Inode->Alloc.Ext4.Extent[i].EE_Length;
            if (*Size <= ReadSize)
            {
                Status = ReadDevice (PeiServices, Volume, Offset, (UINTN)*Size, Buffer);
                if (EFI_ERROR(Status)) {
                    *Size = TotalBytesRead;
                    return Status;
                } else {
                    TotalBytesRead += *Size;
                    *Size = TotalBytesRead;
                    return EFI_SUCCESS;
                }
            }

            Status = ReadDevice (PeiServices, Volume, Offset, ReadSize, Buffer);
            if (EFI_ERROR(Status)) return Status;
            *Size -= ReadSize;
            TotalBytesRead += ReadSize;
        } // End of read loop

        return EFI_VOLUME_CORRUPTED; // Shouldn't get here

    } else {
    //
    // Use the EXT2, EXT3 allocation method
    //
        Status = GetNextBlock ( PeiServices,
                                Volume,
                                Sb,
                                Inode,
                                &BlockNo,
                                &Block,
                                TRUE );
        if (EFI_ERROR(Status)) // Zero-length file
        {
            *Size = 0;
            return Status;
        }

        do
        {
            Offset = Mul64 (BlockSize, Block);

            if (*Size <= BlockSize)
            {
                Status = ReadDevice (PeiServices, Volume, Offset, (UINTN)*Size, Buffer);
                if (EFI_ERROR(Status)) {
                    *Size = TotalBytesRead;
                    return Status;
                } else {
                    TotalBytesRead += *Size;
                    *Size = TotalBytesRead;
                    return EFI_SUCCESS;
                }
            }

            Status = ReadDevice (PeiServices, Volume, Offset, BlockSize, Buffer);
            if (EFI_ERROR(Status)) return Status;
            *Size -= BlockSize;
            TotalBytesRead += BlockSize;

            Status = GetNextBlock ( PeiServices,
                                    Volume,
                                    Sb,
                                    Inode,
                                    &BlockNo,
                                    &Block,
                                    TRUE );
            if (EFI_ERROR(Status)) // EOF found
            {
                *Size = TotalBytesRead;
                return EFI_SUCCESS;
            }
        }
        while (*Size);

        return EFI_VOLUME_CORRUPTED; // Shouldn't get here
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadExtRoot
//
// Description: 
//  Prepares given volume for read operations. Reads Ext(n) root directory.
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  VOLUME_SB *Sb - pointer to Superblock
//
// Output:      
//  EFI_STATUS - possible return values 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadExtRoot(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume,
    IN VOLUME_SB        *Sb )
{
    EFI_STATUS          Status;
    UINT32              BlockSize;
    UINT16              InodeSize;
    UINT32              BgdtBlock;
    VOLUME_BGDT         Bgdt;
//    VOLUME_IT           RootInode;
    UINT64              Offset;
    UINT64              TmpRootSize;
    UINTN               RootPages;
    EFI_PHYSICAL_ADDRESS Allocate;

    BlockSize = 1024 << Sb->SB_BlockSize;
    if (BlockSize == 1024)
    {
        BgdtBlock = 2;
    } else {
        BgdtBlock = 1;
    }

    // Read in the Block Group Descriptor Table
    Offset = Mul64(BlockSize, BgdtBlock);
    Status = ReadDevice (PeiServices, 
                         Volume, 
                         Offset, 
                         sizeof(VOLUME_BGDT), 
                         &Bgdt);
    if (EFI_ERROR(Status))
    {
        return EFI_NOT_FOUND;
    }

    InodeBlock = Bgdt.BGDT_InodeTableBlk;
    InodeSize = Sb->SB_InodeStrucSize;

    // The root directory's inode is always the 2nd inode in the
    // inode table. Read in that inode.
    Offset = Mul64(BlockSize, InodeBlock) + InodeSize;
    Status = ReadDevice (PeiServices, 
                         Volume, 
                         Offset, 
                         sizeof(VOLUME_IT), 
                         &MemBlk->RootInode);
    if (EFI_ERROR(Status))
    {
        return EFI_NOT_FOUND;
    }

    TmpRootSize = MemBlk->RootInode.IT_SizeLo + Shl64(MemBlk->RootInode.IT_SizeHi, 0x20);

    RootPages = EFI_SIZE_TO_PAGES( TmpRootSize );
    Status = (*PeiServices)->AllocatePages( PeiServices, EfiBootServicesData, RootPages, &Allocate );
    if ( EFI_ERROR( Status )) {
        return Status;
    }
    RootBuffer     = (UINT8*)((UINTN)Allocate);
    RootBufferSize = EFI_PAGES_TO_SIZE( RootPages );
    MemSet( RootBuffer, RootBufferSize, 0 );
    
    Status = ReadExtFile( PeiServices, 
                          Volume, 
                          Sb, 
                          &MemBlk->RootInode, 
                          RootBuffer, 
                          &TmpRootSize );
    RootSize = (UINT32)TmpRootSize;

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessExtVolume
//
// Description: 
//  Reads recovery capsule from Ext(n) volume
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  CHAR8 *FileName - recovery capsule file name
//  IN  UINTN *FileSize - pointer to size of provided buffer
//  OUT VOID *Buffer - pointer to buffer to store data
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessExtVolume(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume,
    IN OUT UINTN        *FileSize,
    OUT VOID            *Buffer )
{
    EFI_STATUS          Status;
//    VOLUME_SB           Sb;
//    VOLUME_IT           FileInode;
    UINT32              i;
    UINT32              Inode;
    UINT64              TmpFileSize;
    UINTN               NumberOfFiles;
    UINT64              Offset;
    UINT32              BlockSize;
    UINT16              InodeSize;
    UINT8               *TmpPtr;

    Status = ReadDevice( PeiServices, Volume, 0, 512, &MemBlk->Sb );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    // On an EXT(n) volume, the first sector will be all zeros
    TmpPtr = (UINT8*)&MemBlk->Sb.SB_TotalInodes;
    for (i=0; i<512; i++)
    {
        if ((UINT8)TmpPtr[i] != 0)
        {
            return EFI_NOT_FOUND; // Not an EXT(n) volume
        }
    }

    // The Superblock is always 1024 bytes in on the volume
    Status = ReadDevice( PeiServices, Volume, 1024, 512, &MemBlk->Sb );

    if (!IsExt( &MemBlk->Sb )) {
        return EFI_NOT_FOUND;
    }

    Status = ReadExtRoot( PeiServices, Volume, &MemBlk->Sb );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    GetFileListFromExtVolume((UINT8*)RootBuffer, RootSize, &NumberOfFiles, ExtRecoveryFiles);

    if ( NumberOfFiles == 0 )
        return EFI_NOT_FOUND;

    BlockSize = 1024 << MemBlk->Sb.SB_BlockSize;
    InodeSize = MemBlk->Sb.SB_InodeStrucSize;
    for(i = 0; i < NumberOfFiles; i++) {
        // An EXT(n) directory  entry only contains the name and inode, so we have to
        // read the inode to get the size.
        Inode = ExtRecoveryFiles[i]->DIR_Inode;
        Offset = Mul64(BlockSize, InodeBlock) + \
                 Mul64((Inode-1), InodeSize);
        Status = ReadDevice (PeiServices, 
                             Volume, 
                             Offset, 
                             sizeof(VOLUME_IT), 
                             &MemBlk->FileInode);
        if (EFI_ERROR(Status)) continue;

        TmpFileSize = MemBlk->FileInode.IT_SizeLo + Shl64(MemBlk->FileInode.IT_SizeHi, 0x20);
        if ( *FileSize < (UINTN)TmpFileSize )
            continue;
        Status = ReadExtFile( PeiServices, 
                              Volume, 
                              &MemBlk->Sb, 
                              &MemBlk->FileInode, 
                              Buffer, 
                              &TmpFileSize );
        if ( EFI_ERROR( Status )) {
            return Status;
        }

        if(IsValidFile(Buffer, (UINTN)TmpFileSize)) {
            *FileSize = (UINTN)TmpFileSize;
            return EFI_SUCCESS;
        }
    }
    return EFI_NOT_FOUND;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindNextPartition
//
// Description:
//  Finds the next partition on the volume, and sets the VolumeOffset in
//  the RC_VOL_INFO structure. 
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//
// Output:      
//  EFI_STATUS
//
// Note:
//  This function uses the following global variables:
//  UINTN PartCount - Counter to keep track of search
//  BOOLEAN IsMbr - True if looking for MBR partitions
//  UINT32 GpeCount - GUID Partition Entry count
//  UINT32 PartSector - Starting sector of partition
//  PartCount and PartSector must be seeded to 0, and IsMbr must be
//  seeded to TRUE before the first call.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindNextPartition(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume )
{
    EFI_STATUS          Status;
    UINT64              Offset;
    GUID_BOOT_RECORD    *Gbr;
    GUID_TABLE_HEADER   *Gth;
    UINT32              GpeSize;
    UINT32              i;
    UINT32              TempSector;

    //
    // Check for MBR partitions
    //
    if ( IsMbr ) {
        while ( PartCount < 4 ) {
            if ( MemBlk->Mbr.PartRec[PartCount].OSType == 0xEE ) {
                IsMbr = FALSE; // Mark GUID partition found
                PartCount = 0; // Reset counter
                break;
            }

            if ( MemBlk->Mbr.PartRec[PartCount].OSType == 5
                 || MemBlk->Mbr.PartRec[PartCount].OSType == 15 ) { // Extended partition
                PartSector += MemBlk->Mbr.PartRec[PartCount].StartingLba;
                Volume->PartitionOffset = Mul64( 512, PartSector );
                Status = ReadDevice( PeiServices, Volume, 0, 512, &MemBlk->Mbr );
                if ( EFI_ERROR( Status )) {
                    return Status;
                }
                PartCount = 0;
            }

            if ( MemBlk->Mbr.PartRec[PartCount].OSType == 0
                 || MemBlk->Mbr.PartRec[PartCount].SizeInLba == 0
                 || MemBlk->Mbr.PartRec[PartCount].StartingLba == 0 ) {
                PartCount++; // Check next partition
                continue;
            }

            TempSector = MemBlk->Mbr.PartRec[PartCount].StartingLba + PartSector;
            Volume->PartitionOffset = Mul64( 512, TempSector );
            PartCount++;
            return EFI_SUCCESS;
        }
    }
    if ( IsMbr ) return EFI_NOT_FOUND; // No MBR partitions were found

    //
    // Check for GUID partitions
    //
    if ( PartCount == 0 ) {
        Offset = Mul64( 1, Volume->BlockSize ); 
        Status = ReadDevice( PeiServices, Volume, Offset, 512, &MemBlk->Mbr );
        if ( EFI_ERROR( Status )) {
            return Status;
        }
        Gth = (GUID_TABLE_HEADER*)&MemBlk->Mbr.BootCode[0];
        if ( (Gth->Signature[0] == 0x45) && // Check for "EFI"
             (Gth->Signature[1] == 0x46) &&
             (Gth->Signature[2] == 0x49) )
        {
            GpeCount = Gth->EntryCount;
            GpeSize = Gth->EntrySize;
            //
            // We only support entry size of 128 for now.
            //
            if ( GpeSize != 128 ) return EFI_NOT_FOUND; // 
            Offset = Mul64( 2, Volume->BlockSize );
            //
            // Read in the first entry in the partition table
            //
            Status = ReadDevice( PeiServices, Volume, Offset, 512, &MemBlk->Mbr );
            if ( EFI_ERROR( Status )) {
                return Status;
            }
        } else return EFI_NOT_FOUND; // Table header not found.
    }

    while ( PartCount < GpeCount ) {
        i = PartCount % 4;
        if ( (i == 0) && (PartCount != 0) ) {
            Offset = Mul64( 2+(PartCount/4), Volume->BlockSize );
            Volume->PartitionOffset = 0; // Reset this to zero
            Status = ReadDevice( PeiServices, Volume, Offset, 512, &MemBlk->Mbr );
            if ( EFI_ERROR( Status )) {
                return Status;
            }
        }
        PartCount++;
        Gbr = (GUID_BOOT_RECORD*)&MemBlk->Mbr.BootCode[0];
        Volume->PartitionOffset = Mul64( Gbr->GuidPart[i].FirstLba, Volume->BlockSize );
        //
        // The partition count is incremented by 4 for each new Guid Boot Record,
        // even if it does not contain 4 partition records. So we may find an empty
        // partition. Exit with EFI_NOT_FOUND if there is one.
        //
        if ( Volume->PartitionOffset == 0 ) {
            return EFI_NOT_FOUND;
        }
        return EFI_SUCCESS;
    }

    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessFatDevice
//
// Description: 
//  Reads recovery capsule from FAT device. First treat device as 
//  non-partitioned device. If failed tries to discover primary partitions and 
//  search for capsule there.
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  CHAR8 *FileName - recovery capsule file name
//  IN  UINTN *FileSize - pointer to size of provided buffer
//  OUT VOID *Buffer - pointer to buffer to store data
//
// Output:      
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessFatDevice(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume,
    IN OUT UINTN        *FileSize,
    OUT VOID            *Buffer )
{
    EFI_STATUS          Status;
    EFI_STATUS          Status2;

    //
    // Assume the volume is floppy-formatted
    //
    Status = ProcessFatVolume( PeiServices, Volume, FileSize, Buffer );

    if ( !EFI_ERROR( Status )) {
        return Status;
    }

    //
    // Not floppy formatted, look for partitions. Rread sector 0 (MBR).
    //
    Status = ReadDevice( PeiServices, Volume, 0, 512, &MemBlk->Mbr );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    if ( MemBlk->Mbr.Sig != 0xaa55 ) {
        return EFI_NOT_FOUND;
    }

    PartCount = 0;
    PartSector = 0;
    IsMbr = TRUE;

    //
    // Locate all partitions. Check each one for the recovery file.
    // The recovery file will be loaded if it is found, and this
    // function will return EFI_SUCCESS.
    //
    do {
        Status = FindNextPartition( PeiServices, Volume );
        if ( !EFI_ERROR(Status) ) {
            Status2 = ProcessFatVolume( PeiServices, Volume, FileSize, Buffer );
            if ( !EFI_ERROR(Status2) ) {
                return Status2;
            }
        }
    } while (Status == EFI_SUCCESS);

    return EFI_NOT_FOUND;
}

#if NTFS_RECOVERY_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessNTFSDevice
//
// Description: 
//  Reads recovery capsule from NTFS device. Tries to discover primary partitions
//  and search for capsule there.
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  CHAR8 *FileName - recovery capsule file name
//  IN  UINTN *FileSize - pointer to size of provided buffer
//  OUT VOID *Buffer - pointer to buffer to store data
//
// Output:      
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessNTFSDevice(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume,
    IN OUT UINTN        *FileSize,
    OUT VOID            *Buffer )
{
    EFI_STATUS          Status;
    EFI_STATUS          Status2;

    //
    // Assume the volume is floppy-formatted.
    //
    Status = ProcessNTFSVolume( PeiServices, Volume, FileSize, Buffer );

    if ( !EFI_ERROR( Status )) {
        return Status;
    }

    //
    // Not floppy formatted, look for partitions. Read sector 0 (MBR).
    //
    Status = ReadDevice( PeiServices, Volume, 0, 512, &MemBlk->Mbr );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    if ( MemBlk->Mbr.Sig != 0xaa55 ) {
        return EFI_NOT_FOUND;
    }

    PartCount = 0;
    PartSector = 0;
    IsMbr = TRUE;

    //
    // Locate all partitions. Check each one for the recovery file.
    // The recovery file will be loaded if it is found, and this
    // function will return EFI_SUCCESS.
    //
    do {
        Status = FindNextPartition( PeiServices, Volume );
        if ( !EFI_ERROR(Status) ) {
            Status2 = ProcessNTFSVolume( PeiServices, Volume, FileSize, Buffer );
            if ( !EFI_ERROR(Status2) ) {
                return Status2;
            }
        }
    } while (Status == EFI_SUCCESS);

    return EFI_NOT_FOUND;
}
#endif

#if EXT_RECOVERY_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessExtDevice
//
// Description: 
//  Reads recovery capsule from Ext(n) device. Tries to discover primary partitions
//  and search for capsule there.
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  CHAR8 *FileName - recovery capsule file name
//  IN  UINTN *FileSize - pointer to size of provided buffer
//  OUT VOID *Buffer - pointer to buffer to store data
//
// Output:      
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessExtDevice(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume,
    IN OUT UINTN        *FileSize,
    OUT VOID            *Buffer )
{
    EFI_STATUS          Status;
    EFI_STATUS          Status2;

    //
    // Assume the volume is floppy-formatted.
    //
    Status = ProcessExtVolume( PeiServices, Volume, FileSize, Buffer );

    if ( !EFI_ERROR( Status )) {
        return Status;
    }

    //
    // Not floppy formatted, look for partitions. Read sector 0 (MBR).
    //
    Status = ReadDevice( PeiServices, Volume, 0, 512, &MemBlk->Mbr );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    if ( MemBlk->Mbr.Sig != 0xaa55 ) {
        return EFI_NOT_FOUND;
    }

    PartCount = 0;
    PartSector = 0;
    IsMbr = TRUE;

    //
    // Locate all partitions. Check each one for the recovery file.
    // The recovery file will be loaded if it is found, and this
    // function will return EFI_SUCCESS.
    //
    do {
        Status = FindNextPartition( PeiServices, Volume );
        if ( !EFI_ERROR(Status) ) {
            Status2 = ProcessExtVolume( PeiServices, Volume, FileSize, Buffer );
            if ( !EFI_ERROR(Status2) ) {
                return Status2;
            }
        }
    } while (Status == EFI_SUCCESS);

    return EFI_NOT_FOUND;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessPrimaryVolume
//
// Description: 
//  Reads recovery capsule from ISO9660 device
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//  IN  CHAR8 *FileName - recovery capsule file name
//  IN  UINTN *FileSize - pointer to size of provided buffer
//  OUT VOID *Buffer - pointer to buffer to store data
//
// Output:      
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessPrimaryVolume(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume,
    IN OUT UINTN        *FileSize,
    OUT VOID            *Buffer )
{
    EFI_STATUS                Status;
    PRIMARY_VOLUME_DESCRIPTOR PriVol;
    UINT32                    RootSize;
    UINTN                     RootPages;
    EFI_PHYSICAL_ADDRESS      Allocate;
    UINTN                     NumberOfFiles;
    UINT32                    i;

    Volume->PartitionOffset = 0;
    Status = ReadDevice( PeiServices, Volume, 16 * Volume->BlockSize, Volume->BlockSize, &PriVol );

    //
    //check that we read CD
    //
    if ( PriVol.Type != 1 || MemCmp( PriVol.StandardId, "CD001", 5 )) {
        return EFI_NOT_FOUND;
    }

    //
    //read root directory
    //
    RootSize  = PriVol.RootDir.DataLength;
    RootPages = EFI_SIZE_TO_PAGES( RootSize );

    if ( RootBufferSize < EFI_PAGES_TO_SIZE( RootPages )) {
        Status = (*PeiServices)->AllocatePages( PeiServices, EfiBootServicesData, RootPages, &Allocate );

        if ( EFI_ERROR( Status )) {
            return Status;
        }

        RootBuffer     = (UINT8*)((UINTN)Allocate);
        RootBufferSize = EFI_PAGES_TO_SIZE( RootPages );
    }
    MemSet( RootBuffer, RootBufferSize, 0 );

    Status = ReadDevice( PeiServices, Volume, PriVol.RootDir.ExtentOffset * Volume->BlockSize, RootSize, RootBuffer );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    GetFileListFromPrimaryVolume((DIR_RECORD*)RootBuffer, RootSize, &NumberOfFiles, CdRecoveryFiles);

    if(NumberOfFiles == 0)
        return EFI_NOT_FOUND;

    for(i = 0; i < NumberOfFiles; i++) {
        if ( *FileSize < CdRecoveryFiles[i]->DataLength )
            continue;

        Status = ReadDevice( PeiServices, Volume, CdRecoveryFiles[i]->ExtentOffset * Volume->BlockSize, CdRecoveryFiles[i]->DataLength, Buffer );
        if(EFI_ERROR(Status)) 
            continue;

        if(IsValidFile(Buffer, CdRecoveryFiles[i]->DataLength)) {
            *FileSize = CdRecoveryFiles[i]->DataLength;
            return EFI_SUCCESS;
        }
    }
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessCd
//
// Description: 
//  Reads recovery capsule ATAPI device. First search for recovery capsule in
//  primary volume. If not found tries to process Eltorito images
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  OUT RC_VOL_INFO *Volume - pointer to volume description structure
//  CHAR8 *FileName - recovery capsule file name
//  UINTN *FileSize - pointer to size of provided buffer
//  OUT VOID *Buffer - pointer to buffer to store data
//
// Output:      
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessCd(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT RC_VOL_INFO  *Volume,
    IN OUT UINTN        *FileSize,
    OUT VOID            *Buffer )
{
    EFI_STATUS                    Status;
    UINT8                         Data[2048];       //space for 1 block
    BOOT_RECORD_VOLUME_DESCRIPTOR *BootDesc;
    INITIAL_DEFAULT_ENTRY         *Entry;

    Status = ProcessPrimaryVolume( PeiServices, Volume, FileSize, Buffer );

    if ( !EFI_ERROR( Status )) {
        return Status;
    }

    //
    //file not found in primary volume, check Eltorito partitions
    //
    Status = ReadDevice( PeiServices, Volume, 17 * Volume->BlockSize, Volume->BlockSize, Data );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    //
    //check if it is Eltorito
    //
    BootDesc = (BOOT_RECORD_VOLUME_DESCRIPTOR*)Data;

    if ( BootDesc->BootRecordIndicator != 0
         || MemCmp( &(BootDesc->ISO9660Identifier),    "CD001",                   5 )
         || BootDesc->DescriptorVersion != 1
         || MemCmp( &(BootDesc->BootSystemIdentifier), "EL TORITO SPECIFICATION", 23 )) {
        return EFI_NOT_FOUND;
    }

    //
    //it is Eltorito, read boot catalog
    //
    Status = ReadDevice( PeiServices, Volume, BootDesc->BootCatalogFirstSector * Volume->BlockSize, Volume->BlockSize, Data );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    Entry                   = (INITIAL_DEFAULT_ENTRY*) &Data[32];
    Volume->PartitionOffset = Entry->LoadRBA * Volume->BlockSize;
    Status                  = ProcessFatDevice( PeiServices, Volume, FileSize, Buffer );
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FsRecoveryRead
//
// Description: 
//  Search for recovery capsule file on all file system devices
//
// Input:       
//  IN  EFI_PEI_SERVICES **PeiServices - pointer to PEI services
//  IN  CHAR8 *FileName - recovery capsule file name
//  IN UINTN DeviceIndex - device index for given BlockIo PPI
//  IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *pBlockIo - pointer to BlockIo PPI
//  UINTN *FileSize - pointer to size of provided buffer
//  VOID *Buffer - pointer to buffer to store data
//
// Output:      
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FsRecoveryRead(
    IN EFI_PEI_SERVICES              **PeiServices,
    IN UINTN                         DeviceIndex,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *pBlockIo,
    IN OUT UINTN                     *pSize,
    OUT VOID                         *pBuffer )
{
    EFI_STATUS              Status;
    RC_VOL_INFO             Volume;
    EFI_PEI_BLOCK_IO_MEDIA  Media;
    UINTN                   BlockPages;
    EFI_PHYSICAL_ADDRESS    Allocate;

    if ( !pBlockIo || !pSize || *pSize && !pBuffer ) {
        return EFI_INVALID_PARAMETER;
    }

    MemSet( &Volume, sizeof(RC_VOL_INFO), 0 );

    Status = pBlockIo->GetBlockDeviceMediaInfo( PeiServices, pBlockIo, DeviceIndex, &Media );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    if ( !Media.MediaPresent ) {
        return EFI_NOT_FOUND;
    }

    Volume.BlkIo     = pBlockIo;
    Volume.Device    = DeviceIndex;
    Volume.BlockSize = Media.BlockSize;

    //
    // Allocate memory for MBR, Boot Sector, etc.
    //
    BlockPages = EFI_SIZE_TO_PAGES( sizeof(MEMORY_BLOCK) );
    Status = (*PeiServices)->AllocatePages( PeiServices, EfiBootServicesData, BlockPages, &Allocate );
    if ( EFI_ERROR( Status )) {
        return EFI_NOT_FOUND;
    }
    MemBlk = (MEMORY_BLOCK*)((UINTN)Allocate);

    if ( Media.BlockSize == 2048 && CdRecoverySupport ) {
        Volume.PartitionOffset = 0;
        Status = ProcessCd( PeiServices, &Volume, pSize, pBuffer );
        if ( Status == EFI_SUCCESS ) return Status;
    }
    if ( FatRecoverySupport ) {
        Volume.PartitionOffset = 0;
        Status = ProcessFatDevice( PeiServices, &Volume, pSize, pBuffer );
        if ( Status == EFI_SUCCESS ) return Status;
#if NTFS_RECOVERY_SUPPORT
    }
    if ( NtfsRecoverySupport ) {
        Volume.PartitionOffset = 0;
        Status = ProcessNTFSDevice( PeiServices, &Volume, pSize, pBuffer );
        if ( Status == EFI_SUCCESS ) return Status;
#endif
#if EXT_RECOVERY_SUPPORT
    }
    if ( ExtRecoverySupport ) {
        Volume.PartitionOffset = 0;
        Status = ProcessExtDevice( PeiServices, &Volume, pSize, pBuffer );
        if ( Status == EFI_SUCCESS ) return Status;
#endif

    } else {
        Status = EFI_NOT_FOUND;
    }
    return Status;
}


/************************************************************************/
/*				Device Recovery Module PPI								*/
/************************************************************************/
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	GetNumberRecoveryCapsules
//
// Description:	
//  GetNumberRecoveryCapsules function of ppi 
//  EFI_PEI_DEVICE_RECOVERY_MODULE_PPI.
//
// Input:
//
// Output:
//  EFI_SUCCESS - number of recovery capsules returned
//  EFI_INVALID_PARAMETER - the pointer NumberRecoveryCapsules is NULL
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS GetNumberRecoveryCapsules(
    IN EFI_PEI_SERVICES                   **PeiServices,
    IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This,
    OUT UINTN                             *NumberRecoveryCapsules )
{
    if ( !NumberRecoveryCapsules ) {
        return EFI_INVALID_PARAMETER;
    }
    *NumberRecoveryCapsules = 1;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	GetRecoveryCapsuleInfo
//
// Description:	
//  GetRecoveryCapsuleInfo function of ppi EFI_PEI_DEVICE_RECOVERY_MODULE_PPI 
//  for any block devices including floppies, USB keys, CD-ROMs and HDDs.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to PeiServices Structure
//  IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This - pointer to the PPI structure
//  IN UINTN CapsuleInstance - value indicating the instance of the PPI
//  OUT UINTN *Size - Size of the recovery capsule
//  OUT EFI_GUID *CapsuleType OPTIONAL - Type of recovery capsule
//
// Output:
//  EFI_SUCCESS - Parameters are valid and output parameters are updated
//  EFI_INVALID_PARAMETER - Size pointer is NULL
//  EFI_NOT_FOUND - asking for a 1 or greater instance of the PPI
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetRecoveryCapsuleInfo(
    IN EFI_PEI_SERVICES                   **PeiServices,
    IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This,
    IN UINTN                              CapsuleInstance,
    OUT UINTN                             *Size,
    OUT EFI_GUID                          *CapsuleType )
{
    EFI_STATUS Status;

    if ( !Size ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( CapsuleInstance > 0 ) {
        return EFI_NOT_FOUND;
    }

    Status = GetRecoveryFileInfo(PeiServices, NULL, Size, NULL);
    if(EFI_ERROR(Status))
        return Status;

    if ( CapsuleType ) {
        *CapsuleType = guidBlockDeviceCapsule;
    }
    return EFI_SUCCESS;
}

#define NUMBER_OF_RETRIES 3

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	LoadRecoveryCapsule
//
// Description:	
//  Locates all EFI_PEI_RECOVERY_BLOCK_IO_PPI PPIs.  Calls function 
//  GetNumberOfBlockDevices.  For each block device, calls the function 
//  FsRecoveryRead, to find the recovery image named in var sAmiRomFile.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to PeiServices Structure 
//  IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This - pointer to the PPI structure
//  IN UINTN CapsuleInstance - value indicating the instance of the PPI
//  OUT VOID *Buffer - contains information read from the block device
//
// Output:
//  EFI_SUCCESS - File read from recovery media
//  EFI_INVALID_PARAMETER - Buffer is a NULL pointer
//  EFI_NOT_FOUND - asking for a 1 or greater instance of the PPI
//  Other - return error values from LocatePpi or FsRecoveryRead
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS LoadRecoveryCapsule(
    IN EFI_PEI_SERVICES                   **PeiServices,
    IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This,
    IN UINTN                              CapsuleInstance,
    OUT VOID                              *Buffer )
{
    static EFI_GUID        guidBlockIo = EFI_PEI_VIRTUAL_BLOCK_IO_PPI;
    EFI_STATUS             Status;
    EFI_PEI_PPI_DESCRIPTOR *pDummy;
    UINTN                  i;
    UINTN                  RecoveryCapsuleSize;
    BOOLEAN                ExtendedVerification;

    PEI_TRACE((-1, PeiServices, "..BLOCK DEVICE.."));

    if ( !Buffer ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( CapsuleInstance > 0 ) {
        return EFI_NOT_FOUND;
    }

    Status = GetRecoveryFileInfo(PeiServices, NULL, &RecoveryCapsuleSize, &ExtendedVerification);
    if ( EFI_ERROR( Status ))
        return Status;

    i = 0;

    do
    {
        EFI_PEI_RECOVERY_BLOCK_IO_PPI *pBlockIo;
        UINTN                         NumberBlockDevices;
        UINTN                         j;
        UINTN                         Size;
        Status = (*PeiServices)->LocatePpi( PeiServices, &guidBlockIo, i++, &pDummy, &pBlockIo );

        if ( EFI_ERROR( Status )) {
            break;
        }

        if (EFI_ERROR( Status = pBlockIo->GetNumberOfBlockDevices(
                                            PeiServices, pBlockIo, &NumberBlockDevices))) {
            continue;
        }

        for ( j = 0; j < NumberBlockDevices; j++ ) {
            UINTN k;
            Size = RecoveryCapsuleSize;

            for ( k = 0; k < NUMBER_OF_RETRIES; k++ )
            {
                Status = FsRecoveryRead(
                    PeiServices, j, pBlockIo,
                    &Size, Buffer
                    );

                if ( !EFI_ERROR(Status) ){
                    if(ExtendedVerification || Size == RecoveryCapsuleSize )
                        return EFI_SUCCESS;
                }
            }
        }
    } while ( TRUE );
    return Status;
}

/************************************************************************/
/*				Entry Point												*/
/************************************************************************/
EFI_PEI_DEVICE_RECOVERY_MODULE_PPI BlockDeviceRecoveryModule = {
    GetNumberRecoveryCapsules, GetRecoveryCapsuleInfo, LoadRecoveryCapsule
};

// PPI to be installed
static EFI_PEI_PPI_DESCRIPTOR      BlockDeviceRecoveryPpiList[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &guidRecoveryDevice, &BlockDeviceRecoveryModule
    }
};


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	BlockDeviceRecoveryEntry
//
// Description:	
//  Installs EFI_PEI_DEVICE_RECOVERY_MODULE_PPI for loading recovery 
//  images from block devices such as floppies, USB keys, HDDs or CD-ROMs
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BlockDeviceRecoveryEntry(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    ThisPeiServices = PeiServices;
    return (*PeiServices)->InstallPpi( PeiServices, BlockDeviceRecoveryPpiList );
}

//************************** AMI custom eLink implementation *******************

VOID AmiGetFileListFromPrimaryVolume(
    IN  DIR_RECORD          *Root,
    IN  UINT32              RootSize,
    OUT UINTN               *NumberOfFiles,
    OUT DIR_RECORD          **Buffer
)
{
    UINT32 Count = 0;
    CHAR8  *DirFileName;
    UINT32 FileNameSize;

    VOID *FileName;
    UINTN FileSize;
    EFI_STATUS Status;


    *NumberOfFiles = 0;     //no files found yet

    Status = GetRecoveryFileInfo(ThisPeiServices, &FileName, &FileSize, NULL);
    if(EFI_ERROR(Status))
        return;

    //
    //find file in root directory
    //
    while ( Count < RootSize ) {
        DirFileName = (CHAR8*)(Root + 1);

        if(Root->Length == 0)
            return;

        // Find the length of the file name.  The ISO9660 spec has the following structure
        // up to 8 characters then a '.' then up to 3 more characters then a ';' 
        //  then the digits that make up a number between 0 and 32767
        // The filename search uses all characters up to the ';'
        FileNameSize = 0;
        while(DirFileName[FileNameSize] != ';' && (FileNameSize < Root->LengthOfFileId)) 
            FileNameSize++;

        if (!EFI_ERROR(FileSearch((CHAR8*)FileName, DirFileName, FALSE, FileNameSize))) {
            Buffer[*NumberOfFiles] = Root;
            (*NumberOfFiles)++;
            break;
        }

        Count += Root->Length;
        (UINT8 *)Root += Root->Length;
    }
}

#if SEARCH_FAT_PATH
BOOLEAN IsolateName (
    IN  CHAR8       **FilePath,
    OUT CHAR8       **NextName
)
{
    UINTN   len;
    BOOLEAN GotName;
    UINTN   i;
    CHAR8   *TempPath;

    TempPath = *FilePath;
    len = Strlen(TempPath);
    GotName = TRUE;
    for ( i = 0; i < len; i++ ) {
        if ( TempPath[i] == 0x5C ) { // "\"
            GotName = FALSE;
            TempPath[i] = 0;
            *NextName = TempPath + i + 1;
            return GotName;
        }
    }
    return GotName;
}

#endif

VOID AmiGetFileListFromFatVolume(
    IN  DIR_ENTRY           *Root,
    IN  UINT32              RootEntries,
    OUT UINTN               *NumberOfFiles,
    OUT DIR_ENTRY           **Buffer
)
{
    UINT32 i;

    VOID *FileName;
    UINTN FileSize;
    EFI_STATUS Status;
    UINT32 DirEntries;
    DIR_ENTRY *DirPtr;
    CHAR8 *FilePath;
#if SEARCH_FAT_PATH
    UINT32 DirSize;
    CHAR8 *NextName;
    UINTN DirPages;
    EFI_PHYSICAL_ADDRESS Allocate;
    UINT32 Cluster;
#endif

    *NumberOfFiles = 0;     //no files found yet

    Status = GetRecoveryFileInfo(ThisPeiServices, &FileName, &FileSize, NULL);
    if(EFI_ERROR(Status))
        return;

    FilePath = FileName;
    DirEntries = RootEntries;
    DirPtr = Root;
#if SEARCH_FAT_PATH
    FilePath = (CHAR8*)FileName;
    NextName = FilePath;

    while ( IsolateName (&FilePath, &NextName) == FALSE ) {
        //
        //Find path name in directory
        //
        for(i = 0; i < DirEntries; i++) {
            if((DirPtr[i].FileName[0] == 0xE5) || (DirPtr[i].FileName[0] == 0)) 
                continue;

            if(!EFI_ERROR(FileSearch((CHAR8*)FilePath, DirPtr[i].FileName, TRUE, FAT_FILE_NAME_SIZE))) {
                //
                // A match was found...
                // Update FilePath to next name. 
                // Update DirPtr to this directory, and read it in
                // 
                // *REMOVED* DirSize = DirPtr[i].FileSize;
                //
                // The size of a directory is not stored in it's directory entry,
                // So we will only read in one cluster for now.
                //
                DirSize = ThisVolume->BytesPerCluster;
                DirEntries = DirSize / 32;
                Cluster = DirPtr[i].FirstClusterLo + (DirPtr[i].FirstClusterHi << 16);

                DirPages = EFI_SIZE_TO_PAGES( DirSize );

                if ( DirSize < EFI_PAGES_TO_SIZE( DirPages )) {
                    Status = (*ThisPeiServices)->AllocatePages( ThisPeiServices,
                                                 EfiBootServicesData, DirPages, &Allocate );
                    if ( EFI_ERROR( Status )) {
                        *NumberOfFiles = 0;
                        return;
                    }

                    DirPtr = (DIR_ENTRY*)((UINTN)Allocate);
                    DirSize = EFI_PAGES_TO_SIZE( DirPages );
                }
                MemSet( DirPtr, DirSize, 0 );

                Status = GetFatData( ThisPeiServices, ThisVolume, Cluster, DirSize, DirPtr );
                if ( EFI_ERROR( Status )) {
                    *NumberOfFiles = 0;
                    return;
                }
                FilePath = NextName;
                break;
            }
        }
    }
#endif
    //
    // Find file in directory
    //
    for(i = 0; i < DirEntries; i++) {
        if((DirPtr[i].FileName[0] == 0xE5) || (DirPtr[i].FileName[0] == 0)) 
            continue;

        if(!EFI_ERROR(FileSearch((CHAR8*)FilePath, DirPtr[i].FileName, TRUE, FAT_FILE_NAME_SIZE))) {
            Buffer[*NumberOfFiles] = &DirPtr[i];
            *NumberOfFiles = 1;
            break;
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	AmiGetFileListFromNtfsVolume
//
// Description:	
//  Gets a list of valid recovery files from an NTFS volume.
//  As currently written, gets only one file.
//
// Input:
//  UINT8 *Root - Pointer to a buffer containing the root directory
//  UINT32 RootSize - Size of the root directory
//  UINTN *NumberOfFiles - Pointer to number of files found
//  INDEX_ENTRY **Buffer - Pointer to buffer containing index entry of
//    the file that was found.
//
// Output:
//  None - returned in variables.
//
// Notes:
//  This is an e-linked function, which can be replaced.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AmiGetFileListFromNtfsVolume(
    IN  UINT8               *Root,
    IN  UINT32              RootSize,
    OUT UINTN               *NumberOfFiles,
    OUT INDEX_ENTRY         **Buffer
)
{
#if NTFS_RECOVERY_SUPPORT
    UINT8       i;
    UINT32      IndexSize;
    UINT32      IndexSize2;
    UINTN       Offset;
    UINT8       *TmpPtr;
    CHAR16      *NamePtr;
    CHAR8       TmpFileName[13];
    UINT8       LfnSize;
    UINT16      EntrySize;
    INDEX_ENTRY *IndxPtr;
    VOID		*FileName;
    UINTN		FileSize;
    EFI_STATUS	Status;

    *NumberOfFiles = 0;     //no files found yet

    Status = GetRecoveryFileInfo(ThisPeiServices, &FileName, &FileSize, NULL);
    if(EFI_ERROR(Status))
        return;

    if (ResidentPresent) { // If resident index found...
        TmpPtr = &MemBlk->ResidentIndex[0];
        IndexSize = ResidentSize;

        do { // loop inside the index
            EntrySize = ((INDEX_ENTRY*)TmpPtr)->INDE_EntrySize;
            LfnSize = ((INDEX_ENTRY*)TmpPtr)->INDE_NameLength;
            if (LfnSize > 12) LfnSize = 12; // Limit name to 12 chars
            NamePtr = &((INDEX_ENTRY*)TmpPtr)->INDE_Name[0];
            for ( i=0; i<LfnSize; i++ )
            {
                TmpFileName[i] = (CHAR8)(CHAR16)NamePtr[i];
            }
            TmpFileName[i] = 0; // Zero-terminate name

            if(!EFI_ERROR(FileSearch((CHAR8*)FileName, TmpFileName, FALSE, LfnSize))) {
                IndxPtr = (INDEX_ENTRY*)&TmpPtr[0];
                Buffer[*NumberOfFiles] = IndxPtr; // Save pointer to this entry
                *NumberOfFiles = 1;
                return;
            }

            TmpPtr += EntrySize;
            IndexSize -= EntrySize;
            if ( IndexSize < MINIMUM_ENTRY_SIZE ) break;

        } while (IndexSize);
    }

    do { // do loop handling indexes in the root
        Offset = 0;
        // Look for "INDX", start of index record
        if ( (Root[0] == 0x49) && \
             (Root[1] == 0x4E) && \
             (Root[2] == 0x44) && \
             (Root[3] == 0x58) ) 
        {
            IndexSize = ((INDEX_RECORD*)Root)->INDR_IndxEntrySize;
            IndexSize2 = IndexSize;
            Offset += ((INDEX_RECORD*)Root)->INDR_IndxEntryOff + \
                        EFI_FIELD_OFFSET(INDEX_RECORD, INDR_IndxEntryOff);
            TmpPtr = Root;
            TmpPtr += Offset; // Point to first entry in index
            if (IndexSize < MINIMUM_ENTRY_SIZE) { // Empty index
                return;
            }
        } else return; // no index found

        do { // loop inside the index
            EntrySize = ((INDEX_ENTRY*)TmpPtr)->INDE_EntrySize;
            LfnSize = ((INDEX_ENTRY*)TmpPtr)->INDE_NameLength;
            if (LfnSize > 12) LfnSize = 12; // Limit name to 12 chars
            NamePtr = &((INDEX_ENTRY*)TmpPtr)->INDE_Name[0];
            for ( i=0; i<LfnSize; i++ )
            {
                TmpFileName[i] = (CHAR8)(CHAR16)NamePtr[i];
            }
            TmpFileName[i] = 0; // Zero-terminate name

            if(!EFI_ERROR(FileSearch((CHAR8*)FileName, TmpFileName, FALSE, LfnSize))) {
                IndxPtr = (INDEX_ENTRY*)&TmpPtr[0];
                Buffer[*NumberOfFiles] = IndxPtr; // Save pointer to this entry
                *NumberOfFiles = 1;
                return;
            }

            TmpPtr += EntrySize;
            IndexSize -= EntrySize;
            if ( IndexSize < MINIMUM_ENTRY_SIZE ) break;

        } while (IndexSize);
        if ( IndexSize2 < 0x1000 ) {
            IndexSize2 = 0x1000;
        } else {
            IndexSize2 = (IndexSize2 + 0x100) & 0xffffff00 ; // Round off
        }
        Root += IndexSize2;
        RootSize -= IndexSize2;

    } while (RootSize);
#else
    *NumberOfFiles = 0;     //no files found
    return;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	AmiGetFileListFromExtVolume
//
// Description:	
//  Gets a list of valid recovery files from an EXT(n) volume.
//  As currently written, gets only one file.
//
// Input:
//  UINT8 *Root - Pointer to a buffer containing the root directory
//  UINT32 RootSize - Size of the root directory
//  UINTN *NumberOfFiles - Pointer to number of files found
//  DIR_ENTRY_EXT **Buffer - Pointer to buffer containing index entry of
//    the file that was found.
//
// Output:
//  None - returned in variables.
//
// Notes:
//  This is an e-linked function, which can be replaced.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AmiGetFileListFromExtVolume(
    IN  UINT8               *Root,
    IN  UINT32              RootSize,
    OUT UINTN               *NumberOfFiles,
    OUT DIR_ENTRY_EXT       **Buffer
)
{
#if EXT_RECOVERY_SUPPORT
    EFI_STATUS              Status;
    DIR_ENTRY_EXT           *TmpPtr;
    UINT16                  EntryLength;
    UINT8                   NameLength;
    VOID		            *FileName;
    UINTN		            FileSize;
    UINT8                   i;
    CHAR8                   TmpFileName[13];

    *NumberOfFiles = 0;     //no files found yet

    Status = GetRecoveryFileInfo(ThisPeiServices, &FileName, &FileSize, NULL);
    if(EFI_ERROR(Status))
        return;

    do { // do loop handling entries in the root

        TmpPtr = (DIR_ENTRY_EXT*)&Root[0];
        EntryLength = TmpPtr->DIR_EntryLength;
        if (EntryLength == 0) break; // End of directory, file not found
        NameLength = TmpPtr->DIR_NameLength;
        if (NameLength > 12) NameLength = 12;
        for ( i=0; i<NameLength; i++ )
        {
            TmpFileName[i] = TmpPtr->DIR_Name[i];
        }
        TmpFileName[i] = 0; // Zero-terminate name

        if(!EFI_ERROR(FileSearch((CHAR8*)FileName, 
                                 TmpFileName, 
                                 FALSE, 
                                 NameLength))) {
            Buffer[*NumberOfFiles] = TmpPtr; // Save pointer to this entry
            *NumberOfFiles = 1;
            return;
        }

        Root += EntryLength;
        RootSize -= EntryLength;

    } while (RootSize);
#else
    *NumberOfFiles = 0;     //no files found
    return;
#endif
}

BOOLEAN AmiIsValidFile(
    IN VOID  *FileData,
    IN UINTN FileSize
)
{
    return TRUE;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
