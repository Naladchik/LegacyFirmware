#include "main.h"
#include "cmsis_os.h"

extern QueueHandle_t myQueueLORAHandle;

extern uint8_t buzz_on;

extern SX1278_hw_t SX1278_hw;
extern SX1278_t SX1278;
extern uint16_t RSSI_WORD;

uint8_t buffer[256];
uint8_t packet_data[MESS_LEN];

uint8_t lora_q_buff[MESS_LEN];

uint8_t ret;

uint8_t LR_BW = SX1278_LORA_BW_125KHZ; //SX1278_LORA_BW_7_8KHZ;
uint8_t LR_ML = MESS_LEN;
int16_t LR_RSSI;
uint32_t LR_FREQ = LoRa_FREQ;
int32_t LR_FREQ_ERR;
int32_t mod_freq_err;
uint32_t NoLinkCounter = 0;


uint8_t LORA_busy = 0;

void process_lora(void){
	const int32_t BW_Hz_array[10] = {7800, 10400, 15600, 20800, 31200, 41700, 62500, 125000, 250000, 500000};
	
  	//===========================================================================
		//======================= SENDER ============================================
		//===========================================================================
	if(ROLE == SENDER){
		if(xQueueReceive(myQueueLORAHandle, &lora_q_buff, 0) == pdTRUE){
					for(uint8_t i = 0; i < MESS_LEN; i++){
						packet_data[i] = lora_q_buff[i];
					}
			LORA_busy = 1;
			if(SX1278_LoRaEntryTx(&SX1278, LR_ML, LoRa_TIMEOUT)){
				SX1278_LoRaTxPacket(&SX1278, packet_data, LR_ML, 10*LoRa_TIMEOUT);
			}
			SX1278_init(&SX1278, LR_FREQ, SX1278_POWER_17DBM, SX1278_LORA_SF_12,	LR_BW, SX1278_LORA_CR_4_5, SX1278_LORA_CRC_EN, LR_ML);
			LORA_busy = 0;			
		}
			
	}
	
		//===========================================================================
		//======================= RECEIVER ==========================================
		//===========================================================================
	if(ROLE == RECEIVER){
		if((ret = SX1278_LoRaRxPacket(&SX1278)) > 0){
 				SX1278_read(&SX1278, (uint8_t*) buffer, ret);			
				if(EXPLORE){
					buzz_on = 1;
					osDelay(3);
					buzz_on = 0;
				}
				//UnPackPacket(&Alarm, packet_data, &Volt->LEDvalueL, &Volt->LEDvalueR, &ActiveGas);
				//get RSSI
			  LR_RSSI = SX1278_SPIRead(&SX1278, LR_RegPktRssiValue);
				RSSI_WORD = ConvertRSSI(LR_RSSI);
				//get frequency error
			  LR_FREQ_ERR = SX1278_get_freq_err(&SX1278);
				if(LR_FREQ_ERR >0) mod_freq_err = LR_FREQ_ERR; else mod_freq_err = -LR_FREQ_ERR;
				if(((mod_freq_err * 100)/BW_Hz_array[LR_BW]) > 1){
						LR_FREQ -= LR_FREQ_ERR;
					  SX1278_init(&SX1278, LR_FREQ, SX1278_POWER_17DBM, SX1278_LORA_SF_12,	LR_BW, SX1278_LORA_CR_4_5, SX1278_LORA_CRC_EN, LR_ML);
						SX1278_LoRaEntryRx(&SX1278, MESS_LEN, LoRa_TIMEOUT);
				}
				if(ret == MESS_LEN){
					for(uint8_t i = 0; i < MESS_LEN; i++){
						lora_q_buff[i] = buffer[i];
					}
					if(xQueueSend(myQueueLORAHandle, &lora_q_buff, 0) != pdTRUE){
						while(1){}
					}
					NoLinkCounter = 0;
				}
		  }
		if(NoLinkCounter < MAX_NOLINK)NoLinkCounter++; else NVIC_SystemReset();
	  }
	}

	
	
uint16_t rssi_out = 0;
	
	uint16_t ConvertRSSI(uint8_t rssi){
		
		rssi_out = 0;
		for(uint8_t i; i <10; i++){
			rssi_out <<= 1; 
			if(rssi > (i * 20)) rssi_out |= 0x0001;			
		}
		//rssi_out = 0x03ff;
		return(rssi_out);
	}
