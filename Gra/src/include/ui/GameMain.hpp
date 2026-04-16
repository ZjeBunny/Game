#pragma once
#include "CoinManager.hpp"
#include "../Game.hpp"
#include "../Helpers.hpp"
#include <string>

class Main {
public:
    
    void LoadMainAssets(SDL_Renderer* renderer, int windowW, int windowH);
    void RenderMain(SDL_Renderer* renderer);
    void UpdateLayout(int winW, int winH);
    void HandleMainEvents(SDL_Event& event, bool& isRunning, GameState& currentState, SDL_Renderer* renderer);
    void CleanMenu();
    void Update(SDL_Renderer* renderer);
    inline void HoverEffect(SDL_FRect* currentRect, const SDL_FRect& baseRect, const SDL_FPoint& mousePos);
private:
    bool shopActive = false;
    float shopAnimationProgress = 0.0f;
    bool isMouseOver = false;

    SDL_FRect shop_bgRect{}, exitRect{}, coinPickerRect{}, shop_iconRect{}, money_bgRect{}, pauzeRect{}, moneyTextRect{};
    SDL_FRect opt1Rec{}, opt2Rec{}, opt3Rec{};
    SDL_FRect shopBaseRect, pauseBaseRect;
    SDL_Texture* Background = nullptr;
    SDL_Texture* coinPicker = nullptr;
    SDL_Texture* shop_icon = nullptr;
    SDL_Texture* shop_bg = nullptr;
    SDL_Texture* money_bg = nullptr;
    SDL_Texture* pauze = nullptr;
    SDL_Texture* exit = nullptr;
    SDL_Texture* tex1ct = nullptr;
    SDL_Texture* moneyTexture = nullptr;
    SDL_Texture* opt1Tex = nullptr;
    SDL_Texture* opt2Tex = nullptr;
    SDL_Texture* opt3Tex = nullptr;

    SDL_Cursor* cursorPointer = nullptr;
    CoinManager* cm = nullptr;
    TTF_Font* font = nullptr;

    const char* shopOption1 = "Coins";
    const char* shopOption2 = "Charms";
    const char* shopOption3 = "Worker";
    bool activeOpt1 = true;
    bool activeOpt2 = false;
    bool activeOpt3 = false;

    double money = 0.0;
    std::string moneyText;
    SDL_FRect Frame1, Frame2, Frame3;
};
