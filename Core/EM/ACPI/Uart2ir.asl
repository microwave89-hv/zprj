//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/Uart2ir.asl 7     3/26/09 4:53p Oleksiyy $
//
// $Revision: 7 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/Uart2ir.asl $
// 
// 7     3/26/09 4:53p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 6     4/09/08 5:05p Yakovlevs
// 
// 5     9/18/07 10:13a Pats
// Removed unnecessary decode range code.
// 
// 4     3/30/07 12:00p Pats
// Modified to support Fast IR.
// 
// 3     8/03/06 12:45p Stacyh
// Updated to allow the use of SI1P for systems with 2 SIOs.  Now contains
// generic methods assuming SI1P to be 0 as well as methods which check
// SI1P (these are commented out).
// 
// 2     4/03/06 4:05p Felixp
// New Super I/O infrastructure Support
// 
// 1     3/24/05 5:01p Sivagarn
// 
// 1     2/03/05 6:42p Sivagarn
// 0ABHI001 Check in
// 
// 1     7/27/04 2:48p Yakovlevs
// 
// 6     03/04/07 5:42p Chung
// Modify all I/O beta version
//
// 5	9/06/02 10:53a Alexp
// Add SourceSafe headers to all core asl files
//
//**********************************************************************;
// UART2 - COMB or Infrared //
// Requires Uart1(ir).asl component present as well
// Cannot be included along with UART2.ASL. Only one UART2 Device can be present in ASL.
// Category # :0x01
Device(UAR2)	// SMSC N207 UART 2.
{

OperationRegion(IOID,		// Name of Operation Region for SuperIO device
	SystemIO,		// Type of address space
	SP1O,			// Offset to start of region
	2)			// Size of region in bytes
				// End of Operation Region
Field(IOID, ByteAcc, NoLock,Preserve){
	INDX, 8,		// Field named INDX is 8 bit wide
	DATA, 8 		// Field DATA is 8 bit wide
}


//----------------------------------------------------------------------
//  Set of Field names to be used to access SIO configuration space.
//----------------------------------------------------------------------
IndexField(INDX, DATA, ByteAcc, NoLock, Preserve){
		Offset(0x02),
		CR02,	8, 	// UART Power Management
        Offset(0x0C),
        CR0C, 8,  // UARTMODE
		Offset(0x24),
		CR24,	8, 	// UART 1 Base Address
		CR25,	8, 	// UART 2 Base Address
		Offset(0x28),
		CR28,	8, 	// UART IRQ Select
		Offset(0x2B),
		CR2B,	8, 	// FIR Base address
		CR2C,	8, 	// FIR DMA
		Offset(0x3A),
		CR3A,	8, 	// LPC Docking Activate
		CR3B,	8, 	// LPC Docking Base (High)
		CR3C,	8, 	// LPC Docking Base (Low)
//		Offset(0x55),
//		CR55,	8, 	// Configuration Enable Key
//		Offset(0xAA),
//		CRAA,	8	// Configuration Disable Key
} //End of indexed field


//------------------------------------------------------------------------
// Entry Config Mode
//------------------------------------------------------------------------
Method(ENFG) {
	Store(0x55, INDX)
}


//------------------------------------------------------------------------
// Exit Config Mode
//------------------------------------------------------------------------
Method(EXFG, 0) {
	Store(0xAA, INDX)
}

    // Identify UART 2 as an IR Device.
	Name(_UID, 2)	//Generic ID for COMA
//	Name(_HID, EISAID("PNP0510"))

	Method(_HID, 0){
		ENFG()
		And(CR0C, 0x18, Local0)
		Store(CR2B, Local1)
		EXFG()
		If(Local0){
			If(Local1)
				{Return(EISAID("SMCF010"))}	//PnP Device ID FIR Type
			Else
				{Return(EISAID("PNP0510"))}	//PnP Device ID InfraRed Type
		}Else
			{Return(EISAID("PNP0501"))}	//PnP Device ID 16550 Type
	}


    // Status Method for UART 2.
    Method(_STA,0,Serialized)
    {
		//
		//Check SIR Base Address, If ADR9 and ADR8 are 0, SIR disabled.	
		//

		If(And(\IOST,0x02)){
			Return (0x0F)   // UART2 device Present
		} else {
			Return(0x00)	// Device not present
		}

	}

	// Disable Method for UART 2.
	Method(_DIS,0,Serialized)
	{
        ENFG()
		Store(And(CR02,0x0F),CR02)
        EXFG()
	}


  //
	// Current Resource Setting Method for UART 2.
  //
	Method(_CRS,0,Serialized)
	{

		ENFG()
		Store(CR2B, Local0)
		EXFG()
		If(Local0)
        {
    		// Create the FIR Buffer that stores the Resources to
    		// be returned.
    		Name(BUF0,ResourceTemplate()
    		{
        		IO(Decode16, 0x0000, 0x0000, 0x01, 0x08)
        		IO(Decode16, 0x0000, 0x0000, 0x01, 0x08)
        		IRQNoFlags() {7}
        		DMA(Compatibility, NotBusMaster, Transfer8, ) {2}
        	})

        	  // Create pointers to the specific byte.
              //
    	  	CreateByteField(BUF0,0x02,IO10)
    	  	CreateByteField(BUF0,0x03,IO11)
      		CreateByteField(BUF0,0x04,IO12)
    	  	CreateByteField(BUF0,0x05,IO13)
    	  	CreateByteField(BUF0,0x0a,IO20)
      		CreateByteField(BUF0,0x0b,IO21)
      		CreateByteField(BUF0,0x0c,IO22)
      		CreateByteField(BUF0,0x0d,IO23)
      	    CreateWordField(BUF0,0x11,IRQW)
   			CreateByteField(BUF0,0x14,DMA0)

            ENFG()
		
            //
		    // Write the Base Address into the Buffer.
            //
    		ShiftLeft(CR25,2,IO10)		// Low Byte.
            ShiftRight(And(CR25,0xC0), 6, IO11)
            Store(IO10, IO12)
            Store(IO11, IO13)

    		ShiftLeft(CR2B,3,IO20)		// Low Byte.
            ShiftRight(And(CR2B,0xE0), 5, IO21)
            Store(IO20, IO22)
            Store(IO21, IO23)

              //
    		  // Write the IRQ value into the Buffer.
              //
            Store(0x0,Local1)
            And(CR28,0x0F,Local1)
            ShiftLeft(1, Local1, IRQW)

            // Write DMA value into buffer
            Store(0x0,Local1)
            And(CR2C,0x0F,Local1)
    		If(LEqual(Local1, 0x0F)){
    			Store(0, DMA0)	//No DMA
    		}Else{
                ShiftLeft(1, Local1, DMA0)
    		}

            EXFG()

    		Return(BUF0)
        }
		Else 
        {
    		// Create the SIR Buffer that stores the Resources to
    		// be returned.
    		Name(BUF1,ResourceTemplate()
    		{
    			IO(Decode16,0x0000, 0x0000, 0x01, 0x08)
    			IRQNoFlags(){7}
        	})

        	  // Create pointers to the specific byte.
              //
    	  	CreateByteField(BUF1,0x02,IOL0)
      		CreateByteField(BUF1,0x03,IOL1)
    	  	CreateByteField(BUF1,0x04,IOL2)
      		CreateByteField(BUF1,0x05,IOL3)
      	    CreateWordField(BUF1,0x09,IRQR)
    
            ENFG()
		
            //
		    // Write the Base Address into the Buffer.
            //
    		ShiftLeft(CR25,2,IOL0)		// Low Byte.
            ShiftRight(And(CR25,0xC0), 6, IOL1)
            Store(IOL0, IOL2)
            Store(IOL0, IOL3)

              //
    		  // Write the IRQ value into the Buffer.
              //
            Store(0x0,Local1)
            And(CR28,0x0F,Local1)
            ShiftLeft(One,Local1,IRQR)

            EXFG()

    		Return(BUF1)
        }
	}

  //
	// Possible Resource Setting Method for UART 2.
  //
	Name(_PRS, ResourceTemplate() {
// IRQ, No DMA
	    	StartDependentFn(0, 0) 
            {
    			IO(Decode16,0x3E8,0x3E8,0x01,0x08) 
    			IRQNoFlags(){7}
    		}

			StartDependentFnNoPri()
			{
				IO(Decode16,0x2F8,0x2F8,0x01,0x08) 
    			IRQNoFlags() {3,4,5,6,7,10,11,12}
			}	

			StartDependentFnNoPri()
			{
				IO(Decode16,0x3F8,0x3F8,0x01,0x08) 
    			IRQNoFlags() {3,4,5,6,7,10,11,12}
			}	
	
			StartDependentFnNoPri()
			{
				IO(Decode16,0x2E8,0x2E8,0x01,0x08) 
    			IRQNoFlags() {3,4,5,6,7,10,11,12}
			}	

//IRA and DMA
		StartDependentFn(0, 0) {
   			IO(Decode16,0x3E8,0x3E8,0x01,0x08) 
			IO(Decode16,0x7E8,0x7E8,0x01,0x08)
   			IRQNoFlags(){7}
			DMA(Compatibility, NotBusMaster, Transfer8) {3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3F8, 0x3F8, 1, 8)
			IO(Decode16,0x7E8,0x7E8,0x01,0x08)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2F8, 0x3F8, 1, 8)
			IO(Decode16,0x7E8,0x7E8,0x01,0x08)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3E8, 0x3E8, 1, 8)
			IO(Decode16,0x7E8,0x7E8,0x01,0x08)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2E8, 0x3E8, 1, 8)
			IO(Decode16,0x7E8,0x7E8,0x01,0x08)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {1,2,3}
		}
		EndDependentFn()
	})


	// Set Resource Setting Method for UART 2.
	Method(_SRS,1,Serialized)
	{
		ENFG()
		Store(CR2B, Local0)
		EXFG()
		If(Local0)
        {
    		// Point to the specific information in the passed
    		// in Buffer.
    	  	CreateByteField(Arg0,0x02,IO10)
      		CreateByteField(Arg0,0x03,IO11)
    	  	CreateByteField(Arg0,0x0a,IO20)
      		CreateByteField(Arg0,0x0b,IO21)
      	    CreateWordField(Arg0,0x11,IRQW)
   			CreateByteField(Arg0,0x14,DMA0)

            ENFG()

            //
    		// Disable the device.
            //
    		And(CR02,0x0F,CR02)

            //
            // Set UART2 mode
            //
//    		Store(0x0B, CR0C)		
//	    	Store(0x40, CR0A)		
//	    	Store(0x0C, CR0C)		

            //
    		// Set the Base IO Address.
            //
            Store(ShiftRight(IO10,2),CR25)
            Or(CR25,ShiftLeft(IO11,6),CR25)
			If(IO20){
                Store(ShiftRight(IO20,3),CR2B)
                Or(CR2B,ShiftLeft(IO21,5),CR2B)
			}


            //
     		// Set the IRQ.
            //
    		And(CR28,0xF0,CR28)
    		Or(CR28,Subtract(FindSetRightBit(IRQW),1),CR28)

            // Set DMA
            And(CR2C,0xF0,CR2C)
            If(DMA0)
            {
        		Or(CR2C,Subtract(FindSetRightBit(DMA0),1),CR2C)
            }
            Else
            {
        		Or(CR2C,0x0F,CR2C) // No DMA
            }

            //
    		// Enable the device.
            // 
    		Or(CR02,0x80,CR02)
        
            EXFG()

        }
        Else
        {
    		// Point to the specific information in the passed
    		// in Buffer.
    		CreateByteField(Arg0,0x02,IOLO)
    		CreateByteField(Arg0,0x03,IOHI)
    		CreateWordField(Arg0,0x09,IRQR)

            ENFG()

            //
    		// Disable the device.
            //
    		And(CR02,0x0F,CR02)

            //
            // Set UART2 mode
            //
//    		Store(0x0B, CR0C)		
//	    	Store(0x40, CR0A)		
//	    	Store(0x0C, CR0C)		

            //
    		// Set the Base IO Address.
            //
            Store(ShiftRight(IOLO,2),CR25)
            Or(CR25,ShiftLeft(IOHI,6),CR25)

            //
     		// Set the IRQ.
            //
    		And(CR28,0xF0,CR28)
    		Or(CR28,Subtract(FindSetRightBit(IRQR),1),CR28)

            //
    		// Enable the device.
            // 
    		Or(CR02,0x80,CR02)
        
            EXFG()
        }
   	}

    //
	// D0 Method for UART 2.
    //
	Method(_PS0,0,Serialized)
	{
        ENFG()
		Store(Or(CR02,0x80),CR02)
        EXFG()
	}



    //
	// D3 Method for UART 2.
    //
	Method(_PS3,0,Serialized)
	{
        ENFG()
		Store(And(CR02,0x0F),CR02)
        EXFG()
	}

}