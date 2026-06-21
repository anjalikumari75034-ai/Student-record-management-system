/*
    ===================================================
    STUDENT RECORD MANAGEMENT SYSTEM
    ===================================================
    Features:
    1. Add Student
    2. Display Students
    3. Search Student
    4. Update Student
    5. Delete Student
    6. Find Topper
    7. Generate Report
    8. Exit
    Data is automatically saved to and loaded from "students.dat"
    ===================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100              // maximum number of students we can store
#define FILENAME "students.dat"
int main()
{

// ---------- Structure to hold one student's data ----------
struct Student {
    int roll;
    char name[50];
    char course[30];
    float marks;
    char grade;              // calculated automatically, not entered by user
};

struct Student students[MAX];   // array that holds all student records in memory
int totalStudents = 0;          // how many students are currently stored

// ---------- Function Prototypes (declared early so order of writing doesn't matter) ----------
void loadFromFile();
void saveToFile();
char calculateGrade(float marks);
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void findTopper();
void generateReport();
int findIndexByRoll(int roll);


// =====================================================
// MAIN FUNCTION - shows menu and calls other functions
// =====================================================
int main() {
    int choice;

    loadFromFile();   // load old data automatically when program starts

    do {
        printf("\n========= STUDENT RECORD MANAGEMENT SYSTEM =========\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Find Topper\n");
        printf("7. Generate Report\n");
        printf("8. Exit\n");
        printf("======================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: findTopper(); break;
            case 7: generateReport(); break;
            case 8:
                saveToFile();   // save before exiting, just to be safe
                printf("Data saved. Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 8.\n");
        }

    } while (choice != 8);

    return 0;
}


// =====================================================
// Calculates grade automatically based on marks
// 90-100 -> A, 80-89 -> B, 70-79 -> C, 60-69 -> D, below 60 -> F
// =====================================================
char calculateGrade(float marks) {
    if (marks >= 90)
        return 'A';
    else if (marks >= 80)
        return 'B';
    else if (marks >= 70)
        return 'C';
    else if (marks >= 60)
        return 'D';
    else
        return 'F';
}


// =====================================================
// Finds the array index of a student using roll number
// Returns -1 if not found
// =====================================================
int findIndexByRoll(int roll) {
    for (int i = 0; i < totalStudents; i++) {
        if (students[i].roll == roll) {
            return i;
        }
    }
    return -1;   // not found
}


// =====================================================
// 1. ADD STUDENT
// =====================================================
void addStudent() {
    if (totalStudents >= MAX) {
        printf("Storage full! Cannot add more students.\n");
        return;
    }

    struct Student s;

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    // check if roll number already exists (roll number should be unique)
    if (findIndexByRoll(s.roll) != -1) {
        printf("A student with this Roll Number already exists!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);     // %[^\n] reads full name including spaces

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Marks (0-100): ");
    scanf("%f", &s.marks);

    s.grade = calculateGrade(s.marks);   // grade calculated automatically

    students[totalStudents] = s;   // store the new student in the array
    totalStudents++;

    saveToFile();   // save updated data to file immediately

    printf("Student added successfully! Grade assigned: %c\n", s.grade);
}


// =====================================================
// 2. DISPLAY STUDENTS
// =====================================================
void displayStudents() {
    if (totalStudents == 0) {
        printf("No student records found.\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-10s %-5s\n", "Roll", "Name", "Course", "Marks", "Grade");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < totalStudents; i++) {
        printf("%-10d %-20s %-15s %-10.2f %-5c\n",
               students[i].roll,
               students[i].name,
               students[i].course,
               students[i].marks,
               students[i].grade);
    }
}


// =====================================================
// 3. SEARCH STUDENT (by roll number)
// =====================================================
void searchStudent() {
    int roll;
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    int index = findIndexByRoll(roll);

    if (index == -1) {
        printf("Student with Roll Number %d not found.\n", roll);
    } else {
        printf("\nStudent Found:\n");
        printf("Roll No : %d\n", students[index].roll);
        printf("Name    : %s\n", students[index].name);
        printf("Course  : %s\n", students[index].course);
        printf("Marks   : %.2f\n", students[index].marks);
        printf("Grade   : %c\n", students[index].grade);
    }
}


// =====================================================
// 4. UPDATE STUDENT
// =====================================================
void updateStudent() {
    int roll;
    printf("Enter Roll Number of student to update: ");
    scanf("%d", &roll);

    int index = findIndexByRoll(roll);

    if (index == -1) {
        printf("Student with Roll Number %d not found.\n", roll);
        return;
    }

    printf("Enter new Name: ");
    scanf(" %[^\n]", students[index].name);

    printf("Enter new Course: ");
    scanf(" %[^\n]", students[index].course);

    printf("Enter new Marks (0-100): ");
    scanf("%f", &students[index].marks);

    // grade recalculated automatically after updating marks
    students[index].grade = calculateGrade(students[index].marks);

    saveToFile();   // save changes to file

    printf("Student record updated successfully! New Grade: %c\n", students[index].grade);
}


// =====================================================
// 5. DELETE STUDENT
// =====================================================
void deleteStudent() {
    int roll;
    printf("Enter Roll Number of student to delete: ");
    scanf("%d", &roll);

    int index = findIndexByRoll(roll);

    if (index == -1) {
        printf("Student with Roll Number %d not found.\n", roll);
        return;
    }

    // shift all students after this index one place to the left
    for (int i = index; i < totalStudents - 1; i++) {
        students[i] = students[i + 1];
    }

    totalStudents--;   // one less student now

    saveToFile();   // save changes to file

    printf("Student record deleted successfully!\n");
}


// =====================================================
// 6. FIND TOPPER (student with highest marks)
// =====================================================
void findTopper() {
    if (totalStudents == 0) {
        printf("No student records found.\n");
        return;
    }

    int topperIndex = 0;

    for (int i = 1; i < totalStudents; i++) {
        if (students[i].marks > students[topperIndex].marks) {
            topperIndex = i;
        }
    }

    printf("\n----- TOPPER OF THE CLASS -----\n");
    printf("Roll No : %d\n", students[topperIndex].roll);
    printf("Name    : %s\n", students[topperIndex].name);
    printf("Course  : %s\n", students[topperIndex].course);
    printf("Marks   : %.2f\n", students[topperIndex].marks);
    printf("Grade   : %c\n", students[topperIndex].grade);
}


// =====================================================
// 7. GENERATE REPORT
// Shows total students, average marks, topper, and grade-wise count
// =====================================================
void generateReport() {
    if (totalStudents == 0) {
        printf("No student records found to generate report.\n");
        return;
    }

    float totalMarks = 0;
    int countA = 0, countB = 0, countC = 0, countD = 0, countF = 0;
    int topperIndex = 0;

    for (int i = 0; i < totalStudents; i++) {
        totalMarks += students[i].marks;

        if (students[i].marks > students[topperIndex].marks) {
            topperIndex = i;
        }

        // count how many students got each grade
        switch (students[i].grade) {
            case 'A': countA++; break;
            case 'B': countB++; break;
            case 'C': countC++; break;
            case 'D': countD++; break;
            case 'F': countF++; break;
        }
    }

    float average = totalMarks / totalStudents;

    printf("\n================ CLASS REPORT ================\n");
    printf("Total Students   : %d\n", totalStudents);
    printf("Average Marks    : %.2f\n", average);
    printf("Topper           : %s (Roll No %d, Marks %.2f)\n",
           students[topperIndex].name, students[topperIndex].roll, students[topperIndex].marks);
    printf("------------------------------------------------\n");
    printf("Grade A Students : %d\n", countA);
    printf("Grade B Students : %d\n", countB);
    printf("Grade C Students : %d\n", countC);
    printf("Grade D Students : %d\n", countD);
    printf("Grade F Students : %d\n", countF);
    printf("================================================\n");
}


// =====================================================
// Saves all student records into students.dat (binary file)
// =====================================================
void saveToFile() {
    FILE *fp = fopen(FILENAME, "wb");   // "wb" = write in binary mode

    if (fp == NULL) {
        printf("Error: Could not open file for saving!\n");
        return;
    }

    fwrite(&totalStudents, sizeof(int), 1, fp);            // first save how many students
    fwrite(students, sizeof(struct Student), totalStudents, fp);  // then save all records

    fclose(fp);
}


// =====================================================
// Loads student records from students.dat automatically
// Called once when the program starts
// =====================================================
void loadFromFile() {
    FILE *fp = fopen(FILENAME, "rb");   // "rb" = read in binary mode

    if (fp == NULL) {
        // file doesn't exist yet (first time running program) - that's okay
        totalStudents = 0;
        return;
    }

    fread(&totalStudents, sizeof(int), 1, fp);
    fread(students, sizeof(struct Student), totalStudents, fp);

    fclose(fp);

    printf("Loaded %d student record(s) from file.\n", totalStudents);
}
}