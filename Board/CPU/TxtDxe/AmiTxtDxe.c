//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/AmiTxtDxe.c 11    6/11/15 10:31p Crystallee $
//
// $Revision: 11 $
//
// $Date: 6/11/15 10:31p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/AmiTxtDxe.c $
// 
// 11    6/11/15 10:31p Crystallee
// [TAG]  		EIP207854
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Txt test fail with TCG2 module
// [RootCause]  	Tokne TCG_SUPPORT was removed.
// [Solution]  	Add TCG2Support token.
// 
// 10    4/10/15 3:11a Crystallee
// 
// 9     5/05/14 11:57p Hsingyingchung
// [TAG]  		EIP167029
// [Category]  	Improvement
// [Description]  	Keep the original attribute of "Setup" variable when
// use SetVariable().
// 
// 8     1/17/14 4:08a Crystallee
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Show Txt information in setup->Advanced ->Intel Txt
// Information page.
// 
// 7     8/28/13 5:57a Crystallee
// [TAG]  		EIP134339
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	[Sharkbay]Build error after update Haswell Cpu module
// [RootCause]  	If token TCG_SUPPORT is disabled, TpmSupport setup data
// will not define, then cause built error.
// [Solution]  	Add token TCG_SUPPORT condition when use TpmSupport setup
// data.
// 
// 6     8/14/13 5:07a Davidhsieh
// 
// 4     7/23/13 7:47a Crystallee
// [TAG]  		EIP128089
// [Category]  	Improvement
// [Description]  	TXT will be disabled and grayed out in Setup when TPM
// Support is disabled.
// 
// 3     9/13/12 4:13a Davidhsieh
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Desable TCG causes BIOS building error
// [RootCause]  	TCG setup data is used in TxtPei and the data is not
// exist when TCG disabled.
// [Solution]  	Do not use the TCG setup data when TCG disabled
// 
// 2     9/05/12 1:36a Davidhsieh
// [TAG]  		EIP97350
// [Category]  	Improvement
// [Description]  	Add AUX index define in TPM NVRAM to avoid system keep
// reset when TXT enabled
// 
// 1     7/18/12 2:07a Davidhsieh
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	AMI TXT Dxe module part create
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    AmiTxtDxe.c
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
//
#include "AmiTxtDxe.h"
#include "Txt.h"

AMI_TXT_INFO_PROTOCOL gAmiTxtInfoProtocol = {0};
AMI_TXT_INFO_DATA     gAmiTxtInfoData = {0};

EFI_GUID gHobListGuid               = HOB_LIST_GUID;
EFI_GUID gAmiTxtInfoProtocolGuid    = AMI_TXT_INFO_PROTOCOL_GUID;

#if TCG_SUPPORT || TCG2Support    
EFI_GUID gSetupGuid = SETUP_GUID;
EFI_GUID gEfiTcgProtocolGuid        = EFI_TCG_PROTOCOL_GUID;
EFI_GUID gEfiTpmDeviceProtocolGuid  = EFI_TPM_DEVICE_PROTOCOL_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LtSendTpmCommand
//
// Description: Sends a command to the TPM
//
// Input:   *EFI_TCG_PROTOCOL   - Tcg Protocol type.
//          UINT32              - Tcg Command ordinal.
//          int                 - cmd datasize.
//          VOID*               - cmd data.
//
// Output:  UINT32              - TPM_RESULT
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
LtSendTpmCommand    (
    IN EFI_TCG_PROTOCOL     *tcg,
    IN UINT32               ord,
    IN int                  dataSize,
    IN VOID                 *data
)
{
    EFI_STATUS              Status;
    static UINT8            result[0x400];
    TPM_1_2_RET_HEADER*     tpmResult;
    struct  {
        TPM_1_2_CMD_HEADER  hdr;
        UINT8               data[0x100];
    } cmd;

    cmd.hdr.Tag = TPM_H2NS (TPM_TAG_RQU_COMMAND);
    cmd.hdr.ParamSize = TPM_H2NL (sizeof(TPM_1_2_RET_HEADER) + dataSize);
    cmd.hdr.Ordinal = TPM_H2NL (ord);
    pBS->CopyMem(cmd.data, data, dataSize);
    Status = tcg->PassThroughToTpm (    tcg, \
                                        sizeof(TPM_1_2_CMD_HEADER) + dataSize, \
                                        (UINT8*)&cmd, \
                                        sizeof (result), \
                                        (UINT8*)&result );
    tpmResult = (TPM_1_2_RET_HEADER*)result;
    if ( EFI_ERROR(Status) || (tpmResult->RetCode != 0))
        TRACE((TRACE_ALWAYS, "TXT (TPM Error) Status: %r; RetCode: %x.\n", \
                                    Status, \
                                    TPM_H2NL(tpmResult->RetCode)    ));
    return tpmResult->RetCode;
}

#if defined SINIT_ACM_SUPPORT && SINIT_ACM_SUPPORT == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EventUpdateSinitAcmToMemory
//
// Description: This routine copy SINIT ACM to SINIT meory for BIOS-Base SINI 
//              AC Module implementation.
//
// Input:       IN EFI_EVENT   Event
//              IN VOID        *Context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
EventUpdateSinitAcmToMemory (
    IN EFI_EVENT      Event,
    IN VOID           *Context
)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    EFI_HANDLE      *FvHandle;
    UINTN           Number, i, SinitacmSize = 0;
    UINT32          Authentication, TxtMemBase;
    VOID            *pSinitacmPtr = NULL;
    EFI_FIRMWARE_VOLUME_PROTOCOL    *Fv;
    EFI_GUID        SinitAcmFfsGuid = \
    { 0x7fbfe0ea, 0x0e9d, 0x406b, 0xa2, 0x2, 0xca, 0x6a, 0x7d, 0x0e, 0x0f, 0x1e};
    EFI_GUID  	    gEfiFirmwareVolume2ProtocolGuid 	= 
    { 0x220e73b6, 0x6bdb, 0x4413, 0x84, 0x5, 0xb9, 0x74, 0xb1, 0x8, 0x61, 0x9a };

    pBS->CloseEvent (Event);
    Status = pBS->LocateHandleBuffer (ByProtocol, \
                                      &gEfiFirmwareVolume2ProtocolGuid, \
                                      NULL, \
                                      &Number, \
                                      &FvHandle);
    if (EFI_ERROR(Status)) return;
        
    for (i = 0; i < Number; i++) {
        
        Status = pBS->HandleProtocol (\
                    FvHandle[i], &gEfiFirmwareVolume2ProtocolGuid, &Fv);
        if (EFI_ERROR(Status)) continue;
        
        // Read SINIT AC module from Firmware Volume
        SinitacmSize = 0;        
        pSinitacmPtr = NULL;
        Status  = Fv->ReadSection ( Fv,
                                    &SinitAcmFfsGuid,
                                    EFI_SECTION_RAW,
                                    0,
                                    &pSinitacmPtr,
                                    &SinitacmSize,
                                    &Authentication );
        if (!EFI_ERROR(Status)) {
            // SINIT Memory Base = TXT Public Space + 270h
            TxtMemBase = *(UINT32*)0xfed30270;
            // copy SINIT ACM to SINIT memory
            pBS->CopyMem ((VOID*)TxtMemBase, pSinitacmPtr, SinitacmSize);
            // BiosToOS Region Base = TXT Public Space + 300h
            TxtMemBase = *(UINT32*)0xfed30300;
            // Update SINIT ACM size to BiosToOS region
            *(UINT32*)(TxtMemBase + 12) = (UINT32)SinitacmSize;
            pBS->FreePool (pSinitacmPtr);
            break;
        }
    }
    pBS->FreePool (FvHandle);
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LtDefineTpmNvramSpace
//
// Description: This routine for define the TPM Nvram space.
//
// Input:       None.
//
// Output:      TURE    - Success.
//              FALSE   - Failed.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
LtDefineTpmNvramSpace   (
    VOID
)
{
    EFI_STATUS              Status;
    EFI_TCG_PROTOCOL        *tcg;
    EFI_TPM_DEVICE_PROTOCOL *TpmDevice;
    UINT32  CmdReadNvram[3] = { TPM_H2NL(0x50000002),
                                TPM_H2NL(0x00000000),
                                TPM_H2NL(0x40)  };
    TPM_DEF_NV_DATA  CmdDefineNvram [] = { \
        // TPM_NV_DATA_PUBLIC1 & TPM_NV_DATA_PUBLIC1.TPM_PCR_INFO_SHORT
        TPM_H2NS(0x18), TPM_H2NL(0x50000003), TPM_H2NS(0x03), 0, 0, 0 , 0x1f, \
        // TPM_NV_DATA_PUBLIC1.TPM_PCR_INFO_SHORT.TCPA_DIGEST
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        // TPM_NV_DATA_PUBLIC2.TPM_PCR_INFO_SHORT
        TPM_H2NS(0x3), 0, 0, 0 , 0x18, \
        // TPM_NV_DATA_PUBLIC2.TPM_PCR_INFO_SHORT.TCPA_DIGEST
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        // TPM_NV_DATA_PUBLIC2
        TPM_H2NS(0x17), TPM_H2NL(0), 0, 0, 0, TPM_H2NL(0x40), \
        // TCPA_DIGEST
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // locate the TPM Device Protocol for sending TPM command.
    Status = pBS->LocateProtocol (  &gEfiTpmDeviceProtocolGuid, \
                                    NULL, \
                                    &TpmDevice  );
    if (EFI_ERROR(Status)) {
        TRACE ((TRACE_ALWAYS, \
                "TXT (TPM Error) : failed to locate TPM Device protocol.\n"));
        return FALSE;
    }
    // locate the TCG Protocol for sending TPM command.
    Status = pBS->LocateProtocol ( &gEfiTcgProtocolGuid,  NULL, &tcg );
    if (EFI_ERROR (Status)) {
        TRACE ((TRACE_ALWAYS, \
                "TXT (TPM Error) : failed to locate TCG protocol.\n"));
        return FALSE;
    }
#if defined SINIT_ACM_SUPPORT && SINIT_ACM_SUPPORT == 1
{
        // BIOS-Based SINIT AC module support.
        EFI_EVENT       SinitEvent;
        
        Status = CreateReadyToBootEvent(TPL_CALLBACK, \
	                                    EventUpdateSinitAcmToMemory, \
	                                    NULL, \
	                                    &SinitEvent );
}	                                    
#endif	      
    TpmDevice->Init(TpmDevice);
    // Send TPM command to read TPM NVRAM space.
    Status = LtSendTpmCommand ( tcg, \
                                TPM_ORD_NV_READVALUE, \
                                sizeof(CmdReadNvram), \
                                CmdReadNvram    );
    // if TPM NVRAM isn't defined, Send TPM command to define TPM NVRAM space.
    if (Status != 0) {
        CmdReadNvram[0] = TPM_H2NL(0x50000003);
        Status = LtSendTpmCommand ( tcg, \
                                    TPM_ORD_NV_READVALUE, \
                                    sizeof(CmdReadNvram), \
                                    CmdReadNvram    );
        if (Status != 0) {
            Status = LtSendTpmCommand ( tcg, \
                                        TPM_ORD_NV_DEFINESPACE, \
                                        sizeof(TPM_DEF_NV_DATA), \
                                        &CmdDefineNvram );
        }
    }                                        
    Status = TpmDevice->Close(TpmDevice);

    if ( Status ) return FALSE;
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TxtTpmNvRamDefine
//
// Description: 
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID TxtTpmNvRamDefine()    
{
    UINTN		VariableSize;
    SETUP_DATA	SetupData;
	EFI_STATUS	Status;

    VariableSize = sizeof(SETUP_DATA);
    Status = pRS->GetVariable ( L"Setup", \
                                &gSetupGuid, \
                                NULL, \
                                &VariableSize, \
                                &SetupData );
    if (EFI_ERROR(Status))
	   	return;
	
    if (SetupData.TxtSupport != 0) {
        if (SetupData.TpmSupport != 0) LtDefineTpmNvramSpace();
    }        
}
#else
VOID TxtTpmNvRamDefine()
{
    return;
}
#endif    

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetTxtInfo
//
// Description: Get Txt information
//
// Input:       None
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetTxtInfo (
	IN AMI_TXT_INFO_PROTOCOL  *AMI_TXT_INFO_PROTOCOL,
    OUT VOID                    **AmiTxtInfoData
){
    *AmiTxtInfoData = (VOID*)(&gAmiTxtInfoData);
    return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitAmiTxtInfo
//
// Description: Initialize Txt information
//
// Input:       None
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitAmiTxtInfo() 
{
    EFI_STATUS   Status;
    VOID         *HobList;
    TXT_INFO_HOB *TxtInfoHob;
    UINT32       RegEax, RegEbx, RegEcx, RegEdx;    
	UINT32		 *TxtErrCode  = (UINT32*)(TXT_PUBLIC_BASE + 0x0030);
	EFI_GUID 	 gTxtInfoHobGuid = TXT_INFO_HOB_GUID;
	

    HobList = GetEfiConfigurationTable(pST,&gHobListGuid);
    if (!HobList) return;    
    
    //Find RC Txt Info Hob.
    TxtInfoHob = (TXT_INFO_HOB*)HobList;
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &TxtInfoHob))) {
        if (guidcmp(&TxtInfoHob->EfiHobGuidType.Name, &gTxtInfoHobGuid) == 0) break;
    }
    if (EFI_ERROR(Status)) return;
	
	//Initialize AmiTxtInfoProtocol
	gAmiTxtInfoProtocol.ProtocolVer = AMI_TXT_INFO_PROTOCOL_VERSION;
	gAmiTxtInfoProtocol.GetTxtInfo = GetTxtInfo;	
    
    //Initialize AMI TXT info data from HOB created by Intel Txt RC
    gAmiTxtInfoData.ChipsetIsTxtCapable = TxtInfoHob->Data.ChipsetIsTxtCapable;
    gAmiTxtInfoData.TxtDprMemoryBase = TxtInfoHob->Data.TxtDprMemoryBase;
    gAmiTxtInfoData.BiosAcmBase = TxtInfoHob->Data.BiosAcmBase;
    gAmiTxtInfoData.McuUpdateDataAddr = TxtInfoHob->Data.McuUpdateDataAddr;
    gAmiTxtInfoData.SinitAcmBase = TxtInfoHob->Data.SinitAcmBase;
    
    //Initializing ChipsetIsProduction default value
    gAmiTxtInfoData.ChipsetIsProduction = (*(UINT32 *) (TXT_PUBLIC_BASE + 0x200) & BIT31) ? TRUE : FALSE;
    
    //Check ACM is production or not    
    gAmiTxtInfoData.BiosAcmIsProduction = (((ACM_HEADER*)(gAmiTxtInfoData.BiosAcmBase))->ModuleID & BIT31) ? FALSE : TRUE;
    
    //CPUID funciton 1 ECX[6], Secure Mode Extensions check
    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    gAmiTxtInfoData.CpuIsTxtCapable = (RegEcx & BIT6) ? TRUE : FALSE;
    
    //TXT.CRASH register, TXT_PUBLIC_BASE + 0x30
    gAmiTxtInfoData.TxtErrCode = *TxtErrCode;
    
    Status = pBS->InstallProtocolInterface(
                    &TheImageHandle,
                    &gAmiTxtInfoProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &gAmiTxtInfoProtocol
                );

	if (EFI_ERROR(Status))
		TRACE ((TRACE_ALWAYS, "AmiTXTDxe : Install Protocol error, Status = %x\n", Status));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AmiTxtDxeEntry
//
// Description: DXE Entry Point for Intel TXT Driver.
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
AmiTxtDxeEntry (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
)
{
#if TCG_SUPPORT || TCG2Support
	EFI_STATUS  Status;
    UINTN		DataSize;
    SETUP_DATA  SetupData;
	UINT8       *TpmBaseAddr = (UINT8*)0xfed40000;
    UINT32      Attributes = 0;
#endif

	InitAmiLib(ImageHandle, SystemTable);   
    InitAmiTxtInfo();

#if TCG_SUPPORT || TCG2Support
	DataSize = sizeof(SETUP_DATA);

	Status = pRS->GetVariable(
				L"Setup",
				&gSetupGuid,
				&Attributes,
				&DataSize,
				&SetupData
			 );

	ASSERT_EFI_ERROR(Status);
	if (EFI_ERROR(Status)) return EFI_SUCCESS;
	//If TxtSupport on, but Tpm device is not present or TpmSupport off,
	//then turn off TxtSupport.
	if (SetupData.TxtSupport){
		if ((*TpmBaseAddr == 0xff) || (!SetupData.TpmSupport)){
			SetupData.TxtSupport = 0;

			Status = pRS->SetVariable(
                        L"Setup",
                        &gSetupGuid,
                        Attributes,
                        sizeof(SETUP_DATA),
                        &SetupData
					);

			ASSERT_EFI_ERROR(Status);
		}
	}
#endif

	TxtTpmNvRamDefine();
	
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
