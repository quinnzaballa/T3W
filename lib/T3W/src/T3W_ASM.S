.section .flash.text, "ax"
.global T3W_TIMER_A2_CALL, T3W_CE_EN, T3W_CE_DS, TEST
.hidden CE_IO2

// ##### TIMER T3W ##### //
.align 4
T3W_TIMER_A2_CALL:
    entry a1, 0                     // Entry but dont allocate anything
_T3W_TIMER_A2_CALL:
    addi a2, a2, -1                 // Subtract 1 per loop
    bnez a2, _T3W_TIMER_A2_CALL     // Jmp if not zero
    retw                            // Return window
// ##### END OF TIMER T3W ##### //

// ##### CE CONTROL ##### //
// Note :   This always expect Base Addresses are stored in stack.
//          It must follow this stack map:
//          0x00 = GPIO BASE ADDRESS.
//          0x04 = DATA ARRAY BASE ADDRESS.

// ##### CE ENABLE ##### //
.align 4
T3W_CE_EN:  // Enable CE ( Chip Enable )
    entry a1, 0     // Dont allocate anything

    l32i a2, a1, 0  // Load base addresses
    l32i a7, a1, 4  // ^^^

    l32i a3, a7, ( 4 * 2 )          // Load data CE PINBIT
    l32i a5, a7, ( 4 * 5 )          // Load PINB

    // CE GPIO PROCESS
    bbsi a5, 0x00, CE_IO2_EN        // Check PINB IF CE is BANK2

    s32i a3, a2, 0x08               // Enable pin BANK 1
    j EOC_CE_EN

CE_IO2_EN:
    s32i a3, a2, 0x14               // Enable pin BANK 2
    j EOC_CE_EN

EOC_CE_EN:
    retw            // Return Window
// ##### END OF CE ENABLE ##### //

// ##### CE DISABLE ##### //
.align 4
T3W_CE_DS:  // Enable CE ( Chip Enable )
    entry a1, 0     // Dont allocate anything

    l32i a2, a1, 0  // Load base addresses
    l32i a7, a1, 4  // ^^^

    l32i a3, a7, ( 4 * 2 )          // Load data CE PINBIT
    l32i a5, a7, ( 4 * 5 )          // Load PINB

    // CE GPIO PROCESS
    bbsi a5, 0x00, CE_IO2_DS        // Check PINB IF CE is BANK2

    s32i a3, a2, 0x0C               // Enable pin BANK 1
    j EOC_CE_DS

CE_IO2_DS:
    s32i a3, a2, 0x18               // Enable pin BANK 2
    j EOC_CE_DS

EOC_CE_DS:
    retw            // Return Window
// ##### END OF CE DISABLE ##### //

// ##### WRITE SINGLE ##### //

TEST:
    nop
    nop
    nop