#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"ADC_INTERFACE.h"
#include"TIMERinterface.h"
#include"LCDinterfaceV5.h"
#include"FreeRTOS.h"
#include"FreeRTOSConfig.h"
#include"task.h"
#include"queue.h"


#define Clear_Diplay 0x01


TaskHandle_t First_task =  0 ;  // Handler task for task 1
TaskHandle_t Second_Task = 0 ; // Handler task for task 2

QueueHandle_t Qeue_ADC;



void Task1(void *parameters)
{
	/* Creating the queue the fucntion  */


	u32 ADC_GET_value = 0;

	Qeue_ADC = xQueueCreate(2,sizeof(u32));



	while(1)
	{
		DIO_VidSetPinValue(1,0,1);

		xQueueSend(Qeue_ADC,&ADC_GET_value,0);

		ADC_GET_value = ADC_READ(0);

		ADC_GET_value = ADC_GET_value * (5*150)/ (1023*1.5);

		LCD_VidGOTOPOS(0,0);

		LCD_VidSendNum(ADC_GET_value);

		DIO_VidSetPinValue(1,0,0);

		vTaskDelay(1);

	}
}


void Task2(void *parameters)
{

	u32 GOT_VALUE = 0 ;

	while(1)
	{
		xQueueReceive(Qeue_ADC,&GOT_VALUE,0);

		LCD_VidGOTOPOS(1,0);

		//GOT_VALUE = GOT_VALUE * (5*150)/ (1023*1.5);

		LCD_VidSendNum(GOT_VALUE);

		if(GOT_VALUE >= 0 && GOT_VALUE < 15 )
		{
			VidTimer0SetPWMDutyCycle(0);
		}

		else if(GOT_VALUE >= 15 && GOT_VALUE < 20 )
		{
			VidTimer0SetPWMDutyCycle(50);
		}

		else if(GOT_VALUE >= 20 && GOT_VALUE < 30)
		{
			VidTimer0SetPWMDutyCycle(150);
		}

		vTaskDelay(1);

	}
}



void main()
{

	/* Setting PIN B0 High */

	DIO_VidSetPinDirection(1,0,1);

	/* Setting PIN B3 High >> OUTT PWM Signal  */

	DIO_VidSetPinDirection(1,3,1);

	/* Timer0 Init */

	VidTimer0_PWM_INIT();  // PWM Signal output based on ADC value


	BaseType_t Task1_ret;
	BaseType_t Task2_ret;

	/* Adc Init */
	ADC_INIT();

	/* Init Lcd */
	LCD_VidIntialize();


	/* Creatng Task1 */
	
	Task1_ret = xTaskCreate(Task1,"TASK1",200,(void *)1,0,&First_task); 
	
	/* Creatng Task1 */
	
	Task2_ret = xTaskCreate(Task2,"TASK2",200,(void *)1,0,&Second_Task);

	/* Starting scheduler */
	
	vTaskStartScheduler();

	while(1)
	{

	}

}
