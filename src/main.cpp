#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

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
    GLFWwindow* window = glfwCreateWindow(640, 480, "Простое окно GLFW", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Делаем контекст окна текущим
    glfwMakeContextCurrent(window);

    // Включаем вертикальную синхронизацию
    glfwSwapInterval(1);

    // Устанавливаем callback-функцию для обработки клавиш
    glfwSetKeyCallback(window, key_callback);

    // 3. Главный цикл приложения
    while (!glfwWindowShouldClose(window)) {
        // Здесь происходит отрисовка (например, glClear, glDrawArrays и т.д.)

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
