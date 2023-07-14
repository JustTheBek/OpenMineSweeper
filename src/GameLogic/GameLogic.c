/*!
 * @file GameLogic.c
 * @author JustTheBek
  *
 * @brief Implementation of the GameLogic class.
 * @details
 * Instancing an object of this class generates a new game board
 * based on the settings forwarded to the constructor. The game
 * can be controlled via the public functions of the class. After
 * finishing the game the logic has to be destroyed by the destructor.
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

#define GL_FLAG_IS_SET                    (gboolean)TRUE
#define GL_FLAG_IS_NOT_SET                (gboolean)FALSE

#define GL_FIELD_VALUE_MASK                (guint8)0x0Fu
#define GL_CONTROL_FLAGS_MASK              (guint8)0xF0u

#define GL_MINE_SHIFT                      (guint8)4u
#define GL_FLAG_SHIFT                      (guint8)5u
#define GL_REVEALED_SHIFT                  (guint8)6u

#define GL_MINE_BIT                        ((guint8)1u << GL_MINE_SHIFT)
#define GL_FLAG_BIT                        ((guint8)1u << GL_FLAG_SHIFT)
#define GL_REVEALED_BIT                    ((guint8)1u << GL_REVEALED_SHIFT)

#define GL_BIT_SET                         (guint8)1u
#define GL_BIT_CLEAN                       (guint8)0u

/*
 **********************************************************************
 * PRIVATE MACROS
 **********************************************************************
 */

// macros to set/get/reset bit(s) of a uint8 field
#define GL_SET(field,bit) (field |=  bit)
#define GL_GET(field,bit) (field &   bit)
#define GL_CLR(field,bit) (field &= (~bit))

// macros to manage flags of a game board field
#define GL_PLACE_MINE(field)            GL_SET(field, GL_MINE_BIT)
#define GL_CHECK_MINE(field)            GL_GET(field, GL_MINE_BIT) >> GL_MINE_SHIFT

#define GL_PLACE_FLAG(field)            GL_SET(field, GL_FLAG_BIT)
#define GL_CHECK_FLAG(field)            GL_GET(field, GL_FLAG_BIT) >> GL_FLAG_SHIFT
#define GL_REMOVE_FLAG(field)           GL_CLR(field, GL_FLAG_BIT)

#define GL_PLACE_REVEALED(field)        GL_SET(field, GL_REVEALED_BIT)
#define GL_CHECK_REVEALED(field)        GL_GET(field, GL_REVEALED_BIT) >> GL_REVEALED_SHIFT

#define GL_GET_FIELD_VALUE(field)       GL_GET(field, GL_FIELD_VALUE_MASK)
#define GL_SET_FIELD_VALUE(field,value) GL_SET(field, (value & GL_FIELD_VALUE_MASK))

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
  guint32 NumOfFieldsToReveal;   // difference of total field number - number of mines
  Gl_FieldValueType** GameBoard; // start address of the 2D array used as gameboard
  Gl_GameConfigType GameConfig;  //includes the user defined game presets
  Gl_GameStatusType GameStatus;
  GRand* MineGenerator;          // random generator used to place the mines
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
static gboolean Gl_EvaluateRevealedField(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates);
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
      if(GL_CHECK_FLAG(this->GameBoard[row][col]) == GL_BIT_SET)
      {
        g_print(" I ");
      }
      else if(GL_CHECK_MINE(this->GameBoard[row][col]) == GL_BIT_SET)
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
      else if(GL_CHECK_REVEALED(this->GameBoard[row][col]) == GL_BIT_CLEAN)
      {
        g_print(" _ ");
      }
      else
      {
        g_print(" %d ",GL_GET_FIELD_VALUE(this->GameBoard[row][col]));
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
  guint32 numOfFields = ((guint32)this->GameConfig.Rows) * ((guint32)this->GameConfig.Columns);
  this->NumOfMines = (guint32)(((gfloat)numOfFields) * (this->GameConfig.Difficulty));
  this->NumOfFieldsToReveal = numOfFields-(this->NumOfMines);
  guint32 row = 0u;
  guint32 col = 0u;

  for(guint32 mineCount = 0u; mineCount < (this->NumOfMines); mineCount++)
  {
    gboolean mineValid = FALSE;

    do
    {
      // generate random coordinates (with limitation)
      row = g_rand_int_range(this->MineGenerator ,0u, (guint32)(this->GameConfig.Rows));
      col = g_rand_int_range(this->MineGenerator ,0u, (guint32)(this->GameConfig.Columns));

      // check if the coordinates are valid an if there is no mine placed
      if(((row >=0) && (row < (this->GameConfig.Rows)))
      &&((col >=0) && (col < (this->GameConfig.Columns)))
      &&(GL_CHECK_MINE(this->GameBoard[row][col]) != GL_BIT_SET))
      {
        GL_PLACE_MINE(this->GameBoard[row][col]);
        mineValid = TRUE;
        g_print("mine: %d, %d.\n",row, col);
      }
    }while(mineValid == FALSE);
    mineValid = FALSE;
  }
  g_print("Number of mines: %d.\n",this->NumOfMines);
}

static void Gl_CalculateFieldValue(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates)
{
  //TODO: implement
}

static gboolean Gl_EvaluateRevealedField(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates)
{
  gboolean couldBeRevealed = (gboolean)TRUE;

  guint16 row = FieldCoordinates.Row;
  guint16 col = FieldCoordinates.Column;

  if(GL_CHECK_MINE(this->GameBoard[row][col]) == GL_BIT_SET)
  {
    this->GameStatus = GL_LOST;
  }
  else if(GL_CHECK_REVEALED(this->GameBoard[row][col]) == GL_BIT_CLEAN)
  {
    Gl_CalculateFieldValue(this,FieldCoordinates);
    this->NumOfFieldsToReveal--;
    GL_PLACE_REVEALED(this->GameBoard[row][col]);
    Gl_CheckVictory(this);
  }
  else
  {
    couldBeRevealed = FALSE;
    g_print("Field was already revealed or is marked with a flag.\n");
  }

  return couldBeRevealed;
}

static void Gl_CheckVictory(Gl_GameLogicType* this)
{
  // user wins only if he/she has uncovered every safe field and has marked every mine with a flag
  if((this->NumOfFieldsToReveal == 0) && (this->NumOfFlags == this->NumOfMines))
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

      // Allocate Game Board and init fields with default values
      gameLogic->GameBoard = (Gl_FieldValueType**)g_malloc((gameLogic->GameConfig.Rows)*sizeof(Gl_FieldValueType*));

      for(guint32 row = 0; row < (guint32)gameLogic->GameConfig.Rows; row++)
      {
        gameLogic->GameBoard[row] = (Gl_FieldValueType*)g_malloc((gameLogic->GameConfig.Columns)*(sizeof(Gl_FieldValueType)));
        memset(gameLogic->GameBoard[row], (guint8)0u, (gameLogic->GameConfig.Columns)*(sizeof(Gl_FieldValueType)));
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

void Gl_DeallocateGameLogic(Gl_GameLogicType* this)
{
  // TODO: implement destructor!
}


Gl_RevealingResultType Gl_RevealField(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates)
{
  Gl_RevealingResultType opState = GL_REVEALING_FAILED;

  if((this == NULL)
  ||((FieldCoordinates.Row < 0) || (FieldCoordinates.Row >= this->GameConfig.Rows))
  ||((FieldCoordinates.Column < 0) || (FieldCoordinates.Column >= this->GameConfig.Columns)))

  {
    g_print("Gl_RevealField invalid function parameter(s)!\n");
  }
  else
  {
    if(this->GameStatus != GL_RUNNING)
    {
      g_print("No game is running at the moment!\n");
    }
    else
    {
      gboolean revSucceeded = Gl_EvaluateRevealedField(this, FieldCoordinates);
      if(revSucceeded == FALSE)
      {
        opState = GL_CANT_BE_REVEALED;
      }
      else
      {
        opState = GL_REVEALING_SUCCEEDED;
      }
    }
  }
  return opState;
}

Gl_FlagToggleResultType Gl_ToggleFlag(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates)
{
  Gl_FlagToggleResultType opState = GL_TOGGLE_FAILED;

  if((this == NULL)
  ||((FieldCoordinates.Row < 0) || (FieldCoordinates.Row >= this->GameConfig.Rows))
  ||((FieldCoordinates.Column < 0) || (FieldCoordinates.Column >= this->GameConfig.Columns)))
  {
    g_print("Gl_ToggleFlag invalid function parameter(s)!\n");
  }
  else
  {
    guint16 row = FieldCoordinates.Row;
    guint16 col = FieldCoordinates.Column;

    // flag will be toggled only if it the field is still not revealed
    if(GL_CHECK_REVEALED(this->GameBoard[row][col]) == GL_BIT_SET)
    {
      opState = GL_CANT_BE_TOGGLED;
    }
    else
    {
      switch(GL_CHECK_FLAG(this->GameBoard[row][col]))
      {
        case GL_BIT_SET:
        {
          GL_REMOVE_FLAG(this->GameBoard[row][col]);
          this->NumOfFlags--;
          opState = GL_TOGGLE_SUCCEEDED;
          break;
        }
        case GL_BIT_CLEAN:
        {
          GL_PLACE_FLAG(this->GameBoard[row][col]);
          this->NumOfFlags++;
          opState = GL_TOGGLE_SUCCEEDED;
          break;
        }
        default:
        {
          // does nothing if flag value is invalid
          g_print("Stored flag value invalid! Flag can't be toggled.\n");
          break;
        }
      }
      Gl_CheckVictory(this);
    }
  }
  return opState;
}

Gl_GetFieldValResultType Gl_GetFieldValue(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates, Gl_FieldValueType* fieldValue)
{
  Gl_GetFieldValResultType opState = GL_OPERATION_FAILED;

  if((this == NULL)
  ||((FieldCoordinates.Row < 0) || (FieldCoordinates.Row >= this->GameConfig.Rows))
  ||((FieldCoordinates.Column < 0) || (FieldCoordinates.Column >= this->GameConfig.Columns)))

  {
    g_print("Gl_GetFieldValue invalid function parameter(s)!\n");
  }
  else
  {
    guint16 row = FieldCoordinates.Row;
    guint16 col = FieldCoordinates.Column;
    opState = GL_OPERATION_SUCCEEDED;

    if(this->GameStatus != GL_RUNNING)
    {
      *fieldValue = this->GameBoard[row][col];
    }
    else if(GL_CHECK_REVEALED(this->GameBoard[row][col]) == GL_BIT_SET)
    {
      *fieldValue = this->GameBoard[row][col];
    }
    else
    {
      opState = GL_OPERATION_NOT_ALLOWED;
      *fieldValue = (guint8)0xFFu;
    }
  }
  return opState;
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
