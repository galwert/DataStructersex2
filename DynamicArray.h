//
// Created by galwe on 04/01/2022.
//

#ifndef MAIN_CPP_DYNAMICARRAY_H
#define MAIN_CPP_DYNAMICARRAY_H
#include "library2.h"
namespace Ehsan {

    template<class T>
    class ListNode//---------------ListNode-----------------------------
    {
    public:
        T* data;
        ListNode *next;
        int id;

        ListNode(T* data,int id):
                data(data),
                next(nullptr),
                id(id)
        { }

        ListNode(T* data,ListNode<T>* next,int id):
                data(data),
                next(next),
                id(id)
        {}
        ~ListNode()
        {
            delete data;
        }
    };//---------------ListNode END-----------------------------


    template<class T>
    class List {//-----------------List Class----------------------------------
    public:
        ListNode <T> *head;

        List():head(nullptr)
        {}

        void insert(T* data,int id)
        {
            this->head = new ListNode<T>(data,this->head,id);

        }

        StatusType remove(int id)
        {
            ListNode<T> * node=this->head,*prev= nullptr;
            while(node!= nullptr)
            {
                if(id==node->id)
                {
                    if(prev== nullptr)
                    {
                        this->head=node->next;
                    }
                    else
                    {
                        prev->next=node->next;
                    }
                    delete node;
                    return SUCCESS;
                }
                prev=node;
                node=node->next;

            }
            return FAILURE;
        }
        ListNode<T> *find(int id)
        {
            if(this== nullptr)
            {
                return nullptr;
            }
            ListNode<T> *node = this->head;
            while(node != nullptr)
            {
                if(id == node->id)
                {
                    return node;
                }
                node = node->next;
            }
            return nullptr;
        }
    };
    template<class T>
    class DynamicArray {
    public:
        int size;
        List<T> **array;
        int balance_factor;
        int node_count;

        explicit DynamicArray(int size, int balance_factor) :
                size(size),
                balance_factor(balance_factor),
                node_count(0)
        {
            array = new List<T>*[size]();
        }
        void ClearArray()
        {
            ListNode<T> * node,*next;
            for(int i=0;i<size;i++)
            {
                if(array[i]!= nullptr) {
                    node = array[i]->head;
                    while (node != nullptr) {
                        next=node->next;
                        //delete node->data;
                        delete node;
                        node = next;
                    }
                    delete array[i];
                }
            }
            delete[] array;
        }
        ~DynamicArray()
        {
            this->ClearArray();
        }
        DynamicArray() = delete;

        StatusType insert(int id,T* data)
        {
            if((this->balance_factor*this->size)<this->node_count)
            {
                ListNode<T> * node;
                List<T>** new_array=new List<T>*[2*size]();
                for(int i=0;i<size;i++)
                {
                    if(array[i]!= nullptr) {
                        node = array[i]->head;
                        while (node != nullptr) {
                            if (new_array[node->id % (2 * size)] == nullptr) {
                                new_array[node->id % (2 * size)] = new List<T>();
                            }
                            new_array[node->id % (2 * size)]->insert(new T(node->data), node->id);
                            node = node->next;
                        }
                    }
                }
                this->ClearArray();
                array=new_array;
                size*=2;
            }

            if(array[id%size]== nullptr)
            {
                array[id%size] = new List<T>();
            }
            array[id%size]->insert(data,id);
            node_count++;
            return SUCCESS;
        }
        T* find(int id)
        {
            if( array[id%size]->find(id)== nullptr)
            {
                return nullptr;
            }
            else
            {
                return array[id%size]->find(id)->data;
            }
        }
        StatusType remove(int id)
        {
            if(find(id) == nullptr)//change
            {
                return FAILURE;
            }
            if(this->size>this->node_count)
            {
                ListNode<T> * node;
                List<T>** new_array=new List<T>*[size/2]();
                for(int i=0;i<size;i++)
                {
                    if(array[i]!= nullptr) {
                        node = array[i]->head;
                        while (node != nullptr) {
                            if (new_array[node->id % (size/2)] == nullptr) {
                                new_array[node->id % (size/2)] = new List<T>();
                            }
                            new_array[node->id % (size/2)]->insert(new T(node->data), node->id);//change
                            node = node->next;
                        }
                    }
                }
                this->ClearArray();
                array=new_array;
                size/=2;

            }
            node_count--;
            array[id%size]->remove(id);
            return SUCCESS;
        }
    };

}
#endif //MAIN_CPP_DYNAMICARRAY_H
