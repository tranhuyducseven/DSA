#include <iostream>
using namespace std;
#include <list>
class ChainingHash
{
private:
    int (*hash)(int);
    list<int> *data;
    int size;

public:
    ChainingHash()
    {
        throw "Cannot create a hash with no hash function!";
    }

    ChainingHash(int size, int (*hash)(int))
    {
        this->hash = hash;
        this->size = size;
        this->data = new list<int>[size];
    }
    int count()
    {
        int total = 0;
        for (int i = 0; i < this->size; i++)
        {
            total += this->data[i].size();
        }
        return total;
    }

    void dump()
    {
        for (int i = 0; i < this->size; i++)
        {
            cout << "Slot " << i << ": " << this->data[i].size() << " element(s)" << endl;
        }
    }
    void insert(int key)
    {
        int index = this->hash(key);
        this->data[index].push_front(key);
    }

    void remove(int key)
    {
        int index = this->hash(key);
        for (list<int>::iterator it = this->data[index].begin(); it != this->data[index].end(); ++it)
        {
            if (*it == key)
            {
                this->data[index].erase(it);
                return;
            }
        }
        throw "Not found!";
    }

    bool search(int key)
    {
        int index = this->hash(key);
        for (list<int>::iterator it = this->data[index].begin(); it != this->data[index].end(); ++it)
        {
            if (*it == key)
                return true;
        }
        return false;
    }
};

int hashWith11(int key)
{
    return key % 11;
}
int hashWith15(int key)
{
    return key % 15;
}
int hashWith17(int key)
{
    return key % 17;
}
int main()
{

    ChainingHash *hashTable = new ChainingHash(11, hashWith11);
    int data[] = {28, 81, 55, 92, 33, 29, 18, 23, 40, 99, 79, 74, 49, 64, 17};
    int size = sizeof(data) / sizeof(int);
    for (int i = 0; i < size; i++)
    {
        hashTable->insert(data[i]);
    }

    int indices[] = {1, 5, 7};
    int indicesSize = sizeof(indices) / sizeof(int);
    for (int i = 0; i < indicesSize; i++)
    {
        hashTable->remove(data[indices[i]]);
    }

    hashTable->dump();
}