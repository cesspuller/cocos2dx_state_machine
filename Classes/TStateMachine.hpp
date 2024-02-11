#ifndef _T_STATE_MACHINE_HPP_
#define _T_STATE_MACHINE_HPP_

#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"
#include <string>
#include <memory>

using namespace cocos2d;
using namespace spine;

//! ��������� ���������
class TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, Event* mouseEvent ) = 0;

   virtual ~TState() = default;

   static int curDirection;
};

//! ��������� ����
class TIdle final : public TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, Event* mouseEvent ) override;
};

//! ��������� �����������
class TMove final : public TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, Event* mouseEvent ) override;
};

//! ��������� �����  
class TAttack final : public TState
{
   public:

   virtual void handleInput( SkeletonAnimation* player, Event* mouseEvent ) override;
};

//! ����� ����������� ����������� ���������
class TStateContext
{
   public:
   
   TStateContext();

   //! ������� ��������� ����������� ��������� ���������
   void setState( TState* state );

   //! ������� ��������� ������ 
   void handleInput( SkeletonAnimation* player, Event* mouseEvent );

   private:

   TState* currentState;               // ��������� �� ������� ����� ���������
};

#endif // !_T_STATE_MACHINE_HPP_


