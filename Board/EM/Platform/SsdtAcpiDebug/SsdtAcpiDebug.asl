
DefinitionBlock (
	"AcpiDebug.aml",
	"SSDT",
	1,
	"Intel_",
	"ADebTabl",
	0x1000
  )
{
  Scope(\)
  {
    //
    // These pointers are patched during POST.
    // 
    Name(DPTR, 0x80000000) // Address of Acpi debug memory buffer, fixed up during POST
    Name(EPTR, 0x80000000) // End of Acpi debug memory buffer, fixed up during POST
    Name(CPTR, 0x80000000) // Current pointer used as an index into the buffer(starts after the buffer signature), fixed up during POST

    //
    //Use a Mutex to prevent multiple calls from simutaneously writing to the same memory.
    //
    Mutex(MMUT, 0)

    //
    // Write a string to a memory buffer
    //
    Method(MDBG,1,Serialized)
    {
        Store (Acquire(MMUT, 1000),Local0)  // save Acquire result so we can check for Mutex acquired
        If (LEqual(Local0, Zero))  // check for Mutex acquired
        {
          OperationRegion(ABLK, SystemMemory, CPTR, 16) // Operation region to allow writes to ACPI debug buffer
          Field(ABLK, ByteAcc, NoLock, Preserve) 
          {
            Offset(0x0),
            AAAA,	128  // 16 byte string or data
          }
          Store(Arg0,AAAA)  // anything past string buffer size is ignored by ACPI

          Add(CPTR,16,CPTR) // advance current pointer to next string location in memory buffer
          If (LGreaterEqual(CPTR,EPTR) ) // check for end of 64kb Acpi debug buffer
          {
            Add(DPTR,16,CPTR) // wrap around to beginning of buffer if the end has been reached
          }
          Release(MMUT)
        }
        Return(Local0) // return error code indicating whether Mutex was acquired
    }

  } // End Scope
} // End SSDT
