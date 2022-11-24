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

// float CurveReader::calculateAngle(vector<vec3*> curvePoints, int index) {
// 	vec3* a = curvePoints.at(index);
// 	vec3* b;
// 	vec3* c;

// 	if (index == curvePoints.size() - 2) {
// 		b = curvePoints.at(index+1);
// 		c = curvePoints.at(0);
// 	}
//     else if (index == curvePoints.size() - 1) {
// 		b = curvePoints.at(0);
// 		c = curvePoints.at(1);
// 	}
// 	else {
// 		b = curvePoints.at(index+1);
// 		c = curvePoints.at(index+2);
// 	}

// 	float angle = atan(b->x - a->x, b->z - a->z) - atan(c->x - b->x, c->z - b->z);

// 	return angle;
// }

float CurveReader::calculateAngle(vector<vec3*> curvePoints, int index) {
	vec3* a = curvePoints.at(index);
	vec3* b;

	if (index == curvePoints.size() - 1) b = curvePoints.at(0);
	else b = curvePoints.at(index+1);

    float dx = b->x - a->x;
	float dy = b->y - a->y;

    if (dx == 0 || dy == 0) {
        dx = b->x - curvePoints.at(index - 1)->x;
        dy = b->y - curvePoints.at(index - 1)->y;
    }

	float angle = atan(dy, dx);

	return angle;
}