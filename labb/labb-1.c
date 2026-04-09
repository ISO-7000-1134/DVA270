#include <stdio.h>
#include <stdlib.h>
#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>

#define LED1 28
#define LED2 29 
#define LED3 30
#define LED4 31
#define BUTTON1 23
#define BUTTON2 24 
#define BUTTON1 08
#define BUTTON2 09
#define LED_OFF 1
#define LE_DON 0 


// Exorcise 1
void read_string(char* buffer, size_t bufferSize) {

}

int read_int() {
    int number;

    return number;
}

void send_int(int number) {

}

// Exorcise 2
void lightLEDWithButton() {

    nrfx_systic_init();

    nrf_gpio_cfg_output(LED1);
    nrf_gpio_cfg_output(LED2);
    nrf_gpio_cfg_output(LED3);
    nrf_gpio_cfg_output(LED4);

    // Nollar LEDs
    nrf_gpio_pin_write(LED1, LED_OFF);
    nrf_gpio_pin_write(LED2, LED_OFF);
    nrf_gpio_pin_write(LED3, LED_OFF);
    nrf_gpio_pin_write(LED4, LED_OFF);

    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO-PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON2, NRF_GPIO-PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON3, NRF_GPIO-PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON4, NRF_GPIO-PIN_PULLUP);

    while(1)
    {
        nrf_systick_delay_ms(50);

        if (nrf_gpio_pin_read(BUTTON1) == 0){
            nrf_gpio_pin_write(LED1,LED_ON)
        }else {nrf_gpio_pin_write(LED1, LED_OF)}
    }
}

// Exorcise 3
void delay_s(int seconds) {

}

// Exorcise 4
void init_rng() {
    
}