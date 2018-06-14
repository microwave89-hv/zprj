#define NBCI_EFI_GUID \
    { 0x4EA9D4FE, 0xE6F6, 0x410B, 0x80, 0x37, 0x0F, 0x98, 0xB5, 0x96, 0x8B, 0x65 }

/////////////////////////////////////////////////////////////////////////////////////////
//////N B C I  D E F I N I T I O N S ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define EFI_Nbci_DataBlockID   NBCI_REV_SUPPORTED 
//0x11;
//          the revision of the NBCI software specification that is supported by the NBCI module.
//          Format is binary coded decimal, for example: 0x30 = 3.0, etc.

#define EFI_Nbci_SupportFuncs  NBCI_FUNC_SUPPORTED 
//0x3;
//          Bit 0 = `1' NBCIReturnSpecLevel method is required
//          Bit 1 = `1' NBCIReturnStucture is also required
//          Bit 2 = `1' OPTIONAL. if NBCISelectOutputDevice is supported, `0' if not
//          Bit 3 = `1' OPTIONAL. if NBCICheckOutputDevice is supported, `0' if not

typedef struct {
    CHAR8   Sig[4]; // "NBCI_"
    UINT8   Ver;
    UINT8   Rev;
    UINT16  Len;
} NBCI_STRUCT_HDR;

typedef EFI_STATUS (EFIAPI *NBCI_RETURN_SPEC_LEVEL) (
    IN struct _NBCI_EFI_INTERFACE *This,
    IN OUT CHAR8    *pucRevisionLevel,
    OUT UINTN       *puSupportFuncs
);

typedef EFI_STATUS (EFIAPI *NBCI_RETURN_STRUCTURE)(
    IN struct _NBCI_EFI_INTERFACE *This,
    IN EFI_HANDLE    ControllerHandle,
    IN OUT CHAR16    *usStructSize,
    IN CHAR16        usDataBlockID,
    OUT CHAR8        **pNBCIStruct
);

typedef EFI_STATUS (EFIAPI *NBCI_SELECT_OUTPUT_DEVICE)(
    IN struct _NBCI_EFI_INTERFACE *This,
    IN EFI_HANDLE      ControllerHandle,
    IN OUT CHAR16      usStructSize,
    IN EFI_HANDLE      ChildHandle,
    IN CHAR8           ucOutputSetting
);

typedef EFI_STATUS (EFIAPI *NBCI_CHECK_OUTPUT_DEVICE)(
    IN struct _NBCI_EFI_INTERFACE *This,
    IN EFI_HANDLE       ControllerHandle,
    IN OUT CHAR16       usStructSize,
    IN EFI_HANDLE       ChildHandle,
    OUT CHAR8           ucDisplayAvailable
);

typedef struct _NBCI_EFI_INTERFACE {
    NBCI_RETURN_SPEC_LEVEL   NBCIReturnSpecLevel;
    NBCI_RETURN_STRUCTURE    NBCIReturnStructure;
    NBCI_SELECT_OUTPUT_DEVICE NBCISelectOutputDevice;
    NBCI_CHECK_OUTPUT_DEVICE NBCICheckOutputDevice;
} NBCI_EFI_PROTOCOL;


EFI_STATUS
LoadAcpiTables(
    IN EFI_EVENT Event, IN VOID *Context  
  );

EFI_STATUS 
LoadFile(
    IN EFI_GUID *Guid, 
    OUT VOID	**Buffer, 
    OUT UINTN	*BufferSize
    );

//#define		NBCI_DRIVER_VERSION		0x001

