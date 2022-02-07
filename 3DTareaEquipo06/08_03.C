/* ejemplo 08_03.c, despliegue de objetos tridimensionales
   m‚todo de alambre, m‚todo de caras */

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

int ORIGEN_X = 320;  /* origen del plano tridimensional     */
int ORIGEN_Y = 240;  /* con relaci¢n al plano bidimensional */

int ESCALA_X = 30;   /* escala absoluta de los v‚rtices tridimensionales */
int ESCALA_Y = 30;

int ANGULO_EJE_Z = 45;  /* definici¢n del  ngulo del eje Z */

struct vertices
{
  int x;      /* coordenada en X */
  int y;      /* coordenada en Y */
  int z;      /* coordenada en Z */
};

struct caras
{
  int arreglo_caras[20];  /* hasta 20 v‚rtices por cara */
};

void desplegar_objeto_3d(struct vertices *puntos, int n_caras, struct caras *lados);
double grados_radianes(double grados);
void iniciar_graficos();
void leer_archivo_objeto3d(char *nombre_archivo, int *n_puntos, struct vertices *puntos, int *n_caras, struct caras *lados);
void linea_3d(int x1, int y1, int z1, int x2, int y2, int z2);
int  redondear(double numero);

void main()
{
  struct vertices puntos_objeto[50];
  struct caras    caras_objeto[50];
  int numero_puntos;
  int numero_caras;

  iniciar_graficos();

  /* cubo */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto03.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  desplegar_objeto_3d(puntos_objeto, numero_caras, caras_objeto);
  getch();
  cleardevice();

 /* leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto04.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  desplegar_objeto_3d(puntos_objeto, numero_caras, caras_objeto);
  getch();
  closegraph();   */
}

void desplegar_objeto_3d(struct vertices *puntos, int n_caras, struct caras *lados)
{
  int i, j;
  int va;  /* v‚rtice actual    */
  int vs;  /* v‚rtice siguiente */

  for(i=0; i<n_caras; i++)  /* dibuja las caras */
  {
     j=1;
     while (lados[i].arreglo_caras[j]>0)  /* dibuja las l¡neas hasta v‚rtice negativo */
     {
	va = lados[i].arreglo_caras[j-1];  /* x1, y1, z1 */
	vs = lados[i].arreglo_caras[j];    /* x2, y2, z2 */
	linea_3d(puntos[va-1].x, puntos[va-1].y, puntos[va-1].z, puntos[vs-1].x, puntos[vs-1].y, puntos[vs-1].z);  /* se resta 1 para acceso al vector de v‚rtices */
	j++;
     }
     va = lados[i].arreglo_caras[j-1];  /* "cierra" la cara */
     vs = -lados[i].arreglo_caras[j];
     linea_3d(puntos[va-1].x, puntos[va-1].y, puntos[va-1].z, puntos[vs-1].x, puntos[vs-1].y, puntos[vs-1].z);
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

void leer_archivo_objeto3d(char *nombre_archivo, int *n_vertices, struct vertices *puntos, int *n_caras, struct caras *lados)
{
  FILE *archivo_3d;
  int i, j;

  if ((archivo_3d = fopen(nombre_archivo, "r")) == NULL)
  {
     printf("archivo %s no puede abrirse", nombre_archivo);
     exit(1);
  }

  fscanf(archivo_3d, "%d", n_vertices);  /* lectura en formato entero */

  if (*n_vertices > 50)
  {
     printf("cantidad de puntos del objeto 3D no v lida, demasiado grande");
     exit(1);
  }

  for (i=0; i<*n_vertices; i++)  /* lee los v‚rtices */
     fscanf(archivo_3d, "%d %d %d", &puntos[i].x, &puntos[i].y, &puntos[i].z);

  fscanf(archivo_3d, "%d", n_caras);
  if (*n_caras > 50)
  {
     printf("cantidad de puntos del objeto 3D no v lida, demasiado grande");
     exit(1);
  }

  for (i=0; i<*n_caras; i++)  /* lee caras */
  {
     j = -1;  /* ¡ndice de caras */
     do
     {
	j++;
	fscanf(archivo_3d, "%d", &lados[i].arreglo_caras[j]);
     }while(lados[i].arreglo_caras[j] > 0);
  }
  fclose(archivo_3d);
}

void linea_3d(int x1, int y1, int z1, int x2, int y2, int z2)
{
  int x1_2d, y1_2d, x2_2d, y2_2d;  /* variables para conversi¢n bidimensional */
  double angulo;

  angulo = grados_radianes(ANGULO_EJE_Z);
  x1_2d = redondear(  x1*ESCALA_X  + ORIGEN_X - z1*ESCALA_X * cos(angulo));
  y1_2d = redondear(-(y1*ESCALA_Y) + ORIGEN_Y + z1*ESCALA_Y * sin(angulo));  /* punto Y positivo en el plano */
  x2_2d = redondear(  x2*ESCALA_X  + ORIGEN_X - z2*ESCALA_X * cos(angulo));
  y2_2d = redondear(-(y2*ESCALA_Y) + ORIGEN_Y + z2*ESCALA_Y * sin(angulo));  /* es negativo en el monitor    */

  line(x1_2d, y1_2d, x2_2d, y2_2d);
}

int redondear(double numero)
{
  if (numero - (int) numero >= 0.5)
     return numero + 1;
  else
     return numero;
}
