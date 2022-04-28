//
// Created by Gustavo on 4/28/22.
//

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main() {
    try {
        
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        
        const auto endpoint = tcp::endpoint(tcp::v4(), 1313);
        
        tcp::socket socket(io_context);
        socket.connect(endpoint);
        
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