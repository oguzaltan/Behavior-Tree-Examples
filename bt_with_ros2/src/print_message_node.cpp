#include <behaviortree_cpp/action_node.h>
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/utils/shared_library.h>
#include <iostream>

// A simple SyncActionNode that prints an input string
class PrintMessage : public BT::SyncActionNode
{
public:
	PrintMessage(const std::string& name, const BT::NodeConfig& config)
	: BT::SyncActionNode(name, config) {}

	static BT::PortsList providedPorts()
	{
		return { BT::InputPort<std::string>("msg") };
	}

	BT::NodeStatus tick() override
	{
		auto msg = getInput<std::string>("msg");
		if (!msg)
		{
			std::cerr << "[PrintMessage] missing input port: msg: " << msg.error() << std::endl;
			return BT::NodeStatus::FAILURE;
		}
		std::cout << "[PrintMessage] " << msg.value() << std::endl;
		return BT::NodeStatus::SUCCESS;
	}
};

// Register into a plugin so it can be loaded with BT::SharedLibrary
BT_REGISTER_NODES(factory)
{
	factory.registerNodeType<PrintMessage>("PrintMessage");
}