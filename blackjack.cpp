//single deck black jack probability
#include <iostream>
#include <stdlib.h>
#include <deque>
#include <stack>
using namespace std;

int cards[] = {11,11,11,11,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
int con;
deque<int> usedCard;


void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomize ( int arr[], int n )
{
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );
 
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);
 
        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}

int pickCard(){

	int current = cards[con];
	con++;

	return current;

}


int hit(int sum){
	sum = sum + pickCard();
	return sum;

}


int Sum(int card1, int card2){
	int sum = card1 + card2;
	return sum;
}


int basicStaragy(int pSum, int dealerC1){
	
		if((pSum >= 5 && pSum <= 7) || (pSum == 8 && (dealerC1 < 5 || dealerC1 > 6)) || 
		  (pSum == 9 && dealerC1 > 7) || (pSum == 10 && dealerC1 > 9) || (pSum == 12 && (dealerC1 < 4 || dealerC1 > 6)) ||
	   	  ((pSum == 13 || pSum == 14 || pSum == 15) && ((dealerC1 > 6)&& (dealerC1 < 10))))
			{
				pSum = hit(pSum);
				return basicStaragy(pSum, dealerC1);
			}else {
				return pSum;
			}
		  

}

int dealer (int sum, bool soft){

	while(sum < 17){
		sum = hit(sum);
	}
	if(sum > 21 && soft == true){
		sum = sum -10;
		return dealer(sum, false);
	}
	 return sum;
}



int main(){
	int deck[] = {11,11,11,11,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};

	int playerC1, playerC2, dealerC1, dealerC2;
	int player, dealerf;
	double win = 0.0;
	double draw = 0.0; 
	double total = 0.0;
	double winRate = 0.0;
	bool dSoft = false;
	bool pSoft = false;

	randomize(cards,52);




	for(int i = 0; i < 500; i++){

		randomize(cards,52);
		con = 0;
		cout << "the deck has been shuffled" << endl;
			for(int i = 0; i < 2; i ++){

				playerC1 = pickCard();
				dealerC1 = pickCard();
				playerC2 = pickCard();
				dealerC2 = pickCard();

				int pSum = Sum(playerC1, playerC2);
				int dSum = Sum(dealerC1, dealerC2);

				if(dealerC1 == 11 || dealerC2 == 11)
					dSoft = true;
				if(playerC1 == 11 || playerC2 == 11)
					pSoft = true;

				player = basicStaragy(pSum, dealerC1);
				dealerf = dealer(dSum,dSoft);

				if((player > dealerf && player <= 21) || (player <= 21 && dealerf > 21 ) )
					win = win + 1;
				if(player == dealerf || (player > 21 && dealerf > 21))
					draw = draw + 1;

				total = total +1;
				cout << player << " " << dealerf  << endl;
			}

	}

	cout << win <<" " << draw << " "<< total <<endl;
	
	winRate = win/(total - draw);
	cout << winRate << endl;
	
	

	return 0;

}









