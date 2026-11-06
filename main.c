#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int roll;
    char name[50];
    char course[30];
    float marks;
} Student;

// Add Student
void addStudent()
{
    Student s;
    FILE *fp = fopen("students.dat", "ab");

    if (fp == NULL)
    {
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

// View Students
void viewStudents()
{
    Student s;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("No student records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(Student), 1, fp) == 1)
    {
        printf("\nRoll Number: %d", s.roll);
        printf("\nName: %s", s.name);
        printf("\nCourse: %s", s.course);
        printf("\nMarks: %.2f\n", s.marks);
    }

    fclose(fp);
}

// Search Student
void searchStudent()
{
    Student s;
    int roll, found = 0;

    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1)
    {
        if (s.roll == roll)
        {
            printf("\nStudent Found!\n");
            printf("Roll Number: %d\n", s.roll);
            printf("Name: %s\n", s.name);
            printf("Course: %s\n", s.course);
            printf("Marks: %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent not found!\n");

    fclose(fp);
}

// Update Student
void updateStudent()
{
    Student s;
    int roll, found = 0;

    FILE *fp = fopen("students.dat", "rb+");

    if (fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1)
    {
        if (s.roll == roll)
        {
            printf("\nStudent Found!\n");

            printf("Enter New Name: ");
            scanf(" %49[^\n]", s.name);

            printf("Enter New Course: ");
            scanf(" %29[^\n]", s.course);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);

            found = 1;
            printf("\nStudent Updated Successfully!\n");
            break;
        }
    }

    if (!found)
        printf("\nStudent not found!\n");

    fclose(fp);
}

// Delete Student
void deleteStudent()
{
    Student s;
    int roll, found = 0;

    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL)
    {
        printf("No records found!\n");
        if (temp != NULL)
            fclose(temp);
        return;
    }

    if (temp == NULL)
    {
        printf("Temporary file creation failed!\n");
        fclose(fp);
        return;
    }

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1)
    {
        if (s.roll == roll)
        {
            found = 1;
            continue;
        }

        fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        if (remove("students.dat") != 0 ||
            rename("temp.dat", "students.dat") != 0)
        {
            printf("File replacement failed!\n");
            return;
        }

        printf("\nStudent Deleted Successfully!\n");
    }
    else
    {
        remove("temp.dat");
        printf("\nStudent not found!\n");
    }
}

// Main Function
int main()
{
    int choice;

    do
    {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("\nEnter Your Choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            return 1;
        }

        switch (choice)
        {
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
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid Choice! Try Again.\n");
        }

    } while (choice != 6);

    return 0;
}
