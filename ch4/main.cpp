//
// Created by bing on 2023/6/19.
//

#include "iostream"
#include "thread"
#include "mutex"

std::mutex resource_mutex;
std::once_flag g_flag; // 与std::call_once配合使用

// 单例类
class MyClass {
    static void CreatInstance() {
        m_instance = new MyClass();
        static CGarhuishou cl;
    }
private:
    MyClass() {}

private:
    static MyClass *m_instance;

public:
    static MyClass* GetInstance() {
//        if (m_instance == NULL) {
//            std::unique_lock<std::mutex> lock(resource_mutex);
//            if (m_instance == NULL) {
//                m_instance = new MyClass();
//                static CGarhuishou cl;
//            }
//        }
        std::call_once(g_flag, CreatInstance);
        return m_instance;
    }
    class CGarhuishou {
    public:
        ~CGarhuishou() {
            if (MyClass::m_instance) {
                delete MyClass::m_instance;
                MyClass::m_instance = NULL;
            }
        }
    };

    void fun() {
        std::cout << "11" << std::endl;
    }
};

// 静态成员变量初始化
MyClass* MyClass::m_instance = NULL;

void myPrint() {
    std::cout << "start print " << std::endl;
    MyClass* p_a = MyClass::GetInstance();
    std::cout << "end print " << std::endl;
}

int main() {
    // 单例设计模式，在整个项目中，有某个或者某些特殊的类，属于该类的对象，只能创建一个
//    MyClass* p_a = MyClass::GetInstance();
//    p_a->fun();

    std::thread myThread1(myPrint);
    std::thread myThread2(myPrint);
    myThread1.join();
    myThread2.join();

    // std::call_once(); 该函数的第二个参数是一个函数名a()，能够保证函数a()只被调用一次

    return 0;

}

