
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int roll;
    char name[50];
    char course[30];
    float marks;
} Student;

void addStudent() {
    Student s;
    FILE *fp = fopen("students.dat", "ab");

    if (fp == NULL) {
        printf("File opening failed!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter Course: ");
    scanf(" %29[^\n]", s.course);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("\nStudent added successfully!\n");
}

void viewStudents() {
    Student s;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("\nRoll Number: %d\n", s.roll);
        printf("Name: %s\n", s.name);
        printf("Course: %s\n", s.course);
        printf("Marks: %.2f\n", s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    Student s;
    int roll, found = 0;

    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("\nStudent Found!\n");
            printf("Name: %s\n", s.name);
            printf("Course: %s\n", s.course);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                viewStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                printf("Thank you!\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
