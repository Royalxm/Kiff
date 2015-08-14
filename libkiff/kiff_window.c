#include <libkiff/kiff_window.h>

struct _KiffWindowPrivate {     
     GString *title;
     
     guint width;
     guint height;
};

G_DEFINE_TYPE_WITH_PRIVATE (KiffWindow, kiff_window, G_TYPE_OBJECT)

static GObject *
kiff_window_constructor (GType                  gtype,
			 guint                  n_properties,
			 GObjectConstructParam *properties)
{
     GObject *obj;

     obj = G_OBJECT_CLASS (kiff_window_parent_class)->constructor (gtype, n_properties, properties);

     return obj;
}

static void
kiff_window_class_init (KiffWindowClass *klass)
{
     GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

     gobject_class->constructor = kiff_window_constructor;
}

static void
kiff_window_init (KiffWindow *self)
{
     self->priv = kiff_window_get_instance_private(self);

     self->priv->width = 800;
     self->priv->height = 600;
}

void kiff_window_start_app (KiffWindow *self, GtkApplication *app)
{
     GtkWidget *window;
     
     window = gtk_application_window_new (app);
     gtk_window_set_title (GTK_WINDOW (window), "Window");
     gtk_window_set_default_size (GTK_WINDOW (window), self->priv->width, self->priv->height);
     gtk_widget_show_all (window);
}
