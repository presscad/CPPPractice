#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T>
class Singleton
{
public:
    static auto_ptr<T> getInstance();

private:
    Singleton() {}
    Singleton(const Singleton &); // hide copy constructor
    Singleton& operator=(const Singleton &); // hide assign op

    static auto_ptr<T> sg;
};

#endif // SINGLETON_H
