#include <vector>
#include <iostream>

#define max_val 1
#define min_val -1
//t‰ydellinen tieto ( molemmat tiet‰‰ t‰ydellisesti pelitilanteen)

#define TIKUT 221 //tikkujen m‰‰r‰  



int minimax_maxille[TIKUT] = {};  //alustuu t‰yteen nollia tyhj‰t hakasulkeet (jossei globaali arvo alusta muutenkin??)
int minimax_minille[TIKUT] = {};




// siirtogeneraattori
std::vector<int> get_legal_moves(int n)
{
    std::vector<int> retval;
    for (int i = 1; (i <= n) && (i <= 3); ++i)
        retval.push_back(i);

    return retval;
}

// pelipuuhaku  //max = siirtovuoro (min ja max pelaa) min haluaa minimoida, 
// max maximoida tms tuloksen, 1 = max voittaa, -1 min voittaa
int minimax(int const n, bool const max)
{
    //Jos ratkaistu jo, otetaan vaan arvo, ei tarvitse laskea joka tulosta , 
    // eik‰ tule edes puuta.. paljon nopeampi,
    //  ilman taulukkoa 29 kesti kauan, taulukolla 229 kest‰‰ v‰h‰n..
    if (max && minimax_maxille[n - 1])
    {
        return minimax_maxille[n - 1];
    }
    //jos minin siirtovuoro (ei max), ja ratkaistu jo siirtovuoro t‰ll‰ tikkum‰‰r‰ll‰
    if (!max && minimax_minille[n - 1])
    {
        return minimax_minille[n - 1];
    }

    if (n == 0)
        return max ? max_val : min_val;
    if (n == 1)
        return max ? min_val : max_val;

    std::vector<int> mv = get_legal_moves(n); /* get legal moves palauttaa vektorin laillisista siirroista, esim. 1,2,3 */
    int best_val;
    if (max) {
        best_val = min_val;
        for (int const lm : mv) {
            int const val = minimax(n - lm, false);
            if (val > best_val)
                best_val = val;
        }
    }
    else { // min
        best_val = max_val;
        for (int const lm : mv) {
            int const val = minimax(n - lm, true);
            if (val < best_val)
                best_val = val;
        }
    }

    //ajetaan uudestaan jos ei ole jo taulukossa

    if (max) { minimax_maxille[n - 1] = best_val; }

    else { minimax_minille[n - 1] = best_val; }

    return best_val;
}
//pit‰‰ ottaa huomioon kumman siirtovuoro, esim. minin siirto ja 18 tikkua j‰ljell‰
//on eri kuin maxin siirto ja 18 tikkua j‰ljell‰


int main()
{
    int tulos = minimax(TIKUT, true);
    //21 :  aloittaja h‰vi‰‰ jos molemmat pelaavat t‰ydelliseti
    //siit‰ kumpaankin suuntaan aloittaja h‰vi‰‰ aina nelj‰ll‰ erikokoisen / joka nelj‰nnen

    std::cout << "voittaja: " << tulos << "\n";

    return 0;
}