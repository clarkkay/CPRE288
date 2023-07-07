#include "Timer.h"
#include "lcd.h"
#include "servo.h"

int main(void) {
    timer_init();
    lcd_init();
    servo_init();

    lcd_printf("hello");

    servo_move(90);
    timer_waitMillis(3000);
    servo_move(30);
    timer_waitMillis(3000);
    servo_move(150);
    timer_waitMillis(3000);
    servo_move(90);

}
