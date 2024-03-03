#include <optional>
#include <iostream>
#include <vector>

template<class T>
concept string_like = std::is_convertible_v<T, std::string_view>;

void print(string_like auto s)
{
    std::cout << s;
}

void print(std::integral auto i)
{
    std::cout << i;
}

template<class T>
void print(std::optional<T> opt)
{
    if (not opt.has_value())
        std::cout << "Is a nullopt\n";
    else print(opt.value());
}

template<class T>
void print(std::vector<T> cont) {
    for (auto const & el : cont)
    {
        print(el);
        print(" ");
    }
    print("\n");
}