# 🎓 Attendance Management System (SMIU)

A simple, console-based **C** program to manage student attendance in-memory.
This project is beginner-friendly and demonstrates the use of **structs, arrays, and basic I/O** in C.

---

## 📌 Table of Contents

* [Project Overview](#project-overview)
* [Key Features](#key-features)
* [Requirements](#requirements)
* [How to Run](#how-to-run)
* [Program Flow](#program-flow)
* [Data Structures](#data-structures)
* [Function Summary](#function-summary)
* [Limitations](#limitations)
* [Future Improvements](#future-improvements)
* [Project Team](#project-team)

---
   
## 📘 Project Overview

This project allows users to:

* Register students (name and ID)
* Mark attendance (Present or Absent) for a given date
* View all students
* View an individual student’s attendance records

All data is stored in **RAM**, with a menu-driven console interface, making it ideal for learning core C programming concepts.

---

## ⭐ Key Features

* Add new students with unique IDs
* Mark attendance with user-specified date
* View all registered students
* View individual student attendance history
* Menu-driven interface for simple navigation

---

## 🖥 Requirements

* C compiler (tested with GCC, Dev-C++, or MSVC)
* Windows OS recommended for best experience (uses `system("cls")` for clearing console)
* Basic console/terminal access

---

## ▶ How to Run

### Using Dev-C++

1. Create a **New Project → Console Application → C Project**
2. Add the `.c` file
3. Press **F9** to compile
4. Run the program via Dev-C++

### Using Command Line (GCC)

```bash
gcc -o attendance attendance.c
./attendance         # Linux/macOS
attendance.exe       # Windows
```

---

## 🔄 Program Flow

```
========== ATTENDANCE MANAGEMENT SYSTEM ==========
1. Add New Student
2. View All Students
3. Mark Attendance
4. View Student Attendance
5. Exit
```

* The program loops until the user selects **Exit**.
* Users navigate via numeric menu input.

---

## 🧱 Data Structures

```c
typedef struct {
    char date[15];       // YYYY-MM-DD
    char status[10];     // "Present" or "Absent"
} AttendanceRecord;

typedef struct {
    char name[50];
    char id[20];
    AttendanceRecord attendance[200];
    int attendanceCount;
} Student;

Student students[100];
int studentCount = 0;
```

---

## 🧩 Function Summary

| Function                  | Purpose                                   |
| ------------------------- | ----------------------------------------- |
| `addStudent()`            | Adds a new student                        |
| `viewAllStudents()`       | Displays all students                     |
| `markAttendance()`        | Marks attendance for a student            |
| `viewStudentAttendance()` | Displays attendance records for a student |
| `clearScreen()`           | Clears console screen (Windows only)      |
| `pauseProgram()`          | Pauses execution and waits for user input |

---

## ⚠ Limitations

* All data is **lost on program exit** (no file saving)
* Maximum **100 students**
* Maximum **200 attendance records per student**
* Only supports **Present / Absent** statuses
* Windows-specific console clear (`system("cls")`)
* No duplicate ID prevention or date validation

---

## 👥 Project Team

Developed by a team of three:
**Okasha Nadeem (Team Lead)**
**Muhammad Tabish**
**Syed Muhammad Sarim**
**Muhammad Yahya Alvi**

Final project for **Programming Fundamentals** under the guidance of
**Miss Iqra — SMI University**

---
