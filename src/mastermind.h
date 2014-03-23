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

#ifndef __MASTERMIND_H__
#define __MASTERMIND_H__

enum Outcome {Undecided, NPC_Has_Won, NPC_Has_Lost};
enum Color {NONE, Black, Red, White, Pink, Green, Yellow};

/*
 * A colored code peg
 */
class Peg
{
public:
	Peg()
		: color(NONE)
		{
		};

	Peg(Color kind)
		: color(kind)
		{
		};

	virtual ~Peg()
		{
		};
	
	bool operator==(const Peg & rhs) const
		{
			return (color == rhs.color);
		};

	Peg& operator=(Color rhs)
		{
			color = rhs;

			return *this;
		};

	Color color;
};
typedef Peg row_t[4];

/*
 * The game class
 */
class Game
{
public:
	Game()
		: _npc_is_codebreaker(true)
		{
		};

	virtual ~Game()
		{
		};

 	void run(void);

	void determine_role(void);
	
private:
	bool _npc_is_codebreaker;
	
};


/*
 * CodeBreaker and CodeMaker descents from this one
 */
class GameRole
{
public:
	GameRole(void)
		{
		};
	
	virtual ~GameRole()
		{
		};

 	virtual void run(void) = 0;

};


#endif /* __MASTERMIND_H__ */
