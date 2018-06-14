## @file
#  This is the build description file containing the IIO library modules.
#  This should be included in a [Libraries] section of the DSC files for a platform build.
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
#  This file contains a 'Sample Driver' and is licensed as such
#  under the terms of your license agreement with Intel or your
#  vendor.  This file may be modified by the user, subject to
#  the additional terms of the license agreement
#

$(PROJECT_SA_ROOT)\Guid\SaGuidLib.inf
$(PROJECT_SA_ROOT)\Ppi\IntelSaPpiLib.inf
$(PROJECT_SA_ROOT)\SampleCode\Ppi\IntelSaSampleCodePpiLib.inf

#
# Typically the sample code referenced will be available in the code base already
# So keep this include at the end to defer to the source base definition
# and only use the sample code definition if source base does not include these files.
#
