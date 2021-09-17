#include "analog.h"
#include "cmsis_os.h"

#define adc_timeout 500

ADC_ChannelConfTypeDef ADC_CONF;
extern ADC_HandleTypeDef hadc1;

void measure_volt(TypeVolt* Volt){
		//ADC global variables
	static uint32_t ADCL_acc = 0;
	static uint32_t ADCR_acc = 0;
  static uint32_t ADCPSU_acc = 0;
	static uint32_t ADCBat_acc = 0;
	static uint16_t ADC_counter = 0;
	static uint16_t ADC_avg;
	double PressLeft;
  double PressRight;
  double PSUVolt;
  double BatVolt;
	
		ADC_CONF.Channel = ADC_Left_Press;
		HAL_ADC_ConfigChannel(&hadc1, &ADC_CONF);
		HAL_ADC_Start (&hadc1);
		HAL_ADC_PollForConversion (&hadc1, adc_timeout);
		ADCL_acc += HAL_ADC_GetValue (&hadc1);
		
		ADC_CONF.Channel = ADC_Right_Press;
		HAL_ADC_ConfigChannel(&hadc1, &ADC_CONF);
		HAL_ADC_Start (&hadc1);
		HAL_ADC_PollForConversion (&hadc1, adc_timeout);
		ADCR_acc += HAL_ADC_GetValue (&hadc1);
		
		ADC_CONF.Channel = ADC_PSU;
		HAL_ADC_ConfigChannel(&hadc1, &ADC_CONF);
		HAL_ADC_Start (&hadc1);
		HAL_ADC_PollForConversion (&hadc1, adc_timeout);
		ADCPSU_acc += HAL_ADC_GetValue (&hadc1);
		
		ADC_CONF.Channel = ADC_BAT;
		HAL_ADC_ConfigChannel(&hadc1, &ADC_CONF);
		HAL_ADC_Start (&hadc1);
		HAL_ADC_PollForConversion (&hadc1, adc_timeout);
		ADCBat_acc += HAL_ADC_GetValue (&hadc1);
		
		ADC_counter++;
    if(ADC_counter == ADC_AVG_NUM){
      //Left Pressure calculation
      ADC_avg = ADCL_acc/ADC_AVG_NUM;
      ADCL_acc = 0;
      PressLeft = (double)ADC_avg * H_P_a + H_P_b;
      if(PressLeft < 0) PressLeft = 0;
      //Right pressure calculation
      ADC_avg = ADCR_acc/ADC_AVG_NUM;
      ADCR_acc = 0;
      PressRight = (double)ADC_avg * H_P_a + H_P_b;
      if(PressRight < 0) PressRight = 0;
      //PSU voltage calculation
      ADC_avg = ADCPSU_acc/ADC_AVG_NUM;
      ADCPSU_acc = 0;
      PSUVolt = (double)ADC_avg * Volt_a + Volt_b;
      //Battery voltage calculation
      ADC_avg = ADCBat_acc/ADC_AVG_NUM;
      ADCBat_acc = 0;
      BatVolt = (double)ADC_avg * Volt_a + Volt_b;
      ADC_counter = 0;

			Volt->PressLeft = PressLeft;
			Volt->PressRight = PressRight;
			Volt->BatVolt = BatVolt;
			Volt->PSUVolt = PSUVolt;
			//Volt->LEDvalueL = LEDvalueL;
			//Volt->LEDvalueR = LEDvalueR;
			Volt->new_data = 1;
    }
}
