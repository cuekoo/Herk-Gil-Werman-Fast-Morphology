#ifndef MATWRAPPER_HPP
#define MATWRAPPER_HPP

#include <iostream>
#include <vector>
typedef unsigned char uchar;

using namespace std;

template<typename _T>
class RectWrapper
{
public:
    RectWrapper()
        : x(0), y(0), width(0), height(0) { };

    RectWrapper(_T _x, _T _y, _T _width, _T _height)
        : x(_x), y(_y), width(_width), height(_height) { };

    bool contains(_T x0, _T y0)
    {
        if ((x0 >= x) && (x0 < x + width) && (y0>=y) && (y0<y+height))
            return true;
        else
            return false;
    }

    _T area() { return width * height;};

    _T x;
    _T y;
    _T width;
    _T height;
};

template<typename _T>
class MatWrapper
{
public:
    MatWrapper() ;
    MatWrapper(int rows, int cols, void *data);
    MatWrapper(int rows, int cols);
    MatWrapper(int rows, int cols, int value);
    ~MatWrapper() {};
    void set_data(int rows, int cols, void *data);
    void get_data(int rows, int cols);

    void set_rect_value(int x, int y, int width, int height, int value);

    _T* ptr(int i=0)
    {
        return data + i * cols;
    }

    MatWrapper row(int i0=0);
    MatWrapper col(int i0=0);

    void get_min_max(_T* minv, _T*maxv);
    _T get_value(int row, int col);

    int rows;
    int cols;

    _T * data;
private:
    vector<_T> vdata;
};

template<typename _T>
MatWrapper<_T>::MatWrapper()
{
    rows = 0;
    cols = 0;
    vdata = vector<_T>();
}

template<typename _T>
MatWrapper<_T>::MatWrapper(int _rows, int _cols)
{
    vdata.resize(_rows * _cols * sizeof(_T));
    data = &vdata[0];
    rows = _rows;
    cols = _cols;
}

template<typename _T>
MatWrapper<_T>::MatWrapper(int _rows, int _cols, int value)
{
    vdata.resize(_rows * _cols * sizeof(_T));
    int num = _rows * _cols;
    for (int i = 0; i < num; i++)
        vdata[i] = value;
    data = &vdata[0];
    rows = _rows;
    cols = _cols;
}

template<typename _T>
MatWrapper<_T>::MatWrapper(int _rows, int _cols, void *_data)
{
    data = (_T*) _data;
    rows = _rows;
    cols = _cols;
}

template<typename _T>
void MatWrapper<_T>::set_data(int _rows, int _cols, void *_data)
{
    data = (_T*) _data;
    rows = _rows;
    cols = _cols;
}

template<typename _T>
void MatWrapper<_T>::get_data(int _rows, int _cols)
{
    vdata.resize(_rows * _cols * sizeof(_T));
    data = &vdata[0];
    rows = _rows;
    cols = _cols;
}

template<typename _T>
void MatWrapper<_T>::set_rect_value(int x, int y, int width, int height, int value)
{
    int xend = x + width;
    int yend = y + height;
    for (int j = y; j < yend; j++)
    {
        _T* p = ptr(j);
        for (int i = x; i < xend; i++)
            p[i] = value;
    }

}

template<typename _T>
MatWrapper<_T> MatWrapper<_T>::row(int i0)
{
    MatWrapper m;
    m.get_data(1, cols);
    for (int i = 0; i < cols; i++)
    {
        m.ptr(0)[i] = ptr(i0)[i];
    }

    return m;
}

template<typename _T>
MatWrapper<_T> MatWrapper<_T>::col(int i0)
{
    MatWrapper m;
    m.get_data(rows, 1);
    for (int i = 0; i < rows; i++)
    {
        m.ptr(i)[0] = ptr(i)[i0];
    }

    return m;
}

template<typename _T>
void MatWrapper<_T>::get_min_max(_T* minv, _T*maxv)
{
    if (rows == 0 || cols == 0)
        return;
    *minv = ptr(0)[0];
    *maxv = ptr(0)[0];
    for (int i = 0; i < rows; i++)
    {
        _T* p = ptr(i);
        
        for (int j = 0; j < cols; j++)
        {
            *minv = min(*minv, p[j]);
            *maxv = max(*maxv, p[j]);
        }
    }
}

template<typename _T>
_T MatWrapper<_T>::get_value(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        return 0;
    else
        return ptr(row)[col];
}

#endif
