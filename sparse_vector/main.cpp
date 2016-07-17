#include <iostream>
#include <sparse_vector.h>
#include <list>
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    sparse_vector<int> v(0);
    v.set(31,4);
    v.set(12,8);
    v.set(31,6);
    v.set(50,5);
    v[3] = 2;
    v[0] = 7;
    cout<<v[13]<<endl;

    sparse_vector<int>::iterator it = v.begin();
    it++;
    it++;
    cout<<*it++<<endl;
    cout<<*it<<endl;
    for (sparse_vector<int>::iterator i = v.begin();i!=v.end(); i++) {
        cout<<*i<<"-";
    }
    cout<<endl;
    sparse_vector<int>v1(0);
    sparse_vector<int>v2(0);

    v1[5] = 3;
    v1[5] = 0;
    cout<<(v1==v2)<<endl;
    /*
    list<int> l1;
    l1.push_front(5);


    list<int> l2 = l1;

    list<int>::iterator i1 = l1.begin();
    list<int>::iterator i2 = l1.begin();
    cout<<(i1 == i2)<<endl;
    i1++;
    i2++;
    cout<< (i1 == i2)<<endl;*/
    return 0;
}

