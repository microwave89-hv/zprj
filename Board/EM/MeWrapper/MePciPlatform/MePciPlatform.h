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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePciPlatform/MePciPlatform.h 1     2/08/12 1:05a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:05a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePciPlatform/MePciPlatform.h $
// 
// 1     2/08/12 1:05a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:41a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:09a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            MePciPlatform.h
//
// Description:     
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

This file contains a 'Sample Driver' and is licensed as such
under the terms of your license agreement with Intel or your
vendor.  This file may be modified by the user, subject to  
the additional terms of the license agreement               

--*/

/*++
Copyright (c)  2008 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
  
Module Name:

 MePciPlatform.h

Abstract:

  
--*/
#ifndef _DXE_ME_PCI_PLATFORM_H_
#define _DXE_ME_PCI_PLATFORM_H_

#include "EdkIIGlueDxe.h"
#include "MeLib.h"

#include EFI_PROTOCOL_PRODUCER    (PciPlatform)
#include EFI_PROTOCOL_DEFINITION  (PciRootBridgeIo)

#define EFI_DRIVER_ENTRY_POINT(x)

#define Flex0         (1 << 0)
#define Flex1         (1 << 1)
#define Flex2         (1 << 2)
#define Flex3         (1 << 3)
#define PCI_Clock0    (1 << 7)
#define PCI_Clock1		(1 << 8)
#define PCI_Clock2    (1 << 9)
#define PCI_Clock3    (1 << 10)
#define PCI_Clock4    (1 << 11)
#define SRC0          (1 << 16)
#define SRC1				  (1 << 17)
#define SRC2				  (1 << 18)
#define SRC3				  (1 << 19)
#define SRC4          (1 << 20)
#define SRC5          (1 << 21)
#define SRC6          (1 << 22)
#define SRC7				  (1 << 23)
#define CSI_SRC8      (1 << 24)
#define CSI_DP        (1 << 25)
#define PEG_A         (1 << 26)
#define PEG_B         (1 << 27)
#define	DMI           (1 << 28)

#define PCI_SKIP              0xFF
#define R_PCH_PCIE_SLSTS      0x5A

typedef union _R_PCH_PCIE_SLSTS_VALUE {
	UINT16							                       REG;
  struct {
    UINT16  ReservedBIT0 : 1;
    UINT16  PFD : 1;
    UINT16  MSC : 1;
    UINT16  PDC : 1;
    UINT16  ReservedBIT4 : 1; 
    UINT16  MS  : 1;
    UINT16  PDS : 1;
    UINT16  ReservedBIT7 : 1;
    UINT16  LASC : 1;
    UINT16  Reserved : 7;
  } Fields;
} R_PCH_PCIE_SLSTS_VALUE;

typedef union _PCI_CFG_ADDR {
	UINT64							                        ADDR;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_PCI_ADDRESS	Addr;
} PCI_CFG_ADDR;

typedef struct {
	PCI_CFG_ADDR	PciExpressBridgeAddress;
	BOOLEAN 	    HotPlugSupport;
  UINT32        ClockEnables;
} PLATFORM_PCI_EXPRESS_BRIDGE;

#endif


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