#ifndef SINGLETON_H
#define SINGLETON_H
#include <memory>
#include <mutex>
#include <iostream>
#include "global.h"

using namespace std;

template <typename T>
class Singleton{
protected:
    // 构造函数不允许外部访问，但子类能够构造基类
    Singleton() = default;
    // 不允许拷贝构造
    Singleton(const Singleton<T>&) = delete;
    // 不允许拷贝赋值
    Singleton& operator=(const Singleton<T>& st) = delete;

    // 单例类会返回一个实例，使用智能指针回收，使用静态变量将所有的Singleton都返回这一个实例
    // 一定要初始化
    static std::shared_ptr<T> _instance;

public:
    static std::shared_ptr<T> GetInstance() {
        // 局部静态变量，once_flag只会初始化一次
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            // 不用 make_shared 是因为这里的构造函数是protected
            _instance = shared_ptr<T>(new T);
        });

        return _instance;
    }

    void PrintAddress() {
        std::cout << _instance.get() << endl;
    }
    ~Singleton() {
        std::cout << "this is singleton destruct" << std::endl;
    }
};

// 模板类的初始化
template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
