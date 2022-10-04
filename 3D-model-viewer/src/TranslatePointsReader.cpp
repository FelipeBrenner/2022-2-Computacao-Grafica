#include "TranslatePointsReader.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

vector<vec3*> TranslatePointsReader::read(string filename)
{
    vector<vec3*> points;

    ifstream arq(filename);

    // cout << "Lendo arquivo: " << filename << endl;

    if (!arq) {
        // cout << "- Arquivo de objeto nao encontrado" << endl;
        exit(EXIT_FAILURE);
    }

    // cout << endl;

    while (!arq.eof()) {
        string line;
        getline(arq, line);

        stringstream sline(line);

        // l� tipo de elemento

        // cout << "Linha lida: " << line << endl;
        // cout << "- Tipo: " << temp << endl;

        float x, y, z;
        sline >> x >> y >> z;
        //cout << "  Resultado: vec3(" << x << ", " << y << ", " << z << ")" << endl;
        points.push_back(new glm::vec3(x, y, z));

        // cout << endl;
    }

    arq.close();

    return points;
}
