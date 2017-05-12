#include "console.h"
#include "timer.h"

void main(void) 
{
    console_init(24, 40);

    console_printf("GREETINGS PROFESSOR FALKEN\n");
    console_printf("\n");
    delay_ms(2000);
    console_printf("HELLO\n");
    console_printf("\n");
    delay_ms(2000);
    console_printf("A STRANGE GAME\n");
    delay_ms(2000);
    console_printf("THE ONLY WINNING MOVE IS\n");
    delay_ms(2000);
    console_printf("NOT TO PLAY\n");
    console_printf("\n");
    delay_ms(2000);
    console_printf("HOW ABOUT A NICE GAME OF CHESS?\n");
    delay_ms(2000);
}

