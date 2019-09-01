//*********************************************************
//* Escarabajo                                            *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: Javascript                                  *
//*                                                       *
//*  SERIALIZACIÓN DE LA BASE DE DATOS                    *
//*                                                       *
//* Tecnología: Javascript+jQuery                         *
//* Conexión con repositorio MyJSON que                   *
//* guarda la base de datos del proyecto. Se usa API REST *
//* para la conexión vía los protocolos PUT y GET         *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autor: Andrea Rosana Vellicce                         *
//*********************************************************

// Conexión con repositorio MyJSON.com que guarda la base de datos
// del proyecto de manera permanente en el siguiente link
var uriRepositorio = "https://api.myjson.com/bins/7i873";

function SerializarBD(){
    
    // Se usa protocolo PUT

    var bd = [];
    bd.push( bdTablaUsuario );
    bd.push( bdTablaFractal );

    var bdJSON = JSON.stringify(bd);    
 
    // Guarda JSON
   $.ajax({
        url:uriRepositorio,
        type:"PUT",
        data:bdJSON,
        contentType:"application/json; charset=utf-8",
        dataType:"json",
        success: function(data, textStatus, jqXHR){
        
        }
    });
}

function DesSerializarBD(){

    // Se usa protocolo GET

     // Carga JSON
    $.get(uriRepositorio, function (data, textStatus, jqXHR) {
          
        bdTablaUsuario = data[0];
        bdTablaFractal = data[1];

    });
}