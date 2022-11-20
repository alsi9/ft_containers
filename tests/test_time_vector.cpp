#include <iostream>
#include <vector>
#include "../vector/vector.hpp"

#define SIZE 100000000

typedef std::chrono::microseconds mic;
typedef std::chrono::duration<float> dur;
typedef std::chrono::high_resolution_clock hrc;
typedef std::chrono::steady_clock::time_point t_point;

std::vector<int> std_vec(SIZE);
ft::vector<int> ft_vec(SIZE);

void IterationSTD()
{
	std::vector<int>::iterator it;
	it = std_vec.begin();
	for (int i = 0; it != std_vec.end(); i++, it++) {
		*it = i;
	}
	return ;
}

void IterationFT()
{
	ft::vector<int>::iterator it;
	it = ft_vec.begin();
	for (int i = 0; it != ft_vec.end(); i++, it++) {
		*it = i;
	}
	return ;
}

void EraseSTD()
{
	std_vec.erase(std_vec.begin(), std_vec.end());
}

void EraseFT()
{
	ft_vec.erase(ft_vec.begin(), ft_vec.end());
}

void InsertSTD()
{
	std_vec.insert(std_vec.begin(), SIZE, 7);
}

void InsertFT()
{
	ft_vec.insert(ft_vec.begin(), SIZE, 7);
}

void AssignFT()
{
	ft_vec.assign(SIZE, 5);
}

void AssignSTD()
{
	std_vec.assign(SIZE, 5);
}

void ClearFT()
{
	ft_vec.clear();
}

void ClearSTD()
{
	std_vec.clear();
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

void test_vector()
{
    std::cout <<"...<test time VECTOR>..." <<std::endl;
    Count_time(IterationSTD, IterationFT, "'iteration'");
	Count_time(EraseSTD, EraseFT, "'erase'");
	Count_time(InsertSTD, InsertFT, "'insert'");
	Count_time(AssignSTD, AssignFT, "'assign'");
	Count_time(ClearSTD, ClearFT, "'clear'");
}

int main (void){
    test_vector();
}