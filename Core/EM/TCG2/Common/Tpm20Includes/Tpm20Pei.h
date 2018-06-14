#ifndef TPM_2_0_PEI_H
#define TPM_2_0_PEI_H

#include <Tpm20Includes\Tpm20.h>

#pragma pack(push, 1)

typedef struct _TPM2_Startup{
    TPMI_ST_COMMAND_TAG tag;
    UINT32              CommandSize;
    TPM_CC              CommandCode;
    TPM_SU              StartupType;
}TPM2_Startup_Cmd;

typedef struct _TPM2_SelfTest{
    TPMI_ST_COMMAND_TAG tag;
    UINT32              CommandSize;
    TPM_CC              CommandCode;
    TPMI_YES_NO         SelfTestType;
}TPM2_SelfTest;

typedef struct _TPM2_Startup_Resp{
    TPM_ST              tag;
    UINT32              ResponsSize;
    TPM_RC              ResponseCode;
}TPM2_Common_RespHdr;

#pragma pack(pop)

EFI_STATUS Tpm20PeiSendStartup(IN EFI_PEI_SERVICES **PeiServices);
EFI_STATUS Tpm20PeiSelfTest();
#endif