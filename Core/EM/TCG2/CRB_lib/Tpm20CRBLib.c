//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Libraries/Tpm20CRBLib/Tpm20CRBLib.c 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Libraries/Tpm20CRBLib/Tpm20CRBLib.c $
// 
// 1     4/21/14 2:15p Fredericko
// 
// 3     3/14/14 3:19p Fredericko
// 
// 2     3/11/14 6:02p Fredericko
// [TAG]  		EIP151925
// [Category]  	New Feature
// [Description]  	Changes for TcgGeneric Regression Testing
// 
// 1     10/08/13 11:59a Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 1:48p Fredericko
// 
// 1     7/10/13 5:51p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: 
//
// Description: 
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Efi.h>
#include "Tpm20CRBLib.h"
#include "AmiLib.h"
#include <token.h>
#include <Tpm20Includes\Tpm20.h>


//Forward declare functions
#if FTpmPlatformProfile == 1

EFI_STATUS
iTpmGetResponse (
  IN OUT   VOID                  *ResponseBuffer,
  IN OUT   UINT32                *ResponseSize
  );

EFI_STATUS
iTpmSendCommand (
  IN     VOID                 *CommandBuffer,
  IN     UINT32                CommandSize
  );

EFI_STATUS
CheckPspDevicePresent (
  VOID
  );

#else

EFI_STATUS
EFIAPI  
PttHciReceive(
  OUT     UINT8     *FtpmBuffer,
  OUT     UINT32    *RespSize
  ); 

EFI_STATUS
EFIAPI  
PttHciSend(
  IN     UINT8      *FtpmBuffer,
  IN     UINT32     DataLength
  );

BOOLEAN
EFIAPI  
PttHciPresenceCheck();


#endif

BOOLEAN isTpm20CrbPresent()
{
  #if FTpmPlatformProfile == 1 
	if(!EFI_ERROR(CheckPspDevicePresent()))return TRUE;
	return FALSE;
  #else
	return (PttHciPresenceCheck());
  #endif
}


EFI_STATUS
EFIAPI  
CrbSend(
  IN     UINT8      *InputBuffer,
  IN     UINT32     DataLength
)
{
  #if FTpmPlatformProfile == 1
	return(iTpmSendCommand(InputBuffer, DataLength));
  #else
	return (PttHciSend(InputBuffer, DataLength));
  #endif
}


EFI_STATUS
EFIAPI  
CrbReceive(
  OUT     UINT8     *OutBuffer,
  OUT     UINT32    *RespSize
)
{
  #if FTpmPlatformProfile == 1
	return(iTpmGetResponse(OutBuffer, RespSize));
  #else
	return (PttHciReceive(OutBuffer, RespSize));
  #endif
}

EFI_STATUS
EFIAPI
CrbSubmitCmd(
  IN      UINT8     *InputBuffer,
  IN      UINT32     InputBufferSize,
  OUT     UINT8     *OutputBuffer,
  OUT     UINT32    *OutputBufferSize
  )
{
  EFI_STATUS Status;

  if(InputBuffer == NULL || OutputBuffer == NULL || InputBufferSize == 0){
    return EFI_INVALID_PARAMETER;
  }

  Status = CrbSend(InputBuffer, InputBufferSize);
  if (EFI_ERROR (Status))  {
    return Status; 
  }

  ///
  /// Receive the response data from TPM
  ///
  Status = CrbReceive(OutputBuffer, OutputBufferSize);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return Status;
}
