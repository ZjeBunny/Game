#include <SDL3/SDL.h>

class Checkbox {
public:
    Checkbox(float x = 0, float y = 0, float size = 30, bool checked = false)
        : rect({ x, y, size, size }), isChecked(checked) {
    }

    void HandleEvent(const SDL_Event& event) {
        
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            SDL_FPoint mousePos = { event.button.x, event.button.y };
            if (SDL_PointInRectFloat(&mousePos, &rect)) {
                isChecked = !isChecked; 
            }
        }
    }

    void Render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        for (float i = 0; i < 4.0f; i += 1.0f) {
            SDL_FRect frame = { rect.x + i, rect.y + i, rect.w - (i * 2.0f), rect.h - (i * 2.0f) };
            SDL_RenderRect(renderer, &frame);
        }

        if (isChecked) {
            SDL_SetRenderDrawColor(renderer, 1, 0, 66, 255);

            float x1 = rect.x + rect.w * 0.2f;
            float y1 = rect.y + rect.h * 0.5f;
            float x2 = rect.x + rect.w * 0.45f;
            float y2 = rect.y + rect.h * 0.75f; 
            float x3 = rect.x + rect.w * 0.8f;
            float y3 = rect.y + rect.h * 0.25f;
            for (float i = -2.5f; i <= 2.5f; i += 0.5f) {
                SDL_RenderLine(renderer, x1 + i, y1, x2 + i, y2);
                SDL_RenderLine(renderer, x1, y1 + i, x2, y2 + i);

                SDL_RenderLine(renderer, x2 + i, y2, x3 + i, y3);
                SDL_RenderLine(renderer, x2, y2 + i, x3, y3 + i);
            }
        }
    }

    bool IsChecked() const { return isChecked; }
    void SetPosition(float x, float y) { rect.x = x; rect.y = y; }
    bool isHovered(const SDL_FPoint* mousepos) {
        if (SDL_PointInRectFloat(mousepos, &rect)) { return true; }
        return false;
    }
    void setChecked(bool check) {
        isChecked = check;
    }
private:
    SDL_FRect rect;
    bool isChecked;
};