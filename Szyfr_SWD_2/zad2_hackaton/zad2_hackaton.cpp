#include <iostream>
#include <chrono>
#include <fstream>
#include <locale.h>
#include <algorithm>
#include <string>

using namespace std;
const string Alphabet = "aąbcćdeęfghijklłmnńoópqrsśtuvwxyzźż";
const string Alphabet_Large = "AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŹŻ";

void separate_words(string textFromImage[], string textFromImage_to_tab) {
    int j = 0;
    for (int i = 0; i < textFromImage_to_tab.length(); i++) {
        if (textFromImage_to_tab[i] != ' ')
            textFromImage[j] += textFromImage_to_tab[i];
        else
            j++;
    }
}

void encode_cesar(string& textFromImage, int shift) {
    for (int i = 0; i < textFromImage.length(); i++) {
        if (textFromImage[i] != ' ') {
            int index = Alphabet.find(textFromImage[i]);
            if (index != string::npos) {
                if (index - shift < 0)
                    index += Alphabet.length();
                textFromImage[i] = Alphabet[index - shift];
            }
            else {
                index = Alphabet_Large.find(textFromImage[i]);
                if (index - shift < 0)
                    index += Alphabet_Large.length();
                textFromImage[i] = Alphabet_Large[index - shift];
            }
        }
    }
}


void changing_polish_symbols(string& textFromImage) {
    for (int i = 0; i < textFromImage.length(); i++) {
        if (textFromImage[i] == 'ą') 
            textFromImage.replace(i, 1, "Ä…");
        if (textFromImage[i] == 'ę')
            textFromImage.replace(i, 1, "Ä™");
        if (textFromImage[i] == 'ć')
            textFromImage.replace(i, 1, "Ä‡");
        if (textFromImage[i] == 'ł')
            textFromImage.replace(i, 1, "Ĺ‚");
        if (textFromImage[i] == 'ń')
            textFromImage.replace(i, 1, "Ĺ„");
        if (textFromImage[i] == 'ó') {
            textFromImage.replace(i, 1, "Ăł");
            i++;
        }
        if (textFromImage[i] == 'ś')
            textFromImage.replace(i, 1, "Ĺ›");
        if (textFromImage[i] == 'ź')
            textFromImage.replace(i, 1, "Ĺş");
        if (textFromImage[i] == 'ż')
            textFromImage.replace(i, 1, "ĹĽ");
        if (textFromImage[i] == 'Ą')
            textFromImage.replace(i, 1, "Ä„");
        if (textFromImage[i] == 'Ę')
            textFromImage.replace(i, 1, "Ä ");
        if (textFromImage[i] == 'Ć')
            textFromImage.replace(i, 1, "Ä†");
        if (textFromImage[i] == 'Ł')
            textFromImage.replace(i, 1, "Ĺ");
        if (textFromImage[i] == 'Ń')
            textFromImage.replace(i, 1, "Ĺ ");
        if (textFromImage[i] == 'Ó')
            textFromImage.replace(i, 1, "Ă“");
        if (textFromImage[i] == 'Ś')
            textFromImage.replace(i, 1, "Ĺš");
        if (textFromImage[i] == 'Ź') {
            textFromImage.replace(i, 1, "Ĺą");
            i++;
        }
        if (textFromImage[i] == 'Ż')
            textFromImage.replace(i, 1, "Ĺ»");
    }
}

bool search_in_file(string textFromImage[], int size_of_textFromImage, string text[], int size_of_text, int& words_amount) {
    int i = 0, j=0;
    while (true) {
        if (j == size_of_text)
            return false;

        words_amount++;
        string textFromImage_word = textFromImage[i];

        if (textFromImage_word == text[j]) {
            i++;
        }
        else
            i = 0;
        if (i == size_of_textFromImage) {

            return true;
        }
        j++;
    }
}


int main(int argc, const char* argv[]) {

    auto start = chrono::system_clock::now();

    int which_image = 2;
    string textFromImages[] = { "ęuhśe tphżąh smgikm ćęłśbg rhuhśb h tphuwćpkpm","zqdge fqmqócógjq falgńc l xngsuaqóżek óqzżek ocuażó sqwtagdc lek aóceaólg oólgł" };
    string textFromImage_to_tab = textFromImages[which_image - 1] ;
    int size_of_textFromImage = count(textFromImage_to_tab.begin(), textFromImage_to_tab.end(), ' ') + 1;
    string* textFromImage = new string[size_of_textFromImage];
    separate_words(textFromImage, textFromImage_to_tab);

    ifstream searched("w_pustyni_i_w_puszczy.txt");
    string text_to_tab;
    getline(searched, text_to_tab);
    int size_of_text = count(text_to_tab.begin(), text_to_tab.end(), ' ') + 1;
    string* text = new string[size_of_text];
    separate_words(text, text_to_tab);

    int shift = 2;
    bool found = false;
    int words_amount = 0;
    while (found == false) {
        string* copy_of_textFromImage = new string[size_of_textFromImage];
        
        for (int i = 0; i < size_of_textFromImage; i++) {
            copy_of_textFromImage[i] = textFromImage[i];
            encode_cesar(copy_of_textFromImage[i], shift);
            changing_polish_symbols(copy_of_textFromImage[i]);
        }

        shift++;
        words_amount = 0;
        found = search_in_file(copy_of_textFromImage, size_of_textFromImage, text, size_of_text, words_amount);
    }

    ofstream output("szyfr_" + to_string(which_image)+".txt");
    output << words_amount - size_of_textFromImage + 1 << " " << words_amount;

    auto end = chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end - start;

    cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}