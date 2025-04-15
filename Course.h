
#ifndef COURSE_H
#define COURSE_H

typedef struct course *Course;
typedef struct darr *DynamicArray;

struct course{
    char *id;
    char *name;
    double credits;
    DynamicArray preCourses;
};


typedef enum{
    COURSE_OK,
    COURSE_ILLEGAL_PARAMETER,
    COURSE_MEMORY_ERROR,
    COURSE_THE_SAME_COURSE,
    COURSE_ALREADY_EXISTS,
    COURSE_NOT_EXIST
}CourseResult;

CourseResult createCourse(char *id, char *name, double credits, Course *course);
int coursesEqualId(Course course1, Course course2);
int courseLessThan(Course course1, Course course2);
CourseResult courseUpdateName(Course course1, char *new_name);
CourseResult addPreCourse(Course course1, Course course2);
CourseResult removePreCourse(Course course1, Course course2);
void displayCourse(Course course1);
void destroyCourse(Course course1);

#endif