/*
 * cardtest3.c
 * unit test for council_room
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */
 
 /*
* Business rules:
* 1. Player gains 4 cards.
* 2. Player loses 4 cards from deck.
* 3. Player gains 1 buy.
* 4. All other players gain 1 card.
* 5. All other players lose 1 card from deck.
& 6. No state changes occur to victory or kingdom card piles.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include "rngs.h"
#include <assert.h>
#include <stdlib.h>

#define TESTCARD "council_room"

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
	int numPlayers = 4;
	int currPlayer = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	//set turn to player 2
	G.whoseTurn = currPlayer;
	
	printf("----------------- Testing %s ----------------\n", TESTCARD);
	
	// copy the game state to a test case	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	
	//play smithy
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	//1. Player gains 4 cards to hand and discards council_room, resulting in a net of +3 cards.
	assertTrue(testG.handCount[testG.whoseTurn] == G.handCount[G.whoseTurn] + 3, "Test 1: +3 cards to hand");
	printf("Expected %d cards. Got %d cards.\n", G.handCount[G.whoseTurn] + 3, testG.handCount[testG.whoseTurn]);
	
	//2. Player loses 4 cards from deck.
	assertTrue(testG.deckCount[testG.whoseTurn] == G.deckCount[G.whoseTurn] - 4, "Test 2: -4 cards from deck");
	printf("Expected %d cards. Got %d cards.\n", G.deckCount[G.whoseTurn] - 4, testG.deckCount[testG.whoseTurn]);
	
	//3. Player gains 1 buy.
	assertTrue(testG.numBuys == G.numBuys + 1, "Test 3: +1 Buys");
	
	//4. All other players gain 1 card to hand.
	//5. All other players lose 1 card from deck.
	for (i = 0; i < numPlayers; i++)
	{
		if (i != G.whoseTurn)
		{
			printf("---Testing state for player %d---\n", i);
			assertTrue (testG.handCount[i] == G.handCount[i] +1, "Hand count.");
			assertTrue (testG.deckCount[i] == G.deckCount[i] -1, "Deck count.");
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