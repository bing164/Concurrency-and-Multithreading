//
// Created by bing on 2023/6/17.
//

#include <condition_variable>
#include "iostream"
#include "thread"
#include "vector"
#include "mutex"
#include "list"


//std::vector<int> vec{1,2,3};
//std::mutex m_read;
//
//void myPrint(int i) {
//    std::unique_lock<std::mutex> lock(m_read);
//    std::cout << "this is " << i << "th thread!!!" << std::endl;
//    std::cout << "the thread id = " << std::this_thread::get_id()
//                << " " << vec[0] << vec[1] << vec[2] << std::endl;
//    return;
//}


class A {
public:
    void inMsgRecvQueue() {
        for (int i = 0; i < 100; i++) {
            std::cout << "insert a value = " << i << std::endl;
            std::unique_lock<std::mutex> lock(m_mutex);
            msgRecvQueue.push_back(i);
            my_cond.notify_one();
        }
    }

    void outMsgQueue() {
        int command = 0;
        while (true) {
            std::unique_lock<std::mutex> sbguard1(m_mutex);
            // 如果第二个参数lambda表达式返回值是false,那么wait()将解锁互斥量，并堵塞到本行
            // 堵塞到其他线程调用notify_one()成员函数为止
            // 如果wait()没有第二个参数，那么就和第二个参数lambda表达式参数返回false一样
            // 当其他程序调用notify_one()，唤醒wait(),
            // a) wait()开始不断尝试重新获取互斥量锁,如果获取不到，那么流程就卡在这等待，如果获取到了，那么wait就继续执行b
            // b)
            //    b1) 如果wait有第二个参数，且为false，则重复上面的状态，等待notify_one()
            //    b2) 如果lambda表达式为true,则wait返回，流程继续往下走(此时互斥量是锁着的)
            my_cond.wait(sbguard1, [this] {
                if (!msgRecvQueue.empty())
                    return true;
                else return false;
            });
        }


//        for (int i = 0; i < 100; i++) {
//            if (!msgRecvQueue.empty()) {
//                std::unique_lock<std::mutex> lock(m_mutex);
//                if (!msgRecvQueue.empty()) {
//                    int val = -1;
//                    val = msgRecvQueue.front();
//                    msgRecvQueue.pop_front();
//                    std::cout << "Delete a value = " << val << std::endl;
//                }
//            }
//        }
    }

private:
    std::list<int> msgRecvQueue;
    std::mutex m_mutex;
    std::condition_variable my_cond;
};


int main() {
//    std::vector<std::thread> threads;
//    threads.reserve(10);
//    for (int i = 0; i < 10; i++) {
//        threads.push_back(std::thread(myPrint, i));
//    }
//    for (auto it = threads.begin(); it != threads.end(); it++) {
//        it->join();
//    }

    A myobj;
    std::thread myThread2(&A::outMsgQueue, &myobj);
    std::thread myThread(&A::inMsgRecvQueue, &myobj);
    myThread.join();
    myThread2.join();



//    死锁：
//    两个线程A，B。两个锁：金锁，银锁。
//    1. 线程A执行时，线程A先锁金锁，把金锁lock()成功后，然后去锁银锁。
//    此时出现了上下文切换。
//    2. 线程B执行了，这个线程先锁银锁，因为银锁还没有被锁，所以银锁会lock()成功，线程B要去锁金锁，此时便出现了死锁。
//    3. 线程A因为拿不到银锁头，流程走不下去，（所有后面代码有解锁金锁头的但是流程走不下去，所以金锁头解不开）
//    4. 线程B因为拿不到银锁头，流程走不下去，（所有后面代码有解锁银锁头的但是流程走不下去，所以银锁头解不开）
    std::cout << "This is main thread!" << std::endl;
    return 0;
}