#include "LayerStack.h"
#include <typeinfo>
#include "Asserts.h"
#include <algorithm>

using layerStackVecDef = std::vector<std::unique_ptr<Layer>>;

layerStackVecDef::iterator LayerStack::begin()
{
  return m_layers.begin();
}

layerStackVecDef::iterator LayerStack::end()
{
  return m_layers.end();
}

template<inheartedFromLayer T>
Layer* LayerStack::GetLayer()
{
  for(auto& layer : m_layers)
  {
    if(typeid(*layer) == typeid(T))
      return &(*layer);
  }

  return nullptr;
}

template<inheartedFromLayer T>
void LayerStack::PushToLayerStack()
{
  xengine_assert(GetLayer<T>() == nullptr);
  m_layers.emplace_back(std::make_unique<T>());
}
