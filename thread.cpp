// g++ -std=c++11 thread.cpp -o thread -pthread
#include <bits/stdc++.h>
#include <thread>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <resolv.h>

#define rep(i,n)                for(int i = 0; i < (int)n; ++i)

using namespace std;

vector<int> 		_a;
vector<int>			_listMain;
vector<int> 		_listFile;

struct timeval		_timeout;

void main_Thread()
{
	struct timeval _time  = _timeout;
	int _numEven 		  = 0;
	while (_listMain.size() < 5){
		_time.tv_sec 	= 3;
		_time.tv_usec 	= 0;
		select(0, NULL, NULL, NULL, &_time);
		cout <<"This is main thread!!!! " << _listMain.size() << endl;

		rep(i, _a.size())
			if (_a[i] % 2 == 0)
				_numEven++;
		_listMain.emplace_back(_numEven);	
	}
}


void file_Thread()
{
	struct timeval _time  = _timeout;
	int _numOld		 	  = 0;
	while (_listFile.size() < 5){
		_time.tv_sec 	= 2;
		_time.tv_usec 	= 0;
		select(0, NULL, NULL, NULL, &_time);
		cout <<"This is file thread!!!! " << _listFile.size() << endl;

		rep(i, _a.size())
			if (_a[i] % 2 == 1)
				_numOld++;
		_listFile.emplace_back(_numOld);
	}
}

int main(){

	_timeout.tv_sec 		= 2;
	_timeout.tv_usec 		= 0; 

	thread _taskMain(main_Thread);
	thread _taskFile(file_Thread);

	struct timeval _time;
	while (_a.size() < 10){
		cout <<"Main Thread!!!!" << _a.size() << endl;
		_time.tv_sec 	= 1;
		_time.tv_usec 	= 0;
		int _value 		= _a.size() + 1;
		select(0, NULL, NULL, NULL, &_time);
		_a.emplace_back(_value);
	}

	if (_taskMain.joinable()){
		_taskMain.join();
	}
	
	if (_taskFile.joinable()){
		_taskFile.join();
	}

	cout <<"ok";
	return 0;
}