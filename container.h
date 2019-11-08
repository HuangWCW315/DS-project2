#ifndef CONTAINER_H
#define CONTAINER_H


#include <iostream>
#include <queue>
#include <stack>
using namespace std;
#define left 0
#define right 1
#define up 2
#define down 3

class node
{
    private:
    int row, col;
    int height;
    int state;
    bool travel;
    node *parent;
    node *direction[4];//, *left, *right, *up, *down;
    node *child[4];
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
/*    void set_left(node *left){this->left = left;}
    void set_right(node *right){this->right = right;}
    void set_up(node *up){this->up = up;}
    void set_down(node *down){this->down = down;}*/
    void set_direction(int index, node* direction){this->direction[index] = direction;}
    void set_child(int index, node* child){this->child[index] = child;}
    void set_height(int height){this->height = height;}
    int get_row(){return this->row;}
    int get_col(){return this->col;}
    int get_state(){return this->state;}
    int get_height(){return this->height;}
    bool get_travel(){return this->travel;}
    node *get_parent(){return this->parent;}
 /*   node *get_left(){return this->left;}
    node *get_right(){return this->right;}
    node *get_up(){return this->up;}
    node *get_down(){return this->down;}*/
    node *get_direction(int index){return this->direction[index];}
    node *get_child(int index){return this->child[index];}
    void print_data(){cout << this->row << ' ' << this->col << '\n';};
};

class graph
{
    private:
    int row_max, col_max;
    int row, col;
    bool all_visit(node *root);
    public:
    int row_begin, col_begin;
    node ***map;
    graph(int row, int col);
    void link(int row, int col);
    void traverse(node *root, int &battery, const int battery_max, int &counter);
    void print(int row, int col);
    void reset_travel();
    bool all_visit();
    void preorder(node *root);
};

#endif