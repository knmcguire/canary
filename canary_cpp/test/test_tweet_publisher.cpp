// Copyright 2026 canary maintainers
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "canary_cpp/tweet_publisher.hpp"

TEST(TweetPublisherTest, PublishesTweetOnChatter)
{
  auto publisher_node = std::make_shared<TweetPublisher>();

  std::string received_data;
  auto subscriber_node = std::make_shared<rclcpp::Node>("test_subscriber");
  auto subscription = subscriber_node->create_subscription<std_msgs::msg::String>(
    "chatter", 10,
    [&received_data](const std_msgs::msg::String & msg) {
      received_data = msg.data;
    });

  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(publisher_node);
  executor.add_node(subscriber_node);

  const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
  while (received_data.empty() && std::chrono::steady_clock::now() < deadline) {
    executor.spin_once(std::chrono::milliseconds(100));
  }

  EXPECT_EQ(received_data, "tweet");
}

int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  rclcpp::init(argc, argv);
  int result = RUN_ALL_TESTS();
  rclcpp::shutdown();
  return result;
}
