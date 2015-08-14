#include <libkiff/kiff_window.h>

static KiffWindow *mainWindow;

static void activate (GtkApplication* app, gpointer user_data)
{
     mainWindow = g_object_new (KIFF_TYPE_WINDOW, NULL);
     kiff_window_start_app (mainWindow, app);
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
