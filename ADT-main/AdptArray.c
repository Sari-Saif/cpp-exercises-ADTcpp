
	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include "AdptArray.h"

	Result help_SetAdptArrayAt(PAdptArray P_ADT_Arr, int index, PElement P_Element);


	// struct structure 
	typedef struct AdptArray_
	{
		COPY_FUNC cf;
		PRINT_FUNC pf;
		DEL_FUNC df;
		PElement *P_Element;
		int SIZE_OF_ARR;
	} AdptArray;
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
			//printf(" alloaction faild ");
			return NULL;
		}
		// Initialize values
		new_arr->cf = cf;
		new_arr->df = df;
		new_arr->pf = pf;
		new_arr->P_Element = NULL;
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
			PAA->df((PAA->P_Element)[at]);
			++at;
		}
		//Pointers should be freed so that there will be no memory leak
		free(PAA->P_Element);
		free(PAA);

	}

	/*

	Receives an index and member and saves a copy of the member
	in the requested place. Frees the old member if
	Exists

	*/
	Result help_SetAdptArrayAt(PAdptArray P_ADT_Arr, int index, PElement P_Element)
	{

		PElement* new_P_E;
		//Validation
		if(P_Element == NULL)
		{
			return FAIL;
		}
		int new_index = index + 1 ; 
		// case that asked index out of range the original array size	
		if( index >= P_ADT_Arr->SIZE_OF_ARR)
		{
			if((new_P_E = (PElement*)calloc((new_index), sizeof(PElement))) == NULL)
			{
				return FAIL;
			}
			memcpy( new_P_E , P_ADT_Arr->P_Element , (P_ADT_Arr->SIZE_OF_ARR)  * sizeof(PElement));
			// release the old value and update it with the new value
			free(P_ADT_Arr->P_Element);
			P_ADT_Arr-> P_Element = new_P_E;
		}
			// delete what was in at index
			P_ADT_Arr ->df((P_ADT_Arr->P_Element)[index]);
			// replace with new element
			(P_ADT_Arr->P_Element)[index] = P_ADT_Arr ->cf(new_P_E);

			// check if need to update size of P_ADT_Arr
			if(index >= P_ADT_Arr -> SIZE_OF_ARR)
			{
				P_ADT_Arr->SIZE_OF_ARR = new_index;
			}
		return SUCCESS;

	}

	Result SetAdptArrayAt(PAdptArray P_ADT_Arr, int index, PElement P_Element)
	{
		Result result = help_SetAdptArrayAt(P_ADT_Arr,index,P_Element);
		return result;
	}

// need to check 
PElement GetAdptArrayAt(AdptArray P_AdptArr, int index)
{

	PElement* new_P_E;
			
			//Validation
			if(P_AdptArr == NULL || P_AdptArr->SIZE_OF_ARR < index)
			{
				//its null or the requested index out of range 
			   // and nothing to do 
				return FAIL;
			}
			new_P_E = (P_AdptArr->P_Element)[index] ;
			free(P_AdptArr->P_Element);
			return new_P_E;
}
// need to check 
int GetAdptArraySize(AdptArray P_adtArr)
{
	int size ;
	if(P_adtArr == NULL )
	{
		size = -1;
	}
	else{

		size = P_adtArr->SIZE_OF_ARR;
	}
	return size;
}
void PrintDB(AdptArray P_ADT_Arr)
{

	int i =0;
	while (i<P_ADT_Arr->SIZE_OF_ARR)
	{
		P_ADT_Arr->pf(P_ADT_Arr->P_Element);
		i+=1;
	}
	free(P_ADT_Arr);

}