#pragma once

/**
 * @file t3wasm.config.h
 * @brief This contains the definition locally on the asm.. DONT TOUCH ANYTHING HERE
 *  UNLESS YOU KNOW WHAT YOURE DOING.
 * 
 * @note Just 1 sentence. Dont touch anything unless you know it..
 * 
 * @author Quinn Matthew C. Zaballa
 * @link https://github.com/quinnzaballa
 * @date 6-2-2025
 */

/* INCLUDES */
#include "config/t3w.def.h"
#include "config/t3w.config.h"

/* INTERNAL DEFINE */
/**
 * @cond
 * 
 * @brief This section contains local Define name for the T3W ASM.
 *  I MUST KEEP the name Short as possible.. probably 7-8 chars.. 
 */

#define NOALLOC 0   // NO ALLOCATION
#define ALLOC16 16  // ALLOCATE 16 BYTES
#define ALC16OS(x) 12 + ( 4 * x )   // Access stack after the allocated stack
