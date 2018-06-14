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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/ATdGPU.asl 1     1/15/13 5:58a Joshchou $
//
// $Revision: 1 $
//
// $Date: 1/15/13 5:58a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/ATdGPU.asl $
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
// 10    4/29/10 11:42a Alexp
// updated ASL names for Mxm power control and switching from GPIO to
// functional names. E.g. old- PO16 to new-MRST etc.
// 
// 9     4/02/10 5:06p Alexp
// Change per Calpella SG BIOS spec 1.03:
// - add link control register
// - add WiDi display
// 
// 8     1/11/10 4:03p Alexp
// Added Nvidia Optimus Gfx support
// 
// 7     12/08/09 10:20a Alexp
// Per BWG 1.2 Added code to save/restore Endpoint Link Contol Register
// during power cycle of DGPU
// 
// 6     10/06/09 1:27p Alexp
// replaced Alias definitions with actual device name scopes for PEG
// display devices
// 
// 5     10/05/09 5:35p Alexp
// updated asl code for Ati and Nvidia according to Calpella SG BWG 1.1
// 
// 4     8/21/09 4:45p Alexp
// Updated Nvidia and ATI SG code to match latest Intel Calpella Acpi
// reference code from Intel code drop v#68 and Ati SG BWG
// SG Asl code. Made PEG PCIe MMIO base address dependent on
// PCIE_BASE_ADDRESS SDL token. Before it was hardwired in ASL code which
// caused SG logic to fail in Mxm & SG Label 005
// 
// 3     8/20/09 7:08p Alexp
// upgraded Ati and Nvidia SSDT Asl files to match latest Acpi code drop
// #68
// 
// 1     7/16/09 11:17a Alexp
// Added SG support for AMD ATI Gfx adaptors
//**********************************************************************
Scope(DGPU_SCOPE)
{   
//    OperationRegion (PEGR, PCI_Config, 0, 0x100)
//    Field(PEGR, DWordAcc, Lock, Preserve)
//    {
//        Offset(0x4C),
//        SSID, 32,
//    }        

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    _ON
//
// Description:  dGPU power ON control method
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>    
    Method(_ON,0,Serialized)
    {
        SGON()  // OEM Mxm Power On

        //Set the SSID for the ATI MXM
//        Store(MXM_SSVID_DID, SSID)

        //Ask OS to do a PnP rescan
        Notify(PEG_SCOPE,0)                      
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    _OFF
//
// Description:  dGPU power OFF control method
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>    
    Method(_OFF,0,Serialized)
    {
        SGOF()  // OEM Mxm Power On

        //Ask OS to do a PnP rescan
        Notify(PEG_SCOPE,0)
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    _STA
//
// Description:  Returns curent dGPU power/presence state
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>    
    Method(_STA,0,Serialized)
    {
        Return(SGST())  // OEM Mxm Power status 
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    _INI
//
// Description:  dGPU Init control method. Used to force dGPU _ADR to return proper PCI address
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>    
//    Method (_INI)
//    {       
// should already be set by now...
////        Store(MXM_SSVID_DID, SSID) //Set the SSID for the ATI MXM
//        Store(0x0, DGPU_SCOPE._ADR) //make sure PEGP address returns 0x00000000
//    }

} // end Scope(DGPU_SCOPE)

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