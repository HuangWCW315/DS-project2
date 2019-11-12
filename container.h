#ifndef CONTAINER_H
#define CONTAINER_H

#include <time.h>
#include <iostream>
#include <queue>
#include <stack>
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
    node *child[4];
    node *direction[4];//, *left, *right, *up, *down;

    public:
    node(){}
    node(int row, int col, int state):row(row), col(col), height(1), state(state), travel(false), 
                                        parent(nullptr)/*, left(nullptr), right(nullptr), 
                                        up(nullptr), down(nullptr)*/
                                        {
                                            for (int i = 0; i < 4; i++)
                                            {    
                                                direction[i] = nullptr;
                                                child[i] = nullptr;
                                            }
                                        }
    void set_state(char state){this->state = state;}
    void set_travel(bool travel){this->travel = travel;}
    void set_parent(node *parent){this->parent=parent;}
    void set_direction(int index, node* direction){this->direction[index] = direction;}
    void set_child(int index, node* child){this->child[index] = child;}
    void set_height(int height){this->height = height;}
    int get_row(){return this->row;}
    int get_col(){return this->col;}
    int get_state(){return this->state;}
    int get_height(){return this->height;}
    bool get_travel(){return this->travel;}
    node *get_parent(){return this->parent;}
    node *get_direction(int index){return this->direction[index];}
    node *get_child(int index){return this->child[index];}
    void print_data(ofstream& file){file << this->row << ' ' << this->col << '\n';}
    bool check_battery(int battery)
    {
        if (this->height - 1 <= battery)
            return true;
        else return false;
    }
};

class graph
{
    private:
    int row_max, col_max;
    int element_number;
    int row_begin, col_begin;
    bool all_visit(node *root);

    public:
    

    node ***map;
    graph(int row, int col);
    ~graph();
    void link(int row, int col);
    void traverse(node *root, int &battery, const int battery_max, int &counter);
    void print(int row, int col);
    void reset_travel();
    bool all_visit();
    void preorder(node *root);
    node *MST();
};

#endif