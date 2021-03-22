#include "../include/View.hpp"

View::View(const FilePath& applicationPath) : m_program(loadProgram(applicationPath.dirPath() + "../shaders/forward.vs.glsl",
                              										applicationPath.dirPath() + "../shaders/normals.fs.glsl")) {
        m_uMVPMatrix = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix");
        m_uMVMatrix = glGetUniformLocation(m_program.getGLId(), "uMVMatrix");
        m_uNormalMatrix = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix");
//         m_uTextures = glGetUniformLocation(m_program.getGLId(), "uTextures");
//         m_uPonctualLights = glGetUniformLocation(m_program.getGLId(), "uPonctualLights");
//         m_uNbPonctualLights = glGetUniformLocation(m_program.getGLId(), "uNbPonctualLights");
//         m_uDirectionnalLight = glGetUniformLocation(m_program.getGLId(), "uDirectionnalLight");
}

void View::useView() const {
	m_program.use();
}

void View::sendMatrixView(const glm::mat4 MVMatrix, const glm::mat4 ProjMatrix) const {
	glUniformMatrix4fv(m_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(m_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
    glUniformMatrix4fv(m_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
}

// void View::sendTexturesView(const Texture &t) const {
//     std::vector<GLint> idTextures(t.getCubeReferences().size());
//     std::iota(std::begin(idTextures), std::end(idTextures), 0);
//     glUniform1iv(m_uTextures, idTextures.size(), idTextures.data());
// }

// void View::sendLightsView(const Lights &lights) const {
//     glUniform1i(m_uDirectionnalLight, lights.isDay());
//     glUniform1i(m_uNbPonctualLights, lights.getNbPonctualLights());
//     glm::vec3 ponctualLights[lights.getNbPonctualLights()];
//     for(int i=0; i< lights.getNbPonctualLights(); i++) {
//         ponctualLights[i] = lights.getPonctualLightsPositions()[i];
//     }
//     glUniform3fv(m_uPonctualLights, lights.getNbPonctualLights(), glm::value_ptr(ponctualLights[0]));
// }