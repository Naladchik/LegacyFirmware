#ifndef __CONFIG_H
#define __CONFIG_H

/* DEVICE CONFIGURATION */

/*INDIVIDUAL PARAMETERS!!!*/
#define TX_DEV_NUM				   		0x01
#define RX_DEV_NUM				   		0x02
#define ROLE 					 					RECEIVER //SENDER, RECEIVER, NOLORA
#define LoRa_FREQ   						434500000  //Frequeny in Hz, was 434500000, was 859500000
#define BARANKI           			0 // 1 - do not take into account LineMin, 0 - do take into account (baranovichi_style)
#define CONC_DELAY            	10  //Delay for concentrator again-on
#define SWTCH_threshold (double)10.0 //threshold to switch to the next gas line
#define ALRM_threshold  (double)40.0 //threshold to activate alarm (if second cylinder <= SWTCH_threshold
#define VALVE_SUSPEND_T					7  //if a valve is suspended (open but no pressure in line) time
#define EMERGENCY_MODE_T				180 //emergency time (suspended valve) before next try
#define EXPLORE 0




#define H_P_a           (double)0.083944 //ADC - cylinder pressure (bar) linear coefficient a
#define H_P_b           (double)-62.5 //ADC - cylinder pressure (bar) linear coefficient b

#define Volt_a          (double)0.0088645 //ADC - battery and PSU voltage coefficient a
#define Volt_b          (double)0.0 //ADC - battery and PSU voltage coefficient b

#define BatteryLow      (double)9.0 //V
#define BatteryOK       (double)10.0 //V
#define PSU_LOW         (double)11.0 //V
#define PSU_HIGH        (double)16.0 //V


#define MAX_NOLINK 10000

#define PressMIN  (double)10.0  //Only bottom LED blinking
#define PressMAX   (double)150.0 //All LEDs light

#define ADC_AVG_NUM     128  //Number of ADC measurements to for averaging

#define ALRM_PAUSE      60  //Mute delay for alarm 

#define CONC_SIG_DUR    3   //Beep duration when concentrator is off

#define Pquant          (double)((PressMAX - PressMIN)/(LED_NUM - 2))

#endif
