#ifndef __BGROUP_HEADER
#define __BGROUP_HEADER

#define CURVE_BN128

#ifdef CURVE_BN128

#include <libff/algebra/curves/bn128/bn128_pp.hpp>

namespace ssfe {

typedef libff::Fr<libff::bn128_pp> Fq;
typedef libff::G1<libff::bn128_pp> G1;
typedef libff::G2<libff::bn128_pp> G2;
typedef libff::GT<libff::bn128_pp> GT;

auto pairing=libff::bn128_pp::reduced_pairing;
auto init_params=libff::bn128_pp::init_public_params;

}

#else

#include <libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp>

namespace ssfe {

typedef libff::Fr<libff::alt_bn128_pp> Fq;
typedef libff::G1<libff::alt_bn128_pp> G1;
typedef libff::G2<libff::alt_bn128_pp> G2;
typedef libff::GT<libff::alt_bn128_pp> GT;

auto pairing=libff::alt_bn128_pp::reduced_pairing;
auto init_params=libff::alt_bn128_pp::init_public_params;

}

#endif

namespace ssfe {

using namespace NTL;

void bgroup_init();

template<class T>
void bgroup_batch_exp(std::vector<T> &t_out,T t_g,vec_ZZ_p t_in);

GT vector_G1_G2_ip(std::vector<G1> t_i1, std::vector<G2> t_i2);

}

#endif
