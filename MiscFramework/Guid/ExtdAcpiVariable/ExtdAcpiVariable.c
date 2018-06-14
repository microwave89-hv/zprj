/*--
Module Name:
  
   AcpiVariable.c
    
Abstract:

   GUIDs used for ACPI variables.

--*/

#include "Tiano.h"
#include EFI_GUID_DEFINITION (ExtdAcpiVariable)

EFI_GUID  gEfiExtdAcpiVariableGuid = EFI_EXTD_ACPI_VARIABLE_GUID;

EFI_GUID_STRING(&gEfiExtdAcpiVariableGuid, "ACPI Varigable", "ACPI 2.0 Variable GUID");
