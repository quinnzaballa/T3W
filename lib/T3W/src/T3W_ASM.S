#include "config/t3wasm.config.h"

.section .flash.text, "ax"
.global T3W_TIMER_A2_CALL, __PINB__ASM___
.hidden CE_IO2

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
__PINB__ASM___:
    entry a1, ALLOC16               // Entry but dont allocate anything

    s32i a2, a1, 0                  // PUSH : A2, A3, A7
    s32i a3, a1, 4                  // ^^^
    s32i a7, a1, 8                  // ^^
    
    l32i a2, a1, ALC16OS(0)         // Load GPIO BA
    l32i a7, a1, ALC16OS(1)         // Load DATA ARR CONFIG BA

    l32i a3, a7, T3W_ARR_PINB       // Lad PINB
    wsr.br a3                       // Store data to Boolean Regs

    l32i a7, a1, 8                  // POP : A2, A3, A7
    l32i a3, a1, 4                  // ^^^
    l32i a2, a1, 0                  // ^^

    retw
/* ----- LOAD PINB to Boolean Registers ( HIDDEN ) ----- */