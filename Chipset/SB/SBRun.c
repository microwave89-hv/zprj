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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Chipset/SB/SBRun.c 1     4/19/16 7:42a Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 4/19/16 7:42a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Chipset/SB/SBRun.c $
// 
// 1     4/19/16 7:42a Chienhsieh
// 
// 5     7/17/13 1:54a Scottyang
// [TAG]  		EIP128233
// [Category]  	Improvement
// [Description]  	Improving UEFI PXE image downloading proformance.
// [Files]  		RTC.h
// SBRun.c
// 
// 4     3/19/13 8:24a Scottyang
// [TAG]  		EIP106509
// [Category]  	Improvement
// [Description]  	3.	Improve the Intel UEFI GbE driver performance in
// IPv4 connection. 
// [Files]  		SBRun.c
// 
// 3     1/27/13 11:01p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Capsule 2.0 crash dump link function.
// [Files]  		SBPEI.c
// SBDxe.c
// SBRun.c
// 
// 2     12/20/12 9:59p Scottyang
// [TAG]         EIP77459
// [Category]    Improvement
// [Description] Update for Intel flash utility "FPT.efi" support.
// [Files]       SBRun.c
// 
// 1     2/08/12 8:24a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SBRUN.C
//
// Description: This file contains code for general Southbridge runtime 
//              protocol 
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Efi.h>
#include <Token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include "RTC.h"

// Produced Protocols
#include <Protocol\Metronome.h>
#include <Protocol\Reset.h>
#include <Protocol\RealTimeClock.h>
#include <Protocol\Timer.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

EFI_STATUS WaitForTick (
    IN EFI_METRONOME_ARCH_PROTOCOL  *This,
    IN UINT32                       TickNumber
);

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

EFI_HANDLE  mResetProtocolHandle = NULL;
static BOOLEAN gTimeOut = FALSE;
                                        // [EIP77459]>
UINT16 gTimeZone;
UINT8  gDaylight;
                                        // <[EIP77459]

EFI_RESET_SYSTEM gCallSavedIntelPointer;

// This the number of days in a month - 1. (0 Based)
UINT8 DaysInMonth[] = { 30, 27, 30, 29, 30, 29, 30, 30, 29, 30, 29, 30 };
                                        // (EIP128233)>>
#pragma pack(push, 1)
typedef struct {
    INT16 TimeZone;
    UINT8 Daylight;
    } TIME_VARIABLE;
#pragma pack(pop)

static TIME_VARIABLE CachedTimeVariable;
static BOOLEAN CachedTimeVariableValid = FALSE;
                                        // <<(EIP128233)
// GUID Definition(s)

EFI_GUID gEfiMetronomeArchProtocolGuid = EFI_METRONOME_ARCH_PROTOCOL_GUID;
EFI_GUID guidReset = EFI_RESET_ARCH_PROTOCOL_GUID;
EFI_GUID gEfiRtcArchProtocolGuid = EFI_REAL_TIME_CLOCK_ARCH_PROTOCOL_GUID;
EFI_GUID gEfiTimeVariableGuid = EFI_TIME_VARIABLE_GUID;

// Protocol Definition(s)

EFI_METRONOME_ARCH_PROTOCOL mMetronomeProtocol = {
    WaitForTick,
    1
};

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiResetSystem
//
// Description: This function is the interface for the reset function.
//              In the future, this may allow for a shared library for DXE
//              and PEI.
//
// Input:       ResetType   -   Type of reset to perform
//              ResetStatus -   System status that caused the reset.  if part
//                              of normal operation then this should be 
//                              EFI_SUCCESS, Otherwise it should reflect the
//                              state of the system that caused it
//              DataSize    -   Size in bytes of the data to be logged
//              *ResetData  -   Pointer to the data buffer that is to be
//                              logged
//
// Output:      None, Even though it should never get that far
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiResetSystem (
    IN EFI_RESET_TYPE   ResetType,
    IN EFI_STATUS       ResetStatus,
    IN UINTN            DataSize,
    IN CHAR16          *ResetData OPTIONAL
)
{
  // Add logging messages here
  // do a cold reset of the system
  if (ResetType == EfiResetWarm)
  {
    SBLib_ResetSystem (ResetType);
  }
  else
  {
    if (gCallSavedIntelPointer == NULL)
        SBLib_ResetSystem (ResetType);

    gCallSavedIntelPointer( ResetType, \
                            ResetStatus, \
                            DataSize, \
                            ResetData );
  }

  // This should not get here
  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WaitForTick
//
// Description: This function calculates the time needed to delay and then
//              calls a library function to delay that amount of time
//
// Input:       *This      - Pointer to the instance of the Metronome Arch
//                           Protocol
//              TickNumber - Number of ticks needed based off of tick period 
//                           defined in Protocol Definiton
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS WaitForTick (
    IN  EFI_METRONOME_ARCH_PROTOCOL     *This,
    IN  UINT32                          TickNumber )
{
    EFI_STATUS          Status;
    UINT32              TotalTime;

    // Manipulate TickNumber into a valid value for the library function call
    // the Current Resolution is 10us.
    // The Library uses Microseconds to count delayed time.
    TotalTime = (TickNumber * This->TickPeriod) / 10;

    // Make Library Function call here
    Status = CountTime( TotalTime, PM_BASE_ADDRESS );

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   DecToBCD
//
// Description: This function converts data from DEC to BCD format
//
// Input:       UINT8 Dec - Value to be converted
//
// Output:      UINT8 - Result of conversion
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 DecToBCD (
    IN UINT8    Dec )
{
    UINT8 FirstDigit = Dec % 10;
    UINT8 SecondDigit = Dec / 10;

    // Only for 2 digit BCD.
    return (SecondDigit << 4) + FirstDigit;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   BCDToDec
//
// Description: This function converts data from BCD to DEC format
//
// Input:       UINT8 Bcd - Value to be converted
//
// Output:      UINT8 - Result of conversion
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 BCDToDec (
    IN UINT8    Bcd )
{
    UINT8 FirstDigit = Bcd & 0xf;
    UINT8 SecondDigit = Bcd >> 4;;

    // Only for 2 digit BCD.
    return SecondDigit * 10  + FirstDigit;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReadRtcIndex
//
// Description: Read the RTC value at the given Index.
//
// Input:       Index - RTC Index
//
// Output:      RTC Value read from the provided Index
//
// Notes:       Here is the control flow of this function:
//              1. Read port 0x70 (RTC Index Register) to get bit 7.
//                 Bit 7 is the NMI bit-it should not be changed.
//              2. Set Index with the NMI bit setting.
//              3. Output 0x70 with the Index and NMI bit setting.
//              4. Read 0x71 for Data. Getting Dec when appropriate.
//              5. Return the Data.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 ReadRtcIndex (
    IN UINT8        Index )
{
    volatile UINT8  Value;
    BOOLEAN         IntState = CPULib_GetInterruptState();

    CPULib_DisableInterrupt();

    IoWrite8(CMOS_IO_INDEX_BACKDOOR, Index);
    Value = IoRead8(CMOS_IO_DATA_BACKDOOR); // Read register.

    if (IntState) CPULib_EnableInterrupt();

    if ((Index <= RTC_YEAR_REG) || (Index == ACPI_CENTURY_CMOS))
        Value = BCDToDec(Value);  

    return (UINT8)Value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteRtcIndex
//
// Description: Write the RTC value at the given Index.
//
// Input:       Index - RTC Index
//              Value - Value to write
//
// Output:      None
//
// Notes:       Here is the control flow of this function:
//              1. Read port 0x70 (RTC Index Register) to get bit 7.
//                 Bit 7 is the NMI bit-it should not be changed.
//              2. Set Index with the NMI bit setting.
//              3. Output 0x70 with the Index. Switch to BCD when needed.
//              4. Write the data to 0x71.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteRtcIndex (
    IN UINT8        Index,
    IN UINT8        Value )
{
    BOOLEAN IntState = CPULib_GetInterruptState();

    if ((Index <= RTC_YEAR_REG) || (Index == ACPI_CENTURY_CMOS))
        Value = DecToBCD(Value);

    CPULib_DisableInterrupt();

    IoWrite8(CMOS_IO_INDEX_BACKDOOR, Index);
    IoWrite8(CMOS_IO_DATA_BACKDOOR, Value); // Write Register.

    if (IntState) CPULib_EnableInterrupt();

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitRtc
//
// Description: This function initializes RTC
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitRtc (VOID)
{
    WriteRtcIndex(RTC_REG_B_INDEX, 0x82);
    WriteRtcIndex(RTC_REG_A_INDEX, 0x26);
    ReadRtcIndex(RTC_REG_C_INDEX);
    ReadRtcIndex(RTC_REG_D_INDEX);
    WriteRtcIndex(RTC_REG_B_INDEX, 0x02);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetUpdate
//
// Description: Enables Disables RTC Date and Time update cicles.
//
// Input:       Enable - TRUE or FALSE to Enable\Disabe RTC Update. 
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SetUpdate (
    IN BOOLEAN      Enable )
{
    RTC_REG_B       RegB;
    UINT8           Set = (Enable) ? 0 : 1;

    RegB.REG_B = ReadRtcIndex(RTC_REG_B_INDEX);
    if (RegB.Set != Set) {
        RegB.Set = Set;
        WriteRtcIndex(RTC_REG_B_INDEX, RegB.REG_B);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckUpdateCmplete
//
// Description: Check if RTC Date and Time update in progress and waits till 
//              it's over.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CheckUpdateCmplete (VOID)
{
    volatile RTC_REG_A  RegA;
    UINTN               TimeOut = 0;

    RegA.REG_A = ReadRtcIndex(RTC_REG_A_INDEX);
    while (RegA.UpdInProgr) {
        RegA.REG_A = ReadRtcIndex(RTC_REG_A_INDEX);
        TimeOut++;
        if (TimeOut >= 0x0fffff) {
            gTimeOut = TRUE;
            return;
        }
    }

    gTimeOut = FALSE;
}

BOOLEAN IsLeapYear (
    IN EFI_TIME     *Time )
{
    if (Time->Year % 4 == 0) {
        if (Time->Year % 100 == 0) {
            if (Time->Year % 400 == 0) {
                return TRUE;
            } else {
                return FALSE;
            }
        } else {
            return TRUE;
        }
    } else {
        return FALSE;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   VerifyTime
//
// Description: This routine verifies if time and data if needed, before
//              setting the RTC
//
// Input:       *Time - Time to verify with
//
// Output:      TRUE if valid time and date
//
// Notes:       Here is the control flow of this function:
//              1. Decrease month and date to change to 0-base
//              2. Validate Year, Month and Day. If invalid, return FALSE.
//              3. Validate Hour, Minute and Second. If invalid, return FALSE.
//              4. Return True.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN VerifyTime (
    IN EFI_TIME         *Time )
{
    // Always check these to satisfy EFI compliancy test even for setting
    // wake-up time.
    UINT8               Month = Time->Month - 1;
    UINT8               Day = Time->Day - 1;

    if ((Time->Year < EARLIEST_YEAR) || (Time->Year > 9999)) return FALSE;
    if (Month > 11) return FALSE;             // 0 based month
    if ((Month != 1) || (!IsLeapYear(Time))) { // Not leap year or not February.
        // All values already adjusted for 0 based. 
        if (Day > DaysInMonth[Month]) return FALSE; 
    } else {
        if (Day > 28) return FALSE; // February
    }

    if (Time->Hour > 23) return FALSE;
    if (Time->Minute > 59) return FALSE;
    if (Time->Second > 59) return FALSE;

    // Check these to satisfy EFI compliancy test.
    if (Time->Nanosecond > 999999999) return FALSE; // 999,999,999
    if (Time->TimeZone < -1440) return FALSE;
    if (Time->TimeZone > 1440 && Time->TimeZone != EFI_UNSPECIFIED_TIMEZONE)
        return FALSE;

    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetDayOfTheWeek
//
// Description: Returns an index that represents the day of the week of the
//              date passed in
//
// Input:       *Time - Pointer to EFI_TIME structure
//
// Output:      Returns the index to the day of the week. 0 = Sunday,
//              1 = Monday ... 6 = Saturday
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 GetDayOfTheWeek (
    IN EFI_TIME         *Time )
{
    UINT16      a;
    UINT16      m;
    UINT16      d;
    UINT16      y;

    a = (14 - Time->Month) / 12;
    y = Time->Year - a;
    m = Time->Month + 12 * a - 2;
    d = (Time->Day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;

    return (UINT8)d;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckRtc
//
// Description: Check if RTC Mode and Format have appropriate values and sets
//              them if necessary
//
// Input:       Set - if true, force Rtc to 24 hour mode and binary format. 
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - RTC mode and format have appropriate values.
//                  EFI_DEVICE_ERROR - RTC mode and/or format are invalid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckRtc ( 
    IN BOOLEAN          Set )
{
    RTC_REG_B   RegB;

    // Check RTC Conditions and stuff
    RegB.REG_B = ReadRtcIndex(RTC_REG_B_INDEX);
    if((RegB.Mode == 0) || (RegB.Format == 1)) {
        if (Set) {
            RegB.Mode = 1; // 1 - 24 hour mode
            RegB.Format = 0; // 0 - BCD Format
            WriteRtcIndex(RTC_REG_B_INDEX, RegB.REG_B);
        } else {
            return EFI_DEVICE_ERROR;    
        }
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiGetTime
//
// Description: Return the current date and time
//
// Input:       *Time         - Current time filled in EFI_TIME structure
//              *Capabilities - Time capabilities (OPTIONAL)
//
// Output:      EFI_SUCCESS
//                  EFI_INVALID_PARAMETER - A NULL Time. 
//                  EFI_DEVICE_ERROR - RTC mode and/or format are invalid
//                  EFI_SUCCESS - Read the current date and time successfully.
//                                          
//
// Notes:       Here is the control flow of this function:
//              1. Read the original time format 12/24 hours and BCD/binary.
//              2. Set the format to 24 hrs and binary.
//              3. Read the 2 digit year.
//              4. Add either 1900 or 2000, so the year is between 1998 - 2097
//              5. Read the month, day, hour, minute, second.
//              6. Set the nanosecond to 0.
//              7. Set the time to zone to unspecified.
//              8. Set daylight savings value to 0.
//              9. Restore the original time format.
//              10.Set Capabilities with 1 sec Resolution, 0 Accuracy
//                 (Unknown), and False SetsToZero. 
//              11.Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiGetTime (
    OUT EFI_TIME                *Time,
    OUT EFI_TIME_CAPABILITIES   *Capabilities OPTIONAL )
{
    EFI_STATUS          Status;
    UINT8               Year;
    BOOLEAN             IntState;
    BOOLEAN             SmiState;
    UINTN               TimeVarSize = sizeof(TIME_VARIABLE);
    UINT8               Buffer8;        // [EIP77459]

    if (Time == NULL) return EFI_INVALID_PARAMETER;

    // Check RTC Conditions (24h Mode and BCD is ON)
    Status = CheckRtc(FALSE);  
    if (EFI_ERROR(Status)) return Status;

    // Get SMI State and disable it
    SmiState = SbLib_GetSmiState();
    SbLib_SmiDisable();    
    // Get INTERRUPT State and disable it
    IntState = CPULib_GetInterruptState();
    CPULib_DisableInterrupt();

    // Wait till RTC is safe to read,
    CheckUpdateCmplete();
    if (gTimeOut) InitRtc();
  
    // After control comes back, we will have 488 u's to read data.
    Year = ReadRtcIndex(RTC_YEAR_REG);
    Time->Month = ReadRtcIndex(RTC_MONTH_REG);
    Time->Day = ReadRtcIndex(RTC_DAY_OF_MONTH_REG);
    Time->Hour = ReadRtcIndex(RTC_HOURS_REG);
    Time->Minute = ReadRtcIndex(RTC_MINUTES_REG);
    Time->Second = ReadRtcIndex(RTC_SECONDS_REG);

    // Restore SMIs and INTERRUPT State
    if(IntState) CPULib_EnableInterrupt();
    if(SmiState) SbLib_SmiEnable();

    // This Register is not affected by UIP bit so read it very last.
    // If RTC Year only 1 digit, EFI spec says years rang is 1998 - 2097
    Time->Year = ReadRtcIndex(ACPI_CENTURY_CMOS) * 100 + Year;

    Time->Nanosecond= 0;

                                        // [EIP77459]>
    // Save BIOSWE bit (B0:D31:F0 Reg#DCh[0])
    Buffer8 = READ_PCI8_SB(SB_REG_BIOS_CNTL);
                                        // (EIP128233)>>
    if(CachedTimeVariableValid && (Buffer8 & BIT00) != 0) {
        Time->TimeZone  = CachedTimeVariable.TimeZone;
        Time->Daylight  = CachedTimeVariable.Daylight;
    } else {
        Status = pRS->GetVariable( L"EfiTime", \
                                   &gEfiTimeVariableGuid, \
                                   NULL, \
                                   &TimeVarSize, \
                                   &CachedTimeVariable );
        if (EFI_ERROR(Status)) {
            CachedTimeVariable.TimeZone = EFI_UNSPECIFIED_TIMEZONE;
            CachedTimeVariable.Daylight = 0;
        }

        Time->TimeZone  = CachedTimeVariable.TimeZone;
        Time->Daylight  = CachedTimeVariable.Daylight;
        CachedTimeVariableValid = TRUE;
    }

    // Restore BIOSWE bit (B0:D31:F0 Reg#DCh[0])
    WRITE_PCI8_SB(SB_REG_BIOS_CNTL, Buffer8);
                                        // <[EIP77459]
                                        // <<(EIP128233)
    if (Capabilities != NULL) {
        Capabilities->Resolution = 1;
        Capabilities->Accuracy = 0;
        Capabilities->SetsToZero = 0;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSetTime
//
// Description: Sets the RTC time
//
// Input:       *Time - Time to set
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - Time is Set
//                  EFI_INVALID_PARAMETER - Time to Set is not valid.
//
// Notes:       Here is the control flow of this function:
//              1. Read the original time format 12/24 hours and BCD/binary.
//              2. Set the format to 24 hrs and binary.
//              3. Verify the time to set. If it is an invalid time,
//                 restore the time format and return EFI_INVALID_PARAMETER.
//              4. Change the 4 digit year to a 2 digit year.
//              5. Stop the RTC time.
//              6. Store time and data on the RTC.
//              7. Read the month, day, hour, minute, second.
//              8. Start the RTC time.
//              9. Restore the original time format.
//              10.Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSetTime (
    IN EFI_TIME     *Time )
{

    EFI_STATUS      Status = EFI_SUCCESS;
    UINTN           TimeVarSize = sizeof(TIME_VARIABLE);

    // Check RTC Conditions and stuff
    CheckRtc(TRUE);  

    if (Time == NULL) return EFI_INVALID_PARAMETER;
    if (!VerifyTime(Time)) return EFI_INVALID_PARAMETER;

    SetUpdate(FALSE);
    WriteRtcIndex(ACPI_CENTURY_CMOS, Time->Year / 100);
    WriteRtcIndex(RTC_YEAR_REG, Time->Year % 100);
    WriteRtcIndex(RTC_MONTH_REG, Time->Month);
    WriteRtcIndex(RTC_DAY_OF_MONTH_REG, Time->Day);
    WriteRtcIndex(RTC_DAY_OF_WEEK_REG, GetDayOfTheWeek(Time) + 1);

    WriteRtcIndex(RTC_HOURS_REG, Time->Hour);
    WriteRtcIndex(RTC_MINUTES_REG, Time->Minute);
    WriteRtcIndex(RTC_SECONDS_REG, Time->Second);
    SetUpdate(TRUE);

                                        // (EIP128233)>>
    if(CachedTimeVariableValid && 
       CachedTimeVariable.TimeZone == Time->TimeZone &&
       CachedTimeVariable.Daylight == Time->Daylight)
        return EFI_SUCCESS;

    CachedTimeVariable.TimeZone  = Time->TimeZone;
    CachedTimeVariable.Daylight  = Time->Daylight;

    Status = pRS->SetVariable(
                        L"EfiTime",
                        &gEfiTimeVariableGuid,
                        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                        sizeof(TIME_VARIABLE),
                        &CachedTimeVariable
                        );
    if(!EFI_ERROR(Status))
        CachedTimeVariableValid = TRUE;
                                        // <<(EIP128233)
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiGetWakeupTime
//
// Description: Read the wake time. Read the status if it is enabled or
//              if the system has woken up.
//
// Input:       *Enabled - Flag indicating the validity of wakeup time
//              *Pending - Check if wake up time has expired.
//              *Time    - Current wake up time setting
//
// Output:      EF_STATUS
//                  EFI_SUCCESS - Read the wake time successfully.
//                  EFI_INVALID_PARAMETER - Invalid input parameters
//                  EFI_DEVICE_ERROR - RTC mode and/or format are invalid
//
// Notes:       Here is the control flow of this function:
//              1. Read the original time format 12/24 hours and BCD/binary.
//              2. Set the format to 24 hrs and binary.
//              3. Read the status if the wake up time is enabled or if it has expired.
//              4. Set the wakeup time.
//              5. Restore the original time format.
//              6. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiGetWakeupTime (
    OUT BOOLEAN             *Enabled,
    OUT BOOLEAN             *Pending,
    OUT EFI_TIME            *Time )
{
    EFI_STATUS              Status;
    BOOLEAN                 IntState;
    BOOLEAN                 SmiState;
    RTC_REG_B               RegB;
    RTC_REG_C               RegC;
#if ACPI_ALARM_DAY_CMOS
    RTC_DATE_ALARM_REG      RegDateAlarm;
#endif
#if ACPI_ALARM_MONTH_CMOS
    RTC_MONTH_ALARM_REG     RegMonthAlarm;
#endif

    if (!Enabled || !Pending || !Time) return EFI_INVALID_PARAMETER;

    // Check RTC Conditions (24h Mode and BCD is ON)
    Status = CheckRtc(FALSE);  
    if (EFI_ERROR(Status)) return Status;

    // Get SMI State and disable it
    SmiState = SbLib_GetSmiState();
    SbLib_SmiDisable();    
    // Get INTERRUPT State and disable it
    IntState = CPULib_GetInterruptState();
    CPULib_DisableInterrupt();

    // Wait till RTC is safe to read,
    CheckUpdateCmplete();
    if (gTimeOut) InitRtc();

    Time->Hour = ReadRtcIndex(RTC_HOURS_ALARM_REG);
    Time->Minute = ReadRtcIndex(RTC_MINUTES_ALARM_REG);
    Time->Second = ReadRtcIndex(RTC_SECONDS_ALARM_REG);

    // Restore SMIs and INTERRUPT State
    if (IntState) CPULib_EnableInterrupt();
    if (SmiState) SbLib_SmiEnable();

#if ACPI_ALARM_DAY_CMOS
    RegDateAlarm.REG_DATE_ALARM = ReadRtcIndex(ACPI_ALARM_DAY_CMOS);
    Time->Day = BCDToDec(RegDateAlarm.DateAlarm);
#else
    Time->Day = 0;
#endif

#if ACPI_ALARM_MONTH_CMOS
    RegMonthAlarm.REG_MONTH_ALARM = ReadRtcIndex(ACPI_ALARM_MONTH_CMOS);
    Time->Month = BCDToDec(RegMonthAlarm.MonthAlarm);
#else
    Time->Month = 0;
#endif

    RegB.REG_B = ReadRtcIndex(RTC_REG_B_INDEX);
    RegC.REG_C = ReadRtcIndex(RTC_REG_C_INDEX);


    *Enabled = (RegB.AlarmInt == 1) ? TRUE : FALSE;
    *Pending = (RegC.AlarmFlag == 1) ? TRUE : FALSE;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSetWakeupTime
//
// Description: Enable/disable and set wakeup time
//
// Input:       Enable - Flag indicating whether to enable/disble the time
//              *Time  - Time to set
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - Wakeup time is Set and/or Enabled/Disabled. 
//                  EFI_DEVICE_ERROR - RTC mode and/or format are invalid
//                  EFI_INVALID_PARAMETER - Invalid time or enabling with a
//                                          NULL Time.
//
// Notes:       Here is the control flow of this function:
//              1. Read the original time format 12/24 hours and BCD/binary.
//              2. If Time is not NULL,
//                  a. Verify the wakeup time to set. If it is an invalid
//                     time, restore the time format and
//                     return EFI_INVALID_PARAMETER.  
//                  b. Set the wakeup time.
//              3. If Time is NULL and Enable is true, restore original
//                 time format and return EFI_INVALID_PARAMETER.
//              4. Enable/Disable wakeup.
//              5. Restore the original time format.
//              6. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSetWakeupTime (
    IN BOOLEAN              Enable,
    IN EFI_TIME             *Time OPTIONAL )
{

    EFI_STATUS              Status;    
    RTC_REG_B               RegB;
    RTC_REG_C               RegC;
#if ACPI_ALARM_DAY_CMOS
    RTC_DATE_ALARM_REG      RegDateAlarm;
#endif
#if ACPI_ALARM_MONTH_CMOS
    RTC_MONTH_ALARM_REG     RegMonthAlarm;
#endif

    // Check RTC Conditions (24h Mode and BCD is ON)
    Status = CheckRtc(FALSE);  
    if(EFI_ERROR(Status)) return Status;

    if (Time != NULL) {
        if (!VerifyTime(Time)) return EFI_INVALID_PARAMETER;
    } else {
        if (Enable) return EFI_INVALID_PARAMETER;
    }

    RegB.REG_B = ReadRtcIndex(RTC_REG_B_INDEX);
    
    SetUpdate(FALSE);
    if (Time != NULL) {
        WriteRtcIndex(RTC_HOURS_ALARM_REG, Time->Hour);
        WriteRtcIndex(RTC_MINUTES_ALARM_REG, Time->Minute);
        WriteRtcIndex(RTC_SECONDS_ALARM_REG, Time->Second);
#if ACPI_ALARM_DAY_CMOS
        // Day == 0 means don't care
        RegDateAlarm.DateAlarm = DecToBCD(Time->Day);
        WriteRtcIndex(ACPI_ALARM_DAY_CMOS, RegDateAlarm.REG_DATE_ALARM);
#endif
#if ACPI_ALARM_MONTH_CMOS
        // Month == 0 means don't care
        RegMonthAlarm.MonthAlarm = DecToBCD(Time->Month);
        WriteRtcIndex(ACPI_ALARM_MONTH_CMOS, RegMonthAlarm.REG_MONTH_ALARM);
#endif
    }

    // Clear Alarm Flag
    RegC.REG_C = ReadRtcIndex(RTC_REG_C_INDEX);

    // Set Enable/Disable
    RegB.AlarmInt = (Enable) ? 1 : 0;
    WriteRtcIndex(RTC_REG_B_INDEX, RegB.REG_B);
    
    SetUpdate(TRUE);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SaveIntelResetPointer
//
// Description:
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SaveIntelResetPointer (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
    gCallSavedIntelPointer = pRS->ResetSystem;
    pRS->ResetSystem = EfiResetSystem;

    pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBRun_Init
//
// Description: This function is the entry point for this DXE. This function
//              installs the runtime services related to SB
//
// Input:       ImageHandle - Image handle
//              SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - All the protocol interfaces were installed.
//                  EFI_ALREADY_STARTED - A Device Path instance was passed
//                                        in that is already present in the
//                                        handle database.
//                  EFI_OUT_OF_RESOURCES - There was not enough memory in
//                                         pool to install all the protocols.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBRun_Init (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS              Status = EFI_SUCCESS;
    EFI_TIME                Time;
    EFI_TIME                NewTime;
    EFI_HANDLE              Handle = NULL;
    UINT8                   PM2 = READ_PCI8_SB(SB_REG_GEN_PMCON_2);
    UINT8                   PM3 = READ_PCI8_SB(SB_REG_GEN_PMCON_3);
    RTC_REG_D               RegD;
    BOOLEAN                 RtcLostPower = FALSE;

    InitAmiRuntimeLib(ImageHandle, SystemTable, NULL, NULL);

    PROGRESS_CODE(DXE_SBRUN_INIT);

    // CspLib PM Specific function to check and Report 
    // CMOS Battary and Power Supply Power loss/failure
    CspLibCheckPowerLoss();

    if(PM3 & BIT02) {
      // Clear RTC_PWR_STS.
      PM3 &= ~BIT02;
      RtcLostPower = TRUE;
    }
    //Write back Cleared Statuses
    WRITE_PCI8_SB(SB_REG_GEN_PMCON_2, PM2);
    WRITE_PCI8_SB(SB_REG_GEN_PMCON_3, PM3);

    RegD.REG_D = ReadRtcIndex(RTC_REG_D_INDEX);
    if (RegD.DataValid == 0)
      RtcLostPower = TRUE;

    if (RtcLostPower) {
      ERROR_CODE(DXE_SB_BAD_BATTERY, EFI_ERROR_MAJOR);
      InitRtc();
    }


    // MakeSure Mode, Format and REG_A is OK
    CheckRtc(TRUE);

    Status = EfiGetTime(&Time, NULL);
    if (EFI_ERROR(Status) || !VerifyTime(&Time)) {
        ERROR_CODE(GENERIC_BAD_DATE_TIME_ERROR,  EFI_ERROR_MINOR);

        TRACE((TRACE_ALWAYS, "\n\nTime: %d/%d/%d  %d:%d:%d\n",
            Time.Month,
            Time.Day,
            Time.Year,
            Time.Hour,
            Time.Minute,
            Time.Second
        ));

        TRACE((TRACE_ALWAYS, "Nanosecond: %d TimeZone: %d\n\n\n",
            Time.Nanosecond,
            Time.TimeZone
        ));

        // if Time is invalid the battery probably has been removed
        // Let's setup RTC_REG_A just in case...
        WriteRtcIndex(RTC_REG_A_INDEX, 0x26);

        // Check to see what part of EFI_TIME was wrong.
        // reset unrelated to RTC fields.
        Time.TimeZone = EFI_UNSPECIFIED_TIMEZONE; 
        Time.Daylight = 0;
        Time.Nanosecond = 0;

        NewTime = Time;

        NewTime.Hour = 0;
        NewTime.Minute = 0;
        NewTime.Second = 0;
        
        if (VerifyTime(&NewTime)) {
            // if we here that means Time was wrong
            Time.Hour = 0;
            Time.Minute = 0;
            Time.Second = 0;
        } else {
            // if we here that means Date was wrong           
            Time.Month = DEFAULT_MONTH;
            Time.Day = DEFAULT_DAY;
            Time.Year = DEFAULT_YEAR;
        }

        // Here is the situation when both Time and Date is Incorrect.
        if (!VerifyTime(&Time)) {
            Time.Hour = 0;
            Time.Minute = 0;
            Time.Second = 0;
            Time.Month=DEFAULT_MONTH;
            Time.Day=DEFAULT_DAY;
            Time.Year=DEFAULT_YEAR;
        }    

        TRACE((TRACE_ALWAYS, "Reseting Date and Time to: %d/%d/%d %d:%d:%d\n",
            Time.Month,
            Time.Day,
            Time.Year,
            Time.Hour,
            Time.Minute,
            Time.Second
        ));
        EfiSetTime(&Time);
    }

    // Install runtime services
    pRS->ResetSystem = EfiResetSystem;

    gCallSavedIntelPointer = NULL;

    pRS->GetTime = EfiGetTime;
    pRS->SetTime = EfiSetTime;
    pRS->GetWakeupTime = EfiGetWakeupTime;
    pRS->SetWakeupTime = EfiSetWakeupTime;

    Status = pBS->InstallProtocolInterface( &ImageHandle, \
                                            &gEfiMetronomeArchProtocolGuid, \
                                            EFI_NATIVE_INTERFACE, \
                                            &mMetronomeProtocol );
    ASSERT_EFI_ERROR(Status);
{
    EFI_EVENT         Event = NULL;
    VOID              *Registration = NULL;

    Status = RegisterProtocolCallback( &gEfiResetArchProtocolGuid,\
                                       SaveIntelResetPointer,\
                                       NULL,\
                                       &Event,\
                                       &Registration );
    ASSERT_EFI_ERROR(Status);
}

    // This protocol is to notify core that the Runtime Table has been
    // updated, so it can update the runtime table CRC.
    return pBS->InstallMultipleProtocolInterfaces( &Handle, \
                                                   &gEfiRtcArchProtocolGuid, \
                                                   NULL, \
                                                   NULL );
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
