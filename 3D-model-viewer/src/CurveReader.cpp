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
            curvePoints.push_back(new vec3(x * scale, y, z * scale));
        }
    }

    archive.close();

    return curvePoints;
}

float CurveReader::calculateAngle(vector<vec3*> curvePoints, int index) {
	vec3* a = curvePoints.at(index);
	vec3* b;

	if (index == curvePoints.size() - 5) b = curvePoints.at(0);
	else b = curvePoints.at(index+5);

    float dx = b->x - a->x;
	float dz = b->z - a->z;

    if (dx == 0 || dz == 0) {
        dx = b->x - curvePoints.at(index - 5)->x;
        dz = b->z - curvePoints.at(index - 5)->z;
    }

	float angle = atan(dz, dx);

    // if (angle > 0) angle += HALF_PI;
	// else angle -= HALF_PI;

    cout << "angle: " << angle << " PI - angle: " << PI - angle << endl;

	return 2*PI - angle;
}