#include "Interfaz.h"
#include "BDEscarabajo.h"
#include <iostream>
#include <iomanip>
#include "Escarabajo.h"
#include "BDEscarabajo.h"
#include "Interfaz.h"

using namespace std; // espacio de trabajo por defecto

Interfaz::Interfaz()
{
	m_nIdUsuario = 0;
	m_bFractalGraficado = false;
}


Interfaz::~Interfaz()
{
}

void Interfaz::Login()
{
	do {
		cls(); //limpia la pantalla

		cout << "Bienvenidos al Graficador del" << endl << "'FRACTAL ESCARABAJO DE MANDELBROT'" << endl << endl;
		cout << "MENU" << endl;
		cout << "1. Iniciar Sesión" << endl;
		cout << "2. Registrarse" << endl;
		cout << "3. Salir" << endl;

		cout << "Escoja una opción -> ";
		//cin >> op;
		char cOp;
		cin.get(cOp);

		switch (cOp)
		{
		case '1': 
			ILogin(); 		
			return;
			break;// cout << "Usted escogio 1" << endl; break;
		case '2': 
			IRegistrarUsuario();			
			return;
			break;		
		case '3':
			//cout << "Saliendo del menú" << endl; 
			return;
			break;		
		}

	} while (1);
		
	return;
}


void Interfaz::InterfazPrincipal()
{
	do {

		cls(); //limpia la pantalla

		cout << "Bienvenido " << m_sNombre << endl << endl;
		cout << "Seleccione una opción:" << endl << endl;
		cout << "1. Graficar nuevo fractal" << endl;
		cout << "2. Graficar sus fractales favoritos" << endl;
		cout << "3. Cerrar sesión" << endl;

		cout << "Escoja una opción -> ";
		char cOp;
		cin.get(cOp);

		switch (cOp)
		{

		case '1':
			GraficarFractal();
			return;			
			break;
		case '2': {
			FRACTAL mFractal;
			if (ListarFractales(mFractal)) {

				m_GraficadorFractal.PlanoComplejo.xmin = mFractal.dXmin;
				m_GraficadorFractal.PlanoComplejo.xmax = mFractal.dXmax;
				m_GraficadorFractal.PlanoComplejo.ymin = mFractal.dYmin;
				m_GraficadorFractal.PlanoComplejo.ymax = mFractal.dYmax;

				GraficarFractal(false);				
			}
			else {
				break;
			}

			return;

		}break;
		case '3': {
			return;			
		}break;		
		}
	} while (1);

}



void Interfaz::ILogin()
{
	string sClave;

	cls(); //limpia la pantalla
	cout << "Iniciar Sesión" << endl << endl;
	cout << "Ingrese su nombre: ";
	cin >> m_sNombre;
	cout << "Ingrese su contraseña: ";
	cin >> sClave;


	if (bd.ValidarUsuario(m_sNombre, sClave, m_nIdUsuario)==false) {

		cout << endl << "Usuario o contraseña no válida" << endl << endl;
		pausa();
		Login();
	} else {
		//cout << "Acceso exitoso." << endl;
		//cout << "Id de usuario: " << m_nIdUsuario << endl << endl;	
		InterfazPrincipal();
	}
}

void Interfaz::IRegistrarUsuario() 
{
	string sClave;
	char cOp;

	cls(); //limpia la pantalla
	cout << "Registro de Usuario" << endl << endl;
	cout << "Ingrese su nombre: ";
	cin >> m_sNombre;
	cout << "Ingrese una contraseña: ";
	cin >> sClave;

	cout << "Guardar (Si 'S' o No 'N')-> ";
	cin >> cOp;

	if (cOp =='S' || cOp =='s'){

		bd.RegistrarUsuario(m_sNombre,sClave);
		InterfazPrincipal();	
	} else {

		Login();
	}

}

void Interfaz::GraficarFractal(bool bMostrarInstrucciones) {

	if ( bMostrarInstrucciones ) {
		char cOp;

		cls();//limpia la pantalla
		cout << "INSTRUCCIONES: " << endl << endl;
		cout << "...A continuación se graficará en una nueva ventana el fractal del 'Escarabajo de Mandelbrot'" << endl;
		cout << "El Escarabajo es una imagen de zoom teoricamente 'infinito', ¡te atreves a encontrar los límites!..." << endl << endl;
		cout << "1. Use click izquierdo para acercar y click derecho para alejar el zoom" << endl << endl;
		cout << "2. Presione la tecla ENTER o ESC para culminar y guardar su imagen actual en fractales favoritos" << endl << endl;

		cout << "¿Ha leido las instrucciones? (Si 'S' o No 'N')-> ";
		cin >> cOp;

		if (cOp == 'S' || cOp == 's') {
			m_bFractalGraficado = true;
			m_GraficadorFractal.Display();
		}

	}else {
		m_bFractalGraficado = true;
		m_GraficadorFractal.Display();
	}
}


bool Interfaz::GuardarFractal() {

	string sNombreFractal;
	string sDescripcion;
	char cOp;

	cls();//limpia la pantalla

	cout << "¿Desea guardar el fractal en favoritos? (Si 'S' o No 'N')-> ";
	cin >> cOp;

	if (cOp == 'S' || cOp == 's') {

		cout << "Guarda el fractal: " << endl;

		cin.clear();
		cin.ignore(10, '\n');

		cout << "Ingrese el nombre del fractal: ";
		std::getline(std::cin, sNombreFractal); // Ingreso de string que permite usar espacios	

		cout << endl << "Ingrese una descripción para su fractal: ";
		std::getline(std::cin, sDescripcion); // Ingreso de string que permite usar espacios

		bd.GuardarFractal(m_nIdUsuario, sNombreFractal, sDescripcion, m_GraficadorFractal.PlanoComplejo.xmin, m_GraficadorFractal.PlanoComplejo.xmax, m_GraficadorFractal.PlanoComplejo.ymin, m_GraficadorFractal.PlanoComplejo.ymax);

		cout << endl << "Su fractal ha sido guardado en la base de datos..." << endl << endl;

		pausa(false);

		return true;
	}

	return false;

}

bool Interfaz::ListarFractales(FRACTAL& mFractal) {

	int nOp;
	bool bRet = true;
	string sNombreFractal;
	string sDescripcion;

	vector<FRACTAL> vFractales;

	bd.ListarFractales( m_nIdUsuario, vFractales);

	int i, nFractales = vFractales.size();

	cls(); //limpia la pantalla

	if (nFractales == 0) {

		cout << "No existen fractales favoritos, por favor cree uno nuevo con la opción 'Graficar nuevo fractal'"<<endl;

		bRet = false;
	}
	else {

		for (i = 0; i < nFractales; i++) {
			FRACTAL& mFractal = vFractales.at(i);

			cout << std::setfill('0') << std::setw(2) << i + 1 << ". " << mFractal.sNombre << " : '" << mFractal.sDescripcion << "'" << endl;
		}

		cout << "Escoge una opción -> ";
		cin >>nOp;				

		if (cin.fail() || 1 > nOp || nOp > int(vFractales.size()) ) {
			cout << "La opción seleccionada no existe!";			
			bRet = false;
			cin.clear();
		}else {			
			mFractal = vFractales.at(nOp - 1);		
		}

	}	

	pausa();

	return bRet;
}

void Interfaz::pausa( bool bIgnorarBuffer )
{
	if(bIgnorarBuffer )
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
	cout << endl << "Presione ENTER para continuar . . .";
	std::cin.get();
}

void Interfaz::cls()
{
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}


