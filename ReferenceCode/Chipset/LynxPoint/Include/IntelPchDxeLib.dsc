## @file
#  Build description file for building the PCH DXE libraries
#
#@copyright
#  Copyright (c)  2008 - 2012 Intel Corporation. All rights reserved
#  This software and associated documentation (if any) is furnished
#  under a license and may only be used or copied in accordance
#  with the terms of the license. Except as permitted by such
#  license, no part of this software or documentation may be
#  reproduced, stored in a retrieval system, or transmitted in any
#  form or by any means without the express written consent of
#  Intel Corporation.
#
#  This file contains a 'Sample Driver' and is licensed as such
#  under the terms of your license agreement with Intel or your
#  vendor.  This file may be modified by the user, subject to
#  the additional terms of the license agreement
#

#
# PCH DXE Libraries
#
$(PROJECT_PCH_ROOT)\Protocol\IntelPchProtocolLib.inf
$(PROJECT_PCH_ROOT)\Library\PchPlatformLib\PchPlatformLib.inf
$(PROJECT_PCH_ROOT)\Library\DxeRuntimePciLibPciExpress\DxeRuntimePciLibPciExpress.inf
$(PROJECT_PCH_ROOT)\Library\PchPciExpressHelpersLib\PchPciExpressHelpersLib.inf
$(PROJECT_PCH_ROOT)\Library\PchSmbusLib\Dxe\PchSmbusLibDxe.inf
$(PROJECT_PCH_ROOT)\Library\RcFviDxeLib\RcFviDxeLib.inf
$(PROJECT_PCH_ROOT)\SampleCode\Library\AslUpdate\Dxe\PchAslUpdateLib.inf
$(PROJECT_PCH_ROOT)\Guid\PchGuidLib.inf