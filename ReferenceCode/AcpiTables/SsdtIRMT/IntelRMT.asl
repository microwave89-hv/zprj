//
// Defined as an SSDT to be able to dynamically load based on BIOS
// setup options
// 
DefinitionBlock (
  "IntelRMT.aml",
  "SSDT",
  0x01,
  "Intel",
  "IntelRMT",
  0x1000
  )
  

{
External(\ADBG, MethodObj)
External(P8XH, MethodObj) 
External(INSC, IntObj)


  Scope(\_SB)
  { 
    Device (INSD)
    {
        Name (_HID, "INT3398")
        Name (_CID, EISAID("PNP0C02"))
        Name (_UID, 0x00)

        Name (NBT1, 0) // Intel Intelr RMT Technology local variable
        // Intelr RMT Modes
        // 0: Exit Intelr RMT
        // 1: Enter Intelr RMT Active State
        // 2: Enter Intelr RMT Idle State
        // 3: Enter Intelr RMT Do Not Disturb State
        // 4: Enter Suspend

        Method(GNSC, 0, NotSerialized)
        {
        // DEBUG START //
        Store(INSC, Local0)
        P8XH(0,0xAA)
        ADBG("GNSC: ")
        ADBG(ToHexString(Local0))
        // DEBUG END //
        return (INSC)
        }

        Method(GNSM, 0, Serialized)
        {
        Store(NBT1, Local0)
        // DEBUG START //
        P8XH(0,0x71)
        ADBG("GNSM: ")
        ADBG(ToHexString(Local0))
        // DEBUG END //
        Return (Local0)
        }

        Method(SNSM, 1, Serialized)
        {
        Store(Arg0, NBT1)
        Store(NBT1, Local0)
            Switch(ToInteger(Local0))
            {
                Case (0)
                {
                ADBG("case 0: ")
                // 0: Exit Intelr RMT
                // TODO: Add platform specific code here
                }
                Case (1)
                {
                ADBG("case 1: ")
                // 1: Enter Intelr RMT Active State
                // TODO: Add platform specific code here
                }
                Case (2)
                {
                ADBG("case 2: ")
                // 2: Enter Intelr RMT Idle State
                // TODO: Add platform specific code here
                }
                Case (3)
                {
                ADBG("case 3: ")
                // 3: Enter Intelr RMT Do Not Disturb State
                // TODO: Add platform specific code here
                }
                Case (4)
                {
                ADBG("case 4: ")
                // 4: Enter Suspend
                // TODO: Add platform specific code here
                }

            }

        // DEBUG START //
        P8XH(0,0x72)
        ADBG("SNSM: ")
        ADBG(ToHexString(Local0))
        // DEBUG END //
        }

    } // Device (INSD)

  } // end \_SB scope
} // end SSDT
