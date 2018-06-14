//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusPei.c 3     3/27/13 10:29p Wesleychen $
//
// $Revision: 3 $
//
// $Date: 3/27/13 10:29p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusPei.c $
// 
// 3     3/27/13 10:29p Wesleychen
// Fix coding error.
// 
// 2     11/25/12 10:40p Scottyang
// [TAG]  		EIP107376
// [Category]  	Improvement
// [Description]  	Add token "PCH_SPD_WRITE_DISABLE" for SMBus reg 40h bit
// 4.
// [Files]  		SmBus.sdl
// SmBusPei.c
// 
// 1     6/06/12 8:00a Victortu
// Implement EFI_PEI_SMBUS2_PPI Support.
// 
// 10    7/21/11 7:31a Abelwu
// [TAG]  		EIP63768
// [Category]  	Improvement
// [Description]  	Supported Core 4.6.5.x PI 1.2 / uEFI 2.3.1 compliance
// [Files]  		SmBusPei.c
// 
// 9     7/19/11 8:03a Abelwu
// [TAG]  		EIP63768
// [Category]  	Improvement
// [Description]  	Supported Core 4.6.5.x PI 1.2 / uEFI 2.3.1 compliance
// [Files]  		SmBusPei.c
// 
// 8     6/27/11 2:26p Artems
// Updated year in file header
// 
// 7     6/17/11 5:53p Artems
// EIP 53378: Replaced tabs with spaces, formatted to follow coding
// standard
// 
// 6     10/13/10 4:15p Artems
// EIP 45184 - fixed pointer size to be same in IA32 and X64 mode
// 
// 5     10/19/09 12:48p Artems
// Updated copyright header
// 
// 4     3/03/09 4:36p Artems
// EIP 19949 Added support for multiple SM Bus controllers that
// represented by different PCI devices
// 
// 3     1/29/09 4:20p Artems
// Change "Note" to "Notes" for HelpBuilder
// 
// 2     1/28/09 6:51p Artems
// Modified in accordance with coding standard
// 
// 1     1/09/09 6:53p Artems
// New implementation of SMBus EIP 16730
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:        SmBusPei.c
//
// Description: SMBUS driver PEI functions implementation
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiLib.h>
#include <AmiHobs.h>
#include "SmBusPei.h"
                                        // [EIP82310]>
#include <Ppi\SmbusPolicy\SmbusPolicy.h>
#include <PchAccess.h>

static EFI_GUID gEfiPeiEndOfPeiPhasePpiGuid = EFI_PEI_END_OF_PEI_PHASE_PPI_GUID;
EFI_GUID  mPeiSmbusPolicyPpiGuid = PEI_SMBUS_POLICY_PPI_GUID;

extern EFI_GUID SmBusIdentifierGuid;
extern UINT8 SmBusPlatformReservedAddress[];
extern UINT8 SmBusPlatformReservedAddressSize;
                                        // <[EIP82310]

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusPeiEntryPoint
//
// Description: SMBUS driver PEI entry point
//
// Input:       EFI_FFS_FILE_HEADER *FfsHeader - pointer to file header
//              EFI_PEI_SERVICES  **PeiServices - pointer to PEI services table
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmBusPeiEntryPoint (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices
)
{
    EFI_STATUS Status;
    SMBUS_PEI_PRIVATE *Private;

    Status = (*PeiServices)->AllocatePool(
                                        PeiServices,
                                        sizeof(SMBUS_PEI_PRIVATE),
                                        &Private);
    if(EFI_ERROR(Status))
        return Status;

    Status = (*PeiServices)->AllocatePool(
                                    PeiServices,
                                    sizeof(EFI_SMBUS_DEVICE_MAP) * MAX_PEI_ARP_DEVICES,
                                    &(Private->SmBusContext.ArpDeviceList));
    if(EFI_ERROR(Status))
        return Status;

    Private->SmBusPpi.Execute   = SmBusPeiExecute;
    Private->SmBusPpi.ArpDevice = SmBusPeiArpDevice;
    Private->SmBusPpi.GetArpMap = SmBusPeiGetArpMap;
    Private->SmBusPpi.Notify    = SmBusPeiNotify;

    Private->SmBusPpiDesc.Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    Private->SmBusPpiDesc.Guid  = &gEfiPeiSmbus2PpiGuid;
    Private->SmBusPpiDesc.Ppi   = &Private->SmBusPpi;

    Private->NotifyDesc.Flags = EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    Private->NotifyDesc.Guid = &gEfiPeiEndOfPeiPhasePpiGuid;
    Private->NotifyDesc.Notify = SmBusEndOfPeiCallback;

    Private->SmBusContext.ArpDeviceCount = 0;
    Private->SmBusContext.MaxDevices = MAX_PEI_ARP_DEVICES;
    Private->SmBusContext.SmBusWait = SmBusPeiWait;

    Private->SmBusPpi.Identifier = SmBusIdentifierGuid;

    SmBusPeiInitialize(PeiServices, &Private->SmBusContext);

    Status = (*PeiServices)->NotifyPpi(PeiServices, &Private->NotifyDesc);
    if(EFI_ERROR(Status))
        return Status;

    return (*PeiServices)->InstallPpi(PeiServices, &Private->SmBusPpiDesc);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusPeiExecute
//
// Description: SMBUS driver PPI Execute function
//
// Input:       PI 0.91
//              **PeiServices - Pointer to the PEI services table
//              *This         - Pointer to the SMBus PPI structure
//
//              PI 1.X
//              *This         - Pointer to the SMBus2 PPI structure
//
//              SlaveAddress  - Address of the SMBus device to be used to
//                              send this command
//              Command       - Command to be sent to the device
//              Operation     - SMBus operation to be performed
//              PecCheck      - Flag indicating the usage of PEC
//              *Length       - Length of the data in the Buffer (IN/OUT)
//              *Buffer       - Pointer to the buffer with the data (IN/OUT)
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmBusPeiExecute (
    IN CONST EFI_PEI_SMBUS2_PPI *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN EFI_SMBUS_DEVICE_COMMAND Command,
    IN EFI_SMBUS_OPERATION Operation,
    IN BOOLEAN PecCheck,
    IN OUT UINTN *Length,
    IN OUT VOID *Buffer
)
{
    SMBUS_PEI_PRIVATE *Private = (SMBUS_PEI_PRIVATE *)This;

    return Execute(
                &(Private->SmBusContext),
                SlaveAddress,
                Command,
                Operation,
                PecCheck,
                Length,
                Buffer);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusPeiArpDevice
//
// Description: SMBUS driver PPI ArpDevice function
//
// Input:       PI 0.91
//              **PeiServices  - Pointer to the PEI services table
//              *This          - Pointer to the SMBus PPI structure
//
//              PI 1.X
//              *This          - Pointer to the SMBus2 PPI structure
//
//              ArpAll         - Flag indicating ARP type - ALL or specific
//              *SmbusUdid     - SMBus UDID for the device whose Address has
//                               to be resolved
//              *SlaveAddress  - Slave address to be assigned to the device
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmBusPeiArpDevice (
    IN CONST EFI_PEI_SMBUS2_PPI     *This,
    IN BOOLEAN ArpAll,
    IN EFI_SMBUS_UDID *SmbusUdid, OPTIONAL
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress OPTIONAL
)
{
    SMBUS_PEI_PRIVATE *Private = (SMBUS_PEI_PRIVATE *)This;

    return ArpDevice(
                &(Private->SmBusContext),
                ArpAll,
                SmbusUdid,
                SlaveAddress);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusPeiGetArpMap
//
// Description: SMBUS driver PPI GetArpMap function
//
// Input:       PI 0.91
//              **PeiServices   - Pointer to the PEI services table
//              *This           - Pointer to the SMBus PPI structure
//
//              PI 1.X
//              *This           - Pointer to the SMBus2 PPI structure
//
//              *Length         - Length of the Device map structure(IN & OUT)
//              *SmBusDeviceMap - Pointer to the buffer where the SMBus
//                                device map will be filled in
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmBusPeiGetArpMap (
    IN CONST EFI_PEI_SMBUS2_PPI *This,
    IN OUT UINTN *Length,
    IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
)
{
    SMBUS_PEI_PRIVATE *Private = (SMBUS_PEI_PRIVATE *)This;

    return GetArpMap(
                &(Private->SmBusContext),
                Length,
                SmbusDeviceMap);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusPeiNotify
//
// Description: SMBUS driver PPI Notify function
//
// Input:       EFI_PEI_SERVICES  **PeiServices - pointer to PEI services table
//              EFI_PEI_SMBUS_PPI *This - pointer to PPI
//              EFI_SMBUS_DEVICE_ADDRESS SlaveAddress - address of notification device
//              UINTN Data - notification data
//              EFI_PEI_SMBUS_NOTIFY_FUNCTION NotifyFunction - pointer to callback function
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmBusPeiNotify (
    IN CONST EFI_PEI_SMBUS2_PPI       *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN UINTN Data,
    IN EFI_PEI_SMBUS_NOTIFY2_FUNCTION NotifyFunction
)
{
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusEndOfPeiCallback
//
// Description: This function creates map of devices connected to SMBUS at the end of PEI phase
//
// Input:       EFI_PEI_SERVICES  **PeiServices - pointer to PEI services table
//              EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor - pointer to notify descriptor
//              VOID *Ppi - pointer to notify PPI
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmBusEndOfPeiCallback (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *Ppi
)
{
    SMBUS_PEI_PRIVATE *Private = OUTTER(NotifyDescriptor, NotifyDesc, SMBUS_PEI_PRIVATE);
    UINTN HobSize;
    AMI_SMBUS_HOB *Hob;
    EFI_STATUS Status;

    HobSize = sizeof(AMI_SMBUS_HOB) + Private->SmBusContext.ArpDeviceCount * sizeof(EFI_SMBUS_DEVICE_MAP);
    Status = (*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, HobSize, &Hob);
    if(!EFI_ERROR(Status))
    {
        Hob->Header.Name = Private->SmBusPpi.Identifier;
        Hob->BoardReservedAddressCount = Private->SmBusContext.BoardReservedAddressCount;
        Hob->BoardReservedAddressList = (UINT32) (Private->SmBusContext.BoardReservedAddressList);
        Hob->ArpDeviceCount = Private->SmBusContext.ArpDeviceCount;
        MemCpy(Hob->ArpDeviceList, 
               Private->SmBusContext.ArpDeviceList, 
               Private->SmBusContext.ArpDeviceCount * sizeof(EFI_SMBUS_DEVICE_MAP));
    }
    return Status;
}

//**********************************************************************
//                  Porting functions
//**********************************************************************

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusPeiWait
//
// Description: This function waits given number of microseconds
//
// Input:       UINTN Microseconds - number of microseconds to wait
//
// Output:      None
//
// Notes:       Porting required
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmBusPeiWait(
    IN UINTN Microseconds
)
{
    // The following code is to generate delay for specified amount of micro
    // seconds using ACPI timer.
    UINT16          AcpiTmrReg = PM_BASE_ADDRESS + ACPI_IOREG_PM1_TMR;
    UINTN           TicksNeeded;
    UINT32          TimerValue;
    UINT32          NewTimerValue;
    UINTN           OverFlow = 0;
    UINTN           TheRest;
    UINTN           EndValue;

    // There are 3.58 ticks per us, so we have to convert the number of us
    // passed in to the number of ticks that need to pass before the timer has
    // expired convert us to Ticks, don't loose significant figures or as few
    // as possible do integer math in ticks/tens of ns and then divide by 100
    // to get ticks per us

    TicksNeeded = Microseconds * 3;            // (Microseconds * 3)
    TicksNeeded += (Microseconds) / 2;         // (Microseconds * 5)/10
    TicksNeeded += (Microseconds * 2) / 25;    // (Microseconds * 8)/100
    TheRest = TicksNeeded;

    // 32 bits corresponds to approz 71 mins  no delay should be that long
    // otherwise get the number of times the counter will have to overflow
    // to delay as long as needed
    if (NUM_BITS_IN_ACPI_TIMER < MAX_ACPI_TIMER_BITS) {
        OverFlow = TicksNeeded / (1 << NUM_BITS_IN_ACPI_TIMER);
        TheRest = TicksNeeded % (1 << NUM_BITS_IN_ACPI_TIMER);
    }

    // Read ACPI Timer
    TimerValue = IoRead32( AcpiTmrReg );

    // Need to adjust the values based off of the start time
    EndValue = TheRest + TimerValue;

    // Check for overflow on addition.  possibly a problem
    if (EndValue < TimerValue) {
        OverFlow++;
    } else {
        if (NUM_BITS_IN_ACPI_TIMER < MAX_ACPI_TIMER_BITS) { 
            // Here make sure that EndValue is less than the max value
            // of the counter
            OverFlow += EndValue / (1 << NUM_BITS_IN_ACPI_TIMER);
            EndValue = EndValue % (1 << NUM_BITS_IN_ACPI_TIMER);
        }
    }

    // Let the timer wrap around as many times as calculated
    while (OverFlow) {
        // read timer amd look to see if the new value read is less than
        // the current timer value.  if this happens the timer overflowed
        NewTimerValue = IoRead32( AcpiTmrReg );

        if (NewTimerValue < TimerValue) OverFlow--;

        TimerValue = NewTimerValue;
    }

    // Now wait for the correct number of ticks that need to occur after
    // all the needed overflows
    while (EndValue > TimerValue) {
        NewTimerValue = IoRead32( AcpiTmrReg );

        // check to see if the timer overflowed.  if it did then
        // the time has elapsed. Because EndValue should be greater than
        // TimerValue
        if (NewTimerValue < TimerValue) break;

        TimerValue = NewTimerValue;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusPeiInitialize
//
// Description: This function initializes SMBUS PCI device and fills device context
//
// Input:       **PeiServices - Pointer to the PEI Services table
//              *Context      - Pointer to the SMBus private structure.
//
// Output:      None
//
// Notes:       Porting required
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmBusPeiInitialize(
    IN EFI_PEI_SERVICES         **PeiServices,
    IN OUT SMBUS_PRIVATE        *Context )
{
                                        // [EIP82310]>
    EFI_STATUS                  Status;
    PEI_SMBUS_POLICY_PPI        *SmbusPolicy;
    UINTN                       SmbusRegBase;

    Context->BoardReservedAddressCount = SmBusPlatformReservedAddressSize;
    Context->BoardReservedAddressList = SmBusPlatformReservedAddress;

    Status = (*PeiServices)->LocatePpi (
                              PeiServices,
                              &mPeiSmbusPolicyPpiGuid,
                              0,
                              NULL,
                              &SmbusPolicy
                              );
    if (EFI_ERROR(Status)) return;

    SmbusRegBase = SB_PCIE_CFG_ADDRESS (SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, 0);

    if (MEM_READ16(SmbusRegBase + R_PCH_SMBUS_VENDOR_ID) != 0xFFFF) {
      Context->SmBusBase = MEM_READ16(SmbusRegBase + R_PCH_SMBUS_BASE) & (UINT16) B_PCH_SMBUS_BASE_BAR;
      if (Context->SmBusBase == SmbusPolicy->BaseAddress) {
        return;
      } else if (Context->SmBusBase == 0) {
        Context->SmBusBase = SmbusPolicy->BaseAddress;

        // Set the BAR & I/O space enable ourselves
        MEM_WRITE16(SmbusRegBase + SMBUS_REG_BASE_ADDR, Context->SmBusBase);
        MEM_SET8(SmbusRegBase + R_PCH_SMBUS_PCICMD, B_PCH_SMBUS_PCICMD_IOSE);

        // Reset the SMBus host controller
        MEM_SET8(SmbusRegBase + R_PCH_SMBUS_HOSTC, (PCH_SPD_WRITE_DISABLE << 4) | B_PCH_SMBUS_HOSTC_SSRESET);

        // Enable the SMBus host controller
        MEM_RW8(SmbusRegBase + R_PCH_SMBUS_HOSTC, \
                B_PCH_SMBUS_HOSTC_HST_EN, \
                B_PCH_SMBUS_HOSTC_SMI_EN | B_PCH_SMBUS_HOSTC_I2C_EN);

        // Clear Status Register before anyone uses the interfaces
        IoWrite8 (Context->SmBusBase + R_PCH_SMBUS_HSTS, B_PCH_SMBUS_HSTS_ALL);
      }
    }
                                        // <[EIP82310]
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

