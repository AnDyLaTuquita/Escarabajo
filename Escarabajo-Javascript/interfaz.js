//*********************************************************
//* Escarabajo                                            *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: Javascript                                  *
//*                                                       *
//* INTERFAZ                                              *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autor: Andrea Rosana Vellicce                         *
//*********************************************************

var out = null;// = document.getElementById('out');
var m_sNombre = "";
var m_nIdUsuario = 0;

window.onload = function() {
    out = document.getElementById('out'); 
    
    // Reacciona a los eventos del teclado
    function OnKeyDown(event) {
        var key = event.keyCode;

        if( canvas.style.visibility=="visible" &&
            (key==13 || key ==27) ){
            CerrarCanvas();
        }        
    }
    document.addEventListener('keydown', OnKeyDown, false);


    // Desserializa la base de datos
    DesSerializarBD();

    Login();
};

function Login()
{ 
    cls(); //limpia la pantalla       

    println("Bienvenidos al Graficador del<br>'FRACTAL ESCARABAJO DE MANDELBROT<br>");
    println("MENU");
    printlnURL("1. Iniciar Sesión", "ILogin()");
    printlnURL("2. Registrarse", "IRegistrarUsuario()");
    printlnURL("3. Salir", "Salir()");

    println("Escoja una opción");      
}


function ILogin()
{
    var sClave;

    cls(); //limpia la pantalla
    println("Iniciar Sesión<br>");    
    m_sNombre = prompt("Ingrese su nombre");
    sClave = prompt("Ingrese su contraseña");
    
    m_nIdUsuario = ValidarUsuario(m_sNombre, sClave);
    
    if (m_nIdUsuario==0) {

        println("<br>Usuario o contraseña no válida<br>");
        pausa("Login()");        
    } else {        
        InterfazPrincipal();
    }
}

function InterfazPrincipal()
{
   
    cls(); //limpia la pantalla

    println("Bienvenido " + m_sNombre + "<br>");
    println("Seleccione una opción:<br>");
    printlnURL("1. Graficar nuevo fractal", "GraficarFractal(true)");
    printlnURL("2. Graficar sus fractales favoritos", "InterfazPrincipal_GraficarFractal()");
    printlnURL("3. Cerrar sesión", "Salir()");

    println("Escoja una opción");  
}

function InterfazPrincipal_GraficarFractal()
{
    ListarFractales1();

}

function IRegistrarUsuario() 
{
    var sClave;	

    cls(); //limpia la pantalla
    println("Registro de Usuario<br>");
    m_sNombre = prompt("Ingrese su nombre");
    sClave = prompt("Ingrese su contraseña");

    var cOp = confirm("Guardar (Si 'S' o No 'N')");
    
    if (cOp){

        m_nIdUsuario = RegistrarUsuario(m_sNombre,sClave);
        InterfazPrincipal();	
    } else {
        Login();
    }

}

function GraficarFractal( bMostrarInstrucciones) {

    if ( bMostrarInstrucciones ) {
        
        cls();//limpia la pantalla
        println("INSTRUCCIONES:<br>");
        println("...A continuación se graficará en una nueva ventana el fractal del 'Escarabajo de Mandelbrot'");
        println("El Escarabajo es una imagen de zoom teoricamente 'infinito', ¡te atreves a encontrar los límites!...<br>");
        println("1. Use click izquierdo para acercar y click derecho para alejar el zoom<br>");
        println("2. Presione el BOTÓN para culminar y guardar su imagen actual en fractales favoritos<br>");

        

        println("¿Ha leido las instrucciones? (", false);
        printlnURL("Si", "GraficarFractal_Display()", false);
        println(" o ", false);
        printlnURL("No", "InterfazPrincipal()", false);
        println(")");


    }else {
        GraficarFractal_Display();
    }
}

function GraficarFractal2( dXmin, dXmax, dYmin, dYmax )
{  

    PlanoComplejo.xmin = dXmin;
    PlanoComplejo.xmax = dXmax;
    PlanoComplejo.ymin = dYmin;
    PlanoComplejo.ymax = dYmax;

    GraficarFractal(false);				
    
}

function GraficarFractal_Display(){
    Display();    
}

function GuardarFractal1() {

    var sNombreFractal;
    var sDescripcion;	

    cls();//limpia la pantalla

    var cOp = confirm("¿Desea guardar el fractal en favoritos?");   
    
    if (cOp){

        println("Guarda el fractal:");

        sNombreFractal = prompt("Ingrese el nombre del fractal:");

        sDescripcion = prompt("Ingrese una descripción para su fractal:");

        GuardarFractal(m_nIdUsuario, sNombreFractal, sDescripcion, PlanoComplejo.xmin, PlanoComplejo.xmax, PlanoComplejo.ymin, PlanoComplejo.ymax);

        println("<br>Su fractal ha sido guardado en la base de datos...<br>");    

    }

    pausa("InterfazPrincipal()");   

}


function ListarFractales1() {

    var vFractales = [];
    
    var mFractal = null;

    ListarFractales( m_nIdUsuario, vFractales);

    var i, nFractales = vFractales.length;

    cls(); //limpia la pantalla

    if (nFractales == 0) {

        println("No existen fractales favoritos, por favor cree uno nuevo con la opción 'Graficar nuevo fractal'");	
        mFractal = null;
    }
    else {

        for (i = 0; i < nFractales; i++) {
            mFractal = vFractales[i];            
            
            printlnURL( pad(i+1,2) + ". " + mFractal.nombreFractal, "GraficarFractal2(" +mFractal.xMin +","+mFractal.xMax+","+ mFractal.yMin+","+mFractal.yMax +  ")", false );
            println( " : '"+ mFractal.descripcion +  "'");				
        }
        
        println("<br>Escoge una opción");      
    }	

    pausa("InterfazPrincipal()");

    return mFractal;
}

function ListarFractales_Opcion(vFractales) {
    mFractal = vFractales.get(nOp - 1);	
}


function Salir()
{ 
    cls(); //limpia la pantalla       

    println("<br>Gracias por usar Escarabajo...");
    pausa("Login()"); 

    SerializarBD();
}


function println( texto, bImprimirLn=true ){
    out.innerHTML += texto     
    if(bImprimirLn )
        out.innerHTML +="<br>";
}

function printlnURL( texto, jsFuncionDestinoURL, bImprimirLn=true  ){
    
    println("<a onclick='" + jsFuncionDestinoURL + "' href='javascript:void(0);'>" + texto + "</a>", bImprimirLn);
}

function cls(){
    out.innerHTML = "";
}

function cls(){
    out.innerHTML = "";
}

function pausa( jsFuncionDestinoURL ){
    printlnURL("Presione AQUI para continuar . . .", jsFuncionDestinoURL );
}

function pad(num, size) {
    var s = num+"";
    while (s.length < size) s = "0" + s;
    return s;
}

