#include <iostream>
#include <stack>
#include <vector>
#include "../stack/stack.hpp"
#include "../vector/vector.hpp"

#define SIZE 100000000

typedef std::chrono::microseconds mic;
typedef std::chrono::duration<float> dur;
typedef std::chrono::high_resolution_clock hrc;
typedef std::chrono::steady_clock::time_point t_point;

std::stack<int, std::vector<int> > std_st;
ft::stack<int, ft::vector<int> > ft_st;

void PushSTD()
{
	for (int i = 0; i != SIZE; i++)
		std_st.push(i);
}

void PushFT()
{
	for (int i = 0; i != SIZE; i++)
		ft_st.push(i);
}

void PopSTD()
{
	for (int i = 0; i != SIZE; i++)
		std_st.pop();
}

void PopFT()
{
	for (int i = 0; i != SIZE; i++)
		ft_st.pop();
}

void Count_time(std::function<void()> f, std::function<void()> f1, const std::string& msg)
{
	t_point start;
	t_point end;

	std::cout <<"Test " << msg << std::endl;
	start = hrc::now();
	f();
	end = hrc::now();
	dur duration_std = end - start;
	
	start = hrc::now();
	f1();
	end = hrc::now();
	dur duration_ft = end - start;

	std::cout.precision(5);	
	std::cout <<"std::" << duration_std.count() << "s" << std::endl;
	std::cout.precision(5);	
	std::cout <<"ft::" << duration_ft.count() << "s" << std::endl;
}

void test_stack()
{
    std::cout <<"...<test time STACK>..." <<std::endl;
	Count_time(PushSTD, PushFT, "'push'");
	Count_time(PopSTD, PopFT, "'pop'");
}

int main (void){
    test_stack();
}