#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <plain-crud.h>

using namespace std;

struct Data {
    int i;
    double d;
};

#include <cstring> 

int main(int argc, char *argv[])
{
    const string file_path = "data.dat";

  
    //list<int> data_list;
    Data data = {
        0,
        0
    };

    PlainCRUD<Data> plainCRUD;
    plainCRUD.load(file_path, data);

    cout << data.i << endl;

    data.i = 12334;
    cout << data.i << endl;

    plainCRUD.write(data);


    system("pause");
}