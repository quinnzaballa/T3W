# T3W - Driver

### Introduction
This project was made because i'm bored. Nothing's wrong with that in the first place, Right?

</br>
So it was created because i wanted to control DS1302 and create a driver by myself, Handle the GPIO and it's configurations. I thought on myself that why not make it dynamic and change it's timing configuration whilst being independent. So here it is, hopefully i won't give up on this simple code.

## TODO

[ ] : Configurator function
    - Configure GPIO pin
    - Skip GPIO that is not allowed to be changed. ( pull-'up/down', open-drain, & 
    open-drain )
    - Write to the volatile array that holds important config and components.

## MEMORY MAP
### GPR 'as' MAP
|   GPR     |   PURPOSE     |   COMMENTS    |
|-----------|---------------|---------------|
|   a0      |   RET ADDR    |   Return address commonly used by call0 and callx0    |
|   a1      |   STACK PTR   |   Stack Pointer   |
|   a2      |   ADDR PTR    |   Address pointer used by the T3W driver  |
|   a3      |   Source.1    |   Source #1 used by the T3W driver    |
|   a4      |   Source.2    |   Source #2 used by the T3W driver    |
|   a5      |   (A/C/C).1   |   Arithmetic, Compare, & Counter #1 Register used by the T3W driver |
|   a6      |   (A/C/C).2   |   Arithmetic, Compare, & Counter #2 Register used by the T3W driver |
|   a7      |  ADDR PTR ARR |   Address pointer to ARRAY config data    |
|  a8-9     |   RESERVED    |   N/A |
|   a10     |   (A/C/C).3   |   Arithmetic, Compare, & Counter #3 Register used by the T3W driver |
|  a11-15   |   UNUSED      |   Not used by the T3W driver  |

</br>

### ARRAY DATA CONF MAP
> Size is Unsigned 32bit

</br>

|   NUM. OFFSET ( Human Readable ~ Memory View( NUM ~ HEX ) )    |   NAME/PURPOSE    |   COMMENTS    |
|---------------------------------------------------------------|-------------------|---------------|
|       1       ~       0       ~       0x00                    |   DATA            |   Data holder what to write   |
|       2       ~       1       ~       0x04                    |   ADDRESS         |   Similar to Data holder  |
|       3       ~       2       ~       0x08                    |   CE              |   Chip Select pin BANK CONF |
|       4       ~       3       ~       0x0C                    |   IO              |   In & Out pin BANK CONF |
|       5       ~       4       ~       0x10                    |   CLK             |   Clock pin BANK CONF |
|       6       ~       5       ~       0x14                    |   PINB            |   GPIO BANK DIFF CONF |
|       7       ~       6       ~       0x18                    |   CE MUX          |   CE : IO MUX BASE ADDR + OFFSET |
|       8       ~       7       ~       0x1C                    |   IO MUX          |   IO : IO MUX BASE ADDR + OFFSET |
|       9       ~       8       ~       0x20                    |   CLK MUX         |   CLK : IO MUX BASE ADDR + OFFSET |
|      10       ~       9       ~       0x24                    |   CE CONFIG       |   CE : IO CONFIG BASE ADDR + OFFSET |
|      11       ~      10       ~       0x28                    |   IO CONFIG       |   IO : IO CONFIG BASE ADDR + OFFSET |
|      12       ~      11       ~       0x2C                    |   CLK CONFIG      |   CLK : IO CONFIG BASE ADDR + OFFSET |
|      13       ~      12       ~       0x30                    |   B1              |   BANK 1 GPIO |
|      14       ~      13       ~       0x34                    |   B2              |   BANK 2 GPIO |