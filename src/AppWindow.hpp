#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class AppWindow : public cocos2d::CCLayerColor {
protected:
    std::string m_title;
    cocos2d::CCPoint m_dragOffset;
    bool m_isDragging = false;
    cocos2d::CCSize m_windowSize;

    virtual bool init(std::string const& title, cocos2d::CCSize size);
    
    void onClose(cocos2d::CCObject* sender);

    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) override;
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) override;
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) override;

public:
    static AppWindow* create(std::string const& title, cocos2d::CCSize size);
};
