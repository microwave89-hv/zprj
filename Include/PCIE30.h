//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Modules/PciBus/PCIE30.h 1     4/05/11 12:26p Yakovlevs $Revision: 6 $
//
// $Date: 4/05/11 12:26p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/PciBus/PCIE30.h $
// 
// 1     4/05/11 12:26p Yakovlevs
// [TAG]  		EIP 53475 
// [Category]  	New Feature
// [Description]  	PCI Express 3.0 support added.
// 
// [Files]  		PciBus.c; PciBus.mak;  PciBus.h;  PciPort.c; PciPort.h;
// 
// 2     2/24/10 11:37a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  PCIE30.h
//
// Description:	PCI-E 3.0/3.x Declarations.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _PCI_EXPRESS30_H
#define _PCI_EXPRESS30_H


#ifdef __cplusplus
extern "C" {
#endif
/****** DO NOT WRITE ABOVE THIS LINE *******/

#pragma pack(push,1)
//////////////////////////////////////////////////////////////////////
//Pci Express Gen 3.x Registers And Definitions
//////////////////////////////////////////////////////////////////////

//Different encoding for determining Link Speed used in V3.0.
//Added in V3.0 
#define PCIE_LINK_SPEED_VECT_25G     0x01
#define PCIE_LINK_SPEED_VECT_50G     0x02
#define PCIE_LINK_SPEED_VECT_80G     0x04

//This Definitions cahnged to reflect LNK SPEED VECTOR BITs
#define PCIE_LINK_SPEED_80G     0x03


//Pci Express GEN2 Link Capabilities 2 Register
//Just a place holder for now....in V2
//Defined  in Spec V3.0
typedef union _PCIE_LNK_CAP2_REG {	
	UINT32		LNK_CAP2;
	struct	{
        UINT32  Reserved1       :   1; //bit 0
        UINT32  SuppLnkSpeeds   :   7; //bit 1..7
        UINT32  CrossLnk        :   1; //bit 8  
        UINT32  Reserved2       :   23;
	};
} PCIE_LNK_CAP2_REG;


// Extended capabilities IDs added in PCIe 3.0 spec                     
#define PCIE_CAP_ID_SEC_PCIE_CAP    0x19

#define PCIE_LNK_CNT3_OFFSET        0x04 //from Secondary PciE Ext Cap Header
#define PCIE_LANE_ERR_STA_OFFSET    0x08
#define PCIE_EQUALIZ_CNT_OFFSET     0x0C //Sized by MAx Link width.

//
//The Secondary PCI Express Extended Capability structure is required for all Ports and RCRBs that
//support a Link speed of 8.0 GT/s or higher. For Multi-Function Upstream Ports, this capability
//must be implemented in Function 0 and must not be implemented in other Functions.
//

//PCI Express GEN 3 Link Control 3 Register 
//Updated to PCIe v2.1
typedef union _PCIE_LNK_CNT3_REG {
	UINT32		LNK_CNT3;
	struct {
		UINT32	PerformEqualiz  :   1;  //bit 0
		UINT32	LnkEqReqIntEn   :   1;  //bit 1
		UINT32	Reserved	    :	29;	//bit 2..31
	};
} PCIE_LNK_CNT3_REG;



typedef union _PCIE_LANE_EQ_CNT_REG {
	UINT16		LANE_EQ_CNT;
	struct {
		UINT16	DnsPortTrPreset :   4;  //bit 0..3
		UINT16	DnsPortRcPrHint :   3;  //bit 4..6
		UINT16	Reserved1	    :	1;	//bit 7
		UINT16	UpsPortTrPreset :   4;  //bit 0..3
		UINT16	UpsPortRcPrHint :   3;  //bit 4..6
		UINT16	Reserved2	    :	1;	//bit 7
	};
} PCIE_LANE_EQ_CNT_REG;

#pragma pack(pop)

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
