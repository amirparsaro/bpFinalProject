#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct book
{
    char esm[100];
    char nevisande[100];
    char reshte[50];
    int mojodbodan;
    struct book *next;
};

struct user
{
    char username[50];
    char password[50];
    char naghsh[10];
    char reshte[50];
};

int main()
{
    printf("be samane modiriate ketabkhane khosh amadid.\n");
    int running = 1;
    char page[50] = "logIn";
    char type[50];
    char user[50], pass[50];
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
                scanf("%s", user);

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
                        if (strcmp(user, username) == 0 && strcmp(pass, password) == 0)
                        {
                            printf("karbar (%s) | shoma ba movafaghiat vared shodid!\n", user);
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
                char user[50], pass[50];
                printf("username ra vared konid: ");
                scanf("%s", user);

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
                        if (strcmp(user, username) == 0 && strcmp(pass, password) == 0)
                        {
                            printf("karbar (%s) | shoma ba movafaghiat vared shodid!\n", user);
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
                return 0;
            }
            else
            {
                printf("entekhab na motabar! dobare emtehan konid.\n");
            }
        }

        else if (strcmp(page, "menu") == 0)
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n");
            printf("==================================== menu ====================================\n");
            if (strcmp(type, "1") == 0)
            {
                printf("ketabdar aziz, (%s) entekhab konid:\n", user);
                printf("1. namayesh list aaza, eijade taghir dar aaza va namayesh tarikhche daryaft ketab\n");
                printf("2. namayesh list ketab ha\n");
                printf("3. namayesh list ketab haye darkhasti\n");
                printf("4. \n");
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
                }
                else if (choice == 0)
                {
                    printf("mamnoonim ke az barname estefade kardid, rooze khoobi dashte bashid!\n");
                    return 0;
                }
                else if (choice == -1)
                {
                    printf("ketabdar aziz (%s), shoma az system log-out shodid.\n", user);
                    strcpy(page, "logIn");
                }
                else
                {
                    printf("entekhab na motabar! dobare emtehan konid.\n");
                }
            }
            else if (strcmp(type, "2") == 0)
            {
            }
        }

        else if (strcmp(page, "modifyUsers") == 0)
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n");
            printf("==================================== list aaza ====================================\n");
            FILE *studentFile = fopen("login_student.txt", "r");
            struct user karbar;

            while (fscanf(studentFile, "%s\n%s", karbar.username, karbar.password) != EOF)
            {
                printf("username: %s\npassword: %s\nactions| info, books, promote, delete\n\n", karbar.username, karbar.password);
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
                char username[50], password[50];
                printf("username ra vared konid: ");
                scanf("%s", username);

                printf("password ra vared konid: ");
                scanf("%s", password);

                FILE *studentFile = fopen("login_student.txt", "a");
                fprintf(studentFile, "%s\n%s\n", username, password);
                fclose(studentFile);
            }
            else
            {
                scanf("%s", un);
                if (strcmp(action, "info") == 0)
                {
                    printf("info\n");
                }
                else if (strcmp(action, "delete") == 0)
                {
                    FILE *studentFile = fopen("login_student.txt", "r");
                    struct user users[1000]; // change to linked list
                    struct user current;
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
                }
                else if (strcmp(action, "promote") == 0)
                {
                    printf("Amaliate promote user be ketabdar aghaz shod...\n");
                    FILE *studentFile = fopen("login_student.txt", "r");
                    struct user users[1000]; // change to linked list
                    struct user current;
                    struct user promote;
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
}