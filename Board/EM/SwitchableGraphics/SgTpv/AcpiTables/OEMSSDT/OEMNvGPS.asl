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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMNvGPS.asl 2     9/09/12 11:01p Joshchou $
//
// $Revision: 2 $
//
// $Date: 9/09/12 11:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMNvGPS.asl $
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
External(\_PR.CPU0._PSS, BuffObj)

External(\_PR.CPU0._PPC, IntObj)
External(\_PR.CPU1._PPC, IntObj)
External(\_PR.CPU2._PPC, IntObj)
External(\_PR.CPU3._PPC, IntObj)
External(\_PR.CPU4._PPC, IntObj)
External(\_PR.CPU5._PPC, IntObj)
External(\_PR.CPU6._PPC, IntObj)
External(\_PR.CPU7._PPC, IntObj)
External(\_SB.PCI0.LPCB.H_EC.GTVR)    // CPU GT VR (IMVP) Temperature
External(\_PR.CPU0._TSS, MethodObj)
External(\_PR.CPU0._PTC, MethodObj)

#define GPS_REVISION_ID        0x00000100               // Revision number
#define GPS_ERROR_SUCCESS      0x00000000               // Generic Success
#define GPS_ERROR_UNSPECIFIED  0x00000001               // Generic unspecified error code
#define GPS_ERROR_UNSUPPORTED  0x00000002               // Sub-Function not supported

#define GPS_FUNC_SUPPORT       0x00000000               // Bit list of supported functions
#define GPS_FUNC_GETCALLBACKS  0x00000013               // Get system requested callback
#define GPS_FUNC_PSHARESTATUS  0x00000020               // Get system requested Power Steering Setting
#define GPS_FUNC_GETPSS        0x00000021               // Get _PSS object
#define GPS_FUNC_SETPPC        0x00000022               // Set _PCC object
#define GPS_FUNC_GETPPC        0x00000023               // Get _PCC object
#define GPS_FUNC_PSHAREPARAMS  0x0000002A               // Get sensor information and capabilities

Scope(PCI_SCOPE){

        Name(GPS, "GPSACPI 2012-Aug-12 14:56:05")       // MCPACPIP build time stamp.

} // end of Scope

Scope (DGPU_SCOPE)
{

Name(PSAP, Zero)
  Name(ECBF, Buffer(20) {})
  CreateDWordField(ECBF, 0, EDS1)
  CreateDWordField(ECBF, 4, EDS2)
  CreateDWordField(ECBF, 8, EDS3)
  CreateDWordField(ECBF, 12, EDS4)
  CreateDWordField(ECBF, 16, EPDT)

      Name(GPSP, Buffer(36) {})
        CreateDWordField(GPSP, 0, RETN)
        CreateDWordField(GPSP, 4, VRV1)
        CreateDWordField(GPSP, 8, TGPU)
        CreateDWordField(GPSP, 12, PDTS)
        CreateDWordField(GPSP, 16, SFAN)
        CreateDWordField(GPSP, 20, SKNT)
        CreateDWordField(GPSP, 24, CPUE)
        CreateDWordField(GPSP, 28, TMP1)
        CreateDWordField(GPSP, 32, TMP2)

Name(NLIM, 0) //set one flag for GPS_EVENT_STATUS_CHANGE 1: will update parameter: 0 just call function 0x1c _PCONTROL

        Name(PSCP, 0)           // P-State capacity, mainly for s/w debugging

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    GPS
//
// Description:  Called from _DSM -Device Specific Method for dGPU device.
//               Implement Ventura specific callback functions
//
// Input:
// Arg0:   UUID      Unique function identifier. 
//               Ventura DSM_GUID A3132D01-8CDA-49BA-A52E-BC9D46DF6B81
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
    Method (GPS, 4, NotSerialized)
    {

        Store("------- GPS DSM --------", Debug)
        // Only Interface Revision 0x0100 is supported
        If (LNotEqual(Arg1, 0x100))
        {
                Return(0x80000002)
        }

        P8DB(0xDD, Arg2, 1000)
        // (Arg2) Sub-Function
        Switch (ToInteger(Arg2))
        {

            case (GPS_FUNC_SUPPORT)
            {

                Name(FMSK, Buffer(0x8)
                {
    				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
                })
                Store(Buffer(0x8)
                {
    				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                }, Local0)
                Divide(GPS_FUNC_SUPPORT, 0x8, Local2, Local1)
		// Local1 is Quotient, Local2 is Remainder
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))

                Divide(GPS_FUNC_GETCALLBACKS, 8, Local2, Local1)
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))
                
                Divide(GPS_FUNC_PSHARESTATUS, 8, Local2, Local1)
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))
                
                Divide(GPS_FUNC_GETPSS, 8, Local2, Local1)
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))
                
                Divide(GPS_FUNC_SETPPC, 8, Local2, Local1)
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))
                
                Divide(GPS_FUNC_GETPPC, 8, Local2, Local1)
                ShiftLeft(0x01, Local2, Local2)
                Or( DeRefOf(Index(Local0, Local1)), Local2, Index(Local0, Local1))
                
                Divide(GPS_FUNC_PSHAREPARAMS, 8, Local2, Local1)
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
            //
            // Function 19: GPS_FUNC_GETCALLBACKS, 
            //
	        case(GPS_FUNC_GETCALLBACKS)
    		{
                Store("GPS fun 19", Debug)
                return(arg3)
    		}
            //
            // Function 32: GPS_FUNC_PSHARESTATUS, 
            //
	        case(GPS_FUNC_PSHARESTATUS)
    		{
                Store("GPS fun 20", Debug)

                Name(RET1, Zero)
                CreateBitField(Arg3,24,NRIT) //new request new IGP turbo state(bit 24 is valid)
                CreateBitField(Arg3,25,NRIS) //request new IGP turbo state
                   if (NRIS){
                      if(NRIT){
                       Or(RET1, 0x01000000, RET1)       
                      }else
                        {
                      //help disable IGP turbo boost
                      And(RET1, 0xFeFFFFFF, RET1)
                        }
                      }
                Or(RET1, 0x40000000, RET1)  // if this machine support GPS
       
                if(NLIM){
                   Or(RET1, 0x00000001, RET1)  // if NLIM falg is set, set bit0 =1
                }

                Return(RET1)
    		}
            //
            // Function 33: GPS_FUNC_GETPSS, Get CPU _PSS structure
            //
	        case(GPS_FUNC_GETPSS)
    		{
		        Return(\_PR.CPU0._PSS)
    		}
            //
            // Function 34: GPS_FUNC_SETPPC, Set current CPU _PPC limit
            //
	        case(GPS_FUNC_SETPPC)
    		{
                CreateBYTEField(Arg3, 0, PCAP)
                Store(PCAP, \_PR.CPU0._PPC)
                Notify(\_PR.CPU0, 0x80)
                store(PCAP, PSAP)
                Return(PCAP)
    		}
            //
            // Function 35: GPS_FUNC_GETPPC, Get current CPU _PPC limit
            //    
	        case(GPS_FUNC_GETPPC)
    		{
                Return(PSAP)
    		}

	        case(0x25)
    		{
                Store("GPS fun 25", Debug)     
                return(\_PR_.CPU0._TSS)
     		}
	        case(0x26)
    		{
                Store("GPS fun 26", Debug)     
                CreateDWordField(Arg3, Zero, TCAP)
                Store(TCAP, \_PR_.CPU0._PTC)
                Notify(\_PR_.CPU0, 0x80)
                return(TCAP)     		}
            //
            // Function 42: GPS_FUNC_PSHAREPARAMS, Get Power Steering platform parameters
            //
	        case(GPS_FUNC_PSHAREPARAMS)
    		{
                Store("GPS fun 2a", Debug)

                CreateBYTEField(Arg3,0,PSH0)
                CreateBYTEField(Arg3,1,PSH1)
                CreateBitField(Arg3,8,GPUT)
                CreateBitField(Arg3,9,CPUT)
                CreateBitField(Arg3,10,FANS)
                CreateBitField(Arg3,11,SKIN)
                CreateBitField(Arg3,12,ENGR)
                CreateBitField(Arg3,13,SEN1)
                CreateBitField(Arg3,14,SEN2)

                   switch (PSH0){
                      case(0){
                        if(CPUT){
                        store(0x00000200, RETN)
                        Or(RETN, PSH0, RETN)
                     // Please return CPU or EC tempture to PDTS
                        store(\_SB.PCI0.LPCB.H_EC.GTVR,PDTS)            
                        }
                	    return(GPSP)
                       } //case(0)

                      case(1){
                        store(0x00000200, RETN)
                        Or(RETN, PSH0, RETN)
                        store(1000,PDTS)
                        return(GPSP)
                      } //case(1)

                      case(2){
                        Or(RETN, PSH0, RETN)
                        store(0x00000000, VRV1)
                        store(0x00000000, TGPU)
                        store(0x00000000, PDTS)
                        store(0x00000000, SFAN)
                        store(0x00000000, CPUE)
                        store(0x00000000, SKNT)
                        store(0x00000000, TMP1)
                        store(0x00000000, TMP2)            
                        return(GPSP)          
                      } //case(2)
                   } // PSH0 of switch

    		}
        } // end of switch

        Return(0x80000002)
    } // end GPS


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
