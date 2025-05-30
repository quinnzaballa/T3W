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

// DATA ARRAY CONF IMM
#define T3W_ARR_DATA        "( 4 * 0 )\n"
#define T3W_ARR_ADDR        "( 4 * 1 )\n"
#define T3W_ARR_CE          "( 4 * 2 )\n"
#define T3W_ARR_IO          "( 4 * 3 )\n"
#define T3W_ARR_CLK         "( 4 * 4 )\n"
#define T3W_ARR_PINB        "( 4 * 5 )\n"
#define T3W_ARR_CE_MUX      "( 4 * 6 )\n"
#define T3W_ARR_IO_MUX      "( 4 * 7 )\n"
#define T3W_ARR_CLK_MUX     "( 4 * 8 )\n"
#define T3W_ARR_CE_CONF     "( 4 * 9 )\n"
#define T3W_ARR_IO_CONF     "( 4 * 10 )\n"
#define T3W_ARR_CLK_CONF    "( 4 * 11 )\n"
#define T3W_ARR_BANK1       "( 4 * 12 )\n"
#define T3W_ARR_BANK2       "( 4 * 13 )\n"

// ##### ASM GLOBAL NAME (MACRO) #####
#define T3W_ASM_TIMER_CALL8 "call8 T3W_TIMER_A2_CALL\n"             // Global name for T3W_TIMER