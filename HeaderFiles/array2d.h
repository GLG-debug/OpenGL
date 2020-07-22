#pragma once
#ifndef _array2d_
#define _array2d_

struct Array2d {
	int xlen; // ������ ����� �������
	// ������������ ��������������� ��� x � y
	int sx, sy;
	// ����� ������� ���� ����� ��������� ��� ����� �������������
	int ox, oy;
	int ind; // ������� ������
	Array2d(int xl, int _ox = 0, int _oy = 0, int _sx = 1, int _sy = 1)
		{ init(xl, _ox, _oy, _sx, _sy); }
	void init(int xl, int _ox = 0, int _oy = 0, int _sx = 1, int _sy = 1);
	// �������� ������ �������� � �����
	// x, y ����������� ������������ ox � oy
	int getind(int x, int y)
		{ return (y * sy + oy) * xlen + x * sx + ox; }
	void setind(int x, int y)
		{ ind = (y * sy + oy) * xlen + x * sx + ox; }
	

};

#endif