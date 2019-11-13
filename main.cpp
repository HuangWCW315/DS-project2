#include "container.h"




int main()
{
    int row, col, Battery;
    ofstream file_out;
    clock_t start_t, end_t;

    file_out.open("final.path", ios::out | ios::trunc);
    if (!file_out.is_open())
    {
        cout << "open file fail!\n";
        return 0;
    }
    cin >> row >> col >> Battery;

    start_t = clock();
    graph g(row, col);

    cout << endl << endl << endl;

  /*  for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            cout << g.map[i][j]->get_state();
        cout << endl;
    }*/


    node *begin;

    begin = g.MST();

    int count = 0;
    int battery = Battery;

    g.reset_travel();
    
    node *order;
    
    order = g.BFS();        // biggest height
 
/*    while (order !=begin)
    {    
        order->print_data();
        order = order->get_order();
    }*/

    
//    node *arr[g.element_number];
/*
cout << "here\n";
    g.sort(arr);*/

 /*   for (int i = 0; i < 8; i++)
        cout << arr[i]->get_height() <<endl;
*/

  //  g.traverse(begin, battery, Battery, count, file_out);
    g.shortest_path(begin, Battery, count, order, file_out);
    cout << count << endl;
    cout << endl;


    file_out.close();
    if (file_out.is_open())
    {
        cout << "Close file fails!\n";
        return 0;
    }

    end_t = clock();

    cout << (double)(end_t - start_t) / CLOCKS_PER_SEC << endl;


    return 0;
}