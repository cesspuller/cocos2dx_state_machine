#include "TStateMachine.hpp"

int TState::curDirection = 1;

void TIdle::handleInput( SkeletonAnimation* player, Event* mouseEvent )
{
   if (std::string( player->getCurrent( 1 )->animation->name ) == std::string( "idle" ))
   {
      return;
   }

   player->stopAllActions();
   player->setScaleX( curDirection );
   player->setAnimation( 1, "idle", true );
}

void TMove::handleInput( SkeletonAnimation* player, Event* mouseEvent )
{
   player->stopAllActions();

   EventMouse* event = dynamic_cast< EventMouse* >(mouseEvent);

   Vec2 clickPos = event->getLocationInView();
   auto currentPosition = player->getPosition();
   auto dstPosition = event->getLocationInView();
   auto distance = currentPosition.getDistance( dstPosition );
   auto duration = distance / 100;

   auto direction = dstPosition - currentPosition;

   if (direction.x > 0)
   {
      curDirection = -1;
      player->setScaleX( curDirection );
   }
   if (direction.x < 0)
   {
      curDirection = 1;
      player->setScaleX( curDirection );
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

void TAttack::handleInput( SkeletonAnimation* player, Event* mouseEvent )
{
   player->stopAllActions();
   player->setScaleX( curDirection );
   
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

void TStateContext::handleInput( SkeletonAnimation* player, Event* mouseEvent )
{
   currentState->handleInput( player, mouseEvent );
};