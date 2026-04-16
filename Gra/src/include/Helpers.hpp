#pragma once
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>
#include <string>
#include <filesystem>

class Helper {
public:
    static inline SDL_FRect CalculateRectCenter(SDL_Texture* tex, float widthPercent, float heightPercent, int windowW, int windowH, float yPosPercentage, bool useAspectRatio) {
        float displayW = (float)windowW * widthPercent;
        float displayH;
        if (useAspectRatio && tex) {
            float tw, th;
            SDL_GetTextureSize(tex, &tw, &th);
            displayH = displayW * (th / tw);
        }
        else {
            displayH = (float)windowH * heightPercent;
        }
        return { (windowW - displayW) / 2.0f, (float)windowH * yPosPercentage, displayW, displayH };
    }

    static inline SDL_FRect CalculateRect(SDL_Texture* tex, float widthPercent, float heightPercent, int windowW, int windowH, float yPosPercentage, float xPosPercentage, bool useAspectRatio) {
        float displayH = (float)windowH * heightPercent;
        float displayW = (float)windowW * widthPercent;
        if (useAspectRatio && tex) {
            float tw, th;
            SDL_GetTextureSize(tex, &tw, &th);
            displayW = displayH * (tw / th);
        }
        return { (float)windowW * xPosPercentage, (float)windowH * yPosPercentage, displayW, displayH };
    }

    static inline bool SaveExists(const std::string& path) {
        return !path.empty() && std::filesystem::exists(path);
    }

    static inline SDL_FRect CalculateRectMoney(SDL_Texture* tex, float heightPercent, int windowW, int windowH, float yPosPercentage, float xPosAnchor, float minXPercent, bool useAspectRatio) {
        float displayH = (float)windowH * heightPercent;
        float displayW = 0;
        if (useAspectRatio && tex) {
            float tw, th;
            SDL_GetTextureSize(tex, &tw, &th);
            displayW = displayH * (tw / th);
        }
        float anchorX = (float)windowW * xPosAnchor;
        float minX = (float)windowW * minXPercent;
        float displayX = anchorX - displayW;
        if (displayX < minX) {
            displayX = minX;
            displayW = anchorX - minX;
        }
        return { displayX, (float)windowH * yPosPercentage, displayW, displayH };
    }
};
