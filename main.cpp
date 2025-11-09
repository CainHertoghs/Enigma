#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "encryption/Enigma.h"

using namespace Encryption;

int main()
{
    // Known configurations
    Rotor rotor0("AJDKSIRUXBLHWTMCQGZNPYFVOE");
    Rotor rotor1("EKMFLGDQVZNTOWYHXUSPAIBRCJ");
    Rotor rotor2("BDFHJLCPRTXVZNYEIWGAKMUSQO");
    Rotor rotor3("THEQUICKBROWNFXJMPSVLAZYDG");
    Rotor rotor4("XANTIPESOKRWUDVBCFGHJLMQYZ");

    Reflector reflector("YRUHQSLDPXNGOKMIEBFZCWVJAT");

    /***************************************************************
     * Here the decription of the ciphertext is done with
     * positions (3,0,2) = (O, U, D)
     * plugboard: {(G,Q), (U,W), (F,K), (L,S), (C,Z), (Y,X)}
     ***************************************************************/
    // rotor3.setStartPosition('O');
    // rotor0.setStartPosition('U');
    // rotor2.setStartPosition('D');
    //
    // Enigma enigma{
    //     rotor3, rotor0, rotor2, reflector, {{{'G', 'Q'}, {'U', 'W'}, {'F', 'K'}, {'L', 'S'}, {'C', 'Z'}, {'Y', 'X'}}}
    // };
    // std::string text = enigma.encrypt(
    //     "PGWDJTWRAQJFJDLTOQLWGZZSNFADTWMJFJHKVYYFIIYBGSJIMAOKAGNYEDPJMSGZHKHPDNWIMZYBQGZACDYQHHFGUYSWJRMSQWJEHPSGFCBNNMFLXFQXBXDYAJLVMZDXXLEGEAQWCSIWYTCPJSMABNYYRZQSXFHBSVXKUTFDTWJFOCRIJFIUSGNPXAWYCFHVNCOIIUAPLZPAQJQNIWDYCDTKVFMSUWQNUHYQRFAANOMZAQVNMXZHUAWDOXGQJRPXWPESXZEDPLPDUMSGEVRPDSCEXPQVSBSGRUSPXYOPCFQEUJTLXMHAQQDAWSMJDUITVMNOPDNIOVOKUHTGBONGIJQMVLQIGLSNMNBSTITNPZVILKERIMOPLPSFFFVYNWCQOGDZSDDNXHHSNNQQWPNJTWBILLWMZPSHMEOLBJUESINPVMCANWVREOFXWWASELJDCIHPDMVDKMUBRYWFQFPZIVYKMLUGRPUDFQWLPRIUOZXARHQPZVYEZNCNVSYQFCBNLFGQLDODQJSXJGSBWUVDBVIKLRSMYPKSFFNGSIXKXXGJUFZDZWZQYTDXBUSXJCSSWDKFATQCYXEAYBJNTUXKHSQLAPHDBXSMCDHBMXJYKRJDVAYRKYHPSGVCBNCGNSMSYIWIKTBSTUGFPOAUCJMMGNWAVCYTTWQNIBEDRBNUSWVMPYEBKZGNLQFEUEXZSUXXMAODXUMRFXLKPGDCXEEZJMKYSFGVWPGTOCNXYRXIWOTESFVOKTQTAXZEQSYWXZQXWWPHULBNMRKXKYKIQXITEBJWLXKYMHBOCDTAUFGVVDCDAMVHBMOWDDNULXBVLYCNLVYRKXRKMLEJVHHXWZAILKWGKVKGHIKIYOVOOCDHRMBJYJUAYZIYSGDOEYSELOCATJCIGYNMJJNCJVSXWDBPXHYZTVXLNFLWCIICKYXQLRPFZYLTWURMLKAWNBTURLIRCJDSFQXPDTKUMTGHDQAIASIDAQBRDLORGSCNVSODANCAMOCXIQHZXYZZDJESUVNOEIVRVKXHIUYMIXZBHJTJHQRLHAJRDTJRBCMUDRAIOJELARZMHMOOUAHOHYRKZIOTLYUZEORDLHLCGITZBCCOWKXMXIXTNILSXSVKNTXYHTYLDFNGMEMXLTUECZTWGLWBHTYCMSTEPHFJZTGWCERFUUOJCOVIQOFUIEZKTJHJZZXXGWKSJTITDCIBKMVPPNVPQNJLYUPQIHIOQFGNCTUODSDNGSYWGQKWETKLBKSLNZSXPLJIENOQCMCZJMYLHXSKMIKUYWHXKZAZYQJIIMNCHGERPZELIPWGLDSHRUNNJWETCLAHPCJFMRCULYMKAZDSXRWNSFNIWHGIYNFRVTGYGJJMUCOOKPOGLZNBDRBOTEPGUCPLVUVDVNOTXVKKDQVWJSDSDTLUMVZFLDQIMKYBDUGJUOAYSWXCLFLCFEOGQSRELMOSTCDELSXJYDJYOFRYZJLMKQLWTNVWBYIOTQVNLZRFPHORGQTQIOJQJJZUDEXXSUKDIXLOQEAAXSOJCVPZSHPRMRINOXYLJDQZJIBWJZSPUATHPRYFUNWZDOUQGWDIHDFODSFDWQFSWLPYRVMESBLWCFJINYRUXNMPPKITMRFFDQZVLIIZKWTFYHTYWXTQOUWKVIIIUCRFJILPSZDRXSUJJGIWQHYZNYWKDGRFFDARFGPZCBHTYTGQEVGMSUNMGXZPBVITOTHQRENVJNAVAMNKPMPJFMAUCAXYMYIESSVLXOEVACZHFHZDMOFVMKRJJFJWXSWMMYYZXCKHFFBEPVDZDKRIUFHUYEVMDWCXQVFAQXBABVGHNOTSKNIWCDMWCBRRKGPWKDPLZPQRXWJGWWGTZMZEDGWALHWJVBATCBKDARLWXMMWAXSPEVCGVBOXYZAZBFNSQHUDNAZDXVGFEKRQNWSDDZBNNTOMIM");
    // std::cout << text << std::endl;

    // Identity plugboard
    PlugBoard identityPB;

    std::string ciphertext = "PGWDJTWRAQJFJDLTOQ"; // Only 18 letters corresponding to crib
    std::string crib = "DEOPGAVEVOORENIGMA";

    if (ciphertext.size() < crib.size())
    {
        std::cerr << "Ciphertext is korter dan crib. Pas input aan.\n";
        return 1;
    }

    std::vector<Rotor> rotors = {rotor0, rotor1, rotor2, rotor3, rotor4};
    size_t len = crib.size();

    const double threshold = 30.0; // Treshold (standard 30%)

    int totalRotorOrders = 0;
    int totalMatchesFound = 0;

    auto t0 = std::chrono::steady_clock::now();

    for (size_t i = 0; i < rotors.size(); ++i)
    {
        for (size_t j = 0; j < rotors.size(); ++j)
        {
            if (j == i) continue;
            for (size_t k = 0; k < rotors.size(); ++k)
            {
                if (k == i || k == j) continue;

                ++totalRotorOrders;
                Enigma prototype(rotors[i], rotors[j], rotors[k], reflector, identityPB);

                for (char L = 'A'; L <= 'Z'; ++L)
                {
                    for (char M = 'A'; M <= 'Z'; ++M)
                    {
                        for (char R = 'A'; R <= 'Z'; ++R)
                        {
                            Enigma e = prototype;
                            e.setRotorStartPositions(L, M, R);
                            e.resetToStartPositions();

                            std::string prefix = e.decryptString(ciphertext.substr(0, len));

                            int matches = 0;
                            for (size_t idx = 0; idx < len; ++idx)
                                if (prefix[idx] == crib[idx]) ++matches;

                            double similarity = 100.0 * matches / len;

                            if (similarity >= threshold)
                            {
                                std::cout << "MATCH: Rotors=(" << i << "," << j << "," << k << ")"
                                    << " Start=" << L << M << R
                                    << " Matches=" << matches << "/" << len
                                    << " (" << static_cast<int>(similarity) << "%)\n";
                                ++totalMatchesFound;
                            }
                        }
                    }
                }
            }
        }
    }

    auto t1 = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

    std::cout << "Klaar. Rotororders getest: " << totalRotorOrders
        << ". Matches gevonden: " << totalMatchesFound
        << ". Tijd: " << ms << " ms\n";

    return 0;
}
