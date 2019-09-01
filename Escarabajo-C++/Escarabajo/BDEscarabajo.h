#pragma once
//*********************************************************
//* Escarabajo                                            *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: C++                                         *
//*                                                       *
//* BASE DE DATOS                                         *
//*                                                       *
//* Tecnología: Sqlite                                    * 
//* Se usó el paradigma orientado a objetos               *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autor: Andrea Rosana Vellicce                         *
//*********************************************************

#include <string>
#include <vector>
#include "sqlite\sqlite3.h"
using std::string;
using std::vector;

struct FRACTAL {
	string sNombre;
	string sDescripcion;
	double dXmin;
	double dXmax;
	double dYmin;
	double dYmax;
};

class BDEscarabajo
{
public:
	BDEscarabajo();
	~BDEscarabajo();

	void AbrirBD();
	void CrearTablas();
	void RegistrarUsuario(string nombre, string clave);
	bool ValidarUsuario(string& nombre, string clave, int & nIdUsuario);	
	void GuardarFractal(int & nIdUsuario, string sNombre, string sDescripcion, double dXmin, double dXmax, double dYmin, double dYmax);

	void ListarFractales(int & nIdUsuario, vector<FRACTAL>& vFractales );

private:
	void Mensaje(int rc, string tabla);	
	
private:
	int rc;	
	sqlite3 *db;
};

