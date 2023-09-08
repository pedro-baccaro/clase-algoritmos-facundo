#include <iostream>
#include <string>
#include <ctime> // Solo para tests
using namespace std;

const int MAXIMO_ALUMNOS = 60;

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
    string nombre;
    int legajo;
};

int contarAlumnos(Alumno alumnos[], int cantidadMaxima);  //Dado el vector de alumnos, y la longitud de este, devuelve cuantos alumnos contiene (el resto tiene -1 de legajo, lo cual se explica en main)
string apellido(string nombre); //Dado un nombre completo (string), devuelve solo la primera palabra (el apellido, un string)
Alumno* ordenarAlumnosPorNombre(Alumno alumnosPorLegajo[], int cantidadAlumnos); //Dado el vector de alumnos, y la cantidad de alumnos que contiene, devuelve un vector ordenado por apellidos
int posicionPorLegajo(Alumno alumno, Alumno alumnosPorLegajo[], int cantidadAlumnos); //Dado un alumno, y el vector de alumnos ordenado por legajo, devuelve la posicion del alumno en dicho vector
Notas buscarNotas(int curso[MAXIMO_ALUMNOS][7], int posicionCurso); //Busca las notas en la matriz del curso, se necesita saber cual de las filas corresponde al alumno (dado por su posicion en el vector ordenado por legajo)
string obtenerSituacionAcademica(Notas notas); //Dadas las notas del alumno, devuelve la situacion academica del mismo (promocionado, regularizado, no aprobado)
void hacerInforme(int curso[MAXIMO_ALUMNOS][7], Alumno alumnosPorLegajo[], int cantidadAlumnos);
void tests();


int main(){
    tests();
    
    int curso[MAXIMO_ALUMNOS][7]; //Asumimos que ya tiene las notas cargadas
    //Ademas asumimos que las filas del curso, que representan a cada alumno, se encuentran ordenadas segun el legajo del alumno
    
    Alumno alumnos[MAXIMO_ALUMNOS]; //Este sería el vector paralelo, asumimos que está cargado (y ordenado por legajo)
    //Además asumimos que luego del ultimo alumno, el resto tienen como legajo -1, para indicar que no hay mas alumnos

    // hacerInforme(curso, alumnos, contarAlumnos(alumnos, MAXIMO_ALUMNOS)); //Ya contamos la cantidad de alumnos que hay
    
    return 0;
}

int contarAlumnos(Alumno alumnos[], int cantidadMaxima){
    int i = 0;
    while(i < cantidadMaxima && alumnos[i].legajo != -1){
        i++;
    }
    return i;
}

string apellido(string nombre){
    string apellido = nombre.substr(0, nombre.find(" "));
    return apellido;
}

Alumno* ordenarAlumnosPorApellido(Alumno alumnosPorLegajo[], int cantidadAlumnos){
    Alumno* alumnosPorApellido = new Alumno[cantidadAlumnos];
    for (int i = 0; i < cantidadAlumnos; i++){
        alumnosPorApellido[i] = alumnosPorLegajo[i];
    }
    //bubble sort de los alumnos (por apellido)
    for (int i = 0; i < cantidadAlumnos; i++){
        for (int j = 0; j < cantidadAlumnos - 1; j++){
            string apellidoActual = apellido(alumnosPorApellido[j].nombre);
            string apellidoProximo = apellido(alumnosPorApellido[j+1].nombre);
            if (apellidoActual > apellidoProximo > 0){
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

Notas buscarNotas(int curso[MAXIMO_ALUMNOS][7], int posicionCurso){
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

string obtenerSituacionAcademica(Notas notas){
    string situacionAcademica;
    if (notas.trabajoPractico >= 8 && (
            notas.primerParcial >= 8 && notas.segundoParcial >= 8 ||
            notas.primerParcial >= 8 && notas.segundoParcial1Rec >= 8 ||
            notas.primerParcial1Rec >=8 && notas.segundoParcial >= 8
        )    
    ){situacionAcademica = "promocionado";}
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
    ){situacionAcademica = "regularizado";}
    else{situacionAcademica = "no aprobado";}
    return situacionAcademica;
}

void hacerInforme(int curso[MAXIMO_ALUMNOS][7], Alumno alumnosPorLegajo[], int cantidadAlumnos){
    //Creamos una copia del vector (ordenada por apellido)
    Alumno* alumnosPorApellido = ordenarAlumnosPorApellido(alumnosPorLegajo, cantidadAlumnos);
    //Empezamos la impresion del informe
    cout << "Orden\tApellido\tSituacion Academica" << endl; 
    //En el orden dado por los apellidos, mostramos el informe de cada alumno
    for (int i = 0; i < cantidadAlumnos; i++){
        //Mostramos el Orden, y apellido. La situacion academica es mas complicada
        cout << i+1 << "\t" << apellido(alumnosPorApellido[i].nombre) << "\t";
        //Obtenemos las notas del alumno (para lo cual necesitamos saber su posicion en el vector ordenado por legajo)
        Notas notas = buscarNotas(curso, posicionPorLegajo(alumnosPorApellido[i], alumnosPorLegajo, cantidadAlumnos));
        string situactionAcademica = obtenerSituacionAcademica(notas);
        cout << situactionAcademica << endl;
    }
    delete[] alumnosPorApellido;
}

void tests(){
    
    //Test de obtenerSituacionAcademica
    Notas notasPromocion = {8, 8, 0, 0, 0, 0, 8};
    Notas notasRegularizacion = {8, 5, 0, 6, 0, 0, 6};
    Notas notasDesaprobado = {10, 9, 0, 0, 0, 0, 4};
    if ((obtenerSituacionAcademica(notasPromocion) != "promocionado") || 
        (obtenerSituacionAcademica(notasRegularizacion) != "regularizado") || 
        (obtenerSituacionAcademica(notasDesaprobado) != "no aprobado")
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
    string nombre = "Perez Juan";
    if (apellido(nombre) != "Perez"){ cout << "Error en apellido" << endl; }

    //Test completo
    srand(time(NULL));
    
    Alumno alumnosPorLegajo[MAXIMO_ALUMNOS];
    for (int i = 0; i < MAXIMO_ALUMNOS; i++){
        if (i<20){
            alumnosPorLegajo[i].legajo = i+1;
            string nombre = "Apellido" + to_string(20-i) + " Juan";
            alumnosPorLegajo[i].nombre = nombre;
        }else{
            alumnosPorLegajo[i].legajo = -1;
        }
    }

    int curso[MAXIMO_ALUMNOS][7];

    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 7; j++){
            curso[i][j] = rand() % 11;
        }
        cout << "Apellido: " << apellido(alumnosPorLegajo[i].nombre) << endl;
        cout << "Notas: " << curso[i][0] << " " << curso[i][1] << " " << curso[i][2] << " " << curso[i][3] << " " << curso[i][4] << " " << curso[i][5] << " " << curso[i][6] << endl << endl;
    }

    hacerInforme(curso, alumnosPorLegajo, contarAlumnos(alumnosPorLegajo, MAXIMO_ALUMNOS));
}


/*
Punto extra:
La funcion devuelve la suma de todos los enteros en el arreglo, en main se declara el arreglo y se muestra por pantalla la suma
*/