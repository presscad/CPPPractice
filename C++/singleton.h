#ifndef SINGLETON_H
#define SINGLETON_H
#include <memory>

template<typename T>
class Singleton
{
public:
    static std::auto_ptr<T> getInstance()
    {
        if(!sg.get())
        {
            // Here can't be auto_ptr<T> sg(new T);
           std::auto_ptr<T> temp(new T);
           sg = temp;
        }
        return sg;
    }

private:
    Singleton() {}
    Singleton(const Singleton &); // hide copy constructor
    Singleton& operator=(const Singleton &); // hide assign op

    static std::auto_ptr<T> sg;
};

#endif // SINGLETON_H
