//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/Runtime/TimeAndReset.C 10    11/17/10 4:44p Felixp $
//
// $Revision: 10 $
//
// $Date: 11/17/10 4:44p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Runtime/TimeAndReset.C $
// 
// 10    11/17/10 4:44p Felixp
// Support for reset type override is added.
// 
// 9     9/07/10 11:07p Felixp
// 
// 8     9/02/10 4:49p Felixp
// Enhancement: RTC driver is updated to use InitAmiRuntimeLib function. 
// The is safer that direct use of pRS->ConvertPointer since by the time
// driver's
// virtual address change callback is invoked, pRS may have already been
// virtualized.
// 
// 7     2/01/10 11:55a Felixp
// Bug fix in EfiSetTime function. The timer zone variable was created
// with the wrong size.
// 
// 6     7/10/09 8:14a Felixp
// 
// 4     6/24/09 4:25p Robert
// updated comments, copyright and some coding standard issues
// 
// 1     5/22/09 1:29p Felixp
// RTC and Reset architectural protocols
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	TimeAndReset.C
//
// Description:	
//  This file contains implementation of Time and Reset Runtime Services
//
//<AMI_FHDR_END>
//**********************************************************************

//======================================================================
// Module specific Includes
#include <token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>

//======================================================================
// Produced Protocols
#include <Protocol/Reset.h>
#include <Protocol/RealTimeClock.h>		
#include <Protocol/Timer.h>

/****************************** RTC Types and Constants *******************/
//----------------------------------------------------------------------
//Define Dallas DS12C887 Real Time Clock INDEX and DATA registers
//----------------------------------------------------------------------
#define RTC_INDEX_REG       0x70
#define RTC_DATA_REG        0x71

//----------------------------------------------------------------------
//Define Internal Registers for Dallas DS12C887 Real Time Clock
//----------------------------------------------------------------------
#define RTC_SECONDS_REG         0x00    // R/W  Range 0..59
#define RTC_SECONDS_ALARM_REG   0x01    // R/W  Range 0..59
#define RTC_MINUTES_REG         0x02    // R/W  Range 0..59
#define RTC_MINUTES_ALARM_REG   0x03    // R/W  Range 0..59
#define RTC_HOURS_REG           0x04    // R/W  Range 1..12
                                        // or 0..23 Bit 7 is AM/PM
#define RTC_HOURS_ALARM_REG     0x05    // R/W  Range 1..12
                                        // or 0..23 Bit 7 is AM/PM
#define RTC_DAY_OF_WEEK_REG     0x06    // R/W  Range 1..7
#define RTC_DAY_OF_MONTH_REG    0x07    // R/W  Range 1..31
#define RTC_MONTH_REG           0x08    // R/W  Range 1..12
#define RTC_YEAR_REG            0x09    // R/W  Range 0..99
#define RTC_REG_A_INDEX         0x0a    // R/W[0..6]  R0[7]
#define RTC_REG_B_INDEX         0x0b    // R/W
#define RTC_REG_C_INDEX         0x0c    // RO
#define RTC_REG_D_INDEX         0x0d    // RO
//Defined in ACPI.sdl
//#define RTC_CENTURY_BYTE        50    // R/W  Range 19..20 Bit 8 is R/W

#define RTC_NMI_MASK            0x80

#define AMI_RESET_TYPE_VARIABLE_GUID \
    {0x308DD02C, 0x092B, 0x4123, 0xA2, 0xAF, 0x3E, 0xF4, 0x44, 0x0A, 0x6B, 0x4A}
//----------------------------------------------------------------------
//Registers A..D Bit definitions
//----------------------------------------------------------------------
#pragma pack(push,1)

//----------------------------------------------------------------------
// Register A
//----------------------------------------------------------------------
typedef union {
  UINT8       REG_A;
  struct {
    UINT8   RateSel     : 4;
    UINT8   Divisor     : 3;
    UINT8   UpdInProgr  : 1;
  };
} RTC_REG_A;

//----------------------------------------------------------------------
// Register B
//----------------------------------------------------------------------
typedef union {
  UINT8       REG_B;
  struct {
      UINT8   DaylightSav : 1;    // 0 - Daylight saving disabled
                                  // 1 - Daylight savings enabled
      UINT8   Mode        : 1;    // 0 - 12 hour mode
                                  // 1 - 24 hour mode
      UINT8   Format      : 1;    // 0 - BCD Format
                                  // 1 - Binary Format
      UINT8   SquareWave  : 1;    // 0 - Disable SQWE output
                                  // 1 - Enable SQWE output
      UINT8   UpdateInt   : 1;    // 0 - Update INT disabled
                                  // 1 - Update INT enabled
      UINT8   AlarmInt    : 1;    // 0 - Alarm INT disabled
                                  // 1 - Alarm INT Enabled
      UINT8   PeriodicInt : 1;    // 0 - Periodic INT disabled
                                  // 1 - Periodic INT Enabled
      UINT8   Set         : 1;    // 0 - Normal operation.
                                  // 1 - Updates inhibited
  };
} RTC_REG_B;

//----------------------------------------------------------------------
// Register C
//----------------------------------------------------------------------
typedef union {
  UINT8       REG_C;
  struct {
    UINT8 Reserved      : 4;    // Read as zero.  Can not be written.
    UINT8 UpdEndFlag    : 1;    // Update End Interrupt Flag
    UINT8 AlarmFlag     : 1;    // Alarm Interrupt Flag
    UINT8 PeriodicFlag  : 1;    // Periodic Interrupt Flag
    UINT8 IrqFlag       : 1;    // Iterrupt Request Flag =
                                //              PF & PIE | AF & AIE | UF & UIE
  };
} RTC_REG_C;

//----------------------------------------------------------------------
// Register D
//----------------------------------------------------------------------
typedef union {
    UINT8       REG_D;
    struct {
		UINT8 DateAlarm		: 6;
		UINT8 Reserved		: 1;	// Read as zero.  Can not be written.
        UINT8 DataValid     : 1;    // Valid RAM and Time
    };
} RTC_REG_D;

#pragma pack(pop)
/*********************** End of RTC Types and Constants *******************/


//===========================================================================
// Time Variable GUID Definition
#define EFI_TIME_VARIABLE_GUID \
    {0x9d0da369, 0x540b, 0x46f8, 0x85, 0xa0, 0x2b, 0x5f, 0x2c, 0x30, 0x1e, 0x15}

//===========================================================================
//			Variable Declaration
static BOOLEAN  gTimeOut = FALSE;

// GUID Definitions
EFI_GUID    gEfiTimeVariableGuid            = EFI_TIME_VARIABLE_GUID;

//This the number of days in a month - 1. (0 Based)
UINT8		DaysInMonth[] = {30, 27, 30, 29, 30, 29, 30, 30, 29, 30, 29, 30};

//===========================================================================
// UEFI Time Variable Type definition
#pragma pack(1)
typedef struct {
    INT16 TimeZone;
    UINT8 Daylight;
    } TIME_VARIABLE;
#pragma pack()

//===========================================================================
// Function Declarations
VOID DummyFunction(IN EFI_EVENT Event, IN VOID *Context);

//===========================================================================
// Function Definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EfiResetSystem
//
// Description:	
//  This function is the interface for the reset function.
//
// Input:		
//  IN EFI_RESET_TYPE ResetType - Type of reset to perform
//  IN EFI_STATUS ResetStatus - System status that caused the reset.  if part of normal operation 
//                              then this should be EFI_SUCCESS, Otherwise it should reflect the 
//                              state of the system that caused it
//  IN UINTN DataSize - Size in bytes of the data to be logged
//  IN CHAR16 *ResetData - Pointer to the data buffer that is to be logged - OPTIONAL
//
// Output:		
//  EFI_DEVICE_ERROR - Even though it should never get that far
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
EfiResetSystem (
	IN EFI_RESET_TYPE	ResetType,
	IN EFI_STATUS    	ResetStatus,
	IN UINTN         	DataSize,
	IN CHAR16        	*ResetData OPTIONAL
){
    static EFI_GUID AmiResetTypeVariableGuid = AMI_RESET_TYPE_VARIABLE_GUID;
    if (!EfiAtRuntime()){
        EFI_EVENT Event;
        UINT32 OverrideResetType;
        UINTN Size = sizeof(UINT32);
        EFI_STATUS Status;

        pBS->CreateEventEx(
            0, TPL_CALLBACK, DummyFunction,
            NULL, &AmiResetTypeVariableGuid, &Event
        );
        pBS->SignalEvent(Event);
        pBS->CloseEvent(Event);
        Status = pRS->GetVariable(
            L"CspResetType", &AmiResetTypeVariableGuid, NULL,
            &Size, &OverrideResetType
        );
        if (!EFI_ERROR(Status)) ResetType = OverrideResetType;
    }
	SBLib_ResetSystem (ResetType);
    ASSERT(FALSE);
	return EFI_DEVICE_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DecToBCD
//
// Description:	
//  This function converts data from DEC to BCD format
//
// Input:		
//  UINT8 DEC - value to be converted
//
// Output:		
//  UINT8 - result of conversion
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 DecToBCD(UINT8 Dec)
{
	UINT8 FirstDigit = Dec % 10;
	UINT8 SecondDigit = Dec / 10;

	return (SecondDigit << 4) + FirstDigit;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BCDToDec
//
// Description:	
//  This function converts data from BCD to DEC format
//
// Input:		
//  UINT8 BCD - value to be converted
//
// Output:		
//  UINT8 - result of conversion
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 BCDToDec(UINT8 BCD)
{
	UINT8 FirstDigit = BCD & 0xf;
	UINT8 SecondDigit = BCD >> 4;;

	return SecondDigit * 10  + FirstDigit;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ReadRtcIndex
//
// Description:	
//  Read the RTC value at the given Index.
//
// Input:		
//  IN UINT8 Index - RTC Register Index to read from
//
// Output:		
//  RTC Value read from the provided Index
//
// Notes:		
//  Here is the control flow of this function:
//  1. Read port 0x70 (RTC Index Register) to get bit 7.
//      Bit 7 is the NMI bit-it should not be changed.
//  2. Set Index with the NMI bit setting.
//  3. Output 0x70 with the Index.
//  4. Read 0x71 for Data.
//  5. Return the Data.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 ReadRtcIndex(IN UINT8 Index)
{
    UINT8 		NMI = IoRead8(RTC_INDEX_REG) & RTC_NMI_MASK;   //Read bit 7 (NMI setting).
	UINT8 		volatile Value;
    BOOLEAN     IntState = CPULib_GetInterruptState();
//----------------------
    CPULib_DisableInterrupt();

    IoWrite8(RTC_INDEX_REG, Index | NMI);
    Value = IoRead8(RTC_DATA_REG);               //Read register.
    
    if (IntState) CPULib_EnableInterrupt();

	if (Index <= RTC_YEAR_REG || Index == ACPI_CENTURY_CMOS) Value = BCDToDec(Value);
    
	return (UINT8)Value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	WriteRtcIndex
//
// Description:	
//  Write the RTC value at the given Index.
//
// Input:		
//  IN UINT8 Index - RTC register Index
//  IN UINT8 Value - Data to write to the Index indicated
// 
// Output:		
//  None
//
// Notes:		
//  Here is the control flow of this function:
//  1. Read port 0x70 (RTC Index Register) to get bit 7.
//      Bit 7 is the NMI bit-it should not be changed.
//  2. Set Index with the NMI bit setting.
//  3. Output 0x70 with the Index.
//  4. Write the data to 0x71.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID WriteRtcIndex(IN UINT8 Index, IN UINT8 Value)
{
    UINT8 		NMI = IoRead8(RTC_INDEX_REG) & RTC_NMI_MASK;   //Read bit 7 (NMI setting).
    BOOLEAN     IntState=CPULib_GetInterruptState();
//--------------------
	if (Index <= RTC_YEAR_REG || Index == ACPI_CENTURY_CMOS) Value = DecToBCD(Value);

    CPULib_DisableInterrupt();

    IoWrite8(RTC_INDEX_REG,Index | NMI);
    IoWrite8(RTC_DATA_REG, Value);	//Write Register.

    if (IntState) CPULib_EnableInterrupt();
} 

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitRtc
//
// Description:	
//  This function initializes RTC
//
// Input:		
//  None
//
// Output:		
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitRtc(VOID)
{
    WriteRtcIndex(RTC_REG_B_INDEX, 0x82);
    WriteRtcIndex(RTC_REG_A_INDEX, 0x26);
    ReadRtcIndex(RTC_REG_C_INDEX);
    ReadRtcIndex(RTC_REG_D_INDEX);
    WriteRtcIndex(RTC_REG_B_INDEX, 0x02);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetUpdate
//
// Description:	Enables Disables RTC Date and Time update cicles.
//
// Input:		Enable	TRUE or FALSE to Enable\Disabe RTC Update. 
//
// Output:		NOTHING
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetUpdate(BOOLEAN Enable){
	RTC_REG_B	RegB;

    RegB.REG_B = ReadRtcIndex(RTC_REG_B_INDEX);
    if(RegB.Set == Enable) {
        RegB.Set = !Enable;
        WriteRtcIndex(RTC_REG_B_INDEX, RegB.REG_B);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckUpdateCmplete
//
// Description:	
//  Check if RTC Date and Time update in progress and waits till it's over.
//
// Input:		
//  None
//
// Output:		
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CheckUpdateCmplete(){
	RTC_REG_A	volatile RegA;
    UINTN       timeout=0;
//-------------------------
	RegA.REG_A = ReadRtcIndex(RTC_REG_A_INDEX);
	while ( RegA.UpdInProgr){
        RegA.REG_A = ReadRtcIndex(RTC_REG_A_INDEX);
        timeout++;
        if(timeout >= 0x0fffff){
            gTimeOut = TRUE;
            return;
        }
    }
    gTimeOut=FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VerifyTime
//
// Description:	This routine verifies if time and data if needed, before
//				setting the RTC
//
// Input:		*Time		Time to verify with
//				CheckDate	TRUE if check date also
//
// Output:		TRUE if valid time and date
//
// Notes: 		Here is the control flow of this function:
//				1. Decrease month and date to change to 0-base
//				2. Validate Year, Month and Day. If invalid, return FALSE.
// 				3. Validate Hour, Minute, and Second. If invalid, return FALSE.
//				4. Return True.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN VerifyTime(IN EFI_TIME *Time)
{
	//Always check these to satisfy EFI compliancy test even for setting wake-up time.
	UINT8 Month = Time->Month - 1;
    UINT8 Day   = Time->Day - 1;

    if (Time->Year < MINIMUM_YEAR || Time->Year > 2099) return FALSE;
    if (Month > 11) return FALSE;             //0 based month
    if (Month != 1 || (Time->Year & 3)) { //not leap year or not February.
        if (Day > DaysInMonth[Month]) return FALSE; //All values already adjusted for 0 based.
    } else {
        if (Day > 28) return FALSE; //February
    }

    if (Time->Hour > 23) return FALSE;
    if (Time->Minute > 59) return FALSE;
    if (Time->Second > 59) return FALSE;

	//Check these to satisfy EFI compliancy test.
	if (Time->Nanosecond > 999999999) return FALSE;	//999,999,999
	if (Time->TimeZone < -1440) return FALSE;
	if (Time->TimeZone > 1440 && Time->TimeZone != EFI_UNSPECIFIED_TIMEZONE) return 0;

    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckRtc
//
// Description:	
//  Check if RTC Mode and Format have appropriate values and sets them if 
//  necessary
//
// Input:		
//  BOOLEAN Set - if true, force Rtc to 24 hour mode and binary format
//
// Output:		
//  EFI_SUCCESS - Rtc mode and format have appropriate values
//  EFI_DEVICE_ERROR - Rtc mode and/or format are invalid
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckRtc(BOOLEAN Set){
    RTC_REG_B   RegB;

    //Check RTC Conditions and stuff
    RegB.REG_B = ReadRtcIndex(RTC_REG_B_INDEX);
    if(RegB.Mode == 0 || RegB.Format == 1) {
        if(Set){
            RegB.Mode = 1;    // 0 - 12 hour mode              1 - 24 hour mode
            RegB.Format = 0;  // 0 - BCD Format                1 - Binary Format
            WriteRtcIndex(RTC_REG_B_INDEX, RegB.REG_B);
        } else {
            return EFI_DEVICE_ERROR;    
        }
    } 
    return EFI_SUCCESS;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EfiGetTime
//
// Description:	
//  Return the current date and time
//
// Input:		
//    OUT EFI_TIME *Time - Current time filled in EFI_TIME structure
//    OUT EFI_TIME_CAPABILITIES   *Capabilities	- Time capabilities (OPTIONAL)
//
// Output:		
//  EFI_SUCCESS		Always
//
// Notes:		
//  Here is the control flow of this function:
//  1. Read the original time format 12/24 hours and BCD/binary.
//  2. Set the format to 24 hrs and binary.
//  3. Read the 2 digit year.
//  4. Add either 1900 or 2000, so the year is between 1998 - 2097.
//  5. Read the month, day, hour, minute, second.
//  6. Set the nanosecond to 0.
//  7. Set the time to zone to unspecified.
//  8. Set daylight savings value to 0.
//  9. Restore the original time format.
//  10. Set Capabilities with 1 sec Resolution, 0 Accuracy (Unknown), and False SetsToZero.
//  11. Return EFI_SUCCESS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EfiGetTime (
    OUT EFI_TIME                *Time,
    OUT EFI_TIME_CAPABILITIES   *Capabilities OPTIONAL
)
{
    EFI_STATUS    Status;
    UINT8         Year;
    BOOLEAN       IntState, SmiState;
    UINTN         TimeVarSize = sizeof(TIME_VARIABLE);
    TIME_VARIABLE TimeVar;

    if (Time == NULL) return EFI_INVALID_PARAMETER;
    //Check RTC Conditions (24h Mode and BCD is ON)
    Status = CheckRtc(FALSE);  
    if(EFI_ERROR(Status)) return Status;
    //Get SMI State and disable it
    SmiState = SbLib_GetSmiState();
    SbLib_SmiDisable();   
    //Get INTERRUPT State and disable it
    IntState = CPULib_GetInterruptState();
    CPULib_DisableInterrupt();
    // Wait till RTC is safe to read,
    CheckUpdateCmplete();
    if(gTimeOut){
        InitRtc();
    }

    // After control comes back, we will have 488 u's to read data.
    Year            = ReadRtcIndex(RTC_YEAR_REG);
    Time->Month     = ReadRtcIndex(RTC_MONTH_REG);
    Time->Day       = ReadRtcIndex(RTC_DAY_OF_MONTH_REG);
    Time->Hour      = ReadRtcIndex(RTC_HOURS_REG);
    Time->Minute    = ReadRtcIndex(RTC_MINUTES_REG);
    Time->Second    = ReadRtcIndex(RTC_SECONDS_REG);
    //Restore SMIs and INTERRUPT State
    if(IntState) CPULib_EnableInterrupt();
    if(SmiState) SbLib_SmiEnable();

    //This Register is not affected by UIP bit so read it very last.
    // If RTC Year only 1 digit, EFI spec says years rang is 1998 - 2097
    Time->Year = ReadRtcIndex(ACPI_CENTURY_CMOS) * 100 + Year;
    Time->Nanosecond= 0;

	Status = pRS->GetVariable(
		                L"EfiTime",
		                &gEfiTimeVariableGuid,
		                NULL,
		                &TimeVarSize,
		                &TimeVar
	                    );

	if (EFI_ERROR(Status)) 
    {
		Time->TimeZone  = EFI_UNSPECIFIED_TIMEZONE;
		Time->Daylight  = 0;
	} 
    else 
    {
		Time->TimeZone  = TimeVar.TimeZone;
		Time->Daylight  = TimeVar.Daylight;
    }

    if (Capabilities != NULL) {
        Capabilities->Resolution = 1;
        Capabilities->Accuracy = 0;
        Capabilities->SetsToZero = 0;
    }
    return  EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EfiSetTime
//
// Description:	
//  Sets the RTC time
//
// Input:		
//  IN EFI_TIME *Time - Time to set
//
// Output:		
//  EFI_SUCCESS - Time is Set
//  EFI_INVALID_PARAMETER - Time to Set is not valid.
//
// Modified: 
//  gTimeZone
//
// Notes:		
//  Here is the control flow of this function:
//  1. Read the original time format 12/24 hours and BCD/binary.
//  2. Set the format to 24 hrs and binary.
//  3. Verify the time to set. If it is an invalid time,
//      restore the time format and return EFI_INVALID_PARAMETER.
//  4. Change the 4 digit year to a 2 digit year.
//  5. Stop the RTC time.
//  6. Store time and data on the RTC.
//  7. Read the month, day, hour, minute, second.
//  8. Start the RTC time.
//  9. Restore the original time format.
//  10. Return EFI_SUCCESS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EfiSetTime (
    IN EFI_TIME     *Time
)
{
    EFI_STATUS    Status = EFI_SUCCESS;
    UINTN         TimeVarSize = sizeof(TIME_VARIABLE);
    TIME_VARIABLE TimeVar;

    //Check RTC Conditions and stuff
    CheckRtc(TRUE);  
	if (Time == NULL) return EFI_INVALID_PARAMETER;
    if (!VerifyTime(Time)) return EFI_INVALID_PARAMETER;
    SetUpdate(FALSE);
    WriteRtcIndex(ACPI_CENTURY_CMOS, Time->Year / 100);
    WriteRtcIndex(RTC_YEAR_REG, Time->Year % 100);
    WriteRtcIndex(RTC_MONTH_REG, Time->Month);
    WriteRtcIndex(RTC_DAY_OF_MONTH_REG, Time->Day);
    WriteRtcIndex(RTC_HOURS_REG, Time->Hour);
    WriteRtcIndex(RTC_MINUTES_REG, Time->Minute);
    WriteRtcIndex(RTC_SECONDS_REG, Time->Second);
    SetUpdate(TRUE);

	Status = pRS->GetVariable(
		                L"EfiTime",
		                &gEfiTimeVariableGuid,
		                NULL,
		                &TimeVarSize,
		                &TimeVar
	                    );
	if (EFI_ERROR(Status) || (TimeVar.TimeZone != Time->TimeZone) || (TimeVar.Daylight != Time->Daylight)) 
    {
		TimeVar.TimeZone  = Time->TimeZone;
		TimeVar.Daylight  = Time->Daylight;
        Status = pRS->SetVariable(
			            L"EfiTime",
			            &gEfiTimeVariableGuid,
			            EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
			            sizeof(TIME_VARIABLE),
			            &TimeVar
		                );
    }
    return  Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EfiGetWakeupTime
//
// Description:	
//  Read the wake time. Read the status if it is enabled or if the system 
//  has woken up.
//
// Input:		
//  OUT BOOLEAN *Enabled - Flag indicating the validity of wakeup time
//  OUT BOOLEAN *Pending - Check if wake up time has expired.
//  OUT EFI_TIME *Time - Current wake up time setting
//
// Output:		
//  EFI_STATUS
//      EFI_SUCCESS (Always)
//
// Notes:		
//  Here is the control flow of this function:
//  1. Read the original time format 12/24 hours and BCD/binary.
//  2. Set the format to 24 hrs and binary.
//  3. Read the status if the wake up time is enabled or if it has expired.
//  4. Set the wakeup time.
//  5. Restore the original time format.
//  6. Return EFI_SUCCESS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EfiGetWakeupTime (
    OUT BOOLEAN     *Enabled,
    OUT BOOLEAN     *Pending,
    OUT EFI_TIME    *Time
)
{
	RTC_REG_B	RegB;
	RTC_REG_C	RegC;
    RTC_REG_D   RegD;
    BOOLEAN     IntState, SmiState;
    EFI_STATUS  Status;

	if (!Enabled || !Pending || !Time) return EFI_INVALID_PARAMETER;

    //Check RTC Conditions (24h Mode and BCD is ON)
    Status = CheckRtc(FALSE);  
    if(EFI_ERROR(Status)) return Status;

    //Get SMI State and disable it
    SmiState = SbLib_GetSmiState();
    SbLib_SmiDisable();    
    //Get INTERRUPT State and disable it
    IntState = CPULib_GetInterruptState();
    CPULib_DisableInterrupt();

    // Wait till RTC is safe to read,
    CheckUpdateCmplete();
    if(gTimeOut){
        InitRtc();
    }

    Time->Hour      = ReadRtcIndex(RTC_HOURS_ALARM_REG);
    Time->Minute    = ReadRtcIndex(RTC_MINUTES_ALARM_REG);
    Time->Second    = ReadRtcIndex(RTC_SECONDS_ALARM_REG);

    //Restore SMIs and INTERRUPT State
    if(IntState) CPULib_EnableInterrupt();
    if(SmiState) SbLib_SmiEnable();


    RegD.REG_D      = ReadRtcIndex(RTC_REG_D_INDEX);
    Time->Day		= BCDToDec(RegD.DateAlarm);

	RegB.REG_B=ReadRtcIndex(RTC_REG_B_INDEX);
	RegC.REG_C=ReadRtcIndex(RTC_REG_C_INDEX);

    *Enabled = RegB.AlarmInt;
    *Pending = RegC.AlarmFlag;


    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EfiSetWakeupTime
//
// Description:	
//  Enable/disable and set wakeup time
//
// Input:		
//  IN BOOLEAN Enable - Flag indicating whether to enable/disble the time
//  IN EFI_TIME *Time - Time to set as the wake up time - OPTIONAL
//
// Output:		
//  EFI_SUCCESS - Time is Set and/or Enabled/Disabled.
//  EFI_INVALID_PARAMETER - Invalid time or enabling with a NULL Time.
//
// Notes:		
//  Here is the control flow of this function:
//  1. Read the original time format 12/24 hours and BCD/binary.
//  2. If Time is not NULL,
//      a. Verify the wakeup time to set. If it is an invalid time,
//          restore the time format and return EFI_INVALID_PARAMETER.
//     	b. Set the wakeup time.
//  3. If Time is NULL and Enable is true, restore original time format
//      and return EFI_INVALID_PARAMETER.
//  4. Enable/Disable wakeup.
//  5. Restore the original time format.
//  6. Return EFI_SUCCESS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EfiSetWakeupTime (
    IN BOOLEAN      Enable,
    IN EFI_TIME     *Time OPTIONAL
)
{
	RTC_REG_B	RegB;
	RTC_REG_D	RegD;
    UINT8       Day = 0;        
    EFI_STATUS  Status;    


    //Check RTC Conditions (24h Mode and BCD is ON)
    Status=CheckRtc(FALSE);  
    if(EFI_ERROR(Status)) return Status;

    if (Enable){
        //According to UEFI specification, 
        // value of 0 is invalid for the alarm day.
        // However, RTC chip supports value 0.
        // It interprets it as "every day".
        //If this functionality is required,
        //uncomment the following workaround.
        //The workaround is commented out be default 
        //for compatibility with UEFI specification
        //(one of the SCT tests fails with the workaround enabled).
/*
        if(Time != NULL) { 
            Day = Time->Day;
            if(Time->Day == 0) Time->Day = 1;
        }
*/
        if (Time == NULL || !VerifyTime(Time)) return EFI_INVALID_PARAMETER;
    }
    
	RegB.REG_B = ReadRtcIndex(RTC_REG_B_INDEX);
	RegD.REG_D = ReadRtcIndex(RTC_REG_D_INDEX);
	Day = DecToBCD(Day);
	RegD.DateAlarm = Day;	
    
    SetUpdate(FALSE);
    if(Time!=NULL){
        WriteRtcIndex(RTC_HOURS_ALARM_REG, Time->Hour);
        WriteRtcIndex(RTC_MINUTES_ALARM_REG, Time->Minute);
        WriteRtcIndex(RTC_SECONDS_ALARM_REG, Time->Second);
	    WriteRtcIndex(RTC_REG_D_INDEX, RegD.REG_D); //Day==0 means don't care
    }
    //Set Enable/Disable
	RegB.AlarmInt = Enable;
    WriteRtcIndex(RTC_REG_B_INDEX, RegB.REG_B);
    
    SetUpdate(TRUE);

    return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: NotInSmmTimeServ
//
// Description: 
//  This function checks the date and time stored in the RTC.  If it's wrong
//  it resets the time and and installs Time Runtime services in Non-SMM Mode
//  RTC Arch Protocol would also be installed. 
//
// Input:
//	IN EFI_HANDLE ImageHandle - Image handle
//	IN EFI_SYSTEM_TABLE *SystemTable - pointer to the UEFI System Table
//
// Output:						 
//  Returns the EFI_STATUS value returned by the 
//  InstallMultipleProtocolInterface function
//
// Notes:      
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS NotInSmmTimeServ(
  EFI_HANDLE ImageHandle,
  EFI_SYSTEM_TABLE *SystemTable
  )
{

	EFI_STATUS		Status = EFI_SUCCESS;
 	EFI_TIME 		Time;
	EFI_HANDLE		Handle = NULL;

	InitAmiRuntimeLib(ImageHandle, SystemTable, NULL, NULL);

	//Make Sure Mode, Format and REG_A is OK
    CheckRtc(TRUE);

 	Status=EfiGetTime(&Time, NULL);
	
	if( EFI_ERROR(Status) || (!VerifyTime(&Time)))
	{
        EFI_TIME    nt;        

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

  		//if Time is invalid the battery probably has been removed
		//Let's setup RTC_REG_A just in case...
		WriteRtcIndex(RTC_REG_A_INDEX, 0x26);

        //Check to see what part of EFI_TIME was wrong.
        //reset unrelated to RTC fields.
        Time.TimeZone = EFI_UNSPECIFIED_TIMEZONE; 
        Time.Daylight = 0;
        Time.Nanosecond = 0;

        nt=Time;

    	nt.Hour = 0;
       	nt.Minute = 0;
    	nt.Second = 0;
        
        if(VerifyTime(&nt)){
            //if we here that means Time was wrong
    	    Time.Hour = 0;
       	    Time.Minute = 0;
    	    Time.Second = 0;
        } else {
            //if we here that means Date was wrong           
			Time.Month = DEFAULT_MONTH;
			Time.Day = DEFAULT_DAY;
			Time.Year = DEFAULT_YEAR;
        }
        //Here is the situation when both Time and Date is Incorrect.
        if(!VerifyTime(&Time)){
    	    Time.Hour = 0;
       	    Time.Minute = 0;
    	    Time.Second = 0;
			Time.Month = DEFAULT_MONTH;
			Time.Day = DEFAULT_DAY;
			Time.Year = DEFAULT_YEAR;
        }    

		TRACE((TRACE_ALWAYS, "Reseting Invalid Date and Time to: %d/%d/%d  %d:%d:%d\n\n",
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

	pRS->GetTime        = EfiGetTime;
    pRS->SetTime        = EfiSetTime;
    pRS->GetWakeupTime  = EfiGetWakeupTime;
    pRS->SetWakeupTime  = EfiSetWakeupTime;

    //This protocol is to notify core that the Runtime Table has been updated, so
    //it can update the runtime table CRC.
    Status = pBS->InstallMultipleProtocolInterfaces(
			&Handle,
			&gEfiRealTimeClockArchProtocolGuid,NULL,
        	NULL
		   );
	ASSERT_EFI_ERROR(Status);

    return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: NotInSmmResetServ
//
// Description: 
//  Installs Reset Runtime Services in Non-SMM Mode 
//  Reset Architectural Protocol is installed
//
// Input:
//	IN EFI_HANDLE ImageHandle - Image handle
//	IN EFI_SYSTEM_TABLE *SystemTable - pointer to the UEFI System Table
//
// Output:						 
//  Returns the EFI_STATUS value returned by the InstallProtocolInterface 
//  function
//
// Notes:      
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS NotInSmmResetServ(
  EFI_HANDLE ImageHandle,
  EFI_SYSTEM_TABLE *SystemTable
  )
{

	EFI_STATUS		Status = EFI_SUCCESS;
    EFI_HANDLE	    ResetProtocolHandle	= NULL;

	InitAmiRuntimeLib(ImageHandle, SystemTable, NULL, NULL);

	// Install reset services
	pRS->ResetSystem = EfiResetSystem;

	Status = pBS->InstallProtocolInterface ( &ResetProtocolHandle,
                    &gEfiResetArchProtocolGuid, EFI_NATIVE_INTERFACE,
                    NULL);
	ASSERT_EFI_ERROR(Status);
    return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: InSmmTimeServ
//
// Description: 
//  Installs Time Runtime Services to SMM mode. 
//              
//
// Input:		
//	IN EFI_HANDLE ImageHandle - Image handle
//	IN EFI_SYSTEM_TABLE *SystemTable - pointer to the UEFI System Table
//
// Output:						 
//  EFI_SUCCESS
//
// Notes:      
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS InSmmTimeServ(
  EFI_HANDLE ImageHandle,
  EFI_SYSTEM_TABLE *SystemTable
  )
{   
    if (pST->RuntimeServices != pRS)
    {

        pRS->GetTime        = EfiGetTime;
        pRS->SetTime        = EfiSetTime;
        pRS->GetWakeupTime  = EfiGetWakeupTime;
        pRS->SetWakeupTime  = EfiSetWakeupTime;

    }
    return EFI_SUCCESS;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: InSmmResetServ
//
// Description: 
//  Installs Reset runtime services to SMM mode. 
//
// Input:		
//	IN EFI_HANDLE ImageHandle - Image handle
//	IN EFI_SYSTEM_TABLE *SystemTable - pointer to the UEFI System Table
//
// Output:						 
//  EFI_SUCCESS
//
// Notes:      
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS InSmmResetServ(
  EFI_HANDLE ImageHandle,
  EFI_SYSTEM_TABLE *SystemTable
  )
{   
    if (pST->RuntimeServices != pRS)
    {
        pRS->ResetSystem = EfiResetSystem;
    }
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeServInit
//
// Description:	
//  This function is the entry point for this DXE. This function installs 
//  Time pRS services
//
// Input:		
//	IN EFI_HANDLE ImageHandle - Image handle
//	IN EFI_SYSTEM_TABLE *SystemTable - pointer to the UEFI System Table
//
// Output:		
//  Return Status based on errors that occurred while waiting for time to expire.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
TimeServInit (
    IN EFI_HANDLE			ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable 
){
	InitAmiLib(ImageHandle, SystemTable);
	return InitSmmHandlerEx(ImageHandle, SystemTable, InSmmTimeServ, NotInSmmTimeServ);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ResetServInit
//
// Description:	
//  This function is the entry point for this DXE Driver. This function 
//  installs the Reset pRS service.
//
// Input:
//	IN EFI_HANDLE ImageHandle - Image handle
//	IN EFI_SYSTEM_TABLE *SystemTable - pointer to the UEFI System Table
//
// Output:		
//  Return Status based on errors that occurred while waiting for time to expire.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ResetServInit(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
){
	InitAmiLib(ImageHandle, SystemTable);
	return InitSmmHandlerEx(ImageHandle, SystemTable, InSmmResetServ, NotInSmmResetServ);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
