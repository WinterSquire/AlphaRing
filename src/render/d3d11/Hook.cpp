#include "D3d11.h"

#include "common.h"

#include "global/Global.h"

namespace AlphaRing::Render::D3d11 {
    DefDetourFunction(HRESULT, __stdcall, DrawIndexed, ID3D11DeviceContext* p_context,
                      const UINT IndexCount, const UINT StartIndexLocation, const INT  BaseVertexLocation) {
        if (AlphaRing::Global::Global()->wireframe) {
            Graphics()->SetWireframe();
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