Got it. I’ve revised the README specifically for **Windows using Dev-C++ (built-in C compiler ≥ version 5)**, removed GCC/Linux instructions, removed the sample session, and replaced it with a concise program flow diagram. This will be a clean, professional, ready-to-use README for your project.

---

# Student Attendance Management System

A console-based C application to manage students and their attendance efficiently.
Designed for Windows, using Dev-C++ with the built-in C compiler (version ≥ 5).

---

## Table of Contents

* [Project Summary](#project-summary)
* [Features](#features)
* [Quick Start](#quick-start)

  * [Requirements](#requirements)
  * [Build & Run (Windows)](#build--run-windows)
* [Program Flow](#program-flow)
* [Data Model](#data-model)
* [Code Structure & Key Functions](#code-structure--key-functions)
* [Design Notes & Behavior](#design-notes--behavior)
* [Known Limitations & Edge Cases](#known-limitations--edge-cases)
* [Future Enhancements / Roadmap](#future-enhancements--roadmap)
* [Contribution & License](#contribution--license)

---

## Project Summary

This system provides instructors with a simple and efficient way to manage student attendance. It stores up to 100 students in memory and up to 365 daily attendance records per student. Each record has a **date** (`YYYY-MM-DD`) and **status** (`Present`, `Absent`, `Late`).

The program uses a text-based menu to:

* Add students
* Mark attendance
* View student details
* Generate class attendance reports

All operations are **in-memory** with no file persistence.

---

## Features

* Add student profiles (Name, unique ID, optional Program)
* Ensure unique Student IDs
* Mark or update attendance for the current date
* View a student's attendance history and statistics
* Generate a class-wide report (attendance % per student and class average)
* Lightweight and self-contained C implementation for Windows

---

## Quick Start

### Requirements

* **Windows OS**
* **Dev-C++ IDE** (built-in C compiler ≥ version 5)
* Terminal / console (Dev-C++ provides a console automatically)

### Build & Run (Windows)

1. Open Dev-C++
2. Create a **New Project → Console Application → C Project**
3. Copy the `main.c` code into the project
4. Compile (`F9`) and Run (`Ctrl+F10`)

> Dev-C++ will automatically compile using its built-in compiler.

---

## Program Flow

```
                                START
                                  │
                                  ▼
                        ╔════════════════════╗
                        ║  displayMenu()     ║
                        ║  (clear + prompt)  ║
                        ╚════════════════════╝
                                  │
                                  ▼
                         ┌──────────────────┐
                         │  Read choice (1) │
                         └──────────────────┘
                                  │
   ┌──────────────┬───────────────┼───────────────┬───────────────┐
   │              │               │               │               │
   ▼              ▼               ▼               ▼               ▼
[1] Add       [2] View All    [3] Mark     [4] View Student  [5] Generate
Student       Students        Attendance   Details           Report
   │              │               │               │               │
   ▼              │               │               │               │
Add Student     Print table      Mark flow      View details     Report flow
   │              │               │               │               │
   └──────────────┴───────────────┴───────────────┴───────────────┘
                                  │
                                  ▼
                                [6] Exit
                                  │
                                  ▼
                                STOP
```

This is the program loop until the user selects Exit.

---

### **Student Attendance Management System - Flow Diagram (Textual Layout)**

```
[Start]
   |
   v
[Display Menu]
   |
   |---> [1. Add New Student] ---> [Input Name, ID, Program] ---> [Check ID uniqueness] ---> [Add Student to Array] ---> [Success Message] ---> [Back to Menu]
   |
   |---> [2. View All Students] ---> [Check if Students Exist?] ---> [Display List Table] ---> [Back to Menu]
   |
   |---> [3. Mark Attendance] ---> [Input Student ID] ---> [Find Student?]
         |                                   |
         |                                   v
         |                           [Error: Student Not Found] ---> [Back to Menu]
         |
         v
   [Display Current Date] ---> [Select Attendance Status: Present/Absent/Late] ---> [Check if Today Already Marked?]
         |                                                           |
         |                                                           v
         |                                               [Update Existing Record]
         |
         v
   [Add New Record if Not Marked] ---> [Success Message] ---> [Back to Menu]
   |
   |---> [4. View Student Details] ---> [Input Student ID] ---> [Find Student?]
         |                                   |
         |                                   v
         |                           [Error: Student Not Found] ---> [Back to Menu]
         |
         v
   [Display Student Info & Attendance Stats] ---> [Display Attendance History] ---> [Back to Menu]
   |
   |---> [5. Generate Report] ---> [Check if Students Exist?] ---> [Calculate Individual Attendance %] ---> [Display Class Report] ---> [Back to Menu]
   |
   |---> [6. Exit] ---> [Clear Screen] ---> [Display Exit Message] ---> [End]
```

This flow covers all core functionalities: student management, attendance marking, and reporting.

---

## Data Model

**Structures**

```c
typedef struct {
    char date[15];    // YYYY-MM-DD
    char status[10];  // Present | Absent | Late
} AttendanceRecord;

typedef struct {
    char name[100];
    char id[30];
    char program[50];
    AttendanceRecord attendance[365];
    int attendanceCount;
} Student;
```

**Constants**

* `MAX_STUDENTS = 100`
* `MAX_ATTENDANCE = 365`
* Fixed-size character buffers for simplicity and safety

---

## Code Structure & Key Functions

* `displayMenu()` — displays main menu
* `clearScreen()` — clears console (`system("cls")`)
* `pause()` — wait for Enter key
* `getCurrentDate(char *date)` — retrieves system date (`YYYY-MM-DD`)
* `findStudent(char *id)` — linear search, returns index or -1
* `addStudent()` — add new student after uniqueness check
* `viewAllStudents()` — prints all students in a formatted table
* `markAttendance()` — mark or update attendance for today
* `viewStudentDetails()` — print student stats and complete history
* `generateReport()` — show per-student attendance % and class average

---

## Design Notes & Behavior

* **Attendance % calculation**: `(Present + Late) / Total Classes × 100`
* **Today's attendance**: updated if already marked
* **Student IDs**: unique key, must be manually assigned by instructor
* **All data**: stored in-memory only, lost when program closes

---

## Known Limitations & Edge Cases

* No persistent storage; all data is temporary
* Fixed limits: 100 students, 365 attendance entries per student
* `clearScreen()` works only on Windows (`cls`)
* Minimal input validation; `scanf` and `fgets` are used
* Single-threaded; no concurrent access support

---

## Future Enhancements / Roadmap

* Persistent storage using CSV or binary file
* Bulk class attendance marking
* Export reports to CSV or PDF
* Multi-course support
* GUI or web interface
* Input validation improvements

---

## Contribution & License

* Fork the project, create a branch, implement features, and submit a pull request
* MIT License

---

📌 **Final Point:**
This README is tailored for **Windows + Dev-C++**. It documents the program flow, build instructions, data model, and limitations clearly, providing a professional, ready-to-use reference for the project.

---

If you want, I can also **add a polished ASCII flow diagram** directly in the console menu style, so the README looks even cleaner for students or instructors. Do you want me to do that?
