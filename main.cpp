#include <iostream>
#include <queue>
#include <stack>


#define left 0
#define right 1
#define up 2
#define down 3

using namespace std;

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
    node(int row, int col, int state):row(row), col(col), height(0), state(state), travel(false), 
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
};

class graph
{

};

void link(node ***map, int row, int col, int row_max, int col_max)
{
    if (col - 1 >= 0 && (map[row][col - 1]->get_state() == 0 || map[row][col - 1]->get_state() == 2))
    {
        map[row][col]->set_direction(left, map[row][col - 1]);
 //       map[row][col]->set_left(map[row][col - 1]);
    }
    if (col + 1 < col_max && (map[row][col + 1]->get_state() == 0 ||  map[row][col + 1]->get_state() == 2))
    {
        map[row][col]->set_direction(right, map[row][col + 1]);
 //       map[row][col]->set_right(map[row][col + 1]);
    }  
    if (row + 1 < row_max && (map[row + 1][col]->get_state() == 0 || map[row + 1][col]->get_state() == 2))
    {
        map[row][col]->set_direction(down, map[row + 1][col]);
 //       map[row][col]->set_down(map[row + 1][col]);
    }
    if (row - 1 >= 0 && (map[row - 1][col]->get_state() == 0 || map[row - 1][col]->get_state() == 2))
    {
        map[row][col]->set_direction(up, map[row - 1][col]);
  //      map[row][col]->set_up(map[row - 1][col]);
    } 
}

void inorder(node *root, int &counter)
{
    if (root != nullptr)
    {
        cout << root->get_row() << ' ' << root->get_col() << ' ' << root->get_height() << endl;
        counter++;
        for (int i = 0; i < 4; i++)
        {
            inorder(root->get_child(i), counter);
        }
    }
}

int main()
{
    int row, col, Battery;
    
    cin >> row >> col >> Battery;

    node ***map;
    map = new node**[row];
    int row_begin, col_begin;

    for (int i = 0; i < row; i++)
    {    
        map[i] = new node*[col];
        for (int j = 0; j < col; j++)
        {
            int state;
 //           cin >> state;
            if (i != row-1 || j != col-1)
            map[i][j] = new node(i, j, 0);
            else map[i][j] = new node(i, j, 2);
            
            if (/*state == 2*/i==row - 1&&j==col - 1)
            {
                row_begin = i;
                col_begin = j;
            }
        }
    }

    for (int i = 0; i < row; i++)
    {    
        for (int j = 0; j < col; j++)
        {
            if (map[i][j]->get_state() == 0 || map[i][j]->get_state() == 2)
                link(map, i , j, row, col);
        }
    }



    queue<node *> queue;
    queue.push(map[row_begin][col_begin]);
    map[row_begin][col_begin]->set_travel(true);
    while (!queue.empty())
    {
        node *root;
        root = queue.front();

        for (int i = 0; i < 4; i++)
        {
            node *next = root->get_direction(i);
            if (next != nullptr && next->get_travel() != true)
            {
                queue.push(root->get_direction(i));
                next->set_parent(root);
                next->set_height(root->get_height() + 1);
                root->set_child(i, next);
                next->set_travel(true);
            }  
        }
            
        queue.pop();
    }

    int count = 0;
    inorder(map[row_begin][col_begin], count);
    cout << count << endl;

    cout << endl;
/*    for (int i = 0; i < row; i++)
    {    
        for (int j = 0; j < col; j++)
        {
            cout << map[i][j]->get_state() << ' ';
            cout << map[i][j]->get_direction(up) << ' ';
            cout << map[i][j]->get_direction(down) << ' ';
            cout << map[i][j]->get_direction(left) << ' ';
            cout << map[i][j]->get_direction(right) << ' ';
            cout << endl;
        }
        cout << endl;
    }*/
    return 0;
}