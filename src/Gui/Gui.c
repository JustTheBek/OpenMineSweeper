/*!
 * @file Gui.c
 * @author JustTheBek
  *
 * @brief One line description of file
 * @details
 * An optional detailed description of file
 *
 * @ingroup Gui
 * @{
 */

/*
 **********************************************************************
 * INCLUDES
 **********************************************************************
 */

#include "Gui.h"
#include "GameLogic.h"
#include <gtk/gtk.h>

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

/* complete data type definition, allows encapsulation of private data */
struct Gui_MineSweeperAppType
{
  gint ExitStatus;
  gint AppVersion; // TODO: set via CMake
  GtkApplication *GtkApp;
  GtkWidget* ReporterBar;
  //TODO GameManager;
};

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

/* static function declarations */
static void Gui_CallbackRestartButton (GtkWidget *widget, gpointer   data);
static void Gui_CallbackNewGameButton (GtkWidget *widget, gpointer   data);
static void Gui_CallbackLoadGameButton (GtkWidget *widget, gpointer   data);
static void Gui_CallbackSaveGameButton (GtkWidget *widget, gpointer   data);
static void Gui_CallbackInfoButton (GtkWidget *widget, gpointer   data);
static void Gui_Activate (GtkApplication *app, gpointer user_data);

// TODO: temp function used to replace game board in early dev phase
static void draw_function (GtkDrawingArea *area,
               cairo_t        *cr,
               int             width,
               int             height,
               gpointer        data)
{
  GdkRGBA color = {.red = 255,
                   .green = 255,
                   .blue = 255,
                   .alpha = 1};

  cairo_rectangle (cr, 0, 0, 500,500);

  //gtk_widget_get_color (GTK_WIDGET (area), &color);
  gdk_cairo_set_source_rgba (cr, &color);

  cairo_fill (cr);
}

/* static function definitions, TODO: null  check of this */
static void Gui_CallbackRestartButton (GtkWidget *widget, gpointer user_data)
{
  //extract this ptr from user_data, necessary since Gtk callback params can't be chosen freely
  Gui_MineSweeperAppType* this = (Gui_MineSweeperAppType*) user_data;

  g_print("Restart klicked.\n");

  const char text[] = {"Restart Game"};
  GtkEntryBuffer* textBuffer = gtk_entry_buffer_new(&text[0], (sizeof(text)/sizeof(text[0])));
  gtk_text_set_buffer((GtkText*)this->ReporterBar, textBuffer);
  // TODO: destroy textBuffer
}

static void Gui_CallbackNewGameButton (GtkWidget *widget, gpointer user_data)
{
  //extract this ptr from user_data, necessary since Gtk callback params can't be chosen freely
  Gui_MineSweeperAppType* this = (Gui_MineSweeperAppType*) user_data;

  g_print("New Game klicked.\n");

  const char text[] = {"New Game"};
  GtkEntryBuffer* textBuffer = gtk_entry_buffer_new(&text[0], (sizeof(text)/sizeof(text[0])));
  gtk_text_set_buffer((GtkText*)this->ReporterBar, textBuffer);
  // TODO: destroy textBuffer
}

static void Gui_CallbackLoadGameButton (GtkWidget *widget, gpointer user_data)
{
  //extract this ptr from user_data, necessary since Gtk callback params can't be chosen freely
  Gui_MineSweeperAppType* this = (Gui_MineSweeperAppType*) user_data;

  g_print("Load Game klicked.\n");

  const char text[] = {"Load Game"};
  GtkEntryBuffer* textBuffer = gtk_entry_buffer_new(&text[0], (sizeof(text)/sizeof(text[0])));
  gtk_text_set_buffer((GtkText*)this->ReporterBar, textBuffer);
  // TODO: destroy textBuffer
}

static void Gui_CallbackSaveGameButton (GtkWidget *widget, gpointer user_data)
{
  //extract this ptr from user_data, necessary since Gtk callback params can't be chosen freely
  Gui_MineSweeperAppType* this = (Gui_MineSweeperAppType*) user_data;

  g_print("Save Game klicked.\n");

  const char text[] = {"Save Game"};
  GtkEntryBuffer* textBuffer = gtk_entry_buffer_new(&text[0], (sizeof(text)/sizeof(text[0])));
  gtk_text_set_buffer((GtkText*)this->ReporterBar, textBuffer);
  // TODO: destroy textBuffer
}

static void Gui_CallbackInfoButton (GtkWidget *widget, gpointer user_data)
{
  //extract this ptr from user_data, necessary since Gtk callback params can't be chosen freely
  Gui_MineSweeperAppType* this = (Gui_MineSweeperAppType*) user_data;

  g_print("Info klicked.\n");

  const char text[] = {"Info"};
  GtkEntryBuffer* textBuffer = gtk_entry_buffer_new(&text[0], (sizeof(text)/sizeof(text[0])));
  gtk_text_set_buffer((GtkText*)this->ReporterBar, textBuffer);
  // TODO: destroy textBuffer
}

static void Gui_Activate (GtkApplication *app, gpointer user_data)
{
  //extract this ptr from user_data, necessary since Gtk callback params can't be chosen freely
  Gui_MineSweeperAppType* this = (Gui_MineSweeperAppType*) user_data;

  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *reporter;
  GtkWidget *grid;
  GtkWidget *drawingArea;

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "OpenMineSweeper");
  gtk_window_set_default_size(GTK_WINDOW (window), 500, 520);

  // Construct Grid of Buttons and Reporter Grid, pack the Container in the Window
  grid = gtk_grid_new ();
  gtk_window_set_child (GTK_WINDOW (window), grid);

  // Create and place Buttons
  button = gtk_button_new();
  g_signal_connect (button, "clicked", G_CALLBACK (Gui_CallbackRestartButton), (gpointer*)this);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);
  GtkWidget *image = gtk_image_new_from_file ("./cliparts/restart.png");
  gtk_button_set_child (GTK_BUTTON (button), image);

  button = gtk_button_new();
  g_signal_connect (button, "clicked", G_CALLBACK (Gui_CallbackNewGameButton), (gpointer*)this);
  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);
  image = gtk_image_new_from_file ("./cliparts/plus.png");
  gtk_button_set_child (GTK_BUTTON (button), image);

  button = gtk_button_new();
  g_signal_connect (button, "clicked", G_CALLBACK (Gui_CallbackLoadGameButton), (gpointer*)this);
  gtk_grid_attach (GTK_GRID (grid), button, 2, 0, 1, 1);
  image = gtk_image_new_from_file ("./cliparts/load.png");
  gtk_button_set_child (GTK_BUTTON (button), image);

  button = gtk_button_new();
  g_signal_connect (button, "clicked", G_CALLBACK (Gui_CallbackSaveGameButton), (gpointer*)this);
  gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 1, 1);
  image = gtk_image_new_from_file ("./cliparts/save.png");
  gtk_button_set_child (GTK_BUTTON (button), image);

  button = gtk_button_new();
  g_signal_connect (button, "clicked", G_CALLBACK (Gui_CallbackInfoButton), (gpointer*)this);
  gtk_grid_attach (GTK_GRID (grid), button, 4, 0, 1, 1);
  image = gtk_image_new_from_file ("./cliparts/info.png");
  gtk_button_set_child (GTK_BUTTON (button), image);

  // TODO: Temporary drawing area used to experiment with grid and widget positioning
  drawingArea = gtk_drawing_area_new ();
  gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (drawingArea), 500);
  gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (drawingArea), 500);
  gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (drawingArea), draw_function, NULL, NULL);
  gtk_grid_attach (GTK_GRID (grid), drawingArea,0, 1, 10, 1);

  // Create and Place Report Bar
  const char text[] = {""}; //init with empty string
  GtkEntryBuffer* textBuffer = gtk_entry_buffer_new(&text[0], (sizeof(text)/sizeof(text[0])));
  reporter = gtk_text_new_with_buffer(textBuffer);
  this->ReporterBar = reporter;
  gtk_text_set_overwrite_mode((GtkText*)reporter, (gboolean)FALSE); // TODO: disabling overwrite does not work
  gtk_grid_attach (GTK_GRID (grid), reporter, 0, 2, 10, 1);

  // TODO: testing GameLogic, remove if done
  const Gl_GameConfigType gameConfig =
  {
     .Rows    = 5,
     .Columns = 5,
     .Difficulty = GL_DIFFICULTY_MODERATE,
  };

  Gl_GameLogicType* gameLogic = Gl_NewGameLogic(&gameConfig);
  Gl_FieldCoordinateType flag =
  {
      .Row = 0,
      .Column = 3,
  };
  Gl_SetFlag(gameLogic, flag);
  Gl_DevApi_PrintGameBoardToConsole(gameLogic, TRUE);
  // Draw window
  gtk_widget_show (window);

}


Gui_MineSweeperAppType* Gui_NewMineSweeperApp (int argc, char **argv) // constructor
{
  Gui_MineSweeperAppType* mineSweeper = NULL;

  mineSweeper = (Gui_MineSweeperAppType*) g_malloc(sizeof(Gui_MineSweeperAppType));

  if(mineSweeper == NULL) // safety check that allocation was ok
  {
    g_print("Allocation of new mine sweeper application failed!\n");
  }
  else
  {
    mineSweeper->GtkApp = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (mineSweeper->GtkApp, "activate", G_CALLBACK (Gui_Activate), mineSweeper);

    // TODO: add comand line parser which checks the arguments and ads some configs

    // infinite loop will be started here, exits only after closing the app
    mineSweeper->ExitStatus = g_application_run (G_APPLICATION (mineSweeper->GtkApp), argc, argv);
    g_object_unref (mineSweeper->GtkApp);
  }

  return mineSweeper;
}

void Gui_CloseMineSweeperApp (Gui_MineSweeperAppType* this) // destructor
{
  if(this != NULL) // avoids double free call
  {
    g_free(this); // deallocate memory
    this = NULL;  // set ptr null, to make former allocated memory unreachable
  }

  return;
}

gint Gui_GetMineSweeperExitStatus(Gui_MineSweeperAppType* this)
{
  gint exitStatus = -1;

  if(this != NULL) // avoids double free call
  {
    exitStatus = this->ExitStatus;
  }

  return exitStatus;
}


/*! @} */
