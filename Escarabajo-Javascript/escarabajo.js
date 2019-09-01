//*********************************************************
//* Escarabajo                                            *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: Javascript                                  *
//*                                                       *
//* GRAFICADOR                                            *
//*                                                       *
//* Tecnología: HTML5 + Javascript 2d Canvas              *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autor: Andrea Rosana Vellicce                         *
//*********************************************************

var nAncho = 640;
var nAlto = 480;
var dDIVERGE = 4  // valor de divergencia
var nITERMAX = 255  // iteracion maxima

// Paleta de colores del fractal
var nPaletaR = 10
var nPaletaG = 5
var nPaletaB = 1

// PLANO COMPLEJO
var PlanoComplejo = {
    xmin: -2,
    xmax: 1,
    ymin: -1.2,
    ymax: 1.2
};

// Canvas Javascript
var canvas = document.getElementById('FractalCanvas');
var context = canvas.getContext('2d');
//var nAncho = canvas.width;
//var nAlto = canvas.height;
//var nAncho = window.innerWidth;;
//var nAlto = Math.round(0.95*window.innerHeight);

canvas.width = nAncho;
canvas.height = nAlto;

var controlCanvas = document.getElementById('ControlCanvas');
var ControlContext = controlCanvas.getContext('2d');

controlCanvas.width = nAncho;
controlCanvas.height = nAlto;

var imgData = context.createImageData(nAncho, nAlto); // only do this once per page

canvas.style.visibility="hidden";
document.getElementById('botonCerrarCanvas').style.visibility = "hidden";


function Mandelbrot(){

    var i, j, nITERACION;    

    var Cr_delta = (PlanoComplejo.xmax - PlanoComplejo.xmin) / nAncho;
    var Ci_delta = (PlanoComplejo.ymax - PlanoComplejo.ymin) / nAlto;

    var Cr;
    var Ci = PlanoComplejo.ymax;

    //PROCESO DE DIAGRAMADO
    for (j = 0; j < nAlto; j++) {

        Cr = PlanoComplejo.xmin;

        for (var i = 0; i < nAncho; i++) {

            // Algoritmo usando operaciones entre números reales            
    
            nITERACION = 0;
    
            var Zr = 0;
            var Zi = 0;
            var Tr = 0;
            var Ti = 0;
            var nITERACION = 0;
    
            for (; nITERACION < nITERMAX && (Tr + Ti) <= dDIVERGE; ++nITERACION) {
                Zi = 2 * Zr * Zi + Ci;
                Zr = Tr - Ti + Cr;
                Tr = Zr * Zr;
                Ti = Zi * Zi;
            }
    
            if (nITERACION != nITERMAX) {
                putpixel(i, j, nITERACION + 50, 10, 5, 1, imgData);
            } else {
                putpixel(i, j, 0, 10, 5, 1, imgData);
            }
    
            Cr += Cr_delta;    
    
        }
      
        Ci -= Ci_delta;
    }

    context.putImageData(imgData, 0, 0);

}


function Zoom(x1, y1, x2, y2) {

    var xmed = 0.5*(x2 + x1);
    var ymed = 0.5*(y2 + y1);

    var Lx = 0.5*Math.abs(x2 - x1); // mitad del ancho del rectangulo de seleccion
    var Ly = nAlto * Lx / nAncho;

    var ex = (PlanoComplejo.xmax - PlanoComplejo.xmin) / nAncho;//escalax
    var ey = (PlanoComplejo.ymax - PlanoComplejo.ymin) / nAlto;//escalay

    PlanoComplejo.xmin = PlanoComplejo.xmin + (xmed - Lx) * ex;
    PlanoComplejo.ymax = PlanoComplejo.ymax - (ymed - Ly) * ey;
    PlanoComplejo.xmax = PlanoComplejo.xmin + 2 * Lx * ex;
    PlanoComplejo.ymin = PlanoComplejo.ymax - 2 * Ly * ey;	
}


controlCanvas.onmouseup = function(event) {

    var dSemiAnchoZoom, dSemiAltoZoom;
    var nMousex= event.clientX, nMousey= event.clientY;

    if (event.button == 0 ) {	// Botón izquierdo

        dSemiAnchoZoom = nAncho*0.25;
        dSemiAltoZoom = nAlto*0.25;
        Zoom(nMousex - dSemiAnchoZoom, nMousey - dSemiAltoZoom, nMousex + dSemiAnchoZoom, nMousey + dSemiAltoZoom);
    
    }else if (event.button == 2 ) { // Botón derecho			

        dSemiAnchoZoom = nAncho;
        dSemiAltoZoom = nAlto;

        Zoom(nMousex - dSemiAnchoZoom, nMousey - dSemiAltoZoom, nMousex + dSemiAnchoZoom, nMousey + dSemiAltoZoom);
    }

    // Repinta el Dibujo
    Draw();

}

function Draw(){	
		
    // Diagrama el fractal
    Mandelbrot();

}

function Display(){	   
    
    // Muestra el canvas
    canvas.style.visibility='visible';
    document.getElementById('botonCerrarCanvas').style.visibility = "visible";

    // Pinta el Dibujo
    Draw();  
   
}


function putpixel(x, y, nColor, nPaletaR, nPaletaG, nPaletaB, imgData) {    
    var nIndicePixel = (x + y * nAncho) * 4;
    imgData.data[nIndicePixel + 0] = (nPaletaR * (nColor + 1)) % 256;
    imgData.data[nIndicePixel + 1] = (nPaletaG * (nColor + 1)) % 256;
    imgData.data[nIndicePixel + 2] = (nPaletaB * (nColor + 1)) % 256;
    imgData.data[nIndicePixel + 3] = 255;
}
function CerrarCanvas(){
    // Oculta el canvas
    canvas.style.visibility="hidden";

    // Guarda el fractal
    GuardarFractal1();

    // Resetea el  PlanoComplejo
    PlanoComplejo = {
        xmin: -2,
        xmax: 1,
        ymin: -1.2,
        ymax: 1.2
    };

    document.getElementById('botonCerrarCanvas').style.visibility = "hidden";
}