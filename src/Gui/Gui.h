/*!
 * @file Gui.h
 * @author JustTheBek
 *
 * @brief One line description of file
 * @details
 * An optional detailed description of file
 *
 * @ingroup Gui
 * @{
 */

#ifndef SRC_GUI_GUI_H_
#define SRC_GUI_GUI_H_

/*
 **********************************************************************
 * INCLUDES
 **********************************************************************
 */

#include <glib.h>

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

typedef struct Gui_MineSweeperAppType Gui_MineSweeperAppType; /* Incomplete type used to data encapsulation*/

/*
 **********************************************************************
 * PUBLIC FUNCTION PROTOTYPES
 **********************************************************************
 */

extern Gui_MineSweeperAppType* Gui_NewMineSweeperApp (int argc, char **argv); // constructor

extern void Gui_CloseMineSweeperApp (Gui_MineSweeperAppType* this); // destructor

extern gint Gui_GetMineSweeperExitStatus(Gui_MineSweeperAppType* this);

#endif /* SRC_GUI_GUI_H_ */

/*! @} */
