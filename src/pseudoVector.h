#ifndef PSEUDOVECTOR_H
#define PSEUDOVECTOR_H

#include <memory>
#include <iostream>
#include <initializer_list>
#include <compare>

#include "Exception.h"


using namespace std;

/*
    N0TES:

    raw pointer initialization
        int* p = new int[10];
    unique pointer initialization
        unique_ptr<int[]> up = make_unique<int[]>(10);
        auto up = make_unique<int[]>(10);
    unique pointer usage
        up[0] = 10; //doesn't use it as an iterator
    using an iterator to modify things
        int* raw = up.get();
*/
namespace pVec{
    template<typename T>
    class Iterator{

        private:
        T* it{nullptr};

        public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

        //constructors
        Iterator() = default;
        Iterator(T* ptr);
        Iterator(const Iterator& copyIT);
    
        //operator functions
        Iterator& operator++();
            //increments, then returns
        Iterator operator++(int);
            //returns, then increments
        Iterator& operator--();
            //decrements, then returns
        Iterator operator--(int);
            //returns, then decrements

        Iterator operator+(Iterator& rhs);
        Iterator operator-(Iterator& rhs);
        Iterator operator+(int rhs);
        Iterator operator-(int rhs);

        T& operator*();
            //operator* returns the value the pointer points to
        T& operator->();
            //operator -> returns the pointer

        Iterator& operator=(Iterator& rhs);

        //comparison operators
        auto operator<=>(const Iterator& other) const = default;
        bool operator==(const Iterator& rhs);
        bool operator!=(const Iterator& rhs);

        //accessor functions
        T* getIt() const;

    };

    template<typename T>
    class pseudoVector{

        private:
        int size{0};
        int capacity{0};

        unique_ptr<T[]> aContainer;
            //T* aContainer = make_unique<T[]>(capacity);

        public:
        using iterator = Iterator<T>;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using size_type = size_t;
        using pointer = value_type*;
        using reference = value_type&;

        //constructors
        pseudoVector(); 
        pseudoVector(int count, T& value);
        pseudoVector(int count);
        pseudoVector(initializer_list<T> list);

        pseudoVector(const pseudoVector& pvIn);
        pseudoVector(pseudoVector&& temp);
            //P = std::move(temp)

        pseudoVector& operator=(pseudoVector& rhs);

        //accessor functions
        T& operator[](int index) const;
        T& at(int index) const;
        T& front() const;
        T& back() const;

        int getSize() const;
        int getCapacity() const;

        //capacity
        bool empty();
        void incSize();
        void incCapacity();

        //modifier functions
        void clear();

        void insert(int index, T& value);
        void insert(Iterator<T>& a, Iterator<T>& b, Iterator<T>& b_end);
        //void insert(v1 it, v2 it, v2 end);
            //all iterators by reference
            //increase size by v2end - v2it
            //copy everything up to where the insert is into a new vector
            //then copy the v2 stuff, then copy the rest of v1
            //then move the copied array to the initial pointer
            //update member variables
            //return an iterator at the position 
            //it is iterator - begin()
        void erase(int index);

        void push_back(T value);
        void pop_back();
        void pop_front();

        //comparison operators
        //auto operator<=>(const pseudoVector& other) = default;

        //iterator functions
        Iterator<T> begin();
        Iterator<T> end();

    };
}

//END OF CLASS DECLARATION



/*
    constructors 
*/
template<typename T>
pVec::pseudoVector<T>::pseudoVector(){

    aContainer = make_unique<T[]>(capacity);
}

template<typename T>
pVec::pseudoVector<T>::pseudoVector(int count, T& value){

    size = count;
    capacity = count*2;

    aContainer = make_unique<T[]>(capacity);
    for (int i = 0; i<size; i++)
        aContainer[i] = value;
}

template<typename T>
pVec::pseudoVector<T>::pseudoVector(int count){

    size = count;
    capacity = count*2;

    aContainer = make_unique<T[]>(capacity);
}

template<typename T>
pVec::pseudoVector<T>::pseudoVector(initializer_list<T> list){

    size = 0;
    capacity = 0;

    aContainer = make_unique<T[]>(capacity);

    for(auto element: list){

        push_back(element);
    }

}

template<typename T>
pVec::pseudoVector<T>::pseudoVector(const pVec::pseudoVector<T>& pvIn){

    size = pvIn.getSize();
    capacity = pvIn.getCapacity();

    aContainer = make_unique<T[]>(capacity);
    try{
        for (int i{0}; i<size; i++)
            aContainer[i] = pvIn.at(i);
    }
    catch(const BadPVIndex& e){
        cout << e.what() << endl;
    }
}

template<typename T>
pVec::pseudoVector<T>::pseudoVector(pseudoVector&& temp){

    size = temp.getSize();
    capacity = temp.getCapacity();

    aContainer = make_unique<T[]>(capacity);
    aContainer = move(temp.aContainer);
}

template<typename T>
pVec::pseudoVector<T>& pVec::pseudoVector<T>::operator=(pseudoVector& rhs){

    clear();

    for (int i{0}; i<rhs.getSize(); i++){

        incSize();

        aContainer[i] = rhs.at(i);
    }

    return *this;

}

/*
    accessor functions
*/
template<typename T>
T& pVec::pseudoVector<T>::operator[](int index) const{

    if(index>=size || index<0)
        throw BadPVIndex("Index is out of range");

    return *(aContainer.get() + index);
}


template<typename T>
T& pVec::pseudoVector<T>::at(int index) const{

    if(index>=size || index<0)
        throw BadPVIndex("Index is out of range");

    return *(aContainer.get() + index);
}

template<typename T>
T& pVec::pseudoVector<T>::front() const{

    return *(aContainer.get());
}

template<typename T>
T& pVec::pseudoVector<T>::back() const{

    return *(aContainer.get() + size - 1);
}


template<typename T>
int pVec::pseudoVector<T>::getSize() const{

    return size;
}

template<typename T>
int pVec::pseudoVector<T>::getCapacity() const{

    return capacity;
}

/*
    capacity functions
*/
template<typename T>
bool pVec::pseudoVector<T>::empty(){

    return (size == 0);
}

template<typename T>
void pVec::pseudoVector<T>::incSize(){

    if (size == capacity){

        incCapacity();
    }

    size++;

}

template<typename T>
void pVec::pseudoVector<T>::incCapacity(){

    int ogCapacity = capacity;

    if(capacity == 0)
        capacity++;
    else
        capacity *=2;
    
    unique_ptr<T[]> temp;
    temp = make_unique<T[]>(capacity);

    for(int i = 0; i < ogCapacity; i++)
        temp[i] = aContainer[i];

    aContainer = move(temp);
}

/*
    modifier functions
*/
template<typename T>
void pVec::pseudoVector<T>::clear(){

    int ogSize = size;

    for (int i = 0; i<ogSize; i++){

        size--;
    }
}

template<typename T>
void pVec::pseudoVector<T>::insert(int index, T& value){

    incSize();

    for (int i = size; i>=index; i--){

        aContainer[i] = aContainer[(i-1)];
    }

    aContainer[index] = value;
}


template<typename T>
void pVec::pseudoVector<T>::insert(Iterator<T>& a, Iterator<T>& b, Iterator<T>& b_end){

    int count = 0;
    Iterator<T> p(b);

    //for new index when incCapacity messes with the things
    Iterator<T> start(aContainer.get());
    int newIndex = (a.getIt() - start.getIt());

    while(p != b_end){
        count++;
        p++;
    }

    for(int i = 0; i<count; i++)
        incSize();

    Iterator<T> p2(this->end());
    Iterator<T> p4(this->begin().getIt() + count);
    do{
        p2--;
        *p2 = *(p2-count);
    }
    while(p2.getIt() != p4.getIt());

    Iterator<T> p3(this->begin().getIt() + newIndex);
    while(b != b_end){

        *p3 = *b;
        b++;
        p3++;
    }

}


template<typename T>
void pVec::pseudoVector<T>::erase(int index){

    for (int i = index; i<(size-1); i++){

        aContainer[i] = aContainer[(i+1)];
    }

    size--;
}

template<typename T>
void pVec::pseudoVector<T>::push_back(T value){

    incSize();

    aContainer[(size - 1)] = value;
}

template<typename T>
void pVec::pseudoVector<T>::pop_back(){

    size--;
}

template<typename T>
void pVec::pseudoVector<T>::pop_front(){
    erase(0);
}

/*
    iterator functions
*/
template<typename T>
pVec::Iterator<T> pVec::pseudoVector<T>::begin(){

    Iterator<T> it_ptr(aContainer.get());

    return it_ptr;
}

template<typename T>
pVec::Iterator<T> pVec::pseudoVector<T>::end(){

    Iterator<T> it_ptr(aContainer.get() + size);

    return it_ptr;
}


/*
    ITERATOR
*/

//constructors
template<typename T>
pVec::Iterator<T>::Iterator(T* ptr){

    it = ptr;
}

template<typename T>
pVec::Iterator<T>::Iterator(const Iterator& copyIT){

    it = copyIT.getIt();
}

//operator functions
template<typename T>
pVec::Iterator<T>& pVec::Iterator<T>::operator++(){

    ++it;

    return *this;
}

template<typename T>
pVec::Iterator<T> pVec::Iterator<T>::operator++(int){

    Iterator<T> copy(it);

    ++it;

    return copy;
}

template<typename T>
pVec::Iterator<T>& pVec::Iterator<T>::operator--(){

    --it;

    return *this;
}

template<typename T>
pVec::Iterator<T> pVec::Iterator<T>::operator--(int){

    Iterator<T> copy(it);

    --it;

    return copy;;
}

template<typename T>
pVec::Iterator<T> pVec::Iterator<T>::operator+(pVec::Iterator<T>& rhs){

    return (it + rhs.getIt());
}

template<typename T>
pVec::Iterator<T> pVec::Iterator<T>::operator-(pVec::Iterator<T>& rhs){

    return (it - rhs.getIt());
}

template<typename T>
pVec::Iterator<T> pVec::Iterator<T>::operator+(int rhs){

    return (it + rhs);
}

template<typename T>
pVec::Iterator<T> pVec::Iterator<T>::operator-(int rhs){

    return (it - rhs);
}

template<typename T>
T& pVec::Iterator<T>::operator*(){

    return *it;
}

template<typename T>
T& pVec::Iterator<T>::operator->(){

    return it;
}

template<typename T>
pVec::Iterator<T>& pVec::Iterator<T>::operator=(Iterator& rhs){

    it = rhs.getIt();

    return *this;
}

template<typename T>
bool pVec::Iterator<T>::operator==(const Iterator<T>& rhs){

    bool test = false;

    if (getIt() == rhs.getIt())
        test = true;

    return test;
}

template<typename T>
bool pVec::Iterator<T>::operator!=(const Iterator<T>& rhs){

    bool test = true;

    if (getIt() == rhs.getIt())
        test = false;

    return test;
}

//accessor functions
template<typename T>
T* pVec::Iterator<T>::getIt() const{

    return it;
}

#endif