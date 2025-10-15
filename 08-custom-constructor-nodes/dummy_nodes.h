#include <iostream>
#include <chrono>
#include <thread>
#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"

using namespace BT;

// Action_A has a different constructor than the default one.
class Action_A: public SyncActionNode
{
public:
    // additional arguments passed to the constructor
    Action_A(const std::string& name, const NodeConfig& config,
             int arg_int, std::string arg_str):
        SyncActionNode(name, config),
        _arg1(arg_int),
        _arg2(arg_str) {}

    // this example doesn't require any port
    static PortsList providedPorts() { return {}; }

    // tick() can access the private members
    NodeStatus tick() override
    {
        // Example behavior: print args then succeed
        std::cout << "[ Action_A ] arg1=" << _arg1 << " arg2=" << _arg2 << std::endl;
        return NodeStatus::SUCCESS;
    }

private:
    int _arg1;
    std::string _arg2;
};


class Action_B: public SyncActionNode
{
public:
    // The constructor looks as usual.
    Action_B(const std::string& name, const NodeConfig& config):
        SyncActionNode(name, config) {}

    // We want this method to be called ONCE and BEFORE the first tick()
    void initialize(int arg_int, const std::string& arg_str)
    {
        _arg1 = arg_int;
        _arg2 = arg_str;
    }

    // this example doesn't require any port
    static PortsList providedPorts() { return {}; }

    // tick() can access the private members
    NodeStatus tick() override
    {
        // Example behavior: print args then succeed
        std::cout << "[ Action_B ] arg1=" << _arg1 << " arg2=" << _arg2 << std::endl;
        return NodeStatus::SUCCESS;
    }

private:
    int _arg1;
    std::string _arg2;
};
