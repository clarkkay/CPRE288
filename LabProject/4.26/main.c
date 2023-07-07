//#include <cyBot_uart.h>
//#include "lcd.h"
#include "ping.h"
#include "Timer.h"
#include "servo.h"
#include "uart.h"
#include "movement.h"
#include "music.h"
#include "open_interface.h"

#warning "Possible unimplemented functions"
#define REPLACEME 0
/*
 * fix clifo
 * bump
 * run on field
 * dest without looking
 *
 */
int main(void)
{
    uint16_t adcValue;
    double adcDistValue;
    char ADC[50];
    char write[50];
    char kns[50];
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    timer_init();
    // lcd_init();
    adc_init();
    servo_init();
    ping_init();
    uart_init();
    int *weretos;
    char string[11];
    int places[20];

    uart_sendStr("                               ##### \r\n");
    uart_sendStr("                           ####### \r\n");
    uart_sendStr("              ######    ########       ##### \r\n");
    uart_sendStr(
            "                  ###########/#####\\#####  ############# \r\n");
    uart_sendStr(
            "               ############/##########--##################### \r\n");
    uart_sendStr(
            "          ####         ######################          ##### \r\n");
    uart_sendStr(
            "          ##          ####      ##########/\\@@  Q    A            ### \r\n");
    uart_sendStr(
            "                #          ####        ,-.##/.#\\#####               ## \r\n");
    uart_sendStr(
            "                         ###         /  |$/  |,-. ####                 # \r\n");
    uart_sendStr("                      ##          \\_,'$\_,'|  \\  ### \r\n");
    uart_sendStr("                      #          \\_$$$$$`._/   ## \r\n");
    uart_sendStr("                                   $$$$$_/     ## \r\n");
    uart_sendStr("                                   $$$$$        # \r\n");
    uart_sendStr("                                  $$$$$ \r\n");
    uart_sendStr("                                  $$$$$ \r\n");
    uart_sendStr("                                  $$$$$ \r\n");
    uart_sendStr("                                  $$$$$ \r\n");
    uart_sendStr("                                  $$$$$ \r\n");
    uart_sendStr("                                  $$$$$ \r\n");
    uart_sendStr("                                 $$$$$ \r\n");
    uart_sendStr("                                  $$$$$         ___ \r\n");
    uart_sendStr(
            "                                 $$$$$     _.-'     `-. \r\n");
    uart_sendStr(
            "                                 $$$$$   ,'            `. \r\n");
    uart_sendStr(
            "                                 $$$$$  /                \\ \r\n");
    uart_sendStr(
            "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$$$$$~~~~~~~~~\\0/~~~~~~~~~~~~~");
    uart_sendStr(
            " \r\n           ~      ~  ~    ~  ~   $$$$$  ~   ~       ~          ~ \r\n");
    uart_sendStr(
            "          ~ ~      ,             $$$$$     ~    ~  ~        ~       ~ \r\n");
    uart_sendStr(
            "     ~            ~ ^   ~        $$$$$~        ______    ~        ~ \r\n");
    uart_sendStr(
            "   ______________________________$$$$$_________________________ \r\n");
    uart_sendStr("                                 $$$$$ \r\n");
    uart_sendStr(
            "            -                    $$$$$                 Surfs up dude \r\n");
    uart_sendStr("                                 $$$$$         \\0/ \r\n");
    uart_sendStr("       ------                    $$$$$          | \r\n");
    uart_sendStr("                                 $$$$$         /\\ \r\n");
    uart_sendStr("                                $$$$$$$         chad \r\n");
    uart_sendStr("                               $$$$$$$$$ \r\n");
    uart_sendStr(
            " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$$$$$$$$$$~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \r\n");
//    unsigned char rickrollNumNotes = 11;
//    unsigned char rickrollNotes[11] = { 53, 55, 48, 55, 57, 60, 58, 57, 53, 55,
//                                        48 };
//    unsigned char rickrollDuration[11] = { 48, 64, 16, 48, 48, 8, 8, 8, 48, 64,
//                                           64 };
//    oi_loadSong(RICK_ROLL, rickrollNumNotes, rickrollNotes, rickrollDuration);
//    oi_play_song(RICK_ROLL);

    while (1)
    {
        if (uart_receive() == 'd')
        {
            while (1)
            {
                int z = 0;
                char c = uart_receive();
                if (c == 'w')
                {

                    z = cliffCheck(sensor_data);
                    if (z == 0)
                    {
                        move_forward(sensor_data, 50.0, 500);
                    }

                }
                else if (c == 's')
                {

                    move_backward(sensor_data, 250.0, 500);

                }
                else if (c == 'a')
                {
                    turn_left(sensor_data, 30);

                }
                else if (c == 'd')
                {
                    turn_right(sensor_data, 30);
                }
                if (sensor_data->bumpLeft || sensor_data->bumpRight)
                { // bump    back up and rescan then provide a dri to go
                    move_backward(sensor_data, 50.0, 500);
                }
                oi_update(sensor_data);
                if (c == 'e')
                    break;
            }
        }
        else if (uart_receive() == 's')
        {
            weretos = scan();
            timer_waitMillis(1000);
            int i;
//            for (i = 0; i < 91; i++)
//            {
//                if (0 == *(weretos + i))
//                {
//                    break;
//                }
//                sprintf(string, "%d   ", *(weretos + i));
//                uart_sendStr(string);
//
//            }
            int jed = 7;
            int zed = 0;
            int s = 0;
            int placesCount = 0;
            for (zed = 0; zed < 91; zed += 1)
            {
                if (2 == *(weretos + zed+1) - *(weretos + zed))
                {                // goes up by two
                    s += 1;

                }
                else
                {                //not up by two
                    s = 0;
                }
                if (s == jed)
                { //gap of j to be found idk the wanted value, prob something between 5-10
                    places[placesCount] = *(weretos + zed - jed/2); //biggest angle -jed to equal mid
                    placesCount += 1;
                    sprintf(write, " %ddeg\r\n", places[placesCount - 1]);
                    uart_sendStr(write);
                    s = 0;
                }
                if (*(weretos + zed + 1) == 0)
                {
                    break;
                }
            }
            int val = 10;
            int it = 0;
            uint16_t sum = 0;
            for (it = 0; it < placesCount; it++)
            {

                for (i = 0; i < val; i++)
                {
                    if(0==(places[it] - jed*2)){
                        servo_move(1);
                    }else {
                        servo_move((places[it] - jed*2));
                    }
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
                adcDistValue = 60230 * (inverse) - 36.258;
                //adcDistValue = -30910*pow((1/n),2) + 13417(1/n)+413.77;
                //adcDistValue = 110722 * (inverse) - 51.26;
                //print the avg ir value onto the screen
                //        uart_sendStr('IR value');
                //                            sprintf(ADC, "%d", n);
                //                            uart_sendStr(ADC);
                //uart_sendChar('\r\n');
                //  uart_sendStr('Distance');
                double formatted = adcDistValue;
                sprintf(write, " %ddeg %lfdis\r\n", (places[it] - (jed / 2)*2),
                        formatted);
                uart_sendStr(write);
                for (i = 0; i < val; i++)
                {
                    servo_move((places[it] + (jed / 2)*2));
                    adcValue = adc_read();
                    //adcDistValue = (((1/7267) * (double) adcValue) - 0.07585248);
                    sum += adcValue;
                    //repeat
                    timer_waitMillis(100);
                }

                n = sum / val; //avg
              inverse = 1.0 / n;
                sum = 0;
                //        adcDistValue = (((0.00013761) * (double) n) - 0.07585248);
                //        adcDistValue = 8*pow(10, -5)*pow(n, 2)-0.2285*n+174.2;
                adcDistValue = 60230 * (inverse) - 36.258;
                //adcDistValue = -30910*pow((1/n),2) + 13417(1/n)+413.77;
                //adcDistValue = 110722 * (inverse) - 51.26;
                //print the avg ir value onto the screen
                //        uart_sendStr('IR value');
                //                            sprintf(ADC, "%d", n);
                //                            uart_sendStr(ADC);
                //uart_sendChar('\r\n');
                //  uart_sendStr('Distance');
                formatted = adcDistValue;
                sprintf(write, " %ddeg %lfdis\r\n", (places[it] + (jed / 2)*2),
                        formatted);
                uart_sendStr(write);
            }
            //o= o+uart_receive();
//            sprintf(write, "%ddeg\r\n", *(weretos + o));
//            uart_sendStr(write);
            //if get e break
        } else if(uart_receive() == 't'){
            int angle = places[uart_receive()];
            if (angle > 90) {
                turn_right(sensor_data, angle - 90);
            } else {
                turn_left(sensor_data, 90 - angle);
            }
        }
    }
}

//auto picks path but user has to agreee to it once set by asking in
//putty and waiting to get a y/n based on the input

//scan objs
//pick path that doesn't collide with objs
// prompt user with where we are going y/n
//rescan if not v
// move safe amount
//rep until in the endgame i guess idk this is rather sper of the moment will figure out later just like do things ig

int* scan()
{
    int scanAmt = 1;
    char string[100];
    int i;
    int x = 0;
    static int waretos[90];
    int t;
    servo_move(0);
    double sumDist = 0;
    double err = ping_getDistance();
    timer_waitMillis(500);
    for (i = 0; i < 180; i += 2)
    {
        servo_move(i);
        sumDist = 0;
        waretos[x] = 0;
        int j;
        for (j = 0; j < scanAmt; j++)
        {
            timer_waitMillis(100);
            if (adc_read() < 700)
            {
                waretos[x] = i;
                x++;
                sumDist += ping_getDistance();
            }
        }
        double dist;
        if (sumDist > 0)
        {
            dist = sumDist / scanAmt;
        }
        else
        {
            dist = 999;
        }
        //
        //        sprintf(string, "m %d %lf", i, dist);
        //
        //uart_sendStr(string);
    }
//where the ___ we going
    return waretos;
}

int cliffCheck(oi_t *sensor)
{
    oi_update(sensor);

    int cliffStatus = 0;

    if (sensor->cliffLeft)
    {
        cliffStatus = 1;
    }
    else if (sensor->cliffRight)
    {
        cliffStatus = 4;
    }
    else if (sensor->cliffFrontLeft)
    {
        cliffStatus = 2;
    }
    else if (sensor->cliffFrontRight)
    {
        cliffStatus = 3;
    }
    else
    {
        cliffStatus = 0;
    }
// lcd_printf("In check:  %d", cliffStatus);
// timer_waitMillis(5000);
    return cliffStatus;
}
