//****************************************************************************
//****************************************************************************
//**                                                                        **
//**         (C)Copyright 1985-2012, American Megatrends, Inc.              **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
//****************************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/NViGDmisc.asl 1     1/15/13 5:59a Joshchou $
//
// $Revision: 1 $
//
// $Date: 1/15/13 5:59a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/NViGDmisc.asl $
// 
// 1     1/15/13 5:59a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create componet for SG support on PEG
// [Files]  		SgNvidia.cif
// NvSSDT.asl
// NVdGPU.asl
// NViGPU.asl
// NViGDmisc.asl
// OpSSDT.asl
// NvVentura.asl
// NvGPS.asl
// 
// 2     9/09/12 11:04p Joshchou
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Tpv module support for sharkbay.
// [Files]  		NvSSDT.asl
// NVdGPU.asl
// NViGPU.asl
// NViGDmisc.asl
// OpSSDT.asl
// NvVentura.asl
// NvGPS.asl
// 
// 1     6/27/11 5:27a Alanlin
// [TAG]  		EIP61848
// [Category]  	New Feature
// [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
// Reference code 0.6.0
// [Files]  		SgNvidia.cif
// NvSSDT.asl
// NVdGPU.asl
// NViGPU.asl
// NViGDmisc.asl
// OpSSDT.asl
// NvVentura.asl
// 
// 
// 4     11/12/10 1:27p Alexp
// Change IDAB method: invoke IGD_SCOPE.IDAB is it's defined 
// 
// 3     10/08/10 12:04p Alexp
// code clean up: removed unused externs
// 
// 2     10/05/10 7:14p Alexp
// 1. Added debug macro to be able to insert check points in target ASL
// code
// 2. Reuse NVdGPU.asl file to build OpSSDT for Optimus and NvSSDT for
// MUXed SG targets.
//     NvOptimus.asl no longer required
// 
// 1     9/17/10 1:21p Alexp
// [TAG]    	  EIP43103 
// [Category]  Function Request
// [Severity]	  Normal
// [Symptom]    Initial check-in of SgTPV module
// [RootCause] Request to implement SG reference code .
// [Solution]	Initial check-in. 
// [Files]	
//         SgNvidia.cif;
//         NvSSDT.asl; NVdGPU.asl;NViGPU.asl;NViGDmisc
//         OpSSDT.asl;NvOptimus.asl;NvVenture.asl
// 
// 1     6/08/10 3:45p Alexp
// 
// 1     6/03/10 2:54p Alexp
// 
// 6     10/05/09 5:35p Alexp
// updated asl code for Ati and Nvidia according to Calpella SG BWG 1.1
// 
// 5     8/20/09 7:08p Alexp
// upgraded Ati and Nvidia SSDT Asl files to match latest Acpi code drop
// #68
// 
// 4     8/10/09 4:21p Alexp
// changed with latest reference code from Intel MPG. not yet tested
// 
// 3     7/16/09 11:17a Alexp
// Added SG support for AMD ATI Gfx adaptors
// 
// 
//**********************************************************************

External(DSEN)
External(IGPU_SCOPE.CDCK)
External(DGPU_SCOPE.DD02)
External(IGPU_SCOPE.IDAB, MethodObj)

//Do not remove this function.
Method(IDAB, 0, Serialized)
{
    If (CondRefOf(IGPU_SCOPE.IDAB))
    {
        IGPU_SCOPE.IDAB()
    }
}

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    HGAS
//
// Description:  HG Adaptor select, notify
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END> 
Method(HGAS) //HG Adaptor select
{
    //Stateless button/Hotkey supporting 3 states - Power Saver, Adaptive and Perf
    
    Increment(IGPU_SCOPE.GPSS)
    Mod(IGPU_SCOPE.GPSS, 3, IGPU_SCOPE.GPSS)

    Store(1,IGPU_SCOPE.GPPO)
    Store(1,IGPU_SCOPE.SGNC)    //indicate 'policy select' change

    Notify(IGPU_SCOPE, 0xD0)
    Notify(PCI_SCOPE.WMI1, 0xD0)    // Mirror Notify on WMI1

}

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    HBRT
//
// Description:  Send backlight notifications to the DGPU LFP device
//              This is required for Win7 and is backward compatible with Vista
//
// Input:       Arg0 - 4 - Brightnes Down, 3- Up
//-------------------------------------------------------------------------
//<AMI_PHDR_END> 
Method(HBRT, 1 , Serialized)
{
    Store(Arg0,IGPU_SCOPE.DACE)
  
    If(And(4,DSEN))     //Note: DSEN variable is expected to be set by IGD miniport only.
    {
        If(LEqual(Arg0,4))
        {   
            Notify(DGPU_SCOPE.DD02,0x87)  //Note: DD02 is hardcoded as the LFP device in intelgfx.asl
        }
        If(LEqual(Arg0,3))
        {
            Notify(DGPU_SCOPE.DD02,0x86)
        }
    }       
    
}

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    HPFS
//
// Description:  Panel Fitting Hot Key
//
// Input:       None
//-------------------------------------------------------------------------
//<AMI_PHDR_END> 
Method(HPFS, 0, Serialized)     //Panel Fitting Hot Key
{
    //
    // HG Handling of Panel Fitting Switch
    //

    Store(5,IGPU_SCOPE.DACE)  // Indicate display scaling hot key event
    Store(2,IGPU_SCOPE.SGNC)  // Indicate platpolicy change

    //
    // Expansion Mode toggling
    //
    Increment(IGPU_SCOPE.GPSP)
    Mod(IGPU_SCOPE.GPSP, 4 , IGPU_SCOPE.GPSP)    

    Notify(IGPU_SCOPE,0xDC)

}


//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    HNOT
//
// Description:  Notification handler for Switchable graphics. Called from GNOT()
//
// Input:	Arg0 = Current event type:
//			1 = display switch
//			2 = lid
//			3 = dock (!!!!!Acpi ref code, Method(GDCK)sends 4 for Dock notifications )
//-------------------------------------------------------------------------
//<AMI_PHDR_END> 
Method (HNOT, 1, Serialized)
{
    Switch(ToInteger(Arg0))
    {
        case(1) //Display Switch event
        {            
            Store(3,IGPU_SCOPE.SGNC)    // indicate 'Displaystatus' change
            Store(1,IGPU_SCOPE.DACE)
            Notify(IGPU_SCOPE, 0x80)
            Notify(PCI_SCOPE.WMI1, 0x80)    // Mirror Notify on WMI1
        }

        case (2) //Lid switch event
        {
            //Note: NV clarified that only LDES needs to be set           
            Store(1,IGPU_SCOPE.LDES)            
            Notify(IGPU_SCOPE, 0xDB)
            Notify(PCI_SCOPE.WMI1, 0xDB)    // Mirror Notify on WMI1
        }
//        case (3) //Dock event
        case (4) //Dock event (!!!Acpi ref code, Method(GDCK)sends 4 for Dock notifications)
        {
            Store(IGPU_SCOPE.CDCK, IGPU_SCOPE.DKST) // Store the current dock state
            Notify(IGPU_SCOPE, 0x81)     
            Notify(PCI_SCOPE.WMI1, 0x81)    // Mirror Notify on WMI1
        }

        Default 
        {
            Notify(IGPU_SCOPE,0x80)
        }
        
    }

}

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    CHPS
//
// Description:  Shows current Hybrid Policy status on Port80 header
//         Adaptive -> 1, Save power -> 2 and High performance -> 3
//
// Input:	None
//-------------------------------------------------------------------------
//<AMI_PHDR_END> 
Method(CHPS)
{
    P8DB(0xEC, Add(IGPU_SCOPE.GPSS, 1), 2000)
}


//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    HDOS
//
// Description:  Check if the _DOS flag was set during the hot key handling
//
// Input:	None
//-------------------------------------------------------------------------
//<AMI_PHDR_END> 
Method(HDOS, 0, Serialized)
{
    If(LEqual(IGPU_SCOPE.DOSF,1))
    {                
        Store(1,IGPU_SCOPE.SGNC)    // indicate 'policy select' change
        Notify(IGPU_SCOPE,0xD0)
        Notify(PCI_SCOPE.WMI1, 0xD0)    // Mirror Notify on WMI1
        Store(0, IGPU_SCOPE.DOSF)   // Clear the DOSF
    }
}
//**********************************************************************
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************