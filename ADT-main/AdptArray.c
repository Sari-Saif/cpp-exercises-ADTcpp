
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
	int SIZE_ARR;
}AdptArray, * PAdptArray;




PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df, PRINT_FUNC pf)
{
	// space allocation
	PAdptArray new_arr;
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
	new_arr->SIZE_ARR = 0;

	return new_arr;
}
