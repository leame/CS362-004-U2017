/*
 * unittest3.c
 * unit test for isGameOver function
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest3: unittest1.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 */

/*
* Business rules:
* 1. The game is over when the province stack is empty. 
* 2. The game is over when 3 supply piles are empty.
* 3. Otherwise, the game is not over.
*
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "isGameOver()"

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

int main()
{
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing %s ----------------\n", TESTFUNCTION);
	
	// copy the game state to a test case	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//initial game state. !isGameOver
	assertTrue(isGameOver(&testG) == 0, "Test 1: Game in progress.");
	
	//set province stack to 0. province enum is 3
	testG.supplyCount[3] = 0;
	assertTrue(isGameOver(&testG) == 1, "Test 2: Province stack empty.");
	
	//copy game state to reset to !isGameOver
	memcpy(&testG, &G, sizeof(struct gameState));
	//set first 3 supply stacks to 0. enum 0, 1, 2
	testG.supplyCount[0] = 0;
	testG.supplyCount[1] = 0;
	testG.supplyCount[2] = 0;
	assertTrue(isGameOver(&testG) == 1, "Test 3: 3 empty supply stacks.");	
	
	printf("-----------------%d/%d TESTS PASSED FOR %s----------------\n", passedTest, numTest, TESTFUNCTION);
	return 0;
}