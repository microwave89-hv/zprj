//****************************************************************************
//****************************************************************************
//**                                                                        **
//**         (C)Copyright 1985-2011, American Megatrends, Inc.              **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPCH/AtiSSDTPCH.asl 2     7/16/13 5:15a Joshchou $
//
// $Revision: 2 $
//
// $Date: 7/16/13 5:15a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPCH/AtiSSDTPCH.asl $
// 
// 2     7/16/13 5:15a Joshchou
// [TAG]  		None
// [Category]  	New Feature
// [Description]  	Add _DSW method to support MSHybrid.
// 
// 1     1/15/13 6:02a Joshchou
// [TAG]  		EIP107237
// [Category]  	Improvement
// [Description]  	Create componet for SG support on PCH
// [Files]  		SgUltAti.cif
// AtiSSDTPCH.asl
// ATdGPUPCH.asl
// ATiGPUPCH.asl
// ATiGDmiscPCH.asl
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
External(SG_ULT_RP_NUM, DeviceObj)
External(DGPUPCH_SCOPE, DeviceObj)
External(IGPU_SCOPE, DeviceObj)
External(DGPUPCH_SCOPE._ADR, DeviceObj)
External(DGPUPCH_SCOPE.SGST, MethodObj)
External(DGPUPCH_SCOPE.SGON, MethodObj)
External(DGPUPCH_SCOPE.SGOF, MethodObj)
External(DGPUPCH_SCOPE.SGPI, MethodObj)
External(DGPUPCH_SCOPE.SGPO, MethodObj)
External(\DSEL)
External(\ESEL)
External(\SSEL)
External(\PSEL)
External(\HLRS)
External(\PWEN)


#include <ATdGPUPCH.ASL>     // Include dGPU device namespace
#include <ATiGPUPCH.ASL>     // Include IGD _DSM and AMD ATIF/ATPM/ATRM methods
#include <ATiGDmiscPCH.ASL>  // Include misc event callback methods

Scope(SG_ULT_RP_NUM)
{
    Method(_DSW, 3, NotSerialized)
    {
         If(Arg1)
         {
             Store("RP05 -_DSW call ", Debug)
         }
         Else
         {
             If(LAnd(Arg0, Arg2))
             {
                  Store("RP05 -_DSW call-1 ", Debug)
             }
             Else
             {
                  Store("RP05 -_DSW call-2 ", Debug)
             }
          }
      }
}

} // end SSDT       
