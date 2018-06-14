//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/TdtWrapper/TdtOfbd.c 7     4/30/13 7:59a Tristinchou $
//
// $Revision: 7 $
//
// $Date: 4/30/13 7:59a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/TdtWrapper/TdtOfbd.c $
// 
// 7     4/30/13 7:59a Tristinchou
// [TAG]  		EIPNone
// [Category]  	Bug Fix
// [Severity]  	Normal
// [RootCause]  	Pointer may be destroyed in smm.
// [Solution]  	Get value instead of using pointer.
// [Files]  		TdtOfbd.c
// 
// 6     3/26/13 8:09a Calvinchen
// [TAG]  		EIP119036.2
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	SecureFlash fail with ME "AT disable"
// [RootCause]  	SMM HECI not installed if ME is disabled by FDO Jumper.
// [Solution]  	Added check SmmHeci protocol before AtGetTimerInfo call.
// 
// 5     3/26/13 4:49a Calvinchen
// [TAG]  		EIP119036.1
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	SecureFlash fail with ME ¡§AT disable¡¨
// [RootCause]  	HECI returns "UNSUPPORTED" not "TIMEOUT" if ME is
// disabled.
// [Solution]  	Added check ME Mode and AT state before AtGetTimeInfo
// call.
// [Files]  		TdtOfbd.c
// 
// 4     3/25/13 10:17a Calvinchen
// [TAG]  		EIP119036
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	SecureFlash fail with ME "AT disable"
// [RootCause]  	HECI Timeout if AtGetTimeInfo call.
// [Solution]  	To Skip AtGetTimeInfo call if HECI Timeout at first call.
// [Files]  		TdtOfbd.c
// 
// 3     3/12/13 8:01a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Fix AFU can update after frist time enrolled
// 
// 2     3/04/13 4:48a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Update for get timer fail in windows.
// 
// 1     1/24/13 3:52a Klzhan
// [TAG]  		EIP113197 
// [Category]  	Improvement
// [Description]  	Block AFU when AT DTimer is running out
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	TDTOfbd.c
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include "token.h"
#include "OFBD.h"
#include "HeciSmm\HeciSmm.h"
#include "MkhiMsgs.h"
#define _ME_LIB_H_
#include "AtHi.h"
#include "MeBiosPayloadData\MeBiosPayloadData.h"

EFI_GUID gSetupGuid = SETUP_GUID;
SMM_HECI_PROTOCOL *mHeci;
EFI_GUID gSmmHeciProtocolGuid = SMM_HECI_PROTOCOL_GUID;
DXE_MBP_DATA_PROTOCOL *MbpData;
EFI_GUID gMeBiosPayloadDataProtocolGuid = ME_BIOS_PAYLOAD_DATA_PROTOCOL_GUID;
BOOLEAN gIntelAT;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   AsciiStrLen
//
// Description: 
//
// Input:       
//              
//
// Output:      
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN
EFIAPI
AsciiStrLen (
  IN      CONST CHAR8               *String
  )
{
  UINTN                             Length;

  for (Length = 0; *String != '\0'; String++, Length++) {}
  return Length;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   HMRFPO_ENABLE_MSG
//
// Description: Send Enable HECI message to ME FW.
//
// Input:   NONE
//
// Output:  EFI_STATUS
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtGetTimerInfo   (
  IN OUT UINT32                         *Interval,
  IN OUT UINT32                         *TimeLeft
)
{
  UINT32                    HeciLength;
  EFI_STATUS                Status;

  ATHI_GET_TIMER_INFO_CMD   AtGetTimerInfoCmd;
  ATHI_GET_TIMER_INFO_RSP   AtGetTimerInfoRsp;

  MemSet ((VOID *)&AtGetTimerInfoCmd, sizeof (ATHI_GET_TIMER_INFO_CMD), 0);
  MemSet ((VOID *)&AtGetTimerInfoRsp, sizeof (ATHI_GET_TIMER_INFO_RSP), 0);

  AtGetTimerInfoCmd.Header.Version.Minor        = ATHI_PROTOCOL_VERSION_MINOR;
  AtGetTimerInfoCmd.Header.Version.Major        = ATHI_PROTOCOL_VERSION_MAJOR;
  AtGetTimerInfoCmd.Header.Command.Category     = ATHI_CMD_GROUP_THEFT_DETECTION;
  AtGetTimerInfoCmd.Header.Command.IsResponse   = AT_COMMAND;
  AtGetTimerInfoCmd.Header.Command.Code         = ATHI_THEFT_DETECT_GRP_GET_TIMER_INFO_CMD;
  //
  // 0- Length 0 only header with command is send as message
  //
  AtGetTimerInfoCmd.Header.Length  = sizeof (ATHI_GET_TIMER_INFO_CMD) - sizeof (ATHI_HEADER);
  AtGetTimerInfoCmd.TimerId        = AT_TID_DISABLE_TIMER;


  HeciLength = sizeof (ATHI_GET_TIMER_INFO_CMD);
  Status = mHeci->ResetHeci();
  Status = mHeci->SendMsg (
                  (UINT32 *) &AtGetTimerInfoCmd,
                  HeciLength,
                  BIOS_FIXED_HOST_ADDR,
                  HECI_AT_MESSAGE_ADDR
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  HeciLength = sizeof (ATHI_GET_TIMER_INFO_RSP);


  Status = mHeci->ReadMsg (
                  BLOCKING,
                  (UINT32 *) &AtGetTimerInfoRsp,
                  &HeciLength
                  );

  if (EFI_ERROR (Status)) {

    return Status;
  }

  *Interval = AtGetTimerInfoRsp.TimerInfo.Interval;
  *TimeLeft = AtGetTimerInfoRsp.TimerInfo.TimeLeft;

  return EFI_SUCCESS;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TDTOfbdEntry
//
// Description:	
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TDTOfbdEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{
    UINTN               VariableSize;
    UINT32              TimeLeft, Interval;
    EFI_STATUS          Status = EFI_SUCCESS;
    OFBD_HDR            *pOFBDHdr = (OFBD_HDR*)Buffer;
    char                *TDTErrorMsg_1 = \
                            CONVERT_TO_STRING(TDT_FLASH_UPDATE_ERROR_MESSAGE_1);
    char                *TDTErrorMsg_2 = \
                            CONVERT_TO_STRING(TDT_FLASH_UPDATE_ERROR_MESSAGE_2);
    OFBD_EXT_HDR        *pOFBDExtHdr = (OFBD_EXT_HDR*)((UINT8 *)Buffer + pOFBDHdr->OFBD_HDR_SIZE);	
    UINT32              MeMode;
	
    // Check AT timer one time when AFU is checking OFBD version.
    if ((pOFBDHdr->OFBD_FS != 0) || (pOFBDExtHdr->TypeCodeID != 0)) return;
    if ((mHeci == NULL)) return;
    // Check AT timer if ME is normal state.
    Status = mHeci->GetMeMode(&MeMode);
    if (EFI_ERROR(Status) || (MeMode != ME_MODE_NORMAL)) return;
    // Check AT timer if AT is enabled in FITC.
    if (!gIntelAT) return;
    Status = AtGetTimerInfo(&Interval, &TimeLeft);
    // If not enrolled, TimeLeft will be 0
    if (EFI_ERROR(Status) || (TimeLeft == 0)) return ;
    if (TimeLeft > EXPECTED_FLASH_UPDATE_TIME) return ;
    // Set the AFU Force Exit +>>>
    VariableSize = AsciiStrLen(TDTErrorMsg_1);
    (UINT8*)Buffer += pOFBDHdr->OFBD_Size;
    MemSet ((UINT8*)Buffer + pOFBDHdr->OFBD_Size, VariableSize + 1, 0);
    MemCpy ((UINT8*)Buffer , TDTErrorMsg_1, VariableSize);
    (UINT8*)Buffer += VariableSize;
    VariableSize = AsciiStrLen(TDTErrorMsg_2);
    MemSet ((UINT8*)Buffer, VariableSize + 1, 0);
    MemCpy ((UINT8*)Buffer, TDTErrorMsg_2, VariableSize);
    pOFBDHdr->OFBD_RS |= (OFBD_RS_ERR_OUT + OFBD_RS_DIS_OEMSTR);    // Tell the AFU display the OEM Message
    // Set the AFU Force Exit <<<+
    return;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TDTOfbdInSmmEntry
//
// Description:	
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TDTOfbdInSmmEntry (VOID)
{

    EFI_STATUS  Status;

    Status = pBS->LocateProtocol (&gSmmHeciProtocolGuid, NULL, &mHeci);
    if (EFI_ERROR (Status)) mHeci = NULL;
    Status = pBS->LocateProtocol (&gMeBiosPayloadDataProtocolGuid, NULL, (VOID **) &MbpData);
    if (EFI_ERROR (Status)) gIntelAT = FALSE;
    else gIntelAT = (BOOLEAN)MbpData->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.IntelAT;

    return ;
}
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
