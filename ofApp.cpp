#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	for (int x = -650; x <= 650; x += 650) {

		for (int y = -650; y <= 650; y += 650) {

			int start_index = this->mesh.getNumVertices();
			for (int i = 0; i < 3; i++) {

				auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
				for (int deg = 0; deg < 360; deg += 2) {

					auto angle_x = ofMap(ofNoise(noise_seed.x, cos(deg * DEG_TO_RAD), ofGetFrameNum() * 0.006), 0, 1, 0, PI);
					auto angle_y = ofMap(ofNoise(noise_seed.y, sin(deg * DEG_TO_RAD), ofGetFrameNum() * 0.006), 0, 1, 0, PI);
					auto angle_z = ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * 0.006), 0, 1, 0, PI);

					auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
					auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
					auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

					auto location = glm::vec3(300 * cos(deg * DEG_TO_RAD), 300 * sin(deg * DEG_TO_RAD), 0);
					location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;

					this->mesh.addVertex(location + glm::vec3(x, y, 0));
				}
			}

			int end_index = this->mesh.getNumVertices();
			for (int i = start_index; i < end_index; i++) {

				for (int k = i + 1; k < end_index; k++) {

					if (glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k)) < 50) {

						this->mesh.addIndex(i); this->mesh.addIndex(k);
					}
				}
			}
		}
	}	
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(39, 64);
	this->mesh.drawWireframe();

	ofSetColor(39);
	for (auto& vertex : this->mesh.getVertices()) {

		ofDrawSphere(vertex, 3);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}