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

/* Коды некоторых вируальных клавиш
Символьные клавиши
    0x30 - 0x39 клавиши 0 - 9
    0x41 - 0x5a клавиши A - z
    Можно использовать как if(in.vkey == 'A')

Клавиши на числовой клавиатуры (numeric keypad)
    VK_NUMPAD0 - VK_NUMPAD9 0X60 - 0x69 цифры на 0 - 9
    VK_MULTIPLY знак умножения
    VK_ADD знак сложения
    VK_SUBTRACT знак вычитания
    VK_DIVIDE знак деления
Мышь
    VK_LBUTTON 01 левая клавиша мыши
    VK_RBUTTON 02 левая клавиша мыши
    VK_MBUTTON 04 левая клавиша мыши
    VK_XBUTTON1 05 X1 левая клавиша мыши
    VK_XBUTTON2 06 X2 левая клавиша мыши
Разное
    VK_F1 - VK_F24 0x70 - 0x87 клавиши F1 - F24
    VK_ESCAPE 0x1b клавиша ESC
    VK_END 0x23 клавиша END
    VK_HOME 0x24 клавиша HOME
    VK_LEFT 0x25 клавиша стрелка влево
    VK_UP 0x26 клавиша стрелка вверх
    VK_RIGHT 0x27 клавиша стрелка вправо
    VK_DOWN 0x28 клавиша стрелка вниз
    VK_SELECT 0x29 клавиша SELECT key
    VK_SPACE пробел
    VK_LSHIFT 0xa0 левый шифт
    VK_RSHIFT 0xa1 правый шифт 
    VK_LCONTROL 0xa2 левая клавиша Ctrl
    VK_RCONTROL 0xa3 правая клавиша Ctrl
    VK_RETURN 0x0D клавиша ENTER
    VK_SHIFT 0x10 клавиша SHIFT
    VK_CONTROL 0x11 клавиша Ctrl
    VK_MENU 0x12 клавиша Alt
*/

#endif
