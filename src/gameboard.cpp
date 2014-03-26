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
#include "gameboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool operator==(const Color &lhs, const Peg & rhs)
{
	return (lhs == rhs.color);
};

bool operator==(const Peg & lhs, const Color & rhs) 
{
	return (lhs.color == rhs);
};

/*
 * Points earned is the number of guesses by the code
 * breaker. If the code breaker has lost then the code maker
 * score is the total number of quesses plus one.
 */
unsigned int
GameBoard::GetCodeMakerPoints(void) const
{
        if (GameBoard::MaxGuesses == _attempts) {
                return ((NPC_Has_Won == _outcome) ? (1 + GameBoard::MaxGuesses) : _attempts);
        }

        return _attempts;
};

bool
GameBoard::SetSecret(const row_t & secret)
{
        if ((NONE == secret[0])
            ||  (NONE == secret[1])
            ||  (NONE == secret[2])
            ||  (NONE == secret[3])) {
                return false;
        }

	for (int n = 0; n < 4; ++n) {
		_secret[n] = secret[n];
	}

	_initiated = true;
        return true;
};

bool
GameBoard::EvaluateGuess(const row_t & guess,
			 unsigned int & blacks,
			 unsigned int & whites)
{
        blacks = 0;
        whites = 0;

	if (!_initiated) {
		return false;
	}
	
        // validate input
	for (int n = 0; n < 4; ++n) {
		if (NONE == guess[n]) {
			return false;
		}
        }
	
	if (GameBoard::MaxGuesses == _attempts) {
                _outcome = NPC_Has_Won;
                return true;
        }
        ++_attempts;

        // set number of black - correct color and correct placement
        unsigned short guess_pegs_used = 0x0000;
        for (int n = 0; n < 4; ++ n) {
                if (_secret[n] == guess[n]) {
                        guess_pegs_used |= 1 << n;
                        ++blacks;
                }
        }
        if (4 == blacks) {
                _outcome = NPC_Has_Lost;
                return true;
        }

	// set the number of correct colors with wrong placement
        unsigned short secret_pegs_used = guess_pegs_used;
        for (int g = 0; g < 4; ++g) {
                // this guess peg has been matched
                if (((1 << g) & guess_pegs_used)) {
                        continue;
                }

                for (int s = 0; s < 4; ++s) {
			if (((1 << s) & secret_pegs_used)) {
				continue;
			}
			if (_secret[s] == guess[g]) {
				guess_pegs_used |= 1 << g;
				secret_pegs_used |= 1 << s;
				++whites;
				break;
			}
                }
        }

        return true;
};

Outcome
GameBoard::GetGameState(void)
{
	if (!_initiated) {
                return Undecided;
	}

        if (Undecided != _outcome) {
                return _outcome;
        }

        if (!_attempts) {
                return Undecided;
        }

        if (GameBoard::MaxGuesses == _attempts) {
                _outcome = NPC_Has_Won;
                return NPC_Has_Won;
        }

        return Undecided;
};
