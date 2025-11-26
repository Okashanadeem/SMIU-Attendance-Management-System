# Developer Documentation

This document provides a technical overview of the Student Attendance Management System, covering the C language concepts used, the system's architecture, data storage model, and answers to frequently asked questions.

---

## C Language Concepts Used

This project is a straightforward, single-file C application that relies on fundamental language features.

*   **Preprocessor Directives**:
    *   `#include`: Used to import standard C libraries:
        *   `stdio.h`: For standard input/output functions (`printf`, `scanf`, `fgets`, `getchar`).
        *   `string.h`: For string manipulation functions (`strcpy`, `strcmp`, `strlen`, `strcspn`).
        *   `stdlib.h`: For general utility functions, including `system("cls")`.
        *   `time.h`: For retrieving the current system date and time.
    *   `#define`: Creates compile-time constants for setting fixed limits, such as `MAX_STUDENTS` and `MAX_NAME`. This makes the code easier to configure and read.

*   **Data Structures (`struct`)**:
    *   `typedef struct`: Defines two custom data types: `AttendanceRecord` and `Student`. This groups related data into organized, reusable units.
    *   `Student`: Represents a student, containing their name, ID, program, and an array of `AttendanceRecord`s.
    *   `AttendanceRecord`: Represents a single attendance entry with a date and a status.

*   **Memory and Variables**:
    *   **Global Variables**: `Student students[MAX_STUDENTS]` and `int studentCount` are declared globally. This makes them accessible from any function, serving as the central in-memory database for the application.
    *   **Local Variables**: Variables declared inside functions are local and only exist within that function's scope.
    *   **Pointers**: Used to pass data efficiently. For example, `char *date` in `getCurrentDate` allows the function to modify the date string directly, and `Student *currentStudent` provides direct access to a student's record without copying it.

*   **Functions**:
    *   The program is modularized into functions, each with a specific purpose (e.g., `addStudent`, `markAttendance`).
    *   **Function Prototypes**: All functions are declared at the top of the file, which allows `main` and other functions to call them before their full definition appears.

*   **Control Flow**:
    *   `do-while`: The main program loop in `main` ensures the menu is displayed at least once and continues until the user chooses to exit.
    *   `switch-case`: Used in `main` to execute the correct function based on the user's menu choice.
    *   `for` and `if-else`: Used for iterating through arrays (e.g., searching for students, calculating statistics) and making logical decisions.

---

## System Architecture & Flow

The program follows a simple, continuous loop centered around a main menu.

1.  **Initialization**: The program starts, and the `main` function is called.
2.  **Main Loop**: A `do-while` loop begins, which will run until the user selects option `6` (Exit).
3.  **Display Menu**: `displayMenu()` clears the screen and prints the available options.
4.  **User Input**: The program waits for the user to enter a choice using `scanf`.
5.  **Function Execution**: A `switch` statement directs the program to the corresponding function based on the user's choice.
6.  **Task Execution**: The chosen function runs (e.g., `addStudent` prompts for user details and saves a new student). Most functions end with a `pause()` call, waiting for the user to press Enter before returning to the main menu.
7.  **Loop Continuation**: The loop repeats, displaying the menu again.
8.  **Exit**: If the user enters `6`, a thank you message is displayed, and the loop terminates, ending the program.

---

## Data Model & Storage

The system's data is stored **entirely in memory** and is **volatile**.

*   **Storage Mechanism**: A global array `Student students[MAX_STUDENTS];` acts as the database. It can hold up to 100 `Student` structs.
*   **Data Lifetime**: All data, including student profiles and attendance records, is **lost when the program closes**. There is no file persistence.
*   **How Data is Used**: Functions access and modify the `students` array directly or by finding a specific student's index using `findStudent()`. The global variable `studentCount` keeps track of the current number of students in the array.

---

## Function Reference

*   `main()`: The entry point. Contains the main menu loop and user choice handling.
*   `displayMenu()`: Clears the screen and shows the main menu options.
*   `clearScreen()`: Clears the console window (Windows-specific).
*   `pause()`: Waits for the user to press Enter.
*   `getCurrentDate(char *date)`: Gets the current system date and formats it as `YYYY-MM-DD`.
*   `findStudent(char *id)`: Searches the global `students` array for a matching ID and returns the student's index or `-1` if not found.
*   `addStudent()`: Prompts for new student details, checks for ID uniqueness, and adds the student to the `students` array.
*   `viewAllStudents()`: Displays a formatted table of all registered students.
*   `markAttendance()`: Marks or updates a student's attendance for the current date.
*   `viewStudentDetails()`: Displays a student's full profile, attendance statistics, and history.
*   `generateReport()`: Calculates and displays the attendance percentage for every student and the class average.
*   `calculateAttendancePercentage(const Student *student)`: A helper function that computes the attendance percentage for a single student.

---

## Frequently Asked Questions (FAQ)

**Q: Is it possible to add an attendance record for tomorrow or a past date?**
**A:** No. The `markAttendance` function is hardcoded to use `getCurrentDate()`, so it can only mark or update attendance for the present day.

**Q: Is it possible to have attendance data for different dates?**
**A:** Yes. If you run the program on different days and mark attendance, each record is stored with the date on which it was created. The `viewStudentDetails` function will show a history of all records.

**Q: Where is my data saved? What happens when I close the program?**
**A:** All data is stored in memory (a global array). It is not saved to any file. When you close the program, all student and attendance information is permanently lost.

**Q: Can I run this program on Linux or macOS?**
**A:** Not without modification. The `system("cls")` command is specific to Windows. To make it cross-platform, you would need to replace it with a command like `system("clear")` for Linux/macOS, typically using conditional compilation (`#ifdef`).

**Q: What are the limits of the system?**
**A:** The system has hardcoded limits defined by constants: 100 students (`MAX_STUDENTS`) and 365 attendance records per student (`MAX_ATTENDANCE`).

**Q: What happens if I enter text when the menu asks for a number?**
**A:** The program will likely enter an infinite loop or behave unexpectedly. The `scanf("%d", ...)` function is not robust against invalid input types. This is a known limitation of the current implementation.

**Q: How is the attendance percentage calculated?**
**A:** The percentage is calculated as `( (Present + Late) / Total_Classes ) * 100`. Absences are not counted as attended days.
