#pragma once
#include "common.h"

class CARD;
class CheckCard;

class VideoPoker2
{
private:
	CheckCard* m_pChecker;
	CARD* m_pHand;
	CARD* m_pAvail;
	CARD* m_pRemain;
	void GenerateNCard(int* cardIdx, int numTotalCard, int numGenCard);

	void ChangeOneCARD(CARD* card, int handIdx, int remainIdx);

	float ComputeAvgCreditForNoCardChange(int* handIdx);
	float ComputeAvgCreditForOneCardChange(int* handIdx);
	float ComputeAvgCreditForTwoCardChange(int* handIdx);
	float ComputeAvgCreditForThreeCardChange(int* handIdx);
	float ComputeAvgCreditForFourCardChange(int* handIdx);
	float ComputeAvgCreditForFiveCardChange(int* handIdx);


	int ComputeCredit(CARD* card);
	void PrintCard(CARD* card, int numCard);
public:
	VideoPoker2();
	~VideoPoker2();

	CARD* GetHand(); // test
	void PrintHand(); // test
	void GenerateCARD(); // test
	void GenerateCARDForTest();

	float ComputeOptimumChange(int* handIdx, int* numChangeCard);
	void ChangeHand();

	void TotalProbability();
};

