#include "container.h"

//*******************************************************************************************//
/*bool graph::all_visit(node *root)
{

    if (root == nullptr)
        return true;
    else if (root->travel == false)
        return false;

    else return all_visit(root->child[0]) && all_visit(root->child[1]) 
        && all_visit(root->child[2]) && all_visit(root->child[3]);
}*/
//*******************************************************************************************//
/*bool graph::all_visit()
{
    return all_visit(map[row_begin][col_begin]);
}*/
//*******************************************************************************************//
void graph::reset_travel()
{
    for (int i = 0; i < row_max; i++)
        for (int j = 0; j < col_max ; j++)
            map[i][j]->travel = false;
}
//*******************************************************************************************//
graph::graph(int row, int col)
{
        element_number = 0;
        row_max = row;
        col_max = col;
        map = new node**[row];
 /*       for (int i = 0; i < row; i++)
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
            }
        }
        */
        cin.get();
        for (int i = 0; i < row; i++)
        {    
            map[i] = new node*[col];
            for (int j = 0; j < col; j++)
            {
                int state;
                char ch;
                cin.get(ch);
                if (ch == '0')
                    state = 0;
                else if (ch == '1')
                    state = 1;
                else if (ch == 'R')
                    state = 2;
                map[i][j] = new node(i, j, state);
                
                if (state == 2)
                {
                    row_begin = i;
                    col_begin = j;
                }
            }
            cin.get();
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
void graph::traverse(node *root, int &battery, const int battery_max, int &counter, ofstream& file_out)
{
    stack<node *> path;
    node *now = root;
    reset_travel();
    bool stop = true;

  //  map[98][62]->parent->print_data();
    int element = element_number;
    counter--;

    while(element)
    {
        if (now == root)
            battery = battery_max;

        now->print_data(file_out);
        stop = true;
        now->travel = true;
        counter++;
        for (int i = 0; i < 4 && stop; i++)
        {
            if (now->direction[i] != now->parent)
            {
                node *next = now->direction[i];
                if (next != nullptr && next->travel != true)
                {
                    now = next;
                    stop = false;
                    element--;
                    battery--;
                }
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
                temp->travel = true;
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
            now = now->parent;
            battery--;
        }
    }

    while(now != nullptr)
    {
        now->print_data(file_out);
        now = now->parent;
        counter++;
    }


}
//*******************************************************************************************//
/*void graph::print(int row, int col)
{
    for (int i = 0; i < row_max; i++)
    {        
        for (int j = 0; j < col_max; j++)
            cout << map[i][j]->travel << ' ';
        cout << '\n';
    }
    cout << '\n';
}*/
//*******************************************************************************************//

/*
void graph::preorder(node *root)
{
    if (root != nullptr)
    {
        cout << root->row << ' ' << root->col << '\n';
        root->travel = true;
        for (int i = 0; i < 4; i++)
        {
            if (root->direction[i] != root->parent)
                preorder(root->direction[i]);
        }
    }
}
*/
//*******************************************************************************************//

node *graph::MST()
{
    queue<node *> queue;
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


void graph::shortest_path(node *root, const int battery_max, int &counter, node *highest, ofstream& file_out)
{
    stack<node *> path_go;
    stack<node *> path_back;
    int element = element_number;
    node *index = highest;
    node *pt = index;
    reset_travel();
    int battery = battery_max;
    counter--;
    while (element)
    {    
        
        root->print_data(file_out);

        while (index->travel)       // find highest
            index = index->order;

        pt = index;
//        pt->print_data();
        while(pt!=root && element)   // find next and travel
        {

            path_go.push(pt);
            pt->travel = true;
            bool find = false;
            node* p[4];
            for (int i = 0; i < 4; i++)
                p[i] = nullptr;
            for (int i = 0; i < 4; i++)
            {
                int k = 0;
   //         cout << pt->direction[i] << endl;
                if (pt->direction[i] != pt->parent)
                {
                    node *next = pt->direction[i];
                    if (next != nullptr && next->check_battery_short(battery - 1, battery_max) && next->travel == false)
                    {           
 //                       pt->print_data(battery);
                        p[k++] = next;  
                        find = true;
                    }
                }
            }
            if (find)
            {
                node *big = p[0];
                for (int i = 1; i < 4; i++)
                    if (p[i] != 0)
                        if (p[i] > big)
                            big = p[i];
                pt = big;
                battery--;
                element--;
            }

            if (!find)
            {
                
                
  //              pt->print_data(battery);
                pt = pt->parent;
                battery--;
                if (pt->travel != true)
                    element--;
                    
            }
        }

        battery = battery_max;
       counter++;
 //       pt->print_data(battery); 
        while(!path_go.empty())
        {
            counter++;
            path_back.push(path_go.top());
            path_go.top()->print_data(file_out);
            path_go.pop();
        }
   //     file_out << "first loop\n";
        if (element == 0)
        {
            index = index->parent;
            while(index != nullptr)
            {            
                index->print_data(file_out);
                index = index->parent;
                counter++;
            }
            
        }
        else 

        {     
            path_back.pop();  
            while(!path_back.empty())
            {
                counter++;
                path_back.top()->print_data(file_out);
                path_back.pop();
            }
        }
//        file_out << "second loop\n";
    }
 //   root->print_data(file_out);


}

//*************************************************************************************************//
/*
void graph::sort(node **arr)
{
    BST BST(map[row_begin][col_begin]);
    node *root;
    int counter = 0;
    root = sort(map[row_begin][col_begin], BST);
//    cout << root->Right->Left->row << ' ' << root->Right->Left->col << endl;
    sort(root, arr, counter);

}

node *graph::sort(node *root, BST &BST)
{
    if (root != nullptr)
    {    
        BST.insert(root);
        for (int i = 0; i < 4; i++)
        {
            if (root->direction[i] != root->parent)
                sort(root->direction[i], BST);
        }
        return root;
    }
    return nullptr;
}
*//*
void graph::sort(node *root, node **arr, int &counter)
{    
//       if (root != nullptr)
 //      cout << root->row << ' ' << root->col << ' ' << root->height<< ' ' << counter << endl;
    if (root != nullptr)
    {
        sort(root->Left, arr, counter);
        arr[counter++] = root;


        sort(root->Right, arr, counter);
    }
}
*/



node * graph::BFS()
{
    queue<node *> queue;
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
    return root;

}