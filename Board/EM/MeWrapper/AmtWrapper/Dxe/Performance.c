//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/Performance.c 3     5/14/14 9:53p Tristinchou $
//
// $Revision: 3 $
//
// $Date: 5/14/14 9:53p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/Performance.c $
// 
// 3     5/14/14 9:53p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 2     9/19/12 6:35a Klzhan
// Fix Build error when Performance is enabled.
// 
// 1     2/08/12 1:08a Klzhan
// Initial Check in 
// 
// 2     9/21/11 9:00a Klzhan
// [TAG]  		EIP69500
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Compiler Error when DXE_PERFORMANCE is on
// [RootCause]  	EDK Library doesn't support this function.
// 
// 1     2/25/11 1:44a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            Performance.c
//
// Description:     help to get the system performance
//
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

Copyright (c) 2004 - 2005, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  Performance.c

Abstract:

  This file include the file which can help to get the system
  performance, all the function will only include if the performance
  switch is set.

--*/

#include "Tiano.h"
#include "EfiDriverLib.h"
#include "EfiPrintLib.h"

#ifndef GUID_VARIABLE_DECLARATION
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#endif

//#define EFI_DXE_PERFORMANCE

#ifdef EFI_DXE_PERFORMANCE
#include "EfiImage.h"
#include "Include\Protocol\Performance.h"

VOID
ConvertChar16ToChar8 (
  IN CHAR8      *Dest,
  IN CHAR16     *Src
  )
{
  while (*Src) {
    *Dest++ = (UINT8) (*Src++);
  }

  *Dest = 0;
}
#include <token.h>
#include EFI_ARCH_PROTOCOL_CONSUMER (Cpu)
#include EFI_GUID_DEFINITION     (GlobalVariable)


extern EFI_STATUS GetTimerValue (  UINT64 *TimerValue );//extern UINT64 GetCpuTimer ();
extern UINT64 DivU64x32 (UINT64 Dividend,UINTN Divisor,UINTN *Remainder);
extern CHAR8 *EfiAsciiStrCpy (CHAR8 *Destination,CHAR8    *Source );

#define Div64(a,b,c) DivU64x32(a,b,c)
#define Strcpy(a,b) EfiAsciiStrCpy(a,b)
//**********************************************************************
//      PERFORMANCE FUNCTIONS AND STRUCTURES
//**********************************************************************

#define EFI_PERF_PEI_ENTRY_MAX_NUM      50

typedef struct {
    CHAR8   Token[EFI_PERF_PDBFILENAME_LENGTH];
    UINT32  Duration;
} EFI_PERF_DATA;
    
typedef struct {
    UINT64        BootToOs;
    UINT64        S3Resume;
    UINT32        S3EntryNum;
    EFI_PERF_DATA S3Entry[EFI_PERF_PEI_ENTRY_MAX_NUM];
    UINT64        CpuFreq;
    UINT64        BDSRaw;
    UINT32        Count;
    UINT32        Signiture;
} EFI_PERF_HEADER;
//*************************************************************************
//<AMI_PHDR_START>
//
// Name: WriteBootToOsPerformanceData
//
// Description:
//  VOID WriteBootToOsPerformanceData() allocates a block of memory and
// writes performance data into it.  
//
// Input:
//  VOID.
//
// Output:
//  VOID.
//
// Modified:
//
// Referrals:
//  GetCpuTimer
//  Div64
//  Strcpy
// 
// Notes:
//  This function must only be called once; by default, it is called by BDS.
//          
//<AMI_PHDR_END>
//*************************************************************************
VOID WriteBootToOsPerformanceData (){
  static EFI_PHYSICAL_ADDRESS      AcpiLowMemoryBase = 0;
  static BOOLEAN                   FirstCall = TRUE;

  EFI_STATUS                Status;
  EFI_CPU_ARCH_PROTOCOL     *Cpu;
  EFI_PERFORMANCE_PROTOCOL  *DrvPerf;
  UINT32                    AcpiLowMemoryLength;
  UINT32                    LimitCount;
  EFI_PERF_HEADER           PerfHeader;
  EFI_PERF_DATA             PerfData;
  EFI_GAUGE_DATA            *DumpData;
  EFI_HANDLE                *Handles;
  UINTN                     NoHandles;
  UINT8                     *Ptr;
  UINT8                     *PdbFileName;
  UINT32                    Index;
  UINT64                    Ticker;
  UINT64                    Freq;
  UINT32                    Duration;
  UINT64                    CurrentTicker;
  UINT64                    TimerPeriod;
  EFI_GUID                  gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE_GUID;
  IN CHAR8                  *Dest;
  IN CHAR16                 *Src;
  UINT32                    VarAttr;
  UINTN                     VarSize;



  // Retrive time stamp count as early as possilbe
  GetTimerValue(&Ticker);//Ticker = GetCpuTimer (); //Bruce[c]

  // Allocate a block of memory that contain performance data to OS for the first call
  if(FirstCall)
  {
    Status = gBS->AllocatePages (
                  AllocateAnyPages,
                  EfiRuntimeServicesData,
                  4,
                  &AcpiLowMemoryBase
                  );
    if (EFI_ERROR (Status)) {
        return ;
    }
  }

  AcpiLowMemoryLength  = EFI_PAGES_TO_SIZE(4);

  Ptr                   = (UINT8 *) ((UINT32) AcpiLowMemoryBase + sizeof (EFI_PERF_HEADER));
  LimitCount            = (AcpiLowMemoryLength - sizeof (EFI_PERF_HEADER)) / sizeof (EFI_PERF_DATA);

  // Get performance architecture protocol
  Status = gBS->LocateProtocol (
                  &gEfiPerformanceProtocolGuid,
                  NULL,
                  &DrvPerf
                  );
  if (EFI_ERROR (Status)) {
    gBS->FreePages (AcpiLowMemoryBase, 4);
    return ;
  }
  // Initialize performance data structure
  gBS->SetMem (&PerfHeader, sizeof (EFI_PERF_HEADER), 0);

  // Get CPU frequency
  Status = gBS->LocateProtocol (
                  &gEfiCpuArchProtocolGuid,
                  NULL,
                  &Cpu
                  );
  if (EFI_ERROR (Status)) {
    gBS->FreePages (AcpiLowMemoryBase, 4);
    return ;
  }
  // Get Cpu Frequency
  Status = Cpu->GetTimerValue (Cpu, 0, &(CurrentTicker), &TimerPeriod);
  if (EFI_ERROR (Status)) {
    gBS->FreePages (AcpiLowMemoryBase, 4);
    return ;
  }

  Freq                = Div64(1000000000000, (UINTN) TimerPeriod, NULL);
  PerfHeader.CpuFreq = Freq;

  // Record current raw performance data
  PerfHeader.BDSRaw = Ticker;

  // Put Detailed performance data into memory
  Handles = NULL;
  Status = gBS->LocateHandleBuffer (
                  AllHandles,
                  NULL,
                  NULL,
                  &NoHandles,
                  &Handles
                  );
  if (EFI_ERROR (Status)) {
    gBS->FreePages (AcpiLowMemoryBase, 1);
    return ;
  }

  // Get DXE drivers performance
  for (Index = 0; Index < NoHandles; Index++) {
    Ticker = 0;
    PdbFileName = NULL;
    DumpData = DrvPerf->GetGauge (
                          DrvPerf,    // Context
                          NULL,       // Handle
                          NULL,       // Token
                          NULL,       // Host
                          NULL        // PrecGauge
                          );
    while (DumpData) {
      if (DumpData->Handle == Handles[Index]) {
      	PdbFileName = &(DumpData->PdbFileName[0]);
      	if (DumpData->StartTick < DumpData->EndTick) {
      	  Ticker += (DumpData->EndTick - DumpData->StartTick);
      	}
      }

      DumpData = DrvPerf->GetGauge (
                            DrvPerf,  // Context
                            NULL,     // Handle
                            NULL,     // Token
                            NULL,     // Host
                            DumpData  // PrecGauge
                            );
    }

    Duration = (UINT32) Div64 (
                          Ticker,
                          (UINT32) Freq,
                          NULL
                          );

    if (Duration > 0) {
      gBS->SetMem (&PerfData, sizeof (EFI_PERF_DATA), 0);

      if (PdbFileName != NULL) {
        Strcpy (PerfData.Token, PdbFileName);
      }

      PerfData.Duration = Duration;

      gBS->CopyMem (Ptr, &PerfData, sizeof (EFI_PERF_DATA));
      Ptr += sizeof (EFI_PERF_DATA);

      PerfHeader.Count++;
      if (PerfHeader.Count == LimitCount) {
        goto Done;
      }
    }
  }

  gBS->FreePool (Handles);

  // Get inserted performance data
  DumpData = DrvPerf->GetGauge (
                        DrvPerf,      // Context
                        NULL,         // Handle
                        NULL,         // Token
                        NULL,         // Host
                        NULL          // PrecGauge
                        );
  while (DumpData) {
    if ((DumpData->Handle) || (DumpData->StartTick > DumpData->EndTick)) {
      DumpData = DrvPerf->GetGauge (
                            DrvPerf,  // Context
                            NULL,     // Handle
                            NULL,     // Token
                            NULL,     // Host
                            DumpData  // PrecGauge
                            );
      continue;
    }

    gBS->SetMem (&PerfData, sizeof (EFI_PERF_DATA), 0);

    //convert CHAR16 string to CHAR8 string
    Src = DumpData->Token;
    Dest = (UINT8 *) PerfData.Token;
    while (*Src) *Dest++ = (UINT8) (*Src++);
    *Dest = 0;

    PerfData.Duration = (UINT32) Div64 (
                                    DumpData->EndTick - DumpData->StartTick,
                                    (UINT32) Freq,
                                    NULL
                                    );

    gBS->CopyMem(Ptr, &PerfData, sizeof (EFI_PERF_DATA));
    Ptr += sizeof (EFI_PERF_DATA);

    PerfHeader.Count++;
    if (PerfHeader.Count == LimitCount) {
      goto Done;
    }

    DumpData = DrvPerf->GetGauge (
                          DrvPerf,    // Context
                          NULL,       // Handle
                          NULL,       // Token
                          NULL,       // Host
                          DumpData    // PrecGauge
                          );
  }

Done:
  PerfHeader.Signiture = 0x66726550;

  // Put performance data to memory
  gBS->CopyMem (
    (UINTN *) (UINTN) AcpiLowMemoryBase,
    &PerfHeader,
    sizeof (EFI_PERF_HEADER)
    );

  if(FirstCall)
  {
    VarAttr = 0;
    VarSize = 0;

    Status = gRT->GetVariable(
                    L"PerfDataMemAddr",
                    &gEfiGlobalVariableGuid,
                    &VarAttr,
                    &VarSize,
                    NULL );
    if( EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL )
    {
        VarAttr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
        VarSize = sizeof(UINT32);
    }

    gRT->SetVariable (
            L"PerfDataMemAddr",
            &gEfiGlobalVariableGuid,
            VarAttr,
            VarSize,
            (VOID *) &AcpiLowMemoryBase );

    FirstCall = FALSE;
  }
}

#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
