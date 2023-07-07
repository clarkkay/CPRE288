

#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "movement.h"
#include "uart-interrupt.h"
#include "cyBot_Scan.h"
#include "string.h"
#include "stdio.h"
#include <math.h>


int array[180];
int ang[10];
float dist[10];
float widths[10];
int object = 0;
int midPoint = 0;


void doScan();
void findSmallestObject(oi_t *sensor_data);


int main (void) {


    //bot 11
    // Right 232750
    // Left 1214500

    //bot 15 i think?
    //right(0) 274750
    //left(180) 1282750

    timer_init();
    lcd_init();
    uart_interrupt_init();
    cyBOT_init_Scan(0b0111);

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    right_calibration_value = 232750;
    left_calibration_value = 1214500;

    char fromPutty;
    while (1) {
        fromPutty = uart_receive();
        if (fromPutty == 'f') {
            doScan();
            findSmallestObject(sensor_data);
            oi_free(sensor_data);
            break;
        }
    }

}

void doScan() {
    int i;
    int x;
    int temp1;
    int temp2;
    int temp3;
    char temp[100];
    char angle[5];
    cyBOT_Scan_t scan;
    for (i=0; i <= 180; i++){
        if (command_flag == 1) {
            return;
        }
        cyBOT_Scan(i, &scan);
        temp1 = scan.IR_raw_val;
        if (temp1 > 550) {
            cyBOT_Scan(i, &scan);
            temp2 = scan.IR_raw_val;
            cyBOT_Scan(i, &scan);
            temp3 = scan.IR_raw_val;
            x = (temp1 + temp2 + temp3) / 3;
        }
        else {
            x = temp1;
        }
        array[i] = x;
        sprintf(temp, " %d\r\n", array[i]);
        sprintf(angle, "%d ", i);
        uart_sendStr(angle);
        uart_sendStr(temp);
    }
    int j = 0;
    for (j; j < 179; j++) {
        if (command_flag == 1) {
            return;
        }
        int count = 0;
        int initalAngle = j;
        int finalAngle = 0;
        while (((array[j] - array[j + 1] > -90) || (array[j] - array[j + 1] < 90)) && (array[j] > 550 && array[j] < 1600)) {
            count++;
            j++;
        }
        if (count >= 5) {
            finalAngle = j - 1;
            midPoint = (initalAngle + finalAngle) / 2;
            ang[object] = midPoint;
            cyBOT_Scan(midPoint, &scan);
            if (scan.sound_dist < 35.0){
                timer_waitMillis(300);
                cyBOT_Scan(midPoint, &scan);
            }
            sprintf(temp, "%d ", midPoint);
            uart_sendStr(temp);
            sprintf(temp, "%f ", scan.sound_dist);
            uart_sendStr(temp);
            dist[object] = scan.sound_dist;
            widths[object] = 2 * dist[object] * tan(((midPoint - initalAngle) * M_PI) / 180);
            sprintf(temp, "Width: %f\r\n", widths[object]);
            uart_sendStr(temp);
            object++;
            timer_waitMillis(300);
        }
    }

}

void findSmallestObject(oi_t *sensor_data) {
    if (object < 2) {
        return;
    }
    int k = 0;
    int minIndex = k;
    for (k = 1; k < object; k++) {
        if (widths[k] < widths[minIndex]){
            minIndex = k;
        }
    }
    int minAng = ang[minIndex] - 90;
    float minDist = dist[minIndex];
    turn(sensor_data, minAng - (minAng / 12));
    move_forward(sensor_data, (minDist * 10) - 100);
    oi_free(sensor_data);
}


