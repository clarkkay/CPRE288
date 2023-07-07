#include "servo.h"
#include "Timer.h"
#include "lcd.h"

unsigned long pwm_period = 0x4E200;

void servo_init() {
    // replace 'A' with 'B' for the Timer B
    SYSCTL_RCGCGPIO_R |= 0x02;
    SYSCTL_RCGCTIMER_R |= 0x02;
    while ((SYSCTL_PRGPIO_R & 0x02) != 0x02) {};
    GPIO_PORTB_DIR_R &= ~0x20;
    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFF7FFFFF) | 0x00700000;
    GPIO_PORTB_DEN_R |= 0x20;

    // pwm mode enabled
    TIMER1_CTL_R &= ~0x100;
    TIMER1_CFG_R = 0x4;
    TIMER1_TBMR_R = 0x0A;
    // start values
    TIMER1_TBPR_R = pwm_period >> 16;
    TIMER1_TBILR_R = pwm_period & 0xFFFF;
    TIMER1_CTL_R |= 0x100;
    // software has capability of inverting output by setting TAPWML in the GPTMCTL register
}

void servo_move(uint16_t degrees) {
    float millis;
    int high;
    int low;
    unsigned long low_hex;
    millis = (0.0056 * degrees) + 1;
    high = millis * 1000000 / 62.5;
    low = 320000 - high;
    TIMER1_TBMATCHR_R = low;
    TIMER1_TBPMR_R = low >> 16;
}
