//
// ScatteredCircleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredCircleBrush.h"
#include <math.h>

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredCircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredCircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatteredCircleBrush::BrushMove  document is NULL\n" );
		return;
	}

	int size = pDoc->getSize();

	int maximum = rand() % 4 + 1;

	while (maximum) {
		int x_offset = rand() % size;
		int y_offset = rand() % size;

		glBegin(GL_TRIANGLE_FAN);
		Point newSource = Point(target.x + x_offset, target.y + y_offset);
		SetColor(newSource);

		for (int i = 0; i < 360; i++) {
			float angle = (i * 3.14159) / 180;
			glVertex2d(newSource.x + size*cos(angle), newSource.y + size*sin(angle));
		}

		glEnd();

		maximum -= 1;
	}	
}

void ScatteredCircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

