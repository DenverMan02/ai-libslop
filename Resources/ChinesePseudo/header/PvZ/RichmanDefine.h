/*
 * RichmanDefine.h
 *
 *  Created on: 2019-12-19
 *      Author: zhousen
 */

#ifndef RICHMANDEFINE_H_
#define RICHMANDEFINE_H_


enum RichmanTileEventType
{
    TileEvent_None = -1,
    TileEvent_MoveForward,// move N tiles
    TIleEvent_MoveBackward,// move N tiles
    TileEvent_ThrowAgain,// throw new move value
    TileEvent_Start,// get reward from start position
    TileEvent_Reward,// get reward
    TileEvent_Reward_Big,// get plant pieces
    TileEvent_Reward_Coin3,// get coins x 3
    TileEvent_Reward_Coin4,// get coins x 4
    TileEvent_Reward_PlantPiecesChest,// get plant pieces chest
    TileEvent_Reward_AvatarPiecesChest,// get avatar pieces chest
    TileEvent_MiniGame,// go to mini game
    TileEvent_BossBattle,// go to boss battle
    TileEvent_WorldLevel,// go to world level
    TileEvent_GuessGame,// guess game 
    TileEvent_Max,
};

namespace Message 
{
    // execute event
    void TileEvent_MoveForward(int step);
    void TileEvent_MoveForward_Index(int index);
    void TileEvent_MoveBackward(int step);
    void TileEvent_MoveBackward_Index(int index);
    void TileEvent_ThrowAgain(int min, int max);
    void TileEvent_Start();
    void TileEvent_Reward();
    void TileEvent_MiniGame();
    void TileEvent_BossBattle();
    void TileEvent_WorldLevel();
    void TileEvent_GuessGame();

    // post event
    void TileEvent_MoveForward_Post(int step);
    void TileEvent_MoveForward_Index_Post(int index);
    void TileEvent_MoveBackward_Post(int step);
    void TileEvent_MoveBackward_Index_Post(int index);
    void TileEvent_ThrowAgain_Post(int min, int max);
    void TileEvent_Start_Post();
    void TileEvent_Reward_Post();
    void TileEvent_MiniGame_Post();
    void TileEvent_BossBattle_Post();
    void TileEvent_WorldLevel_Post();
    void TileEvent_GuessGame_Post(int bet, int result);
}

// scissor > paper
// paper > rock
// rock > scissor
enum GuessGameType 
{
    GuessGame_Default = 1,
    GuessGame_Scissor = GuessGame_Default,
    GuessGame_Rock,
    GuessGame_Paper,
};

// server protocol type
enum {
    Richman_Protocol_MiniGame = 2,// get bonus battle event
    Richman_Protocol_WorldLevel = 2,
    Richman_Protocol_BossBattle = 3,
    Richman_Protocol_GuessGame = 4,
    Richman_Protocol_MoveForward = 5,
    Richman_Protocol_MoveBackward = 6,
};

#define RICHMAN_COURSE_EVENT_MAX (24)

#define RICHMAN_PLANT_PIECES_CHEST_ID (52289)
#define RICHMAN_AVATAR_PIECES_CHEST_ID (52288)
#define RICHMAN_START_CHEST_ID (23042)

#endif /* RICHMANDEFINE_H_ */
