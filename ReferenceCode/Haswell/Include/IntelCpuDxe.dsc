## @file
#  Build description file for building the Intel CPU DXE drivers
#
#@copyright
#  Copyright (c)  2010 - 2012 Intel Corporation. All rights reserved
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
# CpuInit DXE drivers
#
$(PROJECT_CPU_ROOT)\CpuInit\Dxe\CpuInitDxe.inf                        SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

#
# DTS SMM drivers
#
$(PROJECT_CPU_ROOT)\Dts\Smm\DigitalThermalSensorSmm.inf                SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

#
# PFAT SMM drivers
#
$(PROJECT_CPU_ROOT)\Pfat\Smm\PfatServices.inf                         SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

#
# Power Management Drivers
#
$(PROJECT_CPU_ROOT)\PowerManagement\Dxe\PowerMgmtDxe.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_CPU_ROOT)\PowerManagement\Smm\PowerMgmtS3.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_CPU_ROOT)\PowerManagement\AcpiTables\PowerMgmtAcpiTables.inf

#
# TxT drivers
#
$(PROJECT_CPU_ROOT)\Txt\TxtInit\Dxe\TxtDxe.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

#
# Sample drivers
#
$(PROJECT_CPU_ROOT)\SampleCode\SmramSaveInfoHandlerSmm\SmramSaveInfoHandlerSmm.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_CPU_ROOT)\SampleCode\TxtOneTouch\Dxe\TxtOneTouchDxe.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_CPU_ROOT)\SampleCode\SmmThunk\Smm\SmmThunk.inf SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

