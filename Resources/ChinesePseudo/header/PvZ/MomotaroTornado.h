/*
 * MomotaroTornado.h
 *
 *  Created on: 2021-3-25
 *      Author: admin
 */

#ifndef MOMOTAROTORNADO_H_
#define MOMOTAROTORNADO_H_

#include "SkatingGuacodile.h"

class MomotaroTornado : public SkatingGuacodile
{
public:
    RT_CLASS_DEFINE(MomotaroTornado, SkatingGuacodile, RtClass);

    MomotaroTornado();
    virtual ~MomotaroTornado();

protected:
    std::string GetPam() override;
    std::string	GetUpPamLabel() override;
    std::string	GetDownPamLabel() override;
    SexyVector2 GetDrawOffet() override;
};

class MomotaroLargeTornado : public MomotaroTornado
{
public:
    RT_CLASS_DEFINE(MomotaroLargeTornado, MomotaroTornado, RtClass);

    MomotaroLargeTornado();
    virtual ~MomotaroLargeTornado();

    Rect GetAttackRect() override;

protected:
    std::string GetPam() override;
};

#endif /* MOMOTAROTORNADO_H_ */
