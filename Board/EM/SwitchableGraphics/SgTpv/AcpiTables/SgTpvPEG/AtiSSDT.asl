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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/AtiSSDT.asl 1     1/15/13 5:58a Joshchou $
//
// $Revision: 1 $
//
// $Date: 1/15/13 5:58a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/AtiSSDT.asl $
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
// 2     12/22/11 6:36a Alanlin
// Declared "defined(SGTPV_ASL_DEBUG) && (SGTPV_ASL_DEBUG ==1)"
// 
// 1     6/27/11 5:26a Alanlin
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
// 3     11/12/10 1:22p Alexp
// include "token.h" inside the command line to CL preprocessor in
// SgAcpiTable.mak
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
// 1     6/03/10 2:56p Alexp
// 
// 1     7/16/09 11:17a Alexp
// Added SG support for AMD ATI Gfx adaptors
// 
// 
//**********************************************************************

DefinitionBlock (
        "Amd.aml",
        "SSDT",
        1,
        "AmdRef",
        "AmdTabl",
        0x1000
        ){       

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

#include <ATdGPU.ASL>     // Include dGPU device namespace
#include <ATiGPU.ASL>     // Include IGD _DSM and AMD ATIF/ATPM/ATRM methods
#include <ATiGDmisc.ASL>  // Include misc event callback methods

} // end SSDT       

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
