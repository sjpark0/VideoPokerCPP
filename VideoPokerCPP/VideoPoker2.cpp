#include "VideoPoker2.h"
#include "CARD.h"
#include "CheckCard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
VideoPoker2::VideoPoker2()
{
	srand((unsigned int)time(NULL));

	m_pChecker = new CheckCard();
	m_pHand = new CARD[NUM_HAND];
	m_pAvail = new CARD[NUM_HAND];
	m_pRemain = new CARD[NUM_TOTAL - NUM_HAND];
}
VideoPoker2::~VideoPoker2()
{
	if (m_pChecker) {
		delete m_pChecker;
		m_pChecker = NULL;
	}
	if (m_pHand) {
		delete[]m_pHand;
		m_pHand = NULL;
	}
	if (m_pRemain) {
		delete[]m_pRemain;
		m_pRemain = NULL;
	}
}
CARD* VideoPoker2::GetHand()
{
	return m_pHand;
}
void VideoPoker2::PrintHand()
{
	PrintCard(m_pHand, NUM_HAND);
}
void VideoPoker2::PrintCard(CARD *card, int numCard)
{
	for (int i = 0; i < numCard; i++) {
		card[i].Print();
	}
}
void VideoPoker2::GenerateNCard(int* cardIdx, int numTotalCard, int numGenCard)
{
	for (int i = 0; i < numGenCard; i++) {
		cardIdx[i] = rand() % numTotalCard;
		for (int j = 0; j < i; j++) {
			if (cardIdx[i] == cardIdx[j]) {
				i--;
				break;
			}
		}
	}
}
void VideoPoker2::GenerateCARDForTest()
{
	bool* isHand = new bool[NUM_TOTAL];
	int* handIdx = new int[NUM_HAND];

	for (int i = 0; i < NUM_TOTAL; i++) {
		isHand[i] = false;
	}

	handIdx[0] = 0;
	handIdx[1] = 1;
	handIdx[2] = 2;
	handIdx[3] = 4;
	handIdx[4] = 8;


	for (int i = 0; i < NUM_HAND; i++) {
		m_pHand[i].SetCard(handIdx[i] / 4 + 1, (TYPE)(handIdx[i] % 4));
		isHand[handIdx[i]] = true;
	}

	int cntRemain = 0;
	for (int i = 0; i < NUM_TOTAL; i++) {
		if (!isHand[i]) {
			m_pRemain[cntRemain].SetCard(i / 4 + 1, (TYPE)(i % 4));
			cntRemain++;
		}
	}
	delete[]handIdx;
	delete[]isHand;
}
void VideoPoker2::GenerateCARD()
{
	bool* isHand = new bool[NUM_TOTAL];
	int* handIdx = new int[NUM_HAND];

	for (int i = 0; i < NUM_TOTAL; i++) {
		isHand[i] = false;
	}
	GenerateNCard(handIdx, NUM_TOTAL, NUM_HAND);

	for (int i = 0; i < NUM_HAND; i++) {
		m_pHand[i].SetCard(handIdx[i] / 4 + 1, (TYPE)(handIdx[i] % 4));
		isHand[handIdx[i]] = true;
		printf("%d\n", handIdx[i]);
	}

	int cntRemain = 0;
	for (int i = 0; i < NUM_TOTAL; i++) {
		if (!isHand[i]) {
			m_pRemain[cntRemain].SetCard(i / 4 + 1, (TYPE)(i % 4));
		}
	}
	delete[]handIdx;
	delete[]isHand;
}
void VideoPoker2::ChangeOneCARD(CARD* card, int handIdx, int remainIdx)
{
	card[handIdx].AssignFrom(m_pRemain[remainIdx]);
}

int VideoPoker2::ComputeCredit(CARD* card)
{
	CARD* tempCARD = new CARD[NUM_HAND];
	for (int i = 0; i < NUM_HAND; i++) {
		tempCARD[i].AssignFrom(card[i]);
	}
	m_pChecker->Sorting(tempCARD);
	int credit = m_pChecker->ReturnCredit(tempCARD, 1);
	//m_pChecker->PrintHandCheck(tempCARD);
	//printf("%d\n", credit);
	delete[]tempCARD;
	return credit;
}

float VideoPoker2::ComputeAvgCreditForNoCardChange(int* handIdx)
{	
	return ComputeCredit(m_pHand);
}
float VideoPoker2::ComputeAvgCreditForOneCardChange(int* handIdx)
{
	int numTotal = 0;
	float creditTotal = 0.0;

	CARD* tempCARD = new CARD[NUM_HAND];
	for (int i = 0; i < NUM_HAND; i++) {
		tempCARD[i].AssignFrom(m_pHand[i]);
	}

	for (int i = 0; i < NUM_TOTAL - NUM_HAND; i++) {
		for (int mm = 0; mm < NUM_HAND; mm++) {
			tempCARD[mm].AssignFrom(m_pHand[mm]);
		}

		ChangeOneCARD(tempCARD, handIdx[0], i);
		creditTotal += ComputeCredit(tempCARD);
		numTotal++;
	}
	delete[]tempCARD;
	return creditTotal / numTotal;
}
float VideoPoker2::ComputeAvgCreditForTwoCardChange(int* handIdx)
{
	int numTotal = 0;
	float creditTotal = 0.0;

	CARD* tempCARD = new CARD[NUM_HAND];
	for (int i = 0; i < NUM_HAND; i++) {
		tempCARD[i].AssignFrom(m_pHand[i]);
	}

	for (int i = 0; i < NUM_TOTAL - NUM_HAND; i++) {
		for (int j = i + 1; j < NUM_TOTAL - NUM_HAND; j++) {
			for (int mm = 0; mm < NUM_HAND; mm++) {
				tempCARD[mm].AssignFrom(m_pHand[mm]);
			}

			ChangeOneCARD(tempCARD, handIdx[0], i);
			ChangeOneCARD(tempCARD, handIdx[1], j);
			creditTotal += ComputeCredit(tempCARD);
			numTotal++;
		}
	}
	delete[]tempCARD;
	return creditTotal / numTotal;
}
float VideoPoker2::ComputeAvgCreditForThreeCardChange(int* handIdx)
{
	int numTotal = 0;
	float creditTotal = 0.0;

	CARD* tempCARD = new CARD[NUM_HAND];
	for (int i = 0; i < NUM_HAND; i++) {
		tempCARD[i].AssignFrom(m_pHand[i]);
	}

	for (int i = 0; i < NUM_TOTAL - NUM_HAND; i++) {
		for (int j = i + 1; j < NUM_TOTAL - NUM_HAND; j++) {
			for (int k = j + 1; k < NUM_TOTAL - NUM_HAND; k++) {
				for (int mm = 0; mm < NUM_HAND; mm++) {
					tempCARD[mm].AssignFrom(m_pHand[mm]);
				}

				ChangeOneCARD(tempCARD, handIdx[0], i);
				ChangeOneCARD(tempCARD, handIdx[1], j);
				ChangeOneCARD(tempCARD, handIdx[2], k);

				creditTotal += ComputeCredit(tempCARD);
				numTotal++;
			}
		}
	}
	delete[]tempCARD;
	return creditTotal / numTotal;
}
float VideoPoker2::ComputeAvgCreditForFourCardChange(int* handIdx)
{
	int numTotal = 0;
	float creditTotal = 0.0;

	CARD* tempCARD = new CARD[NUM_HAND];
	for (int i = 0; i < NUM_HAND; i++) {
		tempCARD[i].AssignFrom(m_pHand[i]);
	}

	for (int i = 0; i < NUM_TOTAL - NUM_HAND; i++) {
		for (int j = i + 1; j < NUM_TOTAL - NUM_HAND; j++) {
			for (int k = j + 1; k < NUM_TOTAL - NUM_HAND; k++) {
				for (int l = k + 1; l < NUM_TOTAL - NUM_HAND; l++) {
					for (int mm = 0; mm < NUM_HAND; mm++) {
						tempCARD[mm].AssignFrom(m_pHand[mm]);
					}

					ChangeOneCARD(tempCARD, handIdx[0], i);
					ChangeOneCARD(tempCARD, handIdx[1], j);
					ChangeOneCARD(tempCARD, handIdx[2], k);
					ChangeOneCARD(tempCARD, handIdx[3], l);

					creditTotal += ComputeCredit(tempCARD);
					numTotal++;
				}
			}
		}
	}
	delete[]tempCARD;
	return creditTotal / numTotal;
}
float VideoPoker2::ComputeAvgCreditForFiveCardChange(int* handIdx)
{
	int numTotal = 0;
	float creditTotal = 0.0;

	CARD* tempCARD = new CARD[NUM_HAND];
	for (int i = 0; i < NUM_HAND; i++) {
		tempCARD[i].AssignFrom(m_pHand[i]);
	}
	for (int i = 0; i < NUM_TOTAL - NUM_HAND; i++) {
		for (int j = i + 1; j < NUM_TOTAL - NUM_HAND; j++) {
			for (int k = j + 1; k < NUM_TOTAL - NUM_HAND; k++) {
				for (int l = k + 1; l < NUM_TOTAL - NUM_HAND; l++) {
					for (int m = l + 1; m < NUM_TOTAL - NUM_HAND; m++) {
						for (int mm = 0; mm < NUM_HAND; mm++) {
							tempCARD[mm].AssignFrom(m_pHand[mm]);
						}

						ChangeOneCARD(tempCARD, handIdx[0], i);
						ChangeOneCARD(tempCARD, handIdx[1], j);
						ChangeOneCARD(tempCARD, handIdx[2], k);
						ChangeOneCARD(tempCARD, handIdx[3], l);
						ChangeOneCARD(tempCARD, handIdx[4], m);

						creditTotal += ComputeCredit(tempCARD);
						numTotal++;
					}
				}
			}
		}
	}
	delete[]tempCARD;
	return creditTotal / numTotal;
}


float VideoPoker2::ComputeOptimumChange(int* handIdx, int * numChangeCard)
{
	int *tempHandIdx = new int[NUM_HAND];
	for (int i = 0; i < NUM_HAND; i++) {
		tempHandIdx[i] = 0;
	}

	float credit;
	float optimumCredit = ComputeAvgCreditForNoCardChange(handIdx);
	*numChangeCard = 0;
	//printf("No Change : %f\n", optimumCredit);

	//PrintCard(m_pHand, NUM_HAND);
	for (int i = 0; i < NUM_HAND; i++) {
		tempHandIdx[0] = i;
		credit = ComputeAvgCreditForOneCardChange(tempHandIdx);
		//printf("Change Id : %d => %f\n", i, credit);

		if (credit > optimumCredit) {
			optimumCredit = credit;
			*numChangeCard = 1;
			for (int idx = 0; idx < *numChangeCard; idx++) {
				handIdx[idx] = tempHandIdx[idx];
			}
		}
	}
	/*printf("One Change : %f, %d\n", optimumCredit, *numChangeCard);

	for (int idx = 0; idx < *numChangeCard; idx++) {
		printf("%d ", handIdx[idx]);
	}
	printf("\n");*/
	for (int i = 0; i < NUM_HAND; i++) {
		for (int j = i + 1; j < NUM_HAND; j++) {
			tempHandIdx[0] = i;
			tempHandIdx[1] = j;
			credit = ComputeAvgCreditForTwoCardChange(tempHandIdx);
			//printf("Change Id : %d, %d => %f\n", i, j, credit);

			if (credit > optimumCredit) {
				optimumCredit = credit;
				*numChangeCard = 2;
				for (int idx = 0; idx < *numChangeCard; idx++) {
					handIdx[idx] = tempHandIdx[idx];
				}
			}
		}
	}
	/*printf("Two Change : %f, %d\n", optimumCredit, *numChangeCard);
	for (int idx = 0; idx < *numChangeCard; idx++) {
		printf("%d ", handIdx[idx]);
	}
	printf("\n");*/

	for (int i = 0; i < NUM_HAND; i++) {
		for (int j = i + 1; j < NUM_HAND; j++) {
			for (int k = j + 1; k < NUM_HAND; k++) {
				tempHandIdx[0] = i;
				tempHandIdx[1] = j;
				tempHandIdx[2] = k;
				credit = ComputeAvgCreditForThreeCardChange(tempHandIdx);
				//printf("Change Id : %d, %d, %d => %f\n", i, j, k, credit);

				if (credit > optimumCredit) {
					optimumCredit = credit;
					*numChangeCard = 3;
					for (int idx = 0; idx < *numChangeCard; idx++) {
						handIdx[idx] = tempHandIdx[idx];
					}
				}
			}
		}
	}
	/*printf("Three Change : %f, %d\n", optimumCredit, *numChangeCard);
	for (int idx = 0; idx < *numChangeCard; idx++) {
		printf("%d ", handIdx[idx]);
	}
	printf("\n");*/

	for (int i = 0; i < NUM_HAND; i++) {
		for (int j = i + 1; j < NUM_HAND; j++) {
			for (int k = j + 1; k < NUM_HAND; k++) {
				for (int l = k + 1; l < NUM_HAND; l++) {
					tempHandIdx[0] = i;
					tempHandIdx[1] = j;
					tempHandIdx[2] = k;
					tempHandIdx[3] = l;
					credit = ComputeAvgCreditForFourCardChange(tempHandIdx);
					//printf("Change Id : %d, %d, %d, %d => %f\n", i, j, k, l, credit);

					if (credit > optimumCredit) {
						optimumCredit = credit;
						*numChangeCard = 4;
						for (int idx = 0; idx < *numChangeCard; idx++) {
							handIdx[idx] = tempHandIdx[idx];
						}
					}
				}
			}
		}
	}
	/*printf("Four Change : %f, %d\n", optimumCredit, *numChangeCard);
	for (int idx = 0; idx < *numChangeCard; idx++) {
		printf("%d ", handIdx[idx]);
	}
	printf("\n");*/

	for (int i = 0; i < NUM_HAND; i++) {
		for (int j = i + 1; j < NUM_HAND; j++) {
			for (int k = j + 1; k < NUM_HAND; k++) {
				for (int l = k + 1; l < NUM_HAND; l++) {
					for (int m = l + 1; m < NUM_HAND; m++) {
						tempHandIdx[0] = i;
						tempHandIdx[1] = j;
						tempHandIdx[2] = k;
						tempHandIdx[3] = l;
						tempHandIdx[4] = m;
						credit = ComputeAvgCreditForFiveCardChange(tempHandIdx);
						//printf("Change Id : %d, %d, %d, %d, %d => %f\n", i, j, k, l, m, credit);

						if (credit > optimumCredit) {
							optimumCredit = credit;
							*numChangeCard = 5;
							for (int idx = 0; idx < *numChangeCard; idx++) {
								handIdx[idx] = tempHandIdx[idx];
							}
						}
					}
				}
			}
		}
	}
	/*printf("Five Change : %f, %d\n", optimumCredit, *numChangeCard);
	for (int idx = 0; idx < *numChangeCard; idx++) {
		printf("%d ", handIdx[idx]);
	}
	printf("\n");*/

	delete[]tempHandIdx;
	return optimumCredit;
}

void VideoPoker2::ChangeHand()
{
	int* handIdx = new int[NUM_HAND];
	int numChangeCard;
	// Print Remain
	//printf("Print Remain Card\n");
	//PrintCard(m_pRemain, NUM_TOTAL - NUM_HAND);

	ComputeOptimumChange(handIdx, &numChangeCard);

	int* changeIdx = new int[numChangeCard];

	GenerateNCard(changeIdx, NUM_TOTAL - NUM_HAND, numChangeCard);

	for (int i = 0; i < numChangeCard; i++) {
		m_pHand[handIdx[i]].AssignFrom(m_pRemain[changeIdx[i]]);
	}

	delete[]handIdx;
	delete[]changeIdx;

}

void VideoPoker2::TotalProbability()
{
	bool* isHand = new bool[NUM_TOTAL];

	int* handIdx = new int[NUM_HAND];
	int numChangeCard;

	int cntRemain;
	float optimumCredit;

	int numGame = 0;
	float totalCredit = 0.0;
	for (int c1 = 0; c1 < NUM_TOTAL; c1++) {
		for (int c2 = c1 + 1; c2 < NUM_TOTAL; c2++) {
			for (int c3 = c2 + 1; c3 < NUM_TOTAL; c3++) {
				for (int c4 = c3 + 1; c4 < NUM_TOTAL; c4++) {
					for (int c5 = c4 + 1; c5 < NUM_TOTAL; c5++) {

						for (int i = 0; i < NUM_TOTAL; i++) {
							isHand[i] = false;
						}
						m_pHand[0].SetCard(c1 / 4 + 1, (TYPE)(c1 % 4));
						m_pHand[1].SetCard(c2 / 4 + 1, (TYPE)(c2 % 4));
						m_pHand[2].SetCard(c3 / 4 + 1, (TYPE)(c3 % 4));
						m_pHand[3].SetCard(c4 / 4 + 1, (TYPE)(c4 % 4));
						m_pHand[4].SetCard(c5 / 4 + 1, (TYPE)(c5 % 4));
						isHand[c1] = true;
						isHand[c2] = true;
						isHand[c3] = true;
						isHand[c4] = true;
						isHand[c5] = true;

						cntRemain = 0;
						for (int i = 0; i < NUM_TOTAL; i++) {
							if (!isHand[i]) {
								m_pRemain[cntRemain].SetCard(i / 4 + 1, (TYPE)(i % 4));
								cntRemain++;
							}
						}

						optimumCredit = ComputeOptimumChange(handIdx, &numChangeCard);
						totalCredit += optimumCredit;
						//printf("%f\n", optimumCredit);
						numGame++;
						if (numGame % 10 == 0) {
							printf("Probability : %d, %f, %f\n", numGame, totalCredit, totalCredit / numGame);
						}
						
					}
				}
			}
		}
	}

	printf("Total Probability : %d, %f, %f\n", numGame, totalCredit, totalCredit / numGame);

	delete[]isHand;
	delete[]handIdx;
}
