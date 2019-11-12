#include "container.h"




int main()
{
    int row, col, Battery;
    
    clock_t start_t, end_t;

    cin >> row >> col >> Battery;

    start_t = clock();
    graph g(row, col);

    node *begin;

    begin = g.MST();


    int count = 0;
    int battery = Battery;
    g.reset_travel();

  

  //      cout << g.map[2][0]->get_child(up)->get_travel() << endl;
 //   g.preorder(g.map[g.row_begin][g.col_begin]);
    g.traverse(begin, battery, Battery, count);
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


    
    end_t = clock();

    cout << (double)(end_t - start_t) / CLOCKS_PER_SEC << endl;

    return 0;
}