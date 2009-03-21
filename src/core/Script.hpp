#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <string>

class Script{
public:
    Script();
    ~Script();

    /// Charge un script en m�moire
    /// @param[in] str Script � charger
    void Load(const std::string & str);
};

#endif

