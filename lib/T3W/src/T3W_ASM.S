#include "config/t3wasm.define.h"

.section .flash.text, "ax"
.global T3W_TIMER_A2_CALL, T3W_WRITE_SINGLE

.global TEST_ASM
.hidden __T3W_PINB__

// TODO CLEAN UP NAMES, COMMENTS, and CATEGORIES. Make it readable

// ##### TIMER T3W ##### //
.align 4
T3W_TIMER_A2_CALL:
    entry a1, NOALLOC               // Entry but dont allocate anything
_T3W_TIMER_A2_CALL:
    addi a2, a2, -1                 // Subtract 1 per loop
    bnez a2, _T3W_TIMER_A2_CALL     // Jmp if not zero
    retw                            // Return window
// ##### END OF TIMER T3W ##### //

/* ##### LOAD PINB to Boolean Registers ( HIDDEN ) ##### */
.align 4
/**
 * @cond
 * 
 * @brief This code always expect that the GPIO BA and DATA ARR CONFIG BA
 *  is just behind the allocated stack. So dont fiddle around with the
 *  base code unless yk what youre doing.
 * 
 * @endcond
 */
__T3W_PINB__:
    entry a1, ALLOC16               // Entry + Alloc 16

    s32i a2, a1, 0                  // PUSH : A2, A3, A7
    s32i a3, a1, 4                  // ^^^
    s32i a7, a1, 8                  // ^^
    
    l32i a2, a1, ALC16OS(0)    // Load GPIO BA
    l32i a7, a1, ALC16OS(1)    // Load DATA ARR CONFIG BA

    l32i a3, a7, T3W_ARR_PINB       // Lad PINB
    wsr.br a3                       // Store data to Boolean Regs

    l32i a7, a1, 8                  // POP : A2, A3, A7
    l32i a3, a1, 4                  // ^^^
    l32i a2, a1, 0                  // ^^

    retw
/* ----- LOAD PINB to Boolean Registers ( HIDDEN ) ----- */

/* ##### CRITICAL ASM FUNCTIONS ##### */
.align 4
/**
 * @cond
 * 
 * @brief This code expects that the stack that the Base Address
 *  Located IS JUST behind the Allocated Stack... DONT touch unless
 *  You know what youre doing.
 * 
 * @endcond
 */
T3W_WRITE_SINGLE:
    entry a1, NOALLOC   // Dont allocate
    __LDADDR__ASM__     // Lodaddr | Expects no entry allocation

    call12 __T3W_PINB__     // Store PINB to boolean registers
    
    __T3W_CE_ENABLE__ASM__  // Enable CE

    __T3W_CE_DISABLE__ASM__
    
    retw

/* ----- CRITICAL ASM FUNCTIONS ----- */

/* TEST ONLY FUNCTION */
.align 4
TEST_ASM:
    entry a1, 0
    l32i a2, a1, 0
    l32i a7, a1, 4

    call12 __T3W_PINB__

    // Code here



    retw