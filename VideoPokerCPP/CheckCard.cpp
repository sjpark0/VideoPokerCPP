#include "CheckCard.h"
#include "CARD.h"
#include <stdio.h>

CheckCard::CheckCard()
{
    m_creditJackBetter = 1;
    m_creditTwoPair = 2;
    m_creditTriple = 3;
    m_creditStraight = 4;
    m_creditFlush = 6;
    m_creditFullHouse = 9;
    m_creditFourCARD = 25;
    m_creditStraightFlush = 50;
    m_creditRoyalFlush = 800;
}
CheckCard::~CheckCard()
{

}
bool CheckCard::IsOnePair(CARD* card)
{
    if (card[0].IsSameNumber(card[1]) || card[1].IsSameNumber(card[2]) || card[2].IsSameNumber(card[3]) || card[3].IsSameNumber(card[4])) {
        return true;
    }
    else return false;
}
bool CheckCard::IsJackBetter(CARD* card)
{
    if ((card[0].IsSameNumber(card[1]) && (card[0].GetNumber() >= 11 || card[0].GetNumber() == 1)) ||
        (card[1].IsSameNumber(card[2]) && (card[1].GetNumber() >= 11 || card[1].GetNumber() == 1)) ||
        (card[2].IsSameNumber(card[3]) && (card[2].GetNumber() >= 11 || card[2].GetNumber() == 1)) ||
        (card[3].IsSameNumber(card[4]) && (card[3].GetNumber() >= 11 || card[3].GetNumber() == 1))) {
        return true;
    }
    else return false;
}
bool CheckCard::IsTwoPair(CARD* card)
{
    if ((card[0].IsSameNumber(card[1]) && card[2].IsSameNumber(card[3])) ||
        (card[0].IsSameNumber(card[1]) && card[3].IsSameNumber(card[4])) ||
        (card[1].IsSameNumber(card[2]) && card[3].IsSameNumber(card[4]))){
        return true;
    }
    else return false;
}
bool CheckCard::IsTriple(CARD* card)
{
    if (card[0].IsSameNumber(card[2]) ||
        card[1].IsSameNumber(card[3]) ||
        card[2].IsSameNumber(card[4])) {
        return true;
    }
    else return false;
}
bool CheckCard::IsFlush(CARD* card)
{
    if (card[0].IsSameType(card[1]) && card[0].IsSameType(card[2]) && card[0].IsSameType(card[3]) && card[0].IsSameType(card[4])) {
        return true;
    }
    else return false;
}
bool CheckCard::IsStraight(CARD* card)
{
    if (card[0].GetNumber() == card[1].GetNumber() - 1 &&
        card[1].GetNumber() == card[2].GetNumber() - 1 &&
        card[2].GetNumber() == card[3].GetNumber() - 1 &&
        card[3].GetNumber() == card[4].GetNumber() - 1) {
        return true;
    }
    else if (card[0].GetNumber() == 1 &&
        card[1].GetNumber() == 10 &&
        card[2].GetNumber() == 11 &&
        card[3].GetNumber() == 12 &&
        card[4].GetNumber() == 13) {
        return true;
    }
    else return false;
}
bool CheckCard::IsFullHouse(CARD* card)
{
    if ((card[0].IsSameNumber(card[2]) && card[3].IsSameNumber(card[4])) ||
        (card[0].IsSameNumber(card[1]) && card[2].IsSameNumber(card[4]))) {
        return true;
    }
    else return false;
}
bool CheckCard::IsFourCARD(CARD* card)
{
    if (card[0].IsSameNumber(card[3]) ||
        card[1].IsSameNumber(card[4])) {
        return true;
    }
    else return false;
}
bool CheckCard::IsStraightFlush(CARD* card)
{
    if (IsFlush(card) && IsStraight(card)) {
        return true;
    }
    else return false;
}
bool CheckCard::IsRoyalFlush(CARD* card)
{
    if (IsFlush(card)) {
        if (card[0].GetNumber() == 1 &&
            card[1].GetNumber() == 10 &&
            card[2].GetNumber() == 11 &&
            card[3].GetNumber() == 12 &&
            card[4].GetNumber() == 13) {
            return true;
        }
        else return false;
    }
    else return false;
}

void CheckCard::SetCredit(int cdJackBetter, int cdTwoPair, int cdTriple, int cdStraight, int cdFlush, int cdFullHouse, int cdFourCARD, int cdStrightFlush, int cdRoyalFlush)
{
    m_creditJackBetter = cdJackBetter;
    m_creditTwoPair = cdTwoPair;
    m_creditTriple = cdTriple;
    m_creditStraight = cdStraight;
    m_creditFlush = cdFlush;
    m_creditFullHouse = cdFullHouse;
    m_creditFourCARD = cdFourCARD;
    m_creditStraightFlush = cdStrightFlush;
    m_creditRoyalFlush = cdRoyalFlush;
}
int CheckCard::ReturnCredit(CARD* card, int bet)
{
    if (IsRoyalFlush(card)) {
        return bet * m_creditRoyalFlush;
    }
    else if (IsStraightFlush(card)) {
        return bet * m_creditStraightFlush;
    }
    else if (IsFourCARD(card)) {
        return bet * m_creditFourCARD;
    }
    else if (IsFullHouse(card)) {
        return bet * m_creditFullHouse;
    }
    else if (IsFlush(card)) {
        return bet * m_creditFlush;
    }
    else if (IsStraight(card)) {
        return bet * m_creditStraight;
    }
    else if (IsTriple(card)) {
        return bet * m_creditTriple;
    }
    else if (IsTwoPair(card)) {
        return bet * m_creditTwoPair;
    }
    else if (IsJackBetter(card)) {
        return bet * m_creditJackBetter;
    }
    else return 0;
}
void CheckCard::PrintHandCheck(CARD* card)
{
    if (IsRoyalFlush(card)) {
        printf("Royal Flush\n");
    }
    else if (IsStraightFlush(card)) {
        printf("Straight Flush\n");
    }
    else if (IsFourCARD(card)) {
        printf("Four CARD\n");
    }
    else if (IsFullHouse(card)) {
        printf("Full House\n");
    }
    else if (IsFlush(card)) {
        printf("Flush\n");
    }
    else if (IsStraight(card)) {
        printf("Straight\n");
    }
    else if (IsTriple(card)) {
        printf("Triple\n");
    }
    else if (IsTwoPair(card)) {
        printf("Two Pair\n");
    }
    else if (IsJackBetter(card)) {
        printf("Jack Better\n");
    }
    else if (IsOnePair(card)) {
        printf("One Pair\n");
    }
    else {
        printf("Nothing\n");
    }
}
void CheckCard::Sorting(CARD* card)
{
    CARD tempCARD;
    for (int i = 0; i < NUM_HAND; i++) {
        for (int j = i + 1; j < NUM_HAND; j++) {
            if (card[i].GetNumber() > card[j].GetNumber()) {
                tempCARD.AssignFrom(card[i]);
                card[i].AssignFrom(card[j]);
                card[j].AssignFrom(tempCARD);
            }
        }
    }
}