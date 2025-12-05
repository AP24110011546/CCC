#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUD_FILE "students.txt"
#define CRE_FILE "credentials.txt"

char currentUser[50];
char currentRole[20];

void printLine()
{
    printf("=====================================\n");
}

void heading(const char *title)
{
    printLine();
    printf("             %s\n", title);
    printLine();
}

int login()
{
    char u[50], p[50], r[20];
    char inUser[50], inPass[50];

LOGIN:
    heading("LOGIN");

    printf("USERNAME : ");
    scanf("%s", inUser);

    printf("PASSWORD : ");
    scanf("%s", inPass);

    FILE *fp = fopen(CRE_FILE, "r");
    if (!fp)
    {
        printf("Credentials file missing!\n");
        return 0;
    }

    while (fscanf(fp, "%49s %49s %19s", u, p, r) == 3)
    {
        if (strcmp(u, inUser) == 0 && strcmp(p, inPass) == 0)
        {
            strcpy(currentUser, u);
            strcpy(currentRole, r);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    printf("\nInvalid username or password! Try again.\n\n");
    goto LOGIN;
}

void addStudent()
{
    int roll;
    char name[50];
    float mark;

    printf("Roll : ");
    scanf("%d", &roll);

    printf("Name : ");
    scanf(" %[^\n]", name);

    printf("Marks : ");
    scanf("%f", &mark);

    FILE *fp = fopen(STUD_FILE, "a");
    if (!fp)
    {
        printf("Error opening student file!\n");
        return;
    }

    fprintf(fp, "%d|%s|%.2f\n", roll, name, mark);
    fclose(fp);

    printf("Student added successfully!\n");
}

void displayStudents()
{
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp)
    {
        printf("No records found!\n");
        return;
    }

    int roll;
    char name[50];
    float mark;
    char line[200]; // buffer to read each line

    printf("\nROLL\tNAME\t\tMARKS\n");
    printf("------------------------------------------\n");

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Expecting format: roll|name|mark
        if (sscanf(line, "%d|%49[^|]|%f", &roll, name, &mark) == 3)
        {
            printf("%04d\t%-20s %.2f\n", roll, name, mark);
        }
        // If the line is badly formatted, we just skip it
    }

    fclose(fp);
}

void searchStudent()
{
    int target;
    printf("Enter roll to search: ");
    scanf("%d", &target);

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp)
    {
        printf("No records!\n");
        return;
    }

    int roll;
    char name[50];
    float mark;

    while (fscanf(fp, "%d|%49[^|]|%f\n", &roll, name, &mark) == 3)
    {
        if (roll == target)
        {
            printf("\nFOUND: %d  %s  %.2f\n", roll, name, mark);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("Student not found!\n");
}

void deleteStudent()
{
    int target;
    printf("Enter roll to delete: ");
    scanf("%d", &target);

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp)
    {
        printf("No records found!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");

    int roll;
    char name[50];
    float mark;
    int found = 0;

    while (fscanf(fp, "%d|%49[^|]|%f\n", &roll, name, &mark) == 3)
    {
        if (roll != target)
            fprintf(temp, "%d|%s|%.2f\n", roll, name, mark);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found)
        printf("Student deleted!\n");
    else
        printf("Roll not found!\n");
}

void updateStudent()
{
    int target;
    printf("Enter roll to update: ");
    scanf("%d", &target);

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp)
    {
        printf("No records found!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");

    int roll;
    char name[50];
    float mark;
    int found = 0;

    while (fscanf(fp, "%d|%49[^|]|%f\n", &roll, name, &mark) == 3)
    {
        if (roll == target)
        {
            found = 1;
            char newName[50];
            float newMark;

            printf("New Name : ");
            scanf(" %[^\n]", newName);

            printf("New Marks : ");
            scanf("%f", &newMark);

            fprintf(temp, "%d|%s|%.2f\n", roll, newName, newMark);
        }
        else
        {
            fprintf(temp, "%d|%s|%.2f\n", roll, name, mark);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found)
        printf("Student updated!\n");
    else
        printf("Roll not found!\n");
}

void adminMenu()
{
    int c;

    while (1)
    {
        heading("ADMIN MENU");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");

        printf("\nEnter choice: ");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            return;
        default:
            printf("Invalid choice!\n");
        }
    }
}

void staffMenu()
{
    int c;

    while (1)
    {
        heading("STAFF MENU");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Logout\n");

        printf("\nEnter choice: ");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            return;
        default:
            printf("Invalid!\n");
        }
    }
}

void guestMenu()
{
    int c;

    while (1)
    {
        heading("GUEST MENU");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");

        printf("\nEnter choice: ");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            displayStudents();
            break;
        case 2:
            searchStudent();
            break;
        case 3:
            return;
        default:
            printf("Invalid!\n");
        }
    }
}

void userMenu()
{
    int c;

    while (1)
    {
        heading("USER MENU");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");

        printf("\nEnter choice: ");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            displayStudents();
            break;
        case 2:
            searchStudent();
            break;
        case 3:
            return;
        default:
            printf("Invalid!\n");
        }
    }
}

int main()
{
    if (!login())
        return 0;

    printf("\nWelcome %s (%s)\n", currentUser, currentRole);

    if (strcmp(currentRole, "admin") == 0)
        adminMenu();
    else if (strcmp(currentRole, "staff") == 0)
        staffMenu();
    else if (strcmp(currentRole, "user") == 0)
        userMenu();
    else
        guestMenu();

    printf("\nLogging out...\n");
    return 0;
}
