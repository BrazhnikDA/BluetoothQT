#include "weathermodel.h"

WeatherModel::WeatherModel()
{

}

const std::string &WeatherModel::getName() const
{
    return name;
}

void WeatherModel::setName(const std::string &newName)
{
    name = newName;
}

const std::string &WeatherModel::getMain() const
{
    return main;
}

void WeatherModel::setMain(const std::string &newMain)
{
    main = newMain;
}

const std::string &WeatherModel::getDescription() const
{
    return description;
}

void WeatherModel::setDescription(const std::string &newDescription)
{
    description = newDescription;
}

const std::string &WeatherModel::getFeelsLike() const
{
    return feelsLike;
}

void WeatherModel::setFeelsLike(const std::string &newFeelsLike)
{
    feelsLike = newFeelsLike;
}

const std::string &WeatherModel::getSpeed() const
{
    return speed;
}

void WeatherModel::setSpeed(const std::string &newSpeed)
{
    speed = newSpeed;
}
