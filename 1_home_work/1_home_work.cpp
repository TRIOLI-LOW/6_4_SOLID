
// 1. Использование switch - case   в методе saveTo, который лучше и проще заменить на отдельные классы
// 2.метод открытости и закрытости, все тот же метод saveTo придется менять при добавлении нового интерфейса
// 3. принцип разделения интерфейса, все тот же метод saveTo, который нужно разделить

#include <fstream>

class Formatter
{
public:
    virtual ~Formatter() = default;
    virtual std::string format(const std::string& data) const = 0;
};

class HTMLFormatter : public Formatter
{
public:
    std::string format(const std::string& data) const override
    {
        return "<html>" + data + "</html>";
    }
};

class JSONFormatter : public Formatter
{
public:
    std::string format(const std::string& data) const override
    {
        return "{ \"data\": \"" + data + "\"}";
    }
};

class TextFormatter : public Formatter
{
public:
    std::string format(const std::string& data) const override
    {
        return data;
    }
};


class Data
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON,
    
    };

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    std::string print(const Formatter& formatter) const
    {
        return formatter.format(data_);
    }

private:
    std::string data_;
    Format format_;
};

void saveTo(std::ofstream& file, const Data& data, const Formatter& formatter)
{
    if (file.is_open()) {
        file << data.print(formatter);
    }
}

int main()
{
    std::ofstream file("out.txt");

    Data data("SOLID", Data::Format::kText);
    TextFormatter textFormatter;

    saveTo(file, data, textFormatter);

    HTMLFormatter htmlFormatter;
    saveTo(file, data, htmlFormatter);

    JSONFormatter jsonFormatter;
    saveTo(file, data, jsonFormatter);


    return 0;
}