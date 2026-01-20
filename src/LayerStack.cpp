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
