//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:    _DSM PPI Method for TPM device 
//
// Description:  Implement Phisical Presence Interface using WordAcc
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
Scope(\_SB.TPM)
{    
    OperationRegion (TSMI, SystemIO, SMIA , 0x2) 
    Field (TSMI, WordAcc, NoLock, Preserve) 
    { 
        SMI,16,
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
                        Store(OFST, TMF1)	                        
                        Or(0x1200, TMF1, TMF1)

                        Store(0xFA,P80D)		
                        Store(TMF1,SMI)	
                        Store(SMI,TMF1)	
                        ShiftRight(TMF1, 0x8, TMF1)

                        if(Lequal(TMF1,0xFF)){
                            return(0x2)
                        }   	

                        ShiftLeft(TMF2, 0x8, TMF2)
                        Or(OFST, TMF2, TMF2)

                        Store(TMF2,SMI)	   
                        Store(SMI,TMF1)	
                        ShiftRight(TMF1, 0x8, TMF1)

                        if(Lequal(TMF1,0xFF)){
                            return(0x2)
                        } 

                        if(Lequal(TMF1,0xFF)){
                            return(0x1)
                        }

                        return (Zero) 		 //Success                       
                    }

                    //
                    // Function 3: Get pending TPM operation
                    case(3)
                    {
                        Store(0xFB,P80D)
 	                	Name(PPI1, Package(){0,0})
                        Store(OFST,TMF1)	                        
                        Or(0x1100, TMF1, TMF1)

                        Store(TMF1, SMI)	
                        Store(SMI,TMF1)	
                        ShiftRight(TMF1, 0x8, TMF1)

                        if(Lequal(TMF1,0xFF)){
                            return(0x1)
                        } 

						Store(TMF1, Index(PPI1,1))
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
                        Store(0xFC,P80D)  
                        return (TRST) //Shutdown                       
                    }

                    //
                    // Function 5: Return TPM responce
                    //    
                    case(5)
                    {
	                	Name(PPI2, Package(){0,0,0})
                        Store(0xFD,P80D)
                        Store(OFST,TMF1)	                        
                        Or(0x2100, TMF1, TMF1)
                        Store(TMF1,SMI)	

                        Store(SMI,TMF1)	
                        ShiftRight(TMF1, 0x8, TMF1)

                        if(Lequal(TMF1,0xFF)){
                            return(0x2)
                        }  		

                        Store(TMF1, Index(PPI2,1))                

                        Store(OFST,TMF1)	                        
                        Or(0x3100, TMF1, TMF1)

                        Store(TMF1,SMI)	

                        Store(SMI,TMF1)	
                        ShiftRight(TMF1, 0x8, TMF1)


                        if(Lequal(TMF1,0xFF)){
                            return(0x2)
                        } 	 	

                        IF (Lequal(TMF1, 0xF0))
                        {
                           Store(OFST,TMF1)	                        
                           Or(0x5100, TMF1, TMF1)
                           Store(TMF1,SMI)	
                           Store(SMI,TMF1)	
                           ShiftRight(TMF1, 0x8, TMF1)

                           if(Lequal(TMF1,0xFF)){
                              Store(0xFFFFFFF0, Index(PPI2,2))
                              return(PPI2)
                           }

                        }
                        ElseIF (Lequal(TMF1, 0xF1))
                        {
                           Store(OFST,TMF1)	                        
                           Or(0x5100, TMF1, TMF1)
                           Store(TMF1,SMI)	
                           Store(SMI,TMF1)	
                           ShiftRight(TMF1, 0x8, TMF1)

                           if(Lequal(TMF1,0xFF)){
                              Store(0xFFFFFFF1, Index(PPI2,2))
                              return(PPI2)
                           }
                        }
                        Else
                        {Store(TMF1, Index(PPI2,2))}
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
                        Store(0xFE,P80D)
                        Store(OFST,TMF1)	                        
                        Or(0x1200, TMF1, TMF1)
                        Store(TMF1,SMI)	

                        Store(SMI,TMF1)	
                        ShiftRight(TMF1, 0x8, TMF1)

                        if(Lequal(TMF1,0xFF)){
                            return(0x2)
                        }   	

                        ShiftLeft(TMF2, 0x8, TMF2)
                        Or(OFST, TMF2, TMF2)

                        Store(TMF2,SMI)	   
                        Store(SMI,TMF1)	
                        ShiftRight(TMF1, 0x8, TMF1)

  	
                        if(Lequal(TMF1,0xFF)){
                            return(0x2)
                        } 

                        if(Lequal(TMF1,0xF1)){
                            return(0x1)
                        }

                        return (Zero) 		 //Success                       
                    }

                    case(8)
                    {
                          Store(0xFF,P80D)
                        ToInteger(DeRefOf(Index(Arg3,0)), TMF2)  //save request in temp flag           
                          Store(OFST,TMF1)	                        
                          Or(0x4300, TMF1, TMF1)
                          Store(TMF1,SMI)	
                          Store(SMI,TMF1)
                          ShiftLeft(TMF2, 0x8, TMF2)
                          Or(OFST, TMF2, TMF2)
                          Store(TMF2,SMI)	   
                          Store(SMI,TMF1)	
                          ShiftRight(TMF1, 0x8, TMF1)	
                          return (TMF1)
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
                        Store(0xF1,P80D)
                        Or(0x2200, TMF1, TMF1)
                        Store(TMF1,SMI)	
                        Store(SMI,TMF1)
                        ShiftRight(TMF1, 0x8, TMF1)

                        if(Lequal(TMF1,0xFF)){
                            return(0x2)
                        }  

                        ToInteger(DeRefOf(Index(Arg3,0)), TMF1)  //save request in temp flag
                        ShiftLeft(TMF1, 0x8, TMF1)
                        Or(OFST, TMF1, TMF1)
                        Store(TMF1,SMI)	   
                        Store(SMI,TMF1)
                        ShiftRight(TMF1, 0x8, TMF1)

                        if(Lequal(TMF1,0xFF)){
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
