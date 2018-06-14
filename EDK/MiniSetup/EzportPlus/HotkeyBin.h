//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**           5555 Oakbrook Pkwy, Norcross, Georgia 30093       **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
#ifndef __HOTKEY_BIN_H__
#define __HOTKEY_BIN_H__

typedef	VOID	(*HOTKEY_CALLBACK)	( VOID *container, VOID *object, VOID *cookie );

typedef struct _HOTKEY_TEMPLATE
{
	EFI_INPUT_KEY	Key;
	UINT32			KeySftSte;
	HOTKEY_CALLBACK	Callback;
	UINT32			BasePage;
}
HOTKEY_TEMPLATE;

extern VOID EzportPlusHandleEscKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID EzportPlusHandleHelpKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID EzportPlusHandlePrevValuesKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID EzportPlusHandleFailsafeKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID EzportPlusHandleOptimalKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID EzportPlusHandleSaveExitKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID EzportPlusHandlePrnScrnKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID	PrntScrnKeyNotification(VOID *app, VOID *hotkey, VOID *cookie );//EIP-123311

#endif //__HOTKEY_BIN_H__
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**           5555 Oakbrook Pkwy, Norcross, Georgia 30093       **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
