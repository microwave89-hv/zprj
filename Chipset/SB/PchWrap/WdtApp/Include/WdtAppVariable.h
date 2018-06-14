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

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppInclude/WdtAppVariable.h 1     2/08/12 8:35a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 8:35a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppInclude/WdtAppVariable.h $
// 
// 1     2/08/12 8:35a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************

#define WDT_PERSISTENT_DATA_GUID \
{0x78ce2354, 0xcfbc, 0x4643, 0xae, 0xba, 0x7, 0xa2, 0x7f, 0xa8, 0x92, 0xbf}

#define WDT_PERSISTENT_DATA_C_NAME         L"WdtPersistentData"
        
typedef struct _WDT_PERSISTENT_DATA {
  UINT8  Enable;
} WDT_PERSISTENT_DATA;
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

