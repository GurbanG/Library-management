cmake_minimum_required(VERSION 3.23)
project(Library_system)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Library_system
        DB/database.cpp
        system.cpp Users/Password.cpp Users/Password.h Library/MailSystem.cpp Library/MailSystem.h Users/Author/Author.cpp Users/Admin/Admin.cpp Library/Authentication.cpp Library/Library.cpp Library/ManagingSystem.cpp Library/SearchSystem.cpp Library/SortSystem.cpp Book/Book.cpp Book/MakeRequest.cpp Users/Reader/Reader.cpp Library/RequestSystem.cpp Library/RequestSystem.h)

target_link_libraries(Library_system ${PROJECT_SOURCE_DIR}/sqlite3.dll)
