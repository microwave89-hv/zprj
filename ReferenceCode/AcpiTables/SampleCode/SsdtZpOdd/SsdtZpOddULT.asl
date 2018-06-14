
DefinitionBlock (
	"SsdtZpOddult.aml",
	"SSDT",
	1,
	"Intel",
	"zpoddult",
	0x1000
  )
{
External(\GO17)
External(\_SB.PCI0.SAT0.PRT1, DeviceObj)
External(RTD3, IntObj)
External(ECON, IntObj)
External(\_SB.WTGP, MethodObj)


 If(LEqual(RTD3, Zero))
 {
    Scope(\_SB.PCI0.SAT0.PRT1)
	{		
        
          //
          // _DSM Device Specific Method supporting SATA ZPODD function
          //
          // Arg0: UUID Unique function identifier
          // Arg1: Integer Revision Level
          // Arg2: Integer Function Index
          // Arg3: Package Parameters
          //
          Method (_DSM, 4, NotSerialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj}) {
            If (LEqual(Arg0, ToUUID ("bdfaef30-aebb-11de-8a39-0800200c9a66"))) {
              //
              // Switch by function index
              //
              Switch (ToInteger(Arg2)) {
                //
                // Standard query - A bitmask of functions supported
                // Supports function 0-5
                //
                Case (0) {
                  switch(ToInteger(Arg1)) {
                    case(1) {
                        //
                        // Return - 0 (No Functions supported) for Desktop Platforms
                        //
                        If(LEqual(ECON, Zero)) {
                            Return (Buffer () {0})
                        }
                         Return (Buffer () {0xF})
                    }
                    Default {Return (Buffer () {0})}
                  }
                } // Case (0)
                //
                // Enable ZPODD feature
                //
                Case (1) {
                   Return (1)
                } // Case (1)
                //
                // Power Off Device
                //
                Case (2) {
                  //
                  // Drive GPIO to low to power off device.
                  //
                  \_SB.WTGP(86,1) // Power Off the device
                  Store(0,\GO17) // Enable GPIO86
                  Return (1)
                } // Case (2)
                //
                // Power ON Device
                //
                Case (3) {
                  \_SB.WTGP(86,0) // Power ON Device
                  Store(1,\GO17) // Enable GPIO86
                  Sleep(0x0A) // To turn the FET
                  Return (1)
                } // Case (3)

               Default { 
                Return (0) 
               }
              } // Switch (ToInteger(Arg2))
            } Else {
              Return (0) 
            } // bdfaef30-aebb-11de-8a39-0800200c9a66
          } // _DSM
    } // (\_SB.PCI0.SAT0)

//
// GPE Event Handler
//
Scope(\_GPE) {
  //
  // GPI03 = SATA_ODD_DA 
  //
  Method(_L11) {
    If(LEqual(ECON, Zero)) {
        Return ()
    }

    Store(1,\GO17) // Enable GPIO86
    Notify(\_SB.PCI0.SAT0, 0x81)
    Return ()
  }
} // \_GPE
} // If(LEqual(RTD3, Zero))
} // End SSDT
