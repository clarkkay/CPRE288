/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */

#include "ping_template.h"
#include "Timer.h"
#include "lcd.h"

volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE = LOW; // State of ping echo pulse
int count = 0;
bool intflag = true;

void ping_init (void){

  // YOUR CODE HER

    // Configure and enable the timer
    SYSCTL_RCGCGPIO_R |= 0x02;
    SYSCTL_RCGCTIMER_R |= 0x08;
    while ((SYSCTL_PRGPIO_R & 0x02) != 0x02) {};
    GPIO_PORTB_DIR_R &= ~0x08;
    GPIO_PORTB_AFSEL_R |= 0x08;
    GPIO_PORTB_PCTL_R |= 0x00007000;
    GPIO_PORTB_PCTL_R &= 0xFFFF7FFF;
    GPIO_PORTB_DEN_R |= 0x08;

    TIMER3_CTL_R &= ~0x100;
    TIMER3_CFG_R = 0x4;
    TIMER3_TBMR_R = 0x07;
    TIMER3_CTL_R |= (0x0C00);
    TIMER3_TBPR_R = 0xFF;
    TIMER3_TBILR_R = 0xFFFF;
    TIMER3_ICR_R |= 0x400;
    TIMER3_IMR_R |= 0x400;
    NVIC_EN1_R = 0x00000010;
    NVIC_PRI9_R = 0x8;
    IntRegister(INT_TIMER3B, TIMER3B_Handler);
    IntMasterEnable();
    TIMER3_CTL_R |= 0x100;
}

void ping_trigger (void){
    STATE = LOW;
    // Disable timer and disable timer interrupt
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R = ~0x400;
    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_AFSEL_R &= ~0x08;
    GPIO_PORTB_DIR_R |= 0x08;

    // YOUR CODE HERE FOR PING TRIGGER/START PULSE
    GPIO_PORTB_DATA_R &= ~0x08;
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R |= 0x08;
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R &= ~0x08;

    GPIO_PORTB_DIR_R &= ~0x08;


    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R |= 0x400;
    // Re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R |= 0x08;
    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;
}

void TIMER3B_Handler(void){

  // YOUR CODE HERE
  // As needed, go back to review your interrupt handler code for the UART lab.
  // What are the first lines of code in the ISR? Regardless of the device, interrupt handling
  // includes checking the source of the interrupt and clearing the interrupt status bit.
  // Checking the source: test the MIS bit in the MIS register (is the ISR executing
  // because the input capture event happened and interrupts were enabled for that event?
  // Clearing the interrupt: set the ICR bit (so that same event doesn't trigger another interrupt)
  // The rest of the code in the ISR depends on actions needed when the event happens.

    if(TIMER3_MIS_R & 0x400) {
        TIMER3_ICR_R |= 0x400;
        if(STATE == LOW) {
            START_TIME = TIMER3_TBR_R;
            STATE = HIGH;
        }
        else if (STATE == HIGH) {
            END_TIME = TIMER3_TBR_R;
            STATE = DONE;
        }
    }

}

float ping_getDistance (void){

    // YOUR CODE HERE
    ping_trigger();
    while (STATE != DONE) {};
    float timeDif = 0;
    int overflowCnt = 0;
    int overflow = (END_TIME > START_TIME);
    if (START_TIME > END_TIME) {
        timeDif = START_TIME - END_TIME;
        lcd_printf("%d %d", timeDif, count);
    }
    else {
        timeDif = ((unsigned long) overflow << 24) + START_TIME - END_TIME;
        count++;
        uart_sendChar('h');
        lcd_printf("%d %d", timeDif, count);
    }
    timeDif /= 16000000;
    timeDif = (timeDif/2)*343*100;
    lcd_printf("%.2f %d", timeDif, count);
    return timeDif;
}
