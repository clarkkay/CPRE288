

//#include <cyBot_uart.h>
//#include <lcd.h>
#include <ping.h>
#include <Timer.h>
#include <servo.h>
#include <uart.h>
#include <movement.h>

#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    //lcd_init();
    servo_init();
    ping_init();
    uart_init();

    //auto picks path but user has to agreee to it once set by asking in
    //putty and waiting to get a y/n based on the input


    //scan objs
    //pick path that doesn't collide with objs
    // prompt user with where we are going y/n
    //rescan if not v
    // move safe amount
    //rep until in the endgame i guess idk this is rather sper of the moment will figure out later just like do things ig
}

