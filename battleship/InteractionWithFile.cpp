#include "InteractionWithFile.h"
#include "GameState.h"

InteractionWithFile::InteractionWithFile(const string& filename) : filename(filename) {}

ofstream InteractionWithFile::open_for_save() {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        throw std::runtime_error("Невозможно открыть файл для чтения\n");
    }
    return outfile;
}

void InteractionWithFile::save(ofstream& outfile, const GameState& game) {
    outfile << game;
}

void InteractionWithFile::close_saving(ofstream& outfile) {
    outfile.close();
}

ifstream InteractionWithFile::open_for_writing() {
    ifstream infile(filename);
    if (!infile.is_open()) {
        //throw FileError("Невозможно открыть файл для записи\n");
    }
    return infile;
}

void InteractionWithFile::write(ifstream& infile, GameState& game) {
    string json_string((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    json j = json::parse(json_string);
    infile >> game;
}

void InteractionWithFile::close_writing(ifstream& infile) {
    infile.close();
}

InteractionWithFile::~InteractionWithFile(){
    outfile.close();
    infile.close();
}

