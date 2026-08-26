cmake_minimum_required(VERSION 3.20)
project(canary_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)

add_executable(tweet_publisher src/tweet_publisher.cpp)
target_link_libraries(tweet_publisher rclcpp::rclcpp ${std_msgs_TARGETS})

install(TARGETS
  tweet_publisher
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_tweet_publisher test/test_tweet_publisher.cpp)
  target_link_libraries(test_tweet_publisher rclcpp::rclcpp ${std_msgs_TARGETS})
endif()

ament_package()
