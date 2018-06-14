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
// $Header: /Alaska/SOURCE/Core/Modules/IdeBus/IdePowerManagement.c 11    10/11/10 11:32a Krishnakumarg $
//
// $Revision: 11 $
//
// $Date: 10/11/10 11:32a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/IdeBus/IdePowerManagement.c $
// 
// 11    10/11/10 11:32a Krishnakumarg
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
// 10    8/25/10 4:10a Rameshr
// New Feature: EIP 37748
// Description: Move all the IDEBus Source driver SDL token into IdeBus
// Bin Driver.
// FilesModified: Ata.c, Atapi.c, idebus.c, IdeBus.h,
// IdebuscomponentName.c, IdeBusmaster.c IdeBusSrc.mak IdebusSrc.sdl
// IdeHpa.c, IdePowerManagement.c
// 
// 9     8/31/09 10:40a Felixp
// IDLE_CMD is used instead of STANDBY_CMD if standby time is zero to
// avoid HDD spin up and down-EIP 22135
// 

// 
// 6     7/01/09 12:23p Rameshr
// Coding Standard and File header updated.
// 
// 5     13/04/07 3:05p Anandakrishnanl
// Ide Bus Module - Update source files to comply with AMI coding
// standard"!!!
// 
// 4     1/09/06 11:36a Felixp
// 
// 2     12/14/05 3:10p Srinin
// 
// 1     12/01/05 9:43a Felixp
// 
// 4     3/04/05 11:35a Mandal
// 
// 3     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     1/11/05 2:26p Srinin
// IDE Power Management Support added.
// 
// 
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name: IDEPOWERMANAGEMENT.c
//
// Description:	IDE Power Management Support
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "IdeBus.h"
#include <Protocol\IdeBusBoard.h>

//
//External variables
//
extern PLATFORM_IDE_PROTOCOL    *gPlatformIdeProtocol;
extern EFI_GUID                 gPowerMgmtProtocolGuid;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitIDEPowerManagement
//
// Description:	Initializes IDE power Management
//
// Input:
//	IDE_BUS_PROTOCOL			*IdeBusInterface;
//
// Output:
//	EFI_STATUS
//
// Modified:
//      
// Referrals: ConfigureIdeDevice
//
// Notes:	
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitIDEPowerManagement (
	IN IDE_BUS_PROTOCOL			    *IdeBusInterface
 )
{

	UINT8							bData = 0;
	EFI_STATUS						Status = EFI_SUCCESS;

    //
    //Check if POWER Managmentfeature is enabled
    //
	if	(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Enabled_85 & 0x8) {

    //
    //Enable/Disable STANDBY Timer
    //
		    bData = ConvertStanbyTimeoutValue ((UINT8)gPlatformIdeProtocol->StandbyTimeout);
            if ( (gPlatformIdeProtocol->StandbyTimeout) == 0 ) {
		        Status = IdeNonDataCommand (
					     IdeBusInterface,
    					 0,				// Features
				    	 bData,			// Sector Count
    					 0, 			// LBA Low
				    	 0,				// LBA Mid
					     0,				// LBA High
    					 IdeBusInterface->IdeDevice.Device << 4,	// Device
                         IDLE_CMD);     // IDLE_CMD when StandbyTimeout = 0
            } else {
    		    Status = IdeNonDataCommand (
				    	 IdeBusInterface,
					     0,				// Features
    					 bData,			// Sector Count
				    	 0,				// LBA Low
    					 0,				// LBA Mid
				         0,				// LBA High
				  	     IdeBusInterface->IdeDevice.Device << 4,	// Device
                         STANDBY_CMD);	// STANDBY_CMD when StandbyTimeout > 0
           }
            //
            //Enable/Disable STANDBY Timer
            //

	}

    //
    //Check Advanced Power Management Mode
    //
    if ( gPlatformIdeProtocol->AdvPowerManagementSupport ) {
    	if	(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x8){
            //
            //Enable/Disable Advanced Power Management
            //
	    	bData = ( gPlatformIdeProtocol->AdvPowerManagementLevel ) == 0 ? DISABLE_ADV_POWER_MANAGEMENT : ADV_POWER_MANAGEMENT;
	    	IdeSetFeatureCommand (IdeBusInterface, bData, gPlatformIdeProtocol->AdvPowerManagementLevel );
	    }
    }


    if ( gPlatformIdeProtocol->PowerupInStandbySupport ) {
        //
        //Check Power-up in Standby Mode Support
        //    
    	if	(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x20){
            //
            //Check if the desires state is already present or not
            //
    		if	(!((IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Enabled_86 & 0x20)  == (gPlatformIdeProtocol->PowerupInStandbyMode))){
    			bData = ( gPlatformIdeProtocol->PowerupInStandbyMode ) == 0 ? DISABLE_POWERUP_IN_STANDBY : ENABLE_POWERUP_IN_STANDBY;			
    			IdeSetFeatureCommand (IdeBusInterface, bData, 0);
    		}
    	}
    }

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InstallIDEPowerMgmtInterface
//
// Description:	Install  IDE power Management Interface
//
// Input:
//	IDE_BUS_PROTOCOL			*IdeBusInterface;
//
// Output:
//	EFI_STATUS
//
// Modified:
//      
// Referrals: IdeBusStart
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InstallIDEPowerMgmtInterface (
	IN IDE_BUS_PROTOCOL			    *IdeBusInterface
 )
{

	EFI_STATUS 		                Status = EFI_UNSUPPORTED;
	POWER_MGMT_INTERFACE	        *PowerMgmtInterface;


    //
    //Check if Power Management is Supported or not	
    //
	if	(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Enabled_85 & 0x8){
		Status = pBS->AllocatePool (EfiBootServicesData,
					sizeof (POWER_MGMT_INTERFACE),
			  	    (VOID**)&PowerMgmtInterface);
		if (EFI_ERROR(Status)) return Status;

		PowerMgmtInterface->CheckPowerMode          = CheckPowerMode;				
		PowerMgmtInterface->IdleMode                = IdleMode;				
		PowerMgmtInterface->StandbyMode             = StandbyMode;				
		PowerMgmtInterface->AdvancePowerMgmtMode    = AdvancePowerMgmtMode;				
		PowerMgmtInterface->IdeBusInterface         = IdeBusInterface;				
		IdeBusInterface->PowerMgmtInterface         = PowerMgmtInterface;				

        //
        //Install the protocol on the device
        //
		Status = pBS->InstallMultipleProtocolInterfaces (
					&(IdeBusInterface->IdeDeviceHandle),
					&gPowerMgmtProtocolGuid, IdeBusInterface->PowerMgmtInterface,
					NULL);

		if (EFI_ERROR(Status)) pBS->FreePool(PowerMgmtInterface);
	}

	return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	StopIDEPowerMgmtInterface
//
// Description:	Uninstall  IDE power Management Interface
//
// Input:
//	IDE_BUS_PROTOCOL			*IdeBusInterface;
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
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
StopIDEPowerMgmtInterface (
	IN IDE_BUS_PROTOCOL			    *IdeBusInterface
 )
{

	EFI_STATUS 			            Status;
	POWER_MGMT_INTERFACE            *PowerMgmtInterface = IdeBusInterface->PowerMgmtInterface;

	if (IdeBusInterface->PowerMgmtInterface == NULL) return EFI_SUCCESS;
	Status = pBS->UninstallMultipleProtocolInterfaces (
					IdeBusInterface->IdeDeviceHandle,
					&gPowerMgmtProtocolGuid, IdeBusInterface->PowerMgmtInterface,
					NULL);
	if (Status == EFI_SUCCESS) {
		pBS->FreePool(IdeBusInterface->PowerMgmtInterface);
		IdeBusInterface->PowerMgmtInterface = NULL;
	}

	return Status;
}
 //IDE_POWER_MANAGEMENT_INTERFACE_SUPPORT ends

//<AMI_PHDR_START>
//---------------------------------------------------------------------------//
// Procedure:	ConvertStanbyTimeoutValue
//
// Description:	Initializes IDE power Managment
//
// Input:
//	IN UINT8		StandbyTimeout (In Minutes)
//
// Output:
//	UINT8		StandbyTimeout  (Converted Timeout period)
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
ConvertStanbyTimeoutValue (
	IN UINT8	                    StandbyTimeout
 )
{

	if ( StandbyTimeout ) {
		if ( StandbyTimeout < 30 ) {
			if ( StandbyTimeout > 20 ) { 
				StandbyTimeout = 20;	
			}
			return StandbyTimeout * 60 / 5;
		}
		if ( StandbyTimeout < 16 * 30 ) {
			return StandbyTimeout / 30;			
		}
	}
	return 0;							// Standby Timer Disabled

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	CheckPowerMode
//
// Description:	Returns the Current State of the device
//
// Input:
//	
//
// Output:
//	EFI_STATUS, Current state of the Device, 
//
// Modified:
//      
// Referrals: 
//
// Notes:	PowerMode : 00 Standby Mode, 80h : Idle Mode, FF : Active/Idle Mode
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CheckPowerMode (
	IN IDE_POWER_MGMT_INTERFACE		*IdePowerMgmtInterface,
	IN OUT UINT8					*PowerMode
 )
{
	EFI_STATUS					    Status;
	IDE_BUS_PROTOCOL			    *IdeBusInterface = ((POWER_MGMT_INTERFACE *)IdePowerMgmtInterface)->IdeBusInterface;

	Status = IdeNonDataCommand (
				IdeBusInterface,
				0,				// Features
				0,				// SectorCount
				0,				// LBA Low
				0,				// LBA Mid
				0,				// LBA High
				IdeBusInterface->IdeDevice.Device << 4,	// Device
				CHECK_POWER_MODE);		// Command

	if (Status == EFI_SUCCESS) {		
		IdeReadByte ( IdeBusInterface->PciIO,  
					  IdeBusInterface->IdeDevice.Regs.CommandBlock.SectorCountReg,
					  PowerMode);
    }		

	return Status;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	IdleMode
//
// Description:	Puts the device in Idle Mode
//
// Input:	StandbyTimeout : Value in Minutes. (0 : Disabled)
//	
// Output:
//	EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
IdleMode(
	IN IDE_POWER_MGMT_INTERFACE		*IdePowerMgmtInterface,
	IN UINT8						StandbyTimeout
 )
{
	EFI_STATUS					    Status;
	IDE_BUS_PROTOCOL			    *IdeBusInterface = ((POWER_MGMT_INTERFACE *)IdePowerMgmtInterface)->IdeBusInterface;
	UINT8						    bData;

	bData = ConvertStanbyTimeoutValue (StandbyTimeout);
	Status = IdeNonDataCommand (
				IdeBusInterface,
				0,				// Features
				bData,			// SectorCount
				0,				// LBA Low
				0,				// LBA Mid
				0,				// LBA High
				IdeBusInterface->IdeDevice.Device << 4,	// Device
				IDLE_CMD);		// Command

	return Status;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	StandbyMode
//
// Description:	Puts the device in StandbyMode
//
// Input:	StandbyTimeout : Value in Minutes. (0 : Disabled)
//	
// Output:
//	EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
StandbyMode(
	IN IDE_POWER_MGMT_INTERFACE		*IdePowerMgmtInterface,
	IN UINT8						StandbyTimeout
 )
{
	EFI_STATUS					    Status;
	IDE_BUS_PROTOCOL			    *IdeBusInterface = ((POWER_MGMT_INTERFACE *)IdePowerMgmtInterface)->IdeBusInterface;
	UINT8						    bData;

	bData = ConvertStanbyTimeoutValue (StandbyTimeout);
	Status = IdeNonDataCommand (
				IdeBusInterface,
				0,				// Features
				bData,			// SectorCount
				0,				// LBA Low
				0,				// LBA Mid
				0,				// LBA High
				IdeBusInterface->IdeDevice.Device << 4,	// Device
				STANDBY_CMD);		// Command

	return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	AdvancePowerMgmtMode
//
// Description:	Enables Adavance Power Management
//
// Input:	AdvPowerMgmtLevel ( 0 : Disable, FEh : Max. Performance, 81h - FDh Intermediate performance without Standby
//								80h : Min. Power Consumption without Standby, 02h - 7Fh Intermediate Performance with Standby
//								01h : Min. Power Consumption with Standby)
//	
// Output:
//	EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
AdvancePowerMgmtMode(
	IN IDE_POWER_MGMT_INTERFACE		*IdePowerMgmtInterface,
	IN UINT8						AdvPowerMgmtLevel
 )
{
	EFI_STATUS					    Status = EFI_UNSUPPORTED;
	IDE_BUS_PROTOCOL                *IdeBusInterface = ((POWER_MGMT_INTERFACE *)IdePowerMgmtInterface)->IdeBusInterface;
	UINT8						    bData;

	if	(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x8){
        //    
        //Enable/Disable Advanced Power Management
        //
		bData = AdvPowerMgmtLevel == 0 ? DISABLE_ADV_POWER_MANAGEMENT : ADV_POWER_MANAGEMENT;
		Status = IdeSetFeatureCommand (IdeBusInterface, bData, AdvPowerMgmtLevel);
	}

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
//**********************************************************************
