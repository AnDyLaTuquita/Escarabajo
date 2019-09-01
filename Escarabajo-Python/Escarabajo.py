#########################################################
# Escarabajo                                            #
# Diagrama el Fractal  del "Escarabajo de Mandelbrot"   #
# Lenguaje: Python                                      #
#                                                       #
# INTERFAZ                                              #
#                                                       #
# Tecnología: PYGAME                                    #
# Se usa paradigma orientado a objetos                  #
#                                                       #
# Fecha: 05-Agosto-2019                                 #
# Autor: Andrea Rosana Vellicce                         #
#########################################################

import pygame
import math 

# Se desactiva alertas de pygame no soportadas por vscode
# pylint: disable=no-member

class PLANOCOMPLEJO:
    xmin = -2
    xmax = 1
    ymin = -1.2
    ymax = 1.2


class CEscarabajo:
    nAncho = 640
    nAlto = 480
    dDIVERGE = 4  # valor de divergencia
    nITERMAX = 255  # iteracion maxima

    # Paleta de colores del fractal
    nPaletaR = 10
    nPaletaG = 5
    nPaletaB = 1

    # PLANO COMPLEJO
    PlanoComplejo = PLANOCOMPLEJO()

    # Canvas Pygame
    canvas = []

    def Mandelbrot(self):

        Cr_delta = (self.PlanoComplejo.xmax -
                    self.PlanoComplejo.xmin) / self.nAncho
        Ci_delta = (self.PlanoComplejo.ymax -
                    self.PlanoComplejo.ymin) / self.nAlto

        Ci = self.PlanoComplejo.ymax

        # PROCESO DE DIAGRAMADO
        for j in range(self.nAlto):

            Cr = self.PlanoComplejo.xmin

            # for (i = 0 i < nAncho i++) {
            for i in range(self.nAncho):

                # Algoritmo usando operaciones entre números reales
                Zr = 0
                Zi = 0
                Tr = 0
                Ti = 0
                nITERACION = 0

                # for ( nITERACION < nITERMAX && (Tr + Ti) <= dDIVERGE ++nITERACION) {
                while nITERACION < self.nITERMAX and (Tr + Ti) <= self.dDIVERGE:
                    Zi = 2 * Zr * Zi + Ci
                    Zr = Tr - Ti + Cr
                    Tr = Zr * Zr
                    Ti = Zi * Zi
                    nITERACION += 1

                if (nITERACION != self.nITERMAX):

                    nColor = nITERACION + 50

                    r = (self.nPaletaR * (nColor + 1)) % 256
                    g = (self.nPaletaG * (nColor + 1)) % 256
                    b = (self.nPaletaB * (nColor + 1)) % 256

                    self.canvas.set_at([i, self.nAlto-j], [r, g, b])
                else:                   
                    self.canvas.set_at([i, self.nAlto-j], [0, 0, 0])

                Cr += Cr_delta

            Ci -= Ci_delta

    def Zoom(self, x1, y1,  x2,  y2):

        xmed = 0.5*(x2 + x1)
        ymed = 0.5*(y2 + y1)

        Lx = 0.5*math.fabs(x2 - x1)  # mitad del ancho del rectangulo de seleccion
        Ly = (self.nAlto) * Lx / (self.nAncho)

        ex = (self.PlanoComplejo.xmax - self.PlanoComplejo.xmin) / (self.nAncho)  # escalax
        ey = (self.PlanoComplejo.ymax - self.PlanoComplejo.ymin) / (self.nAlto)  # escalay

        self.PlanoComplejo.xmin = self.PlanoComplejo.xmin + (xmed - Lx) * ex
        self.PlanoComplejo.ymax = self.PlanoComplejo.ymax - (ymed - Ly) * ey
        self.PlanoComplejo.xmax = self.PlanoComplejo.xmin + 2 * Lx * ex
        self.PlanoComplejo.ymin = self.PlanoComplejo.ymax - 2 * Ly * ey

    def Display(self):
        pygame.init()
        pygame.display.set_mode(
            (self.nAncho, self.nAlto), pygame.OPENGL | pygame.DOUBLEBUF | pygame.RESIZABLE)
        self.canvas = pygame.display.set_mode([self.nAncho, self.nAlto])
        #self.canvas.fill((255, 0, 0))
        #s = pygame.Surface(self.canvas.get_size(), pygame.SRCALPHA, 32)
        self.Mandelbrot()
        #self.canvas.blit(s, (0, 0))
        # pygame.display.flip()

        try:
            while 1:
                event = pygame.event.wait()
                if event.type == pygame.QUIT:
                    break

                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE or event.key == pygame.K_RETURN :
                        break

                if event.type == pygame.MOUSEBUTTONDOWN:                
                    self.OnMouseClick(event.button, event.pos[0], event.pos[1])

                # Repinta el Dibujo
                pygame.display.flip()
        finally:
            pygame.quit()

    def OnMouseClick(self, nButton, nMousex, nMousey):

        # double dSemiAnchoZoom, dSemiAltoZoom

        if (nButton == 1):  # Botón izquierdo del mouse

            dSemiAnchoZoom = (self.nAncho)*0.25
            dSemiAltoZoom = (self.nAlto)*0.25
            self.Zoom(nMousex - dSemiAnchoZoom, (self.nAlto - nMousey) - dSemiAltoZoom,
                 nMousex + dSemiAnchoZoom, (self.nAlto - nMousey) + dSemiAltoZoom)

        else:
            if (nButton == 3):  # Botón derecho del mouse

                dSemiAnchoZoom = self.nAncho
                dSemiAltoZoom = self.nAlto

                self.Zoom(nMousex - dSemiAnchoZoom, (self.nAlto - nMousey) - dSemiAltoZoom,
                     nMousex + dSemiAnchoZoom, (self.nAlto - nMousey) + dSemiAltoZoom)

        self.Mandelbrot()


