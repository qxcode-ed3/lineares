#ifndef SPARSE_VECTOR_H
#define SPARSE_VECTOR_H
#include <iostream>
#include <list>
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
    void set(unsigned int index, T x){
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

    T get(unsigned int index) const{
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

    class pos_ref{
        friend class sparse_vector;
        sparse_vector &sv;
        unsigned int index;
    public:
        pos_ref(sparse_vector &sv, unsigned int index):sv(sv), index(index){}

        pos_ref& operator=(T value){
            sv.set(index,value);
            return *this;
        }

        bool operator==(T value){
            return sv.get(index)==value;
        }

        bool operator!=(T value){
            return !operator==(value);
        }

        operator T()const{
            return sv.get(index);
        }
    };

    T operator[](unsigned int idx) const{
        return this->get(idx);
    }

    pos_ref operator [](unsigned int idx) {
        return pos_ref(*this,idx);
    }

    struct iterator{
        bool operator==(iterator other){

        }
    };
};

#endif // SPARSE_VECTOR_H
