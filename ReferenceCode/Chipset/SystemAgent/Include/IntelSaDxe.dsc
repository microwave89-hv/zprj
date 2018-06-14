## @file
#  This is the build description file containing the Iio 
#  DXE, Runtime DXE, SMM, legacy support or other later modules.
#
#  This should be included in a [Components] section of the DSC files for a platform build.
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

$(PROJECT_SA_ROOT)\SmbiosMemory\Dxe\SmbiosMemory.inf   SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_SA_ROOT)\SmmAccess\Dxe\SmmAccess.inf  SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_SA_ROOT)\PciHostBridge\Dxe\PciHostBridge.inf  SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_SA_ROOT)\Acpitables\SaAcpiTables_Edk.inf  SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_SA_ROOT)\Acpitables\SaSsdt\SaSsdt_Edk.inf  SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_SA_ROOT)\SaInit\Dxe\SaInit.inf  SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_SA_ROOT)\BdatAccessHandler\Dxe\BdatAccessHandler.inf  SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
#
# Comment out below line if ASPM Init After Oprom was not supported
#
$(PROJECT_SA_ROOT)\SaInit\Smm\SaLateInitSmm.inf  SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
