#pragma once
#include <vector>
#include <cmath>
#include <cassert>
#include "fftsg_c.h"

namespace fftsg
{

    template <typename T>
    class DCTEngine
    {
        // Tにdouble型とfloat型のみ指定可能にする
        static_assert(
            std::is_same<T, double>::value || std::is_same<T, float>::value,
            "DCTEngine<T> only supports double and float.");

    private:
        const int m_frameSize;

        // m_ipとm_wは大浦版FFTが利用する事前計算領域
        // (あくまでnにだけ依存する計算だけなので, 同じインスタンスで
        //  dctやidctは気にせずに呼んで構わない)
        std::vector<int> m_ip;
        std::vector<T> m_w;

    public:
        explicit DCTEngine(int frameSize);

        // 離散コサイン変換
        void dct(T *a);
        void dct(std::vector<T> & a);

        // 逆離散コサイン変換
        void idct(T *a);
        void idct(std::vector<T> & a);

        int frameSize() const { return m_frameSize; }
    };

    template <typename T>
    DCTEngine<T>::DCTEngine(int frameSize)
        : m_frameSize(frameSize)
        , m_ip(2 + (1 << static_cast<int>(std::log(frameSize / 2 + 0.5) / std::log(2.0)) / 2))
        , m_w(frameSize * 5 / 4)
    {
        m_ip[0] = 0;
    }

    template <typename T>
    void DCTEngine<T>::dct(T *a)
    {
        ddct(m_frameSize, -1, a, &m_ip[0], &m_w[0]);
    }

    template <typename T>
    void DCTEngine<T>::dct(std::vector<T> & a)
    {
        assert(static_cast<int>(a.size()) == m_frameSize);
        ddct(m_frameSize, -1, &a[0], &m_ip[0], &m_w[0]);
    }

    template <typename T>
    void DCTEngine<T>::idct(T *a)
    {
        a[0] *= 0.5;
        ddct(m_frameSize, 1, a, &m_ip[0], &m_w[0]);
        for (int i = 0; i < m_frameSize; ++i)
        {
            a[i] *= static_cast<T>(2.0) / m_frameSize;
        }
    }

    template <typename T>
    void DCTEngine<T>::idct(std::vector<T> & a)
    {
        assert(static_cast<int>(a.size()) == m_frameSize);
        a[0] *= 0.5;
        ddct(m_frameSize, 1, &a[0], &m_ip[0], &m_w[0]);
        for (int i = 0; i < m_frameSize; ++i)
        {
            a[i] *= static_cast<T>(2.0) / m_frameSize;
        }
    }

}
