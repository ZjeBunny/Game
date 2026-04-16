#include "../../Include/ui/GameSettings.hpp"
#include "../../include/Helpers.hpp"

void GSettings::LoadSettingsAssets(SDL_Renderer* renderer, int windowW, int windowH) {
	cursorPointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
	cursorMove = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_EW_RESIZE);
	font = TTF_OpenFont("assets/fonts/ThaleahFat.ttf", 48.0f);
	background = IMG_LoadTexture(renderer, "assets/menu_background.png");
	bg = IMG_LoadTexture(renderer, "assets/item/item_background.png");
	x = IMG_LoadTexture(renderer, "assets/settings/exit.png");

	SDL_Color textColor = { 1, 0, 66, 255 };
	SDL_Surface* settingsSur = TTF_RenderText_Solid(font, title, 0, textColor);
	SDL_Surface* volumeSur = TTF_RenderText_Solid(font, volume, 0, textColor);
	SDL_Surface* musicSur = TTF_RenderText_Solid(font, music, 0, textColor);
	SDL_Surface* fscreenSur = TTF_RenderText_Solid(font, fullscreen, 0, textColor);
	SDL_Surface* fpsSur = TTF_RenderText_Solid(font, showFps, 0, textColor);
	titleTex = SDL_CreateTextureFromSurface(renderer, settingsSur);
	volumeTex = SDL_CreateTextureFromSurface(renderer, volumeSur);
	musicTex = SDL_CreateTextureFromSurface(renderer, musicSur);
	fullscreenTex = SDL_CreateTextureFromSurface(renderer, fscreenSur);
	fpsTex = SDL_CreateTextureFromSurface(renderer, fpsSur);
	SDL_DestroySurface(fpsSur);
	SDL_DestroySurface(fscreenSur);
	SDL_DestroySurface(settingsSur);
	SDL_DestroySurface(volumeSur);
	SDL_DestroySurface(musicSur);

	UpdateLayout(windowW, windowH);
}

void GSettings::RenderSettings(SDL_Renderer* renderer) {
	float mX, mY;
	SDL_GetMouseState(&mX, &mY);
	SDL_FPoint mousePos = { mX, mY };
	HoverEffect(&xRect, xRect_base, mousePos);
	if (background) {
		SDL_SetTextureScaleMode(background, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, background, nullptr, nullptr);
	}
	if (bg) {
		SDL_SetTextureScaleMode(bg, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, bg, nullptr, &bgRect);
	}
	if (x) {
		SDL_SetTextureScaleMode(x, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, x, nullptr, &xRect);
	}
	if (menu) {
		SDL_SetTextureScaleMode(menu, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, menu, nullptr, &menuRect);
	}
	if (titleTex) {
		SDL_SetTextureScaleMode(titleTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, titleTex, nullptr, &titleR);
	}
	if (volumeTex) {
		SDL_SetTextureScaleMode(volumeTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, volumeTex, nullptr, &volumeR);
	}
	if (musicTex) {
		SDL_SetTextureScaleMode(musicTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, musicTex, nullptr, &musicR);
	}
	if (fpsTex) {
		SDL_SetTextureScaleMode(fpsTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, fpsTex, nullptr, &fpsR);
	}
	if (fullscreenTex) {
		SDL_SetTextureScaleMode(fullscreenTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, fullscreenTex, nullptr, &fsR);
	}
	volumeSlider.RenderSlider(renderer);
	musicSlider.RenderSlider(renderer);
	fullCheckbox.Render(renderer);
	fpsCheckbox.Render(renderer);
}

void GSettings::UpdateLayout(int winW, int winH) {
	bgRect = Helper::CalculateRectCenter(bg, 0.8f, 0.8f, winW, winH, 0.1f, false);
	xRect = Helper::CalculateRect(x, 0.1f, 0.1f, winW, winH, 0.15f, 0.8f, true);
	xRect_base = xRect;

	titleR = Helper::CalculateRectCenter(titleTex, 0.5f, 0.2f, winW, winH, 0.12f, false);

	volumeR = Helper::CalculateRect(volumeTex, 0.1f, 0.1f, winW, winH, 0.4f, 0.2f, false);
	musicR = Helper::CalculateRect(musicTex, 0.1f, 0.1f, winW, winH, 0.5f, 0.2f, false);
	fpsR = Helper::CalculateRect(fpsTex, 0.1f, 0.1f, winW, winH, 0.5f, 0.55f, false);
	fsR = Helper::CalculateRect(fullscreenTex, 0.1f, 0.1f, winW, winH, 0.4f, 0.55f, false);

	SDL_FRect vRect = Helper::CalculateRect(nullptr, 0.2f, 0.02f, winW, winH, 0.43f, 0.3f, false);
	volumeSlider.UpdateDimensions(vRect.x, vRect.y, vRect.w, vRect.h);

	SDL_FRect mRect = Helper::CalculateRect(nullptr, 0.2f, 0.02f, winW, winH, 0.53f, 0.3f, false);
	musicSlider.UpdateDimensions(mRect.x, mRect.y, mRect.w, mRect.h);

	fullCheckbox = Checkbox(fsR.x + fsR.w + 20, fsR.y + 20, 60, fullCheckbox.IsChecked());
	fpsCheckbox = Checkbox(fpsR.x + fpsR.w + 20, fpsR.y + 20, 60, fpsCheckbox.IsChecked());

}

void GSettings::HandleSettingsEvents(SDL_Event& event, bool& isRunning, GameState& currentState, SDL_Renderer* renderer) {
	volumeSlider.HandleSliderEvent(event);
	musicSlider.HandleSliderEvent(event);
	fullCheckbox.HandleEvent(event);
	fpsCheckbox.HandleEvent(event);

	if (event.type == SDL_EVENT_QUIT) {
		isRunning = false;
	}
	if (event.type == SDL_EVENT_WINDOW_RESIZED) {
		UpdateLayout(event.window.data1, event.window.data2);
	}
	if (event.type == SDL_EVENT_MOUSE_MOTION) {
		SDL_FPoint mousePos = { event.motion.x, event.motion.y };
		bool hoverAny = SDL_PointInRectFloat(&mousePos, &xRect) ||
			volumeSlider.isMouseOverHandle(event.motion.x, event.motion.y) ||
			musicSlider.isMouseOverHandle(event.motion.x, event.motion.y) ||
			fpsCheckbox.isHovered(&mousePos) || fullCheckbox.isHovered(&mousePos);
		bool draggingSlider = volumeSlider.isDraggng() || musicSlider.isDraggng();
		if (hoverAny) {
			if (draggingSlider) {
				SDL_SetCursor(cursorMove);
			}
			else {
				SDL_SetCursor(cursorPointer);
			}
			
		}else if (draggingSlider) {
			SDL_SetCursor(cursorMove);
		}
		else {
			SDL_SetCursor(SDL_GetDefaultCursor());
		}
		
	}
	if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
		SDL_SetCursor(SDL_GetDefaultCursor());
	}
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		SDL_FPoint mousePos = { event.button.x, event.button.y };
		if (SDL_PointInRectFloat(&mousePos, &xRect)) {
			currentState = GameState::MENU;
		}
	}
}

void GSettings::CleanSettings() {
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(x);
	SDL_DestroyTexture(save);
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(titleTex);
	SDL_DestroyTexture(volumeTex);
	SDL_DestroyTexture(musicTex);
	SDL_DestroyTexture(fpsTex);
	SDL_DestroyTexture(fullscreenTex);
	SDL_DestroyCursor(cursorPointer);
	SDL_DestroyCursor(cursorMove);

	TTF_CloseFont(font);
}

inline void GSettings::HoverEffect(SDL_FRect* currentRect, const SDL_FRect& baseRect, const SDL_FPoint& mousePos) {
	if (SDL_PointInRectFloat(&mousePos, &baseRect)) {
		currentRect->w = baseRect.w * 1.1f;
		currentRect->h = baseRect.h * 1.1f;
		currentRect->x = baseRect.x - (currentRect->w - baseRect.w) / 2.0f;
		currentRect->y = baseRect.y - (currentRect->h - baseRect.h) / 2.0f;
	}
	else {
		*currentRect = baseRect;
	}
}

