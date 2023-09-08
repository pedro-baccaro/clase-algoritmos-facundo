#include <iostream>
using namespace std;

struct Fecha{
    int dia;
    int mes;
    int anio;
};

struct Persona{
    string nombre;
    int edad;
    string dni;
    Fecha fechaNacimiento;

    void mostrar(){
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
        cout << "DNI: " << dni << endl;
        cout << "Fecha de nacimiento: " << fechaNacimiento.dia << "/" << fechaNacimiento.mes << "/" << fechaNacimiento.anio << endl;
    }
};

bool esMayorQue(Persona persona, Persona otraPersona){
    return persona.edad > otraPersona.edad;
}

int main(){
    //Como creamos personas?
    Persona persona1 = {"Juan", 20, "12345678", {1,1,2000}};
    //O sino
    Persona persona2;
    persona2.nombre = "Maria";
    persona2.edad = 40;
    persona2.dni = "13572468";
    persona2.fechaNacimiento.dia = 1;
    persona2.fechaNacimiento.mes = 1;
    persona2.fechaNacimiento.anio = 1980;
    
    //Podemos crear funciones que reciban personas:
    cout << "Es mayor que: " << esMayorQue(persona1, persona2) << endl;
    
    //Y con punteros?
    Persona* pPersona1 = &persona1;
    Persona* pPersona2 = &persona2;
    (*pPersona1).edad = 30;
    //o sino
    pPersona1->edad = 30;
    pPersona1->fechaNacimiento.anio = 1990; //Se puede encadenar de esta forma
    
    //Por ultimo, esto no siempre se usa (en C no existe, solo C++), podemos crear funciones en un struct
    persona1.mostrar();
    return 0;
}
