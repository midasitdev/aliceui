<!-- 문서 시작 -->
# Alice UI Documentation

<!-- Introduction -->
# Introduction
## 보는 방법
1. Visual Studio Code 미리 보기 기능 사용 (추천)
 * https://code.visualstudio.com/
2. Visual Studio Addin - Web Essentials 설치
 * http://vswebessentials.com/

<!-- 유의 사항 -->
# 유의 사항
## Widget 크기에 대해
Widget은 크기를 직접 정할 수 없다. 
## `SizePolicy` 기능
Widget은 기본 크기를 지정할 수 있다. 하지만 Layout 등에 의해 그 크기가 변경될 여지가 있다. <br>
이 때, 변화할 크기에 대한 옵션이 `SizePolicy`이다. <br>
### `SizePolicy::Content`
Widget 내부에서 정의한 최적 크기를 기본으로 하도록 지정
### `SizePolicy::Fixed`
어떠한 상황에서도 크기가 Default Size와 일치하도록 지정
### `SizePolicy::Parent`
자신의 부모 Widget의 크기를 따르도록 지정
## Padding / Margin 에 대하여
Padding과 Margin은 내부의 Child Widget의 위치를 결정하기 위한 요소로 주로 Layout에서 사용됨
### Padding
Padding은 자기 자신을 기준으로 내부에 얼마나 Offset을 줄지에 대한 값이다. Layout에서 Child Widget의 경우 항상 Padding만큼 간격을 두고 위치하게 된다.
### Margin
Margin은 자기 자신을 기준으로 외부(부모)에게 얼마나 Offset을 줄지에 대한 값이다. Layout에서 Parent Widget이 Child Widget의 위치를 결정할 때, Margin만큼 간격을 추가하여 Child Widget의 위치를 결정하게 된다.

<!-- Signal / Slot -->
# Signal & Slot
Qt framework에서의 Signal/Slot 컨셉을 일반 C++11 컴파일러로 사용할 수 있게 만든 기능.
## nGen Signal의 문제점
Signal에 함수가 연결될 때, 해당 연결 대한 ID값을 발급하도록 되어있음. 이 연결에 대한 자원 관리는 Signal을 사용하는 개발자가 직접 수동으로 처리 해야 올바르게 동작함(수신 받는 객체가 사라진 경우 명시적으로 ID에 대해 Disconnect를 호출해야 함)
## 개선된 Signal
Signal에 함수를 연결할 경우 그 연결 관계에 대한 Slot을 발급함. 발급된 Slot 객체가 사라지거나 Disconnect를 호출하기 전까지 해당 연결 관계를 유지하도록 되어있음.
## SlotPool
SlotPool은 Signal에 연결할 때 발급되는 Slot을 일괄적으로 관리하는 객체. 연결 관계에 대한 묶음 처리 담당. 
## Signal / Slot / SlotPool 활용 방법
하나의 연결 관계만 사용하는 경우 Signal에서 `Bind` 함수로 부터 발급 받는 Slot을 저장하고 있으면 연결 관계가 유지됨.
```C++
MSlot my_slot = Signal.Bind( my_func );
```
여러개의 연결 관계를 사용하는 경우 class 자체를 SlotPool을 상속받아서 `Connect` 멤버 함수로 Signal을 연결하여 사용 가능.
```C++
class MyClass : public MSlotPool
{
public:
    void SomeFunction( MSignal& signal )
    {
        Connect( signal, this, &MyClass::OtherFunction );
    }
}
```
서로 다른 연결 관계 묶음으로 사용하는 경우 (멤버)변수로 SlotPool을 정의하고 해당 SlotPool에 `Connect` 함수로 연결하여 사용.
```C++
class MyClass
{
private:
    MSlotPool m_MySlotPool;
public:
    void SomeFunction( MSignal& signal )
    {
        m_MySlotPool.Connect( signal, this, &MyClass::OtherFunction );
    }
}
```
연결 해제는 Slot 또는 SlotPool에서 `Disconnect` 함수로 해제 가능
```C++
MSlot slot;
// Some connection ...
slot.Disconnect();
MSlotPool slotpool;
// Some connection ...
slotpool.DisconnectAll();
```
<!-- Widget -->
# Widget
UI를 구성하는 기본 단위

<!-- Adapter -->
# Adapter 설명
## 역할
Combo / List 형태의 UI를 자동 생성하기 위한 Visitor Pattern 형태의 클래스 <br>
일반적으로 `MAUIBaseAdapter` 를 상속 받아 구현 <br>
## 인터페이스 함수
* `GetWidget` : Adapter 내의 데이터를 Widget으로 생성할 때, 일반적으로 호출되는 함수
* `GetComboItemWidget` : Combo에서 Widget으로 생성할 때, 호출되는 함수 

<!-- Form Window Handle -->
# Form / Window / Handle
## Form
OS Dependent 한 기능에 대한 Query Interface 비슷한 역할
