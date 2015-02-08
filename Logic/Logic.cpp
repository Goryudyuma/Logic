// Logic.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"

using namespace System;

int _main(array<System::String ^> ^args)
{
	Console::WriteLine(L"Hello World");
	return 0;
}

#define _crt_secure_no_warnings

#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif


#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

using namespace std;

#define none 0
#define black 1
#define white 2

class data
{
private:
	vector<vector<int>> main_data;
	int length;
	int sum = 0;
public:
	void set_length();
	void set_data();
	void show_data();
	int return_length();
	int return_sum();
	vector<int> return_data_one_line(int);
	void end_data(int);
};

class board
{
private:
	vector<vector<char>> main_board;
	data x, y;
	void rewrite_main_bord(int, int, char);
	void resize_bord(int, int);
	vector<int>serch_and_rewrite_sub(vector<char>, vector<int>, int);
	vector<char> return_bord_one_line(int, int);
public:
	bool rewrite_flag;
	void init();
	void serch_and_rewrite();
	void draw_board();
	void check();
};

void data::set_length()
{
	int n;
	cin >> n;
	if (n % 5)
	{
		cout << "error" << endl;
		exit;
	} else
	{
		length = n;
	}
}

void data::set_data()
{
	main_data.resize(length);
	for (size_t i = 0; i < length; i++)
	{
		int n = 0;
		do
		{
			main_data[i].push_back(n);
			sum += n;
			cin >> n;
		} while (n);
	}
}

void data::show_data()
{
	for (vector <vector<int>>::iterator ite1 = main_data.begin(); ite1 < main_data.end(); ite1++)
	{
		for (vector<int>::iterator ite2 = ite1->begin(); ite2 < ite1->end(); ite2++)
		{
			cout << *ite2 << " ";
		}
		cout << endl;
	}
	cout << sum << endl;
}

int data::return_length()
{
	return length;
}

int data::return_sum()
{
	return sum;
}

vector<int> data::return_data_one_line(int line)
{
	return main_data[line];
}

void data::end_data(int i)
{
	main_data[i][0] = 1;
}

vector<char> board::return_bord_one_line(int x, int y)
{
	if (y == -1)
	{
		return main_board[x];
	} else if (x == -1)
	{
		vector<char> return_vector;
		for (auto i = 0; i < main_board.size(); i++)
		{
			return_vector.push_back(main_board[i][y]);
		}
		return return_vector;
	} else
	{
		cout << "不正な操作" << endl;
		exit;
	}
}

void board::rewrite_main_bord(int x, int y, char z)
{
	if (main_board[x][y] == none && (z == white || z == black))
	{
		cout << x << " " << y << " " << z << " " << (int)main_board[x][y] << endl;
		main_board[x][y] = z;
		rewrite_flag = 1;
	} else
	{
		cout << "指定の方法が違っています。" << endl;
	}
}

void board::resize_bord(int x_length, int y_length)
{
	main_board.resize(x_length);
	for (auto ite = main_board.begin(); ite < main_board.end(); ite++)
	{
		ite->resize(y_length);
	}
}

void board::init()
{
	x.set_length();
	y.set_length();
	x.set_data();
	y.set_data();

	cout << endl;
	x.show_data();
	cout << endl;
	y.show_data();

	if (x.return_sum() != y.return_sum())
	{
		cout << "数がどこか間違ってます。" << endl;
		exit;
	}

	resize_bord(x.return_length(), y.return_length());
}

void board::serch_and_rewrite()
{
	int x_length = x.return_length(), y_length = y.return_length();
	vector<int> clear_data;
	for (size_t i = 0; i < x_length; i++)
	{
		clear_data = serch_and_rewrite_sub(return_bord_one_line(i, -1), x.return_data_one_line(i), y.return_length());
		for (auto ite = clear_data.begin(); ite < clear_data.end(); ite++)
		{
			cout << i << *ite << endl;
			if (main_board[i][*ite] == none)
			{

				rewrite_main_bord(i, *ite, (char)black);
			}
		}
		clear_data.clear();
	}
	for (size_t i = 0; i < y_length; i++)
	{
		clear_data = serch_and_rewrite_sub(return_bord_one_line(-1, i), y.return_data_one_line(i), x.return_length());
		for (auto ite = clear_data.begin(); ite < clear_data.end(); ite++)
		{
			cout << i << *ite << endl;
			if (main_board[*ite][i] == none)
			{
				rewrite_main_bord(*ite, i, (char)black);
			}
		}
		clear_data.clear();
	}
}

vector<int> board::serch_and_rewrite_sub(vector<char> board_one_line, vector<int> data_one_line, int limit)
{
	vector<int>go, come, black_point;
	auto test = [=, &black_point](vector<char> v_c, vector<int> v_i, int limit, bool b)->vector < int > {
		vector<int> v_return;
		int start = 0;
		for (auto ite = v_i.begin() + 1; ite < v_i.end(); ite++)
		{
			bool flag;
			while (1)
			{
				flag = 0;
				bool flag2 = 0;
				int i;
				for (i = start; i < *ite + start; i++)
				{
					if (v_c[i] == white)
					{
						start = i + 1;
						flag = 1;
						break;
					}
					if (ite == v_i.begin() + 1 && i > 0 && i < limit&& v_c[i - 1] == black)
					{
						flag2 = 1;
						if (b)
						{
							black_point.push_back(i);
						} else
						{
							black_point.push_back(limit - i - 1);
						}
					}
				}
				
				if (!flag)
				{
					if (limit <= i || v_c[i] != black)
					{
						v_return.push_back(i - 1);
						start = i + 1;
						break;
					} else
					{
						start++;
					}
				}
			}
		}
		/*cout << endl;
		for (auto ite = v_return.begin(); ite < v_return.end(); ite++)
		{
		cout << *ite << " ";
		}
		cout << endl << endl;*/
		return v_return;
	};

	for (auto x : board_one_line) cout << (int)x;
	cout << endl;
	for (auto x : data_one_line) cout << (int)x;
	cout << endl;


	go = test(board_one_line, data_one_line, limit, 1);
	reverse(board_one_line.begin(), board_one_line.end());
	reverse(data_one_line.begin() + 1, data_one_line.end());
	come = test(board_one_line, data_one_line, limit, 0);
	reverse(come.begin(), come.end());
	cout << endl << "go";
	for (auto x : go)cout << x << " ";
	cout << endl << "come";
	for (auto x : come)cout << x << " ";
	cout << endl << "black_point";


	for (size_t i = 0, x = min(go.size(), come.size()); i < x; i++)
	{
		if (go[i] >= limit - come[i] - 1)
		{
			for (size_t j = limit - come[i] - 1; j <= go[i]; j++)
			{
				black_point.push_back(j);
			}
		}
	}
	for (auto x : black_point)cout << x << " ";
	cout << endl;
	return black_point;
	/*int start=0;
	for (auto ite = data_one_line.begin()+1; ite < data_one_line.end(); ite++)
	{
	cout << *ite;
	bool flag;
	while (1)
	{
	flag = 0;
	int i;
	for (i = start; i < *ite+start; i++)
	{
	if (board_one_line[i] == white)
	{
	start = i + 1;
	flag = 1;
	break;
	}
	}

	if (!flag)
	{
	if (limit<=i|| board_one_line[i] != black)
	{
	go.push_back(i-1);
	start = i+1;
	break;
	} else
	{
	start++;
	}
	}
	}
	}
	cout << endl;
	for (auto ite = go.begin(); ite < go.end(); ite++)
	{
	cout << *ite<<" ";
	}
	cout << endl << endl;;
	return go;
	*/
}

void board::draw_board()
{
	for (size_t j = 0; j < x.return_length(); j++)
	{
		for (size_t i = 0; i < y.return_length(); i++)
		{
			if (main_board[i][j] == black) cout << "■";
			else if (main_board[i][j] == white)cout << "  ";
			else cout << "・";
		}
		cout << endl;
	}
}

void board::check()
{
	vector <int> one_line;
	for (size_t i = 0; i < y.return_length(); i++)
	{
		one_line = x.return_data_one_line(i);
		if (!one_line[0])
		{
			int sum = accumulate(one_line.begin(), one_line.end(), 0);
			int count = 0;
			for (size_t j = 0; j < x.return_length(); j++)
			{
				if (main_board[i][j] == black)
				{
					count++;
				}
			}
			if (count == sum)
			{
				for (size_t j = 0; j < x.return_length(); j++)
				{
					if (main_board[i][j] != black)
					{
						main_board[i][j] = white;
					}
				}
				x.end_data(i);
			}
		}
	}
	for (size_t i = 0; i < x.return_length(); i++)
	{
		one_line = y.return_data_one_line(i);
		if (!one_line[0])
		{
			int sum = accumulate(one_line.begin(), one_line.end(), 0);
			int count = 0;
			for (size_t j = 0; j < y.return_length(); j++)
			{
				if (main_board[j][i] == black)
				{
					count++;
				}
			}
			if (count == sum)
			{
				for (size_t j = 0; j < y.return_length(); j++)
				{
					if (main_board[j][i] != black)
					{
						main_board[j][i] = white;
					}
				}
				y.end_data(i);
			}
		}
	}
}

int main()
{
	board board;
	board.init();
	do
	{
		board.rewrite_flag = 0;
		board.serch_and_rewrite();
		board.draw_board();
		board.check();
	} while (board.rewrite_flag);


	return 0;
}