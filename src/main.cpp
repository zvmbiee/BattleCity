#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Функция для обработки ошибок GLFW
static void error_callback(int error, const char* description) {
    fprintf(stderr, "Ошибка: %s\n", description);
}

// Функция для обработки ввода с клавиатуры
static void key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
}

GLfloat point[] = {
     0.0f,  50.f, 0.0f,
     50.f, -50.f, 0.0f,
    -50.f, -50.f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat texCoord[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

glm::ivec2 g_windowSize(640, 480);

static void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int heigth) {
    g_windowSize.x = width;
    g_windowSize.y = heigth;
    glViewport(0, 0, g_windowSize.x, g_windowSize.y);
}

int main(int argc, char** argv) {

    // 1. Инициализируем библиотеку GLFW
    if (!glfwInit()) {
        std::cout << "glfwInit failed!" << "\n";
        exit(EXIT_FAILURE);
    }

    // Установка функции для вывода ошибок
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Создаем окно и контекст OpenGL
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);
    if (!pWindow) {
        std::cout << "glfwCreateWindow failed!" << "\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);

    // Делаем контекст окна текущим
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD!" << "\n";
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";


    glClearColor(1, 1, 0, 1);

    {
        ResourceManager resourceManager(argv[0]);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram) {
            std::cerr << "Can't create shader program: " << "DefaultShader\n";
            return -1;
        }

        auto pSpriteShaderProgram = resourceManager.loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
        if (!pDefaultShaderProgram) {
            std::cerr << "Can't create shader program: " << "SpriteShader\n";
            return -1;
        }

        auto tex = resourceManager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");

        auto pSprite = resourceManager.loadSprite("NewSprite", "DefaultTexture", "SpriteShader", 200, 300);
        pSprite->setPosition(glm::vec2(0, 180));

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint texCoord_vbo = 0;
        glGenBuffers(1, &texCoord_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);

        glm::mat4 mode1Matrix_1 = glm::mat4(1.f);
        mode1Matrix_1 = glm::translate(mode1Matrix_1, glm::vec3(50.f, 50.f, 0.f));

        glm::mat4 mode1Matrix_2 = glm::mat4(1.f);
        mode1Matrix_2 = glm::translate(mode1Matrix_2, glm::vec3(150.f, 50.f, 0.f));

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y), -100.f, 100.f);


        pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        pSpriteShaderProgram->use();
        pSpriteShaderProgram->setInt("pSprite", 0);

        pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        // Включаем вертикальную синхронизацию
        glfwSwapInterval(1);

        // Устанавливаем callback-функцию для обработки клавиш
        glfwSetKeyCallback(pWindow, key_callback);

        // 3. Главный цикл приложения
        while (!glfwWindowShouldClose(pWindow)) {
            // Здесь происходит отрисовка (например, glClear, glDrawArrays и т.д.)
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();

            glBindVertexArray(vao);
            tex->bind();

            pDefaultShaderProgram->setMatrix4("modelMat", mode1Matrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            pDefaultShaderProgram->setMatrix4("modelMat", mode1Matrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            pSprite->render();

            // Меняем буферы (выводим нарисованное на экран)
            glfwSwapBuffers(pWindow);

            // Обрабатываем события ввода (клики мыши, нажатия клавиш)
            glfwPollEvents();
        }
    }

    // 4. Освобождаем ресурсы и завершаем работу
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
