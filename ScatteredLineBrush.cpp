//
// ScatteredLineBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLineBrush.h"
#include <random>

extern float frand();

ScatteredLineBrush::ScatteredLineBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredLineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredLineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatteredLineBrush::BrushMove  document is NULL\n" );
		return;
	}
	
	int size = pDoc->getSize();
	int linewidth = pDoc->getLineWidth();
	int lineangle = pDoc->getLineAngle();
	double lineangle_rad = ((double)lineangle / 180)*(3.14159);

	glLineWidth((float)linewidth);

	glBegin(GL_LINES);
 
	for (int i = -size / 2; i < size / 2; i++) {
		for (int j = -size / 2; j < size / 2; j++) {
			int v = rand() % size;
			if (v == 0) {
				
				Point newsource = Point(source.x + i, source.y + j);
				SetColor(newsource);

				double Ax = newsource.x - size*0.5*cos(lineangle_rad);
				double Ay = newsource.y - size*0.5*sin(lineangle_rad);
				double Bx = newsource.x + size*0.5*cos(lineangle_rad);
				double By = newsource.y + size*0.5*sin(lineangle_rad);
				glVertex2d(Ax, Ay);
				glVertex2d(Bx, By);							
			}
		}
	}

	glEnd();
}

void ScatteredLineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

