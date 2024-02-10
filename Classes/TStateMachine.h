#ifndef _T_STATE_MACHINE_HPP_
#define _T_STATE_MACHINE_HPP_

#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"

using namespace cocos2d;
using namespace spine;

class TState
{
   public:
   virtual void handleInput( SkeletonAnimation* player, EventMouse* mouseEvent ) = 0;
};

class TIdle : public TState
{
   public:
   virtual void handleInput( SkeletonAnimation* player, EventMouse* mouseEvent ) override final
   {
      player->stopAllActions();

      player->setAnimation( 1, "idle", true );
   }
};

class TMove : public TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, EventMouse* mouseEvent ) override final
   {
      player->stopAllActions();

      Vec2 clickPos = mouseEvent->getLocationInView();
      auto currentPosition = player->getPosition();
      auto dstPosition = mouseEvent->getLocationInView();  
      auto distance = currentPosition.getDistance( dstPosition );
      auto duration = distance / 100;  

      auto direction = dstPosition - currentPosition;

      if (direction.x > 0)
      {
         player->setScaleX( -1 );
      }
      if (direction.x < 0)
      {
         player->setScaleX( 1 );
      }

      auto moveAction = MoveBy::create( duration, dstPosition - currentPosition );
      moveAction->setTag( 0 );

      auto idle = CallFunc::create( [=](){ player->setAnimation( 1, "idle", true ); } );
      auto move = CallFunc::create( [=]() { player->setAnimation( 1, "move", true ); } );
;
      auto sequence = Sequence::create( move, moveAction, idle, nullptr );
      player->runAction( sequence );
   }
};

class TAttack : public TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, EventMouse* mouseEvent ) override final
   {
      player->stopAllActions();

      auto currentPosition = player->getPosition();
      auto dstPosition = mouseEvent->getLocationInView();   // some Vec2
      auto direction = dstPosition - currentPosition;

      if (direction.x > 0)
      {
         player->setScaleX( -1 );
      }
      if (direction.x < 0)
      {
         player->setScaleX( 1 );
      }

      auto attack = CallFunc::create( [=]()
                                      {
                                         player->setAnimation( 1, "attack", false );
                                      } );

      auto idle = CallFunc::create( [=]()
                                    {
                                       player->setAnimation( 1, "idle", true );
                                    } );


      auto sequence = Sequence::create( attack, idle, nullptr );


      player->runAction( sequence );
   }
};

class TStateContext
{
   public:

   TStateContext()
   { 
      currentState = new TIdle();
   }

   void setState( TState* state )
   {
      currentState = state;
   }

   void handleInput( SkeletonAnimation* player, EventMouse* mouseEvent )
   {
      currentState->handleInput( player, mouseEvent );
   }

   private:

   TState* currentState;
};

#endif // !_T_STATE_MACHINE_HPP_


