/** @file serverTests.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <camera.hpp>
#include <chrono>
#include <gtest/gtest.h>
#include <server.hpp>
#include <thread>

/**
 * @test SendFrame
 * -----------------------------
 * Sends a Mat to the client.
 */
TEST(ServerTests, SendFrame)
{
    TcpServer server;
    while (!server.hasConnection())
    {
        std::cout << "No Connection" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "Connected" << std::endl;
    std::string oop = "test";

    while (oop != "q")
    {
        cv::Mat frame = cv::Mat(cv::Size(1920, 1080), CV_8UC3, cv::Scalar(0, 255, 255));
        server.addMessage("frame", cf::serializeMat(frame));
        std::cout << "frame sent" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    server.~TcpServer();
}

/** @test Run_Server
 * -----------------------------
 * Just runs server for testing purposes
 */
// TEST(ServerTests, Run_Server)
// {
//     TcpServer server;
//     while (!server.hasConnection())
//     {
//         std::cout << "No Connection" << std::endl;
//         std::this_thread::sleep_for(std::chrono::seconds(2));
//     }

//     std::cout << "Connected" << std::endl;
//     std::string oop = "test";

//     while (oop != "q")
//     {
//         std::cin >> oop;
//         std::cout << "echo" << oop << std::endl;
//         server.addMessage("log", oop);
//     }
//     server.~TcpServer();
// }