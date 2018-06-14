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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMNViGPU.asl 2     9/09/12 11:01p Joshchou $
//
// $Revision: 2 $
//
// $Date: 9/09/12 11:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMNViGPU.asl $
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
External(NVGA)

External(NXD1)
External(NXD2)
External(NXD3)
External(NXD4)
External(NXD5)
External(NXD6)
External(NXD7)
External(NXD8)
External(DID1)
External(DID2)
External(DID3)
External(DID4)
External(DID5)
External(DID6)
External(DID7)
External(DID8)

Scope (IGPU_SCOPE)
{

    Method(_INI,0)
    {
        //DIDx values have been changed in MxmAcpiTables.c 
        //Port - D to be used for eDP only and not as DFP. Hence generating a new toggle list
        Store(DID1, Index(TLPK,0))      // CRT
        Store(DID2, Index(TLPK,2))      // LFP 
        Store(DID3, Index(TLPK,4))      // DP_B
        Store(DID4, Index(TLPK,6))      // HDMI_B 
        Store(DID5, Index(TLPK,8))      // HDMI_C
        Store(DID6, Index(TLPK,10))     // DP_D
        Store(DID7, Index(TLPK,12))     // HDMI_D             
        Store(DID2, Index(TLPK,14))     // LFP+CRT                 
        Store(DID1, Index(TLPK,15))
        Store(DID2, Index(TLPK,17))     // LFP+DP_B                
        Store(DID3, Index(TLPK,18))
        Store(DID2, Index(TLPK,20))     // LFP+HDMI_B                
        Store(DID4, Index(TLPK,21))
        Store(DID2, Index(TLPK,23))     // LFP+HDMI_C              
        Store(DID5, Index(TLPK,24))
        Store(DID2, Index(TLPK,26))     // LFP+DP_D                
        Store(DID6, Index(TLPK,27))
        Store(DID2, Index(TLPK,29))     // LFP+HDMI_D
        Store(DID7, Index(TLPK,30))       
    }

//
// MXMX method is dupplicated under GFX0 scope in INTELGFX.ASL
// need to replace it with method in this file.
//
#ifndef OPTIMUS_DSM_GUID
//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    MXMX
//
// Description:  Display DDC Mux Control
//
// Input:
// Arg0: Get/Set DDC/Aux Mux State
//  0- Acquire DDC/Aux Mux on this GPU
//  1- Release Mux from this GPU
//  2- Get Mux state
//
// Output:
//    0, Not Acquired.
//       if Arg0 = 0 or 1, Non-Zero return indicates success acquiring MUX 
//          (and MUX has switched to this output)
//       if Arg0 = 2, Non-Zero return indicates MUX is currently set to this output
//-------------------------------------------------------------------------
//<AMI_PHDR_END> 
    Method (MXMX, 1, Serialized) 
    {
        P8DB(0x77, Arg0, 2000)

        If (LEqual (Arg0, 0)) 
        {
            //Acquire DDC/AUX mux
            // No mutex implemented. No need to acquire mutex. 
            // Set mux to iGPU
            DGPU_SCOPE.SGPO(DSEL, 0)
            DGPU_SCOPE.SGPO(ESEL, 0)  // use edid_select# as mutex flag

            Return(0x1)
        }
            
        If (LEqual (Arg0, 1)) 
        {
            //Release DDC/AUX mux
            // No mutex implemented. No need to release mutex.
            // 2-way mux. Hence no need to do anything            
            Return(0x1)
        }

        If (LEqual (Arg0, 2))
        {

            //Get ddc/aux mux status for iGPU
            Return(LNot(DGPU_SCOPE.SGPI(ESEL)))
        }

        Return(0x0) // mutex not acquired
    }


//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    MXDS
//
// Description:  Display output MUX control
//
// Input:
// Arg0:
// 0 - Get Mux state
// 1 - Set Display to active on this GPU
// 2 - Set Backlight control to active on this GPU
// 3 - Set Display & Backlight to active on this GPU 
//
// Output:
//  If Arg0 = 0, Error = Display is not MUXed
//  Else return value of the state of the MUX
//-------------------------------------------------------------------------
//<AMI_PHDR_END>    
    Method(MXDS, 1, Serialized)
    {
        P8DB(0x7A, Arg0, 2000)

        If(LEqual (Arg0, 0))
        {
            //Get display mux status for iGPU
            return(LNot(DGPU_SCOPE.SGPI(DSEL)))
        } else       
//        If(LOr(LEqual (Arg0, 1), LEqual (Arg0, 2)))
        {
            //Set display mux to igpu
            DGPU_SCOPE.SGPO(DSEL, 0)
            DGPU_SCOPE.SGPO(PSEL, 0)
        }

        Return (0)
    }

#endif // OPTIMUS_DSM_GUID

//<AMI_SHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    NVIG
//
// Description:  Nvidia NVIG (iGPU) OperationRegion
//
//-------------------------------------------------------------------------
//<AMI_SHDR_END>    
    OperationRegion(NVIG,SystemMemory,NVGA,0x400)
    Field(NVIG, DWordAcc, NoLock, Preserve)
    {
        // OpRegion Header

        NISG,   0x80,          // (000h) Signature-"NVSG-IGD-DSM-VAR".
        NISZ,   0x20,          // (010h) OpRegion Size in KB.
        NIVR,   0x20,          // (014h) OpRegion Version.

        // OpRegion Data
        GPSS,   0x20,           // Policy Selection Switch Status (Policy selection)
        GACD,   0x10,           // Active Displays
        GATD,   0x10,           // Attached Displays
        LDES,   0x08,           // Lid Event State
        DKST,   0x08,           // Dock State
        DACE,   0x08,           // Display ACPI event
        DHPE,   0x08,           // Display Hot-Plug Event
        DHPS,   0x08,           // Display Hot-Plug Status
        SGNC,   0x08,           // Notify Code (Cause of Notify(..,0xD0))
        GPPO,   0x08,           // Policy Override (Temporary ASL variables)
        USPM,   0x08,           // Update Scaling Preference Mask (Temporary ASL variable)
        GPSP,   0x08,           // Panel Scaling Preference
        TLSN,   0x08,           // Toggle List Sequence Number
        DOSF,   0x08,           // Flag for _DOS
        ELCL,   0x10,           // Endpoint Link Contol Register Value
    }
    
    // Toggle List Package
    Name(TLPK,Package()
    {
        //fix this toggle list. DIDx values have been changed in MxmAcpiTables.c 
        0xFFFFFFFF, 0x2C,                           // CRT
        0xFFFFFFFF, 0x2C,                           // LFP
        0xFFFFFFFF, 0x2C,                           // DP_B
        0xFFFFFFFF, 0x2C,                           // HDMI_B
        0xFFFFFFFF, 0x2C,                           // HDMI_C
        0xFFFFFFFF, 0x2C,                           // DP_D
        0xFFFFFFFF, 0x2C,                           // HDMI_D
        0xFFFFFFFF, 0xFFFFFFFF, 0x2C,               // LFP+CRT
        0xFFFFFFFF, 0xFFFFFFFF, 0x2C,               // LFP+DP_B
        0xFFFFFFFF, 0xFFFFFFFF, 0x2C,               // LFP+HDMI_B
        0xFFFFFFFF, 0xFFFFFFFF, 0x2C,               // LFP+HDMI_C
        0xFFFFFFFF, 0xFFFFFFFF, 0x2C,               // LFP+DP_D
        0xFFFFFFFF, 0xFFFFFFFF, 0x2C,               // LFP+HDMI_D

    })
  
//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    INDL
//
// Description:  Initialize Global Next active device list.
//
// Input: None
//
// Output: None
//-------------------------------------------------------------------------
//<AMI_PHDR_END>    
    Method(INDL, 0, Serialized)
    {
            Store(0, NXD1)
            Store(0, NXD2)
            Store(0, NXD3)
            Store(0, NXD4)
            Store(0, NXD5)
            Store(0, NXD6)
            Store(0, NXD7)
            Store(0, NXD8)
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    SND1
//
// Description:  Set Next active device for a single device
//
// Input: 
//  Arg0 : Device ID of the device that's to be set as next active device.
//
// Output: None
//-------------------------------------------------------------------------
//<AMI_PHDR_END>    
    Method(SND1, 1, Serialized)
    {
        If(LEqual(Arg0, DID1))
        {
                Store(1, NXD1)
        }
        If(LEqual(Arg0, DID2))
        {
                Store(1, NXD2)
        }
        If(LEqual(Arg0, DID3))
        {
                Store(1, NXD3)
        }
        If(LEqual(Arg0, DID4))
        {
                Store(1, NXD4)
        }
        If(LEqual(Arg0, DID5))
        {
                Store(1, NXD5)
        }
        If(LEqual(Arg0, DID6))
        {
                Store(1, NXD6)
        }
        If(LEqual(Arg0, DID7))
        {
                Store(1, NXD7)
        }
        If(LEqual(Arg0, DID8))
        {
                Store(1, NXD8)
        }
                
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    SNXD
//
// Description:  Set Next active device
//
// Input: 
//      Arg0 TLSN
//
// Output: None
//-------------------------------------------------------------------------
//<AMI_PHDR_END>    
    Method(SNXD, 1, Serialized)
    {
        INDL()
        
        //
        // Locate the toggle table entry corresponding to TLSN value
        // Toggle list entries are separated by 0x2C.
        //
        
        Store(1, Local0)  // Local0 to track entries. Point to the first entry (TLSN starts from 1)
        Store(0, Local1)  // Local1 to track elements inside the TLPK package (ACPI IDs and '0x2C')

        while(LLess(Local0, Arg0))  // TLSN start from 1!!
        {
            if(LEqual(DeRefOf(Index(TLPK,Local1)), 0x2C))
            {
                Increment(Local0)
            }
            Increment(Local1) 
            
        }

        SND1(DeRefOf(Index(TLPK, Local1)))      // 1 st ACPI ID in the entry corresponding to TLSN
        Increment(Local1)
        if(LNotEqual(DeRefOf(Index(TLPK,Local1)), 0x2C))  // Check for separator
        {
            SND1(DeRefOf(Index(TLPK, Local1)))  // 2 nd ACPI ID in the entry corresponding to TLSN
        }
        
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    CTOI
//
// Description:  Convert _DOD indices-> MDTL index
//
// Input: 
//          Arg 0 is the currently active display list
//
// Output: None
//-------------------------------------------------------------------------
//<AMI_PHDR_END>    
    Method(CTOI,1, Serialized)
    {
        Switch(ToInteger(Arg0))        //Arg 0 is the currently active display list
        {
            //_DOD indices-> MDTL index
            case(0x1)       {Return(1)}     //CRT
            case(0x2)       {Return(2)}     //LFP
            case(0x4)       {Return(3)}     //DP_B
            case(0x8)       {Return(4)}     //HDMI_B
            case(0x10)      {Return(5)}     //HDMI_C           
            case(0x20)      {Return(6)}     //DP_D
            case(0x40)      {Return(7)}     //HDMI_D
            case(0x3)       {Return(8)}     //LFP+CRT
            case(0x6)       {Return(9)}     //LFP+DP_B
            case(0xA)       {Return(10)}    //LFP+HDMI_B
            case(0x12)      {Return(11)}    //LFP+HDMI_C
            case(0x22)      {Return(12)}    //LFP+DP_D
            case(0x42)      {Return(13)}    //LFP+HDMI_D
            Default         {Return(1)}
        }
    }

// Check for Nvidia _DSM  UUIDs
//
//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    HDSM
//
// Description:  Device Specific Methods for Hybrid GPU (may be invoked from dGP and iGD)
//               Implements Mxm and SG specific callback functions
//
// Input:
// Arg0:   UUID      Unique function identifier. 
//                   nVidia
//                         SG dGPU  GUID :9D95A0A0-0060-4D48-B34D-7E5FEA129FD4
//                          NBCI    GUID :D4A50B75-65C7-46F7-BfB7-41514CEA0244
//                          Ventura GUID :95DB88FD-940A-4253-A446-70CE0504AEDF
//                      Optimus DSM_GUID :A486D8F8-0BDA-471B-A72B-6042A6B5BEE0
//
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
    Method(HDSM, 4, SERIALIZED)
    {      

#if NV_VENTURA_SUPPORT == 1
        //SPB_DSM_GUID     {95DB88FD-940A-4253-A446-70CE0504AEDF}
//x     if(CMPB(Arg0, Buffer(){0xFD,0x88,0xDB,0x95,0x0A,0x94,0x53,0x42,0xA4,0x46,0x70,0xCE,0x05,0x04,0xAE,0xDF}))
        If(LEqual(Arg0, ToUUID("95DB88FD-940A-4253-A446-70CE0504AEDF")))
        {
            return ( DGPU_SCOPE.SPB(Arg0, Arg1, Arg2, Arg3))
        }
#endif

#if NV_GPS_SUPPORT == 1
        //SPB_DSM_GUID     {A3132D01-8CDA-49BA-A52E-BC9D46DF6B81}
//x     if(CMPB(Arg0, Buffer(){0x01, 0x2D, 0x13, 0xA3, 0xDA, 0x8C, 0xBA, 0x49,0xA5, 0x2E, 0xBC, 0x9D, 0x46, 0xDF, 0x6B, 0x81}))
        If(LEqual(Arg0, ToUUID("A3132D01-8CDA-49BA-A52E-BC9D46DF6B81")))
        {
            return ( DGPU_SCOPE.GPS(Arg0, Arg1, Arg2, Arg3))
        }
#endif

#if HYBRID_DSM_GUID || NBCI_DSM_GUID || OPTIMUS_DSM_GUID

        Name(SGCI, 0)   // SG Common Interface
        Name(NBCI, 0)   // Notebok Common Interface
        Name(OPCI, 0)   // Optimus Common Interface
        Name(BUFF, 0)   // Buff Parameter

// Hybrid Graphics Methods supported only if MUXed mode is selected
#ifdef HYBRID_DSM_GUID
        If(LEqual(Arg0, ToUUID("9D95A0A0-0060-4D48-B34D-7E5FEA129FD4")))
        {
            Store(1, SGCI)
        }
#endif
// NBCI Methods can be querried in botd MUXed and MUXless modes
#ifdef NBCI_DSM_GUID
        if(LEqual(Arg0, ToUUID("D4A50B75-65C7-46F7-BfB7-41514CEA0244")))
        {
            Store(1, NBCI)
        }
#endif
// Optimus Methods can be querried in botd MUXed and MUXless modes
#ifdef OPTIMUS_DSM_GUID
        If(LEqual(Arg0, ToUUID("A486D8F8-0BDA-471B-A72B-6042A6B5BEE0")))
        {
            Store(1, OPCI)
        }
#endif

        If(LOr(OPCI, LOr( SGCI, NBCI)) )
        { 

        P8DB(0xEE, Arg2, 1000)

            if(OPCI) {
                if(LNotEqual(Arg1, 0x100)) {
                    Return(0x80000002)
                }
            }
            else { // NBCI & SGCI
                If(LNotEqual(Arg1,0x0102))
                {
                    Return(0x80000002)
                }
            }
            //
            // Function 0: NVSG_FUNC_SUPPORT - Return Supported Functions
            //
            // Returns:
            // SGCI: Functions 0-6,18 are supported
            // NBCI: Functions 0,4-6,18 are supported
            // OPCI: Functions 0,5,6,12,13,16,17,26,27
            //
            If(LEqual(Arg2,0))
            {
                if(SGCI){
                    Return(Buffer(){0x7F, 0x00, 0x04, 0x00})
                } else { 
                    if(NBCI){
                        Return(Buffer(){0x73, 0x00, 0x04, 0x00})
                    }
                    else {
                        if(OPCI){
                        //Sub-Functions 0,16,17,26 are supported
    //                    Return(ToBuffer(0x04030001))
                        //Sub-Functions 0,5, 6, 12, 13, 16, 17, 26,27 are supported
    //                     Return(ToBuffer(0x0c031861))
                            Return(Buffer(){0x61, 0x18, 0x03, 0x0C})
                        //Sub-Functions 0,16 26,27 are supported
//                            Return(ToBuffer(0x0c010001))

                        }
                    }
                }
            }
    
            //
            // Function 1: NVSG_FUNC_CAP
            //
            // Returns the capabilities of the Switchable Graphics
            // implementation on the platform
            //
            If(LEqual(Arg2,1))
            {
                Name (TEMP, Buffer () {0x00, 0x00, 0x00, 0x00})
                CreateDwordField(TEMP,0,STS0)
                if(SGCI){          
                    // Return status (bit0-1 Hybrid enabled) and indicate Hybrid power On/Off
            
                    // 0 HG Enable Status           = 1
                    // 1 GPU Output MUX Capabilities= 1
                    // 2 GPU Policy Selector Capabilities = 1
                    // 3-4 GPU Control Status       = 3
                    // 5 GPU Reset Control          = 1
                    // 6 MUX'ed Hot-Plug Capabilities = 0
                    // 7 MUX'ed DDC/AUX Capabilities  = 1
                    // 8-10 Notify Codes
                    //    0= Not a Notify(0xD0)
                    //    1= POLICYSELECT change
                    //    2= PLATPOLICY change
                    //    3= DISPLAYSTATUS change
                    // 11-12 EC Notify code
                    // 14-15 Eject Capabilities     = 0
                    // 16    Mux'd backlight cap    = 0
                    // 17-23 Hybrid EC version      = 0
                    // 24-26 HG capability          = 3 (Power saver & Boost performance)
                    // 27-28 HG switch              = 1 (hot-key or stateless button) 
                    // 29 Fasl LCD swithing         = 0
                    // 31 = 0
       
                // Switchable caps
                    Or(STS0,0x0B0000BF,STS0)
        
                // Switchable Notify Code (Cause of Notify(..,0xD0))
                    Or(STS0,ShiftLeft(SGNC,8,SGNC),STS0)
                } else {
            // NBCI
                    // 0..3 Reserved=00
                    // 4 Aux Power States
                    // 6:5 LID State Event
                    //   0= Use the event List to determine support
                    //   1= Force use of Generic Hot-Plug Notify(0x81)
                    //   2= Force use of Specific Lid Event, e.g. Notify (0xDB)
                    //   3= Reserved for future use
                    // 7:8 LID State Enumeration
                    //   0= Use _DCS under _LCD device(default)
                    //   1= Provides status DISPLAYSTATUS Bit[4], for single pannel systems only(recommended)
                    //   2,3= Reserved
                    // 9 Dock State Enumerartion
                    //   0= Doesn't have a Dock(or _DCS under device reflects attachments-via-dock (default)
                    //   1= Provides dock status info via DISPLAYSTATUS Bit[5] (recommended)
                    // 10:30 Reserved
                    // 31 = 0

                    // use all defaults for now        
                    Or(STS0,0x00000,STS0)
                }
                return(TEMP)
            }
    
            //
            // Function 2: NVSG_FUNC_SELECTOR
            // 
            // Returns device preference between iGPU and dGPU
            //
            If(LEqual(Arg2,2))
            {
                Name (TMP1, Buffer () {0x00, 0x00, 0x00, 0x00})
                CreateDwordField(TMP1,0,STS1)
    
                //Ignore bits[6:5] since we are not supporting Switchable enable/disable policy selection
                //Only Switchable policy selection is supported via CAS+F6 hotkey
    
                //bugbug:Proxy is sending Arg3 as Buffer and not package! 
                //ToInteger(DerefOf(Index(Arg3,0)), Local0)
                ToInteger(Arg3, Local0)
                And(Local0, 0x1F, Local0)
                              
                If(And(Local0,0x10))    //If Switchable policy update bit is set
                {
                    And(Local0,0xF,Local0)
                    Store(Local0,GPSS)
                    Notify(IGPU_SCOPE,0xD9)     //Broadcast "policy completed" notification
                    Notify(PCI_SCOPE.WMI1, 0xD9)    // Mirror Notify on WMI1
    
                }
                Else
                {
                    And(Local0,0xF,Local0)
                    If(LEqual(GPPO,1))
                    {
                        // Retrieve the setting from NVS
                        Store(GPSS,Local0)
                        Or(Local0,0x10,Local0)
                        Store(0,GPPO)
                    }
                }
    
                Or(STS1,Local0,STS1)
    
                Return(TMP1)
            }
    
            //
            // Function 3: NVSG_FUNC_POWERCONTROL
            //
            // Allows control of dGPU power methods from the iGPU
            //
            If(LEqual(Arg2,3))
            {
                Name (TMP2, Buffer () {0x00, 0x00, 0x00, 0x00})
                CreateDwordField(TMP2,0,STS2)
    
                // GPU Power Control
                //bugbug:Proxy is sending Arg3 as Buffer and not package! 
                //ToInteger(DerefOf(Index(Arg3,0)), Local0)
                ToInteger(Arg3, Local0)
                And(Local0, 0x3, Local0)
    
                If(LEqual(Local0,0))
                {
                    DGPU_SCOPE.SGST()
                }
    
                If(LEqual(Local0,1))
                {
                    DGPU_SCOPE.SGON()
                }
    
                If(LEqual(Local0,2))
                {
                    DGPU_SCOPE.SGOF()
                }
    
                //dGPU_PWROK is not working. Using dGPU_PWR_EN# instead as w/a
                //Or(STS2,DGPU_SCOPE.MPOK,STS2)
                If(LEqual(DGPU_SCOPE.SGST(), 0xF))
                {
                    Or(STS2,0x1,STS2)
                }
                //else do nothing since STS2 is already 0
                Return(TMP2)
            }
    
            //
            // Function 4: NVSG_FUNC_PLATPOLICY
            // 
            // Sets or Returns the current System Policy settings
            //
            If(LEqual(Arg2,4))
            {

// common for SGCI and NBCI
                Name (TMP3, Buffer () {0x00, 0x00, 0x00, 0x00})
                CreateDwordField(TMP3,0,STS3)
                
                // Panel Scaling Preference
    
                //bugbug:Proxy is sending Arg3 as Buffer and not package! 
                //ToInteger(DerefOf(Index(Arg3,0)), Local0)
                ToInteger(Arg3, Local0)
                Store(Local0, Local1)
                ShiftRight(Local0, 16, Local0)
                And(Local0, 0x1, USPM)
    
                ShiftRight(Local1, 13, Local1)
                And(Local1, 0x3, Local1)
    
    
                If(LNotEqual(Local1,GPSP))
                {
                    If(LEqual(USPM,1))
                    {
                        Store(Local1,GPSP)
                    }
                    Else
                    {
                        // Retrieve the setting from NVS
                        Store(GPSP,Local1)
                        Or(STS3,0x8000,STS3)    // Set Panel Scaling override
                    }
                }
                Or(STS3,ShiftLeft(Local1,13),STS3)
    
    
                Return(TMP3)
            }
    
            //
            // Function 5: NVSG_FUNC_DISPLAYSTATUS
            // 
            // Sets or Returns the current display detection,
            // hot-key toggle sequence
            //
            If(LEqual(Arg2,5))
            {
// common for SGCI and NBCI
                Name (TMP4, Buffer () {0x00, 0x00, 0x00, 0x00})
                CreateDwordField(TMP4,0,STS4)
    
                //bugbug:Proxy is sending Arg3 as Buffer and not package! 
                //ToInteger(Derefof(Index(Arg3,0)), Local0)    //Store input field in local0
                ToInteger(Arg3, Local0)                    
    
                // Next Combination Sequence
    
                If(And(Local0,0x80000000))      //If Bit31 is set
                {
                    Store(And(ShiftRight(Local0,25),0x1F),TLSN)
                
                    If(And(Local0,0x40000000))   //If Bit30 is set
                    {                           
                        Store(1,DOSF)
                    }
                }
    
                // Display Mask for Attached and Active Displays
    
                If(And(Local0,0x01000000))       //If Bit24 is set
                {
                    Store(And(ShiftRight(Local0,12),0xFFF),GACD)
                    Store(And(Local0,0xFFF),GATD)
                    
                    //Get current toggle list index based on currently active display list
                    Store(CTOI(GACD),TLSN)
                    Increment(TLSN)
    
                    If(LGreater(TLSN, 13))        //For Huron River ,13 is the number of entries in the toggle list 
                    {
                        Store(1, TLSN)
                    }
    
                    SNXD(TLSN)                  //This is optional for NV SG
                }
    
                // Display Hot-Plug Event/Status
                Or(STS4,ShiftLeft(DHPE,21),STS4)
                Or(STS4,ShiftLeft(DHPS,20),STS4)
    
                // Toggle Sequence number
                Or(STS4,ShiftLeft(TLSN,8),STS4)
    
                // Dock State                
                Or(STS4,ShiftLeft(DKST,5),STS4)
    
                // Lid Event State
                Or(STS4,ShiftLeft(LDES,4),STS4)
    
                // Display ACPI Event(SGCI only)
                Or(STS4,DACE,STS4)
    
                Store(0,LDES)
                Store(0,DHPS)
                Store(0,DHPE)
                Store(0,DACE)
    
                Return(TMP4)
            }
    
            //
            // Function 6: NVSG_FUNC_MDTL - Returns Hot-Key display switch toggle sequence
            //
            // Returns:
            //   Returns Hot-Key display switch toggle sequence
            //
            If(LEqual(Arg2,6))
            {
// common for SGCI and NBCI
                Return(TLPK)
            }
            //
            // Function 16:  
            //
            If(LEqual(Arg2,16))
            {
                CreateWordField(Arg3, 2, USRG)          // Object type signature passed in by driver.                  
                Name(OPVK, Buffer()
                {
                // Key below is for Emerald Lake Fab2 platform
                // Customer need to ask NVIDIA PM to get the key
                // Customer need to put the key in between labels "// key start -" and
                //  "// key end -". Please consult NVIDIA PM if any issues
            //148597456985Genuine NVIDIA Certified Optimus Ready Motherboard for 736019_MIRc
                // Key start -
                    0xE4,0x42,0x5F,0x14,0x36,0x26,0x16,0x37,0x4B,0x56,0xE6,0x00,0x00,0x00,0x01,0x00,
                    0x31,0x34,0x38,0x35,0x39,0x37,0x34,0x35,0x36,0x39,0x38,0x35,0x47,0x65,0x6E,0x75,
                    0x69,0x6E,0x65,0x20,0x4E,0x56,0x49,0x44,0x49,0x41,0x20,0x43,0x65,0x72,0x74,0x69,
                    0x66,0x69,0x65,0x64,0x20,0x4F,0x70,0x74,0x69,0x6D,0x75,0x73,0x20,0x52,0x65,0x61,
                    0x64,0x79,0x20,0x4D,0x6F,0x74,0x68,0x65,0x72,0x62,0x6F,0x61,0x72,0x64,0x20,0x66,
                    0x6F,0x72,0x20,0x37,0x33,0x36,0x30,0x31,0x39,0x5F,0x4D,0x49,0x52,0x63,0x20,0x20,
                    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x2D,0x20,0x3C,0x34,0x27,0x21,0x58,0x29,
                    0x57,0x27,0x58,0x20,0x27,0x25,0x59,0x5D,0x31,0x29,0x3A,0x2A,0x26,0x39,0x59,0x43,
                    0x56,0x3B,0x58,0x56,0x58,0x3D,0x59,0x4E,0x3B,0x3A,0x35,0x44,0x25,0x42,0x5A,0x48,
                    0x55,0x3A,0x58,0x4C,0x25,0x48,0x54,0x21,0x35,0x4B,0x4D,0x37,0x2C,0x3C,0x20,0x2D,
                    0x20,0x43,0x6F,0x70,0x79,0x72,0x69,0x67,0x68,0x74,0x20,0x32,0x30,0x31,0x30,0x20,
                    0x4E,0x56,0x49,0x44,0x49,0x41,0x20,0x43,0x6F,0x72,0x70,0x6F,0x72,0x61,0x74,0x69,
                    0x6F,0x6E,0x20,0x41,0x6C,0x6C,0x20,0x52,0x69,0x67,0x68,0x74,0x73,0x20,0x52,0x65,
                    0x73,0x65,0x72,0x76,0x65,0x64,0x2D,0x31,0x34,0x38,0x35,0x39,0x37,0x34,0x35,0x36,
                    0x39,0x38,0x35,0x28,0x52,0x29,
            //Copyright 2010 NVIDIA Corporation All Rights Reserved-148597456985(R)
                // Key end -
                })
                If(LEqual(USRG, 0x564B)) {              // 'VK' for Optimus Validation Key Object.
                   Return(OPVK)
                }
                Return(Zero)
            }
            //
            // Function 17 NVOP_FUNC_GETALLOBJECTS
            //
            If(LEqual(Arg2,17))

            {
                Return(Zero)
            }
            //
            // Function 18: NVSG_FUNC_GETEVENTLIST
            //
            // Returns:
            //   Returns list of notifiers and their meanings
            //
            If(LEqual(Arg2,18))
            {
// common for SGCI and NBCI
                return(Package(){
                    0xD0, ToUUID("921A2F40-0DC4-402d-AC18-B48444EF9ED2"), // Policy request
                    0xD9, ToUUID("C12AD361-9FA9-4C74-901F-95CB0945CF3E"), // Policy set
                    0xDB, ToUUID("42848006-8886-490E-8C72-2BDCA93A8A09"), // Display scaling

                    0xEF, ToUUID("B3E485D2-3CC1-4B54-8F31-77BA2FDC9EBE"), // Policy change
                    0xF0, ToUUID("360d6fb6-1d4e-4fa6-b848-1be33dd8ec7b"), // Display status
        
            // unfinished list of events. we do not need this Func18 unless event notifiers differ from standard ones defined in BWG. 
                    })
            }
            //
            // Function 26: NVOP_FUNC_OPTIMUSCAPS
            //
            If(LEqual(Arg2,26))
            {
                // On Input
                //Bit25-24 Power Control Enable
                // 2-Platform should not power down GPU in the _PS3 method(default)
                // 3-Platform should power down GPU in the _PS3 method(default)
                // Bit0 No flag upd present in this call (SBIOS returns curent status)
                //
                CreateField(Arg3,24,2,OMPR)
                CreateField(Arg3,0,1,FLCH)
                If(ToInteger(FLCH))
                {
                    Store(OMPR, DGPU_SCOPE.OPCE)                   // Optimus Power Control Enable - From DD
                }
                // On return
                // Bit 24:26 Capabilities
                //  0: No special platf cap
                //  1: Platform has dynamic GPU power control
                // Bit6 GPU Display Hot Plug NEW Optimus BWG v02
                // Bit4:3 Current GPU Control status
                //  0: GPU is powered off
                //  1: GPU is powered on and enabled
                //  2: reserved
                //  3: GPU Power has stabilized
                // Bit0  
                //  0:Optimus Disabled
                //  1:Optimus Enabled
                Store(Buffer(4) {0, 0, 0, 0}, Local0)
                CreateField(Local0,0,1,OPEN)
                CreateField(Local0,3,2,CGCS)
                CreateField(Local0,6,1,SHPC)
                CreateField(Local0,24,3,DGPC)           // DGPC - Default: No Dynamic GPU Power Control
                CreateField(Local0,27,2,HDAC)           // HDAC - HD Audio Codec Cap

                Store(One, OPEN)                        // Optimus Enabled

                Store(One, SHPC)                        // GPU Display Hotplug Supported
                Store(0x2, HDAC)                        // HDA BIOS control Supported

                Store(One, DGPC)                        // Dynamic GPU Power Control Available
                If(LNotEqual(DGPU_SCOPE.SGST(), 0))
                {
                    Store(0x3, CGCS)                    // Current GPU Control status
                }
  		        Return(Local0)

            }//case (26)
            //
            // Function 27: NVOP_FUNC_OPTIMUSFLAGS
            //
            If(LEqual(Arg2,27))
            {
                //bugbug:Proxy is sending Arg3 as Buffer and not package! 
                //ToInteger(Derefof(Index(Arg3,0)), Local0)    //Store input field in local0
                ToInteger(Arg3, Local0)    
//                Store(Arg3, Local0)
//                CreateField(Local0,0,1,OPFL)
//                CreateField(Local0,1,1,OPVL)
                If(And(Local0,0x00000002))
                {
                    Store(Zero, BUFF)
                    If(And(Local0,0x00000001))
                    {
                        Store(One, BUFF)
                    }
                }
                And(SGFL, Not(0x2), SGFL)
                Or(SGFL, ShiftLeft(BUFF,1), SGFL)
                Store(SWSMI_NVOEM_CMOS_W, SSMP)  // Set Audio Codec flag to CMOS
                Return(Local0)
            }
            // FunctionCode or SubFunctionCode not supported
            Return(0x80000002)  // OTHER ARGUMENTS NOT SUPPORTED
        } 
#endif // common scope for Hybrid/Nbci/Optimus

        // Check for common with dGPU _DSM  UUIDs
//      return (DGPU_SCOPE.HDSM(Arg0, Arg1, Arg2, Arg3))
      Return (0x80000001)
    }
} // end PCI0.GFX0 scope
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
