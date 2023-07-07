/**
 * lab6-interrupt_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include <Lab8 Code Files/cyBot_Scan.h>  // For scan sensors
#include <Lab8 Code Files/lcd.h>
#include <Lab8 Code Files/movement.h>
#include <Lab8 Code Files/Timer.h>
#include <Lab8 Code Files/uart-interrupt.h>
#include <Lab8 Code Files/adc.h>
// Uncomment or add any include directives that you want to use
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"

// Your code can use the global variables defined in uart-interrupt.c
// They are declared with the extern qualifier in uart-interrupt.h, which makes the variables visible to this file.

#warning "Possible unimplemented functions"
#define INT_UART1 22

int main(void)
m{
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    lcd_clear();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    uart_interrupt_init();
    adc_init();

     right_calibration_value = 290500;
     left_calibration_value = 1214500;

    int i, j;
    int val = 15;
    uint16_t sum = 0;
    cyBOT_Scan_t scan;
    uint16_t adcValue;
    double adcDistValue;
    char ADC[50];
    char write[50];
    char c;
    while (1) {
        c = uart_receive();
        if (c == 's'){

        for (i = 0; i < val; i++) {
            cyBOT_Scan(90, &scan);
            adcValue = adc_read();
            //adcDistValue = (((1/7267) * (double) adcValue) - 0.07585248);
            sum += adcValue;
            //repeat
            timer_waitMillis(100);
        }
        uint16_t n = sum / val; //avg
        double inverse = 1.0 / n;
        sum = 0;
//        adcDistValue = (((0.00013761) * (double) n) - 0.07585248);
//        adcDistValue = 8*pow(10, -5)*pow(n, 2)-0.2285*n+174.2;
//        adcDistValue = 60230*n-36.258;
        //adcDistValue = -30910*pow((1/n),2) + 13417(1/n)+413.77;
        adcDistValue = 110722*(inverse) - 51.26;
        //print the avg ir value onto the screen
//        uart_sendStr('IR value');
        sprintf(ADC, "%d", n);
        uart_sendStr(ADC);
        uart_sendChar('\r\n');
      //  uart_sendStr('Distance');
        double formatted = adcDistValue;
        sprintf(write, "%.2f", formatted);
        uart_sendStr(write);
        uart_sendChar('\r\n');
       //now calculate the distance, so we will put ir value in the y column and distance in the x column, then inverse this
       // should now see a pointed line, take the equation of this line and solve for X, this will be the distance. then display this distance.

    }
    }
    oi_free(sensor_data);
}

