//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"
#include <math.h>

extern float frand();

LineBrush::LineBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void LineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;
	
	int size = pDoc->getSize();
	int linewidth = pDoc->getLineWidth();
	brushdirection_startpoint = target; 
//	glPointSize( (float)size );
	glLineWidth((float)linewidth);
	BrushMove( source, target );
}

void LineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;	

	if ( pDoc == NULL ) {
		printf( "LineBrush::BrushMove  document is NULL\n" );
		return;
	}

	int size = pDoc->getSize();
	int lineangle = 0;
	int rawangle = 0;

	float x_gradient = 0;
	float y_gradient = 0;
	
	switch (pDoc->m_pCurrentDirection) {

		case 1: // right mouse

			lineangle = pDoc->getLineAngle();

			break;

		case 2: // mouse direction

			rawangle = atan((float)(target.y - brushdirection_startpoint.y) / (float)(target.x - brushdirection_startpoint.x)) * 180 / 3.14159;
			if (target.x < brushdirection_startpoint.x) {
				rawangle += 180;
			}
			else if (rawangle < 0) {
				rawangle += 360;
			}

			if (pDoc->m_pCurrentDirection == 2) {
				pDoc->m_pUI->setLineAngle(rawangle);
			}

			lineangle = pDoc->getLineAngle();
			brushdirection_startpoint = target;

			break;

		case 3: // gradient

			GLubyte color[3];
			int greyness[5][5];
			for (int i = -2; i < 3; i++) {
				for (int j = -2; j < 3, j++;) {
					if (target.x <= 1 || target.y <= 1 || target.x >= pDoc->m_nWidth - 1 || target.y >= pDoc->m_nHeight - 1) {
						memcpy(color, pDoc->GetOriginalPixel(target.x, target.y), 3);
					}
					else {
						memcpy(color, pDoc->GetOriginalPixel(target.x + i, target.y + j), 3);
					}
					greyness[i + 2][j + 2] = 0.299 * color[0] + 0.587 * color[1] + 0.144 * color[2];	// getting grayscale value					
				}
			}

			// process grayscale matrix w/ gaussian filter		

			int blurred_pixels[3][3];

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						for (int l = 0; l < 3; l++) {
							blurred_pixels[i][j] += greyness[k + i][l + j] * gaussian_kernal[k][l];
						}
					}
					blurred_pixels[i][j] /= 16;
				}
			}

			// get gradients 

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					x_gradient += sobel_x[i][j] * blurred_pixels[i][j];
				}
			}
		
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					y_gradient += sobel_y[i][j] * blurred_pixels[i][j];
				}
			}

			// make perpendicular

			float sobel_angle;

			sobel_angle = atan((float)(y_gradient) / (float)(x_gradient)) * 180 / 3.14159;
			if (sobel_angle < 0) {
				sobel_angle += 360;
			}

			if (pDoc->m_pCurrentDirection == 3) {
				pDoc->m_pUI->setLineAngle(sobel_angle);
			}

			// set brush angle

			lineangle = pDoc->getLineAngle();		

			break;


		default:
			lineangle = pDoc->getLineAngle();			
			break;

	}

	
	double lineangle_rad = ((double)lineangle / 180)*(3.14159);
	double Ax = target.x - size*0.5*cos(lineangle_rad);
	double Ay = target.y - size*0.5*sin(lineangle_rad);
	double Bx = target.x + size*0.5*cos(lineangle_rad);
	double By = target.y + size*0.5*sin(lineangle_rad);

	glBegin(GL_LINES);
	SetColor(source);

	glVertex2d(Ax, Ay);
	glVertex2d(Bx, By);

	glEnd();
	
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

