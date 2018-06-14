echo off
Set AMI_PFAT_FLASH_CONFIGURATIONS=Flash.ini
echo AMI_PFAT_Flash_Configurations>%AMI_PFAT_FLASH_CONFIGURATIONS%
Set FITC_OUTIMAGE_MAP=%1
Set BuildBIOSMap=%2
Set WORKING_PATH=%3
Set BIOS_SVN=%4
Set /a FlashSectionSize=%5
if not exist %FITC_OUTIMAGE_MAP% (
    echo Error:OutImage.map isn't found, please check the eModule of RomImgae
    goto END
)
if not exist %BuildBIOSMap% (
    echo Error:BuildBIOS.map isn't found, please check the PfatPubKeysAndBuildPSL.sdl
    goto END
)
if not exist ForPfatName.txt (
    echo Error:ForPfatName.txt isn't found, please check the eModule of RomImgae
    goto END
)
FOR /F "usebackq tokens=1" %%G IN ("ForPfatName.txt") DO (
    Set INPUT_BIOS_IMAGE=%%G
)
del ForPfatName.txt
FOR /F "skip=2 usebackq tokens=1,2,3,4-6" %%G IN ("%FITC_OUTIMAGE_MAP%") DO (
    if "%%J %%K %%L" EQU "Flash Image " (
        Set /a TOTAL_ROM_SIZE=0x%%I
    )else if "%%J %%K %%L" EQU "Descriptor Region " (
        Set /a DescriptorRegionStartingAddress=0x%%G
        Set /a DescriptorRegionLength=0x%%I
    )else if "%%J %%K %%L" EQU "GbE Region " (
        Set /a GbERegionStartingAddress=0x%%G
        Set /a GbERegionLength=0x%%I
    )else if "%%J %%K %%L" EQU "ME Region " (
        Set /a MERegionStartingAddress=0x%%G
        Set /a MERegionLength=0x%%I
    )else if "%%J %%K %%L" EQU "BIOS Region " (
        Set /a BIOSRegionStartingAddress=0x%%G
        Set /a BIOSRegionLength=0x%%I
    )
)
goto Define_Flash_Type

:Define_Flash_Type
Set MeType=0
Set BiosType=1
Set EcType=2
Set OthersType=3
goto Prepare_Definitions

:Prepare_Definitions
Set DESCRIPTOR_REGION_ROM=DescriptorRegion.bin
Set GBE_REGION_ROM=GbERegion.bin 
Set ME_REGION_ROM=MERegion.bin
Set PUBLIC_KEY_FILENAME=%WORKING_PATH%\PfatPublic.key
Set PRIVATE_KEY_FILENAME=%WORKING_PATH%\PfatPrivate.key
Set PFAT_VKEY_EXP=%WORKING_PATH%\.VkeyExp
Set PUBLIC_KEY_FILENAME_HASH=%WORKING_PATH%\PubKeyhash.bin
Set PFATCRYPTCON=%WORKING_PATH%\PfatCryptoCon.exe
Set KEYGEN=%WORKING_PATH%\Keygen.exe
Set CUTROM=%WORKING_PATH%\CutRom.exe
Set PSL2BIN=%WORKING_PATH%\psl2bin.exe
Set PPB=%WORKING_PATH%\PPB.exe
Set PSL_FILE=AmiPfatBiosPSL
Set PFAT_SCRIPT_HDR=%WORKING_PATH%\PfatCertHeader.bin
Set PFAT_UPDATEPKG_FILENAME=UpdatePkg.pfat
Set PFAT_SIGNATURE_FILENAME=.out_PfatCer
Set PFAT_INTREGRATION_ROM=AMIPFAT.bin
Set AMI_PFAT_HEADER=%WORKING_PATH%\AMIPFATHeader.bin
%WORKING_PATH%\BuildAmiPfatHeader.exe /Empty %AMI_PFAT_HEADER%
copy %AMI_PFAT_HEADER% %PFAT_INTREGRATION_ROM%
goto BUILD_DESCRIPTOR_REGION_ROM

:BUILD_DESCRIPTOR_REGION_ROM
    Set ROM_PRIORITY=%DESCRIPTOR_REGION_ROM%
    Set /a FV_StartingAddress=%DescriptorRegionStartingAddress%
    Set /a FV_Length=%DescriptorRegionLength%
    goto SETUP_PARAMETERS

:BUILD_GBE_REGION_ROM
    Set ROM_PRIORITY=%GBE_REGION_ROM%
    Set /a FV_StartingAddress=%GbERegionStartingAddress%
    Set /a FV_Length=%GbERegionLength%
    goto SETUP_PARAMETERS

:BUILD_ME_REGION_ROM
    Set ROM_PRIORITY=%ME_REGION_ROM%
    Set /a FV_StartingAddress=%MERegionStartingAddress%
    Set /a FV_Length=%MERegionLength%
    goto SETUP_PARAMETERS

:BUILD_BIOS_REGION_ROM_FIRST_FV
    Set /a BIOS_FV_Number=0
    FOR /F "usebackq tokens=1-4" %%G IN ("%BuildBIOSMap%") DO (
        Set ROM_PRIORITY=%%G
        Set FlashCMD=%%H
        Set /a FV_StartingAddress=%BIOSRegionStartingAddress%+%%I
        Set /a FV_Length=%%J
        goto SETUP_PARAMETERS
    )
    goto BuildAmiPfatHeader

:BUILD_BIOS_REGION_ROM_REMAINDER
    Set /a BIOS_FV_Number+=1
    FOR /F "skip=%BIOS_FV_Number% usebackq tokens=1-4" %%G IN ("%BuildBIOSMap%") DO (
        Set ROM_PRIORITY=%%G
        Set FlashCMD=%%H
        Set /a FV_StartingAddress=%BIOSRegionStartingAddress%+%%I
        Set /a FV_Length=%%J
        goto SETUP_PARAMETERS
    )
    goto BuildAmiPfatHeader

:SETUP_PARAMETERS
    %CUTROM% %INPUT_BIOS_IMAGE% %ROM_PRIORITY% %FV_StartingAddress% %FV_Length%
    Set /a FlashRemainderSize=%FV_Length%%%FlashSectionSize%
    Set /a SUBTRACT_BLOCK_SIZE_FROM_DATA_SIZE=%FlashSectionSize%-0x1000
    Set /a START_COUNT=0
    Set /a NoRemainderCount=%FV_Length%/%FlashSectionSize%
    if %NoRemainderCount% GTR 0 (
        Set /a NoRemainderCount-=1
        Set /a SKIP_CUT_ROM=1
    ) else (
        Set /a SKIP_CUT_ROM=0
    )
    if %FlashRemainderSize% EQU 0 (
        Set /a END_COUNT=%FV_Length%/%FlashSectionSize%-1
    ) else (
        Set /a END_COUNT=%FV_Length%/%FlashSectionSize%
    )
    Set /a END_OF_SIZE=%FV_StartingAddress%+%FV_Length%
    goto AutoBuildPSL

:AutoBuildPSL
    Set /a START_FLASH_SECTION=%START_COUNT%*%FlashSectionSize%
    Set /a START_FLASH_SECTION_IN_MB=%START_FLASH_SECTION%/%FlashSectionSize%
    Set FLASH_ROM=AMI_%START_FLASH_SECTION_IN_MB%M.rom
    Set PSL_OUT_FILENAME=AmiPfatBiosPSLOutput_%START_FLASH_SECTION_IN_MB%M.bin
    Set FLASH_ROM_OUTPUT_FILENAME=APFAT%START_FLASH_SECTION_IN_MB%M.bin
    Set /a SUBTRACT_BLOCK_SIZE_FROM_TOTAL_ROM_SIZE=%FV_StartingAddress%
    Set /a CURRENT_SIZE=%START_COUNT%+1
    Set /a CURRENT_SIZE*=%FlashSectionSize%
    Set /a CURRENT_SIZE-=0x1000
    if %SKIP_CUT_ROM% EQU 1 (
         if %NoRemainderCount% GEQ %START_COUNT% (
             %CUTROM% %ROM_PRIORITY% %FLASH_ROM% %START_FLASH_SECTION% %FlashSectionSize%
             Set /a SUBTRACT_BLOCK_SIZE_FROM_TOTAL_ROM_SIZE+=%CURRENT_SIZE%
         ) else (
             %CUTROM% %ROM_PRIORITY% %FLASH_ROM% %START_FLASH_SECTION% %FlashRemainderSize%
             Set /a SUBTRACT_BLOCK_SIZE_FROM_TOTAL_ROM_SIZE=%END_OF_SIZE%-0x1000
             Set /a SUBTRACT_BLOCK_SIZE_FROM_DATA_SIZE=%FlashRemainderSize%-0x1000
        )
    ) else (
         Set FLASH_ROM=%ROM_PRIORITY%
         Set /a SUBTRACT_BLOCK_SIZE_FROM_TOTAL_ROM_SIZE=%END_OF_SIZE%-0x1000
         Set /a SUBTRACT_BLOCK_SIZE_FROM_DATA_SIZE=%FlashRemainderSize%-0x1000
    )
    echo begin > %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo // Set up initial values for update process >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set F0 %SUBTRACT_BLOCK_SIZE_FROM_TOTAL_ROM_SIZE%; Total ROM size >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set B0 %SUBTRACT_BLOCK_SIZE_FROM_DATA_SIZE%; Data size >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set I0 0; the offset count >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set I1 0x1000; the FLASH BLOCK SIZE >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set I2 0; Erase error count >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set I3 0; Write error count >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set I4 3; Max errors >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set I5 0; Error Code Buffer >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set I6 0; Read error count >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jmp _read; >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _read_retry_label:  >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo add I6 1; increment the read retries count >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo compare I6 I4; compare read retries count to max retries >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jge _read_error_label >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jmp _read; if error START_COUNT is smaller than Max errors jump to read>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _erase_retry_label:  >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo add I2 1; increment the erase retries count >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo compare I2 I4; compare erase retries count to max retries >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jge _erase_error_label >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jmp _erase; if error START_COUNT is smaller than Max errors jump to erase >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _write_retry_label: >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo add I3 1; increment the write retries count >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo compare I3 I4; compare write retries count to max retries >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jge _write_error_label >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jmp _write; if error START_COUNT is smaller than Max errors jump to weite>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _loop: >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _read: >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo read B1 F0 I1; read block 4KB >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo rdsts I5; read the HW status into I5 >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo compare I5 0; >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jne _read_retry_label; if HW status != 0 jump to retry >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo compare B0 B1 I1; compare B0 vs B1 >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl    
    echo je _skip_erase_and_write; if B0 == B1 skip erase and write >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl  

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _erase: >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo eraseblk F0; erase block 4KB >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo rdsts I5; read the HW status into I5 >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo compare I5 0; >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jne _erase_retry_label; if HW status != 0 jump to retry >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _write: >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo write F0 B0 I1; write block >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo rdsts I5; read the HW status into I5 >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo compare I5 0; >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jne _write_retry_label; if HW status != 0 jump to retry  >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _skip_erase_and_write: >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo add I0 I1; increment offset >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo // check if we reached the end of the buffer. We can't increment F0.offset and B0.offset to be more than BIOS size. >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    if %SKIP_CUT_ROM% EQU 1 (
        if %NoRemainderCount% GEQ %START_COUNT% (
            echo compare I0 %FlashSectionSize%; compare count with BIOS image size >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
            echo jge _end; if the count is greater or equal to %FlashSectionSize% then complete  >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl        
        ) else (
            echo compare I0 %FlashRemainderSize%; compare count with BIOS image size >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
            echo jge _end; if the count is greater or equal to %FlashRemainderSize% then complete  >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
        )
    ) else (
        echo compare I0 %FlashRemainderSize%; compare count with BIOS image size >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
        echo jge _end; if the count is greater or equal to %FlashRemainderSize% then complete  >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    )
    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo //Sub 4KB to offsets >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo sub F0 I1; Decrement flash offset >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo sub B0 I1; Decrement buffer offset >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jmp _loop; work on the next block >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _read_error_label: >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set If 1; set error in If >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jmp _end; >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _erase_error_label: >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set If 2; set error in If >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo jmp _end; >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _write_error_label: >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set If 3; set error in If >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo _end: >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo set If 0; set error = 0 if success >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    echo.>> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl
    echo end >> %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl

    %PSL2BIN%  %PSL_FILE%_%START_FLASH_SECTION_IN_MB%M.psl  %PSL_OUT_FILENAME%
    %PPB% -script %PSL_OUT_FILENAME% -data %FLASH_ROM% -package %PFAT_UPDATEPKG_FILENAME% -use_sfam true -bios_svn %BIOS_SVN%
    %PFATCRYPTCON% -z -k %PRIVATE_KEY_FILENAME% -f %PFAT_UPDATEPKG_FILENAME% -s
    copy /b %PFAT_UPDATEPKG_FILENAME% + %PFAT_SCRIPT_HDR% + %PFAT_SIGNATURE_FILENAME% %FLASH_ROM_OUTPUT_FILENAME%
    if exist .out_key (
        del .out_key
    )
    del .out_PfatCer
    del %PFAT_UPDATEPKG_FILENAME%
    if %START_COUNT% EQU %END_COUNT% goto FinishedAutoBuildPSL
    Set /a START_COUNT+=1
    goto AutoBuildPSL

:FinishedAutoBuildPSL
    Set /a START_COUNT=0
:IntegrateAllROMs
    Set /a START_FLASH_SECTION=%START_COUNT%*%FlashSectionSize%
    Set /a START_FLASH_SECTION_IN_MB=%START_FLASH_SECTION%/%FlashSectionSize%
    copy /b %PFAT_INTREGRATION_ROM%+APFAT%START_FLASH_SECTION_IN_MB%M.bin %PFAT_INTREGRATION_ROM%
    del APFAT%START_FLASH_SECTION_IN_MB%M.bin
    del AmiPfatBiosPSLOutput_%START_FLASH_SECTION_IN_MB%M.bin
    if exist AMI_%START_FLASH_SECTION_IN_MB%M.rom (
        del AMI_%START_FLASH_SECTION_IN_MB%M.rom
    )
    if %START_COUNT% EQU %END_COUNT% goto FinishedIntegrateAllROMs
    Set /a START_COUNT+=1
    goto IntegrateAllROMs

:FinishedIntegrateAllROMs
    del *.psl
    Set /a END_COUNT+=1
    del %ROM_PRIORITY%
    if "%ROM_PRIORITY%" EQU "%DESCRIPTOR_REGION_ROM%" (
        echo %MeType% /DESC %END_COUNT% ;%ROM_PRIORITY%>>%AMI_PFAT_FLASH_CONFIGURATIONS%
        goto BUILD_GBE_REGION_ROM
    )
    if "%ROM_PRIORITY%" EQU "%GBE_REGION_ROM%" (
        echo %MeType% /GBE  %END_COUNT% ;%ROM_PRIORITY%>>%AMI_PFAT_FLASH_CONFIGURATIONS%
        goto BUILD_ME_REGION_ROM
    )
    if "%ROM_PRIORITY%" EQU "%ME_REGION_ROM%" (
        echo %MeType% /ME   %END_COUNT% ;%ROM_PRIORITY%>>%AMI_PFAT_FLASH_CONFIGURATIONS%
        goto BUILD_BIOS_REGION_ROM_FIRST_FV
    )
    echo %BiosType% %FlashCMD% %END_COUNT% ;%ROM_PRIORITY%>>%AMI_PFAT_FLASH_CONFIGURATIONS%
    goto BUILD_BIOS_REGION_ROM_REMAINDER

:BuildAmiPfatHeader
    %WORKING_PATH%\BuildAmiPfatHeader.exe %AMI_PFAT_FLASH_CONFIGURATIONS% %AMI_PFAT_HEADER%
    copy /b %AMI_PFAT_HEADER%+%PFAT_INTREGRATION_ROM% AMIPFAT_%INPUT_BIOS_IMAGE%
    del %AMI_PFAT_HEADER%
    del %PFAT_INTREGRATION_ROM%
:END