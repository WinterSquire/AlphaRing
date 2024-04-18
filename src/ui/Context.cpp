#include "Context.h"

#include <set>
#include <cstdio>

#include "imgui.h"

namespace UI {void ContextEntry();}


const int MAX_PAGE = 32;
static Page* pages[MAX_PAGE];
static unsigned int page_count;
static unsigned int selected_page;
static int ComparePage(const void* lhs, const void* rhs) {return ((Page*)lhs)->weight < ((Page*)rhs)->weight;}

Page::Page(int weight, const char *name, callback_t callback)
        : weight(weight), name(name), callback(callback) {
    pages[page_count++] = this;
    qsort(pages, page_count, sizeof(Page*), ComparePage);
}

void setStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

}

void left_pane_context() {
    if (page_count == 0) return;

    float height = ImGui::GetWindowHeight() / page_count;

    for (int i = 0; i < page_count; ++i) {
        if (ImGui::Selectable(pages[i]->name, i == selected_page, 0, {0, height}))
            selected_page = i;
    }
}

void right_pane_context() {
    if (pages[selected_page] == nullptr || pages[selected_page]->callback == nullptr) return;
    pages[selected_page]->callback();
}

void UI::ContextEntry() {
    ImGui::Begin("Alpha Ring");

    setStyle();

    // Left
    {
        ImGui::BeginChild("left pane", {150, 0}, ImGuiChildFlags_Border);
        left_pane_context();
        ImGui::EndChild();
    }

    ImGui::SameLine();

    // Right
    {
        ImGui::BeginChild("right pane");
        right_pane_context();
        ImGui::EndChild();
    }

    ImGui::End();
}
