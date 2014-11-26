#ifndef SINGLETON_H
#define SINGLETON_H
#include <memory>

template<typename T>
class Singleton
{
public:
    static T* getInstance()
    {
        if(NULL == instance)
            instance = new T();

        return instance;
    }

private:
    Singleton() {}
    Singleton(const Singleton &); // hide copy constructor
    Singleton& operator=(const Singleton &); // hide assign op

    static T* instance;
};

template <class T>
T *Singleton<T>::instance = NULL;


/*
template <class T, bool bAutoCreate = false>
class Singleton
{
public:
	static T* Instance(void)
	{
		if (bAutoCreate && (m_Instance == NULL))
		{
			// Auto create & delete
			CreateInstance(true);
		}
		return m_Instance;
	}
	static void CreateInstance(bool bAutoDelete = false)
	{
		if (m_Instance == NULL)
		{
			mutex.lock();
			if (!m_Instance)
			{
				m_Instance = new T;
				if (bAutoDelete)
					atexit(&Singleton<T,bAutoCreate>::DeleteInstance);
			}
			mutex.unlock();
		}
	}
	static void DeleteInstance(void)
	{
		if (m_Instance)
		{
			mutex.lock();
			delete m_Instance;
			m_Instance = 0;
			mutex.unlock();
		}
	}

protected:
	Singleton() {}

	Singleton(const Singleton &); // hide copy constructor
	Singleton& operator=(const Singleton &); // hide assign op
	// we leave just the declarations, so the compiler will warn us 
	// if we try to use those two functions by accident

	static T* m_Instance;
	static QMutex mutex;
};

template <class T, bool bAutoCreate>
T *Singleton<T,bAutoCreate>::m_Instance = NULL;

template <class T, bool bAutoCreate>
QMutex Singleton<T, bAutoCreate>::mutex;
*/

#endif // SINGLETON_H
