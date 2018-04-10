#include <iostream>
#include <map>
#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <assert.h>
  
using namespace std;

int random(float min, float max){
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void roll(int count){
	int a[6] = {0,0,0,0,0,0};
	for(int i = 0; i < count; i++){
		a[random(1,6)-1] += 1;
	}
	for(int i = 0; i < 6; i++){
		cout << i+1 << ": " <<  (float)a[i]/(float)count << endl;
	}
}

void rollSplit(int count){
	float counter = 0;
	for(int j = 0; j < count; j++){
		int a[2] = {0,0};
		for(int i = 0; i < 100; i++){
			random(1,6) > 3? a[1] += 1: a[0] += 1;
		}
		if(a[1] == a[0]){
			counter += 1;
			// cout << a[1] << '\t' << a[0] << '\t' << counter << '\n';
			}
	}	
	assert(counter <= count);  
  cout << counter/(float)count << endl;
}

void rollTwo(int count){
	map <int, int> a;
	for(int i = 2; i <= 12; i++){
		a[i] = 0;
	}
  for(int i = 0; i < count; i++){
    a[random(1,6)+random(1,6)] += 1;
	}
  for(int i = 2; i <= 12; i++){
		assert(a[i] <= count);
    cout << i << ": " << (float)a[i]/(float)count << endl;
  }
}

int main(){
	//cout << "DICE\n";
	srand (time(NULL));
	cout << "Question 1:\n10 times\n";
	roll(10);
	cout << "1000 times:\n";
  roll(1000);
	cout << "1000000 times:\n";
  roll(1000000);
	//cout << "1 x 100 rolls SPLIT:\n";
  //rollSplit(1);
	cout << "Question 2:\n";
	rollSplit(10000);
	cout << "Question 3:\n";
	rollTwo(10000);
	//rollTwo(100000);
	//rollTwo(1000000);
	//rollTwo(100);
	//rollTwo(500);
	cout.flush();
	//cout << endl;
}
