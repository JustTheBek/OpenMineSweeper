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
 * DEFINES
 **********************************************************************
 */

/*
 **********************************************************************
 * GLOBAL MACROS
 **********************************************************************
 */

/*
 **********************************************************************
 * GLOBAL DATA TYPES/STRUCTS/ENUMS
 **********************************************************************
 */

/* Incomplete type used to data encapsulation*/
typedef struct Gui_MineSweeperAppType Gui_MineSweeperAppType;

/*
 **********************************************************************
 * GLOBAL CONSTANTS
 **********************************************************************
 */

/*
 **********************************************************************
 * GLOBAL VARIABLES
 **********************************************************************
 */

/*
 **********************************************************************
 * EXTERNALS
 **********************************************************************
 */

extern Gui_MineSweeperAppType* Gui_NewMineSweeperApp (int argc, char **argv); // constructor

extern void Gui_CloseMineSweeperApp (Gui_MineSweeperAppType* this); // destructor

extern gint Gui_GetMineSweeperExitStatus(Gui_MineSweeperAppType* this);

/*
 **********************************************************************
 * GLOBAL FUNCTION PROTOTYPES
 **********************************************************************
 */

#endif /* SRC_GUI_GUI_H_ */

/*! @} */
