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

   virtual void handleInput( SkeletonAnimation* player, Event* mouseEvent ) = 0;

   virtual ~TState() = default;

   static int curDirection;
};

//! Состояние айдл
class TIdle final : public TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, Event* mouseEvent ) override;
};

//! Состояние перемещения
class TMove final : public TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, Event* mouseEvent ) override;
};

//! Состояние атаки  
class TAttack final : public TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, Event* mouseEvent ) override;
};

//! Класс управляющий состояниями персонажа
class TStateContext
{
   public:
   
   TStateContext();

   //! Функция установки актуального состояния персонажа
   void setState( TState* state );

   //! Функция обработки инпута 
   void handleInput( SkeletonAnimation* player, Event* mouseEvent );

   private:

   TState* currentState;               // Указатель на базовый класс состояний
};

#endif // !_T_STATE_MACHINE_HPP_


