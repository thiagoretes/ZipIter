#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include "ZipIterator.h"


using namespace std;


int main ()
{
    vector<int> v = {1, 2, 3, 4, 5};
    array<double, 5> u = {10, 20, 30, 40, 50};


    //for_each(zip::zipIterator(v.begin(), u.begin()), zip::zipIterator(v.end(), u.end()), [](auto&& tup)
    for_each(zip::zipIterator(v.begin(), u.begin()), zip::zipIterator(v.end(), u.end()), zip::unZip([](auto&& x, auto&& y)
    {
        cout << *x << "   " << *y << endl;
        //cout << *std::get<0>(tup) << "   " << *get<1>(tup) << endl;
    }));



    return 0;
}
