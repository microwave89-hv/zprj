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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/OpSSDT.asl 4     7/16/13 5:23a Joshchou $
//
// $Revision: 4 $
//
// $Date: 7/16/13 5:23a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/OpSSDT.asl $
// 
// 4     7/16/13 5:23a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Remove _STA method in the scope of root port because
// it's not required.
// 
// 
// 2     2/21/13 5:37a Joshchou
// [TAG]  		EIP106524
// [Category]  	New Feature
// [Description]  	Support GC6 function for Optimus.
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
// 2     9/09/12 11:05p Joshchou
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
// 5     12/22/11 6:31a Alanlin
// Declared "defined(SGTPV_ASL_DEBUG) && (SGTPV_ASL_DEBUG ==1)"
// 
// 
// 3     12/02/11 12:40a Alanlin
// [TAG]  		EIP75359
// [Category]  	Improvement
// [Description]  	Report _STA asl method to PCIe root port for nVidia
// GPU.
// 
// 2     10/14/11 2:59a Alanlin
// [TAG]  		EIP64451
// [Category]  	New Feature
// [Description]  	Optimus GPS feature update 
// [Files]  		NvSSDT.asl
// NViGPU.asl
// OpSSDT.asl
// NvGPS.asl
// SgNvidia.cif
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
// 6     3/17/11 6:17p Alexp
// Optimus:Add code to preserve HD AudioCodec enable flag in CMOS
// 
// 5     11/12/10 1:26p Alexp
// rename ELCT to ELCL in order to avoid name conflict with Intel's ref
// code in SgDGPU.asl
// 
// 4     10/06/10 3:34p Alexp
// Include defines for different Nvidia GUID functions. Helps to control
// inclusion of peices of ASL depending on type of desired SG mode
// 
// 3     10/05/10 7:14p Alexp
// 1. Added debug macro to be able to insert check points in target ASL
// code
// 2. Reuse NVdGPU.asl file to build OpSSDT for Optimus and NvSSDT for
// MUXed SG targets.
//     NvOptimus.asl no longer required
// 
// 2     9/17/10 3:22p Alexp
// remove test comments
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
//**********************************************************************

DefinitionBlock (
        "NvOpt.aml",
        "SSDT",
        1,
        "OptRef",
        "OptTabl",
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

#include <NVdGPU.ASL>     // Include DGPU device namespace
#include <NViGPU.ASL>     // Include NVHG DSM calls
//#include <NViGDmisc.ASL>  // Include misc event callback methods

#if NV_VENTURA_SUPPORT == 1
#include <NvVentura.ASL>  // Include Ventura support
#endif
#if NV_GPS_SUPPORT == 1
#include <NvGPS.ASL>  // Include GPS support
#endif
#if NV_GC6_SUPPORT == 1
#include <NvGC6.ASL>  // Include GC6 support
#endif

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
