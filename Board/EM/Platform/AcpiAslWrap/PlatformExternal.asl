//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
//<AMI_FHDR_START>
//
// Name:        PlatformExternal.asl
//
//<AMI_FHDR_END>
//*************************************************************************

#if !defined(ASL_Remove_SaSsdt_Data_To_Dsdt) || (ASL_Remove_SaSsdt_Data_To_Dsdt == 0)
External(LHIH)
External(LLOW)
External(IGDS)
External(LIDS)
External(BRTL)
External(ALSE)
External(GSMI)
External(\_SB.PCI0.GFX0.ALSI)
External(\_SB.PCI0.GFX0.CDCK)
External(\_SB.PCI0.GFX0.CBLV)
External(\_SB.PCI0.GFX0.GSSE)
External(\_SB.PCI0.PEG0, DeviceObj)
External(\_SB.PCI0.PEG0.PEGP, DeviceObj)
External(\_SB.PCI0.PEG1, DeviceObj)
External(\_SB.PCI0.PEG2, DeviceObj)
External(\_SB.PCI0.GFX0.DD1F, DeviceObj)
External(\_SB.PCI0.GFX0.GDCK, MethodObj)
External(\_SB.PCI0.GFX0.GHDS, MethodObj)
External(\_SB.PCI0.GFX0.AINT, MethodObj)
External(\_SB.PCI0.GFX0.GLID, MethodObj)
External(\_SB.PCI0.GFX0.GSCI, MethodObj)
#endif
External(\_PR.CPU0, DeviceObj)
External(\_PR.CPU0._PSS, MethodObj)
External(\_PR.CPU0._PPC, IntObj)
#if !defined(ASL_EC_SUPPORT) || (ASL_EC_SUPPORT == 0)
#if !defined(ASL_Remove_SaSsdt_Data_To_Dsdt) || (ASL_Remove_SaSsdt_Data_To_Dsdt == 0)
External(\_SB.PCI0.GFX0.CLID)
External(\_SB.PCI0.GFX0.IUEH, MethodObj)
#endif
External(\_SB.IETM, DeviceObj)
#endif // ASL_EC_SUPPORT

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
