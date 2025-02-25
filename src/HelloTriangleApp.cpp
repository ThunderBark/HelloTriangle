#include <iostream>
#include <vector>
#include <algorithm>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vk_enum_string_helper.h>

#include <HelloTriangleApp.hpp>


const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;


struct ctx_t {
    GLFWwindow* window;
    VkInstance instance;
};

HelloTriangleApp::HelloTriangleApp():
    ctx(new ctx_t) {}

HelloTriangleApp::~HelloTriangleApp() {
    delete ctx;
}


void HelloTriangleApp::initWindow() {
    glfwInit();

    // Do not create OpenGl context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Disable window resizing
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create windowed window
    ctx->window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Triangle", nullptr, nullptr);
}

void HelloTriangleApp::createInstance() {
    // Optional but useful application info
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Get glfw required extensions
    uint32_t glfwExtensionCount;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    if (glfwExtensions == nullptr) {
        throw std::runtime_error("Can't get glfw required extensions!");
    }

    // List all extensions
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    std::cout << "Available extensions: " << std::endl;
    for (const auto& extension : extensions) {
        std::cout << '\t' << extension.extensionName << std::endl;
    }
    std::cout << std::endl;

    // Check if all required extensions for glfw is present
    for (uint32_t i = 0; i < glfwExtensionCount; ++i) {
        if (std::find_if(
                extensions.begin(),
                extensions.end(),
                [&](const VkExtensionProperties p) {
                    return p.extensionName == std::string(glfwExtensions[i]);
                }
            ) == extensions.end()
        ) {
            throw std::runtime_error(
                "Can't find extension required for glfw: " +
                std::string(glfwExtensions[i])
            );
        }
    }

    // Instance info specifying global extensions and validators
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    // Create vulkan instance
    VkResult res = vkCreateInstance(&createInfo, nullptr, &ctx->instance);
    if (res != VK_SUCCESS) {
        throw std::runtime_error(
            "failed to create instance! res: " +
            std::string(string_VkResult(res))
        );
    }
}

void HelloTriangleApp::initVulkan() {
    createInstance();
}

void HelloTriangleApp::mainLoop() {
    while (!glfwWindowShouldClose(ctx->window)) {
        glfwPollEvents();
    }
}

void HelloTriangleApp::cleanup() {
    vkDestroyInstance(ctx->instance, nullptr);

    glfwDestroyWindow(ctx->window);
    glfwTerminate();
}