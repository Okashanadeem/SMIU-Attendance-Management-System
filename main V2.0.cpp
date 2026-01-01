#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_ID 20
#define MAX_RECORDS 200   
#define FILENAME "attendance_data.csv" // The file Excel will open

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
    int attendanceCount;   
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
void saveData();
void loadData();
int findStudentIndex(char *id);

int main() {
    int choice;

    // Load data automatically when program starts
    loadData();

    do {
        clearScreen();

        printf("\n==========Attendance  MANAGEMENT SYSTEM ==========\n");
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
                saveData(); // Save before exiting
                printf("\nData saved to '%s'. Exiting program. Goodbye!\n", FILENAME);
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

// Helper: Find student index by ID
int findStudentIndex(char *id) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// === FILE OPERATIONS ===

// Save data to CSV (Excel compatible)
void saveData() {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("Error: Could not save data!\n");
        return;
    }

    // Write CSV Header
    fprintf(fp, "ID,Name,Date,Status\n");

    for (int i = 0; i < studentCount; i++) {
        // If student has no attendance, save just their info
        if (students[i].attendanceCount == 0) {
            fprintf(fp, "%s,%s,None,None\n", students[i].id, students[i].name);
        } else {
            // If student has attendance, save a row for every record
            for (int j = 0; j < students[i].attendanceCount; j++) {
                fprintf(fp, "%s,%s,%s,%s\n", 
                    students[i].id, 
                    students[i].name, 
                    students[i].attendance[i].date, 
                    students[i].attendance[j].date, 
                    students[i].attendance[j].status);
            }
        }
    }

    fclose(fp);
}

// Load data from CSV
void loadData() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        // File doesn't exist yet (first run), just return
        return;
    }

    char line[256];
    // Skip the header line
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        char *id = strtok(line, ",");
        char *name = strtok(NULL, ",");
        char *date = strtok(NULL, ",");
        char *status = strtok(NULL, ",");

        if (id && name && date && status) {
            // Check if student already exists in our RAM array
            int index = findStudentIndex(id);

            if (index == -1) {
                // New student found in file, add to array
                if (studentCount < MAX_STUDENTS) {
                    strcpy(students[studentCount].id, id);
                    strcpy(students[studentCount].name, name);
                    students[studentCount].attendanceCount = 0;
                    index = studentCount;
                    studentCount++;
                }
            }

            // If the record is not "None", add the attendance
            if (strcmp(date, "None") != 0 && index != -1) {
                int ac = students[index].attendanceCount;
                if (ac < MAX_RECORDS) {
                    strcpy(students[index].attendance[ac].date, date);
                    strcpy(students[index].attendance[ac].status, status);
                    students[index].attendanceCount++;
                }
            }
        }
    }

    fclose(fp);
}

// === END FILE OPERATIONS ===

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

    // Check if ID already exists
    if (findStudentIndex(newStudent.id) != -1) {
        printf("Error: Student ID already exists!\n");
        pauseProgram();
        return;
    }

    newStudent.attendanceCount = 0;  // initialize record count

    // Add to array
    students[studentCount++] = newStudent;

    saveData(); // Auto-save
    printf("\nStudent added and saved successfully!\n");
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

    int found = findStudentIndex(id);

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

    saveData(); // Auto-save
    printf("\nAttendance marked and saved successfully!\n");
    
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

    int found = findStudentIndex(id);

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

    for (int i = 0; i < s->attendanceCount; i++) {
        printf("%s : %s\n", s->attendance[i].date, s->attendance[i].status);
    }

    pauseProgram();
}
