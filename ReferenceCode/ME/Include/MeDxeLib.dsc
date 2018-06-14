## @file
#  Build description file for building the Me Libries for DXE
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
#  This file contains an 'Intel Peripheral Driver' and uniquely
#  identified as "Intel Reference Module" and is
#  licensed for Intel CPUs and chipsets under the terms of your
#  license agreement with Intel or your vendor.  This file may
#  be modified by the user, subject to additional terms of the
#  license agreement
#

$(PROJECT_ME_ROOT)\Guid\MeGuidLib.inf
$(PROJECT_ME_ROOT)\Protocol\MeProtocolLib.inf
$(PROJECT_ME_ROOT)\Library\MeKernel\Common\MeChipsetLib\MeChipsetLib.inf
$(PROJECT_ME_ROOT)\Library\MeKernel\Dxe\MeLib.inf
$(PROJECT_ME_ROOT)\Library\AMT\Dxe\AmtLib.inf
$(PROJECT_ME_ROOT)\Library\AtLibrary\Dxe\AtDxeLib.inf
#
# Disable the following library if PTT is not supported
#
$(PROJECT_ME_ROOT)\Library\Ptt\Dxe\PttHciDeviceDxeLib.inf
