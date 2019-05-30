#include "ssfe_sm.hpp"

namespace ssfe {

void setup(Prms &t_prms, size_t N, size_t K) {
    t_prms.g1=G1::random_element();
    t_prms.g2=G2::random_element();
    t_prms.N=N;
    t_prms.K=K;
}

void keygen(Msk &t_msk, Prms t_prms) {
    size_t i;
    t_msk.Ain = random_mat_ZZ_p(t_prms.K+1,t_prms.K);
    t_msk.Win.reserve(t_prms.N);
    for(i=0;i<t_prms.N;i++) {
        t_msk.Win.push_back(random_mat_ZZ_p(t_prms.K+1,t_prms.K+1));
    }
    t_msk.Aout = random_mat_ZZ_p(t_prms.K+1,t_prms.K);
    t_msk.Wout.reserve(t_prms.N+1);
    for(i=0;i<t_prms.N+1;i++) {
        t_msk.Wout.push_back(random_mat_ZZ_p(t_prms.K+1,t_prms.K+1));
    }
}

void extract(Key &t_key, Vct t_y, Msk t_msk, Prms t_prms) {
    mat_ZZ_p r;
    mat_ZZ_p Uout;
    mat_ZZ_p s;
    mat_ZZ_p U;
    mat_ZZ_p M0;
    std::vector<mat_ZZ_p> skin(t_prms.N+1);
    std::vector<mat_ZZ_p> skout(t_prms.N+2);
    vec_ZZ_p skoute;
    size_t i;

    r=random_mat_ZZ_p(t_prms.K+1,1);
    skin[0].SetDims(t_prms.K+1,1);
    clear(skin[0]);
    for(i=0;i<t_prms.N;i++) {
        skin[i+1]=r*t_y[i]; //K+1 x 1
        skin[0] = skin[0] - t_msk.Win[i]*skin[i+1];
    }

    s = random_mat_ZZ_p(1,t_prms.K);
    M0= s * transpose(t_msk.Aout); //1 x K+1

    U = random_mat_ZZ_p(t_prms.K+1,1);

    t_key=std::vector<std::vector<G2>>(t_prms.N+2);
    t_key[0]=std::vector<G2>(t_prms.K+1);
    bgroup_batch_exp(t_key[0],t_prms.g2,(vec_ZZ_p)M0[0]);

    for (i=0;i<t_prms.N+1;i++) {
        skoute = (M0*(U*transpose(skin[i])+t_msk.Wout[i]))[0];
        t_key[i+1]=std::vector<G2>(t_prms.K+1);
        bgroup_batch_exp(t_key[i+1],t_prms.g2,skoute);
    }

}

void encrypt(Cph &t_cph, Vct t_x, Msk t_msk, Prms t_prms) {
    ZZ_p r;
    mat_ZZ_p Uout;
    mat_ZZ_p s;
    mat_ZZ_p U;
    mat_ZZ_p M0;
    std::vector<mat_ZZ_p> cphin(t_prms.N+1);
    std::vector<mat_ZZ_p> cphout(t_prms.N+2);
    vec_ZZ_p cphoute;
    size_t i;

    s = random_mat_ZZ_p(1,t_prms.K);
    M0= s * transpose(t_msk.Ain); 

    cphin[0]=M0;
    U = random_mat_ZZ_p(t_prms.K+1,t_prms.K+1);
    for(i=0;i<t_prms.N;i++) {
        cphin[i+1]=M0*(U*t_x[i]+t_msk.Win[i]);
    }

    r=random_ZZ_p();
    cphout[0].SetDims(t_prms.K+1,1);
    clear(cphout[0]);
    for(i=0;i<t_prms.N+1;i++) {
        cphout[i+1]=r*cphin[i]; 
        cphout[0] = cphout[0] - t_msk.Wout[i]*transpose(cphout[i+1]);
    }


    t_cph=std::vector<std::vector<G1>>(t_prms.N+2);
    t_cph[0]=std::vector<G1>(t_prms.K+1);
    bgroup_batch_exp(t_cph[0],t_prms.g1,transpose(cphout[0])[0]);
    for (i=1;i<t_prms.N+2;i++) {
        t_cph[i]=std::vector<G1>(t_prms.K+1);
        bgroup_batch_exp(t_cph[i],t_prms.g1,cphout[i][0]);
    }
    
}

bool decrypt(Cph t_cph, Key t_sk, Prms t_prms) {
    GT ip_exp;
    size_t i;
    ip_exp=GT::one();
    for(i=0;i<t_prms.N+2;i++) {
        ip_exp=ip_exp * vector_G1_G2_ip(t_cph[i],t_sk[i]);
    }
    return (ip_exp==GT::one());
}


int key_size(Key t_sk) {
    int count=0;
    for (size_t i = 0; i < t_sk.size();i++) 
        for (size_t j = 0; j < t_sk[i].size();j++) 
            count += t_sk[i][j].size_in_bits();
    return count;
}

int cph_size(Cph t_cph) {
    int count=0;
    for (size_t i = 0; i < t_cph.size();i++) 
        for (size_t j = 0; j < t_cph[i].size();j++) 
            count += t_cph[i][j].size_in_bits();
    return count;
}

}