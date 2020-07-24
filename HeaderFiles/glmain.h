#pragma once
#ifndef _GLmain_
#define _GLmain_

struct GLmain
{
	HGLRC	hrc;
	HDC		hdc;
	HWND	hwnd;
	int select_size;		// Размер буфера выбора
	int feedback_size;		// Размер буфера обратной связи
	uint* select;			// Буфер выбора
	float* feedback;		// Буфер обратной связи
	float l, r, t, b, n, f;	// Шесть плоскостей отсечения
	void resize();			// Обработка изменения размера окна
	void init(HWND hWnd);	// Инициализация OpenGL
	void deinit();			// Деинициализация OpenGL
	void set(int);			// Выбрать одну из настроек OpenGL

	// Преобразовать Windows шрифт в список отображения
	void font(unsigned int disp_start = 1, WCHAR* /* char* */ fontname = 0,
			  LOGFONT* lg = 0, int type = 0) 
	{
		GLYPHMETRICSFLOAT char_set[256];
		LOGFONT font_info; // Шрифт по умолчанию
		if (lg == 0) 
		{
			font_info.lfHeight = 25;
			font_info.lfWidth = 0;
			font_info.lfEscapement = 0;
			font_info.lfOrientation = 0;
			font_info.lfWeight = FW_BOLD;
			font_info.lfItalic = 0;
			font_info.lfUnderline = 0;
			font_info.lfStrikeOut = 0;
			font_info.lfCharSet = ANSI_CHARSET;
			font_info.lfOutPrecision = OUT_DEFAULT_PRECIS;
			font_info.lfClipPrecision = CLIP_DEFAULT_PRECIS;
			font_info.lfQuality = DEFAULT_QUALITY;
			font_info.lfPitchAndFamily = 34;
			if (fontname)
				lstrcpy(font_info.lfFaceName, fontname);
			else
				lstrcpy(font_info.lfFaceName, L"ARIAL" /* "ARIAL" */ );
			lg = &font_info;
		}
		// Создаём шрифт
		HFONT myfont = CreateFontIndirect(lg);
		// Выбираем в контекст созданный шрифт
		HGDIOBJ /* HFONT */ temp = SelectObject(hdc, myfont);
		switch (type) // Тип символов
		{
		case 1: // Символ представлен линиями
			wglUseFontOutlines(hdc, 0, 255, disp_start, 0, 0.1,
							   WGL_FONT_LINES, char_set);
			break;
		case 2: // Символ представлен битовым изображением
			wglUseFontBitmaps(hdc, 0, 255, disp_start);
			break;
		default: // Символ представлен полигонами
			wglUseFontOutlines(hdc, 0, 255, disp_start, 0, 0.1,
				WGL_FONT_POLYGONS, char_set);
			break;
		}
		// Возвращаем предыдущий шрифт
		SelectObject(hdc, temp);
		DeleteObject(myfont); // Уничтожаем созданный шрифт
	}
};

void GLmain::deinit() // Освобождение ресурсов
{
	// Делаем текущий контекст отображения нулевым
	wglMakeCurrent(NULL, NULL);
	// Уничтожаем консекст отображения
	wglDeleteContext(hrc);
	hrc = NULL;
	if (select_size) delete[] select;
	if (feedback_size) delete[] feedback;
}

void GLmain::init(HWND hWnd)
{
	// Заполнение структуры формата пикселя
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), 1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
		16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16,
		16, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};
	hwnd = hWnd;
	// Получение дескриптора контекста устройства
	hdc = GetDC(hwnd);
	int PixelFormat;
	PixelFormat = ChoosePixelFormat(hdc, &pfd);
	// Устанавливаем формат пиикселя в контексте устройства
	SetPixelFormat(hdc, PixelFormat, &pfd);
	// Создаём контекст отображения OpenGL
	hrc = wglCreateContext(hdc);
	// Делаем контекст отображения текущим
	wglMakeCurrent(hdc, hrc);
}

void GLmain::set(int mode)
{
	 // Выбор стека проективных матриц
	glMatrixMode(GL_PROJECTION);
	// Приведение её в единичную
	glLoadIdentity();
	RECT rect;
	// Устанавливаем тип прокции и объём видимости
	switch (mode)
	{
	case 1: // Ортографическая проекция
		glOrtho(-100, 100, -100, 100, -100, 100);
		l = -100; r = 100; b = -100; t = 100; n = -100; f = 100;
		break;
	case 2: // Перспективная проекция
		glOrtho(-100, 100, -100, 100, 1, 200);
		l = -100; r = 100; b = -100; t = 100; n = 1; f = 200;
		break;
	case 3: // Перспективная проекция
		glOrtho(l, r, b, t, n, f);
		break;
	// ...
	default: // Перспективная прокция
		GetClientRect(hwnd, &rect);
		gluPerspective(45.0f, rect.right /
			((!rect.bottom) ? 1 : rect.bottom), 1, 500.0);
		break;
	}
	// Выбор стека выдовых матриц
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Инициализация буфера выбора
	select_size = 100;
	select = new uint[select_size];
	glSelectBuffer(select_size, select);
	// Инициализация буфера обратной связи
	feedback_size = 200;
	feedback = new float[feedback_size];
	glFeedbackBuffer(feedback_size, GL_3D, feedback);
}

void GLmain::resize()
{
	// Получение размеров клиентсвой области окна
	RECT rect;
	GetClientRect(hwnd, &rect);
	//Установка области вывода в окно
	glViewport(0, 0, rect.right, rect.bottom);
}

#endif