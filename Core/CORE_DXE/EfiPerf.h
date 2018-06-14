//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/EDK/DxeMain/EfiPerf.h 3     5/06/08 10:07a Felixp $
//
// $Revision: 3 $
//
// $Date: 5/06/08 10:07a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/DxeMain/EfiPerf.h $
// 
// 3     5/06/08 10:07a Felixp
// 
// 2     5/05/08 4:12p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	EfiPerf.h
//
// Description:	This file provides performance API definitions used by DXE Core.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _EFI_PERF_H_
#define _EFI_PERF_H_

#include <AmiDxeLib.h>
#include <Protocol/Performance.h>

#define DXE_PHASE 0
#define SHELL_PHASE 1
#define PEI_PHASE 2

EFI_STATUS
GetTimerValue (
  OUT UINT64    *TimerValue
  );

EFI_STATUS
InitializePerformanceInfrastructure (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable,
  IN UINT64             Ticker
  );

EFI_STATUS
UpdateMeasure (
  IN EFI_HANDLE      Handle,
  IN UINT16          *Token,
  IN UINT16          *Host,
  IN EFI_HANDLE      HandleNew,
  IN UINT16          *TokenNew,
  IN UINT16          *HostNew
  );

#ifdef EFI_DXE_PERFORMANCE
#define PERF_ENABLE(handle, table, ticker)      InitializePerformanceInfrastructure (handle, table, ticker)
#define PERF_UPDATE(handle, token, host, handlenew, tokennew, hostnew) \
  UpdateMeasure (handle, \
                 token, \
                 host, \
                 handlenew, \
                 tokennew, \
                 hostnew \
      )
#else
#define PERF_ENABLE(handle, table, ticker)
#define PERF_UPDATE(handle, token, host, handlenew, tokennew, hostnew)
#endif

#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
