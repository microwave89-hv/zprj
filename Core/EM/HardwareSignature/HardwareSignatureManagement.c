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
// $Header: /Alaska/SOURCE/Modules/HardwareSignatureManagement/HardwareSignatureManagement.c 12    1/15/14 2:27a Albertlin $
//
// $Revision: 12 $
//
// $Date: 1/15/14 2:27a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HardwareSignatureManagement/HardwareSignatureManagement.c $
// 
// 12    1/15/14 2:27a Albertlin
// [TAG]           EIP147244 
// [Category]      Not Specified
// [Description]   Delay the HardwareSignature excutes sequence after
// function UpdateAml().
// [Files]         HardwareSignatureManagement.c
// 
// 11    1/13/14 3:42a Albertlin
// [TAG]           EIP147244 
// [Category]      Not Specified
// [Description]   Correct the SetupCount variable. 
// [Files]         HardwareSignatureManagement.c
// 
// 10    1/09/14 7:59a Albertlin
// 
// 9     8/27/13 4:28a Albertlin
// [TAG]           EIP133658 
// [Category]      Not Specified
// [Description]   "UpdateHardwareSignatureData" elink doesn't run only
// once on readytoboot event.
// [Files]         HardwareSignatureManagement.c
// 
// 8     1/10/13 10:24p Albertlin
// [TAG]           EIP109014
// [Category]      Improvement
// [Description]   Currently, HardwareSignature module report signature by
// changed count.But it cause the same hardware may have different
// signature.
// For solve this issue, BIOS should report signature by hardware config.
// [Files]         HardwareChangeDetect.c HardwareSignatureManagement.c
// HardwareSignatureManagement.sdl HardwareChangeProtocol.h
// 
// 7     12/12/12 3:40a Sophiachen
// [TAG]  		EIP106129
// [Category]  	New Feature
// [Description]  	After BIOS firmware update, the hardware signature will
// be changed.
// [Files]  		HardwareSignatureManagement.c,
// HardwareSignatureManagement.mak, HardwareSignatureManagement.sdl
// 
// 6     12/11/12 1:48a Sophiachen
// [TAG]  		EIP105523
// [Category]  	New Feature
// [Description]  	Record the disk configuration data to check the
// connection change of disk.
// [Files]  		HardwareChangeDetect.c, HardwareSignatureManagement.c,
// HardwareChangeProtocol.h
// 
// 5     12/07/12 8:10a Sophiachen
// [TAG]  		EIP108596
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	There is a build error when x64_build is off.
// [RootCause]  	Fail to do the shift operation of 64 bits in IA32 mode.
// [Solution]  	Use the functions Shl64() and Shr64() to do the shift
// operation.
// [Files]  		HardwareChangeDetect.c, HardwareSignatureManagement.c
// 
// 4     11/20/12 8:25a Sophiachen
// [TAG]  		EIP105154
// [Category]  	New Feature
// [Description]  	Record the video configuration data to check the
// connection change of monitor.
// [Files]  		HardwareChangeDetect.c, HardwareSignatureManagement.c,
// HardwareChangeProtocol.h
// 
// 3     10/18/12 7:51a Sophiachen
// 
// 2     9/27/12 11:48p Sophiachen
// [TAG]  		EIP102484
// [Category]  	New Feature
// [Description]  	Update the CHM file
// [Files]  		HardwareSignatureManagement.c
// HardwareSignatureManagement.cif
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
// Name:    HardwareSignatureManagement.c
//
// Description: This file will install the HardwareChange protocol. The 
//              hardware signature data of the FACS table will be 
//              updated when the ReadyToBoot event is signaled.
//
//<AMI_FHDR_END>
//**********************************************************************

//---------------------------------------------------------------------------
#include <Efi.h>
#include <Dxe.h>
#include <AmiDxeLib.h>
#include <token.h>
#include <Acpi.h>
#include <Acpi20.h>
#include <Protocol\AcpiSupport.h>
#include <Protocol\HardwareChangeProtocol.h>

//---------------------------------------------------------------------------

#define HARDWARE_CONFIG_DATA_VARIABLE L"HardwareConfigData"

#define FIRMWARE_UPDATE_COUNT_VARIABLE L"FirmwareUpdateCountVar"

#define AMITSE_EVENT_BEFORE_BOOT_GUID \
  { 0x3677770f, 0xefb2, 0x43b2, 0xb8, 0xae, 0xb3, 0x2, 0xe9, 0x60, 0x48, 0x82 }

#define EFI_AMI_LEGACYBOOT_PROTOCOL_GUID            \
  {0x120d28aa, 0x6630, 0x46f0, 0x81, 0x57, 0xc0, 0xad, 0xc2, 0x38, 0x3b, 0xf5};

//---------------------------------------------------------------------------

EFI_GUID  gHardwareChangeProtocolGuid = HARDWARE_CHANGE_PROTOCOL_GUID;
EFI_GUID  gHardwareConfigDataGuid = HARDWARE_CONFIG_DATA_GUID;
EFI_GUID  gFirmwareUpdateCountGuid = FIRMWARE_UPDATE_COUNT_GUID;
EFI_GUID  HSBeforeBootProtocolGuid = AMITSE_EVENT_BEFORE_BOOT_GUID;
EFI_GUID  HSBeforeLegacyBootProtocolGuid = EFI_AMI_LEGACYBOOT_PROTOCOL_GUID;


//Record the hardware change flag if there are some hardware 
//configurations changed. 
UINT32 gHardwareConfigChangeFlag = 0;
//Record the current hardware configuration data.
HW_CONFIG_DATA gCurHardwareConfigData;
//Record firmware update times
UINT32 gFwUpdateCount = 0;
//Record called times if other module called this protocol
UINT32 gExternalFunCallCount = 0;

//---------------------------------------------------------------------------	
//Function prototype
EFI_STATUS 
SetHardwareConfigDataToNvram (
    IN HW_CONFIG_DATA *HardwareConfigData );

EFI_STATUS 
GetFirmwareUpdateCountFromNvram (
    IN OUT UINT32 *ChangeTime );

EFI_STATUS 
SetFirmwareUpdateCountToNvram (
    IN UINT32 *ChangeTime );	
//---------------------------------------------------------------------------

//Functions defined in HardwareChangeDetect.c
BOOLEAN 
IsDifferentMemorySize(
    UINT32 CurMemorySizeMb, 
    UINT32 PreMemorySizeMb);

EFI_STATUS 
GetMemMapData(
    IN OUT HW_MEMORY_MAP_DATA *pMemMapConfigData);

EFI_STATUS 
GetPciDeviceData(
    IN OUT HW_PCI_DATA *pHardwarePciData);

EFI_STATUS 
GetUsbDeviceData(
    IN OUT HW_USB_DATA *pHardwareUsbData);
	
EFI_STATUS 
GetDiskInfoData(
    OUT HW_DISK_DATA *pHardwareDiskData);

EFI_STATUS 
DetectPS2KeyboardMouseState(
    IN HW_CONFIG_TYPE ConfigType, 
    IN OUT BOOLEAN *bPresent);

EFI_STATUS 
GetVideoData(
    OUT HW_VIDEO_DATA *pHardwareVideoData );
//Functions to detect and set Hardware configurations
EFI_STATUS 
DetectAndSetPs2KeyboardConfig(
    IN UINTN BufferSize, 
    IN VOID *Buffer);

EFI_STATUS 
DetectAndSetPs2MouseConfig(
    IN UINTN BufferSize, 
    IN VOID *Buffer);

EFI_STATUS 
DetectAndSetMemorySizeConfig(
    IN UINTN BufferSize, 
    IN VOID *Buffer);

EFI_STATUS 
DetectAndSetMemoryMapConfig(
    IN UINTN BufferSize, 
    IN VOID *Buffer);

EFI_STATUS 
DetectAndSetPciConfig(
    IN UINTN BufferSize, 
    IN VOID *Buffer);

#if HARDWARE_SIGNATURE_USB_CHANGE
EFI_STATUS 
DetectAndSetUsbConfig(
    IN UINTN BufferSize, 
    IN VOID *Buffer);
#endif

EFI_STATUS 
DetectAndSetVideoConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer );

EFI_STATUS 
DetectAndSetDiskConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer );

EFI_STATUS 
UpdateHardwareSignatureData(
    IN EFI_EVENT Event, 
    IN VOID *Context);

VOID 
QuickSort(
	IN OUT UINT32 *ChecksumData, 
	IN     UINT32 LChecksumPosition, 
	IN     UINT32 RChecksumPosition);

//---------------------------------------------------------------------------

EFI_HARDWARE_CHANGE_PROTOCOL gHardwareChangeProtocol = 
{
    SetHardwareConfigData,
    GetHardwareConfigDataFromNvram,
    SignalHardwareSignatureChange
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Name:   HardwareSignatureUpdateEntryPoint
//
//  Description:
//  This function is a driver entry point that installs a protocol to set the  
//  hardware configurations. These hardware configurations will determine the  
//  hardware ignature of the FACS table.  
//
//  Input:
//  IN EFI_HANDLE       ImageHandle - Image handle
//  IN EFI_SYSTEM_TABLE *SystemTable - pointer to system table
//
//  Output:
//   EFI_STATUS
//     EFI_SUCCESS - Function executed successfully.
//     Other - Function executed unsuccessfully.
//
//  Notes:
//   This function also creates ReadyToBoot event to update the hardware 
//   signature of the FACS table.  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
HardwareSignatureEntryPoint (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{

    EFI_STATUS          Status;
    EFI_EVENT           ReadyToBootEvent;
    EFI_HANDLE          HardwareChangeHandle = NULL;
	UINT8               i;
    VOID                *Registration;
  
    InitAmiLib(ImageHandle,SystemTable);

    //clear the global variable first
    MemSet(&gCurHardwareConfigData, sizeof(HW_CONFIG_DATA),0);

	//Initial ReturnChecksum
	for(i=0;i<LIMIT_PROTOCOL_CALLED;i++)
		gCurHardwareConfigData.ReturnChecksum[i] = 0;

    Status = pBS->InstallProtocolInterface(
                      &HardwareChangeHandle,
                      &gHardwareChangeProtocolGuid,
                      EFI_NATIVE_INTERFACE,
                      &gHardwareChangeProtocol
                      );

    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) 
        return Status;

      RegisterProtocolCallback(
              &HSBeforeBootProtocolGuid,
              UpdateHardwareSignatureData,
              NULL, 
              &ReadyToBootEvent, 
              &Registration
              );

      RegisterProtocolCallback(
              &HSBeforeLegacyBootProtocolGuid,
              UpdateHardwareSignatureData,
              NULL, 
              &ReadyToBootEvent, 
              &Registration
              );    
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SetHardwareConfigData
//
// Description:
//  This function sets the hardware configuration data for each configuration
//  type.
//
// Input:
//  IN HW_CONFIG_TYPE  ConfigType - the hardware configuration type 
//  IN UINTN           BufferSize - Size of buffer for recording the 
//                                  configuration data.
//  IN VOID            *Buffer - Buffer for recording the config. data. 
//
// Output:
//  EFI_STATUS
//    EFI_INVALID_PARAMETER - ConfigType is incorrect. Buffer is NULL and
//                            BufferSize is not zero.
//    EFI_SUCCESS - Set the hardware configuration data successfully.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
SetHardwareConfigData (
    IN HW_CONFIG_TYPE ConfigType, 
    IN UINTN          BufferSize,
    IN VOID           *Buffer )
{
    EFI_STATUS Status;

    if( (Buffer == NULL && BufferSize != 0) || ConfigType >= MaxConfigType )
        return EFI_INVALID_PARAMETER;
  
    switch(ConfigType)
    {
        case Ps2KeyboardConfigType:
            Status = DetectAndSetPs2KeyboardConfig(BufferSize, Buffer);
            break;
          
        case Ps2MouseConfigType:
            Status = DetectAndSetPs2MouseConfig(BufferSize, Buffer);
            break;   
          
        case MemorySizeConfigType:
            Status = DetectAndSetMemorySizeConfig(BufferSize, Buffer);
            break;
          

        case MemoryMapConfigType:
            Status = DetectAndSetMemoryMapConfig(BufferSize, Buffer);
            break;
          
        case PciConfigType:
            Status = DetectAndSetPciConfig(BufferSize, Buffer);
            break;
#if HARDWARE_SIGNATURE_USB_CHANGE          
        case UsbConfigType:
            Status = DetectAndSetUsbConfig(BufferSize, Buffer);
            break;
#endif
        case VideoConfigType:
            Status = DetectAndSetVideoConfig(BufferSize, Buffer);
            break;
		case DiskConfigType:
            Status = DetectAndSetDiskConfig(BufferSize, Buffer);
            break;   
        default:
            Status = EFI_INVALID_PARAMETER;
            break;
    }
      
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: GetHardwareConfigDataFromNvram
//
// Description:
//  This function gets the hardware configuration data from NVRAM.
//
// Input:
//  IN OUT HW_CONFIG_DATA *HardwareConfigData - The hardware configuration data of NVRAM.
//
// Output:
//  EFI_STATUS
//    EFI_INVALID_PARAMETER - HardwareConfigData is NULL.
//    EFI_NOT_FOUND - It is the first boot. There is no Hardware 
//                    configuration data.
//    EFI_SUCCESS - Get the hardware configuration data successfully.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
GetHardwareConfigDataFromNvram(
    IN OUT HW_CONFIG_DATA *HardwareConfigData )
{
    EFI_STATUS          Status;
    UINTN               VarSize = sizeof(HW_CONFIG_DATA);

    if(HardwareConfigData == NULL)
        return EFI_INVALID_PARAMETER;
    
    Status = pRS->GetVariable(
            HARDWARE_CONFIG_DATA_VARIABLE, 
            &gHardwareConfigDataGuid,
            NULL, 
            &VarSize, 
            HardwareConfigData ); 

    if( EFI_ERROR(Status) )
    {
        MemSet(HardwareConfigData,sizeof(HW_CONFIG_DATA),0);
    }
    
    return Status;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: GetFirmwareUpdateCountFromNvram
//
// Description:
//  This function gets the firmware update times from NVRAM.
//
// Input:
//  IN OUT UINT32 *ChangeTime - The firmware update times.
//
// Output:
//  EFI_STATUS
//    EFI_INVALID_PARAMETER - ChangeTime is NULL.
//    EFI_SUCCESS - Get the firmware update change times successfully.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
GetFirmwareUpdateCountFromNvram(
    IN OUT UINT32 *ChangeTime )
{
    EFI_STATUS          Status;
    UINTN               VarSize = sizeof(UINT32);

    if(ChangeTime == NULL)
        return EFI_INVALID_PARAMETER;
    
    Status = pRS->GetVariable(
            FIRMWARE_UPDATE_COUNT_VARIABLE, 
            &gFirmwareUpdateCountGuid,
            NULL, 
            &VarSize, 
            ChangeTime ); 

    if( EFI_ERROR(Status) )
    {
        MemSet(ChangeTime,sizeof(UINT32),0);
    }
    
    return Status;    
}

//<EIP147244 >
EFI_GUID  gSetupUpdateCountGuid = SETUP_UPDATE_COUNT_GUID;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: GetSetupUpdateCountFromNvram
//
// Description:
//  This function gets the setup update times from NVRAM.
//
// Input:
//  IN OUT UINT32 *ChangeTime - The setup update times.
//
// Output:
//  EFI_STATUS
//    EFI_INVALID_PARAMETER - ChangeTime is NULL.
//    EFI_SUCCESS - Get the firmware update change times successfully.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
GetSetupCountFromNvram(
    IN OUT UINT32 *ChangeTime )
{
    EFI_STATUS          Status;
    UINTN               VarSize = sizeof(UINT32);

    if(ChangeTime == NULL)
        return EFI_INVALID_PARAMETER;
    
    Status = pRS->GetVariable(
            SETUP_UPDATE_COUNT_VARIABLE, 
            &gSetupUpdateCountGuid,
            NULL, 
            &VarSize, 
            ChangeTime ); 

    if( EFI_ERROR(Status) )
    {
        MemSet(ChangeTime,sizeof(UINT32),0);
    }
    
    return Status;    
}
//<EIP147244 >


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SignalHardwareSignatureChange
//
// Description:
//  This function will update the global variable 'gExternalFunCallCount' and
//  save the checksum value in the global variable
//  gCurHardwareConfigData(ReturnChecksum array).
//
// Modified: gExternalFunCallCount, gCurHardwareConfigData.ReturnChecksum
//
// Input: 
//  IN UINT32 ReturnChecksum - The checksum value that external function gives.
//
// Output: 
//  EFI_STATUS
//    EFI_OUT_OF_RESOURCES - The global variable 'gExternalFunCallCount' is 
//                           larger than and equal to LIMIT_PROTOCOL_CALLED.
//    EFI_SUCCESS - Record the checksum which external function gives successfully
//
// Notes:
//  The global variable gExternalFunCallCount will be increased.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SignalHardwareSignatureChange ( 
    IN UINT32 ReturnChecksum )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if (gExternalFunCallCount >= LIMIT_PROTOCOL_CALLED)
		return EFI_OUT_OF_RESOURCES;
	else
	{
		gCurHardwareConfigData.ReturnChecksum[gExternalFunCallCount]= ReturnChecksum;	
		gExternalFunCallCount++;
		return Status;
	}	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SaveFwUpdateCountToMemory
//
// Description:
//  This function gets update counts from NVRAM and copy this data to the 
//  global variable 'gFwUpdateCount' before updating the firmware. The NVRAM
//  data could erase during firmware update, so we need to save the data to  
//  memory first. 
//
// Modified: gFwUpdateCount
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
SaveFwUpdateCountToMemory ( VOID )
{
	EFI_STATUS	Status;
	UINT32		ChangeCount = 0;
	
	Status = GetFirmwareUpdateCountFromNvram(&ChangeCount);
	gFwUpdateCount = ChangeCount+1;
		
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//       
// Name: SaveCountToNvramAfterFwUpdate
//
// Description:
//  This function saves the global variable 'gFwUpdateCount' to NVRAM after 
//  the firmware updated.
//
// Input: None
//
// Output: None
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
SaveCountToNvramAfterFwUpdate( VOID )
{
	EFI_STATUS	Status;
	
	Status = SetFirmwareUpdateCountToNvram(&gFwUpdateCount);
	if (EFI_ERROR(Status))
		return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SetPs2KeyboardState
//
// Description:
//  This function sets the PS2 Keyboard configurations to global variable 
//  gCurHardwareConfigData.
//
// Input:
//  IN BOOLEAN bPresent - If valuse is TRUE, PS2 Keyboard is present. 
//                        If valuse is FALSE, PS2 Keyboard is not present. 
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
SetPs2KeyboardState (
    IN BOOLEAN bPresent )
{
    if( bPresent )
    {    
        gHardwareConfigChangeFlag |= HW_CHANGE_PS2_KEYBOARD; 

        gCurHardwareConfigData.bPs2Keyboard = TRUE;
    }
    else 
    {   
        gHardwareConfigChangeFlag |= HW_CHANGE_PS2_KEYBOARD; 
        //no PS2 Keyboard  
        gCurHardwareConfigData.bPs2Keyboard = FALSE;
    }    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SetPs2MouseState
//
// Description:
//  This function sets the PS2 Mouse configurations to global variable 
//  gCurHardwareConfigData.
//
// Input:
//  IN BOOLEAN bPresent - If valuse is TRUE, PS2 Mouse is present. 
//                        If valuse is FALSE, PS2 Mouse is not present. 
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
SetPs2MouseState (
    IN BOOLEAN bPresent )
{
    if( bPresent )
    {    
        gHardwareConfigChangeFlag |= HW_CHANGE_PS2_MOUSE; 
        gCurHardwareConfigData.bPs2Mouse = TRUE;
    }
    else 
    {
        gHardwareConfigChangeFlag |= HW_CHANGE_PS2_MOUSE;     
        //no PS2 Mouse
        gCurHardwareConfigData.bPs2Mouse = FALSE;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SetMemorySizeConfigState
//
// Description:
//  This function sets the memory size configurations to global variable 
//  gCurHardwareConfigData.
//
// Input:
//  IN UINT32 MemorySizeMb - Current memory size (MB)                                             
//  IN UINTN  BufferSize - Size of buffer for recording the memory size.
//
// Output:
//  EFI_STATUS
//    EFI_INVALID_PARAMETER - Buffer size is too small to record the memory 
//                            size.
//    EFI_SUCCESS - Memory size config. is set successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
SetMemorySizeConfigState (
    IN UINT32 MemorySizeMb, 
    IN UINTN  BufferSize )
{

    if(BufferSize < sizeof(UINT32)){
        return EFI_INVALID_PARAMETER;
    }
    
    gHardwareConfigChangeFlag |= HW_CHANGE_MEMORY_SIZE_CONFIG; 

    gCurHardwareConfigData.MemMapData.MemoryMbSize = MemorySizeMb;
        
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SetMemoryMapConfigState
//
// Description:
//  This function sets the memory map configurations to global variable 
//  gCurHardwareConfigData.
//
// Input:
//  IN HW_MEMORY_MAP_DATA MemMapConfig - Current memory map data                                             
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
SetMemoryMapConfigState (
    IN HW_MEMORY_MAP_DATA MemMapConfig )
{    
    gHardwareConfigChangeFlag |= HW_CHANGE_MEMORY_MAP_CONFIG;        
    gCurHardwareConfigData.MemMapData.MemMapCheckSum = MemMapConfig.MemMapCheckSum;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: SetPciConfigState
//
// Description:
//  This function sets the PCI configurations to global variable 
//  gCurHardwareConfigData.
//
// Input:
//  IN HW_PCI_DATA PciConfig - Current PCI data                                             
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
SetPciConfigState (
    IN HW_PCI_DATA PciConfig )
{    
    gHardwareConfigChangeFlag |= HW_CHANGE_PCI_CONFIG; 
       
    gCurHardwareConfigData.PciData.PciNum = PciConfig.PciNum;
    gCurHardwareConfigData.PciData.BdfChecksum = PciConfig.BdfChecksum;
    gCurHardwareConfigData.PciData.VidDidChecksum = PciConfig.VidDidChecksum;           
}

#if HARDWARE_SIGNATURE_USB_CHANGE

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: SetUsbConfigState
//
// Description:
//  This function sets the USB configurations to global variable 
//  gCurHardwareConfigData.
//
// Input:
//  IN HW_USB_DATA UsbConfig - Current USB data                                             
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
SetUsbConfigState (
    IN HW_USB_DATA UsbConfig )
{    
    gHardwareConfigChangeFlag |= HW_CHANGE_USB_CONFIG; 
       
    gCurHardwareConfigData.UsbData.UsbNum = UsbConfig.UsbNum;
    gCurHardwareConfigData.UsbData.VidPidChecksum = UsbConfig.VidPidChecksum;
    gCurHardwareConfigData.UsbData.PortNumInterfaceNumChecksum = UsbConfig.PortNumInterfaceNumChecksum;
           
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: SetVideoConfigState
//
// Description:
//  This function sets the Video configurations to global variable 
//  gCurHardwareConfigData.
//
// Input:
//  IN HW_VIDEO_DATA VideoConfig - Current Video data                                             
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
SetVideoConfigState (
    IN HW_VIDEO_DATA VideoConfig )
{    
    gHardwareConfigChangeFlag |= HW_CHANGE_VIDEO_CONFIG; 
       
    gCurHardwareConfigData.VideoData.EdidCheckNum = VideoConfig.EdidCheckNum;
    gCurHardwareConfigData.VideoData.ResolutionChecksum = VideoConfig.ResolutionChecksum;
           
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: SetDiskConfigState
//
// Description:
//  This function sets the Disk configurations to global variable 
//  gCurHardwareConfigData.
//
// Input:
//  IN HW_DISK_DATA DiskConfig - Current Disk data                                             
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
SetDiskConfigState (
    IN HW_DISK_DATA DiskConfig )
{    
    gHardwareConfigChangeFlag |= HW_CHANGE_DISK_CONFIG; 
       
    gCurHardwareConfigData.DiskData.CDSchecksum = DiskConfig.CDSchecksum;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: DetectAndSetPs2KeyboardConfig
//
// Description:
//  This function detects the PS2 Keyboard configurations and sets this  
//  configuration to global variable gCurHardwareConfigData.
//
// Input:
//  IN UINTN BufferSize - Size of buffer for recording the PS2 Keyboard 
//                        configuration. It should be one byte. 
//  IN VOID *Buffer - Buffer for recording the PS2 Keyboard configuration. 
//                    If *Buffer is 1, it means the PS2 Keyboard is present. 
//                    If *Buffer is 0, the PS2 Keyboard is not present  
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - PS2 Keyboard config. is set successfully.
//    Other - Set PS2 Keyboard config. failed.
//
// Notes:
//  If Buffer is NULL and BufferSize is 0, the function will save the 
//  detected data to gCurHardwareConfigData. Otherwise,  it will compare the 
//  input data and the  detected data to determine the PS2 Keyboard is 
//  present or not.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
DetectAndSetPs2KeyboardConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    BOOLEAN             bPs2KeyboardPresent = FALSE;
    BOOLEAN             DetectPs2KeyboardPresent = FALSE;

    Status = DetectPS2KeyboardMouseState( Ps2KeyboardConfigType, 
                                          &DetectPs2KeyboardPresent);

    if( BufferSize == 0 && Buffer == NULL)
    {
        bPs2KeyboardPresent = DetectPs2KeyboardPresent;
    }
    else
    {     
        if((*(BOOLEAN *)Buffer) == 0 && DetectPs2KeyboardPresent == 0)
            bPs2KeyboardPresent = FALSE;        
        else
            bPs2KeyboardPresent = TRUE;
    }

    SetPs2KeyboardState(bPs2KeyboardPresent);

    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:   DetectAndSetPs2MouseConfig
//
//  Description:
//  This function detects the PS2 Mouse configurations and sets this config. 
//  to global variable gCurHardwareConfigData.
//
//  Input:
//  IN UINTN BufferSize - Size of buffer for recording the PS2 Mouse config.  
//                        It should be one byte. 
//  IN VOID  *Buffer - Buffer for recording the PS2 Mouse configuration. If  
//                     *Buffer is 1, it means the PS2 Mouse is present. If 
//                     *Buffer is 0, the PS2 Mouse is not present  
//
//  Output:
//  EFI_STATUS
//    EFI_SUCCESS - PS2 Mouse config. is set successfully.
//    Other - Set PS2 Mouse configuration failed.
//
//  Notes:
//  If Buffer is NULL and BufferSize is 0, the function will save the 
//  detected data to gCurHardwareConfigData. Otherwise,  it will compare  
//  the input data and the detected data to determine the PS2 Mouse is 
//  present or not.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
DetectAndSetPs2MouseConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    BOOLEAN             bPs2MousePresent = FALSE;
    BOOLEAN             DetectPs2MousePresent = FALSE;

    Status = DetectPS2KeyboardMouseState( Ps2MouseConfigType, 
                                          &DetectPs2MousePresent);

    if( BufferSize == 0 && Buffer == NULL)
    {
        bPs2MousePresent = DetectPs2MousePresent;
    }
    else
    {     
        if((*(BOOLEAN *)Buffer) == 0 && DetectPs2MousePresent == 0)
            bPs2MousePresent = FALSE;        
        else
            bPs2MousePresent = TRUE;
    }


    SetPs2MouseState(bPs2MousePresent);

    return Status;
    
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: DetectAndSetMemorySizeConfig
//
// Description:
//  This function detects the memory size configurations and sets this  
//  configuration to global variable gCurHardwareConfigData.
//
// Input:
//  IN UINTN BufferSize - Size of buffer for recording the memory size.
//  IN VOID *Buffer - Buffer for recording the memory size.
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - Memory size config. is set successfully.
//    Other - Detect the memory size failed or set the memory size 
//            configuration failed.
//
// Notes:
//  If Buffer is NULL and BufferSize is 0, the function will save the 
//  detected size(DetectMemSize) to gCurHardwareConfigData. Otherwise, it  
//  will compare the input data(Buffer) and the detected size(DetectMemSize) 
//  to determine which one should be saved. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
DetectAndSetMemorySizeConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    UINT32              CurrentMemSize= 0;
    UINTN               BuffSize = 0;
    UINT32              DetectMemSize = 0;
    BOOLEAN             bDifferent = FALSE;
    HW_MEMORY_MAP_DATA  DetectMemMapConfigData;

    MemSet(&DetectMemMapConfigData, sizeof(HW_MEMORY_MAP_DATA), 0);

    Status = GetMemMapData (&DetectMemMapConfigData);

    if(EFI_ERROR(Status)) 
        return Status;

    DetectMemSize = DetectMemMapConfigData.MemoryMbSize;
      
    if( BufferSize == 0 && Buffer == NULL)
    {
        CurrentMemSize = DetectMemSize;
        BuffSize = sizeof (CurrentMemSize);
    }
    else
    {     
        bDifferent = IsDifferentMemorySize( DetectMemSize, (*(UINT32 *)Buffer) );
      
        if(bDifferent)
          CurrentMemSize = DetectMemSize; 
        else
          CurrentMemSize = (*(UINT32 *)Buffer);

        BuffSize = BufferSize;
    }

    Status = SetMemorySizeConfigState(CurrentMemSize, BuffSize);

    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: DetectAndSetMemoryMapConfig
//
// Description:
//  This function detects the memory map configurations and sets this  
//  configuration to global variable gCurHardwareConfigData.
//
// Input:
//  IN UINTN BufferSize - Size of buffer for recording the memory map data.
//  IN VOID  *Buffer - Buffer for recording the memory map data.
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - Memory map config. is set successfully.
//    EFI_INVALID_PARAMETER - BufferSize is incorrect.
//    Other - Get memory map data failed.
//
// Notes:
//  If Buffer is NULL and BufferSize is 0, the function will save the 
//  detected memory map data to gCurHardwareConfigData. Otherwise, it will 
//  save the input data(Buffer).
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
DetectAndSetMemoryMapConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    UINTN               BuffSize = 0;
    HW_MEMORY_MAP_DATA  DetectMemMapConfigData;
    HW_MEMORY_MAP_DATA  CurMemMapConfigData;
    
    MemSet(&DetectMemMapConfigData, sizeof(HW_MEMORY_MAP_DATA), 0);

    Status = GetMemMapData (&DetectMemMapConfigData);

    if(EFI_ERROR(Status)) 
        return Status;
      
    if( BufferSize == 0 && Buffer == NULL)
    {
        BuffSize = sizeof(DetectMemMapConfigData.MemMapCheckSum);       
        MemCpy(&CurMemMapConfigData, &DetectMemMapConfigData, BuffSize);
    }
    else
    {     
        BuffSize = sizeof(DetectMemMapConfigData.MemMapCheckSum);
        if(BufferSize < BuffSize || BufferSize > sizeof(HW_MEMORY_MAP_DATA))
        {
            Status = EFI_INVALID_PARAMETER;
            return Status;
        }
        
        BuffSize = BufferSize;
        MemCpy(&CurMemMapConfigData, Buffer, BuffSize);
    }

    SetMemoryMapConfigState(CurMemMapConfigData);

    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: DetectAndSetPciConfig
//
// Description:
//  This function detects the PCI configurations and sets this configuration 
//  to global variable gCurHardwareConfigData.
//
// Input:
//  IN UINTN BufferSize - Size of buffer for recording the PCI data.
//  IN VOID  *Buffer - Buffer for recording the PCI data.
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - PCI config. is set successfully.
//    EFI_INVALID_PARAMETER - BufferSize is incorrect.
//    Other - Get PCI data failed.
//
// Notes:
//  If Buffer is NULL and BufferSize is 0, the function will save the 
//  detected PCI data to gCurHardwareConfigData. Otherwise, it will save 
//  the input data (Buffer). 
//  
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
DetectAndSetPciConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    UINTN               BuffSize = 0;
    HW_PCI_DATA         DetectPciConfigData;
    HW_PCI_DATA         CurrentPciConfigData;

    Status = GetPciDeviceData (&DetectPciConfigData);
      
    if(EFI_ERROR(Status)) 
        return Status;
      
    if( BufferSize == 0 && Buffer == NULL)
    {
        BuffSize = sizeof(HW_PCI_DATA);
        MemCpy(&CurrentPciConfigData, &DetectPciConfigData, BuffSize);
    }
    else
    {     
        BuffSize = sizeof(HW_PCI_DATA);
        if(BufferSize != BuffSize )
        {
            Status = EFI_INVALID_PARAMETER;
            return Status;
        }
        
        MemCpy(&CurrentPciConfigData, Buffer, BuffSize);
    }

    SetPciConfigState(CurrentPciConfigData);

    return Status;
    
}
#if HARDWARE_SIGNATURE_USB_CHANGE

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: DetectAndSetUsbConfig
//
// Description:
//  This function detects the USB configurations and sets this configuration
//  to global variable gCurHardwareConfigData.
//
// Input:
//  IN UINTN BufferSize - Size of buffer for recording USB data.
//  IN VOID  *Buffer - Buffer for recording the USB data.
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - USB config. is set successfully.
//    EFI_INVALID_PARAMETER - BufferSize is incorrect.
//    Other - Get USB data failed.
//
// Notes:
//  If Buffer is NULL and BufferSize is 0, the function will save the 
//  detected USB data to gCurHardwareConfigData. Otherwise, it will save the 
//  input data (Buffer). 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
DetectAndSetUsbConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    UINTN               BuffSize = 0;
    HW_USB_DATA         DetectUsbConfigData;
    HW_USB_DATA         CurrentUsbConfigData;

    Status = GetUsbDeviceData (&DetectUsbConfigData);
      
    if(EFI_ERROR(Status)) 
        return Status;
      
    if( BufferSize == 0 && Buffer == NULL)
    {
        BuffSize = sizeof(HW_USB_DATA);
        MemCpy(&CurrentUsbConfigData, &DetectUsbConfigData, BuffSize);
    }
    else
    {     
        BuffSize = sizeof(HW_USB_DATA);
        if(BufferSize != BuffSize )
        {
            Status = EFI_INVALID_PARAMETER;
            return Status;
        }
        
        MemCpy(&CurrentUsbConfigData, Buffer, BuffSize);
    }

    SetUsbConfigState(CurrentUsbConfigData);

    return Status;
    
}

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: DetectAndSetVideoConfig
//
// Description:
//  This function detects the Video configurations and sets this configuration 
//  to global variable gCurHardwareConfigData.
//
// Input:
//  IN UINTN BufferSize - Size of buffer for recording the Video data.
//  IN VOID  *Buffer - Buffer for recording the Video data.
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - Video configuration is set successfully.
//    EFI_INVALID_PARAMETER - BufferSize is incorrect.
//    Other - Get Video data failed.
//
// Notes:
//  If Buffer is NULL and BufferSize is 0, the function will save the 
//  detected Video data to gCurHardwareConfigData. Otherwise, it will save 
//  the input data (Buffer). 
//  
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
DetectAndSetVideoConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    UINTN               BuffSize = 0;
    HW_VIDEO_DATA       DetectVideoData;
    HW_VIDEO_DATA       CurrentVideoData;  
    
    Status = GetVideoData( &DetectVideoData);
      
    if(EFI_ERROR(Status)) 
        return Status;
      
    if( BufferSize == 0 && Buffer == NULL)
    {
        BuffSize = sizeof(HW_VIDEO_DATA);
        MemCpy(&CurrentVideoData, &DetectVideoData, BuffSize);
    }
    else
    {     
        BuffSize = sizeof(HW_VIDEO_DATA);
        if(BufferSize != BuffSize )
        {
            Status = EFI_INVALID_PARAMETER;
            return Status;
        }
        
        MemCpy(&CurrentVideoData, Buffer, BuffSize);
    }

    SetVideoConfigState(CurrentVideoData);

    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: DetectAndSetDiskConfig
//
// Description:
//  This function detects the Disk configurations and sets this configuration 
//  to global variable gCurHardwareConfigData.
//
// Input:
//  IN UINTN BufferSize - Size of buffer for recording the Disk data.
//  IN VOID  *Buffer - Buffer for recording the Disk data.
//
// Output:
//  EFI_STATUS
//    EFI_SUCCESS - Disk configuration is set successfully.
//    EFI_INVALID_PARAMETER - BufferSize is incorrect.
//    Other - Get Disk data failed.
//
// Notes:
//  If Buffer is NULL and BufferSize is 0, the function will save the 
//  detected Disk data to gCurHardwareConfigData. Otherwise, it will save 
//  the input data (Buffer). 
//  
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
DetectAndSetDiskConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer)
{
    EFI_STATUS          Status;
    UINTN               BuffSize = 0;
    HW_DISK_DATA		DetectDiskData;
    HW_DISK_DATA		CurrentDiskData;  

    Status = GetDiskInfoData( &DetectDiskData);
      
    if(EFI_ERROR(Status)) 
        return Status;
      
    if( BufferSize == 0 && Buffer == NULL)
    {
        BuffSize = sizeof(HW_DISK_DATA);
        MemCpy(&CurrentDiskData, &DetectDiskData, BuffSize);
    }
    else
    {     
        BuffSize = sizeof(HW_DISK_DATA);
        if(BufferSize != BuffSize )
        {
            Status = EFI_INVALID_PARAMETER;
            return Status;
        }
        
        MemCpy(&CurrentDiskData, Buffer, BuffSize);
    }

    SetDiskConfigState(CurrentDiskData);

    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SetHardwareConfigDataToNvram
//
// Description:
//  This function writes the hardware configurations to NVRAM.
//
// Input:
//  IN HW_CONFIG_DATA   *HardwareConfigData - current HW config. data                                             
//
// Output:
//  EFI_STATUS
//    EFI_INVALID_PARAMETER - HardwareConfigData is invalid
//    EFI_SUCCESS - HW Config. is written successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
SetHardwareConfigDataToNvram (
    IN HW_CONFIG_DATA *HardwareConfigData )
{
    EFI_STATUS          Status;
    UINTN               VarSize = sizeof(HW_CONFIG_DATA);

    if(HardwareConfigData == NULL)
        return EFI_INVALID_PARAMETER;
    
    Status = pRS->SetVariable(
            HARDWARE_CONFIG_DATA_VARIABLE, 
            &gHardwareConfigDataGuid,
            EFI_VARIABLE_NON_VOLATILE |
            EFI_VARIABLE_BOOTSERVICE_ACCESS |
            EFI_VARIABLE_RUNTIME_ACCESS,
            VarSize, 
            HardwareConfigData
            ); 
    
    return Status;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SetFirmwareUpdateCountToNvram
//
// Description:
//  This function saves the firmware update times into NVRAM.
//
// Input:
//  IN UINT32 *ChangeTime - Firmware update times.                                
//
// Output:
//  EFI_STATUS
//    EFI_INVALID_PARAMETER - ChangeTime is invalid
//    EFI_SUCCESS - ChangeTime is written successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
SetFirmwareUpdateCountToNvram (
    IN UINT32 *ChangeTime )
{
    EFI_STATUS          Status;
    UINTN               VarSize = sizeof(UINT32);

    if(ChangeTime == NULL)
        return EFI_INVALID_PARAMETER;
    
    Status = pRS->SetVariable(
            FIRMWARE_UPDATE_COUNT_VARIABLE, 
            &gFirmwareUpdateCountGuid,
            EFI_VARIABLE_NON_VOLATILE |
            EFI_VARIABLE_BOOTSERVICE_ACCESS |
            EFI_VARIABLE_RUNTIME_ACCESS,
            VarSize, 
            ChangeTime
            ); 
    
    return Status;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: GetFacsTable
//
// Description:
//  This function returns address of memory where FACS ACPI table resides
//
// Input:
//  IN OUT EFI_PHYSICAL_ADDRESS *AcpiFacsTable - address of FACS table
//
// Output:
//  EFI_STATUS
//    EFI_NOT_READY - Can't find the EfiAcpiSupportGuid protocol
//    EFI_NOT_FOUND - Can't find the FADT table 
//    EFI_SUCCESS - Table was found successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
GetFacsTable ( 
    IN OUT EFI_PHYSICAL_ADDRESS *AcpiFacsTable )
{
    EFI_STATUS                Status;
    EFI_GUID                  EfiAcpiSupportGuid = EFI_ACPI_SUPPORT_GUID;
    EFI_ACPI_SUPPORT_PROTOCOL *AcpiSupport;
    EFI_ACPI_TABLE_VERSION    Version;
    FACP_20                   *Table = NULL;
    UINT8                     FacpFlag = 0;
    UINTN                     Index;
    UINTN                     Handle;    
    
    Status = pBS->LocateProtocol(&EfiAcpiSupportGuid, NULL, &AcpiSupport);
    if(EFI_ERROR(Status))
    {
        return EFI_NOT_READY;
    }

    for(Index = 0; Index < 3; Index++)
    {
        AcpiFacsTable[Index] = 0;
    }

    //Find DSDT, XSDT ACPI table
    Index = 0;
    do
    {
        Status = AcpiSupport->GetAcpiTable(AcpiSupport, 
                                           Index, 
                                           &Table, 
                                           &Version, 
                                           &Handle);
        if (EFI_ERROR(Status)) 
            break;//no more tables left

        if ((Table->Header.Signature == FACP_SIG))
        {
            if( Version == EFI_ACPI_TABLE_VERSION_1_0B )
            {
                AcpiFacsTable[0] = (EFI_PHYSICAL_ADDRESS)Table->FIRMWARE_CTRL;
                FacpFlag |= BIT0;
            }
            else
            {
                AcpiFacsTable[1] = (EFI_PHYSICAL_ADDRESS)Table->FIRMWARE_CTRL;
                AcpiFacsTable[2] = (EFI_PHYSICAL_ADDRESS)Table->X_FIRMWARE_CTRL;     
                FacpFlag |= BIT1;
            }
                        
        }

        if(FacpFlag == 3)
            break;
        
        Index++;
    }while(1);

    if(FacpFlag == 0)
        return EFI_NOT_FOUND;
       
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: Swap
//
// Description:
//  This function swaps the two input data.
//
// Input:
//  IN OUT UINT32 *LChecksumPosition - Left checksum position
//  IN OUT UINT32 *RChecksumPosition - Right checksum position
//
// Output: 
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
Swap(
    IN OUT UINT32 *LChecksumPosition,
	IN OUT UINT32 *RChecksumPosition )
{
    UINT32 Temp = *LChecksumPosition;
    *LChecksumPosition = *RChecksumPosition;
    *RChecksumPosition = Temp;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: QuickSort
//
// Description:
//  This function sorts the external checksum in ascending order.
//
// Input:
//	IN OUT UINT32 *ChecksumData - all checksum data
//	IN     UINT32 LChecksumPosition - the first position of checksum data 
//	IN     UINT32 RChecksumPosition - the last position of checksum data 
//
// Output:
//  None
//
// Notes:
//  The sorted data will be saved in ChecksumData.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
QuickSort(
    IN OUT UINT32 *ChecksumData, 
    IN     UINT32 LChecksumPosition, 
    IN     UINT32 RChecksumPosition )
{
    UINT32 Pivot; 
	UINT32 LeftIncPosition;
	UINT32 RightDecPostion;

    if (LChecksumPosition >= RChecksumPosition) { return; }

    Pivot = ChecksumData[LChecksumPosition];

    LeftIncPosition = LChecksumPosition + 1;
    RightDecPostion = RChecksumPosition;

    while (1)
    {
        while (LeftIncPosition <= RChecksumPosition)
        {
            if (ChecksumData[LeftIncPosition] > Pivot)
                break;
            LeftIncPosition = LeftIncPosition + 1;
        }

        while (RightDecPostion > LChecksumPosition)
        {
            if (ChecksumData[RightDecPostion] < Pivot)
                break;
            RightDecPostion = RightDecPostion - 1;
        }

        if (LeftIncPosition > RightDecPostion)
			break;

        Swap(&ChecksumData[LeftIncPosition], &ChecksumData[RightDecPostion]);
    }

    Swap(&ChecksumData[LChecksumPosition], &ChecksumData[RightDecPostion]);

    QuickSort(ChecksumData, LChecksumPosition, RightDecPostion - 1);
    QuickSort(ChecksumData, RightDecPostion + 1, RChecksumPosition);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:   UpdateHardwareSignatureData
//
// Description:
//  This function will be called when ReadyToBoot event will be signaled and 
//  will update the hardware signature data of the FACS table.
//
// Input:
//  IN EFI_EVENT Event - signalled event
//  IN VOID      *Context - calling context
//
// Output:
//  EFI_STATUS
//    EFI_NOT_READY - GetFacsTable() can't find the EfiAcpiSupportGuid protocol.
//    EFI_NOT_FOUND - GetFacsTable() can't find the FADT table. 
//    EFI_SUCCESS - Hardware Signature was updated successfully.
//	  Other - Hardware Signature could't be updated.
//
// Notes:
//  This function also writes the hardware configurations to NVRAM.   
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
UpdateHardwareSignatureData (
    IN EFI_EVENT Event, 
    IN VOID      *Context )
{   
    EFI_STATUS                     Status;
    FACS_20                        *FacsPtr = NULL;    
    BOOLEAN                        bDifferent = FALSE;
    BOOLEAN                        bFirstBoot = FALSE;
    EFI_PHYSICAL_ADDRESS           AcpiFacsTable[3];
    UINT8                          Index =0;
    UINTN                          VarSize = sizeof(HW_CONFIG_DATA);
    BOOLEAN                        bPs2MousePresent = FALSE;
    UINTN                          BufferSize = 0;
	UINT32                         FacsSignature = 0;
    UINT32                         ChangeCount = 0;
	UINT32                         SetupCount=0;
	UINTN                          i;
    static UINT8                   UpdateCount = 0;
    
    if(UpdateCount == 0)//To update the signature only once
        UpdateCount++;
    else
        return EFI_SUCCESS;

    //clear table address
    for(Index = 0; Index < 3; Index++)
    {
        AcpiFacsTable[Index] = 0;
    }
    //Get Facs table address. (RSDT, XSDT)
    Status = GetFacsTable(&AcpiFacsTable[0]);
    
    if (EFI_ERROR(Status)) 
        return Status;

	SetHardwareConfigData( Ps2KeyboardConfigType,0,NULL );

    BufferSize = sizeof(bPs2MousePresent); 
	SetHardwareConfigData( Ps2MouseConfigType,BufferSize,(VOID *)&bPs2MousePresent );

    SetHardwareConfigData( MemorySizeConfigType,0,NULL);

    SetHardwareConfigData( MemoryMapConfigType,0,NULL);

    SetHardwareConfigData( PciConfigType,0,NULL);
	
#if HARDWARE_SIGNATURE_USB_CHANGE
    SetHardwareConfigData( UsbConfigType,0,NULL);
#endif
	SetHardwareConfigData( DiskConfigType,0,NULL);

    SetHardwareConfigData( VideoConfigType,0,NULL);
	
	HWSIG_TRACE((-1,"bPs2KB:%x, bPs2Mouse:%x\n", gCurHardwareConfigData.bPs2Keyboard, gCurHardwareConfigData.bPs2Mouse));
	HWSIG_TRACE((-1,"MemMapCheckSum:%x\n", gCurHardwareConfigData.MemMapData.MemMapCheckSum));
	HWSIG_TRACE((-1,"MemorySize:%x\n", gCurHardwareConfigData.MemMapData.MemoryMbSize));
	HWSIG_TRACE((-1,"Pci#:%x, BDF:%x, VID:%x\n", gCurHardwareConfigData.PciData.PciNum, gCurHardwareConfigData.PciData.BdfChecksum, gCurHardwareConfigData.PciData.VidDidChecksum));
#if HARDWARE_SIGNATURE_USB_CHANGE
	HWSIG_TRACE((-1,"Usb#:%x,VID:%x, Port:%x\n", gCurHardwareConfigData.UsbData.UsbNum, gCurHardwareConfigData.UsbData.VidPidChecksum, gCurHardwareConfigData.UsbData.PortNumInterfaceNumChecksum));
#endif
	HWSIG_TRACE((-1,"Edid Chk:0x%x, Resolution Chk:0x%x\n", gCurHardwareConfigData.VideoData.EdidCheckNum, gCurHardwareConfigData.VideoData.ResolutionChecksum));
	HWSIG_TRACE((-1,"CDSchecksum:%x\n", gCurHardwareConfigData.DiskData.CDSchecksum));

	Status = GetFirmwareUpdateCountFromNvram(&ChangeCount);
	if(!EFI_ERROR(Status)){
		HWSIG_TRACE((-1,"Update Change Count:%x\n", ChangeCount));
	}
	else {
		ChangeCount = 0;
	}
	
	gCurHardwareConfigData.FirmwareUpdateCount = ChangeCount;
//<EIP147244 >
	Status = GetSetupCountFromNvram(&SetupCount);

	gCurHardwareConfigData.SetupUpdateCount = SetupCount;

	TRACE((-1,"Setup Update Count:%d\n",SetupCount));
//<EIP147244 >

	if(gExternalFunCallCount !=0)
	{
		for(i=0;i<gExternalFunCallCount;i++)
		{
			TRACE((-1,"Used Protocol Checksum:%x\n",gCurHardwareConfigData.ReturnChecksum[i]));
		}

		QuickSort( gCurHardwareConfigData.ReturnChecksum ,0 , gExternalFunCallCount-1 );

		for(i=0;i<gExternalFunCallCount;i++)
		{
			TRACE((-1,"After Sorting :%x\n",gCurHardwareConfigData.ReturnChecksum[i]));
		}
	}

    FacsSignature = CRC32(&gCurHardwareConfigData.bPs2Keyboard,(UINT16)(sizeof(HW_CONFIG_DATA)),0);
    HWSIG_TRACE((-1,"Update curFacsSigVar:%x\n", FacsSignature));
	
    //Update Hardware Signature of FACS table
    for(Index = 0; Index < 3; Index++)
    {        
        if(AcpiFacsTable[Index] == 0)
            continue;
        
        FacsPtr = (FACS_20 *)(UINTN)AcpiFacsTable[Index];
        FacsPtr->HardwareSignature = FacsSignature;        
    }
	
	pBS->CloseEvent(Event);

    return Status;
}

//<EIP147244 >
EFI_STATUS 
SetSetupCountToNvram (
    IN UINT32 *ChangeTime )
{
    EFI_STATUS          Status;
    UINTN               VarSize = sizeof(UINT32);

    if(ChangeTime == NULL)
        return EFI_INVALID_PARAMETER;
    
    Status = pRS->SetVariable(
            SETUP_UPDATE_COUNT_VARIABLE, 
            &gSetupUpdateCountGuid,
            EFI_VARIABLE_NON_VOLATILE |
            EFI_VARIABLE_BOOTSERVICE_ACCESS |
            EFI_VARIABLE_RUNTIME_ACCESS,
            VarSize, 
            ChangeTime
            ); 
    
    return Status;    
}

VOID SetupChangeCount(VOID)
{
	UINT32 SetupCount;

	SetupCount=0;
	GetSetupCountFromNvram(&SetupCount);
	SetupCount++;
	SetSetupCountToNvram(&SetupCount);
}
//<EIP147244 >

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
