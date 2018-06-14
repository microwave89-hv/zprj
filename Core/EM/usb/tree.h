//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/tree.h 7     9/05/08 4:13p Olegi $
//
// $Revision: 7 $
//
// $Date: 9/05/08 4:13p $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/tree.h $
// 
// 7     9/05/08 4:13p Olegi
// 
// 6     5/16/08 12:02p Olegi
// Compliance with AMI coding standard.
// 
// 5     3/20/07 1:29p Olegi
//
// 3     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 2     6/15/05 1:59p Andriyn
// Comments were changed
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           Tree.h
//
//  Description:    Tree routines header
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __TREE_H__
#define __TREE_H__

typedef struct _TREENODE_T TREENODE_T;
typedef struct _TREENODE_T{
    VOID* data;
    TREENODE_T* right;
    TREENODE_T* left;
    TREENODE_T* child;
    TREENODE_T* parent;
} TREENODE_T;

typedef struct QUEUE_T;

typedef int (*TREE_PREDICATE1_T)(VOID* n, VOID* context);
typedef VOID (*TREE_CALLBACK_T)(VOID* n, VOID* context );

TREENODE_T* TreeCreate( TREENODE_T* n, VOID* d);
VOID TreeAddChild( TREENODE_T* p, TREENODE_T* c );
VOID TreeRemove( TREENODE_T* n );
TREENODE_T* TreeSearchSibling(TREENODE_T* n, TREE_PREDICATE1_T pr, VOID* data );
TREENODE_T* TreeSearchDeep(TREENODE_T* n, TREE_PREDICATE1_T pr, VOID* data );
VOID TreeForEachSibling(TREENODE_T* n, TREE_CALLBACK_T pr, VOID* data );

VOID* QueueGet( QUEUE_T* q);
int QueueSize(QUEUE_T* q);
VOID QueuePut( QUEUE_T* q, VOID * d);
VOID* QueueRemoveMsg( QUEUE_T* q, int sz);
VOID QueuePutMsg( QUEUE_T* q, VOID * d, int sz );

#endif //__TREE_H__

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
