#pragma once
#include <vector>
#include <cmath>
#include <cassert>
#include "fftsg_c.h"

namespace fftsg
{

    template <typename T>
    class RFFTEngine
    {
        // Tにdouble型とfloat型のみ指定可能にする
        static_assert(
            std::is_same<T, double>::value || std::is_same<T, float>::value,
            "RFFTEngine<T> only supports double and float.");

    private:
        const int m_frameSize;

        // m_ipとm_wは大浦版FFTが利用する事前計算領域
        // (あくまでnにだけ依存する計算だけなので, 同じインスタンスで
        //  rfftやirfftは気にせずに呼んで構わない)
        std::vector<int> m_ip;
        std::vector<T> m_w;

    public:
        explicit RFFTEngine(int frameSize);

        // 高速フーリエ変換(実数部のみ)
        void rfft(T *a);
        void rfft(std::vector<T> & a);

        // 逆高速フーリエ変換(実数部のみ)
        void irfft(T *a);
        void irfft(std::vector<T> & a);

        int frameSize() const { return m_frameSize; }
    };

    template <typename T>
    RFFTEngine<T>::RFFTEngine(int frameSize)
        : m_frameSize(frameSize)
        , m_ip(2 + static_cast<int>(sqrt(frameSize/4)))
        , m_w(frameSize / 2)
    {
        m_ip[0] = 0;
    }

    template <typename T>
    void RFFTEngine<T>::rfft(T *a)
    {
        rdft(m_frameSize, 1, a, &m_ip[0], &m_w[0]);
    }

    template <typename T>
    void RFFTEngine<T>::rfft(std::vector<T> & a)
    {
        assert(static_cast<int>(a.size()) == m_frameSize);
        rdft(m_frameSize, 1, &a[0], &m_ip[0], &m_w[0]);
    }

    template <typename T>
    void RFFTEngine<T>::irfft(T *a)
    {
        rdft(m_frameSize, -1, a, &m_ip[0], &m_w[0]);
        for (int i = 0; i < m_frameSize; ++i)
        {
            a[i] *= static_cast<T>(2.0) / m_frameSize;
        }
    }

    template <typename T>
    void RFFTEngine<T>::irfft(std::vector<T> & a)
    {
        assert(static_cast<int>(a.size()) == m_frameSize);
        rdft(m_frameSize, -1, &a[0], &m_ip[0], &m_w[0]);
        for (int i = 0; i < m_frameSize; ++i)
        {
            a[i] *= static_cast<T>(2.0) / m_frameSize;
        }
    }

}
