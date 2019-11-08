#include "container.h"

//*******************************************************************************************//
bool graph::all_visit(node *root)
{

    if (root == nullptr)
        return true;
    else if (root->get_travel() == false)
        return false;

    else return all_visit(root->get_child(0)) && all_visit(root->get_child(1)) 
        && all_visit(root->get_child(2)) && all_visit(root->get_child(3));
}
//*******************************************************************************************//
bool graph::all_visit()
{
    return all_visit(map[row_begin][col_begin]);
}
//*******************************************************************************************//
void graph::reset_travel()
{
 //   cout << row_max << ' ' << col_max << '\n';
    for (int i = 0; i < row_max; i++)
        for (int j = 0; j < col_max ; j++)
            map[i][j]->set_travel(false);
}
//*******************************************************************************************//
graph::graph(int row, int col)
{
        row_max = row;
        col_max = col;
        map = new node**[row];
        for (int i = 0; i < row; i++)
        {    
        map[i] = new node*[col];
        for (int j = 0; j < col; j++)
        {
            int state;
 //           cin >> state;
            if (i == row-1 && j == col-1)
            map[i][j] = new node(i, j, 2);
            else map[i][j] = new node(i, j, 0);
            
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
                link(i , j);
        }
    }
    
}
//*******************************************************************************************//
void graph::link(int row, int col)
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
//*******************************************************************************************//
void graph::traverse(node *root, int &battery, const int battery_max, int &counter)
{
    stack<node *> s1;
    stack<node *> path;
    node *now = root;
    cout << "start\n";
    reset_travel();
    while(!all_visit())
    {
        now->print_data();
        bool stop = true;
        path.push(now);
        now->set_travel(true);
        counter++;
        for (int i = 0; i < 4 && stop; i++)
            if (now->get_child(i) != nullptr && now->get_child(i)->get_travel() != true)
            {
                now = now->get_child(i);
                stop = false;
            }
        if (stop)
            now = now->get_parent();
  //      cout << "stop = "<<stop<<endl; 
  //      cout << now->get_row() << ' ' << now->get_col()<<  endl;  
    }
    while(now != root)
    {
        now->print_data();
        now = now->get_parent();
        counter++;
    }
    now->print_data();
 //   cout << "out\n";
/*    while(!path.empty())
    {
        cout << path.top()->get_row() << ' ' << path.top()->get_col() << endl;
        path.pop();
    }*/
}
//*******************************************************************************************//
void graph::print(int row, int col)
{
    for (int i = 0; i < row; i++)
    {        
        for (int j = 0; j < col; j++)
            cout << map[i][j]->get_travel() << ' ';
        cout << '\n';
    }
    cout << '\n';
}
//*******************************************************************************************//


void graph::preorder(node *root)
{
    if (root != nullptr)
    {
        cout << root->get_row() << ' ' << root->get_col() << '\n';
        root->set_travel(true);
        for (int i = 0; i < 4; i++)
        {
            preorder(root->get_child(i));
        }
    }
}