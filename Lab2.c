#include "stdlib.h"
#include "stdio.h"
#include "Optlib.h"
#include "string.h"

typedef struct students_ {
    char name[30];
    char surname[30];
    char patronymic[30];
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

char *exam_name(int);
int input(studexam_t *, int, int);
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
    printf("Print students number.\n");
    while (!get_int(&students_number))
        printf("Please print numbers.\n");
    students = (studexam_t *) calloc(students_number, sizeof(studexam_t));
    input(students, students_number, sem_number);
    output(students, students_number, sem_number);
    free(students);
    return (0);
}

int input(studexam_t * students, int students_number, int sem_number)
{
    int i = 0, j = 0;
    for (i = 0; i < students_number; i++) {
        printf("Provide student Name.\n");
        fflush(stdin);
        fgets(students[i].student.name, 29, stdin);
        printf("Surname\n");
        fflush(stdin);
        fgets(students[i].student.surname, 29, stdin);
        printf("Patronymic\n");
        fflush(stdin);
        fgets(students[i].student.patronymic, 29, stdin);
        for (j = 0; j < sem_number + 2; j++) {
            printf("Students mark for %s is\n",
                   exam_name(sem_exams[sem_number - 1][j]));
            fflush(stdin);
            if (sem_number == 1)
                while (!get_int(&students[i].exams.sem1[j]))
                    printf("Please print numbers.\n");
            else
                while (!get_int(&students[i].exams.sem2[j]))
                    printf("Please print numbers.\n");
        }
        *strchr(students[i].student.name, '\n') = '\0';
        *strchr(students[i].student.patronymic, '\n') = '\0';
        *strchr(students[i].student.surname, '\n') = '\0';
    }
    return 0;
}

char *exam_name(int i)
{
    char *exam_names[] =
        { "Math", "Physics", "English", "Programming", "NGiG" };
    if (i > 6 || i < 1)
        return 0;
    return exam_names[i - 1];
}

int output(studexam_t * students, int students_number, int sem_number)
{
    int i = 0, j = 0;
    for (i = 0; i < students_number; i++) {
        printf("%s %s %s    ", students[i].student.surname,
               students[i].student.name, students[i].student.patronymic);
        for (j = 0; j < sem_number + 2; j++)
            if (sem_number == 1)
                printf(" %s:%d ", exam_name(sem_exams[sem_number - 1][j]),
                       students[i].exams.sem1[j]);
            else
                printf(" %s:%d ", exam_name(sem_exams[sem_number - 1][j]),
                       students[i].exams.sem2[j]);
        printf("\n");
    }
    return 1;
}
