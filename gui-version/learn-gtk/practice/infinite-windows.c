#include <gtk/gtk.h>

/* ---- RESOURCES UTILIZED ----
 *
 * https://docs.gtk.org/gtk4/getting_started.html#building-applications
 * 
 * https://wiki.gnome.org/HowDoI/GtkApplication
 * 
 * https://www.cc.gatech.edu/data_files/public/doc/gtk/tutorial/gtk_tut-3.html
 * 
 * https://stackoverflow.com/questions/22384333/passing-additional
 * -arguments-to-gtk-function
 *
 * https://stackoverflow.com/questions/1037414/when-the-deleteevent-is-called-by-a
 * -gtk-window-how-can-i-prevent-the-window-fr
 *
 * https://docs.gtk.org/gtk4/class.Window.html#:~:text=A%20GtkWindow%20is%20a
 * %20toplevel,%2C%20close%20it%2C%E2%80%A6).
 *
 * https://docs.gtk.org/gobject/func.signal_connect_swapped.html
 * 
 * */

#define WIDTH 500
#define HEIGHT 500

#define MESSAGE "Click me to open another window.\n"

gboolean close_request(GtkWindow *window_to_close, gpointer user_data) {
	g_print("A window has been closed.\n");
	gtk_window_close(window_to_close);
	return true;
}

/* Creates a new window with a button that opens another window
 * when clicked.
 */
void another_window(GtkApplication *current_application, 
					gpointer auxillary) {

	GtkWidget *new_window = gtk_application_window_new(current_application);
	gtk_window_set_title(GTK_WINDOW(new_window), 
						 "My First GTK Application");
	gtk_window_set_default_size(GTK_WINDOW(new_window), WIDTH, HEIGHT);

	GtkWidget *button_new_window = gtk_button_new_with_label(MESSAGE);
	gtk_window_set_child(GTK_WINDOW(new_window), button_new_window);

	g_signal_connect_swapped(button_new_window, "clicked", 
							 G_CALLBACK(another_window), current_application);

	gtk_window_present(GTK_WINDOW(new_window));
	return;
}

/* Initializes the application with a window and a button that opens
 * a new window when clicked.
 */
void activate(GtkApplication *application, gpointer user_input) {
	another_window(application, NULL);
	return;
}

int main(int argc, char **argv) {
	int status = 0;
	GtkApplication *running_app = NULL;

	running_app = gtk_application_new("com.simeon.firstapp", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(running_app, "activate", G_CALLBACK(activate), NULL);

	status = g_application_run(G_APPLICATION(running_app), argc, argv);
	g_object_unref(running_app);
	return status;
}

