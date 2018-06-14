//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Core/biosdata.h 7     1/12/10 11:46a Olegi $
//
// $Revision: 7 $
//
// $Date: 1/12/10 11:46a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Core/biosdata.h $
// 
// 7     1/12/10 11:46a Olegi
// Copyright message updated.
// 
// 6     4/27/07 5:13p Olegi
// CSM.CHM file preparation.
//
// 5     5/16/06 1:57p Olegi
//
// 4     8/02/05 11:27a Olegi
//
// 3     3/04/05 1:51p Mandal
//
//**********************************************************************
//----------------------------------------------------------------------------
// BIOSDATA.H -- BIOS Global Data Area and EBDA
//----------------------------------------------------------------------------
#ifndef __BIOS_DATA_AREA__
#define __BIOS_DATA_AREA__

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack (1)

typedef struct _BDA_DATA {

UINT16  rs_232_address[4];  // 00 - RS232 adapters addresses
UINT16  printer_address[3]; // 08 - Printer addresses
UINT16  ext_bios_data_seg;  // 0E - Segment pointer to EBDA
UINT16  machine_config;     // 10 - Hardware Equipment Status
UINT8   test_scratch;       // 12 - Scratch byte during init
UINT16  system_memory;      // 13 - System Memory in KBytes
UINT8   sys_info;           // 15 - miscellaneous system info
UINT8   dummy_byte_1;       // 16
UINT8   kb_stat_flag;       // 17 - Keyboard Status Flag
UINT8   kb_hold_flag;       // 18 - Toggle key's hold flag
UINT8   kb_alt_char;        // 19 - Alt_character byte
UINT16  kb_buf_head_ptr;    // 1A - Keyboard buffer head pointer
UINT16  kb_buf_tail_ptr;    // 1C - Keyboard buffer tail pointer
UINT16  kb_buffer[16];      // 1E - Keyboard buffer (15 char max)
UINT8   recal_int_flag;     // 3E - Status for recalibration
UINT8   motor_status_flag;  // 3F - Status for drive motors
UINT8   motor_time_count;   // 40 - Turn off time for motor
UINT8   floppy_io_status;   // 41 - Return code status byte
UINT8   task_file[7];       // 42 - A.K.A. fdc_8272_status
UINT8   mode_of_vdo;        // 49 - Current Video Mode (set by user)
UINT16  columns_of_vdo;     // 4A - Number of columns per row
UINT16  page_length;        // 4C - Number of bytes per Video Page
UINT16  page_start;         // 4E - Start address of Active Video Page
UINT16  position_of_cursor[8];  // 50 - Cursor position for each Video Page
UINT16  mode_of_cursor;     // 60 - Current cursor mode setting
UINT8   active_page_no;     // 62 - Current display page no
UINT16  address_of_6845;    // 63 - Address of 6845 index reg
UINT8   current_mode_set;   // 65 - Mode set in 6845 control port
UINT8   current_palette;    // 66 - Current palette set
//---------------------------------------
//  POST DATA STORAGES
//---------------------------------------
UINT16  offset_shutdown;    // 67 - Offset of shutdown routine
UINT16  segment_shutdown;   // 69 - Segment of shutdown routine
UINT8   interrupt_flag;     // 6B - Interrupt flag
//----------------------------------------------------------------------------
//  TIMER DATA STORAGES
//----------------------------------------------------------------------------
//UINT16    timer_low_count;    // 6C - Low Word of timer count
//UINT16    timer_high_count;   // 6E - High Word of timer count
UINT32  timer_count;    // 6C - timer count
UINT8   timer_count_rolled; // 70 - Timer Rolled Over
//----------------------------------------------------------------------------
//  BIOS DATA STORAGES EXTENDED
//----------------------------------------------------------------------------
UINT8   break_flag;         // 71 - Flag for CTRL-BREAK key key
UINT16  dummy_word;         // 72 - Unused data word
//----------------------------------------------------------------------------
//  WINCHESTER DATA STORAGES
//----------------------------------------------------------------------------
UINT8   winch_status;       // 74 - Status of Hard Disk operation
UINT8   winch_number;       // 75 - Number of Hard Disk drives
UINT8   winch_control_byte; // 76
UINT8   dummy_byte_2;       // 77
//----------------------------------------------------------------------------
//  PRINTER & RS232 DATA STORAGES
//----------------------------------------------------------------------------
UINT8   print_time_max[4];  // 78 - Maximum time for printing
UINT8   rs_232_time_max[4]; // 7C - Maximum transmission time for COM ports
//----------------------------------------------------------------------------
//  KEYBOARD DATA STORAGES EXTENDED
//----------------------------------------------------------------------------
UINT16  kb_buff_begin;      // 80 - Start address of Keyboard Buffer
UINT16  kb_buff_end;        // 82 - End address of Keyboard Buffer
UINT8   rows_of_vdo[7];     // 84 - EGA/VGA control state
//----------------------------------------------------------------------------
//  FLOPPY DATA STORAGES EXTENDED
//----------------------------------------------------------------------------
UINT8   last_xfer_rate;     // 8B - Last data transfer rate (Floppy)
//----------------------------------------------------------------------------
//  WINCHESTER DATA STORAGES EXTENDED
//----------------------------------------------------------------------------
UINT8   winch_stat_reg;     // 8C - Hard Disk status register
UINT8   winch_error_reg;    // 8D - Hard Disk error register, a.k.a. iraid_int_flag
UINT8   winch_int_flag;     // 8E - Hard Disk interrupt status
//----------------------------------------------------------------------------
//  FLOPPY DATA STORAGES EXTENDED
//----------------------------------------------------------------------------
UINT8   duel_card;          // 8F - Availability of 1.2M Floppy Drive
UINT8   current_floppy_media[2];    // 90 - Type of floppy drive/media
UINT8   run_scratch1;       // 92 - Runtime Scratch data byte 1
UINT8   run_scratch2;       // 93 - Runtime Scratch data byte 1
UINT8   current_cylinder[2];// 94 - Cylinder position of Floppy Disk
//----------------------------------------------------------------------------
//  KEYBOARD DATA STORAGES EXTENDED
//----------------------------------------------------------------------------
UINT8   dummy_byte_3;       // 96 - Keyboard Type byte
UINT8   kb_leds_flag;       // 97 - Keyboard LED's status byte
//----------------------------------------------------------------------------
//  REAL TIME CLOCK DATA STORAGES
//----------------------------------------------------------------------------
UINT16  user_flag_offset;   // 98 - Offset of user defined flag
UINT16  user_flag_segment;  // 9A - Segment of user defined flag
UINT16  user_wait_low;      // 9C - Low WORD of user defined time
UINT16  user_wait_high;     // 9E - High WORD of user defined time
UINT8   user_wait_flag[23]; // A0 - User defined time active flag, Video data area
//----------------------------------------------------------------------------
//  APM HANDLING BIOS DATA AREA USED FOR GREEN PC/NOTE BOOK
//----------------------------------------------------------------------------
UINT8   apm_data[73];       // B7
UINT8   prtsc_status_flag;  // 100 - Print Screen status byte

} BDA_DATA;

#pragma pack ()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
