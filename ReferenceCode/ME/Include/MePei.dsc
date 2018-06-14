## @file
#  Build description file PEI Drivers for building
#
#@copyright
#  Copyright (c)  1999 - 2012 Intel Corporation. All rights reserved
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

$(PROJECT_ME_ROOT)\PchMeUma\PchMeUma.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_ME_ROOT)\Heci\Pei\HeciInit.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_ME_ROOT)\ActiveManagement\StartWatchDog\Pei\StartWatchDog.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_ME_ROOT)\ActiveManagement\AlertStandardFormat\Heci\Pei\AlertStandardFormatPei.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
