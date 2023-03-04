#pragma once
#include "common.h"
class CARD;
class CheckCard
{
private:
	int m_creditJackBetter;
	int m_creditTwoPair;
	int m_creditTriple;
	int m_creditStraight;
	int m_creditFlush;
	int m_creditFullHouse;
	int m_creditFourCARD;
	int m_creditStraightFlush;
	int m_creditRoyalFlush;

	bool IsOnePair(CARD* card);
	bool IsJackBetter(CARD* card);
	bool IsTwoPair(CARD* card);
	bool IsTriple(CARD* card);
	bool IsStraight(CARD* card);
	bool IsFlush(CARD* card);
	bool IsFullHouse(CARD* card);
	bool IsFourCARD(CARD* card);
	bool IsStraightFlush(CARD* card);
	bool IsRoyalFlush(CARD* card);

public:
	CheckCard();
	~CheckCard();
	void SetCredit(int cdJackBetter, int cdTwoPair, int cdTriple, int cdStraight, int cdFlush, int cdFullHouse, int cdFourCARD, int cdStrightFlush, int cdRoyalFlush);
	int ReturnCredit(CARD* card, int bet);
	void PrintHandCheck(CARD* card); // test
	void Sorting(CARD* card); // test

};

