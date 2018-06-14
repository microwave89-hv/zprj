## @file
#  Build description file DXE Drivers for building the Me
#
#@copyright
#  Copyright (c)  1999 - 2014 Intel Corporation. All rights reserved
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

$(PROJECT_ME_ROOT)\Heci\Dxe\Hecidrv.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_ME_ROOT)\ActiveManagement\AlertStandardFormat\Heci\Dxe\AlertStandardFormatDxe.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_ME_ROOT)\ActiveManagement\AmtBootOptions\Dxe\ActiveManagement.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_ME_ROOT)\BiosExtension\Efi\BiosExtensionLoader\Dxe\BiosExtensionLoader.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_ME_ROOT)\ActiveManagement\ider\Dxe\IdeRController.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_ME_ROOT)\ActiveManagement\sol\Dxe\PciSerial.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_ME_ROOT)\FwUpdate\MeFwDowngrade\Dxe\MeFwDowngrade.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_ME_ROOT)\At\AtAm\Dxe\AtAm.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
#
# Disable the following driver if PTT is not supported
#
$(PROJECT_ME_ROOT)\Ptt\Smm\PttHciSmm.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_ME_ROOT)\Acpitables\MeSsdt\MeSsdt_Edk.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

#
# Uncomment the following line if the Mebx and MebxSetupBrowser are included by this build description
#
#  $(PROJECT_ME_ROOT)\BiosExtension\Efi\Mebx\Mebx.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
#  $(PROJECT_ME_ROOT)\BiosExtension\Efi\MebxSetupBrowser\MebxSetupBrowser.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

