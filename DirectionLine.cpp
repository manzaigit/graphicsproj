//
// DirectionLine.cpp
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "DirectionLine.h"
#include "ImpBrush.h"
#include <math.h>
extern float frand();

Point startPoint; // need star?
Point endPoint; // need star?

DirectionLine::DirectionLine( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void DirectionLine::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();
	glPointSize( (float)size );

	startpoint = new Point(target.x, target.y);

	BrushMove( source, target );
}

void DirectionLine::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "DirectionLine::BrushMove  document is NULL\n" );
		return;
	}

	glBegin( GL_LINES );
	SetColor( source );
	glVertex2d(startpoint->x, startpoint->y);
	glVertex2d( target.x, target.y );
	glEnd();	
	
}

void DirectionLine::BrushEnd(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int rawangle = atan((float)(target.y - startpoint->y) / (float)(target.x - startpoint->x)) * 180 / 3.14159;
	if (target.x < startpoint->x) {
		rawangle += 180;
	}
	else if (rawangle < 0) {
		rawangle += 360;
	}

	if (pDoc->m_pCurrentDirection == 1) {
		pDoc->m_pUI->setLineAngle(rawangle);
	}
	
	
}

