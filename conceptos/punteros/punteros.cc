#include <iostream>

using namespace std;

void agregar2(int* direccion){
    *direccion += 2;
}

int main(){
    
    // Primero algo básico de como funciona C (o en realidad, cualquier lenguaje de programación, ya que así funciona la memoria)
    int a = 123;  //Este entero, una v/ariable, se guarda en la memoria, pero la memoria tiene espacio para muuuchos enteros, entonces, ¿Cómo lo encontramos cuando lo necesitamos?
    cout << "El valor de a es: " << a << endl;
    cout << "---------------------------------------------" << endl << endl;
    // Cada variable tiene una dirección en memoria, como la direccion de tu casa o la direccion de email, pero en este caso es un numero.
    // En C, y C++, que nos dan mucha libertad con el manejo de memoria, podemos obtener la dirección usando el siguiente operador:
    cout << "La direccion de a es: " << &a << endl;  //El operador & devuelve la dirección de la variable a
    cout << "---------------------------------------------" << endl << endl;
    // Pero... si la dirección es un numero, podemos operar con ese numero?
    //Probemos:
    //int b = &a;
    //cout << "b = " << b << endl;
    
    // Dio error, entonces, &a no está devolviendo exactamente un entero, el compilador nos dice que es de tipo int*... ??QUE ES ESO??
    //Probemos con int*, a ver que pasa
    int* b = &a;
    cout << "b = " << b << endl;
    // Aaaaahi estaa! anduvo! Pero que es un int*?
    // Bueno, seguro ya te diste cuenta que es un puntero, pero que es un puntero?
    // Un puntero es una variable (en este caso b) que almacena la direccion de otra variable (en este caso a), pero para que sirve tener la direccion??
    cout << "---------------------------------------------" << endl << endl;
    //Bueno, para esto usamos el operador *, por eso se llama int* el tipo de dato en este caso, se usa así
    cout << "El valor de la variable ubicada en la direccion de memoria que almacena b (" << b << ") es: " << *b << endl;
    // Podemos cambiar el valor de a usando *b? Probemos:
    cout << "---------------------------------------------" << endl << endl;
    *b = 456;
    cout << "El valor de a es: " << a << endl;
    cout << "El valor de la variable ubicada en la direccion de memoria " << b << " es: " << *b << endl;	
    cout << "---------------------------------------------" << endl << endl;
    // Pero entonces, si tener la direccion de una variable nos permite cambiar su valor, que podemos hacer con eso? un ejemplo es pasar variables 'por referencia'
    agregar2(&a);
    cout << "El valor de a es: " << a << endl;
    //CUIDADO CON ESTO! A veces queremos que lo que sea que una funcion le hace a una variable no le pase a la variable, esto es solo cuando queremos cambiar la original
    cout << "---------------------------------------------" << endl << endl;
    // Otra cosa copada que podemos hacer, es ARITMETICA DE PUNTEROS, que suena feo pero es bastante basico
    int c = 5;
    int* f = &c;
    cout << "El valor de f es: " << f << endl;
    cout << "El valor de f+1 es: " << f+1 << endl;
    cout << "El valor de f+2 es: " << f+2 << endl; //Cada vez se agregan 4 bytes, cada direccion apunta a 1byte en memoria
    cout << "El valor de *f es: " << *f << endl;
    cout << "El valor de *(f+1) es: " << *(f+1) << endl; //Esto depende del contexto de la ejecucion, es un valor 'basura'
    cout << "El valor de *(f+2) es: " << *(f+2) << endl; //Esto tambien
    cout << "---------------------------------------------" << endl << endl;
    //Tecnicamente podemos leer toda la memoria con esto, hay malware que lo usa, pero la idea es no hacer eso jeje
    //La aritmetica de punteros es util cuando sabemos que varios valores son consecutivos en memoria, esto sucede coooooonnnn! arreglos.
    //Pero por ahora vamos con una ultima cosa:

    //Podemos tener un puntero a un puntero? SI! No sirve para muuuchas cosas pero lo enseño igual
    int* g = &c;
    int** h = &g;
    cout << "El valor de g es: " << g << endl;
    cout << "El valor de *g es: " << *g << endl;
    cout << "El valor de h es: " << h << endl;
    cout << "El valor de *h es: " << *h << endl;
    cout << "El valor de **h es: " << **h << endl;
    
    cout << "---------------------------------------------" << endl << endl;

    int z = 2;
    cout << "El valor de z es: " << *&z << endl;

    cout << "---------------------------------------------" << endl << endl;
    //Por ultimo, tambien se pueden hacer punteros a otros tipos de datos
    float d = 1.23;
    float* e = &d;
    
    char* i = "Hola mundo!";
    char** j = &i;

    //Tambien se pueden hacer punteros a archivos con el tipo FILE*
    FILE* archivo = fopen("punteros.txt", "w");
    //Hay varios tipos de usar fopen, son los siguientes:
    /*
    r: Abre un archivo de texto para lectura. El archivo debe existir.
    w: Abre un archivo de texto para escritura. Si el archivo no existe, se crea. Si el archivo existe, se sobreescribe.
    a: Abre un archivo de texto para escritura. Si el archivo no existe, se crea. Si el archivo existe, se agrega al final.
    r+: Abre un archivo de texto para lectura y escritura. El archivo debe existir.
    w+: Abre un archivo de texto para lectura y escritura. Si el archivo no existe, se crea. Si el archivo existe, se sobreescribe.
    a+: Abre un archivo de texto para lectura y escritura. Si el archivo no existe, se crea. Si el archivo existe, se agrega al final.
    Tambien se puede agregar b al final para archivos binarios, por ejemplo: rb, w+b, etc.
    */
    
   //Hay muchas formas de escribir a un archivo
    //La mas basica es con fprintf, que es como printf pero en un archivo
    fprintf(archivo, "Hola mundo!\n");
    //Tambien podemos usar fputc, que escribe un caracter en el archivo
    fputc('H', archivo);
    //O fwrite (esta es mas completa, con archivos binarios sirve para escribir structs, por ejemplo)
    char* texto = "Hola mundo!\n";
    fwrite(texto, sizeof(char), strlen(texto), archivo);

    //Hay que acordarse de punteros para arreglos, pero antes vamos a ver structs
    return 0;
}
