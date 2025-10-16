#include <rclcpp/rclcpp.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/utils/shared_library.h>
#include <filesystem>
#include <iostream>

int main(int argc, char** argv)
{
	rclcpp::init(argc, argv);
	auto node = std::make_shared<rclcpp::Node>("bt_coordinator");

	// Locate this package share directory
	const std::string pkg = "bt_with_ros2";
	std::string share_dir;
	try {
		share_dir = ament_index_cpp::get_package_share_directory(pkg);
	} catch (const std::exception& e) {
		RCLCPP_FATAL(node->get_logger(), "Failed to find package share directory: %s", e.what());
		return 1;
	}

	// Paths
	const auto bt_xml = std::filesystem::path(share_dir) / "behavior_trees" / "simple_bt.xml";
			// Derive install prefix from share_dir (share_dir = <prefix>/share/<pkg>) and build full plugin path
			const auto install_prefix = std::filesystem::path(share_dir).parent_path().parent_path();
			const auto libname = BT::SharedLibrary::getOSName("bt_with_ros2_nodes");
			const auto plugin_lib = install_prefix / "lib" / libname;

	BT::BehaviorTreeFactory factory;

		// Load plugin library containing PrintMessage node
		try {
			factory.registerFromPlugin(plugin_lib.string());
			RCLCPP_INFO(node->get_logger(), "Loaded plugin: %s", plugin_lib.c_str());
		} catch (const std::exception& e) {
			RCLCPP_FATAL(node->get_logger(), "Failed to load plugin library %s: %s", plugin_lib.c_str(), e.what());
			return 1;
		}

	// Create tree
	BT::Tree tree;
	try {
		tree = factory.createTreeFromFile(bt_xml.string());
	} catch (const std::exception& e) {
		RCLCPP_FATAL(node->get_logger(), "Failed to create tree from %s: %s", bt_xml.c_str(), e.what());
		return 1;
	}

		// (Optional) ZMQ/Groot2 publisher omitted to keep dependencies minimal

	// Set an initial Blackboard value, tick a few times
	for (int i = 1; rclcpp::ok() && i <= 3; ++i)
	{
		RCLCPP_INFO(node->get_logger(), "Tick #%d", i);
		tree.tickOnce();
		rclcpp::sleep_for(std::chrono::milliseconds(200));
	}

	rclcpp::shutdown();
	return 0;
}

