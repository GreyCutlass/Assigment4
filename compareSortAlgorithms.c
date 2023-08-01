#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void swap(int* firstVar, int* secondVar)
{

	int temp = *firstVar;
	*firstVar = *secondVar;
	*secondVar = temp;

}

void merge(int inputArray[], int left, int midPoint, int right)
{
	int mergeIndex = left, leftIndex = 0, rightIndex = 0;

	int leftSize = midPoint - left + 1;
	int rightSize = right - midPoint;

	int *leftArray = (int*) malloc(sizeof(int) * leftSize);
	extraMemoryAllocated = extraMemoryAllocated + (sizeof(int) * leftSize);
	int *rightArray = (int*) malloc(sizeof(int) * rightSize);
	extraMemoryAllocated = extraMemoryAllocated + (sizeof(int) * rightSize);

	for(int index = 0; index < leftSize; ++index)
		leftArray[index] = inputArray[left + index];
	for(int index = 0; index < rightSize; ++index)
		rightArray[index] = inputArray[midPoint + 1 + index];

	while(leftIndex < leftSize && rightIndex < rightSize)
	{

		if(leftArray[leftIndex] <= rightArray[rightIndex])
		{

			inputArray[mergeIndex] = leftArray[leftIndex];
			++leftIndex;

		}
		else
		{

			inputArray[mergeIndex] = rightArray[rightIndex];
			++rightIndex;

		}

		++mergeIndex;

	}

	while(leftIndex < leftSize)
	{

		inputArray[mergeIndex] = leftArray[leftIndex];
		++mergeIndex;
		++leftIndex;

	}
	while(leftIndex < leftSize)
	{

		inputArray[mergeIndex] = leftArray[leftIndex];
		++mergeIndex;
		++leftIndex;

	}

	free(leftArray);
	free(rightArray);


}

void mergeSort(int pData[], int l, int r)
{
	
	if(l < r)
	{

		int midPoint = (l + r)/2;
		mergeSort(pData, l, midPoint);
		mergeSort(pData, midPoint+1, r);
		merge(pData, l, midPoint, r);


	}

}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	
	for(int index = 0; index < n; ++index)
	{
		int inIndex = index;
		while(inIndex > 0  && pData[inIndex-1] > pData[inIndex])
		{

			swap(&pData[inIndex], &pData[inIndex - 1]);

			inIndex = inIndex - 1;
		}

	}

}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	unsigned short swapOccured = 0;
	for(int outerIndex = n-1; outerIndex >= 0; --outerIndex)
	{

		for(int innerIndex = 0; innerIndex < outerIndex; ++innerIndex)
		{

			if(pData[innerIndex] > pData[innerIndex+1])
			{

				swap(&pData[innerIndex], &pData[innerIndex+1]);
				swapOccured = 1;

			}

		}
		//Takes too long without this
		if(!swapOccured)
		{

			break;

		}

	}

}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int minNumberIndex;

	for(int minIndex = 0; minIndex < n; ++minIndex)
	{	
		minNumberIndex = minIndex;
		for(int rolIndex = minIndex; rolIndex < n; ++rolIndex)
		{

			if(pData[rolIndex] < pData[minNumberIndex])
			{

				minNumberIndex = rolIndex;

			}

		}

		swap(&pData[minIndex], &pData[minNumberIndex]);


	}

}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		for(int index = 0; index < dataSz; ++index) fscanf(inFile, "%d ", *ppData+index);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}