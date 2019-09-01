//*********************************************************
//* Escarabajo                                            *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: C++                                         *
//*                                                       *
//* MAIN                                                  *
//*                                                       *
//* Libreria gráfica: OpenGL                              * 
//* Base de datos: sqlite                                 *
//* Se uso el paradigma por eventos de OpenGL             *
//* el paradigma orientado a objetos y                    *
//* el paradigma orientado a eventos de C++ (atexit)      *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autor: Andrea Rosana Vellicce                         *
//*********************************************************

#include <iostream>
#include <GL/glut.h>
#include "Interfaz.h"

using namespace std; // espacio de trabajo por defecto

Interfaz interfaz;

// Paradigma por eventos usando atexit
// Esta función es llamada al finalizar el programa
void GuardarFractal() {

	bool bIgnorar = true;

	if (interfaz.m_bFractalGraficado) {
		bIgnorar = interfaz.GuardarFractal()==false;		
	}

	interfaz.cls();
	cout << endl << "Gracias por usar Escarabajo..." << endl << endl;
	interfaz.pausa(bIgnorar);	
}


int main(int argc, char* argv[]) {
	
	setlocale(LC_ALL, "");

	atexit(GuardarFractal);

	glutInit(&argc, argv);

	interfaz.Login();	
	
	return 0;
}