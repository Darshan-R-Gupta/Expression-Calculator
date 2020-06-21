#ifndef LIST
#define LIST // LIST
#include <iostream>
using namespace std;
template <class T>
class Node{
public:
    T data;
    Node<T> *next;
    Node(T a){
        data =a;
        next = NULL;
    };
};
template<class T>
class List
{
public:
    List();
    Node<T> *head;
    void create(T data, int=0);
    void display(char spacing=' ');
    T remove(int ind = 0);
    T get(int ind = 0);
};
template <class T>
List<T>::List()
{
    head= NULL;
}
template <class T>
void List<T>::create(T data, int ind){
    Node<T> *temp = head;
    if(ind == 0){
        Node<T> *t = new Node<T>(data);
        t->next = head;
        head = t;
    }
    else{
        int i = 1;
        while(temp->next != NULL && i != ind){
            i++;
            temp =  temp->next;
        }
        Node<T> *n = new Node<T>(data);
        n->next = temp->next;
        temp->next = n;
    }
}
template <class T>
void List<T>::display(char spacing ){
    Node<T> *temp = head;
    while(temp != NULL){
        cout<<temp->data<<spacing;
        temp = temp->next;
    }
    cout<<endl;
}
template <class T>
T List<T>::remove(int ind){
    T removed = -1;
    if(head != NULL){
        if(ind == 0){
            Node<T> *n = head;
            head = head->next;
            removed = n->data;
            delete n;
        }
        else{
            Node<T> *temp = head;
            int i = 0;
            while(temp->next != NULL && i != ind-1){
                temp = temp->next;
                i++;
            }
            Node<T> *n = temp->next;
            if(n){
                temp->next = n->next;
                removed = n->data;
                delete n;
            }
        }
    }

    return removed;
}
template <class T>
T List<T>::get(int ind){
    Node<T> *temp = head;
    int i = 0;
    while(temp != NULL && i != ind){
        temp = temp->next;
        i++;
    }
    return temp->data;
}
#endif

