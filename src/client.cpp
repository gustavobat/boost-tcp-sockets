//
// Created by Gustavo on 4/28/22.
//

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }
        
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        
        const auto host_name = argv[1];
        const auto service_name = "daytime";
        const auto endpoints = resolver.resolve(host_name, service_name);
        
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);
        
        for (;;) {
            boost::array<char, 128> buf{};
            boost::system::error_code error;
            
            const auto len = socket.read_some(boost::asio::buffer(buf), error);
            
            if (error) {
                // Connection closed
                if (error == boost::asio::error::eof) break;
                // Other errors
                throw boost::system::system_error(error);
            }
            
            std::cout.write(buf.data(), len);
        }
    }
    
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}