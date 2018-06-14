//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:    _DSM PPI Method for TPM device 
//
// Description:  Implement Phisical Presence Interface
//
// Input:        \_SB.PCI0.LPCB.TP
//
// Output:      PPI result
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
Scope(\_SB.PCI0.TPM)
{    
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


    Method( _DSM , 4)
    {
        if( LEqual(Arg0,ToUUID("3DDDFAA6-361B-4EB4-A424-8D10089D1653")))
        {
                switch(ToInteger(Arg2))            
                {
                    //
                    // Function 0: Return supported funcitons
                    //
                    case(0)
                    {
                        return (Buffer() {0xff,0x01}) //support functions 0-6                       
                    }

                    //
                    // Function 1: Ge PPI Version
                    //
                    case(1)
                    {
                        return ("1.2")                        
                    }

                    //
                    // Function 2: Submit TPM Operation request
                    // Arg3[0]: Integer - Operation Value
                    case(2)
                    {
						ToInteger(DeRefOf(Index(Arg3,0)), TMF2)  //save request in temp flag
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
                        ToInteger(DeRefOf(Index(Arg3,0)), TMF2)  //save request in temp flag
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
                    
                        ToInteger(DeRefOf(Index(Arg3,0)), TMF2)  //save request in temp flag
                        Store(0x43, TMF1)           
                        Store(TMF1,DAT)	
                        Store(OFST,INQ)	
                        Store(TMF2,DAT)	
                        Store(OFST,INQ)	
                        return (DAT)                 
                    }

                    default { }                    
                }
        } else {if(LEqual(Arg0,
        ToUUID("376054ED-CC13-4675-901C-4756D7F2D45D"))){
            //
            // Reset Atack Mitigation
            //
             switch(ToInteger(Arg2))            
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

                        ToInteger(DeRefOf(Index(Arg3,0)), TMF1)  //save request in temp flag
						Store(TMF1,DAT)	  	 
                        Store(OFST,INQ)	

                        if(Lequal(DAT,0xFF)){
                            return(0x2)
                        } 
  	 
                        return (Zero) 		 
                    }
                    default { }                    
                }
            
        }}               
        return (Buffer() {0})
    }
}
