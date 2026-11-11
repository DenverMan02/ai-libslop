//
//  DStringNode.h
//  DCore
//
//  Created by lzjseed on 16/2/22.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DStringNode_h
#define DStringNode_h

#include "DNode.h"
#include "DString.h"

class DStringNode:public DTransformNode
{
protected:
    DStringNode();
public:
    virtual ~DStringNode();
    
    virtual void draw(const DMatrix& mat,Graphics* i_g)override;
    
    virtual DStringNode& setStringWithFile(const char* string);
    virtual DStringNode& setString(const char* string);
    virtual DStringNode& setPrimeTypeface(PrimeTypeface* primeTypeFace);
    virtual DStringNode& setPrimeTypeface(class PrimeText_PotentialTypeface* primeTypeFace);
    virtual DStringNode& setHorizAlignment(EA::Text::HAlignment align);
    virtual DStringNode& setVertAlignment(EA::Text::VAlignment align);
    virtual DStringNode& setContextRect(float x,float y,float width,float height) override;
    virtual std::string  getString()const {return m_string;}
    virtual std::string  getFontName();
    virtual DVec2 getStringPostion();
    virtual DVec2 getStringPostion(const char* string);
    virtual float getFontSize();
    
protected:
    
    void    updateString();
    void    clean();
protected:
    DString m_string;
    EA::Text::HAlignment  m_horizAlignment;
    EA::Text::VAlignment  m_vertAlignment;
    PrimeTypeface*        m_primeTypeFace;
    bool                  m_bStringUpdateDirty;
    class PrimeGlyphMesh* m_pPrimeGlyphMesh;
    
    friend class DRefPtr<DStringNode>;
};

#endif
