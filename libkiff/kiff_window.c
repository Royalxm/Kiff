#include <libkiff/kiff_window.h>

struct _KiffWindowPrivate {
  GtkWidget *gtk_window;

  gboolean is_application;

  GString *title;

  guint width;
  guint height;
};

enum {
  PROP_0,

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
  KiffWindow *self;

  self = G_OBJECT_CLASS (kiff_window_parent_class)->constructor (gtype, n_properties, properties);
    
  gtk_window_set_default_size (GTK_WINDOW (self->priv->gtk_window),
			       self->priv->width,
			       self->priv->height);

  return self;
}

static void
kiff_window_dispose (GObject *gobject)
{
  KiffWindow *self = KIFF_WINDOW (gobject);
  
  G_OBJECT_CLASS (kiff_window_parent_class)->dispose (gobject);
}

static void
kiff_window_finalize (GObject *gobject)
{
  KiffWindow *self = KIFF_WINDOW (gobject);

  if (!self->priv->is_application)
    {
      gtk_widget_destroy (self->priv->gtk_window);
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
    case PROP_WINDOW_TITLE:  
      g_string_assign (self->priv->title, g_value_get_string (value));
      gtk_window_set_title (GTK_WINDOW (self->priv->gtk_window),
			    self->priv->title->str);
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

  obj_properties[PROP_WINDOW_TITLE] =
    g_param_spec_string ("window-title",
			 "Window's name",
			 "Set/Get the window's name",
			 "KiffWindow",
			 G_PARAM_CONSTRUCT | G_PARAM_READWRITE);
			 
  obj_properties[PROP_WINDOW_WIDTH] =
    g_param_spec_uint("window-width",
		      "Window's width",
		      "Set/Get the window's width",
		      1,
		      65535,
		      200,
		      G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);
  
  obj_properties[PROP_WINDOW_HEIGHT] = 
    g_param_spec_uint("window-height",
		      "Window's height",
		      "Set/Get the window's height",
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

  self->priv->gtk_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  self->priv->is_application = FALSE;
  self->priv->title = g_string_new (NULL);
}

KiffWindow *
kiff_window_new (void)
{
  KiffWindow *kiffWindow = g_object_new (KIFF_TYPE_WINDOW, NULL);

  return kiffWindow;
}

KiffWindow *
kiff_window_new_with_params (const gchar *title, guint width, guint height)
{
  KiffWindow *kiffWindow = g_object_new (KIFF_TYPE_WINDOW,
					 "window-title", title,
					 "window-width", width,
					 "window-height", height,
					 NULL);

  return kiffWindow;
}

void
kiff_window_start_app (KiffWindow *self, GtkApplication *app)
{
  self->priv->is_application = TRUE;
  
  gtk_window_set_application (GTK_WINDOW (self->priv->gtk_window), app);
  gtk_widget_show_all (self->priv->gtk_window);
}
