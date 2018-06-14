## @file
#  Build description file for building the RapidStart DXE drivers
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

$(PROJECT_RAPID_START_ROOT)\Dxe\RapidStartDxe.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_RAPID_START_ROOT)\Smm\RapidStartSmm.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_RAPID_START_ROOT)\AcpiTables\RapidStartAcpiTables.inf
#
# Please uncomment following line after download binary modules PeiGfxDriver.efi and DxeGfxDriver.efi from IRS UEFI Graphics Drivers Release 5.0.1.1001 and later.
#
# $(PROJECT_RAPID_START_ROOT)\GfxDisplay\FfsGfxDriver\Dxe\DxeFfsGfxDriver.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
