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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMNViGDmisc.asl 2     9/09/12 11:01p Joshchou $
//
// $Revision: 2 $
//
// $Date: 9/09/12 11:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMNViGDmisc.asl $
// 
// 2     9/09/12 11:01p Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Tpv module support for sharkbay.
// [Files]  		OEMSSDT.mak
// OEMSSDT.asl
// OEMNVdGPU.asl
// OEMNViGPU.asl
// OEMNViGDmisc.asl
// OEMNvVentura.asl
// OEMNvGPS.asl
// OEMSSDT.cif
// 
// 1     12/12/11 9:10p Alanlin
// 
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