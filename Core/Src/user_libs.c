#include "main.h"
#include <string.h>

extern uint8_t buzz_on;

void us_delay(void);

//Basic LED registers load
void LoadLEDs(uint32_t LED_value){
  uint32_t LED_buff = LED_value;
  for(uint8_t cnt = 0; cnt < 20; cnt++){
    if((LED_buff&0x00000001) == 0){
			HAL_GPIO_WritePin(GPIOC, DataInput, GPIO_PIN_RESET);
    }else{
      HAL_GPIO_WritePin(GPIOC, DataInput, GPIO_PIN_SET);
    }
    LED_buff >>= 1;
    us_delay();
    HAL_GPIO_WritePin(GPIOC, ShiftClock, GPIO_PIN_SET);
    //GPIO_WriteBit(GPIOC, StorageClock, Bit_RESET);
    us_delay();
    HAL_GPIO_WritePin(GPIOC, ShiftClock, GPIO_PIN_RESET);
    //GPIO_WriteBit(GPIOC, StorageClock, Bit_SET);
    us_delay();
  }
  HAL_GPIO_WritePin(GPIOC, StorageClock, GPIO_PIN_SET);
  us_delay();
  HAL_GPIO_WritePin(GPIOC, StorageClock, GPIO_PIN_RESET);
  us_delay();
}


//-------------------------------------------------------------
void LEDpercent(uint8_t left, uint8_t right){
  uint8_t left_buff = left;
  uint8_t right_buff = right;
  uint16_t left_shift = 0;
  uint16_t right_shift = 0;
  uint32_t value_to_load = 0;
  
  if(left_buff > 10) left_buff = 10;
  if(right_buff > 10) right_buff = 10;
  
  for(uint8_t cnt = 0; cnt < left_buff; cnt++){
    left_shift >>= 1;
    left_shift |= 0x0200;          
  }
  
  for(uint8_t cnt = 0; cnt < right_buff; cnt++){
    right_shift >>= 1;
    right_shift |= 0x0200;          
  }
 
  value_to_load = (uint32_t)right_shift;
  value_to_load <<= 10;
  value_to_load |= (uint32_t)left_shift;
  
  LoadLEDs(value_to_load);
}

void us_delay(void){
	for(uint8_t i; i<144; i++){
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
	}
}

void Buzzer(uint8_t st){
	buzz_on = st;
	if(buzz_on)HAL_GPIO_WritePin(GPIOA, EXT_BUZZ, GPIO_PIN_SET); else HAL_GPIO_WritePin(GPIOA, EXT_BUZZ, GPIO_PIN_RESET);	
}

//---------------------------------------------------------
void PackPacket(TypeAlarm* alrm, uint8_t* out_buf, uint8_t* led_v_left, uint8_t* led_v_right, uint8_t* activ_gas)
{
	uint8_t buff = 0x00;	
	
	buff = TX_DEV_NUM;
	buff <<= 6;
	buff |= *led_v_left;
	if(*activ_gas & 0x02) buff |= 0x20;
	out_buf[0] = buff;
	
	buff = RX_DEV_NUM;
	buff <<= 6;
	buff |= *led_v_right;
	if(*activ_gas & 0x01) buff |= 0x20;
	out_buf[1] = buff;
	
	buff = 0x00;
	if(alrm->CylindersEmpty)   		buff |= 0x01;
	if(alrm->ConcentratorNOT_OK)  buff |= 0x02;
	if(alrm->ConcentratorMax)  		buff |= 0x04;
	if(alrm->LineMin) 				 		buff |= 0x08;
	if(alrm->LineMax)          		buff |= 0x10;
	if(alrm->PowerOff)         		buff |= 0x20;
	if(alrm->BatteryOut)          buff |= 0x40;
	out_buf[2] = buff;
}


uint8_t UnPackPacket(TypeAlarm* alrm, uint8_t* in_buf, uint8_t* led_v_left, uint8_t* led_v_right, uint8_t* activ_gas){
  uint8_t tx_num = 0;
	uint8_t rx_num = 0;
	uint8_t buff;
	
	*activ_gas = 0;
	
	buff = in_buf[0];
	*led_v_left = buff & 0x1f;
	if(buff & 0x20) *activ_gas |= 0x02;
	buff &= 0xc0;
	buff >>= 6;
	tx_num = buff;
	
	buff = in_buf[1];
	*led_v_right = buff & 0x1f;
	if(buff & 0x20) *activ_gas |= 0x01;
	buff &= 0xc0;
	buff >>= 6;
	rx_num = buff;
	
	buff = in_buf[2];
	alrm->CylindersEmpty = 0;
	if(buff & 0x01) alrm->CylindersEmpty = 1;
	alrm->ConcentratorNOT_OK = 0;
	if(buff & 0x02) alrm->ConcentratorNOT_OK = 1;
	alrm->ConcentratorMax = 0;
	if(buff & 0x04) alrm->ConcentratorMax = 1;
	alrm->LineMin = 0;
	if(buff & 0x08) alrm->CylindersEmpty = 1;
	alrm->LineMax = 0;
	if(buff & 0x10) alrm->LineMax = 1;
	alrm->PowerOff = 0;
	if(buff & 0x20) alrm->PowerOff = 1;
	alrm->BatteryOut = 0;
	if(buff & 0x40) alrm->BatteryOut = 1;
	
	if((tx_num == TX_DEV_NUM) && (rx_num == RX_DEV_NUM))return(1); else return(0);
}

uint8_t make_byte(TypeAlarm* alrm){
	uint8_t buff = 0x00;
	if(alrm->CylindersEmpty)   		buff |= 0x01;
	if(alrm->ConcentratorNOT_OK)  buff |= 0x02;
	if(alrm->ConcentratorMax)  		buff |= 0x04;
	if(alrm->LineMin) 				 		buff |= 0x08;
	if(alrm->LineMax)          		buff |= 0x10;
	if(alrm->PowerOff)         		buff |= 0x20;
	if(alrm->BatteryOut)          buff |= 0x40;
	return(buff);
}
