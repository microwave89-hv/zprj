//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatCpuPolicyOverride/PfatCpuPolicyOverride.c 3     10/29/12 4:09p Fredericko $
//
// $Revision: 3 $
//
// $Date: 10/29/12 4:09p $
// 
//
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:   PfatCpuPolicyOverride.c
//
// Description: Code listing file for PfatCpuPolicyOverride
//
//<AMI_FHDR_END>
//*************************************************************************

#include "PfatCpuPolicyOverride.h"

EFI_GUID pFatFileGuid = PFAT_PUB_KEY_FFS_FILE_RAW_GUID;

STATIC EFI_PEI_NOTIFY_DESCRIPTOR  mPfatCpuPolicyOverrideNotifyDesc = {
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gPeiCpuPlatformPolicyPpiGuid,
    PfatCpuPolicyOverrideEndOfPeiCpuPlatformPolicy
};

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  CryptoGetRawImage
//
// Description:    Loads binary from RAW section of X firwmare volume
//
//
// Output:         Buffer - returns a pointer to allocated memory. Caller
//                          must free it when done.
//                 Size   - returns the size of the binary loaded into the
//                          buffer.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
LocatPfatPubKey (IN EFI_PEI_SERVICES  **PpSv, IN OUT VOID **Buffer)
{
    EFI_STATUS                    Status;
    EFI_FIRMWARE_VOLUME_HEADER    *pFV;
    UINTN                         FvNum=0;
    EFI_FFS_FILE_HEADER           *ppFile=NULL;
    BOOLEAN                       Found = FALSE;

    Status = (*PpSv)->FfsFindNextVolume (PpSv, FvNum, &pFV);

    while ( TRUE )
    {
        Status = (*PpSv)->FfsFindNextVolume( PpSv, FvNum, &pFV );
        if ( EFI_ERROR( Status ))
        {
            return Status;
        }

        ppFile = NULL;

        while ( TRUE )
        {
            Status = (*PpSv)->FfsFindNextFile( PpSv,
                                               EFI_FV_FILETYPE_FREEFORM,
                                               pFV,
                                               &ppFile );

            if ( Status == EFI_NOT_FOUND )
            {
                break;
            }

            DEBUG ((EFI_D_INFO, " ppFile guid:: %x \n", ppFile->Name));

            if (CompareGuid( &ppFile->Name, &pFatFileGuid ))
            {
                Found = TRUE;
                break;
            }
        }

        if ( Found )
        {
            break;
        }
        else {
            FvNum++;
        }
    }

     Status = (*PpSv)->FfsFindSectionData( PpSv,
                                          EFI_SECTION_RAW,
                                          ppFile,
                                          Buffer );

    if (EFI_ERROR( Status )) {
        return EFI_NOT_FOUND;
    }

    return Status;
}




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: CpuPolicy Override for Pfat
//
// Description:    PfatCpuPolicyOverride at end of PeiCpuPlatformPolicy
//                 handler.
//
// Output:         PeiServices - Pointer to PEI Services Table.
//                 NotifyDesc  - Pointer to the descriptor for the Notification
//                               event that caused this function to execute.
//                 Ppi         - Pointer to the PPI data associated with
//                               this function.
//
//<AMI_PHDR_END>
//**********************************************************************
STATIC
EFI_STATUS
PfatCpuPolicyOverrideEndOfPeiCpuPlatformPolicy (
    IN      EFI_PEI_SERVICES          **PeiServices,
    IN      EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
    IN      VOID                      *Ppi
)
{
    EFI_STATUS                     Status;
    PEI_CPU_PLATFORM_POLICY_PPI    *CpuPlatformPolicyPpi;
    PFAT_CONFIG                    *PfatConfig;
    CPU_CONFIG_PPI                 *CpuConfig;
    UINT32                         TotalROMSize = 0;
    UINTN                          pFatHashDataSize = 0;
    UINT8                          pFatHash256Val[32];
    UINT8                          *Sha256PubKeyDigest;
    VOID                           *pFatSha256Context;
    VOID                           *pFatData;

    Status = PeiServicesLocatePpi (&gPeiCpuPlatformPolicyPpiGuid, 0, NULL, &CpuPlatformPolicyPpi);
    if ( EFI_ERROR( Status ) ) {
        return   Status;
    }

    PfatConfig = CpuPlatformPolicyPpi->SecurityConfig->PfatConfig;
    CpuConfig = CpuPlatformPolicyPpi->CpuConfig;

    CpuConfig->Pfat = CPU_FEATURE_ENABLE;
    pFatHashDataSize = Sha256GetContextSize ();
    Status = ((*PeiServices)->AllocatePool) (PeiServices, pFatHashDataSize, &pFatSha256Context);
    if ( EFI_ERROR( Status ) ) {
        return   Status;
    }

    Status  = LocatPfatPubKey(PeiServices ,&Sha256PubKeyDigest);
    //
    // If it fails it might be in non PUPC mode
    //
    if ( !EFI_ERROR( Status ) ) {
        PfatConfig->PupHeader.PkgAttributes = 0;
        CopyMem (&PfatConfig->Ppdt.PkeySlot0, Sha256PubKeyDigest, 32);
    }

    ///
    /// Select to Flash Map 0 Register to get the number of flash Component
    ///
    MmioAndThenOr32 (
        SB_RCBA + R_PCH_SPI_FDOC,
        (UINT32) (~(B_PCH_SPI_FDOC_FDSS_MASK | B_PCH_SPI_FDOC_FDSI_MASK)),
        (UINT32) (V_PCH_SPI_FDOC_FDSS_FSDM | R_PCH_SPI_FDBAR_FLASH_MAP0)
    );

    switch ( MmioRead16 (SB_RCBA + R_PCH_SPI_FDOD) & B_PCH_SPI_FDBAR_NC ) {
    case V_PCH_SPI_FDBAR_NC_1:
        PfatConfig->NumSpiComponents  = 1;
        break;
    case V_PCH_SPI_FDBAR_NC_2:
        PfatConfig->NumSpiComponents  = 2;
        break;
    default:
        break;
    }

    ///
    /// Select to Flash Components Register to get the Component 1 Density
    ///
    MmioAndThenOr32 (
        SB_RCBA + R_PCH_SPI_FDOC,
        (UINT32) (~(B_PCH_SPI_FDOC_FDSS_MASK | B_PCH_SPI_FDOC_FDSI_MASK)),
        (UINT32) (V_PCH_SPI_FDOC_FDSS_COMP | R_PCH_SPI_FCBA_FLCOMP)
    );

    ///
    /// Copy Component 1 Density
    ///
    switch ( (UINT8) MmioRead32 (SB_RCBA + R_PCH_SPI_FDOD) & B_PCH_SPI_FLCOMP_COMP1_MASK ) {
    case V_PCH_SPI_FLCOMP_COMP1_512KB:
        PfatConfig->ComponentSize[0]  = EnumSpiCompSize512KB;
        TotalROMSize += (UINT32) LShiftU64(512, KBShift);
        break;
    case V_PCH_SPI_FLCOMP_COMP1_1MB:
        PfatConfig->ComponentSize[0]  = EnumSpiCompSize1MB;
        TotalROMSize += (UINT32) LShiftU64(1, MBShift);
        break;
    case V_PCH_SPI_FLCOMP_COMP1_2MB:
        PfatConfig->ComponentSize[0]  = EnumSpiCompSize2MB;
        TotalROMSize += (UINT32) LShiftU64(2, MBShift);
        break;
    case V_PCH_SPI_FLCOMP_COMP1_4MB:
        PfatConfig->ComponentSize[0]  = EnumSpiCompSize4MB;
        TotalROMSize += (UINT32) LShiftU64(4, MBShift);
        break;
    case V_PCH_SPI_FLCOMP_COMP1_8MB:
        PfatConfig->ComponentSize[0]  = EnumSpiCompSize8MB;
        TotalROMSize += (UINT32) LShiftU64(8, MBShift);
        break;
    case V_PCH_SPI_FLCOMP_COMP1_16MB:
        PfatConfig->ComponentSize[0]  = EnumSpiCompSize16MB;
        TotalROMSize += (UINT32) LShiftU64(16, MBShift);
        break;
    case V_PCH_SPI_FLCOMP_COMP1_32MB:
        PfatConfig->ComponentSize[0]  = EnumSpiCompSize32MB;
        TotalROMSize += (UINT32) LShiftU64(32, MBShift);
        break;
    case V_PCH_SPI_FLCOMP_COMP1_64MB:
        PfatConfig->ComponentSize[0]  = EnumSpiCompSize64MB;
        TotalROMSize += (UINT32) LShiftU64(64, MBShift);
        break;
    default:
        break;
    }

    ///
    /// Copy Component 2 Density
    ///
    if ( PfatConfig->NumSpiComponents == 2 ) {
        switch ( (UINT8) MmioRead32 (SB_RCBA + R_PCH_SPI_FDOD) & B_PCH_SPI_FLCOMP_COMP2_MASK ) {
        case V_PCH_SPI_FLCOMP_COMP2_512KB:
            PfatConfig->ComponentSize[1]  = EnumSpiCompSize512KB;
            TotalROMSize += (UINT32) LShiftU64(512, KBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP2_1MB:
            PfatConfig->ComponentSize[1]  = EnumSpiCompSize1MB;
            TotalROMSize += (UINT32) LShiftU64(1, MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP2_2MB:
            PfatConfig->ComponentSize[1]  = EnumSpiCompSize2MB;
            TotalROMSize += (UINT32) LShiftU64(2, MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP2_4MB:
            PfatConfig->ComponentSize[1]  = EnumSpiCompSize4MB;
            TotalROMSize += (UINT32) LShiftU64(4, MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP2_8MB:
            PfatConfig->ComponentSize[1]  = EnumSpiCompSize8MB;
            TotalROMSize += (UINT32) LShiftU64(8, MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP2_16MB:
            PfatConfig->ComponentSize[1]  = EnumSpiCompSize16MB;
            TotalROMSize += (UINT32) LShiftU64(16, MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP2_32MB:
            PfatConfig->ComponentSize[1]  = EnumSpiCompSize32MB;
            TotalROMSize += (UINT32) LShiftU64(32, MBShift);
            break;
        case V_PCH_SPI_FLCOMP_COMP2_64MB:
            PfatConfig->ComponentSize[1]  = EnumSpiCompSize64MB;
            TotalROMSize += (UINT32) LShiftU64(64, MBShift);
            break;
        default:
            break;
        }
    }

    //
    // LastSfam : Number of SfamData - 1
    //
    PfatConfig->Ppdt.LastSfam = PFAT_COUNT - 1;
    if (PfatConfig->Ppdt.LastSfam > (MAX_SFAM_COUNT - 1)) {
        PfatConfig->Ppdt.LastSfam = MAX_SFAM_COUNT - 1;
    }

    //
    // SfamData[0] : BIOS Region only skip NVRAM
    //
    PfatConfig->Ppdt.SfamData[0].FirstByte = TotalROMSize - (0xFFFFFFFF - FV_MAIN_BASE + 1);
    PfatConfig->Ppdt.SfamData[0].LastByte  = TotalROMSize - 1;

    //
    // SfamData[1] : ME Region + GBE Region + Description Region
    //
    PfatConfig->Ppdt.SfamData[1].FirstByte = 0x00;
    PfatConfig->Ppdt.SfamData[1].LastByte  = TotalROMSize - FLASH_SIZE -1;
    PfatConfig->Ppdt.PpdtSize = (sizeof (PPDT) - sizeof (PfatConfig->Ppdt.SfamData) + ((PfatConfig->Ppdt.LastSfam + 1) * sizeof (SFAM_DATA)));

    //
    // Defined values in the token
    //
    PfatConfig->Ppdt.BiosSvn = BIOS_SVN;
    PfatConfig->PfatMemSize = (UINT8) RShiftU64(PfatMaxSectionSize, MBShift) + 1;

    //
    // Hash the PPDT to PfatConfig->PpdtHash
    //
    pFatHashDataSize = PfatConfig->Ppdt.PpdtSize;
    pFatData = (VOID *) &PfatConfig->Ppdt;
    Sha256Init (pFatSha256Context);
    Sha256Update (pFatSha256Context, pFatData, pFatHashDataSize);
    Sha256Final (pFatSha256Context,  pFatHash256Val);
    CopyMem (&PfatConfig->PpdtHash[0], &pFatHash256Val[0], 8);
    CopyMem (&PfatConfig->PpdtHash[1], &pFatHash256Val[8], 8);
    CopyMem (&PfatConfig->PpdtHash[2], &pFatHash256Val[16], 8);
    CopyMem (&PfatConfig->PpdtHash[3], &pFatHash256Val[24], 8);
    return   Status;
}

EFI_STATUS
PfatCpuPolicyOverrideEntryPoint (
    IN  EFI_FFS_FILE_HEADER  *FfsHeader,
    IN  EFI_PEI_SERVICES     **PeiServices
)
{
    EFI_STATUS                      Status;
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
    SETUP_DATA                      SetupData;
    EFI_GUID                        SetupGuid = SYSTEM_CONFIGURATION_GUID;
    UINTN                           VariableSize= sizeof (SETUP_DATA);

    Status = PeiServicesLocatePpi (&gEfiPeiReadOnlyVariablePpiGuid, 0, NULL, &ReadOnlyVariable);
    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    Status = ReadOnlyVariable->PeiGetVariable (
                 PeiServices,
                 L"Setup",
                 &SetupGuid,
                 NULL,
                 &VariableSize,
                 &SetupData
             );
    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    if ( SetupData.Pfatstate == Enable ) {
        Status = PeiServicesNotifyPpi (&mPfatCpuPolicyOverrideNotifyDesc);
        if ( EFI_ERROR( Status ) ) {
            return   Status;
        }
    }

    return   Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
