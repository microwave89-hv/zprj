//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/AcpiModeEnable/AcpiModeEnable.c 17    5/23/13 1:57a Scottyang $
//
// $Revision: 17 $
//
// $Date: 5/23/13 1:57a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/AcpiModeEnable/AcpiModeEnable.c $
// 
// 17    5/23/13 1:57a Scottyang
// [TAG]  		EIP120623
// [Category]  	Improvement
// [Description]  	LCD turn on automatically when resume from S3.
// [Files]  		SBPEI.c, SBDxe.c, AcpiModeEnable.c
// 
// 16    5/09/13 6:32a Scottyang
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	S3 resume Verb table will error when enable token
// "AMI_INIT_VERB_TABLE_IN_S3".
// [RootCause]  	The FrontPanel is wrong.
// [Solution]  	Change FrontPanel to frontSideNo.
// [Files]  		AcpiModeEnable.c
// 
// 15    4/23/13 4:20a Wesleychen
// [TAG]         None
// [Category]    Improvement
// [Description] Add token "ONLY_CLEAR_RTC_EN_IN_PEI" for improve
//               "EIP120623".
// [Files]       AcpiModeEnable.c; SB.SDL; SBPEI.c
// 
// 14    4/18/13 12:17a Wesleychen
// [TAG]        EIP120623
// [Category]   Bug Fix
// [Severity]   Important
// [Symptom]    LCD doesn't turn on automatically when resume from S3.
// [RootCause]  PM1_STS (PMBASE+00h) are cleared in EnableAcpiMode().
// [Solution]   Avoid PM1_STS clearing behavior is occurring in S3
//              resuming.
//              *AcpiModeEnable.c Rev#8~11(EIP101628 & EIP118531) are are
//              no need be existence.
// [Files]      SBPEI.c; AcpiModeEnable.c
// 
// 12    4/08/13 2:27a Wesleychen
// Revise the content of history.
// 
// 7     10/12/12 2:08a Scottyang
// [TAG]         EIP76432
// [Category]  	 Bug Fix
// [Severity]  	 Normal
// [Symptom]  	 It will BSOD ,while system boot to OS at "starting windows"
//               press the KB in succession.
// [RootCause]   System BSOD is caused by a large number of SMI generated.
// [Solution]    Disable legacy USB SMI in ACPI enable stage.
// [Files]       AcpiModeEnable.c; SBDXE.c
// 
// 6     10/01/12 5:51a Victortu
// [TAG]         None
// [Category]    Improvement
// [Description] Update EIP#102349 "GPE0 setting and SCI routing for ULT
//               platfoem".
// [Files]       AcpiModeEnable.c, AcpiModeEnable.sdl
// 
// 5     9/26/12 3:57a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Fixed RTC on iFFS failed.
// [Files]         AcpiModeEnable.c
// 
// 4     9/12/12 5:16a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Modify for ULT GPIO changed by PCH LPT-LP EDS 1.0.
// [Files]         SB.H, SB.sdl, AcpiModeEnable.c, AcpiModeEnable.sdl,
// SBPEI.c
// 
// 3     7/27/12 6:16a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update to support ULT Platform.
// [Files]         SB.H, SB.mak, SB.sdl, SB.sd, SBSetup.c,
// AcpiModeEnable.c, SBDxe.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c, SBPPI.h, Pch.sdl
// 
// 2     4/25/12 9:25a Victortu
// [TAG]         None
// [Category]    Improvement
// [Description] Apply AcpiModeEnable support PI 1.2.
// [Files]       AcpiModeEnable.c
// 
// 1     2/08/12 8:30a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        AcpiModeEnable.C
//
// Description: Provide functions to enable and disable ACPI mode
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Token.h>
#include <AmiDxeLib.h>

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION>=0x4028B)
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmSwDispatch2.h>
#else
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#endif

#include <Protocol\DevicePath.h>
#include <Token.h>
#include <AmiCspLib.h>
#include <PchAccess.h>
#include "RTC.h"
#include "HDAVBTBL.h"
#include "AcpiModeEnable.h"

#if defined(PchDxePlatformPolicy_SUPPORT) && PchDxePlatformPolicy_SUPPORT
#include <PchDxePlatformPolicy.h>
#endif // PchDxePlatformPolicy_SUPPORT end

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
#define AMI_SMM_SW_DISPATCH_PROTOCOL EFI_SMM_SW_DISPATCH2_PROTOCOL
#define AMI_SMM_SW_DISPATCH_CONTEXT  EFI_SMM_SW_REGISTER_CONTEXT
#define SMM_CHILD_DISPATCH_SUCCESS   EFI_SUCCESS
#else
#define AMI_SMM_SW_DISPATCH_PROTOCOL EFI_SMM_SW_DISPATCH_PROTOCOL
#define AMI_SMM_SW_DISPATCH_CONTEXT  EFI_SMM_SW_DISPATCH_CONTEXT
#define SMM_CHILD_DISPATCH_SUCCESS
#endif

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
VOID InitParts (
    IN VOID*                        DispatchHandle,
    IN CONST VOID                   *DispatchContext
);

VOID InitParts2 (
    IN VOID*                        DispatchHandle,
    IN CONST VOID                   *DispatchContext
);

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

ACPI_DISPATCH_LINK  *gAcpiEnDispatchHead = 0, *gAcpiEnDispatchTail = 0;
ACPI_DISPATCH_LINK  *gAcpiDisDispatchHead = 0, *gAcpiDisDispatchTail = 0;

UINT8  gFirstInFlag = 0;
UINT16 wPM1_SaveState;
UINT32 dGPE_SaveState;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_SMM_BASE2_PROTOCOL  *gSmmBase2;
#endif

// GUID Definition(s)

EFI_GUID gEfiAcpiEnDispatchProtocolGuid = EFI_ACPI_EN_DISPATCH_PROTOCOL_GUID;
EFI_GUID gEfiAcpiDisDispatchProtocolGuid = EFI_ACPI_DIS_DISPATCH_PROTOCOL_GUID;

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)
//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbGpioSciInit
//
// Description: Programming the corresponding GPIO pin to generate SCI#.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SbGpioSciInit (VOID)
{
  UINT32 GpioRoute;
  UINT8  GpioIndex;
  UINT32 GpioSmiEnable;
  UINT32 GpioNmiEnable;

  if (GetPchSeries() == PchLp) {
    GpioRoute = READ_IO32(GPIO_BASE_ADDRESS+GP_IOREG_GPI_ROUT2);
    GpioSmiEnable = READ_IO32(GPIO_BASE_ADDRESS+GP_IOREG_ALTGP_SMI_EN);
    GpioNmiEnable = READ_IO32(GPIO_BASE_ADDRESS+GP_IOREG_PCHLP_GPI_NMI_EN);

    GpioRoute &= ~GPIO_SCI_BITMAP;
    GpioSmiEnable &= ~GPIO_SCI_BITMAP;
    GpioNmiEnable &= ~GPIO_SCI_BITMAP;

    WRITE_IO16(GPIO_BASE_ADDRESS+GP_IOREG_GPI_ROUT2, GpioRoute);  
    WRITE_IO16(GPIO_BASE_ADDRESS+GP_IOREG_ALTGP_SMI_EN, GpioSmiEnable); 
    WRITE_IO16(GPIO_BASE_ADDRESS+GP_IOREG_PCHLP_GPI_NMI_EN, GpioNmiEnable); 
  } else {
    GpioRoute = READ_PCI32_SB(R_PCH_LPC_GPI_ROUT);
    for (GpioIndex = 0; GpioIndex < 16; GpioIndex++) {
      if (GPIO_SCI_BITMAP & (UINT16)(1 << GpioIndex)) {
        GpioRoute &= ~(3 << (GpioIndex * 2));
        GpioRoute |= (2 << (GpioIndex * 2));
      }
    }
    WRITE_PCI32_SB(R_PCH_LPC_GPI_ROUT, GpioRoute);
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EnableAcpiMode
//
// Description: This function enable ACPI mode by clearing all SMI and
//              enabling SCI generation
//              This routine is also called on a S3 resume for special ACPI
//              programming.
//              Status should not be cleared on S3 resume. Enables are
//              already taken care of.
//
// Input:       PI 0.91, 1.0
//                  DispatchHandle   - SMI dispatcher handle
//                  *DispatchContext - Pointer to the dispatch context
//              PI 1.1, 1.2
//                  DispatchHandle  - SMI dispatcher handle
//                  *DispatchContext- Points to an optional S/W SMI context
//                  CommBuffer      - Points to the optional communication
//                                    buffer
//                  CommBufferSize  - Points to the size of the optional
//                                    communication buffer
//
// Output:      EFI_STATUS if the new SMM PI is applied.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS EnableAcpiMode (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
#else
VOID EnableAcpiMode (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext )
#endif
{

    ACPI_DISPATCH_LINK      *Link;
    UINT16                  wordValue;
    UINT32                  dwordValue;
    PCH_SERIES              PchSeries = GetPchSeries();

#if defined EMUL6064_SUPPORT && EMUL6064_SUPPORT == 1
    if (READ_PCI8_SB(R_PCH_LPC_ULKMC)) // 0x94
      WRITE_PCI8_SB(R_PCH_LPC_ULKMC, 0); // 0x94
#endif

    if ( gFirstInFlag == 0 ) {
      gFirstInFlag = 1;

      //  Check if WAK bit is set, if yes skip clearing status
      wordValue = READ_IO16_PM(ACPI_IOREG_PM1_STS); // 0x00
      if (wordValue & B_PCH_ACPI_PM1_STS_WAK) {
      //  NAPA-CHANGES Disable and Clear GPE0 Sources
        if (PchSeries == PchLp) {
          WRITE_IO32_PM(ACPI_PCHLP_IOREG_GPE0_EN+0x0c, 0x0000);    //GPE0_EN 0x9C
          WRITE_IO32_PM(ACPI_PCHLP_IOREG_GPE0_STS+0x0c, 0xffffffff);  //GPE0_STS 0x8C
        } else {
          WRITE_IO32_PM(ACPI_IOREG_GPE0_EN, 0x0000);    //GPE0_EN 0x28
          WRITE_IO32_PM(ACPI_IOREG_GPE0_STS, 0xffffffff);  //GPE0_STS 0x20
        }
      } else {
        //Disable SMI Sources
        dwordValue = READ_IO32_PM(ACPI_IOREG_SMI_EN);    //SMI_EN (SMI Control and Enable register.)

        dwordValue &= ~(B_PCH_SMI_EN_ON_SLP_EN | B_PCH_SMI_EN_SWSMI_TMR);  // Clear SLP_SMI_EN and SWSMI_TMR bit.

                                        // [EIP76432]>>
#if defined EMUL6064_SUPPORT && EMUL6064_SUPPORT == 1
      dwordValue &= ~(B_PCH_SMI_EN_LEGACY_USB);
#endif
                                        // <<[EIP76432]

        WRITE_IO32_PM(ACPI_IOREG_SMI_EN, dwordValue);

        //Disable and Clear PM1 Sources except power button
        wPM1_SaveState = READ_IO16_PM(ACPI_IOREG_PM1_EN);  //PM1_EN
        WRITE_IO16_PM(ACPI_IOREG_PM1_EN, (UINT16)B_PCH_ACPI_PM1_EN_PWRBTN);    //PM1_EN Bit 8: PWRBTN_EN
        WRITE_IO16_PM(ACPI_IOREG_PM1_STS, 0xffff);    //PM1_STS 0x00

        //Disable and Clear GPE0 Sources
        if (PchSeries == PchLp) {
          dGPE_SaveState = READ_IO16_PM(ACPI_PCHLP_IOREG_GPE0_EN+0x0c);//GPE0_EN 0x9C
          WRITE_IO32_PM(ACPI_PCHLP_IOREG_GPE0_EN+0x0c, 0x00000000);    //GPE0_EN 0x9C
          WRITE_IO32_PM(ACPI_PCHLP_IOREG_GPE0_STS+0x0c, 0xffffffff);  //GPE0_STS 0x8C
        } else {
          dGPE_SaveState = READ_IO16_PM(ACPI_IOREG_GPE0_EN);//GPE0_EN 0x28
          WRITE_IO32_PM(ACPI_IOREG_GPE0_EN, 0x00000000);    //GPE0_EN 0x28
          WRITE_IO32_PM(ACPI_IOREG_GPE0_STS, 0xffffffff);  //GPE0_STS
        }

        //Set day of month alarm invalid - ACPI 1.0 section 4.7.2.4
        IoWrite8(CMOS_ADDR_PORT, 0xd | 0x80);                //RTC_REGD
        IoWrite8(CMOS_DATA_PORT, 0);
      }
    }

    //SCI_EN = 1
    SET_IO8_PM(ACPI_IOREG_PM1_CNTL, B_PCH_ACPI_PM1_CNT_SCI_EN); //PM1_CNT

    SbGpioSciInit();

    InitParts(DispatchHandle, DispatchContext);

    for (Link = gAcpiEnDispatchHead; Link; Link = Link->Link)
    {
        Link->Function(Link);
    }

    WRITE_IO8 (PCI_DEBUG_PORT, SW_SMI_ACPI_ENABLE);

    return SMM_CHILD_DISPATCH_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   DisableAcpiMode
//
// Description: This function disables ACPI mode by enabling SMI generation
//
// Input:       PI 0.91, 1.0
//                  DispatchHandle   - SMI dispatcher handle
//                  *DispatchContext - Pointer to the dispatch context
//              PI 1.1, 1.2
//                  DispatchHandle  - SMI dispatcher handle
//                  *DispatchContext- Points to an optional S/W SMI context
//                  CommBuffer      - Points to the optional communication
//                                    buffer
//                  CommBufferSize  - Points to the size of the optional
//                                    communication buffer
//
// Output:      EFI_STATUS if the new SMM PI is applied.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS DisableAcpiMode (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
#else
VOID DisableAcpiMode (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext )
#endif
{
      ACPI_DISPATCH_LINK *Link;

    //Clear PM Sources and set Enables
    WRITE_IO16_PM(ACPI_IOREG_PM1_STS, 0xffff); // 0x00
    WRITE_IO16_PM(ACPI_IOREG_PM1_EN, wPM1_SaveState); // 0x02

    //Clear GPE0 Sources and set Enables
    if (GetPchSeries() == PchLp) {
      WRITE_IO32_PM(ACPI_PCHLP_IOREG_GPE0_STS + 0x0c, 0xffffffff);  //GPE0_STS 0x8C
      WRITE_IO32_PM(ACPI_PCHLP_IOREG_GPE0_EN + 0x0c, dGPE_SaveState); //GPE0_EN 0x9C
    } else {
      WRITE_IO32_PM(ACPI_IOREG_GPE0_STS + 0, 0xffffffff);  //GPE0_STS 0x20
      WRITE_IO32_PM(ACPI_IOREG_GPE0_STS + 4, 0xffffffff);  //GPE0_STS 0x24
      WRITE_IO32_PM(ACPI_IOREG_GPE0_EN, dGPE_SaveState); //GPE0_EN 0x28
    }

    //Disable SCI
    RESET_IO8_PM(ACPI_IOREG_PM1_CNTL, BIT00); // 0x04
    InitParts2(DispatchHandle, DispatchContext);
    for (Link = gAcpiDisDispatchHead; Link; Link = Link->Link)
    {
        Link->Function(Link);
    }


    WRITE_IO8 (PCI_DEBUG_PORT, SW_SMI_ACPI_DISABLE);

    return SMM_CHILD_DISPATCH_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AddLink
//
// Description: Create and add link to specified list.
//
// Input:  Size -
//              Head -
//              Tail -
//
// Output:     VOID Pointer
//
// Modified:
//
// Referrals:   SmmAllocatePool
//
// Notes:       Here is the control flow of this function:
//              1. Allocate Link in Smm Pool.
//              2. Add Link to end.
//              3. Return Link address.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID * AddLink(
    IN UINT32       Size,
    IN VOID         **Head,
    IN VOID         **Tail)
{
    VOID *Link;

    if (pSmst->SmmAllocatePool(0, Size, &Link) != EFI_SUCCESS) return 0;

    ((GENERIC_LINK*)Link)->Link = 0;
    if (!*Head)
    {
        *Head = *Tail = Link;
    }
    else
    {
        ((GENERIC_LINK*)*Tail)->Link = Link;
        *Tail = Link;
    }

    return Link;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RemoveLink
//
// Description: Remove link from specified list.
//
// Input:  Handle - EFI Handle
//              Head -
//              Tail -
//
// Output:     BOOLEAN
//                  TRUE if link was removed. FALSE if link not in the list.
//
// Modified:
//
// Referrals:   SmmFreePool
//
// Notes:       Here is the control flow of this function:
//              1. Search link list for Link.
//              2. Remove link from list.
//              3. Free link.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN RemoveLink(
    IN EFI_HANDLE   Handle,
    IN VOID         **Head,
    IN VOID         **Tail)
{
    GENERIC_LINK *PrevLink, *Link;

    PrevLink = *Head;

    // Is link first. Link address is the same as the Handle.
    if (((GENERIC_LINK*)*Head) == Handle)
    {
        if (PrevLink == *Tail) *Tail = 0; // If Tail = Head, then 0.
        *Head = PrevLink->Link;
        pSmst->SmmFreePool(PrevLink);
        return TRUE;
    }

    // Find Link.
    for (Link = PrevLink->Link; Link; PrevLink = Link, Link = Link->Link)
    {
        if (Link == Handle)     // Link address is the same as the Handle.
        {
            if (Link == *Tail) *Tail = PrevLink;
            PrevLink->Link = Link->Link;
            pSmst->SmmFreePool(Link);
            return TRUE;
        }
    }

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiAcpiEnRegister
//
// Description: Register a Link on ACPI enable SMI.
//
// Input:  This -
//              Function -
//              Context -
//
//
// Output:     Handle -
//              EFI_STATUS
//
// Modified:    gAcpiEnDispatchHead, gAcpiEnDispatchTail
//
// Referrals:   AddLink
//
// Notes:       Here is the control flow of this function:
//              1. Verify if Context if valid. If invalid,
//                 return EFI_INVALID_PARAMETER.
//              2. Allocate structure and add to link list.
//              3. Fill link.
//              4. Enable Smi Source.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiAcpiEnRegister(
    IN EFI_ACPI_DISPATCH_PROTOCOL   *This,
    IN EFI_ACPI_DISPATCH            Function,
    OUT EFI_HANDLE                  *Handle)
{
    ACPI_DISPATCH_LINK *NewLink;

    NewLink = AddLink(sizeof(ACPI_DISPATCH_LINK), \
                      &gAcpiEnDispatchHead, \
                      &gAcpiEnDispatchTail);
    if (!NewLink) return EFI_OUT_OF_RESOURCES;

    NewLink->Function   = Function;
    *Handle = NewLink;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiAcpiEnUnregister
//
// Description: Unregister a Link on ACPI enable SMI.
//
// Input:  This -
//              Handle -
//
// Output:     EFI_STATUS
//
// Modified:    gAcpiEnDispatchHead, gAcpiEnDispatchTail
//
// Referrals:   RemoveLink
//
// Notes:       Here is the control flow of this function:
//              1. Remove link. If no link, return EFI_INVALID_PARAMETER.
//              2. Disable SMI Source if no other handlers using source.
//              3. Return EFI_SUCCESS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiAcpiEnUnregister(
    IN EFI_ACPI_DISPATCH_PROTOCOL   *This,
    IN EFI_HANDLE                   Handle)
{
    if (!RemoveLink(Handle, &gAcpiEnDispatchHead, &gAcpiEnDispatchTail))
        return EFI_INVALID_PARAMETER;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiAcpiDisRegister
//
// Description: Register a Link on ACPI disable SMI.
//
// Input:  This -
//              Function -
//              *Context -
//
//
// Output:     Handle - EFI Handle
//              EFI_STATUS
//
// Modified:    gAcpiDisDispatchHead, gAcpiDisDispatchTail
//
// Referrals:   AddLink
//
// Notes:       Here is the control flow of this function:
//              1. Verify if Context if valid. If invalid,
//                 return EFI_INVALID_PARAMETER.
//              2. Allocate structure and add to link list.
//              3. Fill link.
//              4. Enable Smi Source.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiAcpiDisRegister(
    IN EFI_ACPI_DISPATCH_PROTOCOL   *This,
    IN EFI_ACPI_DISPATCH            Function,
    OUT EFI_HANDLE                  *Handle)
{
    ACPI_DISPATCH_LINK *NewLink;

    NewLink = AddLink(sizeof(ACPI_DISPATCH_LINK), \
                      &gAcpiDisDispatchHead, \
                      &gAcpiDisDispatchTail);
    if (!NewLink) return EFI_OUT_OF_RESOURCES;

    NewLink->Function   = Function;
    *Handle = NewLink;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiAcpiDisUnregister
//
// Description: Unregister a Link on ACPI Disable SMI.
//
// Input:  This -
//              Handle - EFI Handle
//
// Output:     EFI_STATUS
//
// Modified:    gAcpiDisDispatchHead, gAcpiDisDispatchTail
//
// Referrals:   RemoveLink
//
// Notes:       Here is the control flow of this function:
//              1. Remove link. If no link, return EFI_INVALID_PARAMETER.
//              2. Disable SMI Source if no other handlers using source.
//              3. Return EFI_SUCCESS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiAcpiDisUnregister(
    IN EFI_ACPI_DISPATCH_PROTOCOL   *This,
    IN EFI_HANDLE                   Handle)
{
    if (!RemoveLink(Handle, &gAcpiDisDispatchHead, &gAcpiDisDispatchTail))
        return EFI_INVALID_PARAMETER;
    return EFI_SUCCESS;
}

EFI_ACPI_DISPATCH_PROTOCOL gEfiAcpiEnDispatchProtocol = \
        {EfiAcpiEnRegister, EfiAcpiEnUnregister};

EFI_ACPI_DISPATCH_PROTOCOL gEfiAcpiDisDispatchProtocol = \
        {EfiAcpiDisRegister, EfiAcpiDisUnregister};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbAcpiS3PatchedFunction
//
// Description: This function will be called when ACPI S3 resuming.
//
// Input:       PI 0.91, 1.0
//                  DispatchHandle   - SMI dispatcher handle
//                  *DispatchContext - Pointer to the dispatch context
//              PI 1.1, 1.2
//                  DispatchHandle  - SMI dispatcher handle
//                  *DispatchContext- Points to an optional S/W SMI context
//                  CommBuffer      - Points to the optional communication
//                                    buffer
//                  CommBufferSize  - Points to the size of the optional
//                                    communication buffer
//
// Output:      EFI_STATUS if the new SMM PI is applied.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS SbAcpiS3PatchedFunction (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *Context OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
#else
VOID SbAcpiS3PatchedFunction (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext )
#endif
{
#if AMI_INIT_VERB_TABLE_IN_S3
    UINT8               CodecIdx;
    UINT8               j;
    UINT8               i;
    UINT16              Cmd16;
    UINT16              TimeOut;
    UINT16              SDIPin;
    UINT32              Buffer32;
    UINT32              CodecId;
    UINT32              Base32;
    UINT8               VerbTblSize = sizeof(HdaVerbTbl) / \
                                                      sizeof(HDA_VERB_TABLE);
    volatile UINT32     *pHdaVerbTbl;

    if ((READ_MEM8_RCRB(RCRB_MMIO_FD) & 0x10) == 0) { // 0x3418
        Base32 = READ_PCI32_HDA(R_PCH_HDA_HDBARL) & B_PCH_HDA_HDBARL_LBA; // 0x10
        Cmd16 = READ_PCI16_HDA(R_PCH_HDA_COMMAND);
        WRITE_PCI16_HDA(R_PCH_HDA_COMMAND, Cmd16 | B_PCH_HDA_COMMAND_MSE);

        // Deassert the CRST bit in Azalia to cause the link to start up
        SET_MEM8(Base32 | R_HDA_GCTL, B_HDA_GCTL_CRST);

        // Turn off the link by writing a 0 to the Controller Reset bit in
        // HD Audio, poll Controller Reset bit until it reads back as 0.
        RESET_MEM8(Base32 | R_HDA_GCTL, B_HDA_GCTL_CRST);

        for (TimeOut = 0; TimeOut < 0x8000; TimeOut++)
           if ((READ_MEM8(Base32 | R_HDA_GCTL) & B_HDA_GCTL_CRST) == 0) break;

        // Turn on the link again by  writing a 1 to Controller Reset bit
        // This causes a codec link re-enumeration. Delay for 1ms, 
        // then poll Controller Reset bit until it reads back 1.
        SET_MEM8(Base32 | R_HDA_GCTL, B_HDA_GCTL_CRST);
        CountTime(1000, PM_BASE_ADDRESS); // 1ms

        for (TimeOut = 0; TimeOut < 0x8000; TimeOut++)
           if (READ_MEM8(Base32 | R_HDA_GCTL) & B_HDA_GCTL_CRST) break;

        // Set the map of SDI pins
        SDIPin = READ_MEM8(Base32 | R_HDA_STATESTS);
        for (CodecIdx = MAX_NUM_HD_CODECS; CodecIdx; CodecIdx--) {
           if (SDIPin & (1 << (CodecIdx - 1))) {
             SDIPin &= ~(1 << (CodecIdx - 1));
             for (TimeOut = 0; TimeOut < 0x8000; TimeOut++) {
                if ((READ_MEM16(Base32 | R_HDA_IRS) & B_HDA_IRS_ICB) == 0) break;
             }

             if (TimeOut == 0x8000) {
               RESET_MEM8(Base32 | R_HDA_GCTL, B_HDA_GCTL_CRST);
               SET_MEM8(Base32 | R_HDA_GCTL, B_HDA_GCTL_CRST);
             }

             Buffer32 = ((CodecIdx - 1) << 28) | 0xf0000;
             WRITE_MEM32(Base32|R_HDA_IC, Buffer32);

             SET_MEM16(Base32 | R_HDA_IRS, B_HDA_IRS_ICB | B_HDA_IRS_IRV);

             while ((READ_MEM16(Base32 | R_HDA_IRS) & (B_HDA_IRS_ICB | B_HDA_IRS_IRV)) != B_HDA_IRS_IRV);

             CodecId = READ_MEM32(Base32 | R_HDA_IR);

             // CheckforValidCodec

             if (VerbTblSize == 0) break;

             for (j = 0; j < VerbTblSize; j++) {
                if (HdaVerbTbl[j].CodecId32 == CodecId) {
                  pHdaVerbTbl = HdaVerbTbl[j].VerbPtr;
                  Buffer32 = *pHdaVerbTbl;
                  if ((UINT8)(Buffer32 >> 28) == (CodecIdx - 1))
                    break;
                }
             }

             // Program Pin Widget Configuration
             if (j != VerbTblSize) {
               pHdaVerbTbl = HdaVerbTbl[j].VerbPtr;
               for(i = 0; i < (HdaVerbTbl[j].frontSideNo + HdaVerbTbl[j].RearSideNo) * 4; i++) {
                 // Poll the ICB bit of the ICS register at HDABAR + 68h[0] until it return 0.
                 for (TimeOut = 0; TimeOut < 0x8000; TimeOut++) {
                   if ((READ_MEM16(Base32 | R_HDA_IRS) & B_HDA_IRS_ICB) == 0)
                    break; 
                 }
                 // Write the current verb(DWORD) to the IC register at HDABAR + 60h
                 WRITE_MEM32(Base32 | R_HDA_IC, *pHdaVerbTbl++);
                 // Send verb to Codec
                 SET_MEM16(Base32 | R_HDA_IRS, (B_HDA_IRS_ICB | B_HDA_IRS_IRV));
               }
            }
        }
      }
    }

    // Restore Command Register
    WRITE_PCI16_HDA(R_PCH_HDA_COMMAND, Cmd16);
#endif

    return SMM_CHILD_DISPATCH_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: Install ACPI Software SMI Handlers.
//
// Input:       ImageHandle  - Image handle
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InSmmFunction (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS                   Status;
    EFI_HANDLE                   Handle = NULL;
    EFI_HANDLE  DummyHandle = NULL;
    AMI_SMM_SW_DISPATCH_PROTOCOL *SwDispatch = NULL;
    AMI_SMM_SW_DISPATCH_CONTEXT  AcpiEnableContext = {SW_SMI_ACPI_ENABLE};
    AMI_SMM_SW_DISPATCH_CONTEXT  AcpiDisableContext = {SW_SMI_ACPI_DISABLE};
    AMI_SMM_SW_DISPATCH_CONTEXT  AcpiS3PatchContext = {SW_SMI_SB_ACPI_S3};
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    EFI_SMM_SYSTEM_TABLE2   *pSmst2;
#endif

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status = InitAmiSmmLib( ImageHandle, SystemTable );
    if (EFI_ERROR(Status)) return Status;

    // We are in SMM, retrieve the pointer to SMM System Table
    Status = gSmmBase2->GetSmstLocation( gSmmBase2, &pSmst2);
    if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;

    Status = pSmst2->SmmLocateProtocol( &gEfiSmmSwDispatch2ProtocolGuid , \
                                       NULL, \
                                       &SwDispatch );
    TRACE((TRACE_ALWAYS, "Smm Locate Protocol gEfiSmmSwDispatch2ProtocolGuid, Status = %r\n",Status));
#else
    Status = pBS->LocateProtocol( &gEfiSmmSwDispatchProtocolGuid , \
                                  NULL, \
                                  &SwDispatch );
#endif
    if (EFI_ERROR(Status)) return Status;

    Status = SwDispatch->Register( SwDispatch, \
                                   SbAcpiS3PatchedFunction, \
                                   &AcpiS3PatchContext, \
                                   &Handle );
    if (EFI_ERROR(Status)) return Status;

    Status = SwDispatch->Register( SwDispatch, \
                                   EnableAcpiMode, \
                                   &AcpiEnableContext, \
                                   &Handle );
    if (EFI_ERROR(Status)) return Status;

    Status = SwDispatch->Register( SwDispatch, \
                                   DisableAcpiMode, \
                                   &AcpiDisableContext,\
                                   &Handle );
    if (EFI_ERROR(Status)) return Status;

    Status = pBS->InstallMultipleProtocolInterfaces(
             &DummyHandle, 
             &gEfiAcpiEnDispatchProtocolGuid, 
             &gEfiAcpiEnDispatchProtocol, 
             &gEfiAcpiDisDispatchProtocolGuid, 
             &gEfiAcpiDisDispatchProtocol, 
             NULL);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AcpiModeEnableInit
//
// Description: installs appropriate ACPI enable/disable Dispatch Protocol.
//
// Input:       ImageHandle  - Image handle
//              *SystemTable - Pointer to the system table 
//
// Output:      EFI_STATUS
//
// Referrals:   InitAmiLib, InitSmmHandler
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS AcpiModeEnableInit (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS Status = EFI_SUCCESS;

    InitAmiLib( ImageHandle, SystemTable );

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status = SystemTable->BootServices->LocateProtocol( \
                                                &gEfiSmmBase2ProtocolGuid, \
                                                NULL, \
                                                &gSmmBase2 );
    ASSERT_EFI_ERROR(Status);
#endif

    return InitSmmHandler( ImageHandle, SystemTable, InSmmFunction, NULL );
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
