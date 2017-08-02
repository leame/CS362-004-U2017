/*
 * randomtestadventurer.c
 * random test for adventurer
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 */
 
 /*
* Business rules:
* 1. Player gains 2 cards. 
* 2. Those 2 cards are treasure cards.
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

#define TESTCARD "adventurer"
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
	int currCard;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
			
	printf("-----------------Testing %s ----------------\n", TESTCARD);	
	
	for (j = 0; j < NUMTEST; j++)
	{
		int preTreasure = 0;
		int postTreasure = 0;
	
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
		//randomly remove a card that's not adventurer
		discardCard( (rand()%10) + 1, G.whoseTurn, &G, 0);
		//shuffle the deck
		shuffle(0, &G);
		//take a card from the deck to the player's hand
		drawCard(0, &G);
		}
		
		printf("-----------------%d/%d Iterations. Players: %d. ----------------\n", currTest, NUMTEST, numPlayers);
		
		// copy the game state to a test case	
		memcpy(&testG, &G, sizeof(struct gameState));
		
		//play adventurer
		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
		
		//1. Player gains 2 cards to hand and discards adventurer, resulting in a net of +1 cards to hand
		assertTrue(testG.handCount[testG.whoseTurn] == G.handCount[G.whoseTurn] + 1, "Test 1: +1 cards to hand");
		printf("Expected %d cards. Got %d cards.\n", G.handCount[G.whoseTurn] + 1, testG.handCount[testG.whoseTurn]);
		
		//Deck should be net -1 because player's hand gains 2 cards and player's deck gains 1 card.
		assertTrue(testG.playedCardCount + testG.deckCount[testG.whoseTurn] == G.playedCardCount + G.deckCount[G.whoseTurn] - 1, "Test 2: Deck + Played.");
		printf("Expected %d cards. Got %d cards.\n", G.playedCardCount + G.deckCount[G.whoseTurn] - 1, testG.playedCardCount + testG.deckCount[testG.whoseTurn]);
		
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
		
		assertTrue(postTreasure == preTreasure + 2, "Test 3: +2 Treasure cards to hand");
		printf("Expected %d treasure. Got %d treasure.\n",preTreasure + 2, postTreasure);
		
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