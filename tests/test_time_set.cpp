#include <iostream>
#include <set>
#include "../set/set.hpp"

#define SIZE 1000000

typedef std::chrono::microseconds mic;
typedef std::chrono::duration<float> dur;
typedef std::chrono::high_resolution_clock hrc;
typedef std::chrono::steady_clock::time_point t_point;

ft::set<int> set;
std::set<int> s_set;

void InsertFT()
{
	for (int i = 0; i < SIZE; i++)
		set.insert(i);
}

void InsertSTD()
{
	for (int i = 0; i < SIZE; i++)
		s_set.insert(i);
}

void IterationSTD()
{
	std::set<int>::iterator it = s_set.begin();
	for (; it != s_set.end(); ++it)
	;
}

void IterationFT()
{
	ft::set<int>::iterator it = set.begin();
	for (; it != set.end(); ++it)
	;
}

void ClearSTD()
{
	s_set.clear();
}

void ClearFT()
{
	set.clear();
}

void EraseSTD()
{
	std::set<int>::iterator start = s_set.find(1);
	std::set<int>::iterator end = s_set.find(1000000 - 1);
	s_set.erase(start, end);
}

void EraseFT()
{
	ft::set<int>::iterator start = set.find(1);
	ft::set<int>::iterator end = set.find(1000000 - 1);
	set.erase(start, end);
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
	std::cout <<"std:: " << duration_std.count() << "s" << std::endl;
	std::cout.precision(5);	
	std::cout <<"ft::  " << duration_ft.count() << "s" << std::endl;
}

void test_set()
{
    std::cout << "...<test time SET>..." << std::endl;
    Count_time(InsertSTD, InsertFT, "'insert'");
	Count_time(IterationSTD, IterationFT, "'iteration'");
	Count_time(ClearSTD, ClearFT, "'clear'");
	InsertSTD(), InsertFT();
	Count_time(EraseSTD, EraseFT, "'erase'");
}

int main (void){
    test_set();
}