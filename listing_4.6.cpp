#include <future>
#include <iostream>

int find_the_answer_to_ltuae()
{
    return 42;
}

void do_other_stuff()
{}

int main()
{
    std::future<int> the_answer=std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    std::cout<<"The answer is "<<the_answer.get()<<std::endl;

	//
	double a = 1 / 3; a;
	if (a = 0.0)
	{
		int x = 1;
		int y = x;
		++y; 
	}  

	// renc: code from https://bartoszmilewski.com/2011/10/10/async-tasks-in-c11-not-quite-there-yet/ 
	std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;
	std::vector<std::future<void> > futures;
	for (int i = 0; i < 20; ++i)
	{ 
		// renc: if std::launch enum is not used at the std::async(), implemnent depend. 
		// if use std::launch::deferred, or std::launch::async, the results are different. 
		auto fut = std::async([]
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << std::this_thread::get_id() << " ";
		});
		futures.push_back(std::move(fut));
	}
	std::for_each(futures.begin(), futures.end(), [](std::future<void> & fut)
	{
		fut.wait();
	});
	std::cout << std::endl;


}
