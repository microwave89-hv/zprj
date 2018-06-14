
DefinitionBlock (
	"SsdtZpOdd.aml",
	"SSDT",
	1,
	"Intel",
	"zpodd",
	0x1000
  )
{
External(PFLV)
External(FDTP)
External(GPE3)
External(\GL00)
External(\GL08)
External(GPS3)
External(\_SB.PCI0.SAT0.PRT2, DeviceObj)
External(\GIV0)
External(RTD3, IntObj)

 If(LEqual(RTD3, Zero))
 {
    Scope(\_SB.PCI0.SAT0.PRT2)
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
                         If(LEqual(PFLV,FDTP)) { 
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
                  Store(0,GPE3)
                  If(LEqual(And(\GL00, 0x08), 0x08))
                  {
                     Or(\GIV0, 0x08, \GIV0)
                  } Else {
                     And(\GIV0, 0xF7, \GIV0)
                  }
                  And(\GL08, 0xEF, \GL08)
                  Sleep(0xC8) 
                  Store(1,GPS3)
                  Store(1,GPE3)
                  Return (1)
                } // Case (2)
                //
                // Power ON Device
                //
                Case (3) {
                  Store(0,GPE3)
                  Store(1,GPS3)
                  Or(\GL08, 0x10, \GL08)
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
  // SATA_ODD_DA 
  //
  Method(_L13) {
    //
    // Do nothing if Desktop platform
    //
    If(LEqual(PFLV,FDTP)) {
      Return ()
    }
    //
    // Power on drive, disable SCI on GPI
    // Disable SCI on GPIO3 (PMBASE+0x28 - BIT19)
    //
    Store(0,GPE3)
    //
    // Drive GPIO68 to High to power on device.
    //
    Or(\GL08, 0x10, \GL08)
    //
    // Notify the OSPM
    //
    Notify(\_SB.PCI0.SAT0, 0x82)
    Return ()
  }
} // \_GPE
} // If(LEqual(RTD3, Zero))
} // End SSDT
