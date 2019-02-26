#include "pch.h"

#include <iostream>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <AUIApplication.h>
#include <AUIRasterWidgetManager.h>
#include <AUILinearLayoutWidget.h>
#include <AUITextWidget.h>
#include <AUIColorDrawable.h>

#include <SkSurface.h>

constexpr auto VertexShaderCode = R"(
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;

out vec2 oTexCoord;

uniform mat4 uMatModelView;

void main() {
    oTexCoord = texcoord;

    //gl_Position = uMatModelView * vec4(position, 1.0);
    gl_Position.xyz = position;
    gl_Position.w = 1.0;
}
)";
constexpr auto FragmentShaderCode = R"(
#version 330 core

in vec2 oTexCoord;

out vec4 color;

uniform sampler2D uTexture;

void main() {
    color = texture(uTexture, oTexCoord);
}
)";

class Shader final {
public:
    Shader() = default;
    ~Shader() {
        this->Destroy();
    }

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept : m_Id{ other.m_Id } {
        other.m_Id = 0;
    }
    Shader& operator=(Shader&& other) noexcept {
        this->m_Id = other.m_Id;
        other.m_Id = 0;
        return *this;
    }

    bool IsValid() const {
        return (GL_FALSE != glIsShader(m_Id));
    }
    bool CreateVertexShader(const char* shaderCode) {
        m_Id = glCreateShader(GL_VERTEX_SHADER);
        if (!this->IsValid())
            return false;
        glShaderSource(m_Id, 1, &shaderCode, nullptr);
        glCompileShader(m_Id);
        int result = GL_FALSE;
        glGetShaderiv(m_Id, GL_COMPILE_STATUS, &result);
        if (GL_FALSE == result) {
            this->Destroy();
            return false;
        }
        return true;
    }
    bool CreateFragmentShader(const char* shaderCode) {
        m_Id = glCreateShader(GL_FRAGMENT_SHADER);
        if (!this->IsValid())
            return false;
        glShaderSource(m_Id, 1, &shaderCode, nullptr);
        glCompileShader(m_Id);
        int result = GL_FALSE;
        glGetShaderiv(m_Id, GL_COMPILE_STATUS, &result);
        if (GL_FALSE == result) {
            this->Destroy();
            return false;
        }
        return true;
    }
    bool Destroy() {
        if (this->IsValid()) {
            glDeleteShader(m_Id);
            m_Id = 0;
            return true;
        }
        return false;
    }

    GLuint Id() const noexcept {
        return m_Id;
    }
private:
    GLuint m_Id = 0;
};

class ShaderProgram final {
public:
    ShaderProgram() = default;
    ~ShaderProgram() {
        this->Destroy();
    }

    bool IsValid() const {
        return (GL_FALSE != glIsProgram(m_Id));
    }
    bool Create(const Shader& vtxShader, const Shader& fragmentShader) {
        if (false == vtxShader.IsValid())
            return false;
        if (false == fragmentShader.IsValid())
            return false;

        m_Id = glCreateProgram();
        if (false == IsValid())
            return false;

        glAttachShader(m_Id, vtxShader.Id());
        glAttachShader(m_Id, fragmentShader.Id());
        glLinkProgram(m_Id);

        int result = GL_FALSE;
        glGetProgramiv(m_Id, GL_LINK_STATUS, &result);
        if (GL_FALSE == result) {
            this->Destroy();
            return false;
        }

        glDetachShader(m_Id, vtxShader.Id());
        glDetachShader(m_Id, fragmentShader.Id());

        return true;
    }
    bool Destroy() {
        if (IsValid()) {
            glDeleteProgram(m_Id);
            m_Id = 0;
            return true;
        }
        return false;
    }

    GLuint GetUniformId(const char* name) {
        if (false == this->IsValid())
            return 0;
        return glGetUniformLocation(m_Id, name);
    }

    void UseProgram() {
        if (IsValid()) {
            glUseProgram(m_Id);
        }
    }
    void UnuseProgram() {
        glUseProgram(0);
    }

    GLuint Id() const {
        return m_Id;
    }
private:
    GLuint m_Id = 0;
};

class Texture2D final
{
public:
    Texture2D() = default;
    ~Texture2D() {
        this->Destroy();
    }

    bool IsValid() const {
        return (GL_FALSE != glIsTexture(m_Id));
    }
    bool Create() {
        glGenTextures(1, &m_Id);
        glBindTexture(GL_TEXTURE_2D, m_Id);
        char tmp[4] = { 0, };
        glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, 1, 1, 0, GL_BGRA, GL_UNSIGNED_BYTE, tmp);
        if (false == IsValid())
            return false;
        return true;
    }

    bool UpdateImage(const SkPixmap& pixmap) {
        if (false == IsValid())
            return false;
        glBindTexture(GL_TEXTURE_2D, m_Id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, pixmap.width(), pixmap.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, pixmap.addr());
        return true;
    }

    bool Destroy() {
        if (this->IsValid()) {
            glDeleteTextures(1, &m_Id);
            m_Id = 0;
            return true;
        }
        return false;
    }
    bool Bind() {
        if (false == this->IsValid())
            return false;
        glBindTexture(GL_TEXTURE_2D, m_Id);
        return true;
    }
private:
    GLuint m_Id = 0;
};

class SampleState final
{
public:
    SampleState() = default;
    ~SampleState() {
        this->Destroy();
    }

    bool IsValid() const {
        return (GL_FALSE != glIsSampler(m_Id));
    }
    bool Create() {
        glGenSamplers(1, &m_Id);
        if (false == IsValid())
            return false;
        glSamplerParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glSamplerParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glSamplerParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glSamplerParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        return true;
    }
    bool Destroy() {
        if (this->IsValid()) {
            glDeleteSamplers(1, &m_Id);
            m_Id = 0;
            return true;
        }
        return false;
    }

    GLuint Id() const {
        return m_Id;
    }
private:
    GLuint m_Id = 0;
};

class QuadModel final
{
public:
    QuadModel() = default;
    ~QuadModel() {
        this->Destroy();
    }

    bool IsValid() const {
        return (GL_FALSE != glIsVertexArray(m_Id));
    }
    bool Create() {
        glGenVertexArrays(1, &m_Id);
        glBindVertexArray(m_Id);

        glGenBuffers(1, &m_IdVtx);
        static const std::array<float, 18> sVtxData = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f
        };

        glBindBuffer(GL_ARRAY_BUFFER, m_IdVtx);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sVtxData.size(), sVtxData.data(), GL_STATIC_DRAW);

        static const std::array<float, 12> sTexCoordData = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        };
        glGenBuffers(1, &m_IdTex);
        glBindBuffer(GL_ARRAY_BUFFER, m_IdTex);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sTexCoordData.size(), sTexCoordData.data(), GL_STATIC_DRAW);

        if (false == IsValid())
            return false;

        return true;
    }
    bool Destroy() {
        if (this->IsValid()) {
            glDeleteBuffers(1, &m_IdTex);
            glDeleteBuffers(1, &m_IdVtx);
            glDeleteVertexArrays(1, &m_Id);
            m_Id = 0;
            m_IdVtx = 0;
            m_IdTex = 0;
            return true;
        }
        return false;
    }
    void Draw() {
        if (false == IsValid())
            return;
        glBindVertexArray(m_Id);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_IdVtx);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_IdTex);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(0);
    }
private:
    GLuint m_Id = 0;
    GLuint m_IdVtx = 0;
    GLuint m_IdTex = 0;
};


constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;

int main() {
    // Initialize GLFW3
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW3\n";
        return EXIT_FAILURE;
    }

    // Set context hint
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    const auto window = glfwCreateWindow(kWindowWidth, kWindowHeight, "AliceUI Framework OpenGL Example", nullptr, nullptr);
    if (nullptr == window) {
        std::cerr << "Failed to create GLFW window.";
        return EXIT_FAILURE;
    }

    // Init Alice UI Framework
    AUIApplicationAutoInit appAutoInit;

    // Create raster widget manager
    std::unique_ptr<AUIRasterWidgetManager> pWidgetManager(new AUIRasterWidgetManager());

    // Create root widget
    auto pRootLayout = std::make_shared<AUILinearLayoutWidget>();
    auto pText = std::make_shared<AUITextWidget>(L"Hello, World!");
    pText->SetDefaultSize(200.0f, 30.0f);
    pText->SetBackgroundDrawable(std::make_shared<AUIColorDrawable>(SkColorSetARGB(128, 255, 128, 200)));
    pRootLayout->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kParent);
    pRootLayout->AddSubWidget(pText);
    pRootLayout->UpdateChildPosition();
    pRootLayout->UpdateSize();
    pWidgetManager->CreateInstance(pRootLayout);
    pRootLayout->SetDefaultSize(SkIntToScalar(kWindowWidth), SkIntToScalar(kWindowHeight));

    // Create skia surface
    auto pSurface = SkSurface::MakeRaster(SkImageInfo::MakeN32(kWindowWidth, kWindowHeight, SkAlphaType::kOpaque_SkAlphaType));

    // Time reference
    auto prevTickTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    if (GLEW_OK != glewInit()) {
        std::cerr << "Failed to initialize GLEW\n";
        return EXIT_FAILURE;
    }

    Shader vertexShader;
    if (false == vertexShader.CreateVertexShader(VertexShaderCode)) {
        std::cerr << "Failed to create vertex shader\n";
        return EXIT_FAILURE;
    }

    Shader fragmentShader;
    if (false == fragmentShader.CreateFragmentShader(FragmentShaderCode)) {
        std::cerr << "Failed to create fragment shader\n";
        return EXIT_FAILURE;
    }

    ShaderProgram program;
    if (false == program.Create(vertexShader, fragmentShader)) {
        std::cerr << "Failed to create shader program\n";
        return EXIT_FAILURE;
    }

    QuadModel model;
    if (false == model.Create()) {
        std::cerr << "Failed to create model\n";
        return EXIT_FAILURE;
    }

    Texture2D texture;
    if (false == texture.Create()) {
        std::cerr << "Failed to create texture\n";
        return EXIT_FAILURE;
    }

    SampleState samplerState;
    if (false == samplerState.Create()) {
        std::cerr << "Failed to create sampler state\n";
        return EXIT_FAILURE;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        do
        {
            // Update task
            AUIApplication::Instance().RunUpdateInstanceTask();
            AUIApplication::Instance().RunLazyUpdate();

            // Update time
            const auto currentTickTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            pWidgetManager->SendTickTimeEvent(prevTickTime, currentTickTime);
            prevTickTime = currentTickTime;

            // Update instances
            pWidgetManager->UpdateAllInstance();

            // Render
            pSurface->getCanvas()->clear(SkColorSetARGB(200, 255, 255, 255));
            pWidgetManager->Render(pSurface->getCanvas());
            const auto pImage = pSurface->makeImageSnapshot();
            if (nullptr == pImage)
                break;

            SkPixmap pixmap;
            if (false == pImage->peekPixels(&pixmap))
                break;

            texture.UpdateImage(pixmap);

        } while (false);


        // Render in OpenGL

        program.UseProgram();

        glUniform1i(program.GetUniformId("uTexture"), 0);
        glActiveTexture(GL_TEXTURE0 + 0);
        texture.Bind();
        glBindSampler(0, samplerState.Id());


        model.Draw();

        program.UnuseProgram();

        glfwSwapBuffers(window);
        glfwPollEvents();

        const auto key = glfwGetKey(window, GLFW_KEY_ESCAPE);
        if (key == GLFW_PRESS) {
            break;
        }
    }

    return EXIT_SUCCESS;
}
