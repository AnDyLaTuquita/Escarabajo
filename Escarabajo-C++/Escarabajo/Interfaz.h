#pragma once
//*********************************************************
//* Escarabajo                                            *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: C++                                         *
//*                                                       *
//* INTERFAZ                                              *
//*                                                       *
//* Tecnología: Se usó el paradigma orientado a objetos   *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autor: Andrea Rosana Vellicce                         *
//*********************************************************


#include "BDEscarabajo.h"
#include "escarabajo.h"

class Interfaz
{
public:
	Interfaz();
	~Interfaz();

	void Login();
	void InterfazPrincipal();
private:
	void IRegistrarUsuario();	
	void ILogin();
	void GraficarFractal(bool bMostrarInstrucciones=true);
public:
	bool GuardarFractal();
	bool ListarFractales(FRACTAL & mFractal);

	static void pausa(bool bIgnorarBuffer=true); // Hace una pausa
	static void cls(); // Limpia la pantalla

public:
	bool m_bFractalGraficado;

private:	
	string m_sNombre;
	//string clave;
	int m_nIdUsuario;	
	CEscarabajo m_GraficadorFractal;
	BDEscarabajo bd;
};

