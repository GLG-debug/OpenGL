#pragma once
#ifndef _MY_INC_
#define _MY_INC_

#include<windows.h> // WIN API
#include<gl\gl.h>	// GL ����������
#include<gl\glu.h>	// GLU ����������
#include<cmath>		// ����������
// ����������� ����� ��� (��� ���������� ����������)
#include<complex>
// ����� ���������, ��� plus � ptr_fun
#include<functional>
// ����� ���������, ��� copy, fill_n
#include<algorithm>
// ����������� ����� �����
#include<string>
// ����� ���������, ��� accumulate
#include<numeric>
#include<vector>	// ����� �������
#include<stdio.h>	// �������� ����/����� � C
#include<stdlib.h>	// ������ ������� ��� random
using namespace std;
// ��������������� ����� ��� ���������
typedef unsigned int	uint;
typedef unsigned char	uchar;
typedef signed short	sshort;
typedef unsigned short	ushort;
typedef unsigned long	ulong;
typedef complex<float>	complexf;
template<typename T, typename T1, typename T2>
inline void minmax(T& src, T1 mi, T2 ma) 
{ src = (src < mi) ? mi : ((src > ma) ? ma : src); }
#include"array2d.h"		// ������ � ����������� ��������
#include"mtrans.h"		// ������� ��������������
// ������������� / ��������������� OpenGL
#include"glmain.h"
#include"winput.h"		// ���� � ���������
#include"vertex.h"		// �������
#include"model.h"		// ����� �������
#include"globj.h"		// ������
#include"image.h"		// �������� / ���������� �����������
#include"fimage.h"		// ��������� �����������
#include"fractset.h"	// ����������� ���������
#endif