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
    for (int i = 0; i < row_max; i++)
        for (int j = 0; j < col_max ; j++)
            map[i][j]->set_travel(false);
}
//*******************************************************************************************//
graph::graph(int row, int col)
{
        element_number = 0;
        row_max = row;
        col_max = col;
        map = new node**[row];
/*        for (int i = 0; i < row; i++)
        {    
            map[i] = new node*[col];
            for (int j = 0; j < col; j++)
            {
                int state;
                if (i == row-1 && j == col-1)
                map[i][j] = new node(i, j, 2);
                else if (i == row-1 || j == col-1)
                 map[i][j] = new node(i, j, 2);
                else map[i][j] = new node(i, j, 0);
                
                if (i==row - 1&&j==col - 1)
                {
                    row_begin = i;
                    col_begin = j;
                }
        }*/
        
        for (int i = 0; i < row; i++)
        {    
            map[i] = new node*[col];
            for (int j = 0; j < col; j++)
            {
                int state;
               cin >> state;
                map[i][j] = new node(i, j, state);
                
                if (state == 2)
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
    }
    if (col + 1 < col_max && (map[row][col + 1]->get_state() == 0 ||  map[row][col + 1]->get_state() == 2))
    {
        map[row][col]->set_direction(right, map[row][col + 1]);
    }  
    if (row + 1 < row_max && (map[row + 1][col]->get_state() == 0 || map[row + 1][col]->get_state() == 2))
    {
        map[row][col]->set_direction(down, map[row + 1][col]);
    }
    if (row - 1 >= 0 && (map[row - 1][col]->get_state() == 0 || map[row - 1][col]->get_state() == 2))
    {
        map[row][col]->set_direction(up, map[row - 1][col]);
    } 
}
//*******************************************************************************************//
void graph::traverse(node *root, int &battery, const int battery_max, int &counter)
{
    stack<node *> path;
    node *now = root;
    ofstream file_out;
    reset_travel();
    bool stop = true;

    file_out.open("final.path", ios::out | ios::trunc);
    if (!file_out.is_open())
    {
        cout << "open file fail!\n";
        return;
    }

    counter--;

    while(element_number)
    {
        if (now == root)
            battery = battery_max;

        now->print_data(file_out);
        stop = true;
        now->set_travel(true);
        counter++;
        for (int i = 0; i < 4 && stop; i++)
        {
            node *next = now->child[i];
            if (next != nullptr && next->get_travel() != true)
            {
                now = next;
                stop = false;
                element_number--;
                battery--;
            }

        }



        if (!stop && !now->check_battery(battery))
        {
            battery++;
            path.push(now->parent);
            node *temp = now->parent->parent; 
            while (temp != nullptr)
            {
                path.push(temp);
                temp->print_data(file_out);
                temp->set_travel(true);
                temp = temp->parent;
                counter++;
            }
            battery = battery_max;
            path.pop();                 // pop root
            while (!path.empty())
            {
                battery--;
                temp = path.top();
                path.pop();
                temp->print_data(file_out);
                counter++;
            }
        }

        if (stop)
        {    
            now = now->get_parent();
            battery--;
        }
    }

    while(now != nullptr)
    {
        now->print_data(file_out);
        now = now->get_parent();
        counter++;
    }

    file_out.close();
    if (file_out.is_open())
    {
        cout << "Close file fails!\n";
        return;
    }
}
//*******************************************************************************************//
void graph::print(int row, int col)
{
    for (int i = 0; i < row_max; i++)
    {        
        for (int j = 0; j < col_max; j++)
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

//*******************************************************************************************//

node *graph::MST()
{
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
                queue.push(next);
                next->set_parent(root);
                next->set_height(root->get_height() + 1);
                root->set_child(i, next);
                next->set_travel(true);
                element_number++;
            }  
        }
            
        queue.pop();
    }
    map[row_begin][col_begin]->parent = nullptr;

    return map[row_begin][col_begin];
}


graph::~graph()
{
    for (int i = 0; i < row_max; i++)
    {
        for (int j = 0; j < col_max; j++)
            delete map[i][j];
        delete map[i];
    }
    delete map;
}

//***********************************************************************************************//

