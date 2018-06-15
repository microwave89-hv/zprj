//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216 Board/OemIoDecode.c 1     3/31/10 5:56a Fantasylai $
//
// $Revision: 1 $
//
// $Date: 3/31/10 5:56a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216 Board/OemIoDecode.c $
// 
// 1     3/31/10 5:56a Fantasylai
// Initial release to F81216 just as a second IO
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <OemIoDecode.C>
//
// Description: If can't decode IO usually. Change other IoDecode mode in file.
//
// Note: 
//    !!!!!!!!!!!!Attention!!!!!!!!!!!Attention!!!!!!!!!!!Attention!!!!!!!!!!!
//    This sample is not for any chipset, it bases on a chipset. For any indivadual
//      projects, should re-program the IO decode policy.
//    !!!!!!!!!!!!Attention!!!!!!!!!!!Attention!!!!!!!!!!!Attention!!!!!!!!!!!
//
//<AMI_FHDR_END>
//*************************************************************************
#include <Efi.h>
#include <Token.h>
#include <Protocol\PciIo.h>
#include <Protocol\AmiSio.h>

#if(IODECODETYPE)
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:  OEM_F81216_LPCDeviceDecoding
//
// Description: This function goes through the elinked list of identify
//      functions giving control when the token "IODECODETYPE == 1". 
//
// Input:       Base      - I/O base address, Base=0 means disable the decode of the device
//              DevUid    - The device Unique ID
//                          If type is 0xFF, DevUid contain the IO length
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - Set successfully.
//                  EFI_INVALID_PARAMETER - the Input parameter is invalid.
//
// Note: 
//      Input paramete is a multi-paramete. If type is 0xFF, DevUid contain the IO length
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OEM_F81216_LPCDeviceDecoding(
    IN  EFI_PCI_IO_PROTOCOL *LpcPciIo, 
    IN  UINT16 Base,
    IN  UINT8 DevUid
)
{//Chipset porting should provide the Io Ranage decode function.
 //If chipset porting provide this function, set IODECODETYPE = 0.
 //If chipset porting doesn't provide this function, you can use a eLink to replace OEM_F81216_LPCDeviceDecoding()
 //In file of IoDecodeSample.c, there is a example code to decode IO Range. You can eLink your code with CORE_DXEBin object. 
 //-------------------------------------
    EFI_STATUS                Status=EFI_SUCCESS;

/*
    EFI_STATUS                Status;
    ICH_LPC_IO_DECODE_REG    dr;        //IchDecode Register
    BOOLEAN                    a;
//---------------------------------------------------------
    //Read what currently have there...
       Status = LpcPciIo->Pci.Read(LpcPciIo, EfiPciIoWidthUint16, 
                                ICH_LPC_IO_DECODE_OFFSET, 1, &dr.IO_DECODE_REG);
    if (EFI_ERROR(Status)) return Status;
    a = TRUE;
    //Check all possible BAse Addresses 
    switch(Base){
        //LPT Address range 
        case 0x378 :
            dr.LptDecode = 0;
            break;
        case 0x278 :
            dr.LptDecode=1;
            break;
        case 0x3bc :
            dr.LptDecode=2;
            break;
        //FDC Address range
        case 0x3f0 : 
            dr.FdcDecode = 0;
            break;
        case 0x370 :
            dr.FdcDecode = 1;
            break;
        //COM Port Address range 
            case 0x3f8 :
            if (DevUid)
                dr.ComBDecode=0;
            else
                dr.ComADecode=0;
            break;
        case 0x2f8 :
            if (DevUid)
                dr.ComBDecode=1;
            else
                dr.ComADecode=1;
            break;
        case 0x220 :
            if (DevUid)
                dr.ComBDecode=2;
            else
                dr.ComADecode=2;
            break;
        case 0x228 :
            if (DevUid)
                dr.ComBDecode=3;
            else
                dr.ComADecode=3;
            break;
        case 0x238 :
            if (DevUid)
                dr.ComBDecode=4;
            else
                dr.ComADecode=4;
            break;
        
        case 0x2E8 :
            if (DevUid)
                dr.ComBDecode=5;
            else
                dr.ComADecode=5;
            break;
        case 0x338 :
            if (DevUid)
                dr.ComBDecode=6;
            else
                dr.ComADecode=6;
            break;
        case 0x3e8 :
            if (DevUid)
                dr.ComBDecode=7;
            else
                dr.ComADecode=7;
            break;

        default :
            a = FALSE;
    }
    //Use Provided LPC Bridge PCI IO to write data back
    if (a) Status=LpcPciIo->Pci.Write(LpcPciIo, EfiPciIoWidthUint16, 
                            ICH_LPC_IO_DECODE_OFFSET, 1, &dr.IO_DECODE_REG);
*/

    return Status;
}
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************