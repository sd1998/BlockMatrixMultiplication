#include <iostream>
#include <vector>
#include <ctime>
#include <pthread.h>
#include <string>
#include <fstream>

using namespace std;

vector<vector<int> > a;
vector<vector<int> > b;
vector<vector<int> > c;

void * function1(void *data){
	int m = a.size();
	int n = b[0].size();
	int k = (a.size())/4;
	for(int i = 0;i <= k;i++){
		for(int j = 0;j <= n-1;j++){
			for(int l = 0;l <= b.size()-1;l++){
				c[i][j] = c[i][j] + a[i][l] * b[l][j];
			}
		}
	}
}

void * function2(void *data){
	int m = a.size();
	int n = b[0].size();
	int k = (a.size())/2 + 1;
	int s = ((a.size())/4) + 1;
	for(int i = s;i <= k-1;i++){
		for(int j = 0;j <= n-1;j++){
			for(int l = 0;l <= b.size()-1;l++){
				c[i][j] = c[i][j] + a[i][l] * b[l][j];
			}
		}
	}
}

void * function3(void *data){
	int m = a.size();
	int n = b[0].size();
	int k = ((3*(a.size()))/4) + 1;
	int s = (a.size())/2 + 1;
	for(int i = s;i <= k-1;i++){
		for(int j = 0;j <= n-1;j++){
			for(int l = 0;l <= b.size()-1;l++){
				c[i][j] = c[i][j] + a[i][l] * b[l][j];
			}
		}
	}
}

void * function4(void *data){
	int m = a.size();
	int n = b[0].size();
	int k = ((3*(a.size()))/4) + 1;
	for(int i = k;i <= m-1;i++){
		for(int j = 0;j <= n-1;j++){
			for(int l = 0;l <= b.size()-1;l++){
				c[i][j] = c[i][j] + a[i][l] * b[l][j];
			}
		}
	}
}

vector<vector<int> > loadMatrix(string path){
	ifstream in(path);
	int a,b;
	in >> a >> b;
	vector<vector<int> > m(a,vector<int>(b,0));
	for(int i = 0 ;i <= a-1;i++){
		for(int j = 0;j <= b-1;j++){
			in >> m[i][j];
		}
	}
	return m;
}

void storeMatrix(string path){
	int a = c.size();
	int b = c[0].size();
	ofstream f(path);
	f << a << " " << b << "\n";
	for(int i = 0;i <= a-1;i++){
		for(int j = 0;j <= b-1;j++){
			f << c[i][j];
			f << " ";
		}
		f << "\n";
	}
}

int main(){
	pthread_t thread[4];
	time_t timer;
	long long int sysTime = time(&timer);
	a = loadMatrix("/Users/shashvatkedia/Desktop/2000.txt");
	b = loadMatrix("/Users/shashvatkedia/Desktop/2000.txt");
	c.resize(a.size());
	for(int i = 0;i <= a.size()-1;i++){
		c[i].resize(b[0].size());
	}
	pthread_create(&thread[0],NULL,function1,NULL);
	pthread_create(&thread[1],NULL,function2,NULL);
	pthread_create(&thread[2],NULL,function3,NULL);
	pthread_create(&thread[3],NULL,function4,NULL);
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[2],NULL);
	pthread_join(thread[3],NULL);
	storeMatrix("/Users/shashvatkedia/Desktop/c.txt");
	long long int sysTimee = time(&timer);
	cout << sysTimee - sysTime << "\n";
	return 0;
}