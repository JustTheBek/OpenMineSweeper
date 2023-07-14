/*!
 * @file GameManager.h
 * @author JustTheBek
 *
 * @brief Implementation of the GameManager class.
 * @details
 * An optional detailed description of file
 *
 * @ingroup GameManager
 * @{
 */

#ifndef SRC_GAMEMANAGER_GAMEMANAGER_H_
#define SRC_GAMEMANAGER_GAMEMANAGER_H_

/*
 **********************************************************************
 * INCLUDES
 **********************************************************************
 */

#include "GameManager_Types.h"

/*
 **********************************************************************
 * PUBLIC DEFINES
 **********************************************************************
 */

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

extern Gm_GameManagerType* Gm_NewGameManager(void);

extern void Gm_DestroyGameManager(Gm_GameManagerType* this);

extern void Gm_RevealField(Gm_GameManagerType* this);

extern void Gm_ToggleFlag(Gm_GameManagerType* this);

extern void Gm_RestartGame(Gm_GameManagerType* this);

extern void Gm_NewGame(Gm_GameManagerType* this);

extern void Gm_LoadGame(Gm_GameManagerType* this);

extern void Gm_SaveGame(Gm_GameManagerType* this);

extern void Gm_InformationRequest(Gm_GameManagerType* this);

#endif /* SRC_GAMEMANAGER_GAMEMANAGER_H_ */

/*! @} */
