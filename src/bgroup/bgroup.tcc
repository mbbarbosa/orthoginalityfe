#include "bgroup.hpp"
#include "NTL/ZZ_limbs.h"
namespace ssfe {

using namespace NTL;

/* Used once in init, so can be slow */
template<mp_size_t n> 
void bigint_to_ZZ(ZZ &t_out, const libff::bigint<n> &t_in) {
    ZZ res;
    mpz_t tmp;
    size_t size;
    char *buf;
    
    mpz_init(tmp);
    t_in.to_mpz(tmp);

    size = mpz_sizeinbase (tmp, 10) + 2;
    buf = new char[size];

    mpz_get_str(buf,10,tmp);
    t_out=conv<ZZ>(buf);
    
    mpz_clear(tmp);
    delete[] buf;
}

void bgroup_init() {
    ZZ Fq_char;
    ZZ_p zzp_val;

    init_params();

    bigint_to_ZZ(Fq_char,Fq::field_char());
    ZZ_p::init(Fq_char);

}

void Fq_from_ZZ_p(Fq &t_out, const ZZ_p &t_in) {
    mpz_t tmp;
    size_t size;

    mpz_init(tmp);

    size = rep(t_in).size();
    mpz_import(tmp,size,-1,NTL_BITS_PER_LIMB_T / 8,0,0,ZZ_limbs_get(rep(t_in)));

    t_out=Fq(libff::bigint<Fq::num_limbs>(tmp));

    mpz_clear(tmp);
}

template<class T>
void bgroup_batch_exp(std::vector<T> &t_out,T t_g,vec_ZZ_p t_in) {
    size_t i;
    Fq e;
    assert(NTL_BITS_PER_LIMB_T % 8 == 0);
    assert(t_out.size()== (size_t)t_in.length());
    for (i = 0; i < t_out.size(); i++) {
        Fq_from_ZZ_p(e,t_in[i]);
        t_out[i]=e*t_g;
    }
}

GT vector_G1_G2_ip(std::vector<G1> t_i1, std::vector<G2> t_i2) {
    GT res;
    size_t i;
    res=GT::one();
    assert(t_i1.size() == t_i2.size());
    for(i=0;i<t_i1.size();i++) {
        res=res*pairing(t_i1[i],t_i2[i]);
    }
    return res;
}

}
