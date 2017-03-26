#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

int main()
{
	al_init();
	al_init_font_addon();
	al_init_primitives_addon();

	ALLEGRO_DISPLAY* display = al_create_display(800, 600);
	ALLEGRO_FONT* font = al_create_builtin_font();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	ALLEGRO_COLOR electricBlue = al_map_rgb(44, 177, 255);
	al_draw_triangle(10.0f, 15.0f, 15.0f, 15.0f, 10.0f, 25.0f, electricBlue, 3.0f);
	al_flip_display();
	al_rest(5.0);
	return 0;
}