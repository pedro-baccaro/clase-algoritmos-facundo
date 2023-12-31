#include <iostream>
#include <cstring>
#include <ctime> // Solo para tests
using namespace std;

const int MAXIMO_ALUMNOS = 60;
const int MAXIMO_NOMBRE = 40;
const int CANTIDAD_NOTAS = 7;

struct Notas{
    int primerParcial;
    int segundoParcial;
    int primerParcial1Rec;
    int segundoParcial1Rec;
    int primerParcial2Rec;
    int segundoParcial2Rec;
    int trabajoPractico;
};

struct Alumno{
    char nombre[MAXIMO_NOMBRE];
    int legajo;
};

int contarAlumnos(Alumno alumnos[], int cantidadMaxima);  //Dado el vector de alumnos, y la longitud de este, devuelve cuantos alumnos contiene (el resto tiene -1 de legajo, lo cual se explica en main)
void obtenerApellido(char nombre[], char* salidaApellido); //Dado un nombre completo (string), devuelve solo la primera palabra (el apellido, un string) en una variable
Alumno* ordenarAlumnosPorNombre(Alumno alumnosPorLegajo[], int cantidadAlumnos); //Dado el vector de alumnos, y la cantidad de alumnos que contiene, devuelve un vector ordenado por apellidos
int posicionPorLegajo(Alumno alumno, Alumno alumnosPorLegajo[], int cantidadAlumnos); //Dado un alumno, y el vector de alumnos ordenado por legajo, devuelve la posicion del alumno en dicho vector
Notas buscarNotas(int curso[MAXIMO_ALUMNOS][CANTIDAD_NOTAS], int posicionCurso); //Busca las notas en la matriz del curso, se necesita saber cual de las filas corresponde al alumno (dado por su posicion en el vector ordenado por legajo)
void obtenerSituacionAcademica(Notas notas, char* salidaSituacionAcademica); //Dadas las notas del alumno, devuelve la situacion academica del mismo (promocionado, regularizado, no aprobado) en una variable de salida
void hacerInforme(int curso[MAXIMO_ALUMNOS][CANTIDAD_NOTAS], Alumno alumnosPorLegajo[], int cantidadAlumnos);
void tests();


int main(){
    tests();
    
    int curso[MAXIMO_ALUMNOS][CANTIDAD_NOTAS]; //Asumimos que ya tiene las notas cargadas
    //Ademas asumimos que las filas del curso, que representan a cada alumno, se encuentran ordenadas segun el legajo del alumno
    
    Alumno alumnos[MAXIMO_ALUMNOS]; //Este sería el vector paralelo, asumimos que está cargado (y ordenado por legajo)
    //Además asumimos que luego del ultimo alumno, el resto tienen como legajo -1, para indicar que no hay mas alumnos
    //Sino podríamos asumir que sabemos la cantidad, y pasariamos eso como tercer parametro en hacerInforme

    //hacerInforme(curso, alumnos, contarAlumnos(alumnos, MAXIMO_ALUMNOS));
    return 0;
}

int contarAlumnos(Alumno alumnos[], int cantidadMaxima){
    int i = 0;
    while(i < cantidadMaxima && alumnos[i].legajo != -1){
        i++;
    }
    return i;
}

void obtenerApellido(char nombre[], char* salidaApellido){
    char* token = strtok(nombre, " ");
    strcpy(salidaApellido, token);
}

Alumno* ordenarAlumnosPorApellido(Alumno alumnosPorLegajo[], int cantidadAlumnos){
    Alumno* alumnosPorApellido = new Alumno[cantidadAlumnos];
    for (int i = 0; i < cantidadAlumnos; i++){
        alumnosPorApellido[i] = alumnosPorLegajo[i];
    }
    //bubble sort de los alumnos (por apellido)
    for (int i = 0; i < cantidadAlumnos; i++){
        for (int j = 0; j < cantidadAlumnos - 1; j++){
            char apellidoActual[MAXIMO_NOMBRE];
            char apellidoProximo[MAXIMO_NOMBRE];
            obtenerApellido(alumnosPorApellido[j].nombre, apellidoActual);
            obtenerApellido(alumnosPorApellido[j+1].nombre, apellidoProximo);
            if (strcmp(apellidoActual, apellidoProximo) > 0){
                Alumno aux = alumnosPorApellido[j];
                alumnosPorApellido[j] = alumnosPorApellido[j+1];
                alumnosPorApellido[j+1] = aux;
            }
        }
    }
    return alumnosPorApellido;
}

int posicionPorLegajo(Alumno alumno, Alumno alumnosPorLegajo[], int cantidadAlumnos){
    int i = 0;
    while (i < cantidadAlumnos && alumnosPorLegajo[i].legajo != alumno.legajo){
        i++;
    }
    return i;
}

Notas buscarNotas(int curso[MAXIMO_ALUMNOS][CANTIDAD_NOTAS], int posicionCurso){
    Notas notas;
    notas.primerParcial = curso[posicionCurso][0];
    notas.segundoParcial = curso[posicionCurso][1];
    notas.primerParcial1Rec = curso[posicionCurso][2];
    notas.segundoParcial1Rec = curso[posicionCurso][3];
    notas.primerParcial2Rec = curso[posicionCurso][4];
    notas.segundoParcial2Rec = curso[posicionCurso][5];
    notas.trabajoPractico = curso[posicionCurso][6];
    return notas;
}

void obtenerSituacionAcademica(Notas notas, char* salidaSituacionAcademica){
    if (notas.trabajoPractico >= 8 && (
            notas.primerParcial >= 8 && notas.segundoParcial >= 8 ||
            notas.primerParcial >= 8 && notas.segundoParcial1Rec >= 8 ||
            notas.primerParcial1Rec >=8 && notas.segundoParcial >= 8
        )    
    ){strcpy(salidaSituacionAcademica, "promocionado");}
    else if (notas.trabajoPractico >= 6 && (
            notas.primerParcial >= 6 && (
                notas.segundoParcial >= 6 ||
                notas.segundoParcial1Rec >= 6 ||
                notas.segundoParcial2Rec >= 6
            ) ||
            notas.primerParcial1Rec >= 6 && (
                notas.segundoParcial >= 6 ||
                notas.segundoParcial1Rec >= 6 ||
                notas.segundoParcial2Rec >= 6
            ) ||
            notas.primerParcial2Rec >= 6 && (
                notas.segundoParcial >= 6 ||
                notas.segundoParcial1Rec >= 6 ||
                notas.segundoParcial2Rec >= 6
            )
        )
    ){strcpy(salidaSituacionAcademica, "regularizado");}
    else{strcpy(salidaSituacionAcademica, "no aprobado");}
}

void hacerInforme(int curso[MAXIMO_ALUMNOS][CANTIDAD_NOTAS], Alumno alumnosPorLegajo[], int cantidadAlumnos){
    //Creamos una copia del vector (ordenada por apellido)
    Alumno* alumnosPorApellido = ordenarAlumnosPorApellido(alumnosPorLegajo, cantidadAlumnos);
    //Empezamos la impresion del informe
    cout << "Orden\tApellido\tSituacion Academica" << endl; 
    //En el orden dado por los apellidos, mostramos el informe de cada alumno
    for (int i = 0; i < cantidadAlumnos; i++){
        //Mostramos el Orden, y apellido. La situacion academica es mas complicada
        char apellido[MAXIMO_NOMBRE];
        obtenerApellido(alumnosPorApellido[i].nombre, apellido);
        cout << i+1 << "\t" << apellido << "\t";
        //     orden           apellido
        char situactionAcademica[13];
        //Obtenemos las notas del alumno (para lo cual necesitamos saber su posicion en el vector ordenado por legajo)
        Notas notas = buscarNotas(curso, posicionPorLegajo(alumnosPorApellido[i], alumnosPorLegajo, cantidadAlumnos));
        obtenerSituacionAcademica(notas, situactionAcademica);
        cout << situactionAcademica << endl;
    }
    delete[] alumnosPorApellido;
}

void tests(){
    
    //Test de obtenerSituacionAcademica
    Notas notasPromocion = {8, 8, 0, 0, 0, 0, 8};
    Notas notasRegularizacion = {8, 5, 0, 6, 0, 0, 6};
    Notas notasDesaprobado = {10, 9, 0, 0, 0, 0, 4};
    char situacionAcademicaPromocion[13];
    char situacionAcademicaRegularizacion[13];
    char situacionAcademicaDesaprobado[13];
    obtenerSituacionAcademica(notasPromocion, situacionAcademicaPromocion);
    obtenerSituacionAcademica(notasRegularizacion, situacionAcademicaRegularizacion);
    obtenerSituacionAcademica(notasDesaprobado, situacionAcademicaDesaprobado);
    if (strcmp(situacionAcademicaPromocion, "promocionado") != 0 ||
        strcmp(situacionAcademicaRegularizacion, "regularizado") != 0 ||
        strcmp(situacionAcademicaDesaprobado, "no aprobado") != 0
    ){ cout << "Error en obtenerSituacionAcademica" << endl; }

    //Test de contarAlumnos
    Alumno alumnos[MAXIMO_ALUMNOS];
    for (int i = 0; i < MAXIMO_ALUMNOS; i++){
        if (i<20)
            alumnos[i].legajo = i;
        else
            alumnos[i].legajo = -1;
    }
    if (contarAlumnos(alumnos, MAXIMO_ALUMNOS) != 20){ cout << "Error en contarAlumnos" << endl; }

    //Test de apellido
    char nombre[MAXIMO_NOMBRE] = "Perez Juan";
    char apellido[MAXIMO_NOMBRE];
    obtenerApellido(nombre, apellido);
    if (strcmp(apellido, "Perez") != 0){ cout << "Error en apellido" << endl; }

    //Test completo
    srand(time(NULL));
    
    Alumno alumnosPorLegajo[MAXIMO_ALUMNOS];
    for (int i = 0; i < MAXIMO_ALUMNOS; i++){
        if (i<20){
            alumnosPorLegajo[i].legajo = i+1;
            char nombre[MAXIMO_NOMBRE];
            sprintf(nombre, "Apellido%d Juan", 20-i);
            strcpy(alumnosPorLegajo[i].nombre, nombre);
        }else{
            alumnosPorLegajo[i].legajo = -1;
        }
    }

    int curso[MAXIMO_ALUMNOS][CANTIDAD_NOTAS];

    for (int i = 0; i < 20; i++){
        for (int j = 0; j < CANTIDAD_NOTAS; j++){
            curso[i][j] = rand() % 11;
        }
        char apellido[MAXIMO_NOMBRE];
        obtenerApellido(alumnosPorLegajo[i].nombre, apellido);
        cout << "Apellido: " << apellido << endl;
        cout << "Notas: " << curso[i][0] << " " << curso[i][1] << " " << curso[i][2] << " " << curso[i][3] << " " << curso[i][4] << " " << curso[i][5] << " " << curso[i][6] << endl << endl;
    }

    hacerInforme(curso, alumnosPorLegajo, contarAlumnos(alumnosPorLegajo, MAXIMO_ALUMNOS));
}


/*
Punto extra:
La funcion devuelve la suma de todos los enteros en el arreglo, en main se declara el arreglo y se muestra por pantalla la suma
*/