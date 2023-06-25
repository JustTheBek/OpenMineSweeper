/*!
 * @file GameLogic.c
 * @author JustTheBek
  *
 * @brief One line description of file
 * @details
 * An optional detailed description of file
 *
 * @ingroup GameLogic
 * @{
 */

/*
 **********************************************************************
 * INCLUDES
 **********************************************************************
 */

#include <glib.h>
#include "GameLogic.h"

/*
 **********************************************************************
 * DEFINES
 **********************************************************************
 */

#define DEVELOPMENT_MODE //TODO. defines this by cmake

/*
 **********************************************************************
 * LOCAL MACROS
 **********************************************************************
 */

/*
 **********************************************************************
 * LOCAL DATA TYPES/STRUCTS/ENUMS
 **********************************************************************
 */

struct Gl_GameLogicType
{
  guint32 NumOfMines;
  guint32 NumOfUnrevealedFields;
  GRand* MineGenerator;
  Gl_FieldValueType** GameBoard;
  Gl_GameConfigType GameConfig;
};

/*
 **********************************************************************
 * LOCAL CONSTANTS
 **********************************************************************
 */

/*
 **********************************************************************
 * LOCAL VARIABLES
 **********************************************************************
 */

/*
 **********************************************************************
 * LOCAL FUNCTION PROTOTYPES
 **********************************************************************
 */

static void Gl_PrintGameBoardToConsole(Gl_GameLogicType* this);
static void Gl_GenerateMines(Gl_GameLogicType* this);

/*
 **********************************************************************
 * FUNCTION IMPLEMENTATIONS
 **********************************************************************
 */

#ifdef DEVELOPMENT_MODE
static void Gl_PrintGameBoardToConsole(Gl_GameLogicType* this)
{
  for(guint32 row = 0; row < (guint32)this->GameConfig.Rows; row++)
  {
    for(guint32 col = 0; col < (guint32)this->GameConfig.Columns; col++)
    {
      if(this->GameBoard[row][col] == GL_FIELD_VALUE_MINE)
      {
        g_print(" X ");
      }
      else if(this->GameBoard[row][col] == GL_FIELD_VALUE_UNKOWN)
      {
        g_print(" _ ");
      }
      else
      {
        g_print(" %d ",this->GameBoard[row][col]);
      }
    }
    g_print("\n");
  }
}
#endif

static void Gl_GenerateMines(Gl_GameLogicType* this)
{
  if(this == NULL)
  {
    g_print("Game Logic invalid, mine generation failed!\n");
  }
  else
  {
    guint32 numOfFields = ((guint32)this->GameConfig.Rows) * ((guint32)this->GameConfig.Columns);
    this->NumOfMines = (guint32)(((gfloat)numOfFields) * (this->GameConfig.Difficulty));
    this->NumOfUnrevealedFields = numOfFields-(this->NumOfMines);
    guint32 row = 0u;
    guint32 col = 0u;

    for(guint32 mineCount = 0u; mineCount < (this->NumOfMines); mineCount++)
    {
      gboolean mineValid = FALSE;

      do
      {
        row = g_rand_int_range(this->MineGenerator ,0u, (guint32)(this->GameConfig.Rows));
        col = g_rand_int_range(this->MineGenerator ,0u, (guint32)(this->GameConfig.Columns));
        if(((row >=0) && (row < (this->GameConfig.Rows)))
        &&((col >=0) && (col < (this->GameConfig.Columns)))
        &&(this->GameBoard[row][col] != GL_FIELD_VALUE_MINE))
        {
          this->GameBoard[row][col] = GL_FIELD_VALUE_MINE;
          mineValid = TRUE;
        }
      }while(mineValid == FALSE);
      mineValid = FALSE;
    }
  }
}

Gl_GameLogicType* Gl_NewGameLogic(const Gl_GameConfigType* gameConfig) // constructor
{
  Gl_GameLogicType* gameLogic = NULL;

  if(gameConfig == NULL)
  {
    g_print("Invalid Game Configuration!\n");
  }
  else
  {
    gameLogic = (Gl_GameLogicType*)g_malloc(sizeof(Gl_GameLogicType));

    if(gameLogic == NULL)
    {
      g_print("Allocation of Game Logic failed!\n");
    }
    else
    {
      // Store Game Config
      memcpy(&(gameLogic->GameConfig), gameConfig, sizeof(Gl_GameConfigType));

      // Allocate Game Board and init fields with unknown value
      gameLogic->GameBoard = (Gl_FieldValueType**)g_malloc((gameLogic->GameConfig.Rows)*sizeof(Gl_FieldValueType*));
      for(guint32 row = 0; row < (guint32)gameLogic->GameConfig.Rows; row++)
      {
        gameLogic->GameBoard[row] = (Gl_FieldValueType*)g_malloc((gameLogic->GameConfig.Columns)*(sizeof(Gl_FieldValueType)));
        memset(gameLogic->GameBoard[row], GL_FIELD_VALUE_UNKOWN, (gameLogic->GameConfig.Columns)*(sizeof(Gl_FieldValueType)));
      }

      // Generate Mines
      gameLogic->MineGenerator = g_rand_new();
      Gl_GenerateMines(gameLogic);

      #ifdef DEVELOPMENT_MODE
      Gl_PrintGameBoardToConsole(gameLogic);
      #endif

    }
  }
  return gameLogic;
}
/*! @} */
