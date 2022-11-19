#include "CurveReader.h"

CurveReader::CurveReader() {}

void CurveReader::read(string filename) {
    ifstream archive(filename);

    while (!archive.eof()) {
        string line;
        getline(archive, line);

        stringstream sline(line);

        string identifier;
        sline >> identifier;

        if (identifier.empty()) {
            continue;
        }

        if (identifier == "v") {
            float x, y, z;
            sline >> x >> y >> z;
            curvePoints.push_back(new vec3(x, y, z));
            cout << x << " " << y << " " << z << endl;
        }
    }

    archive.close();
}

