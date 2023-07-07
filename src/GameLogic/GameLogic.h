/*!
 * @file GameLogic.h
 * @author JustTheBek
 *
 * @brief One line description of file
 * @details
 * An optional detailed description of file
 *
 * @ingroup GameLogic
 * @{
 */

#ifndef SRC_GAMELOGIC_GAMELOGIC_H_
#define SRC_GAMELOGIC_GAMELOGIC_H_

/*
 **********************************************************************
 * INCLUDES
 **********************************************************************
 */

#include "GameLogic_Types.h"

/*
 **********************************************************************
 * PUBLIC DEFINES
 **********************************************************************
 */

#define DEVELOPMENT_MODE //TODO. defines this by cmake

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
 **********************************************************************
 * CLASS DEFINITION
 **********************************************************************
 */

/*
 **********************************************************************
 * PUBLIC FUNCTION PROTOTYPES
 **********************************************************************
 */

extern Gl_GameLogicType* Gl_NewGameLogic(const Gl_GameConfigType* gameConfig); // constructor

extern void Gl_DeallocateGameLogic(Gl_GameLogicType* this); // destructor

extern Gl_FieldValueType Gl_RevealField(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates);

extern void Gl_SetFlag(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates);

extern void Gl_ResetFlag(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates);

extern guint32 Gl_GetNumberOfMines(Gl_GameLogicType* this);

extern Gl_GameStatusType Gl_GetGameStatus(Gl_GameLogicType* this);

#ifdef DEVELOPMENT_MODE
extern void Gl_DevApi_PrintGameBoardToConsole(Gl_GameLogicType* this, gboolean showMines);
#endif

#endif /* SRC_GAMELOGIC_GAMELOGIC_H_ */

/*! @} */
