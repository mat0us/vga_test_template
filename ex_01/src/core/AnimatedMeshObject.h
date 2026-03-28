#ifndef ANIMATEDMESHOBJECT_H
#define ANIMATEDMESHOBJECT_H

#include "MeshObject.h"

// MeshObject s podporou animace přes pointer binding.
//
// Použití v init():
//   auto* obj = new AnimatedMeshObject(shader, buffer);
//   obj->transform.position = {1, 0, 0};
//   obj->bindRotationY(&m_obj0Animation);      // rotation Y from QML
//   obj->bindRotationX(&m_obj0RotX);           // rotation X from QML
//   obj->bindRotationZ(&m_obj0RotZ);           // rotation Z from QML
//   obj->bindTranslationX(&m_objMoveX, 1.0f);  // movement X, base = 1.0
//   obj->bindTranslationY(&m_objMoveY, 0.0f);  // movement Y, base = 0.0
//   obj->bindScaleUniform(&m_objScale, 1.0f);  // uniform scale multiplier
//
// V paint() stačí: obj->syncAnimations() — žádné if/else podle indexu.

class AnimatedMeshObject : public MeshObject
{
public:
    AnimatedMeshObject(ShaderProgram* shader, VertexBuffer* buffer);

    // ── Animation Bindings (Important Extension Point) ─────────────────────
    // Bind renderer-side channels to this object's transform components.
    // Navazuje animační kanál na proměnnou rendereru.
    // baseX: výchozí X pozice ke které se přičítá offset z QML.
    void bindRotationX(const qreal* src, float baseX = 0.0f) { m_rotXSrc = src; m_baseRotX = baseX; }
    void bindRotationY(const qreal* src, float baseY = 0.0f) { m_rotYSrc = src; m_baseRotY = baseY; }
    void bindRotationZ(const qreal* src, float baseZ = 0.0f) { m_rotZSrc = src; m_baseRotZ = baseZ; }

    void bindTranslationX(const qreal* src, float baseX = 0.0f) { m_txSrc = src; m_baseX = baseX; }
    void bindTranslationY(const qreal* src, float baseY = 0.0f) { m_tySrc = src; m_baseY = baseY; }
    void bindTranslationZ(const qreal* src, float baseZ = 0.0f) { m_tzSrc = src; m_baseZ = baseZ; }

    void bindScaleX(const qreal* src, float baseX = 1.0f) { m_sxSrc = src; m_baseScaleX = baseX; }
    void bindScaleY(const qreal* src, float baseY = 1.0f) { m_sySrc = src; m_baseScaleY = baseY; }
    void bindScaleZ(const qreal* src, float baseZ = 1.0f) { m_szSrc = src; m_baseScaleZ = baseZ; }

    void bindScaleUniform(const qreal* src, float base = 1.0f)   { m_suSrc = src; m_baseScaleU = base; }

    // Přepíše transform podle aktuálních hodnot bindnutých proměnných.
    // Volá se automaticky v paint() před draw().
    void syncAnimations() override;

private:
    const qreal* m_rotXSrc = nullptr;
    const qreal* m_rotYSrc = nullptr;
    const qreal* m_rotZSrc = nullptr;
    const qreal* m_txSrc = nullptr;
    const qreal* m_tySrc = nullptr;
    const qreal* m_tzSrc = nullptr;
    const qreal* m_sxSrc = nullptr;
    const qreal* m_sySrc = nullptr;
    const qreal* m_szSrc = nullptr;
    const qreal* m_suSrc = nullptr;

    float m_baseRotX = 0.0f;
    float m_baseRotY = 0.0f;
    float m_baseRotZ = 0.0f;
    float m_baseX = 0.0f;
    float m_baseY = 0.0f;
    float m_baseZ = 0.0f;
    float m_baseScaleX = 1.0f;
    float m_baseScaleY = 1.0f;
    float m_baseScaleZ = 1.0f;
    float m_baseScaleU = 1.0f;
};

#endif // ANIMATEDMESHOBJECT_H
