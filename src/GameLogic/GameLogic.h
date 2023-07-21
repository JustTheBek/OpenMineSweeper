/*!
 * @file GameLogic.h
 * @author JustTheBek
 *
 * @brief Public interface declaration of GameLogic class.
 * @details
 * Instancing an object of this class generates a new game board
 * based on the settings forwarded to the constructor. The game
 * can be controlled via the public functions of the class. After
 * finishing the game the logic has to be destroyed by the destructor.
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

/*
 * Constructor of the GameLogic class. Allocates a new game logic and unit (including an empty gameboard) and
 * generates randomly distributed mines based on the configured game difficulty. In case of any initialization
 * failure the function returns a null pointer.
 */
extern Gl_GameLogicType* Gl_NewGameLogic(const Gl_GameConfigType* gameConfig); // constructor

/*
 * TODO: add interface description
 */
extern void Gl_DeallocateGameLogic(Gl_GameLogicType* this); // destructor

/*
 *  Function is used to reveal a field on the game board. The function returns only the result of the operation
 *  (according to Gl_RevealingResultType) but not the field value itself, that can be read via the get field method of the class.
 */
extern Gl_OperationResultType Gl_RevealField(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates);

/*
 * Toggles flag if the field was not revealed yet and if the forwarded parameters are valid.
 * Returns result of operation according to the definition of Gl_FlagToggleResultType.
 */
extern Gl_OperationResultType Gl_ToggleFlag(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates);

/*
 * If game is running: Returns the value of the field marked by the forwarded coordinates, but only it
 * the field is already revealed.
 * If game is lost/won: Returns the value of the field marked by the forwarded coordinates, also if the field
 * was unknown before.
 */
extern Gl_OperationResultType Gl_GetFieldValue(Gl_GameLogicType* this, Gl_FieldCoordinateType FieldCoordinates, Gl_FieldValueType* fieldValue);

/*
 * Returns the number of the mines created by the constructor during instancing the object. If a null pointer
 * is forwarded the function returns 0 since there are always some mines even in the easiest game mode.
 */
extern guint32 Gl_GetNumberOfMines(Gl_GameLogicType* this);

/*
 * Returns the game status according to the definition of the Gl_GameStatusType. If a null pointer is
 * forwarded the function returns null to avoid further failures by finsihing the game and prints an error msg.
 */
extern Gl_GameStatusType Gl_GetGameStatus(Gl_GameLogicType* this);


#ifdef DEVELOPMENT_MODE

/*
 * This method helps during the development by printing the actual game board to the console.
 * Shall be used only for development purposes.
 */
extern void Gl_DevApi_PrintGameBoardToConsole(Gl_GameLogicType* this, gboolean showMines);

#endif

#endif /* SRC_GAMELOGIC_GAMELOGIC_H_ */

/*! @} */
