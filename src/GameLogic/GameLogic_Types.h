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

#define GL_FIELD_VALUE_MINE              G_MININT8
#define GL_FIELD_VALUE_UNKOWN            G_MAXINT8

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

typedef gint8 Gl_FieldValueType;

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
