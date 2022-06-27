#include "global.h"
#include "string.h"

//********************************************************************
// to connect widgets with code
//********************************************************************
void ObtainGuiWidgets(GtkBuilder *p_builder)
{
  #define GuiappGET(xx) gui_app->xx=GTK_WIDGET(gtk_builder_get_object(p_builder,#xx))
  GuiappGET(window1);
  GuiappGET(label_result);
  GuiappGET(button_1);
  GuiappGET(button_2);
  GuiappGET(button_3);
  GuiappGET(button_4);
  GuiappGET(button_5);
  GuiappGET(button_6);
  GuiappGET(button_7);
  GuiappGET(button_8);
  GuiappGET(button_9);
  GuiappGET(button_0);
  GuiappGET(button_add);
  GuiappGET(button_sub);
  GuiappGET(button_mul);
  GuiappGET(button_div);
  GuiappGET(button_eql);
  GuiappGET(button_exit);
}

//********************************************************************
// GUI handlers
//********************************************************************

extern "C" void button_0_clicked(GtkWidget *p_wdgt, gpointer p_data){

  const char* a_cc_value;
  char c_cc_value[20];
  int a_d_value = 0;
  if(!clear_f){
	a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
	a_d_value = atof(a_cc_value);
	a_d_value = a_d_value * 10;
  }
  
  a_d_value = a_d_value + 0;
  clear_f = false;
  sprintf(c_cc_value,"%d",a_d_value);
  gtk_label_set_text(GTK_LABEL(gui_app->label_result),c_cc_value);

}

extern "C" void button_1_clicked(GtkWidget *p_wdgt, gpointer p_data )
{
  const char *a_cc_value;
  char c_cc_value[20];
  int a_d_value=0;
  if(!clear_f)
    {
       a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
       a_d_value = atoi(a_cc_value);
       a_d_value*=10;
    }
  a_d_value+=1;     // $$$ The Variable Part
  clear_f=false;

  sprintf(c_cc_value,"%d",a_d_value);

  gtk_label_set_text(GTK_LABEL(gui_app->label_result),c_cc_value);
}


extern "C" void button_2_clicked(GtkWidget *p_wdgt, gpointer p_data )
{
  const char *a_cc_value;
  char c_cc_value[20];
  int a_d_value=0;
  if(!clear_f)
    {
       a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
       a_d_value = atoi(a_cc_value);
       a_d_value*=10;
    }
  a_d_value+=2;     // $$$ The Variable Part
  clear_f=false;

  sprintf(c_cc_value,"%d",a_d_value);

  gtk_label_set_text(GTK_LABEL(gui_app->label_result),c_cc_value);
}


extern "C" void button_3_clicked(GtkWidget *p_wdgt, gpointer p_data){
  const char* a_cc_value;
  char c_cc_value[20];
  int a_d_value = 0;
  if(!clear_f){
       
	a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
	a_d_value = atoi(a_cc_value);
	a_d_value = a_d_value * 10;

  }
  
  a_d_value = a_d_value + 3; //$$$ The Variable Part
  clear_f = false;
  sprintf(c_cc_value,"%d",a_d_value);
  gtk_label_set_text(GTK_LABEL(gui_app->label_result), c_cc_value);
}


extern "C" void button_4_clicked(GtkWidget *p_wdgt, gpointer p_data){
  const char* a_cc_value;
  char c_cc_value[20];
  int a_d_value = 0;
  if(!clear_f){
       
	a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
	a_d_value = atoi(a_cc_value);
	a_d_value = a_d_value * 10;

  }
  
  a_d_value = a_d_value + 4; //$$$ The Variable Part
  clear_f = false;
  sprintf(c_cc_value,"%d",a_d_value);
  gtk_label_set_text(GTK_LABEL(gui_app->label_result), c_cc_value);

}


extern "C" void button_5_clicked(GtkWidget *p_wdgt, gpointer p_data){
  const char* a_cc_value;
  char c_cc_value[20];
  int a_d_value = 0;
  if(!clear_f){
       
	a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
	a_d_value = atoi(a_cc_value);
	a_d_value = a_d_value * 10;

  }
  
  a_d_value = a_d_value + 5; //$$$ The Variable Part
  clear_f = false;
  sprintf(c_cc_value,"%d",a_d_value);
  gtk_label_set_text(GTK_LABEL(gui_app->label_result), c_cc_value);
}


extern "C" void button_6_clicked(GtkWidget *p_wdgt, gpointer p_data){
  const char* a_cc_value;
  char c_cc_value[20];
  int a_d_value = 0;
  if(!clear_f){
       
	a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
	a_d_value = atoi(a_cc_value);
	a_d_value = a_d_value * 10;

  }
  
  a_d_value = a_d_value + 6;	//$$$ The Variable Part
  clear_f = false;
  sprintf(c_cc_value,"%d",a_d_value);
  gtk_label_set_text(GTK_LABEL(gui_app->label_result), c_cc_value);
}



extern "C" void button_7_clicked(GtkWidget *p_wdgt, gpointer p_data){
  const char* a_cc_value;
  char c_cc_value[20];
  int a_d_value = 0;
  if(!clear_f){
       
	a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
	a_d_value = atoi(a_cc_value);
	a_d_value = a_d_value * 10;

  }
  
  a_d_value = a_d_value + 7;	//$$$ The Variable Part
  clear_f = false;
  sprintf(c_cc_value,"%d",a_d_value);
  gtk_label_set_text(GTK_LABEL(gui_app->label_result), c_cc_value);
}


extern "C" void button_8_clicked(GtkWidget *p_wdgt, gpointer p_data){
  const char* a_cc_value;
  char c_cc_value[20];
  int a_d_value = 0;
  if(!clear_f){
       
	a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
	a_d_value = atoi(a_cc_value);
	a_d_value = a_d_value * 10;

  }
  
  a_d_value = a_d_value + 8;	//$$$ The Variable Part
  clear_f = false;
  sprintf(c_cc_value,"%d",a_d_value);
  gtk_label_set_text(GTK_LABEL(gui_app->label_result), c_cc_value);
}


extern "C" void button_9_clicked(GtkWidget *p_wdgt, gpointer p_data){
  const char* a_cc_value;
  char c_cc_value[20];
  int a_d_value = 0;
  if(!clear_f){
       
	a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
	a_d_value = atoi(a_cc_value);
	a_d_value = a_d_value * 10;

  }
  
  a_d_value = a_d_value + 9;	//$$$ The Variable Part
  clear_f = false;
  sprintf(c_cc_value,"%d",a_d_value);
  gtk_label_set_text(GTK_LABEL(gui_app->label_result), c_cc_value);
}



extern "C" void button_add_clicked(GtkWidget *p_wdgt, gpointer p_data )
{
  const char *a_cc_value;
  char c_cc_value[20];
  double a_d_value;
  a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
  a_d_value = atoi(a_cc_value);

  switch (last_function)
    {
       case 1:
	 operand-=a_d_value;
	 break;
       case 2:
	 operand*=a_d_value;
	 break;
       case 3:
	 operand/=a_d_value;
	 break;
       case 0:
	 operand+=a_d_value;
	 break;
       default:
	 break;
    }

  last_function=0;   // $$$ The Variable Part
  clear_f = true;

  sprintf(c_cc_value,"%d",operand);
  gtk_label_set_text(GTK_LABEL(gui_app->label_result),c_cc_value);
}


extern "C" void button_sub_clicked(GtkWidget *p_wdt, gpointer data){

  const char* sub_label_value;
  char sub[20];
  double value;
  sub_label_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
  value = atoi(sub_label_value);
  
   switch (last_function)
   {
      case 1:
	 operand-=value;
	 break;
      case 2:
	 operand*=value;
	 break;
      case 3:
	 operand/=value;
	 break;
      case 0:
	 operand+=value;
	 break;
      default:
	 break;
   }

   last_function = 1;
   clear_f = true;
   sprintf(sub,"%d",operand);
   gtk_label_set_text(GTK_LABEL(gui_app->label_result), sub);
}


extern "C" void button_mul_clicked(GtkWidget* p_wdgt, gpointer){

  const char* mul_label_value;
  char mul[20];
  double value;
  mul_label_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
  value = atoi(mul_label_value);

   switch (last_function)
   {
      case 1:
	 operand-=value;
	 break;
      case 2:
	 operand*=value;
	 break;
      case 3:
	 operand/=value;
	 break;
      case 0:
	 operand+=value;
	 break;
      default:
	 break;
   }

   last_function = 2;
   clear_f = true;
   sprintf(mul,"%d",operand);
   gtk_label_set_text(GTK_LABEL(gui_app->label_result), mul);
}


extern "C" void button_div_clicked(GtkWidget* p_wdgt, gpointer){

  const char* div_label_value;
  char div[20];
  double value;
  div_label_value = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
  value = atoi(div_label_value);

   switch (last_function)
   {
      case 1:
	 operand-=value;
	 break;
      case 2:
	 operand*=value;
	 break;
      case 3:
	 operand/=value;
	 break;
      case 0:
	 operand+=value;
	 break;
      default:
	 break;
   }

   last_function = 3;
   clear_f = true;
   sprintf(div,"%d",operand);
   gtk_label_set_text(GTK_LABEL(gui_app->label_result), div);
}


extern "C" void button_eql_clicked(GtkWidget* p_wdgt, gpointer data){

  char equals[20];
  const char* val;
  double value; 
  val = gtk_label_get_text(GTK_LABEL(gui_app->label_result));
  value = atoi(val);

   switch (last_function)
   {
      case 1:
	 operand-=value;
	 break;
      case 2:
	 operand*=value;
	 break;
      case 3:
	 operand/=value;
	 break;
      case 0:
	 operand+=value;
	 break;
      default:
	 break;
   }

   last_function = 4;
   clear_f = true;
   sprintf(equals,"%d",operand);
   gtk_label_set_text(GTK_LABEL(gui_app->label_result), equals);
}


extern "C" void button_exit_clicked(GtkWidget *p_wdgt, gpointer p_data )
{
  gtk_main_quit();

}

//********************************************************************
//********************************************************************
//
//   Main loop
//
//********************************************************************
//********************************************************************

int main(int argc, char **argv)
{

  GtkBuilder *builder;
  GError *err = NULL;

  // Now we initialize GTK+
  gtk_init(&argc, &argv);

  //create gtk_instance for visualization
  gui_app = g_slice_new(Gui_Window_AppWidgets);

  //builder
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "cal.glade", &err);

  //error handling
  if(err)
    {
      g_error(err->message);
      g_error_free(err);
      g_slice_free(Gui_Window_AppWidgets, gui_app);
      exit(-1);
    }

  // Obtain widgets that we need
  ObtainGuiWidgets(builder);

  // Connect signals
  gtk_builder_connect_signals(builder, gui_app);

  // Destroy builder now that we created the infrastructure
  g_object_unref(G_OBJECT(builder));

  //display the gui
  gtk_widget_show(GTK_WIDGET(gui_app->window1));

  //the main loop
  gtk_main();

  //destroy gui if it still exists
  if(gui_app)
    g_slice_free(Gui_Window_AppWidgets, gui_app);

  return 0;
}
