//
//  main.cpp
//  VideoPoker
//
//  Created by sjpark on 2015. 5. 15..
//  Copyright (c) 2015년 sjpark. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#ifdef __APPLE__
typedef __int64_t __int64;
#endif
#ifdef linux
#include <stdio.h>
#include "VideoPoker.h"
typedef __int64_t __int64;
#endif
typedef struct _CARD{
    int number;
    int type;
}CARD;

bool OnePair(CARD *card)
{
    bool result = false;
    if(card[0].number == card[1].number || card[1].number == card[2].number || card[2].number == card[3].number || card[3].number == card[4].number){
        result = true;
    }
    return result;
}
bool JackBetter(CARD *card)
{
    bool result = false;
	if((card[0].number == card[1].number && (card[0].number >= 11 || card[0].number == 1)) || (card[1].number == card[2].number && (card[1].number >= 11 || card[1].number == 1)) || (card[2].number == card[3].number && (card[2].number >= 11 || card[2].number == 1)) || (card[3].number == card[4].number && (card[3].number >= 11 || card[3].number == 1))){
        result = true;
	}
    return result;

}
bool TwoPair(CARD *card)
{
    bool result = false;
    if((card[0].number == card[1].number && card[2].number == card[3].number) || (card[0].number == card[1].number && card[3].number == card[4].number) || (card[1].number == card[2].number && card[3].number == card[4].number)){
        result = true;
    }
    return result;
}
bool Triple(CARD *card)
{
    bool result = false;
    if(card[0].number == card[2].number || card[1].number == card[3].number || card[2].number == card[4].number){
        result = true;
    }
    return result;
}
bool Flush(CARD *card)
{
    bool result = false;
    if(card[0].type == card[1].type && card[0].type == card[2].type && card[0].type == card[3].type && card[0].type == card[4].type){
        result = true;
    }
    return result;
}
bool Straight(CARD *card)
{
    bool result = false;
    if(card[0].number == card[1].number-1 && card[1].number == card[2].number-1 && card[2].number == card[3].number-1 && card[3].number == card[4].number-1){
        result = true;
    }
    else if(card[0].number == 1 && card[1].number == 10 && card[2].number == 11 && card[3].number == 12 && card[4].number == 13){
        result = true;
    }
    return result;
}
bool FullHouse(CARD *card)
{
    bool result = false;
    if((card[0].number == card[2].number && card[3].number == card[4].number) || (card[0].number == card[1].number && card[2].number == card[4].number)){
        result = true;
    }
    return result;
}
bool FourCARD(CARD *card)
{
    bool result = false;
    if(card[0].number == card[3].number || card[1].number == card[4].number){
        result = true;
    }
    return result;
}
bool StraightFlush(CARD *card)
{
    bool result = false;
    if(Flush(card)){
        if(Straight(card)){
            result = true;
        }
    }
    return result;
}
bool RoyalFlush(CARD *card)
{
    bool result = false;
    if(Flush(card)){
        if(card[0].number == 1 && card[1].number == 10 && card[2].number == 11 && card[3].number == 12 && card[4].number == 13){
            result = true;
        }
    }
    return result;
}
int ReturnCredit(CARD *card, int bet)
{
    int result;
    if(RoyalFlush(card)){
        result = bet * 800;
    }
    else if(StraightFlush(card)){
        result = bet * 50;
    }
    else if(FourCARD(card)){
        result = bet * 25;
    }
    else if(FullHouse(card)){
        result = bet * 9;
    }
    else if(Flush(card)){
        result = bet * 6;
    }
    else if(Straight(card)){
        result = bet * 4;
    }
    else if(Triple(card)){
        result = bet * 3;
    }
    else if(TwoPair(card)){
        result = bet * 2;
    }
    else if(JackBetter(card)){
        result = bet;
    }
    else if(OnePair(card)){
        result = 0;
    }
    else{
        result = 0;
    }
    return result;
}
void Evaluate(CARD *card, __int64 &jackBetter, __int64 &twoPair, __int64 &triple, __int64 &straight, __int64 &flush, __int64 &fullHouse, __int64 &fourCard, __int64 &straightFlush, __int64 &royalFlush)
{
    if(RoyalFlush(card)){
        royalFlush++;
    }
    else if(StraightFlush(card)){
        straightFlush++;
    }
    else if(FourCARD(card)){
        fourCard++;
    }
    else if(FullHouse(card)){
        fullHouse++;
    }
    else if(Flush(card)){
        flush++;
    }
    else if(Straight(card)){
        straight++;
    }
    else if(Triple(card)){
        triple++;
    }
    else if(TwoPair(card)){
        twoPair++;
    }
    else if(JackBetter(card)){
        jackBetter++;
    }
}
void PrintHand(CARD *card)
{
    if(RoyalFlush(card)){
        cout << "Royal Flush" << endl;
    }
    else if(StraightFlush(card)){
        cout << "Straight Flush" << endl;
    }
    else if(FourCARD(card)){
        cout << "Four CARD" << endl;
    }
    else if(FullHouse(card)){
        cout << "Full House" << endl;
    }
    else if(Flush(card)){
        cout << "Flush" << endl;
    }
    else if(Straight(card)){
        cout << "Straight" << endl;
    }
    else if(Triple(card)){
        cout << "Triple" << endl;
    }
    else if(TwoPair(card)){
        cout << "Two Pair" << endl;
    }
    else if(JackBetter(card)){
        cout << "Jack Better" << endl;
    }
    else if(OnePair(card)){
        cout << "Else One Pair" << endl;
    }
    else{
        cout << "Nothing" << endl;
    }
}
void PrintCARD(CARD card)
{
    if(card.number == 1){
        cout << "A ";
    }
    else if(card.number == 11){
        cout << "J ";
    }
    else if(card.number == 12){
        cout << "Q ";
    }
    else if(card.number == 13){
        cout << "K ";
    }
    else{
        cout << card.number << ' ';
    }
    switch (card.type) {
        case 0:
            cout << "Spade" << endl;
            break;
        case 1:
            cout << "Heart" << endl;
            break;
        case 2:
            cout << "Diamond" << endl;
            break;
        case 3:
            cout << "Clover" << endl;
            break;
        default:
            break;
    }
}
void Sorting(CARD *card)
{
    CARD tempCARD;
    for(int i=0;i<5;i++){
        for(int j=i+1;j<5;j++){
            if(card[i].number > card[j].number){
                tempCARD = card[i];
                card[i] = card[j];
                card[j] = tempCARD;
            }
            else if(card[i].number == card[j].number){
                if(card[i].type > card[j].type){
                    tempCARD = card[i];
                    card[i] = card[j];
                    card[j] = tempCARD;
                }
            }
        }
    }
}
double Combin(int a, int b)
{
    double result = 1;
    double resultB = 1;
    for(int i=0;i<b;i++){
        result *= (a-i);
        resultB *= (b-i);
    }
    return result / resultB;
}
void Change(CARD *original, CARD *remain, bool *isHold)
{
    // one card change
    int jackBetter = 0;
    int twoPair = 0;
    int triple = 0;
    int straight = 0;
    int flush = 0;
    int fullHouse = 0;
    int fourCard = 0;
    int straightFlush = 0;
    int royalFlush = 0;
    int total0 = 0;
    int total1 = 0;
    int total2 = 0;
    int total3 = 0;
    int total4 = 0;
    int total5 = 0;
    double optimum = 0;
    double eval = 0;
    bool tempHold[5];
    // no change
    CARD tempCard[5];
    for(int k=0;k<5;k++){
        tempCard[k] = original[k];
    }
    //Evaluate(tempCard, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);
    optimum = ReturnCredit(tempCard, 1);
    total0++;
    
    // 1 change
    for(int j=0;j<5;j++){
        eval = 0;
        
        for(int i=0;i<47;i++){
            for(int k=0;k<5;k++){
                tempCard[k] = original[k];
                tempHold[k] = true;
            }

            tempCard[j] = remain[i];
            tempHold[j] = false;

            Sorting(tempCard);
            eval += ReturnCredit(tempCard, 1);
            //printf("%d, %d, %lf\n", remain[i].number, j, eval);
            //Evaluate(tempCard, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);
            
            total1++;
        }
        eval /= Combin(47, 1);
        if(eval > optimum){
            optimum = eval;
            for(int k=0;k<5;k++){
                isHold[k] = tempHold[k];
            }
        }
    }
    
    // 2 change
    for(int j=0;j<5;j++){
        for(int n=j+1;n<5;n++){
            eval = 0;
            
            for(int i=0;i<47;i++){
                for(int m=i+1;m<47;m++){
                    for(int k=0;k<5;k++){
                        tempCard[k] = original[k];
                        tempHold[k] = true;
                    }
                    tempHold[j] = false;
                    tempHold[n] = false;
                    
                    tempCard[j] = remain[i];
                    tempCard[n] = remain[m];
                    Sorting(tempCard);
                    eval += ReturnCredit(tempCard, 1);
                    
                    //Evaluate(tempCard, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);
                    total2++;
                }
            }
            eval /= Combin(47, 2);
            if(eval > optimum){
                optimum = eval;
                for(int k=0;k<5;k++){
                    isHold[k] = tempHold[k];
                }
            }
        }
    }
    
    // 3 change
    for(int j=0;j<5;j++){
        for(int n=j+1;n<5;n++){
            for(int nn=n+1;nn<5;nn++){
                eval = 0;
                
                for(int i=0;i<47;i++){
                    for(int m=i+1;m<47;m++){
                        for(int mm = m+1;mm<47;mm++){
                            for(int k=0;k<5;k++){
                                tempCard[k] = original[k];
                                tempHold[k] = true;
                            }
                            tempHold[j] = false;
                            tempHold[n] = false;
                            tempHold[nn] = false;
                            
                            tempCard[j] = remain[i];
                            tempCard[n] = remain[m];
                            tempCard[nn] = remain[mm];
                            Sorting(tempCard);
                            eval += ReturnCredit(tempCard, 1);
                            
                            //Evaluate(tempCard, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);
                            total3++;
                        }
                    }
                }
                eval /= Combin(47, 3);
                if(eval > optimum){
                    optimum = eval;
                    for(int k=0;k<5;k++){
                        isHold[k] = tempHold[k];
                    }
                }
            }
        }
    }
    
    // 4 change
    for(int j=0;j<5;j++){
        for(int n=j+1;n<5;n++){
            for(int nn=n+1;nn<5;nn++){
                for(int nnn = nn+1;nnn<5;nnn++){
                    eval = 0;
                    
                    for(int i=0;i<47;i++){
                        for(int m=i+1;m<47;m++){
                            for(int mm = m+1;mm<47;mm++){
                                for(int mmm = mm+1;mmm<47;mmm++){
                                    
                                    for(int k=0;k<5;k++){
                                        tempCard[k] = original[k];
                                        tempHold[k] = true;
                                    }
                                    tempHold[j] = false;
                                    tempHold[n] = false;
                                    tempHold[nn] = false;
                                    tempHold[nnn] = false;
                                    
                                    tempCard[j] = remain[i];
                                    tempCard[n] = remain[m];
                                    tempCard[nn] = remain[mm];
                                    tempCard[nnn] = remain[mmm];
                                    Sorting(tempCard);
                                    eval += ReturnCredit(tempCard, 1);
                                    
                                    //Evaluate(tempCard, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);
                                    total4++;
                                }
                            }
                        }
                    }
                    eval /= Combin(47, 4);
                    if(eval > optimum){
                        optimum = eval;
                        for(int k=0;k<5;k++){
                            isHold[k] = tempHold[k];
                        }
                    }
                }
            }
        }
    }
    
    // 5 change
    eval = 0;
    tempHold[0] = tempHold[1] = tempHold[2] = tempHold[3] = tempHold[4] = false;
    for(int i=0;i<47;i++){
        for(int m=i+1;m<47;m++){
            for(int mm = m+1;mm<47;mm++){
                for(int mmm = mm+1;mmm<47;mmm++){
                    for(int mmmm = mmm+1;mmmm<47;mmmm++){
                        tempCard[0] = remain[i];
                        tempCard[1] = remain[m];
                        tempCard[2] = remain[mm];
                        tempCard[3] = remain[mmm];
                        tempCard[4] = remain[mmmm];
                        Sorting(tempCard);
                        eval += ReturnCredit(tempCard, 1);
                        
                        total4++;
                    }
                }
            }
        }
    }
    eval /= Combin(47, 5);
    if(eval > optimum){
        optimum = eval;
        for(int k=0;k<5;k++){
            isHold[k] = tempHold[k];
        }
    }
    //printf("%d, %d, %d, %d, %d\n", isHold[0], isHold[1], isHold[2], isHold[3], isHold[4]);
    //printf("%d, %d, %d, %d, %d, %d\n", total0, total1, total2, total3, total4, total0+total1+total2+total3+total4);
}
void FullEvaluate(CARD *original, CARD *remain, __int64 &jackBetter, __int64 &twoPair, __int64 &triple, __int64 &straight, __int64 &flush, __int64 &fullHouse, __int64 &fourCard, __int64 &straightFlush, __int64 &royalFlush, __int64 &total)
{

	// no change
    CARD tempCard[5];
    for(int k=0;k<5;k++){
        tempCard[k] = original[k];
    }
    Evaluate(tempCard, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);
	total++;
    
    // 1 change
    for(int j=0;j<5;j++){        
        for(int i=0;i<47;i++){
            for(int k=0;k<5;k++){
                tempCard[k] = original[k];
            }
            tempCard[j] = remain[i]; 
            Sorting(tempCard);
            Evaluate(tempCard, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);   
			total++;
        }        
    }
    
    // 2 change
    for(int j=0;j<5;j++){
        for(int n=j+1;n<5;n++){
            for(int i=0;i<47;i++){
                for(int m=i+1;m<47;m++){
                    for(int k=0;k<5;k++){
                        tempCard[k] = original[k];
                    }                    
                    tempCard[j] = remain[i];
                    tempCard[n] = remain[m];
                    Sorting(tempCard);
                    Evaluate(tempCard, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);
					total++;
                }
            }            
        }
    }
    
    // 3 change
    for(int j=0;j<5;j++){
        for(int n=j+1;n<5;n++){
            for(int nn=n+1;nn<5;nn++){                
                for(int i=0;i<47;i++){
                    for(int m=i+1;m<47;m++){
                        for(int mm = m+1;mm<47;mm++){
                            for(int k=0;k<5;k++){
                                tempCard[k] = original[k];
                            }
                            tempCard[j] = remain[i];
                            tempCard[n] = remain[m];
                            tempCard[nn] = remain[mm];
                            Sorting(tempCard);
                            Evaluate(tempCard, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);     
							total++;
                        }
                    }
                }
                
            }
        }
    }
    
    // 4 change
    for(int j=0;j<5;j++){
        for(int n=j+1;n<5;n++){
            for(int nn=n+1;nn<5;nn++){
                for(int nnn = nn+1;nnn<5;nnn++){                    
                    for(int i=0;i<47;i++){
                        for(int m=i+1;m<47;m++){
                            for(int mm = m+1;mm<47;mm++){
                                for(int mmm = mm+1;mmm<47;mmm++){
                                    
                                    for(int k=0;k<5;k++){
                                        tempCard[k] = original[k];
                                    }
                                    tempCard[j] = remain[i];
                                    tempCard[n] = remain[m];
                                    tempCard[nn] = remain[mm];
                                    tempCard[nnn] = remain[mmm];
                                    Sorting(tempCard);
                                    Evaluate(tempCard, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);
									total++;
                                }
                            }
                        }
                    }                    
                }
            }
        }
    }
    
    // 5 change
    for(int i=0;i<47;i++){
        for(int m=i+1;m<47;m++){
            for(int mm = m+1;mm<47;mm++){
                for(int mmm = mm+1;mmm<47;mmm++){
                    for(int mmmm = mmm+1;mmmm<47;mmmm++){
                        tempCard[0] = remain[i];
                        tempCard[1] = remain[m];
                        tempCard[2] = remain[mm];
                        tempCard[3] = remain[mmm];
                        tempCard[4] = remain[mmmm];
                        Sorting(tempCard);
                        Evaluate(tempCard, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);
						total++;
                    }
                }
            }
        }
    }    
}
void FullGame()
{
	__int64 jackBetter = 0;
    __int64 twoPair = 0;
    __int64 triple = 0;
    __int64 straight = 0;
    __int64 flush = 0;
    __int64 fullHouse = 0;
    __int64 fourCard = 0;
    __int64 straightFlush = 0;
    __int64 royalFlush = 0;
	__int64 total = 0;
	CARD original[52];
	CARD eval[5];
	CARD remain[47];
	int originalPos;
	int remainPos;
	 for(int i=0;i<13;i++){
        for(int j=0;j<4;j++){
			original[j+i*4].number = i+1;
			original[j+i*4].type = j;
		}
	 }
	 //int i, j, k, l, m, mm;
	 for(int i=0;i<52;i++){
		 printf("%d\n", i);
		 for(int j=i+1;j<52;j++){
			 for(int k=j+1;k<52;k++){
				 for(int l=k+1;l<52;l++){
					 for(int m=l+1;m<52;m++){
						 eval[0] = original[i];
						 eval[1] = original[j];
						 eval[2] = original[k];
						 eval[3] = original[l];
						 eval[4] = original[m];
						 remainPos = 0;
						 originalPos = i;
						 for(int mm = 0;mm < 52;mm++){
							 if(mm != i && mm != j && mm != k && mm != l && mm != m){
								 remain[remainPos] = original[mm];
								 remainPos++;
							 }
						 }
						 FullEvaluate(eval, remain, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush, total);
					 }
				 }
				 printf("%d, %d, %d => %lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld\n", original[i].number, original[j].number, original[k].number, jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush, total);
			 }
//			 printf("%d, %d, %d, %d, %d, %d, %d, %d, %d\n", jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);
		 }
//		 printf("%d, %d, %d, %d, %d, %d, %d, %d, %d\n", jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush);
	 }

	 printf("%lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld\n", jackBetter, twoPair, triple, straight, flush, fullHouse, fourCard, straightFlush, royalFlush, total);
}
int VideoPoker(int bet)
{
    int originalPos;
    int remainPos;
    CARD original[10];
    CARD remain[47];
    bool isHold[5];
    for(int i=0;i<10;i++){
        original[i].number = rand() % 13 + 1;
        original[i].type = rand() % 4;
        for(int j=0;j<i;j++){
            if(original[i].number == original[j].number && original[i].type == original[j].type){
                i--;
                break;
            }
        }
    }
    Sorting(original);
    originalPos = 0;
    remainPos = 0;
    for(int i=0;i<13;i++){
        for(int j=0;j<4;j++){
            if(i+1 == original[originalPos].number && j == original[originalPos].type){
                originalPos++;
            }
            else{
                remain[remainPos].number = i+1;
                remain[remainPos].type = j;
                remainPos++;
            }
        }
    }
    printf("original\n");
    for(int i=0;i<5;i++){
        PrintCARD(original[i]);
    }
    for(int i=0;i<5;i++){
        isHold[i] = true;
    }
    
    Change(original, remain, isHold);
    originalPos = 5;
    for(int i=0;i<5;i++){
        if(isHold[i] == false){
            original[i] = original[originalPos];
            originalPos++;
        }
    }
    Sorting(original);
    printf("after change\n");
    for(int i=0;i<5;i++){
        PrintCARD(original[i]);
    }
    PrintHand(original);
    return ReturnCredit(original, bet);
//    printf("%d\n", ReturnCredit(original, 1));
}
int main(int argc, const char * argv[]) {
    // insert code here...
    srand((unsigned int)time(NULL));
    rand();
    int numPlay = atoi(argv[1]);
    int credit = atoi(argv[2]);
    int temp;
    int k;
    for(k=0;k<numPlay;k++){
        credit--;
        temp = VideoPoker(1);
        credit += temp;
        if(credit < 0) break;
        printf("%d\n", credit);
    }
    printf("%d play\n", k);
	//FullGame();
    return 0;
}
