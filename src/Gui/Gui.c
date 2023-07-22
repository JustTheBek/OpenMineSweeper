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
#include "GameManager.h"
#include <gtk/gtk.h>

/*
 **********************************************************************
 * PRIVATE DEFINES
 **********************************************************************
 */

/*
 **********************************************************************
 * PRIVATE MACROS
 **********************************************************************
 */

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

// TODO: temp global var used to experiment with cairo surface
cairo_surface_t *dest = NULL; // cairo surface

/* complete data type definition, allows encapsulation of private data */
struct Gui_MineSweeperAppType
{
  gint ExitStatus;                  // return value of the GTK app
  gint AppVersion;                  // TODO: set via CMake
  GtkApplication *GtkApp;           // the GUI application
  GtkWidget* ReporterBar;           // small text output bar
  GtkWidget* DrawingArea;           // area where the game board will be drawn
  Gm_GameManagerType* GameManager;  // GUI can control the game via this manager
};

/*
 **********************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************
 */

static void Gui_CallbackLeftKlick (GtkGestureClick *self, gint n_press, gdouble x, gdouble y, gpointer *user_data);
static void Gui_CallbackRightKlick (GtkGestureClick *self, gint n_press, gdouble x, gdouble y, gpointer *user_data);
static void Gui_CallbackRestartButton (GtkWidget *widget, gpointer   data);
static void Gui_CallbackNewGameButton (GtkWidget *widget, gpointer   data);
static void Gui_CallbackLoadGameButton (GtkWidget *widget, gpointer   data);
static void Gui_CallbackSaveGameButton (GtkWidget *widget, gpointer   data);
static void Gui_CallbackInfoButton (GtkWidget *widget, gpointer   data);
static void Gui_Activate (GtkApplication *app, gpointer user_data);

/*
 **********************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS
 **********************************************************************
 */

// TODO: temp function used to replace game board in early dev phase
static void draw_function (GtkDrawingArea *area,
               cairo_t        *cr,
               int             width,
               int             height,
               gpointer        data)
{
  cairo_set_source_surface (cr, dest, 0, 0);
  cairo_paint (cr);
}

static void resize_cb (GtkWidget *widget, int width, int height, gpointer  data)
{
  if (dest)
  {
    cairo_surface_destroy (dest);
    dest = NULL;
  }

  if (gtk_native_get_surface (gtk_widget_get_native (widget)))
  {
    dest = gdk_surface_create_similar_surface (gtk_native_get_surface (gtk_widget_get_native (widget)),
                                                  CAIRO_CONTENT_COLOR,
                                                  gtk_widget_get_width (widget),
                                                  gtk_widget_get_height (widget));
  }
}

// Interface based on: https://docs.gtk.org/gtk4/signal.GestureClick.pressed.html
static void Gui_CallbackLeftKlick (GtkGestureClick *self, gint n_press, gdouble x, gdouble y, gpointer *user_data)
{
  //extract this ptr from user_data, necessary since Gtk callback params can't be chosen freely
  Gui_MineSweeperAppType* this = (Gui_MineSweeperAppType*) user_data;

  Gm_KlickCoordinateType klickCoordinates = {x,y};

  Gm_ToggleFlag(this->GameManager, klickCoordinates);

  //##########################################################################################
  // TODO: temp calback testing block
  static guint16 count = 0;
  cairo_t *cr = cairo_create (dest);
  GdkRGBA color = {.red = 0.125+(0.5*count),
                   .green = 0.255,
                   .blue = 0.83,
                   .alpha = 100};

  if(count < 3)
  {
    cairo_rectangle (cr, 0, 0, 500,500);
    gdk_cairo_set_source_rgba (cr, &color);
    cairo_fill (cr);
  }
  else
  {
    cairo_surface_t *src = cairo_image_surface_create_from_png("./cliparts/minimine.png");
    cairo_set_source_surface (cr, src, 100, 100);
    cairo_paint (cr);
  }
  cairo_destroy (cr);
  gtk_widget_queue_draw (this->DrawingArea);
  count++;
  // end of calback testing block
  //##########################################################################################
}

// Interface based on: https://docs.gtk.org/gtk4/signal.GestureClick.pressed.html
static void Gui_CallbackRightKlick (GtkGestureClick *self, gint n_press, gdouble x, gdouble y, gpointer *user_data)
{
  //extract this ptr from user_data, necessary since Gtk callback params can't be chosen freely
  Gui_MineSweeperAppType* this = (Gui_MineSweeperAppType*) user_data;

  Gm_KlickCoordinateType klickCoordinates = {x,y};

  Gm_ToggleFlag(this->GameManager, klickCoordinates);

  //##########################################################################################
  // TODO: temp calback testing block
  cairo_t *cr = cairo_create (dest);
  cairo_surface_t *src = cairo_image_surface_create_from_png("./cliparts/miniflag.png");
  cairo_set_source_surface (cr, src, 300, 40);
  cairo_paint (cr);

  cairo_destroy (cr);
  gtk_widget_queue_draw (this->DrawingArea);
  // end of calback testing block
  //##########################################################################################
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
  g_signal_connect_after (drawingArea, "resize", G_CALLBACK (resize_cb), NULL);
  this->DrawingArea = drawingArea;

  // Defining left button click
  GtkGesture *leftClick = gtk_gesture_click_new ();
  gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (leftClick), GDK_BUTTON_PRIMARY);
  gtk_widget_add_controller (drawingArea, GTK_EVENT_CONTROLLER (leftClick));
  g_signal_connect (leftClick, "pressed", G_CALLBACK (Gui_CallbackLeftKlick), this);


  // Defining right button click
  GtkGesture *rightClick = gtk_gesture_click_new ();
  gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (rightClick), GDK_BUTTON_SECONDARY);
  gtk_widget_add_controller (drawingArea, GTK_EVENT_CONTROLLER (rightClick));
  g_signal_connect (rightClick, "pressed", G_CALLBACK (Gui_CallbackRightKlick), this);

  // Create and Place Report Bar
  const char text[] = {""}; //init with empty string
  GtkEntryBuffer* textBuffer = gtk_entry_buffer_new(&text[0], (sizeof(text)/sizeof(text[0])));
  reporter = gtk_text_new_with_buffer(textBuffer);
  this->ReporterBar = reporter;
  gtk_text_set_overwrite_mode((GtkText*)reporter, (gboolean)FALSE); // TODO: disabling overwrite does not work
  gtk_grid_attach (GTK_GRID (grid), reporter, 0, 2, 10, 1);


  //cr = cairo_create (dest);
  //cairo_surface_t *src = cairo_image_surface_create_from_png("./cliparts/mine.png");
  //cairo_set_source_surface (cr, src, 0, 0);
  //cairo_destroy (cr);



  // Draw window
  gtk_widget_show (window);

}

/*
 **********************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS
 **********************************************************************
 */

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

    mineSweeper->GameManager = Gm_NewGameManager(); // TODO: do it maybe in the activate func??

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
