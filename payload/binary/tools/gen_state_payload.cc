#include "common/common.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    ifstream fin(argv[1], std::ios::binary);
    if (!fin.good()) {
        throw ruby_typer::FileNotFoundException();
    }
    std::vector<ruby_typer::u1> data;

    fin.seekg(0, std::ios::end);
    size_t filesize = fin.tellg();
    fin.seekg(0, std::ios::beg);

    data.resize(filesize);

    fin.read((char *)data.data(), filesize);

    ofstream classfile(argv[2], ios::trunc);

    classfile << "#include \"common/common.h\"\n"
              << "\n"
              << "const ruby_typer::u1 nameTablePayload[] = {\n";
    int i = -1;
    bool first = true;
    for (auto c : data) {
        ++i;
        if (!first) {
            classfile << ", ";
        }
        first = false;
        if (i % 10 == 0) {
            classfile << "\n    ";
        }
        classfile << (int)c;
    }
    classfile << "};\n";
    classfile
        << "extern const ruby_typer::u1 * const getNameTablePayload = (const ruby_typer::u1 * const)&nameTablePayload;"
        << endl;

    classfile.close();

    return 0;
}
