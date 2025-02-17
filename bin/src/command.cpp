#include "command.hxx"

namespace eazy
{
    Command::Command(std::string name, 
        CommandResult(*handle)(const CommandArgs&), 
        const CommandArgs& arguments) {

        this->name = std::move(name);
        this->handle = std::move(handle);
        this->arguments = std::move(arguments);
        this->result = CommandResult::NO_RESULT;
    }

    const std::string& Command::get_name() const noexcept {
        return this->name;
    }

    const CommandArgs& Command::get_args() const noexcept {
        return this->arguments;
    }

    const CommandResult& Command::get_result() const noexcept {
        return this->result;
    }

    const std::function<CommandResult(const CommandArgs&)>& Command::get_handle() const noexcept {
        return this->handle;
    }

    void Command::operator()() {
        CommandResult result = this->handle(this->arguments);

        this->result = result;
    }
}