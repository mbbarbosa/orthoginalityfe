#ifndef __SSFE_GGM_HEADER
#define __SSFE_GGM_HEADER

namespace ssfe {

class Prms {
public:
    G1 g1;
    G2 g2;
    size_t N;
    size_t K;
};

class Msk {
public:
    mat_ZZ_p Ain;
    std::vector<mat_ZZ_p> Win;
    mat_ZZ_p Aout;
    std::vector<mat_ZZ_p> Wout;
};

typedef vec_ZZ_p Vct;
typedef std::vector<std::vector<G2>> Key;
typedef std::vector<std::vector<G1>> Cph;

void setup(Prms &t_prms, size_t N, size_t K);
void keygen(Msk &t_msk, Prms t_prms);
void extract(Key &t_key, Vct t_y, Msk t_msk, Prms t_prms);
void encrypt(Cph &t_cph, Vct t_x, Msk t_msk, Prms t_prms);
bool decrypt(Cph t_cph, Key t_sk, Prms t_prms);

int key_size(Key t_sk);
int cph_size(Cph t_cph);

}

#endif