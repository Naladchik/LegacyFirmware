#ifndef __BASIC_H
#define __BASIC_H

/* Pins definitions */
#define HPS_LEFT        GPIO_PIN_1  //GPIOA AN1 input
#define HPS_RIGHT       GPIO_PIN_2  //GPIOA AN2 input
#define INT_BUZZ        GPIO_PIN_8  //GPIOA
#define EXT_BUZZ        GPIO_PIN_15 //GPIOA
#define BUTT_alarm      GPIO_PIN_4 //GPIOB
#define LED_right_gas   GPIO_PIN_8 //GPIOB
#define LED_conc        GPIO_PIN_9 //GPIOB
#define LED_left_gas    GPIO_PIN_10 //GPIOB
#define BUTT_switch     GPIO_PIN_11 //GPIOB
#define SMC_C_MAX       GPIO_PIN_12 //GPIOB
#define SMC_C_OK        GPIO_PIN_13 //GPIOB
#define SMC_L_MAX       GPIO_PIN_14 //GPIOB
#define SMC_L_MIN       GPIO_PIN_15 //GPIOB

#define LED_alarm       GPIO_PIN_2 //GPIOC
#define PSU_VOLT        GPIO_PIN_3 //GPIOC AN13 input
#define BAT_VOLT        GPIO_PIN_4 //GPIOC AN14 input
#define StorageClock    GPIO_PIN_8 //GPIOC
#define ShiftClock      GPIO_PIN_9 //GPIOC
#define DataInput       GPIO_PIN_10 //GPIOC
#define LEFT_VLV        GPIO_PIN_11 //GPIOC
#define RIGHT_VLV       GPIO_PIN_12 //GPIOC

/* Private defines -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
#define NSS_Pin GPIO_PIN_2
#define NSS_GPIO_Port GPIOB

#define DIO0_Pin GPIO_PIN_3  // LoRa interrupt indicator pin (for receiver mode)
#define DIO0_GPIO_Port GPIOA

#define RESET_Pin GPIO_PIN_0
#define RESET_GPIO_Port GPIOA
/* ---------------------------------------------------------------------------*/

#define SENDER 	 1
#define RECEIVER 2
#define NOLORA   3

#define LoRa_TIMEOUT 2000 //2000

#define ADC_Left_Press  ADC_CHANNEL_1
#define ADC_Right_Press ADC_CHANNEL_2
#define ADC_PSU         ADC_CHANNEL_13
#define ADC_BAT         ADC_CHANNEL_14


/* Other definitions */
#define LEFT            0xf0
#define RIGHT           0x0f
#define CONCENTRATOR    0xff
#define BOTH_VALVES			0xaa

#define TIM3_PERIOD     9600 // 4800 interrupts per second (for 2.4 kHz sound)
#define BUTT_TRIM       (uint8_t)100
#define LED_NUM         20 //how many LED combinations is allowed (though avtual LED number is 10)

#define MESS_LEN				3

#endif
