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
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/xTcgPei.c 1     4/21/14 2:16p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:16p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/xTcgPei.c $
// 
// 1     4/21/14 2:16p Fredericko
// 
// 1     10/08/13 12:02p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 1:54p Fredericko
// 
// 1     7/10/13 5:51p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 36    9/19/12 10:34a Fredericko
// [TAG]  		EIP90807
// [Category]  	Improvement
// [Description]  	MonotonicCounter variable guid changed.
// [Files]  		xTcgPei.c, AmiTcgPlatformPeiAfterMem.c
// 
// 35    3/19/12 6:27p Fredericko
// [TAG]  		EIP82769
// [Description]  	Firmware updates disable the TPM when Firmware update
// is done
// [Files]  		TcgDxe.c, xTcgDxe.c, xTcgPei.c
// 
// 34    12/12/11 3:17p Fredericko
// [TAG]  		EIP76865
// [Category]  	Improvement
// [Description]  	Dual Support for TCM and TPM. System could hang in TXT
// if txt is enabled in setup
// [Files]  		
// AmiTcgPlatfompeilib.c, AmiTcgPlatformPpi.cif,  AmiTcgPlatformPpi.h,
// AmiTcgPlatformProtocol.cif,  AmiTcgPlatformProtocol.h,
// EMpTcmPei.c, TcgDxe.cif, TcgPei.cif, TcgPeiAfterMem.cif,
// TcgPeiAfterMem.mak, TcgTcmPeiAfterMem.c, xTcgDxe.c, xTcgPei.c, 
// xTcgPeiAfterMem.c 
// 
// 33    9/27/11 10:21p Fredericko
// [TAG]  		EIP67286
// [Category]  	Improvement
// [Description]  	changes for Tcg Setup policy
// [Files]  		Tcg.sdl
// TcgPei.cif
// TcgPei.mak
// xtcgPei.c
// xTcgPeiAfterMem.c
// TcgPeiAfterMem.mak
// TcgDxe.cif
// TcgDxe.mak
// xTcgDxe.c
// AmiTcgPlatformPeilib.c
// AmiTcgPlatformDxelib.c
// 
// 32    4/27/11 3:01p Fredericko
// removed VFR compile directive
// 
// 31    3/29/11 12:57p Fredericko
// 
// 30    3/28/11 2:14p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 29    5/19/10 5:53p Fredericko
// Included File Header
// Included File Revision History
// Updated AMI Function Headers
// Code Beautification
// EIP 37653
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  xTcgPei.c
//
// Description:
//        Contians entry point function for TcgPei Subcomponent
//
//<AMI_FHDR_END>
//*************************************************************************
#include <Efi.h>
#include <Pei.h>
#include <TcgCommon.h>
#include <AmiPeiLib.h>
#include <TcgMisc.h>
#include <ppi\AmiTcgPlatformPpi.h>
#include "PPI\TcgService\TcgService.h"
#include "PPI\TpmDevice\TpmDevice.h"
#include "PPI\CpuIo.h"
#include "PPI\LoadFile.h"
#include "TcgPlatformSetupPeiPolicy.h"
#include "Tpm20Includes\Tpm20.h"
#include "Tpm20CRBLib.h"



EFI_GUID        gTcgPpiGuid = PEI_TCG_PPI_GUID;
EFI_GUID        gPlatformGuid = AMI_TCG_PLATFORM_PPI_GUID;

EFI_STATUS
EFIAPI TpmPeiEntry (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices );

EFI_STATUS
EFIAPI TcmPeiEntry (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices );


EFI_STATUS
EFIAPI TcgPeiEntry (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices );

EFI_STATUS
EFIAPI TcgTcmPeiEntry (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices );

EFI_STATUS TcgPeiBuildHobGuid(
    IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_GUID         *Guid,
    IN UINTN            DataLength,
    OUT VOID            **Hob );

EFI_STATUS
EFIAPI Tpm20CrbEntry(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices );

UINT8 GetPlatformSupportType()
{
   return (AutoSupportType());
}

static AMI_TCG_PLATFORM_PPI PlatformTypePpi = {
    GetPlatformSupportType
};


static EFI_PEI_PPI_DESCRIPTOR mPlatformPpiList[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI
        | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gPlatformGuid,
        &PlatformTypePpi
    }
};


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CommonTcgPeiEntryPoint
//
// Description: Entry point for Tcg PEI component
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
EFIAPI CommonTcgPeiEntryPoint(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    EFI_STATUS                     Status;
    VOID                           *Context = NULL;
    BOOLEAN                        DeviceType = FALSE;
    TCG_PLATFORM_SETUP_INTERFACE   *TcgPeiPolicy = NULL;
    EFI_GUID                        gTcgPeiPolicyGuid =\
                                        TCG_PLATFORM_SETUP_PEI_POLICY_GUID;
    TCG_CONFIGURATION              ConfigFlags;
    CHAR16                         Monotonic[] = L"MonotonicCounter";
#if defined(CORE_COMBINED_VERSION) && (CORE_COMBINED_VERSION > 262797)
    EFI_GUID                       Guid        = AMI_GLOBAL_VARIABLE_GUID;
#else
    EFI_GUID                       Guid        = EFI_GLOBAL_VARIABLE;
#endif
    EFI_GUID                       TcgGuid     = AMI_TCG_RESETVAR_HOB_GUID;
    UINTN                          Size        = sizeof(UINT32);
    UINT32                         Counter;
    EFI_PEI_READ_ONLY_VARIABLE_PPI *ReadOnlyVariable;
    EFI_HOB_GUID_TYPE               *Hob;
    BOOLEAN                         ResetAllTcgVar = FALSE;
    EFI_GUID                        gTcgReadOnlyVariablePpiGuid
                                        = EFI_TCG_PEI_READ_ONLY_VARIABLE_PPI_GUID;


    Status = (*PeiServices)->InstallPpi( PeiServices, &mPlatformPpiList[0] );
    if ( EFI_ERROR( Status ))
    {
        return EFI_UNLOAD_IMAGE;
    }

    Status = (*PeiServices)->LocatePpi(
                PeiServices,
                &gTcgPeiPolicyGuid,
                0, NULL,
                &TcgPeiPolicy);

    if(EFI_ERROR(Status) || TcgPeiPolicy == NULL )return Status;
    
    Status = (*PeiServices)->LocatePpi(
        PeiServices,
        &gTcgReadOnlyVariablePpiGuid,
        0, NULL,
        &ReadOnlyVariable
        );

    if(EFI_ERROR(Status) || ReadOnlyVariable == NULL )return Status;

    Status = ReadOnlyVariable->GetVariable( PeiServices, Monotonic, &Guid,
                                            NULL, &Size, &Counter );

    if ( EFI_ERROR( Status ))
    {

        ResetAllTcgVar = TRUE;
        Status         = TcgPeiBuildHobGuid(
            PeiServices,
            &TcgGuid,
            sizeof (BOOLEAN),
            &Hob );
    
        Hob++;
        (*PeiServices)->CopyMem( Hob, &ResetAllTcgVar, sizeof (ResetAllTcgVar));
    }

    if(!AutoSupportType()){
       Status = TpmPeiEntry( FfsHeader, PeiServices );
       PEI_TRACE((-1, PeiServices, "TpmPeiEntry results = %r \n", Status)); 
       if ( EFI_ERROR( Status )){ 
             return Status; 
       }
    }else{
       Status = TcmPeiEntry( FfsHeader, PeiServices );
       if ( EFI_ERROR( Status )){
       return Status;}
    }

    PEI_TRACE((-1, PeiServices, "before getTcgPeiPolicy\n")); 
    Status = TcgPeiPolicy->getTcgPeiPolicy(PeiServices, &ConfigFlags);

    PEI_TRACE((-1, PeiServices, "getTcgPeiPolicy results = %r \n", Status)); 

    if ( ConfigFlags.TpmSupport == 0x00  || EFI_ERROR( Status ))
    {
        PEI_TRACE((-1, PeiServices, "ConfigFlags.TpmSupport == 0x00  || EFI_ERROR( Status )\n")); 
        return EFI_SUCCESS;
    }


    PEI_TRACE((-1, PeiServices, "TcgPeiEntry processing\n")); 
    if(!AutoSupportType()){
       Status = TcgPeiEntry( FfsHeader, PeiServices );
       PEI_TRACE((-1, PeiServices, "TcgPeiEntry result = %r\n", Status)); 
       if(EFI_ERROR(Status)){
            PEI_TRACE((-1, PeiServices, "Tpm20CrbEntry Execution\n", Status));
            Tpm20CrbEntry(FfsHeader, PeiServices );
       }
    }else{
       Status = TcgTcmPeiEntry( FfsHeader, PeiServices );
    }

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
//**********************************************************************
