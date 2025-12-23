#pragma once
#include "Events/Events.h"

class LayerStack;

class Layer
{
friend LayerStack;
public:
  virtual void OnEvent(Event& event) = 0;
  virtual void OnAttach() = 0;
  virtual void OnDetach() = 0;
protected:
  template<typename T>
  void TranslateQueue();
};