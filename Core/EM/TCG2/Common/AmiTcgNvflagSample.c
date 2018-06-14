//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgNvflagSample/AmiTcgNvflagSample.c 1     4/21/14 2:17p Fredericko $Revision: 
//
// $Date:
//*************************************************************************
// Revision History
// ----------------
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name: AmiTcgNvflagSample
//
// Description: This is a sample file for support TCG Ppi. It creates and installed
//      a protocal to access the persistent bios tpm flags in Tpm NV 0x50010000. 
//      See Ppi Spec 1.2
//
//<AMI_FHDR_END>
//************************************************************************
#include "AmiTcgNvflagSample.h"
#include <EFI.h>
#include "TcgEFI12.h"
#include "TcgPc.h"
#include <TcgCommon.h>



EFI_GUID    gEfiTpmDxeDeviceProtocolGuid = EFI_TPM_DEVICE_PROTOCOL_GUID;
EFI_GUID    gEfiTcgProtocolGuid = EFI_TCG_PROTOCOL_GUID;
UINT8       Internal_flag = 0;

UINT32
NvSendTpmCommand    (
    IN EFI_TCG_PROTOCOL     *tcg,
    IN UINT32               ord,
    IN int                  dataSize,
    IN VOID                 *data
);


TPM_RESULT SendSelfTest()
{
    EFI_STATUS              Status = EFI_SUCCESS;
    EFI_TCG_PROTOCOL        *tcgSvc;
    TPM_RESULT              tpmResult = 0;
    EFI_TPM_DEVICE_PROTOCOL *TpmDevice;

    Status = pBS->LocateProtocol( &gEfiTpmDxeDeviceProtocolGuid,NULL, &TpmDevice);
    if ( EFI_ERROR( Status ))
    {
        return 0;
    }

    Status = pBS->LocateProtocol( &gEfiTcgProtocolGuid, NULL, &tcgSvc );
    if ( EFI_ERROR( Status ))
    {
        TRACE((TRACE_ALWAYS, "Error: failed to locate TCG protocol: %r\n"));
        return 0;
    }

#if defined DONT_SEND_SELFTEST_TILL_READY_TO_BOOT && DONT_SEND_SELFTEST_TILL_READY_TO_BOOT == 1
    TpmDevice->Init( TpmDevice );

    if(*(UINT16 *)(UINTN)(PORT_TPM_IOMEMBASE + 0xF00) == SELF_TEST_VID)
    {
       tpmResult = NvSendTpmCommand( tcgSvc,  TPM_ORD_ContinueSelfTest,0, 0);
    }

    TpmDevice->Close( TpmDevice );
#endif
    return tpmResult;
}
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   Set_Persistent_Bios_TPM_Flags
//
// Description: Sets persistent bios flags in TPM NV
//
//
// Input:       IN PERSISTENT_BIOS_TPM_FLAGS *
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS Set_Persistent_Bios_TPM_Flags(PERSISTENT_BIOS_TPM_FLAGS *NvBIOSflags)
{
    EFI_STATUS              Status = EFI_SUCCESS;
    TPM_NV_WRITE_CMD        WriteCmd;
    TPM_NV_WRITE_RET        WriteRet;
    EFI_TCG_PROTOCOL        *tcgSvc;
    TPM_RESULT              RetCode;
    EFI_TPM_DEVICE_PROTOCOL *TpmDevice;
    UINTN                   Count = 10;                 

    if(NvBIOSflags == NULL)return EFI_INVALID_PARAMETER;

    Status = pBS->LocateProtocol( &gEfiTpmDxeDeviceProtocolGuid,NULL, &TpmDevice);
    if ( EFI_ERROR( Status ))
    {
        return EFI_NOT_FOUND;
    }

    Status = pBS->LocateProtocol( &gEfiTcgProtocolGuid, NULL, &tcgSvc );
    if ( EFI_ERROR( Status ))
    {
        TRACE((TRACE_ALWAYS, "Error: failed to locate TCG protocol: %r\n"));
        return EFI_NOT_FOUND;
    }

    SendSelfTest();
    
    TpmDevice->Init( TpmDevice );

    //physical presence is required so tcgpei should have already taken care of 
    //physical presence requirement
    WriteCmd.writeHeader.dataSize    = TPM_H2NL( NV_DATA_SIZE );
    WriteCmd.writeHeader.tag         = TPM_H2NS(TPM_TAG_RQU_COMMAND);
    WriteCmd.writeHeader.paramSize = TPM_H2NL( sizeof(TPM_NV_WRITE_CMD_HDR) + NV_DATA_SIZE);
    WriteCmd.writeHeader.ordinal = TPM_H2NL(TPM_ORD_NV_WriteValue);
    WriteCmd.writeHeader.nvIndex = TPM_H2NL(0x50010000);
    WriteCmd.writeHeader.offset  = TPM_H2NL(0x00000000);

    pBS->SetMem(WriteCmd.data, NV_DATA_SIZE, 0);
    pBS->CopyMem(WriteCmd.data, NvBIOSflags, sizeof(PERSISTENT_BIOS_TPM_FLAGS));

    Status = tcgSvc->PassThroughToTpm ( tcgSvc, \
                                        sizeof(TPM_NV_WRITE_CMD_HDR) +  NV_DATA_SIZE, \
                                        (UINT8*)&WriteCmd, \
                                        sizeof(TPM_NV_WRITE_RET), \
                                        (UINT8*)&WriteRet );

    RetCode = WriteRet.returnCode;

    if ( EFI_ERROR(Status) || (WriteRet.returnCode != 0)){
    
        TRACE((TRACE_ALWAYS, "(TPM Error) Status: %r; RetCode: %x.\n", \
                                    Status, \
                                    TPM_H2NL(WriteRet.returnCode)));  
//wait for proper return codes
        while(TPM_H2NL(RetCode)==INTERNAL_TPM_DOING_SELFTEST){

              pBS->Stall (500000); //stall 500ms for Selftest to complete

              Status = tcgSvc->PassThroughToTpm ( tcgSvc, \
                                       sizeof(TPM_NV_WRITE_CMD_HDR) +  NV_DATA_SIZE, \
                                       (UINT8*)&WriteCmd, \
                                       sizeof(TPM_NV_WRITE_RET), \
                                       (UINT8*)&WriteRet );

              RetCode = WriteRet.returnCode;
              if(Count == 0)break;
              Count-=1;  //total timeout is 5minutes for define the space
        }
    
    }


    TpmDevice->Close( TpmDevice );


    if(RetCode != 0)
    {
        return EFI_ACCESS_DENIED;
    }

    return EFI_SUCCESS;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcmSet_Persistent_Bios_TPM_Flags
//
// Description: Sets persistent bios flags in TPM NV
//
//
// Input:       IN PERSISTENT_BIOS_TPM_FLAGS *
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS TcmSet_Persistent_Bios_TPM_Flags(PERSISTENT_BIOS_TPM_FLAGS *NvBIOSflags)
{
    return EFI_UNSUPPORTED;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcmRead_Persistent_Bios_TPM_Flags
//
// Description: Sets persistent bios flags in TPM NV
//
//
// Input:       IN PERSISTENT_BIOS_TPM_FLAGS *
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS TcmRead_Persistent_Bios_TPM_Flags(PERSISTENT_BIOS_TPM_FLAGS *NvBIOSflags)
{
    return EFI_UNSUPPORTED;
}




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   Read_Persistent_Bios_TPM_Flags
//
// Description: Read persistent bios flags in TPM NV
//
//
// Input:       IN PERSISTENT_BIOS_TPM_FLAGS *
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS Read_Persistent_Bios_TPM_Flags(  PERSISTENT_BIOS_TPM_FLAGS *NvBIOSflags)
{
    EFI_STATUS              Status = EFI_SUCCESS;
    TPM_NV_READ_CMD         ReadCmd;
    TPM_NV_READ_RET         ReadRet;
    EFI_TCG_PROTOCOL        *tcgSvc;
    EFI_TPM_DEVICE_PROTOCOL *TpmDevice;
    EFI_GUID                FlagsStatusguid = AMI_TCG_CONFIRMATION_FLAGS_GUID;
    PERSISTENT_BIOS_TPM_FLAGS  TpmNvflags;
    UINTN                       Size = sizeof(PERSISTENT_BIOS_TPM_FLAGS);

    if(NvBIOSflags == NULL)return EFI_INVALID_PARAMETER;

    Status = pBS->LocateProtocol( &gEfiTpmDxeDeviceProtocolGuid,NULL, &TpmDevice);
    if ( EFI_ERROR( Status ))
    {
        return EFI_NOT_FOUND;
    }

    Status = pBS->LocateProtocol( &gEfiTcgProtocolGuid, NULL, &tcgSvc );
    if ( EFI_ERROR( Status ))
    {
        TRACE((TRACE_ALWAYS, "Error: failed to locate TCG protocol: %r\n"));
        return EFI_NOT_FOUND;
    }

    TpmDevice->Init( TpmDevice );

     //read space
    ReadCmd.dataSize    = TPM_H2NL( NV_DATA_SIZE );
    ReadCmd.tag         = TPM_H2NS(TPM_TAG_RQU_COMMAND);
    ReadCmd.paramSize = TPM_H2NL( sizeof(TPM_NV_READ_CMD));
    ReadCmd.ordinal = TPM_H2NL(TPM_ORD_NV_ReadValue);
    ReadCmd.nvIndex = TPM_H2NL(0x50010000);
    ReadCmd.offset  = TPM_H2NL(0x00000000);

    Status = tcgSvc->PassThroughToTpm ( tcgSvc, \
                                      sizeof(TPM_NV_READ_CMD) , \
                                     (UINT8*)&ReadCmd, \
                                      (sizeof(TPM_NV_READ_CMD) - 4 + NV_DATA_SIZE), \
                                     (UINT8*)&ReadRet );

    if ( EFI_ERROR(Status) || (ReadRet.returnCode != 0))
        TRACE((TRACE_ALWAYS, "(TPM Error) Status: %r; RetCode: %x.\n", \
                                    Status, \
                                    TPM_H2NL(ReadRet.returnCode)));  
    


    TpmDevice->Close( TpmDevice );
    
    if( TPM_H2NL(ReadRet.returnCode) == INTERNAL_TPM_BADINDEX ){
       
        Status = pRS->GetVariable( L"TPMPERBIOSFLAGS", \
                                    &FlagsStatusguid, \
                                    NULL, \
                                    &Size, \
                                    &TpmNvflags );

        if(!EFI_ERROR(Status)){
            NvBIOSflags->NoPpiProvision = TRUE;
            NvBIOSflags->NoPpiClear = FALSE;
            NvBIOSflags->NoPpiMaintenance = FALSE;
            return EFI_SUCCESS;
        }else{
            if(Internal_flag == 1)
            {
                return EFI_NOT_AVAILABLE_YET;
            }
        }
    }

    if( ReadRet.returnCode != 0)
    {
        //all ways require confirmation
        NvBIOSflags->NoPpiProvision = TRUE;
        NvBIOSflags->NoPpiClear = FALSE;
        NvBIOSflags->NoPpiMaintenance = FALSE;
        return EFI_SUCCESS;
    }

    pBS->CopyMem (NvBIOSflags, ReadRet.data, sizeof(PERSISTENT_BIOS_TPM_FLAGS));
    return EFI_SUCCESS;
}





//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NvSendTpmCommand
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
NvSendTpmCommand    (
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



PERSISTENT_BIOS_TPM_MANAGEMENT_FLAGS_PROTOCOL   PersistentBiosflagsManagementProtocol = {
     Read_Persistent_Bios_TPM_Flags,
     Set_Persistent_Bios_TPM_Flags
};

PERSISTENT_BIOS_TPM_MANAGEMENT_FLAGS_PROTOCOL   TcmPersistentBiosflagsManagementProtocol = {
     TcmRead_Persistent_Bios_TPM_Flags,
     TcmSet_Persistent_Bios_TPM_Flags
};

EFI_GUID Overrideguid = AMI_BIOSPPI_FLAGS_MANAGEMENT_GUID;

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AmiTcgPpiNvflagEntry
//
// Description: Entry point 
//
//
// Input:       IN      EFI_FFS_FILE_HEADER       *FfsHeader
//              IN      EFI_PEI_SERVICES          **PeiServices,
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI AmiTcgPpiNvflagEntry (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS 		            Status;
    EFI_TCG_PROTOCOL            *tcgSvc;
    EFI_TPM_DEVICE_PROTOCOL     *TpmDevice;
    PERSISTENT_BIOS_TPM_FLAGS   NvBIOSflags;
    TPM_RESULT                  RetCode;
    UINTN                       Count = 10; 
    EFI_GUID  FlagsStatusguid = AMI_TCG_CONFIRMATION_FLAGS_GUID;
    UINTN     Size = sizeof(PERSISTENT_BIOS_TPM_FLAGS);   
    TPM_DEF_NV_DATA  CmdDefineNvram [] = { \
        // TPM_NV_DATA_PUBLIC1 & TPM_NV_DATA_PUBLIC1.TPM_PCR_INFO_SHORT
        TPM_H2NS(0x18), TPM_H2NL(0x50010000), TPM_H2NS(0x03), 0, 0, 0 , 0x1f, \
        // TPM_NV_DATA_PUBLIC1.TPM_PCR_INFO_SHORT.TCPA_DIGEST
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        // TPM_NV_DATA_PUBLIC2.TPM_PCR_INFO_SHORT
        TPM_H2NS(0x3), 0, 0, 0 , 0x1f, \
        // TPM_NV_DATA_PUBLIC2.TPM_PCR_INFO_SHORT.TCPA_DIGEST
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        // TPM_NV_DATA_PUBLIC2
        TPM_H2NS(0x17), TPM_H2NL(0x00000001), 0, 0, 0, TPM_H2NL(NV_DATA_SIZE), \
        // TCPA_DIGEST
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    InitAmiLib( ImageHandle, SystemTable );

    Status = pBS->LocateProtocol( &gEfiTpmDxeDeviceProtocolGuid,NULL, &TpmDevice);
    if ( EFI_ERROR( Status ))
    {
        return EFI_NOT_FOUND;
    }

    Status = pBS->LocateProtocol( &gEfiTcgProtocolGuid, NULL, &tcgSvc );
    if ( EFI_ERROR( Status ))
    {
        TRACE((TRACE_ALWAYS, "Error: failed to locate TCG protocol: %r\n"));
        return EFI_NOT_FOUND;
    }

    if(AutoSupportType()){
       
        Status = pBS->InstallProtocolInterface(
            &ImageHandle,
            &Overrideguid,
            EFI_NATIVE_INTERFACE,
            &TcmPersistentBiosflagsManagementProtocol);

        return Status;
    }

    Internal_flag = 1;

    Status = Read_Persistent_Bios_TPM_Flags(&NvBIOSflags);

    TpmDevice->Init( TpmDevice );

   
    //analyze return code
    if(Status == EFI_NOT_AVAILABLE_YET){
        //it might not be defined so define it       

        SendSelfTest();   //make sure we send selftest before defining space

	    RetCode = NvSendTpmCommand  ( tcgSvc, \
                            		TPM_ORD_NV_DefineSpace, \
                            		sizeof(TPM_DEF_NV_DATA), \
                            		&CmdDefineNvram );

        if(RetCode != 0){
            while(TPM_H2NL(RetCode) == INTERNAL_TPM_DOING_SELFTEST){

                pBS->Stall (500000); //stall 500ms for Selftest to complete

                RetCode = NvSendTpmCommand  ( tcgSvc, \
                            		TPM_ORD_NV_DefineSpace, \
                            		sizeof(TPM_DEF_NV_DATA), \
                            		&CmdDefineNvram );

                if(Count == 0)break;
                Count-=1;
            }
        } 
	
        Internal_flag = 0;

	    //read again to make sure we can read TPM Indices
	    Status = Read_Persistent_Bios_TPM_Flags(&NvBIOSflags);
	    if(Status)return EFI_ABORTED;

	    //if read is successful set the default values only once
    	//we only do this here because of the protections on TPM Nvram
    	//writes without owner. Do this only after defining the index
       	NvBIOSflags.NoPpiProvision 	    = NO_PPI_PROVISION_DEFAULT;
    	NvBIOSflags.NoPpiClear 		    = NO_PPI_CLEAR_DEFAULT;
    	NvBIOSflags.NoPpiMaintenance 	= NO_PPI_MAINTENANCE_DEFAULT;

    	Set_Persistent_Bios_TPM_Flags(&NvBIOSflags);
    }
    else if(Status){
        return EFI_ABORTED;
    }else{
        //already allocated but check for first boot.
        Status = pRS->GetVariable( L"TPMPERBIOSFLAGS", \
                              &FlagsStatusguid, \
                              NULL, \
                              &Size, \
                              &NvBIOSflags );

        if(Status == EFI_NOT_FOUND){
            NvBIOSflags.NoPpiProvision 	    = NO_PPI_PROVISION_DEFAULT;
	        NvBIOSflags.NoPpiClear 		    = NO_PPI_CLEAR_DEFAULT;
	        NvBIOSflags.NoPpiMaintenance 	= NO_PPI_MAINTENANCE_DEFAULT;
	        Set_Persistent_Bios_TPM_Flags(&NvBIOSflags);
        }
    }

    TpmDevice->Close( TpmDevice );

    Status = pBS->InstallProtocolInterface(
            &ImageHandle,
            &Overrideguid,
            EFI_NATIVE_INTERFACE,
            &PersistentBiosflagsManagementProtocol);

    return Status;
}



//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
