//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia Optimus SMM/NvOptimusSMM.asl 2     9/09/12 11:07p Joshchou $
//
// $Revision: 2 $
//
// $Date: 9/09/12 11:07p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia Optimus SMM/NvOptimusSMM.asl $
// 
// 2     9/09/12 11:07p Joshchou
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Tpv module support for sharkbay.
// [Files]  		NvOptimusSMM.mak
// NvOptimusSMM.c
// NvOptimusSMM.dxs
// NvOptimusSMM.ssp
// NvOptimusSMM.asl
// NvOptimusSMM.cif
// 
//**********************************************************************
External(DGPU_SCOPE.OPTF)

Scope(\_SB.PCI0.LPCB.EC0) {
    Method(_Q4F) {

        If(LEqual(HMIS, one))
            {
                Store(0, DGPU_SCOPE.OPTF)
            }
	else
	    {
		Store(1, DGPU_SCOPE.OPTF)
	    }
        Notify(PEG_SCOPE,0x81)
 
    }

	OperationRegion(ECIS, EmbeddedControl, 0, 0xFF)	// dummy

    	Field(ECIS, ByteAcc, Lock, Preserve) {

		offset(0x78),		// 
		,	6,
		HMIS,	1,		// 1 : hdmi plug in,  0 : out 
	}

}

//**********************************************************************
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
