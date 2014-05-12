#include "alg.h"
#include "simplestring.h"

using namespace std;
using namespace simplestd;

int main()
{
    int a[9] = {2,3,9,4,5,7,6,20,8};
    cout<<"Before:";
    for(size_t i=0;i<9;i++)
        cout<<a[i]<<" ";
    cout<<endl;
    insertSort(a,9);
    cout<<"After:";
    for(size_t i=0;i<9;i++)
        cout<<a[i]<<" ";
    cout<<endl;

    String s("abcdefg");
    String t(s);

    t = "ABC";
    char *cc = "ABCs";
    bool equal = false;
    equal = t == cc;
    cout<<equal;


    cout<<s[2]<<endl;
    cout<<t[2]<<endl;
    cout<<t[1]<<endl;

    return 0;
}

