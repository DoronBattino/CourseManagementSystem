#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Course.h"
#include "CourseSystem.h"
#include "DynamicArray.h"





CourseResult createCourse(char *id, char *name, double credits, Course *course){
    assert( id!=NULL || name != NULL || course!= NULL);
    if(credits<0){
        return COURSE_ILLEGAL_PARAMETER;
    }
    Course dup_course=(Course)malloc(sizeof(struct course));
    if(!dup_course){
        return COURSE_MEMORY_ERROR;
    }
    char* dup_id=(char *)malloc(sizeof(*id)*(strlen(id)+1));
    if(!dup_id) {
        free(dup_course);
        return COURSE_MEMORY_ERROR;
    }
    char* dup_name=(char *)malloc(sizeof(*dup_name)*(strlen(name)+1));
    if(!dup_name){
        free(dup_course);
        free(dup_id);
        return COURSE_MEMORY_ERROR;
    }
    DynamicArray dup_precourses=createDynamicArray();
    if(!dup_precourses){
        free(dup_course);
        free(dup_id);
        free(dup_name);
        return COURSE_MEMORY_ERROR;
    }

    strcpy(dup_id,id);
    strcpy(dup_name,name);
    dup_course->id=dup_id;
    dup_course->name=dup_name;
    dup_course->credits=credits;
    dup_course->preCourses=dup_precourses;
    *course=dup_course;

    return COURSE_OK;

}


int coursesEqualId(Course course1, Course course2){
    assert(course1!=NULL && course2!=NULL);
    int check=0;
    check=strcmp((course1->id), (course2->id));
    if(check==0) return 1;
    else return 0;

}


int courseLessThan(Course course1, Course course2){
    assert(course1!=NULL && course2!=NULL);
    int check=0;
    check=strcmp((course1->id), (course2->id));
    if(check<0) return 1;
    else return 0;

}


CourseResult courseUpdateName(Course course1, char *new_name){
    assert(new_name!=NULL && course1!=NULL);
    char *dup_name=(char *)malloc(sizeof(*new_name)*(strlen(new_name)+1));
    if(!dup_name) {
        return COURSE_MEMORY_ERROR;
    }
    strcpy(dup_name, new_name);
    free(course1->name);
    course1->name=dup_name;

    return COURSE_OK;

}



CourseResult addPreCourse(Course course1, Course course2){
    assert(course1!=NULL && course2!=NULL);
    if(course1->id==course2->id){
        return COURSE_THE_SAME_COURSE;
    }
    if(course1->preCourses->len==0){
        addElementStart(course1->preCourses,course2);
        return COURSE_OK;
    }
    for(int i=0;i<course1->preCourses->len;i++){
        if(coursesEqualId(course1->preCourses->elements[i],course2)){
            return COURSE_ALREADY_EXISTS;
        }
        if(courseLessThan(course1->preCourses->elements[i], course2) && i==0){
            addElementStart(course1->preCourses,course2);
            return COURSE_OK;
        }
        if(courseLessThan(course1->preCourses->elements[i], course2)){
            addElementBefore(course1->preCourses,course2,i);
            return COURSE_OK;
        }
    }
    addElementEnd(course1->preCourses,course2);
    return COURSE_OK;
}

CourseResult removePreCourse(Course course1, Course course2) {
    assert(course1 != NULL && course2 != NULL);
    for (int i = 0; i < course1->preCourses->len; i++) {
        if (strcmp(course2->id, course1->preCourses->elements[i]->id) == 0) {
            removeElement(course1->preCourses, i);
            return COURSE_OK;
        }
    }
    return COURSE_NOT_EXIST;
}

void displayCourse(Course course1){
    assert(course1 !=NULL);
    printf("%s %s %.lf", course1->id, course1->name, course1->credits);

    // if(course1->preCourses->len==0) {
    //     printf("%s %s %.lf", course1->id, course1->name, course1->credits);
    //     return;
    // }
    // else {
    //     printf("%s %s %.lf ", course1->id, course1->name, course1->credits);
    //     for (int i = 0; i < course1->preCourses->len; i++) {
    //         if (i == course1->preCourses->len - 1) {
    //             printf("%s", course1->preCourses->elements[i]->id);
    //             return;
    //         } else printf("%s ", course1->preCourses->elements[i]->id);
    //     }
    // }
}

void destroyCourse(Course course1){
    if (course1 == NULL) return;
    free(course1->id);
    course1->id = NULL;
    free(course1->name);
    course1->name = NULL;
    destroyDynamicArray(course1->preCourses);
    course1->preCourses = NULL;
    free(course1);
}

