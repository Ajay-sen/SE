#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Student
{
    int rollno;
    char name[50];
    int marks1;
    int marks2;
    int marks3;
    int marks4;
    int marks5;
    int totalmarks;
} st;
FILE *fp;
int num = 0;
void add_student()
{
    fp = fopen("student.txt", "ab");
    printf("Enter name: ");
    scanf("%s", &st.name);
    getchar();
    printf("Enter rollno: ");
    scanf("%d", &st.rollno);
    getchar();
    int sum = 0;
    int i = 0;
    printf("Enter marks of Maths-IV: ");
    scanf("%d", &st.marks1);
    printf("Enter marks of Computer Networks: ");
    scanf("%d", &st.marks2);
    printf("Enter marks of Graph Theory: ");
    scanf("%d", &st.marks3);
    printf("Enter marks of OOS: ");
    scanf("%d", &st.marks4);
    printf("Enter marks of Software Engineering: ");
    scanf("%d", &st.marks5);
    st.totalmarks = st.marks1 + st.marks2 + st.marks3 + st.marks4 + st.marks5;
    printf("Student added successfully...\n");
    num++;
    fwrite(&st, sizeof(st), 1, fp);
    fclose(fp);
}
void update_marks()
{
    int roll_no, f;
    printf("\n-----Update marks-----\n");
    printf("Enter rollno to update: ");
    scanf("%d", &roll_no);
    fp = fopen("student.txt", "rb+");
    while (fread(&st, sizeof(st), 1, fp) == 1)
    {
        if (roll_no == st.rollno)
        {
            f = 1;
            printf("enter the new set of marks\n");
            int i = 0;
            st.totalmarks = 0;
            printf("Enter marks of Maths-IV: ");
            scanf("%d", &st.marks1);
            printf("Enter marks of Computer Networks: ");
            scanf("%d", &st.marks2);
            printf("Enter marks of Graph Theory: ");
            scanf("%d", &st.marks3);
            printf("Enter marks of OOS: ");
            scanf("%d", &st.marks4);
            printf("Enter marks of Software Engineering: ");
            scanf("%d", &st.marks5);
            st.totalmarks = st.marks1 + st.marks2 + st.marks3 + st.marks4 + st.marks5;
            fseek(fp, -sizeof(st), 1);
            fwrite(&st, sizeof(st), 1, fp);
            fclose(fp);
            break;
        }
    }
    if (f == 1)
    {
        printf("\nMarks updated successfully...\n");
    }
    else
    {
        printf("\nStudent not found...\n");
    }
}
void display()
{
    system("cls");
    printf("\n---Student details----\n");
    printf("%-10s %-30s %-20s %-20s %-20s %-20s %-20s %-20s\n", "Rollno", "Name", "DSA", "DBMS", "OOP", "OOS", "MATHS", "Total  Marks");
    fp = fopen("student.txt", "rb");
    while (fread(&st, sizeof(st), 1, fp) == 1)
    {
        printf("%-10d %-30s %-20d %-20d %-20d %-20d %-20d %-20d\n", st.rollno, st.name, st.marks1, st.marks2, st.marks3, st.marks4, st.marks5, st.totalmarks);
    }
    fclose(fp);
}
void teacher()
{
    int val;
    printf("\n1. Add student\n");
    printf("2. Update marks\n");
    printf("3. Display marks\n");
    printf("Enter choice: ");
    scanf("%d", &val);
    switch (val)
    {
    case 1:
        add_student();
        break;
    case 2:
        update_marks();
        break;
    case 3:
        display();
        break;
    default:
        printf("invalid input\n");
    }
}
void student()
{
    display();
}
int main()
{
    int val;
    while (1)
    {
        printf("\n1. Teacher\n");
        printf("2. Student\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &val);
        switch (val)
        {
        case 1:
            teacher();
            break;
        case 2:
            student();
            break;
        case 0:
            exit(0);
        default:
            printf("invalid input\n");
        }
    }
}
