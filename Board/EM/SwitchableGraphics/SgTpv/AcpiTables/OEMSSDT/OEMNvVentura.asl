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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMNvVentura.asl 2     9/09/12 11:01p Joshchou $
//
// $Revision: 2 $
//
// $Date: 9/09/12 11:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMNvVentura.asl $
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
//**********************************************************************
// (Ventura+)>
EXTERNAL(\_PR.CPU0, DeviceObj)
EXTERNAL(\_PR.CPU1, DeviceObj)
EXTERNAL(\_PR.CPU2, DeviceObj)
EXTERNAL(\_PR.CPU3, DeviceObj)
//> Andy+ for ClarksField -- 8 processors
EXTERNAL(\_PR.CPU4, DeviceObj)
EXTERNAL(\_PR.CPU5, DeviceObj)
EXTERNAL(\_PR.CPU6, DeviceObj)
EXTERNAL(\_PR.CPU7, DeviceObj)
//<
External(\_PR.CPU0._PSS, BuffObj)
External(\_PR.CPU0._TSS, BuffObj)

External(\_PR.CPU0._PPC, IntObj)
External(\_PR.CPU1._PPC, IntObj)
External(\_PR.CPU2._PPC, IntObj)
External(\_PR.CPU3._PPC, IntObj)
//> Andy+ for ClarksField -- 8 processors
External(\_PR.CPU4._PPC, IntObj)
External(\_PR.CPU5._PPC, IntObj)
External(\_PR.CPU6._PPC, IntObj)
External(\_PR.CPU7._PPC, IntObj)
//<
External(\_PR.CPU0._TPC, IntObj)
External(\_PR.CPU1._TPC, IntObj)
External(\_PR.CPU2._TPC, IntObj)
External(\_PR.CPU3._TPC, IntObj)
//> Andy+ for ClarksField -- 8 processors
External(\_PR.CPU4._TPC, IntObj)
External(\_PR.CPU5._TPC, IntObj)
External(\_PR.CPU6._TPC, IntObj)
External(\_PR.CPU7._TPC, IntObj)
//<
Scope(PCI_SCOPE){

        Name(VEN, "VENACPI 2009-Nov-23 14:56:05")       // MCPACPIP build time stamp.

} // end of Scope

Scope (DGPU_SCOPE)
{
        // value used to notify iGPU
        
        Name(VSTS, 1)           // Ventura Status
        Name(THBG, 50000)       // Thermal Budget
        Name(PSCP, 0)           // P-State capacity, mainly for s/w debugging
        Name(TBUD, 0x88B8)       // Thermal Budget
//        Name(PBCM, 0)

        // Called by EC to notify thermal budget/status change
        // Arg0 is one of SPB_EC_ values
        // Arg1 is an object reference
        Method (THCH, 2, NotSerialized)
        {
            Switch (ToInteger(Arg0))
            {
                case ( 0x03)
                {
                    // VSTS needs to be updated before notification 
                    Store(DeRefOf(Arg1), VSTS)
                    Notify(DGPU_SCOPE, 0xC0)
                }
                case ( 0x01)
                {
                    // THBG needs to be updated before notification 
                    Store(DeRefOf(Arg1), THBG)
                    Notify(DGPU_SCOPE, 0xC1)
                }
            }
        }

	// Wrapper to call Method(SPB)
        Method (SPB2, 2, NotSerialized)
        {
            Store( Buffer() {0x00, 0x00, 0x00, 0x00}, Local0 )
            CreateDwordField(Local0, 0, LLLL)
            Store( Arg1, LLLL )
            Return( SPB(0x00, 0x101, Arg0, Local0) )
        }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    SPB
//
// Description:  Called from _DSM -Device Specific Method for dGPU device.
//               Implement Ventura specific callback functions
//
// Input:
// Arg0:   UUID      Unique function identifier. 
//               Ventura DSM_GUID 95DB88FD-940A-4253-A446-70CE0504AEDF
// Arg1:   Integer   Revision Level
// Arg2:   Integer   Function Index (0 = Return Supported Functions)
// Arg3:   Package   Parameters
//
// Output:
//  Sub-function 0 and unsupported function calls always returns a buffer. 
//  Other subfunctions may return a buffer or a package as defined in the function.
//  When a single DWord is returned the following values have special meaning,
//  controlled by reserved Bit31 as follows:
//      MXM_ERROR_SUCCESS 0x00000000 Success
//      MXM_ERROR_UNSPECIFIED 0x80000001 Generic unspecified error code
//      MXM_ERROR_UNSUPPORTED 0x80000002 FunctionCode or SubFunctionCode not
//          supported by this system
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method (SPB, 4, NotSerialized)
    {

        Store("------- SPB DSM --------", Debug)
        // Only Interface Revision 0x0101 is supported
        If (LNotEqual(Arg1, 0x101))
        {
                Return(0x80000002)
        }

        // (Arg2) Sub-Function
        Switch (ToInteger(Arg2))
        {
            case (0x00)
            {
                Name(FMSK, Buffer(0x8)
                {
    				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
                })
                Store(Buffer(0x8)
                {
    				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                }, Local0)
                Divide(Zero, 0x8, Local2, Local1)
		// Local1 is Quotient, Local2 is Remainder
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))
                
                Divide(0x20, 8, Local2, Local1)
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))
                
                Divide(0x21, 8, Local2, Local1)
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))
                
                Divide(0x22, 8, Local2, Local1)
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))
                
                Divide(0x23, 8, Local2, Local1)
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))
                
                Divide(0x24, 8, Local2, Local1)
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))

                Divide(0x2A, 8, Local2, Local1)
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))

                // mask out specific functions
                Store( SizeOf(Local0), Local1)
                While( LNotEqual(Local1, 0) ) {
                    Decrement(Local1)
                    Store( DeRefOf(Index(FMSK, Local1)), Local2)
                    And( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1) )
                }

                Return(Local0)
            }

        //   Unit is mWAT 
	        case(0x20)
    		{
                Store(TBUD, Local1)
		//failsafe to clear ventura status bit
    			And(Local1, 0xFFFFF, Local1)
				// Just return SPB status for now (bit[0]=1 SPB enabled)
//       		    		If(CondRefOf(PBCM,Local0)){ 	// Make sure this object is present.
//       					If(PBCM){
//                                                // Software/EC have another chance to disable ventura through VSTS
//                                                If(LNotEqual(VSTS, 0)) {
//							Or( Local1, 0x40000000, Local1 )
//                                                }
//       					}
//       				}
                Return(Local1)
    		}

	        case(0x21)
    		{
		        Return(\_PR.CPU0._PSS)
    		}

	        case(0x22)
    		{
                CreateByteField(Arg3, 0, PCAP)
                
                Store(PCAP, PSCP)
               // \_PR.CPU0._PPC(PCAP)
                Store(PCAP, \_PR.CPU0._PPC)
                Notify(\_PR.CPU0, 0x80)

                If(CondRefOf(\_PR.CPU1._PPC, Local0)) {
                      //  \_PR.CPU1._PPC(PCAP)
                        Store(PCAP, \_PR.CPU0._PPC)
                        Notify(\_PR.CPU1, 0x80)
                }

                If(CondRefOf(\_PR.CPU2._PPC, Local0)) {
                      //  \_PR.CPU2._PPC(PCAP)
                        Store(PCAP, \_PR.CPU0._PPC)
                        Notify(\_PR.CPU2, 0x80)
                }

                If(CondRefOf(\_PR.CPU3._PPC, Local0)) {
                     //   \_PR.CPU3._PPC(PCAP)
                        Store(PCAP, \_PR.CPU0._PPC)
                        Notify(\_PR.CPU3, 0x80)
                }

//> Andy+ for ClarksField -- 8 processors
                If(CondRefOf(\_PR.CPU4._PPC, Local0)) {
                     //   \_PR.CPU4._PPC(PCAP)
                        Store(PCAP, \_PR.CPU0._PPC)
                        Notify(\_PR.CPU4, 0x80)
                }

                If(CondRefOf(\_PR.CPU5._PPC, Local0)) {
                     //   \_PR.CPU5._PPC(PCAP)
                        Store(PCAP, \_PR.CPU0._PPC)
                        Notify(\_PR.CPU5, 0x80)
                }

                If(CondRefOf(\_PR.CPU6._PPC, Local0)) {
                     //   \_PR.CPU6._PPC(PCAP)
                        Store(PCAP, \_PR.CPU0._PPC)
                        Notify(\_PR.CPU6, 0x80)
                }

                If(CondRefOf(\_PR.CPU7._PPC, Local0)) {
                     //   \_PR.CPU7._PPC(PCAP)
                        Store(PCAP, \_PR.CPU0._PPC)
                        Notify(\_PR.CPU7, 0x80)
                }
//<

                Return(PCAP)
    		}
    
	        case( 0x23)
    		{
                Return(PSCP)
    		}

	        case(0x24)
    		{
                CreateField(Arg3, 0, 20, THBG)
                CreateField(Arg3, 30, 1, DDVE)
    		}
			case(0x2a)
    		{
                Return(SSNR(Arg3))
    		}   
        } // end of switch

        Return(0x80000002)
    } // end SPB

     // Ventura Sensor parameters header structure
    Name(SBHS, Buffer(0x8) {})
    CreateDWordField(SBHS, 0, VERV)
    CreateDWordField(SBHS, 4, NUMS)

    // Ventura CPU Sensor structure
    Name(SSCP, Buffer(44) {})
    CreateDWordField(SSCP, 4, CSNT)
    CreateDWordField(SSCP, 8, CPTI)
    CreateDWordField(SSCP, 12, CICA)
    CreateDWordField(SSCP, 16, CIRC)
    CreateDWordField(SSCP, 20, CICV)
    CreateDWordField(SSCP, 24, CIRA)
    CreateDWordField(SSCP, 28, CIAV)
    CreateDWordField(SSCP, 32, CIEP)
    CreateDWordField(SSCP, 36, CPPF)
    CreateDWordField(SSCP, 40, CSNR)

   // Ventura GPU Sensor structure
    Name(SSGP, Buffer(44) {})
    CreateDWordField(SSGP, 4, GSNT)
    CreateDWordField(SSGP, 8, GPTI)
    CreateDWordField(SSGP, 12, GICA)
    CreateDWordField(SSGP, 16, GIRC)
    CreateDWordField(SSGP, 20, GICV)
    CreateDWordField(SSGP, 24, GIRA)
    CreateDWordField(SSGP, 28, GIAV)
    CreateDWordField(SSGP, 32, GIEP)
    CreateDWordField(SSGP, 36, GPPF)
    CreateDWordField(SSGP, 40, GSNR)

   // Ventura CPU Parameters Structure
    Name(SCPP, Buffer(72) {})
    CreateDWordField(SCPP, 0, VRV1)
    CreateDWordField(SCPP, 4, VCAP)
    CreateDWordField(SCPP, 8, VCCP)
    CreateDWordField(SCPP, 12, VCDP)
    CreateDWordField(SCPP, 16, VCEP)
    CreateDWordField(SCPP, 20, VCGP)
    CreateDWordField(SCPP, 24, VCHP)
    CreateDWordField(SCPP, 28, VCXP)
    CreateDWordField(SCPP, 32, VCYP)
    CreateDWordField(SCPP, 36, VCZP)
    CreateDWordField(SCPP, 40, VCKP)
    CreateDWordField(SCPP, 44, VCMP)
    CreateDWordField(SCPP, 48, VCNP)
    CreateDWordField(SCPP, 52, VCAL)
    CreateDWordField(SCPP, 56, VCBE)
    CreateDWordField(SCPP, 60, VCGA)
    CreateDWordField(SCPP, 64, VCPP)
    CreateDWordField(SCPP, 68, VCDE)

// Ventura GPU Parameters Structure
    Name(SGPP, Buffer(40) {})
    CreateDWordField(SGPP, 0, VRV2)
    CreateDWordField(SGPP, 4, VGWP)
    CreateDWordField(SGPP, 8, VGPP)
    CreateDWordField(SGPP, 12, VGQP)
    CreateDWordField(SGPP, 16, VGRP)
    CreateDWordField(SGPP, 20, VGAP)
    CreateDWordField(SGPP, 24, VGBP)
    CreateDWordField(SGPP, 28, VGCP)
    CreateDWordField(SGPP, 32, VGDP)
    CreateDWordField(SGPP, 36, VGDE)

    Method(SSNR, 1)
    {
        Switch (ToInteger(Arg0))
        {
            case (0x00)
            {
                    // Populate Header Structure
                    Store(0x00010000, VERV)
                    Store(0x02, NUMS)
                    Return(SBHS)
            }
            case (0x01)
            {
                Store(0x00010000, VRV1)				
    			Store(0x3E8, VCAP)  //VEN_CPU_PARAM_A_CK 0x3E8  
                Store(0x2EE, VCCP)  //VEN_CPU_PARAM_C_CK 0x2EE  
                Store(0x2EE, VCDP)  //VEN_CPU_PARAM_D_CK 0x2EE  
                Store(0x2EE, VCEP)  //VEN_CPU_PARAM_E_CK 0x2EE  
                Store(0x79e, VCGP)  //VEN_CPU_PARAM_G_CK 0x79e  
                Store(0x2bc, VCHP)  //VEN_CPU_PARAM_H_CK 0x2bc  
                Store(0x258, VCXP)  //VEN_CPU_PARAM_X_CK 0x258  
                Store(0x0fa, VCYP)  //VEN_CPU_PARAM_Y_CK 0x0fa  
                Store(0x1f4, VCZP)  //VEN_CPU_PARAM_Z_CK 0x1f4  
                Store(0x000, VCKP)  //VEN_CPU_PARAM_K_CK 0x000  
                Store(0x000, VCMP)  //VEN_CPU_PARAM_M_CK 0x000  
                Store(0x000, VCNP)  //VEN_CPU_PARAM_N_CK 0x000  
                Store(0x000, VCPP)  //VEN_CPU_PARAM_P_CK 0x000  
                Store(0x421, VCAL) //VEN_CPU_PARAM_AL_CK 0x421  
                Store(0x708, VCBE) //VEN_CPU_PARAM_BE_CK 0x708  
                Store(0x016, VCGA) //VEN_CPU_PARAM_GA_CK 0x016  
                Store(0x001, VCDE) //VEN_CPU_PARAM_DEL_CK 0x001
/* Clarksfield 8 CPU            
                Store(0x3E8, VCAP)
                Store(0x258, VCCP)
                Store(0x258, VCDP)
                Store(0x258, VCEP)
                Store(0x2CF, VCGP)
                Store(0x311, VCHP)
                Store(0x136, VCXP)
                Store(0x118, VCYP)
                Store(0x19A, VCZP)
                Store(0x001, VCKP)
                Store(0x001, VCMP)
                Store(0x001, VCNP)
                Store(0x000, VCPP)
                Store(0x36B, VCAL)
                Store(0x13C, VCBE)
                Store(0x019, VCGA)
                Store(0x001, VCDE)
end Clarksfield 8CPUs*/

                Return(SCPP)
            }
            case (0x02)
            {
                Store(0x00010000, VRV2)
                Store(0x3E8, VGWP)
                Store(0x2EE, VGPP)
                Store(0x2EE, VGQP)
                Store(0x2EE, VGRP)
                Store(0x001, VGAP)
                Store(0x1F4, VGBP)
                Store(0x000, VGCP)
                Store(0x000, VGDP)
                Store(0x001, VGDE)
/* Clarksfield 8 CPU            
                Store(0x3E8, VGBP)
                Store(0x001, VGCP)
                Store(0x001, VGDP)
                Store(0x000, VGDE)
end Clarksfield 8CPUs*/
                Return(SGPP)
            }
            case (0x03)
            {
                // The below sensor parameter values for GPU and CPU
                // are board specific. To support for ventura, fill
                // the SSCP and SSGP structures

                // Populate CPU Sensor values
                Store(0x0, Index(SSCP, 0))              // Indicate CPU sensor
                Store(0x00, CSNT)
                Store(0x01, CPTI)
                Store(0x84, CICA)	// 0x80
                Store(0x00, CIRC)
                Store(0x27FF, CICV)
                Store(0x05,   CIRA)
                Store(0xA000, CIAV)
                Store(0x03,   CIEP)
                Store(0x0F,   CPPF)
                Store(0x04,   CSNR)

                // Populate GPU Sensor values
                Store(0x1, Index(SSGP, 0))              // Indicate GPU sensor
                Store(0x00,   GSNT)
                Store(0x01,   GPTI)
                Store(0x8C,   GICA)	// 0x8A
                Store(0x00,   GIRC)
                Store(0x27FF, GICV)
                Store(0x05,   GIRA)
                Store(0xA000, GIAV)
                Store(0x03,   GIEP)
                Store(0x0F,   GPPF)
                Store(0x04,   GSNR)

                Return(Concatenate(SSCP, SSGP))
            }

        } //switch end

        Return(0x80000002)
    }
} // end DGPU_SCOPE scope

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