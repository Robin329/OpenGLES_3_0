//
// Created by ByteFlow on 2019/7/9.
//

#include "../util/GLUtils.h"
#include "../util/LogUtil.h"
#include "RectangleSample.h"

RectangleSample::RectangleSample() {
    LOGCATE("RectangleSample::RectangleSample");
}

RectangleSample::~RectangleSample() {
    LOGCATE("RectangleSample::RectangleSample");
}

void RectangleSample::LoadImage(NativeImage *pImage) {
    LOGCATE("RectangleSample::LoadImage");
    // null implement
}

void RectangleSample::Init() {
    LOGCATE("RectangleSample::Init");
    if (m_ProgramObj != 0) return;
    const char vShaderStr[] = "#version 300 es                          \n"
                              "layout(location = 0) in vec4 vPosition;  \n"
                              "void main()                              \n"
                              "{                                        \n"
                              "   gl_Position = vPosition;              \n"
                              "}                                        \n";

    const char fShaderStr[] = "#version 300 es                              \n"
                              "precision mediump float;                     \n"
                              "out vec4 fragColor;                          \n"
                              "void main()                                  \n"
                              "{                                            \n"
                              "   fragColor = vec4 (1.0f, 0.0f, 1.0f, 1.0f);  \n"
                              "}                                            \n";

    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);
}

void RectangleSample::Draw(int screenW, int screenH) {
    LOGCATE("RectangleSample::Draw");
    GLfloat vVertices[] = {
//            -0.5f, -0.5f, 0.0f, // bl
//            0.5f, -0.5f, 0.0f, // br
//            0.5f, 0.5f, 0.0f, // tr
//            -0.5f, 0.5f, 0.0f  // tl
            // first triangle
            -0.9f, -0.5f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top
            // second triangle
            0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top
    };

    if (m_ProgramObj == 0) return;

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Use the program object
    glUseProgram(m_ProgramObj);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 6); // set the count to 6 since we're drawing 6 vertices now (2 triangles); not 3!
    // glBindVertexArray(0); // no need to unbind it every time
    glUseProgram(GL_NONE);
}

void RectangleSample::Destroy() {
    if (m_ProgramObj) {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }
}
