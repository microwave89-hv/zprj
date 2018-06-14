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
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Smbios131/Smbios131.h 1     2/08/12 1:07a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:07a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Smbios131/Smbios131.h $
// 
// 1     2/08/12 1:07a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:40a Klzhan
// Initial Check-in
// 
// 2     12/16/10 3:58a Klzhan
// [TAG]  		EIP50237
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Txt Support is not been set in SMBIOS type 131
// [RootCause]  	SETUP_CPU_FEATURES structure has been changed.
// [Solution]  	Include PlatformCPULib.h.
// [Files]  		Smbios131.c and Smbios131.h
// 
// 1     12/03/10 5:09a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            Smbios131.h
//
// Description:     Header file for SMbios131 module.
//
//----------------------------------------------------------------------------
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
#define MEBX_FILE_GUID \
  { \
    0x7c81c66a, 0x4f11, 0x47ab, 0x82, 0xd3, 0x67, 0xc4, 0xd6, 0x35, 0xae, 0xd1 \
  }
#if VA_SUPPORT
#include EFI_PROTOCOL_DEFINITION(PlatformVaPolicy)
#endif

#define vPro_Signature                 "vPro"

#define EFI_MSR_IA32_FEATURE_CONTROL      0x3A
#define TXT_OPT_IN_VMX_AND_SMX_MSR_VALUE  0xFF03
#define EFI_VA30_VERSION                  0x0300
#define EFI_VA26_VERSION                  0x0206




#define PciMeRegBase            PCIEX_BASE_ADDRESS + (UINT32) (22 << 15)
#define FW_STATUS_REGISTER      0x40

//
// This is definition for SMBIOS Oem data type 0x81
//
#pragma pack (1)
//
// This is definition for SMBIOS Oem data type 0x83
//
typedef struct {
	UINT32	VMXState : 1;		//[0]	VMX state (On/Off)
	UINT32	SMXState : 1;		//[1]	SMX state (On/Off)
	UINT32	LtTxtCap : 1;		//[2]	LT/TXT capability 
	UINT32	LtTxtEnabled : 1;	//[3]	LT/TXT Enabled state (Optional for vPro verification)
	UINT32	VTxCap : 1;			//[4]	VT-x capability
	UINT32	VTxEnabled : 1;		//[5]	VT-x Enabled state (Optional for vPro verification)
	UINT32	Reserved : 26;		//[31:6]	Reserved, set to 0
} CPU_CAP;

typedef struct {
	UINT32	FunctionNumber : 3;	//[2:0]	PCI Device Function Number
	UINT32	DeviceNumber : 5;	//[7:3]	PCI Device Device Number
	UINT32	BusNumber : 8;		//[15:8]	PCI Device Bus Number
	UINT32	DeviceID : 16;		//[31:16]	Device Identification Number (DID): 		This field is the identifier of ICHx PCI 		device.DID will be set to 0xFF if not 		found.
	UINT32	Reserved : 32;		//[63:32]	Reserved, must set to 0xFF
} PCH_CAP;

typedef struct {
	UINT32	FunctionNumber : 3;	//[2:0]	PCI Device Function Number of Wired LAN
	UINT32	DeviceNumber : 5;	//[7:3]	PCI Device Device Number of Wired LAN
	UINT32	BusNumber : 8;		//[15:8] PCI Device Bus Number of Wired LAN
	UINT32	DeviceID : 16;		//[31:16] PCI Device Identifier (DID) of wired NIC. DID will be set to 0xFF if not found.
	UINT16	Reserved1;		//[47:32] Reserved for Wired NIC.
	UINT32	wFunctionNumber : 3;	//[51:48] PCI Device Function Number of Wireless LAN
	UINT32	wDeviceNumber : 5;	//[56:52] PCI Device Device Number of Wireless LAN
	UINT32	wBusNumber : 8;		//[64:57] PCI Device Bus Number of Wireless LAN
	UINT32	wDeviceID : 16;		//[80:65] PCI Device Identifier (DID) of Wireless NIC. DID will be set to 0xFF if not found.
	UINT16	wReserved1;     	//[95:81] Reserved for Wireless NIC.
} NETWORK_DEV;


typedef struct {
	UINT32	Reserved1 : 1;		//[0]		Reserved,  must be set to 0
	UINT32	VTdSupport : 1;		//[1]		BIOS supports VT-d in BIOS setup screen (can be editable).
	UINT32	TxtSupport : 1;		//[2]		BIOS supports TXT in BIOS setup screen (can be editable).
	UINT32	Reserved2 : 1;		//[3]		Reserved,  must be set to 0
	UINT32	MeSupport : 1;		//[4]		BIOS supports ME in BIOS setup screen (can be editable).
	UINT32	VTxSupport : 1;		//[5]		BIOS supports VT-x in BIOS setup screen (can be editable).
								// The PlaformDataInSpi & MaxVASupported moved from Bit 6 & 7 to 8, 9	        
	UINT32	TdtPbaSupport : 1;	//[6]		BIOS supports VT-d in BIOS setup screen (can be editable).
	UINT32	TdtWwanSuport : 1;	//[7]		BIOS supports TXT in BIOS setup screen (can be editable).
	UINT32	Reserved : 24;		//[31:8]	Reserved, must set to 0
} BIOS_CAP;

typedef struct {
  SMBIOS_STRUCTURE_HEADER        Header;
  CPU_CAP                        CpuCapabilities;
  UINT16                         vMEBX_Major;
  UINT16                         vMEBX_Minor;
  UINT16                         vMEBX_HotFix;
  UINT16                         vMEBX_Build;
  PCH_CAP                        PchCapabilities;
  ME_CAP                         MeCapabilities;
  UINT16                         Reserved1[2];
  NETWORK_DEV                    NetworkDevice;
  BIOS_CAP                       BiosCapabilities;
  UINT8                          vProSignature[4]; 
  UINT32                         Reserved2;
  UINT16                         Zero;   //terminator
} EFI_MISC_OEM_TYPE_0x83;

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