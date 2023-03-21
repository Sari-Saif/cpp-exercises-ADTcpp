#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Result help_SetAdptArrayAt(PAdptArray P_ADT_Arr, int index, PElement P_Element);


// struct structure 
typedef struct AdptArray_
{
	COPY_FUNC cf;
	PRINT_FUNC pf;
	DEL_FUNC df;
	PElement *P_Element;
	int SIZE_OF_ARR;	
} AdptArray ;//*PAdptArray;
/*
	initializes an empty array (ie no members)
*/
PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df, PRINT_FUNC pf)
{
	PAdptArray new_arr;
	// allocate more memory and make it flexible
	new_arr = (PAdptArray)malloc(sizeof(AdptArray));
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
	while (at < PAA->SIZE_OF_ARR)
	{
		if (PAA->P_Element[at])
		{
			PAA->df((PAA->P_Element)[at]);
		}
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

	PElement* new_arr;
	//Validation
	if(P_Element == NULL)
	{
		return FAIL;
	}
	int new_size = index + 1 ; 
	// case that asked index out of range the original array size	
	if( index >= P_ADT_Arr->SIZE_OF_ARR)
	{
		if((new_arr = (PElement*)calloc((new_size), sizeof(PElement))) == NULL)
		{
			return FAIL;
		}
		// release the old value and update it with the new value
		for(int i=0;i<P_ADT_Arr->SIZE_OF_ARR;i++)
		{
			new_arr[i] = P_ADT_Arr->P_Element[i];
		}

		free(P_ADT_Arr->P_Element);
		P_ADT_Arr-> P_Element = new_arr;
	}
		if(P_ADT_Arr->P_Element[index])
		{
		// delete what was in at index;
		P_ADT_Arr->df(P_ADT_Arr->P_Element[index]);
		}

		// replace with new element
		P_ADT_Arr->P_Element[index] = P_ADT_Arr ->cf(P_Element);
		

		// check if need to update size of P_ADT_Arr
		if(index >=P_ADT_Arr->SIZE_OF_ARR)
		{
			P_ADT_Arr->SIZE_OF_ARR = new_size;
		}
	return SUCCESS;

}

Result SetAdptArrayAt(PAdptArray P_ADT_Arr, int index, PElement P_Element)
{
	Result result = help_SetAdptArrayAt(P_ADT_Arr,index,P_Element);
	return result;
}


PElement GetAdptArrayAt(PAdptArray P_AdptArr, int index)
{			
		//Validation
		if(P_AdptArr == NULL || P_AdptArr->SIZE_OF_ARR < index)
		{
			//its null or the requested index out of range 
		   // and nothing to do 
			return NULL;
		}
		if(P_AdptArr->P_Element[index]!=NULL)
		{

		return P_AdptArr->cf((P_AdptArr->P_Element)[index]);
		}
return NULL;	
}
/*

*/
int GetAdptArraySize(PAdptArray P_adtArr)
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
/*
	print elements
*/
void PrintDB(PAdptArray P_ADT_Arr)
{

int i =0;
while (i<P_ADT_Arr->SIZE_OF_ARR)
{
	if((P_ADT_Arr->P_Element)[i] == NULL )
	{
		i++;
	}
	else
	{
		P_ADT_Arr->pf((P_ADT_Arr->P_Element)[i]);
		i+=1;
	}
}
}