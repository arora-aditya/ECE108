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

struct pack{
	int arr[52];
	int remainingCards;
	int runningCount;
	pack(){
		remainingCards = 51;
		for(int i = 0; i <= remainingCards; i++){
			arr[i] = (i+1)%13;
			//cout << arr[i];
		}
		runningCount = 0;
	}
	
	int remaining(){
		return remainingCards + 1;
	}

	bool empty(){
		return remainingCards == -1;
	}	
	
	int deal(){
		if(remainingCards == -1){
			remainingCards = 51;
			for(int i = 0; i <= remainingCards; i++){
				arr[i] = (i+1)%13;
			}
			//cout << "SHUFFLE";
			int i = remainingCards + 1;
			this->shuffle();
			runningCount = 0;	
		}
		remainingCards -= 1;
		int k = arr[remainingCards + 1];
		switch(k){
			case 1:
			case 2:
			case 3:
			case 4:
			case 5: runningCount -= 1; break;
			case 6:
			case 7:
			case 8: break;
			case 9:
			case 10:
			case 11:
			case 12:
			case 0: runningCount += 1; break;
		}
		return k;
	}
	
	int shuffle(){
		//cout << endl << endl << "::::";
		//srand((unsigned int)time(NULL));
		int i = remainingCards + 1;
		while(i){
			int t = random(0, i);
			i -= 1;
			int r = arr[i];
			arr[i] = arr[t];
			arr[t] = r; 
		} 

	}
	
	void print(){
		for(int i = 0; i <= remainingCards; i++){
      cout << arr[i] << '\t';
			if((i+1)%13 == 0){
				cout << endl;
			}
    }
		cout << endl;
	}
		
};

struct hand{
	int arr[52];
	int size;
	int handValue;
	int deckValue;
	int thresh;
	int aceCount;
	
	hand(){
		for(int i = 0; i < 52; i++){
      arr[i] = 0;
    }
    size = 0;
    deckValue = 0;
    handValue = 0;
    aceCount = 0;
    thresh = -1;
	}	
	
	hand(int threshold){
		for(int i = 0; i < 52; i++){
			arr[i] = 0;
		}
		size = 0;
		deckValue = 0;
		handValue = 0;
		aceCount = 0;
		thresh = threshold;
	}

	bool thresholdReached(){
		return handValue >= thresh;
	}
	
	int state(){
		if(handValue > 21){
			return -1;
		}
		else if(handValue >= thresh){
			return 0;
		}
		else{
			return 2;
		}
	}
	
	void print(){
		for(int i = 0; i < size; i++){
			int k = arr[i];
			cout << k << '\t';
		}
		cout << handValue << '\t' << aceCount << endl;
	}

	bool operator>(hand B){
		if(this->state() == -1){
			return false;
		}
		if(B.state() == -1){
			return true;
		}
		return this->handValue >= B.handValue;
	}
	
	void addCard(int card){
		assert(handValue <= 21);
		arr[size] = card;
		size += 1;	
		int val;
		switch(card){
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:val = card; break;
			case 10:
			case 11:
			case 12:val = 10; break;
			case 0: val = 11; aceCount += 1; break;
		}
		if(val + handValue == thresh){
			handValue = thresh;
			return;
		}
		if(val + handValue > thresh){
			if(aceCount == 0){
				handValue = val + handValue;
				return;
			}
			else{
				aceCount -= 1;
				handValue -= 10;
				handValue = val + handValue;
				return;
			}		
		}
		else{
			handValue = val + handValue;
			return;
		}
	}
		

};

void blackJack(){
	int count = 0;
	pack P;
	P.shuffle();
	for(int i = 0; i < 10000; i++){
		int bet = 0;

		if(P.runningCount > 2){
			bet = 1;
		}
		else if(P.runningCount < -2){
			bet = -1;
		} 		
		hand dealer(17);
		hand P1;
		hand P2;
		hand P3;
		hand C(18);
		dealer.addCard(P.deal());
		P1.addCard(P.deal());P1.addCard(P.deal());
		P2.addCard(P.deal());P2.addCard(P.deal());
		P3.addCard(P.deal());P3.addCard(P.deal());

		while(C.thresholdReached() == false){
			int k = P.deal();
      C.addCard(k);
	  }
		if(C.state() == -1){
			//continue;
		}	
		while(dealer.thresholdReached() == false){
			int k = P.deal();
      dealer.addCard(k);
		}
		//cout << "C: ";
    //C.print();
    //cout << "dealer: ";
    //dealer.print();
    //cout << "P1: ";
    //P1.print();
    //cout << "P2: ";
    //P2.print();
    //cout << "P3: ";
    //P3.print();
		if(C>dealer){
			if(bet == 1){
				count += 1;
			}
		}
		else if(dealer > C){
			if(bet == -1){
				count += 1;	
			}
		}
	}
	cout << (float)count/10000 << endl;
}


int main(){
	cout << "Question 4:\n";
  srand((unsigned int)time(NULL));	
	hand H(10);
	pack P;
	P.shuffle();
	int bust = 10;
	for(; bust < 21;bust++){
		int count = 0;
		for(int i = 0; i < 10000; i++){
			//P = pack();
			//P.shuffle();
			while(H.thresholdReached() == false){
				int k = P.deal();
				H.addCard(k);
			}
			if(H.thresholdReached()){
				if(H.state() == -1){
					count += 1;
				// H.print();
				// cout << count << endl;
				}
				H = hand(bust);
			}
			// P.shuffle();
		}

	cout << bust<<": " << (float)count/10000 << endl;
	}
	cout << "Question 5:\n";
	blackJack();
	cout.flush();
	//cout << endl;
	return 0;
}
