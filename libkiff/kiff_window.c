#include <libkiff/kiff_window.h>

struct _KiffWindowPrivate {
  GtkWidget *window;
  GtkWindowType window_type;
  
  GtkApplication *application;
  gboolean is_application;

  GString *title;

  guint width;
  guint height;
};

enum {
  PROP_0,

  PROP_WINDOW_TYPE,
  PROP_WINDOW_TITLE,
  PROP_WINDOW_WIDTH,
  PROP_WINDOW_HEIGHT,

  N_PROPERTIES
};

G_DEFINE_TYPE_WITH_PRIVATE (KiffWindow, kiff_window, G_TYPE_OBJECT)

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

static GObject *
kiff_window_constructor (GType                  gtype,
			 guint                  n_properties,
			 GObjectConstructParam *properties)
{
  GObject *obj = G_OBJECT_CLASS (kiff_window_parent_class)->constructor (gtype, n_properties, properties);
  KiffWindow *self = KIFF_WINDOW (obj);
    
  self->priv->window = gtk_window_new (self->priv->window_type);  
  gtk_window_set_title (GTK_WINDOW (self->priv->window), self->priv->title->str);  
  gtk_window_set_default_size (GTK_WINDOW (self->priv->window),
			       self->priv->width,
			       self->priv->height);

  return obj;
}

static void
kiff_window_dispose (GObject *gobject)
{
  KiffWindow *self = KIFF_WINDOW (gobject);
  
  g_clear_object (&self->priv->application);
  
  G_OBJECT_CLASS (kiff_window_parent_class)->dispose (gobject);
}

static void
kiff_window_finalize (GObject *gobject)
{
  KiffWindow *self = KIFF_WINDOW (gobject);

  if (!self->priv->is_application)
    {
      gtk_widget_destroy (self->priv->window);
    }

  g_string_free (self->priv->title, TRUE);

  G_OBJECT_CLASS (kiff_window_parent_class)->finalize (gobject);
}

static void
kiff_window_set_property (GObject      *object,
                          guint         property_id,
                          const GValue *value,
                          GParamSpec   *pspec)
{
  KiffWindow *self = KIFF_WINDOW (object);

  switch (property_id)
    {
    case PROP_WINDOW_TYPE:
      self->priv->window_type = g_value_get_enum (value);
      break;
      
    case PROP_WINDOW_TITLE:  
      g_string_assign (self->priv->title, g_value_get_string (value));
      break;

    case PROP_WINDOW_WIDTH:
      self->priv->width = g_value_get_uint (value);
      break;

    case PROP_WINDOW_HEIGHT:
      self->priv->height = g_value_get_uint (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
kiff_window_get_property (GObject    *object,
                          guint       property_id,
                          GValue     *value,
                          GParamSpec *pspec)
{
  KiffWindow *self = KIFF_WINDOW (object);

  switch (property_id)
    {
    case PROP_WINDOW_TYPE:
      g_value_set_enum (value, self->priv->window_type);
      break;
      
    case PROP_WINDOW_TITLE:
      g_value_set_string (value, self->priv->title->str);
      break;

    case PROP_WINDOW_WIDTH:
      g_value_set_uint (value, self->priv->width);
      break;

    case PROP_WINDOW_HEIGHT:
      g_value_set_uint (value, self->priv->height);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
kiff_window_class_init (KiffWindowClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->constructor = kiff_window_constructor;
  gobject_class->dispose = kiff_window_dispose;
  gobject_class->finalize = kiff_window_finalize;
  gobject_class->set_property = kiff_window_set_property;
  gobject_class->get_property = kiff_window_get_property;

  obj_properties[PROP_WINDOW_TYPE] =
    g_param_spec_enum ("window-type",
		       "Window's type",
		       "Get the window's type",
		       GTK_TYPE_WINDOW_TYPE,
		       GTK_WINDOW_TOPLEVEL,
		       G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

  obj_properties[PROP_WINDOW_TITLE] =
    g_param_spec_string ("window-title",
			 "Window's name",
			 "Get the window's name",
			 "KiffWindow",
			 G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);
			 
  obj_properties[PROP_WINDOW_WIDTH] =
    g_param_spec_uint("window-width",
		      "Window's width",
		      "Get the window's width",
		      1,
		      65535,
		      200,
		      G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);
  
  obj_properties[PROP_WINDOW_HEIGHT] = 
    g_param_spec_uint("window-height",
		      "Window's height",
		      "Get the window's height",
		      1,
		      65535,
		      200,
		      G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

  g_object_class_install_properties (gobject_class,
                                     N_PROPERTIES,
                                     obj_properties);
}

static void
kiff_window_init (KiffWindow *self)
{
  self->priv = kiff_window_get_instance_private (self);

  self->priv->application = NULL;
  self->priv->is_application = FALSE;
  self->priv->title = g_string_new (NULL);
}

KiffWindow *
kiff_window_new (const gchar *title, guint width, guint height)
{
  return g_object_new (KIFF_TYPE_WINDOW,
		       "window-type", GTK_WINDOW_TOPLEVEL,
		       "window-title", title,
		       "window-width", width,
		       "window-height", height,
		       NULL);
}

KiffWindow *
kiff_window_popup_new (const gchar *title, guint width, guint height)
{
  return g_object_new (KIFF_TYPE_WINDOW,
		       "window-type", GTK_WINDOW_POPUP,
		       "window-title", title,
		       "window-width", width,
		       "window-height", height,
		       NULL);
}

void kiff_window_show (KiffWindow *self)
{
  gtk_widget_show (self->priv->window);
}

void
kiff_window_start_app (KiffWindow *self, GtkApplication *app)
{
  self->priv->application = app;
  self->priv->is_application = TRUE;
  
  gtk_window_set_application (GTK_WINDOW (self->priv->window), app);
  gtk_widget_show_all (self->priv->window);
}
