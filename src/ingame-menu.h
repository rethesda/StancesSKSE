#pragma once
#include "API/FUCK_API.h"

namespace STNG
{
    void RegisterFUCKMenu();

    struct StanceTool : ITool
    {
        [[nodiscard]] const char* Name() const override { return "StancesNG"; }
        [[nodiscard]] const char* Group() const override { return nullptr; }
        void OnClose() override;
        void OnOpen() override;
        bool OnAsyncInput(const void*) override;

        void Draw() override
        {
            if (FUCK::BeginTabBar("StancesNG"))
            {
                if (FUCK::CollapsingHeader("StancesNG Options", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    DrawBoolManipulation();
                }

                FUCK::Spacing(2);
                if (FUCK::CollapsingHeader("Hotkeys",  ImGuiTreeNodeFlags_DefaultOpen))
                {
                    DrawHotkeySelector();
                }
                if (FUCK::CollapsingHeader("Idle Lookup", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    DrawIdleSelection();
                }
                FUCK::EndTabBar();
            }
        }

        void DrawHotkeySelector();
        void DrawBoolManipulation();
        void DrawIdleSelection();

    private:
        void RebuildFilteredIdles();
        static FUCK::ManagedHotkey KeyStringToManagedHotkey(std::string_view a_str);
        static std::string ManagedHotkeyToKeyString(const FUCK::ManagedHotkey& a_hotkey);
        static void UnbindHotkey(const char* label, FUCK::ManagedHotkey &a_hotkey);
        void HotkeyOnLoad();
        void HotkeyOnSave();
        bool use_cycling = false;
        bool apply_on_start = false;
        bool play_animation = false;
        FUCK::ManagedHotkey _bearKey;
        FUCK::ManagedHotkey _wolfKey;
        FUCK::ManagedHotkey _hawkKey;
        FUCK::ManagedHotkey _neutralKey;
        std::vector<RE::TESIdleForm*> _filteredIdles;
        std::string _lastFilter;
        char _filterBuffer[256] = {0};
        std::string _currentFilter;
        RE::TESIdleForm* _selectedIdle{nullptr};

    };

    inline StanceTool g_stanceTool;
}