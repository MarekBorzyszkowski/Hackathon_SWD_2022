/*#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Polish");
    string Alphabet = "aąbcćdeęfghijklłmnńoópqrsśtuvwxyzźż";
    string toDecrypt = "ęuhśe tphżąh smgikm ćęłśbg rhuhśb h tphuwćpkpm";
    //cin >> toDecrypt;
    int add = 10;
    //while (add<27) {
        for (int i = 0; i < toDecrypt.length(); i++) {
            if (toDecrypt[i] != ' ') {
                int index = Alphabet.find(toDecrypt[i]);
                if (index - add < 0)
                    index += Alphabet.length();
                toDecrypt[i] = Alphabet[index - add];
            }
        }
        cout << toDecrypt << endl << endl;
        //add++;
    //}



}*/

#include <iostream>
#include <chrono>
#include <fstream>
#include <locale.h>

using namespace std;
const string Alphabet = "aąbcćdeęfghijklłmnńoópqrsśtuvwxyzźż";

void encode_cesar(string& textFromImage, int shift) {
    for (int i = 0; i < textFromImage.length(); i++) {
        if (textFromImage[i] != ' ') {
            int index = Alphabet.find(textFromImage[i]);
            if (index - shift < 0)
                index += Alphabet.length();
            textFromImage[i] = Alphabet[index - shift];
        }
    }
}


void search_in_file(string textFromImage[], int size_of_textFromImage) {
    ifstream searched("asdc.txt");
    bool found = false;
    int i = 0;

    while (!searched.eof() && found == false) {
        string searched_text;
        searched >> searched_text;
        if (searched_text == "mówił") {
            cout << "123";
            break;
        }

        //while(textFromImage[i]!=)
        string textFromImage_word = textFromImage[i];

        if (textFromImage_word == searched_text) {
            cout << textFromImage_word << endl;
            i++;
        }
        else
            i = 0;
        if (i == size_of_textFromImage) {
            string searched_text;
            searched >> searched_text;
            cout << searched_text << endl;
            found = true;
        }
    }
}


int main(int argc, const char* argv[]) {
    // Saving the time of prpgram start
    cout << Alphabet;
    auto start = chrono::system_clock::now();

    // first picture - shift 10
    // sescond picture - shift 3

    int shift = 10;
    string textFromImage[] = { "ęuhśe", "tphżąh", "smgikm", "ćęłśbg", "rhuhśb", "h", "tphuwćpkpm" };

    //Decode cesar enoding (for first picture shift 10)


    ofstream result;

    int size_of_textFromImage = sizeof(textFromImage) / sizeof(textFromImage[0]);

    for (int i = 0; i < size_of_textFromImage; i++)
        encode_cesar(textFromImage[i], shift);

    search_in_file(textFromImage, size_of_textFromImage);

    for (int i = 0; i < size_of_textFromImage; i++)
        cout << textFromImage[i] << " ";
    cout << endl;

    // Computing the duration of program

    auto end = chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end - start;

    cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}