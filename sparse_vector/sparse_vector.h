#ifndef SPARSE_VECTOR_H
#define SPARSE_VECTOR_H

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
                backup = node;
                node = node->next;
            }
            if(node == nullptr){
                if(x == this->standard)
                    return;
                backup->next = new Node(x,index);
            }else if(node->index == index){
                if(x == this->standard){
                    if(node==this->root)
                        this->root = node->next;
                    else
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
        sparse_vector::Node* current_node;
        pos_ref(sparse_vector& sv,sparse_vector::Node* node):sv(sv),current_node(node){}
    public:
        pos_ref(sparse_vector &sv, unsigned int index):sv(sv), index(index){current_node = nullptr;}

        pos_ref& operator=(T value){
            if(current_node!=nullptr && value!=sv.standard)
                current_node->value = value;
            sv.set(index,value);
            return *this;
        }

        bool operator==(T value){
            if(current_node!=nullptr)
                return current_node->value == value;
            return sv.get(index)==value;
        }

        bool operator!=(T value){
            return !operator==(value);
        }

        operator T()const{
            if(current_node!=nullptr)
                return current_node->value;
            return sv.get(index);
        }
    };

    T operator[](unsigned int idx) const{
        return this->get(idx);
    }

    pos_ref operator [](unsigned int idx) {
        return pos_ref(*this,idx);
    }

    bool operator!=(sparse_vector other){
        if(standard != other.standard)
            return true;
        Node* this_node = root;
        Node* other_node= other.root;
        while(this_node!=nullptr && other_node!=nullptr){
            if(this_node->index != other_node->index || this_node->value != other_node->value)
                return true;
            this_node = this_node->next;
            other_node = other_node->next;
        }

        if(this_node==nullptr && other_node==nullptr)
            return false;
        else
            return true;
    }

    bool operator ==(sparse_vector other){
        return ! operator!=(other);
    }

   struct iterator{
        unsigned int current_index;
        sparse_vector::Node* current_node;
        sparse_vector* sv;

        pos_ref operator*(){
            if(current_node!=nullptr && current_index==current_node->index)
                return pos_ref(*sv,current_node);
            else
                return pos_ref(*sv,current_index);
        }

        iterator operator++(){
            if(current_node!=nullptr){
                current_index++;
                if(current_index > current_node->index)
                    current_node = current_node->next;
            }
            return *(this);
        }

        bool operator==(iterator other){
            if(current_node == nullptr){
                return (other.current_node == nullptr && sv == other.sv);
            }else
                return (current_index == other.current_index && current_node == other.current_node && sv == other.sv);
        }

        bool operator!=(iterator other){
            return !operator==(other);
        }

        iterator operator++(int){
            iterator copy = *this;
            ++(*this);
            return copy;
        }

   };

   iterator begin(){
       iterator it;
       it.current_index = 0;
       it.sv = this;
       it.current_node = this->root;
       return it;
   }

   iterator end(){
       iterator it;
       it.sv = this;
       it.current_node = nullptr;
       return it;

   }
};

#endif // SPARSE_VECTOR_H
