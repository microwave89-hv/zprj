/*++
  This file contains a 'Sample Driver' and is licensed as such  
  under the terms of your license agreement with Intel or your  
  vendor.  This file may be modified by the user, subject to    
  the additional terms of the license agreement                 
--*/

/*++

Copyright (c)  1999 - 2010 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  GlobalNvsArea.h

Abstract:

  Definition of the global NVS area protocol.  This protocol 
  publishes the address and format of a global ACPI NVS buffer used as a communications
  buffer between SMM code and ASL code.
  The format is derived from the ACPI reference code, version 0.95.

  Note:  Data structures defined in this protocol are not naturally aligned.

--*/

#ifndef _GLOBAL_NVS_AREA_H_
#define _GLOBAL_NVS_AREA_H_

//
// Includes
//


//
// Forward reference for pure ANSI compatability
//
EFI_FORWARD_DECLARATION (EFI_GLOBAL_NVS_AREA_PROTOCOL);

//
// Global NVS Area Protocol GUID
//
#define EFI_GLOBAL_NVS_AREA_PROTOCOL_GUID \
  { \
    0x74e1e48, 0x8132, 0x47a1, 0x8c, 0x2c, 0x3f, 0x14, 0xad, 0x9a, 0x66, 0xdc \
  }
//
// Global NVS Area Protocol GUID
//
#define EFI_GLOBAL_SANVS_AREA_PROTOCOL_GUID \
  { \
    0x9f8083d3, 0x292c, 0x4f8f, 0x88, 0x79, 0xca, 0xcc, 0x8e, 0x63, 0xed, 0x67 \
  }
//
// Revision id - Added TPM related fields
//
#define GLOBAL_NVS_AREA_REVISION_1       1
//
// Extern the GUID for protocol users.
//
extern EFI_GUID gEfiGlobalNvsAreaProtocolGuid;
extern EFI_GUID gEfiGlobalSaNvsAreaProtocolGuid;

//
// Global NVS Area definition
//
#pragma pack (1)
typedef struct {
  //
  // Miscellaneous Dynamic Values, the definitions below need to be matched 
  // GNVS definitions in Platform.ASL
  //
  UINT16      OperatingSystem;              // (000) Operating System
  UINT8       SmiFunction;                  // (002) SMI Function Call (ASL to SMI via I/O Trap)
  UINT8       SmiParameter0;                // (003) SMIF - Parameter 0
  UINT8       SmiParameter1;                // (004) SMIF - Parameter 1
  UINT8       SciFunction;                  // (005) SCI Function Call (SMI to ASL via _L00)
  UINT8       SciParameter0;                // (006) SCIF - Parameter 0
  UINT8       SciParameter1;                // (007) SCIF - Parameter 1
  UINT8       GlobalLock;                   // (008) Global Lock Function Call (EC Communication)
  UINT8       LockParameter0;               // 009) LCKF - Parameter 0
  UINT8       LockParameter1;               // (010) LCKF - Parameter 1
  UINT32      Port80DebugValue;             // (011) Port 80 Debug Port Value
  UINT8       PowerState;                   // (015) Power State (AC Mode = 1)
  UINT8       DebugState;                   // (016) Debug State


  //
  // Thermal Policy Values
  //
  UINT8       THOF;                         // (017) Enable Thermal Offset for KSC
  UINT8       Ac1TripPoint;                 // (018) Active Trip Point 1
  UINT8       Ac0TripPoint;                 // (019) Active Trip Point
  UINT8       PassiveThermalTripPoint;      // (020) Passive Trip Point
  UINT8       PassiveTc1Value;              // (021) Passive Trip Point TC1 Value
  UINT8       PassiveTc2Value;              // (022) Passive Trip Point TC2 Value
  UINT8       PassiveTspValue;              // (023) Passive Trip Point TSP Value
  UINT8       CriticalThermalTripPoint;     // (024) Critical Trip Point
  UINT8       EnableDigitalThermalSensor;   // (025) Digital Thermal Sensor Enable
  UINT8       BspDigitalThermalSensorTemperature;   // (026) Digital Thermal Sensor 1 Reading
  UINT8       ApDigitalThermalSensorTemperature;    // (027) Digital Thermal Sensor 2 Reading
  UINT8       DigitalThermalSensorSmiFunction;      // (028) DTS SMI Function Call 
  UINT8       Reserved[1];                     // (029)

  //
  // Battery Support Registers: (Moved outside this ASL code but still in used)
  //
  UINT8       NumberOfBatteries;            // (030) Battery Number Present
  UINT8       BatteryCapacity0;             // (031) Battery 0 Stored Capacity
  UINT8       BatteryCapacity1;             // (032) Battery 1 Stored Capacity
  UINT8       BatteryCapacity2;             // (033) Battery 2 Stored Capacity
  UINT8       BatteryStatus0;               // (034) Battery 0 Stored Status
  UINT8       BatteryStatus1;               // (035) Battery 1 Stored Status
  UINT8       BatteryStatus2;               // (036) Battery 2 Stored Status

  // NOTE: Do NOT Change the Offset of Revision Field
  UINT8       Revision;                     // (037) Revision of the structure EFI_GLOBAL_NVS_AREA
  UINT8       Reserved3[2];                 // (038:039)

  //
  // Processor Configuration Values
  //
  UINT8       ApicEnable;                   // (040) APIC Enabled by SBIOS (APIC Enabled = 1)
  UINT8       ThreadCount;                  // (041) Number of Enabled Threads
  UINT8       CurentPdcState0;              // (042) PDC settings, Processor 0
  UINT8       CurentPdcState1;              // (043) PDC settings, Processor 1
  UINT8       MaximumPpcState;              // (044) Maximum PPC state
  UINT32      PpmFlags;                     // (045) PPM configuration flags, same as CFGD
  UINT8       C6C7Latency;                  // (049) C6/C7 Entry/Exit latency
  
  //
  // SIO Configuration Values
  //
  UINT8       DockedSioPresent;             // (050) Dock SIO Present
  UINT8       DockComA;                     // (051) COM A Port
  UINT8       DockComB;                     // (052) COM B Port
  UINT8       DockLpt;                      // (053) LPT Port
  UINT8       DockFdc;                      // (054) FDC Port
  UINT8       SmscComPort;                  // (055) SMSC Com Port
  UINT8       SmscComCirPort;               // (056) SMSC Com CIR Port
  UINT8       SMSC1007;                     // (057) SMSC1007 SIO Present
  UINT8       WPCN381U;                     // (058) WPCN381U SIO Present
  UINT8       SMSC1000;                     // (059) SMSC1000 SIO Present  
  
  //
  // Extended Mobile Access Values
  //
  UINT8       EmaEnable;                    // (060)  EMA Enable
  UINT16      EmaPointer;                   // (061)  EMA Pointer
  UINT16      EmaLength;                    // (063:064)  EMA Length

  UINT8       Reserved8[1];                 // (065)

  //
  // Mobile East Fork Values
  //
  UINT8       MefEnable;                    // (066) Mobile East Fork Enable

  //
  // PCIe Dock Status
  //
  UINT8       PcieDockStatus;               // (067) PCIe Dock Status

  UINT8       Reserved9[4];                 // (068:071)

  //
  // TPM Registers
  //
  UINT8       MorData;                      // (072) Memory Overwrite Request Data
  UINT8       TcgParamter;                  // (073) Used for save the Mor and/or physical presence paramter
  UINT32      PPResponse;                   // (074) Physical Presence request operation response
  UINT8       PPRequest;                    // (078) Physical Presence request operation
  UINT8       LastPPRequest;                // (079) Last Physical Presence request operation

  //
  // SATA Values
  //
  UINT8       GtfTaskFileBufferPort0[7];    // (080)  GTF Task File Buffer for Port 0
  UINT8       GtfTaskFileBufferPort2[7];    // (087)  GTF Task File Buffer for Port 2
  UINT8       IdeMode;                      // (094)  IDE Mode (Compatible\Enhanced)
  UINT8       GtfTaskFileBufferPort1[7];    // (095) GTF Task File Buffer for Port 1

  //
  // Board Id
  // This field is for the ASL code to know whether this board is Matanzas, or Oakmont, etc
  //
  UINT16      BoardId;                      // (102) Platform board id
  UINT8       PlatformId;                   // (104) Platform id 
  UINT8       ECTG;                         // (105) Toggle EC
  UINT8       Reserved10[6];                // 106:111
  UINT8       PcieOSCControl;               // (112) PCIE OSC Control
  UINT8       NativePCIESupport;            // (113) Native PCI Express Support

  //
  // USB Sideband Deferring Support
  //
  UINT8       HostAlertVector1;             // (114) GPE vector used for HOST_ALERT#1
  UINT8       HostAlertVector2;             // (115) GPE vector used for HOST_ALERT#2

  UINT8       Reserved11[6];                // 116:121
  UINT8       DosDisplaySupportFlag;        // (122) _DOS Display Support Flag.
  UINT8       EcAvailable;                  // (123) Embedded Controller Availability Flag.
  UINT8       GPIC;                         //   (124) Global IOAPIC/8259 Interrupt Mode Flag.
  UINT8       CTYP;                         //   (125) Global Cooling Type Flag.
  UINT8       L01C;                         //   (126) Global L01 Counter.
  UINT8       VFN0;                         //   (127) Virtual Fan0 Status.
  UINT8       VFN1;                         //   (128) Virtual Fan1 Status.
  UINT8       VFN2;                         //   (129) Virtual Fan2 Status.
  UINT8       VFN3;                         //   (130) Virtual Fan3 Status.
  UINT8       VFN4;                         //   (131) Virtual Fan4 Status. 
  UINT8       VFN5;                         //   (132) Virtual Fan5 Status.
  UINT8       VFN6;                         //   (133) Virtual Fan6 Status.
  UINT8       VFN7;                         //   (134) Virtual Fan7 Status.
  UINT8       VFN8;                         //   (135) Virtual Fan8 Status.
  UINT8       VFN9;                         //   (136) Virtual Fan9 Status.
  UINT8       Reserved12[6];                // 137:142

  //
  // Thermal
  //
  UINT8       ActiveThermalTripPointSA;     // (143) Active Trip Point for MCH
  UINT8       PassiveThermalTripPointSA;    // (144) Passive Trip Point for MCH
  UINT8       ActiveThermalTripPointTMEM;   // (145) Active Trip Point for TMEM
  UINT8       PassiveThermalTripPointTMEM;  // (146) Passive Trip Point for TMEM
  UINT32      PlatformCpuId;                // (147) CPUID Feature Information [EAX]
  UINT32      TBARB;                        // (151) Thermal Base Low Address for BIOS
  UINT32      TBARBH;                       // (155) Thermal Base High Address for BIOS
  UINT8       RunTimeInterface;             // (159) Run Time Interface for Intelligent Power Savings
  UINT8       TsOnDimmEnabled;              // (160) TS-on-DIMM is chosen in SETUP and present on the DIMM
  UINT8       ActiveThermalTripPointPCH;    // (161) Active Trip Point for PCH
  UINT8       PassiveThermalTripPointPCH;   // (162) Passive Trip Point for PCH

  //
  // Board info
  //
  UINT8       PlatformFlavor;               // (163) Platform Flavor
  UINT8       BoardRev;                     // (164) Board Rev

  // Package temperature
  UINT8       PackageDTSTemperature;        // (165) Package Temperature
  UINT8       IsPackageTempMSRAvailable;    // (166) Package Temperature MSR available
  UINT8       PeciAccessMethod;             // (167) PECI Access Method (Direct I/O or ACPI)
  UINT8       Ac0FanSpeed;                  // (168) _AC0 Fan Speed
  UINT8       Ac1FanSpeed;                  // (169) _AC1 Fan Speed 
  // New Thermal Policy Values for DTS.
  UINT8  Ap2DigitalThermalSensorTemperature;   // (170) Temperature of the second AP
  UINT8  Ap3DigitalThermalSensorTemperature;   // (171) Temperature of the third AP
  UINT8       Reserved16[4];                // (172):(175) are reserved for future use

  UINT8       LTRE1;                        // (176) Latency Tolerance Reporting Enable
  UINT8       LTRE2;                        // (177) Latency Tolerance Reporting Enable
  UINT8       LTRE3;                        // (178) Latency Tolerance Reporting Enable
  UINT8       LTRE4;                        // (179) Latency Tolerance Reporting Enable
  UINT8       LTRE5;                        // (180) Latency Tolerance Reporting Enable
  UINT8       LTRE6;                        // (181) Latency Tolerance Reporting Enable
  UINT8       LTRE7;                        // (182) Latency Tolerance Reporting Enable
  UINT8       LTRE8;                        // (183) Latency Tolerance Reporting Enable

  UINT8       OBFF1;                        // (184) Optimized Buffer Flush and Fill
  UINT8       OBFF2;                        // (185) Optimized Buffer Flush and Fill
  UINT8       OBFF3;                        // (186) Optimized Buffer Flush and Fill
  UINT8       OBFF4;                        // (187) Optimized Buffer Flush and Fill
  UINT8       OBFF5;                        // (188) Optimized Buffer Flush and Fill
  UINT8       OBFF6;                        // (189) Optimized Buffer Flush and Fill
  UINT8       OBFF7;                        // (190) Optimized Buffer Flush and Fill
  UINT8       OBFF8;                        // (191) Optimized Buffer Flush and Fill

  UINT8       XhciMode;                     // (192) xHCI controller mode
  UINT32      XTUBaseAddress;               // (193) XTU Continous structure Base Address 
  UINT32      XTUSize;                      // (197) XTU Entries Size
  UINT32      XMPBaseAddress;               // (201) XTU Base Address
  UINT8       DDRReferenceFreq;             // (205) DDR Reference Frequency

  UINT8       Rtd3Support;                  // (206) Runtime D3 support.
  UINT8       Rtd3P0dl;                     // (207) User selctable Delay for Device D0 transition.
  UINT8       Rtd3P3dl;                     // (208) User selctable Delay for Device D3 transition.
  //
  // DPTF Devices and trip points
  //
  UINT8     EnableDptfDevice;               // (209) EnableDptfDevice

  UINT8     EnableSaDevice;                 // (210) EnableSaDevice
  UINT8     CriticalThermalTripPointSA;     // (211) CriticalThermalTripPointSa
  UINT8     HotThermalTripPointSA;          // (212) HotThermalTripPointSa

  UINT8     EnablePchDevice;                // (213) EnablePchDevice
  UINT8     CriticalThermalTripPointPCH;    // (214) CriticalThermalTripPointPch
  UINT8     HotThermalTripPointPCH;         // (215) HotThermalTripPointPch
  //
  // DPTF Policies
  //
  UINT8     EnableCtdpPolicy;               // (216) EnableCtdpPolicy
  UINT8     EnableLpmPolicy;                // (217) EnableLpmPolicy
  UINT8     CurrentLowPowerMode;            // (218) CurrentLowPowerMode for LPM
  UINT8     EnableCurrentExecutionUnit;     // (219) EnableCurrentExecutionUnit
  UINT16    TargetGfxFreq;                  // (220:221) TargetGfxFreq
  //
  // DPPM Devices and trip points
  //
  UINT8     EnableMemoryDevice;             // (222) EnableMemoryDevice
  UINT8     CriticalThermalTripPointTMEM;   // (223) CriticalThermalTripPointTMEM
  UINT8     HotThermalTripPointTMEM;        // (224) HotThermalTripPointTMEM

  UINT8     EnableFan1Device;               // (225) EnableFan1Device
  UINT8     EnableFan2Device;               // (226) EnableFan2Device

  UINT8     EnableAmbientDevice;            // (227) EnableAmbientDevice
  UINT8     ActiveThermalTripPointAmbient;  // (228) ActiveThermalTripPointAmbient
  UINT8     PassiveThermalTripPointAmbient; // (229) PassiveThermalTripPointAmbient
  UINT8     CriticalThermalTripPointAmbient;// (230) CriticalThermalTripPointAmbient
  UINT8     HotThermalTripPointAmbient;     // (231) HotThermalTripPointAmbient

  UINT8     EnableSkinDevice;               // (232) EnableSkinDevice
  UINT8     ActiveThermalTripPointSkin;     // (233) ActiveThermalTripPointSkin
  UINT8     PassiveThermalTripPointSkin;    // (234) PassiveThermalTripPointSkin
  UINT8     CriticalThermalTripPointSkin;   // (235) CriticalThermalTripPointSkin
  UINT8     HotThermalTripPointSkin;        // (236) HotThermalTripPointSkin

  UINT8     EnableExhaustFanDevice;         // (237) EnableExhaustFanDevice
  UINT8     ActiveThermalTripPointExhaustFan;   // (238) ActiveThermalTripPointExhaustFan
  UINT8     PassiveThermalTripPointExhaustFan;  // (239) PassiveThermalTripPointExhaustFan
  UINT8     CriticalThermalTripPointExhaustFan; // (240) CriticalThermalTripPointExhaustFan
  UINT8     HotThermalTripPointExhaustFan;  // (241) HotThermalTripPointExhaustFan

  UINT8     EnableVRDevice;                 // (242) EnableVRDevice
  UINT8     ActiveThermalTripPointVR;       // (243) ActiveThermalTripPointVR
  UINT8     PassiveThermalTripPointVR;      // (244) PassiveThermalTripPointVR
  UINT8     CriticalThermalTripPointVR;     // (245) CriticalThermalTripPointVR
  UINT8     HotThermalTripPointVR;          // (246) HotThermalTripPointVR
  //
  // DPPM Policies
  //
  UINT8     EnableActivePolicy;             // (247) EnableActivePolicy
  UINT8     EnablePassivePolicy;            // (248) EnablePassivePolicy
  UINT8     EnableCriticalPolicy;           // (249) EnableCriticalPolicy
  UINT8     EnableCoolingModePolicy;        // (250) EnableCoolingModePolicy
  UINT8     TrtRevision;                    // (251) TrtRevision
  //
  // CLPO (Current Logical Processor Off lining Setting)
  //
  UINT8     LPOEnable;                      // (252) LPOEnable
  UINT8     LPOStartPState;                 // (253) LPOStartPState
  UINT8     LPOStepSize;                    // (254) LPOStepSize
  UINT8     LPOPowerControlSetting;         // (255) LPOPowerControlSetting
  UINT8     LPOPerformanceControlSetting;   // (256) LPOPerformanceControlSetting
  //
  // Miscellaneous DPTF
  //
  UINT32    PpccStepSize;                   // (257:260) PPCC Step Size
  UINT8     EnableDisplayParticipant;       // (261) EnableDisplayParticipant
  //
  // PFAT
  //
  UINT64    PfatMemAddress;                 // (262:269) PFAT Memory Address for Tool Interface
  UINT8     PfatMemSize;                    // (270) PFAT Memory Size for Tool Interface
  UINT16    PfatIoTrapAddress;              // (271) PFAT IoTrap Address for Tool Interface
  //
  // Smart Connect Technology
  //
  UINT8     IsctCfg;                        // (273) Isct Configuration
  //
  // Audio DSP
  //
  UINT32    DspBar0;                        // (274) Audio DSP BAR0
  UINT32    DspBar1;                        // (278) Audio DSP BAR1
  //
  // NFC support
  //
  UINT8     NFCEnable;                      // (282) NFC module selection 	
  //
  // ADSP Codec Selection
  //
  UINT8     AudioDspCodec;                  // (283) Audio Codec selection
  //
  // Sensor Hub Enable
  //
  UINT8     SensorHubEnable;                // (284) Sensor Hub Enable

  UINT8     LowPowerS0Idle;                 // (285) Low Power S0 Idle Enable

  //
  // BIOS only version of Config TDP
  //
  UINT8     ConfigTdpBios;                  // (286) enable/disable BIOS only version of Config TDP

  UINT8     Reserved17[232];                // (287):(518) are reserved for future use
  UINT8     EnablePowerDevice;              // (519) EnablePowerDevice
  UINT8     EnablePowerPolicy;              // (520) EnablePowerPolicy
  UINT8     UsbPowerResourceTest;           // (521) RTD3 USB Power Resource config
  //
  // Intel Serial(R) IO Sensor Device Selection
  //
  UINT8     SDS0;                           // (522) I2C0 Sensor Device Selection
  UINT16    SDS1;                           // (523) I2C1 Sensor Device Selection
  UINT8     SDS2;                           // (525) SPI0 Sensor Device Selection
  UINT8     SDS3;                           // (526) SPI1 Sensor Device Selection
  UINT8     SDS4;                           // (527) UART0 Sensor Device Selection
  UINT8     SDS5;                           // (528) UART1 Sensor Device Selection
  UINT8     Reserved20[1];                  // (529) 529 no longer used.
  UINT8     RIC0;                           // (530) RTD3 support for I2C0 SH
  UINT8     PepDevice;                      // (531) RTD3 PEP support list(BIT0 - GFx , BIT1 - Sata, BIT2 - UART, BIT3 - SDHC, Bit4 - I2C0, BIT5 - I2C1, Bit6 - XHCI, Bit7 - Audio)
  UINT8     DVS0;                           // (532) Port0 DevSlp Enable
  UINT8     DVS1;                           // (533) Port1 DevSlp Enable
  UINT8     DVS2;                           // (534) Port2 DevSlp Enable
  UINT8     DVS3;                           // (535) Port3 DevSlp Enable
  UINT8     GBSX;                           // (536) Virtual GPIO button Notify Sleep State Change
  UINT8     IUBE;                           // (537) IUER Button Enable
  UINT8     IUCE;                           // (538) IUER Convertible Enable
  UINT8     IUDE;                           // (539) IUER Dock Enable
  UINT8     ECNO;                           // (540) EC Notification of Low Power S0 Idle State
  UINT16    AUDD;                           // (541) RTD3 Audio Codec device delay
  UINT16    DSPD;                           // (543) RTD3 ADSP device delay
  UINT16    IC0D;                           // (545) RTD3 SensorHub delay time after applying power to device
  UINT16    IC1D;                           // (547) RTD3 TouchPanel delay time after applying power to device
  UINT16    IC1S;                           // (549) RTD3 TouchPad delay time after applying power to device
  UINT16    VRRD;                           // (551) VR Ramp up delay
  UINT8     PSCP;                           // (553) P-state Capping
  UINT8     RWAG;                           // (554) Rtd3 W/A Gpio, allow W/A for port 1 and 6 to use GPIO from SDHC device
  UINT16    I20D;                           // (555) Delay in _PS0 after powering up I2C0 Controller
  UINT16    I21D;                           // (557) Delay in _PS0 after powering up I2C1 Controller

  UINT8     Reserved18[2];                  // (559:560) are reserved for future use
  UINT8     RCG0;                           // (561) RTD3 Config Setting(BIT0:ZPODD,BIT1:USB Camera Port4, BIT2/3:SATA Port3)
  UINT8     ECDB;                           // (562) EC Debug Light (CAPS LOCK) for when in Low Power S0 Idle State
  UINT8     P2ME;                           // (563) Ps2 Mouse Enable
  
  UINT16    SSH0;                           // (564) SSCN-LOW  for I2C0
  UINT16    SSL0;                           // (566) SSCN-HIGH for I2C0
  UINT16    SSD0;                           // (568) SSCN-HOLD for I2C0
  UINT16    FMH0;                           // (570) FMCN-LOW  for I2C0
  UINT16    FML0;                           // (572) FMCN-HIGH for I2C0
  UINT16    FMD0;                           // (574) FMCN-HOLD for I2C0
  UINT16    FPH0;                           // (576) FPCN-LOW  for I2C0
  UINT16    FPL0;                           // (578) FPCN-HIGH for I2C0
  UINT16    FPD0;                           // (580) FPCN-HOLD for I2C0
  UINT16    SSH1;                           // (582) SSCN-LOW  for I2C1
  UINT16    SSL1;                           // (584) SSCN-HIGH for I2C1
  UINT16    SSD1;                           // (586) SSCN-HOLD for I2C1
  UINT16    FMH1;                           // (588) FMCN-LOW  for I2C1
  UINT16    FML1;                           // (590) FMCN-HIGH for I2C1
  UINT16    FMD1;                           // (592) FMCN-HOLD for I2C1
  UINT16    FPH1;                           // (594) FPCN-LOW  for I2C1
  UINT16    FPL1;                           // (596) FPCN-HIGH for I2C1
  UINT16    FPD1;                           // (598) FPCN-HOLD for I2C1
  UINT16    M0C0;                           // (600) M0D3 for I2C0
  UINT16    M1C0;                           // (602) M1D3 for I2C0
  UINT16    M2C0;                           // (604) M0D0 for I2C0
  UINT16    M0C1;                           // (606) M0D3 for I2C1
  UINT16    M1C1;                           // (608) M1D3 for I2C1
  UINT16    M2C1;                           // (610) M0D0 for I2C1
  UINT16    M0C2;                           // (612) M0D3 for SPI0
  UINT16    M1C2;                           // (614) M1D3 for SPI0
  UINT16    M0C3;                           // (616) M0D3 for SPI1
  UINT16    M1C3;                           // (618) M1D3 for SPI1
  UINT16    M0C4;                           // (620) M0D3 for UA00
  UINT16    M1C4;                           // (622) M1D3 for UA00
  UINT16    M0C5;                           // (624) M0D3 for UA01
  UINT16    M1C5;                           // (626) M1D3 for UA01
  UINT8     TBSF;                           // (628) ThunderBolt SMI Function Number
  UINT32    GIRQ;                           // (629) GPIO IRQ
  UINT8     DMTP;                           // (633) PIRQS 34,50(GPIO)
  UINT8     DMTD;                           // (634) PIRQX 39,55(GPIO)
  UINT8     DMSH;                           // (635) PIRQM 28,14(GPIO)
  UINT8     LANP;                           // (636) LAN PHY Status 0 = Not Present, 1 = Present                          
  UINT8     Reserved19[1];                  // (637) 637 no longer used.
  UINT8     SHSB;                           // (638) Sensor Standby mode
  UINT8     PL1LimitCS;                     // (639) set PL1 limit when entering CS
  UINT16    PL1LimitCSValue;                // (640) PL1 limit value
  UINT8     GN1E;                           // (642) EnableGen1Participant
  UINT8     G1AT;                           // (643) ActiveThermalTripPointGen1
  UINT8     G1PT;                           // (644) PassiveThermalTripPointGen1
  UINT8     G1CT;                           // (645) CriticalThermalTripPointGen1
  UINT8     G1HT;                           // (646) HotThermalTripPointGen1
  UINT8     GN2E;                           // (647) EnableGen2Participant
  UINT8     G2AT;                           // (648) ActiveThermalTripPointGen2
  UINT8     G2PT;                           // (649) PassiveThermalTripPointGen2
  UINT8     G2CT;                           // (650) CriticalThermalTripPointGen2
  UINT8     G2HT;                           // (651) HotThermalTripPointGen2
  UINT8     WWSD;                           // (652) EnableWwanTempSensorDevice
  UINT8     CVSD;                           // (653) EnableCpuVrTempSensorDevice
  UINT8     SSDD;                           // (654) EnableSsdTempSensorDevice
  UINT8     INLD;                           // (655) EnableInletFanTempSensorDevice
  UINT8     IFAT;                           // (656) ActiveThermalTripPointInletFan
  UINT8     IFPT;                           // (657) PassiveThermalTripPointInletFan
  UINT8     IFCT;                           // (658) CriticalThermalTripPointInletFan
  UINT8     IFHT;                           // (659) HotThermalTripPointInletFan
  UINT8     DOSD;                           // (660) DMA OS detection, 1 = check for OS version when enabling DMA, 0 = don't care about OS
  UINT8     USBH;                           // (661) USB Sensor Hub Enable/Disable
  UINT8     BCV4;                           // (662) Broadcom's Bluetooth adapter's revision
  UINT8     WTV0;                           // (663) I2C0/WITT devices version
  UINT8     WTV1;                           // (664) I2C1/WITT devices version
  UINT8     APFU;                           // (665) Atmel panel FW update Enable/Disable
  UINT8     SOHP;                           // (666) SMI on Hot Plug for TBT devices
  UINT8     NOHP;                           // (667) Notify on Hot Plug for TBT devices
  UINT8     TBSE;                           // (668) ThunderBolt Root port selector
  UINT8     WKFN;                           // (669) WAK Finished
  UINT16    PEPC;                           // (670) PEP Constraints
  UINT16    VRSD;                           // (672) VR Staggering delay
  UINT8     PB1E;                           // (674) 10sec Power button support Bit0: 10 sec P-button Enable/Disable
                                            //                                  Bit1: Internal Flag
                                            //                                  Bit2: Rotation Lock flag, 0:unlock, 1:lock
                                            //                                  Bit3: Slate/Laptop Mode Flag, 0: Slate, 1: Laptop
                                            //                                  Bit4: Undock / Dock Flag, 0: Undock, 1: Dock
                                            //                                  Bit5, 6: reserved for future use.
                                            //                                  Bit7: EC 10sec PB Override state for S3/S4 wake up. 
  UINT8     WAND;                           // (675) EnableWWANParticipant
  UINT8     WWAT;                           // (676) ActiveThermalTripPointWWAN
  UINT8     WWPT;                           // (677) PassiveThermalTripPointWWAN
  UINT8     WWCT;                           // (678) CriticalThermalTripPointWWAN
  UINT8     WWHT;                           // (679) HotThermalTripPointWWAN
  UINT8     Reserved21[5];                  // (680:684) are reserved for future use
  UINT16    MPLT;                           // (685) Minimum Power Limit for DPTF use via PPCC Object
  UINT8     GR13;                           // (687) GPIO13 Rework for Sawtooth Peak
  UINT8     SPST;                           // (688) SATA port state, Bit0 - Port0, Bit1 - Port1, Bit2 - Port2, Bit3 - Port3
  UINT8     ECLP;                           // (689) EC Low Power Mode: 1 - Enabled, 0 - Disabled
  UINT8     INSC;                           // (690) Intel RMT Configuration 
//  UINT8     ComIrqShareMode;
} EFI_GLOBAL_NVS_AREA;
#pragma pack ()

//
// Global NVS Area Protocol
//
typedef struct _EFI_GLOBAL_NVS_AREA_PROTOCOL {
  EFI_GLOBAL_NVS_AREA *Area;
} EFI_GLOBAL_NVS_AREA_PROTOCOL;

#endif
