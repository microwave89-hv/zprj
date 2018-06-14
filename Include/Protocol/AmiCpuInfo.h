//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuProtocols/AmiCpuInfo.h 2     6/16/14 4:51a Davidhsieh $
//
// $Revision: 2 $
//
// $Date: 6/16/14 4:51a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuProtocols/AmiCpuInfo.h $
// 
// 2     6/16/14 4:51a Davidhsieh
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Support the cache size which bigger than 0x8000MB
// [Files]  		AmiCpuInfo.h, CpuSmbios.c
// 
// 1     2/07/12 3:59a Davidhsieh
// 
// 1     5/06/11 6:08a Davidhsieh
// First release
// 
// 2     3/04/09 10:45a Markw
// Update copyright header.
// 
// 1     11/02/07 1:59p Markw
// 
// 1     11/02/07 1:45p Markw
// 
// 7     7/23/07 7:58p Markw
// 
// 6     3/23/07 9:54a Markw
// Updated headers.
// 
// 5     2/23/07 12:23p Markw
// Added comments.
// 
// 4     1/31/07 3:03p Markw
// Added providing EMT64 CPU support.
// 
// 3     7/21/05 10:12p Markw
// Fixed AmiCpuInfo.
// 
// 2     7/20/05 3:54p Markw
// Updated CACHE_INFO.
// 
// 1     7/19/05 10:18a Markw
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:	AmiCpuInfo.h
//
// Description:	AMI CPU INFO protocol header.
//
//<AMI_FHDR_END>
//---------------------------------------------------------------------------

#ifndef _AMI_CPU_INFO_H_
#define _AMI_CPU_INFO_H_

#ifdef __cplusplus
extern "C" {
#endif


//F109F361-370C-4d9c-B1AB-7CA2D4C8B3FF
#define AMI_CPU_INFO_PROTOCOL_GUID \
	{0xf109f361,0x370c,0x4d9c,0xb1,0xab,0x7c,0xa2,0xd4,0xc8,0xb3,0xff}

typedef struct _AMI_CPU_INFO_PROTOCOL AMI_CPU_INFO_PROTOCOL;

typedef	struct {
	UINT8	Desc;
	UINT8	Level;
	UINT8	Type;	//0 - Data, 1 - Instruction, 3 - Unified
	UINT32	Size;
	UINT8	Associativity;
} CACHE_DESCRIPTOR_INFO;


typedef struct {
	UINT32	Version;
	UINT64	Features;
	CHAR8	*BrandString;
    BOOLEAN X64Supported;
	UINT8	NumCores;           //Number of Cores. Ex. If Dual core, 2 cores.
	UINT8	NumHts;             //Number of Hyper threading. This will be 0 or 2. 
	UINT32	FSBFreq;			//MT/s
	UINT32	IntendedFreq;		//MHz
	UINT32	ActualFreq;			//MHz
	UINT32	Voltage;			// Volt / 10000.
	UINT32	MicroCodeVers;
	CACHE_DESCRIPTOR_INFO	*CacheInfo;
    BOOLEAN Ht0;                //Set if core is hyper-threadding logical CPU.
                                //True, if not-hyperthreaded CPU.
} AMI_CPU_INFO;


//CPU = 0, 1, 2, ... 
//CPU number is ordered by APIC ID.
//The CPUs are also ordered (because APIC ID) that
//  for example if dual core hyper-threading then
//  CPU 0 = CORE0, HT0
//  CPU 1 = CORE0, HT1
//  CPU 2 = CORE1, HT0
//  CPU 3 = CORE1, HT1
typedef EFI_STATUS (*GET_CPU_INFO) (
	IN AMI_CPU_INFO_PROTOCOL	*This,
	IN UINTN					Cpu,
	OUT AMI_CPU_INFO			**Info
);

struct _AMI_CPU_INFO_PROTOCOL {
	GET_CPU_INFO	GetCpuInfo;
};



/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
