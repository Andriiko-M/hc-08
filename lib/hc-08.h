#include <stdint.h>

#define HC_08_BUFF_RX_SIZE   0x7f
#define HC_08_BUFF_TX_SIZE   0x64

#define HC_08_COMMAND_AT            "AT"
#define HC_08_COMMAND_ATPLUS        "AT+"
#define HC_08_COMMAND_RX            "AT+RX"
#define HC_08_COMMAND_DEFAULT       "AT+DEFAULT"
#define HC_08_COMMAND_RESET         "AT+RESET"
#define HC_08_COMMAND_VERSION       "AT+VERSION"

#define HC_08_COMMAND_ROLE          "AT+ROLE="
#define HC_08_COMMAND_BAUD          "AT+BAUD="
#define HC_08_COMMAND_NAME          "AT+NAME="
#define HC_08_COMMAND_PASS          "AT+PASS="
#define HC_08_COMMAND_TYPE          "AT+TYPE="
#define HC_08_COMMAND_ADDR          "AT+ADDR="
#define HC_08_COMMAND_RFPM          "AT+RFPM="
#define HC_08_COMMAND_CONT          "AT+CONT="
#define HC_08_COMMAND_AVDA          "AT+AVDA="
#define HC_08_COMMAND_MODE          "AT+MODE="
#define HC_08_COMMAND_AINT          "AT+AINT="
#define HC_08_COMMAND_CINT          "AT+CINT="
#define HC_08_COMMAND_CTOUT         "AT+CTOUT="
#define HC_08_COMMAND_CLEAR         "AT+CLEAR"
#define HC_08_COMMAND_LED           "AT+LED="
#define HC_08_COMMAND_LUUID         "AT+LUUID="
#define HC_08_COMMAND_SUUID         "AT+SUUID="
#define HC_08_COMMAND_TUUID         "AT+TUUID="
#define HC_08_COMMAND_AUST          "AT+AUST="

#define HC_08_TEXT_COMMA          ","
#define HC_08_TEXT_EQUEL          "="
#define HC_08_TEXT_QUERY         "?"
#define HC_08_TEXT_OK         "OK"
#define HC_08_TEXT_NAME          "Name"
#define HC_08_TEXT_ROLE          "Role"
#define HC_08_TEXT_BAUD         "Baud"
#define HC_08_TEXT_ADDR         "Addr"
#define HC_08_TEXT_PIN         "PIN"
#define HC_08_TEXT_COLON         ":"
#define HC_08_TEXT_CR         "\r" //'\r'

#define HC_08_MAX_NAME_LENGHT         12
#define HC_08_ADDRES_LENGHT         12

#define HC_08_AINT_MAX  (uint16_t) 16000
#define HC_08_AINT_MIN  (uint16_t) 32

#define HC_08_CINT_MAX  (uint16_t) 3199
#define HC_08_CINT_MIN  (uint16_t) 6

#define HC_08_CTOUT_MAX  (uint16_t) 3200
#define HC_08_CTOUT_MIN  (uint16_t) 10

#define HC_08_AUST_MAX  (uint16_t) 300
#define HC_08_AUST_MIN  (uint16_t) 1

typedef enum{
  hc_08_role_master,
  hc_08_role_slave
}hc_08_role;

static const char * const hc_08_role_c[] = {
  [hc_08_role_master] = "Master",
  [hc_08_role_slave] = "Slave"
};
#define HC_08_ROLE_SIZE 0x02

typedef enum{
  hc_08_rfpm_4dBm,
  hc_08_rfpm_0dBm,
  hc_08_rfpm_m6dBm,
  hc_08_rfpm_m23dBm
}hc_08_rfpm;

static const char * const hc_08_rfpm_param_c[] = {
  [hc_08_rfpm_4dBm] = "0",
  [hc_08_rfpm_0dBm] = "1",
  [hc_08_rfpm_m6dBm] = "2",
  [hc_08_rfpm_m23dBm] = "3"
};

static const char * const hc_08_rfpm_c[] = {
  [hc_08_rfpm_4dBm] = "4dBm",
  [hc_08_rfpm_0dBm] = "0dBm",
  [hc_08_rfpm_m6dBm] = "-6dBm",
  [hc_08_rfpm_m23dBm] = "-23dBm"
};
#define HC_08_RFPM_SIZE 0x08

typedef enum{
  hc_08_baud_1200bps,
  hc_08_baud_2400bps,
  hc_08_baud_4800bps,
  hc_08_baud_9600bps,
  hc_08_baud_19200bps,
  hc_08_baud_38400bps,
  hc_08_baud_57600bps,
  hc_08_baud_115200bps
}hc_08_baud;

static const char * const hc_08_baud_c[] = {
  [hc_08_baud_1200bps] = "1200",
  [hc_08_baud_2400bps] = "2400",
  [hc_08_baud_4800bps] = "4800",
  [hc_08_baud_9600bps] = "9600",
  [hc_08_baud_19200bps] = "19200",
  [hc_08_baud_38400bps] = "38400",
  [hc_08_baud_57600bps] = "57600",
  [hc_08_baud_115200bps] = "115200"
};
#define HC_08_BAUD_SIZE 0x08

typedef enum{
  hc_08_parity_bit_no_parity,
  hc_08_parity_bit_even_parity,
  hc_08_parity_bit_odd_parity
}hc_08_parity_bit;

static const char * const hc_08_parity_bit_c[] = {
  [hc_08_parity_bit_no_parity] = "NONE",
  [hc_08_parity_bit_even_parity] = "EVEN",
  [hc_08_parity_bit_odd_parity] = "ODD"
};
#define HC_08_PARITY_SIZE 0x03

typedef enum{
  hc_08_mode_full,
  hc_08_mode_level_1,
  hc_08_mode_level_2
}hc_08_mode;

static const char * const hc_08_mode_c[] = {
  [hc_08_mode_full] = "0",
  [hc_08_mode_level_1] = "1",
  [hc_08_mode_level_2] = "2"
};

#define HC_08_MODE_SIZE 0x03

typedef enum{
  hc_08_led_on,
  hc_08_led_off
}hc_08_led;

 static const char * const hc_08_led_c[] = {
  [hc_08_led_on] = "ON",
  [hc_08_led_off] = "OFF"
};

#define HC_08_LED_SIZE 0x02


typedef enum{
  hc_08_cont_0,
  hc_08_cont_1
}hc_08_cont;

static const char * const hc_08_cont_c[] = {
  [hc_08_cont_0] = "Connectable",
  [hc_08_cont_1] = "Non-Connectable"
};

 static const char * const hc_08_cont_param_c[] = {
  [hc_08_cont_0] = "0",
  [hc_08_cont_1] = "1"
};

#define HC_08_CONT_SIZE 0x02

typedef enum{
  hc_08_status_ok = 0x00,
  hc_08_status_error = 0xff
}hc_08_status;

typedef enum{
  hc_08_status_connected = 0x00,
  hc_08_status_not_connected = 0x01
}hc_08_status_connect;

typedef struct
{
  struct{
    char name[12];
    uint8_t name_lenght;
    hc_08_role role;
    hc_08_baud baud;  
    hc_08_parity_bit parity;
    uint8_t addres[6];
    uint8_t pin[6];
    hc_08_rfpm rfpm;
    hc_08_cont cont;
    hc_08_mode mode;
    uint16_t aint;
    uint16_t cint_min;
    uint16_t cint_max;
    uint16_t ctout;
    uint16_t luuid;
    uint16_t suuid;
    uint16_t tuuid;
    uint16_t aust;
    uint8_t led;
  }param;
  
  struct
  {
    char buff_rx[HC_08_BUFF_RX_SIZE];
    char buff_tx[HC_08_BUFF_TX_SIZE];
    void (*tx)  (char *buff, uint16_t size);
    void (*rx)  (char *buff, uint16_t size);
  }uart;
  
  hc_08_status_connect status_connect;
} hc_08_ST;

void hc_08_reg_uart_cbfunc(hc_08_ST *hc_08,
                            void (*uart_tx)(char *buff, uint16_t size), 
                            void (*uart_rx)(char *buff, uint16_t size));
void hc_08_read_answer(hc_08_ST *hc_08);

void hc_08_cmd_at(hc_08_ST *hc_08);
void hc_08_cmd_rx(hc_08_ST *hc_08);
void hc_08_cmd_default(hc_08_ST *hc_08);
void hc_08_cmd_reset(hc_08_ST *hc_08);
void hc_08_cmd_version(hc_08_ST *hc_08);
void hc_08_cmd_clear(hc_08_ST *hc_08);

void hc_08_cmd_set_role(hc_08_ST *hc_08, hc_08_role role);
void hc_08_cmd_set_name(hc_08_ST *hc_08, char *name);
void hc_08_cmd_set_address(hc_08_ST *hc_08, uint8_t *address);
void hc_08_cmd_set_rf_power(hc_08_ST *hc_08, hc_08_rfpm rfpm_param);
void hc_08_cmd_set_uart_baud(hc_08_ST *hc_08, hc_08_baud baud);
void hc_08_cmd_set_uart_baud_parity(hc_08_ST *hc_08, hc_08_baud baud, hc_08_parity_bit parity_bit);
void hc_08_cmd_set_cont(hc_08_ST *hc_08, hc_08_cont cont);
void hc_08_cmd_set_avda(hc_08_ST *hc_08, char *avda);
void hc_08_cmd_set_mode(hc_08_ST *hc_08, hc_08_mode mode);
hc_08_status hc_08_cmd_set_aint(hc_08_ST *hc_08, uint16_t value);
hc_08_status hc_08_cmd_set_cint(hc_08_ST *hc_08, uint16_t time);
hc_08_status hc_08_cmd_set_cint_min_max(hc_08_ST *hc_08, uint16_t time_min, uint16_t time_max);
hc_08_status hc_08_cmd_set_ctout(hc_08_ST *hc_08, uint16_t time);
void hc_08_cmd_set_luuid(hc_08_ST *hc_08, uint16_t value);
void hc_08_cmd_set_suuid(hc_08_ST *hc_08, uint16_t value);
void hc_08_cmd_set_tuuid(hc_08_ST *hc_08, uint16_t value);
hc_08_status hc_08_cmd_set_aust(hc_08_ST *hc_08, uint16_t value);

void hc_08_cmd_ask_role(hc_08_ST *hc_08);
void hc_08_cmd_ask_name(hc_08_ST *hc_08);
void hc_08_cmd_ask_address(hc_08_ST *hc_08);
void hc_08_cmd_ask_rf_power(hc_08_ST *hc_08);
void hc_08_cmd_ask_uart_baud_parity(hc_08_ST *hc_08);
void hc_08_cmd_ask_rfpm(hc_08_ST *hc_08);
void hc_08_cmd_ask_mode(hc_08_ST *hc_08);
void hc_08_cmd_ask_aint(hc_08_ST *hc_08);
void hc_08_cmd_ask_cint_min_max(hc_08_ST *hc_08);
void hc_08_cmd_ask_ctout(hc_08_ST *hc_08);
void hc_08_cmd_set_led(hc_08_ST *hc_08, hc_08_led status);
void hc_08_cmd_ask_led(hc_08_ST *hc_08);
void hc_08_cmd_ask_luuid(hc_08_ST *hc_08);
void hc_08_cmd_ask_suuid(hc_08_ST *hc_08);
void hc_08_cmd_ask_tuuid(hc_08_ST *hc_08);
void hc_08_cmd_ask_aust(hc_08_ST *hc_08);

hc_08_status hc_08_check_set(hc_08_ST *hc_08);
hc_08_status hc_08_parse_base_param(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_role(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_name(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_address(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_rfpm(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_baud_and_parity(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_connect(hc_08_ST *hc_08);
hc_08_status hc_08_parse_mode(hc_08_ST *hc_08);
hc_08_status hc_08_parse_cint(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_aint(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_ctout(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_luuid(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_suuid(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_tuuid(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_aust(hc_08_ST *hc_08, uint8_t size);
hc_08_status hc_08_parse_led(hc_08_ST *hc_08, uint8_t size);

void hc_08_status_connect_set(hc_08_ST *hc_08, hc_08_status_connect status_connect);
hc_08_status_connect hc_08_status_connect_get(hc_08_ST *hc_08, hc_08_status_connect status_connect);
void hc_08_clear_buff_tx(hc_08_ST *hc_08);
void hc_08_clear_buff_rx(hc_08_ST *hc_08);
