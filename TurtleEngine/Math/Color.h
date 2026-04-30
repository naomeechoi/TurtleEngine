#pragma once
class Color {
public:
    union {
        struct {
            float red, green, blue, alpha;
        };
        float rgba[4];
    };

    Color() : red(0.0f), green(0.0f), blue(0.0f), alpha(1.0f) {}

    Color(float r, float g, float b, float a = 1.0f)
        : red(r), green(g), blue(b), alpha(a) {
    }

    // Variadic template constructor (Accepts only float-compatible types)
    // Allows flexible initialization like Color(1.0f, 0.5f)
    template <typename... Args>
        requires (sizeof...(Args) > 0 && (std::is_convertible_v<Args, float> && ...))
    Color(Args... args) : red(0.0f), green(0.0f), blue(0.0f), alpha(1.0f) {
        float values[] = { static_cast<float>(args)... };
        int count = (sizeof...(Args) > 4) ? 4 : (int)sizeof...(Args);

        for (int i = 0; i < count; i++) {
            rgba[i] = values[i]; // gba가 아니라 멤버 변수 이름인 rgba 확인!
        }
    }

    Color(const Color& other) noexcept {
        for (int i = 0; i < 4; ++i) rgba[i] = other.rgba[i];
    }

    static const Color White;
    static const Color Black;
    static const Color Gray;
    static const Color Magenta;
    static const Color Yellow;
    static const Color Red;
    static const Color Blue;
    static const Color Green;

    Color& operator=(const Color& other);

    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
    Color operator*(const Color& other) const;
    Color operator*(float inScale) const;
    Color& operator*=(float inScale);
    Color& operator/=(float inScale);
    Color& operator+=(const Color& other);
    Color& operator-=(const Color& other);

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;

    operator float* ();

    std::string ToString();
    std::wstring ToWideString();
};