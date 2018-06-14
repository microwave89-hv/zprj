## @file
#  Build description file for building the CPU DXE libraries
#
#@copyright
#  Copyright (c)  2011 - 2012 Intel Corporation. All rights reserved
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
# CPU DXE Libraries
#
$(PROJECT_CPU_ROOT)\Protocol\CpuProtocolLib.inf
$(PROJECT_CPU_ROOT)\Guid\CpuGuidLib.inf
$(PROJECT_CPU_ROOT)\Library\Thunklib\Thunklib.inf
$(PROJECT_CPU_ROOT)\Library\CpuPlatformLib\CpuPlatformLib.inf
$(PROJECT_CPU_ROOT)\Library\BootGuardLib\BootGuardLib.inf

#
# DTS DXE Libraries
#
$(PROJECT_CPU_ROOT)\SampleCode\Library\SmmIo\SmmIoLib.inf
$(PROJECT_CPU_ROOT)\SampleCode\Library\AslUpdate\Dxe\DxeAslUpdateLib.inf
$(PROJECT_CPU_ROOT)\SampleCode\Library\DTSHookLib\Smm\DTSHookLib.inf
$(PROJECT_CPU_ROOT)\SampleCode\Library\Ksc\Smm\SmmKscLib.inf

#
# Sample Code
#
$(PROJECT_CPU_ROOT)\SampleCode\Protocol\CpuSampleProtocolLib.inf
$(PROJECT_CPU_ROOT)\SampleCode\Library\BootGuardRevocationLib\Dxe\BootGuardRevocationLib.inf