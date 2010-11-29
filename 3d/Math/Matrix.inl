template<class T>
T& operator<<(T& f, const AffineMatrix& m) {
    for(unsigned int i = 0 ; i < 16 ; ++i)
        f << m.array16f()[i];
    for(unsigned int j = 0 ; j < 4 ; ++j)
        for(unsigned int i = 0 ; i < 3 ; ++i)
            f << m.array16fInverse()[(j*4)+i];

    return f;
}

template<class T>
T& operator>>(T& f, AffineMatrix& m) {
    for(unsigned int i = 0 ; i < 16 ; ++i)
        f >> m.m[i];
    for(unsigned int j = 0 ; j < 4 ; ++j)
        for(unsigned int i = 0 ; i < 3 ; ++i)
            f >> m.im[(j*4)+i];

    m.im[3] = m.im[7] = m.im[11] = 0.0f;
    m.im[15] = 1.0f;

    // 3x3 parts are just copied over.

    m.m3[0] = m.m[0]; m.m3[3] = m.m[4]; m.m3[6] = m.m[8];
    m.m3[1] = m.m[1]; m.m3[4] = m.m[5]; m.m3[7] = m.m[9];
    m.m3[2] = m.m[2]; m.m3[5] = m.m[6]; m.m3[8] = m.m[10];

    m.im3[0] = m.im[0]; m.im3[3] = m.im[4]; m.im3[6] = m.im[8];
    m.im3[1] = m.im[1]; m.im3[4] = m.im[5]; m.im3[7] = m.im[9];
    m.im3[2] = m.im[2]; m.im3[5] = m.im[6]; m.im3[8] = m.im[10];

    return f;
}

template<class T>
T& operator<<(T& f, const General4x4Matrix& m) {
    for(unsigned int i = 0 ; i < 16 ; ++i)
        f << m.array16f()[i];
    for(unsigned int i = 0 ; i < 16 ; ++i)
        f << m.array16fInverse()[i];

    return f;
}

template<class T>
T& operator>>(T& f, General4x4Matrix& m) {
    for(unsigned int i = 0 ; i < 16 ; ++i)
        f >> m.m[i];
    for(unsigned int i = 0 ; i < 16 ; ++i)
        f >> m.im[i];

    return f;
}
