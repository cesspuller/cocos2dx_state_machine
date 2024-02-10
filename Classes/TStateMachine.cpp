#include "TStateMachine.hpp"

void TMove::handleInput( SkeletonAnimation* player, EventMouse* mouseEvent )
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

   auto idle = CallFunc::create( [=]() { player->setAnimation( 1, "idle", true ); } );
   auto move = CallFunc::create( [=]() { player->setAnimation( 1, "move", true ); } );

   if (std::string( player->getCurrent( 1 )->animation->name ) == std::string( "move" ))
   {
      auto actionSequence = Sequence::create( moveAction, idle, nullptr );
      player->runAction( actionSequence );

      return;
   }

   auto actionSequence = Sequence::create( move, moveAction, idle, nullptr );
   player->runAction( actionSequence );
};

void TAttack::handleInput( SkeletonAnimation* player, EventMouse* mouseEvent )
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

   auto attack = CallFunc::create( [=]() { player->setAnimation( 1, "attack", false ); } );
   auto idle = CallFunc::create( [=]() { player->setAnimation( 1, "idle", true ); } );

   if (std::string( player->getCurrent( 1 )->animation->name ) == std::string( "attack" ))
   {
      auto delayOff = DelayTime::create( 0.66 - 0.2 );
      auto delayNew = DelayTime::create( 0.66 );
      
      auto actionSequence = Sequence::create( delayOff, attack, delayNew, idle, nullptr );
      player->runAction( actionSequence );
   
      return;
   }

   //auto onAnimationComplete = [=]( spTrackEntry* entry )
   //   {
   //      //if ( entry->animationEnd - entry->animationLast == 0)
   //      //{
   //         player->setAnimation( 0, "attack", false );
   //      //}
   //   };
   
   //player->setCompleteListener( onAnimationComplete );
   
   //spTrackEntry* te = player->setAnimation( 0, "attack", false );  // BUG
   //auto delay = te->animationEnd;

   auto delay1 = DelayTime::create( 0.66 );

   auto actionSequence = Sequence::create( attack, delay1, idle, nullptr );
   //auto actionSequence = Sequence::create( attack, delay1, idle, nullptr );
   player->runAction( actionSequence );
};

TStateContext::TStateContext()
{
   currentState = new TMove();
};

void TStateContext::setState( TState* state )
{
   currentState = state;
};

void TStateContext::handleInput( SkeletonAnimation* player, EventMouse* mouseEvent )
{
   currentState->handleInput( player, mouseEvent );
};