#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class Heap {
protected:
    T* elements;
    int capacity;
    int count;
public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete[]elements;
    }
    void push(T item);
    
    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();
    
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }
private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};

template<class T>
int Heap<T>::size()
{
    return this->count;
}

template<class T>
bool Heap<T>::isEmpty()
{
    return (this->count == 0);
}

template<class T>
T Heap<T>::peek()
{
    return (this->count == 0) ? -1 : elements[0];
}

template<class T>
bool Heap<T>::contains(T item)
{
    for (int i = 0; i < this->count; i++)
    {
        if (elements[i] == item) 
            return true;
    }
    return false;
}

template<class T>
bool Heap<T>::pop()
{
    if (isEmpty()) 
        return false;
    else 
    {
        elements[0] = elements[count - 1];
        count--;
        reheapDown(0);
        return true;
    }
}

template<class T>
int Heap<T>::getItem(T item) 
{
    // TODO: return the index of item in heap
    for (int i = 0; i < count; i++) 
    {
        if (elements[i] == item) 
            return i;
    }
    return -1;
}

template<class T>
void Heap<T>::remove(T item) 
{
    // TODO: remove the element with value equal to item
    int index = getItem(item);
    T temp = elements[index];
    elements[index] = elements[count - 1];
    elements[count - 1] = temp;
    count--;
    reheapDown(index);
}

template<class T>
void Heap<T>::clear() 
{
    // TODO: delete all elements in heap
    delete[] elements;
    capacity = 10;
    elements = new T[capacity];
    count = 0;
}

template<class T>
void Heap<T>::push(T item)
{
    ensureCapacity(count);
    elements[count] = item;
    count++;
    reheapUp(count - 1);
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity)
{
    minCapacity++;
    if (minCapacity > this->capacity) 
    {
        this->capacity = minCapacity * 3 / 2;
        T* temp = new T[capacity];
        memmove(temp, elements, capacity * sizeof(T));
        delete[] elements;
        elements = temp;
    }
}

template<class T>
void Heap<T>::reheapUp(int position)
{
    int parent = (position - 1) / 2;
    while (position > 0 && position < count) 
    {
        if (elements[position] > elements[parent])
            swap(elements[position], elements[parent]);
        position = parent;
        parent = (position - 1) / 2;
    }
}

void reheapDown(int maxHeap[], int numberOfElements, int index)
{
    int finalInnerNode = (numberOfElements / 2) - 1;		
	while (index <= finalInnerNode) 
	{	
		int leftChild = ((2 * index + 1) < numberOfElements) ? (2 * index + 1) : -1;
		int rightChild = ((2 * index + 2) < numberOfElements) ? (2 * index + 2) : -1;
		int maxChild;
		if (rightChild == -1)			
			maxChild = leftChild;				
		else
			maxChild = (maxHeap[leftChild] >= maxHeap[rightChild]) ? leftChild : rightChild;
		if (maxHeap[maxChild] > maxHeap[index])
			swap(maxHeap[maxChild], maxHeap[index]);
		index = maxChild;
	}
}

void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    int parent = (index - 1) / 2;
	while (index > 0 && index < numberOfElements) 
	{
		if (maxHeap[index] > maxHeap[parent])
			swap(maxHeap[index], maxHeap[parent]);
		index = parent;
		parent = (index - 1) / 2;
	}
}

template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    
    static void reheapDown(T *start, T*end, int n, int i)
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && start[l] > start[largest]) 
            largest = l;
        if (r < n && start[r] > start[largest]) 
            largest = r;
        if (largest != i)
        {
            swap(start[i], start[largest]);
            reheapDown(start, end, n, largest);
        }
    }
    static void heapSortRec(T *start, T *end)
    {
        int size = end-start;
        int tmp = (size / 2) - 1;
        for (int i = tmp; i >= 0; i--)
            reheapDown(start, end, size, i);
        for (int i = size - 1; i > 0; i--)
        {
            swap(start[i], start[0]);
            reheapDown(start, end, i, 0);
        }
    }
    static void heapSort(T* start, T* end){
        //TODO
        heapSortRec(start, end);
        Sorting<T>::printArray(start,end);
    }
    
};


struct player {
	int index;
	int key;
};

void reheapUp(player minHeap[], int numberOfElements, int index)
{
	int father = (index - 1) / 2;
	while (index > 0 && index < numberOfElements) 
	{
		if (minHeap[index].key < minHeap[father].key)
			swap(minHeap[index], minHeap[father]);
		index = father;
		father = (index - 1) / 2;
	}
}

void reheapDown(player minHeap[], int numberOfElements, int index)
{
	int finalInnerNode = (numberOfElements / 2) - 1;		
	while (index <= finalInnerNode) 
	{						
		int leftChild = ((2 * index + 1) < numberOfElements) ? (2 * index + 1) : -1;
		int rightChild = ((2 * index + 2) < numberOfElements) ? (2 * index + 2) : -1;
		int minChild;
		if (rightChild == -1) 	
			minChild = leftChild;
		else
			minChild = (minHeap[leftChild].key >= minHeap[rightChild].key) ? rightChild : leftChild;
		if (minHeap[minChild].key < minHeap[index].key)
			swap(minHeap[minChild], minHeap[index]);
		index = minChild;
	}
}

void pop(player* minHeap, int& numberOfElements) 
{
	swap(minHeap[0], minHeap[numberOfElements - 1]);
	numberOfElements--;
	reheapDown(minHeap, numberOfElements, 0);
}

int findCostumer(int n, int* arrvalTime, int time) {
	for (int i = 0; i < n; i++) 
	{
		if (arrvalTime[i] == time) 
		    return i;
	}
	return -1;
}

int minWaitingTime(int n, int arrvalTime[], int completeTime[]) 
{
	// YOUR CODE HERE
	int time = 0, cumWaitingTime = 0, working = 0;
	int served = 0;
	for (int i = 0; i < n - 1; i++) 
	{
		for (int j = 0; j < n - i - 1; j++) 
		{
			if (arrvalTime[j] > arrvalTime[j + 1]) 
			{
				int temp = arrvalTime[j];
				arrvalTime[j] = arrvalTime[j + 1];
				arrvalTime[j + 1] = temp;

				int temp2 = completeTime[j];
				completeTime[j] = completeTime[j + 1];
				completeTime[j + 1] = temp2;
			}
		}
	}

	player* heap = new player[n];
	int heapSize = 0;

	int indexTime = 0;
	time = arrvalTime[0];
	
	while (served < n) 
	{
		while ((heapSize == 0 || time >= arrvalTime[indexTime]) && indexTime < n) 
		{
			heap[heapSize].key = completeTime[indexTime];
			heap[heapSize].index = indexTime;
			heapSize++;
			indexTime++;
			reheapUp(heap, heapSize, heapSize - 1);
		}
		if (heapSize > 0) 
		{
			working = heap[0].key;
			if (time > arrvalTime[heap[0].index])
				cumWaitingTime = cumWaitingTime + time - arrvalTime[heap[0].index] + working;
			else 
			{
				time = arrvalTime[heap[0].index];
				cumWaitingTime = cumWaitingTime + time - arrvalTime[heap[0].index] + working;
			}
			served++;
			pop(heap, heapSize);
		}
		time += working;
	}
	delete[] heap;
	return cumWaitingTime;
}

int main()
{
    int n = 4; 
    int arrvalTime[] = { 0, 4, 2, 5 };
    int completeTime[] = { 4, 2, 3, 4 };
    
    cout << minWaitingTime(n, arrvalTime, completeTime);
}
