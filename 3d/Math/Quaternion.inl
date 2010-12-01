template<class T>
T& operator<<(T& f, const Quaternion& v) {
    return f << v.x() << v.y() << v.z() << v.w();
}

template<class T>
T& operator>>(T& f, Quaternion& v) {
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f;
    f >> x >> y >> z >> w;
    v.x(x).y(y).z(z).w(w);
    return f;
}
