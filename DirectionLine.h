//
// DirectionLine.h
//
// The header file for Point Brush. 
//

#ifndef DirectionLine_H
#define DirectionLine_H

#include "ImpBrush.h"

class DirectionLine : public ImpBrush
{
public:
	DirectionLine( ImpressionistDoc* pDoc = NULL, char* name = NULL );
	Point* startpoint;
	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif