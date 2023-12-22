#include <algorithm>
#include <concepts>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

namespace anoban {
    inline namespace v2 {
        template<typename T> requires std::integral<T> || std::floating_point<T>
        static inline T sum(const std::vector<T>& container) noexcept {
            return std::accumulate(container.cbegin(), container.cend(), static_cast<T>(0), std::plus {});
        }
    } // namespace v2
} // namespace anoban

int main(void) {
    srand(time(nullptr));
    std::vector<float>   randoms_f {};
    std::vector<int64_t> randoms_i {};
    randoms_f.resize(20'000);
    randoms_i.resize(20'000);

    std::for_each(randoms_f.begin(), randoms_f.end(), [](float& f) { f = static_cast<float>(::rand()); });
    std::for_each(randoms_i.begin(), randoms_i.end(), [](int64_t& i) { i = static_cast<float>(::rand()); });

    std::wcout << L"Sum of 20,000 random floats is " << anoban::sum<float>(randoms_f) << L"\n";
    std::wcout << L"Sum of 20,000 random integers is " << anoban::sum<int64_t>(randoms_i) << std::endl;

    return EXIT_SUCCESS;
}