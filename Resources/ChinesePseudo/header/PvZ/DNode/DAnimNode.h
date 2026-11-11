//
//  DAnimNode.h
//  DCore
//
//  Created by lzjseed on 16/2/4.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DAnimNode_h
#define DAnimNode_h

#include "DNode.h"
#include "PopAnimRig.h"

class DAnimNode:public DTransformNode
{
protected:
    DAnimNode(){}
public:
    virtual ~DAnimNode();
    virtual DAnimNode& setResource(const std::string& name)override;
    virtual inline PopAnimRig* getPopAnimRig()const {return m_pPopAnim;}
    
    virtual void draw(const DMatrix& mat,Graphics* i_g)override;
    
    virtual DAnimNode& setResource(PopAnimRig* animRig,bool needDelete = false);
    
    virtual DAnimNode& playAndStop(const std::string& actionName,const std::function<void(const std::string&)>& stopFunc = nullptr);
    virtual DAnimNode& playAndContinus(const std::string& actionName,const std::function<void(const std::string&,const std::string&,int)>& continusFunc = nullptr);
    
    
    virtual DAnimNode& onStop(const std::function<void(const std::string&)>& stopFunc = nullptr);
    virtual DAnimNode& onContinus(const std::function<void(const std::string&,const std::string&,int)>& continusFunc = nullptr);
    
    virtual bool isRunning();
    
    virtual void cleanup() override;
    
private:
    void onAnimStop(const std::string& name);
    void onAnimContinus(const std::string& name,const std::string& newAnimLabel,int activeAnimSeqEndCount);
protected:
    std::function<void(const std::string&)> m_animStopFunc = nullptr;
    std::function<void(const std::string&,const std::string&,int)> m_animContinusFunc = nullptr;
    PopAnimRig* m_pPopAnim = nullptr;
    bool        m_pNeedDelete = false;
    friend class DRefPtr<DAnimNode>;
};

#endif
