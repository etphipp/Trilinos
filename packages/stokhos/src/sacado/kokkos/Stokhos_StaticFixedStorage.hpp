// @HEADER
// ***********************************************************************
//
//                           Stokhos Package
//                 Copyright (2009) Sandia Corporation
//
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
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
// Questions? Contact Eric T. Phipps (etphipp@sandia.gov).
//
// ***********************************************************************
// @HEADER

#ifndef STOKHOS_STATIC_FIXED_STORAGE_HPP
#define STOKHOS_STATIC_FIXED_STORAGE_HPP

#include "Stokhos_StaticArrayTraits.hpp"
#include "Stokhos_MemoryTraits.hpp"

#include "Kokkos_Core_fwd.hpp"

#include "Sacado_Traits.hpp"
#include "Stokhos_KokkosTraits.hpp"
#include <sstream>

namespace Stokhos {

  namespace details {

    // Container class for a compile-time fixed array.
    // StaticFixedStorage below uses this, instead of a raw array, to support
    // constexpr constructors with c++11.  It is important that this class
    // not define any constructors, so that it can use aggregate initialization
    // in array_init below.
    template <typename T, int N, typename Device>
    struct static_array {
#if STOKHOS_ALIGN_MEMORY && ( defined(__INTEL_COMPILER) )
      T x[N]; __attribute__((aligned(MemTraits::Alignment)));
#else
      T x[N];
#endif
    };

#if defined(KOKKOS_ENABLE_CUDA)
    // Container class for a compile-time fixed array.
    // Specialization for Cuda without alignment
    template <typename T, int N>
    struct static_array<T,N,Kokkos::Cuda> {
      T x[N];
    };
#endif

    // Function for initializing static_array to a constant value, suitable
    // for constexpr evaluation (a little clunky until c++14).  Thanks to
    // this stackoverflow post for the idea:
    // https://stackoverflow.com/questions/23901394/c11-initialize-array-with-uniform-value-in-constexpr-function
    template <int N, typename Device>
    struct array_init {
      template <typename T, typename ...Tn>
      KOKKOS_INLINE_FUNCTION
      static constexpr
      auto apply(T v, Tn ...vs) ->
        decltype(array_init<N-1,Device>::apply(v, v, vs...))
      {
        return array_init<N-1,Device>::apply(v, v, vs...);
      }
    };


    template <typename Device>
    struct array_init<1,Device> {
      template <typename T, typename ...Tn>
      KOKKOS_INLINE_FUNCTION
      static constexpr
      auto apply(T v, Tn ...vs) -> static_array<T, sizeof...(vs)+1, Device>
      {
        return static_array<T, sizeof...(vs)+1, Device>{v, vs...};
      }
    };

  }

  //! Statically allocated storage class
  template <typename ordinal_t, typename value_t, int Num, typename device_t>
  class StaticFixedStorage {
  public:

    static const bool is_static = true ;
    static const int static_size = Num;
    static const bool supports_reset = false;

    typedef ordinal_t ordinal_type;
    typedef value_t value_type;
    typedef typename device_t::execution_space execution_space;
    typedef typename device_t::memory_space memory_space;
    typedef value_type& reference;
    typedef volatile value_type& volatile_reference;
    typedef const value_type& const_reference;
    typedef const volatile value_type& const_volatile_reference;
    typedef value_type* pointer;
    typedef volatile value_type* volatile_pointer;
    typedef const value_type* const_pointer;
    typedef const volatile value_type* const_volatile_pointer;
    typedef Stokhos::StaticArrayTraits<value_type,execution_space> ss;

    typedef typename Stokhos::MemoryTraits<memory_space> MemTraits;

    //! Turn StaticFixedStorage into a meta-function class usable with mpl::apply
    template <typename ord_t, typename val_t = value_t , typename dev_t = device_t >
    struct apply {
      typedef StaticFixedStorage<ord_t,val_t,Num,dev_t> type;
    };

    template <int N>
    struct apply_N {
      typedef StaticFixedStorage<ordinal_type,value_type,N,device_t> type;
    };

    //! Constructor
    KOKKOS_INLINE_FUNCTION
    constexpr StaticFixedStorage() = default;

    //! Constructor
    KOKKOS_INLINE_FUNCTION
    constexpr StaticFixedStorage(const ordinal_type& sz,
                                 const value_type& x = value_type(0.0)) :
      coeff_(details::array_init<Num,device_t>::apply(x))
    {
      //ss::fill(coeff_.x, Num, x);
    }

    //! Constructor from array
    KOKKOS_INLINE_FUNCTION
    StaticFixedStorage(const ordinal_type& sz, const value_type* x) {
      ss::copy(x, coeff_.x, sz);
    }

    //! Constructor for creating a view (not allowed)
    KOKKOS_INLINE_FUNCTION
    StaticFixedStorage(const ordinal_type& sz, pointer v, bool owned) {}

    //! Copy constructor
    KOKKOS_INLINE_FUNCTION
    StaticFixedStorage(const StaticFixedStorage& s) = default;

    //! Copy constructor
    KOKKOS_INLINE_FUNCTION
    StaticFixedStorage(const volatile StaticFixedStorage& s) {
      ss::copy(s.coeff_.x, coeff_.x, Num);
    }

    //! Destructor
    KOKKOS_INLINE_FUNCTION
    ~StaticFixedStorage() = default;

    //! Assignment operator
    KOKKOS_INLINE_FUNCTION
    StaticFixedStorage& operator=(const StaticFixedStorage& s) = default;

    //! Assignment operator
    KOKKOS_INLINE_FUNCTION
    StaticFixedStorage& operator=(const volatile StaticFixedStorage& s) {
      ss::copy(s.coeff_.x, coeff_.x, Num);
      return *this;
    }

    //! Assignment operator
    KOKKOS_INLINE_FUNCTION
    /*volatile*/ StaticFixedStorage&
    operator=(const StaticFixedStorage& s) volatile {
      ss::copy(s.coeff_.x, coeff_.x, Num);
      return const_cast<StaticFixedStorage&>(*this);
    }

    //! Assignment operator
    KOKKOS_INLINE_FUNCTION
    /*volatile*/ StaticFixedStorage&
    operator=(const volatile StaticFixedStorage& s) volatile {
      ss::copy(s.coeff_.x, coeff_.x, Num);
      return const_cast<StaticFixedStorage&>(*this);
    }

    //! Initialize values to a constant value
    KOKKOS_INLINE_FUNCTION
    void init(const_reference v) {
      ss::fill(coeff_.x, Num, v);
    }

    //! Initialize values to a constant value
    KOKKOS_INLINE_FUNCTION
    void init(const_reference v) volatile {
      ss::fill(coeff_.x, Num, v);
    }

    //! Initialize values to an array of values
    KOKKOS_INLINE_FUNCTION
    void init(const_pointer v, const ordinal_type& sz = 0) {
      if (sz == 0)
        ss::copy(v, coeff_.x, Num);
      else
        ss::copy(v, coeff_.x, sz);
    }

    //! Initialize values to an array of values
    KOKKOS_INLINE_FUNCTION
    void init(const_pointer v, const ordinal_type& sz = 0) volatile {
      if (sz == 0)
        ss::copy(v, coeff_.x, Num);
      else
        ss::copy(v, coeff_.x, sz);
    }

    //! Load values to an array of values
    KOKKOS_INLINE_FUNCTION
    void load(pointer v) {
      ss::copy(v, coeff_.x, Num);
    }

    //! Load values to an array of values
    KOKKOS_INLINE_FUNCTION
    void load(pointer v) volatile {
      ss::copy(v, coeff_.x, Num);
    }

    //! Resize to new size (values are preserved)
    KOKKOS_INLINE_FUNCTION
    void resize(const ordinal_type& sz) {}

    //! Resize to new size (values are preserved)
    KOKKOS_INLINE_FUNCTION
    void resize(const ordinal_type& sz) volatile {}

    //! Reset storage to given array, size, and stride
    KOKKOS_INLINE_FUNCTION
    void shallowReset(pointer v, const ordinal_type& sz,
                      const ordinal_type& stride, bool owned) {}

    //! Reset storage to given array, size, and stride
    KOKKOS_INLINE_FUNCTION
    void shallowReset(pointer v, const ordinal_type& sz,
                      const ordinal_type& stride, bool owned) volatile {}

    //! Return size
    KOKKOS_INLINE_FUNCTION
    static ordinal_type size() { return Num; }

    //! Coefficient access (avoid if possible)
    KOKKOS_INLINE_FUNCTION
    const_reference operator[] (const ordinal_type& i) const {
      return coeff_.x[i];
    }

    //! Coefficient access (avoid if possible)
    KOKKOS_INLINE_FUNCTION
    const_volatile_reference operator[] (const ordinal_type& i) const volatile {
      return coeff_.x[i];
    }

    //! Coefficient access (avoid if possible)
    KOKKOS_INLINE_FUNCTION
    reference operator[] (const ordinal_type& i) { return coeff_.x[i]; }

    //! Coefficient access (avoid if possible)
    KOKKOS_INLINE_FUNCTION
    volatile_reference operator[] (const ordinal_type& i) volatile {
      return coeff_.x[i]; }

    template <int i>
    KOKKOS_INLINE_FUNCTION
    reference getCoeff() { return coeff_.x[i]; }

    template <int i>
    KOKKOS_INLINE_FUNCTION
    volatile_reference getCoeff() volatile { return coeff_.x[i]; }

    template <int i>
    KOKKOS_INLINE_FUNCTION
    const_volatile_reference getCoeff() const volatile { return coeff_.x[i]; }

     template <int i>
    KOKKOS_INLINE_FUNCTION
    const_reference getCoeff() const { return coeff_.x[i]; }

    //! Get coefficients
    KOKKOS_INLINE_FUNCTION
    const_volatile_pointer coeff() const volatile { return coeff_.x; }

    //! Get coefficients
    KOKKOS_INLINE_FUNCTION
    const_pointer coeff() const { return coeff_.x; }

    //! Get coefficients
    KOKKOS_INLINE_FUNCTION
    volatile_pointer coeff() volatile { return coeff_.x; }

    //! Get coefficients
    KOKKOS_INLINE_FUNCTION
    pointer coeff() { return coeff_.x; }

  private:

    //! Coefficient values
    details::static_array<value_type,Num,device_t> coeff_;

  };

}

namespace Sacado {
  template <typename ordinal_t, typename value_t, int Num, typename device_t>
  struct StringName< Stokhos::StaticFixedStorage<ordinal_t,
                                                 value_t,
                                                 Num,
                                                 device_t> > {
    static std::string eval() {
      std::stringstream ss;
      ss << "Stokhos::StaticFixedStorage<"
         << StringName<ordinal_t>::eval() << ","
         << StringName<value_t>::eval() << ","
         << Num << ","
         << StringName<device_t>::eval() << ">";
      return ss.str();
    }
  };
}

#endif // STOKHOS_STATIC_FIXED_STORAGE_HPP
