#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
#<AMI_FHDR_START>
#
# Name: <EcPs2Kbd.mak>
#
# Description:
#
#<AMI_FHDR_END>  
#**********************************************************************
{$(ECPS2KBD_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\\ $<

all : EcPs2Kbd

EcPs2Kbd : $(BUILD_DIR)\EcPs2Kbd.mak EcPs2KbdBin

$(BUILD_DIR)\EcPs2Kbd.mak : $(ECPS2KBD_DIR)\$(@B).cif $(ECPS2KBD_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(ECPS2KBD_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EcPs2KbdBin : $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\EcPs2Kbd.mak all\
                GUID=2F72309E-D5B0-4a9d-84A9-1AB38C698F78\
                ENTRY_POINT=EcPs2KbdEntry\
		TYPE=BS_DRIVER \
		COMPRESS=1
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
