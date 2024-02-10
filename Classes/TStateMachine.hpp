#ifndef _T_STATE_MACHINE_HPP_
#define _T_STATE_MACHINE_HPP_

#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"
#include <string>
#include <memory>

using namespace cocos2d;
using namespace spine;

//! Интерфейс состояний
class TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, EventMouse* mouseEvent ) = 0;

   virtual ~TState() = default;
};

//! Состояние перемещения
class TMove final : public TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, EventMouse* mouseEvent ) override;
};

//! Состояние атаки  
class TAttack final : public TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, EventMouse* mouseEvent ) override;
};

//! Класс управляющий состояниями персонажа
class TStateContext
{
   public:
   
   TStateContext();

   void setState( TState* state );

   void handleInput( SkeletonAnimation* player, EventMouse* mouseEvent );

   private:

   TState* currentState;
};

#endif // !_T_STATE_MACHINE_HPP_


