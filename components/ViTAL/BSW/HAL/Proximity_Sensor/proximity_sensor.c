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
#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"

void PROX_vRequest()
{
    GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, LOW_LEVEL);
    ets_delay_us(2);
    GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, HIGH_LEVEL);
    ets_delay_us(10);
    GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, LOW_LEVEL);
}

uint16_t PROX_u16Read()
{
    PROX_vRequest();
    int echo_start = 0, echo_stop = 0;
    double distance = 0, delta_t = 0;
    while(GPIO_iGetLevel(HC_SR04_ECHO_PIN) == 0) //se sta in while pana se pune pinul pe 1
    echo_start = esp_timer_get_time();
    while(GPIO_iGetLevel(HC_SR04_ECHO_PIN) == 1)
    echo_stop = esp_timer_get_time();
    delta_t = echo_stop - echo_start;
    distance = (0.0343 * delta_t)/2;
    
    return (uint16_t)distance;
}