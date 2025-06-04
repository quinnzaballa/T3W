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

// TODO CLEAN UP NAMES, COMMENTS, and CATEGORIES. Make it readable

/* INCLUDES */
#include "config/t3w.def.h"
#include "config/t3w.config.h"

/* INTERNAL DEFINE */
/**
 * @cond
 * 
 * @brief This section contains local Define name for the T3W ASM.
 *  I MUST KEEP the name Short as possible.. probably 7-8 chars.. 
 * 
 * @endcond
 */

/* ##### DEFINE FORMULAS ##### */
#define NOALLOC 0   // NO ALLOCATION
#define ALLOC16 16  // ALLOCATE 16 BYTES
#define ALC16OS(x) 16 + ( 4 * x )   // Access stack after the allocated stack
/* ----- END OF DEFINE FORMULAS ----- */

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                      MACRO ASM                                       //
//                                                                                      //
//--------------------------------------------------------------------------------------//

/**
 * @cond
 * 
 * @brief This contains MACRO ASM's like it says up there.
 *  Technically its just inline asm and pure asm for .S files.
 *  This makes the code easier to maintain and view.
 * 
 * @endcond
 */

//--------------------------------------------------------------------------------------//
//                                         ASM                                          //
//--------------------------------------------------------------------------------------//

/**
 * @cond
 * 
 * @brief This 2 parts enables and disable CE by ASM (RAW)
 * 
 * @endcond
 */
#define __T3W_CE_ENABLE__ASM__ \
    mov a3, a2; \
    bf b0, 1f; \
    addi a3, a3, 0x0C; \
    1: \
    addi a3, a3, 0x08; \
    l32i a4, a7, T3W_ARR_CE; \
    s32i a4, a3, 0x00;

#define __T3W_CE_DISABLE__ASM__ \
    mov a3, a2; \
    bf b0, 1f; \
    addi a3, a3, 0x0C; \
    1: \
    addi a3, a3, 0x0C; \
    l32i a4, a7, T3W_ARR_CE; \
    s32i a4, a3, 0x00;

/**
 * @cond
 * 
 * @brief LODADDR w/ 16byte stack allocation
 * 
 * @endcond
 */
#define __LDADDR16__ASM__ \
    l32i a2, a1, ALC16OS(0); \
    l32i a7, a1, ALC16OS(1);

/**
 * @cond
 * 
 * @brief LODADDR
 * 
 * @endcond
 */
#define __LDADDR__ASM__ \
    l32i a2, a1, 0; \
    l32i a7, a1, 4;


//--------------------------------------------------------------------------------------//
//                                      INLINE ASM                                      //
//--------------------------------------------------------------------------------------//

/**
 * @cond
 * 
 * @brief This 2 parts enables and disable CE by inline asm.
 * 
 * @endcond
 */
#define __T3W_CE_ENABLE__ASM_INLINE__ \
    __asm__ volatile( \
        "mov a3, a2\n" \
        "bf b0, CE_BANK\n" \
        "addi a3, a3, 0x0C\n" \
        "CE_BANK:\n" \
        "addi a3, a3, 0x08\n" \
        "l32i a4, a7, T3W_ARR_CE\n" \
        "s32i a4, a3, 0x00" \
        : \
        : \
        :   "a3", "a4" \
    );

#define __T3W_CE_DISABLE__ASM_INLINE__ \
    __asm__ volatile( \
        "mov a3, a2\n" \
        "bf b0, CE_BANK\n" \
        "addi a3, a3, 0x0C\n" \
        "CE_BANK:\n" \
        "addi a3, a3, 0x0C\n" \
        "l32i a4, a7, T3W_ARR_CE\n" \
        "s32i a4, a3, 0x00" \
        : \
        : \
        : "a3", "a4" \
    );

/**
 * @cond
 * 
 * @brief Just timers...
 * 
 * @endcond
 */
#define T3W_ASM_TIMER_CALL8(x)  __asm__ volatile(                   \
                                    "movi a10," T3W_EXPD_NSTRNL(x)  \
                                    "call8 T3W_TIMER_A2_CALL"       \
                                    :                               \
                                    :                               \
                                    :   "a8", "a10"                 \
                                );
#define T3W_ASM_TIMER_CALL0(x)  __asm__ volatile(                   \
                                    "movi a3," T3W_EXPD_NSTRNL(x)   \
                                    "call0 T3W_TIMER_A2_CALL"       \
                                    :                               \
                                    :                               \
                                    :   "a0", "a3"                  \
                                );


/**
 * @cond
 * 
 * @brief Clobber all registers a0-a15
 * 
 * @endcond
 */
#define T3W_CLOBBER_ALL __asm__ volatile("" ::: "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10", "a11", "a12", "a13", "a14", "a15");
