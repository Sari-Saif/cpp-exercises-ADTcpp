
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

// struct structure 
typedef struct AdptArray_
{
	COPY_FUNC cf;
	PRINT_FUNC pf;
	DEL_FUNC df;
	PElement *P_E;
	int SIZE_OF_ARR;
} AdptArray, * PAdptArray;
/*
	initializes an empty array (ie no members)
*/
PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df, PRINT_FUNC pf)
{
	PAdptArray new_arr;
	// allocate more memory and make it flexible
	new_arr = (PAdptArray)malloc(sizeof(AdptArray) * 2);
	if (new_arr == NULL)
	{
		// If no place has been allocated
		prift(" alloaction faild ");
		exit(FAIL);
	}
	// Initialize values
	new_arr->cf = cf;
	new_arr->df = df;
	new_arr->pf = pf;
	new_arr->P_E = NULL;
	new_arr->SIZE_OF_ARR = 0;

	return new_arr;
}

/*
   frees the memory of the object including his organs(including his organs)
*/
void DeleteAdptArray(PAdptArray PAA)
{
	if(PAA == NULL)
	{
		// there nothing to do
		return;
	}
	int at = 0;
	while (at < PAA ->SIZE_OF_ARR)
	{
		PAA->df((PAA->P_E)[at]);
		++at;
	}
	//Pointers should be freed so that there will be no memory leak
	free(PAA->P_E);
	free(PAA);

}
