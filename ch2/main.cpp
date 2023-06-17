//
// Created by bing on 2023/6/15.
//

#include "iostream"
#include "thread"

void myprint(const int i, char *pmybuf) {
    std::cout << "i = " << i << std::endl;
    std::cout << pmybuf << std::endl;
}

void myPrint(std::unique_ptr<int> ptn) {
    std::cout << "*pth = " << *ptn << std::endl;
    std::cout << "thread = " << std::this_thread::get_id() << std::endl;
}

int main() {
//    int mvar = 1;
//    int &mvary = mvar;
//    char mybuf[] = "this is a test!";
//    std::thread mytobj(myprint, mvar, mybuf);
//    mytobj.join();


    std::unique_ptr<int> up(new int (10));
    //独占式指针只能通过std::move()才可以传递给另一个指针
    //传递后up就指向空，新的ptn指向原来的内存
    //所以这时就不能用detach了，因为如果主线程先执行完，ptn指向的对象就被释放了
    std::thread myThread(myPrint, std::move(up));
    myThread.join();

    std::cout << "main thread end!" << std::endl;

    return 0;
}

