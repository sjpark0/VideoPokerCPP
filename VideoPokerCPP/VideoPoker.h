#pragma once
#include "common.h"

class CARD;
class CheckCard;
class VideoPoker
{
private:
	CheckCard* m_pChecker;
	CARD* m_pHand;
	CARD* m_pAvail;
	CARD* m_pRemain;
	void GenerateNCard(int* cardIdx, int numTotalCard, int numGenCard);

	void ChangeOneCARD(CARD* card, int handIdx, int remainIdx);
	float ComputeAvgCreditForCardChange(CARD* card, int* handIdx, int numChangeCard);
	int ComputeTotalCreditForCardChange(CARD* card, int* handIdx, int startRemainIdx, int numChangeCard, int *numComputeCredit);
	int ComputeCredit(CARD* card);	
	void PrintCard(CARD* card, int numCard);

public:
	VideoPoker();
	~VideoPoker();	
	CARD* GetHand(); // test
	void PrintHand(); // test
	void GenerateCARD(); // test
	void GenerateCARDForTest();

	float ComputeOptimumChange(int* handIdx, int* numChangeCard);
	void ChangeHand();

	void TotalProbability();
};

