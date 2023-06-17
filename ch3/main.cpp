//
// Created by bing on 2023/6/17.
//

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
            std::unique_lock<std::mutex> lock(m_mutex);
            msgRecvQueue.push_back(i);
            std::cout << "insert a value = " << i << std::endl;
        }
    }

    void outMsgQueue() {
        for (int i = 0; i < 100; i++) {
            std::unique_lock<std::mutex> lock(m_mutex);
            if (!msgRecvQueue.empty()) {
                int val = -1;
                val = msgRecvQueue.front();
                msgRecvQueue.pop_front();
                std::cout << "Delete a value = " << val << std::endl;
            }

        }
    }

private:
    std::list<int> msgRecvQueue;
    std::mutex m_mutex;;
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
    std::thread myThread(&A::inMsgRecvQueue, &myobj);
    std::thread myThread2(&A::outMsgQueue, &myobj);
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