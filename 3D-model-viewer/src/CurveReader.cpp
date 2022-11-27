#include "CurveReader.h"

CurveReader::CurveReader() {}

vector<vec3*> CurveReader::read(string filename, float scale) {
    vector<vec3*> curvePoints;
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
            curvePoints.push_back(new vec3(x * scale, y * scale, z * scale));
        }
    }

    archive.close();

    return curvePoints;
}

float CurveReader::calculateAngle(vector<vec3*> curvePoints, int index, char coordinate) {
	vec3* a = curvePoints.at(index);
	vec3* b;

	if (index == curvePoints.size() - 2) b = curvePoints.at(0);
	else b = curvePoints.at(index + 2);

    float dx, dy, dz, angle;

    switch(coordinate) {
        case 'x':
            dz = b->z - a->z;
            dy = b->y - a->y;

            if (dz == 0 || dy == 0) {
                dz = b->z - curvePoints.at(index - 2)->z;
                dy = b->y - curvePoints.at(index - 2)->y;
            }

            angle = PI - atan(dy, dz);

            break;
        case 'y':
            dx = b->x - a->x;
            dz = b->z - a->z;

            if (dx == 0 || dz == 0) {
                dx = b->x - curvePoints.at(index - 2)->x;
                dz = b->z - curvePoints.at(index - 2)->z;
            }

            angle = 2 * PI - atan(dz, dx);

            break;
        case 'z':
            dx = b->x - a->x;
            dy = b->y - a->y;

            if (dx == 0 || dy == 0) {
                dx = b->x - curvePoints.at(index - 2)->x;
                dy = b->y - curvePoints.at(index - 2)->y;
            }

            cout << "dx = " << dx << " dy = " << dy << endl;

            angle = PI - atan(dy, dx);

            break;
    }

	return angle;
}