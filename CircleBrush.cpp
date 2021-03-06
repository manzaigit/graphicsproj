//
// CircleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include <math.h>

extern float frand();

CircleBrush::CircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void CircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize( (float)size );

	BrushMove( source, target );
}

void CircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "CircleBrush::BrushMove  document is NULL\n" );
		return;
	}

	int size = pDoc->getSize();
	
	glBegin(GL_TRIANGLE_FAN);
	//glVertex2d(target.x, target.y);
	SetColor(source);

	for (int i = 0; i < 360; i++) {
		float angle = (i * 3.14159)/180;
		glVertex2d(target.x + size*cos(angle), target.y + size*sin(angle));
	}
	glEnd();
 
}

void CircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

