/**************************************************************************;
;*                                                                        *;
;*    Intel Confidential                                                  *;
;*                                                                        *;
;*    Intel Corporation - ACPI Reference Code for the Haswell             *;
;*    Family of Customer Reference Boards.                                *;
;*                                                                        *;
;*                                                                        *;
;*    Copyright (c)  1999 - 2013 Intel Corporation. All rights reserved   *;
;*    This software and associated documentation (if any) is furnished    *;
;*    under a license and may only be used or copied in accordance        *;
;*    with the terms of the license. Except as permitted by such          *;
;*    license, no part of this software or documentation may be           *;
;*    reproduced, stored in a retrieval system, or transmitted in any     *;
;*    form or by any means without the express written consent of         *;
;*    Intel Corporation.                                                  *;
;*                                                                        *;
;*                                                                        *;
;**************************************************************************/
/*++
  This file contains a 'Sample Driver' and is licensed as such  
  under the terms of your license agreement with Intel or your  
  vendor.  This file may be modified by the user, subject to    
  the additional terms of the license agreement                 
--*/



  // Define a Global region of ACPI NVS Region that may be used for any
  // type of implementation.  The starting offset and size will be fixed
  // up by the System BIOS during POST.  Note that the Size must be a word
  // in size to be fixed up correctly.

  OperationRegion(GNVS,SystemMemory,0xFFFF0000,0xAA55)
  Field(GNVS,AnyAcc,Lock,Preserve)
  {
  Offset(0),    // Miscellaneous Dynamic Registers:
  OSYS, 16,     //   (000) Operating System
  SMIF, 8,      //   (002) SMI Function Call (ASL to SMI via I/O Trap)
  PRM0, 8,      //   (003) SMIF - Parameter 0
  PRM1, 8,      //   (004) SMIF - Parameter 1
  SCIF, 8,      //   (005) SCI Function Call (SMI to ASL via _L00)
  PRM2, 8,      //   (006) SCIF - Parameter 0
  PRM3, 8,      //   (007) SCIF - Parameter 1
  LCKF, 8,      //   (008) Global Lock Function Call (EC Communication)
  PRM4, 8,      //   (009) LCKF - Parameter 0
  PRM5, 8,      //   (010) LCKF - Parameter 1
  P80D, 32,     //   (011) Port 80 Debug Port Value
  PWRS, 8,      //   (015) Power State (AC Mode = 1)
  DBGS, 8,      //   (016) Debug State
  Offset(17),   // Thermal Policy Registers:
  THOF, 8,      //   (017) Enable Thermal Offset for KSC
  ACT1, 8,      //   (018) Active Trip Point 1
  ACTT, 8,      //   (019) Active Trip Point
  PSVT, 8,      //   (020) Passive Trip Point
  TC1V, 8,      //   (021) Passive Trip Point TC1 Value
  TC2V, 8,      //   (022) Passive Trip Point TC2 Value
  TSPV, 8,      //   (023) Passive Trip Point TSP Value
  CRTT, 8,      //   (024) Critical Trip Point
  DTSE, 8,      //   (025) Digital Thermal Sensor Enable
  DTS1, 8,      //   (026) Digital Thermal Sensor 1 Reading
  DTS2, 8,      //   (027) Digital Thermal Sensor 2 Reading
  DTSF, 8,      //   (028) DTS SMI Function Call 
  Offset(30),   // Battery Support Registers: (Moved outside this ASL code but still in used)
//  BNUM, 8,    //   (030) Battery Number Present
//  B0SC, 8,    //   (031) Battery 0 Stored Capacity
//  B1SC, 8,    //   (032) Battery 1 Stored Capacity
//  B2SC, 8,    //   (033) Battery 2 Stored Capacity
//  B0SS, 8,    //   (034) Battery 0 Stored Status
//  B1SS, 8,    //   (035) Battery 1 Stored Status
//  B2SS, 8,    //   (036) Battery 2 Stored Status
  Offset(37),   // Revision Field:
  REVN, 8,      //   (037) Revison of GlobalNvsArea
  Offset(40),   // CPU Identification Registers:
  APIC, 8,      //   (040) APIC Enabled by SBIOS (APIC Enabled = 1)
  TCNT, 8,      //   (041) Number of Enabled Threads
  PCP0, 8,      //   (042) PDC Settings, Processor 0
  PCP1, 8,      //   (043) PDC Settings, Processor 1
  PPCM, 8,      //   (044) Maximum PPC state
  PPMF, 32,     //   (045) PPM Flags (Same as CFGD)
  C67L, 8,      //   (049) C6/C7 Entry/Exit latency
  Offset(50),   // SIO CMOS Configuration Registers:
  NATP, 8,      //   (050) National SIO Present
  CMAP, 8,      //   (051)   COM A Port
  CMBP, 8,      //   (052)   COM B Port
  LPTP, 8,      //   (053)   LPT Port
  FDCP, 8,      //   (054)   FDC Port
  CMCP, 8,      //   (055) SMSC Com Port
  CIRP, 8,      //   (056) SMSC Com CIR Port
  SMSC, 8,      //   (057) SMSC1007 SIO Present
  W381, 8,      //   (058) WPCN381U SIO Present
  SMC1, 8,      //   (059) SMSC1000 SIO Present  
  EMAE, 8,      //   (060) EMA Enable
  EMAP, 16,     //   (061) EMA Pointer   
  EMAL, 16,     //   (063) EMA Length
  Offset(66),   // MEF Registers:
  MEFE, 8,      //   (066) MEF Enable
  Offset(67),   // PCIe Dock:
  DSTS, 8,      //   (067) PCIe Dock Status
  Offset(72),   // TPM Registers:
  MORD, 8,      //   (072) Memory Overwrite Request Data
  TCGP, 8,      //   (073) Used for save the Mor and/or physical presence paramter
  PPRP, 32,     //   (074) Physical Presence request operation response
  PPRQ, 8,      //   (078) Physical Presence request operation
  LPPR, 8,      //   (079) Last Physical Presence request operation
  Offset(80),   // SATA Registers:
  GTF0, 56,     //   (080) GTF Task File Buffer for Port 0
  GTF2, 56,     //   (087) GTF Task File Buffer for Port 2
  IDEM, 8,      //   (094) IDE Mode (Compatible\Enhanced)
  GTF1, 56,     //   (095) GTF Task File Buffer for Port 1
  BID,  16,     //   (102) Platform board id
  PLID, 8,      //   (104) Platform id 
  ECTG, 8,      //   (105) Toggle EC
  Offset(112),
  OSCC, 8,      //   (112) PCIE OSC Control
  NEXP, 8,      //   (113) Native PCIE Setup Value
  Offset(114),
  SBV1, 8,      //   (114) USB Sideband Deferring GPE Vector (HOST_ALERT#1)
  SBV2, 8,      //   (115) USB Sideband Deferring GPE Vector (HOST_ALERT#2)
  Offset(122),  // Global Variables
  DSEN, 8,      //   (122) _DOS Display Support Flag.
  ECON, 8,      //   (123) Embedded Controller Availability Flag.
  GPIC, 8,      //   (124) Global IOAPIC/8259 Interrupt Mode Flag.
  CTYP, 8,      //   (125) Global Cooling Type Flag.
  L01C, 8,      //   (126) Global L01 Counter.
  VFN0, 8,      //   (127) Virtual Fan0 Status.
  VFN1, 8,      //   (128) Virtual Fan1 Status.
  VFN2, 8,      //   (129) Virtual Fan2 Status.
  VFN3, 8,      //   (130) Virtual Fan3 Status.
  VFN4, 8,      //   (131) Virtual Fan4 Status. 
  VFN5, 8,      //   (132) Virtual Fan5 Status.
  VFN6, 8,      //   (133) Virtual Fan6 Status.
  VFN7, 8,      //   (134) Virtual Fan7 Status.
  VFN8, 8,      //   (135) Virtual Fan8 Status.
  VFN9, 8,      //   (136) Virtual Fan9 Status.

  Offset(143),
  ATMC, 8,      //   (143) Active Trip Point for MCH
  PTMC, 8,      //   (144) Passive Trip Point for MCH
  ATRA, 8,      //   (145) Active Trip Point for TMEM
  PTRA, 8,      //   (146) Passive Trip Point for TMEM
  PNHM, 32,     //   (147) CPUID Feature Information [EAX]
  TBAB, 32,     //   (151) Thermal Base Low Address for BIOS
  TBAH, 32,     //   (155) Thermal Base High Address for BIOS
  RTIP, 8,      //   (159) Run Time Interface for Intelligent Power Savings
  TSOD, 8,      //   (160) TS-on-DIMM is chosen in SETUP and present on the DIMM
  ATPC, 8,      //   (161) Active Trip Point for PCH
  PTPC, 8,      //   (162) Passive Trip Point for PCH
  PFLV, 8,      //   (163) Platform Flavor
  BREV, 8,      //   (164) Board Rev
  Offset(165),
  PDTS, 8,      //   (165) Package Temperature
  PKGA, 8,      //   (166) Package Temperature MSR available
  PAMT, 8,      //   (167) Peci Access Method
  AC0F, 8,      //   (168) _AC0 Fan Speed
  AC1F, 8,      //   (169) _AC1 Fan Speed 
  DTS3, 8,      //   (170) Digital Thermal Sensor 3 Reading
  DTS4, 8,      //   (171) Digital Thermal Sensor 4 Reading
  Offset(176),  //   (172):(175) are reserved for future use
  LTR1, 8,      //   (176) Latency Tolerance Reporting Enable
  LTR2, 8,      //   (177) Latency Tolerance Reporting Enable
  LTR3, 8,      //   (178) Latency Tolerance Reporting Enable
  LTR4, 8,      //   (179) Latency Tolerance Reporting Enable
  LTR5, 8,      //   (180) Latency Tolerance Reporting Enable
  LTR6, 8,      //   (181) Latency Tolerance Reporting Enable
  LTR7, 8,      //   (182) Latency Tolerance Reporting Enable
  LTR8, 8,      //   (183) Latency Tolerance Reporting Enable
  Offset(184),
  OBF1, 8,      //   (184) Optimized Buffer Flush and Fill
  OBF2, 8,      //   (185) Optimized Buffer Flush and Fill
  OBF3, 8,      //   (186) Optimized Buffer Flush and Fill
  OBF4, 8,      //   (187) Optimized Buffer Flush and Fill
  OBF5, 8,      //   (188) Optimized Buffer Flush and Fill
  OBF6, 8,      //   (189) Optimized Buffer Flush and Fill
  OBF7, 8,      //   (190) Optimized Buffer Flush and Fill
  OBF8, 8,      //   (191) Optimized Buffer Flush and Fill
  Offset (192),
  XHCI, 8,      //   (192) xHCI controller mode
  XTUB, 32,     //   (193) XTU Continous structure Base Address 
  XTUS, 32,     //   (197) XMP Size
  XMPB, 32,     //   (201) XMP Base Address
  DDRF, 8,      //   (205) DDR Reference Frequency

  RTD3, 8,      //   (206) Runtime D3 support.
  PEP0, 8,      //   (207) User selctable Delay for Device D0 transition.
  PEP3, 8,      //   (208) User selctable Delay for Device D3 transition.
  //
  // DPTF Devices and trip points
  //
  DPTF, 8,      //   (209) EnableDptf

  SADE, 8,      //   (210) EnableSaDevice
  SACR, 8,      //   (211) CriticalThermalTripPointSa
  SAHT, 8,      //   (212) HotThermalTripPointSa

  PCHD, 8,      //   (213) EnablePchDevice
  PCHC, 8,      //   (214) CriticalThermalTripPointPch
  PCHH, 8,      //   (215) HotThermalTripPointPch
  //
  // DPTF Policies
  //
  CTDP, 8,      //   (216) EnableCtdpPolicy
  LPMP, 8,      //   (217) EnableLpmPolicy
  LPMV, 8,      //   (218) CurrentLowPowerMode for LPM
  ECEU, 8,      //   (219) EnableCurrentExecutionUnit
  TGFG, 16,     //   (220) TargetGfxFreq
  //
  // DPPM Devices and trip points
  //
  MEMD, 8,      //   (222) EnableMemoryDevice
  MEMC, 8,      //   (223) CriticalThermalTripPointTMEM
  MEMH, 8,      //   (224) HotThermalTripPointTMEM

  FND1, 8,      //   (225) EnableFan1Device
  FND2, 8,      //   (226) EnableFan2Device

  AMBD, 8,      //   (227) EnableAmbientDevice
  AMAT, 8,      //   (228) ActiveThermalTripPointAmbient
  AMPT, 8,      //   (229) PassiveThermalTripPointAmbient
  AMCT, 8,      //   (230) CriticalThermalTripPointAmbient
  AMHT, 8,      //   (231) HotThermalTripPointAmbient

  SKDE, 8,      //   (232) EnableSkinDevice
  SKAT, 8,      //   (233) ActiveThermalTripPointSkin
  SKPT, 8,      //   (234) PassiveThermalTripPointSkin
  SKCT, 8,      //   (235) CriticalThermalTripPointSkin
  SKHT, 8,      //   (236) HotThermalTripPointSkin

  EFDE, 8,      //   (237) EnableExhaustFanDevice
  EFAT, 8,      //   (238) ActiveThermalTripPointExhaustFan
  EFPT, 8,      //   (239) PassiveThermalTripPointExhaustFan
  EFCT, 8,      //   (240) CriticalThermalTripPointExhaustFan
  EFHT, 8,      //   (241) HotThermalTripPointExhaustFan

  VRDE, 8,      //   (242) EnableVRDevice
  VRAT, 8,      //   (243) ActiveThermalTripPointVR
  VRPT, 8,      //   (244) PassiveThermalTripPointVR
  VRCT, 8,      //   (245) CriticalThermalTripPointVR
  VRHT, 8,      //   (246) HotThermalTripPointVR
  //
  // DPPM Policies
  //
  DPAP, 8,      //   (247) EnableActivePolicy
  DPPP, 8,      //   (248) EnablePassivePolicy
  DPCP, 8,      //   (249) EnableCriticalPolicy
  DCMP, 8,      //   (250) EnableCoolingModePolicy
  TRTV, 8,      //   (251) TrtRevision
  //
  // CLPO (Current Logical Processor Off lining Setting)
  //
  LPOE, 8,      //   (252) LPOEnable
  LPOP, 8,      //   (253) LPOStartPState
  LPOS, 8,      //   (254) LPOStepSize
  LPOW, 8,      //   (255) LPOPowerControlSetting
  LPER, 8,      //   (256) LPOPerformanceControlSetting
  //
  // Miscellaneous DPTF
  //
  PPSZ, 32,     //   (257) PPCC Step Size
  DISE, 8,      //   (261) EnableDisplayParticipant
  //
  // PFAT
  //
  PFMA,  64,    //   (262) PFAT Memory Address for Tool Interface
  PFMS,  8,     //   (270) PFAT Memory Size for Tool Interface
  PFIA,  16,    //   (271) PFAT IoTrap Address for Tool Interface
  //
  // ISCT
  //
  ICNF, 8,      //   (273) Isct Configuration
  //
  // ADSP
  //
  DSP0, 32,     //   (274) Audio DSP BAR0
  DSP1, 32,     //   (278) Audio DSP BAR1
  //
  // NFC
  //
  NFCE, 8,      //   (282) NFC module selection 	
  //
  // ADSP Codec Selection
  //
  CODS, 8,      //   (283) Audio Codec selection
  //
  // Sensor Hub Enable
  //
  SNHE, 8,      //   (284) Sensor Hub Enable

  S0ID, 8,      //   (285) Low Power S0 Idle Enable

  //
  // BIOS only version of Config TDP
  //
  CTDB, 8,      //   (286) enable/disable BIOS only version of Config TDP

  Offset(519), 
  PWRE, 8,      //   (519) EnablePowerDevice
  PWRP, 8,      //   (520) EnablePowerPolicy
  XHPR, 8,      //   (521) RTD3 USB Power Resource config
  //
  // Intel Serial(R) IO Sensor Device Selection
  //
  SDS0, 8,      //   (522) I2C0 Sensor Device Selection
  SDS1, 16,     //   (523) I2C1 Sensor Device Selection
  SDS2, 8,      //   (525) SPI0 Sensor Device Selection
  SDS3, 8,      //   (526) SPI1 Sensor Device Selection
  SDS4, 8,      //   (527) UART0 Sensor Device Selection
  SDS5, 8,      //   (528) UART1 Sensor Device Selection
  Offset(530),  //   529 no longer used
  RIC0, 8,      //   (530) RTD3 support for I2C0 SH
  PEPY, 8,      //   (531) RTD3 PEP support list(BIT0 - GFx , BIT1 - Sata, BIT2 - UART, BIT3 - SDHC, Bit4 - I2C0, BIT5 - I2C1, Bit6 - XHCI, Bit7 - Audio)
  DVS0, 8,      //   (532) Port0 DevSlp Enable
  DVS1, 8,      //   (533) Port1 DevSlp Enable
  DVS2, 8,      //   (534) Port2 DevSlp Enable
  DVS3, 8,      //   (535) Port3 DevSlp Enable
  GBSX, 8,      //   (536) Virtual GPIO button Notify Sleep State Change
  IUBE, 8,      //   (537) IUER Button Enable
  IUCE, 8,      //   (538) IUER Convertible Enable
  IUDE, 8,      //   (539) IUER Dock Enable
  ECNO, 8,      //   (540) EC Notification of Low Power S0 Idle State
  AUDD, 16,     //   (541) RTD3 Audio Codec device delay
  DSPD, 16,     //   (543) RTD3 ADSP device delay
  IC0D, 16,     //   (545) RTD3 SensorHub delay time after applying power to device
  IC1D, 16,     //   (547) RTD3 TouchPanel delay time after applying power to device
  IC1S, 16,     //   (549) RTD3 TouchPad delay time after applying power to device
  VRRD, 16,     //   (551) VR Ramp up delay
  PSCP, 8,      //   (553) P-state Capping
  RWAG, 8,      //   (554) Rtd3 W/A Gpio, allow W/A for port 1 and 6 to use GPIO from SDHC device
  I20D, 16,     //   (555) Delay in _PS0 after powering up I2C0 Controller
  I21D, 16,     //   (557) Delay in _PS0 after powering up I2C1 Controller
  
  Offset(561),
  RCG0, 8 ,     //   (561) RTD3 Config Setting(BIT0:ZPODD,BIT1:USB Camera Port4, BIT2/3:SATA Port3)
  ECDB, 8,      //   (562) EC Debug Light (CAPS LOCK) for when in Low Power S0 Idle State
  P2ME, 8,      //   (563) Ps2 Mouse Enable
  
  SSH0, 16,     // (564) SSCN-LOW  for I2C0
  SSL0, 16,     // (566) SSCN-HIGH for I2C0
  SSD0, 16,     // (568) SSCN-HOLD for I2C0
  FMH0, 16,     // (570) FMCN-LOW  for I2C0
  FML0, 16,     // (572) FMCN-HIGH for I2C0
  FMD0, 16,     // (574) FMCN-HOLD for I2C0
  FPH0, 16,     // (576) FPCN-LOW  for I2C0
  FPL0, 16,     // (578) FPCN-HIGH for I2C0
  FPD0, 16,     // (580) FPCN-HOLD for I2C0
  SSH1, 16,     // (582) SSCN-LOW  for I2C1
  SSL1, 16,     // (584) SSCN-HIGH for I2C1
  SSD1, 16,     // (586) SSCN-HOLD for I2C1
  FMH1, 16,     // (588) FMCN-LOW  for I2C1
  FML1, 16,     // (590) FMCN-HIGH for I2C1
  FMD1, 16,     // (592) FMCN-HOLD for I2C1
  FPH1, 16,     // (594) FPCN-LOW  for I2C1
  FPL1, 16,     // (596) FPCN-HIGH for I2C1
  FPD1, 16,     // (598) FPCN-HOLD for I2C1
  M0C0, 16,     // (600) M0D3 for I2C0
  M1C0, 16,     // (602) M1D3 for I2C0
  M2C0, 16,     // (604) M0D0 for I2C0
  M0C1, 16,     // (606) M0D3 for I2C1
  M1C1, 16,     // (608) M1D3 for I2C1
  M2C1, 16,     // (610) M0D0 for I2C1
  M0C2, 16,     // (612) M0D3 for SPI0
  M1C2, 16,     // (614) M1D3 for SPI0
  M0C3, 16,     // (616) M0D3 for SPI1
  M1C3, 16,     // (618) M1D3 for SPI1
  M0C4, 16,     // (620) M0D3 for UA00
  M1C4, 16,     // (622) M1D3 for UA00
  M0C5, 16,     // (624) M0D3 for UA01
  M1C5, 16,     // (626) M1D3 for UA01
  TBSF, 8,      // (628) ThunderBolt SMI Function Number
  GIRQ, 32,     // (629) GPIO IRQ
  DMTP, 8,      // (633) PIRQS 34,50(GPIO)
  DMTD, 8,      // (634) PIRQX 39,55(GPIO)
  DMSH, 8,      // (635) PIRQM 28,14(GPIO)
  LANP, 8,      // (636) LAN PHY Status 0 = Not Present, 1 = Present
  Offset(638),  // 637 no longer used.
  SHSB, 8,      // (638) Sensor Standby mode
  PLCS, 8,      // (639) set PL1 limit when entering CS
  PLVL, 16,     // (640) PL1 limit value
  GN1E, 8,      // (642) EnableGen1Participant
  G1AT, 8,      // (643) ActiveThermalTripPointGen1
  G1PT, 8,      // (644) PassiveThermalTripPointGen1
  G1CT, 8,      // (645) CriticalThermalTripPointGen1
  G1HT, 8,      // (646) HotThermalTripPointGen1
  GN2E, 8,      // (647) EnableGen2Participant
  G2AT, 8,      // (648) ActiveThermalTripPointGen2
  G2PT, 8,      // (649) PassiveThermalTripPointGen2
  G2CT, 8,      // (650) CriticalThermalTripPointGen2
  G2HT, 8,      // (651) HotThermalTripPointGen2
  WWSD, 8,      // (652) EnableWwanTempSensorDevice
  CVSD, 8,      // (653) EnableCpuVrTempSensorDevice
  SSDD, 8,      // (654) EnableSsdTempSensorDevice
  INLD, 8,      // (655) EnableInletFanTempSensorDevice
  IFAT, 8,      // (656) ActiveThermalTripPointInletFan
  IFPT, 8,      // (657) PassiveThermalTripPointInletFan
  IFCT, 8,      // (658) CriticalThermalTripPointInletFan
  IFHT, 8,      // (659) HotThermalTripPointInletFan
  DOSD, 8,      // (660) DMA OS detection, 1 = check for OS version when enabling DMA, 0 = don't care about OS
  USBH, 8,      // (661) USB Sensor Hub Enable/Disable
  BCV4, 8,      // (662) Broadcom's Bluetooth adapter's revision
  WTV0, 8,      // (663) I2C0/WITT devices version
  WTV1, 8,      // (664) I2C1/WITT devices version
  APFU, 8,      // (665) Atmel panel FW update Enable/Disable
  SOHP, 8,      // (666) SMI on Hot Plug for TBT devices
  NOHP, 8,      // (667) Notify on Hot Plug for TBT devices
  TBSE, 8,      // (668) ThunderBolt Root port selector
  WKFN, 8,      // (669) WAK Finished
  PEPC, 16,     // (670) PEP Constraints
  VRSD, 16,     // (672) VR Staggering delay
  PB1E, 8,      // (674) 10sec Power button support Bit0: 10 sec P-button Enable/Disable
                //                                  Bit1: Internal Flag
                //                                  Bit2: Rotation Lock flag, 0:unlock, 1:lock
                //                                  Bit3: Slate/Laptop Mode Flag, 0: Slate, 1: Laptop
                //                                  Bit4: Undock / Dock Flag, 0: Undock, 1: Dock
                //                                  Bit5, 6: reserved for future use.
                //                                  Bit7: EC 10sec PB Override state for S3/S4 wake up. 
  WAND, 8,      // (675) EnableWWANParticipant
  WWAT, 8,      // (676) ActiveThermalTripPointWWAN
  WWPT, 8,      // (677) PassiveThermalTripPointWWAN
  WWCT, 8,      // (678) CriticalThermalTripPointWWAN
  WWHT, 8,      // (679) HotThermalTripPointWWAN
  Offset(685),
  MPLT, 16,     // (685) Minimum Power Limit for DPTF use via PPCC Object
  GR13, 8,      // (687) GPIO13 Rework for Sawtooth Peak
  SPST, 8,      // (688) SATA port state, Bit0 - Port0, Bit1 - Port1, Bit2 - Port2, Bit3 - Port3
  ECLP, 8,      // (689) EC Low Power Mode: 1 - Enabled, 0 - Disabled
  INSC, 8,      // (690) Intel RMT Configuration
  }

#if defined(ASL_Remove_SaSsdt_Data_To_Dsdt) && (ASL_Remove_SaSsdt_Data_To_Dsdt == 1)
///
/// Below Data structure is copy from SaSsdt.asl
///
  OperationRegion(SANV,SystemMemory,0xFFFF0000,0xAA55)
  Field(SANV,AnyAcc,Lock,Preserve)
  {
  SARV, 32,     /// (000) SA RC Revision
  ASLB, 32,     /// (004) IGD OpRegion base address
  IMON, 8,      /// (008) IMON Current Value
  IGDS, 8,      /// (009) IGD State (Primary Display = 1)
  CADL, 8,      /// (010) Current Attached Device List
  PADL, 8,      /// (011) Previous Attached Device List
  CSTE, 16,     /// (012) Current Display State
  NSTE, 16,     /// (014) Next Display State
  DID9, 32,     /// (016) Device Id 9
  DIDA, 32,     /// (020) Device Id 10
  DIDB, 32,     /// (024) Device Id 11
  IBTT, 8,      /// (028) IGD Boot Display Device
  IPAT, 8,      /// (029) IGD Panel Type CMOs option
  IPSC, 8,      /// (030) IGD Panel Scaling
  IBLC, 8,      /// (031) IGD BLC Configuration
  IBIA, 8,      /// (032) IGD BIA Configuration
  ISSC, 8,      /// (033) IGD SSC Configuration
  IPCF, 8,      /// (034) IGD Power Conservation Feature Flag
  IDMS, 8,      /// (035) IGD DVMT Memory Size
  IF1E, 8,      /// (036) IGD Function 1 Enable
  HVCO, 8,      /// (037) HPLL VCO
  NXD1, 32,     /// (038) Next state DID1 for _DGS
  NXD2, 32,     /// (042) Next state DID2 for _DGS
  NXD3, 32,     /// (046) Next state DID3 for _DGS
  NXD4, 32,     /// (050) Next state DID4 for _DGS
  NXD5, 32,     /// (054) Next state DID5 for _DGS
  NXD6, 32,     /// (058) Next state DID6 for _DGS
  NXD7, 32,     /// (062) Next state DID7 for _DGS
  NXD8, 32,     /// (066) Next state DID8 for _DGS
  GSMI, 8,      /// (070) GMCH SMI/SCI mode (0=SCI)
  PAVP, 8,      /// (071) IGD PAVP data
  LIDS, 8,      /// (072) Lid State (Lid Open = 1)
  KSV0, 32,     /// (073) First four bytes of AKSV (mannufacturing mode)
  KSV1, 8,      /// (077) Fifth byte of AKSV (mannufacturing mode)
  BBAR, 32,     /// (078) IGFX Audio (D3F0) MMIO BAR Address
  BLCS, 8,      /// (082) Backlight Control Support
  BRTL, 8,      /// (083) Brightness Level Percentage
  ALSE, 8,      /// (084) ALS Enable
  ALAF, 8,      /// (085) Ambient Light Adjusment Factor
  LLOW, 8,      /// (086) LUX Low Value
  LHIH, 8,      /// (087) LUX High Value
  ALFP, 8,      /// (088) Active LFP
  AUDA, 32,     /// (089) Audio MMIO WA 1
  AUDB, 32,     /// (093) Audio MMIO WA 2
  AUDC, 32,     /// (097) Audio MMIO WA 3 
  DIDC, 32,	/// (101) Device Id 12
  DIDD, 32,	/// (105) Device Id 13
  DIDE, 32,	/// (109) Device Id 14
  DIDF, 32,	/// (113) Device Id 15
//AMI_OVERRIDE --- Change name from CADR to CCSA to fix that the system has BsOD issue. It is due to the name(CADR) is conflict with AMI Aptio definition name. >>
  CCSA, 32,     /// (117) Codec Save Address 
  CCNT, 32,     /// (121) Codec Save Count 
//CADR, 32,     /// (117) Codec Save Address 
//CCNT, 8,      /// (121) Codec Save Count 
//AMI_OVERRIDE --- <<
  ///
  /// Switchable Graphics Info
  ///
  Offset(200),
  SGMD, 8,      /// (200) SG Mode (0=Disabled, 1=SG Muxed, 2=SG Muxless, 3=DGPU Only)
  SGFL, 8,      /// (201) SG Feature List
  PWOK, 8,      /// (202) dGPU PWROK GPIO assigned
  HLRS, 8,      /// (203) dGPU HLD RST GPIO assigned
  PWEN, 8,      /// (204) dGPU PWR Enable GPIO assigned
  PRST, 8,      /// (205) dGPU Present Detect GPIO assigned
  CPSP, 32,     /// (206) PEG Endpoint Capability Structure Presence (Bit 0: Virtual Channel Capability)
  EECP, 8,      /// (210) PEG Endpoint PCIe Capability Structure Offset
  EVCP, 16,     /// (211) PEG Endpoint Virtual Channel Capability Structure Offset
  XBAS, 32,     /// (213) Any Device's PCIe Config Space Base Address
  GBAS, 16,     /// (217) GPIO Base Address
  SGGP, 8,      /// (219) SG GPIO Support
  NVGA, 32,     /// (220) NVIG opregion address
  NVHA, 32,     /// (224) NVHM opregion address
  AMDA, 32,     /// (228) AMDA opregion address
  NDID, 8,      /// (232) Number of Valid Device IDs
  DID1, 32,     /// (233) Device ID 1
  DID2, 32,     /// (237) Device ID 2
  DID3, 32,     /// (241) Device ID 3
  DID4, 32,     /// (245) Device ID 4
  DID5, 32,     /// (249) Device ID 5
  DID6, 32,     /// (253) Device ID 6
  DID7, 32,     /// (257) Device ID 7
  DID8, 32,     /// (261) Device ID 8
  OBS1, 32,     /// (265) Occupied Buses - from 0 to 31
  OBS2, 32,     /// (269) Occupied Buses - from 32 to 63
  OBS3, 32,     /// (273) Occupied Buses - from 64 to 95
  OBS4, 32,     /// (277) Occupied Buses - from 96 to 127
  OBS5, 32,     /// (281) Occupied Buses - from 128 to 159
  OBS6, 32,     /// (285) Occupied Buses - from 160 to 191
  OBS7, 32,     /// (289) Occupied Buses - from 192 to 223
  OBS8, 32,     /// (293) Occupied Buses - from 224 to 255
  LTRA, 8,      /// (297) Latency Tolerance Reporting Enable
  OBFA, 8,      /// (298) Optimized Buffer Flush and Fill
  LTRB, 8,      /// (299) Latency Tolerance Reporting Enable
  OBFB, 8,      /// (300) Optimized Buffer Flush and Fill
  LTRC, 8,      /// (301) Latency Tolerance Reporting Enable
  OBFC, 8,      /// (302) Optimized Buffer Flush and Fill
  SMSL, 16,     /// (303) SA Peg Latency Tolerance Reporting Max Snoop Latency
  SNSL, 16,     /// (305) SA Peg Latency Tolerance Reporting Max No Snoop Latency
  P0UB, 8,      /// (307) Peg0 Unused Bundle Control
  P1UB, 8,      /// (308) Peg1 Unused Bundle Control
  P2UB, 8,      /// (309) Peg2 Unused Bundle Control
  EDPV, 8,      /// (310) Check for eDP display device
  NXDX, 32,     /// (311) Next state DID for eDP
  DIDX, 32,     /// (315) Device ID for eDP device
  PCSL, 8,      /// (319) The lowest C-state for the package
  SC7A, 8,      /// (316) Run-time C7 Allowed feature (0=Disabled, 1=Enabled)
// AMI_OVERRIDE...
  DSEL, 8,      /// (319) dGPU Display Select GPIO assigned
  ESEL, 8,      /// (320) dGPU EDID Select GPIO assigned
  PSEL, 8,      /// (321) dGPU PWM Select GPIO assigned
  MXD1, 32,     /// (322) DID1 Mux Setting
  MXD2, 32,     /// (326) DID2 Mux Setting
  MXD3, 32,     /// (330) DID3 Mux Setting
  MXD4, 32,     /// (334) DID4 Mux Setting
  MXD5, 32,     /// (338) DID5 Mux Setting
  MXD6, 32,     /// (342) DID6 Mux Setting
  MXD7, 32,     /// (346) DID7 Mux Setting
  MXD8, 32,     /// (350) DID8 Mux Setting
  PXFD, 8,      /// (354) ATI 5.0 Fixed/Dynamic ATI 5.0 Fixed/Dynamic
  EBAS, 32,     /// (355) Endpoint PCIe Base Address
  HYSS, 32,     /// (359) dGPU SSID for MSHyBrid restore
// AMI_OVERRIDE...end.
  }
#endif
