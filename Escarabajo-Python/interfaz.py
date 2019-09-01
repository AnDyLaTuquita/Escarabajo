#########################################################
# Escarabajo                                            #
# Diagrama el Fractal  del "Escarabajo de Mandelbrot"   #
# Lenguaje: Python                                      #
#                                                       #
# INTERFAZ                                              #
#                                                       #
# Tecnología: Se usa paradigma funcional                #
#                                                       #
# Fecha: 05-Agosto-2019                                 #
# Autor: Andrea Rosana Vellicce                         #
#########################################################

#import bdescarabajo
from bdescarabajo import *
from Escarabajo import *

# para portabilidad de código fuente en Python 2/3 y
# múltiples sistemas operativos
import os  # os.system
import six  # six.PY2 - Version de Python
import sys  # exit - salir del programa

endl = "\n"

# Variables globales
m_bFractalGraficado = False
m_sNombre = None
m_nIdUsuario = 0
m_GraficadorFractal = CEscarabajo()
bd = BDEscarabajo()


# Limpia la pantalla en diferentes plataformas
def cls():
    # cls en windows,  clear en linux/mac
    os.system('cls' if os.name == 'nt' else 'clear')


def pausa():
    if six.PY2:
        raw_input("Presione ENTER para continuar . . .")
    else:
        input("Presione ENTER para continuar . . .")


def Login():
    while 1:
        cls()  # limpia la pantalla
        print("Bienvenidos al Graficador del" + endl +
              "'FRACTAL ESCARABAJO DE MANDELBROT'" + endl)
        print("MENU")
        print("1. Iniciar Sesión")
        print("2. Registrarse")
        print("3. Salir")

        cOp = input("Escoja una opción -> ")

        if(cOp == "1"):
            ILogin()
            return
        elif(cOp == "2"):
            IRegistrarUsuario()
            return
        elif(cOp == "3"):
            return


def InterfazPrincipal():

    while 1:

        cls()  # limpia la pantalla
        print("Bienvenido " + m_sNombre + endl)
        print("Seleccione una opción:" + endl)
        print("1. Graficar nuevo fractal")
        print("2. Graficar sus fractales favoritos")
        print("3. Cerrar sesión")

        cOp = input("Escoja una opción -> ")

        if(cOp == "1"):
            GraficarFractal()
            return False
        elif(cOp == "2"):
            mFractal = ListarFractales()

            if ( mFractal!=None ):

                m_GraficadorFractal.PlanoComplejo.xmin = mFractal.dXmin
                m_GraficadorFractal.PlanoComplejo.xmax = mFractal.dXmax
                m_GraficadorFractal.PlanoComplejo.ymin = mFractal.dYmin
                m_GraficadorFractal.PlanoComplejo.ymax = mFractal.dYmax

                GraficarFractal(False)
                return False

        elif(cOp == "3"):    
	        return True
    
    return True


def ILogin():

    global m_sNombre	
    global m_nIdUsuario

    cls()  # limpia la pantalla
    print("Iniciar Sesión" + endl)
    m_sNombre = input("Ingrese su nombre: ")
    sClave = input("Ingrese su contraseña: ")
	
    m_nIdUsuario = bd.ValidarUsuario(m_sNombre, sClave, m_nIdUsuario)

    if ( m_nIdUsuario==0):

        print(endl + "Usuario o contraseña no válida" + endl)
        pausa()
        Login()
    else:
        InterfazPrincipal()


def IRegistrarUsuario():

    global m_sNombre
    global m_nIdUsuario

    cls()  # limpia la pantalla
    print("Registro de Usuario" + endl)
    m_sNombre = input("Ingrese su nombre: ")
    sClave = input("Ingrese su contraseña: ")

    cOp = input("Guardar (Si 'S' o No 'N')-> ")

    if (cOp == "S" or cOp == "s"):

        m_nIdUsuario = bd.RegistrarUsuario(m_sNombre, sClave)
        InterfazPrincipal()
    else:
        Login()


def GraficarFractal(bMostrarInstrucciones=True):

    if (bMostrarInstrucciones):

        cls()  # limpia la pantalla
        print("INSTRUCCIONES: " + endl)
        print("...A continuación se graficará en una nueva ventana el fractal del 'Escarabajo de Mandelbrot'")
        print("El Escarabajo es una imagen de zoom teoricamente 'infinito', ¡te atreves a encontrar los límites!..." + endl)
        print("1. Use click izquierdo para acercar y click derecho para alejar el zoom" + endl)
        print("2. Presione la tecla ENTER o ESC para culminar y guardar su imagen actual en fractales favoritos" + endl)

        cOp = input("¿Ha leido las instrucciones? (Si 'S' o No 'N')-> ")

        if (cOp == 'S' or cOp == 's'):
            m_bFractalGraficado = True
            m_GraficadorFractal.Display()	
            GuardarFractal()
            Salir()
            
    else:
        m_bFractalGraficado = True
        m_GraficadorFractal.Display()
        GuardarFractal()
        Salir()

def GuardarFractal():

    cls()  # limpia la pantalla

    cOp = input("¿Desea guardar el fractal en favoritos? (Si 'S' o No 'N')-> ")

    if (cOp == 'S' or cOp == 's'):

        print("Guarda el fractal: ")

        sNombreFractal = input("Ingrese el nombre del fractal: ")
        sDescripcion = input("Ingrese una descripción para su fractal: ")

        bd.GuardarFractal(m_nIdUsuario, sNombreFractal, sDescripcion, m_GraficadorFractal.PlanoComplejo.xmin,
                          m_GraficadorFractal.PlanoComplejo.xmax, m_GraficadorFractal.PlanoComplejo.ymin, m_GraficadorFractal.PlanoComplejo.ymax)

        print(endl + "Su fractal ha sido guardado en la base de datos...")

        pausa()

        return True

    return False

def Salir() :
    cls()
    print( endl +  "Gracias por usar Escarabajo..." + endl)
    pausa()	
    sys.exit()

def ListarFractales():

    bRet = True

    vFractales = []

    bd.ListarFractales(m_nIdUsuario, vFractales)

    nFractales = len(vFractales)

    cls()  # limpia la pantalla

    if (nFractales == 0):

        print("No existen fractales favoritos, por favor cree uno nuevo con la opción 'Graficar nuevo fractal'")
        bRet = False

    else:

        i = 1
        for mFractal in vFractales:
            print( '{num:02d}'.format(num=i), ". " + mFractal.sNombre + " : '" + mFractal.sDescripcion +"'")
            i+=1

        nOp = int(input("Escoja una opción -> "))

        if (1 > nOp or nOp > int(len(vFractales))):
            print("La opción seleccionada no existe!")
            bRet = False
        else:
            mFractal = vFractales[nOp - 1]

    pausa()

    if( bRet ):
        return mFractal
	
    return None

Login()
bd.Cerrar()




