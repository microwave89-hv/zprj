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

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/TxtTcgService.h 1     7/18/12 2:07a Davidhsieh $
//
// $Revision: 1 $
//
// $Date: 7/18/12 2:07a $
//
//**********************************************************************
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/TxtTcgService.h $
// 
// 1     7/18/12 2:07a Davidhsieh
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	AMI TXT Dxe module part create
// 
// 1     2/25/11 3:55a Hpbirdchen
// Initial 0.5 RC Check-in
// 
// 1     12/01/10 11:11p Calvinchen
// 
// 2     10/05/25 3:07p Calvinchen
// 
// 4     7/27/09 7:12a Calvinchen
// TXT module uses internal TPM startup procedure instead of TCG
// library.(EIP#20424)
// 
// 3     6/24/09 12:10a Calvinchen
// (EIP#22177)Updated for Aptio Source Enhancement.
//
//
//**********************************************************************
//
// Statements that include other header files.
//
typedef struct  _EFI_TCG_PROTOCOL EFI_TCG_PROTOCOL;
typedef struct  _EFI_TPM_DEVICE_PROTOCOL EFI_TPM_DEVICE_PROTOCOL;
typedef UINT16  TPM_STRUCTURE_TAG;
typedef UINT16  TPM_TAG;
typedef UINT32  TPM_COMMAND_CODE;
typedef UINT32  TPM_RESULT;
typedef UINT16  TPM_STARTUP_TYPE;

// The TPM is starting up from a clean state
#define TPM_ST_CLEAR                ((TPM_STARTUP_TYPE) 0x0001) 
#define ST_CLEAR                    0
// The TPM is starting up from a saved state
#define TPM_ST_STATE                ((TPM_STARTUP_TYPE) 0x0002) 
#define ST_STATE                    1
#define TPM_ORD_Startup             ((TPM_COMMAND_CODE) 0x00000099)
#define TPM_ORD_ContinueSelfTest    ((TPM_COMMAND_CODE) 0x00000053)
#define TPM_ORD_NV_READVALUE        ((TPM_COMMAND_CODE) 0x000000CF) // 207
#define TPM_ORD_NV_WRITEVALUE       ((TPM_COMMAND_CODE) 0x000000CD) // 205
#define TPM_ORD_NV_DEFINESPACE      ((TPM_COMMAND_CODE) 0x000000CC) // 204
#define TPM_ORD_VERIFY              0x020000001
#define TPM_NV_INDEX_LOCK           0x0FFFFFFFF
#define TPM_TAG_RQU_COMMAND         ((TPM_STRUCTURE_TAG) 0x00C1)
#define TPM_TAG_RQU_AUTH1_COMMAND   ((TPM_STRUCTURE_TAG) 0x00C2)
#define EFI_TCG_PROTOCOL_GUID  \
  {0xf541796d, 0xa62e, 0x4954, 0xa7, 0x75, 0x95, 0x84, 0xf6, 0x1b, 0x9c, 0xdd}
#define EFI_TPM_DEVICE_PROTOCOL_GUID \
  { 0xde161cfe, 0x1e60, 0x42a1, 0x8c, 0xc3, 0xee, 0x7e, 0xf0, 0x73, 0x52, 0x12 }
#define TPM_H2NS(x) \
  (((UINT16)(x) << 8) | ((UINT16)(x) >> 8))
#define TPM_H2NL(x) \
  (UINT32)((((UINT32)(x)) >> 24) |  \
           (((x) >> 8) & 0xff00) |  \
           ((x) << 24) |  \
           (((x) & 0xff00) << 8))
//----------------------------------------------------------------------------
//  NVram definition
//----------------------------------------------------------------------------
#pragma pack (push)
#pragma pack (1)

typedef struct _TCPA_DIGEST {
    UINT8           digest[20];
} TCPA_DIGEST;

typedef struct _TPM_PCR_SELECTION {
    UINT16          sizeOfSelect;
    UINT8           pcrSelect[3];
} TPM_PCR_SELECTION;

typedef struct _TPM_PCR_INFO_SHORT {
//- TPM_PCR_SELECTION   pcrSelection;
    UINT16          sizeOfSelect;
    UINT8           pcrSelect[3];
    UINT8           localityAtRelease;
    TCPA_DIGEST     digestAtRelease;
} TPM_PCR_INFO_SHORT;

typedef struct _TPM_NV_ATTRIBUTES {
    UINT16          tag;
    UINT32          attributes;
} TPM_NV_ATTRIBUTES;

typedef struct _TPM_NV_DATA_PUBLIC1 {
    UINT16          Tag_;
    UINT32          NvIndex;
    TPM_PCR_INFO_SHORT  PcrInfoRead;
} TPM_NV_DATA_PUBLIC1;

typedef struct _TPM_NV_DATA_PUBLIC2 {
    TPM_PCR_INFO_SHORT  PcrInfoWrite;
    TPM_NV_ATTRIBUTES   PerMission;
    UINT8           bReadSTClear;
    UINT8           bWriteSTClear;
    UINT8           bWriteDefine;
    UINT32          DataSize;
} TPM_NV_DATA_PUBLIC2;

typedef struct _TPM_DEF_NV_DATA {
    TPM_NV_DATA_PUBLIC1 TpmDefineSpaceIn_pubinfo1;
    TPM_NV_DATA_PUBLIC2 TpmDefineSpaceIn_pubinfo2;
    TCPA_DIGEST     TpmDefineSpaceIn_encAuth;
} TPM_DEF_NV_DATA;

//----------------------------------------------------------------------------
//  TCG definition
//----------------------------------------------------------------------------
typedef struct _TPM_1_2_CMD_HEADER {
  TPM_TAG                           Tag;
  UINT32                            ParamSize;
  TPM_COMMAND_CODE                  Ordinal;
} TPM_1_2_CMD_HEADER;

typedef struct _TPM_1_2_RET_HEADER {
  TPM_TAG                           Tag;
  UINT32                            ParamSize;
  TPM_RESULT                        RetCode;
} TPM_1_2_RET_HEADER;

typedef struct _TPM_1_2_CMD_STARTUP {
  TPM_1_2_CMD_HEADER                Header;
  TPM_STARTUP_TYPE                  StartupType;
} TPM_1_2_CMD_STARTUP;

typedef struct _TPM_1_2_REGISTERS {
  UINT8                             Access;             // 0
  UINT8                             Reserved1[7];       // 1
  UINT32                            IntEnable;          // 8
  UINT8                             IntVector;          // 0ch
  UINT8                             Reserved2[3];       // 0dh
  UINT32                            IntSts;             // 10h
  UINT32                            IntfCapability;     // 14h
  UINT8                             Sts;                // 18h
  UINT16                            BurstCount;         // 19h
  UINT8                             Reserved3[9];
  UINT32                            DataFifo;           // 24h
  UINT8                             Reserved4[0xed8];   // 28h
  UINT16                            Vid;                // 0f00h
  UINT16                            Did;                // 0f02h
  UINT8                             Rid;                // 0f04h
  UINT8                             TcgDefined[0x7b];   // 0f05h
  UINT32                            LegacyAddress1;     // 0f80h
  UINT32                            LegacyAddress1Ex;   // 0f84h
  UINT32                            LegacyAddress2;     // 0f88h
  UINT32                            LegacyAddress2Ex;   // 0f8ch
  UINT8                             VendorDefined[0x70];// 0f90h
} TPM_1_2_REGISTERS;

#pragma pack (pop)

typedef EFI_STATUS (EFIAPI *EFI_TCG_STATUS_CHECK) (
//-  IN      EFI_TCG_PROTOCOL          *This,
//-  OUT     TCG_EFI_BOOT_SERVICE_CAPABILITY
//-                                    *ProtocolCapability,
//-  OUT     UINT32                    *TCGFeatureFlags,
//-  OUT     EFI_PHYSICAL_ADDRESS      *EventLogLocation,
//-  OUT     EFI_PHYSICAL_ADDRESS      *EventLogLastEntry
);

typedef EFI_STATUS (EFIAPI *EFI_TCG_HASH_ALL) (
//-  IN      EFI_TCG_PROTOCOL          *This,
//-  IN      UINT8                     *HashData,
//-  IN      UINT64                    HashDataLen,
//-  IN      TCG_ALGORITHM_ID          AlgorithmId,
//-  IN OUT  UINT64                    *HashedDataLen,
//-  IN OUT  UINT8                     **HashedDataResult
);

typedef EFI_STATUS (EFIAPI *EFI_TCG_LOG_EVENT) (
//-  IN      EFI_TCG_PROTOCOL          *This,
//-  IN      TCG_PCR_EVENT             *TCGLogData,
//-  IN OUT  UINT32                    *EventNumber,
//-  IN      UINT32                    Flags
);

typedef EFI_STATUS (EFIAPI *EFI_TCG_PASS_THROUGH_TO_TPM) (
  IN      EFI_TCG_PROTOCOL          *This,
  IN      UINT32                    TpmInputParamterBlockSize,
  IN      UINT8                     *TpmInputParamterBlock,
  IN      UINT32                    TpmOutputParameterBlockSize,
  IN      UINT8                     *TpmOutputParameterBlock
  );

typedef EFI_STATUS (EFIAPI *EFI_TCG_HASH_LOG_EXTEND_EVENT) (
//-  IN      EFI_TCG_PROTOCOL          *This,
//-  IN      UINT8                     *HashData,
//-  IN      UINT64                    HashDataLen,
//-  IN      TCG_ALGORITHM_ID          AlgorithmId,
//-  IN OUT  TCG_PCR_EVENT             *TCGLogData,
//-  IN OUT  UINT32                    *EventNumber,
//-     OUT  EFI_PHYSICAL_ADDRESS      *EventLogLastEntry
);

typedef struct _EFI_TCG_PROTOCOL {
  EFI_TCG_STATUS_CHECK              StatusCheck;
  EFI_TCG_HASH_ALL                  HashAll;
  EFI_TCG_LOG_EVENT                 LogEvent;
  EFI_TCG_PASS_THROUGH_TO_TPM       PassThroughToTpm;
  EFI_TCG_HASH_LOG_EXTEND_EVENT     HashLogExtendEvent;
} EFI_TCG_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_TPM_MP_INIT) (
  IN      EFI_TPM_DEVICE_PROTOCOL   *This
  );

typedef EFI_STATUS (EFIAPI *EFI_TPM_MP_CLOSE) (
  IN      EFI_TPM_DEVICE_PROTOCOL   *This
  );

typedef EFI_STATUS (EFIAPI *EFI_TPM_MP_GET_STATUS_INFO) (
  IN      EFI_TPM_DEVICE_PROTOCOL   *This
  );

typedef EFI_STATUS (EFIAPI *EFI_TPM_MP_TRANSMIT) (
//-  IN      EFI_TPM_DEVICE_PROTOCOL   *This,
//-  IN      UINTN                     NoInBuffers,
//-  IN      TPM_TRANSMIT_BUFFER       *InBuffers,
//-  IN      UINTN                     NoOutBuffers,
//-  IN OUT  TPM_TRANSMIT_BUFFER       *OutBuffers
 );

typedef struct _EFI_TPM_DEVICE_PROTOCOL {
  EFI_TPM_MP_INIT                   Init;
  EFI_TPM_MP_CLOSE                  Close;
  EFI_TPM_MP_GET_STATUS_INFO        GetStatusInfo;
  EFI_TPM_MP_TRANSMIT               Transmit;
} EFI_TPM_DEVICE_PROTOCOL;

typedef struct _TPM_TRANSMIT_BUFFER {
  VOID                              *Buffer;
  UINTN                             Size;
} TPM_TRANSMIT_BUFFER;
typedef volatile TPM_1_2_REGISTERS  *TPM_1_2_REGISTERS_PTR;

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
