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

#include "Binding_BaseLink.h"
#include "Binding_BaseLink_doc.h"

namespace sofapython3
{

void setHelp(BaseLink* self, const std::string value)
{
    /// The copy of a string into a char * is necessary because char * are temporary when using pybind11.
    /// For more information, see : https://github.com/pybind/pybind11/issues/1168
    char * S = new char[value.length() + 1];
    std::strcpy(S,value.c_str());
    self->setHelp(S);
}

void moduleAddBaseLink(py::module& m)
{
    py::class_<BaseLink> link(m, "Link", sofapython3::doc::baseLink::baseLinkClass);
    link.def("getName", &BaseLink::getName, sofapython3::doc::baseLink::getName);
    link.def("setName", &BaseLink::setName, sofapython3::doc::baseLink::setName);
    link.def("isMultiLink", &BaseLink::isMultiLink, sofapython3::doc::baseLink::isMultiLink);

    link.def("isPersistent", &BaseLink::isPersistent, sofapython3::doc::baseLink::isPersistent);
    link.def("setPersistent", &BaseLink::setPersistent, sofapython3::doc::baseLink::setPersistent);

    link.def("isReadOnly", &BaseLink::isReadOnly, sofapython3::doc::baseLink::isReadOnly);
    link.def("getSize", &BaseLink::getSize, sofapython3::doc::baseLink::getSize);
    link.def("getValueString", &BaseLink::getValueString, sofapython3::doc::baseLink::getValueString);
    link.def("getValueTypeString", &BaseLink::getValueTypeString,  sofapython3::doc::baseLink::getValueTypeString);
    link.def("getHelp", &BaseLink::getHelp,  sofapython3::doc::baseLink::getHelp);
    link.def("setHelp", setHelp, sofapython3::doc::baseLink::setHelp);

    link.def("getOwnerData", &BaseLink::getOwnerData, sofapython3::doc::baseLink::getOwnerData);
    link.def("getOwnerBase", &BaseLink::getOwnerBase, sofapython3::doc::baseLink::getOwnerBase);

    link.def("getLinkedData", &BaseLink::getLinkedData, sofapython3::doc::baseLink::getLinkedData);
    link.def("getLinkedBase", &BaseLink::getLinkedBase, sofapython3::doc::baseLink::getLinkedBase);

    link.def("getLinkedPath", &BaseLink::getLinkedPath, sofapython3::doc::baseLink::getLinkedPath);
    link.def("read", &BaseLink::read, sofapython3::doc::baseLink::read);

}

} /// namespace sofapython3
