#pragma once
#ifndef _M_TRANFORMATION_ 
#define _M_TRANFORMATION_

struct  Mtransform // Матрица преобразований
{
    float m[16];
    Mtransform() { identity(); }
    void identity() {
        fill_n(m, 16, 0);
        m[0] = m[5] = m[10] = m[15] = 1;
    }

    // Перемножение матриц 4x4
    void mul(float* M1, float* M2, float* R) {
        float temp[16]; // Для хранения результата
        if(M1 == 0) M1 = m;
        if(M2 == 0) M2 = m;
        for(int i = 0; i < 4; ++i) // Строки
            for(int j = 0; j < 4; ++j) // Столбцы
                // Сумма произведений i строки M1 и j столбца M2
                temp[i * 4 + j] = M1[i * 4] * M2[j] + M1[i * 4 + 1] * M2[4 + j] +
                                  M1[i * 4 + 2] * M2[8 + j] + M1[i * 4 + 3] * M2[12 + j];
                if(R == 0) R = m;
                copy(temp, temp + 16, R); // Сохраняем результат
    }
    
    float& operator[] (int i) { return m[i]; }
    void operator= (float* v) { copy(v, v + 16, m); }
    operator float* () { return m; }
};

#endif