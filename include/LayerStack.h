#pragma once
#include "Layer.h"
#include <vector>
#include <memory>
#include "Asserts.h"

template<typename T> 
concept inheartedFromLayer = std::is_base_of_v<Layer,T>;

class LayerStack
{
private:
  using layerStackVectorDef = std::vector<std::unique_ptr<Layer>>;
public:

  template<inheartedFromLayer T>
  void PushToLayerStack()
  {
    xengine_assert(GetLayer<T>() == nullptr);
    m_layers.emplace_back(std::make_unique<T>());
  }

  // @return - Pointer to layer, if it not finded return nullptr
  template<inheartedFromLayer T>
  Layer* GetLayer()
  {
    for(auto& layer : m_layers)
    {
      if(typeid(*layer) == typeid(T))
      return &(*layer);
    }
  
    return nullptr;
  }

  layerStackVectorDef::iterator begin();
  layerStackVectorDef::iterator end();

  LayerStack() = default;
  ~LayerStack() = default;

  LayerStack(const LayerStack&) = delete;
  void operator=(const LayerStack&) = delete;
  LayerStack(LayerStack&&) = delete;
  void operator=(LayerStack&&) = delete;
private:
  layerStackVectorDef m_layers;
};