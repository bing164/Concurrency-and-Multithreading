//
// Created by bing on 2023/6/15.
//

#include "iostream"
#include "thread"

class TA {
public:
    TA(int i) : m_i(i) {}
    void operator() () {
        std::cout << "start thread 2" << std::endl;
        std::cout << "mi = " << m_i << std::endl;
    }

public:
    int m_i;
};

void myprint() {
    std::cout << "start...." << std::endl;

    std::cout << "end......" << std::endl;
}

int main(int argc, char** argv) {
    /// 1. creat a thread;
    std::thread myThread(myprint);

    if (myThread.joinable()) {  // joinable():是否能够成功使用join(),detach()。返回true/false。
        std::cout << "joinable = true" << std::endl;
    }
//    myThread.join();       // 等待子线程执行完毕
    myThread.detach();     // 将子线程和主线程分离。一旦dectach()之后，与这个主线程关联的thread对象就会失去这个主线程关联，
                           // 此时这个子线程就会驻留在后台，这个子线程就相当于被C++的运行时库接管，
                           // 当这个子线程执行完毕后，由运行时库负责清理该线程相关的资源



    /// 2. creat a thread;
    int m = 6;
    TA ta(m);
    std::thread myThread2(ta);
    myThread2.join();

    std::cout << "main thread....." << std::endl;
    return 0;
}

