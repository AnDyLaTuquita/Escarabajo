#include "BDEscarabajo.h"
#include <iostream>



using namespace std; // espacio de trabajo por defecto


BDEscarabajo::BDEscarabajo()
{
	AbrirBD();
}


BDEscarabajo::~BDEscarabajo()
{
	sqlite3_close(db);
}

void BDEscarabajo::AbrirBD()
{
	//Abrir Base de Datos

	rc = sqlite3_open("BDEscarabajo.db", &db);
	if (rc)
	{
		cerr << "Error al abrir la base de datos SQLite3: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_close(db);
	}
	else
	{
		//cout << "BDEscarabajo.db abierta" << endl << endl;	
	}
}

void BDEscarabajo::CrearTablas()
{

	//Crear TablaUsuario
	cout << "Creando TablaUsuario ..." << endl;
	string sqlCreateTable = "CREATE TABLE TablaUsuario (idUsuario INTEGER PRIMARY KEY, nombreUsuario TEXT UNIQUE, contrasenia TEXT);";
	rc = sqlite3_exec(db, sqlCreateTable.c_str(), NULL, NULL, NULL);
	Mensaje(rc,"TablaUsuario");

	//Crear TablaFractal
	cout << "Creando TablaFractal ..." << endl;
	sqlCreateTable = "CREATE TABLE TablaFractal (idFractal INTEGER PRIMARY KEY, idUsuario INTEGER, nombreFractal TEXT, descripcion TEXT, xMin REAL, xMax REAL, yMin REAL, yMax REAL);";
	rc = sqlite3_exec(db, sqlCreateTable.c_str(), NULL, NULL, NULL);
	Mensaje(rc, "TablaFractal");

}

void BDEscarabajo::RegistrarUsuario(string nombre, string clave)
{
	sqlite3_stmt *stmt;

	sqlite3_prepare_v2(db,"INSERT INTO TablaUsuario VALUES(NULL, ?1, ?2);", -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, clave.c_str(), -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);

	if (rc != SQLITE_DONE)
	{
		cerr << "Error al ejecutar la sentencia SQLite3: " << sqlite3_errmsg(db) << endl << endl;
		//sqlite3_free(error);
	}
	else
	{
		//cout << "Los datos fueron guardados en TablaUsuario." << endl << endl;
	}

	sqlite3_finalize(stmt);

}

bool BDEscarabajo::ValidarUsuario(string& nombre, string clave, int& nIdUsuario)
{
	sqlite3_stmt *stmt;


	//Buscando Usuario y Contraseña...
	sqlite3_prepare_v2(db, "SELECT * FROM TablaUsuario WHERE nombreUsuario= ?1 AND contrasenia = ?2 ;", -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, clave.c_str(), -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);

	if (sqlite3_data_count(stmt) == 0)
	{
		//cerr << "Error: " << sqlite3_errmsg(db) << endl << endl;		
		//cout << "Usuario o contraseña no válida"  << endl << endl;
		
		sqlite3_finalize(stmt);
		return false;

	}
	else
	{
		// Recupera nIdUsuario
		nIdUsuario = sqlite3_column_int(stmt, 0);

		//cout << "Acceso exitoso." << endl;
		//cout << "Id de usuario: " << nIdUsuario << endl << endl;	
	}

	sqlite3_finalize(stmt);
	return true;	
}


void BDEscarabajo::GuardarFractal(int& nIdUsuario, string sNombre, string sDescripcion, double dXmin, double dXmax, double dYmin, double dYmax) {

	sqlite3_stmt *stmt;

	sqlite3_prepare_v2(db, "INSERT INTO TablaFractal VALUES(NULL, ?1, ?2, ?3, ?4, ?5, ?6, ?7 );", -1, &stmt, NULL);

	sqlite3_bind_int(stmt, 1, nIdUsuario);
	sqlite3_bind_text(stmt, 2, sNombre.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, sDescripcion.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_double(stmt, 4, dXmin);
	sqlite3_bind_double(stmt, 5, dXmax);
	sqlite3_bind_double(stmt, 6, dYmin);
	sqlite3_bind_double(stmt, 7, dYmax);


	rc = sqlite3_step(stmt);

	if (rc != SQLITE_DONE)
	{
		cerr << "Error al ejecutar la sentencia SQLite3: " << sqlite3_errmsg(db) << endl << endl;
	}
	else
	{
		//cout << "Los datos fueron guardados en TablaFractal." << endl << endl;
	}

	sqlite3_finalize(stmt);

}

void BDEscarabajo::ListarFractales(int & nIdUsuario, vector<FRACTAL>& vFractales){

	sqlite3_stmt *stmt;

	sqlite3_prepare_v2(db, "SELECT * FROM TablaFractal WHERE idUsuario= ?1;", -1, &stmt, NULL);

	sqlite3_bind_int(stmt, 1, nIdUsuario);	

	FRACTAL mFractal;

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {                                     
	
		mFractal.sNombre = std::string(reinterpret_cast<const char*>(
							sqlite3_column_text(stmt, 2)
							));

		mFractal.sDescripcion = std::string(reinterpret_cast<const char*>(
								sqlite3_column_text(stmt, 3)
								));

		mFractal.dXmin = sqlite3_column_double(stmt, 4);
		mFractal.dXmax = sqlite3_column_double(stmt, 5);
		mFractal.dYmin = sqlite3_column_double(stmt, 6);
		mFractal.dYmax = sqlite3_column_double(stmt, 7);
		
		vFractales.push_back(mFractal);
	}

	sqlite3_finalize(stmt);
}

void BDEscarabajo::Mensaje(int rc, string tabla)
{
	if (rc)
	{
		cerr << "Error al ejecutar la sentencia SQLite3: " << sqlite3_errmsg(db) << endl << endl;
	}
	else
	{
		cout << tabla << " creada." << endl << endl;
	}
}




