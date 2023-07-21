/*!
 * @file GameLogic_Types.h
 * @author JustTheBek
 *
 * @brief One line description of file
 * @details
 * An optional detailed description of file
 *
 * @ingroup GameLogic_Types
 * @{
 */

#ifndef SRC_GAMELOGIC_GAMELOGIC_TYPES_H_
#define SRC_GAMELOGIC_GAMELOGIC_TYPES_H_

/*
 **********************************************************************
 * INCLUDES
 **********************************************************************
 */

#include <gtk/gtk.h>

/*
 **********************************************************************
 * PUBLIC DEFINES
 **********************************************************************
 */

// difficulty represents the amount of mines in percentage
#define GL_DIFFICULTY_EASY             (gfloat)0.10
#define GL_DIFFICULTY_MODERATE         (gfloat)0.20
#define GL_DIFFICULTY_HARD             (gfloat)0.30

/*
 **********************************************************************
 * PUBLIC MACROS
 **********************************************************************
 */

/*
 **********************************************************************
 * PUBLIC DATA TYPES/STRUCTS/ENUMS
 **********************************************************************
 */

/*
 * The field value is the main data type of the mine sweeper logic.
 * It represents a single field on the game board and stores every
 * information about it which is needed by a game logic instance
 * to evaluate the result of a step applied on the chosen field.
 *
 * The interpretation of the bits of a field value is the following:
 * MSB --[x][r][f][m][v3][v2][v1][v0] -- LSB
 * [x] - unused bit
 * [r] - revealed bit: field was revealed (1) / is still unknown(0)
 * [f] - flag bit: field is marked with a flag (1) / or not (0)
 * [m] - mine bit: field holdas a mine (1) / holds no mine (1)
 * [v3-0] - field value: number of mines next to the field (max 8)
 */
typedef guint8 Gl_FieldValueType;

typedef struct
{
  guint16 Row;
  guint16 Column;
}Gl_FieldCoordinateType;

typedef enum
{
  GL_RUNNING = 0,
  GL_LOST,
  GL_VICTORY,
}Gl_GameStatusType;

typedef enum
{
  GL_OPERATION_NOT_SUPPORTED = 0, // operation is not allowed to execute in the current game state
  GL_OPERATION_FAILED,            // an error happened during the function call (invalid input)
  GL_OPERATION_SUCCEEDED,         // operation was executed successfully
}Gl_OperationResultType;

typedef struct
{
  guint16 Rows;
  guint16 Columns;
  gfloat Difficulty;
}Gl_GameConfigType;

/*
 **********************************************************************
 * CLASS DEFINITION
 **********************************************************************
 */

typedef struct Gl_GameLogicType Gl_GameLogicType; /* Incomplete type used to data encapsulation*/

/*
 **********************************************************************
 * PUBLIC FUNCTION PROTOTYPES
 **********************************************************************
 */

#endif /* SRC_GAMELOGIC_GAMELOGIC_TYPES_H_ */

/*! @} */
