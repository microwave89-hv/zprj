//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPCH/NvGC6PCH.asl 1     2/21/13 5:39a Joshchou $Revision: 
//
// $Date: 2/21/13 5:39a $Log: 
// 
// 
// 
//**********************************************************************
External(\_SB.PCI0.LPCB.H_EC, DeviceObj)

External(SG_ULT_RP_NUM.LNKD)
External(SG_ULT_RP_NUM.LNKS)
External(DGPUPCH_SCOPE.TGPC, MethodObj)

#define JT_REVISION_ID        0x00000103               // Revision number
#define JT_FUNC_SUPPORT       0x00000000               // Function is supported?
#define JT_FUNC_CAPS          0x00000001               // Capabilities
#define JT_FUNC_POWERCONTROL  0x00000003               // dGPU Power Control
#define JT_FUNC_PLATPOLICY    0x00000004               // Platform Policy
#define JT_FUNC_DISPLAYSTATUS 0x00000005               // Query the Display Hot-Key
#define JT_FUNC_MDTK          0x00000006               // Display Hot-Key Toggle List


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!Note:This Asl Code is sample code for reference,should be modified it by different board design!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


Scope(\_SB.PCI0.LPCB.H_EC)
{
	// Nvidia recommneded to use EC IO for SBIOS to communicate GC6 entry/exit to EC,
        // Use EC RAM is polling mechanism and might cause the longer delay time for GC6 T1/T2 timing.
	// Here we just use EC RAM for example, pleae use EC IO access for production solution.
  OperationRegion(ECF3,EmbeddedControl,0,0xFF)
	Field(ECF3, ByteAcc, Lock, Preserve)
	{
		Offset(0xF0),	// assume GC6 control flags located at offset 0xE0
		EC6I, 1,        // EC flag to prepare GC6 entry
		EC6O, 1,        // EC flag to prepare GC6 exit
		FBST, 1,        // the state of FB_CLAMP
	}
	Mutex(GC6M, 0)
	Method(ECNV, 1, NotSerialized)
	{
		Acquire(GC6M, 0xFFFF)
		If(LEqual(Arg0, Zero))
		{
			Store(One, EC6I)
		}
		If(LEqual(Arg0, One))
		{
			Store(One, EC6O)
		}
	Release(GC6M)
	}

	Method(_Q60, 0, NotSerialized) // for GC6 entry Q-event
	{
		Store("------- GC6I-SCI _Q event --------", Debug)
                CreateField(DGPUPCH_SCOPE.TGPC,0x0A,0x2,PRGE)                // PRGE : PCIe Root Power GC6 Enter Sequence
                If(LEqual(ToInteger(PRGE), 0x0))                                   // DAGC : Link Disable after GC6 Entry complete & before GPU Power Down
                {
			Store(One, SG_ULT_RP_NUM.LNKD)                           // PCIE link disabling.
        	}
        		
		DGPUPCH_SCOPE.SGPO(HLRS, 0) // dGPU RST# to low
		DGPUPCH_SCOPE.SGPO(PWEN, 0)  // dGPU PWN Enable to low
                
		If(LEqual(ToInteger(PRGE), 0x2))                                   // DAGP : Link Disable after GC6 Entry & GPU Power down is complete
               	{
			Store(One, SG_ULT_RP_NUM.LNKD)                                    // PCIE link disabling.
        	}	
         }
	 Method(_Q61, 0, NotSerialized) // for GC6 exit Q-event
	 {
		Store("------- GC6O-SCI _Q event --------",Debug)
	 }
}

Scope (DGPUPCH_SCOPE)
{
  Name(TGPC, Buffer(0x04)
  {
           0x00
  }
  )

   Method(GC6I, 0, Serialized)
   {
               Store("<<< GC6I >>>", Debug)
               CreateField(TGPC,0x06,0x2,ECOC)	    // NOC: Notify on complete: Reserve
               CreateField(TGPC,0x0A,0x2,PRGE)     // PRGE : PCIe Root Power GC6 Enter Sequence
               If(Lor(LEqual(ToInteger(PRGE), 0x3), LEqual(ToInteger(PRGE), 0x1)))               // DBGS : Link Disable before GC6 Entry starts (E0)  
               {
		Store(One, SG_ULT_RP_NUM.LNKD)            // PCIE link disabling.
                }
        \_SB.PCI0.LPCB.H_EC.ECNV (0) // notify EC to prepare GC6 entry.
   }

   Method(GC6O, 0, Serialized)
   {
                Store("<<< GC6O >>>", Debug)
                CreateField(TGPC,0x06,0x2,ECOC)	    // NOC: Notify on complete: Reserve
                CreateField(TGPC,0x08,0x2,PRGX)     // PRGX : PCIe Root Power GC6 Exit Sequence
                 If(LEqual(ToInteger(PRGX), Zero))              // EBPG : Link Enable before GPU Power-On & GC6 Exit begins (X0)
                {
		Store(Zero, SG_ULT_RP_NUM.LNKD)          //  PCIE link enabling
                }
		DGPUPCH_SCOPE.SGPO(HLRS, 0)	   //  dGPU RST# is low 
         	DGPUPCH_SCOPE.SGPO(PWEN, 1)	   //  dGPU PWR Enable is high 
                //+ Todo - need to addd more delay to make sure all power rail is ready and stable       
                //         if you have PWR_OK to check, please check PWR_OK instead of delay here              
                //....................
                //-
                // GC6 T5 1.5ms 
                Store(Zero, Local0)                           // Delay by Stall(0x32) *30 times.= 1.5ms , you can add more if you don't think 1.5ms is good enough
		While(LLess(Local0, 0x1E))
 		{
   			   Add(Local0, One, Local0)
      		           Stall(0x32)
 		}
		DGPUPCH_SCOPE.SGPO(HLRS, 1)	   //  dGPU RST# is high
		If(LEqual(ToInteger(PRGX), 0x3))              // EAPG : Link Enable after GPU Power-On Reset, but before GC6 Exit begins
                {
                            Store(Zero, SG_ULT_RP_NUM.LNKD)          //  PCIE link enabling
                }
		 
		// Haswell UTL has no LNKS register, please remove it from Haswell platform
                While(LLess(SG_ULT_RP_NUM.LNKS, 0x07))
		{
			Sleep(One)
		}
                \_SB.PCI0.LPCB.H_EC.ECNV (1) // notify EC to prepare GC6 exit.
   }

   Method(GETS, 0, Serialized)
   {
		If(LEqual(DGPUPCH_SCOPE.SGPI(PWEN), One))   // dGPU PWR Enable is high
		{
				Store("<<< GETS() return 0x1 >>>", Debug)
				Return(One)// GC6 - dGPU on
		}
		Else
		{
			If(LEqual(\_SB.PCI0.LPCB.H_EC.FBST, One)) // FB_CLAMP asserted.
			{
				Store("<<< GETS() return 0x3 >>>", Debug)
				Return(0x03)// GC6 - dGPU off, FB On, w/ FB_CLAMP asserted
			}
			Else
			{
				Store("<<< GETS() return 0x2 >>>", Debug)
				Return(0x02)// GC6 - dGPU & FB Powered off
			}
		}
   }


//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    NGC6
//
// Description:  Called from _DSM -Device Specific Method for dGPU device.
//               Implement Ventura specific callback functions
//
// Input:
// Arg0:   UUID      Unique function identifier. 
//               Ventura DSM_GUID CBECA351-067B4924-9CBDB46B00B86F34
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
    Method (NGC6, 4, NotSerialized)
    {

        Store("------- GC6 DSM --------", Debug)
        // Only Interface Revision 0x0100 is supported
        If (LLess(Arg1, 0x100))
        {
                Return(0x80000001)
        }

        // (Arg2) Sub-Function
        Switch (ToInteger(Arg2))
        {
            //
            // Function 0:  
            //
            case (JT_FUNC_SUPPORT)
            {
				Return(Buffer(0x04)
				{
					0x1B, 0x00, 0x00, 0x00
				})
            }
            //
            // Function 1:  
            //
            case (JT_FUNC_CAPS)
            {

                Name(JTB1, Buffer(0x4)
                {
    				0x00
                })
				CreateField(JTB1,Zero,One,JTEN)
				CreateField(JTB1,One,0x02,SREN)
				CreateField(JTB1,0x03,0x03,PLPR)
				CreateField(JTB1,0x06,0x02,FBPR)
				CreateField(JTB1,0x08,0x02,GUPR)
				CreateField(JTB1,0x0A,One,GC6R)
				CreateField(JTB1,0x0B,One,PTRH)
				CreateField(JTB1,0x14,0x0C,JTRV)
				Store(One, JTEN)     // JT enable
				Store(One, GC6R)     // GC6 integrated ROM
				Store(One, PTRH)     // No SMI Handler
				Store(One, SREN)     // Disable NVSR
				Store(JT_REVISION_ID, JTRV)  // JT rev

                Return(JTB1)
            }
            //
            // Function 2:  
            //
	        case(0x00000002)
    		{
                Store("GPS fun 19", Debug)
                return(arg3)
    		}
            //
            // Function 3:  
            //
	        case(0x00000003)
    		{
				CreateField(Arg3,Zero,0x03,GUPC)
				CreateField(Arg3,0x04,One,PLPC)
				Name(JTB3, Buffer(0x04)
				{
					0x00
				})
				CreateField(JTB3,Zero,0x03,GUPS)
				CreateField(JTB3,0x03,One,GPGS)	    // dGPU Power status 
				CreateField(JTB3,0x07,One,PLST)
				If(LEqual(ToInteger(GUPC), One))           // EGNS 
				{
                                        Store(Arg3,TGPC)         // Store GC6 control input for GC6I GC6O
					GC6I()
					Store(One, PLST)
				}
				Else
				{
					If(LEqual(ToInteger(GUPC), 0x02))  // EGIS 
					{
                                                Store(Arg3,TGPC)         // Store GC6 control input for GC6I GC6O
						GC6I()
						If(LEqual(ToInteger(PLPC), Zero))
						{
							Store(Zero, PLST)
						}
					}
					Else
					{
						If(LEqual(ToInteger(GUPC), 0x03)) // XGXS 
						{
							Store(Arg3,TGPC)         // Store GC6 control input for GC6I GC6O
							GC6O()
							If(LNotEqual(ToInteger(PLPC), Zero))
							{
								Store(Zero, PLST)
							}
						}						
						Else
						{
							If(LEqual(ToInteger(GUPC), 0x04)) // XGIS
							{
								Store(Arg3,TGPC)         // Store GC6 control input for GC6I GC6O
								GC6O()
								If(LNotEqual(ToInteger(PLPC), Zero))
								{
									Store(Zero, PLST)
								}
							}
							Else
							{
								If(LEqual(ToInteger(GUPC), Zero)) 
								{
									Store(GETS(), GUPS)
									If(LEqual(ToInteger(GUPS), 0x01)) 
									{
                                  					   Store(One, GPGS)       // dGPU power status is Power OK
									}
									Else
									{
									    Store(Zero, GPGS)       // dGPU power status is Power off
									} 
								  }
								  Else 
								  {
								      If(LEqual(ToInteger(GUPC), 0x6)) // XLCM 
								      { 
								      //+ De-assert FB_CLAMP

								      //-
								  } 
								}
							}
						}
					}
				}
				Return(JTB3)
    		}
            //
            // Function 4:  
            //
	        case(JT_FUNC_PLATPOLICY)
    		{
                Return(0x80000002)
    		}

        } // end of switch

        Return(0x80000002)
    } // end NGC6


} // end DGPUPCH_SCOPE scope
//**********************************************************************
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
