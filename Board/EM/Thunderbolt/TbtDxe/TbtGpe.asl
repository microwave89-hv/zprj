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
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtDxe/TbtGpe.asl 22    5/19/14 7:32a Barretlin $
//
// $Revision: 22 $
//
// $Date: 5/19/14 7:32a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtDxe/TbtGpe.asl $
// 
// 22    5/19/14 7:32a Barretlin
// [TAG]  		EIP165410
// [Category]  	New Feature
// [Description]  	Support Thunderbolt AIC at NB PCIE slot
// [Files]  		TbtPei.c TbtDxe.c TbtGpe.asl TbtSmm.c TbtOemBoard.c
// TbtOemLib.c TbtOemLib.h TbtSetup.sdl TbtSetup.sd TbtSetup.uni
// TbtSetupReset.c
// 
// 21    5/19/14 7:13a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Using setup item choose return value of _RMV method in
// ASL code
// [Files]  		TbtDxe.c TbtGpe.asl TbtOemBoard.c TbtOemBoard.h TbtSetup.sd
// TbtSetup.sdl TbtSetup.uni
// 
// 20    2/22/14 5:50p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	For Cactus Ridge host the thunderbolt hotplug event cannot
// be trigger
// [RootCause]  	signal event is not trigger under _INI/TINI method cause
// OS will not set GPE event enable bit
// [Solution]  	Change signal event location of _INI/TINI method
// [Files]  		TbtGpe.asl
// 
// 19    2/18/14 12:07p Barretlin
// 
// 18    2/18/14 6:02a Barretlin
// [TAG]  		EIP152401
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Update Intel Thunderbolt Sample code rev 1.9
// [Files]  		TbtSmm.c TbtGpe.asl TbtOemPorting.asl
// 
// 17    1/05/14 1:43p Barretlin
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Support Thunderbolt feature Enable/Disable in run time
// Support dynamic Thunderbolt AIC location in run time
// [Files]  		TbtDxe.c TbtGpe.asl
// 
// 16    7/26/13 2:24a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	remove non Intel RC config
// [Files]  		TbtGpe.asl
// 
// 15    6/21/13 7:41a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix build error with non Intel RC project
// [Files]  		TbtDxe.sdl TbtDxe.c TbtGpe.asl TbtDxeLib.h
// 
// 14    6/19/13 9:24a Barretlin
// [TAG]  		EIP126581
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Update Intel Thunderbolt sample code to rev. 1.7
// [Files]  		TbtGpe.asl
// 
// 13    5/27/13 8:57a Barretlin
// [TAG]  		EIP124914
// [Category]  	New Feature
// [Description]  	Support Falcon Ridge chip
// [Files]  		TbtGpe.asl
// 
// 12    5/27/13 8:54a Barretlin
// [TAG]  		EIP122882
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	let system entering sleep status continually and waking up
// system via Thunderbolt Lan device, system will auto-wake
// [RootCause]  	PCIE PME status is not cleared by ASL in SB module
// [Solution]  	Clear PCIE PME status againg before system entring sleep
// status
// [Files]  		TbtDxe.sdl TbtGpe.asl
// 
// 11    5/27/13 8:46a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	add sychronized method to make sure executed sequence
// is one by one
// [Files]  		TbtGpe.asl
// 
// 10    4/12/13 1:18p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Rollback OSUP method and following Intel sample code
// [Files]  		TbtGpe.asl
// 
// 9     4/10/13 2:31p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Change reported MMIO address way in ASL code
// [Files]  		TbtDxe.c TbtGpe.asl
// 
// 8     4/10/13 1:37p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Adding a TPTS method into _PTS method in ASL code
// [Files]  		TbtDxe.sdl TbtGpe.asl
// 
// 7     4/03/13 8:42a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix might hang up when S3 resuming
// [Files]  		TbtGpe.asl
// 
// 6     3/21/13 4:58a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Use token to decide where location of OS_UP command for
// RR chip is
// [Files]  		TbtDxe.sdl TbtGpe.asl
// 
// 5     2/08/13 1:23a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Following Intel sample code move _INI method of
// thunderbolt from under PCIE root port to under system bus
// [Files]  		TbtDxe.sdl TbtGpe.asl
// 
// 4     2/06/13 7:49a Barretlin
// [TAG]  		EIP114556
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Update RR handshake flow for Thunderbolt RR Spec 0.9
// [Files]  		TbtGpe.asl
// 
// 3     1/24/13 1:31a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	TBT debug setup item function fail
// [RootCause]  	ASL updating error
// [Files]  		TbtGpe.asl
// 
// 2     1/18/13 2:26a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Improve _RMV ASL code  for SharkBay RC
// [Files]  		TbtDxe.sdl TbtDxe.c TbtGpe.asl
// 
// 1     1/10/13 4:56a Barretlin
// Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
// Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
// 
// 6     12/12/12 3:02a Barretlin
// [TAG]  		EIP108272
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update to Spec 1.4 to support Redwood Ridge chip
// [Files]  		TbtPei.c TbtSmm.c TbtDxe.c TbtDxe.sdl TbtGpe.asl
// TbtOemBoard.c TbtOemBoard.h TbtOemLib.c TbtOemLib.h
// 
// 5     10/28/12 10:50p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Change GPIO routing for SharkBay ULT platform
// [Files]  		TbtDxe.c TbtGpe.asl TbtDxeLib.c TbtDxeLib.h TbtSmm.c
// 
// 4     5/07/12 6:34a Barretlin
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add three setup items for debug
// [Files]  		TbtDxe.c
// TbtGpe.asl
// TbtSmm.c
// TbtSetup.sd
// TbtSetup.uni
// TbtOemBoard.c
// TbtOemBoard.h
// 
// 3     4/16/12 10:17a Barretlin
// [TAG]  		EIP86590
// [Category]  	Bug Fix
// [Symptom]  	Only EP#1 can be detected after resume from S3
// [Solution]  	Adding a TWAK method into _WAK method
// [Files]  		TbtDxe.sdl  TbtGpe.asl
// 
// 2     4/14/12 4:50a Barretlin
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Improve ASL code, which redefines device name and RMV
// mothod at same address when project supports RMV method, that might
// cause conflict.
// [Files]  		TbtDxe.c  TbtGpe.asl
// 
// 1     12/08/11 4:09a Wesleychen
// Thunderbolt eModule initially releases.
// 
//*************************************************************************
Scope(\)
{
    Mutex(OSUM, 0)  // OS Up mutex
    Event(WFEV)
//    Name(TBTE, 0) // Thunderbolt function enable
    Name(PEMA, ASL_PCIEX_BASE_ADDRESS) // PCIE base address
    Name(TBRP, ASL_TBT_RPNum) // PCIE root port location for Thunderbolt Host
    Name(TBUS, 0xFF) // Thunderbolt Host BUS number
    Name(TBHR, 0xFF) //1:Cactus Ridge 2:Redwood Ridge 3:Falcon Ridge 4:Win Ridge will be updated
    Name(TBMV, 0xFF) // _RMV return value for Thunderbolt
    Name(RPR6, 0)
    Name(RPR7, 0)
    Name(RPR8, 0)
    Name(RPR9, 0)
    Name(RPRA, 0)
    Name(RPRB, 0)
}

Scope(\_SB)
{
    // Include OEM porting required ASL
    Include("..\\TbtOemBoard\\TbtOemPorting.asl")

	// WMI ACPI device to control TBT force power
    Device(WMTF)
    {
        // pnp0c14 is pnp id assigned to WMI mapper
        Name(_HID, "PNP0C14")
        Name(_UID, "TBFP")   
        
        Name(_WDG, Buffer() {
            // {86CCFD48-205E-4A77-9C48-2021CBEDE341}
            0x48, 0xFD, 0xCC, 0x86,
            0x5E, 0x20,
            0x77, 0x4A,
            0x9C, 0x48,
            0x20, 0x21, 0xCB, 0xED, 0xE3, 0x41,
            84, 70,    // Object Id (TF)
            1,         // Instance Count
            0x02       // Flags (WMIACPI_REGFLAG_METHOD)
        })
        
        // Set TBT force power
        // Arg2 is force power value
        Method(WMTF, 3)
        {
            CreateByteField(Arg2,0,FP)
            
            If(FP)
            {
                TBFP(1)
            }
            Else
            {
                TBFP(0)
            }						
        }
    }
}

Scope(\_GPE)
{
  // OSUP method apply TB2P<->P2TB handshake procedure 
  // with Command = OS_Up
  // Arg0 - Memory mapped IO address of RR host router upstream port
  Method(OSUP, 1)
  {
      Add(Arg0, 0x548, Local0)
      OperationRegion(PXVD,SystemMemory,Local0,0x08)
      Field(PXVD,DWordAcc, NoLock, Preserve)
      {
        TB2P, 32, 
        P2TB, 32
      }    

      Store(100, Local1)
      Store(0x0D, P2TB) // Write (OS_Up << 1) | 1 to PCIe2TBT
      While(LGreater(Local1, 0))
      {
          Store(Subtract(Local1, 1), Local1)
          Store(TB2P, Local2)
          If(LEqual(Local2, 0xFFFFFFFF))// Device gone
          {
              Return(2)
          }
          If(And(Local2, 1)) // Done
          {
              break
          }
          Sleep(50)
      }
      Store(0x00, P2TB) // Write 0 to PCIe2TBT
      Return(1)
  }

  Method(MMRP)
  {
      // Calculate Memory mapped IO address of RR host router PCIE root port
      // And put it into XXXXX

      Store(\PEMA, Local0)
      If(LLessEqual(ToInteger(TBRP), 0x08))     // SB PCIE root port
      {
          Add(Local0, 0xE0000, Local0) // RP01
          Subtract(ToInteger(\TBRP), 1, Local1)
          Multiply(Local1, 0x1000, Local1)
          Add(Local0, Local1, Local0) //RP0x
      }
      Else                          // NB PCIE root port
      {
          Add(Local0, 0x8000, Local0) //PEG0
          Subtract(ToInteger(\TBRP), 0x20, Local1)
          Multiply(Local1, 0x1000, Local1)
          Add(Local0, Local1, Local0)
      }
      Return(Local0)
  }

  // Calculate Memory mapped IO address of RR host router upstream port
  Method(MMTB)
  {
      // Calculate Memory mapped IO address of RR host router upstream port
      // And put it into XXXXX

      Store(MMRP(), Local0)
      OperationRegion(MMMM, SystemMemory, Local0, 0x1A)
      Field(MMMM, AnyAcc, NoLock, Preserve)
      {
         Offset(0x19),
         SBUS, 8
      }

      Store(SBUS, Local2)
      Store(\PEMA, Local0)
      Multiply(Local2, 0x100000, Local2)
      Add(Local0, Local2, Local0)  //TBT HR US port MMIO address
      Return(Local0)
  }

  Method(GDRP)
  {
    // Put TBT PCIE root port to D0 state

    Store(MMRP(), Local0)
    OperationRegion(RP_X, SystemMemory, Local0, 0x100)
    Field(RP_X, AnyAcc, NoLock, Preserve)
    {
        Offset(0x84),
        NBPS, 2,       // Power State of PEG slot
        Offset(0xA4),
        PSD3, 2        // Power State of SB PCIE slot
    }
    If(LLess(TBRP, 0x20)){
        Store(0, PSD3)
        Return (PSD3)
    }
    If(LGreaterEqual(TBRP, 0x20)){
        Store(0, NBPS)
        Return (NBPS)
    }
  }

  Method(RPDX, 1)
  {
    // Change TBT PCIE root port Power state via Arg0
    // Arg0 - 0: D0 Status
    //        3: D3 Status
    
    Store(MMRP(), Local0)
    OperationRegion(RP_X, SystemMemory, Local0, 0x100)
    Field(RP_X, AnyAcc, NoLock, Preserve)
    {
        Offset(0x84),
        NBPS, 2,       // Power State of PEG slot
        Offset(0xA4),
        PSD3, 2
    }
    If(LLess(TBRP, 0x20)){
        Store(Arg0, PSD3)
        Sleep(100)
    }
    If(LGreaterEqual(TBRP, 0x20)){
        Store(Arg0, NBPS)
        Sleep(100)
    }
  }

  Method(TBAC)
  {
      // Equal Intel BIOS method TSUB and WSUB
      
      Acquire(OSUM, 0xFFFF)
      Store(MMRP(), Local0)
      OperationRegion(RP_X, SystemMemory, Local0, 0x100)
      Field(RP_X, AnyAcc, NoLock, Preserve)
      {
        Offset(0x08),
        RDCC, 32,
        Offset(0x18),
        PBUS, 8,
        SBUS, 8,
        SUBS, 8,
        Offset(0x84),
        NBPS, 2,       // Power State of PEG slot
        Offset(0xA4),
        PSD3, 2
      }
      Store(0, Local1)
      While(1)
      {
        If(LAnd(LNotEqual(RDCC, 0xFFFFFFFF), LNotEqual(SBUS, 0xFF)))
        {
            If(LAnd(LLess(TBRP, 0x20), LEqual(PSD3, 0x0))){
                Break
            }
            If(LAnd(LGreaterEqual(TBRP, 0x20), LEqual(PSD3, 0x0))){
                Break
            }
        }
        Else
        {
            Add(Local1, 0x01, Local1)
            If(LGreater(Local1, 0x03E8))
            {
                P8XH(1,0x7B)
                P8XH(0,0xAC)
                Sleep(0x3E8)
                Break
            }
            Else
            {
                Sleep(0x10)
            }
        }
      }
      Release(OSUM)
  }

  Method(NTFY)
  {
    // Intel Chipset Sample code Notify Method
    Sleep(100)
    Switch(ToInteger(TBRP)) // TBT Selector
    {
        Case (1)
        {
            Notify(\_SB.PCI0.RP01,0)
        }
        Case (2)
        {
            Notify(\_SB.PCI0.RP02,0)
        }
        Case (3)
        {
            Notify(\_SB.PCI0.RP03,0)
        }
        Case (4)
        {
            Notify(\_SB.PCI0.RP04,0)
        }
        Case (5)
        {
            Notify(\_SB.PCI0.RP05,0)
        }
        Case (6)
        {
            Notify(\_SB.PCI0.RP06,0)
        }
        Case (7)
        {
            Notify(\_SB.PCI0.RP07,0)
        }
        Case (8)
        {
            Notify(\_SB.PCI0.RP08,0)
        }
        Case (0x20)
        {
            Notify(\_SB.PCI0.PEG0,0)
        }
        Case (0x21)
        {
            Notify(\_SB.PCI0.PEG1,0)
        }
        Case (0x22)
        {
            Notify(\_SB.PCI0.PEG2,0)
        }
    }
  }

  // Check for 0xFFFFFFFF in TBT Vendor/Device ID
  // And Call OSUP if true
  Method(TBFF)
  {
      // Get mapped IO address of RR host router upstream port
      Store(MMTB(), Local0) 
      OperationRegion(PXVD,SystemMemory,Local0,0x4) 
      Field(PXVD,DWordAcc, NoLock, Preserve)
      {
        VEDI, 32 // Vendor/Device ID
      }    
      
	  //Check Vendor/Device ID for 0xFFFFFFFF
      Store(VEDI, Local1)
      If(LEqual(Local1, 0xFFFFFFFF))
      {
          Return (OSUP(Local0))
      }
      Else
      {
          Return (0)
      }
  } 

  Method(OE1X)
  {
    Name(TSNE, 0xFF) //will be updated by setup menu
    
    If(LLess(OSYS,2009)) { Return() } // only support win7 or above OS

    Wait(WFEV, 0xFFFF)
    Signal(WFEV)
    TBAC()
    Acquire(OSUM, 0xFFFF)    
    If(LNotEqual(\TBHR, 0x01))// For Redwood Ridge/Falcon Ridge
    {
        Store(TBFF(), Local0)
        If(LEqual(Local0, 1))// Only HR
        {
            Sleep(16)
            Release(OSUM)
            Return ()
        }
        If(LEqual(Local0, 2)) // Disconnect
        {
            If(And(TSNE, 0x02)) // If notification is enabled call Notify
            {
                Sleep(16)
                NTFY()
            }
            P8XH(0,0x7D)
            Release(OSUM)
            Return ()
        }
    }

    If(And(TSNE, 0x01))
    {
        Store(TBSW, SSMP)
    }
    If(And(TSNE, 0x02))
    {
        NTFY()
    }
    Sleep(16)
    Release(OSUM)
  }
}

#if defined (ASL_TBT_RMV_REPORT) && (ASL_TBT_RMV_REPORT == 1)
Scope (ASL_TBT_RP_NUM.PXSX)
{
    Method(_RMV)
    {
      Return(TBMV)
    } // end _RMV
}
#endif

Scope (ASL_TBT_RP_NUM)
{
#if defined ASL_TBT_PCI0_INI_SUPPORT && ASL_TBT_PCI0_INI_SUPPORT == 1
  Method(TINI,0)
#else
  Method(_INI,0)
#endif
  {
      If(LLess(OSYS,2009)) { Return() } // only support win7 or above OS

      If(LAnd(LNotEqual(\TBHR, 0xFF), LNotEqual(\TBHR, 0x01)))// For Redwood Ridge/Falcon Ridge
      {
          Acquire(OSUM, 0xFFFF)
          P8XH(0, 0x51)     // for debug
/*
          Store(MMRP(), Local1)
          OperationRegion(RP_X, SystemMemory, Local1, 0x20)
          Field(RP_X, DWordAcc, NoLock, Preserve)
          {
            REG0, 32,
            REG1, 32,
            REG2, 32,
            REG3, 32,
            REG4, 32,
            REG5, 32,
            REG6, 32,
            REG7, 32,
          }
          Store(REG6, Local2)
          Store(0x00F0F000, REG6)
*/
          \_GPE.TBAC()
          // Get memory mapped IO address of RR host router upstream port
          Store(\_GPE.MMTB(), Local3)
          // Call OSUP
          \_GPE.OSUP(Local3)
          Release(OSUM)
      }
      Signal(WFEV)
  }

#if defined(ASL_TBT_WAK_SUPPORT) && (ASL_TBT_WAK_SUPPORT==1)
  Method(TWAK, 1)
  {
      Name(RPL1, 0)
      Name(RPL6, 0)
      Name(RPL7, 0)
      Name(RPL8, 0)
      Name(RPL9, 0)
      Name(RPLA, 0)
      Name(RPLB, 0)
      
      If(LLess(OSYS,2009)) { Return() } // only support win7 or above OS

      If(LAnd(LNotEqual(\TBHR, 0xFF), LNotEqual(\TBHR, 0x01)))// Only for Redwood Ridge/Falcon Ridge
      {
          Acquire(OSUM, 0xFFFF)
          \_GPE.TBAC()
          //Sleep(50)  // fix hang up when S3 resuming
          // Get memory mapped IO address of RR host router upstream port
          Store(\_GPE.MMRP(), Local0)
          OperationRegion(RP_X, SystemMemory, Local0, 0x34)
          Field(RP_X, DWordAcc, NoLock, Preserve)
          {
            REG0, 32,
            REG1, 32,
            REG2, 32,
            REG3, 32,
            REG4, 32,
            REG5, 32,
            REG6, 32,
            REG7, 32,
            REG8, 32,
            REG9, 32,
            REGA, 32,
            REGB, 32,
            REGC, 32,
          }
          Store(REG1, RPL1)
          Store(REG6, RPL6)
          Store(REG7, RPL7)
          Store(REG8, RPL8)
          Store(REG9, RPL9)
          Store(REGA, RPLA)
          Store(REGB, RPLB)
          Store(RPR6, REG6)
          Store(RPR7, REG7)
          Store(RPR8, REG8)
          Store(RPR9, REG9)
          Store(RPRA, REGA)
          Store(RPRB, REGB)
          Store(0x00100007, REG1)
          Store(\_GPE.GDRP(), Local2)
          \_GPE.RPDX(Zero)
          Store(\_GPE.MMTB(), Local3)
          // Call OSUP
          \_GPE.OSUP(Local3)
          // Restore TBT root port resource/bus/cmd/D state registers as before Sx entry
          Store(TBSW, SSMP)
          // Restore original register values as before calling SMI
          Store(RPL1, REG1)
          Store(RPL6, REG6)
          Store(RPL7, REG7)
          Store(RPL8, REG8)
          Store(RPL9, REG9)
          Store(RPLA, REGA)
          Store(RPLB, REGB)
          \_GPE.RPDX(Local2)
          Release(OSUM)

          // For TBT host at NB PCIE slot
          If(LGreaterEqual(ToInteger(TBRP), 0x20))
          {
              Switch(ToInteger(TBRP))
              {
                  Case (0x20)
                  {
                      Notify(\_SB.PCI0.PEG0,0)
                  }
                  Case (0x21)
                  {
                      Notify(\_SB.PCI0.PEG1,0)
                  }
                  Case (0x22)
                  {
                      Notify(\_SB.PCI0.PEG2,0)
                  }
              }
          }
      }

#if defined(ASL_TBT_S3_WAK_SMI) && (ASL_TBT_S3_WAK_SMI == 1) && (ASL_TBT_WAK_SUPPORT == 1)
      Store(Arg0,Local0)
      If(LEqual(Local0, 0x03)){
           If(ASL_TBT_RP_NUM.PDSX){
              Store(TBSW, SSMP)
              NTFY()
           }
      }
#endif
      Signal(WFEV)
  }
#endif

#if defined(ASL_TBT_PTS_SUPPORT) && (ASL_TBT_PTS_SUPPORT==1)
  Method(TPTS, 1)
  {
    If(LLess(OSYS,2009)) { Return() } // only support win7 or above OS

    If(LAnd(LNotEqual(\TBHR, 0xFF), LNotEqual(\TBHR, 0x01)))// Only for Redwood Ridge/Falcon Ridge
    {
        Acquire(OSUM, 0xFFFF)
        Store(\_GPE.MMRP(), Local0)
        OperationRegion(RP_X, SystemMemory, Local0, 0x34)
        Field(RP_X, DWordAcc, NoLock, Preserve)
        {
            REG0, 32,
            REG1, 32,
            REG2, 32,
            REG3, 32,
            REG4, 32,
            REG5, 32,
            REG6, 32,
            REG7, 32,
            REG8, 32,
            REG9, 32,
            REGA, 32,
            REGB, 32,
            REGC, 32,
        }
        Store(REG6, RPR6)
        Store(REG7, RPR7)
        Store(REG8, RPR8)
        Store(REG9, RPR9)
        Store(REGA, RPRA)
        Store(REGB, RPRB)
        Release(OSUM)
    }
#if defined(ASL_TBT_CLEAR_PME_STATUS) && (ASL_TBT_CLEAR_PME_STATUS == 1)
    If(LOr(PSPX, PMEP)){
        Store(PMEX, Local1)
        Store(0, PMEX)
        Sleep(10)
        Store(1, PSPX)
        Sleep(10)
        If(PSPX){
            Store(1, PSPX)
            Sleep(10)
        }
        Store(Local1, PMEX)
	}
#endif
    Reset(WFEV)
  }
#endif
}
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
