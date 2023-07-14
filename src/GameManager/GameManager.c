/*!
 * @file GameManager.c
 * @author JustTheBek
  *
 * @brief Implementation of the GameManager class.
 * @details
 * An optional detailed description of file
 *
 * @ingroup GameManager
 * @{
 */

/*
 **********************************************************************
 * INCLUDES
 **********************************************************************
 */

#include "GameManager.h"
#include "GameLogic.h"

/*
 **********************************************************************
 * PRIVATE DEFINES
 **********************************************************************
 */

/*
 **********************************************************************
 * PRIVATE MACROS
 **********************************************************************
 */

/*
 **********************************************************************
 * PRIVATE DATA TYPES/STRUCTS/ENUMS
 **********************************************************************
 */

/*
 **********************************************************************
 * CLASS DEFINITION
 **********************************************************************
 */

struct Gm_GameManagerType
{

};

/*
 **********************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************
 */

/*
 **********************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS
 **********************************************************************
 */

/*
 **********************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS
 **********************************************************************
 */

Gm_GameManagerType* Gm_NewGameManager(void)
{
  Gm_GameManagerType* gameManager = NULL;

  // TODO: testing GameLogic, remove if done
  const Gl_GameConfigType gameConfig =
  {
     .Rows    = 5,
     .Columns = 5,
     .Difficulty = GL_DIFFICULTY_MODERATE,
  };

  Gl_GameLogicType* gameLogic = Gl_NewGameLogic(&gameConfig);
  Gl_FieldCoordinateType flag =
  {
      .Row = 0,
      .Column = 3,
  };
  Gl_ToggleFlag(gameLogic, flag);
  Gl_DevApi_PrintGameBoardToConsole(gameLogic, TRUE);

  return gameManager;
}

void Gm_DestroyGameManager(Gm_GameManagerType* this)
{

}

void Gm_RevealField(Gm_GameManagerType* this)
{

}

void Gm_ToggleFlag(Gm_GameManagerType* this)
{

}

void Gm_RestartGame(Gm_GameManagerType* this)
{

}

void Gm_NewGame(Gm_GameManagerType* this)
{

}

void Gm_LoadGame(Gm_GameManagerType* this)
{

}

void Gm_SaveGame(Gm_GameManagerType* this)
{

}

void Gm_InformationRequest(Gm_GameManagerType* this)
{

}

/*! @} */
