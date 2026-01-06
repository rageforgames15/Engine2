#pragma once
#include "Layer.h"
#include <vector>
#include <memory>

template<typename T> 
concept inheartedFromLayer = std::is_base_of_v<Layer,T>;

class LayerStack
{
private:
  using layerStackVectorDef = std::vector<std::unique_ptr<Layer>>;
public:
  LayerStack() = default;
  ~LayerStack() = default;

  template<inheartedFromLayer T>
  void PushToLayerStack();

  // @return - Pointer to layer, if it not finded return nullptr
  template<inheartedFromLayer T>
  Layer* GetLayer();

  layerStackVectorDef::iterator begin();
  layerStackVectorDef::iterator end();
private:
  layerStackVectorDef m_layers;
};