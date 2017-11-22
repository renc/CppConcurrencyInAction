#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>

// unique function to avoid disambiguating the std::pow overload set
int f(int x, int y) { return (int)std::pow(x, y); }

void task_lambda()
{
	std::packaged_task<int(int, int)> task([](int a, int b) {
		return (int)std::pow(a, b);
	});
	std::future<int> result = task.get_future();

	task(2, 8);

	std::cout << "task_lambda:\t" << result.get() << '\n';
}

void task_bind()
{
	std::packaged_task<int()> task(std::bind(f, 2, 9));
	std::future<int> result = task.get_future();

	task();

	std::cout << "task_bind:\t" << result.get() << '\n';
}

void task_thread()
{
	std::packaged_task<int(int, int)> task(f);
	std::future<int> result = task.get_future();

	std::thread task_td(std::move(task), 2, 10);
	task_td.join();

	std::cout << "task_thread:\t" << result.get() << '\n';
}


void task_promise()
{
	std::promise<int> pro;
	std::future<int> result = pro.get_future();

	std::thread task_td(
		[] (int a, int b, std::promise<int> pro) 
		{
			int c = (int)std::pow(a, b);
			pro.set_value(c);
		}
		, 2, 10, std::move(pro));
	task_td.join();

	std::cout << "task_promise:\t" << result.get() << '\n';
}

int main()
{
	task_lambda();
	task_bind();
	task_thread();
	task_promise();
	system("pause");
}



