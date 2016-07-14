#ifndef SPARSE_VECTOR_H
#define SPARSE_VECTOR_H
#include <iostream>
using namespace std;
template <class T>
class sparse_vector
{
private:
    typedef struct node{
        T value;
        int index;
        node* next;
        node(T value,int index):value(value),index(index){
            next = nullptr;
        }
        node(T value,int index,node* next):value(value),index(index),next(next){
            next = nullptr;
        }
    }Node;

    Node *root;
    T standard;
public:
    sparse_vector(T standard):standard(standard){
        root = nullptr;
    }
    void set(int index, T x){
        if(index < 0)
            return;

        if(this->root == nullptr){
            if(x == this->standard)
                return;
            root = new Node(x,index);
        }else{
            Node *node,*backup;
            node = backup = root;
            while(node != nullptr && node->index < index){
                cout<<"lkjdsf\n";
                backup = node;
                node = node->next;
            }
            if(node == nullptr){
                if(x == this->standard )
                    return;
                backup->next = new Node(x,index);
            }else if(node->index == index){
                if(x == this->standard){
                    backup->next = node->next;
                    delete (node);
                }else{
                    node->value = x;
                }
            }else{
                if(x == this->standard )
                    return;
                if(node == this->root)
                    this->root = new Node(x,index,node);
                else
                    backup->next = new Node(x,index,node);
            }

        }

    }

    T get(int index){
        Node *node = this->root;
        while(node != nullptr && node->index < index)
            node = node->next;
        if(node == nullptr || node->index > index){
            return this->standard;
        }else{
            return node->value;
        }
    }

    int find(T x){
        Node* node = this->root;
        while(node != nullptr && node->value != x)
            node = node->next;
        if(node != nullptr)
            return node->index;
        else
            return -1;
    }

};

#endif // SPARSE_VECTOR_H
