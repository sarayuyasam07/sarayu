#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credential.txt"

struct student {
    int roll;
    char name[50];
    float marks;
};

char currentrole[10];
char currentuser[50];

void mainmenu();
void adminmenu();
void staffmenu();
void guestmenu();
void addstudent();
void displaystudents();
void searchstudent();
void updatestudent();
void deletestudent();
int loginsystem();

int main() {
    if (loginsystem()) {
        mainmenu();
    } else {
        printf("\nLogin failed. Exiting...\n");
    }
    return 0;
}

int loginsystem() {
    char username[20], password[20];
    char fileuser[20], filepass[20], filerole[20];

    printf("========= LOGIN SCREEN ======\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        printf("Error: credential.txt not found!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s", fileuser, filepass, filerole) == 3) {
        if (strcmp(username, fileuser) == 0 && strcmp(password, filepass) == 0) {
            strcpy(currentrole, filerole);
            strcpy(currentuser, fileuser);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void mainmenu() {
    if (strcmp(currentrole, "ADMIN") == 0)
        adminmenu();
    else if (strcmp(currentrole, "STAFF") == 0)
        staffmenu();
    else if (strcmp(currentrole, "GUEST") == 0)
        guestmenu();
    else
        printf("Invalid role!\n");
}

void adminmenu() {
    int choice;
    while (1) {
        printf("\n----- ADMIN MENU -----\n");
        printf("1. Add new student\n");
        printf("2. Display all records\n");
        printf("3. Search record\n");
        printf("4. Update student details\n");
        printf("5. Delete student record\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addstudent(); break;
            case 2: displaystudents(); break;
            case 3: searchstudent(); break;
            case 4: updatestudent(); break;
            case 5: deletestudent(); break;
            case 6: return;
            default: printf("Invalid choice!\n");
        }
    }
}

void staffmenu() {
    int choice;
    while (1) {
        printf("\n----- STAFF MENU -----\n");
        printf("1. Display all students\n");
        printf("2. Search student\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displaystudents(); break;
            case 2: searchstudent(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    }
}

void guestmenu() {
    int choice;
    while (1) {
        printf("\n----- GUEST MENU -----\n");
        printf("1. Display all students\n");
        printf("2. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displaystudents(); break;
            case 2: return;
            default: printf("Invalid choice!\n");
        }
    }
}

void addstudent() {
    struct student s;
    FILE *fp = fopen(STUDENT_FILE, "a");

    printf("Enter roll: ");
    scanf("%d", &s.roll);
    printf("Enter name: ");
    scanf("%s", s.name);
    printf("Enter marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("Student added successfully.\n");
}

void displaystudents() {
    struct student s;
    FILE *fp = fopen(STUDENT_FILE, "r");

    if (!fp) {
        printf("No records found.\n");
        return;
    }

    printf("\nROLL\tNAME\tMARKS\n");
    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        printf("%d\t%s\t%.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}

void searchstudent() {
    struct student s;
    int roll, found = 0;

    printf("Enter roll to search: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No records.\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll) {
            printf("\nRecord Found:\n");
            printf("Roll: %d\nName: %s\nMarks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Record not found.\n");

    fclose(fp);
}

void updatestudent() {
    struct student s;
    int roll, found = 0;

    printf("Enter roll to update: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {

        if (s.roll == roll) {
            printf("Enter new name: ");
            scanf("%s", s.name);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
            found = 1;
        }

        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Record updated.\n");
    else
        printf("Record not found.\n");
}

void deletestudent() {
    struct student s;
    int roll, found = 0;

    printf("Enter roll to delete: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll != roll)
            fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Record deleted.\n");
    else
        printf("Record not found.\n");
}