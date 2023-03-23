#include "AdptArray.h"

typedef struct AdptArray_ {
    int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray_, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_) {
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray_));
	if (pArr == NULL) return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc_;
	return pArr;
}

void DeleteAdptArray(PAdptArray pArr) {
	if (pArr == NULL) return;
    for(int i = 0; i < pArr->ArrSize; i++) {
        if(pArr->pElemArr[i] != NULL) pArr->delFunc(pArr->pElemArr[i]);
    }
    free(pArr->pElemArr);
	free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int index, PElement pElem) {
    PElement* newpElemArr = NULL;
	if (pArr == NULL) return FAIL;
	if (index >= pArr->ArrSize) {
	    if ((newpElemArr = (PElement*)calloc((index + 1), sizeof(PElement))) == NULL) return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

    if((pArr->pElemArr)[index] != NULL) pArr->delFunc((pArr->pElemArr)[index]);

	(pArr->pElemArr)[index] = pArr->copyFunc(pElem);
    
    if(index >= pArr->ArrSize) pArr->ArrSize = index + 1;
	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int index) {
    if(pArr == NULL || pArr->pElemArr[index] == NULL) return NULL;
    return pArr->copyFunc((pArr->pElemArr)[index]);
}

int GetAdptArraySize(PAdptArray pArr) { 
    if(pArr == NULL) return 0;
    return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr) {
    if(pArr == NULL || pArr->pElemArr == NULL) return;
    for(int i = 0; i < pArr->ArrSize; i++) {
        if(pArr->pElemArr[i]) pArr->printFunc(pArr->pElemArr[i]);
    }
}