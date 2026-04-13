#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <nrfx_uarte.h>
#include <nrfx_rtc.h>
#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_systick.h>
#include <nrf_gpio.h>
#include <labb-1.h>

// Exorcise 1
#define PIN_TXD 20
#define PIN_RXD 22

nrfx_uarte_t uarte_instance = NRFX_UARTE_INSTANCE(0);
void uarte_init() {
    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);

    //Initierar UARTE:
    nrfx_err_t errr = nrfx_uarte_init(&uarte_instance, &config, NULL);
    if (errr != 0){
        //Här kan vi implementera felhantering, men för stunden håller vi tummarna att allt funkar
    }
}
void uarte_write(char* string, size_t stringLength) {
    nrfx_uarte_tx(&uarte_instance, string, stringLength, 0);
}
char getchar_uarte() {
    char c;
    nrfx_uarte_rx (&uarte_instance, &c, sizeof(char));
    uarte_write(&c, sizeof(char));
    return c;
}
#define RETURN_CHAR '\r'
#define BUFFER_OVERFLOW_ERROR_MESSAGE " (inputed string was longer that the buffer size)\r\n"
void read_string(char* buffer, size_t bufferSize) {
    int i;
    buffer[0] = getchar_uarte();
    // Read characters until the output buffer is full or a the return character character is given
    for (i = 1; buffer[i - 1] != RETURN_CHAR && i < bufferSize; i++)
        buffer[i] = getchar_uarte();

    // If the output buffer was filled and the last character was not the return character,
    // then let the user enter characthers untill a return character
    if (i == bufferSize && buffer[i - 1] != RETURN_CHAR) {
        while (getchar_uarte() != RETURN_CHAR); 
        uarte_write(BUFFER_OVERFLOW_ERROR_MESSAGE, sizeof(BUFFER_OVERFLOW_ERROR_MESSAGE));
    }

    // Terminate the string
    buffer[i - 1] = '\0';
}

#define NUMBER_STRING_BUFFER_SIZE 32
int read_int() {
    char stringOfNum[NUMBER_STRING_BUFFER_SIZE];

    read_string(stringOfNum, NUMBER_STRING_BUFFER_SIZE);

    return atoi(stringOfNum);
}

void send_int(int number) {
    char stringOfNum[NUMBER_STRING_BUFFER_SIZE];
    
    sprintf(stringOfNum, "%d", number);
    uarte_write(stringOfNum, strlen(stringOfNum));
}

// Exorcise 2
#define LED1 28
#define LED2 29 
#define LED3 30
#define LED4 31
#define BUTTON1 23
#define BUTTON2 24 
#define BUTTON3 8
#define BUTTON4 9
#define LED_OFF 1
#define LED_ON 0 
void button_led_init() {
    nrf_gpio_cfg_output(LED1);
    nrf_gpio_cfg_output(LED2);
    nrf_gpio_cfg_output(LED3);
    nrf_gpio_cfg_output(LED4);

    nrf_gpio_pin_write(LED1, LED_OFF);
    nrf_gpio_pin_write(LED2, LED_OFF);
    nrf_gpio_pin_write(LED3, LED_OFF);
    nrf_gpio_pin_write(LED4, LED_OFF);

    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);
}
void lightLEDWithButton() {

    nrfx_systick_init();

    button_led_init();
    
    while(1)
    {
        nrfx_systick_delay_ms(50);
        
        if (nrf_gpio_pin_read(BUTTON1) == 0){
            nrf_gpio_pin_write(LED1,LED_ON);
        }else {nrf_gpio_pin_write(LED1, LED_OFF);}

        if (nrf_gpio_pin_read(BUTTON2) == 0){
            nrf_gpio_pin_write(LED2,LED_ON);
        }else {nrf_gpio_pin_write(LED2, LED_OFF);}

        if (nrf_gpio_pin_read(BUTTON3) == 0){
            nrf_gpio_pin_write(LED3,LED_ON);
        }else {nrf_gpio_pin_write(LED3, LED_OFF);}

        if (nrf_gpio_pin_read(BUTTON4) == 0){
            nrf_gpio_pin_write(LED4,LED_ON);
        }else{nrf_gpio_pin_write(LED4, LED_OFF);}
    }
}

// Exorcise 3
const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);
void rtc_init() {
    const nrfx_rtc_config_t config = NRFX_RTC_DEFAULT_CONFIG;

    //Initierar RTC:
    nrfx_err_t errr = nrfx_rtc_init(&rtc_instance, &config, NULL);
    nrfx_rtc_enable(&rtc_instance);
}
void delay_s(int seconds) {
    nrfx_rtc_counter_clear(&rtc_instance);
    uint32_t startTime = nrfx_rtc_counter_get(&rtc_instance);
    uint32_t overflow = 0;

    uint32_t delta_rtc = startTime;
    uint32_t rtc;
    do {
        rtc = nrfx_rtc_counter_get(&rtc_instance);
        if (rtc < delta_rtc)
            overflow++;
    }
    while ((nrfx_rtc_counter_get(&rtc_instance) - startTime) / 32768 + overflow * 512 < seconds);
}

// Exorcise 4
void init_rng() {
    nrfx_systick_init();
    rtc_init();
    uarte_init();
    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);

    while (1)
    {
        while (nrf_gpio_pin_read(BUTTON1) != 0)
            nrfx_systick_delay_ms(50);

        srand(nrfx_rtc_counter_get(&rtc_instance));
        send_int(rand() % 1000);
        nrfx_systick_delay_ms(500);
    }
}
    