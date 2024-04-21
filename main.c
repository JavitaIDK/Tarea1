#include "tdas/list.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct {
  char nombre[MAX];
  char nombreMayus[MAX];
  char sintoma[MAX];
  int edad;
  int identificacion;
  char prioridad[MAX];
  int importancia;
  time_t hora;
} TipoPaciente;

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★");
  puts("|    Sistema de Gestión Hospitalaria   |");
  puts("★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
  printf("\n");
}

int totalPacientes = 0; // variable global para contar los pacientes

void registrar_paciente(List *pacientes) {
  puts("★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★");
  puts("|     Registrar nuevo paciente    |");
  printf("★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★\n\n");
  getchar();
  TipoPaciente *nuevoPaciente =
      malloc(sizeof(TipoPaciente)); // rerservando memoria
  if (nuevoPaciente == NULL) {
    printf("ERROR EN ASIGNAR MEMORIA");
    return;
  }
  printf("Ingrese el nombre del paciente\n");
  printf("➤ ");
  scanf("%[^\n]", nuevoPaciente->nombre);

  printf("\nIngrese la edad del paciente\n");
  printf("➤ ");
  scanf("%d", &nuevoPaciente->edad);

  printf("\nIngrese el sintoma del paciente\n");
  printf("➤ ");
  getchar();
  scanf("%[^\n]", nuevoPaciente->sintoma);

  nuevoPaciente->identificacion = totalPacientes; // asigna el orden de llegada
  strcpy(nuevoPaciente->prioridad, "Bajo");       // asigna prioidad baja
  nuevoPaciente->importancia = 0;

  time(&nuevoPaciente->hora); // Guarda la hora actual

  list_pushBack(pacientes, nuevoPaciente);
  totalPacientes += 1;
}

int compararPacientes(const void *a, const void *b) {
  const TipoPaciente *paciente1 = (const TipoPaciente *)a;
  const TipoPaciente *paciente2 = (const TipoPaciente *)b;
  if (paciente1->importancia > paciente2->importancia)
    return -1; // si el paciente1 tiene mayor prioridad que el paciente2 va por
               // encima
  else if (paciente1->importancia < paciente2->importancia)
    return 1; // si el paciente1 tiene menor prioridad que el paciente2 va abajo
  return paciente1->identificacion -
         paciente2->identificacion; // si tienen la misma importancia, se
                                    // comparan las ids
}

void ordenarLista(List *pacientes) {
  TipoPaciente *tempArray = malloc(
      totalPacientes * sizeof(TipoPaciente)); // se crea un array temporal
  if (tempArray == NULL)
    return;
  TipoPaciente *current =
      list_first(pacientes); // se inicializa un puntero al primero de la lista
  for (int i = 0; i < totalPacientes;
       i++) { // este for copia los elementos de current al array temporal
    tempArray[i] = *current;
    current = list_next(pacientes);
  }

  qsort(tempArray, totalPacientes, sizeof(TipoPaciente),
        compararPacientes); // qsort para ordenar el array

  current = list_first(pacientes);
  for (int i = 0; i < totalPacientes;
       i++) { // se copia los elementos de temparray al current
    *current = tempArray[i];
    current = list_next(pacientes);
  }
  free(tempArray); // liberar memoria de array
}
void mostrar_lista_pacientes(List *pacientes) {
  ordenarLista(pacientes); // funcion para ordenar la lista
  TipoPaciente *pacienteActual = list_first(pacientes);
  if (totalPacientes == 0) {
    puts("No hay pacientes en espera, intentelo de nuevo");
    return;
  }
  puts("★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
       "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★");
  printf("|                             Pacientes en espera: %d                "
         "                                  |\n",
         totalPacientes);
  puts("★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
       "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★");
  puts("|          Nombres        |          Edad        |          Sintoma    "
       "    |          Prioridad      |");
  puts("★----------------------------------------------------------------------"
       "------------------------------★");

  while (pacienteActual != NULL) { // mientras el paciente actual exista
    printf("%17s        %14d        %18s        %19s        ",
           pacienteActual->nombre, pacienteActual->edad,
           pacienteActual->sintoma, pacienteActual->prioridad);
    struct tm *local = localtime(&pacienteActual->hora);
    printf("     %02d:%02d:%02d", local->tm_hour, local->tm_min,
           local->tm_sec); // imprimir la hora de llegada
    printf("\n");
    if (pacienteActual == NULL) // verifica si la lista esta vacia
      return;
    pacienteActual = list_next(pacientes);
  }
  puts("★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
       "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★");
}

// Modificar textos
void toMayus(char *texto) { // funcion para pasar el texto a mayusculas
  for (int i = 0; texto[i] != '\0'; i++)
    texto[i] = toupper(texto[i]);
}
void corregir(char *texto) { // funcion para colocar la primera letra del texto
                             // en mayus y lo restante en minusculas
  for (int i = 1; texto[i] != '\0'; i++) {
    texto[0] = toupper(texto[0]);
    texto[i] = tolower(texto[i]);
  }
}
void nameMayus(
    List *pacientes) { // funcion para transformar el nombre en mayusculas
  TipoPaciente *updateName = list_first(pacientes);
  while (updateName != NULL) {
    strcpy(updateName->nombreMayus, updateName->nombre);
    toMayus(updateName->nombreMayus);
    updateName = list_next(pacientes);
  }
}

void asignar_prioridad(List *pacientes) {
  nameMayus(pacientes);
  TipoPaciente *updatePriority = list_first(pacientes);

  char copiaNombre[MAX]; // variable para escribir el nombre que busco
  char priority[MAX];    // variable para escribir la prioridad
  bool existe = false;   // variable inicializada en falso para despues ver si
                         // existe el paciente buscado
  printf("\n");
  puts("★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★");
  puts("|     Asignar prioridad al paciente    |");
  puts("★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★");
  printf("Ingrese el nombre del paciente--> ");
  getchar();
  scanf("%[^\n]", copiaNombre);
  toMayus(copiaNombre);

  while (true) {
    printf("\nAsigne prioridad (Bajo, Medio, Alto) --> ");
    scanf("%s", priority);
    getchar();
    toMayus(priority);
    if (strcmp(priority, "BAJO") == 0 ||
        strcmp(priority, "MEDIO") ==
            0 || // verificando si ingreso una prioridad valida
        strcmp(priority, "ALTO") == 0)
      break;
    else
      printf("Por favor, ingrese una prioridad válida (Bajo, Medio, Alto).\n");
  }

  while (updatePriority != NULL) { // actualizando prioridad
    if (strcmp(copiaNombre, updatePriority->nombreMayus) ==
        0) { // veo si el nombre existe en la lista
      // asignando prioridad caso por caso
      if (strcmp(priority, "BAJO") == 0) {
        updatePriority->importancia = 1;
      } else if (strcmp(priority, "MEDIO") == 0) {
        updatePriority->importancia = 2;
      } else if (strcmp(priority, "ALTO") == 0) {
        updatePriority->importancia = 3;
      }
      corregir(priority); // escribiendo la prioridad bien
      strcpy(updatePriority->prioridad, priority);
      existe = true; // el paciente si existe
      printf("\n-------------->Prioridad actualizada<--------------\n");
      break;
    }
    updatePriority = list_next(pacientes);
  }
  if (!existe) {
    printf("\nERROR: EL PACIENTE NO EXISTE, INTENTELO DE NUEVO\n");
  }
}

void atender_siguiente(List *pacientes) {
  TipoPaciente *pacienteActual = list_first(pacientes);
  puts("★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★");
  puts("|    Atender al siguiente paciente     |");
  puts("★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★");
  if (pacienteActual != NULL) { // mientras el paciente no sea null
    puts("PACIENTE ATENDIDO");
    puts("⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓");
    printf("Nombre ➤ %s\nEdad ➤ %d\nSintoma ➤ %s\n", pacienteActual->nombre,
           pacienteActual->edad, pacienteActual->sintoma);
    list_popCurrent(pacientes); // eliminar el paciente actual
    totalPacientes--;
  } else {
    printf("No hay pacientes en espera\n");
  }
}

void mostrar_xPrioridad(List *pacientes) {
  puts("========================================");
  puts("|       Pacientes por prioridad        |");
  puts("========================================");

  TipoPaciente *pacientesElegidos = list_first(pacientes);

  char eleccion[MAX]; // variable para que se escriba la prioridad que quiera
  printf("Ingrese la prioridad que desea ver (Bajo, Media, Alto)--> ");
  scanf("%s", eleccion);
  corregir(eleccion);
  printf("Mostrando pacientes de prioridad: %s\n", eleccion);
  while (pacientesElegidos !=
         NULL) { // while para mostar los pacientes por la categoria
    if (strcmp(eleccion, "Bajo") == 0 &&
        strcmp(eleccion, pacientesElegidos->prioridad) == 0)
      printf("Nombre: %s\n", pacientesElegidos->nombre);
    if (strcmp(eleccion, "Medio") == 0 &&
        strcmp(eleccion, pacientesElegidos->prioridad) == 0)
      printf("Nombre: %s\n", pacientesElegidos->nombre);
    if (strcmp(eleccion, "Alto") == 0 &&
        strcmp(eleccion, pacientesElegidos->prioridad) == 0)
      printf("Nombre: %s\n", pacientesElegidos->nombre);
    pacientesElegidos = list_next(pacientes);
  }
}
int main() {
  char opcion;
  List *pacientes =
      list_create(); // puedes usar una lista para gestionar los pacientes
  if (pacientes == NULL) {
    printf("ERROR EN CREAR LA LISTA");
    exit(EXIT_FAILURE);
  }
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      asignar_prioridad(pacientes);
      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':
      atender_siguiente(pacientes);
      // Lógica para atender al siguiente paciente
      break;
    case '5':
      mostrar_xPrioridad(pacientes);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);

  return 0;
}
