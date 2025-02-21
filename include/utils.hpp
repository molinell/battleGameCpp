#include <stdlib.h>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>
#include <stdexcept>
#include <string>

/**
 * @brief Determines which `clear` command to used based on OS
 */
#if defined(_WIN32)
    #define CLEAR "cls"
#elif defined(__APPLE__) && defined(__MACH__)
    #define CLEAR "clear"
#elif defined(__linux__)
    #define CLEAR "clear"
#else
    #define CLEAR NULL
#endif

namespace Utils {

    /**
     * @brief Enum for terminal text colors
     */
    enum Colors {
        RED,
        BLUE,
        GREEN,
        BLACK,
        WHITE,
        CYAN,
        MAGENTA,
        RESET
    };

/**
 * @brief Map for terminal text colors
 * Maps the \p Colors to their ANSI equivalent
 */
static const std::unordered_map<Colors, std::string> colors = {
    {RED, "\033[31m"},
    {BLUE, "\033[34m"},
    {GREEN, "\033[32m"},
    {BLACK, "\033[30m"},
    {WHITE, "\033[37m"},
    {CYAN, "\033[36m"},
    {MAGENTA, "\033[35m"},
    {RESET, "\033[0m"}
};

/**
 * @brief Serialises an object and writes it to a text file
 * Relies on the object being serialisable (like having a \p serialize() function)
 * 
 * @tparam T 
 * @param path the path for the file which to write
 * @param obj a pointer to the object to serialise
 */
template <typename T>
void saveObject(const std::string& path, T* obj) {
  
  try
  {
    std::ofstream f(path);
    if (!f.is_open()) {
        throw std::ios_base::failure("Failed to save game");
    }

    boost::archive::text_oarchive oa(f);
    oa << *obj;
  }
  catch(const std::exception& e)
  {
    throw std::runtime_error(std::string("Serialization failed"));
  }
  
}

/**
 * @brief Deserialises an object
 * 
 * @tparam T 
 * @param path the path to the textfile to deserialise
 * @return T the object
 */
template <typename T>
T loadObject(const std::string& path) {

    try
    {
        std::ifstream f(path);
        if (!f.is_open()) {
            throw std::ios_base::failure("Failed to load game");
        }
        T obj;
        boost::archive::text_iarchive ia(f);
        ia >> obj;

        return obj;
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error(std::string("Deserialization failed"));
    }
    //return NULL;
}

/**
 * @brief Set the Up object
 * Clears the terminal window
 */
void setUp() {
     system(CLEAR);
}

}  // namespace Utils
