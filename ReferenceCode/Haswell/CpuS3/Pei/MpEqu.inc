;@file
;  This is the equates file for HT (Hyper-threading) support
;
;@copyright
;  Copyright (c)  1999 - 2012 Intel Corporation. All rights reserved
;  This software and associated documentation (if any) is furnished
;  under a license and may only be used or copied in accordance
;  with the terms of the license. Except as permitted by such
;  license, no part of this software or documentation may be
;  reproduced, stored in a retrieval system, or transmitted in any
;  form or by any means without the express written consent of
;  Intel Corporation.
;
;  This file contains a 'Sample Driver' and is licensed as such
;  under the terms of your license agreement with Intel or your
;  vendor.  This file may be modified by the user, subject to
;  the additional terms of the license agreement
;

VacantFlag             Equ   00h
NotVacantFlag          Equ   0ffh

LockLocation                  equ        1000h - 0200h
StackStartAddressLocation     equ        LockLocation + 04h
StackSizeLocation             equ        LockLocation + 08h
CProcedureLocation            equ        LockLocation + 0Ch
GdtrLocation                  equ        LockLocation + 10h
IdtrLocation                  equ        LockLocation + 16h
BufferStartLocation           equ        LockLocation + 1Ch
PmodeOffsetLocation           equ        LockLocation + 20h
AcpiCpuDataAddressLocation    equ        LockLocation + 24h
MtrrValuesAddressLocation     equ        LockLocation + 28h
FinishedCountAddressLocation  equ        LockLocation + 2Ch
WakeupCountAddressLocation    equ        LockLocation + 30h
SerializeLockAddressLocation  equ        LockLocation + 34h
MicrocodeAddressLocation      equ        LockLocation + 38h
BootScriptAddressLocation     equ        LockLocation + 3Ch
StartStateLocation            equ        LockLocation + 40h
VirtualWireMode               equ        LockLocation + 44h
SemaphoreCheck                equ        LockLocation + 48h
PeiServices                   equ        LockLocation + 4Ch
PeiStall                      equ        LockLocation + 50h
CpuPerfCtrlValue              equ        LockLocation + 54h
CpuPlatformPolicyPpi          equ        LockLocation + 5Ch

PAUSE32   MACRO
            DB      0F3h
            DB      090h
            ENDM

;-------------------------------------------------------------------------------
