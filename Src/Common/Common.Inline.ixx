// Hazno - 2026

export module Common:Inline;
import std;

export template<typename T>
constexpr T&& atlas_forward(std::remove_reference_t<T>& param) noexcept
{
    return static_cast<T&&>(param);
}
