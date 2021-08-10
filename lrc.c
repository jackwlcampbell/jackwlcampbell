//lrc.c file
// "Random Seed:"
// "How many players:"
// /* function_name:

#include "philos.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// returns position of the player to the left.
static inline uint8_t left(uint8_t pos, uint8_t players) { //creating the function left()
    return ((pos + players - 1) % players);
}

// returns position of the player to the right.
static inline uint8_t right(uint8_t pos, uint8_t players) { //creating the function right()
    return ((pos + 1) % players);
}

int main(void) {

    //
    //
    //initializing variables
    //
    //
    int seedNum, playerNum, centerPot, rollNum, leftPos, rightPos, result, playerEND, winner_idx;
    centerPot = rollNum = winner_idx = 0;

    //
    //prompting user for a random seed
    //
    //seedNum: the value input from the user
    //
    printf("Random seed: ");
    scanf("%d", &seedNum);
    if (seedNum < 0) {
        printf("Pseudorandom seed must be non-negative (%d).\n", seedNum);
        return 0;
    }

    //
    //prompting user for a number of players
    //
    //playerNum: the value input from the user
    //
    printf("How many players? ");
    scanf("%d", &playerNum);
    if (playerNum < 2 || playerNum > 14) { //makes sure number of players is from 2 - 14.
        printf("Number of players must be from 1 to 14\n");
        return 0;
    }

    srand(seedNum); //creating the random seed
    int playerPos = 0;

    //
    //creating an array of the players money
    //
    int money[playerNum]; // creating an array of the players money
    for (int i = 0; i < playerNum; ++i) {
        money[i] = 3;
    }

    //
    //creates an array named die[] of type "faces"
    //
    typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
    faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

    //
    //main game loop.
    //
    //runs until break condition is met
    //
    while (1) {

        //
        //assigns number of rolls players have based on their current money
        //
        //rollNum: number of times player can roll the dice
        //
        if (money[playerPos] == 0) {
            playerPos = right(playerPos, playerNum);
            continue;
        }

        if (money[playerPos] == 1) {
            rollNum = 1;
        }

        if (money[playerPos] == 2) {
            rollNum = 2;
        }

        if (money[playerPos] >= 3) {
            rollNum = 3;
        }

        printf("%s rolls...", philosophers[playerPos]);

        //
        //main dice rolling loop
        //
        //runs as many times as the current player has dice rolls/rollNum
        //
        for (int k = 0; k < rollNum; ++k) {
            result = die[rand()
                         % 6]; //generates a random index of the die[] array and sets it to result

            //
            //checks value of 'result' and transfers money according to the game rules
            //
            if (result == LEFT) {
                money[playerPos] = money[playerPos] - 1; //decrements player money by one
                leftPos = left(
                    playerPos, playerNum); //finds index of player to the left of the current player
                money[leftPos] = money[leftPos] + 1; //increments left players money by one
                printf(" gives $1 to ");
                printf("%s", philosophers[leftPos]);
            }

            if (result == RIGHT) {
                money[playerPos] = money[playerPos] - 1; //decrements player money by one
                rightPos = right(playerPos,
                    playerNum); //finds index of player to the right of the current player
                money[rightPos] = money[rightPos] + 1; //increments right players money by one
                printf(" gives $1 to ");
                printf("%s", philosophers[rightPos]);
            }

            if (result == CENTER) {
                money[playerPos] = money[playerPos] - 1;
                centerPot = centerPot + 1; //increments the centerPot value by one
                printf(" puts $1 in the pot");
            }

            if (result == PASS) {
                printf(" gets a pass");
            }

        } //for loop END

        printf("\n");
        playerPos = right(playerPos, playerNum); //increments the current player by one

        //
        //end condition check: counts number of players still with money
        //
        //when the number of players with money is just one, there is a winner
        //
        playerEND = 0; //resets count of players out of the game
        for (int u = 0; u < playerNum; ++u) { //loops through all players
            if (money[u] != 0) {
                playerEND = playerEND + 1;
                winner_idx = u; //stores the index of the winner
            }
        } //for2 loop END

        if (playerEND == 1) { //if there is only one player with money, break
            break;
        }
    } // while loop END

    printf("%s wins the $%d pot with $%d left in the bank!\n", philosophers[winner_idx], centerPot,
        money[winner_idx]);
    return 0;

} // main loop END
