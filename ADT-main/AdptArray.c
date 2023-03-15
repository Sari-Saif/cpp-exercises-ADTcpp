
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

	/*

	Receives an index and member and saves a copy of the member
	in the requested place. Frees the old member if
	Exists

	*/
	Result help_SetAdptArrayAt(PAdptArray P_ADT_A, int index, PElement P_E)
	{

		PElement* new_P_E;
		//Validation
		if(P_E == NULL)
		{
			return FAIL;
		}
		int new_index = index + 1 ; 
		// case that asked index out of range the original array size	
		if( index >= P_ADT_A->SIZE_OF_ARR)
		{
			if((new_P_E = (PElement*)calloc((new_index), sizeof(PElement)) == NULL))
			{
				return FAIL;
			}
			memcpy( new_P_E , P_ADT_A->P_E , (P_ADT_A->SIZE_OF_ARR)  * sizeof(PElement));
			// release the old value and update it with the new value
			free(P_ADT_A->P_E);
			P_ADT_A-> P_E = new_P_E;
		}
			// delete what was in at index
			P_ADT_A ->df((P_ADT_A->P_E)[index]);
			// replace with new element
			(P_ADT_A->P_E)[index] = P_ADT_A ->cf(new_P_E);

			// check if need to update size of P_ADT_A
			if(index >= P_ADT_A -> SIZE_OF_ARR)
			{
				P_ADT_A->SIZE_OF_ARR = new_index;
			}
		return SUCCESS;

	}

	Result SetAdptArrayAt(PAdptArray P_ADT_A, int index, PElement P_E)
	{
		Result result = help_SetAdptArrayAt(P_ADT_A,index,P_E);
		return result;
	}
