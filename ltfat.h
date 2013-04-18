#ifndef LTFAT_H
#define LTFAT_H 1

#include "fftw3.h"
#include "cblas.h"

/* Allow using arbitrary complex types. Assumes identical memory layout. */
#ifndef LTFAT_USER_COMPLEX
typedef fftw_complex  ltfat_complex;
typedef fftwf_complex ltfat_scomplex;
#endif

/* BEGIN_C_DECLS */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Handle Windows DLL files, not used */

#if defined(LTFAT_DLL_NEVERUSED) && (defined(_WIN32) || defined(__WIN32__))
#  if defined(COMPILING_LTFAT) /* defined by Makefile when compiling LTFAT */
#    define LTFAT_EXTERN extern __declspec(dllexport)
#  else /* user is calling LTFAT; import symbol */
#    define LTFAT_EXTERN extern __declspec(dllimport)
#  endif
#else
#  define LTFAT_EXTERN extern
#endif

  /* -------- Define the double precision routines ----- */

#define LTFAT_H_REAL double
#define LTFAT_H_COMPLEX fftw_complex
#define LTFAT_H_COMPLEXH _Complex double
#define LTFAT_H_TYPE LTFAT_H_REAL
#define LTFAT_H_NAME(name) name
#define LTFAT_H_COMPLEXNAME(name) c ## name
#define LTFAT_H_FFTW(name) fftw_ ## name
/*
#define PLOT(...) __VA__ARGS__
#define LTFAT_H_NAMEVAR(name,...) template <class LTFAT_H_REAL, class LTFAT_H_COMPLEX> PLOT(name)(__VA_ARGS__);
#define LTFAT_H_NAMEVAR(name,...) template <class LTFAT_H_TYPE> PLOT(name)(__VA_ARGS__);
#define LTFAT_H_NAMEVAR(name,...) template <> PLOT(name)<double>(__VA_ARGS__)  \
{                                                                               \
PLOT(name)();                                                                   \
}
*/
#include "ltfat_typeindependent.h"
#undef LTFAT_H_COMPLEX
#define LTFAT_H_COMPLEX LTFAT_H_COMPLEXH
#include "ltfat_typecomplexindependent.h"

#undef LTFAT_H_TYPE
#undef LTFAT_H_NAME
#define LTFAT_H_TYPE LTFAT_H_COMPLEX
#define LTFAT_H_NAME(name) LTFAT_H_COMPLEXNAME(name)


#include "ltfat_typecomplexindependent.h"

#undef LTFAT_H_REAL
#undef LTFAT_H_COMPLEX
#undef LTFAT_H_COMPLEXH
#undef LTFAT_H_NAME
#undef LTFAT_H_FFTW
#undef LTFAT_H_TYPE
#undef LTFAT_H_COMPLEXNAME

  /* -------- Define the single precision routines ----- */

#define LTFAT_H_REAL float
#define LTFAT_H_COMPLEX fftwf_complex
#define LTFAT_H_COMPLEXH _Complex float
#define LTFAT_H_NAME(name) s ## name
#define LTFAT_H_COMPLEXNAME(name) cs ## name
#define LTFAT_H_FFTW(name) fftwf_ ## name
#define LTFAT_H_TYPE LTFAT_H_REAL

#include "ltfat_typeindependent.h"
#undef LTFAT_H_COMPLEX
#define LTFAT_H_COMPLEX LTFAT_H_COMPLEXH
#include "ltfat_typecomplexindependent.h"

#undef LTFAT_H_TYPE
#undef LTFAT_H_NAME
#define LTFAT_H_TYPE LTFAT_H_COMPLEX
#define LTFAT_H_NAME(name) LTFAT_H_COMPLEXNAME(name)

#include "ltfat_typecomplexindependent.h"

#undef LTFAT_H_REAL
#undef LTFAT_H_COMPLEX
#undef LTFAT_H_COMPLEXH
#undef LTFAT_H_TYPE
#undef LTFAT_H_NAME
#undef LTFAT_H_FFTW
#undef LTFAT_H_COMPLEXNAME


  /* -------- Define routines that do not change between single/double-- */

int gcd(const int a, const int b, int *r, int *s );

void* ltfat_malloc (size_t n);
void* ltfat_calloc (size_t nmemb, size_t size);
void* ltfat_realloc (void *ptr, size_t n);
void  ltfat_free(void *ptr);

void fftindex(const int N, int *indexout);

int makelarger(const int L, const int K);
int int_max(const int a, const int b);
int int_min(const int a, const int b);
int lcm(const int a, const int b);
void gabimagepars(const int Ls, const int x, const int y,
		  int *a, int *M, int *L, int *N, int *Ngood);

int wfacreal_size(const int L, const int a, const int M);

#ifdef __cplusplus
}  /* extern "C" */
#endif /* __cplusplus */

/* END_C_DECLS */

#endif /* !LTFAT_H */
