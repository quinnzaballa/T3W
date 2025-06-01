.section .iram1.text, "ax"
.global T3W_TIMER_A2_CALL

// ##### TIMER T3W #####
.align 4
T3W_TIMER_A2_CALL:
    entry a1, 0                     // Entry but dont allocate anything
_T3W_TIMER_A2_CALL:
    addi a2, a2, -1                 // Subtract 1 per loop
    bnez a2, _T3W_TIMER_A2_CALL     // Jmp if not zero
    retw                            // Return window

// IO latch processing...
// REG USED:    A5 RESERVED
//              A6 IO BITPIN
//              A7 DATA CONF ARRAY BASE ADDRESS
LATCHIO:
    l32i a5, a7, ( 4 * 5 )      // Load PINB
    
    beqz a6, IO0                // Check if IO or a6 is 0.

    // ### This section is when IO is 1. ### //

    bbsi a5, 0x2, L0_IO1        // Check PINB IO is stored in BANK 2
    s32i a6, a2, 0x08           // Write 1 to SET bank 1 out
    j EOC
        
L0_IO1:
    s32i a6, a2, 0x14           // Write 1 to SET bank 2 out
    j EOC

    // ### This section is when IO is 0. ### //

IO0:
    bbsi a5, 0x2, L0_IO0        // Check PINB IO is stored in BANK 2
    s32i a6, a2, 0x0C           // Write 1 to SET bank 1 out
    j EOC
        
L0_IO0:
    s32i a6, a2, 0x18           // Write 1 to SET bank 2 out
    j EOC

EOC:
    retw