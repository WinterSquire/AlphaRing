#include "main_context.h"

#include "imgui/game/mcc/CMCCContext.h"
#include "imgui/game/halo3/CHalo3Context.h"

class CMainContext : public ICMainContext {
public:
    CMainContext() {

    }

    void render(int render_flag) override {
        pages[0]->render();

        if (render_flag != None)
            pages[render_flag]->render();

        if (ImGui::BeginMainMenuBar()) {
            ImGui::Text("%.1f fps", ImGui::GetIO().Framerate);
            ImGui::EndMainMenuBar();
        }
    }

    static CMainContext instance;

private:
    ICContext* pages[7] {
        g_pMCCContext,
        nullptr,
        nullptr,
        g_pHalo3Context,
        nullptr,
        nullptr,
        nullptr,
    };
};

CMainContext CMainContext::instance;
ICMainContext* g_pMainContext = &CMainContext::instance;
