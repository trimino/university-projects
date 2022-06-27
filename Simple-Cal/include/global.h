#include <gtk/gtk.h>
#include <stdlib.h>
#include <iostream>
#define __STDC_FORMAT_MACROS


#ifndef _MY__GLOBAL__H
#define _MY__GLOBAL__H

using namespace std;

/**************************************************************
 * GUI window stuff
 **************************************************************/

typedef struct
{
  GtkWidget *window1; //visualization window

  GtkWidget *label_result;  // the label for the output

  GtkWidget *button_1;  //the 1 button
  GtkWidget *button_2;  //the 2 button
  GtkWidget *button_3;  //the 3 button
  GtkWidget *button_4;  //the 4 button
  GtkWidget *button_5;  //the 5 button
  GtkWidget *button_6;  //the 6 button
  GtkWidget *button_7;  //the 7 button
  GtkWidget *button_8;  //the 8 button
  GtkWidget *button_9;  //the 9 button
  GtkWidget *button_0;  //the 10 button
  
  GtkWidget *button_add;  //the + button
  GtkWidget *button_sub;  //the - button
  GtkWidget *button_mul;  //the * button
  GtkWidget *button_div;  //the / button
  GtkWidget *button_eql;  //the = button

  GtkWidget *button_exit;  //the exit button

} Gui_Window_AppWidgets;

extern Gui_Window_AppWidgets *gui_app;

extern int operand;
extern int last_function;
extern int clear_f;

#endif
