#pragma once
#include "common.h"

class CARD
{
private:
    NUM_TYPE m_number;
	TYPE m_type;
public:
	CARD();
	CARD(NUM_TYPE number, TYPE type);
	~CARD();
	void SetNumber(NUM_TYPE number);
	void SetType(TYPE type);
	void SetCard(NUM_TYPE number, TYPE type);
	void AssignFrom(CARD card);
    NUM_TYPE GetNumber();
	TYPE GetType();

	bool IsSameNumber(CARD card);
	bool IsSameType(CARD card);
	bool IsSameCard(CARD card);
	void Print();
};

