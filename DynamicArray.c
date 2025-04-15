#include <stdio.h>
#include <string.h>
#include "DynamicArray.h"
#include "Course.h"
#include "CourseSystem.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray createDynamicArray() {
    DynamicArray arr = (DynamicArray)malloc(sizeof(struct darr));
    if (!arr) {
        return NULL;
    }
    arr->len = 0;
    arr->elements = NULL;

    return arr;
}


DAResult addElementBefore(DynamicArray arr, Course add, int index){
    assert(arr!=NULL && add!=NULL);
    if(index<0 || index>arr->len){
        return DA_ILLEGAL_INDEX;
    }

    arr->len++;
    arr->elements=realloc(arr->elements,sizeof(Course)*(arr->len));
        if(!(arr->elements)) {
            return DA_MEMORY_ERROR;
        }
    for(int i=(arr->len-2);i>index-1; i--){
        arr->elements[i+1]=arr->elements[i];
    }
    arr->elements[index]=add;
    return DA_OK;

}


DAResult addElementStart(DynamicArray arr, Course add){
    assert(arr!=NULL && add!=NULL);
    arr->len++;
    arr->elements=realloc(arr->elements,sizeof(Course)*(arr->len));
    if(!(arr->elements)){
        return DA_MEMORY_ERROR;
    }
    for(int i=(arr->len-2);i>=0; i--){
        arr->elements[i+1]=arr->elements[i];
    }
    arr->elements[0]=add;
    return DA_OK;

}



DAResult addElementEnd(DynamicArray arr , Course add){
    assert(arr!=NULL && add!=NULL);
    arr->len++;
    arr->elements=realloc(arr->elements,sizeof(Course)*(arr->len));
    if(!(arr->elements)){
        return DA_MEMORY_ERROR;
    }
    arr->elements[arr->len-1]=add;
    return DA_OK;

}

DAResult indexOfElement(DynamicArray da, Course c , int base_index, int *result_index){
    assert(da!=NULL && c!=NULL && result_index!=NULL);
    if(base_index<0 || base_index>=(da->len)) {
        *result_index=-1;
        return DA_ILLEGAL_INDEX;
    }
    for(int cur_index=base_index;cur_index<(da->len);cur_index++){
        if(coursesEqualId(da->elements[cur_index],c)){
            *result_index=cur_index;
            return DA_OK;
        }
        else continue;
    }
    *result_index=-1;
    return DA_OK;
}




DAResult removeElement(DynamicArray arr, int index){
    assert(arr!=NULL);
    if(index<0 || index>=(arr->len)){
        return DA_ILLEGAL_INDEX;
    }
    for(int i=index+1;i<(arr->len);i++){
        arr->elements[i-1]=arr->elements[i];
    }
    arr->len--;
    if (arr->len == 0){
        free(arr->elements);
        arr->elements = NULL;
        return DA_OK;
    }
    arr->elements=realloc(arr->elements,sizeof(Course)*(arr->len));
        if(!arr->elements){
            return DA_MEMORY_ERROR;
        }
     return DA_OK;

}



DAResult updateElement(DynamicArray da, int id, Course course){
    assert(da!=NULL && course!=NULL);
    if(id<0 || id>=(da->len)){
        return DA_ILLEGAL_INDEX;
    }

    if (strcmp(da->elements[id]->id, course->id) == 0){
        return DA_OK;
    }

    char *tmp = (char *)malloc(sizeof(char) * strlen(course->name)+1);
    if (!tmp){
        return DA_MEMORY_ERROR;
    }
    strcpy(tmp, course->name);
    free(da->elements[id]->name);
    da->elements[id]->name = tmp;
    strcpy(da->elements[id]->id,course->id);
    da->elements[id]->credits = course->credits;
    DynamicArray tmp1 = createDynamicArray();
    if (!tmp1){
        return DA_MEMORY_ERROR;
    }
    for (int i = 0; i < course->preCourses->len; ++i){
        addElementEnd(tmp1, course->preCourses->elements[i]);
    }
    free(da->elements[id]->preCourses);
    da->elements[id]->preCourses = tmp1;
    
    return DA_OK;
}

DAResult displayElement(DynamicArray da, int i){
    assert(da!=NULL);
    if(i<0 || i>=(da->len)){
        return DA_ILLEGAL_INDEX;
    }
    displayCourse(da->elements[i]);
    return DA_OK;

}

void displayAllElements(DynamicArray arr){
    assert(arr!=NULL);
    for(int i=0;i<arr->len;i++){
        displayCourse(arr->elements[i]);
        printf("\n");
    }
}


int size(DynamicArray arr){
    assert(arr!=NULL);
    return arr->len;
}


void destroyDynamicArray(DynamicArray arr){
    if (arr == NULL) return;
    if (arr->elements != NULL){
        free(arr->elements);
    }
    arr->len = 0;
    free(arr);
}