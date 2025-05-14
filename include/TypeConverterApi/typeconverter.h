#pragma once

#include "sfinae.h"

#include <memory>
#include <sstream>
#include <string>

namespace type_converter_api {
namespace impl {

template<typename T, std::enable_if_t<sfinae::has_right_shift_operator_v<T>, bool> = true>
void fill_from_string(T& value, const std::string& str, int)
{
    std::stringstream stream;
    stream << str;
    stream >> value;
}

template<typename T, std::enable_if_t<sfinae::has_left_shift_operator_v<T>, bool> = true>
std::string convert_to_string(const T& value, int)
{
    std::stringstream stream;
    stream << value;

    return stream.str();
}

template<typename T, std::enable_if_t<std::is_enum<T>::value, bool> = true>
void fill_from_string(T& value, const std::string& str, int)
{
    std::stringstream stream;
    stream << str;
    int temp;
    stream >> temp;
    value = static_cast<T>(temp);
}

template<typename T, std::enable_if_t<std::is_enum<T>::value, bool> = true>
std::string convert_to_string(const T& value, int)
{
    std::stringstream stream;
    stream << static_cast<int>(value);

    return stream.str();
}

template<typename T>
void fill_from_string(T&, const std::string&, ...)
{
    throw std::runtime_error("fill_from_string not implemented");
}

template<typename T>
std::string convert_to_string(const T&, ...)
{
    throw std::runtime_error("convert_to_string not implemented");
}

} // namespace impl

template<typename T>
class type_converter
{
public:
    virtual ~type_converter() = default;

    virtual void fill_from_string(T& value, const std::string& str) const
    {
        impl::fill_from_string<T>(value, str, 0);
    }

    virtual std::string convert_to_string(const T& value) const
    {
        return impl::convert_to_string<T>(value, 0);
    }
};

template<>
class type_converter<bool>
{
public:
    virtual ~type_converter() = default;

    virtual void fill_from_string(bool& value, const std::string& str) const
    {
        std::stringstream stream;
        stream << str;
        stream >> std::boolalpha >> value;
    }

    virtual std::string convert_to_string(const bool& value) const
    {
        return value ? "true" : "false";
    }
};

template<>
class type_converter<std::string>
{
public:
    virtual ~type_converter() = default;

    virtual void fill_from_string(std::string& value, const std::string& str) const
    {
        value = str;
    }

    virtual std::string convert_to_string(const std::string& value) const
    {
        return value;
    }
};

template<typename T>
class type_converter<std::shared_ptr<T>>
{
public:
    virtual ~type_converter() = default;

    virtual void fill_from_string(std::shared_ptr<T>& value, const std::string& str) const
    {
        if(str.empty())
            return;

        if(value == nullptr)
            value = std::make_shared<T>();

        std::stringstream stream;
        stream << str;
        stream >> *value;
    }

    virtual std::string convert_to_string(const std::shared_ptr<T>& value) const
    {
        if(value == nullptr)
            return "";

        std::stringstream stream;
        stream << *value;

        return stream.str();
    }
};

template<typename T>
class type_converter<std::unique_ptr<T>>
{
public:
    virtual ~type_converter() = default;

    virtual void fill_from_string(std::unique_ptr<T>& value, const std::string& str) const
    {
        if(str.empty())
            return;

        if(value == nullptr)
            value = std::make_unique<T>();

        std::stringstream stream;
        stream << str;
        stream >> *value;
    }

    virtual std::string convert_to_string(const std::unique_ptr<T>& value) const
    {
        if(value == nullptr)
            return "";

        std::stringstream stream;
        stream << *value;

        return stream.str();
    }
};

} // namespace type_converter_api