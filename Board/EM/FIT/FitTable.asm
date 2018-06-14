include token.equ

FitEntry Struct
	TblAddress      DQ      0
	TblSIZE	        DD      0   ;only 3 bytes valid,
	TblVer          DW      0
	TblType         DB      0
	TblChkSum       DB      0
FitEntry ENDS


ifndef EFIx64
.model small
endif

.data
  Type0Entry      FitEntry <'   _TIF_', 0, 100h, 00h, 0>       ; FIT type 0x00 - FIT Header Entry
  Type1Entry      FitEntry <0FFFFFFFFh, 0, 100h, 01h, 0>       ; FIT type 0x01 - Microcode Update Entry
IFDEF MKF_INTEL_BOOT_GUARD_SUPPORT
IF MKF_INTEL_BOOT_GUARD_SUPPORT
  Type2Entry      FitEntry <0FFFFFFFFh, 0, 100h, 02h, 0>       ; FIT type 0x02 - Anc ACM location
  TypebEntry      FitEntry <0FFFFFFFFh, 241h, 100h, 0Bh, 0>    ; FIT Type 0x0B - Key Manifest
  TypecEntry      FitEntry <0FFFFFFFFh, 2BBh, 100h, 0Ch, 0>    ; FIT type 0x0C - Boot Policy Manifest
ENDIF
ENDIF

  ; Reserve
  DQ  0FFFFFFFFFFFFFFFFh
  DQ  0FFFFFFFFFFFFFFFFh

  ; Reserve
  DQ  0FFFFFFFFFFFFFFFFh
  DQ  0FFFFFFFFFFFFFFFFh

  ; Reserve
  DQ  0FFFFFFFFFFFFFFFFh
  DQ  0FFFFFFFFFFFFFFFFh

  ; Reserve
  DQ  0FFFFFFFFFFFFFFFFh
  DQ  0FFFFFFFFFFFFFFFFh

  ; Reserve
  DQ  0FFFFFFFFFFFFFFFFh
  DQ  0FFFFFFFFFFFFFFFFh

  ; Reserve
  DQ  0FFFFFFFFFFFFFFFFh
  DQ  0FFFFFFFFFFFFFFFFh

  ; Reserve
  DQ  0FFFFFFFFFFFFFFFFh
  DQ  0FFFFFFFFFFFFFFFFh

  ; Reserve
  DQ  0FFFFFFFFFFFFFFFFh
  DQ  0FFFFFFFFFFFFFFFFh

  ; Reserve
  DQ  0FFFFFFFFFFFFFFFFh
  DQ  0FFFFFFFFFFFFFFFFh

  ; Reserve
  DQ  0FFFFFFFFFFFFFFFFh
  DQ  0FFFFFFFFFFFFFFFFh
END
