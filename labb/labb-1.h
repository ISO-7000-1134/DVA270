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

#ifndef LABB_1
#define LABB_1

// Exorcise 1
void uarte_init();
void uarte_write(char* string, size_t stringLength);
void read_string(char* buffer, size_t bufferSize);
int read_int();
void send_int(int number);

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

void button_led_init();
void lightLEDWithButton();

// Exorcise 3
void rtc_init();
void delay_s(int seconds);

// Exorcise 4
void init_rng();

#endif