#include <iostream>
using namespace std;
enum STATUS_TYPE
{
    NIL,
    NON_EMPTY,
    DELETED
};
class OpenHash
{
private:
    int (*hp)(int, int);
    STATUS_TYPE *status;
    int *data;
    int size;

public:
    OpenHash()
    {
        throw "Cannot create a hash with no hash function!";
    }

    OpenHash(int size, int (*hp)(int, int))
    {
        this->hp = hp;
        this->size = size;
        this->data = new int[size];
        this->status = new STATUS_TYPE[size];
        for (int i = 0; i < size; i++)
        {
            this->status[i] = NIL;
        }
    }

    int insert(int key)
    {
        //18/5/2021 12:08
        int j = 0;
        int i = 0;
        while (i < this->size)
        {
            j = this->hp(key, i);
            if (j < size && (this->status[j] == NIL || this->status[j] == DELETED))
            {
                this->data[j] = key;
                this->status[j] = NON_EMPTY;
                return j;
            }
            else
                i += 1;
        }
        throw "Not Found!";
        return -1;
    }

    void remove(int key)
    {
        int k = this->search(key);
        if (k == -1)
            throw "Not Found!";
        else
            this->status[k] = DELETED;
    }

    int search(int key)
    {
        int j = 0;
        int i = 0;
        do
        {
            j = this->hp(key, i);
            if (this->data[j] == key && this->status[j] == NON_EMPTY)
                return j;
            i += 1;
        } while (this->status[j] != NIL && i < this->size);
        return -1;
    }

    void dump()
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->status[i] != NON_EMPTY)
                cout << "Slot " << i << ": Empty" << endl;
            else
                cout << "Slot " << i << ": " << this->data[i] << endl;
        }
    }
};

int linearProbing(int key, int i)
{
    return ((key % 11) + i) % 11;
}

int quadraticProbing(int key, int i)
{
    return ((key % 11) + i + 3 * i * i) % 11;
}

int doubleHashing(int key, int i)
{
    int h1 = key % 11;
    int h2 = 1 + (key % 10);
    return (h1 + i * h2) % 11;
}

int main()
{

    OpenHash *hashTable = new OpenHash(11, doubleHashing);
    int data[] = {10, 22, 31, 4, 15, 28, 17, 88, 59};
    int size = sizeof(data) / sizeof(int);

    for (int i = 0; i < size; i++)
    {
        hashTable->insert(data[i]);
    }

    hashTable->remove(22);
    hashTable->dump();
}