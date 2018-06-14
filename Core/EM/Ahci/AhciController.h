//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/AHCI/AhciController.h 9     11/13/13 1:52a Divyac $
//
// $Revision: 9 $
//
// $Date: 11/13/13 1:52a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AHCI/AhciController.h $
// 
// 9     11/13/13 1:52a Divyac
// [TAG]  		EIP143018 
// [Category]  	Improvement
// [Description]  	Removed the EIP 128912 changes and checked-in again.
// EIP 128912 changes creates lot more side effect, so we planed to remove
// the changes. 
// [Files]  		AhciController.h
// 
// 8     7/23/13 11:56p Srikantakumarp
// [TAG]  		EIP129989
// [Category]  	Improvement
// [Description]  	Added DIPM support in Aptio 4.x AHCIBUS driver.
// [Files]  		AhciBus.c, AhciBus.h, AhciController.h, AhciSrc.sdl,
// PAhciBus.h
// 
// 7     7/18/13 7:35a Rameshr
// [TAG]  		EIP128912
// [Category]  	Improvement
// [Description]  	10b to 8b decode error is mentioned as Diagnostic error
// for use by Diagnostic software, So removed this error status checking
// [Files]  		AhciController.h
// 
// 6     7/17/13 10:40a Rameshr
// [TAG]  		EIP128912
// [Category]  	Improvement
// [Description]  	10b to 8b decode error is mentioned as Diagnostic error
// for use by Diagnostic software, So removed this error status checking.
// [Files]  		AhciController.h
// 
// 5     2/10/11 10:35a Rameshr
// [TAG]  		EIP53704
// [Category]  	Improvement
// [Description]  	AMI headers update for Alaska Ahci Driver
// [Files]  		AhciSrc.mak
// AhciBus.c
// AhciController.c
// AhciComponentName.c
// AhciBus.h
// AhciController.h
// 
// 4     5/07/10 11:45a Krishnakumarg
// Coding standard update
// 
// 3     7/09/09 4:50p Fasihm
// Fixed the Read/Write failure when ALPE is Enabled.
// 
// 2     5/28/08 9:39a Rameshraju
// Based on the SDL token index/data or MMIO method used to access the
// AHCI configuration space.
// 
// 1     28/02/08 6:03p Anandakrishnanl
// AHCI Bus Driver initial check-in.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    AhciController.h
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************

// Forward reference for pure ANSI compatability
typedef struct _AHCI_COMMAND_FIS AHCI_COMMAND_FIS;
typedef struct _AHCI_ATAPI_COMMAND AHCI_ATAPI_COMMAND;
typedef struct _AHCI_COMMAND_PRDT AHCI_COMMAND_PRDT;

#pragma pack(1)

// Command List Structure
typedef struct {
    UINT32          Ahci_Cmd_CFL:5;
    UINT32          Ahci_Cmd_A:1;
    UINT32          Ahci_Cmd_W:1;
    UINT32          Ahci_Cmd_P:1;
    UINT32          Ahci_Cmd_R:1;
    UINT32          Ahci_Cmd_B:1;
    UINT32          Ahci_Cmd_C:1;
    UINT32          Ahci_Cmd_Rsvd1:1;
    UINT32          Ahci_Cmd_PMP:4;
    UINT32          Ahci_Cmd_PRDTL:16;  
    UINT32          Ahci_Cmd_PRDBC;
    UINT32          Ahci_Cmd_CTBA;
    UINT32          Ahci_Cmd_CTBAU;  
    UINT32          Ahci_Cmd_Rsvd2[4]; 
} AHCI_COMMAND_LIST;

typedef struct {
    UINT8           Ahci_Dsfis[0x1C];               // DMA Setup Fis
    UINT8           Ahci_Dsfis_Rsvd[0x04];             
    UINT8           Ahci_Psfis[0x14];               // PIO Setip Fis
    UINT8           Ahci_Psfis_Rsvd[0x0C];             
    UINT8           Ahci_Rfis[0x14];                // D2H Register Fis
    UINT8           Ahci_Rfis_Rsvd[0x04];            
    UINT64          Ahci_Sdbfis;                     // Set Device Bits Fis
    UINT8           Ahci_Ufis[0x40];                 // Unkonw FIS
    UINT8           Ahci_Ufis_Rsvd[0x60];            
} AHCI_RECEIVED_FIS; 

// Register - Host to Device FIS Layout
typedef struct _AHCI_COMMAND_FIS{
    UINT8           Ahci_CFis_Type;
    UINT8           AHci_CFis_PmPort:4;
        UINT8           Ahci_CFis_Rsvd1:1;
        UINT8           Ahci_CFis_Rsvd2:1;
    UINT8           Ahci_CFis_Rsvd3:1;
    UINT8           Ahci_CFis_C:1;
    UINT8           Ahci_CFis_Cmd;
    UINT8           Ahci_CFis_Features;
    UINT8           Ahci_CFis_SecNum;
    UINT8           Ahci_CFis_ClyLow;
    UINT8           Ahci_CFis_ClyHigh;
    UINT8           Ahci_CFis_DevHead;
    UINT8           Ahci_CFis_SecNumExp;
    UINT8           Ahci_CFis_ClyLowExp;
    UINT8           Ahci_CFis_ClyHighExp;
    UINT8           Ahci_CFis_FeaturesExp;
    UINT8           Ahci_CFis_SecCount;
    UINT8           Ahci_CFis_SecCountExp;
    UINT8           Ahci_CFis_Rsvd4;
    UINT8           Ahci_CFis_Control;
    UINT8           Ahci_CFis_Rsvd5[4];
    UINT8           Ahci_CFis_Rsvd6[44];
} AHCI_COMMAND_FIS;

// Physical Region Descriptor Table
typedef struct _AHCI_COMMAND_PRDT{
    UINT32          Ahci_Prdt_DBA;
    UINT32          Ahci_Prdt_DBAU;
    UINT32          Ahci_Prdt_Rsvd;
    UINT32          Ahci_Prdt_DBC:22;  
    UINT32          Ahci_Prdt_Rsvd1:9;
    UINT32          Ahci_Prdt_I:1;  
} AHCI_COMMAND_PRDT;

// Command table

typedef struct _AHCI_COMMAND_TABLE{
    AHCI_COMMAND_FIS        CFis;
    AHCI_ATAPI_COMMAND      AtapiCmd;
    UINT8                   Rsvd[0x30];
    AHCI_COMMAND_PRDT       PrdtTable;
}   AHCI_COMMAND_TABLE;

typedef struct _AHCI_COMMAND_TABLE_NO_PRDT{
    AHCI_COMMAND_FIS        CFis;
    AHCI_ATAPI_COMMAND      AtapiCmd;
    UINT8                   Rsvd[0x30];
}   AHCI_COMMAND_TABLE_NO_PRDT;

#pragma pack()

#define     ATA_SIGNATURE_32                0x00000101
#define     ATAPI_SIGNATURE_32              0xEB140101
#define     PMPORT_SIGNATURE                0x96690101
#define     PRD_MAX_DATA_COUNT              0x400000



#define     PCI_ABAR                    0x24
#define     RECEIVED_FIS_SIZE           0x100

#define     CONTROL_PORT                0x0F

//Generic Host Control Registers
#define     HBA_CAP                      0x0000
#define         HBA_CAP_NP_MASK          0x1F
#define         HBA_CAP_EMS              BIT06
#define         HBA_CAP_PSC              BIT13
#define         HBA_CAP_SSC              BIT14
#define         HBA_CAP_PMD              BIT15
#define         HBA_CAP_FBSS             BIT16
#define         HBA_CAP_SPM              BIT17
#define         HBA_CAP_SAM              BIT18
#define         HBA_CAP_SNZO             BIT19
#define         HBA_CAP_ISS_MASK         (BIT20 | BIT21 | BIT22 | BIT23)
#define         HBA_CAP_SCLO             BIT24
#define         HBA_CAP_SAL              BIT25
#define         HBA_CAP_SALP             BIT26
#define         HBA_CAP_SSS              BIT27
#define         HBA_CAP_SMPS             bit28
#define         HBA_CAP_SSNTF            BIT29
#define         HBA_CAP_SCQA             BIT30
#define         HBA_CAP_S64A             BIT31

#define     HBA_GHC                      0x0004
#define         HBA_GHC_RESET            0x0001
#define         HBA_GHC_IE               0x0002
#define         HBA_GHC_AE               0x80000000
#define         HBA_GHC_AE_RESET         0x80000001
#define     HBA_IS                       0x0008
#define     HBA_PI                       0x000C
#define     HBA_VS                       0x0010
#define     HBA_CCC_CTL                  0x0014
#define     HBA_CCC_PORTS                0x0018
#define     HBA_EM_LOC                   0x001C
#define     HBA_EM_CTL                   0x0020
#define     HBA_CAP2                     0x0024
#define         HBA_CAP2_APST            0x0004
#define         HBA_CAP2_SDS             0x0008
#define         HBA_CAP2_SADM            0x0010
#define         HBA_CAP2_DESO            0x0020

//Port Registers
#define     HBA_PORTS_START              0x0100
#define     HBA_PORTS_REG_WIDTH          0x0080
#define     HBA_PORTS_CLB                0x0000
#define     HBA_PORTS_CLBU               0x0004
#define     HBA_PORTS_FB                 0x0008
#define     HBA_PORTS_FBU                0x000C
#define     HBA_PORTS_IS                 0x0010
#define         HBA_PORTS_IS_DHRS        BIT00
#define         HBA_PORTS_IS_PSS         BIT01
#define         HBA_PORTS_IS_SSS         BIT02
#define         HBA_PORTS_IS_SDBS        BIT03
#define         HBA_PORTS_IS_UFS         BIT04
#define         HBA_PORTS_IS_DPS         BIT05
#define         HBA_PORTS_IS_PCS         BIT06
#define         HBA_PORTS_IS_DIS         BIT07
#define         HBA_PORTS_IS_PRCS        BIT22
#define         HBA_PORTS_IS_IPMS        BIT23
#define         HBA_PORTS_IS_OFS         BIT24
#define         HBA_PORTS_IS_INFS        BIT26
#define         HBA_PORTS_IS_IFS         BIT27
#define         HBA_PORTS_IS_HBDS        BIT28
#define         HBA_PORTS_IS_HBFS        BIT29
#define         HBA_PORTS_IS_TFES        BIT30
#define         HBA_PORTS_IS_CPDS        BIT31
#define         HBA_PORTS_IS_CLEAR       0xFFC000FF
#define         HBA_PORTS_IS_FIS_CLEAR   0x0000001F
#define         HBA_PORTS_IS_ERR_CHK     BIT04 + BIT06 + BIT23 + BIT24 + BIT27 + \
                                         BIT28 + BIT29 + BIT30 + BIT31

#define     HBA_PORTS_IE                 0x0014
#define     HBA_PORTS_CMD                0x0018
#define         HBA_PORTS_CMD_ST_MASK    0xFFFFFFFE
#define         HBA_PORTS_CMD_ST         BIT00
#define         HBA_PORTS_CMD_SUD        BIT01
#define         HBA_PORTS_CMD_POD        BIT02
#define        HBA_PORTS_CMD_CLO        BIT03
#define         HBA_PORTS_CMD_CR         BIT15
#define         HBA_PORTS_CMD_FRE        BIT04
#define         HBA_PORTS_CMD_FR         BIT14
#define         HBA_PORTS_CMD_MASK       ~(HBA_PORTS_CMD_ST | HBA_PORTS_CMD_FRE | HBA_PORTS_CMD_CLO)
#define         HBA_PORTS_CMD_PMA        BIT17
#define         HBA_PORTS_CMD_HPCP       BIT18
#define         HBA_PORTS_CMD_MPSP       BIT19
#define         HBA_PORTS_CMD_CPD        BIT20
#define         HBA_PORTS_CMD_ESP        BIT21
#define         HBA_PORTS_CMD_ATAPI      BIT24
#define         HBA_PORTS_CMD_DLAE       BIT25
#define         HBA_PORTS_CMD_ALPE       BIT26
#define         HBA_PORTS_CMD_ASP        BIT27
#define         HBA_PORTS_CMD_ICC_MASK   (BIT28 | BIT29 | BIT30 | BIT31)
#define         HBA_PORTS_CMD_ACTIVE     (1 << 28 )
#define     HBA_PORTS_TFD                0x0020
#define         HBA_PORTS_TFD_MASK       (BIT07 | BIT03 | BIT00)
#define         HBA_PORTS_TFD_BSY        BIT07
#define         HBA_PORTS_TFD_DRQ        BIT03
#define         HBA_PORTS_TFD_ERR        BIT00
#define         HBA_PORTS_TFD_ERR_MASK   0x00FF00    // BIT8 - BIT15
#define     HBA_PORTS_SIG                0x0024
#define     HBA_PORTS_SSTS               0x0028
#define         HBA_PORTS_SSTS_DET_MASK  0x000F
#define         HBA_PORTS_SSTS_DET       0x0001
#define         HBA_PORTS_SSTS_DET_PCE   0x0003
#define         HBA_PORTS_SSTS_SPD_MASK  0x00F0
#define     HBA_PORTS_SCTL               0x002C
#define         HBA_PORTS_SCTL_DET_MASK  0x000F
#define         HBA_PORTS_SCTL_MASK      (~HBA_PORTS_SCTL_DET_MASK)
#define         HBA_PORTS_SCTL_DET_INIT  0x0001
#define         HBA_PORTS_SCTL_DET_PHYCOMM   0x0003
#define         HBA_PORTS_SCTL_SPD_MASK   0x00F0
#define         HBA_PORTS_SCTL_SPD_NSNR   0x0  
#define         HBA_PORTS_SCTL_SPD_GEN1   0x1  
#define         HBA_PORTS_SCTL_SPD_GEN2   0x2  
#define         HBA_PORTS_SCTL_SPD_GEN3   0x3  
#define         HBA_PORTS_SCTL_IPM_MASK   0x0F00
#define         HBA_PORTS_SCTL_IPM_DIS    0x00
#define             HBA_PORTS_SCTL_IPM_PSD    0x01
#define         HBA_PORTS_SCTL_IPM_SSD    0x02
#define         HBA_PORTS_SCTL_IPM_PSSD   0x03
#define         HBA_PORTS_SCTL_IPM_PSD_SSD 0x0300
#define     HBA_PORTS_SERR              0x0030
#define         HBA_PORTS_SERR_RDIE      BIT00
#define         HBA_PORTS_SERR_RCE       BIT01
#define         HBA_PORTS_SERR_TDIE      BIT08
#define         HBA_PORTS_SERR_PCDIE     BIT09
#define         HBA_PORTS_SERR_PE        BIT10
#define         HBA_PORTS_SERR_IE        BIT11
#define         HBA_PORTS_SERR_PRC       BIT16
#define         HBA_PORTS_SERR_PIE       BIT17
#define         HBA_PORTS_SERR_CW        BIT18
#define         HBA_PORTS_SERR_BDE       BIT19
#define         HBA_PORTS_SERR_DE        BIT20                // Not used
#define         HBA_PORTS_SERR_CRCE      BIT21
#define         HBA_PORTS_SERR_HE        BIT22
#define         HBA_PORTS_SERR_LSE       BIT23
#define         HBA_PORTS_SERR_TSTE      BIT24
#define         HBA_PORTS_SERR_UFT       BIT25
#define         HBA_PORTS_SERR_EX        BIT26
#define         HBA_PORTS_PxSACT         0x0034
#define         HBA_PORTS_PxCI           0x0038
#define         HBA_PORTS_PxDEVSLP       0x0044
#define         HBA_PORTS_PxDEVSLP_ADSE  BIT00
#define         HBA_PORTS_PxDEVSLP_DSP   BIT01
#define         HBA_PORTS_PxDEVSLP_DETO_MASK (0x000003FC)
#define         HBA_PORTS_PxDEVSLP_DMDAT_MASK (0x00007C00)
#define         HBA_PORTS_PxDEVSLP_DITO_MASK (0x01FF8000)
#define         HBA_PORTS_PxDEVSLP_DM_MASK   (0x1E000000)

#define         HBA_PORTS_ERR_CHK        (HBA_PORTS_SERR_TDIE + HBA_PORTS_SERR_PCDIE +\
                                          HBA_PORTS_SERR_PE + HBA_PORTS_SERR_IE + \
                                          HBA_PORTS_SERR_PIE + \
                                          HBA_PORTS_SERR_BDE + \
                                          HBA_PORTS_SERR_DE + HBA_PORTS_SERR_CRCE + \
                                          HBA_PORTS_SERR_HE +  HBA_PORTS_SERR_LSE + \
                                          HBA_PORTS_SERR_TSTE + HBA_PORTS_SERR_UFT  + \
                                          HBA_PORTS_SERR_EX)

#define   	    HBA_PORTS_ERR_CLEAR      (HBA_PORTS_SERR_RDIE + HBA_PORTS_SERR_RCE +\
                                          HBA_PORTS_SERR_TDIE + HBA_PORTS_SERR_PCDIE +\
                                          HBA_PORTS_SERR_PE + HBA_PORTS_SERR_IE + \
                                          HBA_PORTS_SERR_PRC + HBA_PORTS_SERR_PIE + \
                                          HBA_PORTS_SERR_CW + HBA_PORTS_SERR_BDE + \
                                          HBA_PORTS_SERR_DE + HBA_PORTS_SERR_CRCE + \
                                          HBA_PORTS_SERR_HE +  HBA_PORTS_SERR_LSE + \
                                          HBA_PORTS_SERR_TSTE + HBA_PORTS_SERR_UFT  + \
                                          HBA_PORTS_SERR_EX)
#define     HBA_PORTS_SACT               0x0034
#define     HBA_PORTS_CI                 0x0038
#define     HBA_PORTS_SNTF               0x003C

//FIS Types
#define     D2H_FIS_OFFSET                 0x40
#define     DMA_FIS_OFFSET                 0x00
#define     PIO_FIS_OFFSET                 0x20
#define     SDB_FIS_OFFSET                 0x58
#define     FIS_TYPE_MASK                  0xFF
#define     U_FIS_OFFSET                   0x60

#define     FIS_REGISTER_H2D               0x27           // Host To Device
#define         FIS_REGISTER_H2D_LENGTH    20
#define     FIS_REGISTER_D2H               0x34           // Device To Host
#define         FIS_REGISTER_D2H_LENGTH    20             // Device To Host
#define     FIS_DMA_ACTIVATE               0x39           // Device To Host
#define         FIS_DMA_ACTIVATE_LENGTH    4
#define     FIS_DMA_SETUP                  0x41           // Bi-directional
#define         FIS_DMA_SETUP_LENGTH       28 
#define     FIS_DATA                       0x46           // Bi-directional
#define     FIS_BIST                       0x58           // Bi-directional
#define         FIS_BIST_LENGTH            12
#define     FIS_PIO_SETUP                  0x5F           // Device To Host
#define         FIS_PIO_SETUP_LENGTH       20
#define     FIS_SET_DEVICE                 0xA1           // Device To Host
#define         FIS_SET_DEVICE_LENGTH      8              


#define     READ_PORT_MULTIPLIER            0xE4
#define     WRITE_PORT_MULTIPLIER           0xE8

#define     GSCR_0                          0x00
#define     GSCR_1                          0x01
#define     GSCR_2                          0x02
#define     GSCR_32                         32
#define     GSCR_64                         64
#define     GSCR_96                         96

#define     PSCR_0_SSTATUS                  0x00
#define     PSCR_1_SERROR                   0x01
#define     PSCR_2_SCONTROL                 0x02


#define     HBA_CR_CLEAR_TIMEOUT           500          // AHCI 1.2 spec 10.1.2
#define     HBA_FR_CLEAR_TIMEOUT           500          // AHCI 1.2 spec 10.1.2
#define     HBA_PRESENCE_DETECT_TIMEOUT    10           // 10msec Serial ATA 1.0 Sec 5.2

#if INDEX_DATA_PORT_ACCESS

    //
    //Index , Data port access 
    //

#define     HBA_PORT_REG_BASE(Port) \
            (UINTN) (Port * HBA_PORTS_REG_WIDTH + HBA_PORTS_START)

#define     HBA_REG32( BaseAddr, Register ) \
            (ReadDataDword ((BaseAddr), (Register)))

#define     HBA_WRITE_REG32( BaseAddr, Register, Data ) \
            (WriteDataDword( BaseAddr, Register, Data ))

#define     HBA_REG16( BaseAddr, Register ) \
            (ReadDataWord( BaseAddr, Register ))

#define     HBA_WRITE_REG16( BaseAddr, Register, Data ) \
            (WriteDataWord( BaseAddr, Register, Data ))

#define     HBA_REG8( BaseAddr, Register ) \
            (ReadDataByte ((BaseAddr), (Register)))

#define     HBA_WRITE_REG8( BaseAddr, Register, Data ) \
            (WriteDataByte( BaseAddr, Register, Data ))

#define     HBA_REG8_OR( BaseAddr, Register, OrData) \
            HBA_WRITE_REG8(BaseAddr, Register, ((HBA_REG8 ((BaseAddr), (Register))) | ((UINT8) (OrData))))

#define     HBA_REG16_OR( BaseAddr, Register, OrData) \
            HBA_WRITE_REG16(BaseAddr, Register, ((HBA_REG16 ((BaseAddr), (Register))) | ((UINT16) (OrData))))

#define     HBA_REG32_OR( BaseAddr, Register, OrData) \
            HBA_WRITE_REG32(BaseAddr, Register, ((HBA_REG32 ((BaseAddr), (Register))) | ((UINT32) (OrData))))

#define     HBA_REG8_AND( BaseAddr, Register, AndData) \
            HBA_WRITE_REG8(BaseAddr, Register, ((HBA_REG8 ((BaseAddr), (Register))) & ((UINT8) (AndData))))

#define     HBA_REG16_AND( BaseAddr, Register, AndData) \
            HBA_WRITE_REG16(BaseAddr, Register, ((HBA_REG16 ((BaseAddr), (Register))) & ((UINT16) (AndData))))
 
#define     HBA_REG32_AND( BaseAddr, Register, AndData) \
            HBA_WRITE_REG32(BaseAddr, Register, ((HBA_REG32 ((BaseAddr), (Register))) & ((UINT32) (AndData))))

#define     HBA_REG8_AND_OR( BaseAddr, Register, AndData, OrData) \
            HBA_WRITE_REG8(BaseAddr, Register, ((HBA_REG8 ((BaseAddr), (Register))) & ((UINT8) (AndData)) | ((UINT8) (OrData))))

#define     HBA_REG16_AND_OR( BaseAddr, Register, AndData, OrData) \
            HBA_WRITE_REG16(BaseAddr, Register, ((HBA_REG16 ((BaseAddr), (Register))) & ((UINT16) (AndData)) | ((UINT16) (OrData))))

#define     HBA_REG32_AND_OR( BaseAddr, Register,AndData,  OrData) \
            HBA_WRITE_REG32(BaseAddr, Register, ((HBA_REG32 ((BaseAddr), (Register))) & ((UINT32) (AndData)) | ((UINT32) (OrData))))
  
//Ports
#define     HBA_PORT_REG8(BaseAddr, Port, Register) \
            (HBA_REG8 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))

#define     HBA_PORT_REG16(BaseAddr, Port, Register) \
            (HBA_REG16 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))

#define     HBA_PORT_REG32(BaseAddr, Port, Register) \
            (HBA_REG32 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))

#define     HBA_PORT_WRITE_REG8(BaseAddr, Port, Register, Data) \
            (HBA_WRITE_REG8 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), Data))

#define     HBA_PORT_WRITE_REG16(BaseAddr, Port, Register, Data) \
            (HBA_WRITE_REG16 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)),Data))

#define     HBA_PORT_WRITE_REG32(BaseAddr, Port, Register,Data) \
            (HBA_WRITE_REG32 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)),Data))

#define     HBA_PORT_REG8_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG8_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG16_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG16_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG32_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG32_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG8_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG8_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG16_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG16_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG32_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG32_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG8_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG8_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#define     HBA_PORT_REG16_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG16_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#define     HBA_PORT_REG32_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG32_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#else
    //
    //MMIO Access
    //
#define     MmAddress( BaseAddr, Register ) \
            ((UINTN)(BaseAddr) + \
            (UINTN)(Register) \
             )
#define     Mm32Ptr( BaseAddr, Register ) \
            ((volatile UINT32 *)MmAddress (BaseAddr, Register ))

#define     Mm16Ptr( BaseAddr, Register ) \
            ((volatile UINT16 *)MmAddress (BaseAddr, Register ))

#define     Mm8Ptr( BaseAddr, Register ) \
            ((volatile UINT8 *)MmAddress (BaseAddr, Register ))
  
//HBA Generic
#define     HBA_PORT_REG_BASE(Port) \
             (UINTN) (Port * HBA_PORTS_REG_WIDTH + HBA_PORTS_START)

#define     HBA_REG32( BaseAddr, Register ) \
            (*Mm32Ptr ((BaseAddr), (Register)))

#define     HBA_REG16( BaseAddr, Register ) \
            (*Mm16Ptr ((BaseAddr), (Register)))

#define     HBA_REG8( BaseAddr, Register ) \
            (*Mm8Ptr ((BaseAddr), (Register)))

#define     HBA_WRITE_REG32( BaseAddr, Register, Data ) \
            (HBA_REG32 ((BaseAddr), (Register))) = ((UINT32) (Data))

#define     HBA_WRITE_REG16( BaseAddr, Register, Data ) \
            (HBA_REG16 ((BaseAddr), (Register))) = ((UINT16) (Data))

#define     HBA_WRITE_REG8( BaseAddr, Register, Data ) \
            (HBA_REG8 ((BaseAddr), (Register))) = ((UINT8) (Data))

#define     HBA_REG8_OR( BaseAddr, Register, OrData) \
            (HBA_REG8 ((BaseAddr), (Register))) |= ((UINT8) (OrData))

#define     HBA_REG16_OR( BaseAddr, Register, OrData) \
            (HBA_REG16 ((BaseAddr), (Register))) |= ((UINT16) (OrData))

#define     HBA_REG32_OR( BaseAddr, Register, OrData) \
            (HBA_REG32 ((BaseAddr), (Register))) = (HBA_REG32 ((BaseAddr), (Register))) | ((UINT32) (OrData))

#define     HBA_REG8_AND( BaseAddr, Register, AndData) \
            (HBA_REG8 ((BaseAddr), (Register))) = (HBA_REG8 ((BaseAddr), (Register))) & ((UINT8) (AndData))

#define     HBA_REG16_AND( BaseAddr, Register, AndData) \
            (HBA_REG16 ((BaseAddr), (Register))) &= ((UINT16) (AndData))
 
#define     HBA_REG32_AND( BaseAddr, Register, AndData) \
            (HBA_REG32 ((BaseAddr), (Register))) = (HBA_REG32 ((BaseAddr), (Register))) & ((UINT32) (AndData))

#define     HBA_REG8_AND_OR( BaseAddr, Register, AndData, OrData) \
            (HBA_REG8 ((BaseAddr), (Register)) = \
                (((HBA_REG8 ((BaseAddr), (Register))) & ((UINT8) (AndData))) | ((UINT8) (OrData))))

#define     HBA_REG16_AND_OR( BaseAddr, Register, AndData, OrData) \
            (HBA_REG16 ((BaseAddr), (Register)) = \
                (((HBA_REG16 ((BaseAddr), (Register))) & ((UINT16) AndData)) | ((UINT16) (OrData))))

#define     HBA_REG32_AND_OR( BaseAddr, Register,AndData,  OrData) \
            (HBA_REG32 ((BaseAddr), (Register)) = \
                (((HBA_REG32 ((BaseAddr), (Register))) & ((UINT32) (AndData))) | ((UINT32) (OrData))))
  
//Ports
#define     HBA_PORT_REG8(BaseAddr, Port, Register) \
            (HBA_REG8 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))

#define     HBA_PORT_REG16(BaseAddr, Port, Register) \
            (HBA_REG16 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))

#define     HBA_PORT_REG32(BaseAddr, Port, Register) \
            (HBA_REG32 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))

#define     HBA_PORT_WRITE_REG8(BaseAddr, Port, Register, Data) \
            (HBA_WRITE_REG8 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), Data))

#define     HBA_PORT_WRITE_REG16(BaseAddr, Port, Register, Data) \
            (HBA_WRITE_REG16 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)),Data))

#define     HBA_PORT_WRITE_REG32(BaseAddr, Port, Register,Data) \
            (HBA_WRITE_REG32 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)),Data))

#define     HBA_PORT_REG8_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG8_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG16_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG16_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG32_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG32_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG8_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG8_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG16_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG16_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG32_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG32_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG8_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG8_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#define     HBA_PORT_REG16_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG16_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#define     HBA_PORT_REG32_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG32_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************