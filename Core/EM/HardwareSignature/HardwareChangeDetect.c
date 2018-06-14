//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/HardwareSignatureManagement/HardwareChangeDetect.c 9     4/22/13 8:39a Albertlin $
//
// $Revision: 9 $
//
// $Date: 4/22/13 8:39a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HardwareSignatureManagement/HardwareChangeDetect.c $
// 
// 9     4/22/13 8:39a Albertlin
// [TAG]           EIP121317
// [Category]      Not Specified
// [Description]   Can not enter Safe mode via PBR with onboard graphics
// on SharkBay platform.
// [Files]         HardwareChangeDetect.c
// 
// 8     3/01/13 3:30a Albertlin
// [TAG]           EIP115994
// [Category]      Improvement
// [Description]   Add CRC32 description.
// [Files]         HardwareChangeDetect.c
// 
// 7     1/10/13 10:19p Albertlin
// [TAG]           EIP109014
// [Category]      Improvement
// [Description]   Currently, HardwareSignature module report signature by
// changed count.But it cause the same hardware may have different
// signature.
// For solve this issue, BIOS should report signature by hardware config.
// [Files]         HardwareChangeDetect.c HardwareSignatureManagement.c
// HardwareSignatureManagement.sdl HardwareChangeProtocol.h
// 
// 6     12/11/12 1:46a Sophiachen
// [TAG]  		EIP105523
// [Category]  	New Feature
// [Description]  	Record the disk configuration data to check the
// connection change of disk.
// [Files]  		HardwareChangeDetect.c, HardwareSignatureManagement.c,
// HardwareChangeProtocol.h
// 
// 5     12/07/12 8:02a Sophiachen
// [TAG]  		EIP108596
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	There is a build error when x64_build is off.
// [RootCause]  	Fail to do the shift operation of 64 bits in IA32 mode.
// [Solution]  	Use the functions Shl64() and Shr64() to do the shift
// operation.
// [Files]  		HardwareChangeDetect.c, HardwareSignatureManagement.c
// 
// 4     11/21/12 1:42a Sophiachen
// [TAG]  		EIP105154
// [Category]  	Improvement
// [Description]  	Do the error check early in the function
// GetResolutionData().
// [Files]  		HardwareChangeDetect.c
// 
// 3     11/20/12 8:27a Sophiachen
// [TAG]  		EIP105154
// [Category]  	New Feature
// [Description]  	Record the video configuration data to check the
// connection change of monitor. 
// [Files]  		HardwareChangeDetect.c, HardwareSignatureManagement.c,
// HardwareChangeProtocol.h
// 
// 2     10/26/12 3:04a Sophiachen
// Use PciIo protocol to get Vendor ID and Device ID.
// 
// 1     9/25/12 8:57a Sophiachen
// [TAG]  		EIP96258
// [Category]  	New Feature
// [Description]  	Update the Hardware Signature of the ACPI table FACS
// field can notify ACPI OS whether any hardware configuration change.
// [Files]  		HardwareSignatureManagement.cif
// HardwareSignatureManagement.mak
// HardwareSignatureManagement.dxs
// HardwareSignatureManagement.sdl
// HardwareSignatureManagement.c
// HardwareChangeDetect.c
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: HardwareChangeDetect.c
//
// Description: This file will detect the current Hardware configuration.
//
//<AMI_FHDR_END>
//**********************************************************************

//---------------------------------------------------------------------------
#include <Efi.h>
#include <Dxe.h>
#include <AmiDxeLib.h>
#include <token.h>
#include <Protocol\HardwareChangeProtocol.h>
#include "GenericSio.h"
#include <Protocol\PciIo.h>
#include <AmiCspLib.h>
#include <Protocol\UsbIo.h>
#include <Protocol\DevicePath.h>
#include <Protocol\GraphicsOutput.h>
#include <Protocol\EdidDiscovered.h>
#include <Protocol\PDiskInfo.h>
#include <Protocol\BlockIo.h>
#include <Protocol\PIDEController.h>
#include <Protocol\PIDEBus.h>

//---------------------------------------------------------------------------
#define IsRestoreMemoryType(MemoryType) \
    ((MemoryType) == EfiACPIReclaimMemory || \
    (MemoryType) == EfiACPIMemoryNVS || \
    (MemoryType) == EfiRuntimeServicesCode || \
    (MemoryType) == EfiRuntimeServicesData || \
    (MemoryType) == EfiReservedMemoryType )

#define VESA_BIOS_EXTENSIONS_EDID_BLOCK_SIZE 128
//---------------------------------------------------------------------------
   
#if HARDWARE_SIGNATURE_DEBUG_MESSAGES  
CHAR8 *gMemMapType[] = {
    "reserved  ",
    "LoaderCode",
    "LoaderData",
    "BS_code   ",
    "BS_data   ",
    "RT_code   ",
    "RT_data   ",
    "available ",
    "Unusable  ",
    "ACPI_recl ",
    "ACPI_NVS  ",
    "MemMapIO  ",
    "MemPortIO ",
    "PAL_code  "
};
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: IsDifferentMemorySize
//
// Description:
//  This function compares the current and previous memory sizes.
//
// Input:
//  IN UINT32 CurMemorySizeMb - Current memory size (MB)
//  IN UINT32 PreMemorySizeMb - Previous memory size (MB)
//
// Output:
//  BOOLEAN
//    TRUE - Memory sizes are different.
//    FALSE - Memory sizes are similar.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN 
IsDifferentMemorySize (
    IN UINT32 CurMemorySizeMb,
    IN UINT32 PreMemorySizeMb )
{
    BOOLEAN bDifferent = FALSE;

    HWSIG_TRACE((-1,"Diff Mem Size - Cur:0x%x MB, Pre:0x%x MB\n", CurMemorySizeMb, PreMemorySizeMb));

    if(CurMemorySizeMb > PreMemorySizeMb)
    {
        if((CurMemorySizeMb - PreMemorySizeMb) >= 
            THRESHOLD_OF_DIFFERENT_MEMORY_SIZE)
        {  
            bDifferent = TRUE;
        }
    }
    else if(CurMemorySizeMb < PreMemorySizeMb)
    {
        if((PreMemorySizeMb - CurMemorySizeMb) >= 
            THRESHOLD_OF_DIFFERENT_MEMORY_SIZE)
        {
            bDifferent = TRUE;
        }
    }

    return bDifferent;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:  GetMemMapData
//
// Description:
//  This function detects the current memory size and memory map data.
//
// Input:
//  IN OUT HW_MEMORY_MAP_DATA *pMemMapConfigData - Current memory map data
//                                                 and memory size(MB)
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - Detect the current memory map data successfully.
//    Other - Get MemoryMap failed or allocate pool failed.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
GetMemMapData (
    IN OUT HW_MEMORY_MAP_DATA *pMemMapConfigData )
{
    EFI_STATUS                Status = EFI_NOT_READY;
    UINTN                     MemMapSize = 0;
    EFI_MEMORY_DESCRIPTOR     *MemMap = NULL;
    EFI_MEMORY_DESCRIPTOR     *OrigMemMap = NULL;
    UINT64                    PageCount[EfiMaxMemoryType] = {0};
    UINTN                     MapKey = 0;
    UINTN                     DescriptorSize = 0;
    UINT32                    DescriptorVersion = 0;
    UINTN                     Index = 0;
    UINT64                    TotalMemory = 0;
    UINTN                     AllocateMemMapSize = 0;    
    EFI_PHYSICAL_ADDRESS      EndAddress = 0;
    EFI_PHYSICAL_ADDRESS      StartAddress = 0;
    UINT64                    EntrySize = 0;
    UINT8                     EndAddrCheckSum = 0;
    UINT8                     StartAddrCheckSum = 0;
    UINT32                    AddrData = 0; 
    UINT8                     MemCheckSum = 0;
    //Detect the memory map only once.  
    static BOOLEAN            IsMemoryMapDetected = FALSE;
    static HW_MEMORY_MAP_DATA DetectMemMapConfigData;
	UINT32                    LogVal = 0;

    if(pMemMapConfigData == NULL)
    {
        Status = EFI_INVALID_PARAMETER;
        goto GetMemSizeFinish;        
    }

    //To detect the memory map only once
    if(!IsMemoryMapDetected)    
    {
        MemSet(&DetectMemMapConfigData, sizeof(HW_MEMORY_MAP_DATA), 0);
        MemSet(pMemMapConfigData, sizeof(HW_MEMORY_MAP_DATA), 0);
    } 
    else
    {
        MemCpy(pMemMapConfigData, &DetectMemMapConfigData, sizeof(HW_MEMORY_MAP_DATA));
        Status = EFI_SUCCESS;
        goto GetMemSizeFinish;
    }
    
    Status = pBS->GetMemoryMap (&MemMapSize, 
                                MemMap, 
                                &MapKey, 
                                &DescriptorSize, 
                                &DescriptorVersion);

    if (Status != EFI_BUFFER_TOO_SMALL)
    {
        Status = EFI_NOT_READY;
        goto GetMemSizeFinish;
    }
  
    MemMapSize += EFI_PAGE_SIZE;
    AllocateMemMapSize = MemMapSize;
    
    Status = pBS->AllocatePool (
                  EfiBootServicesData,
                  AllocateMemMapSize,
                  (VOID**)&MemMap
                  );

    if (EFI_ERROR (Status))
    {
        goto GetMemSizeFinish;
    }
  
    OrigMemMap = MemMap;
    if (OrigMemMap == NULL)
    {
        Status = EFI_OUT_OF_RESOURCES;
        goto GetMemSizeFinish;
    }
  
    Status = pBS->GetMemoryMap (&MemMapSize, 
                                MemMap, 
                                &MapKey, 
                                &DescriptorSize, 
                                &DescriptorVersion);

    if (EFI_ERROR (Status))
    {
        goto GetMemSizeFinish;
    }

    for (Index = 0; Index < EfiMaxMemoryType; Index++)
    {
        PageCount[Index] = 0;
    } 

    StartAddrCheckSum = 0;
    EndAddrCheckSum = 0;
    MemCheckSum =0;
    for (Index = 0; Index < MemMapSize/DescriptorSize; Index++)
    {
        if( IsRestoreMemoryType(MemMap->Type) )
        {

            EntrySize = Shl64(MemMap->NumberOfPages, EFI_PAGE_SHIFT);
            StartAddress = MemMap->PhysicalStart;
            EndAddress = MemMap->PhysicalStart + EntrySize -1;

            AddrData = 0;
            AddrData = (UINT32)( Shr64(EndAddress, EFI_PAGE_SHIFT));
            EndAddrCheckSum += (UINT8)(AddrData);
            EndAddrCheckSum += (UINT8)(AddrData >> 8);
            EndAddrCheckSum += (UINT8)(AddrData >> 16);
          
            AddrData = 0;
            AddrData = (UINT32)( Shr64(StartAddress, EFI_PAGE_SHIFT));
            StartAddrCheckSum += (UINT8)AddrData;
            StartAddrCheckSum += (UINT8)(AddrData >> 8);
            StartAddrCheckSum += (UINT8)(AddrData >> 16);

//	            HWSIG_TRACE ((-1,"%a %016lX - %016lX: # %08lX %016lX\n", gMemMapType[MemMap->Type % EfiMaxMemoryType], StartAddress, EndAddress, MemMap->NumberOfPages, MemMap->Attribute));

        }  
        
        PageCount[MemMap->Type % EfiMaxMemoryType] += MemMap->NumberOfPages;
        MemMap = (EFI_MEMORY_DESCRIPTOR *)((UINTN)MemMap + DescriptorSize);
    }

    MemCheckSum = (UINT8)(StartAddrCheckSum+EndAddrCheckSum);
    HWSIG_TRACE((-1,"MemCheckSum:0x%x\n",   MemCheckSum));

    DetectMemMapConfigData.MemMapCheckSum = MemCheckSum;

    for (Index = 0, TotalMemory = 0; Index < EfiMaxMemoryType; Index++)
    {
#if HARDWARE_SIGNATURE_DEBUG_MESSAGES
        HWSIG_TRACE((-1,"%a  : 0x%lx Pages\n", gMemMapType[Index], PageCount[Index]));
#endif
        if (PageCount[Index] == 0)
            continue; 
    
        if ((Index == EfiLoaderCode) || (Index == EfiLoaderData) ||
          (Index == EfiBootServicesCode) || (Index == EfiBootServicesData) ||
          (Index == EfiRuntimeServicesCode) || (Index == EfiRuntimeServicesData) ||
          (Index == EfiConventionalMemory) || (Index == EfiACPIReclaimMemory) ||
          (Index == EfiACPIMemoryNVS) || (Index == EfiPalCode))
        {
            // Count total memory
            TotalMemory += PageCount[Index];
        }
      
    }

	TotalMemory += PageCount[EfiReservedMemoryType]; 
	DetectMemMapConfigData.MemoryMbSize = \
        (UINT32)(Shr64(TotalMemory, 8));//MB
	
    //When all of the DetectMemMapConfigData are saved, this variable is 
    //changed to "TRUE" 
    IsMemoryMapDetected = TRUE; 
 
    MemCpy(pMemMapConfigData, &DetectMemMapConfigData, sizeof(HW_MEMORY_MAP_DATA));

    HWSIG_TRACE((-1,"GetMemMapData - MemoryMbSize:0x%lx MB\n", pMemMapConfigData->MemoryMbSize));

	//get log2 value for memory size and set it to memory
	while(pMemMapConfigData->MemoryMbSize)
	{	
		LogVal++;
		(pMemMapConfigData->MemoryMbSize) >>= 1;
	}
	
	pMemMapConfigData->MemoryMbSize = 1<<LogVal;
	
GetMemSizeFinish:
    if (OrigMemMap != NULL)
    {
        pBS->FreePool(OrigMemMap);    
    }
  
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: DetectPS2KeyboardMouseState
//
// Description:
//  This function gets the SIO variable from NVRAM. It records the PS2 KB/
//  Mouse are present or not.
//
// Input:
//  IN     HW_CONFIG_TYPE ConfigType- Current Type is PS2 KB or PS2 Mouse
//  IN OUT BOOLEAN        *bPresent - Current Type is present or not.
//
// Output:
//  EFI_STATUS
//    EFI_NOT_FOUND - SIO variable doesn't exist.
//    EFI_SUCCESS - Get SIO variable successfully.
//
//  Notes:
//   The tokens "DETECT_PS2_MOUSE" and "DETECT_PS2_KEYBOARD" need to enable. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
DetectPS2KeyboardMouseState (
  IN HW_CONFIG_TYPE ConfigType, 
  IN OUT BOOLEAN *bPresent )
{
    EFI_GUID       SioDevStatusVarGuid = SIO_DEV_STATUS_VAR_GUID;
    UINTN          SioDevStatusVarSize = sizeof(SIO_DEV_STATUS);
    SIO_DEV_STATUS SioDevStatus;
    UINT32         SioDevStatusVarAttributes = 0;
    EFI_STATUS     Status;

    //
    // Get the SIO variable.
    //
    Status = pRS->GetVariable( SIO_DEV_STATUS_VAR_NAME, 
                                &SioDevStatusVarGuid, 
                                &SioDevStatusVarAttributes,
                                &SioDevStatusVarSize, 
                                &SioDevStatus.DEV_STATUS);


    if(Status == EFI_NOT_FOUND)
    {
        if(ConfigType == Ps2KeyboardConfigType)
        {
            *bPresent = FALSE;
        }
       
        if(ConfigType == Ps2MouseConfigType)
        {
            *bPresent = FALSE;
        }
        return Status;
    }
    
    if(ConfigType == Ps2KeyboardConfigType)
    {
        HWSIG_TRACE((-1,"SioDevStatus.Key60_64:%d, %r\n",SioDevStatus.Key60_64, Status));

        if(SioDevStatus.Key60_64 == 1)
        {   //PS2 Keyboard is present 
            *bPresent = TRUE;
        }
        else
        {
            //no PS2 Keyboard
            *bPresent = FALSE;
        }
    }

    if(ConfigType == Ps2MouseConfigType)
    {
        HWSIG_TRACE((-1,"SioDevStatus.Ps2Mouse:%d, %r\n", SioDevStatus.Ps2Mouse, Status));

        if(SioDevStatus.Ps2Mouse == 1)
        {   //PS2 Mouse is present 
            *bPresent = TRUE;
        }
        else
        {
            //no PS2 Mouse
            *bPresent = FALSE;
        }
    }

    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:  GetPciDeviceData
//
// Description:
//  This function detects the current PCI number and calculate the checksum  
//  of Bus number/Device number/Function number, VID/DID.
//
// Input:
//  IN OUT HW_PCI_DATA *pHardwarePciData -Get current PCI data.
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - Detect the current PCI data successfully.
//    EFI_INVALID_PARAMETER - input data pHardwarePciData is NULL 
//    Other - Get PCI data failed.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
GetPciDeviceData (
    IN OUT HW_PCI_DATA *pHardwarePciData )
{
    EFI_STATUS          Status;
    EFI_HANDLE          *HandleBuffer;
    UINTN               HandleCount = 0;
    EFI_PCI_IO_PROTOCOL *PciIo;
    EFI_GUID            PciIoProtocolGuid = EFI_PCI_IO_PROTOCOL_GUID;
    UINT8               DevNum;
    UINT8               FuncNum;
    UINT16              BusNum = 0;
    UINT16              PciNum = 0;
    UINT16              Index;
    UINTN               PciSeg, PciBus, PciDev, PciFun;
    UINT16              Vid, Did;
    UINT8               BdfChecksum, VidDidChecksum;   
    UINT32				VidDid; 
      
    if(pHardwarePciData == NULL)
        return EFI_INVALID_PARAMETER;

    MemSet(pHardwarePciData, sizeof(HW_PCI_DATA), 0);
    
    // Locate handle buffer for PCI Io Protocol.
    Status = pBS->LocateHandleBuffer( ByProtocol, \
                                  &PciIoProtocolGuid, \
                                  NULL, \
                                  &HandleCount, \
                                  &HandleBuffer   );
    if (EFI_ERROR(Status)) 
        return Status;

    Vid = 0; 
    Did = 0;
    BdfChecksum = 0;
    VidDidChecksum = 0;

    for ( Index=0; Index < HandleCount; Index++ ) {

        // Handle PCI Io Protocol.
        Status = pBS->HandleProtocol ( HandleBuffer[Index], \
                                   &PciIoProtocolGuid, \
                                   &PciIo );
        if (EFI_ERROR(Status)) 
            return Status;

        // Get PCI Io location.
        Status = PciIo->GetLocation(PciIo, &PciSeg, &PciBus, &PciDev, &PciFun);
        if (EFI_ERROR(Status)) 
            return Status;

        // Skip on-board device.
        if (PciBus == 0) 
            continue;

        Status=PciIo->Pci.Read( PciIo, EfiPciIoWidthUint32, 0, 1, &VidDid);
		
        if (EFI_ERROR (Status))
            continue;
			
        BusNum = (UINT16)PciBus;
        DevNum = (UINT8)PciDev;
        FuncNum = (UINT8)PciFun;
        BdfChecksum += ((UINT8)PciBus + (UINT8)PciDev + (UINT8)PciFun);
    
        // Record the PCI Vendor ID.
        Vid = (UINT16)(VidDid);
        // Record the PCI Device ID.
        Did = (UINT16)(VidDid >> 16);

        VidDidChecksum += ((UINT8)Vid + (UINT8)(Vid >> 8));
        VidDidChecksum += ((UINT8)Did + (UINT8)(Did >> 8));

        HWSIG_TRACE ((-1, "GetPciDeviceData: B: %X , D: %X, F: %X, Vid:%X, Did:%X\n", PciBus, PciDev, PciFun, Vid, Did));
       
        PciNum++;
    }

    pHardwarePciData->PciNum = PciNum;
    pHardwarePciData->BdfChecksum = 0x100 - BdfChecksum;
    pHardwarePciData->VidDidChecksum = 0x100 - VidDidChecksum;

    HWSIG_TRACE ((-1, "Pci#:%d, Checksum - BDF:%x, VID DID:%x \n",pHardwarePciData->PciNum, pHardwarePciData->BdfChecksum, pHardwarePciData->VidDidChecksum));
    
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:  GetUsbDeviceData
//
// Description:
//  This function detects the current number of the USB devices and calculate  
//  the checksum of Parent Port Num/Interface Num, and VID/PID.
//
// Input:
//  IN OUT HW_USB_DATA *pHardwareUsbData -Get current USB data.
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - Detect the current USB data successfully.
//    EFI_INVALID_PARAMETER - input data pHardwareUsbData is NULL 
//    Other - Get USB data failed.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
GetUsbDeviceData (
    IN OUT HW_USB_DATA *pHardwareUsbData )
{
    EFI_STATUS                Status;
    EFI_HANDLE                *HandleBuffer;
    UINTN                     HandleCount = 0;
    EFI_GUID                  EfiUsbIoProtocolGuid = EFI_USB_IO_PROTOCOL_GUID;
    EFI_USB_IO_PROTOCOL       *UsbIo;      
    EFI_USB_DEVICE_DESCRIPTOR DevDes;        
    UINT16                    Vid, Pid;
    UINT8                     VidPidChecksum;   
    EFI_GUID                  EfiDevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
    EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL  *DevicePathNode;
    UINT8                     PortNumInterfaceNumChecksum = 0;
    UINT8                     InterfaceNumber, ParentPortNumber;
    UINT16                    UsbNum = 0;
    UINT16                    Index;

    if(pHardwareUsbData == NULL)
        return EFI_INVALID_PARAMETER;

    MemSet(pHardwareUsbData, sizeof(HW_USB_DATA), 0);
    
    // Locate handle buffer for USB Io Protocol
    Status = pBS->LocateHandleBuffer( ByProtocol, \
                                  &EfiUsbIoProtocolGuid, \
                                  NULL, \
                                  &HandleCount, \
                                  &HandleBuffer   );
    if (EFI_ERROR(Status)) 
        return Status;

    Vid = 0; 
    Pid = 0;
    InterfaceNumber = 0; 
    ParentPortNumber = 0;
    VidPidChecksum = 0;
    PortNumInterfaceNumChecksum = 0;

    for ( Index=0; Index < HandleCount; Index++ ) {

        // Handle USB Io Protocol
        Status = pBS->HandleProtocol ( HandleBuffer[Index], \
                                   &EfiUsbIoProtocolGuid, \
                                   &UsbIo );
        
        if (EFI_ERROR(Status)) 
            return Status;

        // Get USB Io Descriptor
        Status = UsbIo->UsbGetDeviceDescriptor(UsbIo, &DevDes);
        if (EFI_ERROR(Status)) 
            return Status;
    
        Vid = DevDes.IdVendor;
        Pid = DevDes.IdProduct;

        VidPidChecksum += ((UINT8)Vid + (UINT8)(Vid >> 8));
        VidPidChecksum += ((UINT8)Pid + (UINT8)(Pid >> 8));

        UsbNum++;
        // Get USB DevicePath
        Status = pBS->HandleProtocol ( HandleBuffer[Index], \
                                   &EfiDevicePathProtocolGuid, \
                                   (VOID *)&DevicePath );
   
        if (EFI_ERROR(Status)) 
            continue;

        // Is USB Device Path ?
        DevicePathNode = DevicePath;
        while ( !isEndNode ( DevicePathNode ) ) {

            if(DevicePathNode->Type == MESSAGING_DEVICE_PATH) {
                if(DevicePathNode->SubType == MSG_USB_DP) {     
              
                    ParentPortNumber = ((USB_DEVICE_PATH*)DevicePathNode)->ParentPortNumber;
                    InterfaceNumber = ((USB_DEVICE_PATH*)DevicePathNode)->InterfaceNumber;

                    PortNumInterfaceNumChecksum += (UINT8)(ParentPortNumber + InterfaceNumber);
                    HWSIG_TRACE ((-1, "Index:%x - USB(0x%x, 0x%x)\n", Index, ParentPortNumber, InterfaceNumber));
                }
                
            } 
            DevicePathNode = NEXT_NODE ( DevicePathNode );
        }
               
    }

    pHardwareUsbData->UsbNum = UsbNum;
    pHardwareUsbData->VidPidChecksum= 0x100 - VidPidChecksum;
    pHardwareUsbData->PortNumInterfaceNumChecksum= 0x100 - PortNumInterfaceNumChecksum;

    HWSIG_TRACE ((-1, "Usb#:%d, Checksum -VID DID:%x , PortNum_InterNum:%x\n",pHardwareUsbData->UsbNum, pHardwareUsbData->VidPidChecksum, pHardwareUsbData->PortNumInterfaceNumChecksum));
    
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:  GetEdidData
//
// Description:
//  This function gets the checksum data of EDID.
//
// Input:
//  IN OUT HW_VIDEO_DATA *pHardwareVideoData - Record the EdidCheckNum of   
//                                             current Video data.
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - Get the checksum data of EDID successfully.
//    EFI_NOT_FOUND - EfiEdidDiscoveredProtocolGuid interface not found.
//    EFI_INVALID_PARAMETER - Invalid parameter.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
GetEdidData(
    IN OUT HW_VIDEO_DATA *pHardwareVideoData )
{
    EFI_STATUS                         Status = EFI_NOT_FOUND;    
    UINT8                              EdidCheckSum = 0;  
    UINT32                             index = 0;
    EFI_GUID                           EfiEdidDiscoveredProtocolGuid = EFI_EDID_DISCOVERED_PROTOCOL_GUID;
    EFI_EDID_DISCOVERED_PROTOCOL       *EdidDiscoveredProtocol;

    pHardwareVideoData->EdidCheckNum = 0;

    Status = pBS->LocateProtocol (
                  &EfiEdidDiscoveredProtocolGuid,
                  NULL,
                  &EdidDiscoveredProtocol
                  );
    
    HWSIG_TRACE((-1,"Locate EDID discovered protocol:%r\n", Status));

    if (EFI_ERROR (Status)) 
        return Status;

    HWSIG_TRACE((-1,"EDID Size:%d\n", EdidDiscoveredProtocol->SizeOfEdid));

    Status = EFI_NOT_FOUND; 
    if(EdidDiscoveredProtocol->SizeOfEdid != 0 && EdidDiscoveredProtocol->Edid != NULL){
        if( EdidDiscoveredProtocol->SizeOfEdid == VESA_BIOS_EXTENSIONS_EDID_BLOCK_SIZE){
            index = EdidDiscoveredProtocol->SizeOfEdid -1;
            EdidCheckSum = EdidDiscoveredProtocol->Edid[index];
            Status = EFI_SUCCESS;    
        }        
    }

    if(!EFI_ERROR(Status)){
        pHardwareVideoData->EdidCheckNum = EdidCheckSum;
        HWSIG_TRACE((-1,"EdidCheckNum:0x%x\n", EdidCheckSum));

    }    

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:  GetResolutionData
//
// Description:
//  This function gets all resolution data and calculates the the checksum of   
//  resolution data.
//
// Input:
//  IN OUT HW_VIDEO_DATA *pHardwareVideoData -Record the ResolutionChecksum of  
//                                            current Video data.
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - Get all resolution data and calculate checksum successfully.
//    EFI_NOT_FOUND - EfiGraphicsOutputProtocolGuid interface not found.
//    EFI_INVALID_PARAMETER - Invalid parameter.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
GetResolutionData(
    IN OUT HW_VIDEO_DATA *pHardwareVideoData )
{
    EFI_STATUS                                   Status = EFI_NOT_FOUND;
    UINT8                                        TotalCheckSum = 0;
    UINT8                                        CheckSum = 0;
	UINT8							             k;
    EFI_GUID                                     EfiGraphicsOutputProtocolGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL                 *GraphicsOutput;
    UINT32                                       TmpSum = 0;
    BOOLEAN                                      bGetData = TRUE;

    pHardwareVideoData->ResolutionChecksum = 0;

    
    Status = pBS->LocateProtocol (
                  &EfiGraphicsOutputProtocolGuid,
                  NULL,
                  &GraphicsOutput
                  );
    

    if(EFI_ERROR (Status))
    {
        bGetData = FALSE;
    }
    else 
    {   
        // 1. TmpSum: Sum of HorizontalResolution + VerticalResolution
        // 2. CheckSum: the checksum of TmpSum
        // 3. TotalCheckSum: sum of CheckSum
            TmpSum = GraphicsOutput->Mode->Info->HorizontalResolution + \
		GraphicsOutput->Mode->Info->VerticalResolution;

            CheckSum = (UINT8)TmpSum;
         	for( k = 1; k < sizeof(TmpSum); k++) {    
                TmpSum = TmpSum >> 8;
                CheckSum = CheckSum + (UINT8)TmpSum;
            }

            TotalCheckSum = TotalCheckSum + CheckSum;
    }   

    if(bGetData)
    {
        TotalCheckSum = 0x100 - TotalCheckSum;
        HWSIG_TRACE((-1,"Resolution TotalCheckSum:0x%x\n", TotalCheckSum));
        pHardwareVideoData->ResolutionChecksum = TotalCheckSum;
        Status = EFI_SUCCESS;
    }
    else
    {
        Status = EFI_NOT_FOUND;
    }
    
    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:  GetVideoData
//
// Description:
//  This function gets the checksum of EDID and calculates the checksum 
//  of all resolution data.
//
// Input:
//  IN OUT HW_VIDEO_DATA *pHardwareVideoData -Get current Video data.
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - Get the current Video data successfully.
//    EFI_UNSUPPORTED - Get the current Video data failed. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
GetVideoData(
    OUT HW_VIDEO_DATA *pHardwareVideoData )
{
    EFI_STATUS                    Status = EFI_NOT_FOUND;
    BOOLEAN                       bSuccess = FALSE;
    
    Status = GetEdidData(pHardwareVideoData);
    HWSIG_TRACE((-1,"GetEdidData: %r\n", Status));

    if(!EFI_ERROR(Status))
        bSuccess = TRUE;
    
    Status = GetResolutionData(pHardwareVideoData);
    HWSIG_TRACE((-1,"GetResolutionData: %r\n", Status));

    if(!EFI_ERROR(Status))
        bSuccess = TRUE;
        
    if(bSuccess)
        return EFI_SUCCESS;

    return EFI_UNSUPPORTED;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CRC32
//
// Description: A cyclic redundancy check (CRC) is an error-detecting code 
// commonly used in storage devices to detect accidental changes to raw data.
//
// Input:
//  IN  UINT8   *fpData - Pointer to the start of data that will be calculated.
//  IN  UINT16  Length - The length of data 
//  IN  UINT8   ExtenData - The count(byte) of zero data that will be included
//                          when calculate CRC32.
//
// Output:
//  UINT32  CRC32 checksum
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
CRC32 (
    IN UINT8  *fpData,
    IN UINT16 Length,
    IN UINT8  ExtenData )
{
    UINT32  CRC32Table[256] = {  
        0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
        0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
        0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
        0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
        0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
        0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
        0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
        0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
        0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
        0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
        0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
        0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
        0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
        0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
        0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
        0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
        0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
        0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
        0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
        0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
        0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
        0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
        0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
        0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
        0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
        0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
        0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
        0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
        0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
        0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
        0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
        0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
        0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
        0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
        0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
        0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
        0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
        0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
        0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
        0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
        0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
        0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
        0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
        0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
        0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
        0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
        0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
        0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
        0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
        0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
        0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
        0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
        0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
        0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
        0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
        0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
        0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
        0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
        0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
        0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
        0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
        0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
        0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
        0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d };
	
    UINT32  CRC = 0xFFFFFFFF;
    UINT16  i; 

    for ( i=0; i<Length; i++)
        CRC = CRC32Table[(CRC^(*(fpData+i)))& 0xff] ^ (CRC>>8);
	
    // include pad into checksum, pad value is 0
    for ( i=0; i<ExtenData; i++)
        CRC = CRC32Table[(CRC^0)& 0xff] ^ (CRC>>8);
	
    return ~CRC;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetDiskInfoData
//
// Description: Calculate the disk checksum , include port number and serial number.
// Calculate the CRC32 checksum with port number and serial number of all disks.
//
// Input:
//  OUT HW_DISK_DATA *pHardwareDiskData - Get current Disk data.
//
// Output:
//  HW_DISK_DATA  *pHardwareDiskData
//    CRC32 checksum - Get the current Disk data successfully.
//    ~(CDSchecksum of previous disk data) - Get the current Disk data failure.                                           
//
//  EFI_STATUS
//    EFI_SUCCESS - Get the current Disk data successfully.
//    EFI_NOT_READY - Get the current Disk data unsuccessfully.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
GetDiskInfoData(
    OUT HW_DISK_DATA *pHardwareDiskData)
{
	EFI_GUID	           EfiDiskInfoProtocolGuid = EFI_DISK_INFO_PROTOCOL_GUID;
	EFI_HANDLE	           *HandleBuffer;
	EFI_DISK_INFO_PROTOCOL *DiskInfo;	
	IDENTIFY_DATA	       *IdentifyDriveInfo = NULL;
	DISK_STRUCTURE	       *DiskStructure;
	EFI_STATUS	           Status = EFI_NOT_FOUND;
	UINTN	               NumberOfDISKHandles = 0;
	UINT8	               Index;
	UINT32	               IdeChannel; 
	UINT32	               IdeDevice;
	UINT32	               BufferSize;

	Status = pBS->LocateHandleBuffer(
					ByProtocol,
					&EfiDiskInfoProtocolGuid,
					NULL,
					&NumberOfDISKHandles,
					&HandleBuffer
				);
	if (EFI_ERROR(Status))
	{
		pHardwareDiskData->CDSchecksum = 0xff;
		pBS->FreePool(HandleBuffer);
		return EFI_NOT_READY;
	}

	Status = pBS->AllocatePool(
					EfiBootServicesData, 
					sizeof (IDENTIFY_DATA), 
					&IdentifyDriveInfo
				);
	if (EFI_ERROR(Status))
	{
		pHardwareDiskData->CDSchecksum = 0xff;
		pBS->FreePool(HandleBuffer);
		pBS->FreePool(IdentifyDriveInfo);
		return EFI_NOT_READY;
	}
	
	DiskStructure = MallocZ (NumberOfDISKHandles*sizeof (DISK_STRUCTURE));

	BufferSize = sizeof (IDENTIFY_DATA);	

	for (Index = 0; Index < NumberOfDISKHandles; Index++)
	{
		Status = pBS->HandleProtocol (
					HandleBuffer[Index],
					&EfiDiskInfoProtocolGuid,
					&DiskInfo
					);
		if (EFI_ERROR(Status))
		{
			pHardwareDiskData->CDSchecksum = 0xff;
			pBS->FreePool(HandleBuffer);
			pBS->FreePool(IdentifyDriveInfo);
			pBS->FreePool(DiskStructure);
			return EFI_NOT_READY;
		}
		
		Status = DiskInfo->WhichIde(DiskInfo,&IdeChannel,&IdeDevice);
		if (EFI_ERROR(Status))	
		{
			pHardwareDiskData->CDSchecksum = 0xff;
			pBS->FreePool(HandleBuffer);
			pBS->FreePool(IdentifyDriveInfo);
			pBS->FreePool(DiskStructure);
			return EFI_NOT_READY;
		}
	
		Status = DiskInfo->Identify(DiskInfo,IdentifyDriveInfo,&BufferSize);
		if (EFI_ERROR(Status))	
		{
			pHardwareDiskData->CDSchecksum = 0xff;
			pBS->FreePool(HandleBuffer);
			pBS->FreePool(IdentifyDriveInfo);
			pBS->FreePool(DiskStructure);
			return EFI_NOT_READY;
		}
		
		DiskStructure[Index].Portnumber = IdeChannel;
		
		MemCpy( &DiskStructure[Index].Serialnumber[0], &IdentifyDriveInfo->Serial_Number_10[0], 20);		
		
	}	
	pHardwareDiskData->CDSchecksum = CRC32(&DiskStructure[0].Portnumber,(UINT16)(NumberOfDISKHandles*sizeof(DISK_STRUCTURE)),0);
	
	pBS->FreePool(DiskStructure);
	pBS->FreePool(HandleBuffer);
	pBS->FreePool(IdentifyDriveInfo);
	
	return EFI_SUCCESS;

}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
