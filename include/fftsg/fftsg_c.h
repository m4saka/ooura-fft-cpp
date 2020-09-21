#ifndef FFTSG_C_H
#define FFTSG_C_H

#ifdef __cplusplus
namespace fftsg { extern "C" {
#endif

// double版
void cdft(int n, int isgn, double *a, int *ip, double *w);
void rdft(int n, int isgn, double *a, int *ip, double *w);
void ddct(int n, int isgn, double *a, int *ip, double *w);
void ddst(int n, int isgn, double *a, int *ip, double *w);
void dfct(int n, double *a, double *t, int *ip, double *w);
void dfst(int n, double *a, double *t, int *ip, double *w);

// float版
void cdftf(int n, int isgn, float *a, int *ip, float *w);
void rdftf(int n, int isgn, float *a, int *ip, float *w);
void ddctf(int n, int isgn, float *a, int *ip, float *w);
void ddstf(int n, int isgn, float *a, int *ip, float *w);
void dfctf(int n, float *a, float *t, int *ip, float *w);
void dfstf(int n, float *a, float *t, int *ip, float *w);

#ifdef __cplusplus
}

// float版(オーバーロード)
void cdft(int n, int isgn, float *a, int *ip, float *w);
void rdft(int n, int isgn, float *a, int *ip, float *w);
void ddct(int n, int isgn, float *a, int *ip, float *w);
void ddst(int n, int isgn, float *a, int *ip, float *w);
void dfct(int n, float *a, float *t, int *ip, float *w);
void dfst(int n, float *a, float *t, int *ip, float *w);

}
#endif

#endif
