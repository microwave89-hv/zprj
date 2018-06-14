// {2EF1BA1A-C836-4a50-BF89-525FF29FF787}
#define MXM30_PEI_GUID \
    { 0x2ef1ba1a, 0xc836, 0x4a50, 0xbf, 0x89, 0x52, 0x5f, 0xf2, 0x9f, 0xf7, 0x87 }

// {4EA9D4FE-E6F6-410b-8037-0F98B5968B65}
#define MXM3_EFI_GUID \
  { 0x4EA9D4FE, 0xE6F6, 0x410B, 0x90, 0x37, 0x0f, 0x98, 0xB5, 0x96, 0x8B, 0x65 }

/////////////////////////////////////////////////////////////////////////////////////////
//////M X M  3.0  D E F I N I T I O N S /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define EFI30_DataBlockID   MXM_REV_SUPPORTED 
//0x30;
//          the revision of the MXM software specification that is supported by the MXM module.
//          Format is binary coded decimal, for example: 0x30 = 3.0, etc.

#define EFI30_SupportFuncs  MXM_FUNC_SUPPORTED 
//0x3;
//          Bit 0 = `1' MxmReturnSpecLevel method is required
//          Bit 1 = `1' MxmReturnStucture is also required
//          Bit 2 = `1' OPTIONAL. if MxmSelectOutputDevice is supported, `0' if not
//          Bit 3 = `1' OPTIONAL. if MxmCheckOutputDevice is supported, `0' if not

typedef struct {
    CHAR8   Sig[4]; // "MXM_"
    UINT8   Ver;
    UINT8   Rev;
    UINT16  Len;
} MXM_STRUCT_HDR;

typedef EFI_STATUS (EFIAPI *MXM_RETURN_SPEC_LEVEL) (
    IN struct _MXM3_EFI_INTERFACE *This,
    IN EFI_HANDLE   ControllerHandle,
    IN OUT CHAR16   usStructSize,
    IN OUT CHAR8    *pucRevisionLevel,
    OUT UINTN       *puSupportFuncs
);

typedef EFI_STATUS (EFIAPI *MXM_RETURN_STRUCTURE)(
    IN struct _MXM3_EFI_INTERFACE *This,
    IN EFI_HANDLE    ControllerHandle,
    IN OUT CHAR16    *usStructSize,
    IN CHAR16        usDataBlockID,
    OUT CHAR8        **pMxmStruct
);

typedef EFI_STATUS (EFIAPI *MXM_SELECT_OUTPUT_DEVICE)(
    IN struct _MXM3_EFI_INTERFACE *This,
    IN EFI_HANDLE      ControllerHandle,
    IN OUT CHAR16      usStructSize,
    IN EFI_HANDLE      ChildHandle,
    IN CHAR8           ucOutputSetting
);

typedef EFI_STATUS (EFIAPI *MXM_CHECK_OUTPUT_DEVICE)(
    IN struct _MXM3_EFI_INTERFACE *This,
    IN EFI_HANDLE       ControllerHandle,
    IN OUT CHAR16       usStructSize,
    IN EFI_HANDLE       ChildHandle,
    OUT CHAR8           ucDisplayAvailable
);

typedef struct _MXM3_EFI_INTERFACE {
    MXM_RETURN_SPEC_LEVEL   MxmReturnSpecLevel;
    MXM_RETURN_STRUCTURE    MxmReturnStructure;
    MXM_SELECT_OUTPUT_DEVICE MxmSelectOutputDevice;
    MXM_CHECK_OUTPUT_DEVICE MxmCheckOutputDevice;
} MXM3_EFI_PROTOCOL;



EFI_STATUS 
LoadFile(
    IN EFI_GUID *Guid, 
    OUT VOID	**Buffer, 
    OUT UINTN	*BufferSize
    );

//#define		MXM_DRIVER_VERSION		0x001

