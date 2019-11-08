#include "container.h"




int main()
{
    int row, col, Battery;
    
    cin >> row >> col >> Battery;

    graph g(row, col);


    queue<node *> queue;
    queue.push(g.map[g.row_begin][g.col_begin]);
    g.map[g.row_begin][g.col_begin]->set_travel(true);
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
            }  
        }
            
        queue.pop();
    }



    int count = 0;
    int battery = Battery;
    g.reset_travel();
        cout << g.map[2][0]->get_child(up)->get_travel() << endl;
 //   g.preorder(g.map[g.row_begin][g.col_begin]);
    g.traverse(g.map[g.row_begin][g.col_begin], battery, Battery, count);
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

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            delete g.map[i][j];
        delete g.map[i];
    }
    delete g.map;
    
    return 0;
}