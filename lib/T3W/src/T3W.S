.section .iram1, "ax"   // 'a' = alloc, 'x' = executable
.align 4                // Align code if you want..
// dummy label; This is for global name functions.
.global dummylbl, T3W_TIMER_A2_CALL

dummylbl:   // No purpose really
    nop

.align 4
T3W_TIMER_A2_CALL:
    entry a1, 0                     // Don't Allocate anything
_T3W_TIMER_A2_CALL:                 // Internal loop
    addi a2, a2, -1                 // overall cycles is 2 + 1 for window return
    bnez a2, _T3W_TIMER_A2_CALL     // i.e. TIMER call (a2 = 12 loop); 50ns + 4.167 (240MHz) = 54ns 
    retw