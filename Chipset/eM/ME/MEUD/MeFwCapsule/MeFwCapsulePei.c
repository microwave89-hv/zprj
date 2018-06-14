//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
/** @file MeFwCapsulePei.c
    ME FW Capsule Update Pei driver.
**/
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <PEI.h>
#include <AmiPeiLib.h>
#include <FlashUpd.h>
#include <Token.h>
#include <PPI\NBPPI.h>
#include <FlashUpd.h>
#include <AmiHobs.h>
//----------------------------------------------------------------------------
// Function Externs
EFI_GUID mFlashUpdBootModePpiGuid = EFI_PEI_BOOT_IN_FLASH_UPDATE_MODE_PEIM_PPI;
EFI_GUID mAmiPeiBeforeMrcGuid = AMI_PEI_BEFORE_MRC_GUID;
EFI_GUID mAmiCapsuleHobGuid = AMI_CAPSULE_HOB_GUID;
//----------------------------------------------------------------------------
// Local prototypes
EFI_STATUS
MeFwBootOnFlashUpdateNotify (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *NullPpi
);
EFI_STATUS
MeFwBeforeMrcNotify (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *NullPpi
);

// PPI to be installed
static 
EFI_PEI_NOTIFY_DESCRIPTOR 
MeFwBootOnFlashUpdateNotifyList[] = {
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &mFlashUpdBootModePpiGuid, MeFwBootOnFlashUpdateNotify },
};

static 
EFI_PEI_NOTIFY_DESCRIPTOR 
MeFwBeforeMrcNotifyList[] = {
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
      &mAmiPeiBeforeMrcGuid, MeFwBeforeMrcNotify }
};

//----------------------------------------------------------------------------
// Local Variables

//----------------------------------------------------------------------------
// Function Definitions
#define R_PCH_ACPI_PM1_STS                        0x00
#define B_PCH_ACPI_PM1_STS_WAK                    0x8000
#define R_PCH_ACPI_PM1_CNT                        0x04
#define B_PCH_ACPI_PM1_CNT_SLP_TYP                0x00001C00
#define R_PCH_RST_CNT                             0xCF9
#define V_PCH_RST_CNT_SOFTRESET                   0x04
#define V_PCH_RST_CNT_SOFTSTARTSTATE              0x00

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MeFwBootOnFlashUpdateNotify
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MeFwBootOnFlashUpdateNotify (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *NullPpi
)
{
    VOID                    *p;

    for ((*PeiServices)->GetHobList(PeiServices,&p); \
            !(FindNextHobByGuid(&mAmiCapsuleHobGuid, &p));  ) {
        // When the gFlashUpdBootModePpi is installed, bios identify the Capsule Guid
        // either APTIO FW or Windows FW Capsule, so, we just check the Capsule Length
        // for determine whether contains the ME FW. 
        if ((((AMI_CAPSULE_HOB*)p)->CapsuleLength != FWCAPSULE_IMAGE_SIZE) && \
            (((AMI_CAPSULE_HOB*)p)->CapsuleLength != \
                    (FV_MEFWCAP_SIZE + FWCAPSULE_MAX_HDR_SIZE))) continue;
        // Clear Wake Status (WAK_STS) and Sleep Type (SLP_TYP)
        IoWrite16(PM_BASE_ADDRESS + R_PCH_ACPI_PM1_STS, B_PCH_ACPI_PM1_STS_WAK);
        IoWrite16(PM_BASE_ADDRESS + R_PCH_ACPI_PM1_CNT, \
          IoRead16(PM_BASE_ADDRESS + R_PCH_ACPI_PM1_CNT) & ~B_PCH_ACPI_PM1_CNT_SLP_TYP);
        // Since, HECI interface not work if S3 resume path, to generate a Soft Reset
        // to re-activate HECI.
        IoWrite8(R_PCH_RST_CNT, V_PCH_RST_CNT_SOFTSTARTSTATE);
        IoWrite8(R_PCH_RST_CNT, V_PCH_RST_CNT_SOFTRESET);
        EFI_DEADLOOP()
    }
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MeFwBeforeMrcNotify
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MeFwBeforeMrcNotify (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *NullPpi
)
{
    EFI_STATUS          Status;
    EFI_BOOT_MODE       BootMode;
 
    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if (EFI_ERROR(Status) || (BootMode != BOOT_ON_S3_RESUME)) return EFI_SUCCESS;
    (*PeiServices)->NotifyPpi (PeiServices, MeFwBootOnFlashUpdateNotifyList);       
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MeFwCapsulePeiEntry
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MeFwCapsulePeiEntry (
    IN EFI_FFS_FILE_HEADER  *FfsHeader,
    IN EFI_PEI_SERVICES     **PeiServices
)
{
    (*PeiServices)->NotifyPpi (PeiServices, MeFwBeforeMrcNotifyList);
    return EFI_SUCCESS;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
