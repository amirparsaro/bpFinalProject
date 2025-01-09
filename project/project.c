#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct book
{
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
    char naghsh[10];
    char reshte[50];
    int islibrarian;
    struct user *next;
} user;

user *login(user *head, char username[], char password[])
{
    user *current = head;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0)
        {
            return current; // karbar peyda shod
        }
        current = current->next;
    }
    return NULL; // karbar peyde nashod
}

int main()
{
    user *users = NULL;
    int choice;
    int running = 1;
    int loggedIn = 0;
    while (running)
    {
        printf("be samane modiriate ketabkhane khosh amadid.\n");
        if (loggedIn == 0)
        {
            printf("brarye vorod \"1\" ra vared konid.\n");
            printf("baraye khoroj \"2\" ra vared konid.\n");
            scanf("%d", &choice);
            if (choice == 1)
            {
                char username[50], password[50];
                printf("username ra vared konid: ");
                scanf("%s\n", username);
                printf("password ra vared konid: ");
                scanf("%s", password);

                user *uservaredshode = login(users, username, password);
                if (uservaredshode)
                {
                    if (strcmp(uservaredshode->naghsh, "ketabdar") == 0)
                    {
                        int loginFile = fopen("login_librarian.txt", "r");
                        if (loginFile == NULL)
                        {
                            printf("file vojood nadarad. dar hale sakht file...\n");
                            int fileMaker = fopen("login_librarian.txt", "w");
                            fclose(fileMaker);

                            printf("file eijad shod!\n");
                        }
                        else
                        {
                            char username[50], password[50];
                            while (fscanf(loginFile, "%s\n%s", username, password) != EOF)
                            {
                                if (login(users, username, password))
                                {
                                    printf("karbar ba movafaghiat vared shod!\n");
                                    loggedIn = 1;
                                }
                                else
                                {
                                    printf("karbar dar samane vojoood nadarad!\n");
                                }
                            }
                        }
                    }
                    else
                    {
                        printf("username ya password ghalat ast");
                    }
                }
            }
            else if (choice == 2)
            {
                running = 0;
            }
            else
            {
                printf("dastoor eshtebah mibashad. Lotfan dobare talash konid\n");
            }
        }
    }
}