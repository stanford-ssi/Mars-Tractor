/**
 * @file clientTests.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <client.hpp>
#include <gtest/gtest.h>

/** @test Run_Client
 * -----------------------------
 * Just runs client for testing purposes
 */
TEST(ClientTests, Run_Client)
{
    TcpClient client("192.168.`.58");
    client.connect();
}