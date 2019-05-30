#include "ssfe_ggm.hpp"

namespace ssfe {

void setup(Prms &t_prms, size_t N) {
    t_prms.g1=G1::random_element();
    t_prms.g2=G2::random_element();
    t_prms.N=N;
}

void keygen(Msk &t_msk, Prms t_prms) {
    ZZ_p d;
    while(true) {
        t_msk.B = random_mat_ZZ_p(t_prms.N,t_prms.N);
        d=determinant(t_msk.B);
        if (!IsZero(d)) {
            break;
        }
    }
    t_msk.Bstar=inv(t_msk.B);
    t_msk.Bstar=transpose(t_msk.Bstar);
}

void extract(Key &t_key, Vct t_y, Msk t_msk, Prms t_prms) {
    ZZ_p alpha;
    vec_ZZ_p alphayB;

    alpha= random_ZZ_p();
    t_y =  t_y * alpha;
    alphayB = t_msk.B * t_y;

    bgroup_batch_exp(t_key,t_prms.g2,alphayB);
}

void encrypt(Cph &t_cph, Vct t_x, Msk t_msk, Prms t_prms) {
    ZZ_p beta;
    vec_ZZ_p betaxBstar;

    beta=random_ZZ_p();
    t_x = t_x * beta;
    betaxBstar=t_msk.Bstar * t_x;

    bgroup_batch_exp(t_cph,t_prms.g1,betaxBstar);
}

bool decrypt(Cph t_cph, Key t_sk, Prms t_prms) {
    GT ip_exp;
    ip_exp=vector_G1_G2_ip(t_cph,t_sk);
    return (ip_exp==GT::one());
}

int key_size(Key t_sk) {
    int count=0;
    for (size_t i = 0; i < t_sk.size();i++) 
        count += t_sk[i].size_in_bits();
    return count;
}

int cph_size(Cph t_cph) {
    int count=0;
    for (size_t i = 0; i < t_cph.size();i++) 
        count += t_cph[i].size_in_bits();
    return count;
}

}