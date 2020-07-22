#pragma once
#ifndef _array2d_
#define _array2d_

struct Array2d {
	int xlen; // Ширина всего массива
	// Коэффициенты масштабирования для x и y
	int sx, sy;
	// Левый верхний угол блока элементов без учёта коэффициентов
	int ox, oy;
	int ind; // Текущий индекс
	Array2d(int xl, int _ox = 0, int _oy = 0, int _sx = 1, int _sy = 1)
		{ init(xl, _ox, _oy, _sx, _sy); }
	void init(int xl, int _ox = 0, int _oy = 0, int _sx = 1, int _sy = 1);
	// Получить индекс элемента в блоке
	// x, y указываются относительно ox и oy
	int getind(int x, int y)
		{ return (y * sy + oy) * xlen + x * sx + ox; }
	void setind(int x, int y)
		{ ind = (y * sy + oy) * xlen + x * sx + ox; }
	

};

#endif