//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Libraries/Tpm20CRBLib/Tpm20CRBLib.h 2     6/14/14 12:24a Fredericko $
//
// $Revision: 2 $
//
// $Date: 6/14/14 12:24a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Libraries/Tpm20CRBLib/Tpm20CRBLib.h $
// 
// 2     6/14/14 12:24a Fredericko
// 
// 1     4/21/14 2:15p Fredericko
// 
// 1     10/08/13 11:59a Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     9/16/13 1:51p Fredericko
// 
// 1     7/10/13 5:51p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: 
//
// Description: 
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Efi.h>
#include <token.h>


//Defines ACPI Interface for Control Resource Buffer Access
#define TPM20H2NS(x)        ((((x) << 8) | ((x) >> 8)) & 0xffff)
#define TPM20H2NL(x)        (TPM20H2NS ((x) >> 16) | (TPM20H2NS ((x) & 0xffff) << 16))

#define CONTROL_AREA_RSVD                  0x00
#define CONTROL_AREA_ERROR                 0x04
#define CONTROL_AREA_CANCEL                0x08
#define CONTROL_AREA_START                 0x0C
#define CONTROL_AREA_INT                   0x10
#define CONTROL_AREA_CMD_SZ                0x18
#define CONTROL_AREA_CMD_BASE              0x1C
#define CONTROL_AREA_RSP_SZ                0x24
#define CONTROL_AREA_RSP_BASE              0x28

//Timeouts
#define TIMEOUT_A         500           ///< 500 microseconds
#define TIMEOUT_B         500 * 1000    ///< 10ms (max command processing time in PK-TPM ca. 3ms)
#define TIMEOUT_C         1000 * 1000   ///< 1s
#define TIMEOUT_D         500 * 1000    ///< 500 ms
#define POLLING_PERIOD    140           ///< Poll register every 140 microsecondss

#define CRB_DEVICE_CMD     0x40 
#define CRB_DEVICE_STS     0x44

#define TPM20_CRB_IDLE     0x02

#define TPM20_MAX_COMMAND_SIZE     0x0F80
#define StartStatusFieldSet        0x00000001

#define TPM20_CRB_CMD_BASE 0x80
#define TPM20_CRB_RSP_BASE 0x80

#define TPM20_CRBSTATUS_START      0x00000001
#define TPM20_CRB_ALL_CLEAR        0xFFFFFFFF

#define RESPONSE_HEADER_SIZE  0x0a


#pragma pack(1)

typedef struct _STATUS_FIELD_
{
   UINT32   Rsvd;
   UINT32   Error;
   UINT32   Cancel;
   UINT32   Start;
}STATUS_FIELD;

typedef struct _CONTROL_AREA_LAYOUT_
{
    STATUS_FIELD StatusFieled;
    UINT64       IntCntrl;
    UINT32       Cmd_Sz;
    UINT64       Cmd_Addrs;
    UINT32       Rsp_Sz;
    UINT64       Rsp_Addrs;
}CONTROL_AREA_LAYOUT;

typedef struct _GENERIC_RESP_HDR_
{
    UINT16 Tag;
    UINT32 RespSize;
    UINT32 RespCode;
}GENERIC_RESP_HDR;

#pragma pack()


EFI_STATUS
EFIAPI
CrbSubmitCmd(
  IN      UINT8     *InputBuffer,
  IN      UINT32     InputBufferSize,
  OUT     UINT8     *OutputBuffer,
  OUT     UINT32    *OutputBufferSize);

BOOLEAN isTpm20CrbPresent();

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************