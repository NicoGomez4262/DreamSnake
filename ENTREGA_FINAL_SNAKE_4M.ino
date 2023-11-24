/* DreamSnake.ino ***************************************************************************************************************************/
/*                                                                            				                                                      */
/*   ┌────┐ ┌────┐                      				                     DreamSnake                                                             */
/*   └┐  ┌┘ └┐╔══╧═╗                                                                        				                                        */
/*    │  │   │╚╗  ╔╝                        DEVELOPED BY: Est. FELIPE USECHE, NICOLAS GOMEZ, JUAN CONRADO                             			*/
/*    │  │   │ ║  ║            jfelipe.usechec@javeriana.edu.co, conradom.juan@javeriana.edu.co,nandres-gomez@javeriana.edu.co              */
/*    │  │   │ ║  ║                                                        	                                                  							*/
/*    │╔═╧══╗│ ║  ║                                       Bogota, D.C., nov; 23th, 2023.                                      							*/
/*    │╚╗  ╔╝┘ ║  ║                                                       			                                                   					*/
/*    └┐║  ╚╗ ╔╝  ║                               Copyright (C) Electronics Engineering Program       			                        				*/
/*     └╚╗  ╚═╝  ╔╝                                          School of Engineering                                                     			*/
/*      └╚╗     ╔╝                                      Pontificia Universidad Javeriana                                               			*/
/*        ╚═════╝                                       Bogota - Colombia - South America                                                  	*/
/*                                                                            				                                                      */
/********************************************************************************************************************************************/
#include <stdlib.h>
#include <MD_MAX72xx.h>  // Necesario para la funcion rand()
#include <LiquidCrystal_I2C.h>
#include <time.h>
#include <SPI.h>
/****DEFINICION NOTAS CANCION INSPIRADA EN PACMAN PARA LA FSM**/
#define QT 0 /* QUIET */
#define E6 1319
#define G6 1568
#define A6 1760
#define AS6 1865
#define B6 1976
#define C7 2093
#define D7 2349
#define E7 2637
#define F7 2794
#define G7 3136
#define A7 3520
#define DS6 1245
#define FS6 1480
#define FS7 2960
#define DS7 2489
//*DEFINICION PINES LCD 20X4 ******//
#define op1 52
#define op2 53
#define ANCHURA_LCD 20
#define ALTURA_LCD 4
#define DIRECCION_LCD 0x27
LiquidCrystal_I2C pantalla(DIRECCION_LCD, ANCHURA_LCD, ALTURA_LCD);
//*DEFINICION PINES MATRIZ 8X8 ******//
#define HARDWARE_TYPE MD_MAX72XX::DR0CR0RR1_HW
#define NUM_OF_MATRIX 4
#define CLK_PIN 4
#define DATA_PIN 2
#define CS_PIN 3
#define MAX_SNAKE_LENGTH 14
#define PLAYERES 2
//DEFINICION PULSADORES COMO PULSADORES TIPO PULL UP RESISTANCE*****//
#define Pin 12
#define DOWN_BUTTON 8
#define RIGHT_BUTTON 11
#define UP_BUTTON 10
#define LEFT_BUTTON 9
//*DEFINICION PULSADORES PLAYER 2
#define UP_P2 5
#define DOWN_P2 7
#define RIGHT_P2 6
#define LEFT_P2 13
//DEFINICION PULSADORES COMO PULSADORES TIPO PULL UP RESISTANCE*****//
#define grilla_FILAS 16               /* Maximum number of FILAS in map of grilla */
#define grilla_COLS 16              /* Maximum number of cols in map of grilla */
#define CON_FILAS (grilla_FILAS)       /* Maximum number of FILAS in console */
#define CON_COLS (2 * grilla_COLS + 1) /* Maximum number of cols in console */
#define SCALE 1                        /* Factor scale to advance one step forward inside grilla */
//*******DEFINICION GRILLA DE LA MATRIZ ******//
static char my_grilla[grilla_FILAS][grilla_COLS] = {

  /*        00 01 02 03 04 05 06 07 08 09 10  11 12 13 14 15 16 17 18 19 20 21 22*/
  /* 00 */ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  /* 01 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 02 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 03 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 04 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 05 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 07 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 08 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
           { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 01 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 02 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 03 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 04 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 05 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 07 */ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 1 },
  /* 08 */ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },

};
//*********ESTRUCTURAS DE LA SERPIENTE ,lA FRUTA Y LOS ESTADOS   ******//
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, NUM_OF_MATRIX);

typedef struct {
  int length = 0;
  int puntaje = 0;
  char lastmove[2];
  char direction[2];
  char tail[MAX_SNAKE_LENGTH][2];

  char input_up;
  char input_down;
  char input_right;
  char input_left;
  char input = ' ';  // Inicializar con un valor que no sea una dirección válida
  char last_input = ' ';

} SNAKE_T;
SNAKE_T my_snake[PLAYERES];

typedef struct {
  char ubicationF[2];
} FRUIT_T;
FRUIT_T my_fruit;

typedef enum { Screen,
               Music,
               end } STATE_T;
static STATE_T state;

typedef struct {
  unsigned int tone;    /* Tone [cycles per second: cps] */
  unsigned long length; /* Time for reproducing tone [milliseconds] */
} TONE_T;

TONE_T Pacman_Melody[] = {
  { E6, 250 },
  { G6, 250 },
  { B6, 250 },
  { QT, 250 },  // Pausa
  { B6, 250 },
  { G6, 250 },
  { E6, 250 },
  { QT, 250 },  // Pausa
  { E6, 250 },
  { G6, 250 },
  { B6, 250 },
  { QT, 250 },  // Pausa
  { B6, 250 },
  { A6, 250 },
  { G6, 250 },
  { AS6, 250 },
  { A6, 250 },
  { QT, 250 },  // Pausa
  { A6, 250 },
  { AS6, 250 },
  { G6, 250 },
  { A6, 250 },
  { B6, 250 },
  { QT, 250 }  // Pausa
};
TONE_T Pacman_Death[] = {
  { E6, 100 },
  { QT, 50 },
  { DS6, 100 },
  { QT, 50 },
  { E6, 100 },
  { QT, 50 },
  { G6, 100 },
  { QT, 50 },
  { QT, 100 },
  { G7, 100 },
  { QT, 50 },
  { QT, 100 },
  { FS7, 100 },
  { QT, 50 },
  { QT, 100 },
  { F7, 100 },
  { QT, 50 },
  { QT, 100 },
  { DS7, 100 },
  { D7, 100 },
  { QT, 100 },
  { QT, 50 },
  { QT, 100 },
  { C7, 100 },
  { QT, 50 },
  { QT, 100 },
  { E7, 100 },
  { QT, 50 },
  { QT, 100 },
  { C7, 100 },
  { QT, 50 },
  { QT, 100 },
  { G6, 100 },
  { QT, 50 },
  { QT, 100 },
  { G6, 100 },
  { QT, 50 },
  { QT, 100 },
  { E6, 100 },
  { QT, 50 },
  { QT, 100 },
  { A6, 100 },
  { QT, 50 },
  { QT, 100 },
  { QT, 100 },
  { E6, 100 },
  { QT, 50 },
  { QT, 100 },
  { FS6, 100 },
  { G6, 100 },
  { QT, 50 },
  { QT, 100 },
  { E6, 100 },
  { QT, 50 },
  { QT, 100 },
  { QT, 100 },
  { QT, 100 }
};
enum States {
  INIT,
  PLAY,
  FINISH
};
// Variables globales
enum States currentState = PLAY;
unsigned int currentNote = 0;
unsigned long noteStartTime = 0;

unsigned int Melody_Size = sizeof(Pacman_Melody) / sizeof(TONE_T);
double Melody_Pause = 1.3;

//****DEFINICION VARIABLES GLOBALES Y STATICS ******//
int z = 0;
char fruit;
char SnakeHead;
static int current_time;
static int previous_time;
static char buffer_pantalla[CON_FILAS][CON_COLS];
static int currentX;
static int currentY;
static int prevX;
static int prevY;
static int velocidad = 800;
static int opcion = 0;
static int PLAYERS = 0;

//****FUNCIONES DEL JUEGO  ******//
int Dibujar_Grilla(char buffer_pantalla[][CON_COLS], char grilla[][grilla_COLS]);
int MoveSnake(SNAKE_T *snake, char direction, char grilla[][grilla_COLS], FRUIT_T *fruit, STATE_T *state);
int PrintSnake(SNAKE_T *snake, FRUIT_T *fruit, char buffer_pantalla[][CON_COLS], char grilla[][grilla_COLS]);
int UbicarFrutaAleatoria(FRUIT_T *fruit, char buffer_pantalla[][CON_COLS], char grilla[][grilla_COLS]);
void mostrarPuntaje(SNAKE_T *snake);
void dibujarDigito(int digito, int columna);
int PARED_PRELIMINAR(SNAKE_T *snake, char grilla[][grilla_COLS]);
int CheckCollisionBetweenSnakes(SNAKE_T *snake1_ptr, SNAKE_T *snake2_ptr);
void main_game(SNAKE_T *snake, FRUIT_T *fruit_ptr, STATE_T *state);
void MoveTail(SNAKE_T *snake);
int puntajeFinal(SNAKE_T *snake);
void mostrarMenu();
int Final_Juego();
int Hay_Pared();
void buzzer();
void nota(int a, int b);
void reproducirMelodiaMuerte();
void Notasmuerte();
void NotasComida();
void Gameloop(SNAKE_T *snake_ptr, STATE_T *state_ptr);
void loopMusic();

void setup() {
  Serial.begin(9600);
  srand(time(NULL));
  pantalla.init();
  pantalla.backlight();
  pantalla.clear();
  //UbicarFrutaAleatoria(&my_fruit, buffer_pantalla, my_grilla);
  pinMode(Pin, OUTPUT);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(UP_P2, INPUT_PULLUP);
  pinMode(DOWN_P2, INPUT_PULLUP);
  pinMode(RIGHT_P2, INPUT_PULLUP);
  pinMode(LEFT_P2, INPUT_PULLUP);
  mostrarMenu();
  my_fruit.ubicationF[0] = 4;  //rand() % grilla_FILAS;
  my_fruit.ubicationF[1] = 5;  //rand() % grilla_COLS;
  for (int i = 0; i < PLAYERS; i++) {
    my_snake[i].direction[0] = ((rand() % grilla_FILAS) / 2) + 1;
    my_snake[i].direction[1] = ((rand() % grilla_COLS) / 2) + 1;
    my_snake[i].length = 1;
    if (i == 1) {
      my_snake[i].input_up = UP_P2;
      my_snake[i].input_down = DOWN_P2;
      my_snake[i].input_right = RIGHT_P2;
      my_snake[i].input_left = LEFT_P2;
    } else {
      my_snake[i].input_up = UP_BUTTON;
      my_snake[i].input_down = DOWN_BUTTON;
      my_snake[i].input_right = RIGHT_BUTTON;
      my_snake[i].input_left = LEFT_BUTTON;
    }
  }

  mx.begin();
  mx.control(MD_MAX72XX::TEST, true);
  delay(500);
  mx.control(MD_MAX72XX::TEST, false);
  mx.control(MD_MAX72XX::INTENSITY, 5);
}

void loop() {
  Gameloop(my_snake, &state);
}
/*###########################################################################
#
#   prototype: void loop()
#
#   Return:  void
#
#   Purpose: Función principal que invoca el gameloop del juego.
#
#   Plan:
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

void Gameloop(SNAKE_T *snake_ptr, STATE_T *state_ptr) {
  switch (*state_ptr) {
    case Screen:
      if (PLAYERS > 1) {
        main_game(&my_snake[0], &my_fruit, &state);
        main_game(&my_snake[1], &my_fruit, &state);
        fflush(stdout);
      } else {
        main_game(&my_snake[0], &my_fruit, &state);
        fflush(stdout);
      }
      if (*state_ptr != end) {
        *state_ptr = Music;
      }
      break;
    case Music:
      buzzer();
      Serial.println("MUSIC: ");
      *state_ptr = Screen;
      break;
    case end:
      noTone(Pin);
      reproducirMelodiaMuerte();
      Serial.print("END");
      Final_Juego();
      mostrarPuntaje(snake_ptr);
      break;
  }
}
/*###########################################################################
#
#   prototype: void Gameloop(SNAKE_T *snake_ptr, STATE_T *state_ptr)
#
#   Return:  void
#
#   Purpose: Implementa el gameloop del juego y controla la reproducción de
#            la melodía.
#
#   Plan: Utiliza una máquina de estados para controlar el flujo del juego y
#         la reproducción de la música. En el estado 'Screen', ejecuta el bucle
#         principal del juego para cada jugador. En el estado 'Music', activa
#         la función 'buzzer()' para reproducir una melodía. En el estado 'end',
#         detiene el tono, reproduce otra melodía y muestra el puntaje final.
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

void main_game(SNAKE_T *snake_ptr, FRUIT_T *fruit_ptr, STATE_T *state_ptr) {
  static char input = ' ';
  static char last_input = ' ';
  input = snake_ptr->input;
  last_input = snake_ptr->last_input;
  PrintSnake(snake_ptr, fruit_ptr, buffer_pantalla, my_grilla);
  Dibujar_Grilla(buffer_pantalla, my_grilla);
  if (true) {
    if ((digitalRead(snake_ptr->input_up) == 0) || (digitalRead(snake_ptr->input_down) == 0) || (digitalRead(snake_ptr->input_right) == 0) || (digitalRead(snake_ptr->input_left) == 0)) {
      // Obtener la entrada del usuario sin esperar a presionar Enter
      if (digitalRead(snake_ptr->input_up) == 0 && snake_ptr->last_input != 's') {
        snake_ptr->input = 'w';
        snake_ptr->last_input = 'w';
      }
      if (digitalRead(snake_ptr->input_down) == 0 && snake_ptr->last_input != 'w') {
        snake_ptr->input = 's';
        snake_ptr->last_input = 's';
      }
      if (digitalRead(snake_ptr->input_right) == 0 && snake_ptr->last_input != 'a') {
        snake_ptr->input = 'd';
        snake_ptr->last_input = 'd';
      }
      if (digitalRead(snake_ptr->input_left) == 0 && snake_ptr->last_input != 'd') {
        snake_ptr->input = 'a';
        snake_ptr->last_input = 'a';
      }
      // Mover la serpiente en función de la entrada
      MoveSnake(snake_ptr, input, my_grilla, fruit_ptr, state_ptr);
      // Imprimir el laberinto con la serpiente
      PrintSnake(snake_ptr, fruit_ptr, buffer_pantalla, my_grilla);

    } else {
      // Si no hay entrada del usuario, seguir moviendo la serpiente en la dirección actual
      MoveSnake(snake_ptr, input, my_grilla, fruit_ptr, state_ptr);
      // Imprimir el laberinto con la serpiente
      PrintSnake(snake_ptr, fruit_ptr, buffer_pantalla, my_grilla);
    }
    // Agregar una pequeña pausa para que la serpiente no se mueva demasiado rápido
    fflush(stdout);
    // Ajustar la velocidad para que la serpiente no se mueva demasiado rápido
    Serial.print("VELOCIDAD :");
    Serial.println(velocidad);
  }
}

/*###########################################################################
#
#   prototype: int Dibujar_Grilla(char buffer_pantalla[][CON_COLS], char grilla[][grilla_COLS])
#
#   Return:  int
#
#   Purpose: Llena el búfer de pantalla con la representación visual de la grilla
#            y la serpiente.
#
#   Plan: Utiliza la información de la grilla y la posición de la serpiente para
#         actualizar el búfer de pantalla con la representación visual del juego.
#
#   Register of Revisions:
#
#   DATE                               RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/
int Dibujar_Grilla(char buffer_pantalla[][CON_COLS], char grilla[][grilla_COLS]) {
  char i, j;
  /* Part 1: llena la consola con 0's */
  for (i = 0; i < CON_FILAS; i++)
    for (j = 0; j < CON_COLS; j++)
      buffer_pantalla[i][j] = 0;
  /* Part 2: llena la consola con */
  for (i = 0; i < grilla_FILAS; i++) {
    for (j = 0; j < grilla_COLS; j++)
      buffer_pantalla[i][j] = grilla[i][j] ? 1 : 0;
    buffer_pantalla[i][CON_COLS - 1] = '\n';
  }
  return 1;
} /* Dibujar_Grilla */


int MoveSnake(SNAKE_T *snake_ptr, char direction, char grilla[][grilla_COLS], FRUIT_T *fruit_ptr, STATE_T *state_ptr) {
  static char next_x, next_y;
  static unsigned long lastMoveTime = 0;
  unsigned long currentTime = millis();
  unsigned long moveInterval = velocidad;  // Puedes ajustar este valor según la velocidad deseada
  // Mover la serpiente en la dirección especificada


  // Verifica si ha pasado el tiempo suficiente desde el último movimiento
  if (currentTime - lastMoveTime < moveInterval) {
    return 1;  // No ha pasado suficiente tiempo, sal de la función
  }
  lastMoveTime = currentTime;
  switch (direction) {
    case 'w':
      snake_ptr->direction[0]--;  // Mover hacia arriba
      MoveTail(snake_ptr);
      SnakeHead = 1;
      break;
    case 'a':
      snake_ptr->direction[1]--;  // Mover hacia la izquierda
      MoveTail(snake_ptr);
      SnakeHead = 1;
      break;
    case 's':
      snake_ptr->direction[0]++;  // Mover hacia abajo
      MoveTail(snake_ptr);
      SnakeHead = 1;
      break;
    case 'd':
      snake_ptr->direction[1]++;  // Mover hacia la derecha
      MoveTail(snake_ptr);
      SnakeHead = 1;
      break;
  }

  next_x = snake_ptr->direction[0];
  next_y = snake_ptr->direction[1];

  currentX = snake_ptr->direction[0];
  currentY = snake_ptr->direction[1];

  prevX = fruit_ptr->ubicationF[0];
  prevY = fruit_ptr->ubicationF[1];

  if (currentX == fruit_ptr->ubicationF[0] && currentY == fruit_ptr->ubicationF[1]) {
    // La serpiente ha alcanzado la fruta, actualiza la posición de la fruta y haz crecer la serpiente
    UbicarFrutaAleatoria(fruit_ptr, buffer_pantalla, my_grilla);
    NotasComida();
    snake_ptr->length++;   // Incrementa el ancho de la serpiente (crecimiento)
    snake_ptr->puntaje++;  // Incrementa el ancho de la serpiente (crecimiento)
    velocidad -= 20;
  }
  for (int i = snake_ptr->length; i > 0; i--) {
    if ((snake_ptr->direction[0] == snake_ptr->tail[i][0] && snake_ptr->direction[1] == snake_ptr->tail[i][1])) {
      //exit(1);
      *state_ptr = end;
    }
    if ((fruit_ptr->ubicationF[0] == (snake_ptr->direction[0] || snake_ptr->tail[i][0])) || (fruit_ptr->ubicationF[1] == (snake_ptr->direction[1] || snake_ptr->tail[i][1]))) {
      fruit_ptr->ubicationF[0] = rand() % grilla_FILAS;
      fruit_ptr->ubicationF[1] = rand() % grilla_COLS;
    }
  }
  if (PLAYERS > 1) {
    if (my_snake[0].direction[0] == my_snake[1].direction[0] && my_snake[0].direction[1] == my_snake[1].direction[1]) {
      // Colisión con la otra serpiente
      *state_ptr = end;
    }
    if (CheckCollisionBetweenSnakes(&my_snake[0], &my_snake[1])) {
      // Colisión entre serpientes
      *state_ptr = end;
    }
  }
  if (grilla[next_x][next_y]) {
    *state_ptr = end;
  }
  if ((prevX == 0 || prevX >= grilla_FILAS - 1 || prevY == 0 || prevY >= grilla_COLS - 1)) {
    fruit_ptr->ubicationF[0] = rand() % grilla_FILAS;
    fruit_ptr->ubicationF[1] = rand() % grilla_COLS;
  }
}
/*###########################################################################
#
#   prototype: int MoveSnake(SNAKE_T *snake_ptr, char direction, char grilla[][grilla_COLS], 
#                             FRUIT_T *fruit_ptr, STATE_T *state_ptr)
#
#   Return:  int
#
#   Purpose: Mueve la serpiente y gestiona la lógica relacionada con la fruta,
#            colisiones y velocidad del juego.
#
#   Plan: Mueve la serpiente en la dirección especificada. Actualiza la posición
#         de la fruta y el puntaje si la serpiente come la fruta. Verifica
#         colisiones con la pared y la serpiente misma, y ajusta la velocidad.
#
#   Register of Revisions:
#
#   DATE                             RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

void MoveTail(SNAKE_T *snake_ptr) {
  for (int i = snake_ptr->length - 1; i >= 0; i--) {
    snake_ptr->tail[i][0] = snake_ptr->tail[i - 1][0];
    snake_ptr->tail[i][1] = snake_ptr->tail[i - 1][1];
  }
  if (snake_ptr->length >= 0) {
    snake_ptr->tail[0][0] = snake_ptr->direction[0];
    snake_ptr->tail[0][1] = snake_ptr->direction[1];
  }
}
/*###########################################################################
#
#   prototype: void MoveTail(STATE_T *state_ptr)
#
#   Return:  void
#
#   Purpose: Mueve la cola de la serpiente en la matriz LED según la dirección actual.
#
#   Plan: Actualiza la posición de la cola de la serpiente en la matriz LED según
#         la dirección actual. El último segmento de la cola se mueve a la posición
#         del segmento anterior, y así sucesivamente. El primer segmento se mueve
#         a la posición del segmento que le sigue en la dirección actual.
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

int UbicarFrutaAleatoria(FRUIT_T *fruit_ptr, char buffer_pantalla[][CON_COLS], char grilla[][grilla_COLS]) {

  char buffer_pantalla_tmp[CON_FILAS][CON_COLS];

  fruit_ptr->ubicationF[0] = rand() % grilla_FILAS;
  fruit_ptr->ubicationF[1] = rand() % grilla_COLS;

  while (buffer_pantalla_tmp[fruit_ptr->ubicationF[0]][fruit_ptr->ubicationF[1]] != 0 || (fruit_ptr->ubicationF[0] == prevX && fruit_ptr->ubicationF[1] == prevY)) {
    fruit_ptr->ubicationF[0] = rand() % grilla_FILAS;
    fruit_ptr->ubicationF[1] = rand() % grilla_COLS;
  }

  return 1;
}
/*###########################################################################
#
#   prototype: int UbicarFrutaAleatoria(FRUIT_T *fruit_ptr, char buffer_pantalla[][CON_COLS], 
#                                         char grilla[][grilla_COLS])
#
#   Return:  int
#
#   Purpose: Ubica una nueva fruta aleatoria en la grilla del juego.
#
#   Plan: Evita que la fruta aparezca en la posición actual de la serpiente y
#         la ubica aleatoriamente en la grilla.
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

int PrintSnake(SNAKE_T *snake_ptr, FRUIT_T *fruit_ptr, char buffer_pantalla[][CON_COLS], char grilla[][grilla_COLS]) {
  // Parte 1: Copiar el laberinto en un búfer temporal
  char buffer_pantalla_tmp[CON_FILAS][CON_COLS];

  for (int i = 0; i < CON_FILAS; i++)
    for (int j = 0; j < CON_COLS; j++)
      buffer_pantalla_tmp[i][j] = buffer_pantalla[i][j];

  for (int i = 0; i < snake_ptr->length; i++) {
    buffer_pantalla_tmp[snake_ptr->tail[i][0]][SCALE * snake_ptr->tail[i][1]] = 1;
  }
  // Parte 2: Imprimir la cabeza de la serpiente en la nueva posición
  buffer_pantalla_tmp[snake_ptr->direction[0]][SCALE * snake_ptr->direction[1]] = SnakeHead;
  buffer_pantalla_tmp[fruit_ptr->ubicationF[0]][SCALE * fruit_ptr->ubicationF[1]] = 1;

  // Parte 3: Imprimir el laberinto con la serpiente
  mx.clear();
  for (int i = 0; i < CON_FILAS; i++) {
    for (int j = 0; j < CON_COLS; j++) {
      if (buffer_pantalla_tmp[i][j] == 1) {
        mx.setPoint(i, j, 1);
      } else {
        mx.setPoint(i, j, 0);
      }
    }
  }
  fflush(stdout);
  return 1;
}
/*###########################################################################
#
#   prototype: int PrintSnake(SNAKE_T *snake_ptr, FRUIT_T *fruit_ptr, 
#                               char buffer_pantalla[][CON_COLS], char grilla[][grilla_COLS])
#
#   Return:  int
#
#   Purpose: Imprime la serpiente y la fruta en el búfer de pantalla.
#
#   Plan: Utiliza las posiciones de la serpiente y la fruta para actualizar el
#         búfer de pantalla con la representación visual del juego.
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

int PARED_PRELIMINAR(SNAKE_T *snake_ptr, char grilla[][grilla_COLS]) {
  char next_x, next_y;

  next_x = snake_ptr->direction[0];
  next_y = snake_ptr->direction[1];
  return grilla[next_x][next_y] = 1;

} /* PARED_PRELIMINAR */
/*###########################################################################
#
#   prototype: int PARED_PRELIMINAR(SNAKE_T *snake_ptr, char grilla[][grilla_COLS])
#
#   Return:  int
#
#   Purpose: Verifica si hay una pared en la posición dada, antes de establecerla.
#
#   Plan: Similar a 'Hay_Pared', pero verifica primero si la posición está dentro
#         de los límites antes de consultar la grilla, evitando posibles desbordamientos.
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

int Hay_Pared(SNAKE_T *snake_ptr) {
  return (PARED_PRELIMINAR(snake_ptr, my_grilla));
}
/*###########################################################################
#
#   prototype: char Hay_Pared(char x, char y)
#
#   Return:  int
#
#   Purpose: Verifica si hay una pared en la posición dada.
#
#   Plan: Consulta la grilla para determinar si hay una pared en la posición
#         especificada por las coordenadas (x, y).
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

int CheckCollisionBetweenSnakes(SNAKE_T *snake1_ptr, SNAKE_T *snake2_ptr) {
  for (int i = 0; i <= snake1_ptr->length; i++) {
    if (snake2_ptr->direction[0] == snake1_ptr->tail[i][0] && snake2_ptr->direction[1] == snake1_ptr->tail[i][1]) {
      // Colisión de la cabeza de la primera serpiente con el cuerpo de la segunda
      return 1;
    }
  }
  for (int i = 0; i <= snake2_ptr->length; i++) {
    if (snake1_ptr->direction[0] == snake2_ptr->tail[i][0] && snake1_ptr->direction[1] == snake2_ptr->tail[i][1]) {
      // Colisión con la otra serpiente
      return 1;
    }
  }
  return 0;  // No hay colisión entre las serpientes
}


int Final_Juego() {
  for (int i = 0; i < 13; i++) {
    // limpiar la matriz
    mx.clear();
    // dibujar el caracter F empezando en la columna i
    mx.setChar(i, 'F');
    delay(150);
    // esperar un tiempo
  }
  return 1;
}
/*###########################################################################
#
#   prototype: int final_Juego(STATE_T *state_ptr)
#
#   Return:  int
#
#   Purpose: Gestiona las acciones finales del juego, imprimiendo una F.
#
#   Plan:
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

void mostrarPuntaje(SNAKE_T *snake_ptr) {
  pantalla.clear();
  pantalla.setCursor(1, 0);
  pantalla.print(" DreamSnake POINTS");
  pantalla.setCursor(0, 1);
  pantalla.print("PUNTAJE PLAYER 1: ");
  pantalla.print(my_snake[0].puntaje);
  pantalla.setCursor(0, 2);
  pantalla.print("PUNTAJE PLAYER 2: ");
  pantalla.print(my_snake[1].puntaje);
  exit(1);
}
/*###########################################################################
#
#   prototype: void mostrarPuntaje(SNAKE_T *snake_ptr)
#
#   Return:  void
#
#   Purpose: Muestra el puntaje en la PANTALLA lcd utilizando la función 'dibujarDigito'.
#
#   Plan: Obtiene el puntaje de la serpiente y utiliza la función 'dibujarDigito'
#         para mostrar cada dígito en la matriz LCD.
#
#   Register of Revisions:
#
#   DATE                              RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

void mostrarMenu() {
  while (opcion == 0) {
    pantalla.setCursor(0, 0);
    pantalla.print("     DreamSnake");
    pantalla.setCursor(0, 1);
    pantalla.print("1. Un Solo jugador ");
    pantalla.setCursor(0, 2);
    pantalla.print("2. Multijugador (2)");
    pantalla.setCursor(0, 3);
    pantalla.print("Escoja con pulsador:");
    if (digitalRead(op1) == 1) {
      opcion = 1;
    } else if (digitalRead(op2) == 1) {
      opcion = 2;
    } else {
      opcion = 0;
    }
  }
  PLAYERS = opcion;
}
/*###########################################################################
#
#   prototype: void mostrarmenu()
#
#   Return:  void
#
#   Purpose: Muestra el menú de inicio del juego en el LCD.
#
#   Plan: Utiliza la biblioteca 'LiquidCrystal_I2C' para inicializar y configurar
#         el LCD. Luego, muestra el menú de inicio con las opciones disponibles.
#
#   Register of Revisions:
#
#   DATE                                RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

void buzzer(void) {
  //customDelay(velocidad);
  switch (currentState) {
    case PLAY:
      unsigned long currentTime = millis();
      // Si la nota actual es una pausa, espera la duración
      if (Pacman_Melody[currentNote].tone == QT) {
        if (currentTime - noteStartTime >= Pacman_Melody[currentNote].length + 10) {
          currentNote++;
          noteStartTime = currentTime;
        }
      } else {  // Si es una nota, reproduce la nota
        if (currentTime - noteStartTime >= Pacman_Melody[currentNote].length + 10) {
          noTone(Pin);    // Detiene la reproducción de la nota
          currentNote++;  // Avanza a la siguiente nota
          noteStartTime = currentTime;
        } else {
          tone(Pin, Pacman_Melody[currentNote].tone);  // Reproduce la nota
        }
      }
      // Si se ha reproducido la última nota, cambia al estado FINISH
      if (currentNote >= sizeof(Pacman_Melody) / sizeof(Pacman_Melody[0])) {
        currentNote = 0;
        Pacman_Melody[currentNote].tone = 0;
        currentState = PLAY;
      }
      break;
  }
}
/*###########################################################################
#
#   prototype: void buzzer(int frequency, long time)
#
#   Return:  void
#
#   Purpose: Genera un tono en el buzzer durante el tiempo especificado.
#
#   Plan: Utiliza la biblioteca 'tone' para generar un tono en el buzzer con
#         la frecuencia y duración especificadas. La función bloquea la ejecución
#         durante el tiempo de duración.
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

void customDelay(int milisegundos) {
  static unsigned long lastTime = 0;
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= milisegundos) {
    lastTime = currentTime;
  }
}
/*###########################################################################
#
#   prototype: void customDelay(long time)
#
#   Return:  void
#
#   Purpose: Implementa una función de retardo personalizada.
#
#   Plan: Utiliza un bucle para realizar una pausa en la ejecución del programa
#         durante el tiempo especificado en milisegundos.
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

void Notasmuerte(void) {
  // Reproduce la melodía de la muerte de Pac-Man
  nota(A6, 100);
  //delay(50); // Pausa
  nota(DS6, 100);
  // delay(50); // Pausa
  nota(E6, 100);
  //delay(50); // Pausa
}
/*###########################################################################
#
#   prototype: void Notasmuerte()
#
#   Return:  void
#
#   Purpose: Define las notas para la melodía que se reproduce al morir en el juego.
#
#   Plan: Utiliza la función 'nota' para definir las frecuencias de las notas
#         que componen la melodía de muerte.
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

void NotasComida(void) {
  noTone(Pin);
  tone(Pin, E6, 50);
}

void nota(int a, int b) {
  tone(Pin, a, b);
  delay(b);
  noTone(Pin);
}
/*###########################################################################
#
#   prototype: void nota(int frecuencia, int duracion)
#
#   Return:  void
#
#   Purpose: Reproduce una nota en el buzzer con la frecuencia y duración especificadas.
#
#   Plan: Utiliza la función 'buzzer' para reproducir una nota en el buzzer
#         con la frecuencia y duración especificadas.
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/

void reproducirMelodiaMuerte() {
  Notasmuerte();
}
/*###########################################################################
#
#   prototype: void reproducirMelodiaMuerte()
#
#   Return:  void
#
#   Purpose: Reproduce la melodía asociada a la muerte en el juego.
#
#   Plan: Utiliza la función 'nota' para reproducir cada nota de la melodía
#         de muerte y realiza pausas entre las notas.
#
#   Register of Revisions:
#
#   DATE                                            RESPONSIBLE 
#   -----------------------------------------------------------------------
#   11/23/2023                N. Gomez, J.Conrado y F.Useche 
#
##############################################################################*/