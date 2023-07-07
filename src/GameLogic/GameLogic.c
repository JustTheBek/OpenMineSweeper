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
 * PRIVATE DEFINES
 **********************************************************************
 */


#define GL_FLAG_IS_SET              (gboolean)TRUE
#define GL_FLAG_IS_NOT_SET         (gboolean)FALSE

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

struct Gl_GameLogicType
{
  guint32 NumOfMines;
  guint32 NumOfFlags;
  guint32 NumOfUnrevealedFields;
  GRand* MineGenerator;
  gboolean** FlagField;
  Gl_FieldValueType** GameBoard;
  Gl_GameConfigType GameConfig;
  Gl_GameStatusType GameStatus;
};

/*
 **********************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************
 */

#ifdef DEVELOPMENT_MODE
static void Gl_PrintGameBoardToConsole(Gl_GameLogicType* this, gboolean showMines);
#endif

static void Gl_CalculateFieldValue(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates);
static void Gl_GenerateMines(Gl_GameLogicType* this);
static void Gl_EvaluateRevealedField(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates);
static void Gl_CheckVictory(Gl_GameLogicType* this);

/*
 **********************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS
 **********************************************************************
 */

#ifdef DEVELOPMENT_MODE
static void Gl_PrintGameBoardToConsole(Gl_GameLogicType* this, gboolean showMines)
{
  for(guint32 row = 0; row < (guint32)this->GameConfig.Rows; row++)
  {
    for(guint32 col = 0; col < (guint32)this->GameConfig.Columns; col++)
    {
      if(this->FlagField[row][col] == GL_FLAG_IS_SET)
      {
        g_print(" I ");
      }
      else if(this->GameBoard[row][col] == GL_FIELD_VALUE_MINE)
      {
        if(showMines == TRUE)
        {
          g_print(" X ");
        }
        else
        {
          g_print(" _ ");
        }
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
  // seprator line: ugly but thin implementation, is just a dev function, covers no real functionality, should be ok :D
  g_print("\n"); for(guint32 col = 0; col < (guint32)this->GameConfig.Columns; col++){g_print("---");}g_print("\n\n");
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

static void Gl_CalculateFieldValue(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates)
{
  if(this == NULL)
  {
    g_print("Game Logic invalid!\n");
  }
  else
  {
    //TODO
  }
}

static void Gl_EvaluateRevealedField(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates)
{
  if(this == NULL)
  {
    g_print("Game Logic invalid!\n");
  }
  else
  {
    Gl_FieldValueType revealedField = this->GameBoard[FieldCoordinates.Row][FieldCoordinates.Column];

    switch(revealedField)
    {
      case GL_FIELD_VALUE_MINE:
      {
        this->GameStatus = GL_LOST;
        break;
      }
      case GL_FIELD_VALUE_UNKOWN:
      {
        Gl_CalculateFieldValue(this,FieldCoordinates);
        this->NumOfUnrevealedFields--;
        Gl_CheckVictory(this);
        break;
      }
      default:
      {
        g_print("Field was already revealed.\n");
        break;
      }
    }
  }
}

static void Gl_CheckVictory(Gl_GameLogicType* this)
{
  if((this->NumOfUnrevealedFields == 0) && (this->NumOfFlags == this->NumOfMines))
  {
    this->GameStatus =  GL_VICTORY;
  }
}

/*
 **********************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS
 **********************************************************************
 */

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

      // Allocate Game Board + Flag Field and init fields with default values
      gameLogic->GameBoard = (Gl_FieldValueType**)g_malloc((gameLogic->GameConfig.Rows)*sizeof(Gl_FieldValueType*));
      gameLogic->FlagField = (gboolean**)g_malloc((gameLogic->GameConfig.Rows)*sizeof(gboolean*));

      for(guint32 row = 0; row < (guint32)gameLogic->GameConfig.Rows; row++)
      {
        gameLogic->GameBoard[row] = (Gl_FieldValueType*)g_malloc((gameLogic->GameConfig.Columns)*(sizeof(Gl_FieldValueType)));
        memset(gameLogic->GameBoard[row], GL_FIELD_VALUE_UNKOWN, (gameLogic->GameConfig.Columns)*(sizeof(Gl_FieldValueType)));

        gameLogic->FlagField[row] = (gboolean*)g_malloc((gameLogic->GameConfig.Columns)*(sizeof(gboolean)));
        memset(gameLogic->FlagField[row], GL_FLAG_IS_NOT_SET, (gameLogic->GameConfig.Columns)*(sizeof(gboolean)));
      }

      // Generate Mines
      gameLogic->MineGenerator = g_rand_new();
      Gl_GenerateMines(gameLogic);

      #ifdef DEVELOPMENT_MODE
      Gl_PrintGameBoardToConsole(gameLogic, TRUE);
      #endif

      gameLogic->GameStatus = GL_RUNNING;
    }
  }
  return gameLogic;
}

Gl_FieldValueType Gl_RevealField(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates)
{
  Gl_FieldValueType retVal = 0;

  if(((FieldCoordinates.Row < 0) || (FieldCoordinates.Row >= this->GameConfig.Rows))
      ||((FieldCoordinates.Column < 0) || (FieldCoordinates.Column >= this->GameConfig.Columns))
      ||(this == NULL))
  {
    g_print("Gl_GetFieldValue invalid function parameter!\n");
  }
  else
  {
    if(this->GameStatus != GL_RUNNING)
    {
      g_print("No game is running at the moment!\n");
    }
    else
    {
      Gl_EvaluateRevealedField(this, FieldCoordinates);
      retVal = this->GameBoard[FieldCoordinates.Row][FieldCoordinates.Column];
    }
  }
  return retVal;
}

void Gl_SetFlag(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates)
{
  if(((FieldCoordinates.Row < 0) || (FieldCoordinates.Row >= this->GameConfig.Rows))
    ||((FieldCoordinates.Column < 0) || (FieldCoordinates.Column >= this->GameConfig.Columns))
    ||(this == NULL))
  {
    g_print("Gl_SetFlag invalid function parameter!\n");
  }
  else
  {
    guint16 row = FieldCoordinates.Row;
    guint16 col = FieldCoordinates.Column;

    // flag will be set only if it was not set yet and if the field is still not revealed
    if((this->FlagField[row][col] == GL_FLAG_IS_NOT_SET) &&
        ((this->GameBoard[row][col] == GL_FIELD_VALUE_UNKOWN) || (this->GameBoard[row][col] == GL_FIELD_VALUE_MINE)))
    {
      this->FlagField[row][col] = GL_FLAG_IS_SET;
      this->NumOfFlags++;
      Gl_CheckVictory(this);
    }
  }
}

void Gl_ResetFlag(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates)
{
  if(((FieldCoordinates.Row < 0) || (FieldCoordinates.Row >= this->GameConfig.Rows))
    ||((FieldCoordinates.Column < 0) || (FieldCoordinates.Column >= this->GameConfig.Columns))
    ||(this == NULL))
  {
    g_print("Gl_ResetFlag invalid function parameter!\n");
  }
  else
  {
    guint16 row = FieldCoordinates.Row;
    guint16 col = FieldCoordinates.Column;

    // flag will be reset only if it was set previously and if the field is still not reveald
    if((this->FlagField[row][col] == GL_FLAG_IS_SET) &&
        ((this->GameBoard[row][col] == GL_FIELD_VALUE_UNKOWN) || (this->GameBoard[row][col] == GL_FIELD_VALUE_MINE)))
    {
      this->FlagField[row][col] = GL_FLAG_IS_NOT_SET;
      this->NumOfFlags--;
    }
  }
}

guint32 Gl_GetNumberOfMines(Gl_GameLogicType* this)
{
  guint32 mineNum = 0;

  if(this == NULL)
  {
    g_print("Forwarded Game Logic invalid!\n");
  }
  else
  {
    mineNum = this->NumOfMines;
  }
  return mineNum;
}

Gl_GameStatusType Gl_GetGameStatus(Gl_GameLogicType* this)
{
  Gl_GameStatusType gameStatus = GL_LOST;

  if(this == NULL)
  {
    g_print("Forwarded Game Logic invalid!\n");
  }
  else
  {
    gameStatus = this->GameStatus;
  }
  return gameStatus;
}

#ifdef DEVELOPMENT_MODE
void Gl_DevApi_PrintGameBoardToConsole(Gl_GameLogicType* this, gboolean showMines)
{
  if(this == NULL)
  {
    g_print("Forwarded Game Logic invalid!\n");
  }
  else
  {
    Gl_PrintGameBoardToConsole(this, showMines);
  }
}
#endif
/*! @} */
