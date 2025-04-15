
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct course *Course;
typedef struct darr *DynamicArray;


struct darr{
    int len;
    Course *elements;
};

typedef enum {
    DA_OK,
    DA_ILLEGAL_INDEX,
    DA_MEMORY_ERROR
}DAResult;


DynamicArray createDynamicArray();
DAResult addElementBefore(DynamicArray arr, Course add, int index);
DAResult addElementStart(DynamicArray arr, Course add);
DAResult addElementEnd(DynamicArray arr , Course add);
DAResult indexOfElement(DynamicArray da, Course c , int base_index, int *result_index);
DAResult removeElement(DynamicArray arr, int index);
DAResult updateElement(DynamicArray da, int id, Course Course);
DAResult displayElement(DynamicArray da, int i);
void displayAllElements(DynamicArray arr);
int size(DynamicArray arr);
void destroyDynamicArray(DynamicArray arr);

#endif