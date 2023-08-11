#include "hc-08.h"  
#include <string.h>
#include <stdio.h>

/**
* @brief Binding data transfer functions using UART to the structure of the BLE module
   * @param *hc_08 pointer to the HC-08 module structure
   * @param void (*uart_tx)(char *buff, uint16_t size) function to send data via UART. Where:
               *buff pointer to the buffer with the data to be transferred
               size number of bytes of data to be transferred
   * @param void (*uart_tx)(char *buff, uint16_t size) function to receive data using UART. Where:
               *buff pointer to the buffer with the data to be transferred
               size number of bytes of data to be received
  */
void hc_08_reg_uart_cbfunc(hc_08_ST *hc_08,
                            void (*uart_tx)(char *buff, uint16_t size), 
                            void (*uart_rx)(char *buff, uint16_t size)){
  hc_08->uart.tx = uart_tx;
  hc_08->uart.rx = uart_rx;
}

/**
  * @brief  Reading the response from the HC-08 module
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_read_answer(hc_08_ST *hc_08){
	hc_08->uart.rx(hc_08->uart.buff_rx, 
						HC_08_BUFF_RX_SIZE);
}

/**
  * @brief  Sending an AT command
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_at(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s", HC_08_COMMAND_AT);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Sending an RX command
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_rx(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s", HC_08_COMMAND_RX); 
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Sending an DEFAULT command
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_default(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s", HC_08_COMMAND_DEFAULT);

  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Sending an RESET command
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_reset(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s", HC_08_COMMAND_RESET);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Sending an VERSION command
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_version(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s", HC_08_COMMAND_VERSION);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Сhange master/slave role 
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  role the role to change to. Takes one of the following values
              hc_08_role_master,
              hc_08_role_slave  
  */
void hc_08_cmd_set_role(hc_08_ST *hc_08, hc_08_role role){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_ROLE, hc_08_role_c[role]);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Query the module about its current role
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_ask_role(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_ROLE, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Specifying a new name for the module (no more than 12 characters)
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_set_name(hc_08_ST *hc_08, char *name){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_NAME, name);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Query the module for its name
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_ask_name(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_NAME, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Specifying a new address module ()
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  address вказівник на адресу (масив з 6 байт)
  */
void hc_08_cmd_set_address(hc_08_ST *hc_08, uint8_t* address){
  strcpy((hc_08->uart.buff_tx), HC_08_COMMAND_ADDR);
  
  for(uint8_t i = 0; i < sizeof(hc_08->param.addres); i++){
    sprintf(&hc_08->uart.buff_tx[strlen(HC_08_COMMAND_ADDR) + i * 2], "%x", (unsigned int) address[i]);
  }
  
  hc_08->uart.tx(hc_08->uart.buff_tx, 
                      strlen(HC_08_COMMAND_ADDR) + HC_08_ADDRES_LENGHT);
}

/**
  * @brief  Query the module for its address
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_ask_address(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_ADDR, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set RF power
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  rfpm transmission power of the module. Takes one of the following values:
              hc_08_rfpm_4dBm,
              hc_08_rfpm_0dBm,
              hc_08_rfpm_m6dBm,
              hc_08_rfpm_m23dBm
  */
void hc_08_cmd_set_rf_power(hc_08_ST *hc_08, hc_08_rfpm rfpm){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_RFPM, hc_08_rfpm_param_c[rfpm]);

  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Request to the module its RF power
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_ask_rf_power(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_RFPM, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set UART baud rate
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  baud UART baud rate. Takes one of the following values:
                hc_08_baud_1200bps,
                hc_08_baud_2400bps,
                hc_08_baud_4800bps,
                hc_08_baud_9600bps,
                hc_08_baud_19200bps,
                hc_08_baud_38400bps,
                hc_08_baud_57600bps,
                hc_08_baud_115200bps
  */
void hc_08_cmd_set_uart_baud(hc_08_ST *hc_08, hc_08_baud baud){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_BAUD, hc_08_baud_c[baud]);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set UART baud rate and parity bit
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  baud UART baud rate. Takes one of the following values:
                hc_08_baud_1200bps,
                hc_08_baud_2400bps,
                hc_08_baud_4800bps,
                hc_08_baud_9600bps,
                hc_08_baud_19200bps,
                hc_08_baud_38400bps,
                hc_08_baud_57600bps,
                hc_08_baud_115200bps
  * @param  parity_bit UART parity bit. Takes one of the following values:
                hc_08_parity_bit_no_parity,
                hc_08_parity_bit_even_parity,
                hc_08_parity_bit_odd_parity
  */
void hc_08_cmd_set_uart_baud_parity(hc_08_ST *hc_08, hc_08_baud baud, hc_08_parity_bit parity_bit){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s%s%s", HC_08_COMMAND_BAUD, 
                          hc_08_baud_c[baud], HC_08_TEXT_COMMA, 
                          hc_08_parity_bit_c[parity_bit]);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Request to the module its baud rate and parity bit
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_ask_uart_baud_parity(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_BAUD, HC_08_TEXT_QUERY);

  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set connect ability
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  cont connect ability. Takes one of the following values:
              hc_08_cont_0,
              hc_08_cont_1
  */
void hc_08_cmd_set_cont(hc_08_ST *hc_08, hc_08_cont cont){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_CONT, hc_08_cont_c[cont]);

  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Ask connect ability
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_ask_rfpm(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_CONT, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Change the broadcast data
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_set_avda(hc_08_ST *hc_08, char *avda){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_AVDA, avda);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set working mode
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  mode working mode. Takes one of the following values:
              hc_08_mode_full,
              hc_08_mode_level_1,
              hc_08_mode_level_2
  */
void hc_08_cmd_set_mode(hc_08_ST *hc_08, hc_08_mode mode){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_MODE, hc_08_mode_c[mode]);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Request to the module working mode
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_ask_mode(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_MODE, HC_08_TEXT_QUERY);

  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set broadcast interval
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  value unit range of the broadcast interval is 32~16000
  * @retval hc_08_status:
  *             hc_08_status_ok if 32<=value<=16000
  *             hc_08_status_error
  */
hc_08_status hc_08_cmd_set_aint(hc_08_ST *hc_08, uint16_t value){
  if(value >= HC_08_AINT_MIN && value <= HC_08_AINT_MAX){
    uint8_t size = sprintf(&hc_08->uart.buff_tx[strlen(HC_08_COMMAND_AINT)], "%s%d", HC_08_COMMAND_AINT, (unsigned int) value);
  
    hc_08->uart.tx(hc_08->uart.buff_tx, size);
  }else{
    return hc_08_status_error;
  }
  
  return hc_08_status_ok;
}
/**
  * @brief  Request to the module broadcast interval
  * @param  *hc_08 pointer to the HC-08 module structure 
*/
void hc_08_cmd_ask_aint(hc_08_ST *hc_08){
  uint8_t size = sprintf(&hc_08->uart.buff_tx[strlen(HC_08_COMMAND_AINT)], "%s%s", HC_08_COMMAND_AINT, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set  connection interval
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  time unit range of the connection interval is 6~3199
  * @retval hc_08_status:
  *             hc_08_status_ok if 6<=time<=3199
  *             hc_08_status_error
  */
hc_08_status hc_08_cmd_set_cint(hc_08_ST *hc_08, uint16_t time){
  if(time >= HC_08_CINT_MIN && time <= HC_08_CINT_MAX){
    uint8_t size = sprintf(&hc_08->uart.buff_tx[strlen(HC_08_COMMAND_CINT)], "%s%d", HC_08_COMMAND_CINT, (unsigned int) time);
  
    hc_08->uart.tx(hc_08->uart.buff_tx, size);
  }else{
    return hc_08_status_error;
  }
  
  return hc_08_status_ok;
}

/**
  * @brief  Set connection interval
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  time_min unit range of the connection interval is 6~3199
  * @param  time_max unit range of the connection interval is 6~3199
  * @retval hc_08_status:
  *             hc_08_status_ok if 6<=time_min<=3199 && 6<=time_max<=3199 && time_min<time_max
  *             hc_08_status_error
  */
hc_08_status hc_08_cmd_set_cint_min_max(hc_08_ST *hc_08, uint16_t time_min, uint16_t time_max){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%d%s%d", HC_08_COMMAND_CINT, 
                        (unsigned int) time_min, HC_08_TEXT_COMMA, (unsigned int)time_max);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
  
  if(time_min >= HC_08_CINT_MIN && time_min <= HC_08_CINT_MAX &&
      time_max >= HC_08_CINT_MIN && time_max <= HC_08_CINT_MAX &&
      time_min <= time_max){
    uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%d%s%d", HC_08_COMMAND_CINT, 
                        (unsigned int) time_min, HC_08_TEXT_COMMA, (unsigned int)time_max);
  
    hc_08->uart.tx(hc_08->uart.buff_tx, size);
  }else{
    return hc_08_status_error;
  }
  
  return hc_08_status_ok;
}

/**
  * @brief  Request to the module connection interval
  * @param  *hc_08 pointer to the HC-08 module structure 
*/
void hc_08_cmd_ask_cint_min_max(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_CINT, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set connection timeout time
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  time range of the connection timeout time is 10~3200
  * @retval hc_08_status:
  *             hc_08_status_ok if 6<=time<=3199
  *             hc_08_status_error
  */
hc_08_status hc_08_cmd_set_ctout(hc_08_ST *hc_08, uint16_t time){
  if(time >= HC_08_CTOUT_MIN && time <= HC_08_CTOUT_MIN){
    uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%d", HC_08_COMMAND_CTOUT, time);  
    hc_08->uart.tx(hc_08->uart.buff_tx, size);
  }else{
    return hc_08_status_error;
  }
  
  return hc_08_status_ok;
}

/**
  * @brief  Request to the module connection timeout time
  * @param  *hc_08 pointer to the HC-08 module structure 
*/
void hc_08_cmd_ask_ctout(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_CTOUT, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Sending an CLEAR command
  * @param  *hc_08 pointer to the HC-08 module structure
  */
void hc_08_cmd_clear(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s", HC_08_COMMAND_CLEAR);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  LED ON/OFF
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  status led status. Takes one of the following values:
  *           hc_08_led_on,
  *           hc_08_led_off
  */
void hc_08_cmd_set_led(hc_08_ST *hc_08, hc_08_led status){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_LED, hc_08_led_c[status]);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Request to the module LED status
  * @param  *hc_08 pointer to the HC-08 module structure 
*/
void hc_08_cmd_ask_led(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_LED, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set Search UUID
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  value range of the Search UUID is 0~0xffff
  */
void hc_08_cmd_set_luuid(hc_08_ST *hc_08, uint16_t value){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%d", HC_08_COMMAND_LUUID, value);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Request to the module Search UUID
  * @param  *hc_08 pointer to the HC-08 module structure 
*/
void hc_08_cmd_ask_luuid(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_LUUID, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set Service UUID
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  value range of the Service UUID is 0~0xffff
  */
void hc_08_cmd_set_suuid(hc_08_ST *hc_08, uint16_t value){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%d", HC_08_COMMAND_SUUID, value);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Request to the module Service UUID
  * @param  *hc_08 pointer to the HC-08 module structure 
*/
void hc_08_cmd_ask_suuid(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_SUUID, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set Characteristic UUID
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  value range of the Characteristic UUID is 0~0xffff
  */
void hc_08_cmd_set_tuuid(hc_08_ST *hc_08, uint16_t value){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%d", HC_08_COMMAND_TUUID, value);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Request to the module Characteristic UUID
  * @param  *hc_08 pointer to the HC-08 module structure 
*/
void hc_08_cmd_ask_tuuid(hc_08_ST *hc_08){
  uint8_t size = sprintf(hc_08->uart.buff_tx, "%s%s", HC_08_COMMAND_TUUID, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  Set connection timeout time
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  value range of the connection timeout value is 1~300
  * @retval hc_08_status:
  *             hc_08_status_ok if 1<=value<=300
  *             hc_08_status_error
  */
hc_08_status hc_08_cmd_set_aust(hc_08_ST *hc_08, uint16_t value){
  if(value >= HC_08_AUST_MIN && value <= HC_08_AUST_MAX){
    uint8_t size = sprintf(&hc_08->uart.buff_tx[strlen(HC_08_COMMAND_AINT)], "%s%d", HC_08_COMMAND_AINT, (unsigned int) value);
  
    hc_08->uart.tx(hc_08->uart.buff_tx, size);
  }else{
    return hc_08_status_error;
  }
  
  return hc_08_status_ok;
}

/**
  * @brief  Request to the module Characteristic UUID
  * @param  *hc_08 pointer to the HC-08 module structure 
*/
void hc_08_cmd_ask_aust(hc_08_ST *hc_08){
  uint8_t size = sprintf(&hc_08->uart.buff_tx[strlen(HC_08_COMMAND_AINT)], "%s%s", HC_08_COMMAND_AINT, HC_08_TEXT_QUERY);
  
  hc_08->uart.tx(hc_08->uart.buff_tx, size);
}

/**
  * @brief  checking the module's response to the set command. 
  *         Only the presence of "OK" in the response is checked
  * @param  *hc_08 pointer to the HC-08 module structure 
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_check_set(hc_08_ST *hc_08){
  if(HC_08_BUFF_RX_SIZE >= sizeof(HC_08_TEXT_OK)){
    if(strstr((const char *)(uint32_t)&hc_08->uart.buff_rx, (const char *)HC_08_TEXT_OK)){
      return hc_08_status_ok;
    }
  }
  return hc_08_status_error;
}

/**
  * @brief  Parsing of the response to the AT+RX command is performed. The result will be 
  * recorded in the corresponding fields of the structure *hc_08.param. 
  * The physical response to the command may not correspond to that given in the datasheet. 
  * Example:
  * Name:HC-08
  * Role:Slave
  * Baud:115200,NONE
  * Addr:3C,E4,B0,89,DC,03
  * PIN :000000
  * www.hc01.com
  * www.hc01.com
  * www.hc01.com
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_base_param(hc_08_ST *hc_08, uint8_t size){
  uint32_t possition_start = 0;
  uint32_t possition_end = 0;
/* if the size of the received data is larger than the size of the reception buffer,
   something was overwritten*/
  if(size <= HC_08_BUFF_RX_SIZE){
    possition_start = strcspn((const char *)(hc_08->uart.buff_rx), (const char *)HC_08_TEXT_COLON) + strlen(HC_08_TEXT_COLON);

    // name
    if(possition_start != strlen(HC_08_TEXT_COLON)){
      hc_08->param.name_lenght = strcspn(&hc_08->uart.buff_rx[possition_start], (const char *)HC_08_TEXT_CR);
      possition_end = hc_08->param.name_lenght + possition_start;
      strncpy(hc_08->param.name, (const char *)((uint32_t)&hc_08->uart.buff_rx + possition_start), hc_08->param.name_lenght);
    }else{
      return hc_08_status_error;
    }
    
    //role
    if(strstr((const char *)(hc_08->uart.buff_tx), (const char *)hc_08_role_c[hc_08_role_master])){
       hc_08->param.role = hc_08_role_master;
    }else if(strstr((const char *)((uint32_t)&hc_08->uart.buff_rx + possition_end), (const char *)hc_08_role_c[hc_08_role_slave])){
       hc_08->param.role = hc_08_role_slave;
    }else{
      return hc_08_status_error;
    }
    possition_end = possition_end + strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx + possition_end), (const char *)HC_08_TEXT_COLON);
    
    //baud
    for(int i = 0; i < HC_08_BAUD_SIZE; i++){
      if(strstr((const char *)((uint32_t)&hc_08->uart.buff_rx + possition_end), (const char *)hc_08_baud_c[i])){
         hc_08->param.baud = i;
         break;
      }else if(i == HC_08_BAUD_SIZE - 1){
        return hc_08_status_error;
      }
    }
    possition_end = possition_end + strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx + possition_end), (const char *)HC_08_TEXT_COMMA);
    
    // PARITY
    for(int i = 0; i < HC_08_PARITY_SIZE; i++){
      if(strstr((const char *)((uint32_t)&hc_08->uart.buff_rx + possition_end), (const char *)hc_08_parity_bit_c[i])){
         hc_08->param.parity = i;
         break;
      }else if(i == HC_08_PARITY_SIZE - 1){
        return hc_08_status_error;
      }
    }
    
    possition_end = possition_end + strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx + possition_end), (const char *)HC_08_TEXT_COLON) + strlen(HC_08_TEXT_COLON);
    
    //Addr
    for(uint8_t i = 0; i < sizeof(hc_08->param.addres); i++){
      sscanf(&hc_08->uart.buff_rx[possition_end + i * 3], "%x", (int *)&hc_08->param.addres[i]);
    }
    possition_end = possition_end + strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx + possition_end), (const char *)HC_08_TEXT_COLON) + strlen(HC_08_TEXT_COLON);
    
    //pin
    for(uint8_t i = 0; i < sizeof(hc_08->param.addres); i++){
      sscanf(&hc_08->uart.buff_rx[possition_end + i], "%d", (int *)&hc_08->param.pin[i]);
    }
    possition_end = possition_end + strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx + possition_end), (const char *)HC_08_TEXT_CR) + sizeof(HC_08_TEXT_CR);
  }
   
  if(possition_end > HC_08_BUFF_RX_SIZE){
    return hc_08_status_error;
  }

  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+ROLE=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.role.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_role(hc_08_ST *hc_08, uint8_t size){
  uint32_t possition = strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx), (const char *)HC_08_TEXT_COMMA);
  
  for(int i = 0; i < HC_08_ROLE_SIZE; i++){
    if(strstr((const char *)(hc_08->uart.buff_rx), (const char *)hc_08_role_c[i])){
       hc_08->param.role = i;
       break;
    }else if(i == HC_08_BAUD_SIZE - 1){
      return hc_08_status_error;
    }
  }
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+NAME=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.name.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_name(hc_08_ST *hc_08, uint8_t size){
  uint32_t possition = strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx), (const char *)HC_08_TEXT_COLON);
  
  possition < size ? (hc_08->param.name_lenght = possition) : (hc_08->param.name_lenght = size);
  
  if(!possition){
    return hc_08_status_error;
  }
  
  strncpy(hc_08->param.name, hc_08->uart.buff_rx, hc_08->param.name_lenght);
  
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+ADDR=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.addres.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_address(hc_08_ST *hc_08, uint8_t size){
  uint32_t possition = strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx), (const char *)HC_08_TEXT_COLON);
  
  if(possition - 1 <= (sizeof(hc_08->param.addres) * 3)){
    for(uint8_t i = 0; i < sizeof(hc_08->param.addres); i++){
      sscanf(&hc_08->uart.buff_rx[i * 3], "%x", (int *)&hc_08->param.addres[i]);
    }
  }else{
    return hc_08_status_error;
  }
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+RFPM=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.rfpm.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_rfpm(hc_08_ST *hc_08, uint8_t size){
    uint32_t possition = strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx), (const char *)HC_08_TEXT_EQUEL);
  
  if(possition < size){
    for(int i = 0; i < HC_08_RFPM_SIZE; i++){
      if(strstr(&hc_08->uart.buff_rx[possition], (const char *)hc_08_rfpm_c[i])){
         hc_08->param.rfpm = i;
         break;
      }else if(i == HC_08_RFPM_SIZE - 1){
        return hc_08_status_error;
      }
    }
  }else{
    return hc_08_status_error;
  }
  
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+BAUD=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.baud, hc_08->param.parity.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_baud_and_parity(hc_08_ST *hc_08, uint8_t size){
  uint32_t possition = strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx), (const char *)HC_08_TEXT_EQUEL);
  
  if(possition < size){
    for(int i = 0; i < HC_08_BAUD_SIZE; i++){
      if(strstr(&hc_08->uart.buff_rx[possition], (const char *)hc_08_baud_c[i])){
         hc_08->param.baud = i;
         break;
      }else if(i == HC_08_BAUD_SIZE - 1){
        return hc_08_status_error;
      }
    }
  }else{
    return hc_08_status_error;
  }
  
  possition = strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx), (const char *)HC_08_TEXT_COMMA);
  
  if(possition < size){
    for(int i = 0; i < HC_08_PARITY_SIZE; i++){
      if(strstr(&hc_08->uart.buff_rx[possition], (const char *)hc_08_parity_bit_c[i])){
         hc_08->param.parity = i;
         break;
      }else if(i == HC_08_PARITY_SIZE - 1){
        return hc_08_status_error;
      }
    }
  }else{
    return hc_08_status_error;
  }
  
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+CONT=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.cont.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_connect(hc_08_ST *hc_08){
  for(int i = 0; i < HC_08_CONT_SIZE; i++){
    if(strstr((const char *)(hc_08->uart.buff_rx), (const char *)hc_08_cont_c[i])){
       hc_08->param.cont = i;
       break;
    }else if(i == HC_08_CONT_SIZE - 1){
      return hc_08_status_error;
    }
  }
  
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+MODE=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.mode.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_mode(hc_08_ST *hc_08){
  for(int i = 0; i < HC_08_CONT_SIZE; i++){
    if(strstr((const char *)(hc_08->uart.buff_rx), (const char *)hc_08_mode_c[i]) != NULL){
       hc_08->param.mode = i;
       break;
    }else if(i == HC_08_MODE_SIZE - 1){
      return hc_08_status_error;
    }
  }

  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+CINT=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.cint_min, hc_08->param.cint_max.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_cint(hc_08_ST *hc_08, uint8_t size){
  uint16_t result = 0;
  uint16_t possition = strcspn((const char *)(hc_08->uart.buff_rx), 
                                      (const char *)HC_08_TEXT_EQUEL) + 
                                      strlen(HC_08_TEXT_EQUEL);
  
  // cint_min
  if(possition < size){
    sscanf(&hc_08->uart.buff_rx[possition], "%d", (int *)&result);
    if (result >= HC_08_CINT_MIN && result <= HC_08_CINT_MAX){
      hc_08->param.cint_min = result;
    }else{
      return hc_08_status_error;
    }
  }else{
    return hc_08_status_error;
  }

  //cint_max
  possition = strcspn((const char *)(hc_08->uart.buff_rx), 
                                    (const char *)HC_08_TEXT_EQUEL) + 
                                    strlen(HC_08_TEXT_EQUEL);
  if(possition != size){
    sscanf(&hc_08->uart.buff_rx[possition], "%d", (int *)&result);
    if (result >= HC_08_CINT_MIN && result <= HC_08_CINT_MAX){
      hc_08->param.cint_max = result;
    }else{
      return hc_08_status_error;
    }
  }else{
    return hc_08_status_error;
  }
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+AINT=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.aint.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_aint(hc_08_ST *hc_08, uint8_t size){
  uint16_t result = 0;
  uint16_t possition = strcspn((const char *)(hc_08->uart.buff_rx), 
                                      (const char *)HC_08_TEXT_EQUEL) + 
                                      strlen(HC_08_TEXT_EQUEL);

    if(possition < size){
      sscanf(&hc_08->uart.buff_rx[possition], "%d", (int *)&result);
      if (result >= HC_08_AINT_MIN && result <= HC_08_AINT_MAX){
        hc_08->param.aint = result;
      }else{
        return hc_08_status_error;
      }
    }else{
      return hc_08_status_error;
    }
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+CTOUT=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.ctout.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_ctout(hc_08_ST *hc_08, uint8_t size){
  uint16_t result = 0;
  uint16_t possition = strcspn((const char *)(hc_08->uart.buff_rx), 
                                      (const char *)HC_08_TEXT_EQUEL) + 
                                      strlen(HC_08_TEXT_EQUEL);

    if(possition < size){
      sscanf(&hc_08->uart.buff_rx[possition], "%d", (int *)&result);
      if (result >= HC_08_CTOUT_MIN && result <= HC_08_CTOUT_MAX){
        hc_08->param.ctout = result;
      }else{
        return hc_08_status_error;
      }
    }else{
      return hc_08_status_error;
    }
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+LUUID=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.luuid.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_luuid(hc_08_ST *hc_08, uint8_t size){
  uint16_t possition = strcspn((const char *)(hc_08->uart.buff_rx), 
                                      (const char *)HC_08_TEXT_EQUEL) + 
                                      strlen(HC_08_TEXT_EQUEL);

    if(possition < size){
      sscanf(&hc_08->uart.buff_rx[possition], "%x", (int *)&hc_08->param.luuid);
    }else{
      return hc_08_status_error;
    }
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+SUUID=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.suuid.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_suuid(hc_08_ST *hc_08, uint8_t size){
  uint16_t possition = strcspn((const char *)(hc_08->uart.buff_rx), 
                                      (const char *)HC_08_TEXT_EQUEL) + 
                                      strlen(HC_08_TEXT_EQUEL);

    if(possition < size){
      sscanf(&hc_08->uart.buff_rx[possition], "%x", (int *)&hc_08->param.suuid);
    }else{
      return hc_08_status_error;
    }
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+TUUID=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.tuuid.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_tuuid(hc_08_ST *hc_08, uint8_t size){
  uint16_t possition = strcspn((const char *)(hc_08->uart.buff_rx), 
                                      (const char *)HC_08_TEXT_EQUEL) + 
                                      strlen(HC_08_TEXT_EQUEL);

    if(possition != size){
      sscanf(&hc_08->uart.buff_rx[possition], "%x", (int *)&hc_08->param.tuuid);
    }else{
      return hc_08_status_error;
    }
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+AUST=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.aust.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_aust(hc_08_ST *hc_08, uint8_t size){
  uint16_t result = 0;
  uint16_t possition = strcspn((const char *)(hc_08->uart.buff_rx), 
                                      (const char *)HC_08_TEXT_EQUEL) + 
                                      strlen(HC_08_TEXT_EQUEL);

  if(possition < size){
    sscanf(&hc_08->uart.buff_rx[possition], "%d", (int *)&result);
    if (result >= HC_08_AUST_MIN && result <= HC_08_AUST_MAX){
      hc_08->param.aust = result;
    }else{
      return hc_08_status_error;
    }
  }else{
    return hc_08_status_error;
  }
  return hc_08_status_ok;
}

/**
  * @brief  Parsing of the response to the AT+LED=? command is performed. The result will be 
  * recorded in the corresponding fields of the structure hc_08->param.led.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  size the size of received data. Actual is preferred, but HC_08_BUFF_RX_SIZE is acceptable
  * @retval hc_08_status:
  *             hc_08_status_ok
  *             hc_08_status_error
*/
hc_08_status hc_08_parse_led(hc_08_ST *hc_08, uint8_t size){
    uint32_t possition = strcspn((const char *)((uint32_t)&hc_08->uart.buff_rx), (const char *)HC_08_TEXT_EQUEL);
  
  if(possition < size){
    for(int i = 0; i < HC_08_LED_SIZE; i++){
      if(strstr(&hc_08->uart.buff_rx[possition], (const char *)hc_08_led_c[i])){
         hc_08->param.led = i;
         break;
      }else if(i == HC_08_LED_SIZE - 1){
        return hc_08_status_error;
      }
    }
  }else{
    return hc_08_status_error;
  }
  
  return hc_08_status_ok;
}

/**
  * @brief  Setting the connection status of the module with another device. The result will be 
  * recorded in the corresponding fields of the structure hc_08->status_connect.
  * @param  *hc_08 pointer to the HC-08 module structure
  * @param  status_connect Takes one of the following values:
  *                           hc_08_status_connected
  *                           hc_08_status_not_connected
*/
void hc_08_status_connect_set(hc_08_ST *hc_08, hc_08_status_connect status_connect){
  hc_08->status_connect = status_connect;
}

/**
  * @brief  Return the connection status of the module with another device. 
  * @param  *hc_08 pointer to the HC-08 module structure
  * @retval hc_08_status:
  *             hc_08_status_connected
  *             hc_08_status_not_connected
*/  
hc_08_status_connect hc_08_status_connect_get(hc_08_ST *hc_08, hc_08_status_connect status_connect){
  return hc_08->status_connect;
}

/**
  * @brief  Clearing the data receiving buffer
  * @param  *hc_08 pointer to the HC-08 module structure
*/  
void hc_08_clear_buff_tx(hc_08_ST *hc_08){
  for(int8_t i = 0; i < HC_08_BUFF_TX_SIZE; i++){
    hc_08->uart.buff_tx[i] = 0;
  }
}

/**
  * @brief  Clearing the data transfer buffer 
  * @param  *hc_08 pointer to the HC-08 module structure
*/  
void hc_08_clear_buff_rx(hc_08_ST *hc_08){
  for(int8_t i = 0; i < HC_08_BUFF_RX_SIZE; i++){
    hc_08->uart.buff_rx[i] = 0;
  }
}
