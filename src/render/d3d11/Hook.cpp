#include "D3d11.h"

#include "common.h"

#include <d3d11.h>
#include "global/Global.h"

#include "../imgui/ImGui.h"

namespace AlphaRing::Render::D3d11 {
    void *GetFunction(int index);

    DefDetourFunction(HRESULT, __stdcall, DrawIndexed, ID3D11DeviceContext* p_context,
                      const UINT IndexCount, const UINT StartIndexLocation, const INT  BaseVertexLocation) {
        ID3D11RasterizerState* r_state;
        D3D11_RASTERIZER_DESC r_desc;

        if (AlphaRing::Global::Global()->wireframe) {
            p_context->RSGetState(&r_state);
            if (r_state != nullptr) {
                r_state->GetDesc(&r_desc);
                r_desc.FillMode = D3D11_FILL_WIREFRAME;
                graphics.pDevice->CreateRasterizerState(&r_desc, &r_state);
                p_context->RSSetState(r_state);
            }
#ifdef NEW_WIREFRAME
            D3D11_PRIMITIVE_TOPOLOGY topology;
            p_context->IAGetPrimitiveTopology(&topology);

            p_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
            ppOriginal_DrawIndexed(p_context, IndexCount, StartIndexLocation, BaseVertexLocation);

            p_context->IASetPrimitiveTopology(topology);
#endif
        }

        return ppOriginal_DrawIndexed(p_context, IndexCount, StartIndexLocation, BaseVertexLocation);
    }

    bool CreateHook() {
        return Hook::Detour({
            {GetFunction(73), DrawIndexed, (void **) &ppOriginal_DrawIndexed},
        });
    }
}