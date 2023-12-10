#ifndef PSEUDOLIST_H
#define PSEUDOLIST_H

#include <iterator>
#include <initializer_list>
#include <algorithm>
//#include <compare>

using std::swap;

namespace PSEUDOLIST{
    template<typename T>
    struct Node{
        T data{};
        Node* next{nullptr};
        Node* prev{nullptr};

        bool operator==(const Node& other){
            return (this->data == other.data);
        }
    };

    template<typename T>
    class Iterator{

        private:
        Node<T>* it{nullptr};

        public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Node<T>;
        using pointer = value_type*;
        using reference = value_type&;

        //constructors
        Iterator() = default;
        Iterator(Node<T>* ptr);
        Iterator(const Iterator& copyIT);
    
        //operator functions
        Iterator& operator++();
            //increments, then returns
        Iterator& operator++(int);
            //returns, then increments
        Iterator& operator--();
            //decrements, then returns
        Iterator& operator--(int);
            //returns, then decrements

        Iterator operator+(Iterator& rhs);
        Iterator operator-(Iterator& rhs);
        Iterator operator+(int rhs);
        Iterator operator-(int rhs);

        T& operator*();
            //operator* returns the value the pointer points to
        Node<T>*& operator->();
            //operator -> returns the pointer

        Node<T>* getIt() const;

        Iterator& operator=(Iterator& rhs);

        //comparison operators
        //auto operator<=>(const Iterator& other) const = default;
        bool operator==(const Iterator& rhs);
        bool operator!=(const Iterator& rhs);
    };

    template<typename T>
    class pseudoList{
        private:
        Node<T>* head{nullptr};

        public:
        using iterator = Iterator<Node<T>>;
        using difference_type = std::ptrdiff_t;
        using value_type = Node<T>;
        using size_type = size_t;
        using pointer = value_type*;
        using reference = value_type&;

        //constructors
        pseudoList(); //done
        pseudoList(int count, T val); //done
        pseudoList(std::initializer_list<T> list); //done

        pseudoList(Iterator<T> first, Iterator<T> last); //done
        pseudoList(const pseudoList& rhs); //done

        pseudoList& operator=(pseudoList rhs); //done
        pseudoList& operator=(std::initializer_list<T> list); //done

        //accessor functions
        Node<T>* front(); //done
        Node<T>* back(); //done
        Iterator<T> begin() const; //done
        Iterator<T> end() const; //done

        bool empty(); //done
        int getSize(); //done

        //modifier functions
        void clear(); //done
        void insert(Node<T>* pos, T val); //done
        void insert(Iterator<T> itr, T val); //done
        void insert(Iterator<T> pos, int count, T val); //done
        void insert(Iterator<T> a, Iterator<T> b, Iterator<T> b_end); //done
        void insert(Iterator<T> pos, std::initializer_list<T> list); //done
        void erase(Node<T>* pos); //done
        void erase(Iterator<T> itr); //done
        void erase(Iterator<T> first, Iterator<T> last); //done

        void push_back(T val); //done
        void push_front(T val); //done
        void pop_front(); //done
        void pop_back(); //done

        //operator overloaders
        bool operator==(const pseudoList& other); //done
        //auto operator<=>(const pseudoList& other) = default; //done

        //destructor
        ~pseudoList(); //done
    };
}


/*
    CONSTRUCTORS
*/
template<typename T>
PSEUDOLIST::pseudoList<T>::pseudoList(): head{new Node<T>{}}{

    head->next = head;
    head->prev = head;
}

template<typename T>
PSEUDOLIST::pseudoList<T>::pseudoList(int count, T val): pseudoList<T>(){

    for(int i = 0; i < count; i++)
        push_back(val);

}

template<typename T>
PSEUDOLIST::pseudoList<T>::pseudoList(std::initializer_list<T> list): pseudoList<T>(){

    for(auto element: list)
        push_back(element);

}

template<typename T>
PSEUDOLIST::pseudoList<T>::pseudoList(Iterator<T> first, Iterator<T> last): pseudoList<T>(){

    for(; first != last; ++first)
        push_back(*first);

    push_back(*last);
    

    //std::copy(first, last, std::back_inserter(*this));
}

template<typename T>
PSEUDOLIST::pseudoList<T>::pseudoList(const pseudoList& rhs): pseudoList<T>(){

    auto it1 = rhs.begin();
    auto it2 = rhs.end();

    for(; it1 != it2; ++it1)
        push_back(*it1);

    //           it1         it2          this->push_back(*it1)
    //std::copy(rhs.begin(), rhs.end(), std::back_inserter(*this));
}

template<typename T>
PSEUDOLIST::pseudoList<T>& PSEUDOLIST::pseudoList<T>::operator=(pseudoList rhs){

    swap(this->head, rhs.head);

    return *this;
}

template<typename T>
PSEUDOLIST::pseudoList<T>& PSEUDOLIST::pseudoList<T>::operator=(std::initializer_list<T> list){

    pseudoList<T> temp(list);

    swap(this->head, temp.head);

    return *this;
}

/*
    ACCESSORS
*/
template<typename T>
PSEUDOLIST::Node<T>* PSEUDOLIST::pseudoList<T>::front(){

    return head->next;
}

template<typename T>
PSEUDOLIST::Node<T>* PSEUDOLIST::pseudoList<T>::back(){

    return head->prev;
}

template<typename T>
PSEUDOLIST::Iterator<T> PSEUDOLIST::pseudoList<T>::begin() const{

    Iterator<T> itr(head->next);

    return itr;
}

template<typename T>
PSEUDOLIST::Iterator<T> PSEUDOLIST::pseudoList<T>::end() const{

    Iterator<T> itr(head);

    return itr;
}

template<typename T>
bool PSEUDOLIST::pseudoList<T>::empty(){

    return (head->next == head);
}

template<typename T>
int PSEUDOLIST::pseudoList<T>::getSize(){

    int size;

    if(empty())
        size = 0;

    Iterator<T> itr1(begin());
    Iterator<T> itr2(end());

    for(; itr1 != itr2; ++itr1)
        ++size;

    return size;
}

/*
    MODIFIERS
*/
template<typename T>
void PSEUDOLIST::pseudoList<T>::clear(){

    while(!empty())
        erase(head->next);
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::insert(Node<T>* pos, T val){

    Node<T>* tnode = new Node<T>{};
    tnode->data = val;
    tnode->next = pos->next;
    tnode->prev = pos;

    pos->next->prev = tnode;
    pos->next = tnode;
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::insert(Iterator<T> itr, T val){

    Node<T>* tnode = new Node<T>{};
    tnode->data = val;

    tnode->next = itr->next;
    tnode->prev = itr.getIt();

    itr->next->prev = tnode;
    itr->next = tnode;
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::insert(Iterator<T> pos, int count, T val){

    for(int i = 0; i<count; ++i)
        insert(pos, val);
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::insert(Iterator<T> a, Iterator<T> b, Iterator<T> b_end){

    if(b != b_end)
        insert(a, ++b, b_end);
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::insert(Iterator<T> pos, std::initializer_list<T> list){

    pseudoList temp(list);

    insert(pos, temp.begin(), temp.end());
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::erase(Node<T>* pos){

    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;

    delete pos;
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::erase(Iterator<T> itr){

    itr->prev->next = itr->next;
    itr->next->prev = itr->prev;

    delete itr.getIt();
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::erase(Iterator<T> first, Iterator<T> last){

    if(first != last)
        erase(++first, last);

    erase(first);
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::push_back(T val){

    insert(back(), val);
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::push_front(T val){

    insert(head, val);
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::pop_front(){

    erase(front());
}

template<typename T>
void PSEUDOLIST::pseudoList<T>::pop_back(){

    erase(back());
}


/*
    OPERATOR OVERLOADER
*/
template<typename T>
bool PSEUDOLIST::pseudoList<T>::operator==(const pseudoList& other){

    return std::equal(other.begin(), other.end(), this->begin());
}

/*
    DESTRUCTOR
*/
template<typename T>
PSEUDOLIST::pseudoList<T>::~pseudoList(){

    clear();

    delete head;
}

/*
    ITERATOR CLASS FUNCTIONS
*/
//constructors
template<typename T>
PSEUDOLIST::Iterator<T>::Iterator(Node<T>* ptr){
    it = ptr;
}

template<typename T>
PSEUDOLIST::Iterator<T>::Iterator(const Iterator& copyIT){
    it = copyIT.it;
}

//operator functions
template<typename T>
PSEUDOLIST::Iterator<T>& PSEUDOLIST::Iterator<T>::operator++(){

    it = it->next;
    
    return *this;
}

template<typename T>
PSEUDOLIST::Iterator<T>& PSEUDOLIST::Iterator<T>::operator++(int){

    Node<T>* it_copy = it;
    it = it->next;
    
    return Iterator<T>(it_copy);
}

template<typename T>
PSEUDOLIST::Iterator<T>& PSEUDOLIST::Iterator<T>::operator--(){

    it = it->prev;
    
    return *this;
}

template<typename T>
PSEUDOLIST::Iterator<T>& PSEUDOLIST::Iterator<T>::operator--(int){
    
    Node<T>* it_copy = it;
    it = it->prev;
    
    return Iterator<T>(it_copy);
}

template<typename T>
T& PSEUDOLIST::Iterator<T>::operator*(){

    return it->data;
}

template<typename T>
PSEUDOLIST::Node<T>*& PSEUDOLIST::Iterator<T>::operator->(){

    return it;
}

template<typename T>
PSEUDOLIST::Node<T>* PSEUDOLIST::Iterator<T>::getIt() const{

    return it;
}

template<typename T>
PSEUDOLIST::Iterator<T>& PSEUDOLIST::Iterator<T>::operator=(Iterator& rhs){

    it = rhs.it;

    return *this;
}

//comparision operators
template<typename T>
bool PSEUDOLIST::Iterator<T>::operator==(const Iterator& rhs){

    return (it == rhs.it);
}

template<typename T>
bool PSEUDOLIST::Iterator<T>::operator!=(const Iterator& rhs){

    return (it != rhs.it);
}

#endif