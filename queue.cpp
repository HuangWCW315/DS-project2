#include "container.h"

void queue::push(node *q){

    if (empty()) 
    {
        front_node = new node_queue(q);
        back_node = front_node;
        size++;
        return;
    }

    node_queue *new_node = new node_queue(q);
    back_node->next = new_node;
    back_node = new_node;
    size++;
}

void queue::pop(){

    if (empty()) 
    {
        cout << "Cannot pop!.\n";
        return;
    }

    node_queue *deleted = front_node;
    front_node = front_node->next;
    delete deleted;
    size--;
}

node* queue::front(){

    if (empty()) {
        cout << "No element!.\n";
        return nullptr;
    }

    return front_node->data;
}

bool queue::empty(){

    return (front_node == nullptr || back_node == nullptr);
}
