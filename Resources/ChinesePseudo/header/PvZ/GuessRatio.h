/*
 * GuessRatio.h
 *
 *  Created on: 2019-12-24
 *      Author: zhousen
 */

#ifndef GUESSRATIO_H_
#define GUESSRATIO_H_

enum GuessResult
{
    Guess_Invalid = -1, 
    Guess_Win = 1,
    Guess_Lose,
    Guess_Draw,
};

// win ratio should between 0 ~ 1
struct GuessRatio
{
public:
    GuessRatio(float win);
    GuessResult GetResult();

    float _winRatio;
};

// win ratio should between 0 ~ 1
struct GuessThreeConditionRatio
{
public:
    GuessThreeConditionRatio(float win, float lose);
    GuessResult GetResult();

    float _winRatio;
    float _loseRatio;
    float _drawRatio;
};


#endif /* GUESSRATIO_H_ */
