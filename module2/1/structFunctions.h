#ifndef STRUCT_FUNCTION_H
#define STRUCT_FUNCTION_H

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

struct Contact
{
    char surname[40];
    char firstname[40];
    char fathername[40];

    char place_work[40];
    char position[40];

    char nummer[40];
    char mail[40];
    char vkLink[40];
    char telegramProfile[40];
};

void editContact(struct Contact* contacts, int32_t n);
void printListContacts(struct Contact*);
void copyArray(char *source, char *destination);
struct Contact* deleteContact(struct Contact* contacts, int32_t n);
struct Contact* addContact(struct Contact* contacts);
#endif
