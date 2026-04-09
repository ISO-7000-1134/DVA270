#include <stdlib.h>
#include <stddef.h>
#include <nrfx_uarte.h>

// Exorcise 1
char getchar() {
    char* c;
    nrfx_uarte_rx (&instance, c, sizeof(char));
    uarte_write(c, sizeof(char));
    return *c;
}
#define RETURN_CHAR '\r'
void read_string(char* buffer, size_t bufferSize) {
    int i;
    buffer[0] = getchar();
    // Read characters until the output buffer is full or a the return character character is given
    for (i = 1; output[i - 1] != RETURN_CHAR && i < bufferSize; i++)
        buffer[i] = getchar();

    // If the output buffer was filled and the last character was not the return character,
    // then let the user enter characthers untill a return character
    if (i == bufferSize && output[i - 1] != RETURN_CHAR)
        while (getchar() != RETURN_CHAR); 

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

}

// Exorcise 2
void lightLEDWithButton() {

}

// Exorcise 3
void delay_s(int seconds) {

}

// Exorcise 4
void init_rng() {
    
}