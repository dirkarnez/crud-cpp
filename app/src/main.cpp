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

    /*
    c if null
    r
    u / d(w)
    */
    //

    /**/

  
    list<int> data_list;
    PlainCRUD<list<int>> plainCRUD;
    plainCRUD.load(file_path, data_list);

    //data_list.push_back(123);
    //plainCRUD.write(data_list);

    //plainCRUD.read(data_list);

    for (int n : data_list) {
        cout << n << '\n';
    }

   //

    //

    system("pause");

    /**/


    //// Create a list containing integers
 
 
    //// Add an integer to the front of the list
    //l.push_front(25);
    //// Add an integer to the back of the list
    //l.push_back(13);
 
    //// Insert an integer before 16 by searching
    //auto it = std::find(l.begin(), l.end(), 16);
    //if (it != l.end()) {
    //    l.insert(it, 42);
    //}
 
    //// Iterate and print values of the list
    //for (int n : l) {
    //    std::cout << n << '\n';
    //}
}