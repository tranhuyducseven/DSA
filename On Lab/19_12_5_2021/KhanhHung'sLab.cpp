#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class K, class D, int M> // K: key, D: data, M: degree of BTree
class BTree {
    /// Convention: Left sub-tree < Root's key <= Right sub-tree

public:
    class Entry;
    class Node;

private:
    Node *root;

public:
    BTree() : root(0) {};
    ~BTree() {}
    ///////////////////////////////////////////////////
    ///             CLASS `Entry`                   ///
    ///////////////////////////////////////////////////
public:
    class Entry {
    private:
        K key;
        D data;
        Node *rightPtr;

        friend class BTree<K, D, M>;

    public:
        Entry(K key = K{}, D value = D{}) : key(key), data(value), rightPtr(0) {}
        ~Entry() {}
        string toString() {
            stringstream ss;
            ss << "<"
                   << this->key << ","
                   << this->data
                   << ">";
            return ss.str();
        }
    };

    ///////////////////////////////////////////////////
    ///             CLASS `Node`                    ///
    ///////////////////////////////////////////////////
public:
    class Node {
    private:
        Node *firstPtr;
        int numEntries;
        Entry entries[M - 1];

        friend class BTree<K, D, M>;

    public:
        Node() : firstPtr(0), numEntries(0) {};

        ~Node() { }
        string toString() {
            // hidden code
            stringstream ss;
            ss << "[" << "(" << numEntries << ")";
            for (int i = 0; i < numEntries; i++)
                ss << entries[i].toString();
            ss << "]";
            return ss.str();
        }
        bool isFull() {
            return (numEntries >= M - 1);
        }
    };

    /////////////////////////////////////////////////////////////
    ///         CLASS `BTree`: method implementation          ///
    /////////////////////////////////////////////////////////////
public:
    /// toStringPreOrder()
    void toStringPreOrderRec(Node *head, string &res)
    {
        if (head != NULL)
        {
            res = res + head -> toString() + " ";
            toStringPreOrderRec(head -> firstPtr, res);
            for (int i = 0; i < head->numEntries; i++)
                toStringPreOrderRec(head->entries[i].rightPtr, res);
        }
    }
    string toStringPreOrder() 
    {
        string res = "";
        toStringPreOrderRec(root, res);
        return res;
    }
    /// BEGIN STUDENT CODE
    /// =====================================================
    
    /// Proposal methods from slides
    /// Feel free to use them,
    ///     or delete them and implement your own helping methods
    void insertEntry(Node *pNode, int entryIdx, const Entry &newEntry) 
    {
        int shifter = pNode -> numEntries;
        while (shifter > entryIdx)
        {
            pNode -> entries[shifter] = pNode -> entries[shifter-1];
            shifter--;
        }
        pNode -> entries[shifter] = newEntry;
    }
    
    void splitNode(Node *pNode, int entryIdx, Entry &upEntry, int newEntryLow) 
    {
        int minEntries = M / 2;     
        int fromIdx;
        Node *rightPtr = new Node();
        if (entryIdx < minEntries) 
            fromIdx = minEntries;
        else 
            fromIdx = minEntries + 1;
        int toIdx = 0;
        rightPtr -> numEntries = pNode -> numEntries - fromIdx;
        while (fromIdx < pNode->numEntries)
            rightPtr->entries[toIdx++] = pNode->entries[fromIdx++];
        pNode -> numEntries -= rightPtr -> numEntries;
    
        if (entryIdx < minEntries)
        {
            if (newEntryLow) 
                insertEntry(pNode, entryIdx, upEntry);
            else 
                insertEntry(pNode, entryIdx+1, upEntry);
        } 
        else 
        {
            insertEntry(rightPtr, entryIdx - minEntries, upEntry);
            rightPtr -> numEntries = rightPtr -> numEntries + 1;
            pNode -> numEntries = pNode -> numEntries - 1; 
        }
        upEntry.data = pNode -> entries[minEntries].data;
        upEntry.key = pNode -> entries[minEntries].key;
        upEntry.rightPtr = rightPtr;
        rightPtr -> firstPtr = pNode -> entries[minEntries].rightPtr;
    
    }
    
    int searchNode(Node *nodePtr, K key) 
    {
        int walker = 0;
        if (key < nodePtr->entries[0].key)
            walker = 0;
        else 
        {
            walker = nodePtr->numEntries-1;
            while (walker > 0 && key < nodePtr->entries[walker].key) 
                walker--;
        }
        return walker;
    }
    
    bool insertNode(Node *&root, const K &key, const D &data, Entry &upEntry) 
    {
        bool taller;
        if (root == NULL)
        {
            upEntry.key = key;
            upEntry.data = data;
            taller = true;
            return true;
        }
        int entryIdx = searchNode(root, key);
        int newEntryLow = key < root->entries[entryIdx].key;
        Node *subTree = new Node();
        if (entryIdx == 0 && newEntryLow)
            subTree = root->firstPtr;
        else 
            subTree = root->entries[entryIdx].rightPtr;
    
        taller = insertNode(subTree, key, data, upEntry);
        if (taller)
        {
            if (root->isFull())
            {
                splitNode(root, entryIdx, upEntry, newEntryLow);       
                taller = true;
            }
            else 
            {
                if (newEntryLow) 
                    insertEntry(root, entryIdx, upEntry);
                else 
                    insertEntry(root, entryIdx+1, upEntry);
                root->numEntries++;
                taller = false;
            }
    
        }
        return taller;
    }
    
    void insert(Node *&root, const K &key, const D &data) {
    
    }
    
    /// TODO: Implement following method
    void insert(const K &key, const D &data) 
    {
        if (root == NULL)
        {
            root = new Node();
            Entry tmp = Entry(key, data);
            root -> entries[0] = tmp;
            root -> numEntries = 1;
        }
        else {
            Entry upEntry;
            bool taller = insertNode(root, key, data, upEntry);
    
            if (taller == true)
            {
                Node *newPtr = new Node();
                newPtr -> entries[0] = upEntry;
                newPtr -> firstPtr = root;
                newPtr -> numEntries = 1;
                root = newPtr;
            }
        }
    }
    
    /// END STUDENT CODE
};

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};
void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}
void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
    public:
        class Node;
    private:
        Node *root;
    protected:
        int getHeightRec(Node *node)
        {
            if (node == NULL)
                return 0;
            int lh = this -> getHeightRec(node -> pLeft);
            int rh = this -> getHeightRec(node -> pRight);
            return (lh > rh ? lh : rh) + 1;
        }
    public:
        AVLTree() : root(nullptr) {}
        ~AVLTree(){}
        int getHeight()
        {
            return this->getHeightRec(this->root);
        }
        void printTreeStructure()
        {
            int height = this->getHeight();
            if (this->root == NULL)
            {
                cout << "NULL\n";
                return;
            }
            queue<Node *> q;
            q.push(root);
            Node *temp;
            int count = 0;
            int maxNode = 1;
            int level = 0;
            int space = pow(2, height);
            printNSpace(space / 2);
            while (!q.empty())
            {
                temp = q.front();
                q.pop();
                if (temp == NULL)
                {
                    cout << " ";
                    q.push(NULL);
                    q.push(NULL);
                }
                else
                {
                    cout << temp->data;
                    q.push(temp->pLeft);
                    q.push(temp->pRight);
                }
                printNSpace(space);
                count++;
                if (count == maxNode)
                {
                    cout << endl;
                    count = 0;
                    maxNode *= 2;
                    level++;
                    space /= 2;
                    printNSpace(space / 2);
                }
                if (level == height)
                    return;
            }
        }
        
        int diff(Node *root) 
        {
            int lh = getHeightRec(root -> pLeft);
            int rh = getHeightRec(root -> pRight);
            return lh - rh;
        }
        
        Node *ror(Node *p) 
        {
            Node *x = p -> pRight;
            p -> pRight = x -> pLeft;
            x -> pLeft = p;
            return x;
        }
        
        Node *lol(Node *p) 
        {
            Node *x = p -> pLeft;
            p -> pLeft = x -> pRight;
            x -> pRight = p;
            return x;
        }
        
        Node *lor(Node *p) 
        {
            Node *x = p -> pRight;
            p -> pRight = lol(x);
            return ror(p);
        }
        
        Node *rol(Node *p) 
        {
            Node *x = p -> pLeft;
            p -> pLeft = ror(x);
            return lol(p);
        }
        
        Node *balance(Node *x) 
        {
            int different = diff(x);
            if (different > 1) 
            {
                if (diff(x -> pLeft) > 0) 
                    x = lol(x);
                else 
                    x = rol(x);
            } 
            else if (different < -1) 
            {
                if (diff(x -> pRight) > 0)
                    x = lor(x);
                else 
                    x = ror(x);
            }
            return x;
        }
        Node *add(Node *root,const T &value) 
        {
            if (root == NULL) 
            {
                root = new Node(value);
                return root;
            }
            if (value < root -> data) 
            {
                root -> pLeft = add(root -> pLeft, value);
                root = balance(root);
            } 
            else 
            {
                root -> pRight = add(root -> pRight,value);
                root = balance(root);
            }
            return root;
        }
        void insert(const T &value)
        {
            root = add(root, value);
        }
        
        T findMaxLeft(Node *head)
        {
            if (head -> pRight == NULL) 
                return head -> data;
            else 
                return findMaxLeft(head -> pRight);
        }
    
        T findMinRight(Node *head)
        {
            if (head -> pLeft == NULL) 
                return head -> data;
            else 
                return findMinRight(head -> pLeft);
        }
    
        Node *removeRec(Node *head, T value)
        {
            if (head == NULL)
                return head;
        
            if (head -> data == value)
            {
                if (head -> pLeft == NULL && head -> pRight == NULL) 
                {
                    delete head;
                    return NULL;
                }
                else if (head -> pLeft != NULL && head->pRight == NULL)
                {
                    T maxLeft = findMaxLeft(head -> pLeft);
                    head -> data = maxLeft;
                    head -> pLeft = removeRec(head -> pLeft, maxLeft);
                }
                else if (head -> pRight != NULL && head -> pLeft == NULL)
                {
                    T minRight = findMinRight(head -> pRight);
                    head -> data = minRight;
                    head -> pRight = removeRec(head -> pRight, minRight);
                }
                else 
                {
                    T maxLeft = findMaxLeft(head -> pLeft);
                    head -> data = maxLeft;
                    head -> pLeft = removeRec(head -> pLeft, maxLeft);
                }
            }
            else if (head -> data < value) 
                head -> pRight = removeRec(head -> pRight, value);
            else 
                head -> pLeft = removeRec(head -> pLeft, value);
            
    
            int lech = diff(head);
            if (lech > 1)
            {
                if (diff(head -> pLeft) > 0) 
                    head = lol(head);
                else 
                    head = rol(head);
            }
            else if (lech < -1)
            {
                if (diff(head -> pRight) > 0) 
                    head = lor(head);
                else 
                    head = ror(head);
            }
            
            return head;
        }

        void remove(const T &value)
        {
            root = removeRec(root, value);
        }
        
        class Node
        {
            private:
                T data;
                Node *pLeft, *pRight;
                BalanceValue balance;
                friend class AVLTree<T>;
            public:
                Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
                ~Node() {}
        };
};


int main()
{
    BTree<int, int, 3> bTree;
    int keys[] = {9, 21, 14};
    int size = sizeof(keys) / sizeof(int);
    for (int idx = 0; idx < size; idx++) {
        bTree.insert(keys[idx], idx);
    }
    cout << bTree.toStringPreOrder() << endl;

}




