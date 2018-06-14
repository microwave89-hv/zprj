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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMSSDT.asl 2     9/09/12 11:01p Joshchou $
//
// $Revision: 2 $
//
// $Date: 9/09/12 11:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMSSDT.asl $
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
// 2     12/22/11 6:38a Alanlin
// Declared "defined(SGTPV_ASL_DEBUG) && (SGTPV_ASL_DEBUG ==1)"
// 
// 1     12/12/11 9:10p Alanlin
// 
// 
//**********************************************************************

DefinitionBlock (
        "OEMACPI.aml",
        "SSDT",
        1,
        "OEMRef",
        "OEMTabl",
        0x1000
        ) {       

#define OPTIMUS_DSM_GUID 1
//#define NBCI_DSM_GUID 1

External(P8XH, MethodObj) 
#if defined(SGTPV_ASL_DEBUG) && (SGTPV_ASL_DEBUG ==1)
#define P8DB(arg0, arg1, arg2) P8XH (0, arg1) P8XH (1, arg0) sleep(arg2)
#else
#define P8DB(arg0, arg1, arg2)
#endif


External(PCI_SCOPE, DeviceObj)
External(PEG_SCOPE, DeviceObj)
External(DGPU_SCOPE, DeviceObj)
External(IGPU_SCOPE, DeviceObj)
External(DGPU_SCOPE._ADR, DeviceObj)
External(IGPU_SCOPE._DSM, MethodObj)
External(DGPU_SCOPE.SGST, MethodObj)
External(DGPU_SCOPE.SGON, MethodObj)
External(DGPU_SCOPE.SGOF, MethodObj)
External(DGPU_SCOPE.SGPI, MethodObj)
External(DGPU_SCOPE.SGPO, MethodObj)
External(\DSEL)
External(\ESEL)
External(\SSEL)
External(\PSEL)
External(\HLRS)
External(\PWEN)
External(\PWOK)
External(\SGMD)
External(\SGFL)
External(\SSMP)

#include <OEMNVdGPU.ASL>     // Include DGPU device namespace
#include <OEMNViGPU.ASL>     // Include NVHG DSM calls
//#include <NViGDmisc.ASL>  // Include misc event callback methods
#include <OEMNvGPS.ASL>  // Include GPS support


Scope(PEG_SCOPE) 
{
	Method(_STA,0,Serialized)
	{
			Return(0x000F)
        }
}

 Scope(PCI_SCOPE) 
 {
//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    WMI1
//
// Description:  WMI MXM Mapper. ASL Device is used to acccess Nv Optimus native method via WMI API
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END> 
    Device(WMI1) // placed within PCI Bus scope parallel to iGPU 
    { 
        Name(_HID, "PNP0C14")
        Name(_UID, "OPT1")    
   
        Name(_WDG, Buffer() 
        {
            // Methods GUID {F6CB5C3C-9CAE-4ebd-B577-931EA32A2CC0}
            0x3C, 0x5C, 0xCB, 0xF6, 0xAE, 0x9C, 0xbd, 0x4e, 0xB5, 0x77, 0x93, 0x1E,
            0xA3, 0x2A, 0x2C, 0xC0,
            0x4D, 0x58, // Object ID "MX" = method "WMMX"
            1,          // Instance Count
            0x02,       // Flags (WMIACPI_REGFLAG_METHOD)        
        }) // End of _WDG

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    WMMX
//
// Description:  WMI Method execution tunnel. MXM Native methods are called via WMMX index.
//
// Input:
//          Arg1:   Integer     GPU index. 0x10-iGPU, 0x100+PCIe Bus number for the GPU
//
//  Output:
//          Buffer      specific to the funcion being called
//-------------------------------------------------------------------------
//<AMI_PHDR_END> 
        Method(WMMX, 3)
        {

            //Arg1 = 0x10 indicates iGPU, 0x100+PCIe Bus number for the GPU
            // 
            CreateDwordField(Arg2, 0, FUNC)                 // Get the function name

            If (LEqual(FUNC, 0x534F525F))                   // "_ROM"
            {
                If (LGreaterEqual(SizeOf(Arg2), 8))
                {
                    CreateDwordField(Arg2, 4, ARGS)
                    CreateDwordField(Arg2, 8, XARG)
                    Return(DGPU_SCOPE._ROM(ARGS, XARG))
                }
            }            

            If (LEqual(FUNC, 0x4D53445F))                   // "_DSM"
            {
                If (LGreaterEqual(SizeOf(Arg2), 28))
                {
                    CreateField(Arg2, 0, 128, MUID)
                    CreateDwordField(Arg2, 16, REVI)
                    CreateDwordField(Arg2, 20, SFNC)
                    CreateField(Arg2, 0xe0, 0x20, XRG0)
                    
//                    If(LNotEqual(Arg1,0x10))          
//                    {
                    If (CondRefOf(IGPU_SCOPE._DSM)) // common with dGPU DSM functions
                    {
                        Return(IGPU_SCOPE._DSM(MUID, REVI, SFNC, XRG0))
                    }
//                    }
                }
            }            
            Return(0)
        } // End of WMMX
   } // End of WMI1 Device
 } // end scope PCI0
} // end SSDT   
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
