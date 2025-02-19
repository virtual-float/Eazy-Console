#pragma once
#ifndef FILEMAN_HXX_INCLUDED
#define FILEMAN_HXX_INCLUDED

#if __cplusplus >= 201703L // Support for C++17 or latest only

#include <string>
#include <iostream>
#include <fstream>

namespace eazy {

    enum fileOpenType {
        write,
        read,
        append,
        none
    };

    class fileManNode {
        private:
            std::string path;
            bool isFileOpen;
            int lineCounter;
            std::fstream stream;
            bool keepingAlive;
            fileOpenType mode;

        public:
            /**
             * @brief allows you to get a line number that this manager currently uses
             * 
             * @return int 
             */
            int lineNumber();

            /**
             * @brief sets the line pointer to the beginning
             * 
             */
            void toLine();

            /**
             * @brief sets the line pointer to particular line
             * 
             * @param line int that line
             */
            void toLine(int line);

            /**
             * @brief allows you to read the next line
             * 
             * @return std::string the line context
             */
            std::pair<bool, std::string> nextLine();

            /**
             * @brief gives you information about the file stream being kept alive
             * 
             * @return bool information if the stream is keeping alive 
             */
            bool keepAlive();

            /**
             * @brief sets the alive status
             * and gives you information about the file stream being kept alive
             * 
             * @param aliveStatus bool. The new keep alive status
             * 
             * @return bool information if the stream is keeping alive 
             */
            bool keepAlive(bool aliveStatus);

            /**
             * @brief overwrites the file
             * 
             * @param text the text
             * @return true if there was no error
             * @return false if there was an error 
             */
            bool writeBlank(const std::string& text);

            /**
             * @brief allows you to append the text
             * 
             * @param text the text to append
             * @param includeNewLine if the line file should be included
             * @return true if there was no error
             * @return false if there was an error  
             */
            bool append(const std::string& text, bool includeNewLine);

            /**
             * @brief allows you to append the text
             * 
             * @param text the text to append
             * @return true if there was no error
             * @return false if there was an error  
             */            
            bool append(const std::string& text);

            /**
             * @brief clears the whole file
             * 
             * @return true if there was no error
             * @return false if there was an error  
             */
            bool clear();

            /**
             * @brief reads the whole file and returns the contents
             * 
             * @return std::string with no characters if there was an error
             * @return std::string the contents of the file
             */
            std::string readWhole();

            /**
             * @brief checks if the file in that path do exist
             * 
             * @return true if exists
             * @return false if does not
             */
            bool exists();

            /**
             * @brief Allows to get the path back
             * 
             * @return std::string& 
             */
            std::string& getPath();

        // /**
        //  * @brief allows you to get the full name of the file
        //  * 
        //  * @param withExtension bool. If a name should be provided with a file extension (like .cpp or .txt)
        //  * @return std::string&
        //  */
        // std::string& getFileName(bool withExtension);

        

        /**
         * @brief ensures that every file and stream is closed
         * 
         */
        void ensureClosure();

        /**
         * @brief create a file link
         * 
         * @param PathToFile const std::string& the path to the file
         */
        fileManNode(const std::string& PathToFile);

        ~fileManNode();
    };
}

#endif
#endif