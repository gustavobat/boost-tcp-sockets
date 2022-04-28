//
// Created by Gustavo on 4/28/22.
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string() {
    std::time_t now = time(nullptr);
    return ctime(&now);
}

std::string make_endpoint_string(const tcp::endpoint & endpoint) {
    std::stringstream sstr;
    sstr << endpoint.address() << ':' << endpoint.port();
    return sstr.str();
}

int main() {
    try {
        boost::asio::io_context io_context;
        
        const auto endpoint = tcp::endpoint(tcp::v4(), 1313);
        tcp::acceptor acceptor(io_context, endpoint);
    
        std::cout << "Initializing server at: "
                  << make_endpoint_string(endpoint) << std::endl;
        
        for (;;) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            
            const auto message = make_daytime_string();
            
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}