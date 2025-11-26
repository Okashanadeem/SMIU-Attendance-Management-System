/*
 * STUDENT ATTENDANCE MANAGEMENT SYSTEM
 * A console-based application for tracking student attendance records
 * Features: Add students, mark attendance, view details, generate reports
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Maximum capacity constants
#define MAX_STUDENTS 100      // Maximum number of students in the system
#define MAX_ATTENDANCE 365    // Maximum attendance records per student (1 year)
#define MAX_NAME 100          // Maximum length for student name
#define MAX_ID 30             // Maximum length for student ID
#define MAX_PROGRAM 50        // Maximum length for program name
#define MAX_DATE 15           // Maximum length for date string (YYYY-MM-DD)

/*
 * AttendanceRecord Structure
 * Stores a single attendance entry with date and status
 */
typedef struct {
    char date[MAX_DATE];      // Date in YYYY-MM-DD format
    char status[10];          // Status: "Present", "Absent", or "Late"
} AttendanceRecord;

/*
 * Student Structure
 * Contains all information about a student including their attendance history
 */
typedef struct {
    char name[MAX_NAME];                        // Full name of student
    char id[MAX_ID];                            // Unique student ID
    char program[MAX_PROGRAM];                  // Academic program/major
    AttendanceRecord attendance[MAX_ATTENDANCE]; // Array of attendance records
    int attendanceCount;                        // Number of attendance records
} Student;

// Global variables - store all students in memory
Student students[MAX_STUDENTS];  // Array holding all student records
int studentCount = 0;            // Current number of students registered

// Function declarations (prototypes)
void clearScreen();              // Clears the console screen
void pause();                    // Pauses execution until user presses Enter
void getCurrentDate(char *date); // Gets current system date
void addStudent();               // Adds a new student to the system
void viewAllStudents();          // Displays list of all students
void markAttendance();           // Records attendance for a student
void viewStudentDetails();       // Shows detailed info and history for a student
void generateReport();           // Generates attendance report for all students
int findStudent(char *id);       // Searches for a student by ID
float calculateAttendancePercentage(const Student *student); // Calculates a student's attendance percentage
void displayMenu();              // Shows the main menu

/*
 * Main Function
 * Entry point of the program - displays menu and handles user choices
 */
int main() {
    int choice;  // Stores user's menu selection
    
    // Main program loop - continues until user chooses to exit
    do {
        displayMenu();           // Show menu options
        scanf("%d", &choice);    // Read user's choice
        getchar();               // Consume leftover newline character
        
        // Execute function based on user's choice
        switch (choice) {
            case 1: addStudent(); break;          // Add new student
            case 2: viewAllStudents(); break;     // View all students
            case 3: markAttendance(); break;      // Mark attendance
            case 4: viewStudentDetails(); break;  // View student details
            case 5: generateReport(); break;      // Generate report
            case 6: 
                // Exit the program gracefully
                clearScreen();
                printf("\n  Thank you for using the Attendance System!\n\n");
                break;
            default:
                // Handle invalid menu choices
                printf("\n  Invalid choice! Try again.\n");
                pause();
        }
    } while (choice != 6);  // Continue until user selects exit option
    
    return 0;  // Program completed successfully
}

/*
 * displayMenu Function
 * Displays the main menu with all available options
 */
void displayMenu() {
    clearScreen();
    printf("\n");
    printf("  ================================================\n");
    printf("  |    STUDENT ATTENDANCE MANAGEMENT SYSTEM    |\n");
    printf("  ================================================\n");
    printf("\n");
    printf("  1. Add New Student\n");
    printf("  2. View All Students\n");
    printf("  3. Mark Attendance\n");
    printf("  4. View Student Details\n");
    printf("  5. Generate Report\n");
    printf("  6. Exit\n");
    printf("\n  Enter choice: ");
}

/*
 * clearScreen Function
 * Clears the console screen for better readability
 * Note: Uses "cls" command (Windows specific)
 */
void clearScreen() {
    system("cls");
}

/*
 * pause Function
 * Pauses program execution and waits for user to press Enter
 * Useful for viewing output before screen clears
 */
void pause() {
    printf("\n  Press Enter to continue...");
    getchar();  // Wait for Enter key
}

/*
 * getCurrentDate Function
 * Retrieves the current system date and formats it as YYYY-MM-DD
 * Parameters:
 *   date - pointer to character array where date will be stored
 */
void getCurrentDate(char *date) {
    time_t currentTime = time(NULL);                    // Get current time as timestamp
    struct tm *timeInfo = localtime(&currentTime);      // Convert to local time structure
    
    // Format date as YYYY-MM-DD
    sprintf(date, "%04d-%02d-%02d", 
            timeInfo->tm_year + 1900,         // tm_year is years since 1900
            timeInfo->tm_mon + 1,             // tm_mon is 0-11, so add 1
            timeInfo->tm_mday);               // Day of month
}

/*
 * findStudent Function
 * Searches for a student by their ID number
 * Parameters:
 *   id - student ID to search for
 * Returns:
 *   Index of student in array if found, -1 if not found
 */
int findStudent(char *id) {
    // Linear search through all students
    for (int index = 0; index < studentCount; index++) {
        if (strcmp(students[index].id, id) == 0) {  // Compare IDs
            return index;  // Student found, return index
        }
    }
    return -1;  // Student not found
}

/*
 * calculateAttendancePercentage Function
 * Calculates the attendance percentage for a single student
 * Parameters:
 *   student - a constant pointer to the student's record
 * Returns:
 *   The calculated attendance percentage, or 0.0 if no records exist
 */
float calculateAttendancePercentage(const Student *student) {
    if (student->attendanceCount == 0) {
        return 0.0;
    }

    int attendedClasses = 0;
    for (int i = 0; i < student->attendanceCount; i++) {
        if (strcmp(student->attendance[i].status, "Present") == 0 || strcmp(student->attendance[i].status, "Late") == 0) {
            attendedClasses++;
        }
    }

    return ((float)attendedClasses / student->attendanceCount) * 100;
}

/*
 * addStudent Function
 * Adds a new student to the system with their basic information
 * Validates that student ID is unique and doesn't exceed maximum capacity
 */
void addStudent() {
    clearScreen();
    printf("\n  ========== ADD NEW STUDENT ==========\n");
    
    // Check if system has reached maximum capacity
    if (studentCount >= MAX_STUDENTS) {
        printf("\n  ERROR: Maximum students reached!\n");
        pause();
        return;
    }
    
    Student newStudent;  // Temporary student structure
    
    // Get student name
    printf("\n  Enter Student Name: ");
    fgets(newStudent.name, MAX_NAME, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;  // Remove newline
    
    // Get student ID
    printf("  Enter Student ID: ");
    fgets(newStudent.id, MAX_ID, stdin);
    newStudent.id[strcspn(newStudent.id, "\n")] = 0;  // Remove newline
    
    // Check if ID already exists (must be unique)
    if (findStudent(newStudent.id) != -1) {
        printf("\n  ERROR: Student ID already exists!\n");
        pause();
        return;
    }
    
    // Get program/major (optional field)
    printf("  Enter Program (optional): ");
    fgets(newStudent.program, MAX_PROGRAM, stdin);
    newStudent.program[strcspn(newStudent.program, "\n")] = 0;  // Remove newline
    
    // Initialize attendance count to 0 for new student
    newStudent.attendanceCount = 0;
    
    // Add student to array and increment counter
    students[studentCount++] = newStudent;
    
    printf("\n  SUCCESS: Student added!\n");
    pause();
}

/*
 * viewAllStudents Function
 * Displays a formatted list of all registered students
 * Shows ID, name, and program for each student
 */
void viewAllStudents() {
    clearScreen();
    printf("\n  ========== ALL STUDENTS ==========\n\n");
    
    // Check if any students are registered
    if (studentCount == 0) {
        printf("  No students registered.\n");
        pause();
        return;
    }
    
    // Print table header
    printf("  %-20s %-30s %-20s\n", "Student ID", "Name", "Program");
    printf("  %s\n", "--------------------------------------------------------------");
    
    // Print each student's information in table format
    for (int index = 0; index < studentCount; index++) {
        printf("  %-20s %-30s %-20s\n", 
               students[index].id, 
               students[index].name,
               strlen(students[index].program) > 0 ? students[index].program : "N/A");
    }
    
    pause();
}

/*
 * markAttendance Function
 * Records attendance status for a specific student on current date
 * Allows marking as Present, Absent, or Late
 * Updates existing record if attendance already marked for today
 */
void markAttendance() {
    clearScreen();
    printf("\n  ========== MARK ATTENDANCE ==========\n");
    
    // Check if any students exist
    if (studentCount == 0) {
        printf("\n  No students available.\n");
        pause();
        return;
    }
    
    // Get student ID
    char studentId[MAX_ID];
    printf("\n  Enter Student ID: ");
    fgets(studentId, MAX_ID, stdin);
    studentId[strcspn(studentId, "\n")] = 0;  // Remove newline
    
    // Find student in system
    int studentIndex = findStudent(studentId);
    if (studentIndex == -1) {
        printf("\n  ERROR: Student not found!\n");
        pause();
        return;
    }
    
    // Get pointer to student for easier access
    Student *currentStudent = &students[studentIndex];
    printf("\n  Student: %s\n", currentStudent->name);
    
    // Get and display current date
    char currentDate[MAX_DATE];
    getCurrentDate(currentDate);
    printf("  Date: %s\n", currentDate);
    
    // Display attendance status options
    printf("\n  Select Status:\n");
    printf("  1. Present\n");
    printf("  2. Absent\n");
    printf("  3. Late\n");
    printf("\n  Enter choice: ");
    
    int statusChoice;
    scanf("%d", &statusChoice);
    getchar();  // Consume newline
    
    // Determine status string based on choice
    char *attendanceStatus;
    switch (statusChoice) {
        case 1: attendanceStatus = "Present"; break;
        case 2: attendanceStatus = "Absent"; break;
        case 3: attendanceStatus = "Late"; break;
        default:
            printf("\n  Invalid choice!\n");
            pause();
            return;
    }
    
    // Check if attendance already marked for today
    int recordFound = 0;
    for (int recordIndex = 0; recordIndex < currentStudent->attendanceCount; recordIndex++) {
        if (strcmp(currentStudent->attendance[recordIndex].date, currentDate) == 0) {
            // Update existing record
            strcpy(currentStudent->attendance[recordIndex].status, attendanceStatus);
            recordFound = 1;
            break;
        }
    }
    
    // Add new attendance record if not marked today
    if (!recordFound && currentStudent->attendanceCount < MAX_ATTENDANCE) {
        strcpy(currentStudent->attendance[currentStudent->attendanceCount].date, currentDate);
        strcpy(currentStudent->attendance[currentStudent->attendanceCount].status, attendanceStatus);
        currentStudent->attendanceCount++;
    }
    
    printf("\n  SUCCESS: Attendance marked as %s!\n", attendanceStatus);
    pause();
}

/*
 * viewStudentDetails Function
 * Displays comprehensive information about a specific student
 * Includes personal info, attendance statistics, and complete history
 */
void viewStudentDetails() {
    clearScreen();
    printf("\n  ========== STUDENT DETAILS ==========\n");
    
    // Check if any students exist
    if (studentCount == 0) {
        printf("\n  No students available.\n");
        pause();
        return;
    }
    
    // Get student ID
    char studentId[MAX_ID];
    printf("\n  Enter Student ID: ");
    fgets(studentId, MAX_ID, stdin);
    studentId[strcspn(studentId, "\n")] = 0;  // Remove newline
    
    // Find student in system
    int studentIndex = findStudent(studentId);
    if (studentIndex == -1) {
        printf("\n  ERROR: Student not found!\n");
        pause();
        return;
    }
    
    Student *currentStudent = &students[studentIndex];
    
    // Display basic student information
    printf("\n  Name:       %s\n", currentStudent->name);
    printf("  Student ID: %s\n", currentStudent->id);
    printf("  Program:    %s\n", strlen(currentStudent->program) > 0 ? currentStudent->program : "N/A");
    
    // Check if student has any attendance records
    if (currentStudent->attendanceCount == 0) {
        printf("\n  No attendance records.\n");
        pause();
        return;
    }
    
    // Calculate attendance percentage
    float attendancePercentage = calculateAttendancePercentage(currentStudent);
    
    // Calculate statistics
    int presentCount = 0, absentCount = 0, lateCount = 0;
    for (int i = 0; i < currentStudent->attendanceCount; i++) {
        if (strcmp(currentStudent->attendance[i].status, "Present") == 0) {
            presentCount++;
        } else if (strcmp(currentStudent->attendance[i].status, "Absent") == 0) {
            absentCount++;
        } else if (strcmp(currentStudent->attendance[i].status, "Late") == 0) {
            lateCount++;
        }
    }

    // Display statistics
    printf("\n  ========== STATISTICS ==========\n");
    printf("  Total Classes: %d\n", currentStudent->attendanceCount);
    printf("  Present:       %d\n", presentCount);
    printf("  Late:          %d\n", lateCount);
    printf("  Absent:        %d\n", absentCount);
    printf("  Attendance:    %.2f%%\n", attendancePercentage);
    
    // Display complete attendance history
    printf("\n  ========== ATTENDANCE HISTORY ==========\n");
    printf("  %-15s %-10s\n", "Date", "Status");
    printf("  %s\n", "-------------------------");
    
    for (int recordIndex = 0; recordIndex < currentStudent->attendanceCount; recordIndex++) {
        printf("  %-15s %-10s\n", 
               currentStudent->attendance[recordIndex].date, 
               currentStudent->attendance[recordIndex].status);
    }
    
    pause();
}

/*
 * generateReport Function
 * Generates a class-wide attendance report
 * Shows attendance percentage for each student and overall class average
 */
void generateReport() {
    clearScreen();
    printf("\n  ========== CLASS REPORT ==========\n\n");
    
    // Check if any students exist
    if (studentCount == 0) {
        printf("  No students available.\n");
        pause();
        return;
    }
    
    // Print report header
    printf("  %-20s %-30s %-15s\n", "Student ID", "Name", "Attendance %");
    printf("  %s\n", "----------------------------------------------------------------");
    
    float totalAttendancePercentage = 0;  // Accumulator for calculating average
    
    // Process each student
    for (int studentIndex = 0; studentIndex < studentCount; studentIndex++) {
        Student *currentStudent = &students[studentIndex];
        float studentAttendancePercentage = calculateAttendancePercentage(currentStudent);
        
        totalAttendancePercentage += studentAttendancePercentage;  // Add to total for average calculation
        
        // Print student's attendance percentage
        printf("  %-20s %-30s %.2f%%\n", 
               currentStudent->id, 
               currentStudent->name, 
               studentAttendancePercentage);
    }
    
    // Calculate and display class average
    float classAverageAttendance = totalAttendancePercentage / studentCount;
    printf("\n  Average Class Attendance: %.2f%%\n", classAverageAttendance);
    pause();
}