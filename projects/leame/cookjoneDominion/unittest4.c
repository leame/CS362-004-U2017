/*
 * unittest4.c
 * unit test for getCost function
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */

/*
* Business rules:
*http://wiki.dominionstrategy.com/index.php/List_of_cards
* 1. Cards should have the correct cost.
*
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "getCost()"

int numTest = 0;
int passedTest = 0;

int assertTrue(int testVal, char* testName, int i)
{
	numTest++;
	
	if (testVal)
	{
		printf("PASS: %s %d\n", testName, i);
		passedTest++;
	}
	else
	{
		printf("FAIL: %s %d\n", testName, i);
	}
	
	return 0;
}

//expected cost values
int expectedCost(int cardNumber)
{
  switch( cardNumber ) 
    {
    case curse:
      return 0;
    case estate:
      return 2;
    case duchy:
      return 5;
    case province:
      return 8;
    case copper:
      return 0;
    case silver:
      return 3;
    case gold:
      return 6;
    case adventurer:
      return 6;
    case council_room:
      return 5;
    case feast:
      return 4;
    case gardens:
      return 4;
    case mine:
      return 5;
    case remodel:
      return 4;
    case smithy:
      return 4;
    case village:
      return 3;
    case baron:
      return 4;
    case great_hall:
      return 3;
    case minion:
      return 5;
    case steward:
      return 3;
    case tribute:
      return 5;
    case ambassador:
      return 3;
    case cutpurse:
      return 4;
    case embargo: 
      return 2;
    case outpost:
      return 5;
    case salvager:
      return 4;
    case sea_hag:
      return 4;
    case treasure_map:
      return 4;
    }
	
  return -1;
}

int main() {
	int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing %s ----------------\n", TESTFUNCTION);
	
	for (i = 0; i < 27; i++)
	{
		assertTrue(expectedCost(i) == getCost(i), "Testing enum", i);
		printf("Expected value %d. Got value %d.\n", expectedCost(i), getCost(i));
	}
	
	printf("-----------------%d/%d TESTS PASSED FOR %s----------------\n", passedTest, numTest, TESTFUNCTION);
	
	return 0;
		
}