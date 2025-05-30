#ifndef _INFINITE_NUMBER_H_
    #define _INFINITE_NUMBER_H_

    #include <stdlib.h>
    #include <unistd.h>

typedef struct infinite_number_s {
    unsigned char digit;
    struct infinite_number_s *next;
} ifNumber;

// create
ifNumber *ifNumber_create(void);

// destroy
void ifNumber_destroy(ifNumber *nb);

// display
void ifNumber_display(ifNumber *nb);

// set values
ifNumber *ifNumber_set_number(ifNumber *nb, unsigned long val);

// Operations
ifNumber *ifNumber_add(ifNumber *nb, ifNumber *add);

#endif // _INFINITE_NUMBER_H_
