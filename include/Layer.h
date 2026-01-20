#pragma once
#include "Events/Events.h"
#include "DrawData.h"

class Layer
{
public:
  virtual void OnEvent(Event& event) = 0;
  virtual void OnAttach() = 0;
  virtual void OnDetach() = 0;
  virtual void Draw(const DrawData&) = 0;

  virtual ~Layer() = default;
protected:
  template<typename T>
  void TranslateQueue();
};