#include <thread>
#include <iostream>

void do_something(int& i)
{
    ++i; printf("%d, ", i);
}

struct func
{
    int& i;

    func(int& i_):i(i_){}

    void operator()()
    {
        for(unsigned j=0;j<100;++j) 
        {
            do_something(i);
        }
    }
};


void oops()
{
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread my_thread(my_func); printf("After create.\n");

	
	std::thread::id tid1 = my_thread.get_id();
	std::cout << "Tid1 " << tid1 << ".\n";	

	my_thread.detach(); printf("After detach().\n");
	
	std::thread::id tid2 = my_thread.get_id();
	std::cout << "Tid2 " << tid2 << ".\n";	
}

int main()
{
    oops(); 
	std::cout << "After oops().\n"; 
	getchar(); // 假如没有这个的话, 跑完oops()之后程序就退出, for print可能还没有进行完, 这时候就不知道detach的thread是否在执行了.  
	// 加了getchar之后 就有一个等待用户输入, 这时候detach的thread还可以被看到在执行
}

/*
这个程序执行三次，每次的结果都有所不同. 
D:\Users\renc\Documents\GitHub\CppConcurrencyInAction\buildVS\Debug>buildVS.exe
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 2
3, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 4
3, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 6
3, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 8
3, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, After cr
eate.
Tid1 5620.
After detach().
Tid2 0.                       (可以detach之后就是id==0)
After oops().


D:\Users\renc\Documents\GitHub\CppConcurrencyInAction\buildVS\Debug>buildVS.exe
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 2
3, After create.
Tid1 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 2400.                   (这个Tid1 2400.被拆开了.)
After detach().
Tid2 0.
After oops().
34, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 2          (神奇的是i到了34之后就从0重新开始了)
2, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 4
2, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 6
2, 63, 64, 65, 66,                                                                        (结果一共还是100个数字 但是为什么中间从0开始呢? 书上有解释)

D:\Users\renc\Documents\GitHub\CppConcurrencyInAction\buildVS\Debug>buildVS.exe
After create.
Tid1 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1404.
After detach().
Tid2 0.
After oops().
14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 2
2, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 4
2, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 6
2, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 8
2, 83, 84, 85, 86,

D:\Users\renc\Documents\GitHub\CppConcurrencyInAction\buildVS\Debug>

*/ 