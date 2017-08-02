/*
 * randomtestcard2.c
 * random test for smithy
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard1: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 */
 
 /*
* Business rules:
* 1. Player gains 3 cards.
* 2. Player loses 3 cards from deck.
* 3. No state changes occur for other players.
* 4. No state changes occur to victory or kingdom card piles.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "smithy"
#define NUMTEST 10

int currTest = 0;

int assertTrue(int testVal, char* testName)
{	
	if (testVal)
	{
		//printf("PASS: %s\n", testName);
	}
	//only print error message on fail
	else
	{
		printf("FAIL: %s\n", testName);
	}
	
	return 0;
}

void testCard ()
{
	int i;
	int j;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	printf("----------------- Testing %s ----------------\n", TESTCARD);
	
			
	for (j = 0; j < NUMTEST; j++)
	{	
		//random number of players 2-4	
		numPlayers = (rand() % 3) + 2;
		//random seed
		seed = (rand() % 1000) + 1;

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		currTest++;
		
		//up to 5 times

		for (i = 0; i < rand() % 5; i++)
		{
		//randomly remove a card that's not smithy				
			discardCard( rand() % 7 , G.whoseTurn, &G, 0);
		}
		
		//shuffle the deck
		shuffle(0, &G);

		//up to 2 times
		for (i = 0; i < rand() % 2; i++)
		{
			//take a card from the deck to the player's hand
			drawCard(0, &G);		
		}

		printf("-----------------%d/%d Iterations. Players: %d----------------\n", currTest, NUMTEST, numPlayers);
	
		// copy the game state to a test case	
		memcpy(&testG, &G, sizeof(struct gameState));

		//play smithy
		cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
		
		//1. Player gains 3 cards to hand and discards smithy, resulting in a net of +2 cards.
		assertTrue(testG.handCount[testG.whoseTurn] == G.handCount[G.whoseTurn] + 2, "Test 1: +2 cards to hand");
		printf("Expected %d cards. Got %d cards.\n", G.handCount[G.whoseTurn] + 2, testG.handCount[testG.whoseTurn]);
		
		//2. Deck + Played should be net -2 because player's deck loses 3 cards and player's discard gains smithy.
		assertTrue(testG.playedCardCount + testG.deckCount[testG.whoseTurn] == G.playedCardCount + G.deckCount[G.whoseTurn] - 2, "Test 2: Deck + Discard.");
		printf("Expected %d cards. Got %d cards.\n", G.playedCardCount + G.deckCount[G.whoseTurn] - 2, testG.playedCardCount + testG.deckCount[testG.whoseTurn]);
		
		//3. No state changes occur for other players.
		for (i = 0; i < numPlayers; i++)
		{
			if (i != G.whoseTurn)
			{
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
			assertTrue(testG.supplyCount[i] = G.supplyCount[i], "Card pile.");
		}		

	}
}

int main ()
{
	srand(time(NULL));
	testCard();
	return 0;
}