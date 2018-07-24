/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#define GLFW_INCLUDE_VULKAN
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <set>
#include <limits>
#include "Vulkan.hpp"
#include "../../../inc/ArcadeException.hpp"

// When I wrote this,
// only God and I understood what I was doing
// Now, God only knows

VkResult	CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
	auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	} else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void	DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr) {
		func(instance, callback, pAllocator);
	}
}

static VKAPI_ATTR VkBool32 VKAPI_CALL	debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
	std::cerr << "validation layer: " << msg;
	(void)flags;
	(void)objType;
	(void)obj;
	(void)location;
	(void)code;
	(void)layerPrefix;
	(void)userData;
	return VK_FALSE;
}

void	Vulkan::setupDebugCallback()
{
	VkDebugReportCallbackCreateInfoEXT createInfo = {};

	if (!enableValidationLayers)
		return;
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	createInfo.pfnCallback = debugCallback;
	if (CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback) != VK_SUCCESS) {
		throw arcade::GraphicsLibraryError("failed to set up debug callback!");
	}
}

std::vector<const char*>	Vulkan::getRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}

	return extensions;
}

bool	Vulkan::checkValidationLayerSupport()
{
	bool		layerFound;
	uint32_t	layerCount;
	std::vector<VkLayerProperties>	availableLayers;

	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	availableLayers.resize(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
	for (const char *layerName : validationLayers) {
		layerFound = false;
		for (auto const &layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}
		if (!layerFound) {
			return false;
		}
	}
	return true;
}

Vulkan::Vulkan(size_t width, size_t height) : physicalDevice(VK_NULL_HANDLE), width(width), height(height)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(width, height, "Arcade - Vulkan", nullptr, nullptr);
	if (!window)
		throw arcade::GraphicsLibraryError("Vulkan: error while init window");
	initVulkanApi();
	allEvent.insert({arcade::ESCAPE, GLFW_KEY_ESCAPE});
	allEvent.insert({arcade::UP, GLFW_KEY_UP});
	allEvent.insert({arcade::LEFT, GLFW_KEY_LEFT});
	allEvent.insert({arcade::DOWN, GLFW_KEY_DOWN});
	allEvent.insert({arcade::RIGHT, GLFW_KEY_RIGHT});
	allEvent.insert({arcade::Q, GLFW_KEY_Q});
	allEvent.insert({arcade::M, GLFW_KEY_M});
	keyPress = false;
	change = false;
	switchScene = false;
	windowDestroy = false;
}

Vulkan::~Vulkan()
{
	glfwTerminate();
}

bool	Vulkan::GetKey(arcade::TypeEvent typeEvent, std::string const &currentEvent)
{
	(void)typeEvent;
	for (auto const &key : allEvent) {
		if (key.first == currentEvent && glfwGetKey(window, key.second) == GLFW_PRESS) {
			return true;
		}
	}
	return false;
}

bool	Vulkan::isKey()
{
	glfwPollEvents();
	keyPress = !keyPress;
	return keyPress;
}

bool	Vulkan::isOpen()
{
	return !windowDestroy;
}

bool	Vulkan::Display()
{
	return false;
}

void	Vulkan::destroyWindow()
{
	if (!windowDestroy) {
		for (auto imageView : swapChainImageViews) {
			vkDestroyImageView(device, imageView, nullptr);
		}
		vkDestroySwapchainKHR(device, swapChain, nullptr);
		vkDestroyDevice(device, nullptr);
		if (enableValidationLayers) {
			DestroyDebugReportCallbackEXT(instance, callback, nullptr);
		}
		vkDestroySurfaceKHR(instance, surface, nullptr);
		vkDestroyInstance(instance, nullptr);
		glfwDestroyWindow(window);
	}
	windowDestroy = true;
}

bool Vulkan::loadText(std::map<std::string, Texture> const& text)
{
	(void)text;
	return false;
}

bool Vulkan::loadTexture(std::map<std::string, Texture> const& texture)
{
	(void)texture;
	return false;
}

void Vulkan::changeLibrary(std::string const &path)
{
	change = true;
	newLibraryPath = path;
}

bool Vulkan::getChange() const
{
	return change;
}

void Vulkan::setChange(bool state)
{
	change = state;
}

const std::string &Vulkan::getLibraryPath() const
{
	return newLibraryPath;
}

bool Vulkan::loadMap(std::vector<std::vector<char>> const &map)
{
	(void)map;
	return false;
}

const std::string &Vulkan::getNewGamePath() const
{
	return newGamePath;
}

void Vulkan::setNewGamePath(std::string const &path)
{
	newGamePath = path;
}

bool Vulkan::getSwitchScene() const
{
	return switchScene;
}

void Vulkan::setSwitchScene(bool state)
{
	switchScene = state;
}

void	Vulkan::initVulkanApi()
{
	appInfo = {};
	createInfo = {};
	createInstance();
	setupDebugCallback();
	createSurface();
	pickPhysicalDevice();
	createLogicalDevice();
	swapChainSupport = querySwapChainSupport(physicalDevice);
	presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	swapCreateInfo = {};
	createSwapChain();
	createImageView();
	createGraphicsPipeline();
}

void	Vulkan::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	std::vector<VkPhysicalDevice> devices(deviceCount);

	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if (deviceCount == 0) {
		throw arcade::GraphicsLibraryError("failed to find GPUs with Vulkan support!");
	}
	devices.resize(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
	for (const auto& device : devices) {
		if (isDeviceSuitable(device)) {
			physicalDevice = device;
			break;
		}
	}
	if (physicalDevice == VK_NULL_HANDLE) {
		throw arcade::GraphicsLibraryError("failed to find a suitable GPU!");
	}
}

bool	Vulkan::isDeviceSuitable(VkPhysicalDevice device)
{
	QueueFamilyIndices	indices = findQueueFamilies(device);
	bool	extensionsSupported = checkDeviceExtensionSupport(device);
	SwapChainSupportDetails	swapChainSupport;
	bool	swapChainAdequate = false;

	if (extensionsSupported) {
		swapChainSupport = querySwapChainSupport(device);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}
	return indices.isComplete && extensionsSupported && swapChainAdequate;
}

QueueFamilyIndices	Vulkan::findQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices	indices;
	uint32_t	count = 0;
	uint32_t	queueFamilyCount = 0;
	VkBool32	presentSupport = VK_FALSE;
	std::vector<VkQueueFamilyProperties>	queueFamilies;

	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
	queueFamilies.resize(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = count;
		}
		vkGetPhysicalDeviceSurfaceSupportKHR(device, count, surface, &presentSupport);
		if (queueFamily.queueCount > 0 && presentSupport)
			indices.presentFamily = count;
		if (indices.graphicsFamily >= 0 && indices.presentFamily >= 0) {
			break;
		}
		count++;
	}
	indices.isComplete = indices.graphicsFamily >= 0 && indices.presentFamily >= 0;
	return indices;
}

void	Vulkan::initVulkanInfo()
{
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Arcade";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();
}

void	Vulkan::createInstance()
{

	if (enableValidationLayers && !checkValidationLayerSupport())
		throw arcade::GraphicsLibraryError("validation layers requested, but not available!");
	extensions = getRequiredExtensions();
	initVulkanInfo();
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	} else
		createInfo.enabledLayerCount = 0;
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		throw arcade::GraphicsLibraryError("failed to create instance!");
}

void	Vulkan::createLogicalDevice()
{
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<int>	uniqueQueueFamilies = {indices.graphicsFamily, indices.presentFamily};
	VkPhysicalDeviceFeatures deviceFeatures = {};
	VkDeviceCreateInfo createInfo = {};
	VkDeviceQueueCreateInfo queueCreateInfo = {};
	float queuePriority = 1.0f;

	for (auto queueFamily : uniqueQueueFamilies) {
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.emplace_back(queueCreateInfo);
	}
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = 0;
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	} else {
		createInfo.enabledLayerCount = 0;
	}
	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}
	vkGetDeviceQueue(device, (uint32_t)indices.graphicsFamily, 0, &graphicsQueue);
	vkGetDeviceQueue(device, (uint32_t)indices.presentFamily, 0, &presentQueue);
}

void Vulkan::createSurface()
{
	VkResult	result;
	result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
	if (result != VK_SUCCESS)
		throw arcade::GraphicsLibraryError("Unable to create Vulkan surface");
}

VkSurfaceFormatKHR Vulkan::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
		return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
	}
	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}
	return availableFormats[0];
}

VkPresentModeKHR Vulkan::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		} else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
			bestMode = availablePresentMode;
		}
	}
	return bestMode;
}

VkExtent2D Vulkan::chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
	VkExtent2D actualExtent = {(uint32_t)width, (uint32_t)height};

	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
	actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));
	return actualExtent;
}

SwapChainSupportDetails	Vulkan::querySwapChainSupport(VkPhysicalDevice device)
{
	SwapChainSupportDetails details;
	uint32_t presentModeCount;
	uint32_t formatCount;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
	}
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
	}
	return details;
}

bool	Vulkan::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
	std::vector<VkExtensionProperties> availableExtensions;
	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
	availableExtensions.resize(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}
	return requiredExtensions.empty();
}

void	Vulkan::initSwapInfo(VkExtent2D &extent, uint32_t &imageCount, VkSurfaceFormatKHR &surfaceFormat)
{
	swapCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapCreateInfo.surface = surface;
	swapCreateInfo.minImageCount = imageCount;
	swapCreateInfo.imageFormat = surfaceFormat.format;
	swapCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
	swapCreateInfo.imageExtent = extent;
	swapCreateInfo.imageArrayLayers = 1;
	swapCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapCreateInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	swapCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapCreateInfo.presentMode = presentMode;
	swapCreateInfo.clipped = VK_TRUE;
	swapCreateInfo.oldSwapchain = VK_NULL_HANDLE;
}

void	Vulkan::fillSwapInfo(QueueFamilyIndices &indices, uint32_t *queueFamilyIndices)
{
	if (indices.graphicsFamily != indices.presentFamily) {
		swapCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		swapCreateInfo.queueFamilyIndexCount = 2;
		swapCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
	} else {
		swapCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}
}

void	Vulkan::createSwapChain()
{
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
	uint32_t queueFamilyIndices[] = {(uint32_t)indices.graphicsFamily, (uint32_t) indices.presentFamily};
	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}
	initSwapInfo(extent, imageCount, surfaceFormat);
	fillSwapInfo(indices, queueFamilyIndices);
	if (vkCreateSwapchainKHR(device, &swapCreateInfo, nullptr, &swapChain) != VK_SUCCESS) {
		throw arcade::GraphicsLibraryError("failed to create swap chain!");
	}
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
	swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());
	swapChainImageFormat = surfaceFormat.format;
	swapChainExtent = extent;
}

void Vulkan::createImageView()
{
	VkImageViewCreateInfo createInfo = {};

	swapChainImageViews.resize(swapChainImages.size());
	for (size_t i = 0; i < swapChainImages.size(); i++) {
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = swapChainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapChainImageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;
		if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
			throw arcade::GraphicsLibraryError("failed to create image views!");
		}
	}
}

void Vulkan::createGraphicsPipeline()
{
}