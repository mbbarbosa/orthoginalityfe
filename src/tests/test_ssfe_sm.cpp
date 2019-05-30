#include <iostream>
#include <cassert>

#include "libff/common/profiling.hpp"

#include <NTL/mat_ZZ_p.h>
#include <gmp.h>

#include "bgroup/bgroup.tcc"
#include "ssfe/ssfe_sm.tcc"

using namespace ssfe;

const size_t S = 128;
const size_t K = 2;

const size_t Repeat = 10;

int main() {
    Prms prms;
    Msk msk;
    Vct x;
    Vct y;
    Key sk(S);
    Cph cph(S);
    bool r;
    size_t i, j;

    bgroup_init();
    libff::start_profiling();

    for(i=0;i<Repeat;i++) {
        x.SetLength(S);
        y.SetLength(S);
        for(j=0;j<S;j++) {
            x[j]=random_ZZ_p();
            y[j]=random_ZZ_p();
            x[j+1]=x[j];
            y[j+1]=-y[j];
            j++;
        }

        setup(prms,S,K);
        keygen(msk,prms);

        libff::enter_block("Extract");
        extract(sk,y,msk,prms);
        libff::leave_block("Extract");

        libff::enter_block("Encrypt");
        encrypt(cph,x,msk,prms);
        libff::leave_block("Encrypt");

        libff::enter_block("Decrypt");
        r=decrypt(cph,sk,prms);
        libff::leave_block("Decrypt");

        //Orthogonality should be true
        assert(r != 0);

        y[0]=random_ZZ_p();
        extract(sk,y,msk,prms);
        r = decrypt(cph,sk,prms);

        //Orthogonality should be false
        assert(r == 0);
    }

    std::cout << "OK!\n";

    return 0;
}
