/**
 * @file t3w.config.h
 * @brief This contains the T3W Configuration, Settings, etc.
 * 
 * @note This config is coded to 240MHz and will implement 160MHz later
 * 
 * @author Quinn Matthew C. Zaballa
 * @link https://github.com/quinnzaballa
 * @date 5/29/2025
 */

#pragma once

#define T3W_MCU_HZ         240000000.0                         // MCU CPU Speed in HZ ( default: 240MHz )
#define T3W_PER_TICK       ( 1.0 / T3W_MCU_HZ ) * 1e9          // Get the time per clk ( 4.167nS at 240MHz )

// ##### ASM GLOBAL NAME (MACRO) #####
#define T3W_ASM_CALL8 "call8 T3W_TIMER_A2_CALL\n"              // Global name for T3W_TIMER