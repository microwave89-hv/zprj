/*++

   Copyright (c) 2006, Intel Corporation
   All rights reserved. This program and the accompanying materials
   are licensed and made available under the terms and conditions of the BSD License
   which accompanies this distribution.  The full text of the license may be found at
   http://opensource.org/licenses/bsd-license.php

   THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
   WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.


   Abstract:

   TcgService Protocol GUID as defined in TCG_EFI_Protocol_1_20_Final

   See http://trustedcomputinggroup.org for the latest specification

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_Protocol/TcgService/TcgService.c 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_Protocol/TcgService/TcgService.c $
// 
// 1     4/21/14 2:15p Fredericko
// 
// 1     10/08/13 12:00p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:58p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 2     5/20/10 8:44a Fredericko
// Included File Header
// Included File Revision History 
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgService.c
//
// Description: 
//  Defines Tcg Protocol guid
//
//<AMI_FHDR_END>
//*************************************************************************

#include <Tiano.h>

#include EFI_PROTOCOL_DEFINITION( TcgService )

EFI_GUID gEfiTcgProtocolGuid = EFI_TCG_PROTOCOL_GUID;

EFI_GUID_STRING( &gEfiTcgServiceProtocolGuid,
                 "TcgService",
                 "TCG Services Protocol" );
