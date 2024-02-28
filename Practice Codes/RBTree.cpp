#include <iostream>

using namespace std;

class Node
{
public:
    int val;
    char color; // 'b' - black 'r' - red
    // All null leaves are considered black
    Node *left;
    Node *right;
    Node *parent;

public:
    Node(int val, char color)
    {
        this->color = color;
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }
};

class RBTree
{
private:
    Node *root;

public:
    RBTree()
    {
        this->root = nullptr;
    }

    void insert(int val)
    {
        if (this->root == nullptr)
        {
            Node *foo = new Node(val, 'b');
            this->root = foo;
            return;
        }
        Node *foo = new Node(val, 'r');
        Node *temp = root;
        Node *temp2 = nullptr;
        while (temp != nullptr && temp->val != val)
        {
            temp2 = temp;
            if (temp->val > val)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        foo->parent = temp2;
        if (foo->val < temp2->val)
        {
            temp2->left = foo;
        }
        else
        {
            temp2->right = foo;
        }
        insertFix(foo);
    }

    void leftRotate(Node *p)
    {
        if (p->right == nullptr)
        {
            return;
        }
        else
        {
            Node *y = p->right;

            if (y->left != NULL)
            {
                p->right = y->left;
                y->left->parent = p;
            }
            else
            {
                p->right = nullptr;
            }

            if (p->parent != nullptr)
                y->parent = p->parent;
            if (p->parent == nullptr)
            {
                root = y;
            }
            else
            {
                if (p == p->parent->left)
                    p->parent->left = y;
                else
                    p->parent->right = y;
            }
            y->left = p;
            p->parent = y;
        }
    }

    void rightRotate(Node *p)
    {
        if (p->left == nullptr)
            return;
        else
        {
            Node *y = p->left;
            if (y->right != nullptr)
            {
                p->left = y->right;
                y->right->parent = p;
            }
            else
                p->left = nullptr;
            if (p->parent != nullptr)
                y->parent = p->parent;
            if (p->parent == nullptr)
                root = y;
            else
            {
                if (p == p->parent->left)
                    p->parent->left = y;
                else
                    p->parent->right = y;
            }
            y->right = p;
            p->parent = y;
        }
    }

    void insertFix(Node *foo)
    {
        while (foo->parent != nullptr && foo->parent->color == 'r')
        {
            Node *grandpa = foo->parent->parent;
            if (grandpa->left == foo->parent)
            {
                // uncle is right child
                if (grandpa->right != nullptr)
                {
                    Node *uncle = grandpa->right;
                    if (uncle->color == 'r')
                    {
                        foo->parent->color = 'b';
                        uncle->color = 'b';
                        grandpa->color = 'r';
                        foo = grandpa;
                    }
                }
                else
                {
                    if (foo->parent->right == foo)
                    {
                        foo = foo->parent;
                        leftRotate(foo);
                    }
                    foo->parent->color = 'b';
                    grandpa->color = 'r';
                    rightRotate(grandpa);
                }
            }
            else
            {
                // uncle is left child
                if (grandpa->left != NULL)
                {
                    Node *uncle = grandpa->left;
                    if (uncle->color == 'r')
                    {
                        foo->parent->color = 'b';
                        uncle->color = 'b';
                        grandpa->color = 'r';
                        foo = grandpa;
                    }
                }
                else
                {
                    if (foo->parent->left == foo)
                    {
                        foo = foo->parent;
                        rightRotate(foo);
                    }
                    foo->parent->color = 'b';
                    grandpa->color = 'r';
                    leftRotate(grandpa);
                }
            }
        }
    }
};