## @file
#  Build description file for building the PCH PEI modules
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
# PEI module produce PCH PPI
#
$(PROJECT_PCH_ROOT)\PchInit\Pei\PchInitPeim.inf                         SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\Smbus\Pei\PchSmbusArpDisabled.inf                   SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\Spi\Pei\PchSpiPeim.inf                              SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\Wdt\Pei\WdtPeim.inf                                 SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\Reset\Pei\PchResetPeim.inf                          SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\SmmControl\Pei\SmmControl.inf                       SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_PCH_ROOT)\S3Support\Pei\PchS3Peim.inf                         SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

#
# Recovery related modules
#
$(PROJECT_PCH_ROOT)\Usb\Pei\PchUsb.inf    Package = CompressPEIM        SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

#
# Sample drivers
#
