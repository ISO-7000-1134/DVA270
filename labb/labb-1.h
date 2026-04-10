#include <stddef.h>
#include <stdlib.h>

#ifndef LABB_1
#define LABB_1

// Exorcise 1
void uarte_init();
void uarte_write(char* string, size_t stringLength);
void read_string(char* buffer, size_t bufferSize);
int read_int();
void send_int(int number);

// Exorcise 2
void lightLEDWithButton();

// Exorcise 3
void rtc_init();
void delay_s(int seconds);

// Exorcise 4
void init_rng();

#endif