#pragma once
//*********************************************************
//* Escarabajo                                            *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: C++                                         *
//*                                                       *
//* GRAFICADOR                                            *
//*                                                       *
//* Tecnología: OpenGL                                    * 
//* Se usó el paradigma orientado a objetos               *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autor: Andrea Rosana Vellicce                         *
//*********************************************************

class CEscarabajo
{
public:
	struct PLANOCOMPLEJO {
		double xmin;
		double xmax;
		double ymin;
		double ymax;
	};
public:
	CEscarabajo();
	~CEscarabajo();	

	void Mandelbrot();
	void Zoom(double x1, double y1, double x2, double y2);
	void Draw(void);	
	
	// Paradigma orientado a eventos
	void OnMouseClick(int nButton, int nState, int nMousex, int nMousey);
	void OnKeyPress(unsigned char key, int x, int);

	void Display();

	
private:
	void setupCallback();

public:
	// Parametros de diagramado
	unsigned int nAncho;
	unsigned int nAlto;
	double dDIVERGE;   //valor de divergencia
	unsigned int nITERMAX; //iteracion maxima

	// Paleta Grafica del fractal
	unsigned int nPaletaR;
	unsigned int nPaletaG;
	unsigned int nPaletaB;

	PLANOCOMPLEJO PlanoComplejo;

private:
	int m_nIdWindow;
};

