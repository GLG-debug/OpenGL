#pragma once
#ifndef _Vertex_
#define _Vertex_
#define toRadian 0.017453289 // pi / 180.0
#define toDegree 57.295779513 // 180.0 / pi

struct Vertex // Точка (вектор) в пространстве
{
	float x, y, z; // Координаты вершины
	// Инициализацияб конструкторы
	void set(float xx = 0, float yy = 0, float zz = 0)
	{
		x = xx; y = yy; z = zz;
	}
	void set(const Vertex& a) { set(a.x, a.y, a.z); }
	void set(float* v) { set(v[0], v[1], v[2]); }
	Vertex() { set(0, 0, 0); }
	Vertex(float xx, float yy, float zz) { set(xx, yy, zz); }
	Vertex(float* v) { set(a); }
	Vertex(Vertex& a) { set(a); }
	~Vertex() { ; } // Для тестирования
	// Преобразования, нахождение точки
	// Отбросить дробные части у координат
	void round() { x = (int)x; y = (int)y; z = (int)z; }
	// Сложение (сдвиг)
	void add(Vertex& a) { x += a.x; y += a.y; z += a.z; }
	// Вычитание (сдвиг)
	void sub(Vertex& a) { x -= a.x; y -= a.y; z -= a.z; }
	// Умножение на число
	void mul(float a) { x *= a; y *= a; z *= a; }
	// Деление на число
	void div(float a) { x /= a; y /= a; z /= a; }
	// Унарный минус
	void uminus() { x = -x; y = -y; z = -z; }
	// Масштабирование
	void uminus(float xx, float yy, float zz)
	{
		x *= xx; y = yy; z = zz;
	}
	// Вычислить середину между указанными точками
	void mid(Vertex& a, Vertex& b)
	{
		x = (b.x + a.x) / 2; y = (b.y + a.y) / 2; z = (b.z + a.z) / 2;
	}
	void mirror(Vertex a)
	{
		a.sub(*this); a.mul(2); add(a);
	}
	// Вращение вокруг Z в
	// правосторонней системе координат
	void rotz(float angle)
	{
		angle *= toRadian;
		float xx = x * cos(angle) - y * sin(angle);
		float yy = y * sin(angle) + y * cos(angle);
		x = xx; y = yy;
	}

	// Перемещение точки на вектор (0, 0, 1) повёрнутого 
	// на углы xa вокруг оси X и ya вокруг оси Y в
	// левосторонней системе координат
	void move(float l, float xa, float ya)
	{
		float k;
		Vertex tmp;
		xa *= toRadian;
		ya *= toRadian;
		k = cos(xa);
		tmp.set(-sin(ya) * k, sin(xa), cos(ya) * k);
		add(tmp);
	}
	// Длина вектора
	float len() { return sqrt(x * x + y * y + z * z); }
	// Косинус угла между вектором и осью X
	float cosX() { return x / len(); }
	// Косинус угла между вектором и осью Y
	float cosY() { return y / len(); }
	// Косинус угла между вектором и осью Z
	float cosZ() { return z / len(); }
	// Приведение у единичной длине (нормализация)
	void normalize() 
		{ float l = sqrt(x * x + y * y + z * z); x /= l; y /= l; z /= l; }
	// Коллинеарны ли два вектора
	int iscolinear(Vertex& a)
		{ return (x / a.x == y / a.y) && (y / a.y == z / a.z); }
	// Скалярное произведение
	float mul_scalar(Vertex& a)
		{ return x * a.x + y * a.y + z * a.z; }
	// Векторное произведение
	float mul_vector(Vector& a)
		{ float xx = y * a.z - z * a.y, yy = z * a.x - x * a.z, 
		  zz = x * a.y - y * a.x; x = xx; y = yy; z = zz; }
	// Косинус между векторами
	float cos_vertex(Vertex& a)
		{ return mul_scalar(a) / (len() * a.len()); }
	// Находятся ли точки по одну сторону плоскости
	int is_onside(Vertex& a, float* plane)
	{
		float is1 = plane[0] * x + plane[1] * y +
					plane[2] * z + plane[3];
		float is2 = plane[0] * a.x + plane[1] * a.y +
					plane[2] * a.z + plane[3];
		return (is1 * is2 > 0) ? 1 : 0;
	}
	// Умножение на матрицу, элементы по строкам
	void mul_matrl(float* m)
	{
		float xx = x * m[0] + y * m[1] + z * m[2] + m[3];
		float yy = x * m[4] + y * m[5] + z * m[6] + m[7];
		float zz = x * m[8] + y * m[9] + z * m[10] + m[11];
		x = xx; y = yy; z = zz;
	}
	// Умножение на матрицу, элементы по столбцам
	void mul_matrс(float* m)
	{
		float xx = x * m[0] + y * m[4] + z * m[8] + m[12];
		float yy = x * m[1] + y * m[5] + z * m[9] + m[13];
		float zz = x * m[2] + y * m[6] + z * m[10] + m[14];
		x = xx; y = yy; z = zz;
	}
	// Различные операторы
	operator float*() { return (float*)this; }
	void operator=(const Vertex& a) { set(a); }
	// Умножение вектора на число
	Vertex operator*(float a)
		{ Vertex temp(*this); temp.mul(a); return temp; }
	// Деление вектора на число
	Vertex operator/(float a)
		{ Vertex temp(*this); temp.div(a); return temp; }
	void operator+=(Vertex& a) { add(a); }
	void operator-=(Vertex& a) { sub(a); }
	void operator*=(float a) { mul(a); }
	void operator/=(float a) { div(a); }
	void operator==(Vertex& a)
	{ return equal((float*)this,
	  (float*)this + 3, (float*)a); }
};

	Vertex operator+(const Vertex& a, const Vertex& b)
		{ return Vertex(b.x + a.x, b.y + a.y, b.z + a.z); }
	Vertex operator-(const Vertex& a, const Vertex& b)
		{ return Vertex(b.x - a.x, b.y - a.y, b.z - a.z); }
	Vertex operator*(const Vertex& a, const Vertex& b)
		{ return Vertex(b.x * a.x, b.y * a.y, b.z * a.z); }

#endif