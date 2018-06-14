//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/NvramSmi/NvramSmi.c 3     4/16/14 3:02a Chaseliu $
//
// $Revision: 3 $
//
// $Date: 4/16/14 3:02a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/NvramSmi/NvramSmi.c $
// 
// 3     4/16/14 3:02a Chaseliu
// [TAG]           EIP161860
// [Category]      Improvement
// [Description]   Upadte NvramSmi 05 Handle initialized with NULL.
// [Files]
// Core\EM\NvramSmi\NvramSmi.c
// 
// 18    4/02/14 10:33a Oleksiyy
// [TAG]  		EIP161860
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Dummy protocol do not installs
// [RootCause]  	DummyHandle was not preinitialized with NULL.
// [Solution]  	Initialize Handle with NULL.
// [Files]  		NvramSmi.c
// 
// 17    3/05/14 4:52p Oleksiyy
// [TAG]  		EIP154299
// [Category]  	Improvement
// [Description]  	Integer + heap potential overflow in SetVariable
// patched.
// [Files]  		NvramSmi.c
// 
// 16    4/02/13 6:19p Oleksiyy
// [TAG]  		EIP119970
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	NvramSmi handling of very big variable bug
// [RootCause]  	Out of resources  status returned without enabling
// interrupts and Smi (previously disabled by call to
// NvSmiBeginCriticalSection).
// [Solution]  	Check for size and retutning out of resources moved prior
// to disablig  interrupts and Smi  in NvSmiBeginCriticalSection.
// [Files]  		NvramSmi.c
// 
// 15    12/13/12 4:39p Oleksiyy
// [TAG]  		EIP109427
// [Category]  	Improvement
// [Description]  	Issues found by CppCheck in NvramSmi eModule.
// [Files]  		NvramSmi.c
// 
// 14    11/28/12 3:19p Oleksiyy
// [TAG]  		EIP106304
// [Category]  	Improvement
// [Description]  	Do not need to publish Dummy protocoll if
// PI_SPECIFICATION_VERSION<0x1000A.
// [Files]  		NvramSmi.c
// 
// 13    11/07/12 5:41p Oleksiyy
// [TAG]  		EIP98678
// [Category]  	Improvement
// [Description]  	GetVariable()  response slow. Added token to process
// only SetVariable through SMI.
// [Files]  		NvramSmi.c, NvramSmi.sdl and NVRAM.mak
// 
// 12    10/29/12 4:04p Oleksiyy
// [TAG]  		EIP102428
// [Category]  	Improvement
// [Description]  	Suse 11 SP2 can't boot successfully with uEFI mode and
// Xen kernel.
// Os cant handle optimized comands. Switch back to Memcopy.
// [Files]  		NvramSmi.c
// 
// 11    8/09/12 11:14a Oleksiyy
// [TAG]  		EIP96125
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System will hang on when GetVariable in SMM
// [RootCause]  	pSmmBase->InSmm was destriyed during RT.
// [Solution]  	Check for Legacy Boot Event added.
// [Files]  		NvramSmi.c
// 
// 10    5/22/12 3:46p Oleksiyy
// [TAG]  		EIP89155
// [Category]  	Improvement
// [Description]  	Implementing review comments
// [Files]  		NvraSmi.c and NvramSmi.sdl
// 
// 9     5/08/12 5:54p Oleksiyy
// [TAG]  		EIP89155
// [Category]  	Improvement
// [Description]  	NVRAM SMI module does not boot in PI 1.2
// [Files]  		NvramSmi.c, NvramSmi.sdl and NvramSmi.dxs
// 
// 8     4/20/12 5:26p Oleksiyy
// [TAG]  		EIP88363
// [Category]  	Bug Fix
// [Symptom]  	Build error in NvramSmi when
// PI_SPECIFICATION_VERSION<0x0001000A
// [RootCause]  	Variable Virtual was declared dependent from
// PI_SPECIFICATION_VERSION by mistake.
// [Solution]  	Dependency from PI_SPECIFICATION_VERSION removed.
// [Files]  		NvramSmi.c
// 
// 7     4/10/12 12:29p Oleksiyy
// [TAG]  		EIP86642
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	bios post will hang after add the NVRAMSMI module on
// Mahobay CRB19
// [RootCause]  	pSmmBase do not exist in PI mode during runtime.
// [Solution]  	Do not acces pSmmBase after going Virtual.
// [Files]  		NvramSmi.c
// 
// 6     3/29/12 11:06a Oleksiyy
// [TAG]  		EIP85100
// [Category]  	Improvement
// [Description]  	Added handling of using
// gST->RuntimeServices->GetVariable from SMM
// 
// 
// [Files]  		NvramSmi.c
// 
// 5     1/13/12 12:27p Oleksiyy
// [TAG]  		EIP80096
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	EFI Shell 'time' command hangs on Rose City CRB with label
// 15 BIOS
// [RootCause]  	Memory overwriten if too long VariableLength parameter is
// passed to GatVariable function in NvramSmi.c.
// [Solution]  	Implementing review comments.
// [Files]  	NvramSmi.c
// 
// 4     1/10/12 5:26p Oleksiyy
// [TAG]  		EIP80096
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	EFI Shell 'time' command hangs on Rose City CRB with label
// 15 BIOS
// [RootCause]  	Memory overwriten if too long VariableLength parameter is
// passed to GatVariable function in NvramSmi.c.
// [Solution]  	Check for too long VariableLength parameter is added to
// GatVariable function in NvramSmi.c. too long VariableLength parameter
// is added to GatVariable function in NvramSmi.c.
// [Files]  		NvramSmi.c, NvramSmi.sdl
// 
// 3     12/09/11 4:02p Oleksiyy
// [TAG]  		EIP77762 
// [Category]  	Improvement
// [Description]  	Create a initial label for a created NvramSmi eModule.
// [Files]  		All files in eModule.
// 
// 2     11/14/11 5:14p Oleksiyy
// Dependency from Core Ver added.
// 
// 1     11/11/11 3:41p Oleksiyy
// Initial CheckIn
// 
// 1     11/11/11 3:33p Oleksiyy
// 
// 3     6/27/11 6:46p Alexp
// 
// 2     6/24/11 5:03p Alexp
// add SecFlash OFBD module
// upgrade Security modules. use individual module label histories for
// detalis
// 
// 1     6/10/11 1:01p Alexp
// 
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: NvramSmi.c
//
// Description: NVRAM SMI DXE driver.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#include "NVRAM.h"

EFI_RUNTIME_SERVICES *SmmpRs = NULL;
EFI_GUID SmmRtServTableGuid = EFI_SMM_RUNTIME_SERVICES_TABLE_GUID; 
BOOLEAN ExitBS = FALSE;

#if  PI_SPECIFICATION_VERSION>=0x0001000A
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmCommunication.h>
EFI_HANDLE  VarSmiHandle = NULL;
EFI_SMM_COMMUNICATION_PROTOCOL *SmmCommProtocol = NULL;
EFI_GUID gEfiSmmCommunicationProtocolGuid = EFI_SMM_COMMUNICATION_PROTOCOL_GUID;

EFI_SMM_BASE2_PROTOCOL      *InternalSmmBase2 = NULL;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   LocateCommunicateProt
//
//  Description: This function will be called to locate Smm Communication Protocol
//
//  Input:  IN EFI_EVENT Event - signalled event
//          IN VOID *Context - calling context
//
//  Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LocateCommunicateProt (
            IN EFI_EVENT    Event, 
            IN VOID         *Context
)
{
    
    if (SmmCommProtocol != NULL) 
        return EFI_SUCCESS;

    return (pBS->LocateProtocol ( &gEfiSmmCommunicationProtocolGuid, 
                                   NULL, 
                                   &SmmCommProtocol ));
 
}

#endif
//----------------------------------------------------------------------------
// Function Externs

//----------------------------------------------------------------------------
// Local prototypes
typedef struct
{
    UINT32      Signature;
    UINT32      VarAttrib;
    EFI_GUID    VarGuid;
    UINTN       VarSize;
    EFI_STATUS  Status;
    UINT8       Subfunction;
    UINT64      MaxVarStorageSize;
    UINT64      RemVarStorageSize;
    UINT64      MaxVarSize;
    UINT8       VarData;

} SMI_VARIABLE;

typedef struct
{
    BOOLEAN Busy;
    UINT8   IntState[2];

} NVRAM_SMI_CRITICAL_SECTION;

//----------------------------------------------------------------------------
// Local Variables
#define NVRAM_SMI_GUID \
{0x29C31B9F, 0xD2B9, 0x4900, 0xBD, 0x2A, 0x58, 0x4F, 0x29, 0x12, 0xE3, 0x86}
#define BDS_CONNECT_DRIVERS_PROTOCOL_GUID \
{0x3aa83745, 0x9454, 0x4f7a, 0xa7, 0xc0, 0x90, 0xdb, 0xd0, 0x2f, 0xab, 0x8e}

#define NVRAM_SW_SMI 0x2b
#define SMI_SET_VARIABLE        2
#if NVRAM_SMI_FULL_PROTECTION == 1
#define SMI_GET_VARIABLE        1
#define SMI_GET_NEXT_VAR_NAME   3
#define SMI_QUERY_VAR_INFO      4
#endif
EFI_GUID    gNvramSmiGuid = NVRAM_SMI_GUID;
VOID        *gNvramBuffer = NULL;
EFI_EVENT   EvtNvramSmi;
VOID        *RegNvramSmi;
NVRAM_SMI_CRITICAL_SECTION NvramSmiCs = {FALSE, {0, 0}};

#if  PI_SPECIFICATION_VERSION>=0x0001000A
EFI_SMM_COMMUNICATE_HEADER CommHeader = {NVRAM_SMI_GUID, 1 , {0}};
VOID *CommHeaderPtr;
#endif
//----------------------------------------------------------------------------
// Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BeginCriticalSection
//
// Description: This function calls when critical section begins. It disables interupts, 
//              and Smi and fills CRITICAL_SECTION structure fields
//
// Input:       CRITICAL_SECTION *Cs - pointer to CRITICAL_SECTION structure
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
NvSmiBeginCriticalSection (
    NVRAM_SMI_CRITICAL_SECTION      *Cs
)
{
    if (Cs->Busy) return EFI_ACCESS_DENIED;
    Cs->IntState[0] = IoRead8(0x21);
    Cs->IntState[1] = IoRead8(0xa1);
    IoWrite8 (0x21, 0xff);
    IoWrite8 (0xa1, 0xff);
    Cs->Busy = TRUE;
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EndCriticalSection
//
// Description: This function calls when critical section ends. It enable interupts, 
//              and Smi and fills CRITICAL_SECTION structure fields
//
// Input:       CRITICAL_SECTION *Cs - pointer to CRITICAL_SECTION structure
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
NvSmiEndCriticalSection (
    NVRAM_SMI_CRITICAL_SECTION      *Cs
)
{
    Cs->Busy = FALSE;
    IoWrite8 (0x21, Cs->IntState[0]);
    IoWrite8 (0xa1, Cs->IntState[1]);
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EndCriticalSection
//
// Description: TThis function initiates communication between VAR services outside 
//      of SMM and SMI handlers inside of SMM. With the help of Smm Communication 
//      Protocol, if it is present, or direct I/O write, if not.
//
// Input:       None
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitCommunicate ()
{
#if PI_SPECIFICATION_VERSION>=0x0001000A

    UINTN CommSize = sizeof(EFI_SMM_COMMUNICATE_HEADER);


    if (SmmCommProtocol)
        SmmCommProtocol->Communicate (SmmCommProtocol, CommHeaderPtr, &CommSize);
    else
#endif
        IoWrite8 (SW_SMI_IO_ADDRESS, NVRAM_SW_SMI);
    return;
}

VOID GetSmmRsPtr()
{
    if (SmmpRs == NULL) 
        SmmpRs = GetSmstConfigurationTable(&SmmRtServTableGuid);
    return;
}

#if NVRAM_SMI_FULL_PROTECTION == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetVariableToSmi
//
// Description: This function searches for Var with specific GUID and Name
//
// Input:       IN CHAR16 *VariableName - pointer to Var Name in Unicode
//              IN EFI_GUID *VendorGuid - pointer to Var GUID
//              OPTIONAL OUT UINT32* Attributes - Pointer to memory where Attributes will be returned 
//              IN OUT UINTN *DataSize - size of Var - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              OUT VOID *Data - Pointer to memory where Var will be returned
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetVariableToSmi (
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes OPTIONAL,
    IN OUT UINTN *DataSize, OUT VOID *Data
)
{
    EFI_STATUS          Status;
    UINTN               Length;
    SMI_VARIABLE        *Buffer;
    BOOLEAN				InSmm = FALSE;
    //TRACE((-1,"GetVariableToSmi. Name %S\n", VariableName));
    if (!VariableName || !VendorGuid || !DataSize || !Data && *DataSize)
        return EFI_INVALID_PARAMETER;
    Length = (Wcslen(VariableName) + 1)*sizeof(CHAR16);
    if ((NVRAM_SIZE - sizeof(SMI_VARIABLE)) <=  Length)
        return EFI_OUT_OF_RESOURCES;
    Status = EFI_NO_RESPONSE;
    if (gNvramBuffer != NULL) {
        if (EFI_ERROR(NvSmiBeginCriticalSection(&NvramSmiCs))) 
            return EFI_ACCESS_DENIED;
        Buffer = (SMI_VARIABLE*)gNvramBuffer;

        Buffer->Subfunction = SMI_GET_VARIABLE;
        Buffer->Signature = NVAR_SIGNATURE;
        if (Attributes) Buffer->VarAttrib = *Attributes;
        Buffer->VarSize = *DataSize;
        Buffer->Status = Status;
        MemCpy(&Buffer->VarGuid, VendorGuid, sizeof(EFI_GUID));
        MemCpy((UINT8*)&Buffer->VarData, (UINT8*)VariableName, Length);
        if (!ExitBS)
            pSmmBase->InSmm(pSmmBase, &InSmm);
        if (!InSmm)
            InitCommunicate ();
        else
        {   
	        Status = EFI_SECURITY_VIOLATION;  
            if (pRS->GetVariable == GetVariableToSmi)
            {  
		        if (pSmst==NULL)
		        {
                    pSmmBase->GetSmstLocation(pSmmBase,&pSmst);
   		        } 	
                GetSmmRsPtr(); 
                if (SmmpRs != NULL)
		        {  
                Status = SmmpRs->GetVariable(VariableName, VendorGuid,
                                                Attributes, DataSize, Data);
   		        }  
            }       
            NvSmiEndCriticalSection (&NvramSmiCs);
	        return Status;	
        }
        Status = Buffer->Status;
        if (Status != EFI_NO_RESPONSE) {

            if (Status == EFI_BUFFER_TOO_SMALL) *DataSize = Buffer->VarSize;
            if (!EFI_ERROR(Status)) {

                if (Attributes) *Attributes = Buffer->VarAttrib;
                *DataSize = Buffer->VarSize;
                MemCpy((UINT8*)Data, &Buffer->VarData, Buffer->VarSize);
            }    
        }

        NvSmiEndCriticalSection (&NvramSmiCs);
    }       
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetNextVariableNameToSmi
//
// Description: This function searches for next Var after Var with specific name and GUID and returns it's Name
//              in SMM synchronizing Varstors before and after operation. 
//
// Input:       IN OUT UINTN *VariableNameSize - size of Varname - if smaller than actual EFI_BUFFER_TOO_SMALL 
//              will be returned and DataSize will be set to actual size needed
//              IN OUT CHAR16 *VariableName - pointer where Var Name in Unicode will be stored
//              IN OUT EFI_GUID *VendorGuid - pointer to menory where Var GUID is stored
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetNextVariableNameToSmi (
    IN OUT UINTN *VariableNameSize,
    IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid
)
{
    EFI_STATUS          Status;
    UINTN               Length;
    SMI_VARIABLE        *Buffer;
    BOOLEAN				InSmm = FALSE;
    //TRACE((-1,"GetNextVariableNameToSmi. Name %S\n", VariableName));
    if ( !VariableNameSize || !VariableName || !VendorGuid)
        return EFI_INVALID_PARAMETER;
    Status = EFI_NO_RESPONSE;
    if (gNvramBuffer != NULL) {
        if (EFI_ERROR(NvSmiBeginCriticalSection(&NvramSmiCs))) 
            return EFI_ACCESS_DENIED;

        Length = (Wcslen(VariableName) + 1)*sizeof(CHAR16);
        Buffer = (SMI_VARIABLE*)gNvramBuffer;
        Buffer->Subfunction = SMI_GET_NEXT_VAR_NAME;
        Buffer->Signature = NVAR_SIGNATURE;
        Buffer->VarSize = *VariableNameSize;
        Buffer->Status = Status;
        MemCpy(&Buffer->VarGuid, VendorGuid, sizeof(EFI_GUID));
        
        MemCpy((UINT8*)&Buffer->VarData, (UINT8*)VariableName, Length);
        if (!ExitBS)
            pSmmBase->InSmm(pSmmBase, &InSmm);
        if (!InSmm)
            InitCommunicate ();
        else
        {   
	        Status = EFI_SECURITY_VIOLATION;  
            if (pRS->GetNextVariableName == GetNextVariableNameToSmi)
            {
		        if (pSmst==NULL)
		        {
                    pSmmBase->GetSmstLocation(pSmmBase,&pSmst);
   		        } 	
                GetSmmRsPtr(); 
                if (SmmpRs != NULL)
		        {  
                Status = SmmpRs->GetNextVariableName(VariableNameSize, VariableName,VendorGuid);
   		        }  
            }       
            NvSmiEndCriticalSection (&NvramSmiCs);
	        return Status;	
        }

        Status = Buffer->Status;
        if (Status != EFI_NO_RESPONSE) {

            *VariableNameSize = Buffer->VarSize;
            if (!EFI_ERROR(Status)) {

                MemCpy((UINT8*)VariableName, &Buffer->VarData, Buffer->VarSize);
                MemCpy((UINT8*)VendorGuid, (UINT8*)&Buffer->VarGuid, sizeof(EFI_GUID));
            }    
        }

        NvSmiEndCriticalSection (&NvramSmiCs);
    }       

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   QueryVariableInfoToSmi
//
// Description: This function returns parameters of VarStore with passed attributes
//
// Input:       IN UINT32 Attributes - Atributes to search for
//              OUT UINT64 *MaximumVariableStorageSize - Maximum Variable Storage Size
//              OUT UINT64 *RemainingVariableStorageSize - Remaining Variable Storage Size
//              OUT UINT64 *MaximumVariableSize - Maximum Variable Size
//
// Output:      EFI_STATUS based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS QueryVariableInfoToSmi (
    IN UINT32 Attributes,
    OUT UINT64 *MaximumVariableStorageSize,
    OUT UINT64 *RemainingVariableStorageSize,
    OUT UINT64 *MaximumVariableSize
)
{
    
    EFI_STATUS          Status;
    SMI_VARIABLE        *Buffer;
    BOOLEAN				InSmm = FALSE;
    if (!Attributes || !MaximumVariableStorageSize || !RemainingVariableStorageSize || !MaximumVariableSize)
        return EFI_INVALID_PARAMETER;
    //TRACE((-1, "QueryVariableInfoToSmi.\n"));
    Status = EFI_NO_RESPONSE;
    if (gNvramBuffer != NULL) { 
        if (EFI_ERROR(NvSmiBeginCriticalSection(&NvramSmiCs))) 
            return EFI_ACCESS_DENIED;
        Buffer = (SMI_VARIABLE*)gNvramBuffer;

        Buffer->Subfunction = SMI_QUERY_VAR_INFO;
        Buffer->Signature = NVAR_SIGNATURE;
        Buffer->VarAttrib = Attributes;
        if (!ExitBS)
            pSmmBase->InSmm(pSmmBase, &InSmm);
        if (!InSmm)
            InitCommunicate ();
        else
        {   
	        Status = EFI_SECURITY_VIOLATION;  
            if (pRS->QueryVariableInfo == QueryVariableInfoToSmi)
            {
		        if (pSmst==NULL)
		        {
                    pSmmBase->GetSmstLocation(pSmmBase,&pSmst);
   		        } 	
                GetSmmRsPtr(); 
                if (SmmpRs != NULL)
		        {  
                Status = SmmpRs->QueryVariableInfo(Attributes, MaximumVariableStorageSize,
                                                RemainingVariableStorageSize, MaximumVariableSize);
   		        }  
            }       
            NvSmiEndCriticalSection (&NvramSmiCs);
	        return Status;	
        }

        Status = Buffer->Status;
        if (!EFI_ERROR(Status)) {
            *MaximumVariableStorageSize = Buffer->MaxVarStorageSize;
            *RemainingVariableStorageSize = Buffer->RemVarStorageSize;
            *MaximumVariableSize = Buffer->MaxVarSize;
        }

        NvSmiEndCriticalSection(&NvramSmiCs);
    }

    return Status;
}

#endif //#if NVRAM_SMI_FULL_PROTECTION == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetVariableToSmi
//
// Description: This function sets Var with specific GUID, Name and attributes
//              beginning and ending critical section. 
//
// Input:       IN CHAR16 *VariableName - pointer to Var Name in Unicode
//              IN EFI_GUID *VendorGuid - pointer to Var GUID
//              IN UINT32 Attributes - Attributes of the Var
//              IN UINTN DataSize - size of Var
//              IN VOID *Data - Pointer to memory where Var data is stored
//
// Output:      EFI_STATUS - based on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetVariableToSmi (
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    IN UINT32 Attributes, IN UINTN DataSize, IN VOID *Data
)
{
    EFI_STATUS          Status;
    UINTN               Length;
    SMI_VARIABLE        *Buffer;
    BOOLEAN				InSmm = FALSE;
    //TRACE((-1,"SetVariableToSmi. Name %S\n", VariableName));
    if (!VariableName || VariableName[0]==0 || !VendorGuid || (DataSize && !Data)) 
        return EFI_INVALID_PARAMETER;

    Length = (Wcslen(VariableName) + 1)*sizeof(CHAR16);
    if (((UINTN)(~0) - DataSize) < Length)
      return EFI_OUT_OF_RESOURCES; // Prevent whole variable size overflow (if DataSize + Length > UINTN)

    if ((DataSize + Length) > (NVRAM_SIZE - sizeof(SMI_VARIABLE)))
    	return EFI_OUT_OF_RESOURCES;

    Status = EFI_NO_RESPONSE;
    if (gNvramBuffer != NULL) { 

        if (EFI_ERROR(NvSmiBeginCriticalSection(&NvramSmiCs))) 
            return EFI_ACCESS_DENIED;

        Buffer = (SMI_VARIABLE*)gNvramBuffer;
        
        Buffer->Subfunction = SMI_SET_VARIABLE;
        Buffer->Signature = NVAR_SIGNATURE;
        Buffer->VarAttrib = Attributes;
        Buffer->VarSize = DataSize;
        Buffer->Status = Status;
        MemCpy(&Buffer->VarGuid, VendorGuid, sizeof(EFI_GUID));

        MemCpy(((UINT8*)&Buffer->VarData + DataSize), (UINT8*)VariableName, Length);
        MemCpy(&Buffer->VarData, (UINT8*)Data, DataSize);
        if (!ExitBS)
            pSmmBase->InSmm(pSmmBase, &InSmm);
        if (!InSmm)
            InitCommunicate ();
        else
        {   
	        Status = EFI_SECURITY_VIOLATION;  
            if (pRS->SetVariable == SetVariableToSmi)
            {
		        if (pSmst==NULL)
		        {
                    pSmmBase->GetSmstLocation(pSmmBase,&pSmst);
   		        } 	
                GetSmmRsPtr(); 
                if (SmmpRs != NULL)
		        {  
                Status = SmmpRs->SetVariable(VariableName, VendorGuid,
                                                Attributes, DataSize, Data);
   		        }  
            }       
            NvSmiEndCriticalSection (&NvramSmiCs);
	        return Status;	
        }

        Status = Buffer->Status;

        NvSmiEndCriticalSection(&NvramSmiCs);
//TRACE((-1, "[ SmiSetVariable - %S %r , Data=%x]\n",VariableName, Status, Data));
    }

    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   NvramSmiReadyToBoot
//
//  Description: This function will be called when Ready To Boot will signaled
//  will update data to work in RunTime.
//
//  Input:  IN EFI_EVENT Event - signalled event
//          IN VOID *Context - calling context
//
//  Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NvramSmiReadyToBoot (
    IN EFI_EVENT    Event, 
    IN VOID         *Context
)
{
    UINT32 CRC32=0;
#if NVRAM_SMI_FULL_PROTECTION == 1	
#if CORE_COMBINED_VERSION > 0x4028b
    typedef struct
    {
        BOOLEAN StopRtDataAccess;
        //TODO: there are more field inthe mailbox.
        // we assume that StopRtDataAccess will always be the first field.
    } NVRAM_MAILBOX;

    #define NVRAM_MAILBOX_ADDRESS_VARIABLE_GUID \
        {0x54913a6d, 0xf4ee, 0x4cdb, 0x84, 0x75, 0x74, 0x6, 0x2b, 0xfc, 0xec, 0xf5}
    
    static EFI_GUID NvRamMailboxVariableGuid = NVRAM_MAILBOX_ADDRESS_VARIABLE_GUID;
    NVRAM_MAILBOX *NvRamMailbox;
    EFI_STATUS  Status;
    UINTN       Size=sizeof(NvRamMailbox);

    Status = pRS->GetVariable(
        L"NvRamMailbox",&NvRamMailboxVariableGuid,
        NULL, &Size, &NvRamMailbox
    );     
    if (EFI_ERROR(Status)) return ;

    NvRamMailbox->StopRtDataAccess = TRUE;
    //Make a dummy SMM GetVariable call to process StopRtDataAccess
    GetVariableToSmi(
        L"NvRamMailbox",&NvRamMailboxVariableGuid,
        NULL, &Size, &NvRamMailbox
    );
#endif
#endif //#if NVRAM_SMI_FULL_PROTECTION == 1

    //Init CommHeaderPtr----

    if (gNvramBuffer == NULL) return;
#if PI_SPECIFICATION_VERSION>=0x0001000A
    CommHeaderPtr = &CommHeader;
#endif
    TRACE((-1, "[ NvramSmi-ReadyToLock ]\n"));
    pRS->SetVariable = SetVariableToSmi;
#if NVRAM_SMI_FULL_PROTECTION == 1
    pRS->GetVariable = GetVariableToSmi;
    pRS->GetNextVariableName = GetNextVariableNameToSmi; 
    pRS->QueryVariableInfo = QueryVariableInfoToSmi;
#endif //#if NVRAM_SMI_FULL_PROTECTION == 1 
    pRS->Hdr.CRC32 = 0;
    pBS->CalculateCrc32(pRS, sizeof(*pRS), &CRC32);
    pRS->Hdr.CRC32 = CRC32;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   NvramSmiVirtualFixup
//
//  Description: Called on Virtual address change event and converts 
//               SmmCommProtocol pointer.
//
//  Input:  IN EFI_EVENT Event - signalled event
//          IN VOID *Context - calling context
//
//  Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NvramSmiVirtualFixup (
    IN EFI_EVENT    Event, 
    IN VOID         *Context
)
{
    //TRACE((-1, "NvramSmi-Go Virtual\n"));
    pRS->ConvertPointer (0, &gNvramBuffer);
#if PI_SPECIFICATION_VERSION>=0x0001000A
    if (SmmCommProtocol != NULL)
        pRS->ConvertPointer (0, (VOID**)&SmmCommProtocol);
#endif

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   NvramSmiVirtualFixup
//
//  Description: Called on Exit BS and updates ExitBS variable 
//              
//
//  Input:  IN EFI_EVENT Event - signalled event
//          IN VOID *Context - calling context
//
//  Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NvramSmiExitBs (
    IN EFI_EVENT    Event, 
    IN VOID         *Context
)
{
    ExitBS = TRUE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NotInSmmFunction
//
// Description: This is the "NotInSmmFunction" parameter for the 
//              InitSmmHandler function in the entry point. It allocates 
//              memory for parameters buffer, saves its location, etc.
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NotInSmmFunction(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS  Status;
    EFI_EVENT   EvtReadyToBoot, EvtExitBS;
#if  PI_SPECIFICATION_VERSION>=0x0001000A  
    EFI_EVENT   EvtComm;
#endif
    VOID        *RegReadyToBoot, *RegComm;
    static EFI_GUID    StartNvramSmiServicesGuid = NVRAM_START_SMI_SERVICES_GUID;
    static EFI_GUID    DummyProtocolGuid = { 0xc35f952, 0x5791, 0x4667, { 0xad, 0xe4, 0x1c, 0xfd, 0xa8, 0x37, 0x72, 0x2d } };
    EFI_HANDLE  DummyHandle = NULL;

    //TRACE((-1,"SmiNVRAM NotInSmmFunction.\n"));
    gNvramBuffer = NULL;
    Status = pBS->AllocatePool ( EfiRuntimeServicesData, 
                                 NVRAM_SIZE, 
                                 &gNvramBuffer );
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    Status = pRS->SetVariable ( L"NvramSmiBuffer", 
                                &gNvramSmiGuid, 
                                EFI_VARIABLE_BOOTSERVICE_ACCESS, 
                                sizeof(gNvramBuffer), 
                                &gNvramBuffer  );
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    InitAmiRuntimeLib(
                    ImageHandle, SystemTable, NvramSmiExitBs, NvramSmiVirtualFixup
                    );
    CreateLegacyBootEvent(TPL_CALLBACK, &NvramSmiExitBs, NULL, &EvtExitBS);
    Status = RegisterProtocolCallback ( &StartNvramSmiServicesGuid, 
                                        NvramSmiReadyToBoot, 
                                        NULL, 
                                        &EvtReadyToBoot, 
                                        &RegReadyToBoot );
    ASSERT_EFI_ERROR (Status);
#if  PI_SPECIFICATION_VERSION>=0x0001000A    
    Status = LocateCommunicateProt (NULL, NULL);

    if (EFI_ERROR(Status)){

        Status = RegisterProtocolCallback ( &gEfiSmmCommunicationProtocolGuid, 
                                            LocateCommunicateProt, 
                                            NULL, 
                                            &EvtComm, 
                                            &RegComm );
    }
    //---Installing a Dummy protocol, on which Smm part is relying to make sure 
    //---InSmm function will start after NotInSmm
    pBS->InstallProtocolInterface (
        &DummyHandle, &DummyProtocolGuid, EFI_NATIVE_INTERFACE, NULL
    );
#endif
    return Status;    
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NvramSmiHandler
//
// Description: The SMI handler for Nvram services.
//
// Input:       NONE
//              
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NvramSmiHandler ()
{
    EFI_STATUS              Status = EFI_DEVICE_ERROR;
    SMI_VARIABLE            *SmmVarBuffer;

    SmmVarBuffer = (SMI_VARIABLE*)gNvramBuffer;

    if (SmmVarBuffer->Signature != NVAR_SIGNATURE) return Status;
    
    switch (SmmVarBuffer->Subfunction){

        case SMI_SET_VARIABLE:
        //TRACE((-1,"SmiNVRAM Handler. SMI_SET_VARIABLE \n"));
        Status = pRS->SetVariable ( (CHAR16*)((UINT8*)&SmmVarBuffer->VarData + SmmVarBuffer->VarSize), 
                                    &SmmVarBuffer->VarGuid, 
                                    SmmVarBuffer->VarAttrib, 
                                    SmmVarBuffer->VarSize, 
                                    &SmmVarBuffer->VarData);
        break;
#if NVRAM_SMI_FULL_PROTECTION == 1
        case SMI_GET_VARIABLE:
        //TRACE((-1,"SmiNVRAM Handler. SMI_GET_VARIABLE \n"));

        Status = pRS->GetVariable ( (CHAR16*) &SmmVarBuffer->VarData, 
                                    &SmmVarBuffer->VarGuid, 
                                    &SmmVarBuffer->VarAttrib, 
                                    &SmmVarBuffer->VarSize, 
                                    &SmmVarBuffer->VarData);
        break;

        case SMI_GET_NEXT_VAR_NAME:
        //TRACE((-1,"SmiNVRAM Handler. SMI_GET_NEXT_VAR_NAME \n"));
        Status = pRS->GetNextVariableName ( &SmmVarBuffer->VarSize, 
                                    (CHAR16*) &SmmVarBuffer->VarData, 
                                    &SmmVarBuffer->VarGuid);	
        break;

        case SMI_QUERY_VAR_INFO:
        //TRACE((-1,"SmiNVRAM Handler. SMI_QUERY_VAR_INFO \n"));
        Status = pRS->QueryVariableInfo ( SmmVarBuffer->VarAttrib, 
                                    &SmmVarBuffer->MaxVarStorageSize, 
                                    &SmmVarBuffer->RemVarStorageSize, 
                                    &SmmVarBuffer->MaxVarSize);	
        break;
#endif //#if NVRAM_SMI_FULL_PROTECTION == 1
        default: return Status;
	}
    //TRACE((-1,"SmiNVRAM Handler. END\n"));
    SmmVarBuffer->Status = Status;
    SmmVarBuffer->Subfunction = 0; 
    SmmVarBuffer->Signature = ~NVAR_SIGNATURE; 

    return Status;                                          
}


#if  PI_SPECIFICATION_VERSION>=0x0001000A
EFI_STATUS NvramSmiHandler1 (
  IN     EFI_HANDLE                                DispatchHandle,
  IN     CONST VOID                                *Context,
  IN OUT VOID                                      *CommBuffer,
  IN OUT UINTN                                     *CommBufferSize
  )
{

    if (gNvramBuffer == NULL) 
        return EFI_DEVICE_ERROR;
    
    return NvramSmiHandler();
    
}
#endif


EFI_STATUS NvramSmiHandler2 (
    IN  EFI_HANDLE                  DispatchHandle,
    IN  EFI_SMM_SW_DISPATCH_CONTEXT *DispatchContext
)

{

    if ((gNvramBuffer == NULL) || ((UINT8)DispatchContext->SwSmiInputValue != NVRAM_SW_SMI)) 
        return EFI_DEVICE_ERROR;
    return NvramSmiHandler();

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NvramSmiSmmSwDispatchCallback
//
// Description: This function registers SMI Handler for Nvram services
//
// Input:  IN EFI_EVENT Event - signalled event
//          IN VOID *Context - calling context
//              
// Output:  NONE    
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NvramSmiSmmSwDispatchCallback(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{

    EFI_SMM_SW_DISPATCH_PROTOCOL    *pSwDispatch;
    EFI_SMM_SW_DISPATCH_CONTEXT     SwContext;
    EFI_HANDLE                      Handle;
    EFI_STATUS                      Status;
    UINTN                           VariableSize = sizeof(gNvramBuffer);

    if(gNvramBuffer) return; // already came here once...

    Status = pBS->LocateProtocol ( &gEfiSmmSwDispatchProtocolGuid, 
                                   NULL, 
                                   &pSwDispatch );
    if (EFI_ERROR(Status)) return;

    Status = pRS->GetVariable ( L"NvramSmiBuffer", 
                                &gNvramSmiGuid, 
                                NULL, 
                                &VariableSize, 
                                &gNvramBuffer );
    if ((EFI_ERROR(Status)) || (gNvramBuffer == NULL)) return;

    SwContext.SwSmiInputValue = NVRAM_SW_SMI;
    Status  = pSwDispatch->Register ( pSwDispatch, 
                                      NvramSmiHandler2, 
                                      &SwContext, 
                                      &Handle );
    pBS->CloseEvent (Event);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: Registration of the SMI function.
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InSmmFunction(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS                      Status;

#if  PI_SPECIFICATION_VERSION>=0x0001000A

    EFI_SMM_SYSTEM_TABLE2       *pSmst2           = NULL;

#endif

    //TRACE((-1, "In NvramSmi InSmmFunction\n"));
    NvramSmiSmmSwDispatchCallback (EvtNvramSmi, RegNvramSmi);                                    

    Status = RegisterProtocolCallback ( &gEfiSmmSwDispatchProtocolGuid, 
                                        NvramSmiSmmSwDispatchCallback, 
                                        NULL, 
                                        &EvtNvramSmi, 
                                        &RegNvramSmi );

#if  PI_SPECIFICATION_VERSION>=0x0001000A

    Status = SystemTable->BootServices->LocateProtocol (
                                        &gEfiSmmBase2ProtocolGuid,
                                        NULL,
                                        (VOID **)&InternalSmmBase2
                                        );
    ASSERT_EFI_ERROR (Status);

    Status = InternalSmmBase2->GetSmstLocation (InternalSmmBase2, &pSmst2);
    ASSERT_EFI_ERROR (Status);
    ASSERT (pSmst2 != NULL);
    Status = pSmst2->SmiHandlerRegister(&NvramSmiHandler1, &gNvramSmiGuid, &VarSmiHandle);
    ASSERT_EFI_ERROR (Status);

#endif

    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NvramSmiEntryPoint
//
// Description: DXE Entry Point for NvramSmi Driver.
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
NvramSmiEntry (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
)
{

    InitAmiLib(ImageHandle, SystemTable);

    return InitSmmHandlerEx(
               ImageHandle, SystemTable, InSmmFunction, NotInSmmFunction
           );

}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
