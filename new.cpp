#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<thread>
#include <utility>
#include<algorithm>
#include <chrono>
#include <time.h>

using namespace std;
using namespace chrono;
static const int numthread = 1;
vector<pair<string, int>> b_vec;

vector<string> input_reader(string filename)
{
	vector<string> a;
	ifstream file(filename);
	string s;
	while (file >> s)
	{
		a.push_back(s);
	}
	return a;
}

pair<string, int> map(string input)
{

	
	pair<string, int> p;
	p = make_pair(input, 1);
	b_vec.push_back(p);
	return p;
	
}

pair<string, int> reduce(pair<string, int>& p)
{
	p.second++;
	return p;
}

void output(vector<pair<string, int>> vec)
{
	vector<int> p_val;
	for (int i = 0; i < vec.size(); i++)
	{
		p_val.push_back(vec[i].second);
	}

	vector<pair<string, int>> b_vec3;  //in count order
	int biggest;
	while (p_val.size() > 0)
	{
		biggest = distance(p_val.begin(), max_element(p_val.begin(), p_val.end()));
		b_vec3.push_back(vec[biggest]);
		p_val.erase(p_val.begin() + biggest);
		vec.erase(vec.begin() + biggest);
	}

	for (int i = 0; i < b_vec3.size(); i++)
	{
		cout << b_vec3[i].first << ":" << b_vec3[i].second << endl;
	}
}


int main()
{
	auto start = system_clock::now();
	vector<string> a = input_reader("text.txt");
	thread mythread[numthread];
	
	for (int i = 0; i < a.size(); i = i + numthread)
	{
		for (int j = 0; j < numthread;j++){

			mythread[j] = thread(map, a[j]);
			mythread[j].join();
		}
	}
	
	
		
	auto start2 = system_clock::now();
	vector<pair<string, int>> b_vec2;
	for (int i = 0; i < b_vec.size(); i++)
	{
		for (int j = i + 1; j < b_vec.size(); j++)
		{
			if (b_vec[j].first == b_vec[i].first)
			{
				reduce(b_vec[i]);
				b_vec.erase(b_vec.begin() + j);
				j--;
			}
		}
		b_vec2.push_back(b_vec[i]);
	}
	
	output(b_vec2);
	

	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << endl << "time cost: " << double(duration.count()) << " microseconds" << endl;


	auto duration1 = duration_cast<microseconds>(start2 - start);
	cout << endl << "map time cost: " << double(duration1.count()) << " microseconds" << endl;

	auto duration2 = duration_cast<microseconds>(end - start2);
	cout << endl << "reduce time cost: " << double(duration2.count()) << " microseconds" << endl;

	
	system("pause");
}