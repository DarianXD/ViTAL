/*******************************************************************************
 * COPYRIGHT (C) VITESCO TECHNOLOGIES
 * ALL RIGHTS RESERVED.
 *
 * The reproduction, transmission or use of this document or its
 * contents is not permitted without express written authority.
 * Offenders will be liable for damages. All rights, including rights
 * created by patent grant or registration of a utility model or design,
 * are reserved.
 *******************************************************************************/
#include "BSW/MCAL/GPIO/gpio.h"
#include "BSW/HAL/Com/com.h"
#include "global.h"
#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"
#include "BSW/MCAL/ADC/adc.h"


uint16_t PHRES_u16Read(void);

void PHRES_vTaskCalculate(void);