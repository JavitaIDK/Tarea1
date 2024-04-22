# Codigo para lista de espera de un hospital con prioridad

<br>
<br>

Para ejecutar el codigo hay que usar estos comandos:
````console
gcc tdas/*.c main.c -Wno-unused-result -o main
````

Y luego ejecutar:
````console
./main
````

<br>

<hr>

--> El codigo te abre un menu donde tu eliges que opcion te interesa.

````bash
1) Registrar paciente `nombre`, `edad`, `sintoma`
2) Asignar prioridad al paciente `ALTA`, `MEDIA`, `BAJA`
3) Mostrar lista de espera
4) Atender al siguiente paciente
5) Mostrar paciente por prioridad `ALTA`, `MEDIA`, `BAJA`
6) Exit
````

--> Se crea un struct donde almacenan los datos de los pacientes

````c
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
````

--> **NOTA**
````c
 time_t hora;
````
Vendria siendo la hora en la que se registran los pacientes

<br>

### --> PROTOTIPOS DE FUNCIONES PRINCIPALES

`void mostrarMenuPrincipal();`

`void registrar_paciente(List *pacientes);`

`void ordenarLista(List *pacientes);`

`void mostrar_lista_pacientes(List *pacientes);`

`void asignar_prioridad(List *pacientes);`

`void atender_siguiente(List *pacientes);`

`void mostrar_xPrioridad(List *pacientes);`

<br>

### --> PROTOTIPOS DE FUNCIONES SECUNDARIAS

`void toMayus(char *texto);`

`void corregir(char *texto);`

`void nameMayus(List *pacientes);`

<br>

<hr>

### --> Qsort para ordenar el array por prioridad e identificacion (orden de llegada)

En el programa se utiliza un **qsort** para facilitar el proceso y ser mas eficiente, cree una funcion para comparar la prioridad y si son iguales por la identificacion (orden de llegada), Despues se ordenan al llamar al qsort en `ordenarLista`.

````c
int compararPacientes(const void *a, const void *b) //funcion para comparar los pacientes
````
````c
 qsort(tempArray, totalPacientes, sizeof(TipoPaciente),compararPacientes); //qsort para ordenar de mayor a menor
````
<br>

### --> OBSERVACIONES
- Se pondra prioridad **BAJA** por default al registar a algun paciente.
- Si le agregas una prioridad a un paciente que no existe arrojara el error "ERROR: EL PACIENTE NO EXISTE, INTENTELO DE NUEVO".
- Al querer cambiar la prioridad de un paciente, el nombre tiene que tener las mismas letras que al inicio, da igual las mayusculas o minusculas.


<br>

<br>
