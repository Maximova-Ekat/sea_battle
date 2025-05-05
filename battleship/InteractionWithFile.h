#ifndef INTERACTION_WITH_FILE_HPP
#define INTERACTION_WITH_FILE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include "GameState.h"

using json = nlohmann::json;
using namespace std;

class InteractionWithFile{
private:
    string filename;
    ifstream infile;
    ofstream outfile;
public:
    InteractionWithFile(const string& filename);
    ofstream open_for_save();
    void save(ofstream& outfile, const GameState& game);
    void close_saving(ofstream& outfile);
    ifstream open_for_writing();
    void write(ifstream& infile, GameState& game);
    void close_writing(ifstream& infile);
    ~InteractionWithFile();
};



#endif