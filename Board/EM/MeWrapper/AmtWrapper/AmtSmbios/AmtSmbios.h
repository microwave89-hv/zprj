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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSmbios/AmtSmbios.h 1     2/08/12 1:09a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:09a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSmbios/AmtSmbios.h $
// 
// 1     2/08/12 1:09a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:44a Klzhan
// Initial Check-in
// 
// 2     12/16/10 3:47a Klzhan
// Remove un-use structure.
// 
// 1     12/03/10 5:11a Klzhan
// Initial Check-in.
//
//**********************************************************************
//
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		AMTSmbios.dxs
//
// Description:	AMT Smbios include file.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include  "Token.h"
#include  <Tiano.h>
#include  <Include\Protocol\SMBios.h>
#include  <Include\Protocol\SmbiosGetFlashDataProtocol.h>
#include  <AmtLib.h>
#include  <MeLib.h>
#include  "CpuFuncs.h"

#include EFI_GUID_DEFINITION    (MeBiosExtensionSetup)
#include EFI_GUID_DEFINITION (GlobalVariable)
#include EFI_PROTOCOL_DEFINITION  (PciIo)
#include EFI_PROTOCOL_CONSUMER    (PciRootBridgeIo)
#include EFI_PROTOCOL_DEPENDENCY (SaPlatformPolicy)
#include EFI_PROTOCOL_CONSUMER  (Heci)
#include EFI_PROTOCOL_CONSUMER  (TcgService)

#if VA_SUPPORT
#include EFI_PROTOCOL_DEFINITION(PlatformVaPolicy)
#endif

#define EFI_OEM_ASF_DESCRIPTIONSTRING "Intel_ASF"
#define EFI_OEM_ASF_SYSTEMIDSTRING    "Intel_ASF_001"
#define AMT_Signature                 "$AMT"

#define PciMeRegBase            PCIEX_BASE_ADDRESS + (UINT32) (22 << 15)
#define FW_STATUS_REGISTER      0x40

//
// This is definition for SMBIOS Oem data type 0x81
//
#pragma pack (1)
typedef struct {
  SMBIOS_STRUCTURE_HEADER       Header;
  UINT8                         DescString;// String number
  UINT8                         StructureVersion;
  UINT8                         SystemId;// String number
  UINT8                         Attribute;
  UINT8                         DescStringAscii[sizeof(EFI_OEM_ASF_DESCRIPTIONSTRING)];
  UINT8                         SystemIdAscii[sizeof(EFI_OEM_ASF_SYSTEMIDSTRING)-1];
  UINT16												Zero;		//terminator
} EFI_MISC_OEM_TYPE_0x81; 

//
// This is definition for SMBIOS Oem data type 0x82
//
typedef struct {
  SMBIOS_STRUCTURE_HEADER       Header;
  UINT8                         AmtSignature[4];
  UINT8                         AmtSupported;
  UINT8                         AmtEnabled;
  UINT8                         IderEnabled;
  UINT8                         SolEnabled;
  UINT8                         NetworkEnabled;
  UINT8                         ExtendedData;
  UINT8                         OemCapabilities1;
  UINT8                         OemCapabilities2;
  UINT8                         OemCapabilities3;
  UINT8                         OemCapabilities4;
  UINT8                         KvmEnabled;
  UINT8                         Reserved;		
  UINT16                        Zero;   //terminator
} EFI_MISC_OEM_TYPE_0x82;

#pragma pack ()

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