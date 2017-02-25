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

	switch (pDoc->m_pCurrentDirection) {

		case 1: // right mouse

			lineangle = directionlineangle;

			break;

		case 2: // mouse direction



			break;

		case 3: // gradient



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

