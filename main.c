/*!
 * @file main.c
 * @author JustTheBek
 *
 * @brief Main file of the OpenMineSweeper game.
 * @details
 * This file is only used to define app entry and exit points, the functionalities
 * are implemented in the linked component libraries according to the architecture.
 *
 * Created on: June 24, 2023
 *
 * @ingroup main
 * @{
 */

/*
 **********************************************************************
 * INCLUDES
 **********************************************************************
 */

#include <glib.h>
#include "Gui.h"

/*
 **********************************************************************
 * DEFINES
 **********************************************************************
 */

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

/*
 **********************************************************************
 * FUNCTION IMPLEMENTATIONS
 **********************************************************************
 */

int main (int argc, char **argv)
{
  gint guiExitStatus = 0;

  // some test print
  g_print("Hello here is OpenMineSweeper!\n");
  Gui_MineSweeperAppType* myApp = Gui_NewMineSweeperApp(argc, argv);

  guiExitStatus = Gui_GetMineSweeperExitStatus(myApp);

  if(myApp != NULL) // avoids double free call
  {
    Gui_CloseMineSweeperApp(myApp); // deallocate memory
    myApp = NULL;  // set ptr null, to make former allocated memory unreachable
  }

  return guiExitStatus;
}

/*! @} */
