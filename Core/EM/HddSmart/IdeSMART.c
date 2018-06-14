//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/HddSmart/IdeSMART.c 26    12/22/11 4:29a Lavanyap $
//
// $Revision: 26 $
//
// $Date: 12/22/11 4:29a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddSmart/IdeSMART.c $
// 
// 26    12/22/11 4:29a Lavanyap
// [TAG]  		EIP77259
// [Category]  	Improvement
// [Description]  	Included rollbacked check-ins from ver 14, 15, 16, 17
// and made it compatible with core 4.6.5.3.
// [Files]  		IdeSMART.c, IdeSMART.h, IdeSMART.mak, IdeSMART.uni,
// IdeSMART.dxs
// 
// 25    12/19/11 1:10a Rameshr
// [TAG]  		EIP77527
// [Category]  	Improvement
// [Description]  	IdeSecurity, IdeAcoustic and IdeSmart changes should be
// done based on the Core Version checking.
// [Files]  		IdeSecurity.c, IdeSmart.c , Acoustic.c 
// 
// 24    12/07/11 1:29a Rameshr
// EIP 77142 changes checked-in.
// 
// 22    12/05/11 6:25p Rajkumarkc
// [TAG]         EIP77142 
// [Category]    Improvement
// [Description] Added the function 'IdeNonDataCommandExp' in the
// 'IDE_BUS_PROTOCOL' and removed the existing function
// 'IdeNonDataCommand' for supporting the upper 24bits of LBA.
// [Files]
//     Ata.c, IdeBus.c, Idebus.h, PIDEBus.h, Acoustic.c, IdeSecurity.c,
// IdeSMART.c
// 
// 21    11/16/11 1:40a Lavanyap
//  [TAG]  		EIP45383
//  [Category]  	New Feature
//  [Description]  	Added Setup option in Advanced setup page to Check HDD
// SMART status in POST.
//  [Files]  		IdeSMART.c, IdeSMART.sdl, IdeSMART.uni, IdeSMART.sd,
// IdeSMART.cif
// 
// 20    4/28/11 9:24a Mirk
// [TAG]  		EIP55708
// [Category]	Improvement
// [Description]  	If IdeSmart Error is detected and Quiet Boot is
// enabled,the system waits for F1, while Quiet Boot Logo is displayed.
// [Solution]	If the IdeSmart error found, switch to PostScreen and
// display the error msg.
// [Files] - IdeSmart.c
// 
// 18    3/17/11 10:37a Krishnakumarg
// [TAG] - EIP 55534
// [Category]- Defect
// [Symptom] - Component HddSmart not labeled for CORE 4.6.4.1
// [Solution] - IdeSmart is updated for Core 4.6.4.1
// [Files] - IdeSmart.c,Idesmart.h,IdeSmart.mak,IdeSmart.dxs,IdeSmart.uni,
// IdeSmart.chm
// 
// 13    8/20/10 4:30p Krishnakumarg
// Ide Smart doesn't support the ATA 8 Read Smart Data. EIP#42492
// Corrected datasize for PollPeriod in Selftest funtion
// 
// 12    8/13/10 4:47p Krishnakumarg
// Ide Smart doesn't support the ATA 8 Read Smart Data. EIP#42492 
// 
// 11    6/13/10 4:14p Krishnakumarg
// Ide Smart Protocol reports errors and prompts for continuing when
// SMARTReturnStatus function is called. EIP#39414
// 
// 10    5/07/10 11:20a Krishnakumarg
// Added ELINK for OEM to override SMART error handling. EIP#31559
// Also has coding standard changes
// 
// 9     5/05/10 5:23p Yul
// EIP 37065 
// System hang or reset when set AHCI mode and install a SMART failed HDD
// with AHCI mode.
// 
// 8     5/03/10 11:03a Krishnakumarg
// Request additional generic functionality to be added to the IdeSMART
// component.EIP#31559
// 
// 7     3/26/10 5:41p Krishnakumarg
// UEFI2.1 compliance change EIP#34744.
// 
// 6     1/15/10 9:56a Yul
// coding standard
//
// 5     3/30/09 9:24a Fredericko
//
// 4     3/11/09 6:49p Fredericko
// EIP19618 removed dependency on foundation.lib functions
//
// 3     4/18/08 10:04a Rameshraju
// Updated proper comments.
//
// 2     10/03/08 6:56p Anandakrishnanl
// Fixed the Left Shift, which was accidently checked in with extra LT
// symbol.
//
// 1     7/03/08 5:19p Anandakrishnanl
// Added IdeSmart Module after removing IdeSmart.c from Idebus Src Module
//
// 2     13/04/07 3:05p Anandakrishnanl
// Ide Bus Module - Update source files to comply with "AMI coding
// standard"!!!
//
// 1     12/01/05 9:43a Felixp
//
// 5     8/22/05 4:32p Srinin
// ATA/ATAPI identification changed.
//
// 5     8/17/05 3:28p Srinin
// ATA/ATAPI device identification modified.
//
// 4     3/04/05 11:34a Mandal
//
// 3     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     1/10/05 11:30a Srinin
// SMART support added.
//
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name: IDESMART.c
//
// Description: IDE SMART Support
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "IdeSMART.h"
#include "IdeSMARTStrTokens.h"
#include <Setup.h>

#if EFI_SPECIFICATION_VERSION > 0x20000
#include "Include\UefiHii.h"
#include "Protocol\HiiDatabase.h"
#include "Protocol\HiiString.h"
#endif

static EFI_GUID gHddSmartInitProtocolGuid = HDD_SMART_INIT_PROTOCOL_GUID;
EFI_GUID gSMARTProtocolGuid = IDE_SMART_INTERFACE_GUID;
EFI_GUID gSetupGuid         = SETUP_GUID; 

#if EFI_SPECIFICATION_VERSION > 0x20000
#else
EFI_GUID gEfiHiiProtocolGuid = EFI_HII_PROTOCOL_GUID;
#endif

EFI_GUID gAmiPostManagerProtocolGuid = AMI_POST_MANAGER_PROTOCOL_GUID;

EFI_HII_HANDLE            HiiPostHandle;

#if EFI_SPECIFICATION_VERSION > 0x20000
#define LANGUAGE_CODE_ENGLISH    "en-US"

EFI_HII_STRING_PROTOCOL *HiiString=NULL;
CHAR8 Language[] = LANGUAGE_CODE_ENGLISH;

#else
#define LANGUAGE_CODE_ENGLISH    "eng"

EFI_HII_PROTOCOL          *pHii;
#endif

AMI_POST_MANAGER_PROTOCOL *pAmiPostMgr;
SETUP_DATA                gSetupData;

// Generic function in this file that will call function specified via elink
VOID ReportSmartFailure(BOOLEAN Mode, VOID *Interface);

// ELINK defined function that will be called.  Function name 'OemReportSmartFailureFunction'
//   is #defined via the makefile /D to be the ELINK function name
VOID OemReportSmartFailureFunction(BOOLEAN Mode, VOID *Interface);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IdeSMARTEntryPoint
//
// Description: This function is the entry point for IDE SMART Driver.
//
// Input:
//  EFI_HANDLE          ImageHandle     Image handle.
//  EFI_SYSTEM_TABLE    *SystemTable    Pointer to the EFI system table.
//
// Output:  EFI_STATUS
//  EFI_SUCCESS         When everything is going on fine!
//
// Notes:
//  Entry Points are used to locate or install protocol interfaces and
// notification events.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS IdeSMARTEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_HANDLE Handle = NULL;
    EFI_STATUS Status;

    InitAmiLib( ImageHandle, SystemTable );

    Status = LoadStrings( ImageHandle, &HiiPostHandle );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof(HDD_SMART_INIT_PROTOCOL),
                                (VOID**)&gHddSmartInitProtocol );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    gHddSmartInitProtocol->InstallSMARTInterface   = InstallSMARTInterface;
    gHddSmartInitProtocol->UnInstallSMARTInterface = UnInstallSMARTInterface;
    gHddSmartInitProtocol->InitSMARTSupport        = InitSMARTSupport;
    gHddSmartInitProtocol->SmartDiagonasticFlag    = FALSE;
    #if SMART_DIAGNOSTICS_SUPPORT
    gHddSmartInitProtocol->SmartDiagonasticFlag = TRUE;
    #endif

    Status = pBS->InstallProtocolInterface(
        &Handle,
        &gHddSmartInitProtocolGuid,
        EFI_NATIVE_INTERFACE,
        gHddSmartInitProtocol
        );
    ASSERT_EFI_ERROR( Status );

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   InitSMARTSupport
//
// Description: Initialize SMART functionality
//
// Input:
//  IN VOID             *BusInterface,
//  IN BOOLEAN          ModeFlag
//
// Output:
//  EFI_STATUS
//
// Referrals: ConfigureIdeDeviceAndController, ConfigureIdeDevice
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitSMARTSupport(
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag )

{
    UINT8                 bData;
    EFI_STATUS            Status;
    IDENTIFY_DATA         IdentifyData;
    IDE_BUS_PROTOCOL      *IdeBusInterface;
    SATA_DEVICE_INTERFACE *SataDevInterface;
    DEVICE_TYPE           DeviceType;
    COMMAND_STRUCTURE     CommandStructure;
    UINTN                 SetupDataSize = sizeof(SETUP_DATA);  

    IdeBusInterface  = (IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    if ( ModeFlag == FALSE ){
        IdentifyData = IdeBusInterface->IdeDevice.IdentifyData;
        DeviceType   = IdeBusInterface->IdeDevice.DeviceType;
    } else {
        IdentifyData = SataDevInterface->IdentifyData;
        DeviceType   = SataDevInterface->DeviceType;
    }

    //
    // Check for ATA device
    //
    if  ( DeviceType == ATA ){
        //
        // Check if SMART is supported, if no exit
        //
        if ( IdentifyData.Command_Set_Supported_82 & 0x1 ){
            //
            // Whether to Enable or Disable SMART Support
            //
            bData = ENABLE_SMART == 1 ? SMART_ENABLE_CMD : SMART_DISABLE_CMD;

            //
            // Check if current SMART status is what is required
            //
            Status = EFI_SUCCESS;

            if ( !((IdentifyData.Command_Set_Enabled_85 & 0x1) == ENABLE_SMART)) {
                ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
                CommandStructure.Features = bData;
                CommandStructure.LBAMid   = 0x4F;
                CommandStructure.LBAHigh  = 0xC2;
                CommandStructure.Command  = SMART_COMMAND;

                Status = CommonNonDataHook( BusInterface,
                                            CommandStructure,
                                            ModeFlag );

                if ( EFI_ERROR( Status )) {
                    return Status;
                }
            }

            //
            // Enable Autosave feature
            //
            if ((Status == EFI_SUCCESS) && (bData == SMART_ENABLE_CMD)) {
                ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
                CommandStructure.Features    = SMART_AUTOSAVE;
                CommandStructure.SectorCount = 0xF1;
                CommandStructure.LBAMid      = 0x4F;
                CommandStructure.LBAHigh     = 0xC2;
                CommandStructure.Command     = SMART_COMMAND;

                Status = CommonNonDataHook( BusInterface,
                                            CommandStructure,
                                            ModeFlag );

                if ( EFI_ERROR( Status )) {
                    return Status;
                }
											
				//
				// Get SMART Self test setup option
				//
                Status = pRS->GetVariable(L"Setup", &gSetupGuid, NULL,
                                    &SetupDataSize, &gSetupData);

                if (EFI_ERROR(Status)) {
                    //
                    // If Setup Variable is not found, set Default values
                    //
                    gSetupData.SmartSelfTest = DEFAULT_SMART_SELFTEST;
                }

                if (gSetupData.SmartSelfTest) {

                    //
                    // If SMART threshold exceeded, report it to the user.
                    //
                    Status = SMARTReturnStatusWrapper( BusInterface, ModeFlag );

                    if (EFI_ERROR(Status)) {
                        ERROR_CODE( DXE_IDE_SMART_ERROR, EFI_ERROR_MAJOR );
                        ReportSmartFailure(ModeFlag, BusInterface);
                    }
                }
            }
        }
    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SMARTReturnStatusWrapper
//
// Description: Return SMART Status
//
// Input:
//      IN VOID             *BusInterface,
//      IN BOOLEAN          ModeFlag
//
// Output:
//  EFI_STATUS
//
// Referrals: ConfigureIdeDeviceAndController, ConfigureIdeDevice
//
// Notes:   Returns EFI_SUCCESS if threshold is not exceeded.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SMARTReturnStatusWrapper(
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag )
{
    UINT8                 bData;
    UINT16                wData = THRESHOLD_NOT_EXCEEDED;
    EFI_STATUS            Status;
    COMMAND_STRUCTURE     CommandStructure;
    IDE_BUS_PROTOCOL      *IdeBusInterface;
    SATA_DEVICE_INTERFACE *SataDevInterface;
    EFI_PCI_IO_PROTOCOL   *PciIo            = NULL;

    IdeBusInterface  = (IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    //
    // Read the SMART return Status
    //
    ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Features = SMART_RETURN_STATUS;
    CommandStructure.LBAMid   = 0x4F;
    CommandStructure.LBAHigh  = 0xC2;
    CommandStructure.Command  = SMART_COMMAND;

    Status = CommonNonDataHook( BusInterface, CommandStructure, ModeFlag );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    if ( ModeFlag == FALSE ){
        if ( !EFI_ERROR( Status )){
            PciIo = IdeBusInterface->PciIO;

            PciIo->Io.Read(
                IdeBusInterface->PciIO,
                EfiPciIoWidthFifoUint8,
                EFI_PCI_IO_PASS_THROUGH_BAR,
                IdeBusInterface->IdeDevice.Regs.CommandBlock.
                LBAHighReg,
                1,
                &bData
                );

            //
            // Get the LBA Mid/High register contends.
            //
            wData = bData << 8;
            PciIo->Io.Read(
                IdeBusInterface->PciIO,
                EfiPciIoWidthFifoUint8,
                EFI_PCI_IO_PASS_THROUGH_BAR,
                IdeBusInterface->IdeDevice.Regs.CommandBlock.
                LBAMidReg,
                1,
                &bData
                );
            wData |= bData;
        }
    }else{
        volatile AHCI_RECEIVED_FIS *FISReceiveAddress;
        FISReceiveAddress = (AHCI_RECEIVED_FIS*)SataDevInterface->PortFISBaseAddr;

        // Get the pointer to RFIS
        if ( !EFI_ERROR( Status ) && (FISReceiveAddress->Ahci_Rfis[0] == FIS_REGISTER_D2H))
            wData = (FISReceiveAddress->Ahci_Rfis[6] << 8) + FISReceiveAddress->Ahci_Rfis[5];
    }

    if ( wData == THRESHOLD_NOT_EXCEEDED )
        Status = EFI_SUCCESS;
    else
        Status = EFI_DEVICE_ERROR;

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SmartErrorThresholdExceeded
//
// Description: Default function to report SMART failures to the POST screen
//
// Input:   BOOLEAN Mode - TRUE - Device is in IDE mode
//                        FALSE - Device is in AHCI mode
//          VOID *Interface - Interface.  Should be cast into SATA_DEVICE_INTERFACE
//              or IDE_BUS_PROTOCOL depending on Mode parameter
//
// Output:  none
//
// Returns: none
//
// Referrals: SMARTReturnStatusWrapper 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmartErrorThresholdExceeded(BOOLEAN ModeFlag, VOID *Interface)
{
    EFI_STATUS Status;

    UINTN StringSize = 0;
    CHAR16 *StrBuffer = NULL;

    CHAR16 *Str1 = NULL;
    CHAR16 *Str2 = NULL;
    CHAR16 *DeviceName = NULL;

    UINT8 ChannelorPort;
    UINT8 DeviceorPMPort;

    STRING_REF Token;

    EFI_INPUT_KEY Key;

    // Get the Port/Channel information from the interface
    if(ModeFlag){
        // Sata Mode
        DeviceName = ((SATA_DEVICE_INTERFACE*)Interface)->UDeviceName->UnicodeString;
        ChannelorPort = ((SATA_DEVICE_INTERFACE*)Interface)->PortNumber;
        DeviceorPMPort = ((SATA_DEVICE_INTERFACE*)Interface)->PMPortNumber;
    }else{
        // IDE Mode
        DeviceName = ((IDE_BUS_PROTOCOL*)Interface)->IdeDevice.UDeviceName->UnicodeString;
        ChannelorPort = ((IDE_BUS_PROTOCOL*)Interface)->IdeDevice.Channel;
        DeviceorPMPort = ((IDE_BUS_PROTOCOL*)Interface)->IdeDevice.Device;
    }

    // Locate the Hii Protocol for Getting strings from our string package
#if EFI_SPECIFICATION_VERSION > 0x20000
    Status = pBS->LocateProtocol( &gEfiHiiStringProtocolGuid, NULL, &HiiString);
#else
    Status = pBS->LocateProtocol( &gEfiHiiProtocolGuid, NULL, &pHii );
#endif
    ASSERT_EFI_ERROR (Status);

    // Locate the AMI Post Manger protocol for displaying information on the post screen
    Status = pBS->LocateProtocol(   &gAmiPostManagerProtocolGuid,
                                    NULL,
                                    &pAmiPostMgr );

    // Check if we could locate the ami post manager
    if(!EFI_ERROR(Status) && pST->ConOut != NULL){
        // Depending on the mode, get different strings to identify the port the failing
        //  device is connected to
        if(ModeFlag){
            // Sata Mode

            // Print the SATA port that the device is connected
            //  so get the "Port" string
            Status = GetHiiString(  HiiPostHandle,
                                    STRING_TOKEN( STR_SMART_PORT ),
                                    &StringSize,
                                    &Str2);

	    	if ( EFI_ERROR( Status )) {
 	           return;
   	    	}

            // allocate enough space to print the "port %d" string 
            Status = pBS->AllocatePool(EfiBootServicesData, sizeof(CHAR16)*(Wcslen(Str2)+4), &Str1);
	    	if ( EFI_ERROR( Status )) {
 	           return;
   	    	}

            // Create the "Port <0|1|2|3|4|5>" string in Str1
            Swprintf(Str1, L"%s %01d", Str2, ChannelorPort);

            // Fill string 2 with a null
            Str2[0] = L'\0';
        } else {
            // IDE Mode

            // Determine if we need to get the "Primary" or "Secondary" string
            if (ChannelorPort == PRIMARY_CHANNEL) Token = STRING_TOKEN(STR_PRIMARY);  
            else Token = STRING_TOKEN(STR_SECONDARY);  

            // Get the string out of the Hiidatabase into Str1
            Status = GetHiiString(  HiiPostHandle,
                                    Token,
                                    &StringSize,
                                    &Str1);

	    	if ( EFI_ERROR( Status )) {
 	           return ;
   	    	}

            // Determine if we need to get the "Master" or "Slave" string
            if (DeviceorPMPort == MASTER_DRIVE) Token = STRING_TOKEN(STR_MASTER);  
            else Token = STRING_TOKEN(STR_SLAVE);  

            // Get the string out of the Hiidatabase into Str1
            Status = GetHiiString(  HiiPostHandle,
                                    Token,
                                    &StringSize,
                                    &Str2);
	    	if ( EFI_ERROR( Status )) {
 	           return ;
   	    	}
        }

        // Determine the size of all the compents we are trying to print
        //  and additional spaces for the newline, Carrage return, the two spaces
        //  the colon and the null terminiation
        StringSize = Wcslen(Str1) + Wcslen(Str2) + Wcslen(DeviceName) + 7;

        Status = pBS->AllocatePool(EfiBootServicesData, StringSize*sizeof(CHAR16), &StrBuffer);
        if ( EFI_ERROR( Status )) {
            return;
        }

        // Build the string for IDE or SATA: 
        // ide string looks like - "<Primary|Secondary> <Master|Slave> : <Device Name String>"
        // sata string looks like - "Port <0|1|2|3|4|5> : <Device Name String>"
        Swprintf(StrBuffer, L"\n\r%s %s: %s", Str1, Str2, DeviceName);

        // free the helper buffers
        pBS->FreePool(Str1);
        Str1 = NULL;
        pBS->FreePool(Str2);
        Str2 = NULL;

        // Display the post message
        pAmiPostMgr->SwitchToPostScreen();
        pAmiPostMgr->DisplayPostMessage(StrBuffer);

        // and free the buffer that was used
        pBS->FreePool(StrBuffer);    
        StrBuffer = NULL;

        // get the smart failure string from the Hii Database
        Status = GetHiiString(HiiPostHandle,
                            STRING_TOKEN(STR_SMART_FAILURE),
                            &StringSize,
                            &Str1);

		if ( EFI_ERROR( Status )) {
            return;
 		}

        // And display it below the drive information strings, then free the space allocated
        pAmiPostMgr->DisplayPostMessage(Str1);
        pBS->FreePool(Str1);
        Str1 = NULL;

        // If keyboard input is available, pause for user input
        if(pST->ConIn != NULL){
            // Get the pause string from the Hii Database
            Status = GetHiiString(HiiPostHandle,
                                   STRING_TOKEN(STR_SMART_FAILURE_PROMPT),
                                   &StringSize,
                                   &Str1);

	    	if ( EFI_ERROR( Status )) {
 	           return;
   	    	}

            // Display the pause message on the screen
            pAmiPostMgr->DisplayPostMessage( Str1 );

            // Free the space allocated by GetHiiString
            pBS->FreePool(Str1);
            
            // And wait for the user to press the input key
            Key.UnicodeChar = 0;
            do
            {
                // Pause for 1/2 a second between key press reads
                pBS->Stall(50000);

                pST->ConIn->ReadKeyStroke( pST->ConIn, &Key );
            } while ( Key.ScanCode != WAIT_FOR_ERROR_KEY );
        }//if(pST->ConIn != NULL)
    }//if(!EFI_ERROR(Status) && pST->ConOut != NULL)
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   InstallSMARTInterface
//
// Description: Installs SMARTInterface Protocol
//
// Input:
//  IN VOID             *BusInterface
//  IN BOOLEAN          ModeFlag
//
// Output:
//  EFI_STATUS
//
// Notes:
//      Already SMART support capability has been established.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InstallSMARTInterface(
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag )
{
    EFI_STATUS            Status = EFI_UNSUPPORTED;
    SMART_INTERFACE       *SMARTInterface;
    UINT8                 *Buffer;
    IDENTIFY_DATA         IdentifyData;
    EFI_HANDLE            IdeDeviceHandle;
    IDE_BUS_PROTOCOL      *IdeBusInterface;
    SATA_DEVICE_INTERFACE *SataDevInterface;
    DEVICE_TYPE           DeviceType;
    COMMAND_STRUCTURE     CommandStructure;

    IdeBusInterface  = (IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    if ( ModeFlag == FALSE ){
        IdentifyData    = IdeBusInterface->IdeDevice.IdentifyData;
        DeviceType      = IdeBusInterface->IdeDevice.DeviceType;
        IdeDeviceHandle = IdeBusInterface->IdeDeviceHandle;
    } else {
        IdentifyData    = SataDevInterface->IdentifyData;
        DeviceType      = SataDevInterface->DeviceType;
        IdeDeviceHandle = SataDevInterface->IdeDeviceHandle;
    }

    //
    // Check for HDD and SMART support
    //
    if  ((DeviceType == ATA)        // It is HDD
         && (IdentifyData.Command_Set_Supported_82 & 0x1)   // SMART supported
         && (IdentifyData.Command_Set_Supported_84 & 0x2))  // SMART Enabled

    {
        Status = pBS->AllocatePool( EfiBootServicesData,
                                    512,
                                    (VOID**)&Buffer );

        if ( EFI_ERROR( Status )){
            return EFI_OUT_OF_RESOURCES;
        }

        ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
        CommandStructure.Buffer    = Buffer;
        CommandStructure.ByteCount = 512;
        CommandStructure.Features  = SMART_READ_DATA;
        CommandStructure.LBAMid    = 0x4F;
        CommandStructure.LBAHigh   = 0xC2;
        CommandStructure.Command   = SMART_COMMAND;

        if ( ModeFlag == FALSE ){
            CommandStructure.Device = IdeBusInterface->IdeDevice.Device << 4;
            Status                  = IdeBusInterface->AtaPioDataIn(
                            IdeBusInterface,
                            CommandStructure.Buffer,
                            CommandStructure.ByteCount,
                            CommandStructure.Features,
                            (UINT8)CommandStructure.SectorCount,
                            CommandStructure.LBALow,
                            CommandStructure.LBAMid,
                            CommandStructure.LBAHigh,
                            CommandStructure.Device,
                            CommandStructure.Command,
                            FALSE);
        } else {
            Status = SataDevInterface->AhciBusInterface->ExecutePioDataCommand(
                SataDevInterface,
                &CommandStructure,
                FALSE );
        }

        if ( EFI_ERROR( Status )){
            pBS->FreePool( Buffer );
            return Status;
        }

        //
        // Install the Interface
        //
        Status = pBS->AllocatePool( EfiBootServicesData,
                                    sizeof(SMART_INTERFACE),
                                    (VOID**)&SMARTInterface );

        if ( EFI_ERROR( Status )){
            pBS->FreePool( Buffer );
            return Status;
        }

        SMARTInterface->SMARTSelfTest       = SMARTSelfTest;
        SMARTInterface->SMARTSelfTestStatus = SMARTSelfTestStatus;
        SMARTInterface->SMARTReturnStatus   = SMARTReturnStatus;
        SMARTInterface->SendSmartCommand    = SendSmartCommand;
        SMARTInterface->SmartReadData       = SmartReadData;
        SMARTInterface->SmartWriteData      = SmartWriteData;
        SMARTInterface->SMARTAbortSelfTest  = SMARTAbortSelfTest;
        SMARTInterface->SMARTGetSmartData   = SMARTGetSmartData;
        SMARTInterface->ShortPollingTime    = Buffer[372];
        if(Buffer[373] == 0xFF)
            SMARTInterface->ExtPollingTime  = (UINT16)(Buffer[376]<<8 | Buffer[375]);
        else
            SMARTInterface->ExtPollingTime  = (UINT16)Buffer[373];

        if ( ModeFlag == FALSE ){
            IdeBusInterface->SMARTInterface = SMARTInterface;
            SMARTInterface->BusInterface    = IdeBusInterface;
        }else{
            SataDevInterface->SMARTInterface = SMARTInterface;
            SMARTInterface->BusInterface     = SataDevInterface;
        }

        //
        // Set ModeFlag to FALSE if IdeBus else TRUE for Ahci Bus.
        //
        SMARTInterface->ModeFlag = ModeFlag;  // Ide Bus

        Status = pBS->InstallMultipleProtocolInterfaces(&IdeDeviceHandle,
                                                        &gSMARTProtocolGuid,
                                                        SMARTInterface,
                                                        NULL );

        pBS->FreePool( Buffer );
    }
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   UnInstallSMARTInterface
//
// Description: Uninstall SMARTInterface Protocol
//
// Input:
//  IN VOID             *BusInterface
//  IN BOOLEAN          ModeFlag
//
// Output:
//  EFI_STATUS
//
// Referrals: IdeBusStop
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UnInstallSMARTInterface(
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag )
{
    EFI_STATUS            Status;
    SMART_INTERFACE       *SMARTInterface;
    IDE_BUS_PROTOCOL      *IdeBusInterface;
    SATA_DEVICE_INTERFACE *SataDevInterface;
    EFI_HANDLE            IdeDeviceHandle;

    IdeBusInterface  = (IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    if ( ModeFlag == FALSE ){
        SMARTInterface  = IdeBusInterface->SMARTInterface;
        IdeDeviceHandle = IdeBusInterface->IdeDeviceHandle;
    }else{
        SMARTInterface  = SataDevInterface->SMARTInterface;
        IdeDeviceHandle = SataDevInterface->IdeDeviceHandle;
    }

    if ( SMARTInterface == NULL ){
        return EFI_SUCCESS;
    }
    Status = pBS->UninstallMultipleProtocolInterfaces(IdeDeviceHandle,
                                                        &gSMARTProtocolGuid,
                                                        SMARTInterface,
                                                        NULL );

    if ( Status == EFI_SUCCESS ){
        pBS->FreePool( SMARTInterface );
        SMARTInterface = NULL;
    }
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SMARTSelfTest
//
// Description: Starts SMART SelfTest. SelfTestType will indicate whether to run
//              short or extended selftest.
//
// Input:
//  IN  IDE_SMART_INTERFACE     *This,
//  IN  UINT8                   SelfTestType, ( 0 : short, 1 :extended)
//  OUT UINT16                   *PollPeriod (Minutes)
//
// Output:
//  EFI_STATUS
//  PollPeriod will indicate the recommended time interval between polling.
//  Frequent polling will either abort the self test or may prolong it.
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SMARTSelfTest(
    IN IDE_SMART_INTERFACE *This,
    IN UINT8               SelfTestType,
    OUT UINT16              *PollPeriod )
{
    EFI_STATUS            Status;
    UINT8                 bData;

    VOID *BusInterface = ((SMART_INTERFACE* )This)->BusInterface;
    SMART_INTERFACE       *SMARTInterface = (SMART_INTERFACE*)This;
    BOOLEAN               ModeFlag        = ((SMART_INTERFACE* )This)->ModeFlag;
    IDE_BUS_PROTOCOL      *IdeBusInterface;
    SATA_DEVICE_INTERFACE *SataDevInterface;

    IdeBusInterface  = (IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    //
    // Check for Short or Extended
    //
    bData = SelfTestType == 0 ? 1 : 2;
    Status = SendSmartCommand( This, SMART_EXECUTE_OFFLINE_IMMEDIATE, NULL, bData); 

    *PollPeriod = SelfTestType == 0 ? SMARTInterface->ShortPollingTime : SMARTInterface->ExtPollingTime;

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SMARTAbortSelfTest
//
// Description: Aborts SMART Self Test. 
//
// Input:
//  IN  IDE_SMART_INTERFACE *This
//
// Output:
//  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SMARTAbortSelfTest (
    IN  IDE_SMART_INTERFACE         *This
 )
{
    VOID                            *BusInterface = ((SMART_INTERFACE * )This)->BusInterface;
    SMART_INTERFACE                 *SMARTInterface = (SMART_INTERFACE *)This;
    BOOLEAN                         ModeFlag = ((SMART_INTERFACE * )This)->ModeFlag;
    IDE_BUS_PROTOCOL                *IdeBusInterface;
    SATA_DEVICE_INTERFACE           *SataDevInterface;
    COMMAND_STRUCTURE               CommandStructure;

    IdeBusInterface         = (IDE_BUS_PROTOCOL *)BusInterface;
    SataDevInterface        = (SATA_DEVICE_INTERFACE *)BusInterface;

    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Features = SMART_EXECUTE_OFFLINE_IMMEDIATE;
    CommandStructure.LBALow   = SMART_ABORT_SELF_TEST_SUBROUTINE;
    CommandStructure.LBAMid   = 0x4F;
    CommandStructure.LBAHigh  = 0xC2;
    CommandStructure.Command  = SMART_COMMAND;
    
    return CommonNonDataHook (BusInterface, CommandStructure, ModeFlag);

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SMARTGetSmartData
//
// Description:  Get SMART data of the harddisk.
//
// Input:
//  IN  IDE_SMART_INTERFACE This
//
// Output: 
//  OUT UINT8   **SmartData
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SMARTGetSmartData (
    IN  IDE_SMART_INTERFACE         *This,
    OUT UINT8                       **SmartData
)
{
    EFI_STATUS                      Status;
    SMART_INTERFACE                 *SMARTInterface = (SMART_INTERFACE *)This;
    VOID                            *BusInterface = ((SMART_INTERFACE * )This)->BusInterface;
    BOOLEAN                         ModeFlag = ((SMART_INTERFACE * )This)->ModeFlag;
    IDE_BUS_PROTOCOL                *IdeBusInterface;
    SATA_DEVICE_INTERFACE           *SataDevInterface;
    COMMAND_STRUCTURE               CommandStructure;

    IdeBusInterface         = (IDE_BUS_PROTOCOL *)BusInterface;
    SataDevInterface        = (SATA_DEVICE_INTERFACE *)BusInterface;

    Status = pBS->AllocatePool (EfiBootServicesData, 512, (VOID**)SmartData);

    if (EFI_ERROR(Status)){
        return EFI_OUT_OF_RESOURCES;
    }

    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
    CommandStructure.Buffer     = *SmartData; 
    CommandStructure.ByteCount  = 512;
    CommandStructure.Features   = SMART_READ_DATA;
    CommandStructure.LBAMid     = 0x4F;
    CommandStructure.LBAHigh    = 0xC2;   
    CommandStructure.Command    = SMART_COMMAND;
    
    if (ModeFlag == FALSE) {
        CommandStructure.Device = IdeBusInterface->IdeDevice.Device << 4;
        Status = IdeBusInterface->AtaPioDataIn(  IdeBusInterface, 
                                                 CommandStructure.Buffer,
                                                 CommandStructure.ByteCount,
                                                 CommandStructure.Features, 
                                                 (UINT8)CommandStructure.SectorCount,
                                                 CommandStructure.LBALow, 
                                                 CommandStructure.LBAMid, 
                                                 CommandStructure.LBAHigh,
                                                 CommandStructure.Device, 
                                                 CommandStructure.Command,
                                                 FALSE
                                              );
          
    } else {
        Status = SataDevInterface->AhciBusInterface->ExecutePioDataCommand( 
                                                SataDevInterface, 
                                                &CommandStructure, 
                                                FALSE
                                              );
    }

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SMARTSelfTestStatus
//
// Description: Starts SMART SelfTest. SelfTestType will indicate whether to run
//              short or extended selftest.
//
// Input:
//  IN      IDE_SMART_INTERFACE         *This,
//  OUT     UINT8                       *TestStatus
//
// Output:
//  EFI_STATUS : TestStatus is valid only when EFI_STATUS is EFI_SUCCESS
//  TestStatus : Will indicate the % of test completed.
//  TestStatus = 0xFF Indicates Self Test Failed and EFI_STATUS = EFI_ERROR
//  Example: When TestStatus = 10, 10% of the test has been done.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SMARTSelfTestStatus(
    IN IDE_SMART_INTERFACE *This,
    OUT UINT8              *TestStatus )
{
    EFI_STATUS            Status;
    UINT8                 *Buffer;
    SMART_INTERFACE       *SMARTInterface = (SMART_INTERFACE*)This;
    VOID *BusInterface = ((SMART_INTERFACE* )This)->BusInterface;
    BOOLEAN               ModeFlag = ((SMART_INTERFACE* )This)->ModeFlag;
    IDE_BUS_PROTOCOL      *IdeBusInterface;
    SATA_DEVICE_INTERFACE *SataDevInterface;
    COMMAND_STRUCTURE     CommandStructure;

    IdeBusInterface  = (IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    Status = pBS->AllocatePool( EfiBootServicesData,
                                512,
                                (VOID**)&Buffer );

    if ( EFI_ERROR( Status )){
        return EFI_OUT_OF_RESOURCES;
    }

    ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Buffer    = Buffer;
    CommandStructure.ByteCount = 512;
    CommandStructure.Features  = SMART_READ_DATA;
    CommandStructure.LBAMid    = 0x4F;
    CommandStructure.LBAHigh   = 0xC2;
    CommandStructure.Command   = SMART_COMMAND;

    if ( ModeFlag == FALSE ){
        CommandStructure.Device = IdeBusInterface->IdeDevice.Device << 4;
        Status = IdeBusInterface->AtaPioDataIn(IdeBusInterface,
                                                CommandStructure.Buffer,
                                                CommandStructure.ByteCount,
                                                CommandStructure.Features,
                                                (UINT8)CommandStructure.SectorCount,
                                                CommandStructure.LBALow,
                                                CommandStructure.LBAMid,
                                                CommandStructure.LBAHigh,
                                                CommandStructure.Device,
                                                CommandStructure.Command,
                                                FALSE);
    }else{
        Status = SataDevInterface->AhciBusInterface->ExecutePioDataCommand(
            SataDevInterface,
            &CommandStructure,
            FALSE );
    }

    if ( EFI_ERROR( Status )){
        *TestStatus = 0xff;
        pBS->FreePool( Buffer );
        return EFI_DEVICE_ERROR;
    }

    //
    // If Bits 7:4 is not equal to 0 or 0xf then there was an error
    // in the previous selftest.
    //
    if (((Buffer[363] >> 4) != 0) && ((Buffer[363] >> 4) != 0xf)) {
        *TestStatus = 0xff;
        Status      = EFI_DEVICE_ERROR;
    }else{
        *TestStatus = Buffer[363] & 0xf;
        *TestStatus = 10 - (*TestStatus);
        *TestStatus = 10 * (*TestStatus);
    }
    pBS->FreePool( Buffer );
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SMARTReturnStatus
//
// Description: Returns SMART status
//
// Input:
//      IN      IDE_SMART_INTERFACE         *This
//
// Output:
//  EFI_STATUS
//
// Notes:   Returns EFI_SUCCESS if threshold is not exceeded.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SMARTReturnStatus(
    IN IDE_SMART_INTERFACE *This )
{
    VOID    *BusInterface = ((SMART_INTERFACE* )This)->BusInterface;
    BOOLEAN ModeFlag      = ((SMART_INTERFACE* )This)->ModeFlag;

    return (SMARTReturnStatusWrapper( BusInterface, ModeFlag ));
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SendSMARTCommand
//
// Description: Sends any Non-Data SMART Command. 
//
// Input:
//      IN      IDE_SMART_INTERFACE         *This
//      IN      UINT8                       SubCommand,
//      IN      UINT8                       AutoSaveEnable,      //OPTIONAL
//      IN      UINT8                       SelfTestType         //OPTIONAL
//
// Output:
//      EFI_STATUS
//
// Referrals: IdeNonDataCommand, ExecuteNonDataCommand
//
// Notes:   Returns EFI_UNSUPPORTED when SMART feature is not enabled.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SendSmartCommand ( 
    IN IDE_SMART_INTERFACE  *This,
    IN UINT8                SubCommand,
    IN UINT8                AutoSaveEnable,      
    IN UINT8                SelfTestType      
)
{
    EFI_STATUS                  Status;
    SMART_INTERFACE             *SMARTInterface = (SMART_INTERFACE *)This;
    VOID                        *BusInterface = ((SMART_INTERFACE * )This)->BusInterface;
    BOOLEAN                     ModeFlag = ((SMART_INTERFACE * )This)->ModeFlag;
    IDE_BUS_PROTOCOL            *IdeBusInterface;
    SATA_DEVICE_INTERFACE       *SataDevInterface;
    COMMAND_STRUCTURE           CommandStructure;
    IDENTIFY_DATA               IdentifyData;
    BOOLEAN                     EnableSmart;

    IdeBusInterface  = (IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    if ( ModeFlag == FALSE ){
        IdentifyData = IdeBusInterface->IdeDevice.IdentifyData;
    } else {
        IdentifyData = SataDevInterface->IdentifyData;
    }

    EnableSmart = SubCommand == SMART_ENABLE_CMD ? 1 : 0; 

    if(!((IdentifyData.Command_Set_Enabled_85 & 0x1) == EnableSmart)) {

   	    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE));
        CommandStructure.Features = SubCommand;
        CommandStructure.LBAMid   = 0x4F;
        CommandStructure.LBAHigh  = 0xC2;
        CommandStructure.Command  = SMART_COMMAND;

        switch (SubCommand) {

        case SMART_AUTOSAVE:
          CommandStructure.SectorCount = AutoSaveEnable;
          break;

        case SMART_EXECUTE_OFFLINE_IMMEDIATE:
          CommandStructure.LBALow   = SelfTestType;
          break;

        default:
          break;
        }

        if ( ModeFlag == FALSE ){
	        CommandStructure.Device = IdeBusInterface->IdeDevice.Device << 4;

	        //
            // Idebus API changed from Core 4.6.5.2. Added Core Version check for the OLD 
            // Core support.
            //
#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028b) 
            Status = IdeBusInterface->IdeNonDataCommand(IdeBusInterface,
                                                    CommandStructure.Features,
                                                    (UINT8)CommandStructure.SectorCount,
                                                    (UINT8)(CommandStructure.SectorCount >> 8),
                                                    CommandStructure.LBALow,
                                                    CommandStructure.LBALowExp,
                                                    CommandStructure.LBAMid,
                                                    CommandStructure.LBAMidExp,
                                                    CommandStructure.LBAHigh,
                                                    CommandStructure.LBAHighExp,
                                                    CommandStructure.Device,
                                                    CommandStructure.Command);
#else
           Status = IdeBusInterface->IdeNonDataCommand(IdeBusInterface,
                                                    CommandStructure.Features,
                                                    (UINT8)CommandStructure.SectorCount,
                                                    CommandStructure.LBALow,
                                                    CommandStructure.LBAMid,
                                                    CommandStructure.LBAHigh,
                                                    CommandStructure.Device,
                                                    CommandStructure.Command);
#endif
        } else {
            Status = SataDevInterface->AhciBusInterface->ExecuteNonDataCommand(
                                                            SataDevInterface,
                                                            CommandStructure );
        }
        return Status;
                                                
    } else {
        return EFI_UNSUPPORTED;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SmartReadData
//
// Description: Sends any Data In SMART command. 
//
// Input:
//      IN      IDE_SMART_INTERFACE         *This
//      IN      UINT8                       SubCommand,
//      IN      VOID                        *Buffer,
//      IN      UINT8                       LogAddress,   //OPTIONAL    
//      IN      UINT8                       SectorCount   //OPTIONAL  
// Output:
//      EFI_STATUS
//
// Referrals: AtaPioDataIn, SataPioDataOut
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmartReadData (
    IN  IDE_SMART_INTERFACE  *This,
    IN  UINT8                SubCommand,
    OUT VOID                 *Buffer,
    IN  UINT8                LogAddress,
    IN  UINT8                SectorCount
)
{
    EFI_STATUS              Status;
    SMART_INTERFACE         *SMARTInterface = (SMART_INTERFACE *)This;
    VOID                    *BusInterface = ((SMART_INTERFACE * )This)->BusInterface;
    BOOLEAN                 ModeFlag = ((SMART_INTERFACE * )This)->ModeFlag;
    IDE_BUS_PROTOCOL        *IdeBusInterface;
    SATA_DEVICE_INTERFACE   *SataDevInterface;
    COMMAND_STRUCTURE       CommandStructure;
    BOOLEAN                 MultipleSectors = FALSE;

   IdeBusInterface         = (IDE_BUS_PROTOCOL *)BusInterface;
   SataDevInterface        = (SATA_DEVICE_INTERFACE *)BusInterface;

    //
    //If SubCommand = SMART_READ_DATA then set SectorCount to 1 
    //
    if (SectorCount == NULL) {
        SectorCount = 1;
    }

    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Buffer     = Buffer; 

    if ( SubCommand == SMART_READLOG ) {
        CommandStructure.LBALow       = LogAddress ;      // LOG Address to read
        CommandStructure.SectorCount  = SectorCount;      // No.of sectors to read
        CommandStructure.ByteCount    = SectorCount*ATA_SECTOR_BYTES;
        if ( SectorCount>1 ) {
            MultipleSectors = TRUE;
        }
    } else {
        //
        // SubCommand SMART_READ_DATA reads only 512 bytes.
        //
        CommandStructure.ByteCount    = 512;
    }
    CommandStructure.Features   = SubCommand;
    CommandStructure.LBAMid     = 0x4F;
    CommandStructure.LBAHigh    = 0xC2;
    CommandStructure.Command    = SMART_COMMAND;
 
    if (ModeFlag == FALSE) {

        Status = IdeBusInterface->AtaPioDataOut ( 
                                       IdeBusInterface,
                                       CommandStructure.Buffer,
                                       CommandStructure.ByteCount, 
                                       CommandStructure.Features,
                                       CommandStructure.SectorCount, 
                                       CommandStructure.LBALow, 
                                       CommandStructure.LBALowExp, 
                                       CommandStructure.LBAMid, 
                                       CommandStructure.LBAMidExp, 
                                       CommandStructure.LBAHigh,
                                       CommandStructure.LBAHighExp, 
                                       CommandStructure.Device, 
                                       CommandStructure.Command,
                                       FALSE, 
                                       MultipleSectors );
          
    } else {

        Status = SataDevInterface->AhciBusInterface->SataPioDataOut(
                                                        SataDevInterface,
                                                        CommandStructure.Buffer,
                                                        CommandStructure.ByteCount,
                                                        CommandStructure.Features,
                                                        CommandStructure.LBALow, 
                                                        CommandStructure.LBALowExp, 
                                                        CommandStructure.LBAMid, 
                                                        CommandStructure.LBAMidExp, 
                                                        CommandStructure.LBAHigh,
                                                        CommandStructure.LBAHighExp,
                                                        CommandStructure.Command,
                                                        FALSE );
    }
	if (EFI_ERROR(Status)) {
        pBS->FreePool(Buffer);
	}
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SmartWriteData
//
// Description: Sends any Data Out SMART command.
//
// Input:
//      IN      IDE_SMART_INTERFACE         *This
//      IN      UINT8                       SubCommand,
//      IN      VOID                        *Buffer,
//      IN      UINT8                       LogAddress,
//      IN      UINT8                       SectorCount
// Output:
//      EFI_STATUS
//
// Referrals: AtaPioDataOut, SataPioDataOut
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmartWriteData (
    IN IDE_SMART_INTERFACE  *This,
    IN UINT8                SubCommand,
    IN VOID                 *Buffer,
    IN UINT8                LogAddress,
    IN UINT8                SectorCount
)
{
    EFI_STATUS                  Status;
    IDE_BUS_PROTOCOL            *IdeBusInterface;
    SATA_DEVICE_INTERFACE       *SataDevInterface;
    COMMAND_STRUCTURE           CommandStructure;
    SMART_INTERFACE             *SMARTInterface = (SMART_INTERFACE *)This;
    VOID                        *BusInterface = ((SMART_INTERFACE * )This)->BusInterface;
    BOOLEAN                     ModeFlag = ((SMART_INTERFACE * )This)->ModeFlag;
    BOOLEAN                     MultipleSectors = FALSE;

   	IdeBusInterface         = (IDE_BUS_PROTOCOL *)BusInterface;
   	SataDevInterface        = (SATA_DEVICE_INTERFACE *)BusInterface;

    ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Buffer      = Buffer;
    CommandStructure.Features    = SubCommand;
    CommandStructure.ByteCount   = SectorCount * ATA_SECTOR_BYTES;
    CommandStructure.SectorCount = SectorCount;
    CommandStructure.LBALow      = LogAddress;       //LOG address to write on
    CommandStructure.LBAMid      = 0x4F;
    CommandStructure.LBAHigh     = 0xC2;
    CommandStructure.Command     = SMART_COMMAND;

    if ( SectorCount>1 )
        MultipleSectors = TRUE;

    if (ModeFlag == FALSE) {
        Status = IdeBusInterface->AtaPioDataOut ( 
                                       IdeBusInterface,
                                       CommandStructure.Buffer,
                                       CommandStructure.ByteCount, 
                                       CommandStructure.Features,
                                       CommandStructure.SectorCount, 
                                       CommandStructure.LBALow, 
                                       CommandStructure.LBALowExp, 
                                       CommandStructure.LBAMid, 
                                       CommandStructure.LBAMidExp, 
                                       CommandStructure.LBAHigh,
                                       CommandStructure.LBAHighExp, 
                                       CommandStructure.Device, 
                                       CommandStructure.Command,
                                       TRUE, 
                                       MultipleSectors ); 
    } else {

        Status = SataDevInterface->AhciBusInterface->SataPioDataOut (
                                                        SataDevInterface, 
                                                        CommandStructure.Buffer,
                                                        CommandStructure.ByteCount, 
                                                        CommandStructure.Features,
                                                        CommandStructure.LBALow, 
                                                        CommandStructure.LBALowExp, 
                                                        CommandStructure.LBAMid, 
                                                        CommandStructure.LBAMidExp, 
                                                        CommandStructure.LBAHigh,
                                                        CommandStructure.LBAHighExp, 
                                                        CommandStructure.Command,
                                                        TRUE ); 
    }
    
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   CommonNonDataHook
//
// Description: Common Hook which Calls Non Data Command.
//
// Input:       IN    VOID*                 BusInterface,
//              IN    COMMAND_STRUCTURE     CommandStructure,
//              IN    BOOLEAN               ModeFlag
//
// Output:  
//  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CommonNonDataHook(
    IN VOID              *BusInterface,
    IN COMMAND_STRUCTURE CommandStructure,
    IN BOOLEAN           ModeFlag )
{
    EFI_STATUS            Status;
    IDE_BUS_PROTOCOL      *IdeBusInterface;
    SATA_DEVICE_INTERFACE *SataDevInterface;

    IdeBusInterface  = (IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    if ( ModeFlag == FALSE ){
        CommandStructure.Device = IdeBusInterface->IdeDevice.Device << 4;
        //
        // Idebus API changed from Core 4.6.5.2. Added Core Version check for the OLD 
        // Core support.
        //
#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028b) 
        Status = IdeBusInterface->IdeNonDataCommand(IdeBusInterface,
                                                    CommandStructure.Features,
                                                    (UINT8)CommandStructure.SectorCount,
                                                    (UINT8)(CommandStructure.SectorCount >> 8),
                                                    CommandStructure.LBALow,
                                                    CommandStructure.LBALowExp,
                                                    CommandStructure.LBAMid,
                                                    CommandStructure.LBAMidExp,
                                                    CommandStructure.LBAHigh,
                                                    CommandStructure.LBAHighExp,
                                                    CommandStructure.Device,
                                                    CommandStructure.Command);
#else
        Status = IdeBusInterface->IdeNonDataCommand(IdeBusInterface,
                                                    CommandStructure.Features,
                                                    (UINT8)CommandStructure.SectorCount,
                                                    CommandStructure.LBALow,
                                                    CommandStructure.LBAMid,
                                                    CommandStructure.LBAHigh,
                                                    CommandStructure.Device,
                                                    CommandStructure.Command);
#endif
    }else {
        Status = SataDevInterface->AhciBusInterface->ExecuteNonDataCommand(
            SataDevInterface,
            CommandStructure );
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetHiiString
//
// Description: This function Reads a String from HII
//
// Input:       HiiHandle - Efi Hii Handle
//              Token     - String Token
//
// Output:      Returns  Pointer to allocated String Buffer
//              NULL -  if could not get the data
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetHiiString(
    IN EFI_HII_HANDLE HiiHandle,
    IN STRING_REF     Token,
    IN OUT UINTN      *pDataSize,
    OUT EFI_STRING    *ppData )
{
    EFI_STATUS Status;

    if ( !*ppData ){
        *pDataSize = 0;
    }

#if EFI_SPECIFICATION_VERSION>0x20000
         Status = HiiString->GetString (HiiString,
                                (CHAR8*) &Language,
                                HiiHandle,
                                Token,
                                *ppData,
                                pDataSize,
                                NULL);

#else
    Status = pHii->GetString (  pHii,
                                HiiHandle,
                                Token,
                                TRUE,
                                L"   ",
                                pDataSize,
                                *ppData);
#endif

    if ( !EFI_ERROR( Status )){
        return Status;
    }

    if ( Status == EFI_BUFFER_TOO_SMALL ){

        if ( *ppData ){
            pBS->FreePool( *ppData );
        }

        if ( !(*ppData = Malloc( *pDataSize ))){
            return EFI_OUT_OF_RESOURCES;
        }
#if EFI_SPECIFICATION_VERSION>0x20000
         Status = HiiString->GetString (HiiString,
                                (CHAR8*) &Language,
                                HiiHandle,
                                Token,
                                *ppData,
                                pDataSize,
                                NULL);

#else
        Status = pHii->GetString (  pHii, 
                                    HiiHandle, 
                                    Token, 
                                    TRUE, 
                                    L"   ",
                                    pDataSize, 
                                    *ppData);
#endif
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReportSmartFailure
//
// Description: Wrapper Function to call a ELINKed function
//
// Input:   BOOLEAN Mode - TRUE - Device is in IDE mode
//                        FALSE - Device is in AHCI mode
//          VOID *Interface - Interface.  Should be cast into SATA_DEVICE_INTERFACE
//              or IDE_BUS_PROTOCOL depending on Mode parameter
//
// Output:  none
//
// Returns: none
//
// Referrals: SmartErrorThresholdExceeded 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ReportSmartFailure(BOOLEAN Mode, VOID *Interface)
{
    OemReportSmartFailureFunction(Mode, Interface);
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
