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

int main(){
    
    // Seguro arreglos te lo explicaron antes que punteros, ya que no tiene tanto sentido hacerlo al reves, pero nos va a ser útil la aritmetica de punteros
    // Un ejemplo de arreglo es:
    int arreglo[5] = {1,2,3,4,5};
    //Tambien lo podemos definir como
    //                int arreglo[] = {1,2,3,4,5};
    //Seguramente ya sepas que podemos acceder a los contenidos de un arreglo así:
    cout << "El valor de arreglo[0] es: " << arreglo[0] << endl;
    cout << "El valor de arreglo[1] es: " << arreglo[1] << endl;
    // ...
    // Y que si nos pasamos:
    cout << "El valor de arreglo[5] es: " << arreglo[5] << endl;
    cout << "El valor de arreglo[6] es: " << arreglo[6] << endl;
    
    cout << "---------------------------------------------" << endl << endl;
    
    //Esto se parece a los valores basura que encontramos con los punteros... vamos a hacer algo:
    cout << "El valor de *arreglo es: " << *arreglo << endl;
    //EH!! ERA UN PUNTERO! IMPOSTOR!
    cout << "El valor de *(arreglo+1) es: " << *(arreglo+1) << endl;
    cout << "El valor de *(arreglo+2) es: " << *(arreglo+2) << endl;
    //...

    cout << "---------------------------------------------" << endl << endl;
    // Y si hacemos esto?

    Persona persona1 = {"Juan", 20, "12345678", {1,1,2000}};
    Persona persona2 = {"Pedro", 30, "87654321", {1,1,1990}};
    Persona persona3 = {"Maria", 40, "13572468", {1,1,1980}};
    Persona amigos[3] = {persona1, persona2, persona3};
    (*amigos).mostrar();
    //Lo mismo que
    amigos[0].mostrar();

    return 0;
}
