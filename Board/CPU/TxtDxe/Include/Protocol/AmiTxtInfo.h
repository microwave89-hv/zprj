//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/Include/Protocol/AmiTxtInfo.h 2     4/10/15 3:11a Crystallee $
//
// $Revision: 2 $
//
// $Date: 4/10/15 3:11a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/Include/Protocol/AmiTxtInfo.h $
// 
// 2     4/10/15 3:11a Crystallee
// 
// 1     1/17/14 3:47a Crystallee
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Show Txt information in setup->Advanced ->Intel Txt
// Information page.
// 

//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	AmiTxtInfo.h
//
// Description:
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __AMI_TXT_INFO_H__
#define __AMI_TXT_INFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#define AMI_TXT_INFO_PROTOCOL_GUID \
    {0x1c92f0ab, 0x3351, 0x1be5, 0xaf, 0xba, 0xc1, 0x25, 0x61, 0xbb, 0x32, 0xa3}

#define AMI_TXT_INFO_PROTOCOL_VERSION 1


typedef struct {
  BOOLEAN              ChipsetIsTxtCapable; ///< Value is set to 1 if chipset is Intel TXT capable.  
  UINT64               SinitMemorySize;     ///< Size of memory reserved for placement of SINIT module. This memory is used by MLE.
  UINT64               TxtHeapMemorySize;   ///< Size of memory reserved for TXT Heap. This memory is used by MLE.
  EFI_PHYSICAL_ADDRESS TxtDprMemoryBase;    ///< Base address of DPR protected memory reserved for Intel TXT component.
  UINT64               TxtDprMemorySize;    ///< Size of DPR protected memory reserved for TXT component
  EFI_PHYSICAL_ADDRESS BiosAcmBase;         ///< Base address of BIOS ACM in system firmware.  Intel TXT reference code would skip searching the BIOS ACM in PEI firmware volume if the field is not zero.  
  EFI_PHYSICAL_ADDRESS McuUpdateDataAddr;   ///< Base address of CPU micro code patch loaded into BSP. Intel TXT reference code would skip searching the micro code path in PEI firmware volume if the field is not zero.
  EFI_PHYSICAL_ADDRESS SinitAcmBase;        ///< Base address of SINIT module if installed in system firmware. Zero otherwise.  
  UINT64               TgaSize;             ///< Size of Trusted Graphics Aperture if supported by chipset.
  EFI_PHYSICAL_ADDRESS TxtLcpPdBase;        ///< Base address of Platform Default Launch Control Policy data if installed in system firmware. Zero otherwise.
  UINT64               TxtLcpPdSize;        ///< Size of Platform Default Launch Control Policy data if installed in system firmware. Zero otherwise.
  /**
  Flags passed from BIOS to OS or MRC
  - BIT0: FLAGS0 for compatible definition
  - BIT1: TXT_CPU_RESET_REQUIRED for MRC to issue reset if required
  - BIT2: TPM_INIT_FAILED for indicate TPM initiate status. If the bit set, ResetEstablishmentBit is skipped in Dxe driver.
  **/
  UINT64 Flags;
  //
  BOOLEAN               ChipsetIsProduction; ///<TRUE Production Fuse, FALSE Debug Fuse>
  BOOLEAN               BiosAcmIsProduction; ///<TRUE Production Fuse, FALSE Debug Fuse>
  BOOLEAN               CpuIsTxtCapable;
  UINT32                TxtErrCode;
} AMI_TXT_INFO_DATA;

typedef struct _AMI_TXT_INFO_PROTOCOL AMI_TXT_INFO_PROTOCOL;

typedef EFI_STATUS (*GET_TXT_INFO) (
	IN AMI_TXT_INFO_PROTOCOL    *AMI_TXT_INFO_PROTOCOL,
    OUT VOID                    **AmiTxtInfoData
);

struct _AMI_TXT_INFO_PROTOCOL {
    //Protocol Ver 0
    UINT32                  ProtocolVer;
    UINT64                  Flags;    
    GET_TXT_INFO            GetTxtInfo;
};
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
