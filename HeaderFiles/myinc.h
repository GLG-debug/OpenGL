#pragma once
#ifndef _MY_INC_
#define _MY_INC_

#include<windows.h> // WIN API
#include<gl\gl.h>	// GL библиотека
#include<gl\glu.h>	// GLU библиотека
#include<cmath>		// Математика
// Комплексные числа для (для построения факториала)
#include<complex>
// Такие алгоритмы, как plus и ptr_fun
#include<functional>
// Такие алгоритмы, как copy, fill_n
#include<algorithm>
// Стандартный класс строк
#include<string>
// Такие алгоритмы, как accumulate
#include<numeric>
#include<vector>	// Класс вектора
#include<stdio.h>	// Файловый ввод/вывод в C
#include<stdlib.h>	// Разные функции как random
using namespace std;
// Переопределение типов для краткости
typedef unsigned int	uint;
typedef unsigned char	uchar;
typedef signed short	sshort;
typedef unsigned short	ushort;
typedef unsigned long	ulong;
typedef complex<float>	complexf;
template<typename T, typename T1, typename T2>
inline void minmax(T& src, T1 mi, T2 ma) 
{ src = (src < mi) ? mi : ((src > ma) ? ma : src); }
#include"array2d.h"		// Работа с двуччмерным массивом
#include"mtrans.h"		// Матрица преобразований
// Инициализация / деинициализация OpenGL
#include"glmain.h"
#include"winput.h"		// Ввод с устройств
#include"vertex.h"		// Вершина
#include"model.h"		// Класс можелей
#include"globj.h"		// Камера
#include"image.h"		// Загрузка / сохранение изображений
#include"fimage.h"		// Обработка изображений
#include"fractset.h"	// Фрактальные алгоритмы
#endif