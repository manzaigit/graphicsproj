//
// ScatteredPointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointBrush.h"
#include <random>

extern float frand();

ScatteredPointBrush::ScatteredPointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredPointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize( 1.0 );

	BrushMove( source, target );
}

void ScatteredPointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatteredPointBrush::BrushMove  document is NULL\n" );
		return;
	}

	glBegin( GL_POINTS );
		
		int size = pDoc->getSize();
		std::mt19937 e(std::random_device{}());
		std::bernoulli_distribution d;
		
		for (int i = -size/2; i < size/2; i++) {
			for (int j = -size/2; j < size/2; j++) {
				if (d(e)) {
					Point newsource = Point(source.x + i, source.y + j);
					SetColor(newsource); 
					glVertex2d(newsource.x, newsource.y);
				}
			}
		}

	glEnd();
}

void ScatteredPointBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

