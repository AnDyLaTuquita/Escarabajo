//*********************************************************
//* Escarabajo                                            *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: JAVA                                        *
//*                                                       *
//* GRAFICADOR                                            *
//*                                                       *
//* Tecnología: JFrame + awt (Graphics, event)            *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autor: Andrea Rosana Vellicce                         *
//*********************************************************

package cescarabajo;
import javax.swing.JFrame;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.awt.Color;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class CEscarabajo extends JFrame implements MouseListener, KeyListener { 

    private static final long serialVersionUID = 1L;
	private int nAncho;
	private int nAlto;
	private double dDIVERGE;   //valor de divergencia
	private int nITERMAX; //iteracion maxima

	// Paleta Grafica del fractal
	private int nPaletaR, nPaletaG, nPaletaB;

	public PLANOCOMPLEJO PlanoComplejo;

	// Canvas Java
    private BufferedImage canvas;

    public CEscarabajo() {

        nAncho = 640;
        nAlto = 480;
        dDIVERGE = 4;   //valor de divergencia
        nITERMAX = 255; //iteracion maxima

        // Paleta de colores del fractal
        nPaletaR = 10;
        nPaletaG = 5;
		nPaletaB = 1;
		
		PlanoComplejo = new PLANOCOMPLEJO();

        PlanoComplejo.xmin = -2;
        PlanoComplejo.xmax = 1;
        PlanoComplejo.ymin = -1.2;
		PlanoComplejo.ymax = 1.2;
		
		// Inicializa canvas
		canvas = new BufferedImage(nAncho, nAlto, BufferedImage.TYPE_INT_RGB);
	}

	private void Mandelbrot() {

		int j;
		
		double Cr_delta = (PlanoComplejo.xmax - PlanoComplejo.xmin) / (double)nAncho;
		double Ci_delta = (PlanoComplejo.ymax - PlanoComplejo.ymin) / (double)nAlto;
	
		double Cr;
		double Ci = PlanoComplejo.ymax;
	
		//PROCESO DE DIAGRAMADO		
		for (j = 0; j < nAlto; j++) {
	
			Cr = PlanoComplejo.xmin;
			
			int i;
			for (i = 0; i < nAncho; i++) {
	
				// Algoritmo usando operaciones entre números reales     
	
				double Zr = 0;
				double Zi = 0;
				double Tr = 0;
				double Ti = 0;
				int nITERACION = 0;
	
				for (; nITERACION < nITERMAX && (Tr + Ti) <= dDIVERGE; ++nITERACION) {
					Zi = 2 * Zr * Zi + Ci;
					Zr = Tr - Ti + Cr;
					Tr = Zr * Zr;
					Ti = Zi * Zi;
				}
	
				if (nITERACION != nITERMAX) {
					
					int nColor = nITERACION + 50;
	
					int r = (nPaletaR * (nColor + 1)) % 256;
					int g = (nPaletaG * (nColor + 1)) % 256;
					int b = (nPaletaB * (nColor + 1)) % 256;						

					// Pinta el pixel
					Color col = new Color(r, g, b);
					canvas.setRGB(i, nAlto-j-1, col.getRGB());
				}
				else {
								
					canvas.setRGB(i, nAlto-j-1, 0);
				}
	
				Cr += Cr_delta;	
			}
	
			Ci -= Ci_delta;
		}		
	}

	private void Zoom(double x1, double y1, double x2, double y2) {

		double xmed = 0.5*(x2 + x1);
		double ymed = 0.5*(y2 + y1);
	
		double Lx = 0.5*Math.abs(x2 - x1); // mitad del ancho del rectangulo de seleccion
		double Ly = (double)nAlto * Lx / (double)nAncho;
	
		double  ex = (PlanoComplejo.xmax - PlanoComplejo.xmin) / (double)nAncho;//escalax
		double  ey = (PlanoComplejo.ymax - PlanoComplejo.ymin) / (double)nAlto;//escalay
	
		PlanoComplejo.xmin = PlanoComplejo.xmin + (xmed - Lx) * ex;
		PlanoComplejo.ymax = PlanoComplejo.ymax - (ymed - Ly) * ey;
		PlanoComplejo.xmax = PlanoComplejo.xmin + 2 * Lx * ex;
		PlanoComplejo.ymin = PlanoComplejo.ymax - 2 * Ly * ey;	
	}


	private void OnMouseClick(int nButton, int nMousex, int nMousey) {

		double dSemiAnchoZoom, dSemiAltoZoom;
	
		if (nButton == 1 ) {	// Botón izquierdo
	
			dSemiAnchoZoom = (double)nAncho*0.25;
			dSemiAltoZoom = (double)nAlto*0.25;
			Zoom(nMousex - dSemiAnchoZoom, (nAlto - nMousey) - dSemiAltoZoom, nMousex + dSemiAnchoZoom, (nAlto - nMousey) + dSemiAltoZoom);
		
		}else if (nButton == 3 ) { // Botón derecho			
	
			dSemiAnchoZoom = (double)nAncho;
			dSemiAltoZoom = (double)nAlto;
	
			Zoom(nMousex - dSemiAnchoZoom, (nAlto - nMousey) - dSemiAltoZoom, nMousex + dSemiAnchoZoom, (nAlto - nMousey) + dSemiAltoZoom);
		}
	
		// Repinta el Dibujo
		Draw();
	}

	public void Draw(){	
		
		// Diagrama el fractal
		Mandelbrot();

		// Repinta el Dibujo		
		repaint();		
	}

	public void Display(){	
        
		
		setTitle("Mandelbrot Set");
        setBounds(0, 0, nAncho, nAlto);
        setResizable(false);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);    

		// Añade un mouse listener
		addMouseListener((MouseListener) this);

		// Añade un key listener
		addKeyListener((KeyListener)this);

		
		// Pinta el Dibujo
		Draw();  

	}

	// Eventos JFrame
	
	@Override
    public void paint(Graphics g) {
        g.drawImage(canvas, 0, 0, this);
    }
	
	@Override
    public void mouseClicked(MouseEvent e) {
		//System.out.println("mouseClicked " + e);		
		OnMouseClick(e.getButton(), e.getX(), e.getY() );
	}
    @Override
    public void mouseEntered(MouseEvent e) {
        //System.out.println("mouseEntered " + e);
    }
    @Override
    public void mouseExited(MouseEvent e) {
        //System.out.println("mouseExited " + e);
    }
    @Override
    public void mousePressed(MouseEvent e) {
        //System.out.println("mousePressed " + e);
    }
    @Override
    public void mouseReleased(MouseEvent e) {
        //System.out.println("mouseReleased " + e);
	}
	
	@Override
	public void keyPressed(KeyEvent ke) {
		int key = ke.getKeyCode();
		if (key == KeyEvent.VK_ESCAPE || 
			key == KeyEvent.VK_ENTER) {

				// Cierra la ventana de dibujo
				setVisible(false); //you can't see me!
				dispose(); //Destroy the JFrame object		
		}
	}
		
	@Override
	public void keyReleased(KeyEvent ke) {		
	}

	@Override
	public void keyTyped(KeyEvent ke) {		
	}
}