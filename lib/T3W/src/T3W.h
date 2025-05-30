/**
 * @file T3W.h
 * @brief This file contains the driver for 3-Wire communication.
 * 
 * @note Changing anything here without knowing how it works will break something
 *  or  a  silent break would occur. Please analyze the code before proceeding to
 *  modify this code.
 * 
 * @author Quinn Matthew C. Zaballa
 * @link https://github.com/quinnzaballa
 * @date 5/29/2025
 */

#include "config/t3w.config.h"      // Program Config
#include "config/t3w.def.h"         // Program Definition(s)
#include "stdint.h"                 // Typedefs

// ##### PROTOTYPES ##### //
/**
 * @brief Enable and Disable Interrupt
 * 
 * @note when re-enabling the INTR. prevps MUST HAVE A VALUE that is the last value of ps.
 *   not following this will cause unexpected cpu behaviour.
 * 
 * @param type 0 = Disable INTR, 1 = Enable INTR
 * @param prevps Where to store and write previous PS data reg
 */
void T3W_INTR(bool type, uint32_t &prevps);
/**
 * @brief Disable open-drain and pull-'up/down'
 */
void T3W_SET_WPX_OD_0();
/**
 * @brief Initializes the pins and initialize T3W_CONF_ARR
 * 
 * @note on ESP32-S3 You cannot set above and below 21 and 26. Refer to the esp32 s3 manual.
 * 
 * @param CE Chip Select pin
 * @param IO Data pin
 * @param CLK Clock pin
 * 
 */
void T3W_CONFIG_INIT(int CE, int IO, int CLK); // T3W Configurator.
/**
 * @brief This function is used to write 2bytes on target chip. ( 1bytes for address & 1bytes for data )
 * 
 * @note This function is critical. meaning it links to the DATA CONFIG, If it wasnt initialized. it may cause
 *  unexpected results.
 * 
 * @param address address to write to the chip
 * @param data data to write to the chip 
 */
void T3W_WRS(uint8_t address, uint8_t data);

// ##### ARRAY DATA CONFIG ##### //

/**
 * @brief Data configuration and semi-imm
 */
volatile uint32_t __attribute__((aligned(4))) T3W_CONF_ARR[14] = {
    0x00,       // DATA         0
    0x00,       // ADDRESS      1
    0x00,       // CE           2
    0x00,       // IO           3
    0x00,       // CLK          4
    0x00,       // PINB         5
    0x00,       // CE MUX       6
    0x00,       // IO MUX       7
    0x00,       // CLK MUX      8
    0x00,       // CE CONFIG    9
    0x00,       // IO CONFIG    10
    0x00,       // CLK CONFIG   11
    0x00,       // BANK 1       12
    0x00        // BANK 2       13
};  // Align 4 bytes; Volatile; Declared Name: T3W_CONF_ARR; Memory Allocation: 14.n/13.n-1/34bytes

void T3W_INTR(bool type, uint32_t &prevps) {
    if ( type ) {
        // Write INTR using prevps value
        __asm__ volatile(
            "wsr.ps %0\n"
            "rsync"
            : // No output
            :   "r" (prevps) 
            : // No clobbers
        ); 
    } else {
        __asm__ volatile(
            "rsil %0, 15\n"
            "rsync"
            :   "=r" (prevps)
            : // No input
            : // No clobbers
        );
    }

    return; // return to user
}

void T3W_SET_WPX_OD_0() {
    for ( int i = 0; i < 3; i++ ) {
        __asm__ volatile(
            "mov a2, %[IOMUXA]\n"       // Load the ADDRESS of IO MUX PIN ADDR
            "movi a3, 0xFFFFFE7F\n"     // Mov immediate value to disable Pull-'up/down'

            "l32i a5, a2, 0\n"          // Get the current state of IO MUX register pin

            "and a3, a3, a5\n"          // Bitwise and the values, technically masking everything except for the WPD/WPU

            "s32i a3, a2, 0"            // Store the value back to the IO MUX register pin
            :
            :   [IOMUXA] "r" (T3W_CONF_ARR[ 6 + i ])
            :   "a2", "a3", "a5"
        ); // <- Set Pull-'up/down' to disable

        __asm__ volatile(
            "mov a2, %[IOCONFA]\n"      // Load the ADDRESS of IO CONF pin ADDR
            "movi a3, 0xFFFFFFFB\n"     // Mov immediate value to disable open-drain

            "l32i a5, a2, 0\n"          // Get the current state of IO CONF register pin

            "and a3, a3, a5\n"          // Bitwise and the values, technically masking everything except for the WPD/WPU

            "s32i a3, a2, 0"            // Store the value back to the IO CONF register pin
            :
            :   [IOCONFA] "r" (T3W_CONF_ARR[ 9 + i ])
            :   "a2", "a3", "a5"
        ); // <- Disable Open Drain
    }

    return;
}

void T3W_CONFIG_INIT(int CE, int IO, int CLK) {
    int pin[3] = {CE, IO, CLK}; // Store Pins to temporary array
    uint32_t prevps = 0;        // Store previous ps reg
    T3W_INTR(0, prevps);        // Disable INTR

    for ( int i = 0; i < 3; i++ ) {
        if ( pin[i] > 21 && pin[i] < 26 ) {
            __asm__ volatile(
                "temploop:\n"
                "movi a2, 0x100\n"
                "_temploop:\n"
                "beqz a2, temploop\n"
                "addi a2, a2, -1\n"
                "j _temploop"
            ); // <- No clobbers...
        }
    } // <- If its above 21 and below 26. loop with asm delay infinite...

    for ( int i = 0; i < 3; i++) {
        T3W_CONF_ARR[ 6 + i ] = ( T3W_REG_IOMUX_BO + ( 4 * pin[i] ) );      // Store ( IOMUX_BA + OFFSET )
        T3W_CONF_ARR[ 9 + i ] = ( T3W_REG_IOCONF_BO + ( 4 * pin[i] ) );     // Store ( IOCONF_BA + OFFSET )
        
        if ( pin[i] > 31 ) {
            T3W_CONF_ARR[ 2 + i ] = ( 1 << ( pin[i] - 31 ) );               // Store in Bit shift
            T3W_CONF_ARR[13] |= ( 1 << ( pin[i] - 31 ) );               // Store in Bit shift
            T3W_CONF_ARR[5] |= ( 1 << i );
        } else {
            T3W_CONF_ARR[ 2 + i ] = ( 1 << pin[i] );                        // Store in Bit shift
            T3W_CONF_ARR[12] |= ( 1 << pin[i] );               // Store in Bit shift
        }
            
    } // <- Configure data required.

    __asm__ volatile(
        "mov a7, %[ARR_DAT]\n"          // DATA ARRAY ADDRESS from 0
        "movi a2, %[GPIOBA]\n"          // GPIO BASE ADDR
        
        "l32i a5, a7," T3W_ARR_PINB     // Load PINB data from DATA ARR
        
        "beqz a5, BANK1\n"              // Check PINB if zero. This will there theres no gpio set above 31

        "l32i a5, a7," T3W_ARR_BANK2    // Get the Value from 13th data from DATA ARR; BANK 2
        "s32i a5, a2, %[ENGPIO1]\n"     // ENABLE1 GPIO OFFSET

        "BANK1:\n"
        "l32i a5, a7," T3W_ARR_BANK1    // Get the Value from 12th data from DATA ARR; BANK 1
        "s32i a5, a2, %[ENGPIO]"        // ENABLE GPIO OFFSET
        // END OF ASM CODE

        : // No output
        :   [ARR_DAT] "r" (&T3W_CONF_ARR),
            [GPIOBA] "i" (T3W_REG_GPIO_BA),
            [ENGPIO] "i" (T3W_EN_W1TS_REG),
            [ENGPIO1] "i" (T3W_EN1_W1TS_REG)
        :   "a2", "a5", "a7"
    ); // <- Put pin set as OUTPUT

    T3W_SET_WPX_OD_0();         // Disable Pull-'up/down' and Open-Drain

    T3W_INTR(1, prevps);
    return;
}

void T3W_WRS(uint8_t address, uint8_t data) {
    T3W_CONF_ARR[0] = data;     // Store the data to write
    T3W_CONF_ARR[1] = address;  // ^^^
    uint32_t prevps = 0;
    T3W_INTR(0, prevps);        // Disable INTR
    T3W_SET_WPX_OD_0();         // Disable Pull-'up/down' and Open-Drain

    __asm__ volatile("" ::: "memory");  // Sync memory...

    __asm__ volatile(
        "addi a1, a1, -8\n"     // Allocate 8 bytes or 2x 32bit data
        "movi a2, %[GPIOBA]\n"
        "mov a7, %[DATARR]\n"
        // "s32i a2, a1, 0\n"      // Store GPIO BASE ADDRESS to stack **| Remove.
        // "s32i a2, a1, 4\n"      // Store DATA ARRAY CONF to stack
        :
        :   [GPIOBA] "i" (T3W_REG_GPIO_BA),
            [DATARR] "r" (&T3W_CONF_ARR)
        : "a2", "a7"
    ); // <- Pre-load the addresses to registers.

    __asm__ volatile(
        "l32i a5, a7," T3W_ARR_PINB  // Load the pin location in bit shift
        "l32i a4, a7," T3W_ARR_CE    // Load the CE pin

        "bbsi a3, 0x1, BANK2\n"     // Check if CE is stored to bank 2

        // BANK 1
        "s32i a4, a2," T3W_EXPD_NSTR(T3W_OUT_W1TS_REG)
        "j EOC\n"

        "BANK2:\n"
        "s32i a4, a2," T3W_EXPD_NSTR(T3W_OUT1_W1TS_REG)
        "nop\n"
        "EOC:"
    ); // <- Put CE high

    return;
}