//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPetAlert/AmtPetAlert.c 8     6/18/14 3:16a Larryliu $
//
// $Revision: 8 $
//
// $Date: 6/18/14 3:16a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPetAlert/AmtPetAlert.c $
// 
// 8     6/18/14 3:16a Larryliu
// [TAG]  		EIP173999
// [Category]  	Improvement
// [Description]  	[HWR]Remove useless comments from Intel ME
// component.(except RC)
// [Files]  		AmtPetAlert.c
// 
// 6     5/14/14 9:38p Tristinchou
// [TAG]  		EIP160730
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 5     12/25/12 12:56a Klzhan
// Fix AMT_TC007 fail.
// 
// 4     11/07/12 8:45a Klzhan
// Improvement : Set Booted HDD as expected Boot device
// 
// 3     9/19/12 6:58a Klzhan
// Correct PET Alert behavior.
// 
// 2     6/05/12 2:33a Klzhan
// [TAG]  		EIP90325
// [Category]  	Improvement
// [Description]  	To pass Win8 SCT test.
// 
// 1     2/08/12 1:10a Klzhan
// Initial Check in 
// 
// 2     6/30/11 5:49a Klzhan
// Fix AMT TC007 fail with Fixed bootorder.
// 
// 1     2/25/11 1:45a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:11a Klzhan
// Initial Check-in.
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		AmtPetAlert.c
//
// Description:	AMT Pet Alert Functions.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "AmtPetAlert.h"
#include <ReferenceCode\ME\Protocol\AlertStandardFormat\AlertStandardFormat.h>

EFI_GUID gEfiAmtWrapperProtocolGuid = EFI_AMT_WRAPPER_PROTOCOL_GUID;
EFI_GUID gEfiSetupGuid              = SETUP_GUID;
EFI_GUID gEfiGlobalVariableGuid     = EFI_GLOBAL_VARIABLE_GUID;
EFI_GUID gEfiLegacyBiosProtocolGuid = EFI_LEGACY_BIOS_PROTOCOL_GUID;
EFI_GUID gEfiEventReadyToBootGuid   = EFI_EVENT_GROUP_READY_TO_BOOT;
EFI_GUID gEfiDiskInfoProtocolGuid   = EFI_DISK_INFO_PROTOCOL_GUID;
EFI_GUID gEfiDevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
EFI_GUID gEfiHeciProtocolGuid       = HECI_PROTOCOL_GUID;
EFI_GUID gEfiBlockIoProtocolGuid    = EFI_BLOCK_IO_PROTOCOL_GUID;
EFI_GUID gEfiSimpleFileSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

VOID 
InitializeAmtPetAlert (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS  Status;
    EFI_EVENT   ReadyToBootEvent;
    EFI_EVENT   LegacyBootEvent;
        
    EfiInitializeDriverLib (ImageHandle, SystemTable);
        
    //
    // Register Ready to Boot Event for AMT Wrapper 
    //
    Status = EfiCreateEventReadyToBoot(
                EFI_TPL_CALLBACK,
                AmtPetAlertReadyToBoot,
                (VOID *)&ImageHandle,
                &ReadyToBootEvent
                );

    Status = EfiCreateEventLegacyBoot(
                EFI_TPL_CALLBACK,
                AmtPetAlertLegacyBoot,
                NULL,
                &LegacyBootEvent
                );
                        
    return;
}

VOID SwapEntries (
  IN CHAR8    *Data,
  IN UINT16   Size
)
{
    UINT16  Index;
    CHAR8   Temp8;

    for (Index = 0; (Index+1) < Size; Index+=2) {
        Temp8           = Data[Index];
        Data[Index]     = Data[Index + 1];
        Data[Index + 1] = Temp8;
    }
}

CHAR8 *
ConvertChar16ToChar8 (
    IN CHAR16     *Src
)
{
    UINTN       l;
    CHAR8       *Output;
    CHAR8       *Dest;
    EFI_STATUS  Status;

    l = EfiStrLen(Src) + 1;
    Status = gBS->AllocatePool(
                    EfiBootServicesData, 
                    l, 
                    &Output
                    );
    ASSERT_EFI_ERROR(Status);
    
    Dest = Output;
    while (*Src) {
        *Dest++ = (UINT8) (*Src++);
    }
    *Dest = 0;
    
    return Output;
}

// Example 1: 16 10 0F 6F 02 68 08 FF FF 00 00 40 13 XX XX XX
// Example 2: 15 10 0F 6F 02 68 10 FF FF 22 00 AA 13 03 03 02
BOOT_AUDIT_ENTRY PetAlertWithoutChange = {
    0x15, 0x10, 0x0F, 0x6F, 0x02, 0x68, 0x08, 0xFF, 0xFF, 0x22, 0x00, 0x40, 0x13, 0x00, 0x00, 0x00
};

BOOT_AUDIT_ENTRY PetAlertWithChange = {
    0x15, 0x10, 0x0F, 0x6F, 0x02, 0x68, 0x10, 0xFF, 0xFF, 0x22, 0x00, 0xAA, 0x13, 0x03, 0x03, 0x02
};

EFI_STATUS
SendBaeMessage(
    BOOT_AUDIT_ENTRY                *Buffer
)
{
    EFI_HECI_PROTOCOL               *Heci;
    UINT32                          HeciLength;
    BOOT_AUDIT_ENTRY_PACK           Pack;
    UINT32                          MeStatus;
    EFI_STATUS                      TempStatus;
    EFI_STATUS                      Status;

    gBS->CopyMem(&Pack.Data, Buffer, sizeof(BOOT_AUDIT_ENTRY)); 
    Pack.Command                = EFI_ASF_MESSAGE_COMMAND_MESSAGE;  // 0x04
    Pack.ByteCount              = sizeof(BOOT_AUDIT_ENTRY);
    HeciLength                  = sizeof(BOOT_AUDIT_ENTRY_PACK);    // length include Command & ByteCount            
    
    Status = gBS->LocateProtocol (
                        &gEfiHeciProtocolGuid,
                        NULL,
                        &Heci
                        );                        
    if (!EFI_ERROR(Status)) {
        TempStatus = Heci->GetMeStatus(&MeStatus);
        ASSERT_EFI_ERROR(TempStatus);
        
        //
        // Only send ASF Push Progress code when ME is ready.  Ignore FW Init Status.
        //            
        if (ME_STATUS_ME_STATE_ONLY(MeStatus) == ME_READY) {
            Status = Heci->SendMsg(
                                (UINT32*)&Pack, 
                                HeciLength,
                                BIOS_ASF_HOST_ADDR,
                                HECI_ASF_MESSAGE_ADDR
                                );
            if (EFI_ERROR(Status)) {
            
            }
        } else {
            
        }
    } else {
        
    }
    
    return Status;
}

EFI_STATUS 
PetAlert(
    UINT8                   DeviceType,
    CHAR8                   *HarddriveTag
)
{
    PET_ALERT_CFG           PetAlertCfg[4];
    UINTN                   VarSize;
    UINT32                  VarAttr;
    BOOLEAN                 BootChange = FALSE;
    EFI_STATUS              Status;
    UINT8                   BootHDD = 0, i;

    VarSize = sizeof(PetAlertCfg);
    Status = gRT->GetVariable (
                    L"PetAlertCfg",
                    &gEfiAmtWrapperProtocolGuid,
                    &VarAttr,
                    &VarSize,
                    &PetAlertCfg
                   );
    if (EFI_ERROR (Status)) {
        VarAttr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;

        PetAlertCfg[0].BootQueue = DeviceType;
        PetAlertCfg[1].BootQueue = DeviceType;
        PetAlertCfg[2].BootQueue = DeviceType;
        PetAlertCfg[3].BootQueue = DeviceType;

        if(DeviceType == BBS_TYPE_HARDDRIVE)
            EfiAsciiStrCpy(PetAlertCfg[0].BootHarddriveTag, HarddriveTag);
        else
            EfiAsciiStrCpy(PetAlertCfg[0].BootHarddriveTag, "");
        EfiAsciiStrCpy(PetAlertCfg[1].BootHarddriveTag, "");
        EfiAsciiStrCpy(PetAlertCfg[2].BootHarddriveTag, "");
        EfiAsciiStrCpy(PetAlertCfg[3].BootHarddriveTag, "");
        BootChange = TRUE;
    }else
    {
        if(DeviceType != BBS_HARDDISK)
            BootChange = TRUE;
        else
        // If Boot HDD, check ModelSerialNumber
        {
            // last boot is not HD boot
            if(PetAlertCfg[0].BootQueue != DeviceType)
            {
                BootChange = TRUE;
            }else
            {
                // If this HDD is "excepted" or not
                for(i = 0 ; i < 4 ; i++)
                {
                    if((!EfiAsciiStrCmp(HarddriveTag,PetAlertCfg[i].BootHarddriveTag)))
                        BootHDD++;
                }
                // Not "Excepted", Set BootChanged
                if(BootHDD == 0)
                    BootChange = TRUE;
            }
        }
        if((DeviceType == BBS_HARDDISK) && BootChange)
            PetAlertWithChange.EventData3 = 0x02;
        // Not Frist Boot, update PET BAE variable.
        PetAlertCfg[3].BootQueue = PetAlertCfg[2].BootQueue;
        PetAlertCfg[2].BootQueue = PetAlertCfg[1].BootQueue;
        PetAlertCfg[1].BootQueue = PetAlertCfg[0].BootQueue;
        PetAlertCfg[0].BootQueue = DeviceType;
        
        // Update for HDD string
        EfiAsciiStrCpy(PetAlertCfg[3].BootHarddriveTag, PetAlertCfg[2].BootHarddriveTag);
        EfiAsciiStrCpy(PetAlertCfg[2].BootHarddriveTag, PetAlertCfg[1].BootHarddriveTag);
        EfiAsciiStrCpy(PetAlertCfg[1].BootHarddriveTag, PetAlertCfg[0].BootHarddriveTag);
        EfiAsciiStrCpy(PetAlertCfg[0].BootHarddriveTag, HarddriveTag);
    }

    if (BootChange)
        SendBaeMessage(&PetAlertWithChange);
    else
        SendBaeMessage(&PetAlertWithoutChange);

    VarSize = sizeof(PetAlertCfg);
    Status = gRT->SetVariable (
                    L"PetAlertCfg",
                    &gEfiAmtWrapperProtocolGuid,
                    VarAttr,
                    VarSize,
                    PetAlertCfg
                   );

    return Status;
}

BOOLEAN 
ComparePathNode(
    IN EFI_DEVICE_PATH_PROTOCOL *PathNode1,
    IN EFI_DEVICE_PATH_PROTOCOL *PathNode2
)
{
    BOOLEAN st = FALSE;
    UINTN Size1, Size2;
		UINT8 *p1, *p2;
    
    if (PathNode1 == PathNode2) {
        st = TRUE;
    } else if (PathNode1 == NULL) {
    } else if (PathNode2 == NULL) {
    } else {
        Size1 = DevicePathNodeLength(PathNode1);
        Size2 = DevicePathNodeLength(PathNode2);
        p1 = (UINT8 *)PathNode1;
        p2 = (UINT8 *)PathNode2;        
        if ((Size1 == Size2) 
        	&& (DevicePathType(PathNode1) == DevicePathType(PathNode2)) 
        	&& (EfiCompareMem(p1+1, p2+1, Size1-1) == 0)) {
            st = TRUE;          
        }
    }
    
    return st;
}

UINT8
GetDeviceType(
    IN EFI_DEVICE_PATH_PROTOCOL *DevPath
    )
{
    UINT8 DeviceType = 0;
    EFI_DEVICE_PATH_PROTOCOL *DevPathNode;
    
    //
    // Find HDD Node in BootDevPath
    //
    DevPathNode = BdsLibUnpackDevicePath(DevPath);
    ASSERT (DevPathNode);
    
    while (!IsDevicePathEnd(DevPathNode)) {
        if (DevicePathType(DevPathNode) == MEDIA_DEVICE_PATH) {
            if (DevicePathSubType(DevPathNode) == MEDIA_HARDDRIVE_DP) {
                DeviceType = BBS_TYPE_HARDDRIVE;    // 2
                break;
            } else if (DevicePathSubType(DevPathNode) == MEDIA_CDROM_DP) {
                DeviceType = BBS_TYPE_CDROM;        // 3
                break;
            } else if (DevicePathSubType(DevPathNode) == MEDIA_FILEPATH_DP) {
                DeviceType = BBS_TYPE_FLOPPY;       // 1
                break;
            }           
        }       
        //
        // Next device path node
        //
        DevPathNode = NextDevicePathNode(DevPathNode);
    }
    
    return DeviceType;  
}

EFI_DEVICE_PATH_PROTOCOL *
GetMediaPathNode (
    IN EFI_DEVICE_PATH_PROTOCOL *DevPath
)
{
    EFI_DEVICE_PATH_PROTOCOL *DevPathNode;
    EFI_DEVICE_PATH_PROTOCOL *MediaPathNode = NULL; 
    
    //
    // Find HDD Node in BootDevPath
    //
    DevPathNode = BdsLibUnpackDevicePath(DevPath);
    ASSERT (DevPathNode);
    
    while (!IsDevicePathEnd(DevPathNode)) {
        if (DevicePathType(DevPathNode) == MEDIA_FILEPATH_DP) {
            MediaPathNode = DevPathNode;
            break;
        }
        //
        // Next device path node
        //
        DevPathNode = NextDevicePathNode(DevPathNode);
    }
    
    return MediaPathNode;
}

BOOLEAN
CompareMediaPathNode(
    IN EFI_DEVICE_PATH_PROTOCOL *DevPath1,
    IN EFI_DEVICE_PATH_PROTOCOL *DevPath2
)
{
    EFI_DEVICE_PATH_PROTOCOL *PathNode1;
    EFI_DEVICE_PATH_PROTOCOL *PathNode2;
    BOOLEAN st = FALSE;
                    
    PathNode1 = GetMediaPathNode(DevPath1);
    PathNode2 = GetMediaPathNode(DevPath2);
    st = ComparePathNode(PathNode1, PathNode2);
    
    return st;
}

VOID
Trim(
    CHAR8 *sDesc,
    CHAR8 *sSrc
)
{
    UINTN p1 ,p2;
    CHAR8 ch;
    UINTN i,l;
    
    p1 = 0xFF;
    p2 = 0xFF;
    i = 0;
    for(;;) {
        ch = *(sSrc+i);
        if (ch == 0) {
            break;
        } else if (ch != 0x20) {
            p2 = i;         
            if (p1 == 0xFF) {
                p1 = i;
            }
        } 
        i++;
    }

    l = (p2 - p1) + 1;
    gBS->CopyMem(sDesc, sSrc+p1, l);
    *(sDesc+l) = 0;
}

EFI_STATUS
GetModelSerialNumber(
    IN EFI_HANDLE Handle,
    OUT CHAR8 *ModelSerialNumber
)
{
    EFI_STATUS                      Status = EFI_NOT_FOUND;
    EFI_DISK_INFO_PROTOCOL          *DiskInfo;
    IDENTIFY_DATA                   *IdentifyDriveInfo = NULL;
    UINT32                          BufferSize;
    CHAR8                           ModelNumber[42];
    CHAR8                           SerialNumber[22];
    EFI_DEVICE_PATH_PROTOCOL        *DevicePath = NULL;
    
    EfiAsciiStrCpy(ModelSerialNumber, "");
    
    for(;;) {
        Status = gBS->HandleProtocol(
                        Handle, 
                        &gEfiDevicePathProtocolGuid, 
                        &DevicePath);
        if (EFI_ERROR(Status))  
            break;
            
        Status = gBS->LocateDevicePath (
                      &gEfiDiskInfoProtocolGuid,
                      &DevicePath,
                      &Handle
                      );
        if (EFI_ERROR (Status)) {
            break;
        }
        
        Status = gBS->HandleProtocol (
                        Handle,
                        &gEfiDiskInfoProtocolGuid,
                        &DiskInfo
                        );                        
        if (EFI_ERROR(Status))  
            break;

        Status = gBS->AllocatePool(
                            EfiBootServicesData, 
                            sizeof (IDENTIFY_DATA), 
                            &IdentifyDriveInfo
                            );
        if (EFI_ERROR(Status)) 
            break;
                  
        gBS->SetMem(IdentifyDriveInfo, sizeof (IDENTIFY_DATA), 0); 
        BufferSize = sizeof (IDENTIFY_DATA);
        Status = DiskInfo->Identify (
                            DiskInfo,
                            IdentifyDriveInfo,
                            &BufferSize
                            );
        if (EFI_ERROR(Status)) 
            break;
                                
        gBS->CopyMem(SerialNumber, IdentifyDriveInfo->Serial_Number_10, 20);
        SwapEntries (SerialNumber, 20);
        SerialNumber[20] = '\0';
        Trim(SerialNumber, SerialNumber);
                
        gBS->CopyMem(ModelNumber, IdentifyDriveInfo->Model_Number_27, 40);
        SwapEntries (ModelNumber, 40);
        ModelNumber[40] = '\0';                                 
        Trim(ModelNumber, ModelNumber);
                                
        EfiAsciiStrCpy(ModelSerialNumber, ModelNumber);
        EfiAsciiStrCat(ModelSerialNumber, "_");
        EfiAsciiStrCat(ModelSerialNumber, SerialNumber);        
        
        Status = EFI_SUCCESS;
        break;
    }   
    
    if (IdentifyDriveInfo != NULL)
        gBS->FreePool(IdentifyDriveInfo);
        
    return Status;
}                       

EFI_DEVICE_PATH_PROTOCOL *
GetDevicePathFromBBS(
    UINT8   DeviceType,
    CHAR8   *ModelSerialNumber
    
)
{
    EFI_LEGACY_BIOS_PROTOCOL        *LegacyBios;
    UINT16                          HddCount = 0;
    HDD_INFO                        *LocalHddInfo = NULL;
    UINT16                          BbsCount = 0;
    BBS_TABLE                       *BbsTable;
    EFI_STATUS                      Status;
    BBS_TABLE                       *BbsEntry;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePath = NULL;
    UINTN                           i;
    EFI_HANDLE                      Handle;
    UINTN                           DeviceIndex;
    UINTN                           DevicePriority;
    
    Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);      
    if (!EFI_ERROR (Status)) {      
        Status = LegacyBios->GetBbsInfo (
                              LegacyBios,
                              &HddCount, 
                              &LocalHddInfo, 
                              &BbsCount,
                              &BbsTable
                              );
        if (!EFI_ERROR (Status)) {
            //
            // Find match index by prioridy
            //
            DeviceIndex = (UINTN)-1;        
            DevicePriority = (UINTN)-1;
            for (i = 0; i < BbsCount; i++) {
                BbsEntry = BbsTable+i;
                if (BbsEntry->BootPriority == BBS_IGNORE_ENTRY)
                    continue;
                if (BbsEntry->DeviceType == DeviceType) {               
                    if (DevicePriority > BbsEntry->BootPriority) {
                        DevicePriority = BbsEntry->BootPriority;
                        DeviceIndex = i;                    
                    }                   
                }
            }
            
            //
            // Get model and serial number
            //
            if (DeviceIndex != (UINTN)-1) {
                BbsEntry = BbsTable + DeviceIndex;
                Handle = *(VOID**)(&BbsEntry->IBV1);            
                GetModelSerialNumber(Handle, ModelSerialNumber);
            }
        }           
    }   
    
    return DevicePath;
}

EFI_STATUS
NotifyPetAlert(
    EFI_EVENT           Event,
    VOID                *ParentImageHandle
)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    UINTN                           i;
    UINT16                          BootCurrent;
    UINTN                           VarSize;
    CHAR16                 			BootXXXX[16];
    EFI_LOAD_OPTION                 *BootOption = NULL;
    UINT8                           *pDP;
    BBS_BBS_DEVICE_PATH             *bDP;   // DP for BBS
    UINTN                           LegacyBoot = 1;
    EFI_DEVICE_PATH_PROTOCOL        *BootDevicePath = NULL;
    UINT8                           DeviceType;
    CHAR8                           ModelSerialNumber[64];
    EFI_ASF_BOOT_OPTIONS             *mAsfBootOptions;   
    EFI_ALERT_STANDARD_FORMAT_PROTOCOL  *Asf;
    EFI_GUID gEfiAlertStandardFormatProtocolGuid = EFI_ALERT_STANDARD_FORMAT_PROTOCOL_GUID;
                                                         
    Status = gBS->LocateProtocol (                       
                  &gEfiAlertStandardFormatProtocolGuid,  
                  NULL,                                  
                  &Asf                                   
                  );                                     
                                                         
    if (EFI_ERROR (Status)) return Status;                                            
    Status = Asf->GetBootOptions (Asf, &mAsfBootOptions);
    if (EFI_ERROR (Status)) mAsfBootOptions = NULL;
    
    EfiAsciiStrCpy(ModelSerialNumber, "");

    //
    // BootCurrent
    //
    VarSize = sizeof (UINT16);
    Status = gRT->GetVariable (
                L"BootCurrent",
                &gEfiGlobalVariableGuid,
                NULL,
                &VarSize,
                &BootCurrent
                );
    if (!EFI_ERROR (Status)) {
    } else {
        BootCurrent = 0;
    }

    SPrint(BootXXXX, sizeof(BootXXXX), L"Boot%04x", BootCurrent);

    VarSize = 0;
    Status = gRT->GetVariable (
                BootXXXX,
                &gEfiGlobalVariableGuid,
                NULL,
                &VarSize,
                NULL
            );
    if (Status != EFI_BUFFER_TOO_SMALL) {
        return Status;
    }
        
    //
    // Allocate Memory for BootXXXX
    //
    Status = gBS->AllocatePool(
                    EfiBootServicesData, 
                    VarSize, 
                    &BootOption
                    );
    ASSERT_EFI_ERROR(Status);

  	Status = gRT->GetVariable (
                    BootXXXX,
                    &gEfiGlobalVariableGuid,
                    NULL,
                    &VarSize,
                    BootOption
                );
    if (!EFI_ERROR (Status)) {                        
    	pDP = (UINT8*)(BootOption+1);
        pDP += (EfiStrLen((CHAR16*)pDP) + 1) * sizeof(CHAR16);            

       	BootDevicePath = EfiDuplicateDevicePath((EFI_DEVICE_PATH_PROTOCOL *)pDP);     
        
        //
        // Free Memory for BootXXXX
        //
        if (BootOption != NULL) {
            gBS->FreePool(BootOption);  
            BootOption = NULL;            
        }
    }
    
    if (BootDevicePath != NULL) {
      bDP = (BBS_BBS_DEVICE_PATH *)BootDevicePath;
      if (bDP->Header.Type == BBS_DEVICE_PATH && bDP->Header.SubType == BBS_BBS_DP) {                                     
        LegacyBoot = 1;
      } else {
        LegacyBoot = 0;
      }
    }

    //-------------------------------------------------------------------------
    // EFI Boot
    //-------------------------------------------------------------------------
    if (LegacyBoot == 0) {
        UINTN                       HandleCount;
        EFI_HANDLE                  *HandleBuffer;    
        EFI_HANDLE                  Handle;
        EFI_DEVICE_PATH_PROTOCOL    *DPath;
        EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
        EFI_DEVICE_PATH_PROTOCOL    *BootDeviceHandle;
  
        if (BootDevicePath == NULL) {
            //
            // Boot to EFI Shell
            //
            //Need Save "BootXXXX" in setup when launch entry after add boot option without Save
        }
        else {
            DevicePath = EfiDuplicateDevicePath(BootDevicePath);                   
            Status = gBS->LocateDevicePath (
                          &gEfiSimpleFileSystemProtocolGuid,
                          &DevicePath,
                          &BootDeviceHandle
                          );
            if (EFI_ERROR (Status)) {
                BootDeviceHandle = NULL;
            }

            Status = gBS->LocateHandleBuffer (
                      ByProtocol,
                      &gEfiSimpleFileSystemProtocolGuid,
                      NULL, 
                      &HandleCount,
                      &HandleBuffer
                      );
            if (!EFI_ERROR (Status)) {          
                for (i = 0; i < HandleCount; i ++) {
                    BOOLEAN st;
                    
                    Handle = HandleBuffer[i];
                    Status = gBS->HandleProtocol (
                                    Handle,
                                    &gEfiDevicePathProtocolGuid,
                                    &DPath
                                    );
                    if (!EFI_ERROR (Status)) {
                        //
                        // !!! CompareMedia only work with HDD & CD-ROM !!!
                        //
                        st = CompareMediaPathNode(BootDevicePath, DPath);
                        if (st == FALSE) {
                            //
                            // for USB MassStorage
                            //
                            if (Handle == BootDeviceHandle) {
                                st = TRUE;
                            }
                        }
                        
                        if (st) {
                            DeviceType = GetDeviceType(BootDevicePath);
                            
                            if (DeviceType == BBS_TYPE_HARDDRIVE) {
                                GetModelSerialNumber(Handle, ModelSerialNumber);
                            } else {
                                EfiAsciiStrCpy(ModelSerialNumber, "");
                            }
                            PetAlert(DeviceType, ModelSerialNumber);                                                                      
                        } 
                    }
                }
                if (HandleBuffer != NULL) {
                    gBS->FreePool (HandleBuffer);
                }
            }                   
        }
    }
    //-------------------------------------------------------------------------
    // Legacy Boot 
    //-------------------------------------------------------------------------
    else {
        if (BootDevicePath != NULL) {
          bDP = (BBS_BBS_DEVICE_PATH *)BootDevicePath;
          DeviceType = (UINT8) bDP->DeviceType;
        } else {
          DeviceType = BBS_TYPE_HARDDRIVE;
        }
        if ((mAsfBootOptions != NULL) && (mAsfBootOptions->SubCommand == 0x16)) {
            switch (mAsfBootOptions->SpecialCommand ) {
                case 1: DeviceType = BBS_TYPE_EMBEDDED_NETWORK;
                        break;
                case 2:
                case 3: DeviceType = BBS_TYPE_HARDDRIVE;
                        break;
                case 5: DeviceType = BBS_TYPE_CDROM;
                        break;
            }            
        }    

        switch (DeviceType) {
            case BBS_TYPE_EMBEDDED_NETWORK:
            case BBS_TYPE_FLOPPY:
            case BBS_TYPE_CDROM:
                PetAlert(DeviceType, NULL);         
                break;

            case BBS_TYPE_HARDDRIVE:
                GetDevicePathFromBBS(BBS_TYPE_HARDDRIVE, ModelSerialNumber);
                PetAlert(DeviceType, ModelSerialNumber);          
                break;
                
            default:
                //
                // Add code for process if run here
                //
                PetAlert(DeviceType, NULL);         
                break;
        }        
    }                

    return Status;
}

EFI_STATUS
AmtPetAlertReadyToBoot(
    EFI_EVENT           Event,
    VOID                *ParentImageHandle
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    
    Status = NotifyPetAlert(Event, ParentImageHandle);
                 
    return Status;
}

EFI_STATUS
AmtPetAlertLegacyBoot(
    EFI_EVENT           Event,
    VOID                *ParentImageHandle
)
{
    EFI_STATUS Status = EFI_SUCCESS;
     
    return Status;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
