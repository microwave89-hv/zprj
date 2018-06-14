Scope (\_SB.PCI0)
{
   Device (FTPM)
   {
      //
      // Define _HID, "PNP0C31" is defined in
      //
      Name (_HID, "MSFT0101")
      
      //
      // Readable name of this device, don't know if this way is correct yet
      //
      Name (_STR, Unicode ("TPM 2.0 Device"))

      //
      // Return the resource consumed by TPM device
      //
      Name(_CRS,ResourceTemplate()
	    {
		    Memory32Fixed (ReadOnly, 0xFED70000, 0x1000,PCRS)
	    })

      OperationRegion (TPMR, SystemMemory, 0xFED70000, 0x1000)
      Field (TPMR, AnyAcc, NoLock, Preserve)
      {
        Offset(0x04),
        FERR, 32,
        Offset(0x0c),
        BEGN, 32,
      }

      OperationRegion (CRBD, SystemMemory, 0xFED70000, 0x1000)
      Field (CRBD, AnyAcc, NoLock, Preserve)
      {
        Offset(0x04),
        HERR, 32,
        Offset (0x40),
        HCMD, 32,
        Offset(0x44),
        HSTS, 32,
      }

      OperationRegion (ASMI, SystemIO, SMIA , 0x1) 
      Field (ASMI, ByteAcc, NoLock, Preserve) 
      { 
         INQ,8
      } 

      OperationRegion (BSMI, SystemIO, SMIB , 0x1) 
      Field (BSMI, ByteAcc, NoLock, Preserve) 
      { 
		DAT,8
      } 

      Method (_STA, 0)
      {  
        If(LEqual(TTDP, 1)){      
            If(LEqual(TTPF, 0)){
                Return (0x0f)  
            }
        }
        Return (0x0)
      }


      Method (STRT, 3, Serialized, 0, IntObj, {UnknownObj, UnknownObj, UnknownObj}) // IntObj, IntObj, PkgObj
      {
        //
        // Switch by function index
        //
        Switch (ToInteger (Arg1))
        {
            Case (0)
            {
                //
                // Standard query, supports function 1-1
                //
                Return (Buffer () {0x03})
            }
            Case (1)
            {   
              If(LEqual(Or(And(HSTS,0x00000002),And(HSTS,0x00000001)),0x00000003))
              {
                //
                // Trigger the FTPM_CMD interrupt
                //
                Store (0x00000001, HCMD)
              }
              Else
              {
                //Set Error Bit
                Store(0x00000001,FERR)
                //Clear Start Bit
                Store(0x00000000,BEGN)
              }
               Return (0)     
            }
        }
    
        Return (0)        
      }

      Method (CRYF, 3, Serialized, 0, {BuffObj, PkgObj}, {UnknownObj, UnknownObj, UnknownObj}) // IntObj, IntObj, PkgObj
      {
        //
        // Switch by function index
        //
        Switch (ToInteger(Arg1))
        {
          Case (0)
          {
            //
            // Standard query
            //
            Return (Buffer () {0x03})
          }
          Case (1)
          {
            //
            // Return failure if no TPM present
            //
            Name(TPMV, Package () {0x01, Package () {0x1, 0x20}})
            Return (TPMV)
          }
        }
        Return (Buffer () {0})
      }

      Method (PPIR, 3, Serialized, 0, {BuffObj, PkgObj, IntObj, StrObj}, {UnknownObj, UnknownObj, UnknownObj}) // IntObj, IntObj, PkgObj
      {        
        //
        // Switch by function index
        //
        Switch (ToInteger(Arg1))
        {
          Case (0)
          {
            //
            // Standard query, supports function 1-8
            //
            return (Buffer() {0xff,0x01}) //support functions 0-6            
          }
          Case (1)
          {
            //
            // a) Get Physical Presence Interface Version
            //
            Return ("1.2")
          }
        
            //
            // Function 2: Submit TPM Operation request
            // Arg3[0]: Integer - Operation Value
          case(2)
          {
	        ToInteger(DeRefOf(Index(Arg2,0)), TMF2)  //save request in temp flag
            Store(0x12, TMF1)
            Store(TMF1,DAT)	
            Store(OFST,INQ)	

            if(Lequal(DAT,0xFF)){
               return(0x2)
            }   	

			Store(TMF2,DAT)	  	 
            Store(OFST,INQ)	

            if(Lequal(DAT,0xFF)){
                return(0x2)
            } 

            if(Lequal(DAT,0xF1)){
                return(0x1)
            }

            return (Zero) 		 //Success                       
          }

          //
          // Function 3: Get pending TPM operation
          case(3)
          {
           	 Name(PPI1, Package(){0,0})
             Store(0x11,DAT)	     //read rqst operation
             Store(OFST,INQ)	  	 //should cause SMI

             if(Lequal(DAT,0xFF)){
                 return(0x1)
              } 

 			  Store(DAT, Index(PPI1,1))
			  return(PPI1)
          }

          //
          // Function 4: Get platform-specific action to transition 
          // ot Pre-OS
          // Returns: 
          // 0: None
          // 1: Shutdown
          // 2: Reboot
          // 3: OS Vendor Specific
          case(4)
          {         
                return (TRST) //Shutdown                       
          }

          //
          // Function 5: Return TPM responce
          //    
          case(5)
          {
               	Name(PPI2, Package(){0,0,0})
                Store(0x21,DAT)	 		
                Store(OFST,INQ)	
                Store(DAT, Index(PPI2,1))

                if(Lequal(DAT,0xFF)){
                    return(0x2)
                }  		

                Store(0x31,DAT)	 		
                Store(OFST,INQ)

                if(Lequal(DAT,0xFF)){
                    return(0x2)
                } 	 	
	
                IF (Lequal(DAT, 0xF0))
                {
                    Store(0x51,DAT)	 		
                    Store(OFST,INQ)
                    if(Lequal(DAT,0xFF)){
                       Store(0xFFFFFFF0, Index(PPI2,2))
                       return(PPI2)
                     }
                    }
                    ElseIF (Lequal(DAT, 0xF1))
                    {
                       Store(0x51,DAT)	 		
                       Store(OFST,INQ)
                       if(Lequal(DAT,0xFF)){
                          Store(0xFFFFFFF1, Index(PPI2,2))
                          return(PPI2)
                       }
                     }
                     Else
                     {Store(DAT, Index(PPI2,2))}
                    
                     return(PPI2) 
                 }


                 //
                 // Function 6: Submit preferred user language
                 // Ppi Spec 1.2 section 2.1.6      
                 //  Arg3[0]: String  - preferred language code
                 case(6)
                 {
                      return ( 0x03 ) //Success                             
                 }
                    
                    
                 //
                 // Function 7: Submit TPM Operation Request to Pre-OS Environment 2
                 // Ppi Spec 1.2 section 2.1.7   
                 //  Arg3[0]: String  - preferred language code
                 case(7)
                 {
                      ToInteger(DeRefOf(Index(Arg2,0)), TMF2)  //save request in temp flag
                      Store(0x12, TMF1)
                      Store(TMF1,DAT)	
                      Store(OFST,INQ)	

                      if(Lequal(DAT,0xFF)){
                          return(0x2)
                      }   	

					  Store(TMF2,DAT)	  	 
                      Store(OFST,INQ)	
  	
                      if(Lequal(DAT,0xFF)){
                           return(0x2)
                      } 

                      if(Lequal(DAT,0xF1)){
                           return(0x1)
                      }

                      return (Zero) 		 //Success                       
                  }

                  case(8)
                  {
                      ToInteger(DeRefOf(Index(Arg2,0)), TMF2)  //save request in temp flag
                      Store(0x43, TMF1)                      
                      Store(TMF1,DAT)	
                      Store(OFST,INQ)	
                      Store(TMF2,DAT)	
                      Store(OFST,INQ)	
                      return (DAT)                 
                  }

                  default { }                    
           }
      }

      Method (MORI, 3, Serialized, 0, IntObj, {UnknownObj, UnknownObj, UnknownObj}) // IntObj, IntObj, PkgObj
      {
        //
        // Switch by function index
        //
        Switch (ToInteger (Arg1))
        {
           //
           // Function 0: Return supported funcitons
           //
           case(0)
           {
               return (Buffer() {0x3}) //support functions 0 and 1
           }

           //
           // Function 1: Set MOR Bit State
           //
           case(1)
           {
                Store(0x22, TMF1)
                Store(TMF1,DAT)	
                Store(OFST,INQ)	  	

                if(Lequal(DAT,0xFF)){
                     return(0x2)
                 }  

                ToInteger(DeRefOf(Index(Arg2,0)), TMF1)  //save request in temp flag
				Store(TMF1,DAT)	  	 
                Store(OFST,INQ)	

                if(Lequal(DAT,0xFF)){
                      return(0x2)
                } 
  	 
                 return (Zero) 		 
            }
            default { }                    
         }
        return (Buffer() {0})        
      }

      Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj})
      {

        //
        // TCG Physical Presence Interface
        //
        If(LEqual(Arg0, ToUUID ("3dddfaa6-361b-4eb4-a424-8d10089d1653")))
        {
          Return (PPIR (Arg1, Arg2, Arg3))
        }

        //
        // TCG Memory Clear Interface
        //
        If(LEqual(Arg0, ToUUID ("376054ed-cc13-4675-901c-4756d7f2d45d")))
        {
          Return (MORI (Arg1, Arg2, Arg3))
        }

        //
        // TPM2 ACPI Start Method
        //
        If(LEqual(Arg0, ToUUID ("cf8e16a5-c1e8-4e25-b712-4f54a96702c8")))
        {
          Return (CRYF (Arg1, Arg2, Arg3))
        }

        If(LEqual(Arg0, ToUUID ("6bbf6cab-5463-4714-b7cd-f0203c0368d4")))
        {
          Return (STRT (Arg1, Arg2, Arg3))
        }

        Return (Buffer () {0})
      }

   }
}