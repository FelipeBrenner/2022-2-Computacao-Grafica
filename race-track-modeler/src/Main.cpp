#include "Main.h"

int main() {
	if (setup() != 0){
		return EXIT_FAILURE;
	}

	glGenVertexArrays(1, &vaoCurve);
	glGenBuffers(1, &vboCurve);

	glGenVertexArrays(1, &vaoPoints);
	glGenBuffers(1, &vboPoints);

	glfwMakeContextCurrent(window);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		// renderiza os pontos
		if (controlPointsFloat->size() > 0) {
			glPointSize(10);
			runBinds(vaoPoints, vboPoints, controlPointsFloat, 0);
			glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
			glDrawArrays(GL_POINTS, 0, controlPointsFloat->size() / 3);
		}

		// renderiza a curva
		if (controlPointsFloat->size() > 6) {
			runBinds(vaoCurve, vboCurve, finalCurveFloat, 6 * sizeof(GLfloat));
			glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);
			glDrawArrays(GL_TRIANGLES, 0, finalCurveFloat->size() / 3);
		}

		// gera o desenho na tela
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}

int setup() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Curva", nullptr, nullptr);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (nullptr == window) {
		cout << "Falha ao criar janela GLFW" << endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		cout << "Falha ao criar janela GLEW" << endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	Shader coreShader("shaders/core.vert", "shaders/core.frag");
	coreShader.Use();

	colorLoc = glGetUniformLocation(coreShader.program, "inputColor");

	return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		faces = 0;
		writeObjMtl();

		double xpos, ypos;
		
		// pega posicao
		glfwGetCursorPos(window, &xpos, &ypos);

		convertCoordinates(xpos, ypos);

		// gera um novo vec3 com o ponto para a curva
		vec3* point = new vec3(xpos, ypos, 0.0);
		
		// adiciona ao vetor de pontos selecionados
		controlPoints->push_back(point);

		cout << "- Ponto de Controle Computado:" << endl;
		cout << "x = " << xpos << endl;
		cout << "y = " << ypos << endl;

		setCoordinatesByZone(xpos, ypos);

		controlPointsFloat = convertVectorToFloat(controlPoints);

		runBinds(vaoPoints, vboPoints, controlPointsFloat, 0);

		if(controlPointsFloat->size() > 6) {
			originalCurve = generateOriginalCurve(controlPoints);
			externalCurve = generateSideCurve(originalCurve, true);
			internalCurve = generateSideCurve(originalCurve, false);

			// tamanho do array dividido por 2 - porque a metade desses valores e cor branca
			externalCurveSize = externalCurve->size() / 2.0;
			internalCurveSize = internalCurve->size() / 2.0;

			OBJWriter OBJWriter;
			OBJWriter.saveTextureValuesToOBJ();

			finalCurve->clear();
			finalCurve = generateFinalCurve(internalCurve, externalCurve);
			finalCurveFloat = convertVectorToFloat(finalCurve);

			runBinds(vaoCurve, vboCurve, finalCurveFloat, 6 * sizeof(GLfloat));
		}
	}
}

void runBinds(GLuint vao, GLuint vbo, vector<GLfloat>* vector, float size) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vector->size(), vector->data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size, NULL);
}

void writeObjMtl() {
	MTLWriter MTLWriter;
	MTLWriter.createMTLFile();

	OBJWriter OBJWriter;
	OBJWriter.createOBJFile();
}

vector<GLfloat>* convertVectorToFloat(vector<vec3*>* points) {
	std:vector<GLfloat>* temp = new vector<GLfloat>();

	for (int i = 0; i < points->size(); i++) {
		temp->push_back(points->at(i)->x);
		temp->push_back(points->at(i)->y);
		temp->push_back(points->at(i)->z);
	}

	return temp;
}

void convertCoordinates(double& x, double& y) {
	// se x for maior que a metade da tela da esquerda, ou seja clique na direita, resulta em valores entre 0 e 1
	if (x > (WIDTH / 2)) {
		x = x - (WIDTH / 2);
		x = x / (WIDTH / 2);
	}
	// se estiver no meio
	else if (x == (WIDTH / 2)) {
		x = 0;
	}
	// se o clique for na parte esquerda da tela, entao converte para valores entre -1 e 0
	else {
		x = -(((WIDTH / 2) - x) / (WIDTH / 2));
	}

	// se y for maior que a metade de baixo da tela, ou seja clique na parte de baixo, resulta em valores entre 0 e -1
	if (y > (HEIGHT / 2)) {
		y = y - (HEIGHT / 2);
		y = y / (HEIGHT / 2);
		y = y * (-1);
	}
	// se estiver no meio
	else if (y == (HEIGHT / 2)) {
		y = 0;
	}
	// se o clique for na parte de cima da tela, entao converte para valores entre 0 e 1
	else {
		y = -(((HEIGHT / 2) - y) / (HEIGHT / 2));
		y = y * (-1);
	}
}

int getZone(float x, float y) {

// pega o quadrante que esta
	if (x > 0.0 && y > 0.0) {
		return 1;
	}
	else if (x > 0.0 && y < 0.0) {
		return 4;
	}
	else if (x < 0.0 && y < 0.0) {
		return 3;
	}
	else {
		return 2;
	}
}

void setCoordinatesByZone(double& xpos, double& ypos)
{
	// arrendodamento de curva, aumentando um pouco a curva
	int zone = getZone(xpos, ypos);
	if (zone == 1) {
		xpos += 0.5;
		ypos += 0.5;
	}
	else if (zone == 2) {
		xpos -= 0.5;
		ypos += 0.5;
	}
	else if (zone == 3) {
		xpos -= 0.5;
		ypos -= 0.5;
	}
	else if (zone == 4) {
		xpos += 0.5;
		ypos -= 0.5;
	}
}

vector<vec3*>* generateOriginalCurve(vector<vec3*>* points) {
	TXTWriter TXTWriter;
	TXTWriter.createTXTFile();

	vector<vec3*>* curvaCalculada = new vector<vec3*>();
	vector<vec3*>* temp = new vector<vec3*>();
	vector<vec3*>* temp2 = new vector<vec3*>();

	for (int i = 0; i < points->size(); i++) {
		temp->push_back(new vec3(points->at(i)->x, points->at(i)->y, 0));
	}

	//cria mais um ponto para terminar a curva, com o ponto inicial
	temp->push_back(points->at(0));
	temp->push_back(points->at(1));
	temp->push_back(points->at(2));

	calculateBSpline(temp, curvaCalculada, TXTWriter);

	TXTWriter.closeTXTFile();
	cout << "Curva gerada com sucesso!" << endl;

	return curvaCalculada;
}

void calculateBSpline(vector<vec3*>* temp, vector<vec3*>* curvaCalculada, TXTWriter& TXTWriter) {
	for (int i = 0; i < (temp->size() - 3); i++) {
		// itera entre 99 variacoes para a distancia entre cada ponto
		for (int j = 0; j < 100; ++j) {

			float t = static_cast<float>(j) / 99.0;

			GLfloat x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * temp->at(i)->x +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 4) * temp->at(i + 1)->x +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * temp->at(i + 2)->x +
				pow(t, 3) * temp->at(i + 3)->x) / 6);

			GLfloat y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * temp->at(i)->y +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 4) * temp->at(i + 1)->y +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * temp->at(i + 2)->y +
				pow(t, 3) * temp->at(i + 3)->y) / 6);

			vec3* point = new vec3(x, y, 0.0);

			curvaCalculada->push_back(point);

			TXTWriter.addPoint(point->x, point->y, point->z);

			curvaCalculada->push_back(new vec3(0.0, 0.1, 1.0));
		}
	}
}

vector<vec3*>* generateSideCurve(vector<vec3*>* points, bool external) {

	// recebe os pontos da curva original do meio

	OBJWriter OBJWriter;
	vector<vec3*>* calculatedCurve = new vector<vec3*>();

	for (int j = 0; j < points->size() - 1; j += 2) {
		vec3* a = points->at(j);
		vec3* b;

		if (j == points->size() - 2) b = points->at(0);
		else b = points->at(j + 2);

		GLfloat dx = b->x - a->x;
		GLfloat dy = b->y - a->y;

		if (dx == 0 || dy == 0) {
			dx = b->x - points->at(j - 2)->x;
			dy = b->y - points->at(j - 2)->y;
		}

		// arco tangente
		GLfloat angle = atan(dy, dx);

		if (external) angle += HALF_PI;
		else angle -= HALF_PI;

		// 0.09 -> tamanho da curva, fator de escala
		GLfloat offsetX = cos(angle) * 0.05;
		GLfloat offsetY = sin(angle) * 0.05;

		vec3* pontosGerados = new vec3(a->x + offsetX, a->y + offsetY, 0.0);

		calculatedCurve->push_back(pontosGerados);

		// adiciona pro obj
		OBJWriter.addPointsFinalCurve(pontosGerados->x, pontosGerados->y, pontosGerados->z);

		// adiciona cor branca para curva
		calculatedCurve->push_back(new vec3(0.0, 0.1, 1.0));
	}

	return calculatedCurve;
}

vector<vec3*>* generateFinalCurve(vector<vec3*>* internalCurve, vector<vec3*>* externalCurve) {
	OBJWriter OBJWriter;

	int i = 0;
	int index = 1;

	for (; i < internalCurve->size() - 2; i += 2) {
		// Ponto Interno 1
		finalCurve->push_back(internalCurve->at(i));
		finalCurve->push_back(internalCurve->at(i + 1));

		vec3* a_int = internalCurve->at(i);

		// Ponto Interno 2
		finalCurve->push_back(internalCurve->at(i + 2));
		finalCurve->push_back(internalCurve->at(i + 3));

		vec3* b_int = internalCurve->at(i + 2);

		// Ponto Externo 1
		finalCurve->push_back(externalCurve->at(i));
		finalCurve->push_back(externalCurve->at(i + 1));

		vec3* c_ext = externalCurve->at(i);

		OBJWriter.addFaces(index, externalCurveSize, ++faces, 1);

		// Ponto Interno 2
		finalCurve->push_back(internalCurve->at(i + 2));
		finalCurve->push_back(internalCurve->at(i + 3));

		// Ponto Externo 2
		finalCurve->push_back(externalCurve->at(i + 2));
		finalCurve->push_back(externalCurve->at(i + 3));

		vec3* d_ext = externalCurve->at(i + 2);

		// Ponto Externo 1
		finalCurve->push_back(externalCurve->at(i));
		finalCurve->push_back(externalCurve->at(i + 1));

		OBJWriter.addFaces(index, externalCurveSize, ++faces, 2);

		// pega os vetores das normais
		// y e z sao invertidos para modificar os eixos
		// produto escalar
		vec3 ab = vec3(b_int->x - a_int->x, b_int->z - a_int->z, b_int->y - a_int->y);
		vec3 ac = vec3(c_ext->x - a_int->x, c_ext->z - a_int->z, c_ext->y - a_int->y);
		vec3 dc = vec3(c_ext->x - d_ext->x, c_ext->z - d_ext->z, c_ext->y - d_ext->y);
		vec3 db = vec3(b_int->x - d_ext->x, b_int->z - d_ext->z, b_int->y - d_ext->y);

		// produto vetorial
		vec3 normal_vec_abac = cross(ac, ab);
		vec3 normal_vec_dbdc = cross(db, dc);

		OBJWriter.addNormalExternalCurve(normal_vec_abac, normal_vec_dbdc);

		index++;
	}
	cout << i << " , " << index << endl;
	// O trecho abaixo liga os �ltimos pontos com primeiro os primeiros
	// Ponto Interno 1
	finalCurve->push_back(internalCurve->at(i));
	finalCurve->push_back(internalCurve->at(i + 1));

	vec3* a_int = internalCurve->at(i);

	// Ponto Interno 2
	finalCurve->push_back(internalCurve->at(0));
	finalCurve->push_back(internalCurve->at(1));

	vec3* b_int = internalCurve->at(0);

	// Ponto Externo 1
	finalCurve->push_back(externalCurve->at(i));
	finalCurve->push_back(externalCurve->at(i + 1));

	vec3* c_ext = externalCurve->at(i);

	OBJWriter.addFaces(index, externalCurveSize, ++faces, 3);

	// Ponto Interno 2
	finalCurve->push_back(internalCurve->at(0));
	finalCurve->push_back(internalCurve->at(1));

	// Ponto Externo 2
	finalCurve->push_back(externalCurve->at(0));
	finalCurve->push_back(externalCurve->at(1));

	vec3* d_ext = externalCurve->at(0);

	// Ponto Externo 1
	finalCurve->push_back(externalCurve->at(i));
	finalCurve->push_back(externalCurve->at(i + 1));

	OBJWriter.addFaces(index, externalCurveSize, ++faces, 4);

	// pega os vetores das normais
	// y e z sao invertidos para modificar os eixos
	// produto escalar
	vec3 ab = vec3(a_int->x - b_int->x, a_int->z - b_int->z, a_int->y - b_int->y);
	vec3 ac = vec3(a_int->x - c_ext->x, a_int->z - c_ext->z, a_int->y - c_ext->y);
	vec3 dc = vec3(d_ext->x - c_ext->x, d_ext->z - c_ext->z, d_ext->y - c_ext->y);
	vec3 db = vec3(d_ext->x - b_int->x, d_ext->z - b_int->z, d_ext->y - b_int->y);

	// prooduto vetorial
	vec3 normal_vec_abac = cross(ab, ac);
	vec3 normal_vec_dbdc = cross(db, dc);

	OBJWriter.addNormalExternalCurve(normal_vec_abac, normal_vec_dbdc);

	return finalCurve;
}