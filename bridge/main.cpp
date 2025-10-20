#include "Wor/Network/Utils/IoService.hpp"
#include "Wor/Network/TcpClient.hpp"

#include <pugixml.hpp>

#include <sstream>
#include <unordered_map>

using namespace Wor::Network;
using namespace boost::asio::ip;
using namespace pugi;

int main() {
    auto &io{ Utils::IoService::get() };

    TcpClient client{ io };
    tcp::endpoint endPoint{ tcp::v4(), 33000 };
    tcp::resolver resolver{ io };
    const auto endPointIt{ resolver.resolve(endPoint) };
    client.start(endPointIt);

    TcpClient casparClient{ io };
    tcp::resolver casparEndPoint{ io };
    const auto casparEndPointIt{ casparEndPoint.resolve(tcp::resolver::query("169.254.8.253", "5250")) };
    casparClient.start(casparEndPointIt);

    client.receiveCallback([&casparClient](std::string message) {
        xml_document doc;
        xml_parse_result res{ doc.load_string(message.c_str()) };
        if (res.status != xml_parse_status::status_ok) {
            return;
        }
        xml_node root{ doc.first_child() };

        std::unordered_map<std::string, std::string> items;
        std::ranges::for_each(root.attributes(),
                              [&items](const xml_attribute &each) {
                                  items[each.name()] = each.value();
                              });
        std::stringstream ss;
        ss << items["action"] << " 1-1 " << items["file"] << " \r\n";

        casparClient.send(ss.str());
        std::printf("CALLBACK SAYS: %s\n", message.c_str());
    });

    std::thread t{ [&io]() {
        io.run();
    } };

    t.join();

    return 0;
}
