## @file
#  Build description file for building the PCH PEI Libraries
#
#@copyright
#  Copyright (c)  2008 - 2015 Intel Corporation. All rights reserved
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
# PCH PEI libraries
#
$(PROJECT_PCH_ROOT)\Ppi\IntelPchPpiLib.inf
$(PROJECT_PCH_ROOT)\Library\PchPlatformLib\PchPlatformLib.inf
$(PROJECT_PCH_ROOT)\Library\PchPciExpressHelpersLib\PchPciExpressHelpersLib.inf
$(PROJECT_PCH_ROOT)\Library\PchSmbusLib\Pei\PchSmbusLibPei.inf
$(PROJECT_PCH_ROOT)\Guid\PchGuidLib.inf
$(PROJECT_PCH_ROOT)\SampleCode\Ppi\IntelPchSampleCodePpiLib.inf