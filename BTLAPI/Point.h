#pragma once
class CPoint
{
	int m_x;
	int m_y;
public:
	CPoint() { m_x = 0; m_y = 0; }
	CPoint(int x, int y) { m_x = x; m_y = y; }
	~CPoint() {}

	void SetX(int x) { m_x = x; }
	void SetY(int y) { m_y = y; }
	int GetX() { return m_x; }
	int GetY() { return m_y; }

	CPoint& operator=(const CPoint& cp)
	{
		if (&cp != this)
		{
			this->m_x = cp.m_x;
			this->m_y = cp.m_y;
		}
		return *this;
	}
	bool operator ==(const CPoint& cp)
	{
		if (this->m_x == cp.m_x && this->m_y == cp.m_y)
			return true;
		return false;
	}

	bool operator !=(const CPoint& cp)
	{
		if (!(this->m_x == cp.m_x && this->m_y == cp.m_y))
			return true;
		return false;
	}
};

