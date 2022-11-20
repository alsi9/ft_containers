#include <iostream>
#include <map>
#include "../map/map.hpp"

#define SIZE 1000000

typedef std::chrono::microseconds mic;
typedef std::chrono::duration<float> dur;
typedef std::chrono::high_resolution_clock hrc;
typedef std::chrono::steady_clock::time_point t_point;

ft::map<int, int> map;
std::map<int, int> s_map;

void InsertFT()
{
	for (int i = 0; i < SIZE; i++)
		map.insert(ft::make_pair(i, i));
}

void InsertSTD()
{
	for (int i = 0; i < SIZE; i++)
		s_map.insert(std::make_pair(i, i));
}

void IterationSTD()
{
	std::map<int, int>::iterator it = s_map.begin();
	for (; it != s_map.end(); ++it)
	;
}

void IterationFT()
{
	ft::map<int, int>::iterator it = map.begin();
	for (; it != map.end(); ++it)
	;
}

void ClearSTD()
{
	s_map.clear();
}

void ClearFT()
{
	map.clear();
}

void EraseSTD()
{
	std::map<int, int>::iterator start = s_map.find(1);
	std::map<int, int>::iterator end = s_map.find(1000000 - 1);
	s_map.erase(start, end);
}

void EraseFT()
{
	ft::map<int, int>::iterator start = map.find(1);
	ft::map<int, int>::iterator end = map.find(1000000 - 1);
	map.erase(start, end);
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
	std::cout <<"ft:: " << duration_ft.count() << "s" << std::endl;
}

void test_map()
{
    std::cout << "...<test time MAP>..." << std::endl;
    Count_time(InsertSTD, InsertFT, "'insert'");
	Count_time(IterationSTD, IterationFT, "'iteration'");
	Count_time(ClearSTD, ClearFT, "'clear'");
	InsertSTD(), InsertFT();
	Count_time(EraseSTD, EraseFT, "'erase'");
}

int main (void){
    test_map();
}