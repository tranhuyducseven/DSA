#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template <class T>
class Heap
{
protected:
    T *elements;
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
        delete[] elements;
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
template <class T>
int Heap<T>::size()
{
    return this->count;
}

template <class T>
bool Heap<T>::isEmpty()
{
    if (this->count == 0)
        return true;
    return false;
}

template <class T>
T Heap<T>::peek()
{
    if (this->count >= 0)
        return this->elements[0];
    return -1;
}

template <class T>
bool Heap<T>::contains(T item)
{
    if (this->count >= 0)
    {
        for (int i = 0; i < this->count; i++)
        {
            if (item == this->elements[i])
                return true;
        }
    }
    return false;
}

template <class T>
bool Heap<T>::pop()
{
    if (this->count >= 0)
    {
        this->elements[0] = this->elements[this->count - 1];
        this->count--;
        reheapDown(0);
        return true;
    }
    return false;
}