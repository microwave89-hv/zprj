## @file
#  Build description file for building the CPU PEI modules
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
# PEI module produce CPU PPI
#
$(PROJECT_CPU_ROOT)\CpuInit\Pei\CpuInitPeim.inf                       SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_CPU_ROOT)\CpuS3\Pei\CpuS3Peim.inf                           SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints

#
# TxT Drivers
#
$(PROJECT_CPU_ROOT)\Txt\TxtInit\Pei\TxtPei.inf                        SOURCE_OVERRIDE_PATH = $(EDK_SOURCE)\Foundation\Library\EdkIIGlueLib\EntryPoints
$(PROJECT_CPU_ROOT)\Txt\TxtInit\Pei\Ia32\TxtPeiApV7.inf
# $(PROJECT_CPU_ROOT)\Txt\BiosAcm\TxtBiosAcm.inf

#
# Sample drivers
#
