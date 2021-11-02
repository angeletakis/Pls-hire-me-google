#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <filesystem>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

// Define the LOG() macro in order to be able to add
// a logger in the future without too much refactoring
//#define LOG(x) BOOST_LOG_TRIVIAL(x)
#define LOG(x) std::cout

int main(int argc, char **argv) {
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h",                       "produce help message")
            ("parents,p", po::bool_switch(), "no error if existing, make parent directories as needed")
            ("verbose,v", po::bool_switch(), "print a message for each created directory");

    const po::parsed_options parsed = po::command_line_parser(argc, argv)
            .options(desc).allow_unregistered().run();
    const std::vector<std::string> unrecognized =
            collect_unrecognized(parsed.options, po::include_positional);
    po::variables_map vm;
    po::store(parsed, vm);
    po::notify(vm);

    for (const auto &opt : unrecognized) {
        if (opt[0] == '-') {
            LOG(fatal) << "Unknown option '" << opt << "'\n";
            return 1;
        }
    }
    if (vm.count("help") || argc <= 1) {
        LOG(fatal) << desc;
        return 1;
    }
    std::error_code ec;
    for (const auto &dir_name : unrecognized) {
        auto path = std::filesystem::absolute(std::filesystem::path(dir_name));
        if (vm["parents"].as<bool>())
            std::filesystem::create_directories(path, ec);
        else
            std::filesystem::create_directory(path, ec);
        if (errno) {
            LOG(fatal) << "Cannot create directory '" << dir_name
                       << "': " << strerror(errno) << '\n';
            errno = 0;
        } else {
            LOG(info) << "Created directory '" << dir_name << "'\n";
        }
    }
    return 0;
}