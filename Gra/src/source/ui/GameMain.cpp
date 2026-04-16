#include "../../include/ui/GameMain.hpp"
#include <format>
bool isMouseOver = false;



void Main::LoadMainAssets(SDL_Renderer* renderer, int windowW, int windowH)
{
    SDL_Log("here6");

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
    cursorPointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
    font = TTF_OpenFont("assets/fonts/ThaleahFat.ttf", 18);
    Background = IMG_LoadTexture(renderer, "assets/main_clicker/main_bg.png");
    coinPicker = IMG_LoadTexture(renderer, "assets/main_clicker/pavement.png");
    money_bg = IMG_LoadTexture(renderer, "assets/ui_backgrounds/money_bg.png");
    shop_icon = IMG_LoadTexture(renderer, "assets/shop/shop.png");
    pauze = IMG_LoadTexture(renderer, "assets/settings/puaze.png");
    shop_bg = IMG_LoadTexture(renderer, "assets/shop/shop_background.png");
    exit = IMG_LoadTexture(renderer, "assets/settings/exit.png");
    tex1ct = IMG_LoadTexture(renderer, "assets/coins/1cent.png");
    
    SDL_Surface* opt1sur = TTF_RenderText_Solid(font, shopOption1, 0, { 1, 0, 66, 255 });
    SDL_Surface* opt2sur = TTF_RenderText_Solid(font, shopOption2, 0, { 1, 0, 66, 255 });
    SDL_Surface* opt3sur = TTF_RenderText_Solid(font, shopOption3, 0, { 1, 0, 66, 255 });

    opt1Tex = SDL_CreateTextureFromSurface(renderer, opt1sur);
    opt2Tex = SDL_CreateTextureFromSurface(renderer, opt2sur);
    opt3Tex = SDL_CreateTextureFromSurface(renderer, opt3sur);

    SDL_DestroySurface(opt1sur);
    SDL_DestroySurface(opt2sur);
    SDL_DestroySurface(opt3sur);

    cm = new CoinManager();

    UpdateLayout(windowW, windowH);
    shopBaseRect = shop_iconRect;
    pauseBaseRect = pauzeRect;
    
}

void Main::RenderMain(SDL_Renderer* renderer)
{
    float mX, mY;
    SDL_GetMouseState(&mX, &mY);
    SDL_FPoint mousePos = { mX, mY };
    if (!shopActive) {
        HoverEffect(&shop_iconRect, shopBaseRect, mousePos);
        HoverEffect(&pauzeRect, pauseBaseRect, mousePos);

    }
    if (Background) {
        SDL_SetTextureScaleMode(Background, SDL_SCALEMODE_PIXELART);
        SDL_RenderTexture(renderer, Background, nullptr, nullptr);
    }
    if (coinPicker) {
        SDL_SetTextureScaleMode(coinPicker, SDL_SCALEMODE_PIXELART);
        SDL_RenderTexture(renderer, coinPicker, nullptr, &coinPickerRect);

    }
    if (shop_icon) {
        SDL_SetTextureScaleMode(shop_icon, SDL_SCALEMODE_PIXELART);
        SDL_RenderTexture(renderer, shop_icon, nullptr, &shop_iconRect);
    }
    if (pauze) {
        SDL_SetTextureScaleMode(pauze, SDL_SCALEMODE_PIXELART);
        SDL_RenderTexture(renderer, pauze, nullptr, &pauzeRect);
    }
    if (cm) cm->RenderCoins(renderer, tex1ct);

    if (money_bg) {
        SDL_SetTextureScaleMode(money_bg, SDL_SCALEMODE_PIXELART);
        SDL_RenderTexture(renderer, money_bg, nullptr, &money_bgRect);
    }

    if (moneyTexture) {
        SDL_SetTextureScaleMode(moneyTexture, SDL_SCALEMODE_PIXELART);

        SDL_RenderTexture(renderer, moneyTexture, nullptr, &moneyTextRect);
    }


    float target = shopActive ? 1.0f : 0.0f;
    shopAnimationProgress += (target - shopAnimationProgress) * 0.1f;

    if (shopAnimationProgress > 0.001f) {
        int winW, winH;
        SDL_GetRenderOutputSize(renderer, &winW, &winH);

        SDL_FRect currentPos = shop_bgRect;
        float startY = (float)winH;
        float targetY = shop_bgRect.y;
        currentPos.y = startY + (targetY - startY) * shopAnimationProgress;

        if (shop_bg) {
            SDL_SetTextureScaleMode(shop_bg, SDL_SCALEMODE_PIXELART);
            SDL_RenderTexture(renderer, shop_bg, nullptr, &currentPos);
        }

        if (exit) {
            exitRect.x = currentPos.x + currentPos.w - exitRect.w - 10.0f;
            exitRect.y = currentPos.y + 10.0f;
            SDL_RenderTexture(renderer, exit, nullptr, &exitRect);
        }

        float marginX = currentPos.w * 0.2f;
        float optStartY = currentPos.h * 0.14f;
        float gap = currentPos.w * 0.25f;

        if (opt1Tex) {
            opt1Rec.x = currentPos.x + marginX;
            opt1Rec.y = currentPos.y + optStartY;
            if (activeOpt1) SDL_SetRenderDrawColor(renderer, 1, 0, 66, 255);
            else           SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            for (float i = 0; i < 4.0f; i++) {
                SDL_FRect frame = { (opt1Rec.x + i) - 20, opt1Rec.y + i, (opt1Rec.w - (i * 2.0f)) + 40, opt1Rec.h - (i * 2.0f) };
                SDL_RenderRect(renderer, &frame);
            }
            SDL_SetTextureScaleMode(opt1Tex, SDL_SCALEMODE_PIXELART);
            SDL_RenderTexture(renderer, opt1Tex, nullptr, &opt1Rec);
        }

        if (opt2Tex) {
            opt2Rec.x = currentPos.x + marginX + gap - 40;
            opt2Rec.y = currentPos.y + optStartY;
            if (activeOpt2) SDL_SetRenderDrawColor(renderer, 1, 0, 66, 255);
            else           SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            for (float i = 0; i < 4.0f; i++) {
                SDL_FRect frame = { (opt2Rec.x + i) - 20, opt2Rec.y + i, (opt2Rec.w - (i * 2.0f)) + 40, opt2Rec.h - (i * 2.0f) };
                SDL_RenderRect(renderer, &frame);
            }
            SDL_SetTextureScaleMode(opt2Tex, SDL_SCALEMODE_PIXELART);
            SDL_RenderTexture(renderer, opt2Tex, nullptr, &opt2Rec);
        }

        if (opt3Tex) {
            opt3Rec.x = currentPos.x + marginX + (gap * 2.0f) - 40;
            opt3Rec.y = currentPos.y + optStartY;
            if (activeOpt3) SDL_SetRenderDrawColor(renderer, 1, 0, 66, 255);
            else           SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            for (float i = 0; i < 4.0f; i++) {
                SDL_FRect frame = { (opt3Rec.x + i) - 20, opt3Rec.y + i, (opt3Rec.w - (i * 2.0f)) + 40, opt3Rec.h - (i * 2.0f) };
                SDL_RenderRect(renderer, &frame);
            }
            SDL_SetTextureScaleMode(opt3Tex, SDL_SCALEMODE_PIXELART);
            SDL_RenderTexture(renderer, opt3Tex, nullptr, &opt3Rec);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
}

void Main::UpdateLayout(int winW, int winH)
{

    if (cm) {
        cm->UpdatePosition(winW, winH);
        cm->SpawnCoin(winW, winH, tex1ct);
    }
    coinPickerRect = Helper::CalculateRectCenter(coinPicker, 0.65f, 0.65f, winW, winH, 0.2f, false);
    money_bgRect = Helper::CalculateRect(money_bg, 0.2f, 0.15f, winW, winH, 0.01f, 0.75f, false);
    moneyTextRect = Helper::CalculateRectMoney(moneyTexture, 0.06f, winW, winH, 0.105f, 0.93f, 0.77f, true);
    shop_iconRect = Helper::CalculateRect(shop_icon, 0.2f, 0.2f, winW, winH, 0.7999f, 0.8f, false);
    pauzeRect = Helper::CalculateRect(pauze, 0.08f, 0.1f, winW, winH, 0.01f, 0.01f, false);
    shop_bgRect = Helper::CalculateRect(shop_bg, 0.9f, 1.0f, winW, winH, 0.0f, 0.05f, false);

    exitRect.w = shop_bgRect.w * 0.05f;
    exitRect.h = exitRect.w;
    
    opt1Rec = Helper::CalculateRect(opt1Tex, 0.12f, 0.08f, winW, winH, 0.0f, 0.0f, false);
    opt2Rec = Helper::CalculateRect(opt2Tex, 0.12f, 0.08f, winW, winH, 0.0f, 0.0f, false);
    opt3Rec = Helper::CalculateRect(opt3Tex, 0.12f, 0.08f, winW, winH, 0.0f, 0.0f, false);
}

void Main::Update(SDL_Renderer* renderer)
{
    if (!renderer || !font) return;

    money = cm ? cm->getTotalMoney() : 0.0;
    std::string newMoneyText = std::format("${:.2f}", money);

    if (newMoneyText != moneyText || !moneyTexture) {
        moneyText = newMoneyText;

        SDL_Color color = { 1, 0, 66, 255 };
        SDL_Surface* moneySurface = TTF_RenderText_Solid(font, moneyText.c_str(), 0, color);

        if (moneySurface) {
            if (moneyTexture) {
                SDL_DestroyTexture(moneyTexture);
            }
            moneyTexture = SDL_CreateTextureFromSurface(renderer, moneySurface);
            SDL_DestroySurface(moneySurface);
        }

        int w, h;
        if (SDL_GetRenderOutputSize(renderer, &w, &h) == 0) {
            UpdateLayout(w, h);
        }
    }
}

void Main::HandleMainEvents(SDL_Event& event, bool& isRunning, GameState& currentState, SDL_Renderer* renderer)
{

    if (event.type == SDL_EVENT_WINDOW_RESIZED) {
        UpdateLayout(event.window.data1, event.window.data2);

    }
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        SDL_FPoint mousePos = { event.motion.x, event.motion.y };
        bool overSomething = (cm && cm->isOverMoney(mousePos.x, mousePos.y)) ||
            SDL_PointInRectFloat(&mousePos, &shop_iconRect) ||
            SDL_PointInRectFloat(&mousePos, &pauzeRect);
        bool overShop = SDL_PointInRectFloat(&mousePos, &exitRect) || SDL_PointInRectFloat(&mousePos, &opt1Rec)
            || SDL_PointInRectFloat(&mousePos, &opt2Rec) || SDL_PointInRectFloat(&mousePos, &opt3Rec);
        if (overSomething != isMouseOver && !shopActive) {
            isMouseOver = overSomething;
            SDL_SetCursor(isMouseOver ? cursorPointer : SDL_GetDefaultCursor());
        }
        if (overShop != isMouseOver && shopActive) {
            isMouseOver = overShop;
            SDL_SetCursor(isMouseOver ? cursorPointer : SDL_GetDefaultCursor());
        }
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_FPoint mousePos = { mouseX, mouseY };
        if (SDL_PointInRectFloat(&mousePos, &shop_iconRect)) {
            shopActive = !shopActive; 
            SDL_SetCursor(SDL_GetDefaultCursor());
        }
        if (!shopActive && cm) {
            cm->HandleCoinClick(mousePos.x, mousePos.y);
            Update(renderer);
            SDL_SetCursor(SDL_GetDefaultCursor());
        }
        if (shopActive && SDL_PointInRectFloat(&mousePos, &exitRect)){
            shopActive = !shopActive;
            SDL_SetCursor(SDL_GetDefaultCursor());
        }
        if (shopActive && SDL_PointInRectFloat(&mousePos, &opt1Rec)) {
            activeOpt1 = true;
            activeOpt2 = false;
            activeOpt3 = false;
        }
        if (shopActive && SDL_PointInRectFloat(&mousePos, &opt2Rec)) {
            activeOpt1 = false;
            activeOpt2 = true;
            activeOpt3 = false;
        }
        if (shopActive && SDL_PointInRectFloat(&mousePos, &opt3Rec)) {
            activeOpt1 = false;
            activeOpt2 = false;
            activeOpt3 = true;
        }
    }

}

void Main::CleanMenu()
{
    if (moneyTexture) { SDL_DestroyTexture(moneyTexture); moneyTexture = nullptr; }
    if (money_bg) { SDL_DestroyTexture(money_bg); money_bg = nullptr; }
    if (tex1ct) { SDL_DestroyTexture(tex1ct); tex1ct = nullptr; }
    if (opt1Tex) { SDL_DestroyTexture(opt1Tex); opt1Tex = nullptr; }
    if (opt2Tex) { SDL_DestroyTexture(opt2Tex); opt2Tex = nullptr; }
    if (opt3Tex) { SDL_DestroyTexture(opt3Tex); opt3Tex = nullptr; }

    if (font) { TTF_CloseFont(font); font = nullptr; }
    if (cm) { delete cm; cm = nullptr; }
    if (cursorPointer) { SDL_DestroyCursor(cursorPointer); cursorPointer = nullptr; }

}

inline void Main::HoverEffect(SDL_FRect* currentRect, const SDL_FRect& baseRect, const SDL_FPoint& mousePos) {
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