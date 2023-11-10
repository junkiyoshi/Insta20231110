#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(0.5);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(90);

	int v_span = 1;
	int u_span = 30;
	int R = 330;
	int r = 60;	
	ofColor color;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	float noise_seed = ofRandom(1000);
	for (int v = 0; v <= 360 * 6; v += v_span) {

		bool flag = true;
		auto z = glm::vec3(0, 0, ofMap(v, 0, 360 * 6, -360 * 3, 360 * 3));
		auto next_z = glm::vec3(0, 0, ofMap(v + v_span, 0, 360 * 6, -360 * 3, 360 * 3));
		int u_start = ofMap(ofNoise(noise_seed, z.z * 0.003, ofGetFrameNum() * 0.0035), 0, 1, -360 * 3, 360 * 3);
		int next_u = ofMap(ofNoise(noise_seed, next_z.z * 0.003, ofGetFrameNum() * 0.0035), 0, 1, -360 * 3, 360 * 3);

		int count = 0;
		for (int u = u_start; u < u_start + 360; u += u_span) {

			color.setHsb(ofMap(count, 0, 12, 0, 255), 120, 255);
			count++;

			if (true) {

				face.addVertex(this->make_point(R, r, u, v) + z);
				face.addVertex(this->make_point(R, r, u + u_span, v) + z);
				face.addVertex(this->make_point(R, r, next_u + u_span, v + v_span) + next_z);
				face.addVertex(this->make_point(R, r, next_u, v + v_span) + next_z);

				line.addVertex(this->make_point(R, r, u, v) + z);
				line.addVertex(this->make_point(R, r, u + u_span, v) + z);
				line.addVertex(this->make_point(R, r, next_u + u_span, v + v_span) + next_z);
				line.addVertex(this->make_point(R, r, next_u, v + v_span) + next_z);

				ofColor face_color = ofColor(color);
				ofColor line_color = ofColor(239);

				face.addColor(face_color);
				face.addColor(face_color);
				face.addColor(face_color);
				face.addColor(face_color);

				line.addColor(line_color);
				line.addColor(line_color);
				line.addColor(line_color);
				line.addColor(line_color);

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
				line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
			}

			next_u += u_span;
			flag = !flag;
		}
	}

	face.drawFaces();
	line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}