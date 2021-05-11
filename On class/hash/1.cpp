  void insert(int key)
    {
        int index = this->hash(key);
        this->data[index].push_back(key);
    }

    void remove(int key)
    {
        int index = this->hash(key);
        if (this->search(key))
            this->data[index].remove(key);
        else
            cout << "Not found!";
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