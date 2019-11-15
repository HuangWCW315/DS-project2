#include "container.h"

int main()
{
    int row, col, Battery;
    ifstream file_in;
    ofstream file_out1;
    clock_t start_t, end_t;

    file_in.open("floor.data", ios::in);
    file_out1.open("final.path", ios::out | ios::trunc);
    if (!file_in.is_open())
    {
        cout << "Open file fail!\n";
        return 0;
    }
    if (!file_out1.is_open())
    {
        cout << "Open file fail!\n";
        return 0;
    }
    file_in >> row >> col >> Battery;

    start_t = clock();
    graph g(row, col, file_in);

    file_out1 << "                      " << '\n';

    node *begin;

    begin = g.MST();

    int count = 0;
    int battery = Battery;

    g.reset_travel();
    
    node *order;
    
    order = g.BFS();        // biggest height
 
    g.shortest_path(begin, Battery, count, order, file_out1);

    file_out1.seekp(0L, ios::beg);
    file_out1 << count;
    file_in.close();


    if (file_in.is_open())
    {
        cout << "Close file fails!\n";
        return 0;
    }
    file_out1.close();
    if (file_out1.is_open())
    {
        cout << "Close file fails!\n";
        return 0;
    }
    end_t = clock();

 //   cout << "Run time : " << (double)(end_t - start_t) / CLOCKS_PER_SEC << " seconds."<< endl;


    return 0;
}