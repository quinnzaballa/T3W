#include "config/t3wasm.config.h"

.section .flash.text, "ax"
.global T3W_TIMER_A2_CALL
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

