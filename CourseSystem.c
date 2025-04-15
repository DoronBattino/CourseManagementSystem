#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "CourseSystem.h"
#include "Course.h"
#include "DynamicArray.h"

CourseSystem createSystem(char *name) {
    assert(name != NULL);
    CourseSystem new_courseSystem = malloc(sizeof(*new_courseSystem));
    if (new_courseSystem == NULL) {
        return NULL;
    }
    char *new_name = malloc(sizeof(*name) * (strlen(name) + 1));
    if (new_name == NULL) {
        free(new_courseSystem);
        return NULL;
    }
    DynamicArray new_arr = createDynamicArray();
    if (new_arr == NULL) {
        destroyDynamicArray(new_arr);
        free(new_courseSystem);
        return NULL;
    }
    strcpy(new_name,name);
    new_courseSystem->name = new_name;
    new_courseSystem->courses=new_arr;
    return new_courseSystem;
}


int sysNumCourses(CourseSystem sys){
    assert(sys!=NULL);
    return sys->courses->len;
}

SysResult sysAddCourse(CourseSystem sys, Course c1){
    assert(sys!=NULL && c1!=NULL);
    DAResult check2;
    if(sys->courses->len==0){
        check2=addElementStart(sys->courses,c1);
        if(check2==DA_MEMORY_ERROR) return SYS_MEMORY_PROBLEM;
        else return SYS_OK;
    }
    for(int i=0;i<sys->courses->len;i++) {
        if (coursesEqualId(sys->courses->elements[i], c1)) return SYS_COURSE_ALREADY_EXIST;
        if (courseLessThan(c1, sys->courses->elements[i]) && i==0){
            check2=addElementStart(sys->courses,c1);
            if(check2==DA_MEMORY_ERROR) return SYS_MEMORY_PROBLEM;
            else return SYS_OK;
        }
        if (courseLessThan(c1, sys->courses->elements[i])) {
            check2 = addElementBefore(sys->courses, c1, i);
            if (check2 == DA_MEMORY_ERROR) {
                return SYS_MEMORY_PROBLEM;
            } else return SYS_OK;
        }
    }
        check2=addElementEnd(sys->courses,c1);
        if(check2==DA_MEMORY_ERROR){
            return SYS_MEMORY_PROBLEM;
        }
        else return SYS_OK;
}

SysResult sysRemoveCourse(CourseSystem sys, char *course_id){
    assert(sys!= NULL && course_id!=NULL);
    int check_id;
    for(int i=0;i<sys->courses->len;i++){
        check_id=strcmp(sys->courses->elements[i]->id,course_id);
        if(check_id==0){
            for(int j=0;j<sysNumCourses(sys);j++) {
                removePreCourse(sys->courses->elements[j], sys->courses->elements[i]);
            }
            destroyCourse(sys->courses->elements[i]);
            removeElement(sys->courses,i);
            return SYS_OK;
        }

    }
    return SYS_NOT_IN_SYSTEM;

}


SysResult sysIsPreCourse(CourseSystem sys, char *course_id1 , char *course_id2, int *ans){
    assert(sys != NULL && course_id1!= NULL && course_id2!=NULL);
    int check_id=0, check_id2=0;
    for(int i=0;i<sys->courses->len;i++) {
        check_id = strcmp(sys->courses->elements[i]->id, course_id1);
        if (check_id == 0) break;
    }
    for(int i=0;i<sys->courses->len;i++) {
        check_id2 = strcmp(sys->courses->elements[i]->id, course_id2);
        if (check_id2 == 0) break;
    }
    if(check_id!=0 || check_id2!=0) return SYS_NOT_IN_SYSTEM;
    for(int i=0;i<sys->courses->len;i++){
        check_id = strcmp(sys->courses->elements[i]->id, course_id1);
        if(check_id==0){
            for(int j=0;j<sys->courses->elements[i]->preCourses->len;j++){
                check_id=strcmp(sys->courses->elements[i]->preCourses->elements[j]->id,course_id2);
                if(check_id==0){
                    *ans=1;
                    return SYS_OK;
                }
            }
            *ans=0;
            return SYS_OK;
        }
    }
    return SYS_NOT_IN_SYSTEM;
}




SysResult sysAddPreCourse(CourseSystem sys, char *course_id1 , char *course_id2){
    assert(sys!=NULL && course_id1!=NULL && course_id2!=NULL);
    int check_id=0, check_id2=0;
    CourseResult check_result;
    for(int i=0;i<sys->courses->len;i++) {
        check_id = strcmp(sys->courses->elements[i]->id, course_id1);
        if (check_id == 0) break;

    }
    for(int i=0;i<sys->courses->len;i++) {
        check_id2 = strcmp(sys->courses->elements[i]->id, course_id2);
        if (check_id2 == 0) break;

    }
    if(check_id!=0 || check_id2!=0) return SYS_NOT_IN_SYSTEM;
    for(int i=0;i<sys->courses->len;i++){
        check_id = strcmp(sys->courses->elements[i]->id, course_id1);
        if(check_id==0){
            for(int j=0;j<sys->courses->len;j++){
                check_id2=strcmp(sys->courses->elements[j]->id,course_id2);
                if(check_id2==0){
                    check_result=addPreCourse(sys->courses->elements[i], sys->courses->elements[j]);
                    if(check_result==COURSE_MEMORY_ERROR) return SYS_MEMORY_PROBLEM;
                    if(check_result==COURSE_ALREADY_EXISTS) return SYS_ALREADY_PRE_COURSE;
                    if(check_result==COURSE_THE_SAME_COURSE) return SYS_ALREADY_PRE_COURSE;
                     return SYS_OK;
                }
            }
        }
    }
    return SYS_OK;
}

SysResult sysRemovePreCourse(CourseSystem sys, char *course_id1 , char *course_id2) {
    assert(sys != NULL && course_id1 != NULL && course_id2 != NULL);
    int check_id = 0, check_id2 = 0;
    CourseResult check_result;
    for (int i = 0; i < sys->courses->len; i++) {
        check_id = strcmp(sys->courses->elements[i]->id, course_id1);
        if (check_id == 0) break;
    }
    for (int i = 0; i < sys->courses->len; i++) {
        check_id2 = strcmp(sys->courses->elements[i]->id, course_id2);
        if (check_id2 == 0) break;
    }
    if (check_id != 0 || check_id2 != 0) return SYS_NOT_IN_SYSTEM;
    for (int i = 0; i < sys->courses->len; i++) {
        check_id = strcmp(sys->courses->elements[i]->id, course_id1);
        if (check_id == 0) {
            for (int j = 0; j < sys->courses->len; j++) {
                check_id2 = strcmp(sys->courses->elements[j]->id, course_id2);
                if (check_id2 == 0) {
                    check_result = removePreCourse(sys->courses->elements[i], sys->courses->elements[j]);
                    if (check_result == COURSE_NOT_EXIST) return SYS_NOT_PRE_COURSE;
                    else return SYS_OK;
                }


            }
        }
    }
    return SYS_OK;
}



SysResult sysUpdateCourseName(CourseSystem sys, char *course_id, char *new_name){
    assert(sys!=NULL && course_id!=NULL && new_name != NULL);
    int check_id;
    for(int i=0;i<sys->courses->len;i++){
        check_id=strcmp(sys->courses->elements[i]->id,course_id);
        if(check_id==0){
            char *dup_name=(char *)malloc(sizeof(*new_name)*(strlen(new_name)+1));
            if(!dup_name){
                return SYS_MEMORY_PROBLEM;
            }
            free(sys->courses->elements[i]->name);
            strcpy(dup_name, new_name);
            sys->courses->elements[i]->name=dup_name;
            return SYS_OK;
        }
        if(sys->courses->elements[i]->preCourses){
            int check_pre_id;
            for(int j=0; j<sys->courses->elements[i]->preCourses->len; ++j){
                check_pre_id = strcmp(sys->courses->elements[i]->preCourses->elements[j]->id,course_id);
                if(check_pre_id==0){
                    char *dup_pre_name=(char *)malloc(sizeof(char)*strlen(new_name)+1);
                    if(!dup_pre_name){
                        return SYS_MEMORY_PROBLEM;
                    }
                    free(sys->courses->elements[i]->preCourses->elements[j]->name);
                    strcpy(dup_pre_name, new_name);
                    sys->courses->elements[i]->preCourses->elements[j]->name=dup_pre_name;
                    return SYS_OK;
                }
            }
        }
    }
    return SYS_NOT_IN_SYSTEM;
}


void displaySystem(CourseSystem sys){
    assert(sys!=NULL);
    printf("%s\n", sys->name);
    displayAllElements(sys->courses);
}

void destroySystem(CourseSystem sys){
    for(int i=0;i<sys->courses->len;i++){
        destroyCourse(sys->courses->elements[i]);
    }
    free(sys->name);
    destroyDynamicArray(sys->courses);
    free(sys);
}

