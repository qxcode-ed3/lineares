#include <iostream>
#include <sparse_vector.h>
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    sparse_vector<int> v(0);
    v.set(31,15);
    v.set(12,8);
    v.set(31,17);
    v.set(80,5);
    return 0;
}

