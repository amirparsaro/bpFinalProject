#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct book
{
    int serial; // Emtiazi!
    char esm[100];
    char nevisande[100];
    char reshte[50];
    int mojodbodan;
    struct book *next;
} book;

typedef struct user
{
    char username[50];
    char password[50];

} User;

typedef struct request
{
    int serial;
    char username[50];
    struct request *next;
} request;

void ezafekardanrequest(request **head, int serial, char username[])
{
    request *newRequest = (request *)malloc(sizeof(request));
    newRequest->serial = serial;
    strcpy(newRequest->username, username);
    newRequest->next = *head;
    *head = newRequest;
}

void neshandadarequest(request *head)
{
    request *current = head;
    printf("list darkhast shodehaye ketab\n");
    while (current != NULL)
    {
        printf("serial: %d\n", current->serial);
        printf("username: %s\n", current->username);
        printf("--------------------------------------\n");
        current = current->next;
    }
}

void savekardanrequest(request *head, char *esmfile)
{
    FILE *fp = fopen(esmfile, "w");
    if (!fp)
    {
        printf("file mojod nist\n");
        return;
    }
    request *current = head;
    while (current != NULL)
    {
        fprintf(fp, "%d %s\n", current->serial, current->username);
        current = current->next;
    }
    fclose(fp);
}

void loadkardanrequest(request **head, char *esmfile)
{
    FILE *fp = fopen(esmfile, "r");
    if (!fp)
    {
        printf("file mojod nist\n");
        return;
    }
    int serial;
    char username[50];
    while (fscanf(fp, "%d %s", &serial, username) != EOF)
    {
        ezafekardanrequest(head, serial, username);
    }
    fclose(fp);
}

void ezafekardanketab(book **head, int serial, char *esm,
                      char *nevisande, char *reshte, int mojodbodan)
{
    book *newbook = (book *)malloc(sizeof(book));
    newbook->serial = serial;
    strcpy(newbook->esm, esm);
    strcpy(newbook->nevisande, nevisande);
    strcpy(newbook->reshte, reshte);
    newbook->mojodbodan = mojodbodan;
    newbook->next = *head;
    *head = newbook;
}

void savekardanketab(book *head, char *esmfile)
{
    FILE *fp = fopen(esmfile, "w");
    if (!fp)
    {
        printf("file mojood nist");
    }
    book *current = head;
    while (current != NULL)
    {
        fprintf(fp, "%d %s %s %s %d\n",
                current->serial, current->esm, current->nevisande,
                current->reshte, current->mojodbodan);
        current = current->next;
    }
    fclose(fp);
}

void loadkardanketabha(book **head, char *esmfile)
{
    FILE *fp = fopen(esmfile, "r");
    int serial, mojodbodan;
    char esm[100], nevisande[100], reshte[50];
    if (fp == NULL)
    {
        printf("file ketab ha vojood nadarad.\n");
    }
    while (fscanf(fp, "%d %s %s %s %d", &serial, esm, nevisande, reshte, &mojodbodan) != EOF)
    {
        ezafekardanketab(head, serial, esm, nevisande, reshte, mojodbodan);
    }
    fclose(fp);
}

void neshandadaanketab(book *head)
{
    book *current = head;
    printf("list ketabha\n");
    while (current != NULL)
    {
        printf("serial: %d", current->serial);
        printf("esm: %s\n", current->esm);
        printf("nevisande: %s\n", current->nevisande);
        printf("reshte: %s\n", current->reshte);
        printf("mojodbadan: %d\n", current->mojodbodan);
        printf("--------------------------------------\n");
        current = current->next;
    }
}

void neshandadaanketabdaneshjoo(book *head, char reshte[50])
{
    book *current = head;
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("==================================== list ketabha ====================================\n");
    while (current != NULL)
    {
        if (strcmp(reshte, current->reshte) == 0)
        {
            printf("esm: %s\n", current->esm);
            printf("nevisande: %s\n", current->nevisande);
            printf("reshte: %s\n", current->reshte);
            printf("mojodi ketab: %d\n", current->mojodbodan);
            printf("serial: %d\n", current->serial);
            printf("--------------------------------------\n");
            current = current->next;
        }
        else
            current = current->next;
    }
}

void hazfkardanketab(book **head, int serial)
{
    book *current = *head;
    book *previous = NULL;
    while (current != NULL)
    {
        if (current->serial == serial)
        {
            if (previous == NULL)
            {
                *head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            printf("ketab hazf shod\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("ketabe morede nazar peyda nashod\n");
}

void darkhastketab(book *head, int Serial, char reshte[], char username[], request *requests)
{
    while (head != NULL)
    {
        if (head->serial == Serial && head->mojodbodan != 0 && strcmp(head->reshte, reshte) == 0)
        {
            printf("ketab %s darkhast dadeshod\n", head->esm);
            head->mojodbodan -= 1;
            ezafekardanrequest(&requests, Serial, username);
            return;
        }
        if (head->serial == Serial && head->mojodbodan == 0)
        {
            printf("ketab morednazar mojod nist\n");
            return;
        }
        if (head->serial == Serial && head->mojodbodan != 0 && strcmp(head->reshte, reshte) != 0)
        {
            printf("reshte shoma ba ketab yeksan nist\n");
            return;
        }
        head = head->next;
    }
    printf("ketab morede nazar peyda nashod\n");
}

void bargardondanketab(book *head, int serial)
{
    while (head != NULL)
    {
        if (head->serial == serial)
        {
            printf("ketab %s barghardande shod", head->esm);
            head->mojodbodan += 1;
            return;
        }
        head = head->next;
    }
    printf("ketab peyda nashod");
}

void tarikhcheketab(char *user, int serial, char *fileName, int res)
{
    if (res == 1)
    {

        FILE *tarikhche = fopen(fileName, "a");
        fprintf(tarikhche, "%s %d\n", user, serial);
        fclose(tarikhche);
        return;
    }
}

void randompassgen(char pass[], int length) // Emtiazi!
{
    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        pass[i] = rand() % 90 + 33;
    }
    return;
}

void editketab(book *head, int serial, int num)
{
    while (head != NULL)
    {
        if (head->serial == serial)
        {
            printf("edit ketab %s\n", head->esm);
            if (num == 1)
            {
                int s;
                scanf("%d", &s);
                head->serial = s;
                return;
            }
            else if (num == 2)
            {
                char esms[100];
                scanf("%s", esms);
                strcmp(head->esm, esms);
                return;
            }
            else if (num == 3)
            {
                char nevis[100];
                scanf("%s", nevis);
                strcmp(head->nevisande, nevis);
                return;
            }
            else if (num == 4)
            {
                char re[50];
                scanf("%s", re);
                strcmp(head->reshte, re);
                return;
            }
            else if (num == 5)
            {
                int te;
                scanf("%d", &te);
                head->mojodbodan = te;
                return;
            }
            else
                printf("na motabar\n");
        }
        head = head->next;
    }
}

int main()
{
    book *books = NULL;
    request *requests = NULL;
    loadkardanketabha(&books, "books.txt");
    loadkardanrequest(&requests, "requests.txt");

    printf("be samane modiriate ketabkhane khosh amadid.\n");
    int running = 1;
    char page[50] = "logIn";
    char type[50];
    char usern[50], pass[50];
    while (running)
    {
        if (strcmp(page, "logIn") == 0)
        {
            printf("\n\n\n\n\n");
            printf("==================================== log-in ====================================\n");
            printf("baraye khorooj az barname \"0\" ra type konid.\n");
            printf("Naghshe khod ra entekhab konid: ketabdar(1) ya daneshjoo(2): ");
            scanf("%s", type);

            if (strcmp(type, "1") == 0)
            {
                printf("username ra vared konid: ");
                scanf("%s", usern);

                printf("password ra vared konid: ");
                scanf("%s", pass);

                FILE *loginFile = fopen("login_librarian.txt", "r");
                if (loginFile == NULL)
                {
                    printf("file vojood nadarad. dar hale sakht file...\n");
                    FILE *fileMaker = fopen("login_librarian.txt", "w");
                    fprintf(fileMaker, "Admin\nAdmin\n");
                    fclose(fileMaker);

                    printf("file eijad shod!\n");
                }
                else
                {
                    char username[50], password[50];
                    while (fscanf(loginFile, "%s\n%s", username, password) != EOF)
                    {
                        printf("%s %s\n", username, password);
                        if (strcmp(usern, username) == 0 && strcmp(pass, password) == 0)
                        {
                            printf("karbar (%s) | shoma ba movafaghiat vared shodid!\n", usern);
                            strcpy(page, "menu");
                            break;
                        }
                    }
                    if (strcmp(page, "logIn") == 0)
                    {
                        printf("karbar dar samane vojoood nadarad!\n");
                    }
                }
            }
            else if (strcmp(type, "2") == 0)
            {
                printf("username ra vared konid: ");
                scanf("%s", usern);

                printf("password ra vared konid: ");
                scanf("%s", pass);

                FILE *loginFile = fopen("login_student.txt", "r");
                if (loginFile == NULL)
                {
                    printf("file vojood nadarad. dar hale sakht file...\n");
                    FILE *fileMaker = fopen("login_student.txt", "w");
                    fclose(fileMaker);

                    printf("file eijad shod!\n");
                }
                else
                {
                    char username[50], password[50];
                    while (fscanf(loginFile, "%s\n%s", username, password) != EOF)
                    {
                        if (strcmp(usern, username) == 0 && strcmp(pass, password) == 0)
                        {
                            printf("karbar (%s) | shoma ba movafaghiat vared shodid!\n", usern);
                            strcpy(page, "menu");
                            break;
                        }
                    }
                    if (strcmp(page, "logIn") == 0)
                    {
                        printf("karbar dar samane vojoood nadarad!\n");
                    }
                }
            }
            else if (strcmp(type, "0") == 0)
            {
                printf("mamnoonim ke az barname estefade kardid, rooze khoobi dashte bashid!\n");
                running = 0;
            }
            else
            {
                printf("entekhab na motabar! dobare emtehan konid.\n");
            }
        }
        else if (strcmp(page, "menu") == 0)
        {
            printf("\n\n\n\n\n");
            printf("==================================== menu ====================================\n");
            if (strcmp(type, "1") == 0)
            {
                printf("ketabdar aziz, (%s) entekhab konid:\n", usern);
                printf("1. namayesh list aaza, eijade taghir dar aaza va namayesh tarikhche daryaft ketab\n");
                printf("2. namayesh list ketab ha\n");
                printf("3. namayesh list ketab haye darkhasti\n");
                printf("4. ezafe kardan ketab\n");
                printf("5. hazf ketab\n");
                printf("6. namayesh sabeghe ketabha\n");
                printf("7. edit ketab");
                printf("baraye log-out shodan, \"-1\" ra vared konid.\n");
                printf("baraye khorooj az barname, \"0\" ra vared konid.\n");

                int choice;
                scanf("%d", &choice);

                if (choice == 1)
                {
                    strcpy(page, "modifyUsers");
                }
                else if (choice == 2)
                {
                    neshandadaanketab(books);
                }
                else if (choice == 3)
                {
                    neshandadarequest(requests);
                }
                else if (choice == 4)
                {
                    int serial, mojodbodan;
                    char esm[100], nevisande[100], reshte[50];
                    printf("esm ketab: \n");
                    scanf("%s", esm);
                    printf("nevisande: \n");
                    scanf("%s", nevisande);
                    printf("reshte: \n");
                    scanf("%s", reshte);
                    printf("serial: \n");
                    scanf("%d", &serial);
                    printf("mojoodi: \n");
                    scanf("%d", &mojodbodan);
                    ezafekardanketab(&books, serial, esm, nevisande, reshte, mojodbodan);
                    savekardanketab(books, "books.txt");
                }
                else if (choice == 5)
                {
                    int serial;
                    printf("shomare serial ketab morede nazar ra vared konid: ");
                    scanf("%d", &serial);
                    hazfkardanketab(&books, serial);
                    savekardanketab(books, "books.txt");
                }

                else if (choice == 6)
                {
                    printf("tarikhche ketabha: \n");

                    FILE *book = fopen("books.txt", "r");

                    int serial, amount, s;
                    char name[100], nevisande[50], resht[50];
                    char fard[50];

                    while (fscanf(book, "%d %s %s %s %d", &serial, name, nevisande, resht, &amount) != EOF)
                    {
                        FILE *tarikh = fopen("tarikhche.txt", "r");
                        printf("name ketab: %s\n", name);

                        int i = 0;
                        while (fscanf(tarikh, "%s %d", fard, &s) != EOF)
                        {
                            if (s == serial)
                            {
                                i++;
                                printf("%d. %s\n", i, fard);
                            }
                        }

                        printf("------------------------------\n");
                        fclose(tarikh);
                    }
                    fclose(book);
                }
                else if (choice == 7)
                {
                    int cho;
                    printf("1. serial, 2. esm ketab, 3. nevisande, 4. reshte, 5. tedad\n");
                    scanf("%d", &cho);
                    printf("serial: ");
                    int ser;
                    scanf("%d", &ser);
                    editketab(books, ser, cho);
                    savekardanketab(books, "books.txt");
                }
                else if (choice == 0)
                {
                    printf("mamnoonim ke az barname estefade kardid, rooze khoobi dashte bashid!\n");
                    running = 0;
                }
                else if (choice == -1)
                {
                    printf("ketabdar aziz (%s), shoma az system log-out shodid.\n", usern);
                    strcpy(page, "logIn");
                }
                else
                {
                    printf("entekhab na motabar! dobare emtehan konid.\n");
                }
            }
            else if (strcmp(type, "2") == 0)
            {
                FILE *student = fopen("login_student.txt", "r");
                FILE *reshte = fopen("reshte.txt", "r");

                char username[50], password[50];
                int i = 0;
                while (fscanf(student, "%s\n%s", username, password) != EOF)
                {
                    i++;
                    if (strcmp(username, usern) == 0)
                    {
                        break;
                    }
                }
                char r[50];
                for (int j = 1; j <= i; j++)
                {
                    fscanf(reshte, "%s", r);
                }

                printf("daneshjoo aziz (%s), entekhab konid:\n", usern);
                printf("1. namayesh list ketabha\n");
                printf("2. darkhast ketab\n");
                printf("3. baragardandan ketab\n");
                printf("baraye log-out shodan, \"-1\" ra vared konid.\n");
                printf("baraye khorooj az barname, \"0\" ra vared konid.\n");

                int choice;
                scanf("%d", &choice);

                if (choice == 1)
                {
                    neshandadaanketabdaneshjoo(books, r);
                }
                else if (choice == 2)
                {
                    int serialnum;
                    char reshte[20], username[100];
                    printf("lotfan shomare serial ketab morednazar, reshte va username khod ra vared konid: \n");
                    scanf("%d", &serialnum);
                    scanf("%s", reshte);
                    scanf("%s", username);
                    darkhastketab(books, serialnum, reshte, username, requests);
                    loadkardanrequest(&requests, "requests.txt");
                    savekardanrequest(requests, "requests.txt");
                }
                else if (choice == 3)
                {
                    int serial;
                    printf("lotfan shomare serial ketab morednazar ra baraye bargardan vared konid: ");
                    scanf("%d", &serial);

                    bargardondanketab(books, serial);
                    savekardanketab(books, "books.txt");
                }
                else if (choice == 0)
                {
                    printf("mamnoonim ke az barname estefade kardid, rooze khoobi dashte bashid!\n");
                    running = 0;
                }
                else if (choice == -1)
                {
                    printf("ketabdar aziz (%s), shoma az system log-out shodid.\n", usern);
                    strcpy(page, "logIn");
                }
                else
                {
                    printf("entekhab na motabar! dobare emtehan konid.\n");
                }
            }
        }

        else if (strcmp(page, "modifyUsers") == 0)
        {
            printf("\n\n\n\n");
            printf("==================================== list aaza ====================================\n");
            FILE *studentFile = fopen("login_student.txt", "r");
            User karbar;

            while (fscanf(studentFile, "%s\n%s", karbar.username, karbar.password) != EOF)
            {
                printf("username: %s\npassword: %s\nactions| promote, delete\n\n", karbar.username, karbar.password);
            }
            fclose(studentFile);

            printf("action ra entekhab konid, type konid: \"<action> <username>\"\n");
            printf("ya agar mikhahid user ezafe konid, type konid: \"add\"\n");
            printf("agar mikhahid be menu asli bargardid, type konid: \"menu\"\n");
            char un[50];
            char action[50];
            scanf("%s", action);
            if (strcmp(action, "menu") == 0)
            {
                strcpy(page, "menu");
            }
            else if (strcmp(action, "add") == 0)
            {
                char username[50], password[50], Reshte[50];
                printf("username ra vared konid: ");
                scanf("%s", username);

                char ans[20];
                printf("Aya mikhahid az random password barname estefade konid? (bale / kheir): "); // Emtiazi!
                scanf("%s", ans);
                while (strcmp(ans, "bale") != 0 && strcmp(ans, "kheir") != 0)
                {
                    printf("entekhab na motabar! dobare entekhab konid: ");
                    scanf("%s", ans);
                }
                if (strcmp(ans, "bale") == 0) // Emtiazi!
                {
                    randompassgen(password, 10);
                    printf("password shoma: %s\n", password);
                }
                else
                {
                    printf("password ra vared konid: ");
                    scanf("%s", password);
                }

                printf("reshte tahsili fard ra vared konid: ");
                scanf("%s", Reshte);

                FILE *studentFile = fopen("login_student.txt", "a");
                FILE *reshteFile = fopen("reshte.txt", "a");
                fprintf(studentFile, "%s\n%s\n", username, password);
                fprintf(reshteFile, "%s\n", Reshte);
                fclose(studentFile);
                fclose(reshteFile);
            }
            else
            {
                scanf("%s", un);

                if (strcmp(action, "delete") == 0)
                {
                    FILE *studentFile = fopen("login_student.txt", "r");
                    User users[1000];
                    User current;
                    int i = 0;
                    while (fscanf(studentFile, "%s\n%s", current.username, current.password) != EOF)
                    {
                        if (strcmp(current.username, un) != 0)
                        {
                            strcpy(users[i].username, current.username);
                            strcpy(users[i].password, current.password);
                            i++;
                        }
                    }
                    fclose(studentFile);
                    FILE *studentFile2 = fopen("login_student.txt", "w");
                    printf("%d", i);
                    for (int j = 0; j < i; j++)
                    {
                        fprintf(studentFile2, "%s\n%s\n", users[j].username, users[j].password);
                    }
                    fclose(studentFile2);

                    FILE *reshteFile = fopen("reshte.txt", "r");
                    char reshteha[1000][50];
                    char currentr[50];
                    int j = 0, k = 0;
                    while (fscanf(reshteFile, "%s", currentr) != EOF)
                    {
                        if (j != i)
                        {
                            strcpy(reshteha[j], currentr);
                            k++;
                        }
                        j++;
                    }
                    fclose(reshteFile);
                    FILE *reshteFile2 = fopen("reshte.txt", "w");
                    printf("%d", i);
                    for (int h = 0; h < k; h++)
                    {
                        fprintf(studentFile2, "%s\n", reshteha[h]);
                    }
                    fclose(reshteFile2);
                }
                else if (strcmp(action, "promote") == 0)
                {
                    printf("Amaliate promote user be ketabdar aghaz shod...\n");
                    FILE *studentFile = fopen("login_student.txt", "r");
                    User users[1000];
                    User current;
                    User promote;
                    int i = 0;
                    while (fscanf(studentFile, "%s\n%s", current.username, current.password) != EOF)
                    {
                        if (strcmp(current.username, un) != 0)
                        {
                            strcpy(users[i].username, current.username);
                            strcpy(users[i].password, current.password);
                            i++;
                        }
                        else
                        {
                            strcpy(promote.username, current.username);
                            strcpy(promote.password, current.password);
                        }
                    }
                    fclose(studentFile);
                    FILE *studentFile2 = fopen("login_student.txt", "w");
                    for (int j = 0; j < i; j++)
                    {
                        fprintf(studentFile2, "%s\n%s\n", users[j].username, users[j].password);
                    }
                    fclose(studentFile2);
                    FILE *librarianFile = fopen("login_librarian.txt", "a");
                    fprintf(librarianFile, "%s\n%s\n", promote.username, promote.password);
                    printf("user be ketabdar promote shod!");
                    fclose(librarianFile);
                }
                else
                {
                    printf("entekhab na motabar! dobare emtehan konid.\n");
                }
            }
        }
    }

    savekardanketab(books, "books.txt");
    return 0;
}