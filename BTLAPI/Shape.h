#pragma once
#include <windowsx.h>
#include "Point.h"
#include "Style.h"
class Shape
{
protected:
	CPoint m_PointStart;
	CPoint m_PointEnd;
	CStyle* m_Style = NULL;

public:
	Shape()
	{

	}
	Shape(const Shape& cs)
	{
		
		this->m_PointStart = cs.m_PointStart;
		this->m_PointEnd = cs.m_PointEnd;
		if (this->m_Style != NULL)
			delete this->m_Style;
		this->m_Style = new CStyle(*cs.m_Style);

	}
	virtual ~Shape()
	{
		if (this->m_Style != NULL)
		{
			delete m_Style;
			m_Style = NULL;
		}
	}

};

