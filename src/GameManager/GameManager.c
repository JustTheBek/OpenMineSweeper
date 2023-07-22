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

#include <glib.h>
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
  Gl_GameLogicType* GameLogic;
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

  // TODO incomplete allocation, add checks as in GameLogic
  gameManager = (Gm_GameManagerType*)g_malloc(sizeof(Gm_GameManagerType));


  // ### TODO: testing GameLogic, remove if done and do it correctly############
  const Gl_GameConfigType gameConfig =
  {
     .Rows    = 5,
     .Columns = 5,
     .Difficulty = GL_DIFFICULTY_MODERATE,
  };

  gameManager->GameLogic = Gl_NewGameLogic(&gameConfig);
  Gl_FieldCoordinateType flag =
  {
      .Row = 0,
      .Column = 3,
  };
  Gl_ToggleFlag(gameManager->GameLogic, flag);
  Gl_DevApi_PrintGameBoardToConsole(gameManager->GameLogic, TRUE);
 // ### end of Gam logic testin block##############################################

  return gameManager;
}

void Gm_DestroyGameManager(Gm_GameManagerType* this)
{
  if(this != NULL) // avoids double free call
  {
    // TODO: destroy allocated children before destroying GameManager
    Gl_DeallocateGameLogic(this->GameLogic);
    // .... Game Board
    // .... etc

    g_free(this); // deallocate memory
    this = NULL;  // set ptr null, to make former allocated memory unreachable
  }

  return;
}

void Gm_RevealField(Gm_GameManagerType* this, Gm_KlickCoordinateType coordinates)
{
  Gl_FieldCoordinateType fieldCoordinates = {0,0};
  // TODO: calculate fieldCoordinates from klickCoordinates
  Gl_OperationResultType retVal = Gl_RevealField(this->GameLogic, fieldCoordinates);

  switch(retVal)
  {
    case GL_OPERATION_SUCCEEDED:
    {
      // check field value and handle accordingly (use recursion to discover and draw other field)
      break;
    }
    case GL_OPERATION_NOT_SUPPORTED:
    {
      // nothing shall happen, neglect operation
      break;
    }
    default:
    {
      // finish game
      break;
    }
  }
}

void Gm_ToggleFlag(Gm_GameManagerType* this, Gm_KlickCoordinateType coordinates)
{
  Gl_FieldCoordinateType fieldCoordinates = {0,0};
  // TODO: calculate fieldCoordinates from klickCoordinates
  Gl_OperationResultType retVal = Gl_ToggleFlag(this->GameLogic, fieldCoordinates);

  switch(retVal)
  {
    case GL_OPERATION_SUCCEEDED:
    {
      // set/reset flag symbol on given field
      break;
    }
    case GL_OPERATION_NOT_SUPPORTED:
    {
      // nothing shall happen, neglect operation
      break;
    }
    default:
    {
      // finish game
      break;
    }
  }
}

void Gm_RestartGame(Gm_GameManagerType* this)
{
  // TODO: add implementation
  g_print("Functionality not implemented yet!\n");
}

void Gm_NewGame(Gm_GameManagerType* this)
{
  // TODO: add implementation
  g_print("Functionality not implemented yet!\n");
}

void Gm_LoadGame(Gm_GameManagerType* this)
{
  // TODO: add implementation
  g_print("Functionality not implemented yet!\n");
}

void Gm_SaveGame(Gm_GameManagerType* this)
{
  // TODO: add implementation
  g_print("Functionality not implemented yet!\n");
}

void Gm_InformationRequest(Gm_GameManagerType* this)
{
  // TODO: add implementation
  g_print("Functionality not implemented yet!\n");
}

/*! @} */
