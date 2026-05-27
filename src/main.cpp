#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Функция для обработки ошибок GLFW
static void error_callback(int error, const char* description) {
    fprintf(stderr, "Ошибка: %s\n", description);
}

// Функция для обработки ввода с клавиатуры
static void key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
}

int g_windowSizeX = 640;
int g_windowSizeY = 480;

static void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int heigth) {
    g_windowSizeX = width;
    g_windowSizeY = heigth;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
}

int main(void) {
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
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Battle City", nullptr, nullptr);
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


    glClearColor(10, 1, 0, 1);

    // Включаем вертикальную синхронизацию
    glfwSwapInterval(1);

    // Устанавливаем callback-функцию для обработки клавиш
    glfwSetKeyCallback(pWindow, key_callback);

    // 3. Главный цикл приложения
    while (!glfwWindowShouldClose(pWindow)) {
        // Здесь происходит отрисовка (например, glClear, glDrawArrays и т.д.)
        glClear(GL_COLOR_BUFFER_BIT);

        // Меняем буферы (выводим нарисованное на экран)
        glfwSwapBuffers(pWindow);

        // Обрабатываем события ввода (клики мыши, нажатия клавиш)
        glfwPollEvents();
    }

    // 4. Освобождаем ресурсы и завершаем работу
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
