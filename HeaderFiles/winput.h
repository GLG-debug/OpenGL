#pragma ones
#indef _BASE_input_
#define _BASE_input_

// Класс? сохранющий ввод виртуальных клавиш
struct BASE_input
{
    int vkeys[256]; // Массив состояний клавиш
    int mousepos[2]; // Текущие координаты мыши
    int mkey; // Код последней нажатой клавиши
    // Код последней нажатой виртуальной клавиши
    int vkey;
    int ascii; // ascii код последней нажатой клавиши 
    void (*user_input) (WPARAM, LPARAM, UINT);
    // Сохранить состояние клавиш
    void save_keystate (WPARAM, LPARAM, UINT);
    virtual void keyinput (WPARAM, LPARAM, UINT);
    BASE_input ()
        {user_input = 0; ascii = -1; vkey = -1; mkey = -1; }
};

void BASE_input::save_keystate (WPARAM wp, LPARAM lp, UINT state)
{
    switch (state)
    {
    case WM_KEYDOWN:
        vkey = wp;
        vkeys[wp] = 1;
        break;
    case WM_KEYUP: vkeys[wp] = 0; break;
    case WM_CHAR: ascii = wp; break;
    case WM_LBUTTONDOWN: mkeys[0] = 1; break;
    case WM_LBUTTONUP: mkeys[0] = 0; break;
    case WM_MBUTTONDOWN: mkeys[1] = 1; break;
    case WM_MBUTTONUP: mskey[1] = 0; break;
    case WM_RBUTTONDOWN: mskey[2] = 1; break;
    case WM_RBUTTONUP: mskey[2] = 0; break;
    case WM_MOUSEMOVE:
        mousepos[0] = LOWORD(lp);
        mousepos[1] = HIWORD(lp);
        break;
    }
}

void BASE_input::keyinput(WPARM wp, LPARAM lp, UINT state)
{
    save_keystate(wp, lp, state);
    if(user_input) user_input(wp, lp, state);
}

#endif
