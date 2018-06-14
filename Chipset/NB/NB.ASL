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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB.ASL 6     5/06/13 7:12a Ireneyang $
//
// $Revision: 6 $
//
// $Date: 5/06/13 7:12a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB.ASL $
// 
// 6     5/06/13 7:12a Ireneyang
// [TAG]         EIP105358
// [Category]    Improvement
// [Description] Save and restore the missed 81~86 reg lower nibbles for
//               S3.
// [Files]       NB.ASL;
// 
// 5     10/14/12 11:39a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Follow SA RC 0.71.
// [Files]        NBPei.c, NBDxe.c; NBGeneric.c; NBCspLib.h; NBSetup.c;
//    Nb.sd; GetSetupData.c
// 
// 4     8/14/12 4:32a Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Change for SystemAgent RefCode Revision: 0.6.1.
// [Files]       NB.sdl, NB.sd, NBCSP.CIF, NBDxe.c, NB.ASL, SaAudio.asl 
// 
// 3     7/03/12 6:39a Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Change the Save/Restore NB Registers position.
// [Files]       NB.ASL, NBAcpi.c, NBDxe.c
// 
// 2     6/14/12 4:39a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Description]   Support token to disable PEG 0 ~ 2.
// [Description]   NB.sdl, NB.sd, NB.ASL, HOST_BUS.ASL
// 
// 1     2/08/12 4:34a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NB.asl
//
// Description: The ASL file is for North Bridge specific function.
//
//<AMI_FHDR_END>
//*************************************************************************

Scope(\_SB.PCI0)
{
    // Save/Restore NB Shadow Register(s) Buffer
    Name (PA0H, 0)  
    Name (PA1H, 0)
    Name (PA1L, 0)
    Name (PA2H, 0)
    Name (PA2L, 0)
    Name (PA3H, 0)
    Name (PA3L, 0)
    Name (PA4H, 0)
    Name (PA4L, 0)
    Name (PA5H, 0)
    Name (PA5L, 0)
    Name (PA6H, 0)
    Name (PA6L, 0)
/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:	NPTS
; Description:	METHOD IS CALLED BY OS PRIOR TO ENTER ANY SLEEP STATE
; Input: Arg0 = Arg0 = Sleep state System about to enter
; Output: Nothing
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
	Method (NPTS, 1) {
         Store(PM0H,PA0H) // 0x80
         Store(PM1H,PA1H) // 0x81
         Store(PM1L,PA1L)
         Store(PM2H,PA2H) // 0x82
         Store(PM2L,PA2L)
         Store(PM3H,PA3H) // 0x83
         Store(PM3L,PA3L)
         Store(PM4H,PA4H) // 0x84
         Store(PM4L,PA4L)
         Store(PM5H,PA5H) // 0x85
         Store(PM5L,PA5L)
         Store(PM6H,PA6H) // 0x86
         Store(PM6L,PA6L)
	}

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:	NWAK
; Description:	METHOD CALLED ON WAKE UP FROM ANY SLEEP STATE
; Input: Arg0 = Sleep state System is resuming from
; Output: Nothing
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
	Method (NWAK, 1) {
         Store(PA0H,PM0H) // 0x80
         Store(PA1H,PM1H) // 0x81
         Store(PA1L,PM1L)
         Store(PA2H,PM2H) // 0x82
         Store(PA2L,PM2L)
         Store(PA3H,PM3H) // 0x83
         Store(PA3L,PM3L)
         Store(PA4H,PM4H) // 0x84
         Store(PA4L,PM4L)
         Store(PA5H,PM5H) // 0x85
         Store(PA5L,PM5L)
         Store(PA6H,PM6H) // 0x86
         Store(PA6L,PM6L)
	}


}//Scope(\_SB.PCI0)

//-----------------------------------------------------------------------
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

