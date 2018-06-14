//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Core/Modules/IdeBus/IdeHPA.c 6     10/11/10 11:31a Krishnakumarg $
//
// $Revision: 6 $
//
// $Date: 10/11/10 11:31a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/IdeBus/IdeHPA.c $
// 
// 6     10/11/10 11:31a Krishnakumarg
// [TAG] - EIP 43249
// [Category] - IMPROVEMENT
// [Severity] - Minor
// [Symptom]  - Non-Ascii character in comments causing build problem in
// japanese XP
// [RootCause]- Presence of Non-Ascii character
// [Solution] -  Remove Non-Ascii character present in the file
// [Files] - IdeSecurity.c,IDESMM.c, InstallIdeSmi, Ata.c, Atapi.c,
// IDEBusComponentName.c, IdeBusMaster.c, IdeHPA.c, IdePowerManagement.c
// 
// 5     8/25/10 4:10a Rameshr
// New Feature: EIP 37748
// Description: Move all the IDEBus Source driver SDL token into IdeBus
// Bin Driver.
// FilesModified: Ata.c, Atapi.c, idebus.c, IdeBus.h,
// IdebuscomponentName.c, IdeBusmaster.c IdeBusSrc.mak IdebusSrc.sdl
// IdeHpa.c, IdePowerManagement.c
// 
// 4     7/01/09 12:24p Rameshr
// Coding Standard and File header updated.
//
// 3     13/04/07 3:03p Anandakrishnanl
// Ide Bus Module - Update source files to comply with AMI coding
// standard"!!!
//
// 2     8/24/06 9:30a Felixp
// x64 support (bug fixes)
//
// 1     12/01/05 9:43a Felixp
//
// 4     3/04/05 11:35a Mandal
//
// 3     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     1/13/05 4:25p Srinin
// Host Protection Area Support added.
//
//
//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: IdeHPA.c
//
// Description:	Host Protection Area Support
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "IdeBus.h"

extern EFI_GUID gHPAProtocolGuid;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InstallHPAInterface
//
// Description:	Checks whether Host Protcted Area feature is supported or not.
//				If Supported, installs HPAProtocol.
//
// Input:
//		IDE_BUS_PROTOCOL			*IdeBusInterface,
//
// Output:
//	EFI_STATUS  : EFI_UNSUPPORTED/EFI_SUCCESS/EFI_OUT_OF_RESOURCES
//
// Modified:
//
// Referrals: IdeBusStart
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InstallHPAInterface(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    EFI_STATUS    Status;
    HPA_INTERFACE *HPAInterface;

    //
    //Check if HPA is supported or not
    //    
    if  ((IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_82 & 0x400) == 0 ) {
        return EFI_UNSUPPORTED;
    }

    //
    //Install the Interface
    //
    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof(HPA_INTERFACE),
                                (VOID**)&HPAInterface );

    if ( EFI_ERROR( Status ))  {
        pBS->FreePool( HPAInterface );
        return Status;
    }

    HPAInterface->IdeBusInterface     = IdeBusInterface;
    IdeBusInterface->HPAInterface     = HPAInterface;
    HPAInterface->GetNativeMaxAddress = GetNativeMaxAddress;
    HPAInterface->SetMaxAddress       = SetMaxAddress;
    HPAInterface->HPADisabledLastLBA  = HPADisabledLastLBA;
    HPAInterface->SetMaxPassword      = SetMaxPassword;
    HPAInterface->SetMaxLock          = SetMaxLock;
    HPAInterface->SetMaxUnLock        = SetMaxUnLock;
    HPAInterface->SetMaxFreezeLock    = SetMaxFreezeLock;

    Status = pBS->InstallMultipleProtocolInterfaces(
        &(IdeBusInterface->IdeDeviceHandle),
        &gHPAProtocolGuid, HPAInterface,
        NULL );

    if ( EFI_ERROR( Status )) {
        pBS->FreePool( HPAInterface );
        return Status;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	StopHPAInterface
//
// Description:	Uninstall HPA Protocol
//
// Input:
//		IDE_BUS_PROTOCOL			*IdeBusInterface,
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: IdeBusStop
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StopHPAInterface(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    EFI_STATUS Status;

    if ( IdeBusInterface->HPAInterface == NULL ) {
        return EFI_SUCCESS;
    }

    Status = pBS->UninstallMultipleProtocolInterfaces(
        IdeBusInterface->IdeDeviceHandle,
        &gHPAProtocolGuid, IdeBusInterface->HPAInterface,
        NULL );

    if ( Status == EFI_SUCCESS ) {
        pBS->FreePool( IdeBusInterface->HPAInterface );
        IdeBusInterface->HPAInterface = NULL;
    }
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetNativeMaxAddress
//
// Description:	Returns the Native Max LBA address supported by the device
//
// Input:
//	IN      IDE_HPA_INTERFACE			*This,
//	OUT	UINT64						*LBA
//
// Output:			LBA : Returns Native MAX LBA address.
//					EFI_STATUS  : EFI_SUCCESS/EFI_DEVICE_ERROR
//
// Modified:
//
// Referrals:
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetNativeMaxAddress(
    IN IDE_HPA_INTERFACE *This,
    OUT UINT64           *LBA )
{
    EFI_STATUS       Status;
    BOOLEAN          Ext48BitSupport         = FALSE;
    UINT8            ReadNativeMaxAddressCmd = READ_NATIVE_MAX_ADDRESS;
    IDE_BUS_PROTOCOL *IdeBusInterface        = ((HPA_INTERFACE*)This)->IdeBusInterface;
    UINT32           dData;
    UINT8            bData;

    *LBA = 0;

    //
    //Check for 48 Bit Mode Support
    //
    if ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x400 ) {
        ReadNativeMaxAddressCmd = READ_NATIVE_MAX_ADDRESS_EXT;
    }

    //
    //Get Native Max Address.
    //
    Status = IdeNonDataCommand( IdeBusInterface,
                                0,              // Features
                                0,              // Sector Count
                                0,              // LBA Low
                                0,              // LBA Mid
                                0,              // LBA High
                                0x40 | IdeBusInterface->IdeDevice.Device << 4,  // Device
                                ReadNativeMaxAddressCmd );                      // Command

    if ( EFI_ERROR( Status )) {
        return EFI_UNSUPPORTED;
    }


    //
    //Read Bits 47:24 if 48Bit LBA is supported
    //
    if ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x400 ) {
        //
        //Set HOB to 1 to read the upper DWROD
        //
        IdeWriteByte( IdeBusInterface->PciIO,
                      IdeBusInterface->IdeDevice.Regs.ControlBlock.DeviceControlReg,
                      HOB | nIEN );
        dData = 0;
        IdeReadByte( IdeBusInterface->PciIO,
                     IdeBusInterface->IdeDevice.Regs.CommandBlock.LBAHighReg,
                     &bData );

        dData = bData;                              // LBA 47:40
        IdeReadByte( IdeBusInterface->PciIO,
                     IdeBusInterface->IdeDevice.Regs.CommandBlock.LBAMidReg,
                     &bData );
        dData <<= 8;
        dData  |= bData;                             // LBA 39:32

        IdeReadByte( IdeBusInterface->PciIO,
                     IdeBusInterface->IdeDevice.Regs.CommandBlock.LBALowReg,
                     &bData );
        dData <<= 8;
        dData  |= bData;                             // LBA 31:24

        *LBA = dData;
        //
        //Shift Left *LBA by 24 Bits
        //
        *LBA = Shl64(*LBA, 24);
        //
        //Set HOB to 0 to read the Lower DWROD
        //
        IdeWriteByte( IdeBusInterface->PciIO,
                      IdeBusInterface->IdeDevice.Regs.ControlBlock.DeviceControlReg,
                      nIEN );
    }

    //
    //Read 27:24 only when 48Bit LBA is not supported
    //
    if ((IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x400) == 0 ) {
        IdeReadByte( IdeBusInterface->PciIO,
                     IdeBusInterface->IdeDevice.Regs.CommandBlock.DeviceReg,
                     &bData );
        bData &= 0xf;
        dData  = bData;                              // LBA 27:24
    }

    //
    //Read 23:0 bits of LBA address
    //
    IdeReadByte( IdeBusInterface->PciIO,
                 IdeBusInterface->IdeDevice.Regs.CommandBlock.LBAHighReg,
                 &bData );
    dData <<= 8;                                // LBA 23:16
    dData  |= bData;
    IdeReadByte( IdeBusInterface->PciIO,
                 IdeBusInterface->IdeDevice.Regs.CommandBlock.LBAMidReg,
                 &bData );
    dData <<= 8;
    dData  |= bData;                             // LBA 15:8
    IdeReadByte( IdeBusInterface->PciIO,
                 IdeBusInterface->IdeDevice.Regs.CommandBlock.LBALowReg,
                 &bData );
    dData <<= 8;
    dData  |= bData;                             // LBA 7:0

    ((UINT32) *LBA) |= dData;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SetMaxAddress
//
// Description:	Set the Max LBA address
//
// Input:
//	IN      IDE_HPA_INTERFACE			*This,
//	OUT     UINT64						LBA,
//	IN      BOOLEAN						Volatile
//
// Output:
//	EFI_STATUS  :
//
// Modified:
//
// Referrals:
//
// Notes:	if Volatile = TRUE, Values will not be preserved across resets.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetMaxAddress(
    IN IDE_HPA_INTERFACE *This,
    OUT UINT64           LBA,
    IN BOOLEAN           Volatile )
{
    EFI_STATUS       Status;
    UINT32           dData;
    UINT32           Cmd;
    UINT64           NativeMaxLBA;
    UINT8            bData;
    IDE_BUS_PROTOCOL *IdeBusInterface = ((HPA_INTERFACE*)This)->IdeBusInterface;
    BOOLEAN          Ext48BitSupport  = FALSE;


    //
    //Issue Read MAX Native command before issuing a SET MAX Address command
    //
    Status = GetNativeMaxAddress( This, &NativeMaxLBA );

    if ( EFI_ERROR( Status )) {
        return EFI_UNSUPPORTED;
    }

    //
    //Check for 48 Bit Mode Support
    //
    if ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x400 ) {
        Ext48BitSupport = TRUE;
    }

    //
    //If 48Bit LBA is supported write LBA bits 47:24
    //
    if ( Ext48BitSupport ) {
        //		Enable HOB
        IdeWriteByte( IdeBusInterface->PciIO,
                      IdeBusInterface->IdeDevice.Regs.ControlBlock.DeviceControlReg,
                      HOB | nIEN );
        //get Bits 47:24 from LBA to dData
        dData = (UINT32)Shr64(LBA, 24);

        //dDATA has LBA bits 47:24
        bData = dData >> 16;                // LBA 47:40
        IdeWriteByte( IdeBusInterface->PciIO,
                      IdeBusInterface->IdeDevice.Regs.CommandBlock.LBAHighReg,
                      bData );

        bData = dData >> 8;                 // LBA 39:32
        IdeWriteByte( IdeBusInterface->PciIO,
                      IdeBusInterface->IdeDevice.Regs.CommandBlock.LBAMidReg,
                      bData );

        bData = dData;                      // LBA 31:24
        IdeWriteByte( IdeBusInterface->PciIO,
                      IdeBusInterface->IdeDevice.Regs.CommandBlock.LBALowReg,
                      bData );

        //Reset HOB
        IdeWriteByte( IdeBusInterface->PciIO,
                      IdeBusInterface->IdeDevice.Regs.ControlBlock.DeviceControlReg,
                      nIEN );
    }

    //
    //	Write Bits 23:0
    //
    dData = (UINT32) LBA;

    //
    //	if 48Bit LBA is not supported, write bits 27:24 to Device register
    //
    if ( Ext48BitSupport == FALSE ) {
        bData = dData >> 24;
    }
    else {
        bData = 0;
    }

    bData &= 0xf;
    bData |= 0x40 | IdeBusInterface->IdeDevice.Device << 4;
    Cmd    = Ext48BitSupport == FALSE ? SET_MAX_ADDRESS : SET_MAX_ADDRESS_EXT;

    //
    //Set Max Address.
    //
    Status = IdeNonDataCommand( IdeBusInterface,
                                0,          // Features
                                Volatile == TRUE ? 0 : 1, // Sector Count
                                (UINT8)dData,       // LBA Low
                                (UINT8)( dData >> 8 ),    // LBA Mid
                                (UINT8)( dData >> 16 ),   // LBA High
                                bData,      // Device
                                Cmd ); // Command

    //
    //	Update Identify Data
    //
    GetIdentifyData( IdeBusInterface, &(IdeBusInterface->IdeDevice));

    //
    //Update the LAST LBA number
    //
    if ( Ext48BitSupport ) {
        IdeBusInterface->IdeBlkIo->BlkIo.Media->LastBlock = IdeBusInterface->IdeDevice.IdentifyData.LBA_48 - 1;
    }
    else {
        IdeBusInterface->IdeBlkIo->BlkIo.Media->LastBlock = IdeBusInterface->IdeDevice.IdentifyData.Addressable_Sector_60 - 1;
    }

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	HPADisabledLastLBA
//
// Description:	Returns the valid last LBA # when HPA is disabled.
//
// Input:
//	IN      IDE_HPA_INTERFACE			*This,
//	OUT	    UINT64						*LBA
//
// Output:
//	EFI_STATUS  : EFI_SUCCESS
//
// Modified:
//
// Referrals:
//
// Notes:	The LBA returned will be the maximum valid LBA number an OS can make use of.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HPADisabledLastLBA(
    IN IDE_HPA_INTERFACE *This,
    OUT UINT64           *LBA )
{
    BOOLEAN Ext48BitSupport           = FALSE;
    IDE_BUS_PROTOCOL *IdeBusInterface = ((HPA_INTERFACE*)This)->IdeBusInterface;

    //
    //Check for 48 Bit Mode Support
    //
    if ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x400 ) {
        Ext48BitSupport = TRUE;
    }

    //
    //Update the LAST LBA number
    //
    if ( Ext48BitSupport ) {
        *LBA = IdeBusInterface->IdeDevice.IdentifyData.LBA_48 - 1;
    }
    else {
        *LBA = IdeBusInterface->IdeDevice.IdentifyData.Addressable_Sector_60 - 1;
    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SetMaxPassword
//
// Description:	Sets the Password
//
// Input:
//	IN      IDE_HPA_INTERFACE			*This,
//	IN	    UINT8						*PasswordBuffer, (32 Bytes of Password)
//
// Output:
//	EFI_STATUS  : EFI_UNSUPPORTED/EFI_SUCCESS/EFI_DEVICE_ERROR
//
// Modified:
//
// Referrals:
//
// Notes:	READ NATIVE MAX ADDRESS should not have immediatley PRECEEDED this command.
//			To take care of this situation, a Dummy Identify Device Command will be given before
//			issuing a SET MAX PASSWORD command
//			Once the device is locked, it should be unlocked with the password before
//			issuing any SETMAXADDRESS.
//			After issuing this command device will be in UNLOCKED state.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetMaxPassword(
    IN IDE_HPA_INTERFACE *This,
    IN UINT8             *PasswordBuffer )
{
    EFI_STATUS       Status;
    IDE_BUS_PROTOCOL *IdeBusInterface = ((HPA_INTERFACE*)This)->IdeBusInterface;

    //
    //Check for HPA feature set security extensions are implemented or not?
    //
    if ( !(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x100)) {
        return EFI_UNSUPPORTED;
    }

    Status = IssueSetMaxPasswordCmd( IdeBusInterface, PasswordBuffer, SET_MAX_SET_PASSWORD );

    //
    //Update the Identify Device Data buffer
    //
    GetIdentifyData( IdeBusInterface, &(IdeBusInterface->IdeDevice));

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SetMaxLock
//
// Description:	Locks the device from accepting commands except UNLOCK and FREEZELOCK
//
// Input:
//	IN      IDE_HPA_INTERFACE			*This,
//
// Output:
//	EFI_STATUS  : EFI_UNSUPPORTED/EFI_SUCCESS/EFI_DEVICE_ERROR
//
// Modified:
//
// Referrals:
//
// Notes:	READ NATIVE MAX ADDRESS should not have immediatley PRECEED this command.
//			To take care of this situation, a Dummy Identify Device Command will be given before
//			issuing a SET MAX LOCK/UNLOCK command
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetMaxLock(
    IN IDE_HPA_INTERFACE *This )
{
    EFI_STATUS       Status;
    IDE_BUS_PROTOCOL *IdeBusInterface = ((HPA_INTERFACE*)This)->IdeBusInterface;

    //Check for HPA feature set security extensions are implemented or not? AND
    //Check whether SET MAX PASSWORD command has been issued before or not?
    if ((!(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x100))
        || (!(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Enabled_86 & 0x100))) {
        return EFI_UNSUPPORTED;
    }

    Status = IdeNonDataCommand(
        IdeBusInterface,
        SET_MAX_LOCK,           // Features
        0,              // Sector Count
        0,              // LBA Low
        0,              // LBA Mid
        0,              // LBA High
        IdeBusInterface->IdeDevice.Device << 4, // Device
        SET_MAX_ADDRESS );       // Command

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SetMaxUnLock
//
// Description:	Unlocks the device and allows it to accept all SET MAX commands
//
// Input:
//	IN      IDE_HPA_INTERFACE			*This,
//	IN	    UINT8						*PasswordBuffer
//
// Output:
//	EFI_STATUS  : EFI_UNSUPPORTED/EFI_SUCCESS/EFI_DEVICE_ERROR
//
// Modified:
//
// Referrals:
//
// Notes:	READ NATIVE MAX ADDRESS should not have immediatley PRECEED this command.
//			To take care of this situation, a Dummy Identify Device Command will be given before
//			issuing a SET MAX LOCK/UNLOCK command
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetMaxUnLock(
    IN IDE_HPA_INTERFACE *This,
    IN UINT8             *PasswordBuffer )
{
    EFI_STATUS       Status;
    IDE_BUS_PROTOCOL *IdeBusInterface = ((HPA_INTERFACE*)This)->IdeBusInterface;

    //Check for HPA feature set security extensions are implemented or not? AND
    //Check whether SET MAX PASSWORD command has been issued before or not?
    if ((!(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x100))
        || (!(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Enabled_86 & 0x100))) {
        return EFI_UNSUPPORTED;
    }

    Status = IssueSetMaxPasswordCmd( IdeBusInterface, PasswordBuffer, SET_MAX_UNLOCK );

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SetMaxFreezeLock
//
// Description:	Locks all SET MAX ADDRESS/PASSWORD/LOCK/UNLOCK command untill
//				next power cycle. GetNativeMaxAddress is allowed.
//
// Input:
//	IN      IDE_HPA_INTERFACE			*This,
//
// Output:
//	EFI_STATUS  : EFI_UNSUPPORTED/EFI_SUCCESS/EFI_DEVICE_ERROR
//
// Modified:
//
// Referrals:
//
// Notes:	READ NATIVE MAX ADDRESS should not have immediatley PRECEED this command.
//			To take care of this situation, a Dummy Identify Device Command will be given before
//			issuing a SET MAX FREEZELOCK command
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetMaxFreezeLock(
    IN IDE_HPA_INTERFACE *This )
{
    EFI_STATUS       Status;
    IDE_BUS_PROTOCOL *IdeBusInterface = ((HPA_INTERFACE*)This)->IdeBusInterface;

    //Check for HPA feature set security extensions are implemented or not? AND
    //Check whether SET MAX PASSWORD command has been issued before or not?
    if ((!(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x100))
        || (!(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Enabled_86 & 0x100))) {
        return EFI_UNSUPPORTED;
    }

    Status = IdeNonDataCommand(
        IdeBusInterface,
        SET_MAX_FREEZE_LOCK, // Features
        0,              // Sector Count
        0,              // LBA Low
        0,              // LBA Mid
        0,              // LBA High
        IdeBusInterface->IdeDevice.Device << 4, // Device
        SET_MAX_ADDRESS );       // Command

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	IssueSetMaxPasswordCmd
//
// Description:	Sets the Password to Lock/Unlock use of SETMAXADDRESS command
//
// Input:
//	IN      IDE_HPA_INTERFACE			*This,
//	IN	BOOLEAN						LockUnLock (TRUE : LOCK, FALSE :UNLOCK
//
// Output:
//	EFI_STATUS  : EFI_UNSUPPORTED/EFI_SUCCESS/EFI_DEVICE_ERROR
//
// Modified:
//
// Referrals:
//
// Notes:	READ NATIVE MAX ADDRESS should not have immediatley PRECEED this command.
//			To take care of this situation, a Dummy Identify Device Command will be given before
//			issuing a SET MAX LOCK/UNLOCK command
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS IssueSetMaxPasswordCmd(
    IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT8            *PasswordBuffer,
    UINT8            Cmd )
{
    EFI_STATUS Status;
    UINT8      *Buffer;

    //Issues Identify Device Command
    //Allocate 512 Bytes
    Status = pBS->AllocatePool( EfiBootServicesData,
                                512,
                                (VOID**)&Buffer );

    if ( EFI_ERROR( Status ))  {
        pBS->FreePool( Buffer );
        return Status;
    }

    Status = GetIdentifyData( IdeBusInterface, Buffer );

    //
    //Clear the Buffer
    //
    ZeroMemory( Buffer, 512 );

    //
    //Copy 32 bytes to Password starting from offset 2
    //
    pBS->CopyMem( &(Buffer[2]), PasswordBuffer, 32 );

    //	Issue SET MAX PASSWORD Command
    //	Update the Feature Register
    IdeWriteByte( IdeBusInterface->PciIO,
                  IdeBusInterface->IdeDevice.Regs.CommandBlock.FeatureReg,
                  Cmd );
    Status = AtaReadWritePio( IdeBusInterface, Buffer, 512, 0, SET_MAX_ADDRESS, TRUE );

    pBS->FreePool( Buffer );
    return Status;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
