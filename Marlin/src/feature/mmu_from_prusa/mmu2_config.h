/// @file
#pragma once

// Include the correct MMU2 config based on the printer variant.
// #include "Configuration_var.h"
// #include MMU_CONFIG_FILE
// #if HAS_PRUSA_MMU3 || HAS_PRUSA_MMU2S
#include "mmu2/variants/config_MMU2S.h"
// #elif HAS_PRUSA_MMU2
//     #include "mmu2/variants/config_MMU2.h"
// #endif