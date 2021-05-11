 int insert(int key)
    {
        int index = 0;
        for (int i = 0; i < size; i++)
        {
            index = this->hp(key, i);
            if (index < this->size && status[index] == NIL)
            {
                this->data[index] = key;
                this->status[index] = NON_EMPTY;
                break;
            }
            else if (index >= this->size)
                throw "Overflow!";
        }
        return index;
    }

    void remove(int key)
    {
        int k = this->search(key);
        this->data[k] = 0;
        this->status[k] = DELETED;
    }

    int search(int key)
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->data[i] == key)
                return i;
        }
        return -1;
    }