/*
 *    Copyright (C) 2014 Jules Colding <jcolding@gmail.com>.
 *
 *    All Rights Reserved.
 */

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     (1) Redistributions of source code must retain the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer.
 *
 *     (2) Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *     (3) Neither the name of the copyright holder nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "code_maker.h"
#include "gameboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <random>
#include <cmath>

static Color
char_to_color(const char i)
{
        switch (i) {
        case 'B':
                return Black;
        case 'R':
                return Red;
        case 'W':
                return White;
        case 'P':
                return Pink;
        case 'G':
                return Green;
        case 'Y':
                return Yellow;
        default:
                return NONE;
        }
}

void CodeMaker::run(void)
{
        printf("The following colored pegs are available:\n");
        printf("\tBlack ('B')\n");
        printf("\tRed ('R')\n");
        printf("\tWhite ('W')\n");
        printf("\tPink ('P')\n");
        printf("\tGreen ('G')\n");
        printf("\tYellow ('Y')\n");
        printf("\n");

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distr(1, 6);

        GameBoard gb;
        row_t secret = {
                char_to_color(distr(gen)),
                char_to_color(distr(gen)),
                char_to_color(distr(gen)),
                char_to_color(distr(gen))
        };
        gb.SetSecret(secret);

        printf("My secret has been created. Please enter your guesses\n");
        printf("using the one-letter color codes above.\n");

        row_t guess;
        unsigned int peg_num = 0;
        char color_code;
        unsigned int blacks;
        unsigned int whites;
        Outcome game_result = Undecided;
        do {
                do {
                        color_code = getchar();
                        switch (color_code) {
                        case 'B':
                        case 'R':
                        case 'W':
                        case 'P':
                        case 'G':
                        case 'Y':
                                guess[peg_num++] = char_to_color(color_code);
                                break;
                        default:
                                break;
                        }
                } while (4 > peg_num);

                if (!gb.EvaluateGuess(guess, blacks, whites)) {
                        continue;
                }
                game_result = gb.GetGameState();
        } while (Undecided == game_result);

        switch (game_result) {
        case NPC_Has_Won:
                printf("The computer has won this round\n");
                break;
        case NPC_Has_Lost:
                printf("You won this round\n");
                break;
        default:
                printf("There is a bug somewhere...\n");
        }
        printf("The computer earned %d points\n", gb.GetCodeMakerPoints());
}