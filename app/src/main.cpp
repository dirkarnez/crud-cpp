#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <plain-crud.h>

using namespace std;

struct Data {
    int id;
    char name[50];
};

#include <cstring> 

int main(int argc, char *argv[])
{
    const string file_path = "data.dat";

    Data data = {
        0,
        0
    };

    PlainCRUD<Data> plainCRUD;
    plainCRUD.load(file_path, data);

    cout << "after load" << endl;
    cout << "id: ->" << data.id << "<-" << endl;
    cout << "name: ->" << data.name << "<-" << endl;

    cout << endl;

    cout << "editing..." << endl;
    data.id = 1234;
    snprintf(data.name, 50, "asd");

    cout << endl;

    cout << "after edit" << endl;
    cout << "id: ->" << data.id << "<-" << endl;
    cout << "name: ->" << data.name << "<-" << endl;

    plainCRUD.write(data);

    system("pause");
}