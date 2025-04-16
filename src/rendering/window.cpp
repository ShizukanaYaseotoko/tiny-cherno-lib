#include "window.hpp"
#include "GLFW/glfw3.h"
#include <utility>

namespace tiny_cherno {

    Window::Window(WindowParameters params) {
        m_handle = glfwCreateWindow(params.width, params.height, params.title, NULL, NULL);
    }

    void Window::Update() {
        glfwPollEvents();
        m_renderingContext->SwapBuffers();
    }

    std::pair<int, int> Window::Size() const {
        int width = 0, height = 0;
        glfwGetWindowSize(m_handle, &width, &height);
        return std::make_pair(width, height);
    }

    int Window::Width() const {
        return Size().first;
    }

    int Window::Height() const {
        return Size().second;
    }

    void Window::SetWidth(unsigned int width) {
        glfwSetWindowSize(m_handle, width, Height());
    }

    void Window::SetHeight(unsigned int height) {
        glfwSetWindowSize(m_handle, Width(), height);
    }

    bool Window::IsResizable() const {
        return GetAttribute(GLFW_RESIZABLE);
    }

    void Window::SetResizable(bool resizable) {
        SetAttribute(GLFW_RESIZABLE, resizable);
    }

    bool Window::IsVisible() const {
        return GetAttribute(GLFW_VISIBLE);
    }

    void Window::Show() {
        glfwWindowHint(GLFW_VISIBLE, true);
    }

    void Window::Hide() {
        glfwWindowHint(GLFW_VISIBLE, false);
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_handle);
    }

    void Window::Close() {
        glfwSetWindowShouldClose(m_handle, true);
    }

    const char* Window::Title() const {
        return glfwGetWindowTitle(m_handle);
    }

    void Window::SetTitle(const char* title) {
        glfwSetWindowTitle(m_handle, title);
    }

    int Window::GetAttribute(int attribute) const {
        return glfwGetWindowAttrib(m_handle, attribute);
    }

    void Window::SetAttribute(int attribute, int value) {
        glfwSetWindowAttrib(m_handle, attribute, value);
    }

    RenderingContext *Window::Context() {
        return m_renderingContext;
    }

    void Window::SetRenderingContext(RenderingContext *context) {
        m_renderingContext = context;
    }

    GLFWwindow *Window::Handle() const {
        return m_handle;
    }

}
