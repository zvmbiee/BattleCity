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
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void) {
    // 1. Инициализируем библиотеку GLFW
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // Установка функции для вывода ошибок
    glfwSetErrorCallback(error_callback);

    // 2. Создаем окно и контекст OpenGL
    GLFWwindow* window = glfwCreateWindow(980, 720, "Простое окно GLFW", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Делаем контекст окна текущим
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD!" << "\n";
        return -1;
    }

    std::cout << "OpenGL " << GLVersion.major << '.' << GLVersion.minor << "\n";

    glClearColor(10, 1, 0, 1);

    // Включаем вертикальную синхронизацию
    glfwSwapInterval(1);

    // Устанавливаем callback-функцию для обработки клавиш
    glfwSetKeyCallback(window, key_callback);

    // 3. Главный цикл приложения
    while (!glfwWindowShouldClose(window)) {
        // Здесь происходит отрисовка (например, glClear, glDrawArrays и т.д.)
        glClear(GL_COLOR_BUFFER_BIT);

        // Меняем буферы (выводим нарисованное на экран)
        glfwSwapBuffers(window);

        // Обрабатываем события ввода (клики мыши, нажатия клавиш)
        glfwPollEvents();
    }

    // 4. Освобождаем ресурсы и завершаем работу
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
