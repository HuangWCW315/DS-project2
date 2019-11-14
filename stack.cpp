#include "container.h"

void stack::new_arr(){

    capacity *= 2;
    node **newStack = new node*[capacity];

    for (int i = 0; i < capacity / 2; i++) {
        newStack[i] = arr[i];
    }

    delete [] arr;
    arr = newStack;
}

bool stack::empty(){

    return (index == -1);
}

node *stack::top(){

    if (empty()) {
        cout << "No element!\n";
        return nullptr;
    }
    return arr[index];
}

void stack::push(node* s){

    if (index == capacity - 1) {
        new_arr();
    }
    arr[++index] = s;
}

void stack::pop(){

    if (empty()) {
        std::cout << "Cannot pop!\n";
        return;
    }
    index--;
}



