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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Chipset/NB/SystemAgentWrap/UpdateMemoryRecord/UpdateMemoryRecord.c 1     4/19/16 7:41a Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 4/19/16 7:41a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Chipset/NB/SystemAgentWrap/UpdateMemoryRecord/UpdateMemoryRecord.c $
// 
// 1     4/19/16 7:41a Chienhsieh
// Update rev10.
// 
// 10    12/21/15 5:58a Chienhsieh
// [TAG]  		EIP249553
// [Category]  	Improvement
// [Description]  	SMBIOS Type17 memory speed report issue with Hawell
// (Sharkbay) platform
// [Files]  		UpdateMemoryRecord.c
// 
// 9     8/23/13 2:59a Ireneyang
// [TAG]         EIP126356
// [Category]    Improvement
// [Description] Change calucating method for Dimm Frequency.
// [Files]       UpdateMemoryRecord.c;
// 
// 8     7/31/13 3:38a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Change token name REFERENCE_DDR_IO_BUS to DCLK_FREQUENCY.
//               When it's 0, it would show DDR Frequency in SMBIOS
//               (DCLK Frequency).
//               When it's 1, it would show DDR IO Bus Clock in SMBIOS
//               (QCLK Frequency).
// [Files]       SystemAgentWrap.sdl; UpdateMemoryRecord.c;
// 
// 7     6/26/13 10:00a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] According to SMBIOS spec, Set REFERENCE_DDR_IO_BUS token 
//               for choosing how to show DDR speed.
// [Files]       SystemAgentWrap.sdl; UpdateMemoryRecord.c;
// 
// 5     6/26/13 4:27a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Rename NbSmbiosType17Voltage() to 
//               NbSmbiosType17VoltageAndSpeed().
// [Files]       UpdateMemoryRecord.c;
// 
// 4     6/13/13 7:14a Ireneyang
// [TAG]         EIP125449
// [Category]    Improvement
// [Description] Update XmpId for SMBIOS Spec 2.8.0.
// 
// 3     6/07/13 8:13a Ireneyang
// [TAG]         EIP125449
// [Category]    Improvement
// [Description] Update SMBIOS Spec 2.8.0.
// 
// 2     1/28/13 2:58a Jeffch
// [TAG]         None
// [Category]    Improvement
// [Description] Update SMBIOS Spec 2.7.1.
// 
// 
// 1     2/08/12 4:37a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  UpdateMemoryRecord.c
//
// Description: This file for update SMBIOS Type 16 ~19.
//
//<AMI_FHDR_END>
//**********************************************************************

#include "UpdateMemoryRecord.h"

#include <MemInfo\MemInfo.h>
#define __EFI__H__
#ifndef GUID_VARIABLE_DEFINITION
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#else
#define GUID_VARIABLE_DECLARATION(Variable, Guid) GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID Variable=Guid
#endif
#include <Protocol\SmBus.h>

#include <Protocol\SaPlatformPolicy\SaPlatformPolicy.h>


#define EFI_SMBIOS_BOARD_PROTOCOL_GUID \
    {0x903dd14, 0x2ca0, 0x458a, 0xb5, 0xeb, 0xc, 0xc, 0xa3, 0xd, 0x78, 0x5c}

#define EFI_MEMORY_SUBCLASS_DRIVER_GUID \
  { 0x1767CEED, 0xDB82, 0x47cd, 0xBF, 0x2B, 0x68, 0x45, 0x8A, 0x8C, 0xCF, 0xFF }


EFI_GUID gEfiMemorySubClassDriverGuid     = EFI_MEMORY_SUBCLASS_DRIVER_GUID;
EFI_GUID gEfiSmbiosBoardProtocolGuid      = EFI_SMBIOS_BOARD_PROTOCOL_GUID;
EFI_GUID gEfiSmbiosUpdateDataProtocolGuid = EFI_SMBIOS_UPDATE_DATA_PROTOCOL_GUID;
EFI_GUID gDxePlatformSaPolicyGuid         = DXE_PLATFORM_SA_POLICY_GUID;
EFI_GUID gMemInfoHobProtocolGuid          = MEM_INFO_PROTOCOL_GUID;
EFI_GUID gEfiSmbusProtocolGuid            = EFI_SMBUS_HC_PROTOCOL_GUID;


EFI_SMBIOS_UPDATE_DATA_PROTOCOL           *gSBUpdate;
EFI_SMBIOS_PROTOCOL                       *gSmbiosProtocol;
MEM_INFO_PROTOCOL                         *gMemInfoHobProtocol = NULL;
EFI_SMBUS_HC_PROTOCOL	                  *gSmbusProtocol = NULL;
DXE_PLATFORM_SA_POLICY_PROTOCOL           *gDxePlatformSaPolicy = NULL;
static UINT8 DimmNumber                   = 0;
static UINT8 DimmSlot[4]                  = { DIMM1_SMBUS_ADDRESS, 
                                              DIMM2_SMBUS_ADDRESS, 
                                              DIMM3_SMBUS_ADDRESS, 
                                              DIMM4_SMBUS_ADDRESS 
                                            };

#define MRC_REF_CLOCK_133                 (0)
#define MRC_REF_CLOCK_100                 (1)
#define fNoInit                           (0)
#define f800                              (800)
#define f1000                             (1000)
#define f1067                             (1067)
#define f1200                             (1200)
#define f1333                             (1333)
#define f1400                             (1400)
#define f1600                             (1600)
#define f1800                             (1800)
#define f1867                             (1867)
#define f2000                             (2000)
#define f2133                             (2133)
#define f2200                             (2200)
#define f2400                             (2400)
#define f2600                             (2600)
#define f2667                             (2667)
#define fUnSupport                        (0x7FFFFFFF)

#define MRC_FREQUENCY_MTB_OFFSET          1000000
#define MRC_FREQUENCY_FTB_OFFSET          1000
#define MRC_DDR3_800_TCK_MIN              2500000   /// 1/(800/2) femtoseconds
#define MRC_DDR3_1000_TCK_MIN             2000000   /// 1/(1000/2) femtoseconds
#define MRC_DDR3_1067_TCK_MIN             1875000   /// 1/(1067/2) femtoseconds
#define MRC_DDR3_1200_TCK_MIN             1666666   /// 1/(1200/2) femtoseconds
#define MRC_DDR3_1333_TCK_MIN             1500000   /// 1/(1333/2) femtoseconds
#define MRC_DDR3_1400_TCK_MIN             1428571   /// 1/(1400/2) femtoseconds
#define MRC_DDR3_1600_TCK_MIN             1250000   /// 1/(1600/2) femtoseconds
#define MRC_DDR3_1800_TCK_MIN             1111111   /// 1/(1800/2) femtoseconds
#define MRC_DDR3_1867_TCK_MIN             1071428   /// 1/(1867/2) femtoseconds
#define MRC_DDR3_2000_TCK_MIN             1000000   /// 1/(2000/2) femtoseconds
#define MRC_DDR3_2133_TCK_MIN             937500    /// 1/(2133/2) femtoseconds
#define MRC_DDR3_2200_TCK_MIN             909090    /// 1/(2200/2) femtoseconds
#define MRC_DDR3_2400_TCK_MIN             833333    /// 1/(2400/2) femtoseconds
#define MRC_DDR3_2600_TCK_MIN             769230    /// 1/(2600/2) femtoseconds
#define MRC_DDR3_2667_TCK_MIN             750000    /// 1/(2667/2) femtoseconds
#define MRC_DDR3_2800_TCK_MIN             714285    /// 1/(2800/2) femtoseconds
#define TREFIMULTIPLIER                   1000      /// tREFI value defined in XMP 1.3 spec is actually in thousands of MTB units.
#define MAX(a,b)   (((a) > (b)) ? (a) : (b))
#define MIN(a,b)   (((a) < (b)) ? (a) : (b))

typedef struct {
  UINT32           tCK;
  UINT32           DDRFreq;
  UINT8            RefClkFlag;  // 0 = invalid freq. 1 = valid only at 133 RefClk, 2 = valid only at 100 RefClk, 3 = valid at both.
} NbTRangeTable;

// Timing Range table
const NbTRangeTable NbRange[] = {
  { 0xFFFFFFFF,            fUnSupport, (0 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_800_TCK_MIN,  f800,       (1 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1000_TCK_MIN, f1000,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1067_TCK_MIN, f1067,      (1 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1200_TCK_MIN, f1200,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1333_TCK_MIN, f1333,      (1 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1400_TCK_MIN, f1400,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1600_TCK_MIN, f1600,      (1 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1800_TCK_MIN, f1800,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1867_TCK_MIN, f1867,      (1 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2000_TCK_MIN, f2000,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2133_TCK_MIN, f2133,      (1 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2200_TCK_MIN, f2200,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2400_TCK_MIN, f2400,      (1 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2600_TCK_MIN, f2600,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2667_TCK_MIN, f2667,      (1 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { 0,                     fNoInit,    (0 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) }
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadSpdData
//
// Description: Returns the length of the Dimm Spd
//              
// Input:       	UINT8	                SpdSalveAddr,
// 	                UINT8					Offset,
// 	                UINTN					Count,
// Output:      	UINT8					*Buffer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadSpdData (
	IN      UINT8	                                SpdSalveAddr,
	IN	UINT8					Offset,
	IN	UINTN					Count,
	OUT	UINT8					*Buffer
	)
{
	EFI_STATUS					Status;
	UINTN						Index;
	UINTN						Length;
	EFI_SMBUS_OPERATION			Operation;
	EFI_SMBUS_DEVICE_COMMAND	Command;
    EFI_SMBUS_DEVICE_ADDRESS    SlaveAddress;

    if(gSmbusProtocol == NULL) 	return EFI_UNSUPPORTED;

	SlaveAddress.SmbusDeviceAddress = SpdSalveAddr >> 1;

	for (Index = 0; Index < Count; Index++) 
	{
		Command = Offset + Index;

		Length = 1;
		Operation = EfiSmbusReadByte;
		Status = gSmbusProtocol->Execute (gSmbusProtocol, 
							SlaveAddress,
							Command, 
							Operation, 
							FALSE,
							&Length,
							&Buffer[Index] );
		if (EFI_ERROR(Status)) return Status;
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NbGetDimmTCK
//
// Description: Returns the Dimm tCK Timing
//              
//
// Input:       UINT32 tCK
//
// Output:      TRUE  - Have tCK Timing
//              FALSE - Not have tCK Timing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static BOOLEAN
NbGetDimmTCK (
  UINT8                        SpdFtbDividend,
  UINT8                        SpdFtbDivisor,
  UINT8                        SpdMtbDividend,
  UINT8                        SpdMtbDivisor,
  UINT8                        tCKminMtb,
//  UINT8                        tCKminFine,                            // EIP249553
  INT8                         tCKminFine,
  OUT     UINT32               *tCK
  )
{
    INT32              MediumTimebase = 0;
    INT32              FineTimebase = 0;

    FineTimebase  = (SpdFtbDivisor == 0) ? 0 : (SpdFtbDividend * MRC_FREQUENCY_FTB_OFFSET) / SpdFtbDivisor;
    MediumTimebase  = (SpdMtbDivisor == 0) ? 0 : (SpdMtbDividend * MRC_FREQUENCY_MTB_OFFSET) / SpdMtbDivisor;
     *tCK = (MediumTimebase * tCKminMtb) + (FineTimebase * tCKminFine);

     return (MediumTimebase == 0) ? FALSE : TRUE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NbGetDimmFrequency
//
// Description: Returns Dimm Frequency
//              
//
// Input:       UINT32 tCK
//
// Output:      UINT32 XmpFrequency
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static
UINT32
NbGetDimmFrequency (
  IN     UINT32             tCK
  )
{
  UINT32                              Index;
  UINT32                              XmpFrequency = fNoInit;
  UINT32                              NbRangeSize        = (sizeof (NbRange) / sizeof (NbTRangeTable)) - 1;

  if(tCK == 0 || tCK == 0xffffffff) return fNoInit;

     for (Index = 0; Index < NbRangeSize; Index++) {
       if ((tCK <= NbRange[Index].tCK) && (tCK > NbRange[Index + 1].tCK)) {
         XmpFrequency = NbRange[Index].DDRFreq;
         break;
       }
     }

     while (Index) {
       if ((NbRange[Index].RefClkFlag & (1 << gMemInfoHobProtocol->MemInfoData.RefClk)) == MRC_REF_CLOCK_133) {
         XmpFrequency = NbRange[--Index].DDRFreq;
       } else break;
     }

  return XmpFrequency;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NbSmbiosType17Voltage
//
// Description: To update MinimumVoltage, MaximumVoltage, ConfiguredVoltage
//              and Dimm Frequency
//              
//
// Input:       SMBIOS_MEMORY_DEVICE_INFO     *TypeBuffer
//
// Output:      SMBIOS_MEMORY_DEVICE_INFO     *TypeBuffer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NbSmbiosType17VoltageAndSpeed (
  IN OUT SMBIOS_MEMORY_DEVICE_INFO     *TypeBuffer
  ) 
{
    UINT8                              VoltageCap = 0;
    UINT16                             XmpId = 0; 
    UINT8                              XmpProfileCap = 0;
    UINT8                              SpdFtbDividend = 0;
    UINT8                              SpdFtbDivisor = 0;
    UINT8                              SpdMtbDividend = 0;
    UINT8                              SpdMtbDivisor = 0;
    UINT8                              tCKminMtb = 0;
//    UINT8                              tCKminFine = 0;                // EIP249553
    INT8                               tCKminFine;
    UINT32                             tCK = 0;
    UINT32                             XmpProfile1Speed = 0;
    UINT32                             XmpProfile2Speed = 0;
    UINT8                              SpdData[18] = {6, 9, 10, 11, 12, 34, 176, 177, 178, 180, 181, 182, 183, 184, 186, 211, 221, 246};
    EFI_STATUS                         Status;
    UINT8                              i;

    // find DimmNumber
    for ( ; DimmNumber < 4; DimmNumber++) {
       if (DimmSlot[DimmNumber] != 0) break; 
    } 

    if(gMemInfoHobProtocol != NULL) {
        if (gMemInfoHobProtocol->MemInfoData.DimmExist[DimmNumber]) { // DIMM_PRESENT 
           for (i = 0; i < sizeof(SpdData) ; i++) { 
             // Get Spd data
             Status = ReadSpdData(DimmSlot[DimmNumber], SpdData[i], 1, &SpdData[i]);
             if (EFI_ERROR (Status)) {
                // if memory down mode, use MemInfoHob
                SpdData[i] = *(UINT8 *)(gMemInfoHobProtocol->MemInfoData.DimmsSpdData[DimmNumber] + SpdData[i]);
             }
           }

          XmpId = *(UINT16 *)&SpdData[6];

           VoltageCap = SpdData[0];
           XmpProfileCap = SpdData[8];

#if defined AMI_SMBIOS_MODULE_VERSION && AMI_SMBIOS_MODULE_VERSION >= 105
           if (VoltageCap & 0x04) { // 1.25 v
              TypeBuffer->MinimumVoltage = 1250;
           } else if (VoltageCap & 0x02) { // 1.35 v
              TypeBuffer->MinimumVoltage = 1350; 
           } else if (!(VoltageCap & 0x01)) { // 1.5 v  bit0 = 0 
              TypeBuffer->MinimumVoltage = 1500; 
           }

           if (!(VoltageCap & 0x01)) { // 1.5 v  bit0 = 0 
              TypeBuffer->MaximumVoltage = 1500;
           } else if (VoltageCap & 0x02) { // 1.35 v
              TypeBuffer->MaximumVoltage = 1350; 
           } else if (VoltageCap & 0x04) { // 1.25 v
              TypeBuffer->MaximumVoltage = 1250; 
           }
      
           TypeBuffer->ConfiguredVoltage = gMemInfoHobProtocol->MemInfoData.VddVoltage[0];
#endif
           // Calculate Dimm STD Profile
           SpdFtbDivisor = SpdData[1];
           SpdFtbDividend = (UINT8)(SpdFtbDivisor >> 4);
           SpdFtbDivisor &= 0x0f;
           SpdMtbDividend  = SpdData[2];
           SpdMtbDivisor  = SpdData[3];
           tCKminMtb  = SpdData[4];
           tCKminFine  = SpdData[5];
           // Get tCK Timing
           if(NbGetDimmTCK(SpdFtbDividend, SpdFtbDivisor, SpdMtbDividend, SpdMtbDivisor, tCKminMtb, tCKminFine, &tCK)){
               // Get Dimm Frequency
               TypeBuffer->Speed = NbGetDimmFrequency(tCK);

#if defined DCLK_FREQUENCY && DCLK_FREQUENCY == 1
               // Get Dimm Frequency
             if((NbGetDimmFrequency(tCK)%5) == 3) {
               TypeBuffer->Speed = (NbGetDimmFrequency(tCK)/2)+1;
             } else {
               TypeBuffer->Speed = (NbGetDimmFrequency(tCK)/2);
             }
#endif  
           }

           if(XmpId == 0x4A0C) { // is XMP

              // Calculate Dimm XMP Profile 1
              if (XmpProfileCap & 0x01) {
                SpdFtbDivisor = SpdData[13];
                SpdFtbDividend = (UINT8)(SpdFtbDivisor >> 4);
                SpdFtbDivisor &= 0x0f;
                SpdMtbDividend  = SpdData[9];
                SpdMtbDivisor  = SpdData[10];
                tCKminMtb  = SpdData[14];
                tCKminFine  = SpdData[15];
                // Get tCK Timing
                if(NbGetDimmTCK(SpdFtbDividend, SpdFtbDivisor, SpdMtbDividend, SpdMtbDivisor, tCKminMtb, tCKminFine, &tCK)){
                   // Get Dimm Frequency
                   XmpProfile1Speed = NbGetDimmFrequency(tCK);
                   // Speed must MAX Speed.
                   TypeBuffer->Speed = MAX(TypeBuffer->Speed, XmpProfile1Speed);

#if defined DCLK_FREQUENCY && DCLK_FREQUENCY == 1
                   // Speed must MAX Speed.
                   TypeBuffer->Speed = MAX(TypeBuffer->Speed, ((XmpProfile1Speed/2)+1));
#endif
                }
              }

              // Calculate Dimm XMP Profile 2
              if (XmpProfileCap & 0x02) {
                SpdFtbDivisor = SpdData[13];
                SpdFtbDividend = (UINT8)(SpdFtbDivisor >> 4);
                SpdFtbDivisor &= 0x0f;
                SpdMtbDividend  = SpdData[11];
                SpdMtbDivisor  = SpdData[12];
                tCKminMtb  = SpdData[16];
                tCKminFine  = SpdData[17];
                // Get tCK Timing
                if(NbGetDimmTCK(SpdFtbDividend, SpdFtbDivisor, SpdMtbDividend, SpdMtbDivisor, tCKminMtb, tCKminFine, &tCK)){
                  // Get Dimm Frequency
                   XmpProfile2Speed = NbGetDimmFrequency(tCK);
                   // Speed must MAX Speed.
                   TypeBuffer->Speed = MAX(TypeBuffer->Speed, XmpProfile2Speed);

#if defined DCLK_FREQUENCY && DCLK_FREQUENCY == 1
                   // Speed must MAX Speed.
                   TypeBuffer->Speed = MAX(TypeBuffer->Speed, ((XmpProfile2Speed/2)+1));
#endif
                }
              }

           } // if(XmpId == 0x4A0C)
       } // if (gMemInfoHobProtocol.MemInfoData.DimmExist != DIMM_PRESENT)
    } // if(gMemInfoHobProtocol != NULL)

    return EFI_SUCCESS;    
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetStructureLength
//
// Description: Returns the length of the structure pointed by BufferStart
//              in bytes
//
// Input:       UINT8 *BufferStart
//
// Output:      Structure Size
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetStructureLength(
    IN UINT8     *BufferStart
)
{
     UINT8     *BufferEnd = BufferStart;

     BufferEnd += ((SMBIOS_STRUCTURE_HEADER*)BufferStart)->Length;
     while (*(UINT16*)BufferEnd != 0) 
     {
         BufferEnd++;
     }

     return (UINT16)(BufferEnd + 2 - BufferStart);   // +2 for double zero terminator
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindStructureType
//
// Description: Find structure type starting from memory location pointed by
//              Buffer
//
// Input:       UINT8   **Buffer
//              UINT8   **StructureFoundPtr
//              UINT8   SearchType
//              UINT8   Instance
//
// Output:      If SearchType is found:
//                UINT8   **Buffer - Points to the next structure
//                UINT8   **StructureFoundPtr - Points to the structure
//                                              that was found
//              If SearchType is not found:
//                UINT8   **Buffer - No change
//                UINT8   **StructureFoundPtr = NULL
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
FindStructureType(
    IN OUT  UINT8       **Buffer,
    IN OUT  UINT8       **StructureFoundPtr,
    IN      UINT8       SearchType,
    IN      UINT8       Instance        // 1-based
)
{
    UINT8     *BufferPtr = *Buffer;
    BOOLEAN   FindStatus = FALSE;

    *StructureFoundPtr = NULL;
    while (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type != 127) 
    {
        if (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type == SearchType) 
        {
            // If this instance, set the find status flag and update the Buffer pointer
            if (--Instance == 0) 
            {
                FindStatus = TRUE;
                *StructureFoundPtr = BufferPtr;
                *Buffer = BufferPtr + GetStructureLength(BufferPtr);
                break;
            }
        }
        BufferPtr += GetStructureLength(BufferPtr);
    }

    if ((FindStatus == FALSE) & (SearchType == 127)) 
    {
        FindStatus = TRUE;
        *StructureFoundPtr = BufferPtr;
        *Buffer = BufferPtr + GetStructureLength(BufferPtr);
    }

    return FindStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildType16
//
// Description: Build SMBIOS Type 16
//              
// Input:     SMBIOS_TABLE_ENTRY_POINT     *SmbiosBuffer,
//            EFI_MEMORY_SUBCLASS_RECORDS  *MemorySubClassData
//
// Output:      
//            None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
BuildType16(
     IN SMBIOS_TABLE_ENTRY_POINT     *SmbiosBuffer,
     IN EFI_MEMORY_SUBCLASS_RECORDS  *MemorySubClassData
)
{
     SMBIOS_PHYSICAL_MEM_ARRAY_INFO  *TypeBuffer;
     UINT16                          bsize;

     // Allocate temporary buffer
     TypeBuffer = EfiLibAllocateZeroPool(sizeof(SMBIOS_PHYSICAL_MEM_ARRAY_INFO)+0x100);

     // Build header of structure
     TypeBuffer->StructureType.Type     = 16; // Type 16
     TypeBuffer->StructureType.Length   = sizeof(SMBIOS_PHYSICAL_MEM_ARRAY_INFO);
     TypeBuffer->StructureType.Handle   = gSBUpdate->SMBIOS_GetFreeHandle(SmbiosBuffer);

     // Build Content of structure
     TypeBuffer->Location               = MemorySubClassData->ArrayLocationData.MemoryArrayLocation;
     TypeBuffer->Use                    = MemorySubClassData->ArrayLocationData.MemoryArrayUse;
     TypeBuffer->MemErrorCorrection     = MemorySubClassData->ArrayLocationData.MemoryErrorCorrection;
     TypeBuffer->MaxCapacity            = MemorySubClassData->ArrayLocationData.MaximumMemoryCapacity;
     if (TypeBuffer->MaxCapacity >= 0x80000000)
     {
        TypeBuffer->ExtMaxCapacity      = TypeBuffer->MaxCapacity;
        TypeBuffer->MaxCapacity         = 0x80000000;
     } 
     else
     {
        TypeBuffer->ExtMaxCapacity      = 0;
     }

     //
     // Maximum memory supported by the memory controller
     // 2 GB in terms of KB
     //
#if MEMORY_ERROR_INFO
     TypeBuffer->MemErrInfoHandle  = SMBIOS_UNKNOW;
#else
     TypeBuffer->MemErrInfoHandle  = SMBIOS_NOT_PROVIDE;
#endif
     TypeBuffer->NumberOfMemDev    = MemorySubClassData->ArrayLocationData.NumberMemoryDevices;

     // Write structure To SMBIOS Buffer
     bsize = SMBIOS_GetStructureTotalSize((UINT8 *)TypeBuffer);
     gSBUpdate->SMBIOS_InsertStructure(SmbiosBuffer, (UINT8 *)TypeBuffer, bsize);

     // Fix handle link
     SMBIOS_FixHandleLink(SmbiosBuffer);

     // Free temporary buffer
     gBS->FreePool(TypeBuffer);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildType17
//
// Description: Build SMBIOS Type 17
//              
// Input:     SMBIOS_TABLE_ENTRY_POINT     *SmbiosBuffer,
//            EFI_MEMORY_SUBCLASS_RECORDS  *MemorySubClassData
//
// Output:    None 
//            
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
BuildType17(
    IN SMBIOS_TABLE_ENTRY_POINT         *SmbiosBuffer,
    IN EFI_MEMORY_SUBCLASS_RECORDS      *MemorySubClassData
)
{
    SMBIOS_MEMORY_DEVICE_INFO           *TypeBuffer;
    UINT16                              bsize;

    // Allocate temporary buffer
    TypeBuffer = EfiLibAllocateZeroPool(sizeof(SMBIOS_MEMORY_DEVICE_INFO)+0x100);

    // Build header of structure
    TypeBuffer->StructureType.Type      = 17;  // Type 17
    TypeBuffer->StructureType.Length    = sizeof(SMBIOS_MEMORY_DEVICE_INFO);
    TypeBuffer->StructureType.Handle    = gSBUpdate->SMBIOS_GetFreeHandle(SmbiosBuffer);

    // Build Content of structure
    TypeBuffer->PhysicalMemArrayHandle  = (UINT16)gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 16, 1);
#if MEMORY_ERROR_INFO
    TypeBuffer->MemErrorInfoHandle      = SMBIOS_UNKNOW;
#else
    TypeBuffer->MemErrorInfoHandle      = SMBIOS_NOT_PROVIDE;
#endif
    TypeBuffer->TotalWidth              = MemorySubClassData->ArrayLink.MemoryTotalWidth;
    TypeBuffer->DataWidth               = MemorySubClassData->ArrayLink.MemoryDataWidth;
    TypeBuffer->Size                    = (UINT16) (RShiftU64 (MemorySubClassData->ArrayLink.MemoryDeviceSize, 20));
    TypeBuffer->FormFactor              = MemorySubClassData->ArrayLink.MemoryFormFactor;
    TypeBuffer->DeviceSet               = MemorySubClassData->ArrayLink.MemoryDeviceSet;
    TypeBuffer->DeviceLocator           = TransferHiiStringToSmbios((UINT8 *)TypeBuffer, MemorySubClassData->ArrayLink.MemoryDeviceLocator);
    TypeBuffer->BankLocator             = TransferHiiStringToSmbios((UINT8 *)TypeBuffer, MemorySubClassData->ArrayLink.MemoryBankLocator);
    TypeBuffer->MemoryType              = MemorySubClassData->ArrayLink.MemoryType;
    TypeBuffer->TypeDetail              = *((UINT16*)(&(MemorySubClassData->ArrayLink.MemoryTypeDetail)));
    TypeBuffer->Speed                   = 0;
    TypeBuffer->Manufacturer            = TransferHiiStringToSmbios((UINT8 *)TypeBuffer, MemorySubClassData->ArrayLink.MemoryManufacturer);
    TypeBuffer->SerialNumber            = TransferHiiStringToSmbios((UINT8 *)TypeBuffer, MemorySubClassData->ArrayLink.MemorySerialNumber);
    TypeBuffer->AssetTag                = TransferHiiStringToSmbios((UINT8 *)TypeBuffer, MemorySubClassData->ArrayLink.MemoryAssetTag);
    TypeBuffer->PartNumber              = TransferHiiStringToSmbios((UINT8 *)TypeBuffer, MemorySubClassData->ArrayLink.MemoryPartNumber);
    TypeBuffer->Attributes              = MemorySubClassData->ArrayLink.MemoryAttributes;
    TypeBuffer->ConfMemClkSpeed         = MemorySubClassData->ArrayLink.MemorySpeed;
#if defined DCLK_FREQUENCY && DCLK_FREQUENCY == 1
    TypeBuffer->ConfMemClkSpeed         = ((MemorySubClassData->ArrayLink.MemorySpeed)/2)+1;
#endif
    TypeBuffer->ExtendedSize            = 0;
#if defined AMI_SMBIOS_MODULE_VERSION && AMI_SMBIOS_MODULE_VERSION >= 105
    TypeBuffer->MinimumVoltage          = 0; // unknown  SmBios 2.8.0+        
    TypeBuffer->MaximumVoltage          = 0; // unknown  SmBios 2.8.0+          
    TypeBuffer->ConfiguredVoltage       = 0; // unknown  SmBios 2.8.0+ 
#endif

    if (TypeBuffer->Size >= 0x8000 ) // 32G
    {
       TypeBuffer->ExtendedSize = TypeBuffer->Size;

       // ExtendedSize Bit 31 is reserved for future use and must be set to 0.
       if (TypeBuffer->ExtendedSize >= BIT31) {
          TypeBuffer->ExtendedSize = BIT31 - 1;
       }
       TypeBuffer->Size = 0x7FFF;
    }

    // SmBios 2.8.0+ 
    // To update MinimumVoltage, MaximumVoltage, ConfiguredVoltage and Dimm Frequency
    NbSmbiosType17VoltageAndSpeed (TypeBuffer);
 
    // Write structure To SMBIOS Buffer
    bsize = SMBIOS_GetStructureTotalSize((UINT8 *)TypeBuffer);
    gSBUpdate->SMBIOS_InsertStructure(SmbiosBuffer, (UINT8 *)TypeBuffer, bsize);

    // Fix handle link
    SMBIOS_FixHandleLink(SmbiosBuffer);

    // Free temporary buffer
    gBS->FreePool(TypeBuffer);
}

#if MEMORY_ERROR_INFO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildType18
//
// Description: Build SMBIOS Type 18
//              
// Input:     SMBIOS_TABLE_ENTRY_POINT     *SmbiosBuffer,
//            EFI_MEMORY_SUBCLASS_RECORDS  *MemorySubClassData
//
// Output:    None  
//            
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
BuildType18(
    IN SMBIOS_TABLE_ENTRY_POINT     *SmbiosBuffer,
    IN EFI_MEMORY_SUBCLASS_RECORDS  *MemorySubClassData
)
{
    SMBIOS_MEMORY_ERROR_INFO     *TypeBuffer;
    UINT16                        bsize;

    // Allocate temporary buffer
    TypeBuffer = EfiLibAllocateZeroPool(sizeof(SMBIOS_MEMORY_ERROR_INFO)+0x100);

    // Build header of structure
    TypeBuffer->StructureType.Type      = 18;  // Type 18
    TypeBuffer->StructureType.Length    = sizeof(SMBIOS_MEMORY_ERROR_INFO);
    TypeBuffer->StructureType.Handle    = gSBUpdate->SMBIOS_GetFreeHandle(SmbiosBuffer);

    //Memory.PhysicalMemArray[PMAIdx].ArrayMemoryError.ErrorType = 3;
    TypeBuffer->ErrorType = 3;
    //Memory.PhysicalMemArray[PMAIdx].ArrayMemoryError.ErrorGranularity = 2;
    TypeBuffer->ErrorGranularity = 2;
    //Memory.PhysicalMemArray[PMAIdx].ArrayMemoryError.ErrorOperation = 2;
    TypeBuffer->ErrorOperation = 2;
    //Memory.PhysicalMemArray[PMAIdx].ArrayMemoryError.MemArrayErrorAddress = 0x80000000;
    TypeBuffer->MemArrayErrorAddress = 0x80000000;
    //Memory.PhysicalMemArray[PMAIdx].ArrayMemoryError.DeviceErrorAddress = 0x80000000;
    TypeBuffer->DeviceErrorAddress = 0x80000000;
    //Memory.PhysicalMemArray[PMAIdx].ArrayMemoryError.ErrorResolution = 0x80000000;
    TypeBuffer->ErrorResolution = 0x80000000;

    // Write structure To SMBIOS Buffer
    bsize = SMBIOS_GetStructureTotalSize((UINT8 *)TypeBuffer);
    gSBUpdate->SMBIOS_InsertStructure(SmbiosBuffer, (UINT8 *)TypeBuffer, bsize);

    // Fix handle link
    SMBIOS_FixHandleLink(SmbiosBuffer);

    // Free temporary buffer
    gBS->FreePool(TypeBuffer);

}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildType19
//
// Description: Build SMBIOS Type 19
//              
//              
//
// Input:     SMBIOS_TABLE_ENTRY_POINT     *SmbiosBuffer,
//            EFI_MEMORY_SUBCLASS_RECORDS  *MemorySubClassData
//
// Output:    None  
//            
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
BuildType19(
     IN SMBIOS_TABLE_ENTRY_POINT     *SmbiosBuffer,
     IN EFI_MEMORY_SUBCLASS_RECORDS  *MemorySubClassData
)
{
     SMBIOS_MEM_ARRAY_MAP_ADDR_INFO  *TypeBuffer;
     UINT16                          bsize;

     // Allocate temporary buffer
     TypeBuffer = EfiLibAllocateZeroPool(sizeof(SMBIOS_MEM_ARRAY_MAP_ADDR_INFO)+0x100);

     // Build header of structure
     TypeBuffer->StructureType.Type     = 19; // Type 19
     TypeBuffer->StructureType.Length   = sizeof(SMBIOS_MEM_ARRAY_MAP_ADDR_INFO);
     TypeBuffer->StructureType.Handle   = gSBUpdate->SMBIOS_GetFreeHandle(SmbiosBuffer);

     // Build Content of structure
     TypeBuffer->StartingAddress        = (UINT32)(MemorySubClassData->ArrayStartAddress.MemoryArrayStartAddress / 1024);
     TypeBuffer->EndingAddress          = (UINT32)(MemorySubClassData->ArrayStartAddress.MemoryArrayEndAddress / 1024);
     TypeBuffer->MemoryArrayHandle      = (UINT16)gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 16, 0);
     TypeBuffer->PartitionWidth         = (UINT8) MemorySubClassData->ArrayStartAddress.MemoryArrayPartitionWidth;
     TypeBuffer->ExtendedStartAddr      = (MemorySubClassData->ArrayStartAddress.MemoryArrayStartAddress / 1024);
     if ((MemorySubClassData->ArrayStartAddress.MemoryArrayEndAddress / 1024) >= 0xFFFFFFFF)
     {
         TypeBuffer->ExtendedEndAddr    = (MemorySubClassData->ArrayStartAddress.MemoryArrayEndAddress / 1024);
         TypeBuffer->EndingAddress      = 0xFFFFFFFF;
     }
     else
     {
         TypeBuffer->ExtendedEndAddr    = 0;
     }

     // Write structure To SMBIOS Buffer
     bsize = SMBIOS_GetStructureTotalSize((UINT8 *)TypeBuffer);
     gSBUpdate->SMBIOS_InsertStructure(SmbiosBuffer, (UINT8 *)TypeBuffer, bsize);

     // Fix handle link
     SMBIOS_FixHandleLink(SmbiosBuffer);

     // Free temporary buffer
     gBS->FreePool(TypeBuffer);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildType20
//
// Description: Build SMBIOS Type 20
//              
// Input:     SMBIOS_TABLE_ENTRY_POINT     *SmbiosBuffer,
//            EFI_MEMORY_SUBCLASS_RECORDS  *MemorySubClassData
//
// Output:    None  
//            
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
BuildType20(
     IN SMBIOS_TABLE_ENTRY_POINT     *SmbiosBuffer,
     IN EFI_MEMORY_SUBCLASS_RECORDS  *MemorySubClassData
)
{
     SMBIOS_MEM_DEV_MAP_ADDR_INFO    *TypeBuffer;
     UINT16                          bsize;

     // Allocate temporary buffer
     TypeBuffer = EfiLibAllocateZeroPool(sizeof(SMBIOS_MEM_DEV_MAP_ADDR_INFO)+0x100);

     // Build header of structure
     TypeBuffer->StructureType.Type       = 20;  // Type 20
     TypeBuffer->StructureType.Length     = sizeof(SMBIOS_MEM_DEV_MAP_ADDR_INFO);
     TypeBuffer->StructureType.Handle     = gSBUpdate->SMBIOS_GetFreeHandle(SmbiosBuffer);

     // Build Content of structure
     TypeBuffer->StartingAddress          = (UINT32)(MemorySubClassData->DeviceStartAddress.MemoryDeviceStartAddress / 1024);
     TypeBuffer->EndingAddress            = (UINT32)(MemorySubClassData->DeviceStartAddress.MemoryDeviceEndAddress / 1024);

     TypeBuffer->MemoryDeviceHandle       = SMBIOS_UNKNOW;
     TypeBuffer->MemoryArrayMapAddrHandle = (UINT16)gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 19, 1);

     TypeBuffer->PartitionRowPosition     = 0xFF;// unknow type.
     //MemorySubClassData->DeviceStartAddress.MemoryDevicePartitionRowPosition;
     TypeBuffer->InterleavePosition       = 0xFF;// unknow type.
     //MemorySubClassData->DeviceStartAddress.MemoryDeviceInterleavePosition;
     TypeBuffer->InterleaveDataDepth      = 0xFF;// unknow type.
     //MemorySubClassData->DeviceStartAddress.MemoryDeviceInterleaveDataDepth;
     if ((MemorySubClassData->DeviceStartAddress.MemoryDeviceEndAddress / 1024) >= 0xFFFFFFFF)
     {
         TypeBuffer->ExtendedEndAddr    = (MemorySubClassData->DeviceStartAddress.MemoryDeviceEndAddress / 1024);
         TypeBuffer->EndingAddress      = 0xFFFFFFFF;
     }
     else
     {
         TypeBuffer->ExtendedEndAddr    = 0;
     }

     // Write structure To SMBIOS Buffer
     bsize = SMBIOS_GetStructureTotalSize((UINT8 *)TypeBuffer);
     gSBUpdate->SMBIOS_InsertStructure(SmbiosBuffer, (UINT8 *)TypeBuffer, bsize);
 
    // Fix handle link
     SMBIOS_FixHandleLink(SmbiosBuffer);

     // Free temporary buffer
     gBS->FreePool(TypeBuffer);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosProcessMemoryDataRecord
//
// Description: 
//            This function parses the data record and stores it into the Smbios format  
//              
// Input:     EFI_DATA_RECORD_HEADER     *Record,
//            SMBIOS_TABLE_ENTRY_POINT  *SmbiosBuffer
//
// Output:    None  
//            
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
SmbiosProcessMemoryDataRecord(
    IN EFI_DATA_RECORD_HEADER   *Record,
    IN SMBIOS_TABLE_ENTRY_POINT *SmbiosBuffer
)
{
    UINT8                           *SrcData;
    EFI_SUBCLASS_TYPE1_HEADER       *DataHeader;
    EFI_MEMORY_SUBCLASS_RECORDS     *MemorySubClassData;

    if (EfiCompareGuid (&Record->DataRecordGuid, &gEfiMemorySubClassGuid)) 
    {
        DEBUG((EFI_D_ERROR, "SMBIOS Memory Record Address:0x%X\n", Record));

        DataHeader = (EFI_SUBCLASS_TYPE1_HEADER *) (Record + 1);
        SrcData    = (UINT8 *) (DataHeader + 1);
        MemorySubClassData = (EFI_MEMORY_SUBCLASS_RECORDS *) SrcData;

        switch (DataHeader->RecordType) 
        {
            case EFI_MEMORY_ARRAY_LOCATION_RECORD_NUMBER:       // 16
                BuildType16(SmbiosBuffer, MemorySubClassData);
                break;
            case EFI_MEMORY_ARRAY_LINK_RECORD_NUMBER:           // 17
                BuildType17(SmbiosBuffer, MemorySubClassData);
#if MEMORY_ERROR_INFO
                BuildType18(SmbiosBuffer, MemorySubClassData);  // 18
#endif
                // next dimm
                DimmNumber ++;
                break;
            case EFI_MEMORY_ARRAY_START_ADDRESS_RECORD_NUMBER:  // 19
                BuildType19(SmbiosBuffer, MemorySubClassData);
                break;
            case EFI_MEMORY_DEVICE_START_ADDRESS_RECORD_NUMBER: // 20
                BuildType20(SmbiosBuffer, MemorySubClassData);
                break;
        }
    }

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DynamicUpdateMemoryRecord
//
// Description: Updates Memory related structures (Type 16-20) in
//              input Buffer with dynamically detected Record for Intel Tiano
//              SmBiosMemory Driver.
//
// Input:       UINT8       *Buffer
//
// Output:      EFI_STATUS  - EFI_SUCCESS
//                         
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DynamicUpdateMemoryRecord(
    IN  SMBIOS_TABLE_ENTRY_POINT    *Buffer
)
{
    EFI_STATUS                          Status;
    EFI_HANDLE                          DataHubHandle;
    UINTN                               HandleSize;
    UINT64                              MonotonicCount;
    EFI_DATA_HUB_PROTOCOL               *DataHub;
    EFI_DATA_RECORD_HEADER              *Record;
    EFI_GUID gEfiDataHubProtocolGuid    = EFI_DATA_HUB_PROTOCOL_GUID;
    UINT8                               BitIndex;

    Status  = EFI_SUCCESS;
    DataHub = NULL;
	
    //
    // Get the SmbusProtocol.
    //
    Status = gBS->LocateProtocol( &gEfiSmbusProtocolGuid, \
                                  NULL, \
                                  &gSmbusProtocol );
    //
    // Get the MemInfoHobProtocol.
    //
    Status = gBS->LocateProtocol (&gMemInfoHobProtocolGuid, \
                                  NULL, \
                                  &gMemInfoHobProtocol);

    //
    // Get the DxePlatformSaPolicyProtocol.
    //
    Status = gBS->LocateProtocol (&gDxePlatformSaPolicyGuid, \
                                  NULL, \
                                  &gDxePlatformSaPolicy);
    if (EFI_ERROR (Status)) return Status;

    // Check User Dimm Map
    for (BitIndex = 0; BitIndex < 2; BitIndex++) {
       if (!((gDxePlatformSaPolicy->MemoryConfig->ChannelASlotMap >> BitIndex) & BIT0)) {
         DimmSlot[BitIndex] = 0; //if not, Clear Spd sddress;
       }
       if (!((gDxePlatformSaPolicy->MemoryConfig->ChannelBSlotMap >> BitIndex) & BIT0)) {
         DimmSlot[BitIndex + 2] = 0; //if not, Clear Spd sddress;
       }
    }

    //
    // Get the Data Hub Protocol. Assume only one instance
    // of Data Hub Protocol is availabe in the system.
    //
    HandleSize = sizeof (EFI_HANDLE);

    Status = gBS->LocateHandle (
                     ByProtocol,
                     &gEfiDataHubProtocolGuid,
                     NULL,
                     &HandleSize,
                     &DataHubHandle
                 );

    if (EFI_ERROR (Status))
    {
        return EFI_SUCCESS;
    }
    Status = gBS->HandleProtocol (
                     DataHubHandle,
                     &gEfiDataHubProtocolGuid,
                     &DataHub
                 );

    if (EFI_ERROR (Status))
    {
        return EFI_SUCCESS;
    }
#if defined (MEMORY_DEVICE_INFO) && MEMORY_DEVICE_INFO == 1
    // Clean strcutures which need rebuild
    SMBIOS_DeleteStructureByType(Buffer, 16, SMBIOS_FOR_ALL);
    SMBIOS_DeleteStructureByType(Buffer, 17, SMBIOS_FOR_ALL);
#if defined (MEMORY_ERROR_INFO) && MEMORY_ERROR_INFO == 1
    SMBIOS_DeleteStructureByType(Buffer, 18, SMBIOS_FOR_ALL);
#endif
    SMBIOS_DeleteStructureByType(Buffer, 19, SMBIOS_FOR_ALL);
    SMBIOS_DeleteStructureByType(Buffer, 20, SMBIOS_FOR_ALL);
#endif
    //
    // Get all available data records from data hub
    //
    MonotonicCount  = 0;
    Record          = NULL;

    do {
            Status = DataHub->GetNextRecord (
                             DataHub,
                             &MonotonicCount,
                             NULL,
                             &Record
                            );

            if (!EFI_ERROR (Status)) 
            {
                if (Record->DataRecordClass == EFI_DATA_RECORD_CLASS_DATA)
                {
                    SmbiosProcessMemoryDataRecord (Record, Buffer);
                }
            }
     } while (!EFI_ERROR (Status) && (MonotonicCount != 0));

     return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SMIBiosUpdateMemoryRecordDriverEntryPoint
//
// Description: Update memory record DXE driver for Intel Tiano SmBiosMemory Driver.
//
// Input:       ImageHandle - Image handle. 
//              SystemTable - Pointer to the system table.
//
// Output:      EFI_STATUS  - EFI_SUCCESS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SMIBiosUpdateMemoryRecordDriverEntryPoint(
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS Status;
    EFI_GUID   gEfiSmbiosProtocolGuid = EFI_SMBIOS_PROTOCOL_GUID;
    SMBIOS_TABLE_ENTRY_POINT  *SmbiosTableEntryPoint;

    DxeInitializeDriverLib (ImageHandle, SystemTable);
    Status = gBS->LocateProtocol(&gEfiSmbiosUpdateDataProtocolGuid, NULL, &gSBUpdate);
    ASSERT_EFI_ERROR(Status);

    Status = gBS->LocateProtocol(&gEfiSmbiosProtocolGuid, NULL, &gSmbiosProtocol);
    ASSERT_EFI_ERROR(Status);
    SmbiosTableEntryPoint = gSmbiosProtocol->SmbiosGetTableEntryPoint();

    Status = DynamicUpdateMemoryRecord(SmbiosTableEntryPoint);
    ASSERT_EFI_ERROR(Status);

    return EFI_SUCCESS;
}

//-----------------------------------------------------------------------------
// SMBIOS Dynamic Maintain Functions
//-----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_DeleteStructureByType
//
// Description: SMBIOS Delete Structure Type
//
// Input:       SMBIOS_TABLE_ENTRY_POINT *SmbiosBuffer,
//              UINT8 Type, 
//              UINT8 Index
//
// Output:      UINTN count  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN
SMBIOS_DeleteStructureByType(
    IN SMBIOS_TABLE_ENTRY_POINT *SmbiosBuffer,
    IN UINT8 Type, 
    IN UINT8 Index
)
{
    UINT8 i;
    UINT16 handle;
    UINTN count;

    count = 0;
    if (Index != SMBIOS_FOR_ALL) 
    {   // for Single
        handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, Type, Index);
        if (handle != SMBIOS_NOT_FOUND)
        {
            gSBUpdate->SMBIOS_DeleteStructure(SmbiosBuffer, handle);
        }
    } else { // -1 for ALL
            for(i = 0; i < MAX_HANDLES; i++) 
            {
                handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, Type, 1);
                if (handle != SMBIOS_NOT_FOUND)
                {
                    gSBUpdate->SMBIOS_DeleteStructure(SmbiosBuffer, handle);
                    count++;
                }
            }
    }

    return count; 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_GetStructureTotalSize
//
// Description: SMBIOS get structure total size
//
// Input:       UINT8 *BufferStart
//
// Output:      UINT16 Total Size.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SMBIOS_GetStructureTotalSize(
    IN UINT8 *BufferStart
)
{
    UINT8 *BufferEnd;

    BufferEnd = BufferStart;
    BufferEnd += ((SMBIOS_STRUCTURE_HEADER*)BufferStart)->Length;
    while (*(UINT16*)BufferEnd != 0)
    {
        BufferEnd++;
    }

    return (UINT16)(BufferEnd + 2 - BufferStart);   // +2 for double zero terminator
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_GetStringBase
//
// Description: SMBIOS get String Base
//
// Input:       UINT8 *Buffer
//
// Output:      UINT8 Buffer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8* SMBIOS_GetStringBase(
    IN UINT8 *Buffer
)
{
    SMBIOS_STRUCTURE_HEADER *p;

    p = (SMBIOS_STRUCTURE_HEADER *)Buffer;
    Buffer += p->Length;

    return Buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_NextString
//
// Description: SMBIOS next String
//
// Input:       UINT8 *String
//
// Output:      String point.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8* SMBIOS_NextString(
    IN UINT8 *String
)
{
    return String+(EfiAsciiStrLen(String)+1);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_FindString
//
// Description: SMBIOS find String
//
// Input:       CHAR8 *Buffer
//              CHAR8 *String
//
// Output:      String point.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 
SMBIOS_FindString(
    IN CHAR8 *Buffer,
    IN CHAR8 *String
)
{
    CHAR8 *sp;
    UINT8 i;
    UINTN quit;
    UINTN l;

    quit = 0;
    i = 1;
    sp = SMBIOS_GetStringBase(Buffer);
    while (quit == 0) 
    {
        l = EfiAsciiStrLen(sp);
        if (l == 0)
        {
            i = 0xFF;
            quit = 1;
        } else if (EfiAsciiStrCmp(String, sp) == 0) 
        {
            quit = 1;
        } else {
            sp = SMBIOS_NextString(sp);
            i++;
        }
    }

    return i;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_AddString
//
// Description: SMBIOS add String
//
// Input:       CHAR8 *Buffer
//              CHAR8 *String
//
// Output:      UINT8
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
SMBIOS_AddString(
    IN CHAR8 *Buffer,
    IN CHAR8 *String
)
{
    CHAR8 *sp;
    UINT8 i;
    UINTN l;
    
    if (EfiAsciiStrLen(String) == 0)
    {
        EfiAsciiStrCpy(String, "[Empty]");
    }

    i = 1;
    sp = SMBIOS_GetStringBase(Buffer);
    while ((l = EfiAsciiStrLen(sp)) != 0) 
    {
        sp = sp + (l+1);
        i++;
    }

    EfiAsciiStrCpy(sp, String);
    sp = SMBIOS_NextString(sp);
    *sp = 0;

    return i;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_FixHandleLink
//
// Description: SMBIOS fix handle link
//
// Input:       SMBIOS_TABLE_ENTRY_POINT *SmbiosBuffer
//              
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
SMBIOS_FixHandleLink(
    IN  SMBIOS_TABLE_ENTRY_POINT *SmbiosBuffer
)
{
    UINT16                              handle;
    SMBIOS_PHYSICAL_MEM_ARRAY_INFO      *T16_p;
    SMBIOS_MEMORY_DEVICE_INFO           *T17_p;
    SMBIOS_MEM_ARRAY_MAP_ADDR_INFO      *T19_p;
    SMBIOS_MEM_DEV_MAP_ADDR_INFO        *T20_p;
    UINT16                              T19_Handle;
    UINT16                              T17_Size_KB;
    UINT16                              T20_Size_KB;
    UINTN                               Q_flag;
    UINT8                               i, j;
#if MEMORY_ERROR_INFO
    SMBIOS_MEMORY_ERROR_INFO            *T18_p = NULL;
#endif

    T16_p               = NULL;
    T17_p               = NULL;
    T19_p               = NULL;
    T20_p               = NULL;
    T19_Handle          = SMBIOS_UNKNOW;
    Q_flag              = 0;
    T17_Size_KB         = 0;

    // Looking for Type 19 to set MemoryArrayHandle
    handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 19, 1);
    if (handle != SMBIOS_NOT_FOUND)
    {
        T19_p = (SMBIOS_MEM_ARRAY_MAP_ADDR_INFO *)gSBUpdate->SMBIOS_GetStructureBase(SmbiosBuffer, handle);
        T19_Handle = T19_p->StructureType.Handle;
        if (T19_p->MemoryArrayHandle == SMBIOS_UNKNOW)
        {
            // Looking for Type 16
            handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 16, 1);
            if (handle != SMBIOS_NOT_FOUND)
            {
                T16_p = (SMBIOS_PHYSICAL_MEM_ARRAY_INFO *)gSBUpdate->SMBIOS_GetStructureBase(SmbiosBuffer, handle);
                T19_p->MemoryArrayHandle = T16_p->StructureType.Handle;
            }
        }
    }

#if MEMORY_ERROR_INFO
    // Looking for Type 16
    handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 16, 1);
    if (handle != SMBIOS_NOT_FOUND)
    {
        T16_p = (SMBIOS_PHYSICAL_MEM_ARRAY_INFO *)gSBUpdate->SMBIOS_GetStructureBase(SmbiosBuffer, handle);
        if (T16_p->MemErrInfoHandle == SMBIOS_UNKNOW)
        {
             handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 18, 1);
             if (handle != SMBIOS_NOT_FOUND)
             {
                 T18_p = (SMBIOS_MEMORY_ERROR_INFO *)gSBUpdate->SMBIOS_GetStructureBase(SmbiosBuffer, handle);
                 T16_p->MemErrInfoHandle = T18_p->StructureType.Handle;
             }
        }
    }

    handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 17, 1);
    if (handle != SMBIOS_NOT_FOUND)
    {
        T17_p = (SMBIOS_MEMORY_DEVICE_INFO *)gSBUpdate->SMBIOS_GetStructureBase(SmbiosBuffer, handle);
        if (T17_p->MemErrorInfoHandle == SMBIOS_UNKNOW)
        {
            handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 18, 2);
            if (handle != SMBIOS_NOT_FOUND)
            {
                T18_p = (SMBIOS_MEMORY_ERROR_INFO *)gSBUpdate->SMBIOS_GetStructureBase(SmbiosBuffer, handle);
                T17_p->MemErrorInfoHandle = T18_p->StructureType.Handle;
            }
        }
    }

    handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 17, 3);
    if (handle != SMBIOS_NOT_FOUND)
    {
        T17_p = (SMBIOS_MEMORY_DEVICE_INFO *)gSBUpdate->SMBIOS_GetStructureBase(SmbiosBuffer, handle);
        if (T17_p->MemErrorInfoHandle == SMBIOS_UNKNOW)
        {
            handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 18, 3);
            if (handle != SMBIOS_NOT_FOUND)
            {
                T18_p = (SMBIOS_MEMORY_ERROR_INFO *)gSBUpdate->SMBIOS_GetStructureBase(SmbiosBuffer, handle);
                T17_p->MemErrorInfoHandle = T18_p->StructureType.Handle;
            }
        }
    }
#endif

    Q_flag = 0;
    // Looking for Type 20 to set MemoryArrayMapAddrHandle and MemoryDeviceHandle
    for(i = 1; i < MAX_HANDLES; i++)
    {
        T20_Size_KB = 0;
    
        handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 20, i);
        if (handle != SMBIOS_NOT_FOUND)
        {
            T20_p = (SMBIOS_MEM_DEV_MAP_ADDR_INFO *)gSBUpdate->SMBIOS_GetStructureBase(SmbiosBuffer, handle);
            T20_p->MemoryArrayMapAddrHandle = T19_Handle;
            if (T20_p->MemoryDeviceHandle == SMBIOS_UNKNOW)
            {
                T20_Size_KB =(UINT16) T20_p->EndingAddress + 1;

                // Looking for Type 17
                for(j = i; j < MAX_HANDLES; j++)
                {
                    handle = gSBUpdate->SMBIOS_FindStructure(SmbiosBuffer, 17, j);
                    if (handle != SMBIOS_NOT_FOUND)
                    {
                        T17_p = (SMBIOS_MEMORY_DEVICE_INFO *)gSBUpdate->SMBIOS_GetStructureBase(SmbiosBuffer, handle);

                        T17_Size_KB = (T17_p->Size & 0x7FFF) * ((T17_p->Size & 0x8000) ? 1 : 1024);
                        if (T17_Size_KB == T20_Size_KB)
                        {
                            T20_p->MemoryDeviceHandle = T17_p->StructureType.Handle;
                        }
                    }
                }
            }
            Q_flag++;
        }

        if (Q_flag == 0)
            break;
    }
}

#if (EFI_SPECIFICATION_VERSION < 0x0002000A)
//-----------------------------------------------------------------------------
// HII Functions
//-----------------------------------------------------------------------------
EFI_HII_HANDLE      HiiHandle;
EFI_HII_PROTOCOL    *Hii = NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitHiiString
//
// Description: Init Hii string
//
// Input:       VOID
//              
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
InitHiiString(VOID)
{
    EFI_STATUS          Status;
    UINT16              HandleBufferLength;
    EFI_HII_HANDLE      *HiiHandleBuffer;
    UINTN               NumberOfHiiHandles;
    UINTN               Index;
    UINT16              Length;
    EFI_GUID            HiiGuid;
  
    if (Hii == NULL)
    {
        HandleBufferLength  = 0x1000;
        HiiHandleBuffer     = NULL;
        HiiHandle = 0;

        //
        // Locate HII protocol
        //
        Status = gBS->LocateProtocol (&gEfiHiiProtocolGuid, NULL, &Hii);
        ASSERT_EFI_ERROR (Status);

        HiiHandleBuffer = EfiLibAllocateZeroPool (HandleBufferLength);

        Status          = Hii->FindHandles (Hii, &HandleBufferLength, HiiHandleBuffer);
        ASSERT_EFI_ERROR (Status);

        //
        // Get the Hii Handle that matches the StructureNode->ProducerName
        //
        NumberOfHiiHandles = HandleBufferLength / sizeof (EFI_HII_HANDLE);
        for (Index = 0; Index < NumberOfHiiHandles; Index++)
        {
            Length = 0;
            Status = ExtractDataFromHiiHandle (
                        HiiHandleBuffer[Index],
                        &Length,
                        NULL,
                        &HiiGuid
                        );
            if (EfiCompareGuid (&gEfiMemorySubClassDriverGuid, &HiiGuid))
            {
                HiiHandle = HiiHandleBuffer[Index];
                break;
            }
        }
        gBS->FreePool (HiiHandleBuffer);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HiiGetString
//
// Description: Init get string
//
// Input:       STRING_REF     Token
//              
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *
HiiGetString(
    IN  STRING_REF    Token
)
{
    UINTN             StringBufferLength;
    CHAR16            *StringBuffer;
    EFI_STATUS        Status;

    InitHiiString();

    Status              = EFI_SUCCESS;
    StringBufferLength  = 0x100;
    StringBuffer        = EfiLibAllocateZeroPool(StringBufferLength);
    ASSERT(StringBuffer);

    //
    // Find the string based on the current language
    //
    Status = Hii->GetString (
                    Hii,
                    HiiHandle,
                    Token,
                    FALSE,
                    NULL,
                    &StringBufferLength,
                    StringBuffer
                    );

    if (EFI_ERROR (Status))
    {
        gBS->FreePool(StringBuffer);
        StringBuffer = NULL;
    }
  
    return StringBuffer;
}
#endif //EFI_SPECIFICATION_VERSION < 0x0002000A

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConvertChar16ToChar8
//
// Description: Convert char 16 to char 8
//
// Input:       CHAR8      *Dest
//              CHAR16     *Src
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ConvertChar16ToChar8 (
    IN CHAR8      *Dest,
    IN CHAR16     *Src
)
{
    while (*Src)
    {
        *Dest++ = (UINT8) (*Src++);
    }

    *Dest = 0;
}  

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   TransferHiiStringToSmbios
//
// Description: Transfer Hii string to Smbios
//
// Input:       CHAR8      *Structure
//              STRING_REF Token
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
TransferHiiStringToSmbios (
    IN UINT8       *Structure,
    IN STRING_REF  Token
)
{
    CHAR8        *Buffer;
    UINTN        BufferSize;
    UINT8        i;
    CHAR16       *String;

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
    EFI_STATUS    Status;
#endif

    BufferSize = 0x100;
    Buffer = EfiLibAllocateZeroPool(BufferSize);  
    ASSERT(Buffer);
    i = (UINT8) -1;

#if (EFI_SPECIFICATION_VERSION < 0x0002000A)
    String = HiiGetString(Token);
#else

    Status = GetStringFromToken (&gEfiMemorySubClassDriverGuid, Token, (EFI_STRING *)&String);
    ASSERT_EFI_ERROR(Status);

#endif

    ConvertChar16ToChar8(Buffer, String);

    i = SMBIOS_AddString(Structure, Buffer);
    gBS->FreePool(String);
    gBS->FreePool(Buffer);
    return i;
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
