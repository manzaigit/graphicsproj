//
// LineBrush.h
//
// The header file for Line Brush. 
//

#ifndef LINEBRUSH_H
#define LINEBRUSH_H

#include "ImpBrush.h"

class LineBrush : public ImpBrush
{
public:
	LineBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	Point brushdirection_startpoint;
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );

	int gaussian_kernal[3][3] = { 1,2,1,2,4,2,1,2,1 };
	int sobel_x[3][3] = { -1,0,1,-2,0,2,-1,0,1 };
	int sobel_y[3][3] = { 1, 2, 1, 0, 0, 0, -1, -2, -1 };
};

#endif