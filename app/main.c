#include <libkiff/kiff_window.h>

static KiffWindow *mainWindow;

static void activate (GtkApplication* app, gpointer user_data)
{
  mainWindow = kiff_window_new ();
  kiff_window_start_app (mainWindow, app);

  GValue val_title = G_VALUE_INIT;
  GValue val_width = G_VALUE_INIT;
  GValue val_height = G_VALUE_INIT;

  g_value_init (&val_title, G_TYPE_STRING);
  g_value_init (&val_width, G_TYPE_UINT);
  g_value_init (&val_height, G_TYPE_UINT);
  
  g_value_set_string (&val_title, "Kiff");
  
  g_object_set_property (G_OBJECT (mainWindow), "window-title", &val_title);
  g_object_get_property (G_OBJECT (mainWindow), "window-width", &val_width);
  g_object_get_property (G_OBJECT (mainWindow), "window-height", &val_height);

  g_printf("%s %u %u\n",
	   g_value_get_string(&val_title),
	   g_value_get_uint(&val_width),
	   g_value_get_uint(&val_height));
}


int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  g_object_unref (mainWindow);
  
  return status;
}
