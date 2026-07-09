#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "AppWindow.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("bottom-menu");
        
        auto osIcon = cocos2d::CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png"); 
        auto launcherBtn = CCMenuItemSpriteExtra::create(
            osIcon, this, menu_selector(MyMenuLayer::onOpenGeometryDesktop)
        );

        if (menu) {
            menu->addChild(launcherBtn);
            menu->updateLayout();
        }

        return true;
    }

    void onOpenGeometryDesktop(cocos2d::CCObject* sender) {
        auto testWindow = AppWindow::create("Geometry Apps Terminal", {400, 250});
        testWindow->setPosition({100, 100});
        
        auto scene = cocos2d::CCDirector::sharedDirector()->getRunningScene();
        scene->addChild(testWindow, 100);
    }
};
