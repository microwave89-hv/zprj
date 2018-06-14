#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Core/Languages.mak 3     3/28/11 3:21p Felixp $
#
# $Revision: 3 $
#
# $Date: 3/28/11 3:21p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Languages.mak $
# 
# 3     3/28/11 3:21p Felixp
# Enhancement(EIP52278): CHINESE macro is updated to be an alias for the
# CHINESE_TRAD.
# 
# 2     7/07/10 11:23a Robert
# Added language identifiers for more languages
# 
# 4     6/11/10 3:42p Robert
# - fixed spelling of Norwegian and added simplified and traditional
# chinese
# - For this to work you need a modified version of the UEFIStrGather
# tool and a new fontcfg.ini file.
# 
# 3     5/27/10 6:01p Robert
# removed spaces from a language definition
# 
# 2     5/26/10 5:56p Robert
# added support for additional languages
# 
# 1     10/09/09 5:10p Felixp
# 
# 5     10/05/09 3:52p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Languages.mak
#
# Description: List of language identifiers
#
#<AMI_FHDR_END>
#**********************************************************************
!IF $(EFI_SPECIFICATION_VERSION)>0x20000
#ISO 639-2 Language Identifiers
ENGLISH=en-US
FRENCH=fr-FR
SPANISH=es-ES
GERMAN=de-DE
RUSSIAN=ru-RU
CHINESE_SIMP=zh-chs
CHINESE_TRAD=zh-cht
KOREAN=ko-KR
JAPANESE=ja-JP
ITALIAN=it-IT
DANISH=da-DK
FINNISH=fi-FI
DUTCH=nl-NL
NORWEGIAN=nb-NO
PORTUGUESE=pt-BR
SWEDISH=sv-FI
!ELSE
#RFC 4646 Language Identifiers
ENGLISH=eng
FRENCH=fra
SPANISH=spa
GERMAN=ger
RUSSIAN=rus
CHINESE_SIMP=zho
CHINESE_TRAD=chi
KOREAN=kor
JAPANESE=jpn
ITALIAN=ita
DANISH=dan
FINNISH=fin
DUTCH=dut
NORWEGIAN=nor
PORTUGUESE=por
SWEDISH=swe
!ENDIF
CHINESE=$(CHINESE_TRAD)

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************