
#ifndef COURSE_SYSTEM_H
#define COURSE_SYSTEM_H

typedef enum{
    SYS_OK,
    SYS_NOT_IN_SYSTEM,
    SYS_MEMORY_PROBLEM,
    SYS_NOT_PRE_COURSE,
    SYS_ALREADY_PRE_COURSE,
    SYS_COURSE_ALREADY_EXIST
} SysResult;

typedef struct sys *CourseSystem;
typedef struct darr *DynamicArray;
typedef struct course *Course;

struct sys{
    char* name;
    DynamicArray courses;
};


CourseSystem createSystem(char *name);
int sysNumCourses(CourseSystem sys);
SysResult sysAddCourse(CourseSystem sys, Course c1);
SysResult sysRemoveCourse(CourseSystem sys, char *course_id);
SysResult sysIsPreCourse(CourseSystem sys, char *course_id1 , char *course_id2, int *ans);
SysResult sysAddPreCourse(CourseSystem sys, char *course_id1 , char *course_id2);
SysResult sysRemovePreCourse(CourseSystem sys, char *course_id1 , char *course_id2);
SysResult sysUpdateCourseName(CourseSystem sys, char *course_id, char *new_name);
void displaySystem(CourseSystem sys);
void destroySystem(CourseSystem sys);

#endif