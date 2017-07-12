CFLAGS = -Wall -fpic -coverage -lm

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g -std=c99 unittest1.c dominion.o rngs.o $(CFLAGS)
	
unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g -std=c99 unittest2.c dominion.o rngs.o $(CFLAGS)	

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g -std=c99 unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g -std=c99 unittest4.c dominion.o rngs.o $(CFLAGS)	
	
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g -std=c99 cardtest1.c dominion.o rngs.o $(CFLAGS)	

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g -std=c99 cardtest2.c dominion.o rngs.o $(CFLAGS)	

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g -std=c99 cardtest3.c dominion.o rngs.o $(CFLAGS)	

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g -std=c99 cardtest4.c dominion.o rngs.o $(CFLAGS)

assignment3_test_suite: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4	

run_3: assignment3_test_suite
	./unittest1 &> unittestresult.out
	gcov unittest1 >> unittestresult.out
	./unittest2 >> unittestresult.out
	gcov unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	gcov unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	gcov unittest4 >> unittestresult.out
	./cardtest1 >> unittestresult.out
	gcov cardtest1 >> unittestresult.out
	./cardtest2 >> unittestresult.out
	gcov cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	gcov cardtest3 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	gcov cardtest4 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresult.out

