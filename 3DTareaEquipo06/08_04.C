/* ejemplo 08_04.c, despliegue de objetos tridimensionales
   m‚todo de alambre, m‚todo de l¡neas, representaci¢n isom‚trica */

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

int ORIGEN_X = 320;  /* origen del plano tridimensional     */
int ORIGEN_Y = 240;  /* con relaci¢n al plano bidimensional */
/*Esos nematodos no sirven para nada, al igual que los citadinos y sus maquinas voladoras 7u7*/

int ESCALA_X = 30;   /* escala absoluta de los v‚rtices tridimensionales */
int ESCALA_Y = 30;

/* int ANGULO_EJE_Z = 45;  el  ngulo es fijo a 30 grados */

struct objeto_3d
{
  int punto;  /* n£mero de punto           */
  int x;      /* coordenada en X           */
  int y;      /* coordenada en Y           */
  int z;      /* coordenada en Z           */
  int pluma;  /* pluma, 2 dibujar, 3 mover */
};

void desplegar_objeto_3d(int puntos, struct objeto_3d *vertices);
double grados_radianes(double grados);
void iniciar_graficos();
void leer_archivo_objeto3d(char *nombre_archivo, int *puntos, struct objeto_3d *vertices);
void linea_3d(int x1, int y1, int z1, int x2, int y2, int z2);
int  redondear(double numero);

void main()
{
  struct objeto_3d objeto[50];
  int numero_puntos;

  iniciar_graficos();

  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto01.dat", &numero_puntos, objeto);
  desplegar_objeto_3d(numero_puntos, objeto);
  getch();
  cleardevice();

  /*leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto02.dat", &numero_puntos, objeto);
  desplegar_objeto_3d(numero_puntos, objeto);
  getch();
  closegraph(); */
}

void desplegar_objeto_3d(int puntos, struct objeto_3d *vertices)
{
  int i;

  for (i=0; i<puntos; i++)
  {
     if (vertices[i].pluma == 3)
	continue;  /* la funci¢n mover es solamente conceptual */
     else
	linea_3d(vertices[i-1].x, vertices[i-1].y, vertices[i-1].z, vertices[i].x, vertices[i].y, vertices[i].z);
  }
}

double grados_radianes(double grados)
{
  return grados * 3.14159 / 180.0;
}

void iniciar_graficos()
{
  int controlador = DETECT, modo;

  initgraph(&controlador, &modo, "c:\\tc\\bgi");
}

void leer_archivo_objeto3d(char *nombre_archivo, int *n_puntos, struct objeto_3d *vertices)
{
  FILE *archivo_3d;
  int i;

  if ((archivo_3d = fopen(nombre_archivo, "r")) == NULL)
  {
     printf("archivo %s no puede abrirse", nombre_archivo);
     exit(1);
  }

  fscanf(archivo_3d, "%d", n_puntos);  /* lectura en formato entero */

  if (*n_puntos > 50)
  {
     printf("cantidad de puntos del objeto 3D no v lida, demasiado grande");
     exit(1);
  }

  for (i=0; i<*n_puntos; i++)
     fscanf(archivo_3d, "%d %d %d %d %d", &vertices[i].punto, &vertices[i].x, &vertices[i].y, &vertices[i].z, &vertices[i].pluma);

  fclose(archivo_3d);
}

void linea_3d(int x1, int y1, int z1, int x2, int y2, int z2)
{
  int x1_2d, y1_2d, x2_2d, y2_2d;  /* variables para conversi¢n bidimensional */
  double angulo;

  angulo = grados_radianes(30);
  x1_2d = redondear(  ORIGEN_X + (x1-z1)*ESCALA_X*cos(angulo) );
  y1_2d = redondear( -(y1*ESCALA_Y) + ORIGEN_Y + (x1+z1)*ESCALA_Y*sin(angulo) );  /* punto Y positivo en el plano */
  x2_2d = redondear(  ORIGEN_X + (x2-z2)*ESCALA_X*cos(angulo) );
  y2_2d = redondear( -(y2*ESCALA_Y) + ORIGEN_Y + (x2+z2)*ESCALA_Y*sin(angulo) );  /* es negativo en el monitor    */

  line(x1_2d, y1_2d, x2_2d, y2_2d);
}

int redondear(double numero)
{
  if (numero - (int) numero >= 0.5)
     return numero + 1;
  else
     return numero;
}
