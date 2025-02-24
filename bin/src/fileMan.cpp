#include "fileman.hxx"

namespace eazy {
    explicit FileManipulator::FileManipulator(std::filesystem::path path) {
        this->path = std::move(path);
        this->stream = std::fstream();
    }

    std::string FileManipulator::read() {
        if (!this->exists()) {
            return "";
        }

        this->stream.open(this->path.string(), std::ios::in);

        std::stringstream content;

        content << this->stream.rdbuf();

        this->stream.close();

        return content.str();
    }

    std::string FileManipulator::readline(size_t line) {
        if (line <= 0) {
            return "";
        }

        this->stream.open(this->path.string(), std::ios::in);

        size_t line_num = 1;
        std::string str_line = "";
        while (std::getline(this->stream, str_line)) {
            if (line_num == line) {
                break;
            }

            line_num++;
        }

        this->stream.close();

        return str_line;
    }

    bool FileManipulator::write(std::string text) {
        this->stream.open(this->path.string(), std::ios::out);
        
        this->stream << text;

        this->stream.close();

        return true;
    }

    bool FileManipulator::append(std::string text) {
        this->stream.open(this->path.string(), std::ios::out | std::ios::app); // `out | app` Enables appending content at the end of file

        this->stream << text;

        this->stream.close();

        return true;
    }

    bool FileManipulator::exists() const noexcept {
        return std::filesystem::exists(this->path);
    }

    bool FileManipulator::exists(std::filesystem::path path) noexcept {
        return std::filesystem::exists(path);
    }

    const std::fstream& FileManipulator::get_stream() const {
        return this->stream;
    }

    const std::filesystem::path& FileManipulator::get_path() const noexcept {
        return this->path;
    }
}