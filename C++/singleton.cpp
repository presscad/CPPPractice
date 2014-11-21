#include "singleton.h"


auto_ptr<T> Singleton::getInstance()
{
    if(!sg.get())
    {
        // 此处不能直接写成auto_ptr<T> sg(new T);
       auto_ptr<T> temp(new T);
       sg = temp;
    }
  return sg;
}
