//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//
//*************************************************************************
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866 Device ASL Files/LPTE.ASL 1     7/20/11 4:22a Kasalinyi $
//
// $Revision: 1 $
//
// $Date: 7/20/11 4:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866 Device ASL Files/LPTE.ASL $
// 
// 1     7/20/11 4:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Initial Porting
// [Files]  		DeviceASL.cif
// FDC.ASL
// LPTE.ASL
// PS2kb.asl
// PS2ms.asl
// Uart1.ASL
// Uart2.ASL
// Uart3.ASL
// Uart4.ASL
// Uart5.ASL
// Uart6.ASL
// SIOH.ASL
// 
// 3     3/21/11 9:43p Mikes
// Clean code
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <LPTE.ASL>
//
// Description: Define ACPI method or namespce For Super IO
//
//<AMI_FHDR_END>
//*************************************************************************

//**********************************************************************;
// Parallel port - LPT or ECP(Extended mode)
//**********************************************************************;
// Category # :0x02
Device(LPTE) {
    Method(_HID, 0){                        //PnP Device ID
        If(^^SIO1.LPTM(2))                  //Get LPT mode : 0-plain LPT, non Zero-ECP mode
            {Return(EISAID("PNP0401"))}     //PnP ID for ECP Port
        Else
            {Return(EISAID("PNP0400"))}     //PnP ID for LPT Port
    }

    Method(_STA, 0) {Return(^^SIO1.DSTA(2))}//Get Device status

    Method(_DIS, 0) {^^SIO1.DCNT(2,0)}      //Disable LPT, arg0 - LDN, arg1 - 1(disable)

    Method(_CRS, 0) {                       //Get LPT current resources
        ^^SIO1.DCRS(2, 1)                   //Fill in Return buffer with DMA, Irq and 1st IO

        //adjust base/aligment size if base ports are 0x3bc/0x7bc
        If(And(^^SIO1.IO11, 0x04)) { 
            Store(0x04, ^^SIO1.LEN1)
        }

        If(^^SIO1.LPTM(2)){                 //Extended LPT mode ?
            //Move resources from CRS1 ro CRS2 buffer
            Store(^^SIO1.IRQM, ^^SIO1.IRQE) //IRQ mask 0x1
            Store(^^SIO1.DMAM, ^^SIO1.DMAE) //DMA 0x04

            Store(^^SIO1.IO11, ^^SIO1.IO21) //1st IO Range Min Base Word 0x8
            Store(^^SIO1.IO12, ^^SIO1.IO22) //             Max Base Word 0xa
            Store(^^SIO1.LEN1, ^^SIO1.LEN2)

            Add(^^SIO1.IO21, 0x400, ^^SIO1.IO31)//2nd IO range
            Store(^^SIO1.IO31, ^^SIO1.IO32)
            Store(^^SIO1.LEN2, ^^SIO1.LEN3)
            Return(^^SIO1.CRS2)
        }else{
            Return(^^SIO1.CRS1)
        }
    }

    Method(_SRS, 1) {                       //Set LPT resources
        ^^SIO1.DSRS(Arg0, 2)
    }

    Method(_PRS, 0) {                       //Return Possible resources
        If(^^SIO1.LPTM(2))                   //Get LPT mode : 0-plain LPT, non Zero-ECP mode
            {Return(EPPR)}                  //ECP mode resources
        Else
            {Return(LPPR)}                  //LPT mode resources
    }


//-----------------------------------------------------------------------
// LPT Possible Resources
//-----------------------------------------------------------------------
//------------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
    Name(LPPR, ResourceTemplate(){
// IRQ
        StartDependentFn(0,0) {
            IO(Decode16, 0x378, 0x378, 1, 8)
            IRQNoFlags() {7}
        }
        StartDependentFnNoPri() {
            IO(Decode16, 0x378, 0x378, 1, 8)
            IRQNoFlags() {7}
        }
        StartDependentFnNoPri() {
            IO(Decode16, 0x278, 0x278, 1, 8)
            IRQNoFlags() {7}
        }
        StartDependentFnNoPri() {
            IO(Decode16, 0x3BC, 0x3BC, 1, 4)
            IRQNoFlags() {7}
        }
// No IRQ
//        StartDependentFnNoPri() {
//            IO(Decode16, 0x378, 0x378, 1, 8)
//            IRQNoFlags() {}
//        }
//        StartDependentFnNoPri() {
//            IO(Decode16, 0x278, 0x278, 1, 8)
//            IRQNoFlags() {}
//        }
//        StartDependentFnNoPri() {
//            IO(Decode16, 0x3BC, 0x3BC, 1, 4)
//            IRQNoFlags() {}
//        }
        EndDependentFn()
    })

//-----------------------------------------------------------------------
// ECP Possible Resources
//-----------------------------------------------------------------------
    Name(EPPR, ResourceTemplate() {
        StartDependentFn(0, 0) {
            IO(Decode16, 0x378, 0x378, 1, 8)
            IO(Decode16, 0x778, 0x778, 1, 8)
            IRQNoFlags() {7}
            DMA(Compatibility, NotBusMaster, Transfer8) {3}
        }
        StartDependentFnNoPri() {
            IO(Decode16, 0x378, 0x378, 1, 8)
            IO(Decode16, 0x778, 0x778, 1, 8)
            IRQNoFlags() {7}
            DMA(Compatibility, NotBusMaster, Transfer8) {1,3}
        }
        StartDependentFnNoPri() {
            IO(Decode16, 0x278, 0x278, 1, 8)
            IO(Decode16, 0x678, 0x678, 1, 8)
            IRQNoFlags() {7}
            DMA(Compatibility, NotBusMaster, Transfer8) {1,3}
        }
        StartDependentFnNoPri() {
            IO(Decode16, 0x3BC, 0x3BC, 1, 4)
            IO(Decode16, 0x7BC, 0x7BC, 1, 4)
            IRQNoFlags() {7}
            DMA(Compatibility, NotBusMaster, Transfer8) {1,3}
        }
// No IRQ
//        StartDependentFnNoPri() {
//            IO(Decode16, 0x378, 0x378, 1, 8)
//            IO(Decode16, 0x778, 0x778, 1, 8)
//            IRQNoFlags() {}
//            DMA(Compatibility, NotBusMaster, Transfer8) {1,3}
//        }
//        StartDependentFnNoPri() {
//            IO(Decode16, 0x278, 0x278, 1, 8)
//            IO(Decode16, 0x678, 0x678, 1, 8)
//            IRQNoFlags() {}
//            DMA(Compatibility, NotBusMaster, Transfer8) {1,3}
//        }
//        StartDependentFnNoPri() {
//            IO(Decode16, 0x3BC, 0x3BC, 1, 4)
//            IO(Decode16, 0x7BC, 0x7BC, 1, 4)
//            IRQNoFlags() {}
//            DMA(Compatibility, NotBusMaster, Transfer8) {1,3}
//        }
        EndDependentFn()
    })

//**********************************************************************;
} // End Of LPTE

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
