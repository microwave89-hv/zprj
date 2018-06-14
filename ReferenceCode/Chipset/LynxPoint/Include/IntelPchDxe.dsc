## @file
#  Build description file for building the PCH DXE drivers
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
# DXE drivers produce PCH protocols
#
$(PROJECT_PCH_ROOT)\ActiveBios\Dxe\ActiveBios.inf                       SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\Spi\RuntimeDxe\PchSpiRuntime.inf                    SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\Spi\Smm\PchSpiSmm.inf                               SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\SerialGpio\Dxe\PchSerialGpio.inf                    SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\SmartTimer\Dxe\SmartTimer.inf                       SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\SmmControl\RuntimeDxe\SmmControl.inf                SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\Smbus\Dxe\PchSmbusDxe.inf                           SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\Smbus\Smm\PchSmbusSmm.inf                           SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\LegacyInterrupt\Dxe\LegacyInterrupt.inf             SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\Reset\RuntimeDxe\PchResetRuntime.inf                SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\Wdt\Dxe\WdtDxe.inf                                  SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

#
# DXE drivers use PCH protocols to initialize PCH
#
$(PROJECT_PCH_ROOT)\PchInit\Dxe\PchInitDxe.inf                          SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

#
# SMM drivers
#
$(PROJECT_PCH_ROOT)\Pcie\Smm\PchPcieSmm.inf                             SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\PchInit\Smm\PchLateInitSmm.inf                      SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\IoTrap\Smm\IoTrap.inf                               SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\PchSmiDispatcher\Smm\PchSmiDispatcher.inf           SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\S3Support\Smm\S3SupportSmm.inf                      SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints


#
# EFI 1.1 drivers
#
$(PROJECT_PCH_ROOT)\SataController\Dxe\SataController.inf               SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

#
# Sample drivers
#
$(PROJECT_PCH_ROOT)\SampleCode\BiosWriteProtect\Smm\PchBiosWriteProtect.inf   SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints