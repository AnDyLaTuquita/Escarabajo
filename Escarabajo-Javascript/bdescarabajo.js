//*********************************************************
//* Escarabajo                                            *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: Javascript                                  *
//*                                                       *
//* BASE DE DATOS                                         *
//*                                                       *
//* Tecnología:                                           *
//* - Base de datos local in-memory                       *
//*   Array de diccionarios nativo de javascript          *
//* - La serialización de la BD se hace con API-REST      *
//*   ver mas info en serialize.js                        *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autor: Andrea Rosana Vellicce                         *
//*********************************************************

// Base de datos in-memory
var bdTablaUsuario = [];
var bdTablaFractal = [];

function RegistrarUsuario( nombre, clave )
{
    var nLastId = bdTablaUsuario.length+1;

    var registro = { IdUsuario: nLastId, nombreUsuario: nombre, contrasenia:  clave };

    bdTablaUsuario.push(registro );

    SerializarBD();

    return nLastId;
}

function ValidarUsuario( nombre,  clave ) {

    var i, nDatos = bdTablaUsuario.length;

    for( i=0; i<nDatos; i++ ){

        var registro = bdTablaUsuario[i];

        if( registro.nombreUsuario==nombre &&  registro.contrasenia==clave )
            return registro.IdUsuario;
    }

    return 0;
}

function GuardarFractal( nIdUsuario,  sNombre,  sDescripcion,  dXmin,  dXmax,  dYmin,  dYmax) {

    var nLastId = bdTablaFractal.length+1;

    var registro = { IdFractal: nLastId, IdUsuario: nIdUsuario, nombreFractal: sNombre, descripcion: sDescripcion, xMin: dXmin, xMax: dXmax, yMin: dYmin, yMax: dYmax };

    bdTablaFractal.push(registro );

    SerializarBD();

    return nLastId;
}


function ListarFractales( nIdUsuario, vFractales){

    var i, nDatos = bdTablaFractal.length;

    for( i=0; i<nDatos; i++ ){

        var registro = bdTablaFractal[i];

        if(registro.IdUsuario== nIdUsuario)
            vFractales.push(registro);
    }
}

