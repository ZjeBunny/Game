#include <SDL3/SDL.h>
#include <algorithm>

class Slider {
public:
    Slider(float x = 0, float y = 0, float w = 0, float h = 0, int min = 0, int max = 100, int volume = 50)
        : x(x), y(y), w(w), h(h), min(min), max(max), value(volume) {
    }


    void HandleSliderEvent(const SDL_Event& event) {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (isMouseOverHandle(event.button.x, event.button.y)) {
                dragging = true;
            }
        }

        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            dragging = false;
        }

        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            if (dragging) {
                float t = (event.motion.x - x) / w;
                t = std::clamp(t, 0.0f, 1.0f);
                value = min + (int)(t * (max - min));
            }
        }
    }
    void RenderSlider(SDL_Renderer* renderer) {
        if (w <= 0 || h <= 0) return;

        SDL_FRect track{ x, y, w, h };
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &track);

        float t = (max == min) ? 0 : (float)(value - min) / (max - min);
        float handleX = x + (t * w);
        float hW = 20.0f;
        float hH = h + 10.0f;

        SDL_FRect handle{
            handleX - hW / 2.0f,
            y - (hH - h) / 2.0f,
            hW,
            hH
        };

        SDL_SetRenderDrawColor(renderer, dragging ? 1, 0, 66 : 1,0,120 ,255);
        SDL_RenderFillRect(renderer, &handle);
    }

    int getValue() const { return value; }

    void UpdateDimensions(float newX, float newY, float newW, float newH) {
        x = newX; y = newY; w = newW; h = newH;
    }
    bool isMouseOverHandle(float mx, float my) {
        float t = (max == min) ? 0 : (float)(value - min) / (max - min);
        float hW = 20.0f;
        float hH = h + 10.0f;
        float handleX = x + (t * w);

        return (mx >= handleX - hW / 2.0f && mx <= handleX + hW / 2.0f &&
            my >= y - (hH - h) / 2.0f && my <= y + h + (hH - h) / 2.0f);
    }
    bool isDraggng() { return dragging; };
    void setValue(int val) {
        value = val;
    }
private:
    float x, y, w, h;
    int min, max, value;
    bool dragging = false;

};