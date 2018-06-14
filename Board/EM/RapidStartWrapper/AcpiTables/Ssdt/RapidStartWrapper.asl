//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/Ssdt/RapidStartWrapper.asl 1     12/27/12 2:25a Bensonlai $
//
// $Revision: 1 $
//
// $Date: 12/27/12 2:25a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/Ssdt/RapidStartWrapper.asl $
// 
// 1     12/27/12 2:25a Bensonlai
// [TAG]  		EIP110680
// [Category]  	New Feature
// [Description]  	When iRST application is run under OS, and change
// timer.
// BIOS should update the changed to Setup option as well.
// [Files]  		Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.c
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.h
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.mak
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.dxs
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.sdl
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.cif
// Board\EM\RapidStartWrapper\AcpiTables\RapidStartWrapperAcpiTables.cif
// Board\EM\RapidStartWrapper\AcpiTables\RapidStartWrapperAcpiTables.sdl
// Board\EM\RapidStartWrapper\AcpiTables\Ssdt\RapidStartWrapper.asl
// Board\EM\RapidStartWrapper\RapidStartSetup\RapidStartSetup.sd
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: RapidStartWrapper.asl
//
// Description: RapidStart ACPI ASL code to support OS control
//
//<AMI_FHDR_END>
//**********************************************************************

DefinitionBlock (
  "RapidStart.aml",
  "SSDT",
  0x01,
  "Iffs",
  "IffsAsl",
  0x3000
  )
{

  Scope (\_SB) {
    Device(IFFS) {
      OperationRegion(FFSN,SystemMemory,0xFFFF0000,0xAA55)
      Field(FFSN,AnyAcc,Lock,Preserve)
      {
        FFSA,	8,      // (0) iFFS available events
        FFSS,	8,      // (1) iFFS enabled events
        FFST,	16,     // (2) iFFS wake timer in minutes
        FFSP,	32      // (4) iFFS performance monitoring data
      }

//AMIOVERRIDE_BEGIN
      OperationRegion (RSMI, SystemIO, 0xB2, 0x02)
      Field (RSMI, ByteAcc, NoLock, Preserve) {
        SMIC, 8,
        SMID, 8
      }
//AMIOVERRIDE_END

      Name(_HID,EISAID("INT3392"))
      Name(_CID,EISAID("PNP0C02"))

      Method(GFFS,0,Serialized) {
        Return(FFSS)
      }
      Method(SFFS,1,Serialized) {
        And(Arg0, FFSA, FFSS)
//AMIOVERRIDE_BEGIN
        Store(0x01, SMID)
        Store(0xB4, SMIC)
//AMIOVERRIDE_END
        Return(FFSS)
      }
      Method(GFTV,0,Serialized) {
        Return(FFST)
      }
      Method(SFTV,1,Serialized) {
        //
        //  24*60=1440 minutes (24 Hours)
        //
        If (LLessEqual(Arg0,1440)) {
          Store(Arg0,FFST)
        } Else {
          And(FFSS,0xFFFE,FFSS)
          Store(10,FFST)
        }
//AMIOVERRIDE_BEGIN
        Store(0x01, SMID)
        Store(0xB4, SMIC)
//AMIOVERRIDE_END
        Return(FFST)
      }
    }
  }
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
