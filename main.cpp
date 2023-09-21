#include <iostream>

#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

using boost::asio::ip::tcp;

struct MessageOut {

    std::string msg;
    int value;

    std::string toJson() {
        nlohmann::json json;
        json["msg"] = msg;
        json["value"] = value;

        return json.dump();
    }
};

struct MessageIn {

    double value;

    static MessageIn fromJson(const std::string &data) {
        auto json = nlohmann::json::parse(data);

        MessageIn msg;
        msg.value = json["value"];

        return msg;
    }
};

int main() {

    try {
        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        tcp::resolver::query query("localhost", "8080");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        for (int i = 0; i < 10; i++) {

            MessageOut out{"Hei", 10};
            socket.write_some(boost::asio::buffer(out.toJson()));

            std::array<char, 256> buf{};
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof) {
                return 1;// error
            } else if (error) {
                throw boost::system::system_error(error);// other error
            }

            std::string recv(buf.data(), len);
            MessageIn inData = MessageIn::fromJson(recv);
            std::cout << "Received: " << inData.value << std::endl;
        }

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
