#include <iostream>
#include <fstream>
#include <string>

std::string caesar(std::string text, int key);
std::string fix(std::string& str);

int main() {
	bool v;
	std::cout << "from file (0), from console (1): ";
	std::cin >> v;

	if (!v) {
		std::string text;
		std::ifstream file("file.txt");
		std::string line;
		while (std::getline(file,line)) {
			text += line + "\n";
		}
		fix(text);
		bool c;
		std::cout << "encrypt (0), decrypt (1): ";
		std::cin >> c;
		if (!c) {
			int shift;
			std::cout << "shift: ";
			std::cin >> shift;
			std::ofstream encrypted_file("encrypted_file.txt", std::ios::app);
			encrypted_file << caesar(text, shift);
		}
		else if (c) {
			int shift;
			std::cout << "shift: ";
			std::cin >> shift;
			std::ofstream encrypted_file("decrypted_file.txt", std::ios::app);
			encrypted_file << caesar(text, 26 - shift);
		}
	}

	else if (v) {
		std::string text;
		std::cin.ignore();
		std::cout << "\ninput text: ";
		std::getline(std::cin, text);
		fix(text);
		std::cout << "\n";
		for (int key = 0; key < 27; key++) {
			std::cout << "ROT" << key << ":\t";
			std::cout << caesar(fix(text), key) << "\n\n";
		}
	}

	return 0;
}


std::string fix(std::string& text) {
	std::string fixed_text = "";
	bool check = false;
	for (int i = 0; i < text.length(); i++) {
		if (text[i] == ' ') {
			if (check) {
				continue;
			}
			check = true;
		}
		else {
			check = false;
		}
		fixed_text += text[i];
	}
	return fixed_text;
}

std::string caesar(std::string text, int key) {

	for (int i = 0; i < text.length(); i++) {
		if (isupper(text[i])) {
			text[i] = static_cast<char>(static_cast<int>(text[i] + key - 65) % 26 + 65);
		}
		else if (islower(text[i])) {
			text[i] = static_cast<char>(static_cast<int>(text[i] + key - 97) % 26 + 97);
		}
		else if (static_cast<int>(text[i]) > 47 and static_cast<int>(text[i]) < 58) {
			text[i] = static_cast<char>(static_cast<int>(text[i] + key - 48) % 10 + 48);
		}
	}
	return text;
}