#include "alg.h"
#include "simplestring.h"
#include "interview.h"
#include "singleton.h"

using namespace std;
using namespace simplestd;

class Student
{
public:
         Student(const string name = "Andrew", const int age = 7) : name(name), age(age)
         {
                   cout << "constructor..." << endl;
         }

         void print_info() const
         {
                   cout << "Name: " << name << ", Age: " << age << endl;
         }
private:
         string name;
         int age;
};

template <> auto_ptr<Student> Singleton<Student>::sg;

int main()
{
    auto_ptr<Student> singleton(Singleton<Student>::getInstance());
    singleton->print_info();

    string s = number2String(55);
    cout<<s<<endl;
    system("pause");
    return 0;
}

