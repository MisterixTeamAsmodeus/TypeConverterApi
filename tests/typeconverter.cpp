#include <gtest/gtest.h>
#include <TypeConverterApi/typeconverterapi.h>

// Test for converting a string to an integer
TEST(TypeConverterTest, StringToInt)
{
    type_converter_api::type_converter<int> converter;
    int value = 0;
    converter.fill_from_string(value, "123");
    EXPECT_EQ(value, 123);
}

// Test for converting a string to a boolean
TEST(TypeConverterTest, StringToBool)
{
    const type_converter_api::type_converter<bool> converter;
    bool value = false;
    converter.fill_from_string(value, "true");
    EXPECT_TRUE(value);
}

// Test for converting an integer to a string
TEST(TypeConverterTest, IntToString)
{
    const type_converter_api::type_converter<int> converter;
    const std::string str = converter.convert_to_string(456);
    EXPECT_EQ(str, "456");
}

// Test for converting a boolean to a string
TEST(TypeConverterTest, BoolToString)
{
    type_converter_api::type_converter<bool> converter;
    std::string str = converter.convert_to_string(true);
    EXPECT_EQ(str, "true");
}

// Test for handling empty string input
TEST(TypeConverterTest, EmptyStringInput)
{
    type_converter_api::type_converter<int> converter;
    int value = 0;
    converter.fill_from_string(value, "");
    EXPECT_EQ(value, 0); // Assuming default value is 0 for empty string
}

// Test for converting a string to an enum
enum class Color
{
    RED,
    GREEN,
    BLUE
};

TEST(TypeConverterTest, StringToEnum)
{
    const type_converter_api::type_converter<Color> converter;
    Color color;
    converter.fill_from_string(color, "1");
    EXPECT_EQ(color, Color::GREEN);
}

// Test for converting an enum to a string
TEST(TypeConverterTest, EnumToString)
{
    const type_converter_api::type_converter<Color> converter;
    const std::string str = converter.convert_to_string(Color::BLUE);
    EXPECT_EQ(str, "2");
}
