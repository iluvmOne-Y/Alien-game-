
#include <raylib.h>
#include <memory>
#include <vector>
#include <raymath.h>

class EffectImplementor // interface
{
public:
    virtual ~EffectImplementor() = default;
    virtual Color Apply(const Color &baseColor, const Vector2 &position, Texture2D texture) = 0;
    virtual bool IsComplete() const = 0;
};

class Effect // Abstraction
{
protected:
    std::shared_ptr<EffectImplementor> impl;

public:
    Effect(std::shared_ptr<EffectImplementor> implementation)
        : impl(implementation) {}
    virtual ~Effect() = default;

    virtual Color ApplyEffect(const Color &baseColor, Vector2 position, Texture2D texture)
    {
        return impl->Apply(baseColor, position, texture);
    }
    virtual bool IsComplete() const
    {
        return impl->IsComplete();
    }
};
// Concrete Implementor
class RainbowBehavior : public EffectImplementor
{
public:
    Color Apply(const Color &baseColor, const Vector2 &position, Texture2D texture) override
    {
        // Calculate hue based on time and x position for wave effect
        float time = GetTime();
        float hue = fmod((time * 50.0f) + position.x, 360.0f);
        return HSVtoRGB(hue, 1.0f, 1.0f);
    }
    bool IsComplete() const override
    {
        return false;
    }

private:
    Color HSVtoRGB(float hue, float saturation, float value)
    {
        float c = value * saturation;
        float x = c * (1 - fabs(fmod(hue / 60.0f, 2) - 1));
        float m = value - c;
        float r, g, b;

        if (hue >= 0 && hue < 60)
        {
            r = c;
            g = x;
            b = 0;
        }
        else if (hue >= 60 && hue < 120)
        {
            r = x;
            g = c;
            b = 0;
        }
        else if (hue >= 120 && hue < 180)
        {
            r = 0;
            g = c;
            b = x;
        }
        else if (hue >= 180 && hue < 240)
        {
            r = 0;
            g = x;
            b = c;
        }
        else if (hue >= 240 && hue < 300)
        {
            r = x;
            g = 0;
            b = c;
        }
        else
        {
            r = c;
            g = 0;
            b = x;
        }

        return Color{
            static_cast<unsigned char>((r + m) * 255),
            static_cast<unsigned char>((g + m) * 255),
            static_cast<unsigned char>((b + m) * 255),
            255};
    }
};
// Refined Abstractions
class RainbowEffect : public Effect
{
    RainbowEffect(std::shared_ptr<EffectImplementor> impl) : Effect(std::make_shared<RainbowBehavior>()) {}
};
class NullImplementor : public EffectImplementor
{
public:
    Color Apply(const Color &baseColor, const Vector2 &position, Texture2D texture) override
    {
        return WHITE;
    }
    bool IsComplete() const override
    {
        return true;
    }
};

class ExplodeImplementor : public EffectImplementor
{
private:
    float startTime;
    bool initialized;
    const float duration = 5.0f; // Duration in seconds

    // Particle data
    struct Particle
    {
        Vector2 position;
        Vector2 velocity;
        Color color;
        float lifeTime; // How long the particle lasts
    };
    std::vector<Particle> particles;

public:
    ExplodeImplementor() : startTime(GetTime()), initialized(true)
    {
        // Initialize particles
        const int NUM_PARTICLES = 200;
        particles.reserve(NUM_PARTICLES);
        for (int i = 0; i < NUM_PARTICLES; ++i)
        {
            float angle = GetRandomValue(0, 360) * (PI / 180.0f);
            float speed = GetRandomValue(50, 100);
            Particle p;
            p.position = {0.0f, 0.0f};
            p.velocity = {cosf(angle) * speed, sinf(angle) * speed};
            p.color = {255, 0, 0, 255}; // Red color
            p.lifeTime = duration;
            particles.push_back(p);
        }
    }

    Color Apply(const Color &baseColor, const Vector2 &position, Texture2D texture) override
    {

        printf("ExplodeEffect applying at time: %f\n", GetTime());
        float elapsed = GetTime() - startTime;

        if (elapsed >= duration)
        {
            // The effect is complete
            printf("ExplodeEffect complete.\n");
            return baseColor;
        }

        // Update and draw particles
        for (auto it = particles.begin(); it != particles.end();)
        {
            // Update particle position
            it->position.x += it->velocity.x * GetFrameTime();
            it->position.y += it->velocity.y * GetFrameTime();
            it->lifeTime -= GetFrameTime();
            if (it->lifeTime <= 0)
            {
                it = particles.erase(it);
                continue;
            }

            printf("Particle position: (%.2f, %.2f)\n", it->position.x, it->position.y);
            // Draw particle
            DrawCircleV(Vector2Add(position, it->position), 10.0f, it->color);
            ++it;
        }

        // Optionally draw the boss texture fading out
        float alpha = 1.0f - (elapsed / duration);
        DrawTextureV(texture, position, ColorAlpha(WHITE, alpha));

        return baseColor;
    }

    bool IsComplete() const override
    {
        return (GetTime() - startTime) >= duration;
    }
};
class ExplodeEffect : public Effect
{
public:
    ExplodeEffect() : Effect(std::make_shared<ExplodeImplementor>()) {}
};