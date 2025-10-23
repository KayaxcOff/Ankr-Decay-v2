//
// Created by muham on 19.10.2025.
//

#include "ankr_debug.hpp"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "../../Game/define_character/base/villain_base.hpp"

AnkrDebug::AnkrDebug(SDL_Renderer* renderer) : initialized(false), abilityIndex(0), hero(nullptr), villain(nullptr), renderer(renderer), shouldWarning(false) {}

AnkrDebug::~AnkrDebug() {
    shutdown();
}

void AnkrDebug::init(SDL_Window *window) {
    if (initialized) return;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    initialized = true;
}

void AnkrDebug::setHero(const heroes::Champions *champion) {
    hero = champion;
}

void AnkrDebug::setVillain(const villains::Champions *champion) {
    villain = champion;
}

void AnkrDebug::handleEvent(const SDL_Event &event) const {
    if (!initialized) return;

    ImGui_ImplSDL2_ProcessEvent(&event);
}

void AnkrDebug::newFrame() const {
    if (!initialized) return;

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void AnkrDebug::render() const {
    if (!initialized) return;

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
}


void AnkrDebug::displayGUI() {
    if (!initialized) return;

    this->setInformation();
    //this->setIndex();
}

void AnkrDebug::setInformation() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 work_pos = viewport->WorkPos;
    const auto window_pos = ImVec2(work_pos.x + viewport->WorkSize.x - 10.0f, work_pos.y + 10.0f);

    constexpr auto window_pivot = ImVec2(1.0f, 0.0f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pivot);
    ImGui::SetNextWindowBgAlpha(0.35f);

    constexpr ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar;

    ImGui::Begin("Ankr Debug Panel", nullptr, window_flags);

    if (hero != nullptr && villain != nullptr) {
        ImGui::Text("--- System ---");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::Text("Mouse: (%.0f, %.0f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);

        ImGui::Separator();
        ImGui::Text("--- Hero ---");
        ImGui::Text("Hero Name: %s", hero->getName().c_str());
        ImGui::Text("Hero HP: %d", hero->getHealth());
        ImGui::TextColored(
            hero->isAlive() ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1),
            "Status: %s",
            hero->isAlive() ? "Alive" : "Dead"
        );

        ImGui::Separator();
        ImGui::Text("--- Villain ---");
        ImGui::Text("Enemy Name: %s", villain->getName().c_str());
        ImGui::Text("Enemy HP: %d", villain->getHealth());
        ImGui::TextColored(
            villain->isAlive() ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1),
            "Status: %s",
            villain->isAlive() ? "Alive" : "Dead"
        );

        ImGui::End();
    } else {
        if (!shouldWarning) std::cout << "AnkrDebug: Characters are null!" << std::endl;
        shouldWarning = true;
        ImGui::Text("--- Error ---");
        ImGui::Text("Can't find characters!");

        ImGui::End();
    }
}
/*
void AnkrDebug::setIndex() const {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 work_pos = viewport->WorkPos;
    const auto window_pos = ImVec2(work_pos.x + 10.0f, work_pos.y + 10.0f);
    constexpr auto window_pivot = ImVec2(0.0f, 0.0f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pivot);
    ImGui::SetNextWindowBgAlpha(0.35f);

    constexpr ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar;

    ImGui::Begin("Champions Abilities", nullptr, window_flags);
    ImGui::SliderInt("Ability Index", &abilityIndex, 1, 3);

    if (ImGui::Button("Ability 1")) abilityIndex = 1;
    ImGui::SameLine();
    if (ImGui::Button("Ability 2")) abilityIndex = 2;
    ImGui::SameLine();
    if (ImGui::Button("Ability 3")) abilityIndex = 3;

    ImGui::End();
}

int AnkrDebug::getIndex() const {
    return abilityIndex;
}
*/
void AnkrDebug::shutdown() const {
    if (!initialized) return;

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    initialized = false;
}
