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

#include "SRVL/SCHEDULER/scheduler.h"

#include "BSW/MCAL/ADC/adc.h"
#include "BSW/MCAL/GPIO/gpio.h"
#include "BSW/MCAL/PWM/pwm.h"
#include "BSW/MCAL/WIFI/wifi.h"
#include "BSW/HAL/DC_Motor/dc_motor.h"
#include "RTE/rte.h"

#include "BSW/HAL/Com/com.h"
#include "BSW/HAL/Shift_Register/shift_register.h"
#include "ASW/Ambient_Light/ambient_light.h"
#include "BSW/HAL/Temp_Sensor/temp_sensor.h"
#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"
#include "BSW/HAL/Photo_Resistor/photo_resistor.h"
#include "nvs_flash.h"

static const char *TAG = "SRVL SCHEDULER";
static httpd_handle_t server = NULL;

void SYSTEM_vInit(void)
{
    /* Call these functions only when specific HW parts are connected */
    
	//Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	/* Initialize All periferials */
	ADC_vInit();

	GPIO_vInit();

	PWM_vInit();
	
	WIFI_vInit(&server);
}

void vTask100ms(void)
{	
	/* Send and receive data to the HTML interface -- get and post functions*/
	COM_vTaskProcessServer();
	/* Call Shift register functionalty */
	ASW_vTaskShiftRegControlTest();
}
 
void vTask200ms(void)
{
	/* Call RGB led functioality */
	ASW_vTaskRGBLedControlTest();
}

void vTask500ms(void)
{
	DHT11_vTaskTempAndHumCalculate();
	PHRES_vTaskCalculate();
}

void vTask800ms(void)
{
	uint16_t rez = PROX_u16Read();
	ESP_LOGI(TAG, "Distance: %d\n", rez);
} 


void SYSTEM_vTaskScheduler(void)
{
	uint16_t u16TickCount = 0;

	while (1)
	{

		if (u16TickCount % TASK_100MS == 0)
		{
			vTask100ms();
		}

		if (u16TickCount % TASK_200MS == 0)
		{
			vTask200ms();
		    DCMOT_vChangeSpeed(6000);
		}

		if (u16TickCount % TASK_500MS == 0)
		{
			vTask500ms();	
		}
		
		if (u16TickCount % TASK_800MS == 0)
		{
			vTask800ms();	
		}
		
		u16TickCount++;
		if (u16TickCount >= TASK_800MS)
		{
			u16TickCount = 0;
		}
		
		vTaskDelay(100); // 1 sec 
		
	}
}
