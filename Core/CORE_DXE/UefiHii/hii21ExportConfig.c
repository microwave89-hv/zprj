//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/hii21ExportConfig.c $
//
// $Author: Artems $
//
// $Revision: 1 $
//
// $Date: 1/25/11 3:20p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/hii21ExportConfig.c $
// 
// 1     1/25/11 3:20p Artems
// 
// 
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		hii21ExportConfig.c
//
// Description:	This file contains code to perform the ExportConfig Operation of Config
//              roughting protocol.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


#include "token.h"
#include "efi.h"
//#include "devicepath.h"
#include <AmiDxeLib.h>

#ifndef EFI_PROTOCOL_DEFINITION
#define TSE_STRINGIZE(a) #a
#define EFI_PROTOCOL_DEFINITION(a) TSE_STRINGIZE(Protocol/a.h)
#endif

#include EFI_PROTOCOL_DEFINITION(HiiDatabase)
#include EFI_PROTOCOL_DEFINITION(HiiConfigRouting)
#include EFI_PROTOCOL_DEFINITION(devicepath)

typedef struct _VARSTORE_INFO
{
	EFI_GUID	VariableGuid;		//Varies	EFI_GUID for the NVRAM variable store for this data
    VOID*	    VariableHandle;	    //Varies	HII Handle to the formset that contains this VarStore
	UINT16		VariableSize;		//Varies	The size of Buffer Varstore
    struct _VARSTORE_INFO *Next;
	char 		*VariableName;	//Varies	Variable store name
}VARSTORE_INFO;


// Helper Functions
EFI_HII_DATABASE_PROTOCOL *gHiiDatabase;
EFI_BOOT_SERVICES 	*gBS;
EFI_HII_CONFIG_ROUTING_PROTOCOL * gHiiConfigRouting;

VARSTORE_INFO *gVarInfoHead = NULL;
VARSTORE_INFO *gpVarInfo;

EFI_HII_HANDLE *HiiGetHandles(UINT16 *NumberOfHiiHandles);
VOID * _HiiGetForm( EFI_HII_HANDLE Handle, UINTN *Length );
VOID _HiiGetVariable(EFI_HII_HANDLE Handle, UINT8 * buff);
EFI_STATUS GetVarStoreConfig(VARSTORE_INFO *VarInfo, EFI_STRING *result);
EFI_STATUS GetConfigHeader(VARSTORE_INFO *VarInfo, EFI_STRING *Configuration, UINTN *Length);
EFI_STATUS GetBlockName(EFI_STRING *Configuration, UINTN *Length, UINTN Size);
EFI_STATUS _VerifyResponseString(EFI_STRING Configuration, BOOLEAN NameValue);
EFI_STATUS _ConstructConfigHdr (
  IN OUT CHAR16                *ConfigHdr,
  IN OUT UINTN                 *StrBufferLen,
  IN EFI_GUID                  *Guid,
  IN CHAR16                    *Name, OPTIONAL
  IN EFI_HANDLE                *DriverHandle
  );

EFI_STATUS
BufferToHexString (
  IN OUT CHAR16    *Str,
  IN UINT8         *Buffer,
  IN UINTN         BufferSize
  );
EFI_STATUS
UnicodeToConfigString (
  IN OUT CHAR16                *ConfigString,
  IN OUT UINTN                 *StrBufferLen,
  IN CHAR16                    *UnicodeString
  );
VOID
SwapBuffer (
  IN OUT UINT8     *Buffer,
  IN UINTN         BufferSize
  );
EFI_STATUS
BufToHexString (
  IN OUT CHAR16                    *Str,
  IN OUT UINTN                     *HexStringBufferLength,
  IN     UINT8                     *Buf,
  IN     UINTN                      Len
  );
CHAR16
NibbleToHexChar (
  IN UINT8      Nibble
  );
VOID
ToLower (
  IN OUT CHAR16    *Str
  );
VOID StrCpy8(CHAR8 *dest, CHAR8 *src);
VOID
EfiStrCpy (
  IN CHAR16   *Destination,
  IN CHAR16   *Source
  );

VOID
EfiStrCat (
  IN CHAR16   *Destination,
  IN CHAR16   *Source
  );


//=== HELPER Functions ====================//
VOID *
EfiLibAllocatePool (
  IN  UINTN   AllocationSize
  )
{
	return Malloc(AllocationSize);
}

VOID *
EfiLibAllocateZeroPool (
  IN  UINTN   AllocationSize
  )
{
	return MallocZ(AllocationSize);
}

UINTN
EfiStrLen (
  IN CHAR16   *String
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemFreePointer
//
// Description:	function to free the pointers
//
// Input:		VOID **ptr
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MemFreePointer( VOID **ptr )
{
	if ( ( ptr == NULL ) || ( *ptr == NULL ) )
		return;

	gBS->FreePool( *ptr );
	*ptr = NULL;
}

UINTN StrLen8(CHAR8 *string)
{
    UINTN i=0;
    while(string[i])
        i++;

    return i;
}


CHAR8 *StrDup8( CHAR8 *string )
{
	CHAR8 *text;

	text = EfiLibAllocateZeroPool(1 + StrLen8( string ));
	if ( text != NULL )
		StrCpy8( text, string );

	return text;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemCopy
//
// Description:	function to copy a memory
//
// Input:		VOID *dest, VOID *src, UINTN size
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MemCopy( VOID *dest, VOID *src, UINTN size )
{
	gBS->CopyMem( dest, src, size );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemReallocateZeroPool
//
// Description:	function to reuse a allocated buffer
//
// Input:		VOID *oldBuffer, UINTN oldSize, UINTN newSize
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *MemReallocateZeroPool( VOID *oldBuffer, UINTN oldSize, UINTN newSize )
{
	VOID *buffer;

	buffer = EfiLibAllocateZeroPool( newSize );
	if ( buffer == NULL )
		return buffer;

	if ( newSize < oldSize )
		oldSize = newSize;

	if ( oldBuffer != NULL )
		MemCopy( buffer, oldBuffer, oldSize );

	MemFreePointer( (VOID **)&oldBuffer );

	return buffer;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    StrDup8to16
//
// Description: Duplicates a String from CHAR8 to CHAR16
//
// Input:	CHAR8* string	
//
// Output:	CHAR16 *
//              
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *StrDup8to16( CHAR8 *string )
{
	CHAR16  *text;
    UINTN   i;

	text = EfiLibAllocatePool( (1 + StrLen8( string )) * sizeof(CHAR16));
	if ( text != NULL )
    {
        i=0;
		while(text[i] = (CHAR16)string[i])
            i++;
    }

	return text;
}


INTN
EfiStrnCmp (
  IN CHAR16   *String,
  IN CHAR16   *String2,
  IN UINTN    Length
  )
/*++

Routine Description:
  This function compares the Unicode string String to the Unicode
  string String2 for len characters.  If the first len characters
  of String is identical to the first len characters of String2,
  then 0 is returned.  If substring of String sorts lexicographically
  after String2, the function returns a number greater than 0. If
  substring of String sorts lexicographically before String2, the
  function returns a number less than 0.

Arguments:
  String  - Compare to String2
  String2 - Compare to String
  Length  - Number of Unicode characters to compare

Returns:
  0     - The substring of String and String2 is identical.
  > 0   - The substring of String sorts lexicographically after String2
  < 0   - The substring of String sorts lexicographically before String2

--*/
{
  while (*String && Length != 0) {
    if (*String != *String2) {
      break;
    }
    String  += 1;
    String2 += 1;
    Length  -= 1;
  }
  return Length > 0 ? *String - *String2 : 0;
}

UINTN
EfiDevicePathSize (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{
	return DPLength(DevicePath);
}


VOID InitGlobels(VOID)
{
    gBS=pBS;
    gBS->LocateProtocol(&gEfiHiiDatabaseProtocolGuid, NULL, &gHiiDatabase);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: Hii21ExportConfigHelper
//
// Description: Helper function to perform ExportConfig Operation of Config
//              roughting protocol.
//
// Parameter: EFI_HII_CONFIG_ROUTING_PROTOCOL *This, IN EFI_HII_DATABASE_PROTOCOL *HiiDatabase,
//            OUT EFI_STRING *Results
//
// Return value: Status 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Hii21ExportConfigHelper (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    OUT EFI_STRING *Results
)
{
    EFI_HII_HANDLE *HiiHandleList;
    UINT16 NumberOfHiiHandles = 0;
    UINTN i;
    UINT8 *FormSet;
    UINT8 *ifrData;
    UINTN Length;
    EFI_STRING result=NULL;
	UINTN OldSize,NewSize;

    if(Results == NULL)
        return EFI_INVALID_PARAMETER;

	*Results = NULL;
    InitGlobels();
    gHiiConfigRouting = (EFI_HII_CONFIG_ROUTING_PROTOCOL*)This;

    // To get the All the Valid Hii Handles.
    HiiHandleList = HiiGetHandles(&NumberOfHiiHandles);
    gpVarInfo = gVarInfoHead = NULL;

    for(i=0;i<NumberOfHiiHandles;i++)
    {
        Length = 0;
        // To get the FormPackage
        FormSet = _HiiGetForm( HiiHandleList[i], &Length);
        // donot contain valid package.
        if(FormSet == NULL)
            continue;
        ifrData = (UINT8*)(FormSet + sizeof(EFI_HII_PACKAGE_HEADER));
        _HiiGetVariable(HiiHandleList[i], ifrData);

        // Free the FormPackage
        MemFreePointer(&FormSet);
    }


    gpVarInfo = gVarInfoHead;
	OldSize = NewSize = 0;
    while(  gpVarInfo != NULL )
    {
        VARSTORE_INFO *tmpVarInfo;
		EFI_STATUS Status;
		
		Status = GetVarStoreConfig(gpVarInfo, &result);
		if(!EFI_ERROR(Status))
		{
			NewSize = OldSize + (EfiStrLen(result)*2)+10;
			*Results = MemReallocateZeroPool(*Results, OldSize, NewSize);
			if(OldSize)
				EfiStrCat(*Results,L"&");
			EfiStrCat(*Results,result);
			MemFreePointer(&result);
			OldSize = NewSize;
		}

		MemFreePointer(&gpVarInfo->VariableName);
        tmpVarInfo = gpVarInfo;
        gpVarInfo = gpVarInfo->Next;
        MemFreePointer(&tmpVarInfo);
    }

    // free the Hii Handles
    MemFreePointer((VOID**)&HiiHandleList);
    return EFI_SUCCESS;
}


BOOLEAN IsVarStoreFound(EFI_HII_HANDLE Handle, EFI_IFR_VARSTORE *varstore)
{
	VARSTORE_INFO * VarInfo;
//    EFI_GUID SetupGuid	= SETUP_GUID;

    VarInfo = gVarInfoHead;
    while(  VarInfo != NULL )
    {
		if( MemCmp( (UINT8*)&VarInfo->VariableGuid,(UINT8*) &(varstore->Guid) , sizeof(EFI_GUID)) == 0)
			if(Strcmp(VarInfo->VariableName, (char*)varstore->Name) ==0)
            {
// In Aptio, There are many Variables used in multiple Vfr.

/*
// Setup Variable even if it differ handle the variable info is same.
                if( (MemCmp( (UINT8*)&VarInfo->VariableGuid,(UINT8*) &SetupGuid , sizeof(EFI_GUID)) == 0) &&
                    (Strcmp(VarInfo->VariableName, "Setup") == 0) )
                    return TRUE;                
// For not SETUP_DATA if the Handle is different it can be different Variable
                else if(VarInfo->VariableHandle == Handle)
*/
    				return TRUE;

            }
		VarInfo = VarInfo->Next;
    }
	return FALSE;
}

VOID _HiiGetVariable(EFI_HII_HANDLE Handle, UINT8 * buff)
{
	EFI_IFR_OP_HEADER *Header;
    UINTN ScopeCount = 0;
    EFI_IFR_VARSTORE *varstore;

	//go thru the forms get the variables.
	do
	{
		Header = (EFI_IFR_OP_HEADER*)(buff);
		switch(Header->OpCode )
		{
			case EFI_IFR_END_OP:
				ScopeCount--;
				break;

            case EFI_IFR_VARSTORE_OP:
                if(!IsVarStoreFound(Handle, (EFI_IFR_VARSTORE *)buff))
                {
                    if( gVarInfoHead == NULL)
                    {
                        gVarInfoHead = EfiLibAllocateZeroPool(sizeof(VARSTORE_INFO));
                        gVarInfoHead->Next = NULL;
                        gpVarInfo = gVarInfoHead;
                    }
                    else
                    {
                        gpVarInfo->Next = EfiLibAllocateZeroPool(sizeof(VARSTORE_INFO));
                        gpVarInfo = gpVarInfo->Next;
                        gpVarInfo->Next = NULL;
                    }
                    
            		varstore = (EFI_IFR_VARSTORE*)buff;
        
                    MemCopy(&gpVarInfo->VariableGuid, &(varstore->Guid), sizeof(EFI_GUID));
                    gpVarInfo->VariableHandle =  (VOID*)Handle;
                    gpVarInfo->VariableSize =  varstore->Size;
                    gpVarInfo->VariableName = StrDup8((char*)varstore->Name);
                }            
			default:
				if(Header->Scope)
				{
					ScopeCount++;
				}
		      break;

		}
       buff += Header->Length;
	}while(ScopeCount != 0);

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _HiiGetForm
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *_HiiGetForm( EFI_HII_HANDLE Handle, UINTN *Length )
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_HII_PACKAGE_HEADER *pkgHdr;
	EFI_IFR_OP_HEADER *opHeader = NULL;
	VOID *hiiFormPackage=NULL;
	UINT8 *formPkBuffer = NULL;
	UINT8 *pkgOffset;
	UINT8 end = 0;
	UINT32 offset = 0;
	UINTN len=10;
	//SETUP_LINK DummySetupLink;

	if(Length == NULL)
		Length = &len;

	hiiFormPackage = EfiLibAllocateZeroPool(*Length);

	status = gHiiDatabase->ExportPackageLists(gHiiDatabase, Handle, Length, hiiFormPackage);
	if(status == EFI_BUFFER_TOO_SMALL)
	{
		MemFreePointer(&hiiFormPackage);
		//
		// Allocate space for retrieval of IFR data
		//
		hiiFormPackage = EfiLibAllocateZeroPool(*Length);

		if (hiiFormPackage == NULL)
		{
			hiiFormPackage = NULL;
			goto DONE;
		}
		//
		// Get all the packages associated with this HiiHandle
		//
		status = gHiiDatabase->ExportPackageLists (gHiiDatabase, Handle, Length, hiiFormPackage);
		if(EFI_ERROR(status))
		{
			MemFreePointer(&hiiFormPackage);
			hiiFormPackage = NULL;
			goto DONE;
		}
	}else if(EFI_ERROR(status))
	{
		hiiFormPackage = NULL;
		goto DONE;
	}

  offset = sizeof(EFI_HII_PACKAGE_LIST_HEADER);

  while(offset < ((EFI_HII_PACKAGE_LIST_HEADER*)hiiFormPackage)->PackageLength)
  {
    pkgOffset = ((UINT8*)hiiFormPackage) + offset;
    pkgHdr = (EFI_HII_PACKAGE_HEADER*)pkgOffset;
    switch(pkgHdr->Type)
    {
    case EFI_HII_PACKAGE_FORMS:
      formPkBuffer = (UINT8*)EfiLibAllocateZeroPool(pkgHdr->Length);
      if(formPkBuffer == NULL)
      {
        goto DONE;
      }

      MemCopy(formPkBuffer, pkgHdr, pkgHdr->Length);
        
	  opHeader = (EFI_IFR_OP_HEADER*)((UINT8*)formPkBuffer + sizeof(EFI_HII_PACKAGE_HEADER));
	  if(opHeader->OpCode != EFI_IFR_FORM_SET_OP)
	  {
		MemFreePointer(&formPkBuffer);
		formPkBuffer = NULL;
		*Length = 0;
		goto DONE;
	  }

      end = 1;
      break;
    case EFI_HII_PACKAGE_END:
      end = 1;
      break;
    default:
      break;
    }
    if(end)
    {
      break;
    }
    offset += pkgHdr->Length;
  }

	MemFreePointer(&hiiFormPackage);

DONE:
	return formPkBuffer;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: HiiGetHandles
//
// Description: gets all the HII handles
//
// Parameter: No of handles
//
// Return value: EFI_HII_HANDLE *
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_HII_HANDLE *HiiGetHandles(UINT16 *NumberOfHiiHandles)
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_HII_HANDLE *hiiHandleBuffer = NULL;
	UINTN handleBufferLength = sizeof(EFI_HII_HANDLE);

	hiiHandleBuffer = EfiLibAllocatePool(handleBufferLength);

	status = gHiiDatabase->ListPackageLists (gHiiDatabase, EFI_HII_PACKAGE_TYPE_ALL, NULL,
					&handleBufferLength, hiiHandleBuffer);
	if (status == EFI_BUFFER_TOO_SMALL)
	{
		//
		// Free the old pool
		//
		MemFreePointer ((VOID**)&hiiHandleBuffer);
		//
		// Allocate new pool with correct value
		//
		hiiHandleBuffer = EfiLibAllocatePool(handleBufferLength);

		//
		// Get the Handles of the packages that were registered with Hii
		//
		gBS->SetMem(hiiHandleBuffer,handleBufferLength,0);
		status = gHiiDatabase->ListPackageLists (gHiiDatabase, EFI_HII_PACKAGE_TYPE_ALL,
					  NULL, &handleBufferLength, hiiHandleBuffer);

		if (EFI_ERROR (status))
		{
			MemFreePointer((VOID**)&hiiHandleBuffer);
			hiiHandleBuffer = NULL;
			goto DONE;
		}
	}else if(EFI_ERROR(status))
	{
		MemFreePointer((VOID**)&hiiHandleBuffer);
		hiiHandleBuffer = NULL;
		goto DONE;
	}

	*NumberOfHiiHandles = (UINT16)(handleBufferLength / sizeof(EFI_HII_HANDLE));

DONE:
	return hiiHandleBuffer;
}




EFI_STATUS GetVarStoreConfig(VARSTORE_INFO *VarInfo, EFI_STRING *result)
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_STRING configuration = NULL;
	EFI_STRING progress = NULL;
	//EFI_STRING result = NULL;
	//EFI_STRING stringPtr = NULL;
	UINTN length = 1;
	//UINT8 *buffer = NULL;

	configuration = EfiLibAllocateZeroPool(length);
	if(configuration == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

    //
    // Construct the Configuration Header String
    //
    status = GetConfigHeader(VarInfo, &configuration, &length);
	if(EFI_ERROR(status))
	{
		//TSE_DEBUG ( (TSE_DBG_LEVEL, "\nGetConfigHeader FAIL\n" ));
		goto DONE;
	}

/*	if(VariableInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE)
	{
	}else
*/
	{
		status = GetBlockName(&configuration, &length, VarInfo->VariableSize);
		if(EFI_ERROR(status))
		{
			//TSE_DEBUG ( (TSE_DBG_LEVEL, "\n GetBlockname FAIL\n" ));
			goto DONE;
		}
	}

	// Invoke Config Routing Route Config
	status = gHiiConfigRouting->ExtractConfig(gHiiConfigRouting, configuration, &progress, result);

	if(EFI_ERROR(status))
		*result = NULL;

	status = _VerifyResponseString(*result, /*(VariableInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE)? TRUE :*/ FALSE);

DONE:
  if(configuration)
  {
	MemFreePointer(&configuration);
  }

  return status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    _VerifyResponseString
//
// Description:   Verifies Correctness of Response String. This is to prevent
//				  crashing if the result pointer is pointing to an invalid location.
//
// Parameter:	    EFI_STRING *Configuration
//
// Return value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _VerifyResponseString(EFI_STRING Configuration, BOOLEAN NameValue)
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_STRING config = Configuration;
  CHAR16 *keyWord[] = {L"GUID=", L"&NAME=", L"&PATH=", L"&OFFSET=0&WIDTH=", L"&VALUE="};
  UINT32 i = 0;
  UINT32 count = NameValue? 3 : 5; // If Name Value Check only upto &Path else check until &Value.

  if(EfiStrnCmp(config, keyWord[i], EfiStrLen(keyWord[i])) != 0)
  {
    status = EFI_NOT_FOUND;
    goto DONE;
  }

  for(i = 1; i < count; i++)
  {
    for(;EfiStrnCmp(config, keyWord[i], EfiStrLen(keyWord[i])) != 0 && (config != (Configuration + EfiStrLen(Configuration))); config++)
      ;
    if(EfiStrnCmp(config, keyWord[i], EfiStrLen(keyWord[i])) != 0)
    {
      status = EFI_NOT_FOUND;
      goto DONE;
    }
  }

DONE:
  return status;
}



EFI_STATUS GetConfigHeader(VARSTORE_INFO *VarInfo, EFI_STRING *Configuration, UINTN *Length)
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_STRING configuration = NULL;
  EFI_HANDLE driverHandle;
  UINTN length = 0;
  CHAR16 *VarName=NULL;

  //
  // Retrieve the Device Path from Handle
  //
  status = gHiiDatabase->GetPackageListHandle(gHiiDatabase, VarInfo->VariableHandle, &driverHandle);
	if(EFI_ERROR(status))
	{
		goto DONE;
	}

  //
  // Construct the Configuration Header String
  //
  VarName = StrDup8to16(VarInfo->VariableName);
  status = _ConstructConfigHdr(configuration, &length, &VarInfo->VariableGuid, VarName, driverHandle);
  if(EFI_ERROR(status))
  {
    if(status == EFI_BUFFER_TOO_SMALL)
    {
      MemFreePointer(&configuration);
      configuration = (UINT16*)EfiLibAllocateZeroPool(length);
      if(configuration == NULL)
      {
        status = EFI_OUT_OF_RESOURCES;
        goto DONE;
      }

      status = _ConstructConfigHdr(configuration, &length, &VarInfo->VariableGuid, VarName, driverHandle);
    }
  }

	if(EFI_ERROR(status))
	{
		goto DONE;
	}

  if(*Configuration)
  {
    MemFreePointer(Configuration);
  }
  *Configuration = configuration;
  *Length = length;

DONE:
  MemFreePointer(&VarName);
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    _ConstructConfigHdr
//
// Description:		Construct <ConfigHdr> using routing information GUID/NAME/PATH.
//
// Parameter:	  	IN OUT CHAR16 *ConfigHdr,
//                	IN OUT UINTN  *StrBufferLen,
//                	IN EFI_GUID   *Guid,
//                	IN CHAR16     *Name, OPTIONAL
//                	IN EFI_HANDLE *DriverHandle
//
// Return value:  	EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _ConstructConfigHdr (
  IN OUT CHAR16                *ConfigHdr,
  IN OUT UINTN                 *StrBufferLen,
  IN EFI_GUID                  *Guid,
  IN CHAR16                    *Name, OPTIONAL
  IN EFI_HANDLE                *DriverHandle
  )
{
  EFI_STATUS                Status;
  UINTN                     NameStrLen;
  UINTN                     DevicePathSize;
  UINTN                     BufferSize;
  CHAR16                    *StrPtr;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;

  if (Name == NULL)
  {
    //
    // There will be no "NAME" in <ConfigHdr> for  Name/Value storage
    //
    NameStrLen = 0;
  } else
  {
    //
    // For buffer storage
    //
    NameStrLen = EfiStrLen (Name);
  }

  //
  // Retrieve DevicePath Protocol associated with this HiiPackageList
  //
  Status = gBS->HandleProtocol (
                  DriverHandle,
                  &gEfiDevicePathProtocolGuid,
                  &DevicePath
                  );
  if (EFI_ERROR (Status))
  {
    return Status;
  }

  DevicePathSize = EfiDevicePathSize (DevicePath);

  //
  // GUID=<HexCh>32&NAME=<Char>NameStrLen&PATH=<HexChar>DevicePathStrLen <NULL>
  // | 5  |   32   |  6  |  NameStrLen*4 |  6  |    DevicePathStrLen    | 1 |
  //
  BufferSize = (5 + 32 + 6 + NameStrLen * 4 + 6 + DevicePathSize * 2 + 1) * sizeof (CHAR16);
  if (*StrBufferLen < BufferSize)
  {
    *StrBufferLen = BufferSize;
    return EFI_BUFFER_TOO_SMALL;
  }

  *StrBufferLen = BufferSize;

  StrPtr = ConfigHdr;

  EfiStrCpy (StrPtr, L"GUID=");
  StrPtr += 5;
  BufferToHexString (StrPtr, (UINT8 *) Guid, sizeof (EFI_GUID));
  StrPtr += 32;

  //
  // Convert name string, e.g. name "ABCD" => "&NAME=0041004200430044"
  //
  EfiStrCpy (StrPtr, L"&NAME=");
  StrPtr += 6;
  if (Name != NULL)
  {
    BufferSize = (NameStrLen * 4 + 1) * sizeof (CHAR16);
    UnicodeToConfigString (StrPtr, &BufferSize, Name);
    StrPtr += (NameStrLen * 4);
  }

  EfiStrCpy (StrPtr, L"&PATH=");
  StrPtr += 6;
  BufferToHexString (StrPtr, (UINT8 *) DevicePath, DevicePathSize);

  return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    GetBlockName
//
// Description:   
//
// Parameter:	    EFI_STRING *Configuration, UINTN *Length, UINTN Size
//
// Return value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetBlockName(EFI_STRING *Configuration, UINTN *Length, UINTN Size)
{
	EFI_STATUS status = EFI_SUCCESS;
  UINTN length = 0;
  UINTN finalLen = 0;
	CHAR16 *tempBuffer = NULL;

  length = (EfiStrLen(L"&OFFSET=0&WIDTH=") + sizeof(Size) + 1) * sizeof(CHAR16);
  tempBuffer = (CHAR16*)EfiLibAllocateZeroPool(length);
  if(tempBuffer == NULL)
  {
    status = EFI_OUT_OF_RESOURCES;
    goto DONE;
  }

  Swprintf_s(tempBuffer, length, L"&OFFSET=0&WIDTH=%x", Size);

  length = EfiStrLen(*Configuration) * sizeof(CHAR16);
  finalLen = (EfiStrLen(*Configuration) + EfiStrLen(tempBuffer) + 1) * sizeof(CHAR16);
  *Configuration = MemReallocateZeroPool(*Configuration, length, finalLen);
  if(*Configuration == NULL)
  {
    status = EFI_OUT_OF_RESOURCES;
    goto DONE;
  }

  EfiStrCat(*Configuration, tempBuffer);

	MemFreePointer(&tempBuffer);
  *Length = finalLen;

DONE:
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BufferToHexString
//
// Description:	Converts binary buffer to Unicode string in reversed byte order from BufToHexString().
//
// Input:	Str        -  String for output
//					Buffer     -  Binary buffer.
//					BufferSize -  Size of the buffer in bytes.
//
// Output:	EFI_SUCCESS  -  The function completed successfully.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
BufferToHexString (
  IN OUT CHAR16    *Str,
  IN UINT8         *Buffer,
  IN UINTN         BufferSize
  )
{
  EFI_STATUS  Status;
  UINT8       *NewBuffer;
  UINTN       StrBufferLen;

  NewBuffer = EfiLibAllocatePool (BufferSize);
  MemCopy(NewBuffer, Buffer, BufferSize);

  SwapBuffer (NewBuffer, BufferSize);

  StrBufferLen = BufferSize * 2 + 1;
  Status = BufToHexString (Str, &StrBufferLen, NewBuffer, BufferSize);

  gBS->FreePool (NewBuffer);
  //
  // Convert the uppercase to lowercase since <HexAf> is defined in lowercase format.
  //
  ToLower (Str);
  
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UnicodeToConfigString
//
// Description:	Convert Unicode string to binary representation Config string, e.g.
//					"ABCD" => "0041004200430044". Config string appears in <ConfigHdr> (i.e.
//					"&NAME=<string>"), or Name/Value pair in <ConfigBody> (i.e. "label=<string>").
//
// Input:	ConfigString  - Binary representation of Unicode String, <string> := (<HexCh>4)+
//					StrBufferLen  - On input: Length in bytes of buffer to hold the Unicode string.
//       		    Includes tailing '\0' character.
//					On output:
//						If return EFI_SUCCESS, containing length of Unicode string buffer.
//						If return EFI_BUFFER_TOO_SMALL, containg length of string buffer desired.
//					UnicodeString - Original Unicode string.
//
// Output:	EFI_SUCCESS          - Routine success.
//					EFI_BUFFER_TOO_SMALL - The string buffer is too small.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UnicodeToConfigString (
  IN OUT CHAR16                *ConfigString,
  IN OUT UINTN                 *StrBufferLen,
  IN CHAR16                    *UnicodeString
  )
{
  UINTN       Index;
  UINTN       Len;
  UINTN       BufferSize;
  CHAR16      *String;

  Len = EfiStrLen (UnicodeString);
  BufferSize = (Len * 4 + 1) * sizeof (CHAR16);

  if (*StrBufferLen < BufferSize) {
    *StrBufferLen = BufferSize;
    return EFI_BUFFER_TOO_SMALL;
  }

  *StrBufferLen = BufferSize;
  String        = ConfigString;

  for (Index = 0; Index < Len; Index++) {
    BufToHexString (ConfigString, &BufferSize, (UINT8 *) UnicodeString, 2);

    ConfigString += 4;
    UnicodeString += 1;
  }

  //
  // Add tailing '\0' character
  //
  *ConfigString = L'\0';

  //
  // Convert the uppercase to lowercase since <HexAf> is defined in lowercase format.
  //
  ToLower (String);  
  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ToLower
//
// Description:	Converts the unicode character of the string from uppercase to lowercase.
//
// Input:	Str        -  String to be converted
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ToLower (
  IN OUT CHAR16    *Str
  )
{
  CHAR16      *Ptr;
  
  for (Ptr = Str; *Ptr != L'\0'; Ptr++) {
    if (*Ptr >= L'A' && *Ptr <= L'Z') {
      *Ptr = (CHAR16) (*Ptr - L'A' + L'a');
    }
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SwapBuffer
//
// Description:	Swap bytes in the buffer.
//
// Input:	Buffer     -  Binary buffer.
//					BufferSize -  Size of the buffer in bytes.
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
SwapBuffer (
  IN OUT UINT8     *Buffer,
  IN UINTN         BufferSize
  )
{
  UINTN  Index;
  UINT8  Temp;
  UINTN  SwapCount;

  SwapCount = BufferSize / 2;
  for (Index = 0; Index < SwapCount; Index++) {
    Temp = Buffer[Index];
    Buffer[Index] = Buffer[BufferSize - 1 - Index];
    Buffer[BufferSize - 1 - Index] = Temp;
  }
}

