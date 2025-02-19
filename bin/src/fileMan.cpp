

#include <fileMan.hxx>
#include <filesystem>
#include <istream>

namespace eazy {
    std::string& fileManNode::getPath()
    {
       return this->path;
    }

    bool fileManNode::exists(){
        return std::filesystem::exists(this->path);
    }

    int fileManNode::lineNumber(){
        return this->lineCounter;
    }

    bool fileManNode::keepAlive(){
        return this->keepingAlive;
    }

    bool fileManNode::keepAlive(bool aliveStatus){
        this->keepingAlive = aliveStatus;

        if(!this->keepingAlive){
            this->ensureClosure();
        }

        return this->keepingAlive;
    }

    std::pair<bool, std::string> fileManNode::nextLine(){
        // if there's nothing kept alive
        if(!(this->keepingAlive && this->mode == eazy::fileOpenType::read)){
            std::pair<bool, std::string> errorReturn = {
                false, ""
            };

            return errorReturn;
        }

        // try to get a line
        std::string toReturnString;
        
        if(!std::getline(this->stream, toReturnString)){
            std::pair<bool, std::string> finalReturn = {false, toReturnString};
            return finalReturn;
        }
        
        // increase the counter
        this->lineCounter++;

        // return the result
        std::pair<bool, std::string> finalReturn = {true, toReturnString};
        
        return finalReturn;
      
    }

    std::string fileManNode::readWhole(){
        // in case of keeping it alive
        if(this->keepingAlive){
            // create a file stream
            if(this->mode != eazy::fileOpenType::read){
                this->stream = std::fstream(this->path);
                this->mode = eazy::fileOpenType::read;
            }

            // check if the stream is even "good"
            if(!this->stream.good()){
                // if it's not, then return blank string
                std::string blank = "";

                return blank;
            }

            // create a string stream
            std::ostringstream strstrm;
            
            // transfer the file stream to string stream
            strstrm << this->stream.rdbuf();

            // close the file (precisely speaking: close the file stream)
            this->stream.close();

            // change the file stream to a new string
            std::string toReturn = strstrm.str();

            // return that string
            return toReturn;
        }


        // check if that file even exists
        if(!fileManNode::exists()){
            std::string blank = "";

            return blank;
        }

        // create a file stream
        std::fstream strm = std::fstream(this->path, std::ios::in);

        // check if the stream is even "good"
        if(!strm.good()){
            // if it's not, then return blank string
            std::string blank = "";

            return blank;
        }

        // create a string stream
        std::ostringstream strstrm;
        
        // transfer the file stream to string stream
        strstrm << strm.rdbuf();

        // close the file (precisely speaking: close the file stream)
        strm.close();

        // change the file stream to a new string
        std::string toReturn = strstrm.str();

        // return that string
        return toReturn;

    }

    bool fileManNode::append(const std::string& text){
        return fileManNode::append(text, true);
    }

    bool fileManNode::append(const std::string& text, bool includeNewLine){
        // in case of keeping it alive
        if(this->keepingAlive){
            // create a file stream
            if(this->mode != eazy::fileOpenType::append){
                this->stream = std::fstream(this->path, std::ios::app);
                this->mode = eazy::fileOpenType::append;
            }

            
                // check if the stream is even "good"
                if(!this->stream.good()){
                    return false;
                }

                // go the end
                this->stream.seekg(std::ios::end);
                
                // transfer the string to file
                this->stream << text;

                // a new line
                if(includeNewLine){
                    this->stream << std::endl;
                }

                return true;
        }

        // create a file stream
        std::fstream strm = std::fstream(this->path, std::ios::app);

        // check if the stream is even "good"
        if(!strm.good()){
            return false;
        }

        // go the end
        strm.seekg(std::ios::end);
        
        // transfer the string to file
        strm << text;

        // a new line
        if(includeNewLine){
            strm << std::endl;
        }

        // close the file (precisely speaking: close the file stream)
        strm.close();

        return true;

    }

    bool fileManNode::writeBlank(const std::string& text){
        // in case of keeping it alive
        if(this->keepingAlive){
            // create a file stream
            this->stream = std::fstream(this->path);
            this->mode = eazy::fileOpenType::read;

            // check if the stream is even "good"
            if(!this->stream.good()){
                return false;
            }

            // write to that
            this->stream << text;

            return true;
        }


        // create a file stream
        std::fstream strm = std::fstream(this->path, std::ios::out);

        // check if the stream is even "good"
        if(!strm.good()){
            return false;
        }
        
        // transfer the string to file
        strm << text;

        // close the file (precisely speaking: close the file stream)
        strm.close();

        // reset the line counter
        this->lineCounter = 0;

        return true;

    }
    


    void fileManNode::toLine(){
        this->lineCounter = 0;

        if(this->keepingAlive){
            this->stream.seekg(std::ios::beg);
        }
    }


    void fileManNode::toLine(int line){
        this->lineCounter = line;

        if(this->keepingAlive){
            this->stream.seekg(std::ios::beg);

            int counter = 0;

            while(counter != line){
                this->stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                counter++;
            }
        }
    }


    bool fileManNode::clear(){
        // in case of keeping it alive
        if(this->keepingAlive){
            // create a file stream
            this->stream = std::fstream(this->path);
            this->mode = eazy::fileOpenType::read;

            // check if the stream is even "good"
            if(!this->stream.good()){
                return false;
            }

            return true;
        }

        // create a file stream
        std::fstream strm = std::fstream(this->path, std::ios::out);

        // check if the stream is even "good"
        if(!strm.good()){
            return false;
        }

        // close the file (precisely speaking: close the file stream)
        strm.close();

        // reset the line counter
        this->lineCounter = 0;

        return true;

    }

    fileManNode::fileManNode(const std::string& path){
        this->path = path;
        this->keepingAlive = false;
        this->lineCounter = 0;
        this->mode = eazy::fileOpenType::none;
    }

    void fileManNode::ensureClosure(){
        if(this->keepingAlive && this->stream.is_open()){
            this->stream.close();
        }
        this->keepingAlive = false;
    }

    fileManNode::~fileManNode(){
        this->ensureClosure();
    }

}