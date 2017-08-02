/*
 * cardtest4.c
 * unit test for village
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */
 
 /*
* Business rules:
* 1. Player gains 1 card.
* 2. Player loses 1 card from deck.
* 3. Player gains 2 actions.
* 4. No state changes occur for other players.
& 5. No state changes occur to victory or kingdom card piles.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

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
	
	//play village
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	//1. Player gains 1 card to hand and discards village, resulting in a net of +0 cards.
	assertTrue(testG.handCount[testG.whoseTurn] == G.handCount[G.whoseTurn], "Test 1: +0 cards to hand");
	printf("Expected %d cards. Got %d cards.\n", G.handCount[G.whoseTurn], testG.handCount[testG.whoseTurn]);
	
	//2. Player loses 1 cards from deck.
	assertTrue(testG.deckCount[testG.whoseTurn] == G.deckCount[G.whoseTurn] - 1, "Test 2: -1 cards from deck");
	printf("Expected %d cards. Got %d cards.\n", G.deckCount[G.whoseTurn] - 1, testG.deckCount[testG.whoseTurn]);
	
	//3. Player gains 2 actions.
	assertTrue(testG.numActions == G.numActions + 2, "Test 3: +1 Buys");
	printf("Expected %d actions. Got %d actions.\n", G.numActions + 2, testG.numActions);
	
	//4. No state changes occur for other players.
	for (i = 0; i < numPlayers; i++)
	{
		if (i != G.whoseTurn)
		{
			printf("---Testing state for player %d---\n", i);
			assertTrue (testG.handCount[i] == G.handCount[i], "Hand count.");
			assertTrue (testG.deckCount[i] == G.deckCount[i], "Deck count.");
		}
	}
	
	//5. No state changes occur to victory or kingdom card piles.
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