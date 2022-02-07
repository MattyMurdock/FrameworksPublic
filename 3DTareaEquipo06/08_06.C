/* ejemplo 08_06.c, transformaciones tridimensionales
   traslaci¢n, escalaci¢n, rotaci¢n en X, Y y Z
   m‚todo de caras, proyecci¢n oblicua e isom‚trica */

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <dos.h>

int ORIGEN_X = 200;
int ORIGEN_Y = 200;

int ESCALA_X = 10;
int ESCALA_Y = 10;

int ANGULO_EJE_Z = 45;

struct vertices
{
  double x;  /* coordenada en X, ahora double para las rotaciones */
  double y;  /* coordenada en Y */
  double z;  /* coordenada en Z */
};

struct caras
{
  int arreglo_caras[20];  /* hasta 20 v‚rtices por cara */
};

void copiar_objeto(int n_puntos, struct vertices *origen, struct vertices *destino);
void desplegar_objeto_3d_isometrica(struct vertices *puntos, int n_caras, struct caras *lados);
void desplegar_objeto_3d_oblicua(struct vertices *puntos, int n_caras, struct caras *lados);
void escalar(double sx, double sy, double sz, int n_puntos, struct vertices *puntos);
double grados_radianes(double grados);
void iniciar_graficos();
void leer_archivo_objeto3d(char *nombre_archivo, int *n_puntos, struct vertices *puntos, int *n_caras, struct caras *lados);
void linea_3d_isometrica(double x1, double y1, double z1, double x2, double y2, double z2);
void linea_3d_oblicua(double x1, double y1, double z1, double x2, double y2, double z2);
int  redondear(double numero);
void rotar_en_X(int n_puntos, struct vertices *puntos, double theta);
void rotar_en_Y(int n_puntos, struct vertices *puntos, double theta);
void rotar_en_Z(int n_puntos, struct vertices *puntos, double theta);
void trasladar(double tx, double ty, double tz, int n_puntos, struct vertices *puntos);

void main()
{
  struct vertices puntos_objeto[50];  /* objeto a transformar */
  struct caras    caras_objeto[50];
  struct vertices puntos_objeto_original[50];  /* objeto original */

  int numero_puntos;
  int numero_caras;

  int i;  /* ciclo de  ngulos para la rotaci¢n */

  iniciar_graficos();

  /* proyecci¢n oblicua */
  /* cubo */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto05.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  /* traslaci¢n, cubo */
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);  /* original */
  trasladar(10.0, 0.0, 0.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(0.0, 10.0, 0.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(0.0, 0.0, 10.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(15.0, -10.0, 10.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
  getch();
  cleardevice();

  /* cubo con corte */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto06.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  /* traslaci¢n, cubo con corte */
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);  /* original */
  trasladar(10.0, 0.0, 0.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(0.0, 10.0, 0.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(0.0, 0.0, 10.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(15.0, -10.0, 10.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
  getch();
  cleardevice();

  /* proyecci¢n isom‚trica */
  /* cubo */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto05.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  /* traslaci¢n, cubo */
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);  /* original */
  trasladar(10.0, 0.0, 0.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(0.0, 10.0, 0.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(0.0, 0.0, 10.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(15.0, -10.0, 10.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
  getch();
  cleardevice();

  /* cubo con corte */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto06.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  /* traslaci¢n, cubo con corte */
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);  /* original */
  trasladar(10.0, 0.0, 0.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(0.0, 10.0, 0.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(0.0, 0.0, 10.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  trasladar(15.0, -10.0, 10.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
  getch();
  cleardevice();

  /* proyecci¢n oblicua */
  /* cubo */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto05.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  /* escalaci¢n, cubo */
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);  /* original */
  escalar(3.0, 3.0, 3.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
  getch();
  cleardevice();
  copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura original */
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);  /* original */
  escalar(0.5, 0.5, 0.5, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
  getch();
  cleardevice();

  /* proyecci¢n oblicua */
  /* cubo con corte */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto06.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  /* escalaci¢n, cubo con corte */
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);  /* original */
  escalar(4.0, 3.0, 1.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
  getch();
  cleardevice();

  /* proyecci¢n isom‚trica */
  /* cubo */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto05.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  /* escalaci¢n, cubo */
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);  /* original */
  escalar(4.0, 4.0, 4.0, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
  getch();
  cleardevice();

  /* proyecci¢n isom‚trica */
  /* cubo con corte */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto06.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  /* escalaci¢n, cubo con corte */
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);  /* original */
  escalar(0.5, 0.5, 0.5, numero_puntos, puntos_objeto);
  desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
  getch();
  cleardevice();

  /* proyecci¢n oblicua */
  /* cubo */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto05.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  escalar(3.0, 3.0, 3.0, numero_puntos, puntos_objeto);  /* escala para mejor visualizaci¢n */
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  for(i=0;i<=360; i++)  /* rotar en X */
  {
     cleardevice();
     rotar_en_X(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);
     delay(10);
  }
  for(i=0;i<=360; i++)  /* rotar en Y */
  {
     cleardevice();
     rotar_en_Y(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura objeto original */
     delay(10);
  }
  for(i=0;i<=360; i++)  /* rotar en Z */
  {
     cleardevice();
     rotar_en_Z(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);
     delay(10);
  }

  /* cubo con corte */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto06.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  escalar(3.0, 3.0, 3.0, numero_puntos, puntos_objeto);  /* escala para mejor visualizaci¢n */
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  for(i=0;i<=360; i++)  /* rotar en X */
  {
     cleardevice();
     rotar_en_X(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);
     delay(10);
  }
  for(i=0;i<=360; i++)  /* rotar en Y */
  {
     cleardevice();
     rotar_en_Y(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura objeto original */
     delay(10);
  }
  for(i=0;i<=360; i++)  /* rotar en Z */
  {
     cleardevice();
     rotar_en_Z(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_oblicua(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);
     delay(10);
  }
  getch();
  cleardevice();

  /* proyecci¢n isom‚trica */
  /* cubo */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto05.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  escalar(3.0, 3.0, 3.0, numero_puntos, puntos_objeto);  /* escala para mejor visualizaci¢n */
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  for(i=0;i<=360; i++)  /* rotar en X */
  {
     cleardevice();
     rotar_en_X(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);
     delay(10);
  }
  for(i=0;i<=360; i++)  /* rotar en Y */
  {
     cleardevice();
     rotar_en_Y(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura objeto original */
     delay(10);
  }
  for(i=0;i<=360; i++)  /* rotar en Z */
  {
     cleardevice();
     rotar_en_Z(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);
     delay(10);
  }

  /* cubo con corte */
  leer_archivo_objeto3d("c:\\TC\\BIN\\3d\\objeto06.dat", &numero_puntos, puntos_objeto, &numero_caras, caras_objeto);
  escalar(3.0, 3.0, 3.0, numero_puntos, puntos_objeto);  /* escala para mejor visualizaci¢n */
  copiar_objeto(numero_puntos, puntos_objeto, puntos_objeto_original);  /* respaldo del objeto original */
  for(i=0;i<=360; i++)  /* rotar en X */
  {
     cleardevice();
     rotar_en_X(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);
     delay(10);
  }
  for(i=0;i<=360; i++)  /* rotar en Y */
  {
     cleardevice();
     rotar_en_Y(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);  /* restaura objeto original */
     delay(10);
  }
  for(i=0;i<=360; i++)  /* rotar en Z */
  {
     cleardevice();
     rotar_en_Z(numero_puntos, puntos_objeto, i);
     desplegar_objeto_3d_isometrica(puntos_objeto, numero_caras, caras_objeto);
     copiar_objeto(numero_puntos, puntos_objeto_original, puntos_objeto);
     delay(10);
  }
  getch();
  closegraph();
}

void copiar_objeto(int n_puntos, struct vertices *origen, struct vertices *destino)
{
  int i;

  for (i=0; i<n_puntos; i++)
  {
     destino[i].x = origen[i].x;
     destino[i].y = origen[i].y;
     destino[i].z = origen[i].z;
  }
}

void desplegar_objeto_3d_isometrica(struct vertices *puntos, int n_caras, struct caras *lados)
{
  int i, j;
  int va;  /* v‚rtice actual    */
  int vs;  /* v‚rtice siguiente */

  for(i=0; i<n_caras; i++)
  {
     j=1;
     while (lados[i].arreglo_caras[j]>0)
     {
	va = lados[i].arreglo_caras[j-1];
	vs = lados[i].arreglo_caras[j];
	linea_3d_isometrica(puntos[va-1].x, puntos[va-1].y, puntos[va-1].z, puntos[vs-1].x, puntos[vs-1].y, puntos[vs-1].z);  /* se resta 1 para acceso al vector de v‚rtices */
	j++;
     }
     va = lados[i].arreglo_caras[j-1];
     vs = -lados[i].arreglo_caras[j];
     linea_3d_isometrica(puntos[va-1].x, puntos[va-1].y, puntos[va-1].z, puntos[vs-1].x, puntos[vs-1].y, puntos[vs-1].z);
  }
}

void desplegar_objeto_3d_oblicua(struct vertices *puntos, int n_caras, struct caras *lados)
{
  int i, j;
  int va;  /* v‚rtice actual    */
  int vs;  /* v‚rtice siguiente */

  for(i=0; i<n_caras; i++)
  {
     j=1;
     while (lados[i].arreglo_caras[j]>0)
     {
	va = lados[i].arreglo_caras[j-1];
	vs = lados[i].arreglo_caras[j];
	linea_3d_oblicua(puntos[va-1].x, puntos[va-1].y, puntos[va-1].z, puntos[vs-1].x, puntos[vs-1].y, puntos[vs-1].z);  /* se resta 1 para acceso al vector de v‚rtices */
	j++;
     }
     va = lados[i].arreglo_caras[j-1];
     vs = -lados[i].arreglo_caras[j];
     linea_3d_oblicua(puntos[va-1].x, puntos[va-1].y, puntos[va-1].z, puntos[vs-1].x, puntos[vs-1].y, puntos[vs-1].z);
  }
}

void escalar(double sx, double sy, double sz, int n_puntos, struct vertices *puntos)
{
  int i;

  for(i=0; i<n_puntos; i++)
  {
     puntos[i].x = puntos[i].x * sx;
     puntos[i].y = puntos[i].y * sy;
     puntos[i].z = puntos[i].z * sz;
  }
}

double grados_radianes(double grados)
{
  return grados * 0.017453277;  /* 3.14159 / 180 */
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

  /* ahora lectura flotante */
  for (i=0; i<*n_vertices; i++)
     fscanf(archivo_3d, "%lf %lf %lf", &puntos[i].x, &puntos[i].y, &puntos[i].z);

  fscanf(archivo_3d, "%d", n_caras);
  if (*n_caras > 50)
  {
     printf("cantidad de puntos del objeto 3D no v lida, demasiado grande");
     exit(1);
  }

  for (i=0; i<*n_caras; i++)
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

void linea_3d_isometrica(double x1, double y1, double z1, double x2, double y2, double z2)
{
  int x1_2d, y1_2d, x2_2d, y2_2d;  /* variables para convesi¢n bidimensional */
  double angulo;

  angulo = grados_radianes(30);
  x1_2d = redondear(  ORIGEN_X + (x1-z1)*ESCALA_X*cos(angulo) );
  y1_2d = redondear( -(y1*ESCALA_Y) + ORIGEN_Y + (x1+z1)*ESCALA_Y*sin(angulo) );  /* punto Y positivo en el plano */
  x2_2d = redondear(  ORIGEN_X + (x2-z2)*ESCALA_X*cos(angulo) );
  y2_2d = redondear( -(y2*ESCALA_Y) + ORIGEN_Y + (x2+z2)*ESCALA_Y*sin(angulo) );  /* es negativo en el monitor    */

  line(x1_2d, y1_2d, x2_2d, y2_2d);
}

void linea_3d_oblicua(double x1, double y1, double z1, double x2, double y2, double z2)
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


void rotar_en_X(int n_puntos, struct vertices *puntos, double theta)
{
  int i;
  double angulo;
  double ty;  /* salva el valor del punto en Y */

  angulo = grados_radianes(theta);
  for (i=0; i<n_puntos; i++)
  {
     ty = puntos[i].y;
     /* puntos[i].x = puntos[i].x  s¢lo conceptual, no se afecta */
     puntos[i].y = puntos[i].y*cos(angulo) - puntos[i].z*sin(angulo);
     puntos[i].z = ty*sin(angulo) + puntos[i].z*cos(angulo);  /* se utiliza el valor de Y respaldado */
  }
}

void rotar_en_Y(int n_puntos, struct vertices *puntos, double theta)
{
  int i;
  double angulo;
  double tx;  /* salva el valor del punto en X */

  angulo = grados_radianes(theta);
  for (i=0; i<n_puntos; i++)
  {
     tx = puntos[i].x;
     puntos[i].x = puntos[i].z*sin(angulo) + puntos[i].x*cos(angulo);
     /* puntos[i].y = puntos[i].y  s¢lo conceptual, no se afecta */
     puntos[i].z = puntos[i].z*cos(angulo) - tx*sin(angulo);  /* se utiliza el valor de X respaldado */
  }
}

void rotar_en_Z(int n_puntos, struct vertices *puntos, double theta)
{
  int i;
  double angulo;
  double tx;  /* salva el valor del punto en X */

  angulo = grados_radianes(theta);
  for (i=0; i<n_puntos; i++)
  {
     tx = puntos[i].x;
     puntos[i].x = puntos[i].x*cos(angulo) - puntos[i].y*sin(angulo);
     puntos[i].y = tx*sin(angulo) + puntos[i].y*cos(angulo);  /* se utiliza el valor de X respaldado */
     /* puntos[i].z = puntos[i].z;   s¢lo conceptual, no se afecta */
  }
}

void trasladar(double tx, double ty, double tz, int n_puntos, struct vertices *puntos)
{
  int i;

  for(i=0; i<n_puntos; i++)
  {
     puntos[i].x = puntos[i].x + tx;
     puntos[i].y = puntos[i].y + ty;
     puntos[i].z = puntos[i].z + tz;
  }
}

