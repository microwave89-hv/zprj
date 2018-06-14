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
// $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/MEUD.c 28    5/14/14 1:54a Tristinchou $
//
// $Revision: 28 $
//
// $Date: 5/14/14 1:54a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/MEUD.c $
// 
// 28    5/14/14 1:54a Tristinchou
// [TAG]  		EIP167375
// [Category]  	Improvement
// [Description]  	Remove the variables' RT attribute
// 
// 27    5/16/13 4:05a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Fix system hangs when BIOS is not on the top of ROM
// 
// 26    5/16/13 1:54a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Remove Flash Device Enable/Disable.
// Report BIOS information to AFU.
// 
// 25    3/08/12 5:32a Klzhan
// Report error when CSP_ReportMEInfo return error.
// 
// 24    8/30/11 4:24a Klzhan
// Remove Un-use code.
// 
// 23    8/15/11 5:06a Klzhan
// Fix can't update Ignition FW.
// 
// 22    8/05/11 6:44a Klzhan
// [TAG]  		EIP63481
// [Category]  	Improvement
// [Description]  	AFU support commands for each regions update.
// 
// 21    7/15/11 4:54a Klzhan
// Remove un used comment.
// 
// 20    7/15/11 4:52a Klzhan
// [TAG]  		EIP60754
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Support Direct FW Update.
// 
// 19    6/14/11 3:42a Klzhan
// Support SPS spec to 1.1.
// 
// 18    5/31/11 5:01a Klzhan
// [TAG]  		EIP60991
// [Category]  	New Feature
// [Description]  	Read whole Flash image.
// 
// 17    5/09/11 3:55a Klzhan
// Remove Debug include.
// 
// 16    5/09/11 3:24a Klzhan
// Add Setup Item in Advanced Page to select regions to update.
// 
// 15    4/22/11 5:53a Klzhan
// Fix Build Error.
// 
// 14    4/22/11 4:36a Klzhan
// Add error handler when restore MAC.
// 
// 13    4/22/11 4:15a Klzhan
// Resotre MAC address when update GBE.
// 
// 12    4/22/11 2:30a Klzhan
// Remove the code related to ME AUTO UPDATE.
// Add OFBD version control for update ME though OFBD.
// 
// 11    2/10/11 5:52a Klzhan
// [TAG]  		EIP52968
// [Category]  	New Feature
// [Description]  	Update ME through OFBD not SMIFlash.
// [Files]  		MEUD.sdl
// MEUD.h
// MEUD.c
// 
// 10    1/12/11 10:34p Klzhan
// Fix build error when ME_AUTO_UPDATE is disabled.
// 
// 9     12/27/10 4:42a Klzhan
// Improvement : ME auto update.
// 
// 8     11/16/10 4:38a Klzhan
// Correct behavior of ME update.
// 
// 7     11/16/10 1:44a Klzhan
// Fill all parameters in MEUDStructPtr.
// 
// 6     11/11/10 4:46a Klzhan
// Correct error check when report MEInfo.
// 
// 5     6/10/10 11:25p Klzhan
// BugFix : FIx Compiler Error when ME_Ignition_FW_MSG_SUPPORT is
// disabled.
// 
// 4     6/10/10 4:21a Klzhan
// Improvement : Correct "ME_IGNITION_FW_MSG_SUPPORT" behavior.
// 
// 3     11/18/09 5:07a Klzhan
// Improvement : Restore FlashCapacity after program for AFUWin.
// 
// 2     10/13/09 3:33a Klzhan
// Updated for Aptio Source Enhancement.
// 
// 1     9/30/09 11:15p Lawrencechang
// Move Intel ME update module part to an independent SS path.
// 
// 5     8/31/09 9:04a Klzhan
// Update Procedure name to support Capella.
// 
// 4     7/10/09 4:19a Klzhan
// Improvement: Command /ME support flash entire image when Ignition FW.
// 
// 3     7/03/09 5:04a Klzhan
// Bug fix: Update ME Ignition FW fail.
// Severity: Critical
// Symptom: System will write wrong address when Ignition update.
// Root Cause: Coding Error
// Improvement: Add a token for showing ME Ignition status message
// 
// 2     7/02/09 8:25a Klzhan
// 
// 1     4/13/09 5:47a Lawrencechang
// Initial check-in.
// 
// 1     3/25/05 5:37p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	MEUD.c
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "MEUD.h"
#include "Flash.h"
#include "..\OFBD.h"
#include <Protocol\smiflash.h>
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\SmmBase2.h>
#include "Setup.h"

EFI_SMI_FLASH_PROTOCOL *mSmiFlash;
UINT32 FlashCapacity;
// Skip Area, Now there are only 5 regions(FD, ME, GBE, PDR and BIOS)

UINT8     MacAddr[6];

VOID MEUDSMIHandler (
    IN    EFI_HANDLE    DispatchHandle,
    IN    EFI_SMM_SW_DISPATCH_CONTEXT    *DispatchContext
);

// SMM Nvram Control Protocol Definitions
typedef
EFI_STATUS (*SHOW_BOOT_TIME_VARIABLES)(BOOLEAN Show);

typedef struct{
    SHOW_BOOT_TIME_VARIABLES ShowBootTimeVariables;
}AMI_NVRAM_CONTROL_PROTOCOL;

AMI_NVRAM_CONTROL_PROTOCOL *gNvramControl = NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LocateNvramControlSmmProtocol
//
// Description:	Locate NvramControlProtocol
//
// Input:
//      VOID
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
AMI_NVRAM_CONTROL_PROTOCOL*
LocateNvramControlSmmProtocol()
{
    EFI_STATUS Status;
    static EFI_GUID AmiNvramControlProtocolGuid = { 0xf7ca7568, 0x5a09, 0x4d2c, { 0x8a, 0x9b, 0x75, 0x84, 0x68, 0x59, 0x2a, 0xe2 } };
    EFI_GUID EfiSmmBase2ProtocolGuid = EFI_SMM_BASE2_PROTOCOL_GUID;
    EFI_SMM_BASE2_PROTOCOL  *SmmBase2 = NULL;
    EFI_SMM_SYSTEM_TABLE2   *Smst2 = NULL;
    EFI_CONFIGURATION_TABLE *Table = NULL;
    UINTN                   Count = 0;

    Status = pBS->LocateProtocol( &EfiSmmBase2ProtocolGuid, NULL, &SmmBase2 );
    if( !EFI_ERROR(Status) )
    {
        Status = SmmBase2->GetSmstLocation( SmmBase2, &Smst2 );
        if( EFI_ERROR(Status) || Smst2 == NULL )
            return NULL;
    }

    Table = Smst2->SmmConfigurationTable;
    Count = Smst2->NumberOfTableEntries;

    for( ; Count ; --Count, ++Table )
    {
        if( guidcmp( &Table->VendorGuid, &AmiNvramControlProtocolGuid ) == 0 ) 
            return Table->VendorTable;
    }

    return NULL;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MEUDCallback
//
// Description:	Locate SmiFlash protocol callback
//
// Input:
//      IN EFI_EVENT    Event
//      IN VOID         *Context
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MEUDCallback(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
    EFI_GUID       gEfiSmiFlashProtocolGuid = EFI_SMI_FLASH_GUID;

    pBS->LocateProtocol (&gEfiSmiFlashProtocolGuid, NULL, &mSmiFlash);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MEUDInSmm
//
// Description:	OFBD ME Firmware Update InSmm Function
//
// Input:
//      VOID
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MEUDInSmm(VOID)
{
    EFI_STATUS     Status;
    EFI_GUID       gEfiSmiFlashProtocolGuid = EFI_SMI_FLASH_GUID;
    EFI_GUID       gMEUDErrorGuid = MEUD_ERROR_GUID;
    UINT8          FW_Usage = 0, MeResetFlag;
    UINT32         VariableAttr;
    UINTN          VariableSize;
    FlashCapacity = GetFlashCapacity();

    Status = pBS->LocateProtocol (&gEfiSmiFlashProtocolGuid, NULL, &mSmiFlash);
    if (EFI_ERROR(Status)){
        EFI_EVENT   SmiFlashCallbackEvt;
        VOID        *MEUDReg;
        RegisterProtocolCallback(
             &gEfiSmiFlashProtocolGuid, MEUDCallback,
             NULL,&SmiFlashCallbackEvt, &MEUDReg
        );
    }

    gNvramControl = LocateNvramControlSmmProtocol();

    CSP_MEUDInSmm();
    VariableSize = sizeof(UINT8);
    Status = pRS->GetVariable( L"MEUpdateResetFlag", &gMEUDErrorGuid,
                               &VariableAttr, &VariableSize, &MeResetFlag);


    if((!EFI_ERROR(Status)) && (MeResetFlag == 1))
    {
        UINT32  TempReg;

        // Reset ME
        IoWrite32(0xCF8, 0x8000F8AC);
        TempReg = IoRead32(0xCFC);

        if(!(TempReg & BIT20))
        {
            IoWrite32(0xCF8, 0x8000F8AC);
            IoWrite32(0xCFC, TempReg | BIT20);
        }
 
        // Clear Flag
        VariableSize = 0;
        pRS->SetVariable( L"MEUpdateResetFlag", &gMEUDErrorGuid,
                            VariableAttr,
                            VariableSize, &MeResetFlag);

        pRS->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }


    // If HFS is NULL, return.
#if ME_IGNITION_FW_MSG_SUPPORT
    if(GetHFS() == 0)
        return;

    FW_Usage = (GetHFS() >> 24);
    if(((GetHFS() >> 16) & 0x0F) == 1)
    // Set A variable as Flag or Link many lib to AMITSE.
        pRS->SetVariable( L"ShowMEUDFailMSG", &gMEUDErrorGuid,
	EFI_VARIABLE_BOOTSERVICE_ACCESS,
            sizeof(UINT8), &FW_Usage);
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MEUDEntry
//
// Description:	OFBD ME Firmware Update Entry point
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MEUDEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{

    OFBD_HDR       *pOFBDHdr;
    OFBD_EXT_HDR   *pOFBDExtHdr;
    VOID           *pOFBDTblEnd;
    OFBD_TC_55_MEUD_STRUCT *MEUDStructPtr;
    EFI_STATUS     Status = EFI_SUCCESS;
    UINT32         Buffer1, Buffer2;
    OFBD_TC_55_ME_INFO_STRUCT  *MEInfoStructPtr;
    OFBD_TC_55_ME_PROCESS_STRUCT  *MEProcessStructPtr;
#ifdef CSP_SPSUD_SUPPORT
#if CSP_SPSUD_SUPPORT
    UINT8          Timer = 0;
    UINT8          MeResetFlag = 0;
    EFI_GUID       gMEUDErrorGuid = MEUD_ERROR_GUID;
#endif
#endif
#if (OFBD_VERSION >= 0x0210)
    UINT32         Length, Offset;
    BOOLEAN        FlashStatus = TRUE;
    UINT8          *Address;
    UINT32         Size;
    UINT8*         Data;
#endif
    if (*pOFBDDataHandled == 0)
    {
        pOFBDHdr = (OFBD_HDR *)Buffer;
        pOFBDExtHdr = (OFBD_EXT_HDR *)((UINT8 *)Buffer + \
                      (pOFBDHdr->OFBD_HDR_SIZE));
        MEUDStructPtr = (OFBD_TC_55_MEUD_STRUCT *)((UINT8 *)pOFBDExtHdr + \
                        sizeof(OFBD_EXT_HDR));
        MEInfoStructPtr = (OFBD_TC_55_ME_INFO_STRUCT*)MEUDStructPtr;
        MEProcessStructPtr = (OFBD_TC_55_ME_PROCESS_STRUCT*)MEUDStructPtr;

        pOFBDTblEnd = (VOID *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_Size));

        if (pOFBDHdr->OFBD_FS & OFBD_FS_MEUD)
        {
            //Check Type Code ID
            if (pOFBDExtHdr->TypeCodeID == OFBD_EXT_TC_MEUD)
            {
                switch (MEUDStructPtr->bSubFunction)
                {
                case 0 :

                    Status = CSP_ReportMEInfo(0 , \
                            &(MEUDStructPtr->dMERuntimeBase), \
                            &(MEUDStructPtr->dMERuntimeLength));

                    MEUDStructPtr->dMEBiosRegionBase = \
                                                 FlashCapacity - FLASH_SIZE;
                    MEUDStructPtr->dMEBiosRegionLength = (UINT32)FLASH_SIZE;

                    if ((FlashCapacity == 0) || EFI_ERROR(Status))
                    {
                        // Fail , Return
                        *pOFBDDataHandled = 0xFE;
                        return;
                    }
                    *pOFBDDataHandled = 0xFF;
                    MEUDStructPtr->bReturnStatus =  OFBD_TC_MEUD_OK;
                    return;
                case 3 :
                    Status = CSP_ReportMEInfo(3, \
                            &(MEUDStructPtr->dMERuntimeBase), \
                            &(MEUDStructPtr->dMERuntimeLength));

                    MEUDStructPtr->dMEBiosRegionBase = \
                                                 FlashCapacity - FLASH_SIZE;
                    MEUDStructPtr->dMEBiosRegionLength = (UINT32)FLASH_SIZE;

                    // If FlashCapacity == 0, Not support ME Update
                    if (FlashCapacity == 0)
                    {
                        // Fail , Return
                        *pOFBDDataHandled = 0xFE;
                        return;
                    }

                    *pOFBDDataHandled = 0xFF;
                    MEUDStructPtr->bReturnStatus =  OFBD_TC_MEUD_OK;
                    return;
                case 1 :
                    // Send this again to check is this suppoet.
                    Status = CSP_ReportMEInfo(0, \
                            &Buffer1, \
                            &Buffer2);

                    if (!EFI_ERROR(Status))
                        Status = HMRFPO_ENABLE_MSG();

                    if (EFI_ERROR(Status))
                    {
                        // Fail , Return
                        *pOFBDDataHandled = 0xFE;
                        return;
                    }
                    MEUDStructPtr->bReturnStatus =  OFBD_TC_MEUD_OK;
                    *pOFBDDataHandled = 0xFF;
                    mSmiFlash->FlashCapacity = FlashCapacity;
                    return;
                case 4 :
                    // Send this again to check is this suppoet.
                    Status = CSP_ReportMEInfo(3, \
                            &Buffer1, \
                            &Buffer2);
                    if (EFI_ERROR(Status))
                    {
                        // Fail , Return
                        *pOFBDDataHandled = 0xFE;
                        return;
                    }
                    MEUDStructPtr->bReturnStatus =  OFBD_TC_MEUD_OK;
                    *pOFBDDataHandled = 0xFF;
                    mSmiFlash->FlashCapacity = FlashCapacity;
#if (OFBD_VERSION >= 0x0210)
                    // Get GBE Region for Restore MAC address
                    Status = GetRegionOffset(3, &Offset, &Length);

                    // Before Erase, Get mac address
                    if(Length)
                    {
#if (OFBD_VERSION >= 0x0220)
                        DoNotConvert = TRUE;
#endif
                        Address = (UINT8*)FLASH_BASE_ADDRESS(Offset);
                        FlashRead(Address, MacAddr, 6);
#if (OFBD_VERSION >= 0x0220)
                        DoNotConvert = FALSE;
#endif
                    }
#endif
                    return;
                case 2 :
                    Status = HMRFPO_LOCK_MSG();
                    if (EFI_ERROR(Status))
                    {
                        // Fail , Return
                        *pOFBDDataHandled = 0xFE;
                        return;
                    }
                case 5 :
                    mSmiFlash->FlashCapacity = FLASH_SIZE;
#if defined (CSP_SPSUD_SUPPORT) && (CSP_SPSUD_SUPPORT == 1)
/*
                    do{
                        Status = HMRFPO_LOCK_MSG();
                        if(!EFI_ERROR(Status))
                            break;
                        Timer ++;
                    }while(Timer < 3);
*/
                    //reset ME.
                    MeResetFlag = 1;

                    if( gNvramControl )
                        gNvramControl->ShowBootTimeVariables( TRUE );
                    Status = pRS->SetVariable(
                                    L"MEUpdateResetFlag",
                                    &gMEUDErrorGuid,
                                    EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                    EFI_VARIABLE_NON_VOLATILE,
                                    sizeof(UINT8),
                                    &MeResetFlag );
                    if( gNvramControl )
                        gNvramControl->ShowBootTimeVariables( FALSE );
                    if (EFI_ERROR(Status))
                    {
                        // Fail , Return
                        *pOFBDDataHandled = 0xFE;
                        return;
                    }
#endif
                    MEUDStructPtr->bReturnStatus =  OFBD_TC_MEUD_OK;
                    *pOFBDDataHandled = 0xFF;
                    return;

                default :
                    *pOFBDDataHandled = 0xFE;
                    break;
// =============== OFBD Version 2.1 and AFU version 2.37 or newer ===============
#if (OFBD_VERSION >= 0x0210)
                // earse
                case 6 :

                    Size = MEUDStructPtr->ddBlockSize;

                    Address = (UINT8*)FLASH_BASE_ADDRESS(MEUDStructPtr->ddBlockAddr);



                    for (; FlashStatus && Size > 0; Address += 0x1000, Size -= 0x1000)
                    {
                         FlashBlockWriteEnable(Address);
                         FlashStatus = FlashEraseBlock(Address);
                         FlashBlockWriteDisable(Address);
                     }

                     if(FlashStatus)
                     {
                         *pOFBDDataHandled = 0xFF;
                         MEUDStructPtr->bReturnStatus =  OFBD_TC_MEUD_OK;
                     }
                    break;
                // program
                case 7 :
                    Size = MEUDStructPtr->ddBlockSize;
                    Data = (UINT8*)pOFBDHdr;
                    Status = CSP_ReportMEInfo(3, \
                                &Buffer1,
                                &Buffer2);
                    (UINTN)Address = FLASH_BASE_ADDRESS(MEUDStructPtr->ddBlockAddr);
                    Status = GetRegionOffset(3, &Offset, &Length);

                    (UINTN)Data += MEUDStructPtr->ddFlashBufOffset;
                    // Restore MAC Address
                    if((MEUDStructPtr->ddBlockAddr == Offset) && (Length != 0))
                        MemCpy(Data,MacAddr,6);

                    FlashDeviceWriteEnable();

                    FlashBlockWriteEnable(Address);
                    FlashStatus = FlashProgram(Address, Data, Size);
                    FlashBlockWriteDisable(Address);

                    FlashDeviceWriteDisable();
                    if(FlashStatus)
                    {
                        *pOFBDDataHandled = 0xFF;
                        MEUDStructPtr->bReturnStatus =  OFBD_TC_MEUD_OK;
                    }
                    break;

                // Read
                case 8 :
                    (UINTN)Address = FLASH_BASE_ADDRESS(MEUDStructPtr->ddBlockAddr);
                    Data = (UINT8*)pOFBDHdr;
                    (UINTN)Data += MEUDStructPtr->ddFlashBufOffset;

                    FlashRead(Address, Data, MEUDStructPtr->ddBlockSize);
                    *pOFBDDataHandled = 0xFF;
                    MEUDStructPtr->bReturnStatus =  OFBD_TC_MEUD_OK;
                    break;

                case 9 :
                    // Get Info
                    {
                        UINT16    TotalBlocks = 0;

                        // Get FD
                        Status = GetRegionOffset(0 ,
                            &MEInfoStructPtr->BlockInfo[TotalBlocks].StartAddress, 
                            &MEInfoStructPtr->BlockInfo[TotalBlocks].BlockSize);

                        // Fill FD Info
                        if(!EFI_ERROR(Status))
                        {
                            MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Command,"FDR",4);
                            MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Description,
                                   "Flash Flash-Descriptor Region",64);
                            MEInfoStructPtr->BlockInfo[TotalBlocks].Type = FDT_BLK;
                            // Status = 1 means Protect
                            MEInfoStructPtr->BlockInfo[TotalBlocks].Status = 0;
                            TotalBlocks += 1;
                        }
                        // Get GBE
                        Status = GetRegionOffset(3 ,
                            &MEInfoStructPtr->BlockInfo[TotalBlocks].StartAddress,
                            &MEInfoStructPtr->BlockInfo[TotalBlocks].BlockSize);

                        // Fill GBE Info
                        if(!EFI_ERROR(Status))
                        {
                            MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Command,"GBER",4);
                            MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Description,
                                   "Flash GBE Region",64);
                            MEInfoStructPtr->BlockInfo[TotalBlocks].Type = GBE_BLK;
                            // Status = 1 means Protect
                            MEInfoStructPtr->BlockInfo[TotalBlocks].Status = 0;
                            TotalBlocks += 1;
                        }

                        // Get PDR
                        Status = GetRegionOffset(4 ,
                            &MEInfoStructPtr->BlockInfo[TotalBlocks].StartAddress,
                            &MEInfoStructPtr->BlockInfo[TotalBlocks].BlockSize);

                        // Fill PDR Info
                        if(!EFI_ERROR(Status))
                        {
                            MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Command,"PDR",4);
                            MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Description,
                                   "Flash PDR Region",64);
                            MEInfoStructPtr->BlockInfo[TotalBlocks].Type = PDR_BLK;
                            // Status = 1 means Protect
                            MEInfoStructPtr->BlockInfo[TotalBlocks].Status = 0;
                            TotalBlocks += 1;
                        }

                        // Get ME
                        Status = GetRegionOffset(2 ,
                            &MEInfoStructPtr->BlockInfo[TotalBlocks].StartAddress,
                            &MEInfoStructPtr->BlockInfo[TotalBlocks].BlockSize);

                        // Fill ME Info
                        if(!EFI_ERROR(Status))
                        {
                            MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Command,"MER",4);
                            MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Description,
                                   "Flash Entire ME Region",64);
                            MEInfoStructPtr->BlockInfo[TotalBlocks].Type = ME_BLK;
                            // Status = 1 means Protect
                            MEInfoStructPtr->BlockInfo[TotalBlocks].Status = 0;
                            TotalBlocks += 1;
                        }

                        // Get BIOS
                        Status = GetRegionOffset(1 ,
                            &MEInfoStructPtr->BlockInfo[TotalBlocks].StartAddress,
                            &MEInfoStructPtr->BlockInfo[TotalBlocks].BlockSize);

                        // Fill BIOS Info
                        if(!EFI_ERROR(Status))
                        {
                            MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Command,"MER",4);
                            MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Description,
                                   "Flash Entire ME Region",64);
                            MEInfoStructPtr->BlockInfo[TotalBlocks].Type = BIOS_BLK;
                            // Status = 1 means Protect
                            MEInfoStructPtr->BlockInfo[TotalBlocks].Status = 0;
                            TotalBlocks += 1;
                        }
#if defined (CSP_SPSUD_SUPPORT) && (CSP_SPSUD_SUPPORT == 1)
                        //
                        // Fill SPS Partition Info
                        //

                        // OPR1
                        MEInfoStructPtr->BlockInfo[TotalBlocks].StartAddress = OPR1_START;
                        MEInfoStructPtr->BlockInfo[TotalBlocks].BlockSize = OPR1_LENGTH;
                            // OPR2
                        if(OPR2_LENGTH != 0)
                            MEInfoStructPtr->BlockInfo[TotalBlocks].BlockSize += OPR2_LENGTH;

                        MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Command,"OPR",4);
                        MemCpy(MEInfoStructPtr->BlockInfo[TotalBlocks].Description,
                               "Flash Operation Region of SPS",64);

                        MEInfoStructPtr->BlockInfo[TotalBlocks].Type = ME_OPR_BLK;
                        // Status = 1 means Protect
                        MEInfoStructPtr->BlockInfo[TotalBlocks].Status = 0;
                        TotalBlocks += 1;
#endif
                        MEInfoStructPtr->TotalBlocks = TotalBlocks;
                        *pOFBDDataHandled = 0xFF;
                        MEUDStructPtr->bReturnStatus =  OFBD_TC_MEUD_OK;

                    }
                    break;
                case 10 :
                    // ME Process Handle
                    // In CSP_MEUD.c
                    MEProcessHandler(&MEProcessStructPtr);
                    *pOFBDDataHandled = 0xFF;
                    MEUDStructPtr->bReturnStatus =  OFBD_TC_MEUD_OK;
                    break;
#endif //#if (OFBD_VERSION >= 0x0210)
                }// End of Switch
            }

        }

    }
    return;
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
