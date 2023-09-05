#define PRIMER_PARCIAL 0
#define SEGUNDO_PARCIAL 1
#define PRIMER_PARCIAL_1_R 2
#define SEGUNDO_PARCIAL_1_R 3
#define PRIMER_PARCIAL_2_R 4
#define SEGUNDO_PARCIAL_2_R 5
#define TRABAJO_PRACTICO 6

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h> 
#include <time.h>
using namespace std;

struct Alumno{
    string nombre;
    int legajo;
};


int contarAlumnos(Alumno alumnos[], const int cantidadMaxima){
    int i = 0;
    while(i < cantidadMaxima && alumnos[i].legajo != -1){
        i++;
    }
    return i;
}

string apellido(string nombre){
    int i = 0;
    while(nombre[i] != ','){
        i++;
    }
    return nombre.substr(0, i);
}

//funcion que ordena un vector de alumnos por nombre (bubble sort). Devuelve un puntero al primer elemento del vector ordenado
Alumno* ordenarAlumnosPorNombre(Alumno alumnosPorLegajo[], const int cantidadAlumnos){
    Alumno* alumnosPorNombre = new Alumno[cantidadAlumnos];
    for (int i = 0; i < cantidadAlumnos; i++){
        alumnosPorNombre[i] = alumnosPorLegajo[i];
    }
    for (int i = 0; i < cantidadAlumnos; i++){
        for (int j = 0; j < cantidadAlumnos - i - 1; j++){
            if (apellido(alumnosPorNombre[j].nombre) > apellido(alumnosPorNombre[j+1].nombre)){
                Alumno aux = alumnosPorNombre[j];
                alumnosPorNombre[j] = alumnosPorNombre[j+1];
                alumnosPorNombre[j+1] = aux;
            }
        }
    }
    return alumnosPorNombre;
}

int posicionPorLegajo(Alumno alumno, Alumno alumnosPorLegajo[], const int cantidadAlumnos){
    int i = 0;
    while(i < cantidadAlumnos && alumno.legajo != alumnosPorLegajo[i].legajo){
        i++;
    }
    return i;
}

int* buscarNotas(int curso[60][7], int posicionCurso){
    int* notas = new int[7];
    for (int i = 0; i < 7; i++){
        notas[i] = curso[posicionCurso][i];
    }
    return notas;
}

void hacerInforme(int curso[60][7], Alumno alumnosPorLegajo[], int cantidadAlumnos){
    //Ordenamos el vector de alumnos por nombre y apellido
    Alumno* alumnosPorNombre = ordenarAlumnosPorNombre(alumnosPorLegajo, cantidadAlumnos);
    
    //Empezamos a imprimir el informe
    cout << "Orden\tApellido\tSituacion Academica" << endl; 
    
    //Recorremos el vector de alumnos por nombre
    for (int i = 0; i < cantidadAlumnos; i++){
        //Buscamos la posicion del alumno en el vector de alumnos por legajo
        cout << i+1 << "\t" << apellido(alumnosPorNombre[i].nombre) << "\t";
        int posicionEnCurso = posicionPorLegajo(alumnosPorNombre[i], alumnosPorLegajo, cantidadAlumnos);
        int* notas = buscarNotas(curso, posicionEnCurso);
        if (notas[TRABAJO_PRACTICO] >= 8 && (
                notas[PRIMER_PARCIAL] >= 8 && notas[SEGUNDO_PARCIAL] >= 8 ||
                notas[PRIMER_PARCIAL_1_R] >= 8 && notas[SEGUNDO_PARCIAL] >= 8 ||
                notas[PRIMER_PARCIAL] >= 8 && notas[SEGUNDO_PARCIAL_1_R] >= 8
                )
        ){ cout << "promocionado" << endl; }
        else if (notas[TRABAJO_PRACTICO] >= 6 && (
                notas[PRIMER_PARCIAL] >= 6 && (
                    notas[SEGUNDO_PARCIAL] >= 6 ||
                    notas[SEGUNDO_PARCIAL_1_R] >= 6 ||
                    notas[SEGUNDO_PARCIAL_2_R] >= 6
                ) ||
                notas[PRIMER_PARCIAL_1_R] >= 6 && (
                    notas[SEGUNDO_PARCIAL] >= 6 ||
                    notas[SEGUNDO_PARCIAL_1_R] >= 6 ||
                    notas[SEGUNDO_PARCIAL_2_R] >= 6
                ) ||
                notas[PRIMER_PARCIAL_2_R] >= 6 && (
                    notas[SEGUNDO_PARCIAL] >= 6 ||
                    notas[SEGUNDO_PARCIAL_1_R] >= 6 ||
                    notas[SEGUNDO_PARCIAL_2_R] >= 6
                )
            )
        ){ cout << "regularizado" << endl; }
        else{ cout << "no aprobado" << endl; }
    }
}

int main(){
    srand (time(NULL));
    int curso[60][7]; //Asumimos que ya tiene las notas cargadas
    //Ademas asumimos que las filas del curso, que representan a cada alumno, se encuentran ordenadas segun el legajo del alumno
    
    Alumno* alumnos = new Alumno[60]; //Este sería el vector paralelo, asumimos que está cargado (y ordenado por legajo)
    //Además asumimos que luego del ultimo alumno, el resto tienen como legajo -1, para indicar que no hay mas alumnos
    cout << "aaa" << endl;
    //tests
    for (int i = 0; i < 60; i++){
        if (i<20){
            ostringstream oss;
            oss << "Perez" << 20-i << ", Juan";
            Alumno alumno = {oss.str(), i};
            alumnos[i] = alumno;
        }else{
            Alumno alumno = {"", -1};
            alumnos[i] = alumno;
        }
    }
    cout << "aaa" << endl;
    for (int i = 0; i < 21; i++){
        for (int j = 0; j < 7; j++){
            curso[i][j] = rand() % 11;
        }
        cout << "Alumno:\t" << alumnos[i].nombre << endl;
        cout << "Notas:\t" << curso[i][0] << "\t" << curso[i][1] << "\t" << curso[i][2] << "\t" << curso[i][3] << "\t" << curso[i][4] << "\t" << curso[i][5] << "\t" << curso[i][6] << endl;
    }
    int cantidadAlumnos = contarAlumnos(alumnos, 60);
    
    hacerInforme(curso, alumnos, cantidadAlumnos);
    
    return 0;
}
