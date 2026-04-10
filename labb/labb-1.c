#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <nrfx_uarte.h>
#include <nrfx_rtc.h>


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
    char* c;
    nrfx_uarte_rx (&uarte_instance, c, sizeof(char));
    uarte_write(c, sizeof(char));
    return *c;
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
    uarte_write(stringOfNum, sizeof(stringOfNum));
}

// Exorcise 2
void lightLEDWithButton() {

}

// Exorcise 3
const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);
void rtc_init() {
    const nrfx_rtc_config_t config = NRFX_RTC_DEFAULT_CONFIG;

    //Initierar RTC:
    nrfx_err_t errr = nrfx_rtc_init(&rtc_instance, &config, NULL);
    if (errr != 0){
        //Här kan vi implementera felhantering, men för stunden håller vi tummarna att allt funkar
    }
}
void delay_s(int seconds) {
    nrfx_rtc_counter_clear(&rtc_instance);

    while (nrfx_rtc_counter_get(&rtc_instance) < seconds * 32768);
}

// Exorcise 4
void init_rng() {
    
}