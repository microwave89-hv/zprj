//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/CSP_MEUD/ME80/CSP_MEUD.c 14    5/14/15 4:33a Tristinchou $
//
// $Revision: 14 $
//
// $Date: 5/14/15 4:33a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/CSP_MEUD/ME80/CSP_MEUD.c $
// 
// 14    5/14/15 4:33a Tristinchou
// [TAG]  		EIP215437
// [Category]  	New Feature
// [Description]  	ME capsule update support on SharkBay
// 
// 13    3/05/14 2:51a Tristinchou
// [TAG]  		EIP147099
// [Category]  	New Feature
// [Description]  	Support ME FWUpdate API
// 
// 12    10/01/13 1:40a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	backward compatible
// 
// 11    9/30/13 6:05a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Support PI 1.2
// 
// 10    8/23/13 4:14a Tristinchou
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Fix build error with CrescentBay project.
// 
// 9     5/16/13 6:24a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	1. Pre-allocate Memory while ME is disable(Avoid
// allocate memory error message).
// 2. Support PDR reiong is on top of SPI(AFU 3.05 and
// 4.6.3_Flash_Combined_2_36)
// 
// 8     3/15/13 5:18a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Add new token BITS_OF_SPI_DENSITY
// [Files]  		CSP_MEUD.c
// CSP_MEUD.h
// CSP_MEUD.sdl
// CSP_MEUD.mak
// CSP_MEUD.cif
// 
// 7     11/29/12 4:42a Klzhan
// BugFix : Can't update ME when 2 SPI installed. A token is added
// (Lynx Point spec updated, BIT define chaged).
// 
// 6     11/29/12 2:24a Klzhan
// BugFix : Mac address restored to wrong address.
// 
// 5     11/28/12 4:03a Klzhan
// Getting wrong Flash capacity when 2 flash component.
// 
// 4     9/07/12 4:46a Klzhan
// Support ME 9.
// 
// 1     12/12/11 2:38a Wesleychen
// Update to rev.2 for FD region length correction.
// 
// 2     5/09/11 3:25a Klzhan
// Correct FD region length.
// 
// 1     4/22/11 2:47a Klzhan
// Initial check - in
// 
//  
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	CSP_MEUD.c
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <SB.h>
#include "CoreBiosMsg.h"
#include "ReferenceCode\ME\Protocol\Heci\Heci.h"
#include "MeChipset.h"
#include "PchRegs\PchRegsRcrb.h"
#include "CSP_MEUD.h"
#include <MEUD\MEUD.h>
#include "Flash.h"
#include "MEFwUpdLcl\MeFwUpdLclProtocol.h"

#if defined SecSMIFlash_SUPPORT && SecSMIFlash_SUPPORT == 1
#include <Protocol\SecSmiFlash.h>
#endif

#if PI_SPECIFICATION_VERSION >= 0x1000A
#include <Protocol\SmmBase2.h>
#define RETURN(status) {return status;}

extern EFI_GUID gEfiSmmBase2ProtocolGuid;
EFI_SMM_BASE2_PROTOCOL          *gSmmBase2;
EFI_SMM_SYSTEM_TABLE2	        *gSmst;
#endif
#if defined SecSMIFlash_SUPPORT && SecSMIFlash_SUPPORT == 1
static EFI_GUID	gEfiSecSmiFlashProtocolGuid = SEC_SMI_FLASH_GUID;
UINT32 *gFwCapsuleAddress = NULL;
#endif

EFI_GUID gEfiHeciProtocolGuid       = HECI_PROTOCOL_GUID;

BOOLEAN	IsIgnition;
BOOLEAN	Is_SECOVR_JMPR;
BOOLEAN	Is_MEFW;

EFI_PHYSICAL_ADDRESS   Phy_Address;
OFBD_TC_55_ME_PROCESS_STRUCT  *StructPtr;
UINT8   MacAddr[6];
UINT8	Nounce[8];
UINT32	Factory_Base;
UINT32	Factory_Limit;
#ifdef _HECI_PROTOCOL_H
HECI_PROTOCOL     *mHeci = NULL;
#else
EFI_HECI_PROTOCOL *mHeci = NULL;
#endif
EFI_PHYSICAL_ADDRESS RomBuffer = NULL;
EFI_PHYSICAL_ADDRESS BlockBuffer = NULL;

EFI_GUID mMeFwUpdLclProtocolGuid = ME_FW_UPD_LOCAL_PROTOCOL_GUID;
ME_FW_UPDATE_LOCAL_PROTOCOL     *mMeFwUpdateLocalProtocol = NULL;
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GET_FW_VERSION
//
// Description: Get ME FW Version.
//
// Input:   NONE
//
// Output:  EFI_STATUS
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GET_FW_VERSION(
    IN UINT16 *MeFwVersionData
)
{
  EFI_STATUS        Status;
  UINT32            Length;
  GEN_GET_FW_VER    *MsgGenGetFwVersion;
  GEN_GET_FW_VER    GenGetFwVersion;
  UINT32            MeMode;
  GEN_GET_FW_VER_ACK     MsgGenGetFwVersionAck;

  Status = mHeci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  //
  // Allocate MsgGenGetFwVersion data structure
  //
  MsgGenGetFwVersion = &GenGetFwVersion;
  MsgGenGetFwVersion->MKHIHeader.Data = 0;
  MsgGenGetFwVersion->MKHIHeader.Fields.GroupId = MKHI_GEN_GROUP_ID;
  MsgGenGetFwVersion->MKHIHeader.Fields.Command = GEN_GET_FW_VERSION_CMD;
  MsgGenGetFwVersion->MKHIHeader.Fields.IsResponse = 0;
  Length = sizeof (GEN_GET_FW_VER);
  //
  // Send Get Firmware Version Request to ME
  Status = mHeci->SendMsg (
                  (UINT32 *) MsgGenGetFwVersion,
                  Length,
                  BIOS_FIXED_HOST_ADDR,
                  HECI_CORE_MESSAGE_ADDR
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Length = sizeof (GEN_GET_FW_VER_ACK);
  Status = mHeci->ReadMsg (
                  BLOCKING,
                  (UINT32 *) &MsgGenGetFwVersionAck,
                  &Length
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  MeFwVersionData[0] = MsgGenGetFwVersionAck.Data.CodeMajor;
  MeFwVersionData[1] = MsgGenGetFwVersionAck.Data.CodeMinor;
  MeFwVersionData[2] = MsgGenGetFwVersionAck.Data.CodeHotFix;
  MeFwVersionData[3] = MsgGenGetFwVersionAck.Data.CodeBuildNo;

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetHFS
//
// Description: Get Host Firmware Status pass to MEUD
//
// Input:   NONE
//
// Output:  Host Firmware Status
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetHFS(VOID)
{
    UINT32  R_HFS;
    EFI_STATUS  Status;
    if(mHeci == NULL)
    {
        R_HFS = 0;
        return R_HFS;
    }
    Status = mHeci->GetMeStatus(&R_HFS);
    if (EFI_ERROR (Status)) {
        R_HFS = 0;
    }
    return R_HFS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   HMRFPO_ENABLE_MSG
//
// Description: Send Enable HECI message to enable Ignition Firmwate update.
//
// Input:   NONE
//
// Output:  NONE
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HMRFPO_ENABLE_MSG(VOID)
{
    EFI_STATUS                        Status = EFI_SUCCESS;
    MKHI_HMRFPO_ENABLE                HmrfpoEnableRequest;
    MKHI_HMRFPO_ENABLE_RESPONSE       HmrfpoEnableResponse;
    UINT32                            HeciLength;

    // Function 1 and 4 will call this function, check is ME or Ignition.
    if(Is_MEFW)
    {
        // If ME FW check GPIO33 assert or not
        if(Is_SECOVR_JMPR)
            return EFI_SUCCESS;
        else
            return EFI_UNSUPPORTED;
    }
    if(mHeci == NULL)
        return EFI_NOT_READY;

    HmrfpoEnableRequest.MkhiHeader.Fields.GroupId     = MKHI_SPI_GROUP_ID;
    HmrfpoEnableRequest.MkhiHeader.Fields.Command     = HMRFPO_ENABLE_CMD_ID;
    HmrfpoEnableRequest.MkhiHeader.Fields.IsResponse  = 1;

    MemSet( &HmrfpoEnableRequest.Nonce ,8,0);

    HeciLength = sizeof (MKHI_HMRFPO_ENABLE);

    Status = mHeci->SendMsg (
                 (UINT32 *) &HmrfpoEnableRequest,
                 HeciLength,
                 BIOS_FIXED_HOST_ADDR,
                 HECI_CORE_MESSAGE_ADDR
             );
    if (EFI_ERROR (Status)) {
        IoWrite8(0x80, 0xA0);
        return Status;
    }

    HeciLength = sizeof (MKHI_HMRFPO_ENABLE_RESPONSE);

    Status = mHeci->ReadMsg (
                 BLOCKING,
                 (UINT32 *) &HmrfpoEnableResponse,
                 &HeciLength
             );
    if (EFI_ERROR (Status)) {
        IoWrite8(0x80, 0xA1);
        return Status;
    }

    return Status;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   HMRFPO_LOCK_MSG
//
// Description: Send LOCK HECI message and lock ME.
//
// Input:   NONE
//
// Output:  NONE
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HMRFPO_LOCK_MSG(VOID)
{
    EFI_STATUS                      Status;
    MKHI_HMRFPO_LOCK                HmrfpoLockRequest;
    MKHI_HMRFPO_LOCK_RESPONSE       HmrfpoLockResponse;
    UINT32                          HeciLength;
    // Function 1 and 4 will call this function, check is ME or Ignition.
    if(Is_MEFW)
    {
        // If ME FW check GPIO33 assert or not
        if(Is_SECOVR_JMPR)
            return EFI_SUCCESS;
        else
            return EFI_UNSUPPORTED;
    }
    if(mHeci == NULL)
        return EFI_NOT_READY;
    HmrfpoLockRequest.MkhiHeader.Fields.GroupId     = MKHI_SPI_GROUP_ID;
    HmrfpoLockRequest.MkhiHeader.Fields.Command     = HMRFPO_LOCK_CMD_ID;
    HmrfpoLockRequest.MkhiHeader.Fields.IsResponse  = 1;

    HeciLength = sizeof (MKHI_HMRFPO_LOCK);
    Status = mHeci->SendMsg (
                 (UINT32 *) &HmrfpoLockRequest,
                 HeciLength,
                 BIOS_FIXED_HOST_ADDR,
                 HECI_CORE_MESSAGE_ADDR
             );
    if (EFI_ERROR (Status)) {
        IoWrite8(0x80, 0xA0);
        return Status;
    }

    HeciLength = sizeof (MKHI_HMRFPO_LOCK_RESPONSE);
    Status = mHeci->ReadMsg (
                 BLOCKING,
                 (UINT32 *) &HmrfpoLockResponse,
                 &HeciLength
             );
    if (EFI_ERROR (Status)) {
        IoWrite8(0x80, 0xA1);
        return Status;
    } else {
        Factory_Base   = HmrfpoLockResponse.FactoryDefaultBase;
        Factory_Limit  = HmrfpoLockResponse.FactoryDefaultLimit;
    }

    return Status;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetRegionOffset
//
// Description:	Get GBE Region Offet of whole FlashPart
//
// Input:
//      VOID
// Output:
//      UINT32  The offset of GBE Region
//
// Returns:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetRegionOffset(
    UINT8    Region,
    UINT32*  Offset,
    UINT32*  Length
)
{
    volatile UINT32	*FDOC;
    volatile UINT32	*FDOD;
    UINT32	FlashDescriptorSig = 0x0FF0A55A;
    UINT32	Buffer32, RegionStart, RegionEnd;


    FDOC = (UINT32*)(pSPIBASE + 0xB0);
    FDOD = (UINT32*)(pSPIBASE + 0xB4);
    *FDOC = 0;

    if (*FDOD != FlashDescriptorSig)
        return EFI_UNSUPPORTED;

    switch(Region)
    {
        // Flash Descriptor
        case 0:
        *FDOC = 0x2000;
        break;

        // BIOS
        case 1:
        *FDOC = 0x2004;
        break;

        // ME
        case 2:
        *FDOC = 0x2008;
        break;

        // GBE
        case 3:
        *FDOC = 0x200C;
        break;

        // Platform Data
        case 4:
        *FDOC = 0x2010;
        break;

        default:
        return EFI_UNSUPPORTED;
        break;
    }
    Buffer32 = *FDOD;
    RegionEnd = Buffer32 >> 16;
    RegionStart = Buffer32 & 0xFFFF;

    *Offset = RegionStart << 12;
    *Length = (RegionEnd - RegionStart + 1) << 12;
    if((Region == 0) && (RegionEnd == 0))
    {
        *Length = 0x1000;
        return EFI_SUCCESS;
    }
    if(RegionEnd == 0)
    {
        *Length = 0;
        return EFI_NOT_FOUND;
    }

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetFlashCapacity
//
// Description: Send a HECI message to lock ME.
//
// Input:   NONE
//
// Output:  FlashDensity - Real Flash Size
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetFlashCapacity(VOID)
{
    volatile UINT32	*FDOC;
    volatile UINT32	*FDOD;
    UINT32	FlashDescriptorSig = 0x0FF0A55A;
    UINT16	Components;
    UINT8	i,j;
    static      UINT32 FlashDensity = 0;

    if(FlashDensity)
        return FlashDensity;

    FDOC = (UINT32*)(pSPIBASE + 0xB0);
    FDOD = (UINT32*)(pSPIBASE + 0xB4);
    *FDOC = 0;

    if (*FDOD != FlashDescriptorSig)
        return 0;

    *FDOC = 0x04;
    Components = (*FDOD >> 8) & 0x03;

    *FDOC = 0x1000;
    j = *FDOD;


    for (i=0; i<(Components + 1); i++)
    {
        switch (j & 0x07)
        {
        case 0:
            FlashDensity += 0x80000;
            break;
        case 1:
            FlashDensity += 0x100000;
            break;
        case 2:
            FlashDensity += 0x200000;
            break;
        case 3:
            FlashDensity += 0x400000;
            break;
        case 4:
            FlashDensity += 0x800000;
            break;
        case 5:
            FlashDensity += 0x1000000;
            break;
        default:
            break;
        }
#if BITS_OF_SPI_DENSITY
        j = j >> 4;
#else
        j = j >> 3;
#endif
    }
    return	FlashDensity;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CSP_ReportMEInfo
//
// Description: Report ME Base address and Length to AFU
//
// Input:   BASE_Address - address of ME region to be updated
//          Length - Length of ME region to be updated
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CSP_ReportMEInfo
(
    IN UINT8 Func_Num,
    IN OUT UINT32* BASE_Address,
    IN OUT UINT32* Length
)
{
    switch (Func_Num)
    {
    case 0:

        *BASE_Address = 0;
        *Length = GetFlashCapacity() - FLASH_SIZE;
        return EFI_UNSUPPORTED;

        break;
    case 3:
        // Flash the whole SPI but BIOS region
        *BASE_Address = 0;
        *Length = GetFlashCapacity() - FLASH_SIZE;
        if (Is_SECOVR_JMPR && Is_MEFW)
            return EFI_SUCCESS;
        else
            return EFI_UNSUPPORTED;
        break;
    default:
        return EFI_UNSUPPORTED;
        break;
    }
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HeciCallback
//
// Description:	Locate Heci protocol callback
//
// Input:
//      IN EFI_EVENT    Event
//      IN VOID         *Context
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HeciCallback(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
    EFI_STATUS Status;

    Status = pBS->LocateProtocol (
                  &gEfiHeciProtocolGuid,
                  NULL,
                  &mHeci
                  );

    if(EFI_ERROR(Status))
        mHeci = NULL;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MeFwUpdLclCallback
//
// Description:	Locate ME Firmware update local protocol callback
//
// Input:
//      IN CONST EFI_GUID *Protocol
//      IN VOID *Interface
//      IN EFI_HANDLE Handle
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MeFwUpdLclCallback (
	IN CONST EFI_GUID   *Protocol,
	IN VOID             *Interface,
	IN EFI_HANDLE       Handle
)
{
    EFI_STATUS Status;
    
    Status = gSmst->SmmLocateProtocol(
                        &mMeFwUpdLclProtocolGuid , NULL,
                        &mMeFwUpdateLocalProtocol );
    if( EFI_ERROR(Status) )
        mMeFwUpdateLocalProtocol = NULL;

    return Status;
}
#if defined SecSMIFlash_SUPPORT && SecSMIFlash_SUPPORT == 1
/**
 * Callback funciotn on Secure SmiFlash Protocol for saving FW Capsule Buffer address.
 * @param Protocol OPTIONAL 
 * @param Interface OPTIONAL
 * @param Handle OPTIONAL
 * @retval EFI_SUCCESS Secure SmiFlash Protocol installed.
 * @retval EFI_NOT_FOUND Secure SmiFlash Protocol not install yet.
**/
static
EFI_STATUS 
SecSmiFlashProtocolCallback (
  IN const EFI_GUID	    *Protocol,
  IN VOID               *Interface,
  IN EFI_HANDLE         Handle
)
{
    EFI_SEC_SMI_FLASH_PROTOCOL *SecSmiFlash = NULL;
	if (EFI_ERROR(pBS->LocateProtocol( \
            &gEfiSecSmiFlashProtocolGuid, NULL, &SecSmiFlash)))
        return EFI_NOT_FOUND;
    gFwCapsuleAddress = SecSmiFlash->pFwCapsule;
	return EFI_SUCCESS;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CSP_MEUDInSmm
//
// Description: Get Host Firmware Status.
//              If needed, Send LOCK if needed in SMM.
//
// Input:   NONE
//
// Output:  NONE
//
// Returns: NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CSP_MEUDInSmm(VOID)
{
    UINT32	Buffer32;
    EFI_STATUS  Status;
    VOID        *MeFwUpdLclReg = NULL;

#if PI_SPECIFICATION_VERSION >= 0x1000A
    
    Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &gSmmBase2);
    if (EFI_ERROR(Status)) return;

    Status = gSmmBase2->GetSmstLocation (gSmmBase2, &gSmst);
    if (EFI_ERROR(Status)) return;

#endif

    Buffer32 = *(volatile UINT32 *)((UINTN)PCIEX_BASE_ADDRESS + \
               (UINTN)(HECI_BUS << 20) + (UINTN)(HECI_DEV << 15) + \
               (UINTN)(HECI_FUN << 12) + (UINTN)(0x40));

    if(Buffer32 == 0xFFFFFFFF)
    {
        UINT8* pRCBA_DIS2 = (UINT8*)(SB_RCRB_BASE_ADDRESS + R_PCH_RCRB_FD2);
        // Enable HECI Device
        *pRCBA_DIS2 &= 0xFD;
        // Read Again
        pBS->Stall (1000);//1ms
        Buffer32 = *(volatile UINT32 *)((UINTN)PCIEX_BASE_ADDRESS + \
                   (UINTN)(HECI_BUS << 20) + (UINTN)(HECI_DEV << 15) + \
                   (UINTN)(HECI_FUN << 12) + (UINTN)(0x40));
        // Follow Spec ,Disable HECI Device
        *pRCBA_DIS2 |= 0x02;
    }
    // Check If Ignition FW
    // ME 8.0 is no more Ignition FW, It should alway be FALSE
    if (((Buffer32 >> 16) & 0x0F) == 1)
        IsIgnition = TRUE;
    else
        IsIgnition = FALSE;

    // Check If GPIO33 Assert
    if ( (((Buffer32 >> 16) & 0x0F) == 4) ||  (((Buffer32 >> 16) & 0x0F) == 5))
    {
        Is_SECOVR_JMPR = TRUE;
        Status = pBS->AllocatePages(AllocateAnyPages, 
                                    EfiReservedMemoryType, 
                                    EFI_SIZE_TO_PAGES (GetFlashCapacity()), 
                                    &RomBuffer);
        if(EFI_ERROR(Status))
            RomBuffer = NULL;

        Status = pBS->AllocatePages(AllocateAnyPages, 
                                    EfiReservedMemoryType, 
                                    EFI_SIZE_TO_PAGES (FLASH_BLOCK_SIZE), 
                                    &BlockBuffer);
        if(EFI_ERROR(Status))
            BlockBuffer = NULL;
    }else
        Is_SECOVR_JMPR = FALSE;

    // Check If ME FW
    if ((((Buffer32 >> 16) & 0x0F) == 0) ||
        (((Buffer32 >> 16) & 0x0F) == 3) ||
        (((Buffer32 >> 16) & 0x0F) == 4) ||
        (((Buffer32 >> 16) & 0x0F) == 5))
        Is_MEFW = TRUE;
    else
        Is_MEFW = FALSE;

    //ME Firmware update local
    Status = gSmst->SmmLocateProtocol( &mMeFwUpdLclProtocolGuid , NULL,
                                       &mMeFwUpdateLocalProtocol );
    if( EFI_ERROR(Status) )
    {
        gSmst->SmmRegisterProtocolNotify( &mMeFwUpdLclProtocolGuid,
                                          MeFwUpdLclCallback,
                                          &MeFwUpdLclReg );
    }
    
#if defined SecSMIFlash_SUPPORT && SecSMIFlash_SUPPORT == 1
    {
   		//VOID		    *Registration;
        // Create SecSmiFlash Protocol Callback to get and save the FwCapsule 
        // Address, because of the address could be cleared after calling the 
        // functions of Secure SMI Flash protocol.
        //pSmst->SmmRegisterProtocolNotify(&gEfiSecSmiFlashProtocolGuid, \
        //                            SecSmiFlashProtocolCallback, &Registration);
		SecSmiFlashProtocolCallback(NULL, NULL, NULL);					        
    }    
#endif  
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MEProcessHandleResult
//
// Description:	Handle ME Process
//
// Input:
//      UpdateResult
//      Message
// Output:
//      VOID
//
// Returns:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
MEProcessHandleResult(
    IN UINT16   Result,
    IN CHAR8*   Message
)
{
    StructPtr->UpdateResult = Result;
    MemCpy((UINT8*)(StructPtr->ddMessageBuffer), 
                    Message, Strlen(Message));

    *(CHAR8*)(StructPtr->ddMessageBuffer + Strlen(Message)) = 0;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandleBuffer
//
// Description:	Init the Length and Offset need to be updated
//              If needed, send ENABLE MESSAGE
//
// Input:
//      UpdateResult
//      Message
// Output:
//      VOID
//
// Returns:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
HandleBuffer(
    IN OUT UINT32*   ProgramOffset,
    IN OUT UINT32*   ProgramLength,
    IN OUT UINT8*    Step,
    IN     BOOLEAN   InSmm
)
{
    EFI_STATUS    Status;
    UINT32        Offset, Length;
    UINT32        HFS = GetHFS();

    switch(StructPtr->bBlockType)
    {
        case FDT_BLK:
            Status = GetRegionOffset(0, &Offset, &Length);
            *Step = 0;
        break;

        case PDR_BLK:
            Status = GetRegionOffset(4, &Offset, &Length);
            if(Status == EFI_NOT_FOUND)
                return EFI_UNSUPPORTED;
            *Step = 0;
        break;

        case GBE_BLK:
            Status = GetRegionOffset(3, &Offset, &Length);
            if(Status == EFI_NOT_FOUND)
                return EFI_UNSUPPORTED;
            // Store Mac address
            if(Length)
            {
                UINT8* Address = (UINT8*)FLASH_BASE_ADDRESS(Offset);
                FlashRead(Address, MacAddr, 6);
            }
            *Step = 0;
        break;

        case ME_BLK:
            Status = GetRegionOffset(2, &Offset, &Length);
            if((HFS & BIT05) || (HFS & BIT10))
                *Step = 2;
            else
                *Step = 1;

        break;
        default:
            *Step = 0;
            return EFI_UNSUPPORTED;
        break;
    }
    *ProgramOffset = Offset;
    *ProgramLength = Length;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdateRegions
//
// Description:	UpdateRegions
//
// Input:
//      Buffer
//
// Output:
//      VOID
//
// Returns:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UpdateRegions(
    IN UINT8*    Buffer,
    IN BOOLEAN   InSmm
)
{
    static UINT32          Offset, Length;
    UINT8*                 Address;
    EFI_STATUS             Status;
    BOOLEAN                FlashStatus = TRUE, NeedToVerify = FALSE;
    static UINT8           Step = 0;
    static BOOLEAN         NewRegion;
    UINTN                  Counter = 0;
    static UINT8*          ProgramBuffer;
    UINT8*                 BufferForVerify = (UINT8*)BlockBuffer;
    UINT32                 i;
    // Prepare Offset and Length to be updated
    // If BIT02 , update buffer
    if((StructPtr->bHandleRequest & BIT02))
    {
        Status = HandleBuffer(&Offset, &Length, &Step, InSmm);
        if(EFI_ERROR(Status))
        {
            MEProcessHandleResult(BIT03, 
                      "UN SUPPORT TYPE");
            return Status;
        }
        // Frist In
        NewRegion = TRUE;
        ProgramBuffer = (UINT8*)(Phy_Address + Offset);
    }

    // Set MAC address to buffer
    if(((StructPtr->bBlockType) == GBE_BLK) && NewRegion)
        MemCpy((Buffer + Offset),MacAddr,6);

    if(NewRegion)
    {
        NewRegion = FALSE;
    }

    Address = (UINT8*)FLASH_BASE_ADDRESS(Offset);
    FlashBlockWriteEnable(Address);

    FlashEraseCommand(Address);

    // System hangs when using physical address.
    // So, verify erase complete or not.
    FlashStatus = TRUE;
    FlashReadCommand(Address, BufferForVerify, FLASH_BLOCK_SIZE);

    for(i = 0 ; (i < FLASH_BLOCK_SIZE) && (*(BufferForVerify + i) == 0xFF) ; i++);
    if(i != FLASH_BLOCK_SIZE)
        FlashStatus = FALSE;
    if(FlashStatus)
    {
        FlashProgramCommand(Address, ProgramBuffer, FLASH_BLOCK_SIZE);
        FlashReadCommand(Address, BufferForVerify, FLASH_BLOCK_SIZE);
        for(i = 0 ; (i < FLASH_BLOCK_SIZE) && (*(BufferForVerify + i) == *(BufferForVerify + i)) ; i++);
        if(i != FLASH_BLOCK_SIZE)
            FlashStatus = FALSE;
        if(FlashStatus)
            Status = EFI_SUCCESS;
        else
            Status = EFI_DEVICE_ERROR;
    }else
        Status = EFI_DEVICE_ERROR;
    FlashBlockWriteDisable(Address);
    ProgramBuffer = ProgramBuffer + FLASH_BLOCK_SIZE;
    Length -= FLASH_BLOCK_SIZE;
    Offset += FLASH_BLOCK_SIZE;

    // End of Region Update
    if(Length == 0)
    {
        NewRegion = TRUE;
    }
    // TODO :
    // OEM can output message here in every block updated.
    // Remember to Set BIT02
    else
    {
        MEProcessHandleResult((BIT01), 
                         " ");
        return EFI_SUCCESS;
    }
    // Show Strings
    if(!EFI_ERROR(Status))
    {

        switch(StructPtr->bBlockType)
        {
            case FDT_BLK:
                MEProcessHandleResult((BIT03 | BIT02), 
                          "Update success for /FDT!!");
            break;
            case PDR_BLK:
                MEProcessHandleResult((BIT03 | BIT02), 
                          "Update success for /PDR!!");
            break;
            case GBE_BLK:
                MEProcessHandleResult((BIT03 | BIT02), 
                          "Update success for /GBE!!");
            break;

            case ME_OPR_BLK:
                MEProcessHandleResult((BIT03 | BIT02), 
                          "Update success for /OPR!!");
            break;

            default:
                MEProcessHandleResult((BIT03 | BIT02), 
                          "Update success for /MER!!");
            break;
        }
    }else
    {
        switch(StructPtr->bBlockType)
        {
            case FDT_BLK:
                MEProcessHandleResult((BIT03 | BIT02), 
                          "/FDT is Locked !!");
            break;

            default:
                MEProcessHandleResult((BIT00 | BIT02), 
                          "Update Fail !!");
            break;
        }
    }

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MEProcessHandler
//
// Description:	Handle ME Process
//
// Input:
//      VOID
// Output:
//      OFBD_TC_55_ME_PROCESS_STRUCT
//
// Returns:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
MEProcessHandler
(
    IN OUT OFBD_TC_55_ME_PROCESS_STRUCT  **MEProcessStructPtr
)
{
    EFI_STATUS                    Status;
    static UINTN                  NumberOfPages;
    static UINT32                 SizeCopied;
    static BOOLEAN                UseSmmMem = FALSE;
    static EFI_PHYSICAL_ADDRESS   SMM_Address;
    static UINT8                  HeciIsHide = 0;
    static BOOLEAN                UseMeFwUpdLcl = FALSE;
    static UINTN                  BufferLength = 0;

    StructPtr = *MEProcessStructPtr;
    switch(StructPtr->bHandleRequest)
    {
        // Allocate Buffer
        case 1:
/*
            if ((Mmio32(SB_RCBA, 0x3428) & BIT01) != 0)
            {
                MmioRW32((SB_RCBA+0x3428), 0, BIT01);
                HeciIsHide = 1;
            }
*/
            NumberOfPages = StructPtr->TotalBlocks;
#if PI_SPECIFICATION_VERSION >= 0x1000A
            Status = gSmst->SmmAllocatePages(AllocateAnyPages, 
#else
            Status = pSmst->SmmAllocatePages(AllocateAnyPages, 
#endif
                     EfiRuntimeServicesData, NumberOfPages, &SMM_Address);
            if(!EFI_ERROR(Status))
            {
                UseSmmMem = TRUE;
                Phy_Address = SMM_Address;
            }else
                Phy_Address = RomBuffer;
            // No memory allocated
            if(!Phy_Address)
            {
                if( ( mMeFwUpdateLocalProtocol != NULL ) &&
                    ( mMeFwUpdateLocalProtocol->FwUpdBufferAddress != NULL ) )
                {
                    UseMeFwUpdLcl = TRUE;
                    Phy_Address = mMeFwUpdateLocalProtocol->FwUpdBufferAddress;
                    BufferLength = mMeFwUpdateLocalProtocol->FwUpdBufferLength;
                    SizeCopied = 0;
                    break;
                }
                MEProcessHandleResult((BIT00 | BIT02), 
                              "Error : No Memory Allocated!!");
            }
            SizeCopied = 0;
        break;

        // Recieve Data from AFU
        case 2:
            if( UseMeFwUpdLcl && 
                ( SizeCopied + StructPtr->ddMeDataSize > BufferLength ) )
            {
                MEProcessHandleResult((BIT00 | BIT02), 
                              "Error : No Memory Allocated!!");
                SizeCopied = 0;
                break;
            }
            MemCpy((UINT8*)(Phy_Address + SizeCopied),
                    (UINT8*)StructPtr->ddMeDataBuffer,StructPtr->ddMeDataSize);
            SizeCopied += StructPtr->ddMeDataSize;

        break;

        // Update
        case 4:
#if (OFBD_VERSION >= 0x0220)
            DoNotConvert = TRUE;
#endif
            UpdateRegions((UINT8*)Phy_Address, TRUE);
        break;

        // Continue....
        case 8:
            UpdateRegions((UINT8*)Phy_Address, TRUE);
        break;

        // Free Buffer
        case 0x10:
#if (OFBD_VERSION >= 0x0220)
            DoNotConvert = FALSE;
#endif
            if(UseSmmMem)
#if PI_SPECIFICATION_VERSION >= 0x1000A
                gSmst->SmmFreePages(Phy_Address, NumberOfPages);
#else
                pSmst->SmmFreePages(Phy_Address, NumberOfPages);
#endif


//            if (HeciIsHide)
//               MmioRW32((SB_RCBA+0x3428), BIT01, 0);
        break;
        
        case 0x20:
            if( UseMeFwUpdLcl )
                mMeFwUpdateLocalProtocol->FwUpdLcl( mMeFwUpdateLocalProtocol, (UINT8*)Phy_Address, SizeCopied );
        break;
        
#if defined SecSMIFlash_SUPPORT && SecSMIFlash_SUPPORT == 1
        // ME FW Capsule Update functions.
        case 3: // ME FW Capsule Update. (ME FW only) 
        case 5: // ME FW Capsule Update. (BIOS + ME FW) 
            if (!gFwCapsuleAddress) {
                MEProcessHandleResult((BIT00 | BIT02), "Error : Functon Not Supported!!");
                break;
            }    
            Phy_Address = 0;
            if ((StructPtr->bHandleRequest == 3) && \
                (StructPtr->TotalBlocks <= EFI_SIZE_TO_PAGES(FWCAPSULE_IMAGE_SIZE))) {
                // Function#3 : ME FW Update only, upload ME FW capsule from the beggining.
                Phy_Address = (EFI_PHYSICAL_ADDRESS)gFwCapsuleAddress;
            }
            if ((StructPtr->bHandleRequest == 5) && \
                (StructPtr->TotalBlocks <= \
                        EFI_SIZE_TO_PAGES(FWCAPSULE_IMAGE_SIZE - FLASH_SIZE))) {
                // Function#5 : BIOS + ME FW Update, upload capsule from the end of BIOS.
                Phy_Address = (EFI_PHYSICAL_ADDRESS)gFwCapsuleAddress + FLASH_SIZE;
            }
            if (!Phy_Address) MEProcessHandleResult((BIT00 | BIT02), "Error : Buffer Too Small!!");   
            break;
#endif  // #if SecSMIFlash_SUPPORT == 1
    }
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
