//In this question, you have to perform delete on AVL tree. Note that:

// - Provided insert function already.

// Your task is to implement two functions: remove. You could define one or more functions to achieve this task.

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
        Node *leftTree = node->pLeft;
        node->left = leftTree->right;
        leftTree->right = node;
        return leftTree;
    }
    Node *rotateLeft(Node *&node)
    {
        Node *rightTree = node->right;
        node->right = rightTree->left;
        rightTree->left = node;
        return rightTree;
    }
    //delete
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
        //Helping functions
    }
};
int main()
{
    AVLTree<int> avl;
    int arr[] = {10, 52, 98, 32, 68, 92, 40, 13, 42, 63};
    for (int i = 0; i < 10; i++)
    {
        avl.insert(arr[i]);
    }
    avl.remove(10);
    avl.printTreeStructure();
    return 0;
}