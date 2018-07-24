/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#ifndef CPP_ARCADE_VULKAN_HPP
#define CPP_ARCADE_VULKAN_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <map>
#include "../../../inc/IDisplay.hpp"
#include "../../../inc/Alias.hpp"

static const std::vector<const char*>	validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

static const std::vector<const char*>	deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

struct	QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;
	bool	isComplete = false;
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR	capabilities;
	std::vector<VkSurfaceFormatKHR>	formats;
	std::vector<VkPresentModeKHR>	presentModes;
};

class Vulkan : public IDisplay {
public:
	Vulkan(size_t, size_t);
	~Vulkan() override;
public:
	bool	Display() override;
	bool	isOpen() override;
	bool	GetKey(arcade::TypeEvent, std::string const &) override;
	bool	isKey() override;
	bool	loadTexture(textureList const&) override;
	bool	loadText(textureList const&) override;
	void	destroyWindow() override;
	void	changeLibrary(std::string const &) override;
	bool	getChange() const override;
	void	setChange(bool) override;
	const std::string	&getLibraryPath() const override;
	bool	loadMap(mapChar const &) override;
	const std::string	&getNewGamePath() const override;
	void	setNewGamePath(std::string const &) override;
	bool	getSwitchScene() const override;
	void	setSwitchScene(bool) override;
private:
	void	initVulkanApi();
	void	initVulkanInfo();
	void	initSwapInfo(VkExtent2D &, uint32_t &, VkSurfaceFormatKHR &);
	void	fillSwapInfo(QueueFamilyIndices &, uint32_t *);
	void	createInstance();
	void	pickPhysicalDevice();
	void	createLogicalDevice();
	void	createSwapChain();
	void	setupDebugCallback();
	void	createSurface();
	void	createImageView();
	void	createGraphicsPipeline();
	bool	checkValidationLayerSupport();
	bool	isDeviceSuitable(VkPhysicalDevice);
	QueueFamilyIndices	findQueueFamilies(VkPhysicalDevice);
	std::vector<const char *>	getRequiredExtensions();
	bool	checkDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails	querySwapChainSupport(VkPhysicalDevice device);
	VkExtent2D	chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
	VkPresentModeKHR	chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkSurfaceFormatKHR	chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
private:
	VkSurfaceKHR		surface;
	VkPhysicalDevice	physicalDevice;
	VkDevice		device;
	VkQueue			graphicsQueue;
	VkQueue			presentQueue;
	VkPresentModeKHR	presentMode;
	VkSwapchainKHR		swapChain;
	SwapChainSupportDetails	swapChainSupport;
	std::vector<VkImage>	swapChainImages;
	VkFormat		swapChainImageFormat;
	VkExtent2D		swapChainExtent;
	std::vector<VkImageView>	swapChainImageViews;
	VkSwapchainCreateInfoKHR	swapCreateInfo;
	VkApplicationInfo	appInfo;
	VkInstanceCreateInfo	createInfo;
	std::vector<const char*>	extensions;
	VkDebugReportCallbackEXT	callback;
	VkInstance	instance;
	eventList	allEvent;
	GLFWwindow	*window;
	bool	keyPress;
	bool	windowDestroy;
	size_t	width;
	size_t	height;
};

#endif //CPP_ARCADE_VULKAN_HPP
