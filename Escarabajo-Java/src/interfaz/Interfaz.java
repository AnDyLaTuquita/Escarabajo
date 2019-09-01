//*********************************************************
//* Escarabajo                                            *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: JAVA                                        *
//*                                                       *
//* INTERFAZ                                              *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autor: Andrea Rosana Vellicce                         *
//*********************************************************

package interfaz;
import cescarabajo.*;
import bdescarabajo.*;

import java.util.Scanner; // Usado para pausa()
import java.util.Vector;
import java.io.Console;

public class Interfaz { 

	private int m_nIdUsuario;    
	private String m_sNombre;
	private CEscarabajo m_GraficadorFractal;
	private BDEscarabajo m_bd;
	
	Scanner m_scan = new Scanner(System.in);

    public Interfaz(){
		m_nIdUsuario = 0; 
		m_GraficadorFractal = new CEscarabajo();
		m_bd = new BDEscarabajo();
	}
	
	public void Login()
	{
		while(true) {
			cls(); //limpia la pantalla

			System.out.println("Bienvenidos al Graficador del\n'FRACTAL ESCARABAJO DE MANDELBROT'\n");

			System.out.println("MENU");
			System.out.println("1. Iniciar Sesión");
			System.out.println("2. Registrarse");
			System.out.println("3. Salir");

			System.out.print("Escoja una opción -> ");
			String cOp = m_scan.next();
			
			switch (cOp)
			{
			case "1": 
				ILogin(); 		
				return;
				//break;
			case "2": 
				IRegistrarUsuario();			
				return;
				//break;		
			case "3":	
				m_bd.Cerrar();
				return;
				//break;		
			}

		}
	}

	
	private void InterfazPrincipal()
	{
		while(true) {

			cls(); //limpia la pantalla

			System.out.println("Bienvenido " + m_sNombre + "\n");
			System.out.println("Seleccione una opción:\n");
			System.out.println("1. Graficar nuevo fractal");
			System.out.println("2. Graficar sus fractales favoritos");
			System.out.println("3. Cerrar sesión");

			System.out.print("Escoja una opción -> ");
			String cOp = m_scan.next();

			switch (cOp)
			{

			case "1":
				GraficarFractal(true);
				return;							
			case "2": {
				
				FRACTAL mFractal = ListarFractales();

				if (mFractal!=null) {

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

			}
			case "3": {
				m_bd.Cerrar();
				return;			
			}	
			}
		}

	}

	private void ILogin()
	{
		String sClave;

		cls(); //limpia la pantalla
		System.out.println("Iniciar Sesión\n");
		System.out.print("Ingrese su nombre: ");
		m_sNombre = m_scan.next();		
		System.out.print("Ingrese su contraseña: ");
		sClave = m_scan.next();		
		
		m_nIdUsuario = m_bd.ValidarUsuario(m_sNombre, sClave);
		
		if (m_nIdUsuario==0) {

			System.out.println("\nUsuario o contraseña no válida\n");;
			pausa();
			Login();
		} else {
			//cout << "Acceso exitoso." << endl;
			//cout << "Id de usuario: " << m_nIdUsuario << endl << endl;	
			InterfazPrincipal();
		}
	}

	
	private void IRegistrarUsuario() 
	{
		String sClave;	

		cls(); //limpia la pantalla
		System.out.println("Registro de Usuario\n");
		System.out.print("Ingrese su nombre: ");
		m_sNombre = m_scan.next();		
		System.out.print("Ingrese su contraseña: ");
		sClave = m_scan.next();

		System.out.print("Guardar (Si 'S' o No 'N')-> ");
		char cOp = m_scan.next().charAt(0);
	
		if (cOp =='S' || cOp =='s'){

			m_nIdUsuario = m_bd.RegistrarUsuario(m_sNombre,sClave);
			InterfazPrincipal();	
		} else {
			Login();
		}

	}

	private void GraficarFractal(Boolean bMostrarInstrucciones) {

		if ( bMostrarInstrucciones ) {
			
			cls();//limpia la pantalla
			System.out.println("INSTRUCCIONES:\n");
			System.out.println("...A continuación se graficará en una nueva ventana el fractal del 'Escarabajo de Mandelbrot'");
			System.out.println("El Escarabajo es una imagen de zoom teoricamente 'infinito', ¡te atreves a encontrar los límites!...\n");
			System.out.println("1. Use click izquierdo para acercar y click derecho para alejar el zoom\n");
			System.out.println("2. Presione la tecla ENTER o ESC para culminar y guardar su imagen actual en fractales favoritos\n");
	
			System.out.print("¿Ha leido las instrucciones? (Si 'S' o No 'N')-> ");
			char cOp = m_scan.next().charAt(0);
	
			if (cOp =='S' || cOp =='s'){
				//m_bFractalGraficado = true;
				m_GraficadorFractal.Display();
				GuardarFractal();
				Salir();
			}
	
		}else {
			//m_bFractalGraficado = true;
			m_GraficadorFractal.Display();
			GuardarFractal();
			Salir();
		}
	}

	
	private Boolean GuardarFractal() {

		String sNombreFractal;
		String sDescripcion;	

		cls();//limpia la pantalla

		System.out.print("¿Desea guardar el fractal en favoritos? (Si 'S' o No 'N')-> ");
		char cOp = m_scan.next().charAt(0);
	
		if (cOp =='S' || cOp =='s'){

			System.out.println("Guarda el fractal:");

			System.out.print("Ingrese el nombre del fractal: ");
			sNombreFractal = m_scan.next();

			System.out.print("Ingrese una descripción para su fractal: ");
			sDescripcion = m_scan.next();

			m_bd.GuardarFractal(m_nIdUsuario, sNombreFractal, sDescripcion, m_GraficadorFractal.PlanoComplejo.xmin, m_GraficadorFractal.PlanoComplejo.xmax, m_GraficadorFractal.PlanoComplejo.ymin, m_GraficadorFractal.PlanoComplejo.ymax);

			System.out.println("\nSu fractal ha sido guardado en la base de datos...\n");

			pausa();

			return true;
		}

		return false;

	}

	private FRACTAL ListarFractales() {

		//Boolean bRet = true;
		int nOp;		
	
		Vector<FRACTAL> vFractales = new Vector<FRACTAL>();
		FRACTAL mFractal = null;
	
		m_bd.ListarFractales( m_nIdUsuario, vFractales);
	
		int i, nFractales = vFractales.size();
	
		cls(); //limpia la pantalla
	
		if (nFractales == 0) {
	
			System.out.println("No existen fractales favoritos, por favor cree uno nuevo con la opción 'Graficar nuevo fractal'");	
			mFractal = null;
		}
		else {
	
			for (i = 0; i < nFractales; i++) {
				mFractal = vFractales.get(i);
				
				String sNumero = String.format("%02d", i+1);
				System.out.println( sNumero + ". " + mFractal.sNombre +" : '"+ mFractal.sDescripcion +  "'" );				
			}
	
			System.out.print("Escoge una opción -> ");
			nOp = SuperParse(m_scan.next());	
	
			if ( 1 > nOp || nOp > vFractales.size() ) {
				System.out.println("La opción seleccionada no existe!");							
				mFractal = null;
			}else {			
				mFractal = vFractales.get(nOp - 1);		
			}
	
		}	
	
		pausa();
	
		return mFractal;
	}


	private void Salir() {
		cls();
		System.out.println("\nGracias por usar Escarabajo...");
		pausa();
		m_bd.Cerrar();
		System.exit(0);
	}
	
	private void pausa()
	{		
		Console c = System.console();
		if (c != null) {			
			c.format("Presione ENTER para continuar . . .");
			c.readLine();
		}
	}

	private void cls()
	{	
		// Compatible con Windows, Linux y Mac
		try { 
			if (System.getProperty("os.name").contains("Windows"))
				new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor(); 
			else 
				Runtime.getRuntime().exec("clear"); 
		}catch (final Exception ex){
		}
	}

	// Valida si el string es transformable a entero en caso contrario devuelve cero
	public static int  SuperParse(String input){
		try{			
			return Integer.parseInt(input);
		}catch(NumberFormatException  e){
			return 0;
		}
	}


}