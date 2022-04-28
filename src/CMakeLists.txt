add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_directories(server PUBLIC ${Boost_LIBRARIES})
target_link_directories(client PUBLIC ${Boost_LIBRARIES})
