#define TYPEDEPARGS 0, 1
#define SINGLEARGS
#define COMPLEXINDEPENDENT
#define OCTFILENAME comp_idwilt // change to filename
#define OCTFILEHELP "This function calls the C-library\n\
                     coef=comp_dwilt_fb(f,g,M,L);\n\
                     Yeah."


#include "ltfat_oct_template_helper.h"
// octave_idx_type is 32 or 64 bit signed integer
/*
  dgtreal_ola forwarders
*/

static inline void
fwd_idwilt_fb(const Complex *c, const Complex *g,
             const octave_idx_type L, const octave_idx_type gl,
             const octave_idx_type W, const octave_idx_type M, 
             Complex *f)
{
   idwilt_fb_cd(reinterpret_cast<const double _Complex*>(c),
               reinterpret_cast<const double _Complex*>(g),
               L, gl, W,M, reinterpret_cast<double _Complex*>(f));
}

static inline void 
fwd_idwilt_fb(const FloatComplex *c, const FloatComplex *g,
             const octave_idx_type L,  const octave_idx_type gl,
             const octave_idx_type W, const octave_idx_type M, 
             FloatComplex *f)
{
   idwilt_fb_cs(reinterpret_cast<const float _Complex*>(c),
               reinterpret_cast<const float _Complex*>(g),
               L, gl,W,M,
               reinterpret_cast<float _Complex*>(f));
}

static inline void
fwd_idwilt_fb(const double *c, const double *g,
             const octave_idx_type L,  const octave_idx_type gl,
             const octave_idx_type W, const octave_idx_type M, 
             double *f)
{
   idwilt_fb_d(c,g,L,gl,W,M,f);
}

static inline void
fwd_idwilt_fb(const float *c, const float *g,
             const octave_idx_type L,  const octave_idx_type gl,
             const octave_idx_type W, const octave_idx_type M, 
             float *f)
{
   idwilt_fb_s(c,g,L,gl,W,M,f);
}

static inline void
fwd_idwilt_long(const Complex *c, const Complex *g,
               const octave_idx_type L, const octave_idx_type W, 
               const octave_idx_type M, Complex *f)
{
   idwilt_long_cd(reinterpret_cast<const double _Complex*>(c),
                 reinterpret_cast<const double _Complex*>(g),
                 L,W,M, reinterpret_cast<double _Complex*>(f));
}

static inline void 
fwd_idwilt_long(const FloatComplex *c, const FloatComplex *g,
               const octave_idx_type L, const octave_idx_type W, 
               const octave_idx_type M, FloatComplex *f)
{
   idwilt_long_cs(reinterpret_cast<const float _Complex*>(c),
                 reinterpret_cast<const float _Complex*>(g),
                 L,W,M, reinterpret_cast<float _Complex*>(f));
}

static inline void
fwd_idwilt_long(const double *c, const double *g,
               const octave_idx_type L, const octave_idx_type W, 
               const octave_idx_type M, double *f)
{
   idwilt_long_d(c,g,L,W,M,f);
}

static inline void
fwd_idwilt_long(const float *c, const float *g,
               const octave_idx_type L, const octave_idx_type W, 
               const octave_idx_type M, float *f)
{
   idwilt_long_s(c,g,L,W,M,f);
}

template <class LTFAT_TYPE, class LTFAT_REAL, class LTFAT_COMPLEX>
octave_value_list octFunction(const octave_value_list& args, int nargout)
{
   DEBUGINFO;

   MArray<LTFAT_TYPE> c = ltfatOctArray<LTFAT_TYPE>(args(0));
   MArray<LTFAT_TYPE> g = ltfatOctArray<LTFAT_TYPE>(args(1));
   
   const octave_idx_type M = c.rows()/2;
   const octave_idx_type gl = g.nelem();
   const octave_idx_type N = 2*c.columns();
   const octave_idx_type L = N*M;
   const octave_idx_type W = c.nelem()/L;

   MArray<LTFAT_TYPE> f(dim_vector(L,W)); 

   if(gl<L)
   {     
      fwd_idwilt_fb(c.data(),g.data(),L, gl, W, M,f.fortran_vec());
   }
   else
   {
      fwd_idwilt_long(c.data(),g.data(),L, W, M,f.fortran_vec());
   }

   return octave_value(f);
}

