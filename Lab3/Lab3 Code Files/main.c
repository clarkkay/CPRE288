

#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include "string.h"
#include "stdio.h"

void doScan();
void uart_sendString(const char* str);
void uart_recieve(char c);
void detect();
const int SIZE = 90;
float array[SIZE];
char tab[] = "\t";
char newLine[] = "\r\n";
int ang[10];
int objNum = 0;
int main (void) {

    //right(0) 274750
    //left(180) 1246000

    timer_init();
    lcd_init();
    cyBot_uart_init();
    cyBOT_init_Scan(0b0111);

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    right_calibration_value = 274750;
    left_calibration_value = 1246000;

    char fromPutty;

    //waits for byte
    while(true) {
        fromPutty = cyBot_getByte();
        uart_recieve(fromPutty);

        if(fromPutty == 'w') {
            move_forward(sensor_data, 250);
        } else if (fromPutty == 'a') {
            turn(sensor_data, 90);
        } else if (fromPutty == 'x') {
            move_backwards(sensor_data, 250);
        } else if (fromPutty == 'd') {
            turn(sensor_data, -90);
        } else if (fromPutty == 'p'){
            break;
        } else if (fromPutty == 'm') {
            detect();
        } else if (fromPutty == 'e'){
            oi_free(sensor_data);
            return;
        }
    }
    return 0;
}
void detect() {
    doScan();
    cyBOT_Scan_t scan;
    int i;
    int object = 0;
    char text[] = "Object  Angle   Distance   Radial Width";
    char line[] = "----------------------------------------";
    int obj[10];
    //int ang[10];
    int dist[10];
    int radWidth[10];
      for (i = 0; i < 88; i = i + 1){
        int count = 0;
        while ((array[i] - array[i + 1] >= -2.5) && (array[i] - array[i + 1] <= 2.5) || ((array[i] - array[i+2] >= -2.5) && (array[i] - array[i+2] <= 2.5))) {
            if ((array[i] - array[i+2] >= -2.5) && (array[i] - array[i+2] <= 2.5)){
                i = i + 2;
                count = count + 2;
            }
            else {
                count++;
                i++;
            }
        }
        if (count > 5){
          //Need to find: Angle object was detected. Object Distance. Radial width

          //Finding angle
          int tempi = i * 2;
          int tempCount = count * 2;
          int angle = (tempi + (tempi - tempCount)) / 2;

          //Finding distance
          int j;
          int sum = 0;
          int distance;
          for (j = 0; j < count; j++) {
            sum = sum + array[j + (i - count)];
          }
          distance = sum / j;

          //Finding radial width
          int radialWidth = tempCount;
//          printf("Object %d, Angle object was detected %d, Distance to object %d, Radial width of object %d\n", object, angle, distance, radialWidth);
          object++;
          obj[object - 1] = object;
          ang[object - 1] = angle;
          dist[object - 1] = distance;
          radWidth[object - 1] = radialWidth;


        }

      }
      int h;
                int min = radWidth[0];
                //int objNum = 0;
                int newAng = ang[0];
                for(h = 0; h < object; h++){
                    if (radWidth[h] < min) {
                        min = radWidth[h];
                        objNum = h;
                        newAng = ang[h];
                    }
                }
      cyBOT_Scan(newAng, &scan);
      int k = 0;
      char tempO[10];
      char tempA[10];
      char tempD[10];
      char tempR[10];
      uart_sendString(text);
      uart_sendString(newLine);
      uart_sendString(line);
      uart_sendString(newLine);
      for (k; k < object; k++){
          sprintf(tempO, "%d", obj[k]);
          uart_sendString(tempO);
          uart_sendString(tab);
          sprintf(tempA, "%d", ang[k]);
          uart_sendString(tempA);
          uart_sendString(tab);
          sprintf(tempD, "%d", dist[k]);
          uart_sendString(tempD);
          uart_sendString(tab);
          sprintf(tempR, "%d", radWidth[k]);
          uart_sendString(tempR);
          uart_sendString(newLine);
      }


}



void doScan() {
//    int i = 10;
//    cyBOT_Scan_t scanData;
//    for(i; i <= 50; i = i + 2) {
//        cyBOT_Scan(i, &scanData);
//        cyBot_sendByte(i);
//        cyBot_sendByte(scanData.sound_dist);
    int i;
    float x;
    char text[] = "Degrees   PING Distance  (cm)\r\n";
    char angle[100];
    char dist[100];
    uart_sendString(text);
    cyBOT_Scan_t scan;
    for (i=0; i <= 180; i+=2){
        cyBOT_Scan(i, &scan);
        x = scan.sound_dist;
        array[i / 2] = x;
        sprintf(angle, "%d", i);
        uart_sendString(angle);
        uart_sendString(tab);
        sprintf(dist, "%g", x);
        uart_sendString(dist);
        uart_sendString(newLine);
        timer_waitMillis(300);
    }

}

void uart_sendString(const char* str) {
//    cyBot_uart_init();
    int i = 0;
    int j = strlen(str);
    for (i; i < j; i++) {
        if (str[i] == '\0'){
            return;
        }
        cyBot_sendByte(str[i]);
    }
}

void uart_recieve(char c) {
    int i = 0;
    int j = 0;
    char text[] = "Received a ";
    char text2[] = "\r\n";
    for (i; i < 11; i++) {
        cyBot_sendByte(text[i]);
    }
    cyBot_sendByte(c);
    for (j; j < 4; j++) {
        cyBot_sendByte(text2[j]);
    }
}

