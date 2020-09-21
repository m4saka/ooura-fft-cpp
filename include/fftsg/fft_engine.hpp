#pragma once
#include <type_traits>
#include <vector>
#include <complex>
#include <cmath>
#include <cassert>
#include "fftsg_c.h"

namespace fftsg
{

    template <typename T>
    class FFTEngine
    {
        // Tにdouble型とfloat型のみ指定可能にする
        static_assert(
            std::is_same<T, double>::value || std::is_same<T, float>::value,
            "FFTEngine<T> only supports double and float.");

    private:
        const int m_frameSize;

        // m_ipとm_wは大浦版FFTが利用する事前計算領域
        // (あくまでnにだけ依存する計算だけなので, 同じインスタンスで
        //  fftやifftは気にせずに呼んで構わない)
        std::vector<int> m_ip;
        std::vector<T> m_w;

    public:
        explicit FFTEngine(int frameSize);

        // 高速フーリエ変換
        void fft(std::vector<T> & a);
        void fft(std::vector<std::complex<T>> & a);

        // 逆高速フーリエ変換
        void ifft(std::vector<T> & a);
        void ifft(std::vector<std::complex<T>> & a);

        int frameSize() const { return m_frameSize; }
    };

    template <typename T>
    FFTEngine<T>::FFTEngine(int frameSize)
        : m_frameSize(frameSize)
        , m_ip(2 + (1 << static_cast<int>(std::log(frameSize / 2 + 0.5) / std::log(2.0)) / 2))
        , m_w(frameSize / 2)
    {
        m_ip[0] = static_cast<T>(0.0);
    }

    template <typename T>
    void FFTEngine<T>::fft(std::vector<T> & a)
    {
        assert(static_cast<int>(a.size()) == m_frameSize * 2);
        cdft(m_frameSize * 2, -1, &a[0], &m_ip[0], &m_w[0]);
    }

    template <typename T>
    void FFTEngine<T>::ifft(std::vector<T> & a)
    {
        assert(static_cast<int>(a.size()) == m_frameSize * 2);
        cdft(m_frameSize * 2, 1, &a[0], &m_ip[0], &m_w[0]);
        for (int i = 0; i < m_frameSize * 2; ++i) {
            a[i] /= m_frameSize;
        }
    }

    template <typename T>
    void FFTEngine<T>::fft(std::vector<std::complex<T>> & a)
    {
        assert(static_cast<int>(a.size()) == m_frameSize);
        cdft(m_frameSize * 2, -1, reinterpret_cast<T *>(&a[0]), &m_ip[0], &m_w[0]);
    }

    template <typename T>
    void FFTEngine<T>::ifft(std::vector<std::complex<T>> & a)
    {
        assert(static_cast<int>(a.size()) == m_frameSize);
        cdft(m_frameSize * 2, 1, reinterpret_cast<T *>(&a[0]), &m_ip[0], &m_w[0]);
        for (int i = 0; i < m_frameSize; ++i)
        {
            a[i] /= m_frameSize;
        }
    }

}
