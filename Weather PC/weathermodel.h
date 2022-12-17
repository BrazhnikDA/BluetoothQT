#ifndef WEATHERMODEL_H
#define WEATHERMODEL_H

#include <string>



class WeatherModel
{
public:
    WeatherModel();
    const std::string &getName() const;
    void setName(const std::string &newName);

    const std::string &getMain() const;
    void setMain(const std::string &newMain);

    const std::string &getDescription() const;
    void setDescription(const std::string &newDescription);

    const std::string &getFeelsLike() const;
    void setFeelsLike(const std::string &newFeelsLike);

    const std::string &getSpeed() const;
    void setSpeed(const std::string &newSpeed);

private:
    std::string name;
    std::string main;
    std::string description;
    std::string feelsLike;
    std::string speed;
};

#endif // WEATHERMODEL_H
