//
// Created by bing on 2023/6/27.
//

#include <future>
#include "iostream"
#include "thread"

int myThread() {
    std::cout << "Start thread id = " << std::this_thread::get_id() << std::endl;
    std::chrono::milliseconds duration(5000);
    std::this_thread::sleep_for(duration);
    std::cout << "End thread id = " << std::this_thread::get_id() << std::endl;

    return 5;
}

int main() {
    /// 1. std::async、std::future创建后台任务并返回值
    // std::async是一个函数模板，用来启动一个异步任务，返回std::future对象
    // 什么叫启动一个异步任务，就是创建一个线程并开始执行对应的线程入口函数,返回std::future对象(含有线程入口函数的返回结果),可使用get()函数获取
    std::cout << "main thread id = " << std::this_thread::get_id() << std::endl;
    std::future<int> result = std::async(myThread);
    std::cout << "Continue...." << std::endl;
    int def;
    def = 1;
    std::cout << result.get() << std::endl;   // result.wait()只会等待线程，不会返回结果
    std::cout << "Main thread is finished!!!!!" << std::endl;


    return 0;
}

