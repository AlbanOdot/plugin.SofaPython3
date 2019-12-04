/*********************************************************************
Copyright 2019, CNRS, University of Lille, INRIA

This file is part of sofaPython3

sofaPython3 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

sofaPython3 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with sofaqtquick. If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/
/********************************************************************
 Contributors:
    - damien.marchal@univ-lille.fr
    - bruno.josue.marques@inria.fr
    - eve.le-guillou@centrale.centralelille.fr
    - jean-nicolas.brunet@inria.fr
    - thierry.gaugry@inria.fr
********************************************************************/

#pragma once

#include "Binding_BaseObject.h"
#include <sofa/core/objectmodel/DataCallback.h>
#include <SofaSimulationGraph/DAGNode.h>

#include <sofa/helper/system/FileMonitor.h>

namespace sofa::core::objectmodel
{
class BasePrefab : public sofa::simulation::graph::DAGNode
{
public:
    SOFA_CLASS(BasePrefab, sofa::simulation::graph::DAGNode);
};
} /// namespace sofa::core::objectmodel

template class pybind11::class_<sofa::core::objectmodel::BasePrefab,
                                sofa::simulation::graph::DAGNode,
                                sofa::core::sptr<sofa::core::objectmodel::BasePrefab>>;

namespace sofapython3
{
using sofa::simulation::graph::DAGNode;
using sofa::core::objectmodel::BasePrefab;
using sofa::core::objectmodel::DataCallback;
using sofa::simulation::MutationListener;
using sofa::simulation::Node;

class Prefab;
class PrefabFileEventListener : public sofa::helper::system::FileEventListener
{
public:
    Prefab* m_prefab;

    void fileHasChanged(const std::string& filename) override;
};


class PrefabMutationListener : public MutationListener
{
public:
    void onEndAddChild(Node *parent, Node *child) override;
    void onEndRemoveChild(Node *parent, Node *child) override;
    void onEndAddObject(Node *parent, BaseObject *object) override;
    void onEndRemoveObject(Node *parent, BaseObject *object) override;
};

class Prefab : public BasePrefab
{
public:
    SOFA_CLASS(Prefab, BasePrefab);
    void init();
    void reinit();
    virtual void doReInit() ;

    void addPrefabParameter(const std::string& name, py::object value, const std::string& help, std::string type);
    void setSourceTracking(const std::string& filename);

    Prefab();
    ~Prefab() override;

    PrefabMutationListener m_mutationListener;
    PrefabFileEventListener m_filelistener;
    DataCallback m_datacallback;
};

void moduleAddPrefab(py::module &m);

} /// namespace sofapython3

