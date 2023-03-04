#include "VideoPoker.h"
#include "CARD.h"
#include "CheckCard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
VideoPoker::VideoPoker()
{
	srand((unsigned int)time(NULL));

	m_pChecker = new CheckCard();
	m_pHand = new CARD[NUM_HAND];
	m_pAvail = new CARD[NUM_HAND];
	m_pRemain = new CARD[NUM_TOTAL - NUM_HAND];
}
VideoPoker::~VideoPoker()
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
CARD* VideoPoker::GetHand()
{
	return m_pHand;
}
void VideoPoker::PrintHand()
{
	PrintCard(m_pHand, NUM_HAND);
}
void VideoPoker::PrintCard(CARD *card, int numCard)
{
	for (int i = 0; i < numCard; i++) {
		card[i].Print();
	}
}
void VideoPoker::GenerateNCard(int* cardIdx, int numTotalCard, int numGenCard)
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
void VideoPoker::GenerateCARDForTest()
{
	bool* isHand = new bool[NUM_TOTAL];
	int* handIdx = new int[NUM_HAND];

	for (int i = 0; i < NUM_TOTAL; i++) {
		isHand[i] = false;
	}

	handIdx[0] = 26;
	handIdx[1] = 44;
	handIdx[2] = 8;
	handIdx[3] = 19;
	handIdx[4] = 14;

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
void VideoPoker::GenerateCARD()
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
void VideoPoker::ChangeOneCARD(CARD* card, int handIdx, int remainIdx)
{
	card[handIdx].AssignFrom(m_pRemain[remainIdx]);
}

int VideoPoker::ComputeCredit(CARD* card)
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

float VideoPoker::ComputeAvgCreditForCardChange(CARD* card, int* handIdx, int numChangeCard)
{
	int numComputeCredit = 0;
	//for (int i = 0; i < NUM_TOTAL - NUM_HAND; i++) {

	int credit = ComputeTotalCreditForCardChange(card, handIdx, 0, numChangeCard, &numComputeCredit);
	//}
	//printf("%d, %d, %d\n", numChangeCard, credit, numComputeCredit);
	
	return (float)credit / (float)numComputeCredit;
}

int VideoPoker::ComputeTotalCreditForCardChange(CARD* card, int* handIdx, int startRemainIdx, int numChangeCard, int* numComputeCredit)
{
	if (numChangeCard == 0) {
		*numComputeCredit = 1;
		return ComputeCredit(card);
	}

	int credit = 0;
	int tempNumComputeCredit;
	CARD* tempCARD = new CARD[NUM_HAND];

	for (int i = 0; i < NUM_HAND; i++) {
		tempCARD[i].AssignFrom(card[i]);
	}
	for (int i = startRemainIdx; i < NUM_TOTAL - NUM_HAND; i++) {
		ChangeOneCARD(tempCARD, handIdx[0], i);
		tempNumComputeCredit = 0;
		credit += ComputeTotalCreditForCardChange(tempCARD, &handIdx[1], i + 1, numChangeCard - 1, &tempNumComputeCredit);
		*numComputeCredit += tempNumComputeCredit;
	}
	delete[]tempCARD;
	return credit;
}


float VideoPoker::ComputeOptimumChange(int* handIdx, int * numChangeCard)
{
	int *tempHandIdx = new int[NUM_HAND];
	for (int i = 0; i < NUM_HAND; i++) {
		tempHandIdx[i] = 0;
	}

	float credit;
	float optimumCredit = ComputeAvgCreditForCardChange(m_pHand, handIdx, 0);
	*numChangeCard = 0;
	//printf("No Change : %f\n", optimumCredit);

	//PrintCard(m_pHand, NUM_HAND);
	for (int i = 0; i < NUM_HAND; i++) {
		tempHandIdx[0] = i;
		credit = ComputeAvgCreditForCardChange(m_pHand, tempHandIdx, 1);
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
			credit = ComputeAvgCreditForCardChange(m_pHand, tempHandIdx, 2);
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
				credit = ComputeAvgCreditForCardChange(m_pHand, tempHandIdx, 3);
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
					credit = ComputeAvgCreditForCardChange(m_pHand, tempHandIdx, 4);
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
						credit = ComputeAvgCreditForCardChange(m_pHand, tempHandIdx, 5);
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

void VideoPoker::ChangeHand()
{
	int* handIdx = new int[NUM_HAND];
	int numChangeCard;
	// Print Remain
	//printf("Print Remain Card\n");
	//PrintCard(m_pRemain, NUM_TOTAL - NUM_HAND);

	ComputeOptimumChange(handIdx, &numChangeCard);
    printf("%d card change\n", numChangeCard);
    for(int i=0;i<numChangeCard;i++){
        printf("%d\n", handIdx[i]);
    }
	int* changeIdx = new int[numChangeCard];
	
	GenerateNCard(changeIdx, NUM_TOTAL - NUM_HAND, numChangeCard);

	for (int i = 0; i < numChangeCard; i++) {
		m_pHand[handIdx[i]].AssignFrom(m_pRemain[changeIdx[i]]);
	}

	delete[]handIdx;
	delete[]changeIdx;

}

void VideoPoker::TotalProbability()
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
                        printf("%d, %d, %d, %d, %d\n", c1, c2, c3, c4, c5);
                        printf("%d, %d, %d, %d, %d\n", isHand[c1], isHand[c2], isHand[c3], isHand[c4], isHand[c5]);
                        
						cntRemain = 0;
						for (int i = 0; i < NUM_TOTAL; i++) {
							if (!isHand[i]) {
								m_pRemain[cntRemain].SetCard(i / 4 + 1, (TYPE)(i % 4));
								cntRemain++;
							}
						}

						optimumCredit = ComputeOptimumChange(handIdx, &numChangeCard);
						totalCredit += optimumCredit;
                        printf("%d, %f, %f\n", numGame, optimumCredit, totalCredit);
						//printf("%f\n", optimumCredit);
						numGame++;
						if (numGame % 100 == 0) {
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
