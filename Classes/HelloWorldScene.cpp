/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
   return HelloWorld::create();
};

static void problemLoading( const char* filename )
{
   printf( "Error while loading: %s\n", filename );
   printf( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n" );
};

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    initMenu();
    initMouseListener();
    initPlayerObj();

    return true;
};

void HelloWorld::initMenu()
{
   auto visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();

   auto closeItem = MenuItemImage::create( "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1( HelloWorld::menuCloseCallback, this ) );

   const float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
   const float y = origin.y + closeItem->getContentSize().height / 2;
   closeItem->setPosition( Vec2( x, y ) );

   auto menu = Menu::create( closeItem, NULL );
   menu->setPosition( Vec2::ZERO );
   this->addChild( menu, 1 );
}

void HelloWorld::initMouseListener()
{
   auto _mouseListener = EventListenerMouse::create();
   _mouseListener->onMouseDown = CC_CALLBACK_1( HelloWorld::onMousePressed, this );
   
   _eventDispatcher->addEventListenerWithSceneGraphPriority( _mouseListener, this );
}

void HelloWorld::initPlayerObj()
{
   auto visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();

   auto player = spine::SkeletonAnimation::createWithJsonFile( "./assets/hero_2.json", "./assets/hero_2.atlas" );
   player->setName( "player" );
   player->setPosition( { visibleSize.width / 2 + origin.x,
                        visibleSize.height / 2 + origin.y } );
   player->setAnimation( 1, "idle", true );

   this->addChild( player, 0 );
};

void HelloWorld::onMousePressed( Event* event )
{
   EventMouse* mouseEvent = dynamic_cast<EventMouse*>( event );

   const auto key = mouseEvent->getMouseButton();

   switch( key )
   {
      case EventMouse::MouseButton::BUTTON_LEFT:
         context.setState( new TMove() );
         break;
      case  EventMouse::MouseButton::BUTTON_RIGHT:
         context.setState( new TAttack() );
         break;
   }

   context.handleInput( dynamic_cast<SkeletonAnimation*>( this->getChildByName( "player" ) ), mouseEvent );
}

void HelloWorld::menuCloseCallback( Ref* pSender )
{
   //Close the cocos2d-x game scene and quit the application
   Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
   exit( 0 );
#endif

   /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

   //EventCustom customEndEvent("game_scene_close_event");
   //_eventDispatcher->dispatchEvent(&customEndEvent);
};
