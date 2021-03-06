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

#include "mastermind.h"
#include "code_maker.h"
#include "code_breaker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
Game::run(void)
{
        determine_role();
        if (_npc_is_codebreaker) {
                CodeBreaker cb;
                cb.run();
        } else {
                CodeMaker cm;
                cm.run();
        }
        printf("Game over. Goddbye!\n");
}

void
Game::determine_role(void)
{
        printf("Press 'B' if you want to be the code breaker.\n");
        printf("Press 'M' if you want to be the code maker.\n");
        printf("The computer will assume the other role.\n");
        printf("All other keypresses will be ignored.\n");
        printf("Terminate the game at any time by pressing CTRL-C.\n");

        char role;
        do {
                role = getchar();
        } while (('B' != role) && ('M' != role));

        if ('B' == role) {
                _npc_is_codebreaker = false;
                printf("You are the code breaker. The computer will assume the role of code maker. Enjoy!\n");
        } else {
                _npc_is_codebreaker = true;
                printf("You are the code maker. The computer will assume the role of code breaker. Enjoy!\n");
        }

        printf("\nThe following colored pegs are available:\n");
        printf("\tBlack ('B')\n");
        printf("\tRed ('R')\n");
        printf("\tWhite ('W')\n");
        printf("\tPink ('P')\n");
        printf("\tGreen ('G')\n");
        printf("\tYellow ('Y')\n");
        printf("\n");
}
