# The library is designed to work with the BLE module HC-08 V3.3 (2020-10-16) (Compatibility with other versions has not been tested)

# Connecting the library

1) Connect the library 
#include "hc-08.h"
2) Implement the functions of receiving and transmitting data using UART
``` C
void (*uart_tx)(char *buff, uint16_t size)
void (*uart_rx)(char *buff, uint16_t size)
```
For example (for STM32H743ZI using the HAL library):
``` C
void uart_rx(char *buff, uint16_t size){
  HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t*)buff, size)
}
void uart_tx(char *buff, uint16_t size){
  HAL_UART_Transmit_DMA(&huart2, (uint8_t*)buff, size);
}
```
The names of the functions are not important. The main thing is that they accept these parameters.
4) Declare the structure of the module
```C
hc_08_ST hc_08;
```
5) Bind the exchange functions to the module structure using the hc_08_reg_uart_cbfunc(...) function.
``` C
hc_08_reg_uart_cbfunc(&hc_08, uart_tx, uart_rx);
```

# Library description
The library is based on the "HC-08 BLUETOOTH UART COMMUNICATION MODULE V3.1 USER MANUAL".
Using the library, you can work with all AT Commands. However, there are limitations when working with responses to these commands - all responses to the Set command will only check for the word OK.

To send commands: AT, AT+RX, AT+DEFAULT, AT+RESET, AT+VERSION and CLEAR commands, use the "hc_08_cmd_" + AT command functions.
For other commands, the functions are used: 
- to set the value "hc_08_cmd_set_" + AT command;
- to request the current value "hc_08_cmd_ask_" + AT command;

To read the response to the command, use the function void hc_08_read_answer(hc_08_ST *hc_08). After that, the read response will be written to the receive buffer of the module structure.
To get data from the received response, you need to use one of the following functions:
- hc_08_status hc_08_check_set(hc_08_ST *hc_08) - to check the value set. But only the presence of the word OK will be checked;
- "hc_08_parse_" + AT command. The read value will be written to the corresponding field of the hc_08->param structure. But if an error occurs during parsing, the function will return the status hc_08_status_error.

Before using the hc_08_parse_name(hc_08_ST *hc_08, uint8_t size) function to correctly determine the module name, you need to clear the receive buffer using the void hc_08_clear_buff_rx(hc_08_ST *hc_08) function.

In the size parameter for the functions "hc_08_parse_...(hc_08_ST *hc_08, uint8_t size)" you need to specify the size of the received data. However, if you do not specify the amount of received data, you can specify HC_08_BUFF_RX_SIZE instead of the actual size.

Sending data is performed using 
``` C
hc_08->uart.tx(char *buff, uint16_t size);
```
