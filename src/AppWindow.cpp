#include "AppWindow.hpp"

bool AppWindow::init(std::string const& title, cocos2d::CCSize size) {
    m_title = title;
    m_windowSize = size;

    if (!CCLayerColor::initWithColor({30, 30, 35, 240}, size.width, size.height)) return false;
    
    this->setTouchEnabled(true);

    auto titleBar = cocos2d::CCLayerColor::create({45, 45, 50, 255}, size.width, 30);
    titleBar->setPosition({0, size.height - 30});
    this->addChild(titleBar);

    auto titleLabel = cocos2d::CCLabelBMFont::create(title.c_str(), "goldFont.fnt");
    titleLabel->setScale(0.6f);
    titleLabel->setPosition({10, size.height - 15});
    titleLabel->setAnchorPoint({0, 0.5f});
    this->addChild(titleLabel);

    auto closeBtnSprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    closeBtnSprite->setScale(0.5f);
    auto closeBtn = CCMenuItemSpriteExtra::create(
        closeBtnSprite, this, menu_selector(AppWindow::onClose)
    );
    
    auto menu = cocos2d::CCMenu::create(closeBtn, nullptr);
    menu->setPosition({size.width - 20, size.height - 15});
    this->addChild(menu);

    return true;
}

AppWindow* AppWindow::create(std::string const& title, cocos2d::CCSize size) {
    auto ret = new AppWindow();
    if (ret && ret->init(title, size)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void AppWindow::onClose(cocos2d::CCObject* sender) {
    this->removeFromParentAndCleanup(true);
}

bool AppWindow::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    auto touchPoint = this->convertTouchToNodeSpace(touch);
    
    if (touchPoint.y >= m_windowSize.height - 30 && touchPoint.y <= m_windowSize.height &&
        touchPoint.x >= 0 && touchPoint.x <= m_windowSize.width) {
        m_isDragging = true;
        m_dragOffset = this->getPosition() - touch->getLocation();
        return true;
    }
    return false;
}

void AppWindow::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    if (m_isDragging) {
        this->setPosition(touch->getLocation() + m_dragOffset);
    }
}

void AppWindow::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    m_isDragging = false;
}
