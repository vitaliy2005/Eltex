#include "structFunctions.h"


int32_t height(Node *N)
{
    if (N == NULL) return 0;
    return N->height;
}

int32_t max(int32_t a, int32_t b)
{
    return (a > b) ? a : b;
}

Node* findMin(Node* node)
{
    if (node->left != NULL)
    {
        return findMin(node->left);
    }
    else
    {
        return node;
    }
}

Node* deleteNode(Node* root, int32_t key)
{
    if (root == NULL)
    {
        return root;
    }
    else if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {

        if (root->left == NULL && root->right == NULL)
        {
            root->height = 1 - max(height(root->left), height(root->right));
            free(root);
            root = NULL;
        }
        else if (root->left == NULL)
        {
            root->height = 1 - max(height(root->left), height(root->right));
            Node* temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            root->height = 1 - max(height(root->left), height(root->right));
            Node* temp = root;
            root = root->left;
            free(temp);
        }
        else
        {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    int32_t balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    if (balance > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* newNode(int key, Contact value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}


Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int32_t getBalance(Node *N)
{
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

Node* insert(Node* node, int32_t key)
{
    if (node == NULL)
    {
            node = newNode(key, createContact());
    }
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
    {
        printf("%d\n", key);
        return node;
    }


    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preOrder(Node *root)
{
    if(root != NULL)
    {
        printf("id контакта %d\n", root->key);
        printListContact(&root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}


void printListContact(Contact* contact)
{
        printf("Фамилия: %s\n", contact->surname);
        printf("Имя: %s\n", contact->firstname);
        printf("Отчество: %s\n", contact->fathername);
        printf("Место работы: %s\n", contact->place_work);
        printf("Позиция на работе: %s\n", contact->position);
        printf("Электронная почта: %s\n", contact->mail);
        printf("Номер телефона: %s\n", contact->nummer);
        printf("Тег в телеграме: %s\n", contact->telegramProfile);
        printf("Ссылка профиля во Вконтакте: %s\n\n", contact->vkLink);
}

Contact createContact()
{
    int32_t status;
    Contact* temp = (Contact*)malloc(sizeof(Contact));

    printf("1.Добавить все данные\n"
            "2.Добавить основные данные\n");
    scanf("%d", &status);

    if (status == 2)
    {
        printf("введите фамилию\n");
        scanf("%s", temp->surname);
        printf("введите имя\n");
        scanf("%s", temp->firstname);
        printf("введите отчесвто\n");
        scanf("%s", temp->fathername);
        strcpy(temp->place_work,  "Отсутствует");
        strcpy(temp->position,  "Отсутствует");
        strcpy(temp->mail,  "Отсутствует");
        strcpy(temp->nummer,  "Отсутствует");
        strcpy(temp->telegramProfile,  "Отсутствует");
        strcpy(temp->vkLink,  "Отсутствует");
    }
    else
    {
        printf("Введите фамилию\n");
        scanf("%s", temp->surname);
        printf("Введите имя\n");
        scanf("%s", temp->firstname);
        printf("Введите отчесвто\n");
        scanf("%s", temp->fathername);
        printf("Введите место работы\n");
        scanf("%s", temp->place_work);
        printf("Введите позицию на работе\n");
        scanf("%s", temp->position);
        printf("Введите почту\n");
        scanf("%s", temp->mail);
        printf("Введите номер телефона\n");
        scanf("%s", temp->nummer);
        printf("Введите тег телеграм профиля\n");
        scanf("%s", temp->telegramProfile);
        printf("Введите ссылку страницы во Вконтакте\n");
        scanf("%s", temp->vkLink);
    }
    system("clear");
    printf("Контакт добавлен\n\n");
    return *temp;
}

void editContact(Node* root, int32_t index)
{
    if(root->key != index)
    {
        preOrder(root->left);
        preOrder(root->right);
    }
    else
    {
        int32_t status;
        printf("1.Изменить все данные"
               "2.Изменить основные данные\n");
        scanf("%d", &status);
        system("clear");
        printf("Новая фамилия\n");
        scanf("%s", root->value.surname);
        printf("Новое имя\n");
        scanf("%s", root->value.firstname);
        printf("Новое отчество\n");
        scanf("%s", root->value.fathername);
        if (status == 2)
        {
            system("clear");
            printf("Данные в контакте %d изменены\n\n", index);
            return;
        }
        else
        {
            printf("Новое место работы\n");
            scanf("%s", root->value.place_work);
            printf("Новая позиция на работе\n");
            scanf("%s", root->value.position);
            printf("Новая почта\n");
            scanf("%s", root->value.mail);
            printf("Новый номер телефона\n");
            scanf("%s", root->value.nummer);
            printf("Новый тег телеграм профиля\n");
            scanf("%s", root->value.telegramProfile);
            printf("Новая ссылка страницу во Вконтакте\n");
            scanf("%s", root->value.vkLink);
            system("clear");
            printf("Данные в контакте %d изменены\n\n", index);
        }
    }
}

    void swap(Contact* a, Contact* b)
    {
        Contact temp = *a;
        *a = *b;
        *b = temp;
    }
