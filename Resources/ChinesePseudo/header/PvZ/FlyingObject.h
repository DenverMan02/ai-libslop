/*
 * FlyingObject.h
 *
 *  Created on: 2019-9-26
 *      Author: zhousen
 */

#ifndef FLYINGOBJECT_H_
#define FLYINGOBJECT_H_

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GameSubSystem.h"
#include "PlantUtils.h"

class FlyingObject : public BoardEntity
{
public:
    RT_CLASS_DEFINE(FlyingObject, BoardEntity, RtClass);

    FlyingObject();
    virtual ~FlyingObject();

    void onUpdate() override;
    void SetPosition(const SexyVector3& i_newPosition) override;

    virtual void InitParam(Plant* parent, const std::string& effectPam, RenderLayer layer = RENDER_LAYER_PROJECTILE);
    virtual void PlayAnimation(const std::string& anim, bool loop = false);

protected:
    virtual SexyVector3 GetAdjustEffectPosition();
    virtual SexyVector3 GetAttachPosition();

    Sexy::Point _currentGridPoint;
    float   _speed;
    RtWeakPtr<Effect_PopAnim> _effect;
    RtWeakPtr<Plant> _parent;
};

#endif /* FLYINGOBJECT_H_ */
