#include <stdlib.h>         /* Para "rand" */
#include <allegro.h>
using namespace std;
int main()
{
 
  #define ANCHOPANTALLA 320
  #define ALTOPANTALLA 200
  #define MAXLADODIANA 50
 
  int 
      posXraton = 160,
      posYraton = 100,
      posXdiana,
      posYdiana,
      ladoDiana,
      puntos = 0,
      dibujarDiana = 1;
 
  allegro_init();              /* Inicializamos Allegro */
  install_keyboard();
  install_timer();
  install_mouse();
 
                               /* Intentamos entrar a modo grafico */
  if (set_gfx_mode(GFX_SAFE, ANCHOPANTALLA, ALTOPANTALLA, 0, 0) != 0) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message(
          "Incapaz de entrar a modo grafico\n%s\n",
          allegro_error);
      return 1;
  }
 
  /* ----------------------- Si todo ha ido bien: empezamos */
 
  srand(time(0));
  show_mouse(screen);
 
 
            /* Parte repetitiva: */
  do {
      rest(50); /*Pausa de 50 ms */
 
      if (dibujarDiana) {
          /*Calculo nueva posicion de la diana */
          posXdiana = rand() % (ANCHOPANTALLA - ladoDiana);
          posYdiana = rand() % (ALTOPANTALLA - ladoDiana);
          ladoDiana = (rand() % MAXLADODIANA) + 2;
 
          /* Oculto raton y redibujo */
          scare_mouse();
          clear_bitmap(screen);
          rectfill(screen,posXdiana, posYdiana, posXdiana+ladoDiana, posYdiana+ladoDiana,palette_color[10]);
          textprintf(screen, font, 4,4, palette_color[14],"Puntos: %d", puntos); 
 
          /*Vuelvo a mostrar ratony marco como dibujado */    
          unscare_mouse();
          dibujarDiana = 0;
      }
 
 
    // Si se pulsa el bot?n, compruebo si es dentro del recuadro.
    // Si es as?, aumento puntos. En cualquier caso,dibujo nueva diana
 
    if (mouse_b & 1) {
 
        if ((mouse_x >= posXdiana) && (mouse_x <= posXdiana+ladoDiana) &&
               (mouse_y >= posYdiana) && (mouse_y <= posYdiana+ladoDiana)) {
            puntos ++;
        }
 
        dibujarDiana = 1;              
    }
 
  }
  while ( !keypressed() );  /* Repetimos hasta pulsar tecla */
 
 
  return 0;
 
}
 
                     /* Termino con la "macro" que me pide Allegro */
END_OF_MAIN();
