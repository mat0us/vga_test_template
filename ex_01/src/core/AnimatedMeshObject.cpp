#include "AnimatedMeshObject.h"

AnimatedMeshObject::AnimatedMeshObject(ShaderProgram* shader, VertexBuffer* buffer)
    : MeshObject(shader, buffer)
{}

void AnimatedMeshObject::syncAnimations()
{
    if (m_rotXSrc)
        transform.rotation.setX(m_baseRotX + (float)*m_rotXSrc);

    if (m_rotYSrc)
        transform.rotation.setY(m_baseRotY + (float)*m_rotYSrc);

    if (m_rotZSrc)
        transform.rotation.setZ(m_baseRotZ + (float)*m_rotZSrc);

    if (m_txSrc)
        transform.position.setX(m_baseX + (float)*m_txSrc);

    if (m_tySrc)
        transform.position.setY(m_baseY + (float)*m_tySrc);

    if (m_tzSrc)
        transform.position.setZ(m_baseZ + (float)*m_tzSrc);

    if (m_sxSrc)
        transform.scale.setX(m_baseScaleX + (float)*m_sxSrc);

    if (m_sySrc)
        transform.scale.setY(m_baseScaleY + (float)*m_sySrc);

    if (m_szSrc)
        transform.scale.setZ(m_baseScaleZ + (float)*m_szSrc);

    if (m_suSrc)
        transform.scale = QVector3D(
            m_baseScaleU + (float)*m_suSrc,
            m_baseScaleU + (float)*m_suSrc,
            m_baseScaleU + (float)*m_suSrc);
}
