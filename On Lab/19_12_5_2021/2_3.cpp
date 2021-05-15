/**In this question, you have to perform add on AVL tree. Note that:

- When adding a node which has the same value as parent node, add it in the pRight sub tree.

Your task is to implement function: insert. You could define one or more functions to achieve this task.**/

#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

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

template <class T>
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
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}
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

    Node *rotateRight(Node *&node)
    {
        Node *pLeftTree = node->pLeft;
        node->pLeft = pLeftTree->pRight;
        pLeftTree->pRight = node;
        return pLeftTree;
    }
    Node *rotateLeft(Node *&node)
    {
        Node *pRightTree = node->pRight;
        node->pRight = pRightTree->pLeft;
        pRightTree->pLeft = node;
        return pRightTree;
    }
    Node *LeftBalance(Node *&node, bool &taller)
    {
        if (node->pLeft->balance == LH)
        {
            node->pLeft->balance = EH;
            node->balance = EH;
            node = rotateRight(node);
            taller = false;
        }
        else
        {
            if (node->pLeft->pRight->balance == EH)
            {
                node->balance = EH;
                node->pLeft->balance = EH;
                node->pLeft->pRight->balance = EH;
            }
            else if (node->pLeft->pRight->balance == LH)
            {
                node->balance = RH;
                node->pLeft->balance = EH;
                node->pLeft->pRight->balance = EH;
            }
            else
            {
                node->balance = EH;
                node->pLeft->balance = LH;
                node->pLeft->pRight->balance = EH;
            }
            node->pLeft = rotateLeft(node->pLeft);
            node = rotateRight(node);
            taller = false;
        }
        return node;
    }
    Node *RightBalance(Node *&node, bool &taller)
    {
        if (node->pRight->balance == RH)
        {
            node->pRight->balance = EH;
            node->balance = EH;
            node = rotateLeft(node);
            taller = false;
        }
        else
        {
            if (node->pRight->pLeft->balance == EH)
            {
                node->balance = EH;
                node->pRight->balance = EH;
                node->pRight->pLeft->balance = EH;
            }
            else if (node->pRight->pLeft->balance == RH)
            {
                node->balance = LH;
                node->pRight->balance = EH;
                node->pRight->pLeft->balance = EH;
            }
            else if (node->pRight->pLeft->balance == LH)
            {
                node->balance = EH;
                node->pRight->balance = RH;
                node->pRight->pLeft->balance = EH;
            }

            node->pRight = rotateRight(node->pRight);
            node = rotateLeft(node);
            taller = false;
        }
        return node;
    }
    Node *insertRec(Node *&node, const T &value, bool &taller)
    {
        if (node == nullptr)
        {
            taller = true;
            return new Node(value);
        }
        if (value < node->data)
        {
            node->pLeft = insertRec(node->pLeft, value, taller);
            if (taller)
            {
                if (node->balance == LH)
                {
                    node = LeftBalance(node, taller);
                }
                else if (node->balance == EH)
                {
                    node->balance = LH;
                }
                else
                {
                    node->balance = EH;
                    taller = false;
                }
            }
        }
        else
        {
            node->pRight = insertRec(node->pRight, value, taller);
            if (taller)
            {
                if (node->balance == LH)
                {
                    node->balance = EH;
                    taller = false;
                }
                else if (node->balance == EH)
                {
                    node->balance = RH;
                }
                else
                {
                    node = RightBalance(node, taller);
                }
            }
        }
        return node;
    }
    void insert(const T &value)
    {
        bool taller = false;
        this->root = insertRec(this->root, value, taller);
    }
    Node *removeRightBalance(Node *&r, bool &isShorter)
    {
        if (r->balance == LH)
        {
            r->balance = EH;
        }
        else if (r->balance == EH)
        {
            r->balance = RH;
            isShorter = false;
        }
        else
        {
            if (r->pRight->balance == RH)
            {
                r->balance = EH;
                r->pRight->balance = EH;
                r = rotateLeft(r);
            }
            else if (r->pRight->balance == EH)
            {
                r->balance = RH;
                r->pRight->balance = LH;
                isShorter = false;
                r = rotateLeft(r);
            }
            else
            {
                Node *rRight = r->pRight;
                if (rRight->pLeft->balance == RH)
                {
                    r->balance = LH;
                    rRight->balance = EH;
                    rRight->pLeft->balance = EH;
                }
                else if (rRight->pLeft->balance == LH)
                {
                    r->balance = EH;
                    rRight->balance = RH;
                    rRight->pLeft->balance = EH;
                }
                else
                {
                    r->balance = EH;
                    rRight->balance = EH;
                    rRight->pLeft->balance = EH;
                }
                r->pRight = rotateRight(r->pRight);
                r = rotateLeft(r);
            }
        }
        return r;
    }
    Node *removeLeftBalance(Node *&r, bool &isShorter)
    {
        if (r->balance == RH)
        {
            r->balance = EH;
        }
        else if (r->balance == EH)
        {
            r->balance = LH;
            isShorter = false;
        }
        else
        {
            if (r->pLeft->balance == LH)
            {
                r->balance = EH;
                r->pLeft->balance = EH;
                r = rotateRight(r);
            }
            else if (r->pLeft->balance == EH)
            {
                r->balance = LH;
                r->pLeft->balance = RH;
                isShorter = false;
                r = rotateRight(r);
            }
            else
            {
                Node *rLeft = r->pLeft;
                if (rLeft->pRight->balance == LH)
                {
                    r->balance = RH;
                    rLeft->balance = EH;
                    rLeft->pRight->balance = EH;
                }
                else if (rLeft->pRight->balance == RH)
                {
                    r->balance = EH;
                    rLeft->balance = LH;
                    rLeft->pRight->balance = EH;
                }
                else
                {
                    r->balance = EH;
                    rLeft->balance = EH;
                    rLeft->pRight->balance = EH;
                }
                r->pLeft = rotateLeft(r->pLeft);
                r = rotateRight(r);
            }
        }
        return r;
    }

    void remove(const T &value)
    {
        bool isShorter = false;
        root = removeRec(root, value, isShorter);
    }
    Node *removeRec(Node *&r, const T &value, bool &isShorter)
    {
        if (r == nullptr)
        {
            isShorter = false;
            return r;
        }
        else
        {
            if (value < r->data)
            {
                r->pLeft = removeRec(r->pLeft, value, isShorter);
                if (isShorter)
                {
                    r = removeRightBalance(r, isShorter);
                }
                return r;
            }
            else if (value > r->data)
            {
                r->pRight = removeRec(r->pRight, value, isShorter);
                if (isShorter)
                {
                    r = removeLeftBalance(r, isShorter);
                }
                return r;
            }
            else
            {
                if (r->pLeft == nullptr)
                {
                    Node *newRoot = r->pRight;
                    isShorter = true;
                    delete r;
                    return newRoot;
                }
                else if (r->pRight == nullptr)
                {
                    Node *newRoot = r->pLeft;
                    isShorter = true;
                    delete r;
                    return newRoot;
                }
                else
                {
                    Node *rightMinLeaf = r->pRight;
                    while (rightMinLeaf->pLeft != nullptr)
                    {
                        rightMinLeaf = rightMinLeaf->pLeft;
                    }
                    r->data = rightMinLeaf->data;
                    r->pRight = removeRec(r->pRight, rightMinLeaf->data, isShorter);
                    if (isShorter)
                    {
                        r = removeLeftBalance(r, isShorter);
                    }
                }
                return r;
            }
        }
    }
    void printInorder()
    {
        return printLNR(this->root);
    }
    void printLNR(Node *node)
    {
        if (node != nullptr)
        {
            printLNR(node->pLeft);
            cout << node->data << " ";
            printLNR(node->pRight);
        }
    }
    void searchRec(Node *node, const T &value, bool &isFound)
    {
        if (node != nullptr)
        {
            if (node->data == value)
                isFound = true;
            else if (node->data > value)
                searchRec(node->pLeft, value, isFound);
            else
                searchRec(node->pRight, value, isFound);
        }
    }
    bool search(const T &value)
    {
        bool isFound = false;
        searchRec(this->root, value, isFound);
        return isFound;
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
    AVLTree<int> avl;
    int arr[] = {10, 52, 98, 32, 68, 92, 40, 13, 42, 63, 99, 100};
    for (int i = 0; i < 12; i++)
    {
        avl.insert(arr[i]);
    }
    avl.printInorder();
    cout << endl;
    cout << avl.search(10);
}
