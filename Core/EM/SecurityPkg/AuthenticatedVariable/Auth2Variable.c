//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SecureBoot_WIN8/AuthenticatedVariable_efi/Auth2Variable.c 30    3/09/15 4:31p Alexp $
//
// $Revision: 30 $
//
// $Date: 3/09/15 4:31p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SecureBoot_WIN8/AuthenticatedVariable_efi/Auth2Variable.c $
// 
// 30    3/09/15 4:31p Alexp
// Compliancy with UEFI spec: 
// EFI_VARIABLE_AUTHENTICATION_2.TimeStamp - 
//  during Append operations the TimeStamp value may be set to '0'
// 
// 29    10/08/14 3:16p Alexp
// Introduced global mCustomMode flag passing the status from
// PhysicalUserPresent()
// 
// 28    8/15/13 11:27a Alexp
// Link AmyCryptoLib. Replaced locally defined mkLongTime() with generic
// AmiCryptoLib defined os_mktime()
// 
// 27    2/08/13 5:15p Alexp
// Optimized the code flow fro Auth2 Variables.
// 
// 26    12/07/12 3:48p Alexp
// - Replaced TRACE macro with AVAR_TRACE. Stop debug traces in Virtual
// address mode
// - VerifyVariable2() Fix final check for IsPk and run
// ValidateSignatureList()
// 
// 25    12/04/12 6:56p Alexp
// VerifyVariable2()
// IsPk -> skip ValidateSignatureList if *DataSize =0
// 
// 24    11/29/12 3:08p Alexp
// ValidateSelfSigned(): keep *x509_SignCert ptr to non-0 for
// Pkcs7CertValidateGetSignerKeyHash operation
//  Will trigger an error in old CryptoDxe.c Pkcs7Verify()
// 
// 22    11/16/12 7:11p Alexp
// Fixed ValidateSignatureList() return status for Zero Data or Size
// 
// 21    11/16/12 5:09p Alexp
// EIP:104961 UEFI 2.3.1 SCTc test failed in Generic\EfiCompliant case. 
// Fix for SelfSigned variables.
// 
// 19    9/17/12 4:50p Alexp
// add Time Stamp traces
// 
// 18    9/06/12 5:14p Alexp
// ConstructDataParameter() Fix debug messages.
// 
// 17    9/04/12 3:35p Alexp
// EIP#99648: SCT will fail when enable Secure Boot in setup menu.
//    Fix: Use globally defined buffer to pass calculated Key Hash for
//    SelfSigned Variables
// 
// 15    8/22/12 6:19p Alexp
//  ProcessVarWithPk2()
//   Properly implemented the case for PK variable carrying RSA2048 Key.
//   Requires CryptoPkg Label 009 or later. 
// 
// 12    4/26/12 7:29p Alexp
// fix debug trace messages
// 
// 11    4/16/12 5:28p Alexp
// Add debug traces in ConstructDataParameter to display serialization
// data
// 
// 10    11/30/11 7:58p Alexp
// According to UEFI 2.3.1 Sec 7.2.1 : "db" vars can be validated either
// by KEK key or by PK key. 
// The fix adds the check for PK if none of KEKs can validate new "db"
// 
// 9     8/19/11 5:06p Alexp
// 
// 8     8/18/11 4:54p Alexp
// restored use of global variable mPlatformMode instead of a field in
// AuthVarMaibox
// 
// 7     8/16/11 7:18p Alexp
// added Mailbox variable AuthVarMAilbox to syncronize local state between
// DXE and SMM AuthVariable services
// 
// 6     7/18/11 10:17a Alexp
// made gEfiGlobalVariableGuid static to prevent linker issues
// 
// 5     6/27/11 6:16p Alexp
// code optimization: moved ValidateSignatureList () call in the main
// VerifyVariable1(2) function. 
// 
// 4     6/24/11 7:04p Alexp
// fixed ValidateSignatureList () logic. Added Certificate RSA2048 to
// supported Signatures
// 
// 3     6/24/11 3:23p Alexp
// test PK, KEK, db(x) for valid Signatuer List header with
// ValidateSignatureList()
// run test only if other tests passed
// 
// 2     6/23/11 6:19p Alexp
// Added ValidateSigList() function
// 
// 1     6/13/11 5:25p Alexp
// 
// 13    6/13/11 4:29p Alexp
// 
// 12    6/10/11 6:24p Alexp
// Update SelfSigned variable: Pkcs7CertValidateGetSignerKeyHash
// 
// 11    6/09/11 5:51p Alexp
// add new parameter to ValidateSelfSigned  - Operation.
// test for self-signed variables: hash CA certificate instead of Signer
// certificate.
// 
// 10    6/03/11 10:36a Alexp
// Add alternative cert verify logic in ProcessVarWithPk2 (). Keep it
// commented for now
// 
// 9     6/02/11 5:53p Alexp
// add new function to ValidateSelfSigned certificates
// add processing for Time BAsed self signed variables
// succesfully Verified Msft Win8 PK-KEK test keys
// 
// 8     5/31/11 3:11p Alexp
// Use UpdatePlatformMode() to update SetupMode variable
// 
// 7     5/25/11 8:34p Alexp
// draft fix for TimeBased auth variables. More work w Msft needed
// 
// 6     5/19/11 4:59p Alexp
// Major code revamp to be able to handle of handling Secure vars in Setup
// Mode
// TBD: TimeBased certificates from Msft fail to process. Not compiled as
// Authenticode format 
// 
// 5     5/17/11 12:48p Alexp
// fix WDK level4 compiler warnings
// 
// 4     5/13/11 3:43p Alexp
// add dependency on Core rev.
// 
// 3     5/11/11 7:20p Alexp
// VarData init for FindVariable
// 
// 2     5/10/11 5:07p Alexp
// removed local Hash Guid defines
// intermediate check in befor implementing Auth2 var verify logic
// 
//**********************************************************************

#include "NVRAM.h"
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol/AmiDigitalSignature.h>

#include "AuthVariable.h"
#include <cryptlib.h>

///
/// Global database array for scratch
/// 
extern BOOLEAN AVarRuntime;
extern UINT8 mCustomMode;
extern UINT8 mPlatformMode;
extern UINT8 PublicKeyHashArray[HASH_SHA256_LEN];

extern AMI_DIGITAL_SIGNATURE_PROTOCOL *mDigitalSigProtocol;
static EFI_GUID gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessVarWithPk2
//
// Description: Process variable with platform key for verification.
//              Called for PK or KEK Variables
//
//
// Input:
//          Pkcs7Cert                   Pointer to Pkcs#7 cert.
//          Pkcs7Cert_len               Size of Pkcs7 cert
//          pDigest                     Digest of serialized data block
//          Digest_len                  size of the digest (20 or 32 bytes)
// Output:
//          Status
//              EFI_SUCCESS             Variable passed validation successfully.
//              EFI_INVALID_PARAMETER   Invalid parameter.
//              EFI_SECURITY_VIOLATION  The variable does NOT pass the validation. 
//                                      check carried out by the firmware. 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ProcessVarWithPk2 (
  IN  UINT8     *Pkcs7Cert,
  IN  UINTN      Pkcs7Cert_len,
  IN  UINT8     *pDigest,
  IN  UINTN      Digest_len
  )
{
    EFI_STATUS           Status;
    EFI_SIGNATURE_LIST   *OldPkList;
    EFI_SIGNATURE_DATA   *OldPkData;
    UINT32                VarAttr;
    UINT8                *VarData;
    UINTN                 VarDataSize=0;
    UINT8                *x509_TrustCert, *TrustCert;
    UINTN                 x509_TrustCert_len, TrustCert_len;
    UINT8                 Pkcs7Operation;
    
    //
    // Get platform key from variable.
    //
    Status = FindVariable (
               EFI_PLATFORM_KEY_NAME,
               &gEfiGlobalVariableGuid,
               &VarAttr,
               &VarDataSize,
               &VarData
               );
// PK should have been set when we were in SETUP_MODE. This condition is INVALID.
//    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status) || VarData==NULL || !VarDataSize)
        return EFI_SECURITY_VIOLATION;

    OldPkList = (EFI_SIGNATURE_LIST *) VarData;
    OldPkData = (EFI_SIGNATURE_DATA *) ((UINT8 *) OldPkList + sizeof (EFI_SIGNATURE_LIST) + OldPkList->SignatureHeaderSize);

// Verify the PK SignatureType GUID

    if (!guidcmp ((EFI_GUID*) &(OldPkList->SignatureType), &gEfiCertRsa2048Guid))
    {
        //Process x509 cert and load Raw Key for Root cert comparison
        Pkcs7Operation = Pkcs7CertValidateGetSignerKey;
        x509_TrustCert = NULL;
        x509_TrustCert_len = 0;
    }
    else if(!guidcmp ((EFI_GUID*) &(OldPkList->SignatureType), &gEfiCertX509Guid)) 
        {
            Pkcs7Operation = Pkcs7CertValidateGetSignerCert;
            x509_TrustCert = (UINT8*)OldPkData->SignatureData;
            x509_TrustCert_len = (UINTN)OldPkList->SignatureSize-sizeof(EFI_GUID);
        } else
        //
        // Unsupported Sig Type, return EFI_SECURITY_VIOLATION.
        //
            return EFI_SECURITY_VIOLATION;

    TrustCert     = (UINT8*)OldPkData->SignatureData;
    TrustCert_len = (UINTN)OldPkList->SignatureSize-sizeof(EFI_GUID);

/*
//  Validate Self-Signed
//
        x509_TrustCert = &pDigest; // Init with addr to global var
        //&PublicKeyHashArray[0];
        x509_TrustCert_len = Digest_len;
        Status = mDigitalSigProtocol->Pkcs7Verify (
                 mDigitalSigProtocol,
                 Pkcs7Cert, Pkcs7Cert_len,    // Pkcs7Cert
                 NULL, 0,                     // use Internal Cert 
                 &x509_TrustCert, &x509_TrustCert_len,        // Input->Digest, Output->DER Ptr to Signing Cert
                 Pkcs7Operation, 
                 RESET 
         );
        if (!EFI_ERROR (Status)) {
            Status = ( TrustCert_len == x509_TrustCert_len && 
                    !(MemCmp(TrustCert, x509_TrustCert, x509_TrustCert_len))) ? 
                    EFI_SUCCESS:EFI_SECURITY_VIOLATION;
        }
*/
    Status = mDigitalSigProtocol->Pkcs7Verify (
             mDigitalSigProtocol,
             Pkcs7Cert, Pkcs7Cert_len,           // Pkcs7Cert
             x509_TrustCert, x509_TrustCert_len, // TrustCert
             &pDigest, &Digest_len,              // In/OutData
             Pkcs7Operation,
             RELEASE                             // Flags, mutex
             );
        if (!EFI_ERROR (Status)) {

            Status = ( TrustCert_len == Digest_len && 
                    !(MemCmp(TrustCert, pDigest, Digest_len))) ? 
                    EFI_SUCCESS:EFI_SECURITY_VIOLATION;
        }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessVarWithKek2
//
// Description: Process variable with key exchange key for verification.
//              Called for DB or DBx variables
//
//
// Input:
//          Pkcs7Cert                   Pointer to Pkcs#7 cert.
//          Pkcs7Cert_len               Size of Pkcs7 cert
//          pDigest                     Digest of serialized data block
//          Digest_len                  size of the digest (20 or 32 bytes)
//
// Output:
//          Status
//              EFI_SUCCESS             Variable passed validation successfully.
//              EFI_INVALID_PARAMETER   Invalid parameter.
//              EFI_SECURITY_VIOLATION  The variable does NOT pass the validation. 
//                                      check carried out by the firmware. 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ProcessVarWithKek2 (
  IN  UINT8     *Pkcs7Cert,
  IN  UINTN      Pkcs7Cert_len,
  IN  UINT8     *pDigest,
  IN  UINTN      Digest_len
  )
{
    EFI_STATUS            Status;
    EFI_SIGNATURE_LIST    *KekList;
    EFI_SIGNATURE_DATA    *KekItem;
    UINT32                KekCount;
    BOOLEAN               IsFound;
    UINT32                Index;
    UINT32                VarAttr;
    UINT8                 *VarData;
    UINTN                 VarDataSize=0;

    //
    // Get KEK database from variable.
    //
    Status = FindVariable (
               EFI_KEY_EXCHANGE_KEY_NAME, 
               &gEfiGlobalVariableGuid, 
               &VarAttr, 
               &VarDataSize,
               &VarData
               );
    if (EFI_ERROR (Status) || VarData==NULL || !VarDataSize)
        return EFI_SECURITY_VIOLATION;

    KekList   = (EFI_SIGNATURE_LIST *) VarData;

    //
    // Enumerate all Kek items in this list to verify the variable certificate data.
    // If anyone is authenticated successfully, it means the variable is correct!
    //
    IsFound   = FALSE;
    //
    // scan thru multiple Sig Lists if exist. Add 1 more loop....
    //
    while (!IsFound && (VarDataSize > 0) && (VarDataSize >= KekList->SignatureListSize)) {
        if (!guidcmp ((EFI_GUID*) &(KekList->SignatureType), &gEfiCertX509Guid))
        {
            KekCount  = (KekList->SignatureListSize - sizeof (EFI_SIGNATURE_LIST) - KekList->SignatureHeaderSize) / KekList->SignatureSize;
            KekItem   = (EFI_SIGNATURE_DATA *) ((UINT8 *) KekList + sizeof (EFI_SIGNATURE_LIST) + KekList->SignatureHeaderSize);
            for (Index = 0; Index < KekCount; Index++) {
            // find x509 cert and compare against one from Kek
                Status = mDigitalSigProtocol->Pkcs7Verify (
                    mDigitalSigProtocol,
                    Pkcs7Cert, Pkcs7Cert_len,        // Pkcs7Cert
                    KekItem->SignatureData,          // TrustCert Cert
                    KekList->SignatureSize,
                    &pDigest, &Digest_len,            // In/OutData
                    Pkcs7CertValidate,
                    RELEASE
                );
                if (!EFI_ERROR(Status)) {
                    IsFound = TRUE;
                    break;  
                }
                KekItem = (EFI_SIGNATURE_DATA *) ((UINT8 *) KekItem + KekList->SignatureSize);
            }
        }// else
    // Auth2 Vars must be signed with x509 Certs
//              if (!guidcmp ((EFI_GUID*) &(KekList->SignatureType), &gEfiCertRsa2048Guid))
//                 return EFI_SECURITY_VIOLATION;
         VarDataSize -= KekList->SignatureListSize;
         KekList = (EFI_SIGNATURE_LIST *) ((UINT8 *) KekList + KekList->SignatureListSize);
    }

    if (!IsFound)
        return EFI_SECURITY_VIOLATION;

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ValidateSelfSigned
//
// Description: Extract Signer certificate and verify Pkcs#7 SignedData signature.
//              Called for Private Authenticated variables
//
//
// Input:
//          Pkcs7Cert                   Pointer to Pkcs#7 cert.
//          Pkcs7Cert_len               Size of Pkcs7 cert
//          pDigest                     Digest of serialized data block
//          Digest_len                  size of the digest (20 or 32 bytes)
//          Operation                   type of Pkcs operation:Pkcs7CertValidateGetSignerCert...
//
// Output:      EFI_SUCCESS             SignedData passed validation successfully.
//              EFI_INVALID_PARAMETER   Invalid parameter.
//              EFI_SECURITY_VIOLATION  The data does NOT pass the validation. 
//                                      check carried out by the firmware. 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ValidateSelfSigned (
    IN UINT8     *Pkcs7Cert,
    IN UINTN      Pkcs7Cert_len,
    IN OUT UINT8 **pDigest,
    IN OUT UINTN  *Digest_len,
    IN UINT8       Operation
  )
{
    EFI_STATUS   Status;
    UINT8       *x509_SignCert;
    UINTN        x509_SignCert_len=0;

    //
    //  Extract x509 Signing Cert and validate self-signed data
    //
    x509_SignCert=(UINT8*)&x509_SignCert_len; // non-zero ptr
    Status = mDigitalSigProtocol->Pkcs7Verify (
             mDigitalSigProtocol,
             Pkcs7Cert, Pkcs7Cert_len,
             NULL, 0,                     // RootCert
             &x509_SignCert, &x509_SignCert_len,
             Pkcs7GetSignerCert, 
             KEEP
    );
    //
    // Authenticate using internal Signer Cert, Extract Cert or Key Hash
    //
    if (!EFI_ERROR (Status)) 
    {
        Status = mDigitalSigProtocol->Pkcs7Verify (
                 mDigitalSigProtocol,
                 Pkcs7Cert, Pkcs7Cert_len,          // Pkcs7Cert
                 x509_SignCert, x509_SignCert_len,  // RootCert     
                 pDigest, Digest_len,          // Input->Digest, Output->DER Ptr to Signing Cert
                 Operation, 
                 RELEASE 
         );

//  Status = mDigitalSigProtocol->Hash(mDigitalSigProtocol, &gEfiHashAlgorithmSha256Guid, 1 &x509_SignCert, (const UINTN*)&x509_SignCert_len, pDigest);
//  *Digest_len = HASH_SHA256_LEN;
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructDataParameter
//
// Description: 
//              Generates the Hash (SHA256) out of serialized data block 
//              Hash(VariableName, VendorGuid, Attributes, TimeStamp, Data)
//
// Input:
//              CHAR16 *VariableName  Name of Variable to be found.
//              EFI_GUID *VendorGuid   Variable vendor GUID.
//              IN UINT32 Attributes - Attributes of the Var
//              VOID  *Data - pointer to data block within AutVar Data
//              UINTN  DataSize - size of data block
//
// Output:      EFI_STATUS
//              UINT8  Digest - Hash of the serialized data block
//              UINTN  Digest_len - size of data block
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConstructDataParameter (
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid,
    IN UINT32    Attributes,
    IN VOID     *Data,
    IN UINTN     DataSize, 
    OUT UINT8   *pDigest,
    OUT UINTN   *Digest_len,
    IN  UINT8    Mutex    
)
{
    EFI_STATUS Status;

    EFI_GUID *HashAlgorithm;
    UINT8 *Addr[5];
    UINTN   Len[5];
    EFI_VARIABLE_AUTHENTICATION_2 *CertData;
    UINTN   CertHdrSize, Pkcs7Cert_len;
    UINT8   *Pkcs7Cert;
    UINT8   HashType=SHA1;
    UINT8   *pHash=&HashType;

#ifdef EFI_DEBUG
    UINTN     j, i;
#endif

    CertData  = (EFI_VARIABLE_AUTHENTICATION_2 *)Data;
    CertHdrSize = AUTHINFO_2_SIZE(Data);

// !!!sha256 is the only digest algorithm supported.
// temp w/a: determine the digest algorithm from contentInfo hdr
// 
    // quick cheat. CertBlock->CerData is a begining of Pkcs7 Cert
    Pkcs7Cert  = (UINT8*)&(CertData->AuthInfo.CertData);
    Pkcs7Cert_len = CertHdrSize - ((UINTN)Pkcs7Cert - (UINTN)Data);

    Status = mDigitalSigProtocol->Pkcs7Verify ( 
              mDigitalSigProtocol,
              Pkcs7Cert,
              Pkcs7Cert_len,
              NULL,
              0,
              &pHash,        // returns DER Ptr to Sign Cert
              &Len[0],
              Pkcs7GetDigestAlgorithm,
              Mutex
              );
    if (EFI_ERROR(Status)) 
        return Status;

    switch(*pHash) {
        case SHA1:
            *Digest_len = HASH_SHA1_LEN;
            HashAlgorithm = &gEfiHashAlgorithmSha1Guid;
            break;
        case SHA256:
            *Digest_len = HASH_SHA256_LEN;
            HashAlgorithm = &gEfiHashAlgorithmSha256Guid;
            break;
        default:
            return EFI_UNSUPPORTED;
            break;
    }
    //
    // Hash data payload with SHA.
    //
    Addr[0] = (UINT8*)VariableName;
    Len[0] = StrSize16(VariableName);
    Addr[1] = (UINT8*)VendorGuid;
    Len[1] = sizeof(EFI_GUID);
    Addr[2] = (UINT8*)&Attributes;
    Len[2] = sizeof(UINT32);
    Addr[3] = (UINT8*)&(CertData->TimeStamp);
    Len[3] = sizeof(EFI_TIME);
    Addr[4] = (UINT8*) Data + (CertHdrSize) ;
    Len[4] = DataSize - (CertHdrSize);
// zero out unused Time fields:
/*    CertData->TimeStamp.Pad1 = 0;
    CertData->TimeStamp.Pad2 = 0;
    CertData->TimeStamp.Nanosecond = 0;
    CertData->TimeStamp.TimeZone = 0;
    CertData->TimeStamp.Daylight = 0;*/
#ifdef EFI_DEBUG
AVAR_TRACE((TRACE_ALWAYS,"Hash Serialization"));
    for (j=0; j<5; j++) {
        AVAR_TRACE((TRACE_ALWAYS,"\nArg%d, Len=0x%x\n0000: ", j, Len[j]));
        for (i=0; i<Len[j]; i++) 
        {
            AVAR_TRACE((TRACE_ALWAYS,"%02X ", *(UINT8*)(Addr[j]+i) ));
            if(Len[j]>16 && i>=15){
                AVAR_TRACE((TRACE_ALWAYS,"\n....\n%04X: ",Len[j]-16));
                for (i=Len[j]-16; i<Len[j]; i++) 
                    AVAR_TRACE((TRACE_ALWAYS,"%02X ", *(UINT8*)(Addr[j]+i) ));
            }
        }
    }
#endif
    Status = mDigitalSigProtocol->Hash(mDigitalSigProtocol, HashAlgorithm, 5, Addr, Len, pDigest);
#ifdef EFI_DEBUG
AVAR_TRACE((TRACE_ALWAYS,"\nOutput Digest\n"));
    for (i=0; i<16; i++) 
        AVAR_TRACE((TRACE_ALWAYS,"%02X ", (pDigest[i]) ));
AVAR_TRACE((TRACE_ALWAYS,"...\n"));
#endif
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   VerifyVariable2
//
// Description: 
//              Verify data payload with AuthInfo in EFI_VARIABLE_AUTHENTICATION_2 type.
//              Follow the steps in UEFI2.3.1. This function is called every time variable with 
//              EFI_VARIABLE_AUTHENTICATED_TIME_BASED_ACCESS attribute is 
//              created, updated or deleted. This function does all necessary 
//              authetication checks and based on the results returns Status.
//              Also it updates the ExtFlags.KeyHash with the hash the Signer's
//               certificate from Variable's AuthInfo Hdr
//
// Input:
//              CHAR16 *VariableName  Name of Variable to be found.
//              EFI_GUID *VendorGuid   Variable vendor GUID.
//              IN UINT32 Attributes - Attributes of the Var
//              VOID **Data - pointer to data block within AutVar Data
//              UINTN *DataSize - size of data block
//              VOID  *OldData - pointer to Existing in NVRAM data block 
//              UINTN  OldDataSize - size of data block
//              UINT64 ExtFlags.MonotonicCount - value of MC or TIME stamp 
//              UINT8  ExtFlags.KeyHash[32] - pointer to memory, allocated by caller, 
//                     where Hash of Signer's certificate will be returned.
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VerifyVariable2 (
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid,
    IN UINT32    Attributes,
    IN VOID    **Data,
    IN UINTN    *DataSize, 
    IN VOID     *OldData,
    IN UINTN     OldDataSize,
    IN OUT EXT_SEC_FLAGS *ExtFlags
){
    EFI_STATUS Status;
    VOID        *RealData;
    EFI_VARIABLE_AUTHENTICATION_2 *CertData;
    UINTN       CertHdrSize, Pkcs7Cert_len, i;
    UINT8       *Pkcs7Cert;
    INT32       TimeStamp, NonZeroTime;
    UINT8       *PubKeyHash;
    UINTN       PubKeyHashLen;
    UINT8       AuthVarType;

/*
    common algo for all Auth2 Vars

1. Verify that the correct AuthInfo.CertType (EFI_CERT_TYPE_PKCS7_GUID) has been
used and that the AuthInfo.CertData value parses correctly as a PKCS #7 SignedData
value

2. Verify the signature by:
-extracting the EFI_VARIABLE_AUTHENTICATION_2 descriptor from the Data buffer;
-using the descriptor contents and other parameters to
- construct the input to the digest algorithm;
-computing the digest; 
    digest = hash (VariableName, VendorGuid, Attributes, TimeStamp, DataNew_variable_content).
 and
-comparing the digest with the result of applying the signer's public key to the signature
!!!!Signer must have at least one Cert!!!!

3. Verify that the signer's certificate chains to a certificate in the Key Exchange Key database (or
the Platform Key)
!!!!
!!!! branch off to handle special Vars for PK or KEK-> Use PK Cert to verify Signer's key
!!!! all other vars including DB and DBx should be looking for Cert chains in KEK db!!!!
!!!! 

4. Unless the EFI_VARIABLE_APPEND_WRITE attribute is set, verify that the TimeStamp value
is later than the current timestamp value associated with the variable.

5. For variables with GUID EFI_IMAGE_SECURITY_DATABASE_GUID (i.e. where the data buffer is formatted 
   as EFI_SIGNATURE_LIST), the driver shall not perform an append of EFI_SIGNATURE_DATA values that 
   are already part of the existing variable value
*/
// must have Auth attribute to go deeper
    if ((Attributes & EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)==0)
        return EFI_INVALID_PARAMETER;

    RealData = *Data;

    CertData  = (EFI_VARIABLE_AUTHENTICATION_2 *) *Data;
    CertHdrSize = AUTHINFO_2_SIZE(CertData);//(CertData->AuthInfo.Hdr.Hdr.dwLength + sizeof(EFI_TIME));

    if(*DataSize < CertHdrSize)
        return EFI_SECURITY_VIOLATION;

    // CertBlock->CerData is a begining of Pkcs7 Cert
    Pkcs7Cert  = (UINT8*)&(CertData->AuthInfo.CertData);
    Pkcs7Cert_len = CertHdrSize - ((UINTN)Pkcs7Cert - (UINTN)*Data);

    //
    // wCertificateType should be WIN_CERT_TYPE_EFI_GUID.
    // Cert type should be EFI_CERT_TYPE_PKCS7_GUID.
    //
    if ((CertData->AuthInfo.Hdr.wCertificateType != WIN_CERT_TYPE_EFI_GUID) ||  
        guidcmp ((EFI_GUID*) &(CertData->AuthInfo.CertType), &gEfiCertTypePkcs7Guid)
        ) {
    //
    // Invalid AuthInfo type, return EFI_SECURITY_VIOLATION.
    //
        return EFI_SECURITY_VIOLATION;
    }

    //
    // Time check fail, suspicious replay attack, return EFI_SECURITY_VIOLATION.
    //
    TimeStamp = 0;
    if(os_mktime( CertData->TimeStamp.Year, CertData->TimeStamp.Month, 
                CertData->TimeStamp.Day, CertData->TimeStamp.Hour, 
                CertData->TimeStamp.Minute, CertData->TimeStamp.Second, &TimeStamp ))
    {
        NonZeroTime = 0;
        for(i=0;i < sizeof(EFI_TIME); i++)
        	NonZeroTime+=(INT32)((UINT8*)CertData)[i];

        if(NonZeroTime || ((Attributes & EFI_VARIABLE_APPEND_WRITE) == 0)) {
              AVAR_TRACE((TRACE_ALWAYS,"Invalid Time Stamp\n"));
              return EFI_SECURITY_VIOLATION;
        }
    }        
    AVAR_TRACE((TRACE_ALWAYS,"Update Time Stamp\nOld=%x\nNew=%x\n", ExtFlags->Mc, TimeStamp));
    if( (Attributes & EFI_VARIABLE_APPEND_WRITE) == EFI_VARIABLE_APPEND_WRITE) {
    // AppendWrite: Only update Timestamp if New one is greater then current
        if(OldData && (INT32)ExtFlags->Mc > TimeStamp)
            TimeStamp = (INT32)ExtFlags->Mc;
    } else {
        //Unless the EFI_VARIABLE_APPEND_WRITE attribute is set, verify that the TimeStamp value
        //is later than the current timestamp value associated with the variable.
        // and reserved TimeStamp fields must be set to 0
        if(  CertData->TimeStamp.Pad1 ||
             CertData->TimeStamp.Pad2 ||
             CertData->TimeStamp.Nanosecond ||
             CertData->TimeStamp.TimeZone ||
             CertData->TimeStamp.Daylight ||
            (OldData && (INT32)ExtFlags->Mc >= TimeStamp)
        ) {
            AVAR_TRACE((TRACE_ALWAYS,"Failed\n"));
            return EFI_SECURITY_VIOLATION;
        }
    } 
    ExtFlags->Mc = TimeStamp;
    AVAR_TRACE((TRACE_ALWAYS,"Upd=%x\n", ExtFlags->Mc));
    //
    // Process PK, KEK, seperately.
    //
    if (IsDbVar(VendorGuid)) 
        AuthVarType = IsDbVarType;
    else
        if (IsPkVar(VariableName, VendorGuid))
            AuthVarType = IsPkVarType;
        else
            if (IsKekVar(VariableName, VendorGuid))
                AuthVarType = IsKekVarType;
            else
                AuthVarType = IsPrivateVarType;

    if(AuthVarType != IsPrivateVarType) {

        //
        // PK, KEK and db/dbx should set EFI_VARIABLE_NON_VOLATILE attribute
        // authenticated variable.
        //
        if ((Attributes & EFI_VARIABLE_NON_VOLATILE) == 0) {
            return EFI_INVALID_PARAMETER;
        }
        if (mPlatformMode == SETUP_MODE || mCustomMode == 1 ) {
            Status = EFI_SUCCESS;
            goto Exit_SetupMode;
        }
    }

    PubKeyHash = &PublicKeyHashArray[0];
    Status = ConstructDataParameter (
             VariableName, VendorGuid, Attributes, 
             *Data, *DataSize, 
             PublicKeyHashArray, &PubKeyHashLen,
             LOCK // first time Pkcs7 cert process.
    );
    if (EFI_ERROR(Status)) 
        return EFI_SECURITY_VIOLATION;

//
// Process UEFI Private TimeBased Authenticated Variables
//
    if (AuthVarType == IsPrivateVarType){
        /*
        Extract x509 Signing Cert(hash) and validate self signed data
        Updating Cert hash Existing Variable
        */
        Status = ValidateSelfSigned (
                 Pkcs7Cert, Pkcs7Cert_len,    // Pkcs7Cert
                 &PubKeyHash, &PubKeyHashLen, // Input->Digest, Output->DER Ptr to Signing Cert
                 Pkcs7CertValidateGetSignerKeyHash
         );
        if (!EFI_ERROR(Status)) {
             // Updating Existing Variable
                if (OldData && MemCmp(&ExtFlags->KeyHash[0], PubKeyHash, PubKeyHashLen)){
        AVAR_TRACE((TRACE_ALWAYS,"Private Var Key Compare FAILED!\n"));
                    return EFI_SECURITY_VIOLATION;
                }
            // Setting Hash for self signed variables
            MemCpy(&ExtFlags->KeyHash[0], PubKeyHash, PubKeyHashLen);

            *DataSize   =  *DataSize - CertHdrSize;
            *Data       = (UINT8*)RealData + CertHdrSize;
        }
    } else {
//
// Process UEFI TimeBased PK, KEK and db(x) variables
//
        if (AuthVarType == IsDbVarType) {
            Status = ProcessVarWithKek2 (Pkcs7Cert, Pkcs7Cert_len, PubKeyHash, PubKeyHashLen);
            // verify process db(x) with one of KEK keys or if not found within KEK - with PK
        AVAR_TRACE((TRACE_ALWAYS,"kek for db check %r\n", Status));
            if (Status == EFI_SECURITY_VIOLATION) {
                Status = ProcessVarWithPk2 (Pkcs7Cert, Pkcs7Cert_len, PubKeyHash, PubKeyHashLen);
        AVAR_TRACE((TRACE_ALWAYS,"PK for db check %r\n", Status));
            }
        //
        // Process PK, KEK separately.
        //
        } else 
            if (AuthVarType == IsPkVarType || AuthVarType == IsKekVarType)
                Status = ProcessVarWithPk2 (Pkcs7Cert, Pkcs7Cert_len, PubKeyHash, PubKeyHashLen);

        if (EFI_ERROR(Status))  
            return EFI_SECURITY_VIOLATION;

Exit_SetupMode:

        *DataSize   =  *DataSize - CertHdrSize;
        *Data       = (UINT8*)RealData + CertHdrSize;

        // Validate Signature List integrity 
        if(*DataSize && EFI_ERROR(ValidateSignatureList (*Data, *DataSize)))
            return EFI_SECURITY_VIOLATION;
        //
        // If delete PK in user mode -> change to setup mode.
        // If enroll PK in setup mode -> change to user mode.
        //
        if(AuthVarType == IsPkVarType) {
            if (*DataSize == 0) 
                UpdatePlatformMode (SETUP_MODE);
            else
                UpdatePlatformMode (USER_MODE);
        }
    }

    return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
