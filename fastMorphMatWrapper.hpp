#ifndef FAST_MORPH_MATWRAPPER_HPP
#define FAST_MORPH_MATWRAPPER_HPP

#include <iostream>
#include "matWrapper.hpp"

using namespace std;

template<typename _T> void 
hgwRowDilate(
        MatWrapper<_T>& src, 
        MatWrapper<_T>& dst, 
        MatWrapper<_T>& kernel)
{
    int num = src.rows * src.cols;
    dst.get_data(src.rows, src.cols);

    int p = kernel.cols;
    int r = p - 1;
    int hr = r / 2;

    vector<_T> rimgv(num);
    vector<_T> simgv(num);
    MatWrapper<_T> rimg(src.rows, src.cols, &rimgv[0]);
    MatWrapper<_T> simg(src.rows, src.cols, &simgv[0]);


    int i, j;
    for (i = 0; i < src.rows; i++) 
    {
        _T *srcrow = src.ptr(i);
        _T *rrow = rimg.ptr(i);
        _T *srow = simg.ptr(i);
        _T *dstrow = dst.ptr(i) - hr;
        for (j = r; j < src.cols - r; j+=p)
        {
            _T *psrc = srcrow + j;
            _T *pr = rrow + j;
            _T *ps = srow + j;

            pr[0] = psrc[0];
            ps[0] = psrc[0];

            for (int k = 1; k < p; k++)
            {
                ps[k] = max(psrc[k], ps[k - 1]);
                pr[-k] = max(psrc[-k], pr[- k + 1]);
            }

            _T *pdst = dstrow + j;
            for (int k = 0; k < p; k++)
            {
                pdst[k] = max(pr[k - r], ps[k]);
            }
        }
    }

    //! Process borders
    int endstart = j - hr;
    int hrp = hr + 1;
    for (i = 0; i < src.rows; i++)
    {
        _T* pdst = dst.ptr(i);
        _T* psrc = src.ptr(i);
        for (j = 0; j < hr; j++)
        {
            _T maxv = psrc[0];
            for (int k = 1; k < j + hrp; k++)
                maxv = max(maxv, psrc[k]);
            pdst[j] = maxv;
        }
        for (j = endstart; j < src.cols; j++)
        {
            _T maxv = psrc[j - hr];
            for (int k = j - hr + 1; k < min(src.cols,j+hrp); k++)
                maxv = max(maxv, psrc[k]);
            pdst[j] = maxv;
        }
    }
}

template<typename _T> void 
hgwRowErode(
        MatWrapper<_T>& src, 
        MatWrapper<_T>& dst, 
        MatWrapper<_T>& kernel)
{
    int num = src.rows * src.cols;
    dst.get_data(src.rows, src.cols);

    int p = kernel.cols;
    int r = p - 1;
    int hr = r / 2;

    vector<_T> rimgv(num);
    vector<_T> simgv(num);
    MatWrapper<_T> rimg(src.rows, src.cols, &rimgv[0]);
    MatWrapper<_T> simg(src.rows, src.cols, &simgv[0]);


    int i, j;
    for (i = 0; i < src.rows; i++) 
    {
        _T *srcrow = src.ptr(i);
        _T *rrow = rimg.ptr(i);
        _T *srow = simg.ptr(i);
        _T *dstrow = dst.ptr(i) - hr;
        for (j = r; j < src.cols - r; j+=p)
        {
            _T *psrc = srcrow + j;
            _T *pr = rrow + j;
            _T *ps = srow + j;

            pr[0] = psrc[0];
            ps[0] = psrc[0];

            for (int k = 1; k < p; k++)
            {
                ps[k] = min(psrc[k], ps[k - 1]);
                pr[-k] = min(psrc[-k], pr[- k + 1]);
            }

            _T *pdst = dstrow + j;
            for (int k = 0; k < p; k++)
            {
                pdst[k] = min(pr[k - r], ps[k]);
            }
        }
    }

    //! Process borders
    int endstart = j - hr;
    int hrp = hr + 1;
    for (i = 0; i < src.rows; i++)
    {
        _T* pdst = dst.ptr(i);
        _T* psrc = src.ptr(i);
        for (j = 0; j < hr; j++)
        {
            _T minv = psrc[0];
            for (int k = 1; k < j + hrp; k++)
                minv = min(minv, psrc[k]);
            pdst[j] = minv;
        }
        for (j = endstart; j < src.cols; j++)
        {
            _T minv = psrc[j - hr];
            for (int k = j - hr + 1; k < min(src.cols,j+hrp); k++)
                minv = min(minv, psrc[k]);
            pdst[j] = minv;
        }
    }
}

template<typename _T>
void 
hgwColDilate(
        MatWrapper<_T>& src, 
        MatWrapper<_T>& dst, 
        MatWrapper<_T>& kernel)
{
    int num = src.rows * src.cols;
    dst.get_data(src.rows, src.cols);

    int p = kernel.rows;
    int r = p - 1;
    int hr = p / 2;

    vector<_T> rimgv(num);
    vector<_T> simgv(num);
    MatWrapper<_T> rimg(src.rows, src.cols, &rimgv[0]);
    MatWrapper<_T> simg(src.rows, src.cols, &simgv[0]);

    int step = rimg.cols;
    _T* srcdata = src.data + r * step;
    _T* dstdata = dst.data;
    _T* rdata = rimg.data;
    int pstep = p * step;

    int i, j;
    for (j = r; j < src.rows - r; j+=p)
    {
        _T *psrc = src.ptr(j);
        _T *pdst = dst.ptr(j-hr);
        _T *pr = rimg.ptr(j);
        for (i = 0; i < src.cols; i++,psrc++,pdst++,pr++)
        {
            _T *psrc2 = psrc;
            _T *pdst2 = pdst;

            _T *pr2 = pr;

            _T b0 = pr[0] = psrc[0];
            _T a0 = b0;
            for (int k = 1; k < p; k++)
            {
                psrc2 -= step;
                pr2 -= step;
                b0 = *pr2 = max(*psrc2, b0);
            }

            *pdst = max(psrc[0], b0);

            pr2 = pr - r*step;
            psrc2 = psrc;
            for (int k = 1; k < p; k++)
            {
                pr2 += step;
                psrc2 += step;
                pdst2 += step;

                a0 = max(a0, *psrc2); 

                *pdst2 = max(a0, *pr2);
            }
        }
    }

    //! Process borders
    int hrp = hr + 1;
    int endstart = j - hr;
    for (j = 0; j < hr; j++)
    {
        _T *psrc = src.ptr(j);
        _T *pdst = dst.ptr(j);
        for (i = 0; i < src.cols; i++)
        {
            _T maxv = 0;
            for (int k = 0; k < j + hrp; k++)
                maxv = max(maxv, src.ptr(k)[i]);
            pdst[i] = maxv;
        }
    }

    for (j = endstart; j < src.rows; j++)
    {
        _T *psrc = src.ptr(j);
        _T *pdst = dst.ptr(j);
        for (i = 0; i < src.cols; i++)
        {
            _T maxv = src.ptr(j-hr)[i];
            for (int k = j-hr+1; k < min(j + hr + 1,src.rows); k++)
                maxv = max(maxv, src.ptr(k)[i]);
            pdst[i] = maxv;
        }
    }
}

template<typename _T>
void 
hgwColErode(
        MatWrapper<_T>& src, 
        MatWrapper<_T>& dst, 
        MatWrapper<_T>& kernel)
{
    int num = src.rows * src.cols;
    dst.get_data(src.rows, src.cols);

    int p = kernel.rows;
    int r = p - 1;
    int hr = p / 2;

    vector<_T> rimgv(num);
    vector<_T> simgv(num);
    MatWrapper<_T> rimg(src.rows, src.cols, &rimgv[0]);
    MatWrapper<_T> simg(src.rows, src.cols, &simgv[0]);

    int step = rimg.cols;
    _T* srcdata = src.data + r * step;
    _T* dstdata = dst.data;
    _T* rdata = rimg.data;
    int pstep = p * step;

    int i, j;
    for (j = r; j < src.rows - r; j+=p)
    {
        _T *psrc = src.ptr(j);
        _T *pdst = dst.ptr(j-hr);
        _T *pr = rimg.ptr(j);
        for (i = 0; i < src.cols; i++,psrc++,pdst++,pr++)
        {
            _T *psrc2 = psrc;
            _T *pdst2 = pdst;

            _T *pr2 = pr;

            _T b0 = pr[0] = psrc[0];
            _T a0 = b0;
            for (int k = 1; k < p; k++)
            {
                psrc2 -= step;
                pr2 -= step;
                b0 = *pr2 = min(*psrc2, b0);
            }

            *pdst = min(psrc[0], b0);

            pr2 = pr - r*step;
            psrc2 = psrc;
            for (int k = 1; k < p; k++)
            {
                pr2 += step;
                psrc2 += step;
                pdst2 += step;

                a0 = min(a0, *psrc2); 

                *pdst2 = min(a0, *pr2);
            }
        }
    }

    //! Process borders
    int hrp = hr + 1;
    int endstart = j - hr;
    for (j = 0; j < hr; j++)
    {
        _T *psrc = src.ptr(j);
        _T *pdst = dst.ptr(j);
        for (i = 0; i < src.cols; i++)
        {
            _T minv = src.ptr(0)[i];
            for (int k = 1; k < j + hrp; k++)
                minv = min(minv, src.ptr(k)[i]);
            pdst[i] = minv;
        }
    }

    for (j = endstart; j < src.rows; j++)
    {
        _T *psrc = src.ptr(j);
        _T *pdst = dst.ptr(j);
        for (i = 0; i < src.cols; i++)
        {
            _T minv = src.ptr(j-hr)[i];
            for (int k = j-hr+1; k < min(j + hr + 1,src.rows); k++)
                minv = min(minv, src.ptr(k)[i]);
            pdst[i] = minv;
        }
    }
}

template<typename _T> void 
hgwDilate(
        MatWrapper<_T>& src, 
        MatWrapper<_T>& dst, 
        MatWrapper<_T>& kernel)
{
    MatWrapper<_T> kc = kernel.col(0);
    MatWrapper<_T> kr = kernel.row(0);
    MatWrapper<_T> colresult;
    hgwColDilate(src, colresult, kc);
    hgwRowDilate(colresult, dst, kr);
}

template<typename _T> void 
hgwErode(
        MatWrapper<_T>& src, 
        MatWrapper<_T>& dst, 
        MatWrapper<_T>& kernel)
{
    MatWrapper<_T> kc = kernel.col(0);
    MatWrapper<_T> kr = kernel.row(0);
    MatWrapper<_T> colresult;
    hgwColErode(src, colresult, kc);
    hgwRowErode(colresult, dst, kr);
}

#endif
