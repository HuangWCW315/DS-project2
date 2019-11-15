#include "container.h"

//*******************************************************************************************//
void graph::reset_travel()
{
    for (int i = 0; i < row_max; i++)
        for (int j = 0; j < col_max ; j++)
            map[i][j]->travel = false;
}
//*******************************************************************************************//
graph::graph(int row, int col, ifstream& file)
{
        element_number = 0;
        row_max = row;
        col_max = col;
        map = new node**[row];

        char ch[1000];
        for (int i = 0; i < row; i++)
        {    
            map[i] = new node*[col];
            file >> ch;
            for (int j = 0; j < col; j++)
            {
                int state;
                if (ch[j] == '0')
                    state = 0;
                else if (ch[j] == '1')
                    state = 1;
                else if (ch[j] == 'R')
                    state = 2;
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
            if (map[i][j]->state == 0 || map[i][j]->state == 2)
                link(i , j);
        }
    }
    
}
//*******************************************************************************************//
void graph::link(int row, int col)
{
    if (col - 1 >= 0 && (map[row][col - 1]->state == 0 || map[row][col - 1]->state == 2))
    {
        map[row][col]->direction[left] = map[row][col - 1];
    }
    if (col + 1 < col_max && (map[row][col + 1]->state == 0 ||  map[row][col + 1]->state == 2))
    {
        map[row][col]->direction[right] = map[row][col + 1];
    }  
    if (row + 1 < row_max && (map[row + 1][col]->state == 0 || map[row + 1][col]->state == 2))
    {
        map[row][col]->direction[down] = map[row + 1][col];
    }
    if (row - 1 >= 0 && (map[row - 1][col]->state == 0 || map[row - 1][col]->state == 2))
    {
        map[row][col]->direction[up] = map[row - 1][col];
    } 
}
//*******************************************************************************************//

node *graph::MST()
{
    queue queue;
    queue.push(map[row_begin][col_begin]);
    map[row_begin][col_begin]->travel = true;
    while (!queue.empty())
    {
        node *root;
        root = queue.front();

        for (int i = 0; i < 4; i++)
        {
            node *next = root->direction[i];
            if (next != nullptr && next->travel != true)
            {
                queue.push(next);
                next->parent = root;
                next->height = root->height + 1;
   //             root->child[i] = next;
                next->travel = true;
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

node * graph::BFS()
{
    queue queue;
    queue.push(map[row_begin][col_begin]);
    map[row_begin][col_begin]->travel = true;
    node *pt = map[row_begin][col_begin];
    node *root= map[row_begin][col_begin];
    reset_travel();

    while (!queue.empty())
    {
        pt = root;
        root = queue.front();
        root->order = pt;
        for (int i = 0; i < 4; i++)
        {
            if (root->direction[i] != root->parent)
            {            
                node *next = root->direction[i];
                if (next != nullptr && next->travel != true)
                {
                    queue.push(next);
                    next->travel = true;
                }  
            }
        }
            
        queue.pop();
    }

    map[row_begin][col_begin]->order = nullptr;
    return root;

}


//**************************************************************************************************************//
void graph::shortest_path(node *root, const int battery_max, int &counter, node *highest, ofstream& file_out)
{
    int element = element_number;
    stack path;
    queue s1;
    node* index = highest;
    counter--;
    reset_travel();
    root->travel = true;

    while (element > 0)
    {   
        root->print_data(file_out);     // print root
        while (index->travel)        // find highest
        {
            index = index->order;
        }
        node *pt = index;

        while (pt != nullptr)        // root to index mark
        {
            path.push(pt);
            if (!pt->travel)
            {
                element--;
                pt->travel = true;
            }
            
            pt = pt->parent;
        }

        path.pop();         // pop root
        while (!path.empty())       // print root to index
        {
            path.top()->print_data(file_out);
            path.pop();
            counter++;
        }

        bool can_go = true;
        node *now = index;
        int step = 0;

        while (now != root)        // travel as far as possible
        {
            node *further[4] = {nullptr,nullptr,nullptr,nullptr};
            int k = 0;
            can_go = false;
           if (!now->travel)       // mark
            {
                element--;
                now->travel = true;
            }

            for (int i = 0; i < 4; i++)     // find way to go
            {
                if (now->direction[i] != nullptr && now->direction[i] != now->parent && now->direction[i]->travel != true)
                {
                    node *next = now->direction[i];
                    if (next->check_battery_short(next->height, step + 1, index->height, battery_max))
                    {   
                        further[k++] = next;
                        can_go = true;
                    }
                }
            }
            if (can_go)
            {
                node *max_height = further[0];
                while (further[k] != nullptr && further[k]->height >= max_height->height)
                    max_height = further[k];
                now = max_height;
                s1.push(max_height);
                step++;
            }
            else
            {
                now = now->parent;
                s1.push(now);
                step++;
            }
        }
        while (!s1.empty())            // index to root
        {
            if (!s1.front()->travel)       // mark
            {
                element--;
                s1.front()->travel = true;
            }
            if (s1.front() != root)
                s1.front()->print_data(file_out);
            s1.pop();
            counter++;
        }
    

    }

        root->print_data(file_out);     // print root
        counter++; 
}