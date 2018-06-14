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
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/ATiGDmisc.asl 1     1/15/13 5:58a Joshchou $
//
// $Revision: 1 $
//
// $Date: 1/15/13 5:58a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/ATiGDmisc.asl $
// 
// 1     1/15/13 5:58a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create componet for SG support on PEG
// [Files]  		SgAti.cif
// AtiSSDT.asl
// ATdGPU.asl
// ATiGPU.asl
// ATiGDmisc.asl
// 
// 2     9/09/12 11:02p Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Tpv module support for sharkbay.
// [Files]  		AtiSSDT.asl
// ATdGPU.asl
// ATiGPU.asl
// ATiGDmisc.asl
// SgAti.cif
// 
// 1     6/27/11 5:27a Alanlin
// [TAG]  		EIP61848
// [Category]  	New Feature
// [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
// Reference code 0.6.0
// [Files]  		SgAti.cif
// AtiSSDT.asl
// ATdGPU.asl
// ATiGPU.asl
// ATiGDmisc.asl
// 
// 
// 4     3/17/11 6:18p Alexp
// cleaned up the code.
// 
// 3     11/12/10 1:25p Alexp
// Change IDAB method: invoke IGD_SCOPE.IDAB is defined there
// 
// 2     10/05/10 7:09p Alexp
// Added debug macro to be able to insert include check points in target
// ASL code
// 
// 1     9/17/10 1:20p Alexp
// [TAG]    	  EIP43103 
// [Category]  Function Request
// [Severity]	  Normal
// [Symptom]    Initial check-in of SgTPV module
// [RootCause] Request to implement SG reference code .
// [Solution]	Initial check-in. 
// [Files]	
//         SgAti.cif;
//         AtiSSDT.asl; ATdGPU.asl;ATiGPU.asl;ATiGDmisc
// 
// 1     6/08/10 3:45p Alexp
// 
// 1     6/03/10 2:54p Alexp
// 
// 4     10/05/09 5:35p Alexp
// updated asl code for Ati and Nvidia according to Calpella SG BWG 1.1
// 
// 3     8/20/09 7:08p Alexp
// upgraded Ati and Nvidia SSDT Asl files to match latest Acpi code drop
// #68
// 
// 1     7/16/09 11:17a Alexp
// Added SG support for AMD ATI Gfx adaptors
//**********************************************************************

External(DSEN)
External(IGPU_SCOPE.AINT, MethodObj)
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
Method(HGAS)        // HG Adaptor Select
{
    // Toggle GFX Adapter.
    Store(1,IGPU_SCOPE.PXGS)
    Notify(IGPU_SCOPE,0x81)
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
    If(LNotEqual(IGPU_SCOPE.GSTP,1))
    {

        //
        // HG Handling of Panel Fitting Switch
        //
        If(LEqual(IGPU_SCOPE.AGXA,0))
        {
            IGPU_SCOPE.AINT(2, 0)
        }
        Else
        {
            Store(1,IGPU_SCOPE.EMDR)

            //
            // Expansion Mode toggling
            //
            If(LEqual(IGPU_SCOPE.EXPM,2))
            {
                Store(0,IGPU_SCOPE.EXPM)
            }
            Else
            {
                Increment(IGPU_SCOPE.EXPM)
            }
            Notify(IGPU_SCOPE,0x81)
        }
    }
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
//			3 = dock (!!!!!Calpella ref code, Method(GDCK)sends 4 for Dock notifications )
//-------------------------------------------------------------------------
//<AMI_PHDR_END> 
Method (HNOT, 1, Serialized)
{
    
    Switch(ToInteger(Arg0))
    {
        case(1) //Display Switch event
        {
            If(LNotEqual(IGPU_SCOPE.GSTP,1))
            {
                //
                // HG Handling of Display Switch Event
                //
                // Muxless?                              
                If(LEqual(SGMD,0x2))
                {
                     If(LEqual(IGPU_SCOPE.AGXA,0))
                     {
                      Notify(IGPU_SCOPE,0x80)
                     }

                     If(LEqual(IGPU_SCOPE.AGXA,1))
                     {
                      Notify(DGPU_SCOPE,0x80)
                     }
                }
                Else
                {   
                    Store(1,IGPU_SCOPE.DSWR)
                    Notify(IGPU_SCOPE,0x81)
                }                
            }
        }
        case (2) //Lid switch event
        {
            // Muxless?                              
            If(LEqual(SGMD,0x2))
            {
                 If(LEqual(IGPU_SCOPE.AGXA,0))
                 {
                  Notify(IGPU_SCOPE,0x80)
                 }

                 If(LEqual(IGPU_SCOPE.AGXA,1))
                 {
                  Notify(DGPU_SCOPE,0x80)
                 }
            }
            Else
            {
                Notify(IGPU_SCOPE,0x80)         //Placeholder for LID event
            }
        }
//        case (3) //Dock event
        case (4) //Dock event
        {
            // Muxless?                              
            If(LEqual(SGMD,0x2))
            {
                 If(LEqual(IGPU_SCOPE.AGXA,0))
                 {
                  Notify(IGPU_SCOPE,0x80)
                 }

                 If(LEqual(IGPU_SCOPE.AGXA,1))
                 {
                  Notify(DGPU_SCOPE,0x80)
                 }
            }
            Else
            {
             Notify(IGPU_SCOPE,0x80)     //Placeholder for handling dock event
            }
        }
        Default 
        {
            Notify(IGPU_SCOPE,0x80)
        }
        
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