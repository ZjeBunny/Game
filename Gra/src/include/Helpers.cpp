#pragma once 
#include <SDL3_image/SDL_image.h>

inline SDL_FRect CalculateRectCenter(SDL_Texture* tex, float widthPercent, float heightPercent, int windowW, int windowH, float yPosPercentage, bool useAspectRatio) {
	float displayW = (float)windowW * widthPercent;
	float displayH;

	if (useAspectRatio && tex) {
		float tw, th;
		SDL_GetTextureSize(tex, &tw, &th);
		float aspect = th / tw;
		displayH = displayW * aspect;
	}
	else {
		displayH = (float)windowH * heightPercent;
	}

	float displayX = (windowW - displayW) / 2.0f;
	float displayY = (float)windowH * yPosPercentage;

	return { displayX, displayY, displayW, displayH };
}
inline SDL_FRect CalculateRect(SDL_Texture* tex, float widthPercent, float heightPercent, int windowW, int windowH, float yPosPercentage, float xPosPercentage, bool useAspectRatio) {
	float displayW = (float)windowW * widthPercent;
	float displayH;

	if (useAspectRatio && tex) {
		float tw, th;
		SDL_GetTextureSize(tex, &tw, &th);
		float aspect = th / tw;
		displayH = displayW * aspect;
	}
	else {
		displayH = (float)windowH * heightPercent;
	}

	float displayX = (float)windowW * xPosPercentage;
	float displayY = (float)windowH * yPosPercentage;

	return { displayX, displayY, displayW, displayH };
}
#include <filesystem>

inline bool SaveExists(const std::string& path) {
	std::filesystem::path SavePath = path;
	if (std::filesystem::exists(path)) return true;
	return false;
}

