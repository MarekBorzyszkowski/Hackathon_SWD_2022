// MiI_Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <chrono>
#include <locale.h>
#include <algorithm>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


using namespace cv;
using namespace std;

const string Alphabet = "aπbcÊdeÍfghijkl≥mnÒoÛpqrsútuvwxyzüø";
const string Alphabet_Large = "A•BC∆DE FGHIJKL£MN—O”PQRSåTUVWXYZèØ";
const int whichImage = 1;

void separate_words(string textFromImage[], string textFromImage_to_tab) {
	int j = 0;
	for (int i = 0; i < textFromImage_to_tab.length(); i++) {
		if (textFromImage_to_tab[i] != ' ')
			textFromImage[j] += textFromImage_to_tab[i];
		else
			j++;
	}
}

void separate_words_textFromImage(string textFromImage[], string textFromImage_to_tab, string text_to_tab) {
	int j = 0;
	bool changed = false;
		
	for (int i = 0; i < textFromImage_to_tab.length(); i++) {
		if (whichImage == 1 && textFromImage_to_tab[i] == '\n' && changed == false) {
			textFromImage_to_tab.erase(textFromImage_to_tab.begin() + i);
			changed = true;
		}
		else if (textFromImage_to_tab[i] == '\n')
			textFromImage_to_tab[i] = ' ';
			
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
		if (textFromImage[i] == 'π')
			textFromImage.replace(i, 1, "ƒÖ");
		if (textFromImage[i] == 'Í')
			textFromImage.replace(i, 1, "ƒô");
		if (textFromImage[i] == 'Ê')
			textFromImage.replace(i, 1, "ƒá");
		if (textFromImage[i] == '≥')
			textFromImage.replace(i, 1, "≈Ç");
		if (textFromImage[i] == 'Ò')
			textFromImage.replace(i, 1, "≈Ñ");
		if (textFromImage[i] == 'Û') {
			textFromImage.replace(i, 1, "√≥");
			i++;
		}
		if (textFromImage[i] == 'ú')
			textFromImage.replace(i, 1, "≈õ");
		if (textFromImage[i] == 'ü')
			textFromImage.replace(i, 1, "≈∫");
		if (textFromImage[i] == 'ø')
			textFromImage.replace(i, 1, "≈º");
		if (textFromImage[i] == '•')
			textFromImage.replace(i, 1, "ƒÑ");
		if (textFromImage[i] == ' ')
			textFromImage.replace(i, 1, "ƒòòò ò");
		if (textFromImage[i] == '∆')
			textFromImage.replace(i, 1, "ƒÜ");
		if (textFromImage[i] == '£')
			textFromImage.replace(i, 1, "≈Å");
		if (textFromImage[i] == '—')
			textFromImage.replace(i, 1, "≈É ");
		if (textFromImage[i] == '”')
			textFromImage.replace(i, 1, "√ì");
		if (textFromImage[i] == 'å')
			textFromImage.replace(i, 1, "≈ö");
		if (textFromImage[i] == 'è') {
			textFromImage.replace(i, 1, "≈π");
			i++;
		}
		if (textFromImage[i] == 'Ø')
			textFromImage.replace(i, 1, "≈ª");
	}
}

bool search_in_file(string textFromImage[], int size_of_textFromImage, string text[], int size_of_text, int& words_amount) {
	int i = 0, j = 0;
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



int main()
{
	auto start = chrono::system_clock::now();
	
	Mat srcImage = imread("szyfr_1.png");
	Mat secondImage = imread("szyfr_1.png");
	int indexOfColorChange = 0;
	namedWindow("Display window", cv::WINDOW_AUTOSIZE);


	for (int y = 0; y < srcImage.rows; y++)
	{
		Vec3b& colorBefore = srcImage.at<Vec3b>(y, 0);
		indexOfColorChange = 1;

		for (int x = 1; x < srcImage.cols; x++)
		{
			// get pixel
			Vec3b& color = srcImage.at<Vec3b>(y, x);

			// ... do something to the color ....
			if (color[0] - colorBefore[0] == 1 &&
				color[1] - colorBefore[1] == 1 &&
				color[2] - colorBefore[2] == 1) {


				secondImage.at<Vec3b>(y, x) = Vec3b(255, 255, 255);

			}
			else if (color[0] - colorBefore[0] == -1 &&
				color[1] - colorBefore[1] == -1 &&
				color[2] - colorBefore[2] == -1) {

				int tmp = x;

				while (x != indexOfColorChange) {
					x--;
					secondImage.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
				}

				x = tmp;
				colorBefore = color;
			}
			else {
				colorBefore = color;
				indexOfColorChange = x;
				secondImage.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
			}

		}
	}
	namedWindow("Aleksandra Borsuk");
	moveWindow("Aleksandra Borsuk", 0, 0);
	imshow("Aleksandra Borsuk", secondImage);
	imwrite("output.png", secondImage);

	waitKey(0);

	string outText;

	tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (api->Init("C:/Users/music/Desktop/ImageSteganography-master/tessdata", "pol")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
	}

	// Open input image with leptonica library
	Pix* image = pixRead("output.png");
	api->SetImage(image);
	// Get OCR result
	outText = api->GetUTF8Text();
	cout << outText;

	// Destroy used object and release memory
	api->End();
	delete api;
	pixDestroy(&image);

	// detecting endlines

	ifstream searched("w_pustyni_i_w_puszczy.txt");
	string text_to_tab;
	getline(searched, text_to_tab);

	string textFromImage_to_tab = outText;
	int size_of_textFromImage = count(textFromImage_to_tab.begin(), textFromImage_to_tab.end(), ' ') + 1;
	string* textFromImage = new string[size_of_textFromImage];
	separate_words_textFromImage(textFromImage, textFromImage_to_tab, text_to_tab);

	
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

	ofstream output("szyfr_" + to_string(1) + ".txt");
	output << words_amount - size_of_textFromImage + 1 << " " << words_amount;

	auto end = chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds = end - start;

	cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";


	return 0;
}
