#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20Acpi/Tpm20Acpi.mak 3     4/30/14 11:55a Fredericko $
#
# $Revision: 3 $
#
# $Date: 4/30/14 11:55a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20Acpi/Tpm20Acpi.mak $
# 
# 3     4/30/14 11:55a Fredericko
# 
# 2     4/25/14 4:46p Fredericko
# Use Fixed memory descriptor to prevent O.S. from reassigning TPM
# resources
# 
# 1     4/21/14 2:19p Fredericko
# 
# 3     3/14/14 3:51p Fredericko
# 
# 2     3/11/14 6:51p Fredericko
# [TAG]  		EIP151925
# [Category]  	New Feature
# [Description]  	Changes for TcgGeneric Regression Testing
# 
# 1     10/08/13 12:06p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 2     7/11/13 6:18p Fredericko
# 
# 1     7/10/13 5:58p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 4     12/07/11 4:30p Fredericko
# [TAG]  		EIP59683
# [Category]  	Improvement
# [Description]  	Allow selection between writing to SMI port as a word
# or as a Byte.
# Some platforms might require word writes to the SMI Status port.
# [Files]  		Tcg.cif, Tcg.sdl, Tcg_ppi1_2_Ex.asl, TcgSmm.mak, TcgSmm.c
# 
# 3     8/09/10 2:32p Fredericko
# 
# 2     5/20/10 8:50a Fredericko
# Included File Header
# Included File Revision History 
# EIP 37653
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:  TCGSmm.mak
#
# Description:
# Make file for TCG SMM module
#
#<AMI_FHDR_END>
#*************************************************************************
all : Tpm20Acpi

Tpm20Acpi : $(BUILD_DIR)\Tpm20Acpi.mak Tpm20AcpiBin

$(BUILD_DIR)\Tpm20Acpi.mak : $(TPM20ACPI_DIR)\Tpm20Acpi.cif $(TPM20ACPI_DIR)\Tpm20Acpi.mak $(BUILD_RULES)
	$(CIF2MAK) $(TPM20ACPI_DIR)\Tpm20Acpi.cif $(CIF2MAK_DEFAULTS)

Tpm20PlatformFlags=$(CFLAGS) \
	/I$(TCG_DIR)\
    /I$(TCG_DIR)\Common\
	/I$(PROJECT_DIR)\Include\Protocol\
    /I$(TCG_DIR)\Protocol\
    /I$(TPM20_CRBLIB)\

Tpm20AcpiBin : $(AMICSPLib) $(AMIDXELIB) $(BUILD_DIR)\Tpm20CRBLib.lib
	           $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		       /f $(BUILD_DIR)\Tpm20Acpi.mak all\
               "CFLAGS=$(Tpm20PlatformFlags) "\
               "CPFLAGS=$(Tpm20PlatformFlags) "\
		       GUID=4C8BDF60-2085-4577-8A46-96CB180967BC\
		       ENTRY_POINT=Tpm20AcpiInitEntry\
		       TYPE=BS_DRIVER \
		       COMPRESS=1\


$(BUILD_DIR)\tpm.asl:  $(TPM20ACPI_DIR)\Tpm20Acpi.mak
	copy << $@
//tpm.asl
Device(\_SB.PCI0.TPM)
	{
        Method(_HID, 0){		//PnP Device ID
		    If(TCMF)		
			    {
			    	Return(EISAID("ZIT0101"))
				}	
		    Else
			    {
				  If(LEqual(TTDP, 0)){
                    Return(EISAID("PNP0C31"))
                  }else{
                     Return("MSFT0101")
                  }
				}
	    }


	    Method(_STR,0)
        {
           If(LEqual(TTDP, 0)){
                Return (Unicode ("TPM 1.2 Device"))
           }else {
                Return (Unicode ("TPM 2.0 Device"))
           }
        }
        
	    Name(_UID,0x01)
	    Name(CRST,ResourceTemplate()
	    {
		   Memory32Fixed (ReadOnly, 0xFED40000, 0x5000,PCRS)
	    })

	  OperationRegion(TMMB, SystemMemory, 0x0FED40000, 0x5000)
	  Field(TMMB, ByteAcc, Lock, Preserve)
	  {
	    Offset(0x0000),
	    ACCS, 8,          // Access
	    Offset(0x0018), 
	    TSTA, 8,          // Status 
	    TBCA, 8,          // Burst Count
	    Offset(0x0F00),
	    TVID, 16,         // TPM Chip VID
	    TDID, 16          // TPM Chip DID
	  }
	  
	  Method(_STA, 0){
	   	If(LEqual(TTDP, 0)){
            If(TPMF){
                 Return(0x0F)  // TPM Support 
             }
             Return(0x00)  // No TPM Support
         }ElseIF(LEqual(TTDP, 1)){
            if(TTPF){
              Return(0x0F)  // TPM Support 
            }
         }  
         Return(0x00)  // No TPM Support
	   }
	   
	   Method(_CRS, 0, Serialized)
	   {
	       If(LEqual(TTPF, 1))
	       {
	           CreateDWordField(CRST, ^PCRS._BAS, MTFD) // Min
               CreateDWordField(CRST, ^PCRS._LEN, LTFD) // Length
               
               Store(0x0FED40000, MTFD)
               Store(0x00005000, LTFD)
	       }

	       Return (CRST)
	   }
	 
	}
<<
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************