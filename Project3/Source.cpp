/*
 * Project 3
 * Evan Scarborough
 * SNHU CS-210
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

unsigned int OUTPUT_WIDTH = 44;
ifstream inFS;

string nCharStr(char c, unsigned int length) { // return a string of character 'c' with length "length"
	string returnString = "";
	for (unsigned int i = 0; i < length; ++i) {
		returnString.push_back(c);
	}

	return returnString;
}

void displayMenu() { // format and display options for the user
	string menu_header = "[ MAIN MENU ]";
	string opt1 = "Search for an item";
	string opt2 = "View a list of all items";
	string opt3 = "View a histogram of all items";
	string opt4 = "Exit the program";
	int chars_to_print = (OUTPUT_WIDTH - menu_header.length()) / 2;

	cout << nCharStr('=', chars_to_print) << menu_header << nCharStr('=', chars_to_print) << endl;
	cout << endl;
	cout << nCharStr(' ', 2) << "[1] " << opt1 << endl;
	cout << endl;
	cout << nCharStr(' ', 2) << "[2] " << opt2 << endl;
	cout << endl;
	cout << nCharStr(' ', 2) << "[3] " << opt3 << endl;
	cout << endl;
	cout << nCharStr(' ', 2) << "[4] " << opt4 << endl;
	cout << endl;
	cout << nCharStr('-', OUTPUT_WIDTH) << endl;
}

void searchWord() { // find and display frequency of a single word in input file
	string looking_for = "null";
	string curr_item;
	int freq = 0;

	cout << "Enter the item to search for: ";
	cin >> looking_for;

	while (!inFS.eof()) { // increment freq for each occurrence
		inFS >> curr_item;
		if (!inFS.fail() && curr_item == looking_for) {
			++freq;
		}
	}

	inFS.clear(); // clear any errors
	inFS.seekg(0, std::ios::beg); // return to beginning of file

	cout << "Found (" << freq << ") occurrences of \"" << looking_for << "\" in the input file." << endl; // print result
	cout << endl;
}

void listWords() {
	string curr_item;
	map<string, int> freq_map; // create map of strings and ints to track word frequency
	map<string, int>::iterator i;
	string list_header = "[ ITEM LIST ]";

	inFS >> curr_item; // add/increment words in map for each occurrence in input file
	while (!inFS.fail()) {
		++freq_map[curr_item];
		inFS >> curr_item;
	}

	int chars_to_print = (OUTPUT_WIDTH - list_header.length()) / 2; // print list header
	cout << nCharStr('-', chars_to_print) << list_header << nCharStr('-', chars_to_print) << endl;
	cout << endl;

	for (i = freq_map.begin(); i != freq_map.end(); i++) // print each word and its frequency
	{
		chars_to_print = (OUTPUT_WIDTH / 3) - i->first.length();
		cout << nCharStr(' ', 2) << i->first << nCharStr('.', chars_to_print) << i->second << endl;
	}

	inFS.clear(); // clear any errors
	inFS.seekg(0, std::ios::beg); // return to beginning of file

	cout << endl;
	cout << nCharStr('-', OUTPUT_WIDTH) << endl;
	cout << endl;
}

void genBackupFile() {
	string curr_item;
	map<string, int> freq_map; // create map of strings and ints to track word frequency
	map<string, int>::iterator i;
	ofstream outFS;

	outFS.open("frequency.txt");
	if (!outFS.is_open()) {
		cout << "ERROR : Failed to generate backup file" << endl;
	}
	else {
		inFS >> curr_item; // add/increment words in map for each occurrence in input file
		while (!inFS.fail()) {
			++freq_map[curr_item];
			inFS >> curr_item;
		}

		for (i = freq_map.begin(); i != freq_map.end(); i++) // print each word and its frequency
		{
			outFS << i->first << ' ' << i->second << endl;
		}
	}

	inFS.clear(); // clear any errors
	inFS.seekg(0, std::ios::beg); // return to beginning of file
}

void histogram() {
	string curr_item;
	map<string, int> freq_map; // create map of strings and ints to track word frequency
	map<string, int>::iterator i;
	string hist_header = "[ HISTOGRAMS ]";

	inFS >> curr_item; // add/increment words in map for each occurrence in input file
	while (!inFS.fail()) {
		++freq_map[curr_item];
		inFS >> curr_item;
	}

	int chars_to_print = (OUTPUT_WIDTH - hist_header.length()) / 2; // print histogram header
	cout << nCharStr('-', chars_to_print) << hist_header << nCharStr('-', chars_to_print) << endl;
	cout << endl;

	for (i = freq_map.begin(); i != freq_map.end(); i++) // print each word and its frequency
	{
		chars_to_print = (OUTPUT_WIDTH / 3) - i->first.length();
		cout << nCharStr(' ', chars_to_print) << i->first << " ["; // print right-aligned item name

		chars_to_print = 10 - i->second;
		cout << nCharStr('O', i->second) << nCharStr(' ', chars_to_print) << "]" << endl; // print fancy histogram bar
	}

	inFS.clear(); // clear any errors
	inFS.seekg(0, std::ios::beg); // return to beginning of file

	cout << endl;
	cout << nCharStr('-', OUTPUT_WIDTH) << endl;
	cout << endl;
}

bool getUserInput() { // collect and validate user input, return "true" if user wants to exit
	int user_option = 0;
	string user_input = "null";

	while (user_input == "null") {
		cin >> user_input;

		if (user_input.length() > 1 || isdigit(user_input[0]) == false) { // ensure that input is a single integer
			user_input = "null";
			cout << "Please select a valid option." << endl;
			continue;
		}

		user_option = stoi(user_input);

		if (!(user_option <= 4 && user_option >= 1)) { // ensure that input is between 1 and 4 inclusive
			user_input = "null";
			user_option = 0;
			cout << "Please select a valid option." << endl;
			continue;
		}

		switch (user_option) {
			case 1:
				searchWord();
				return false;
			case 2:
				listWords();
				return false;
			case 3:
				histogram();
				return false;
			case 4:
				return true;
		}
	}
}

int main() {
	bool exit_request = false;

	inFS.open("input.txt"); // attempt to open input file, return an error if unsuccessful
	if (!inFS.is_open()) {
		cout << "ERROR : Failed to open input file." << endl;
		return 1;
	}

	genBackupFile();

	while (exit_request == false) {
		displayMenu();
		exit_request = getUserInput();
	}

	inFS.close();

	return 0;
}