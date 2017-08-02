/*
 * cardtest2.c
 * unit test for adventurer
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */
 
 /*
* Business rules:
* 1. Player gains 2 cards. 
* 2. Those 2 cards are treasure cards.
* 3. No state changes occur for other players.
& 4. No state changes occur to victory or kingdom card piles.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int numTest = 0;
int passedTest = 0;

int assertTrue(int testVal, char* testName)
{
	numTest++;
	
	if (testVal)
	{
		printf("PASS: %s\n", testName);
		passedTest++;
	}
	else
	{
		printf("FAIL: %s\n", testName);
	}
	
	return 0;
}

int main ()
{
	int i;
	int preTreasure = 0;
	int postTreasure = 0;
	int currCard;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing %s ----------------\n", TESTCARD);
	
	// copy the game state to a test case	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//play adventurer
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	//1. Player gains 2 cards to hand and discards adventurer, resulting in a net of +1 cards.
	//This test is currently failing as adventurer is not discarded. There was a question on Piazza (@40) about whether this was a bug in the original code, and it was not answered. 
	assertTrue(testG.handCount[testG.whoseTurn] == G.handCount[G.whoseTurn] + 1, "Test 1: +1 cards to hand");
	printf("Expected %d cards. Got %d cards.\n", G.handCount[G.whoseTurn] + 1, testG.handCount[testG.whoseTurn]);
	
	//2.  Those 2 cards are treasure cards.
	for (i = 0; i < G.handCount[G.whoseTurn]; i++)
	{
		currCard = G.hand[G.whoseTurn][i];
		if (currCard == copper || currCard == silver || currCard == gold)
		{
			preTreasure++;
		}
	}
	
	for (i = 0; i < testG.handCount[testG.whoseTurn]; i++)
	{
		currCard = testG.hand[testG.whoseTurn][i];
		if (currCard == copper || currCard == silver || currCard == gold)
		{
			postTreasure++;
		}
	}
	
	assertTrue(postTreasure == preTreasure + 2, "Test 2: +2 Treasure cards to hand");
	
	//3. No state changes occur for other players.
	for (i = 0; i < numPlayers; i++)
	{
		if (i != G.whoseTurn)
		{
			printf("---Testing state for player %d---\n", i);
			assertTrue (testG.handCount[i] == G.handCount[i], "Hand count.");
			assertTrue (testG.deckCount[i] == G.deckCount[i], "Deck count.");
		}
	}
	
	//4. No state changes occur to victory or kingdom card piles.
	assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], "Estate pile.");
	assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], "Duchy pile.");
	assertTrue(testG.supplyCount[province] == G.supplyCount[province], "Estate pile.");
	
	for (i = adventurer; i <= treasure_map; i++)
	{
		printf("---Testing card pile for enum %d---\n", i);
		assertTrue(testG.supplyCount[i] = G.supplyCount[i], "Card pile.");
	}
	
	printf("-----------------%d/%d TESTS PASSED FOR %s----------------\n", passedTest, numTest, TESTCARD);	
	
	return 0;
}