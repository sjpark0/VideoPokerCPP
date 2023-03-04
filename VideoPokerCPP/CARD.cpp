#include "CARD.h"
#include <stdio.h>

CARD::CARD()
{
	
}
CARD::CARD(NUM_TYPE number, TYPE type)
{
	m_number = number;
	m_type = type;
}
CARD::~CARD()
{

}
void CARD::SetNumber(NUM_TYPE number)
{
	m_number = number;
}
void CARD::SetType(TYPE type)
{
	m_type = type;
}
void CARD::SetCard(NUM_TYPE number, TYPE type)
{
    m_number = number;
    m_type = type;
}
void CARD::AssignFrom(CARD card)
{
    m_number = card.GetNumber();
    m_type = card.GetType();
}
NUM_TYPE CARD::GetNumber()
{
	return m_number;
}
TYPE CARD::GetType()
{
	return m_type;
}
bool CARD::IsSameNumber(CARD card)
{
	if (m_number == card.GetNumber()) {
		return true;
	}
	else return false;
}
bool CARD::IsSameType(CARD card)
{
	if (m_type == card.GetType()) {
		return true;
	}
	else return false;
}
bool CARD::IsSameCard(CARD card)
{
    if (IsSameNumber(card) && IsSameType(card)) {
        return true;
    }
    else return false;
}
void CARD::Print()
{
    if (m_number == 1) {
        printf("A ");
    }
    else if (m_number == 11) {
        printf("J ");
    }
    else if (m_number == 12) {
        printf("Q ");
    }
    else if (m_number == 13) {
        printf("K ");
    }
    else {
        printf("%d ", (int)m_number);
    }
    switch (m_type) {
    case CARD_SPADE:
        printf("Spade\n");
        break;
    case CARD_CLOVER:
        printf("Clover\n");
        break;
    case CARD_DIAMOND:
        printf("Diamond\n");
        break;
    case CARD_HEART:
        printf("Heart\n");
        break;
    default:
        break;
    }
}
