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

.align 4
/* CHIP ENABLE CONTROL */
T3W_CE_CONTROL:
    entry a1, ALLOC16       // Allocate 16 byte.
    
    s32i a5, a1, 0          // Store a5 to stack
    l32i a5, a1, ALC16OS(0) // Get the Setting
    
    /* CE ENABLE SECTION */
    