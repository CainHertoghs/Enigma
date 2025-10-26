// main_with_plug.cpp
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <map>
#include "encryption/Enigma.h"

// compile: g++ -std=c++17 main_with_plug.cpp encryption/Enigma.cpp -O2 -o withplug

int main()
{
    using namespace Encryption;

    // --- definieer je 5 rotors / reflector zoals eerder ---
    Rotor rotor0("AJDKSIRUXBLHWTMCQGZNPYFVOE");
    Rotor rotor1("EKMFLGDQVZNTOWYHXUSPAIBRCJ");
    Rotor rotor2("BDFHJLCPRTXVZNYEIWGAKMUSQO");
    Rotor rotor3("THEQUICKBROWNFXJMPSVLAZYDG");
    Rotor rotor4("XANTIPESOKRWUDVBCFGHJLMQYZ");

    Reflector reflector("YRUHQSLDPXNGOKMIEBFZCWVJAT");
    rotor3.setStartPosition('O');
    rotor0.setStartPosition('U');
    rotor2.setStartPosition('D');

    Enigma engima = Enigma{rotor3, rotor0, rotor2, reflector, PlugBoard{{{'G', 'Q'}, {'W', 'U'}, {'L', 'S'}, {'F', 'K'}}}};


    std::cout << engima.encrypt("PGWDJTWRAQJFJDLTOQLWGZZSNFADTWMJFJHKVYYFIIYBGSJIMAOKAGNYEDPJMSGZHKHPDNWIMZYBQGZACDYQHHFGUYSWJRMSQWJEHPSGFCBNNMFLXFQXBXDYAJLVMZDXXLEGEAQWCSIWYTCPJSMABNYYRZQSXFHBSVXKUTFDTWJFOCRIJFIUSGNPXAWYCFHVNCOIIUAPLZPAQJQNIWDYCDTKVFMSUWQNUHYQRFAANOMZAQVNMXZHUAWDOXGQJRPXWPESXZEDPLPDUMSGEVRPDSCEXPQVSBSGRUSPXYOPCFQEUJTLXMHAQQDAWSMJDUITVMNOPDNIOVOKUHTGBONGIJQMVLQIGLSNMNBSTITNPZVILKERIMOPLPSFFFVYNWCQOGDZSDDNXHHSNNQQWPNJTWBILLWMZPSHMEOLBJUESINPVMCANWVREOFXWWASELJDCIHPDMVDKMUBRYWFQFPZIVYKMLUGRPUDFQWLPRIUOZXARHQPZVYEZNCNVSYQFCBNLFGQLDODQJSXJGSBWUVDBVIKLRSMYPKSFFNGSIXKXXGJUFZDZWZQYTDXBUSXJCSSWDKFATQCYXEAYBJNTUXKHSQLAPHDBXSMCDHBMXJYKRJDVAYRKYHPSGVCBNCGNSMSYIWIKTBSTUGFPOAUCJMMGNWAVCYTTWQNIBEDRBNUSWVMPYEBKZGNLQFEUEXZSUXXMAODXUMRFXLKPGDCXEEZJMKYSFGVWPGTOCNXYRXIWOTESFVOKTQTAXZEQSYWXZQXWWPHULBNMRKXKYKIQXITEBJWLXKYMHBOCDTAUFGVVDCDAMVHBMOWDDNULXBVLYCNLVYRKXRKMLEJVHHXWZAILKWGKVKGHIKIYOVOOCDHRMBJYJUAYZIYSGDOEYSELOCATJCIGYNMJJNCJVSXWDBPXHYZTVXLNFLWCIICKYXQLRPFZYLTWURMLKAWNBTURLIRCJDSFQXPDTKUMTGHDQAIASIDAQBRDLORGSCNVSODANCAMOCXIQHZXYZZDJESUVNOEIVRVKXHIUYMIXZBHJTJHQRLHAJRDTJRBCMUDRAIOJELARZMHMOOUAHOHYRKZIOTLYUZEORDLHLCGITZBCCOWKXMXIXTNILSXSVKNTXYHTYLDFNGMEMXLTUECZTWGLWBHTYCMSTEPHFJZTGWCERFUUOJCOVIQOFUIEZKTJHJZZXXGWKSJTITDCIBKMVPPNVPQNJLYUPQIHIOQFGNCTUODSDNGSYWGQKWETKLBKSLNZSXPLJIENOQCMCZJMYLHXSKMIKUYWHXKZAZYQJIIMNCHGERPZELIPWGLDSHRUNNJWETCLAHPCJFMRCULYMKAZDSXRWNSFNIWHGIYNFRVTGYGJJMUCOOKPOGLZNBDRBOTEPGUCPLVUVDVNOTXVKKDQVWJSDSDTLUMVZFLDQIMKYBDUGJUOAYSWXCLFLCFEOGQSRELMOSTCDELSXJYDJYOFRYZJLMKQLWTNVWBYIOTQVNLZRFPHORGQTQIOJQJJZUDEXXSUKDIXLOQEAAXSOJCVPZSHPRMRINOXYLJDQZJIBWJZSPUATHPRYFUNWZDOUQGWDIHDFODSFDWQFSWLPYRVMESBLWCFJINYRUXNMPPKITMRFFDQZVLIIZKWTFYHTYWXTQOUWKVIIIUCRFJILPSZDRXSUJJGIWQHYZNYWKDGRFFDARFGPZCBHTYTGQEVGMSUNMGXZPBVITOTHQRENVJNAVAMNKPMPJFMAUCAXYMYIESSVLXOEVACZHFHZDMOFVMKRJJFJWXSWMMYYZXCKHFFBEPVDZDKRIUFHUYEVMDWCXQVFAQXBABVGHNOTSKNIWCDMWCBRRKGPWKDPLZPQRXWJGWWGTZMZEDGWALHWJVBATCBKDARLWXMMWAXSPEVCGVBOXYZAZBFNSQHUDNAZDXVGFEKRQNWSDDZBNNTOMIM") << std::endl;

    // // Identity plugboard (no swaps)
    // PlugBoard identityPB;
    //
    // // ciphertext and crib (uppercase, no spaces)
    // std::string ciphertext = "PGWDJTWRAQJFJDLTOQ"; // voorbeeld; vervang door je volledige ciphertext
    // std::string crib = "DEOPGAVEVOORENIGMA";
    //
    // if (ciphertext.size() < crib.size()) {
    //     std::cerr << "Ciphertext is korter dan crib. Pas input aan.\n";
    //     return 1;
    // }
    //
    // std::vector<Rotor> rotors = { rotor0, rotor1, rotor2, rotor3, rotor4 };
    //
    // size_t len = crib.size();
    //
    // auto t0 = std::chrono::steady_clock::now();
    //
    // int totalRotorOrders = 0;
    // for (size_t i = 0; i < rotors.size(); ++i) {
    //     for (size_t j = 0; j < rotors.size(); ++j) {
    //         if (j == i) continue;
    //         for (size_t k = 0; k < rotors.size(); ++k) {
    //             if (k == i || k == j) continue;
    //
    //             ++totalRotorOrders;
    //             Enigma prototype(rotors[i], rotors[j], rotors[k], reflector, identityPB);
    //
    //             int counter = 0;
    //             const int totalStarts = 26 * 26 * 26;
    //             for (char L = 'A'; L <= 'Z'; ++L) {
    //                 for (char M = 'A'; M <= 'Z'; ++M) {
    //                     for (char R = 'A'; R <= 'Z'; ++R) {
    //                         ++counter;
    //                         if (counter % 5000 == 0) {
    //                             double pct = 100.0 * counter / totalStarts;
    //                             std::cout << "[Order " << totalRotorOrders << "/60] RotorIdx=("
    //                                       << i << "," << j << "," << k << ")"
    //                                       << " tested " << counter << "/" << totalStarts
    //                                       << " (" << int(pct) << "%)\r" << std::flush;
    //                         }
    //
    //                         Enigma e = prototype; // copy
    //                         e.setPlugBoard(identityPB);
    //                         e.setRotorStartPositions(L, M, R);
    //                         e.resetToStartPositions();
    //
    //                         // decrypt only the first len chars (zonder plugboard)
    //                         std::string prefix = e.decryptString(ciphertext.substr(0, len));
    //
    //                         // score via aantal matches met crib
    //                         int matches = 0;
    //                         for (size_t idx = 0; idx < len; ++idx) {
    //                             if (prefix[idx] == crib[idx]) ++matches;
    //                         }
    //                         double similarity = 100.0 * matches / len;
    //                         const double threshold = 30.0; // percentage
    //
    //                         if (similarity >= threshold) {
    //                             std::cout << "\n[POTENTIAL] Rotor indices = (" << i << "," << j << "," << k << ")"
    //                                       << " start=" << L << M << R
    //                                       << " -> " << matches << "/" << len
    //                                       << " (" << int(similarity) << "% match)\n";
    //                             std::cout << "prefix (no-plug decrypt): " << prefix << "\n";
    //
    //                             // --- Probeer plugboard af te leiden uit crib vs prefix ---
    //                             std::map<char,char> crib_to_y;
    //                             std::map<char,char> y_to_crib;
    //                             bool conflict = false;
    //
    //                             for (size_t p = 0; p < len; ++p) {
    //                                 char plain_char = crib[p];      // wat we verwachten (crib)
    //                                 char y_char = prefix[p];       // wat zonder plug eruit kwam = P(plain)
    //                                 // Als de tekens gelijk zijn, is dat een self-map candidate (P(x)=x)
    //                                 // Stel constraint P(plain_char) = y_char
    //                                 if (crib_to_y.count(plain_char)) {
    //                                     if (crib_to_y[plain_char] != y_char) {
    //                                         conflict = true;
    //                                         break;
    //                                     }
    //                                 } else {
    //                                     crib_to_y[plain_char] = y_char;
    //                                 }
    //                                 // En ook inverse: P(y_char) = plain_char
    //                                 if (y_to_crib.count(y_char)) {
    //                                     if (y_to_crib[y_char] != plain_char) {
    //                                         conflict = true;
    //                                         break;
    //                                     }
    //                                 } else {
    //                                     y_to_crib[y_char] = plain_char;
    //                                 }
    //                             }
    //
    //                             if (conflict) {
    //                                 std::cout << "=> Conflict bij afleiden van plugboard (inconsistente pairs). Sla candidate over.\n";
    //                             } else {
    //                                 // Toon afgeleide paar-mappingen
    //                                 std::cout << "=> Afgeleide plugboard-paren (crib -> y):\n";
    //                                 int pair_count = 0;
    //                                 // We print unieke swaps (a<->b) slechts één keer
    //                                 std::map<char,bool> printed;
    //                                 for (auto &kv : crib_to_y) {
    //                                     char a = kv.first;
    //                                     char b = kv.second;
    //                                     if (a == b) continue; // self-map, geen swap
    //                                     if (printed[a] || printed[b]) continue;
    //                                     printed[a] = printed[b] = true;
    //                                     std::cout << "   " << a << " <-> " << b << "\n";
    //                                     ++pair_count;
    //                                 }
    //                                 std::cout << "   (aantal afgeleide swaps uit crib: " << pair_count << ")\n";
    //
    //                                 // decrypt full message WITHOUT plugboard (y_full), daarna P(y_full) = Plain
    //                                 e.setRotorStartPositions(L, M, R);
    //                                 e.resetToStartPositions();
    //                                 std::string y_full = e.decryptString(ciphertext);
    //
    //                                 // maak final plaintext door y->crib mapping toe te passen waar mogelijk
    //                                 std::string final_plain;
    //                                 final_plain.reserve(y_full.size());
    //                                 for (char ch : y_full) {
    //                                     if (y_to_crib.count(ch)) final_plain.push_back(y_to_crib[ch]);
    //                                     else final_plain.push_back(ch); // ongewijzigd
    //                                 }
    //
    //                                 std::cout << "full (no-plug): " << y_full << "\n";
    //                                 std::cout << "full (met afgeleide plugboard toegepast): " << final_plain << "\n";
    //
    //                                 // aanvullende tip / warning
    //                                 if (pair_count > 10) {
    //                                     std::cout << "WAARSCHUWING: meer dan 10 koppels afgeleid; dit is ongewoon voor echte steckerboards.\n";
    //                                 }
    //                             }
    //                         }
    //                     }
    //                 }
    //             } // end starts
    //
    //             std::cout << "\n";
    //         }
    //     }
    // }
    //
    // auto t1 = std::chrono::steady_clock::now();
    // auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    // std::cout << "Done. Total rotor orders tested: " << totalRotorOrders << ". Time: " << ms << " ms\n";
    //
    // return 0;
}
