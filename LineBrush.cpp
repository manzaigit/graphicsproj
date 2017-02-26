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
			/*
			GLubyte color[3];
			int greyness[3][3];
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2, j++;) {
					if (target.x == 0 || target.y == 0 || target.x == pDoc->m_nWidth || target.y == pDoc->m_nHeight) {
						memcpy(color, pDoc->GetOriginalPixel(target.x, target.y), 3);
					}
					else {
						memcpy(color, pDoc->GetOriginalPixel(target.x + i, target.y + j), 3);
					}
					
					greyness[i + 1][j + 1] = 0.299 * color[0] + 0.587 * color[1] + 0.144 * color[2];	// getting grayscale value

					
				}
			}

			// process grayscale matrix w/ gaussian filter

			int gaussian_kernal[3][3] = { 1,2,1,2,4,2,1,2,1 };

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					greyness[i][j] ;
				}
			} */

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

