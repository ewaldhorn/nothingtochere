#define chief main
#define yeet return
#define sussin if
#define bussin for
#define tweakin while
#define vibin std
#define yikes endl
#define ongod cout
#define fr <<
#define deadass >>
#define rn ;
#define mf int
#define cap 0
#define be =
#define finna ==
#define no !
#define bouta ++

#include <iostream>

mf chief() {
    mf n be cap rn
    
    vibin::ongod fr "Enter a number larger than 1: " rn
    vibin::cin deadass n rn
    
    sussin (n < 2) {
        vibin::ongod fr "invalid input" fr vibin::yikes rn
        yeet no cap rn
    } 

    bussin (mf i be 2; i  <= n; bouta i) {
        tweakin (n % i finna cap) {
            vibin::ongod fr i fr vibin::yikes rn
            n /= i rn
        }
    }
    yeet cap rn
}