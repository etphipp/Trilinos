/*
//@HEADER
// ************************************************************************
//
//          Kokkos: Node API and Parallel Node Kernels
//              Copyright (2008) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Michael A. Heroux (maherou@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#include "Tpetra_Details_cublasGemv.hpp"
#include "Kokkos_Macros.hpp"
#ifdef KOKKOS_ENABLE_CUDA
#  include <cublas.h>
#endif // KOKKOS_ENABLE_CUDA
#include <sstream>
#include <stdexcept>

namespace Tpetra {
namespace Details {
namespace Blas {
namespace Cublas {
namespace Impl {

void
cgemv (const char char_trans,
       const int m,
       const int n,
       const Kokkos::complex<float>& alpha,
       const Kokkos::complex<float> A[],
       const int lda,
       const Kokkos::complex<float> x[],
       const int incx,
       const Kokkos::complex<float>& beta,
       Kokkos::complex<float> y[],
       const int incy)
{
#ifdef KOKKOS_ENABLE_CUDA
  const cuComplex alpha_c = make_cuFloatComplex (alpha.real (), alpha.imag ());
  const cuComplex beta_c = make_cuFloatComplex (beta.real (), beta.imag ());
  cublasCgemv (char_trans,  m, n,
               alpha_c, reinterpret_cast<const cuComplex*> (A), lda,
               reinterpret_cast<const cuComplex*> (x), incx,
               beta_c, reinterpret_cast<cuComplex*> (y), incy);
  cublasStatus info = cublasGetError ();
  if (info != CUBLAS_STATUS_SUCCESS) {
    std::ostringstream err;
    err << "cublasCgemv failed with status " << info << ".";
    throw std::runtime_error (err.str ());
  }
#else // NOT KOKKOS_ENABLE_CUDA
  throw std::runtime_error ("You must enable CUDA in your Trilinos build in "
                            "order to invoke cuBLAS functions in Tpetra.");
#endif // KOKKOS_ENABLE_CUDA
}

void
dgemv (const char char_trans,
       const int m,
       const int n,
       const double alpha,
       const double A[],
       const int lda,
       const double x[],
       const int incx,
       const double beta,
       double y[],
       const int incy)
{
#ifdef KOKKOS_ENABLE_CUDA
  ::cublasDgemv (char_trans, m, n,
                 alpha, A, lda,
                 x, incx,
                 beta, y, incy);
  cublasStatus info = cublasGetError ();
  if (info != CUBLAS_STATUS_SUCCESS) {
    std::ostringstream err;
    err << "cublasDgemv failed with status " << info << ".";
    throw std::runtime_error (err.str ());
  }
#else // NOT KOKKOS_ENABLE_CUDA
  throw std::runtime_error ("You must enable CUDA in your Trilinos build in "
                            "order to invoke cuBLAS functions in Tpetra.");
#endif // KOKKOS_ENABLE_CUDA
}

void
sgemv (const char char_trans,
       const int m,
       const int n,
       const float alpha,
       const float A[],
       const int lda,
       const float x[],
       const int incx,
       const float beta,
       float y[],
       const int incy)
{
#ifdef KOKKOS_ENABLE_CUDA
  ::cublasSgemv (char_trans, m, n,
                 alpha, A, lda,
                 x, incx,
                 beta, y, incy);
  cublasStatus info = cublasGetError ();
  if (info != CUBLAS_STATUS_SUCCESS) {
    std::ostringstream err;
    err << "cublasSgemv failed with status " << info << ".";
    throw std::runtime_error (err.str ());
  }
#else // NOT KOKKOS_ENABLE_CUDA
  throw std::runtime_error ("You must enable CUDA in your Trilinos build in "
                            "order to invoke cuBLAS functions in Tpetra.");
#endif // KOKKOS_ENABLE_CUDA
}

void
zgemv (const char char_trans,
       const int m,
       const int n,
       const Kokkos::complex<double>& alpha,
       const Kokkos::complex<double> A[],
       const int lda,
       const Kokkos::complex<double> x[],
       const int incx,
       const Kokkos::complex<double>& beta,
       Kokkos::complex<double> y[],
       const int incy)
{
#ifdef KOKKOS_ENABLE_CUDA
  const cuDoubleComplex alpha_c =
    make_cuDoubleComplex (alpha.real (), alpha.imag ());
  const cuDoubleComplex beta_c =
    make_cuDoubleComplex (beta.real (), beta.imag ());
  cublasZgemv (char_trans, m, n,
               alpha_c, reinterpret_cast<const cuDoubleComplex*> (A), lda,
               reinterpret_cast<const cuDoubleComplex*> (x), incx,
               beta_c, reinterpret_cast<cuDoubleComplex*> (y), incy);
  cublasStatus info = cublasGetError ();
  if (info != CUBLAS_STATUS_SUCCESS) {
    std::ostringstream err;
    err << "cublasCgemv failed with status " << info << ".";
    throw std::runtime_error (err.str ());
  }
#else // NOT KOKKOS_ENABLE_CUDA
  throw std::runtime_error ("You must enable CUDA in your Trilinos build in "
                            "order to invoke cuBLAS functions in Tpetra.");
#endif // KOKKOS_ENABLE_CUDA
}

} // namespace Impl
} // namespace Cublas
} // namespace Blas
} // namespace Details
} // namespace Tpetra
