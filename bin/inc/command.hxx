/**
 * @file command.hxx
 * @brief Header file of command.hxx
 * @author Krystian Turek
 * 
 * @date February 17th, 2025
 */
#pragma once
#ifndef COMMAND_HXX_INCLUDED
#define COMMAND_HXX_INCLUDED

#if __cplusplus >= 201703L // Support for C++17 or latest only

#include <functional>
#include <forward_list>
#include <string>

namespace eazy
{
    // Alias. To reduce typing
    using CommandArgs = std::forward_list<std::string>;

    // Enum for the Command's handle result
    enum CommandResult {
        NO_RESULT = -1, // No result, empty, etc.
        TRUE,
        FALSE
    }; 

    // Command non-inheritable class
    class Command final {
        public:

            /**
             * @brief Command's class constructor
             * 
             * @param std::string Name for the command 
             * @param std::function& Handle (function) for the command
             * @param eazy::CommandArgs& Arguments for the handle to pass in (Empty arguments by default)
             */
            Command(std::string name, 
                CommandResult(*handle)(const eazy::CommandArgs&), 
                const eazy::CommandArgs& arguments = {});
            /**
             * @brief Returns the name set for the command
             * 
             * @return std::string reference
             */
            const std::string& get_name() const noexcept;

            /**
             * @brief Returns the arguments for the command's handle
             * 
             * @return eazy::CommandArgs& reference
             */
            const eazy::CommandArgs& get_args() const noexcept;

            /**
             * @brief Returns the result of the handle (if invoked)
             * 
             * @return eazy::CommandResult reference
             */
            const eazy::CommandResult& get_result() const noexcept;

            /**
             * @brief Returns the handle
             * 
             * @return std::function reference
             */
            const std::function<eazy::CommandResult(const eazy::CommandArgs&)>& get_handle() const noexcept;
            
            /**
             * @brief () Operator overloading
             */
            void operator()();

        private:
            // Command's name
            std::string name;
            // Command's handle
            std::function<eazy::CommandResult(const eazy::CommandArgs&)> handle;

            // Command's arguments
            eazy::CommandArgs arguments;
            // Command's result
            eazy::CommandResult result;
    };
}

#endif // C++17 or latest
#endif // COMMAND_HXX_INCLUDED