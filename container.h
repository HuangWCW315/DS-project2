#ifndef CONTAINER_H
#define CONTAINER_H

#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;
#define left 0
#define right 1
#define up 2
#define down 3



class node
{
    friend class graph;

    private:
    int row, col;
    int height;
    int state;
    bool travel;
    node *parent;
    node *direction[4];
    node *Left, *Right;
    node *order;

    public:
    node(){}
    node(int row, int col, int state):row(row), col(col), height(1), state(state), travel(false), 
                                        parent(nullptr), Left(nullptr), Right(nullptr)
                                        {
                                            for (int i = 0; i < 4; i++)
                                            {    
                                                direction[i] = nullptr;
                                            }
                                        }

    void print_data(ofstream& file){file << this->row << ' ' << this->col  << '\n';}
    
    bool check_battery_short(int step, int height, int const battery_max)
    {
        if ((step + height) <= (battery_max / 2))
            return true;
        else return false;
    }

};

class graph
{
    private:
    int row_max, col_max;
    int row_begin, col_begin;
    node *root;
    public:
    
    int element_number;
    node ***map;
    graph(int row, int col, ifstream& file);
    ~graph();
    void link(int row, int col);
    void print(int row, int col);
    void reset_travel();
    void preorder(node *root);
    node *MST();
    void shortest_path(node *root, const int battery_max, int &counter, node *highest,ofstream& file_out);
    node* BFS();
};

class stack
{
    private:
        int index;
        int capacity;
        node **arr;
        void new_arr();
    public:
        stack():index(-1),capacity(1){
            arr = new node*[capacity];
        }
        void push(node *s);
        void pop();
        node *top();
        bool empty();
};

class node_queue
{
    friend class queue;

    private:
        node * data;
        node_queue *next;

        node_queue():data(nullptr),next(nullptr){};
        node_queue(node *data):data(data),next(nullptr){};
};

class queue
{
    private:
        node_queue *front_node;
        node_queue *back_node;
        int size;

    public:
        void push(node *q);
        void pop();
        bool empty();
        node *front();

        queue():front_node(nullptr),back_node(nullptr),size(0){};
};

#endif