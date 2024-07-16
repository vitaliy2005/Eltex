#ifndef STRUCT_FUNCTION_H
#define STRUCT_FUNCTION_H

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <bits/types/siginfo_t.h>

typedef struct Contact
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
}Contact;

typedef struct Node
{
    int32_t key;
    Contact value;
    struct Node *left;
    struct Node *right;
    int32_t height;
} Node;


int height(Node *N);
int max(int a, int b);
Node* newNode(int key, Contact value);
Contact createContact();
Node* deleteNode(Node* root, int32_t key);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *N);
Node* insert(Node* node, int key);
void preOrder(Node *root);
void printListContact(Contact* contact);
void editContact(Node* root, int32_t index);



#endif
