#ifndef KIFF_WINDOW_HEADER
#define KIFF_WINDOW_HEADER

#include <glib-object.h>

#include <glib.h>
#include <glib/gprintf.h>

#include <gtk/gtk.h>

#define KIFF_TYPE_WINDOW                  (kiff_window_get_type ())
#define KIFF_WINDOW(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), KIFF_TYPE_WINDOW, KiffWindow))
#define KIFF_IS_WINDOW(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), KIFF_TYPE_WINDOW))
#define KIFF_WINDOW_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), KIFF_TYPE_WINDOW, KiffWindowClass))
#define KIFF_IS_WINDOW_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), KIFF_TYPE_WINDOW))
#define KIFF_WINDOW_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), KIFF_TYPE_WINDOW, KiffWindowClass))

typedef struct _KiffWindow        KiffWindow;
typedef struct _KiffWindowClass   KiffWindowClass;
typedef struct _KiffWindowPrivate KiffWindowPrivate;

struct _KiffWindow
{
  GObject parent_instance;

  KiffWindowPrivate *priv;
};

struct _KiffWindowClass
{
  GObjectClass parent_class;
};

#ifdef __cplusplus
extern "C" {
#endif
  
  GType kiff_window_get_type (void);

  KiffWindow *kiff_window_new (const gchar *title, guint width, guint height);
  
  KiffWindow *kiff_window_popup_new (const gchar *title, guint width, guint height);

  void kiff_window_show (KiffWindow *self);
  
  void kiff_window_start_app (KiffWindow *self, GtkApplication *app);

#ifdef __cplusplus
}
#endif
  
#endif
