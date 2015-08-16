#include <libkiff/kiff_window.h>

static KiffWindow *kiff_window;

static void activate (GtkApplication* app, gpointer user_data)
{  
  kiff_window = kiff_window_new ("Kiff", 800, 600);
  kiff_window_start_app (kiff_window, app);
}


int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (kiff_window);
  
  return status;
}
