//*********************************************************
//* Escarabajo                                            *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: JAVA                                        *
//*                                                       *
//* BASE DE DATOS                                         *
//*                                                       *
//* Tecnología: Sqlite                                    *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autor: Andrea Rosana Vellicce                         *
//*********************************************************

package bdescarabajo;

import java.util.Scanner;
import java.util.Vector;
import java.io.File;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.ResultSet;

public class BDEscarabajo {

    private static Connection conn;

    public BDEscarabajo(){
        try {
            AbrirBD();
        } catch (SQLException e) {            
            e.printStackTrace();
        }
    
    }

    private void AbrirBD() throws SQLException
    {
        //Abrir Base de Datos
        try {
            Class.forName("org.sqlite.JDBC");
            conn = DriverManager.getConnection("jdbc:sqlite:bdescarabajo.db");          
            if (conn != null) {
                conn.getMetaData();
            }
        } catch (ClassNotFoundException e) {            
            e.printStackTrace();
        }     
    }

    public void Cerrar(){
        try {
            conn.close();            
        } catch (SQLException e) {
            e.printStackTrace();
        }        
    }

    public int RegistrarUsuario(String nombre, String clave)
    {

        try {
            
            PreparedStatement ps = conn.prepareStatement("INSERT INTO TablaUsuario VALUES(NULL, ?, ?)");

            ps.setString(1, nombre);
            ps.setString(2, clave);
            ps.executeUpdate();
            ResultSet rs = ps.getGeneratedKeys();

            while(rs.next()){                
                return rs.getInt(1); //IdUsuario
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return 0;
    }

    
    public int ValidarUsuario( String nombre, String clave ) {

        try{
            
            PreparedStatement ps = conn.prepareStatement("SELECT * FROM TablaUsuario WHERE nombreUsuario = ? AND contrasenia = ?");
            ps.setString(1, nombre);
            ps.setString(2, clave);
            ResultSet rs =  ps.executeQuery();

            while (rs.next()){ 
                return rs.getInt(1); //IdUsuario
            }

        }catch (SQLException e) {
            e.printStackTrace();
        }

        return 0;     
    }

    public void GuardarFractal(int nIdUsuario, String sNombre, String sDescripcion, double dXmin, double dXmax, double dYmin, double dYmax) {

        try {

            PreparedStatement ps = conn.prepareStatement("INSERT INTO TablaFractal VALUES(NULL, ?, ?, ?, ?, ?, ?, ? )");
            ps.setInt(1, nIdUsuario);            
            ps.setString(2, sNombre);
            ps.setString(3, sDescripcion);
            ps.setDouble(4, dXmin);
            ps.setDouble(5, dXmax);
            ps.setDouble(6, dYmin);
            ps.setDouble(7, dYmax);

            ps.executeUpdate();
            
        } catch (SQLException e) {
            e.printStackTrace();
        }
    
    }

    public void ListarFractales(int nIdUsuario, Vector<FRACTAL> vFractales){

        try{

            PreparedStatement ps = conn.prepareStatement("SELECT * FROM TablaFractal WHERE idUsuario = ?");
            ps.setInt(1, nIdUsuario); 

            ResultSet rs =  ps.executeQuery();            

            while (rs.next()){    
                
                FRACTAL mFractal = new FRACTAL();             

                mFractal.sNombre = rs.getString(3);    
                mFractal.sDescripcion = rs.getString(4);        
                mFractal.dXmin = rs.getDouble(5);
                mFractal.dXmax = rs.getDouble(6);
                mFractal.dYmin = rs.getDouble(7);
                mFractal.dYmax = rs.getDouble(8);
                
                vFractales.add(mFractal);
            }

        }catch (SQLException e) {
            e.printStackTrace();
        }
    }

}