#include <stdio.h>

#include "Course.h"
#include "CourseSystem.h"

#define ASSERT(test_number, test_condition)  \
   if (!(test_condition)) {printf("\nTEST %s FAILED", test_number); } \
   else printf("\nTEST %s OK", test_number);

int main(int argc, char **argv){

	CourseResult rc = COURSE_OK;

	Course c1;
	Course c2;
	Course c3;
	rc = createCourse("001", "Course1", 2.5, &c1);
	ASSERT("1.1", rc==COURSE_OK);

	rc = createCourse("002", "Course2", -3.5, &c2);
	ASSERT("1.2", rc==COURSE_ILLEGAL_PARAMETER);

	rc = createCourse("003", "Course3", 3.5, &c3);
	ASSERT("1.3", rc==COURSE_OK);

	int is_courses_equal = coursesEqualId(c1, c3);
	ASSERT("1.4", is_courses_equal==0);

	int is_course_less_then = courseLessThan(c1,c3);
	ASSERT("1.5", is_course_less_then==1);

	rc = courseUpdateName(c1, "Course1.1");
	ASSERT("1.6",rc==COURSE_OK);

	rc = addPreCourse(c1,c3);
	ASSERT("1.7",rc==COURSE_OK);

	rc = removePreCourse(c1,c3);
	ASSERT("1.8", rc==COURSE_OK);

	displayCourse(c1);
	/*001 Course1.1 2.5 003*/

	destroyCourse(c3);
	destroyCourse(c1);
	return 0;
}
