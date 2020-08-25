/** @file cameraTests.cpp
 * -----------------------------
 * @brief Tests camera functions.
 * @author Bartolone, Kai
 * @date June 2020
 */

#include <gtest/gtest.h>
#include <server.hpp>

/** @test Run_Server
 * -----------------------------
 * Just runs server for testing purposes
 */
TEST(ServerTests, Run_Server)
{
    TcpServer server;
    while (!server.hasConnection())
    {
        std::cout << "No Connection" << std::endl;
    }
    server.addMessage("log", "this is a test");
    server.~TcpServer();
}