.section .iram1.text, "ax"
.global T3W_TIMER_A2_CALL
.align 4

// ##### TIMER T3W #####
.align 4
T3W_TIMER_A2_CALL:
    entry a1, 0                     // Entry but dont allocate anything
_T3W_TIMER_A2_CALL:
    addi a2, a2, -1                 // Subtract 1 per loop
    bnez a2, _T3W_TIMER_A2_CALL     // Jmp if not zero
    retw                            // Return window

