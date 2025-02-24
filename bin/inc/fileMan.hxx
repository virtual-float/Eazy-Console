/**
 * @file fileman.hxx
 * @brief few useful tools to manage files
 * @author Naticzka
 * 
 * @date February 19th, 2025
 */
#pragma once
#ifndef FILEMAN_HXX_INCLUDED
#define FILEMAN_HXX_INCLUDED

#if __cplusplus >= 201703L // Support for C++17 or latest only

#include <string>
#include <istream>
#include <filesystem>
#include <fstream>

namespace eazy {

    // FileManipulator non-inheritable class
    class FileManipulator final {
        public:
            /**
             * @brief FileManipulator's class constructor
             * 
             * @param std::filesystem::path Path to the file
             */
            explicit FileManipulator(std::filesystem::path path);
            ~FileManipulator() {}

            /**
             * @brief Returns the content of file
             * @return Content
             */
            std::string read();
            /**
             * @brief Returns the specific content of file (Content line)
             * 
             * @param size_t Content's line
             */
            std::string readline(size_t line);
            /**
             * @brief Overrides the entire file
             * 
             * @param std::string Text
             * 
             * @return Status
             */
            bool write(std::string text);
            /**
             * @brief Appends a text to the file's content
             * 
             * @param std::string Text
             * 
             * @return Status
             */
            bool append(std::string text);
            /**
             * @brief Checks if the file exists
             * 
             * @return Status
             */
            bool exists() const noexcept;

            /**
             * @brief Checks if the file exists
             * 
             * @param std::filesystem::path Path to the file
             * 
             * @return Status
             */
            static bool exists(std::filesystem::path path) noexcept;

            /**
             * @brief Returns the file stream
             * 
             * @return std::fstream reference
             */
            const std::fstream& get_stream() const;
            /**
             * @brief Returns the file's path
             * 
             * @return std::filesystem::path reference
             */
            const std::filesystem::path& get_path() const noexcept;
        private:
            // File's stream
            std::fstream stream;
            // File's path
            std::filesystem::path path;
    };
}

#endif // C++17 or latest
#endif // FILEMAN_HXX_INCLUDED