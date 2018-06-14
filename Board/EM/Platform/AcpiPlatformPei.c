//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/AcpiPlatformPei.c 1     2/09/12 12:30a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/09/12 12:30a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/AcpiPlatformPei.c $
// 
// 1     2/09/12 12:30a Yurenlai
// Initial check in.
// 
//*************************************************************************
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:        ACPIPLATFORM.C
//
// Description: Installs EFI_GLOBAL_NVS_AREA_PROTOCOL_GUID
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Efi.h>
#include <Pei.h>
#include <token.h>
#include <AmiLib.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
//#include <NB.h>
#include <Ppi\Stall.h>

#define  MC_MMIO_CSHRDDR3CTL       0x1E8
#define  MC_RESET_CONTROL          0x05C 
#define  IMC_DEV                   3
#define  IMC_FUNC                  0

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	AcpiPlatformPeiInit
//
// Description:
//
// Input:
//
// Output:
//      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//  Here is the control flow of this function:
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS 
AcpiPlatformPeiInit (
	IN EFI_FFS_FILE_HEADER		*FfsHeader,
	IN EFI_PEI_SERVICES		**PeiServices
  )
{
/*
  EFI_STATUS             Status ;
  UINT32                 Buffer32;
  EFI_BOOT_MODE          BootMode;
  EFI_PEI_STALL_PPI      *StallPpi;
  EFI_GUID               StallPpiGuid = EFI_PEI_STALL_PPI_GUID;

  UINT32                 RegEAX, RegEBX, RegECX, RegEDX;
  UINT8                  MaxBusNumber;
  EFI_PEI_PCI_CFG_PPI    *PciCfg;

  // Determine boot mode
  Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
  ASSERT_PEI_ERROR(PeiServices, Status);

//Config GPIO, CRB use GPIO46 as output and drive it to logic high for S5/S0 boot path

  Buffer32 = IoRead32(GPIO_BASE_ADDRESS + ICH_GPIO_USE_SEL2);  // GPIO USE Select 2 Register
  Buffer32 |= 0x00004000;
  IoWrite32(GPIO_BASE_ADDRESS + ICH_GPIO_USE_SEL2, Buffer32);  // Singal used as a GPIO

  Buffer32 = IoRead32(GPIO_BASE_ADDRESS + ICH_GPIO_IO_SEL2);   // GPIO Input/Output Select 2 Register
  Buffer32 &= 0xFFFFBFFF;
  IoWrite32(GPIO_BASE_ADDRESS + ICH_GPIO_IO_SEL2, Buffer32);   // Program GPIO as a Output

  if(BootMode == BOOT_WITH_FULL_CONFIGURATION || BootMode == BOOT_ON_S5_RESUME){
  Buffer32 = IoRead32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2);   // GPIO Level Select 2 Register
  Buffer32 |= 0x00004000;
  IoWrite32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2, Buffer32);   // Program GPIO level drive to logic high

  } // BootMode == BOOT_WITH_FULL_CONFIGURATION || BootMode == BOOT_ON_S5_RESUME


  if(BootMode == BOOT_ON_S3_RESUME){
  // Locate PPI stall service
  Status = (**PeiServices).LocatePpi(PeiServices,
                                     &StallPpiGuid,
                                     0,
                                     NULL,
                                     &StallPpi);

  ASSERT_PEI_ERROR (PeiServices, Status);

   CPULib_CpuID(1, &RegEAX, &RegEBX, &RegECX, &RegEDX);

     if (((RegEAX & CPUID_FULL_FAMILY_MODEL) == CPUID_FULL_FAMILY_MODEL_DALES) ||
        ((RegEAX & CPUID_FULL_FAMILY_MODEL) == CPUID_FULL_FAMILY_MODEL_DALES_32NM)) {  
          // Write MCHBAR + 0x1E8[2:0] = '110' to de-assert DDR_RESET#, 
          // this should be followed by a write to MCHBAR + 0x1E8[2:0] = '100' 
          // to maintain the state of the DDR_RESET# signal for future accesses to this register.
          Mmio32(MCH_BASE_ADDRESS, MC_MMIO_CSHRDDR3CTL) &= ~(BIT2|BIT1|BIT0);
          Mmio32(MCH_BASE_ADDRESS, MC_MMIO_CSHRDDR3CTL) |= (BIT2|BIT1);
          Mmio32(MCH_BASE_ADDRESS, MC_MMIO_CSHRDDR3CTL) &= ~(BIT2|BIT1|BIT0);
          Mmio32(MCH_BASE_ADDRESS, MC_MMIO_CSHRDDR3CTL) |= (BIT2);

          //
          // wait 50ms delay
          //
          StallPpi->Stall(PeiServices,
                          StallPpi,
                          50000);

          //Drive GPIO 46 high

          //
          // Set GP_LVL2 Register
          //
          Buffer32 = IoRead32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2);   // GPIO Level Select 2 Register
          Buffer32 |= 0x00004000;
          IoWrite32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2, Buffer32);   // Program GPIO level drive to logic high

     } else if ((RegEAX & CPUID_FULL_FAMILY_MODEL) == CPUID_FULL_FAMILY_MODEL_FIELDS) {
          //
          // Set BIOS_RESET_ENABLE in MC_RESET_CONTROL register
          //

          //
          // EFI_PCIEXBAR MSR 0x300 - BIT3 | BIT2 | BIT1
          //
         PciCfg = (*PeiServices)->PciCfg;

         switch ((((UINT8)ReadMsr(0x300)) & (0xE)) >> 1) 
         {
               default:
               case 0x00:
                         MaxBusNumber = 0xFF;
                         break;

               case 0x07:
                         MaxBusNumber = 0x7F;
                         break;

               case 0x06:
                         MaxBusNumber = 0x3F;
                         break;
          }

          PciCfg->Read(
                  PeiServices,
                  PciCfg,
                  EfiPeiPciCfgWidthUint32,
                  PEI_PCI_CFG_ADDRESS(MaxBusNumber, 3, 0, MC_RESET_CONTROL),
                  &Buffer32);

          Buffer32 |= (BIT0);

          PciCfg->Write(
                  PeiServices,
                  PciCfg,
                  EfiPeiPciCfgWidthUint32,
                  PEI_PCI_CFG_ADDRESS(MaxBusNumber, 3, 0, MC_RESET_CONTROL),
                  &Buffer32);

          // MmPci16(MaxBusNumber, IMC_DEV, IMC_FUNC, MC_RESET_CONTROL) |= (BIT0);

          //
          // wait 50ms delay
          //
          StallPpi->Stall(PeiServices,
                          StallPpi,
                          50000);

          //Drive GPIO 46 high

          //
          // Set GP_LVL2 Register
          //
          Buffer32 = IoRead32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2);   // GPIO Level Select 2 Register
          Buffer32 |= 0x00004000;
          IoWrite32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2, Buffer32);   // Program GPIO level drive to logic high
     } 

  } // BootMode == BOOT_ON_S3_RESUME
*/
  return EFI_SUCCESS;
}


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
