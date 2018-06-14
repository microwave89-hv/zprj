//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
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
#ifndef __HOTCLICK_BIN_H__
#define __HOTCLICK_BIN_H__

typedef	VOID	(*HOTCLICK_CALLBACK)	( VOID *container, VOID *object, VOID *cookie );

typedef struct _HOTCLICK_TEMPLATE
{
	UINT32 			Xo, Yo, Xn, Yn;
	HOTCLICK_CALLBACK	Callback;
	UINT32			BasePage;
}
HOTCLICK_TEMPLATE;

extern VOID EzportPlusMainFrameHandlewithMouse( VOID *app, VOID *hotclick, VOID *cookie );
extern VOID EzportPlusHelpFrameHandlewithMouse( VOID *app, VOID *hotclick, VOID *cookie );
extern VOID EzportPlusNavFrameHandlewithMouse( VOID *app, VOID *hotclick, VOID *cookie );


#endif //__HOTKEY_BIN_H__
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
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
