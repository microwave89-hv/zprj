@ECHO OFF
SET RomImagePath=%1
RD /S /Q %RomImagePath%\Build
SET BiosBin=%2
SET FITC_OUTIMAGE_MAP_FILE=%3
SET MeProfile=%4
REM 0 = 1.5MB ME Firmware, 1 = 5MB ME Firmware. 2 = 1.5MB ME9.5 Firmware. 3 = 5MB ME9.5 Firmware.
SET MeFwSelect=%5
SET BinName=%6
REM 1 = One image, 2 = Two image. 
SET ImgCount=%7
REM 0=512KB,1=1MB,2=2MB,3=4MB,4=8MB,5=16MB.
SET ImgSize1=%8
REM 0=512KB,1=1MB,2=2MB,3=4MB,4=8MB,5=16MB.
SET ImgSize2=%9
REM Support SKU=Z87, Z85, Q87, H87, Q85, B85, H81, QM87, HM87, HM86, C222, C223, C224, C228. ME 9.5 SKU = Premium, Mainstream.
SET CheckSku=Z87_SKU Z85_SKU Q87_SKU H87_SKU Q85_SKU B85_SKU H81_SKU QM87_SKU HM87_SKU HM86_SKU C222_SKU C223_SKU C224_SKU C228_SKU Premium_SKU Mainstream_SKU
SET MeFwSku=
FOR %%I IN (%CheckSku%) DO (IF %BinName% == %%I SET MeFwSku=%BinName:~0,-4%&&SET BinName=%BinName:~0,-4%)
GOTO ImageConfig

:MeImageBuild
%MEFITCKIT% %OutImgPath% /b %MeProfile% %OverrideBiosRom% %DefDestDir% %DefWorkingDir% %DefSourceDir% %OverrideMeFwBin% %OverrideMeFwSku% %OverrideGbEBin% %OverrideImgCount% %OverrideImg1Size% %OverrideImg2Size%
IF NOT EXIST %DestDir%\OutImage.bin GOTO FailEND
GOTO RomNameSet

:ImageConfig
SET OverrideMeFwSku=&&SET OverrideMeFwBin=&&SET OverrideImgCount=&&SET OverrideImg1Size=&&SET OverrideImg2Size=&&SET OverrideGbEBin=&&SET DefDestDir=
IF NOT "%ImgCount%" == "" (SET OverrideImgCount=/flashcount %ImgCount%)
IF NOT "%ImgSize1%" == "" SET Img1Size=%ImgSize1%
IF NOT "%Img1Size%" == "" (SET OverrideImg1Size=/flashsize1 %Img1Size%)
IF "%ImgCount%" == "2" SET Img2Size=%ImgSize2%
IF "%ImgCount%" == "2" IF "%ImgSize2%" == "" SET Img2Size=%ImgSize1%
IF NOT "%Img2Size%" == "" (SET OverrideImg2Size=/flashsize2 %Img2Size%)
IF "%MeFwSelect%" == "0" (SET FitcKitFolder=FITC91&&SET MeFitcKitSelect=FITC_1_5.EXE&&SET MeFwBin=ME9.1_1.5M_Production.bin)
IF "%MeFwSelect%" == "1" (SET FitcKitFolder=FITC91&&SET MeFitcKitSelect=FITC_5.EXE&&SET MeFwBin=ME9.1_5M_Production.bin)
IF "%MeFwSelect%" == "2" (SET FitcKitFolder=FITC95&&SET MeFitcKitSelect=FITC_1_5.EXE&&SET MeFwBin=ME9.5_1.5M_Production.bin)
IF "%MeFwSelect%" == "3" (SET FitcKitFolder=FITC95&&SET MeFitcKitSelect=FITC_5.EXE&&SET MeFwBin=ME9.5_5M_Production.bin)
SET DestDir=%RomImagePath%\Build
SET DefDestDir=/d %DestDir%
SET WorkingDir=%RomImagePath%\%FitcKitFolder%\Working
SET DefWorkingDir=/w %WorkingDir%
SET SourceDir=%RomImagePath%
SET DefSourceDir=/s %SourceDir%
SET OutImgPath=/o $DestDir\OutImage.bin
SET OverrideBiosRom=/bios %BiosBin%
SET MEFITCKIT=%RomImagePath%\%FitcKitFolder%\%MeFitcKitSelect%
IF "%MeFwSku%" == "" GOTO MeImageBuild
SET GbEBin=NAHUM6_CLARKSVILLE_MOBILE_5.bin
SET CheckSkuForMB=QM87 HM87 HM86 SuperMobile
FOR %%I IN (%CheckSkuForMB%) DO IF %MeFwSku% == %%I SET GbEBin=NAHUM6_CLARKSVILLE_MOBILE_12.bin
SET CheckSkuForDT=Z87 Z85 Q87 H87 Q85 B85 H81 SuperDesktop
FOR %%I IN (%CheckSkuForDT%) DO IF %MeFwSku% == %%I SET GbEBin=NAHUM6_CLARKSVILLE_DESKTOP_12.bin
SET CheckSkuForWS=C222 C223 C224 C228
FOR %%I IN (%CheckSkuForWS%) DO IF %MeFwSku% == %%I SET GbEBin=NAHUM6_CLARKSVILLE_DESKTOP_12.bin
SET CheckSkuForLPM=Premium Mainstream
FOR %%I IN (%CheckSkuForLPM%) DO IF %MeFwSku% == %%I SET GbEBin=NAHUM6_LP_CLARKVILLE_ULT_5.bin
SET OverrideGbEBin=/gbe %RomImagePath%\GbE\%GbEBin%
SET OverrideMeFwBin=/me %RomImagePath%\ME\%MeFwBin%
SET OverrideMeFwSku=/sku %MeFwSku%
GOTO MeImageBuild

:FailEND
ECHO Build ME Sku=%MeFwSku% Fail.
ECHO Stting:RomImagePath=%RomImagePath% BiosBin=%BiosBin% MeProfile=%MeProfile% MeFwSelect=%MeFwSelect% ImgCount=%ImgCount% ImgSize1=%ImgSize1% ImgSize2=%ImgSize2%
ECHO %MEFITCKIT% %OutImgPath% /b %MeProfile% %OverrideBiosRom% %DefDestDir% %DefWorkingDir% %DefSourceDir% %OverrideMeFwBin% %OverrideMeFwSku% %OverrideGbEBin% %OverrideImgCount% %OverrideImg1Size% %OverrideImg2Size%
GOTO END

:RomNameSet
SET RomSkue=_%BinName%

IF "%BinName%" == "SuperDesktop" SET RomSkue=_SpDt
IF "%BinName%" == "SuperMobile" SET RomSkue=_SpMb
IF "%BinName%" == "Premium" SET RomSkue=_UltP
IF "%BinName%" == "Mainstream" SET RomSkue=_UltM

FOR /F "skip=2 usebackq tokens=1,2,3,4-6" %%G IN ("%FITC_OUTIMAGE_MAP_FILE%") DO (
    if "%%J %%K %%L" EQU "Flash Image " (
        Set /a TOTAL_ROM_SIZE=0x%%I
    )
)
if %TOTAL_ROM_SIZE% LSS 1048576 (
    Set /a FileSize=%TOTAL_ROM_SIZE%/1024
    goto KBSize
) else (
    Set /a FileSize=%TOTAL_ROM_SIZE%/1024/1024
    goto MBSize
)

:KBSize
    Set RomSize=%FileSize%KB
    goto RenameOutImage

:MBSize
    Set RomSize=%FileSize%MB
    goto RenameOutImage

:RenameOutImage
IF EXIST %DestDir%\OutImage(1).bin ren %DestDir%\OutImage(1).bin OutImage_1.bin
IF EXIST %DestDir%\OutImage(2).bin ren %DestDir%\OutImage(2).bin OutImage_2.bin
IF "%BinName%" == "" SET RomSkue=XmlCfg
GOTO ImageOutput

:ImageOutput
IF EXIST %DestDir%\OutImage.bin ECHO Rom_%RomSize%%RomSkue%.bin && move /Y %DestDir%\OutImage.bin Rom_%RomSize%%RomSkue%.bin
IF EXIST Rom_%RomSize%%RomSkue%.bin move /Y Rom_%RomSize%%RomSkue%.bin DW01AR12.bin
IF EXIST %DestDir%\OutImage_1.bin ECHO Rom00%RomSkue%.bin && move /Y %DestDir%\OutImage_1.bin Rom00%RomSkue%.bin
IF EXIST %DestDir%\OutImage_2.bin ECHO Rom01%RomSkue%.bin && move /Y %DestDir%\OutImage_2.bin Rom01%RomSkue%.bin
echo Rom_%RomSize%%RomSkue%.bin>ForPfatName.txt
GOTO END

:END
@ECHO ON