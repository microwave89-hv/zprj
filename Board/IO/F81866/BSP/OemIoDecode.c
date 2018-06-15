//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//
//*************************************************************************
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866 Board/OemIoDecode.c 1     7/20/11 4:22a Kasalinyi $
//
// $Revision: 1 $
//
// $Date: 7/20/11 4:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866 Board/OemIoDecode.c $
// 
// 1     7/20/11 4:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Initial Porting
// [Files]  		BSP.cif
// OemIoDecode.c
// PeiIoTable.h
// DxeIoTable.h
// F81866HwmOemHooks.c
// F81866SmartFan.c
// 
// 3     3/21/11 9:44p Mikes
// Seperate the core and oem job
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <OemIoDecode.c>
//
// Description: This file provides a interface to decode any IO resource used
//      by IO module. In the interface, has provided some sample codes, but 
//      only for reference. The sample code is based on some old chipsets. You
//      must check your platform and re-program the function.
//      You also can call chipset IO decode function with token IODECODETYPE.
//
// Notes: 
//    !!!!!!!!!!!!Attention!!!!!!!!!!!Attention!!!!!!!!!!!Attention!!!!!!!!!!!
//    This sample is not for any chipset, please, re-program the function base
//    on your porject.
//    !!!!!!!!!!!!Attention!!!!!!!!!!!Attention!!!!!!!!!!!Attention!!!!!!!!!!!
//
//<AMI_FHDR_END>
//*************************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <Efi.h>
#include <Token.h>
#include <Protocol\PciIo.h>
#include <Protocol\AmiSio.h>

//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------
#define ICH_LPC_IO_DECODE_OFFSET   	0x80
#define ICH_LPC_IO_ENABLE_OFFSET   	0x82
#define ICH_LPC_REG_GEN1_DEC_OFFSET 0x84
#define SIO_SB_BUS_NUMBER    	   	0x00
#define SIO_SB_DEV_NUMBER   	   	0x1F
#define SIO_SB_FUNC_NUMBER  	   	0x00
#define LPC_PCI_ADDR  (UINT32)(BIT31 | (SIO_SB_BUS_NUMBER << 16) | (SIO_SB_DEV_NUMBER << 11) | (SIO_SB_FUNC_NUMBER << 8))

EFI_STATUS CSP_SetLpcGenericDecoding (
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN UINT16                   Base,
    IN UINT16                   Length,
    IN BOOLEAN                  Enable );

VOID static RWPciReg16 (
    IN UINT32       dNumOfBusDevFunc,
    IN UINT16       Reg,
    IN UINT16       SetData,
    IN UINT16       MaskData );

VOID static WritePciReg32 (
    IN UINT32       dNumOfBusDevFunc,
    IN UINT16       Reg,
    IN UINT32       Value32 );

UINT32 static ReadPciReg32 (
    IN UINT32       dNumOfBusDevFunc,
    IN UINT16       Reg );
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:  RWPciReg16
//
// Description: 
//  This function read or write PCI 16bit register 
//
// Input:
//  UINT32  dNumOfBusDevFunc - Content the BUS DEV and FUNC number to be used
//  UINT16  Reg       
//  UINT16  SetData
//  UINT16  MaskData
//
// Output:
//  NONE
//
// Notes: 
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
static VOID RWPciReg16 (
    IN UINT32       dNumOfBusDevFunc,
    IN UINT16       Reg,
    IN UINT16       SetData,
    IN UINT16       MaskData )
{
    UINT16	Value16;

    dNumOfBusDevFunc |= (UINT32)(Reg & ~3);

    IoWrite32(0xcf8, dNumOfBusDevFunc);
    Value16 = IoRead16(0xcfc | (UINT8)(Reg & 2));

    IoWrite32(0xcf8, dNumOfBusDevFunc);
    IoWrite16(0xcfc | (UINT8)(Reg & 2), (Value16 & MaskData) | SetData);

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:  WritePciReg32
//
// Description: This function write PCI 32bit register 
//
// Input:
//  UINT32    dNumOfBusDevFunc - Content the BUS DEV and FUNC number to be used.
//  UINT16    Reg       
//  UINT32    Value32
//
// Output:
//  NONE
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static VOID WritePciReg32 (
    IN UINT32       dNumOfBusDevFunc,
    IN UINT16       Reg,
    IN UINT32       Value32 )
{
	//BIT31 | (SIO_SB_BUS_NUM << 16) | (SIO_SB_DEV_NUM << 11) | (SIO_SB_FUNC_NUM << 8) | (Reg & 0xfc);
    	dNumOfBusDevFunc |= (UINT32)(Reg & ~3);
        IoWrite32(0xcf8, dNumOfBusDevFunc);
        IoWrite32(0xcfc, Value32);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:  ReadPciReg32
//
// Description: This function read PCI 32bit register 
//
// Input:
//  UINT32    dNumOfBusDevFunc - Content the BUS DEV and FUNC number to be used.
//  UINT16    Reg       
//
// Output:      
//  NONE
//
// Notes: 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static UINT32 ReadPciReg32 (
    IN UINT32       dNumOfBusDevFunc,
    IN UINT16       Reg )
{
	//BIT31 | (SIO_SB_BUS_NUM << 16) | (SIO_SB_DEV_NUM << 11) | (SIO_SB_FUNC_NUM << 8) | (Reg & 0xfc);
    	dNumOfBusDevFunc |= (UINT32)(Reg & ~3);
        IoWrite32(0xcf8, dNumOfBusDevFunc);
        return IoRead32(0xcfc);
}
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:  CSP_SetLpcDeviceDecoding
//
// Description: 
//  This function goes through the elinked list of identify functions 
//  giving control when the token "IODECODETYPE == 1". 
//
// Input:
//  Base    - I/O base address
//            Base=0 means disable the decode of the device
//  DevUid  - The device Unique ID
//            If type is 0xFF, DevUid contain the IO length
//  Type    - Device type
//            If type is 0xFF, DevUid contain the IO length
//
// Output:  
//  EFI_SUCCESS - Set successfully.
//  EFI_INVALID_PARAMETER - the Input parameter is invalid.
//
// Notes:
//  Chipset porting should provide the Io Ranage decode function.
//  If chipset porting provide this function, set IODECODETYPE = 0.
//  If chipset porting doesn't provide this function, you can eLink your
//  function to IoRangeDecodeList or replace CSP_SetLpcDeviceDecoding elink
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CSP_SetLpcDeviceDecoding(
    IN    EFI_PCI_IO_PROTOCOL *LpcPciIo,
    IN    UINT16         Base,
    IN    UINT8          DevUid,
    IN    SIO_DEV_TYPE   Type)
{
    EFI_STATUS              Status = EFI_UNSUPPORTED;
    UINT16                  IoRangeMask16 = 0xffff;
    UINT16                  IoRangeSet16 = 0;
    UINT16                  IoEnMask16 = 0xffff;
    UINT16                  IoEnSet16 = 0;
    switch (Base) {
        //disable device decode
              case 0:
                  switch(Type) {
                    case dsFDC:IoEnMask16 &= ~BIT03;break;
                    case dsLPT:IoEnMask16 &= ~BIT02;break;
                    case dsUART:
                              if(DevUid == 0)
                                 IoEnMask16 &= ~BIT00;break;//disable coma
                              if(DevUid == 1)
                                 IoEnMask16 &= ~BIT01;break;//disable comb
                    case dsPS2K:
                    case dsPS2CK:IoEnMask16 &= ~BIT10;break;//disable kbc
                    case dsGAME:
                              if(DevUid == 0)
                                 IoEnMask16 &= ~BIT08;break;//disable game1
                              if(DevUid == 1)
                                 IoEnMask16 &= ~BIT09;break;//disable game2
                  }
               break;
        // FDC Address Range
              case 0x3f0:IoEnSet16 |= BIT03;IoRangeMask16 &= ~BIT12;IoRangeSet16 |= (0 << 12);break;
              case 0x370:IoEnSet16 |= BIT03;IoRangeMask16 &= ~BIT12;IoRangeSet16 |= (1 << 12);break;
        // LPT Address Range
              case 0x378:IoEnSet16 |= BIT02;IoRangeMask16 &= ~(BIT09 | BIT08);IoRangeSet16 |= (0 << 8);break;
              case 0x278:IoEnSet16 |= BIT02;IoRangeMask16 &= ~(BIT09 | BIT08);IoRangeSet16 |= (1 << 8);break;
              case 0x3bc:IoEnSet16 |= BIT02;IoRangeMask16 &= ~(BIT09 | BIT08);IoRangeSet16 |= (2 << 8);break;

        // ComA Address Range
              case 0x3f8:if(DevUid == 0) {IoEnSet16 |= BIT00;IoRangeMask16 &= ~(BIT02 | BIT01 | BIT00);IoRangeSet16 |= 0;break;}
                         if(DevUid == 1) {IoEnSet16 |= BIT01;IoRangeMask16 &= ~(BIT06 | BIT05 | BIT04);IoRangeSet16 |= (0 << 4);break;}
              case 0x2f8:if(DevUid == 0) {IoEnSet16 |= BIT00;IoRangeMask16 &= ~(BIT02 | BIT01 | BIT00);IoRangeSet16 |= 1;break;}
                         if(DevUid == 1) {IoEnSet16 |= BIT01;IoRangeMask16 &= ~(BIT06 | BIT05 | BIT04);IoRangeSet16 |= (1 << 4);break;}
              case 0x220:if(DevUid == 0) {IoEnSet16 |= BIT00;IoRangeMask16 &= ~(BIT02 | BIT01 | BIT00);IoRangeSet16 |= 2;break;}
                         if(DevUid == 1) {IoEnSet16 |= BIT01;IoRangeMask16 &= ~(BIT06 | BIT05 | BIT04);IoRangeSet16 |= (2 << 4);break;}
              case 0x228:if(DevUid == 0) {IoEnSet16 |= BIT00;IoRangeMask16 &= ~(BIT02 | BIT01 | BIT00);IoRangeSet16 |= 3;break;}
                         if(DevUid == 1) {IoEnSet16 |= BIT01;IoRangeMask16 &= ~(BIT06 | BIT05 | BIT04);IoRangeSet16 |= (3 << 4);break;}
              case 0x238:if(DevUid == 0) {IoEnSet16 |= BIT00;IoRangeMask16 &= ~(BIT02 | BIT01 | BIT00);IoRangeSet16 |= 4;break;}
                         if(DevUid == 1) {IoEnSet16 |= BIT01;IoRangeMask16 &= ~(BIT06 | BIT05 | BIT04);IoRangeSet16 |= (4 << 4);break;}
              case 0x2e8:if(DevUid == 0) {IoEnSet16 |= BIT00;IoRangeMask16 &= ~(BIT02 | BIT01 | BIT00);IoRangeSet16 |= 5;break;}
                         if(DevUid == 1) {IoEnSet16 |= BIT01;IoRangeMask16 &= ~(BIT06 | BIT05 | BIT04);IoRangeSet16 |= (5 << 4);break;}
              case 0x338:if(DevUid == 0) {IoEnSet16 |= BIT00;IoRangeMask16 &= ~(BIT02 | BIT01 | BIT00);IoRangeSet16 |= 6;break;}
                         if(DevUid == 1) {IoEnSet16 |= BIT01;IoRangeMask16 &= ~(BIT06 | BIT05 | BIT04);IoRangeSet16 |= (6 << 4);break;}
              case 0x3e8:if(DevUid == 0) {IoEnSet16 |= BIT00;IoRangeMask16 &= ~(BIT02 | BIT01 | BIT00);IoRangeSet16 |= 7;break;}
                         if(DevUid == 1) {IoEnSet16 |= BIT01;IoRangeMask16 &= ~(BIT06 | BIT05 | BIT04);IoRangeSet16 |= (7 << 4);break;}


        // KBC Address Enable
              case 0x60:
              case 0x64:IoEnSet16 |= BIT10;break;
              case 0x62: 
              case 0x66: IoEnSet16 |= BIT11;break;
        // Game Port Address Enable
              case 0x200:IoEnSet16 |= BIT08;break;
              case 0x208:IoEnSet16 |= BIT09;break;
        // LPC CFG Address Enable
              case 0x2e: IoEnSet16 |= BIT12;break;
              case 0x4e: IoEnSet16 |= BIT13;break;
              default:if(Type == 0xff) {//!!!Attention!!!If type is 0xFF, DevUid contain the IO length
                       return  CSP_SetLpcGenericDecoding(LpcPciIo, \
                                                         Base , \
                                                         DevUid, \
                                                         TRUE );
                      }else return EFI_UNSUPPORTED;
                       
    }
    RWPciReg16(LPC_PCI_ADDR,ICH_LPC_IO_DECODE_OFFSET, IoRangeSet16, IoRangeMask16);	//0X82
    RWPciReg16(LPC_PCI_ADDR,ICH_LPC_IO_ENABLE_OFFSET, IoEnSet16, IoEnMask16);		//0X84
    // Porting End

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure:   CSP_SetLpcGenericDecoding
//
// Description: 
//  This function set LPC Bridge Generic Decoding
//              
// Input:       
//  *LpcPciIo - Pointer to LPC PCI IO Protocol
//  Base      - I/O base address
//  Length    - I/O Length
//  Enabled   - Enable/Disable the generic decode range register
//
// Output:
//  EFI_SUCCESS - Set successfully.
//  EFI_UNSUPPORTED - This function is not implemented or the
//                    Length more than the maximum supported
//                    size of generic range decoding.
//  EFI_INVALID_PARAMETER - the Input parameter is invalid.
//  EFI_OUT_OF_RESOURCES - There is not available Generic
//                         Decoding Register.
//  EFI_NOT_FOUND - the generic decode range will be disabled
//                  is not found.
//
// Notes: 
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CSP_SetLpcGenericDecoding (
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN UINT16                   Base,
    IN UINT16                   Length,
    IN BOOLEAN                  Enable )
{
    // Porting Required
    UINT32                  IoGenDecode32;
    UINT16                  IoGenDecIndex;
    UINT16                  Buffer16;
    UINT8                   Bsf8 = 0;
    UINT8                   Bsr8 = 0;

    if (Length > 0x100) return EFI_UNSUPPORTED;

    if (Length == 0) return EFI_INVALID_PARAMETER;

    if (Length < 4) Length = 4;


    // Read I/O Generic Decodes Register.
    for (IoGenDecIndex = 0; IoGenDecIndex < 4; IoGenDecIndex++) {
        IoGenDecode32 = ReadPciReg32(LPC_PCI_ADDR,ICH_LPC_REG_GEN1_DEC_OFFSET + IoGenDecIndex * 4);
        if (Enable) {
            if ((IoGenDecode32 & 1) == 0) break;
            else if ((IoGenDecode32 & 0xfffc) == Base) break;
        } else {
            if (((IoGenDecode32 & 0xfffc) == Base) && (IoGenDecode32 & 1)) {
                IoGenDecode32 = 0; // Disable & clear the base/mask fields
                break;
            }
        }
    }

    if (Enable) {
        if (IoGenDecIndex == 4) return EFI_OUT_OF_RESOURCES;

        Buffer16 = Length;
        while ((Buffer16 % 2) == 0) {
            Buffer16 /= 2;
            Bsf8++;
        }

        while (Length) {
            Length >>= 1;
            Bsr8++;
        }

        if (Bsf8 == (Bsr8 - 1)) Bsr8--;
    
        Length = (1 << Bsr8) - 1 ;

        Base &= (~Length);

        IoGenDecode32 = Base | (UINT32)((Length >> 2) << 18) | 1;

    } else {
        if (IoGenDecIndex == 4) return EFI_NOT_FOUND;
    }

    WritePciReg32(LPC_PCI_ADDR,ICH_LPC_REG_GEN1_DEC_OFFSET + IoGenDecIndex * 4, IoGenDecode32);
    // Porting End

    return EFI_SUCCESS;

}


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

