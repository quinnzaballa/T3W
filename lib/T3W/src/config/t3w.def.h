#pragma once

/**
 * @file t3w.def.h
 * @brief Contains the important Definition for the t3w to work.
 *  on this current Defined names are defaulted to ESP32-S3 Reg-
 *  isters..
 * 
 * @author Quinn Matthew C. Zaballa
 * @link https://github.com/quinnzaballa
 * @date 5-29-2025
 */

#include "sdkconfig.h"  // Definition Header
#include "soc/soc.h"

// ESP32-S3
#ifdef CONFIG_IDF_TARGET_ESP32S3

// ##### GPIO BASE ADDRESS CONFIGURATION #####
#define T3W_REG_GPIO_BA     DR_REG_GPIO_BASE    // Base Address of GPIO
// #define T3W_REG_IOMUX_BA    DR_REG_IO_MUX_BASE  // Base Address of IO MUX || [REMOVED : use T3W_REG_IOMUX_BO instead]
// ##### END OF GPIO BASE ADDRESS CONFIGURATION #####


// ##### GPIO OFFSET #####
#define T3W_REG_IOCONF_BO   DR_REG_GPIO_BASE + 0x74     // IO CONFIGURATION; OFFSET
#define T3W_REG_IOMUX_BO    DR_REG_IO_MUX_BASE + 0x04   // IO MUX; OFFSET
#define T3W_OUT_REG         0x04                // GPIO OUT REG : 1
#define T3W_OUT_W1TS_REG    0x08                // GPIO OUT WRITE 1 TO SET : 1
#define T3W_OUT_W1TC_REG    0x0C                // GPIO OUT WRITE 1 TO CLR : 1
#define T3W_OUT1_REG        0x10                // GPIO OUT REG : 2
#define T3W_OUT1_W1TS_REG   0x14                // GPIO OUT WRITE 1 TO SET : 2
#define T3W_OUT1_W1TC_REG   0x18                // GPIO OUT WRITE 1 TO CLR : 2
#define T3W_EN_REG          0x20                // GPIO ENABLE REGISTER : 1
#define T3W_EN_W1TS_REG     0x24                // GPIO ENABLE WRITE 1 TO SET : 1
#define T3W_EN_W1TC_REG     0x28                // GPIO ENABLE WRITE 1 TO CLR : 1
#define T3W_EN1_REG         0x2C                // GPIO ENABLE REGISTER : 2
#define T3W_EN1_W1TS_REG    0x30                // GPIO ENABLE WRITE 1 TO SET : 2
#define T3W_EN1_W1TC_REG    0x34                // GPIO ENABLE WRITE 1 TO CLR : 2
#define T3W_IN_GPIO_REG     0x3C                // GPIO IN REGISTER : 1
#define T3W_IN1_GPIO_REG    0x40                // GPIO IN REGISTER : 2
// ##### END OF GPIO OFFSET #####

#endif // <- CONFIG_IDF_TARGET_ESP32S3