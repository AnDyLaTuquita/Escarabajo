#########################################################
# Escarabajo                                            #
# Diagrama el Fractal  del "Escarabajo de Mandelbrot"   #
# Lenguaje: Python                                      #
#                                                       #
# BASE DE DATOS                                         #
#                                                       #
# Tecnología: Sqlite, en paradigma orientado a objetos  #
#                                                       #
# Fecha: 05-Agosto-2019                                 #
# Autor: Andrea Rosana Vellicce                         #
#########################################################

import sqlite3

class FRACTAL :
    sNombre = ""
    sDescripcion = ""
    dXmin = 0
    dXmax = 0
    dYmin = 0
    dYmax = 0

class BDEscarabajo:

    c = None
    conn = None # Conexión a BD

    # Constructor
    def __init__(self):

        # Abrir Base de Datos        
        try:
         self.conn = sqlite3.connect('BDEscarabajo.db')
        except sqlite3.Error as e:
         print(e)

        if( self.conn!=None):
         self.c = self.conn.cursor()

    # Destructor
    def Cerrar(self): 
        self.conn.close()

    def RegistrarUsuario( self, nombre, clave ) :  

        try:
         self.c.execute('INSERT INTO TablaUsuario VALUES(NULL, ?, ?)', (nombre, clave) )
        except sqlite3.Error as e:
         print(e)
         
        # Guarda los cambios en la BD
        self.conn.commit()

        return self.c.lastrowid
        

    def ValidarUsuario( self, nombre, clave, nIdUsuario ) :  
        
        try:
         self.c.execute('SELECT * FROM TablaUsuario WHERE nombreUsuario = ? AND contrasenia = ?', (nombre, clave) )         
         r =  self.c.fetchone()
        except sqlite3.Error as e:
         print(e)

        if( r == None ) :
            return 0
        else:
            nIdUsuario = r[0]

        return nIdUsuario
      
    def GuardarFractal( self, nIdUsuario, sNombre, sDescripcion, dXmin, dXmax, dYmin, dYmax) :  

        try:
         self.c.execute('INSERT INTO TablaFractal VALUES(NULL, ?, ?, ?, ?, ?, ?, ? )', (nIdUsuario, sNombre, sDescripcion, dXmin, dXmax, dYmin, dYmax)  )
        except sqlite3.Error as e:
         print(e)
        
        # Guarda los cambios en la BD
        self.conn.commit()

    def ListarFractales( self, nIdUsuario, vFractales ) :  

        

        try:
         self.c.execute('SELECT * FROM TablaFractal WHERE idUsuario= ?', (nIdUsuario,) )         
        except sqlite3.Error as e:
         print(e)

        for row in self.c.fetchall():
             mEscarabajo = FRACTAL()
             mEscarabajo.sNombre = row[2]
             mEscarabajo.sDescripcion = row[3]
             mEscarabajo.dXmin = row[4]
             mEscarabajo.dXmax = row[5]
             mEscarabajo.dYmin = row[6]
             mEscarabajo.dYmax = row[7]
             vFractales.append( mEscarabajo)
