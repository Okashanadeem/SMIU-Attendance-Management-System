#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_ID 20
#define MAX_RECORDS 200

typedef struct {
    char date[15];
    char status[10];
} AttendanceRecord;

typedef struct {
    char name[MAX_NAME];
    char id[MAX_ID];
    AttendanceRecord attendance[MAX_RECORDS];
    int attendanceCount;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// prototypes
void addStudent();
void markAttendance();
void viewAllStudents();
void viewStudentAttendance();
void pauseProgram();
void clearScreen();
void saveToFile(char name[], char id[], char date[], char status[]);
void loadFromFile();
int findStudent(char id[]);

int main() {
    int choice;
    loadFromFile();

    do {
        clearScreen();
        printf("\n===== ATTENDANCE MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n2. View Students\n3. Mark Attendance\n4. View Student Attendance\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        getchar();

        switch(choice){
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: markAttendance(); break;
            case 4: viewStudentAttendance(); break;
        }
    } while(choice!=5);

    return 0;
}

void clearScreen(){ system("cls"); }
void pauseProgram(){ printf("\nPress Enter..."); getchar(); }

int findStudent(char id[]){
    for(int i=0;i<studentCount;i++)
        if(strcmp(students[i].id,id)==0) return i;
    return -1;
}

void saveToFile(char name[], char id[], char date[], char status[]){
    FILE *fp=fopen("students.csv","a");
    fprintf(fp,"%s,%s,%s,%s\n",name,id,date,status);
    fclose(fp);
}

void loadFromFile(){
    FILE *fp=fopen("students.csv","r");
    if(fp==NULL) return;

    char line[200];
    fgets(line,200,fp);

    while(fgets(line,200,fp)){
        char name[MAX_NAME],id[MAX_ID],date[15],status[10];
        sscanf(line,"%[^,],%[^,],%[^,],%s",name,id,date,status);

        int index=findStudent(id);
        if(index==-1){
            strcpy(students[studentCount].name,name);
            strcpy(students[studentCount].id,id);
            students[studentCount].attendanceCount=0;
            index=studentCount++;
        }

        strcpy(students[index].attendance[students[index].attendanceCount].date,date);
        strcpy(students[index].attendance[students[index].attendanceCount].status,status);
        students[index].attendanceCount++;
    }
    fclose(fp);
}

void addStudent(){
    Student s;
    printf("Name: "); fgets(s.name,MAX_NAME,stdin);
    s.name[strcspn(s.name,"\n")]=0;
    printf("ID: "); fgets(s.id,MAX_ID,stdin);
    s.id[strcspn(s.id,"\n")]=0;
    s.attendanceCount=0;
    students[studentCount++]=s;
}

void viewAllStudents(){
    for(int i=0;i<studentCount;i++)
        printf("%d. %s (%s)\n",i+1,students[i].name,students[i].id);
    pauseProgram();
}

void markAttendance(){
    char id[MAX_ID];
    printf("Enter ID: "); fgets(id,MAX_ID,stdin);
    id[strcspn(id,"\n")]=0;

    int index=findStudent(id);
    if(index==-1){ printf("Not Found"); pauseProgram(); return; }

    AttendanceRecord r;
    printf("Date: "); fgets(r.date,15,stdin);
    r.date[strcspn(r.date,"\n")]=0;
    int ch;
    printf("1.Present 2.Absent: "); scanf("%d",&ch); getchar();
    strcpy(r.status,(ch==1)?"Present":"Absent");

    students[index].attendance[students[index].attendanceCount++]=r;
    saveToFile(students[index].name,students[index].id,r.date,r.status);
}

void viewStudentAttendance(){
    char id[MAX_ID];
    printf("Enter ID: "); fgets(id,MAX_ID,stdin);
    id[strcspn(id,"\n")]=0;

    int index=findStudent(id);
    if(index==-1){ printf("Not Found"); pauseProgram(); return; }

    for(int i=0;i<students[index].attendanceCount;i++)
        printf("%s - %s\n",students[index].attendance[i].date,
               students[index].attendance[i].status);
    pauseProgram();
}

