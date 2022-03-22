#include <gtk/gtk.h>

/* ---- RESOURCES UTILIZED ----
 *
 * https://docs.gtk.org/gtk4/getting_started.html#building-applications
 * 
 * https://docs.gtk.org/gtk4/class.Label.html
 *
 * https://docs.gtk.org/gtk4/class.Label.html
 *
 * https://docs.gtk.org/Pango/pango_markup.html
 * 
 * */

#define WIDTH 500
#define HEIGHT 500

#define MESSAGE "Hello There!"
#define MESSAGE_LABEL "<span font='30'>Hello There!</span>"

#define RESPONSE_TITLE "General Kenobi..."
#define RESPONSE_LABEL "<span font='30'>you are a bold one!</span>"

/* Responds to the "Hello There" sentence with
 * "General Kenobi, you are a bold one!".
 */
void response_window(GtkWidget *unused, gpointer app_pointer) {
	GtkApplication *current_app = (GtkApplication *) app_pointer;

	GtkWidget *new_window = gtk_application_window_new(current_app);
	gtk_window_set_title(GTK_WINDOW(new_window), RESPONSE_TITLE);
	gtk_window_set_default_size(GTK_WINDOW(new_window), WIDTH, HEIGHT);

	GtkWidget *response_label = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(response_label), RESPONSE_LABEL);

	gtk_window_set_child(GTK_WINDOW(new_window), response_label);

	gtk_window_present(GTK_WINDOW(new_window));
	return;
}

/* Creates a main window with a button that displays "Hello There".
 */
void main_window(GtkApplication *current_application, 
				 gpointer unused) {
	GtkWidget *new_window = gtk_application_window_new(current_application);
	gtk_window_set_title(GTK_WINDOW(new_window), MESSAGE);
	gtk_window_set_default_size(GTK_WINDOW(new_window), WIDTH, HEIGHT);

	GtkWidget *message_label = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(message_label), MESSAGE_LABEL);

	GtkWidget *button_new_window = gtk_button_new();
	g_signal_connect(button_new_window, "clicked", G_CALLBACK(response_window), 
					 current_application);

	gtk_window_set_child(GTK_WINDOW(new_window), button_new_window);
	gtk_button_set_child(GTK_BUTTON(button_new_window), message_label);

	gtk_window_present(GTK_WINDOW(new_window));
	return;
}

int main(int argc, char **argv) {
	int status = 0;
	GtkApplication *running_app = NULL;

	running_app = gtk_application_new("com.simeon.hello-there", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(running_app, "activate", G_CALLBACK(main_window), NULL);

	status = g_application_run(G_APPLICATION(running_app), argc, argv);
	g_object_unref(running_app);
	return status;
}

