#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_ID 20
#define MAX_RECORDS 200   // Maximum attendance entries per student

// Structure to store attendance entries
typedef struct {
    char date[15];
    char status[10];  // "Present" or "Absent"
} AttendanceRecord;

// Structure to store a student's whole information
typedef struct {
    char name[MAX_NAME];
    char id[MAX_ID];
    AttendanceRecord attendance[MAX_RECORDS];
    int attendanceCount;   // total records for this student
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// Function prototypes
void addStudent();
void markAttendance();
void viewAllStudents();
void viewStudentAttendance();
void clearScreen();
void pauseProgram();

int main() {
    int choice;

    do {
        clearScreen();

        printf("\n========== ATTENDANCE MANAGEMENT SYSTEM ==========\n");
        printf("1. Add New Student\n");
        printf("2. View All Students\n");
        printf("3. Mark Attendance\n");
        printf("4. View Student Attendance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // clear newline

        switch(choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: markAttendance(); break;
            case 4: viewStudentAttendance(); break;
            case 5: 
                printf("\nExiting program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Try again.\n");
                pauseProgram();
        }

    } while(choice != 5);

    return 0;
}

// Clears the screen (Windows only)
void clearScreen() {
    system("cls");
}

// Simple pause
void pauseProgram() {
    printf("\nPress Enter to continue...");
    getchar();
}

// Add a new student
void addStudent() {
    clearScreen();

    if (studentCount >= MAX_STUDENTS) {
        printf("ERROR: Maximum number of students reached!\n");
        pauseProgram();
        return;
    }

    Student newStudent;

    printf("\n====== ADD NEW STUDENT ======\n");

    printf("Enter Student Name: ");
    fgets(newStudent.name, MAX_NAME, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;

    printf("Enter Student ID: ");
    fgets(newStudent.id, MAX_ID, stdin);
    newStudent.id[strcspn(newStudent.id, "\n")] = 0;

    newStudent.attendanceCount = 0;  // initialize record count

    // Add to array
    students[studentCount++] = newStudent;

    printf("\nStudent added successfully!\n");
    pauseProgram();
}

// View all students
void viewAllStudents() {
    clearScreen();

    printf("\n====== ALL STUDENTS ======\n\n");

    if (studentCount == 0) {
        printf("No students found.\n");
        pauseProgram();
        return;
    }

    int i;
    for (i = 0; i < studentCount; i++) {
        printf("%d. %s (ID: %s)\n", i + 1, students[i].name, students[i].id);
    }

    pauseProgram();
}

// Mark attendance
void markAttendance() {
    clearScreen();

    char id[MAX_ID];
    printf("\n====== MARK ATTENDANCE ======\n");

    if (studentCount == 0) {
        printf("No students available.\n");
        pauseProgram();
        return;
    }

    printf("Enter Student ID: ");
    fgets(id, MAX_ID, stdin);
    id[strcspn(id, "\n")] = 0;

    // Search student
    int found = -1;
    int i;
    for (i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nStudent not found.\n");
        pauseProgram();
        return;
    }

    Student *s = &students[found];
    AttendanceRecord newRecord;

    printf("Enter Date (YYYY-MM-DD): ");
    fgets(newRecord.date, 15, stdin);
    newRecord.date[strcspn(newRecord.date, "\n")] = 0;

    int statusChoice;
    printf("1. Present\n2. Absent\nEnter status: ");
    scanf("%d", &statusChoice);
    getchar();

    if (statusChoice == 1) {
        strcpy(newRecord.status, "Present");
    } else if (statusChoice == 2) {
        strcpy(newRecord.status, "Absent");
    } else {
        printf("Invalid choice!\n");
        pauseProgram();
        return;
    }

    s->attendance[s->attendanceCount++] = newRecord;

    printf("\nAttendance marked successfully!\n");
    if (s->attendanceCount >= MAX_RECORDS) return;
	pauseProgram();
}

// View attendance for a specific student
void viewStudentAttendance() {
    clearScreen();

    char id[MAX_ID];
    printf("\n====== STUDENT ATTENDANCE ======\n");

    if (studentCount == 0) {
        printf("No students available.\n");
        pauseProgram();
        return;
    }

    printf("Enter Student ID: ");
    fgets(id, MAX_ID, stdin);
    id[strcspn(id, "\n")] = 0;

    // Search student
    int found = -1;
    int i;
    for (i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nStudent not found.\n");
        pauseProgram();
        return;
    }

    Student *s = &students[found];

    printf("\nName: %s\nID: %s\n", s->name, s->id);
    printf("\n----- Attendance Records -----\n");

    if (s->attendanceCount == 0) {
        printf("No attendance marked yet.\n");
        pauseProgram();
        return;
    }

    for (i = 0; i < s->attendanceCount; i++) {
        printf("%s : %s\n", s->attendance[i].date, s->attendance[i].status);
    }

    pauseProgram();
}

