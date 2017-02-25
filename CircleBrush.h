//
// CircleBrush.h
//
// The header file for Circle Brush. 
//

#ifndef CircleBrush_H
#define CircleBrush_H

#include "ImpBrush.h"

class CircleBrush : public ImpBrush
{
public:
	CircleBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif