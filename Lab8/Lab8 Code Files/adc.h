#ifndef Lab8_Code_Files_ADC_H
#define Lab8_Code_Files_ADC_H
#include <Lab8 Code Files/adc.h>
#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <stdlib.h>

void adc_init (void);
uint16_t adc_read (void);

#endif /*Lab8_Code_Files_ADC_H*/
