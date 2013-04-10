#include <stdlib.h>
#include <stdio.h>
#include "optlib.h"
#include <string.h>
#define NAME_LENGTH 30

typedef struct students_ {
    char name[NAME_LENGTH];
    char surname[NAME_LENGTH];
    char patronymic[NAME_LENGTH];
    int sem;
} studen_t;

typedef union exams_ {
    int sem1[3];
    int sem2[4];
} exams_t;

typedef struct student_exams {
    studen_t student;
    exams_t exams;
} studexam_t;

const int sem_exams[][4] = { {1, 4, 5}, {1, 2, 3, 4} };
const int sem_exams_number[2] = {3, 4};

char *exam_name(int);
int input(studexam_t *, int);
int output(studexam_t *, int, int);

int main(int argc, char **argv)
{
    int sem_number, students_number;
    studexam_t *students;
    sem_number = options(argc, argv);
    if (sem_number != 1 && sem_number != 2) {
        printf("There are only two sems first(1) and second(2).\n");
        return 0;
    }
    sem_number--;
    printf("Print students number:\n");
    while (get_posint(&students_number,stdin)==-1)
        printf("Please print positive integer values.\n");
    students = (studexam_t *) calloc(students_number, sizeof(studexam_t));
    input(students, students_number);
    output(students, students_number, sem_number);
    free(students);
    return (0);
}

int input(studexam_t * students, int students_number)
{
    int i = 0, j = 0;
    for (i = 0; i < students_number; i++) {
        printf("Provide student Name:\n");
        fgets_c(students[i].student.name, NAME_LENGTH, stdin);
        printf("Surname:\n");
        fgets_c(students[i].student.surname, NAME_LENGTH, stdin);
        printf("Patronymic:\n");
        fgets_c(students[i].student.patronymic, NAME_LENGTH, stdin);
        printf("Print sem number for student:");
        while (get_posint(&students[i].student.sem,stdin)==-1)
            if (students[i].student.sem!=1 && students[i].student.sem!=2)
                printf("1 or 2.\n");
        for (j = 0; j < sem_exams_number[students[i].student.sem]; j++) {
            printf("Students mark for %s is\n",
                   exam_name(sem_exams[students[i].student.sem][j]));
            if (students[i].student.sem == 1)
                while (get_posint(&students[i].exams.sem1[j],stdin)==-1)
                    printf("Please print numbers.\n");
            else
                while (get_posint(&students[i].exams.sem2[j],stdin)==-1)
                    printf("Please print numbers.\n");
        }
    }
    return 0;
}

char *exam_name(int i)
{
    char *exam_names[] =
        { "Math", "Physics", "English", "Programming", "NGiG" };
    return exam_names[i - 1];
}

int output(studexam_t * students, int students_number, int sem_number)
{
    int i = 0, j = 0;
    for (i = 0; i < students_number; i++) {
        printf("%s %s %s    ", students[i].student.surname,
               students[i].student.name, students[i].student.patronymic);
        for (j = 0; j < sem_exams_number[sem_number]; j++)
            if (sem_number == 1)
                printf(" %s:%d ", exam_name(sem_exams[sem_number][j]),
                       students[i].exams.sem1[j]);
            else
                printf(" %s:%d ", exam_name(sem_exams[sem_number][j]),
                       students[i].exams.sem2[j]);
        printf("\n");
    }
    return 1;
}
